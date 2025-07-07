#include "databasemanager.h"
#include <QDebug>
#include <QCryptographicHash>
#include <QDir>

/**
 * @brief 构造函数
 * 初始化成员变量，设置数据库未初始化状态
 */
DatabaseManager::DatabaseManager() : m_isInitialized(false)
{
}

/**
 * @brief 析构函数
 * 自动关闭数据库连接
 */
DatabaseManager::~DatabaseManager()
{
    closeDatabase();
}

/**
 * @brief 获取单例实例
 * @return DatabaseManager的静态实例引用
 * 
 * 使用静态局部变量确保线程安全的单例模式
 */
DatabaseManager& DatabaseManager::getInstance()
{
    static DatabaseManager instance;
    return instance;
}

/**
 * @brief 初始化数据库连接
 * @param dbPath 数据库文件路径
 * @return 初始化是否成功
 * 
 * 步骤：
 * 1. 保存数据库路径
 * 2. 确保目录存在
 * 3. 创建SQLite数据库连接
 * 4. 打开数据库
 * 5. 创建用户表
 */
bool DatabaseManager::initDatabase(const QString &dbPath)
{
    m_dbPath = dbPath;
    
    // 确保数据库目录存在
    QDir dir;
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    // 创建数据库连接，使用唯一的连接名避免冲突
    m_db = QSqlDatabase::addDatabase("QSQLITE", "mainsystem_connection");
    m_db.setDatabaseName(m_dbPath);
    
    // 打开数据库
    if (!m_db.open()) {
        qDebug() << "Failed to open database:" << m_db.lastError().text();
        return false;
    }
    
    m_isInitialized = true;
    qDebug() << "Database initialized successfully:" << m_dbPath;
    
    // 创建用户表
    if (!createUserTable()) {
        qDebug() << "Failed to create user table";
        return false;
    }
    // 创建权限组表
    if (!createGroupsTable()) {
        qDebug() << "Failed to create groups table";
        return false;
    }
    
    return true;

    // 自动化检查表结构（调试用，确认无误后可移除）
    QSqlQuery checkQuery(m_db);
    qDebug() << "[users] table structure:";
    checkQuery.exec("PRAGMA table_info(users)");
    while (checkQuery.next()) {
        qDebug() << checkQuery.value(1).toString() << checkQuery.value(2).toString();
    }
    qDebug() << "[groups] table structure:";
    checkQuery.exec("PRAGMA table_info(groups)");
    while (checkQuery.next()) {
        qDebug() << checkQuery.value(1).toString() << checkQuery.value(2).toString();
    }
}

/**
 * @brief 检查数据库连接状态
 * @return 数据库是否已连接且已初始化
 */
bool DatabaseManager::isConnected() const
{
    return m_isInitialized && m_db.isOpen();
}

/**
 * @brief 关闭数据库连接
 * 关闭数据库并重置初始化状态
 */
void DatabaseManager::closeDatabase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
    m_isInitialized = false;
}

/**
 * @brief 创建用户表
 * @return 创建是否成功
 * 
 * 表结构：
 * - id: 主键，自增
 * - username: 用户名，唯一，非空
 * - password: 密码（加密存储），非空
 * - created_time: 创建时间，默认为当前时间戳
 */
bool DatabaseManager::createUserTable()
{
    if (!isConnected()) {
        qDebug() << "Database not connected";
        return false;
    }
    
    QSqlQuery query(m_db);
    QString createTableSQL = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password TEXT NOT NULL, "
        "`group` INTEGER NOT NULL DEFAULT -1, "
        "isRightToSystem1 INTEGER DEFAULT 0, "
        "isRightToSystem2 INTEGER DEFAULT 0, "
        "isRightToSystem3 INTEGER DEFAULT 0, "
        "isRightToSystem4 INTEGER DEFAULT 0, "
        "isRightToSystem5 INTEGER DEFAULT 0, "
        "created_time DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";
    
    if (!query.exec(createTableSQL)) {
        qDebug() << "Failed to create user table:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "User table created successfully";
    return true;
}

/**
 * @brief 创建权限组表
 * @return 创建是否成功
 * 
 * 表结构：
 * - group_id: 主键
 * - group_name: 组名
 * - isRightToSystem1~5: 权限
 */
bool DatabaseManager::createGroupsTable()
{
    if (!isConnected()) {
        qDebug() << "Database not connected";
        return false;
    }
    QSqlQuery query(m_db);
    QString createTableSQL =
        "CREATE TABLE IF NOT EXISTS groups ("
        "group_id INTEGER PRIMARY KEY, "
        "group_name TEXT NOT NULL, "
        "isRightToSystem1 INTEGER DEFAULT 0, "
        "isRightToSystem2 INTEGER DEFAULT 0, "
        "isRightToSystem3 INTEGER DEFAULT 0, "
        "isRightToSystem4 INTEGER DEFAULT 0, "
        "isRightToSystem5 INTEGER DEFAULT 0"
        ");";
    if (!query.exec(createTableSQL)) {
        qDebug() << "Failed to create groups table:" << query.lastError().text();
        return false;
    }
    qDebug() << "Groups table created successfully";
    return true;
}

/**
 * @brief 注册新用户
 * @param username 用户名
 * @param password 密码（明文）
 * @return 注册是否成功
 * 
 * 注册流程：
 * 1. 检查数据库连接
 * 2. 检查用户是否已存在
 * 3. 对密码进行SHA256加密
 * 4. 插入用户记录到数据库
 */
bool DatabaseManager::registerUser(const QString &username, const QString &password)
{
    if (!isConnected()) {
        qDebug() << "Database not connected";
        return false;
    }
    
    // 检查用户是否已存在
    if (isUserExists(username)) {
        qDebug() << "User already exists:" << username;
        return false;
    }
    
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (username, password) VALUES (?, ?)");
    query.addBindValue(username);
    
    // 密码加密存储 - 使用SHA256算法
    QString hashedPassword = QString(QCryptographicHash::hash(
        password.toUtf8(), QCryptographicHash::Sha256).toHex());
    query.addBindValue(hashedPassword);
    
    if (!query.exec()) {
        qDebug() << "Failed to register user:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "User registered successfully:" << username;
    return true;
}

/**
 * @brief 用户登录验证
 * @param username 用户名
 * @param password 密码（明文）
 * @return 登录是否成功
 * 
 * 登录验证流程：
 * 1. 检查数据库连接
 * 2. 根据用户名查询数据库
 * 3. 对输入的密码进行SHA256加密
 * 4. 比较加密后的密码与数据库中存储的密码
 */
bool DatabaseManager::loginUser(const QString &username, const QString &password)
{
    if (!isConnected()) {
        qDebug() << "Database not connected";
        return false;
    }
    
    QSqlQuery query(m_db);
    query.prepare("SELECT password FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (!query.exec()) {
        qDebug() << "Failed to query user:" << query.lastError().text();
        return false;
    }
    
    if (!query.next()) {
        qDebug() << "User not found:" << username;
        return false;
    }
    
    // 验证密码 - 比较加密后的密码
    QString storedPassword = query.value(0).toString();
    QString hashedPassword = QString(QCryptographicHash::hash(
        password.toUtf8(), QCryptographicHash::Sha256).toHex());
    
    bool isValid = (storedPassword == hashedPassword);
    qDebug() << "Login attempt for user" << username << ":" << (isValid ? "success" : "failed");
    
    return isValid;
}

/**
 * @brief 检查用户是否存在
 * @param username 用户名
 * @return 用户是否存在
 * 
 * 通过COUNT查询检查用户是否存在，避免重复注册
 */
bool DatabaseManager::isUserExists(const QString &username)
{
    if (!isConnected()) {
        return false;
    }
    
    QSqlQuery query(m_db);
    query.prepare("SELECT COUNT(*) FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (!query.exec() || !query.next()) {
        return false;
    }
    
    return query.value(0).toInt() > 0;
}

/**
 * @brief 获取数据库连接对象
 * @return QSqlDatabase对象
 * 
 * 提供对原始数据库连接对象的访问，用于高级操作
 */
QSqlDatabase DatabaseManager::getDatabase() const
{
    return m_db;
} 