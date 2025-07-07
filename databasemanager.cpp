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
 * @brief 获取数据库连接对象
 * @return QSqlDatabase对象
 * 
 * 提供对原始数据库连接对象的访问，用于高级操作
 */
QSqlDatabase DatabaseManager::getDatabase() const
{
    return m_db;
} 