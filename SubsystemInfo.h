#ifndef SUBSYSTEMINFO_H
#define SUBSYSTEMINFO_H

#include <QString>

struct SubsystemInfo {
    QString name;               // 如：system1
    QString path;               // 可执行文件路径
    QString host = "localhost"; // 默认本机
    quint16 port;               // 通信端口，如 8080, 8081 ...
};


#endif // SUBSYSTEMINFO_H
