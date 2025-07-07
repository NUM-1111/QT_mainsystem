#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

/**
 * @brief 数据库管理器类
 * 
 * 使用单例模式管理整个应用程序的数据库连接和操作
 * 负责用户表的创建、用户注册、登录验证等功能
 */
class DatabaseManager
{
public:
    /**
     * @brief 获取数据库管理器单例实例
     * @return DatabaseManager的引用
     */
    static DatabaseManager& getInstance();
    
    /**
     * @brief 初始化数据库连接
     * @param dbPath 数据库文件路径，默认为"mainsystem.db"
     * @return 初始化是否成功
     */
    bool initDatabase(const QString &dbPath = "mainsystem.db");
    
    /**
     * @brief 检查数据库是否已连接
     * @return 连接状态
     */
    bool isConnected() const;
    
    /**
     * @brief 关闭数据库连接
     */
    void closeDatabase();
    
    // ========== 用户表操作 ==========
    
    /**
     * @brief 创建用户表
     * @return 创建是否成功
     */
    bool createUserTable();
    
    /**
     * @brief 创建群组表
     * @return 创建是否成功
     */
    bool createGroupsTable();
    
    /**
     * @brief 获取数据库连接对象
     * @return QSqlDatabase对象
     */
    QSqlDatabase getDatabase() const;

private:
    /**
     * @brief 私有构造函数（单例模式）
     */
    DatabaseManager();
    
    /**
     * @brief 析构函数
     */
    ~DatabaseManager();
    
    // 禁用拷贝构造和赋值操作（单例模式）
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    
    QSqlDatabase m_db;        ///< 数据库连接对象
    QString m_dbPath;         ///< 数据库文件路径
    bool m_isInitialized;     ///< 数据库是否已初始化
};

#endif // DATABASEMANAGER_H 