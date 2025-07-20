/****************************************************************************
** Meta object code from reading C++ file 'subsystemclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../subsystemclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'subsystemclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SubsystemClient_t {
    QByteArrayData data[25];
    char stringdata0[388];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SubsystemClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SubsystemClient_t qt_meta_stringdata_SubsystemClient = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SubsystemClient"
QT_MOC_LITERAL(1, 16, 16), // "subsystemStarted"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 16), // "subsystemStopped"
QT_MOC_LITERAL(4, 51, 14), // "subsystemError"
QT_MOC_LITERAL(5, 66, 5), // "error"
QT_MOC_LITERAL(6, 72, 9), // "connected"
QT_MOC_LITERAL(7, 82, 12), // "disconnected"
QT_MOC_LITERAL(8, 95, 15), // "connectionError"
QT_MOC_LITERAL(9, 111, 16), // "responseReceived"
QT_MOC_LITERAL(10, 128, 8), // "response"
QT_MOC_LITERAL(11, 137, 16), // "onProcessStarted"
QT_MOC_LITERAL(12, 154, 17), // "onProcessFinished"
QT_MOC_LITERAL(13, 172, 8), // "exitCode"
QT_MOC_LITERAL(14, 181, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(15, 202, 10), // "exitStatus"
QT_MOC_LITERAL(16, 213, 14), // "onProcessError"
QT_MOC_LITERAL(17, 228, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(18, 251, 17), // "onSocketConnected"
QT_MOC_LITERAL(19, 269, 20), // "onSocketDisconnected"
QT_MOC_LITERAL(20, 290, 13), // "onSocketError"
QT_MOC_LITERAL(21, 304, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(22, 333, 17), // "onSocketReadyRead"
QT_MOC_LITERAL(23, 351, 18), // "onProcessStdOutput"
QT_MOC_LITERAL(24, 370, 17) // "onProcessStdError"

    },
    "SubsystemClient\0subsystemStarted\0\0"
    "subsystemStopped\0subsystemError\0error\0"
    "connected\0disconnected\0connectionError\0"
    "responseReceived\0response\0onProcessStarted\0"
    "onProcessFinished\0exitCode\0"
    "QProcess::ExitStatus\0exitStatus\0"
    "onProcessError\0QProcess::ProcessError\0"
    "onSocketConnected\0onSocketDisconnected\0"
    "onSocketError\0QAbstractSocket::SocketError\0"
    "onSocketReadyRead\0onProcessStdOutput\0"
    "onProcessStdError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SubsystemClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    1,   96,    2, 0x06 /* Public */,
       6,    0,   99,    2, 0x06 /* Public */,
       7,    0,  100,    2, 0x06 /* Public */,
       8,    1,  101,    2, 0x06 /* Public */,
       9,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  107,    2, 0x08 /* Private */,
      12,    2,  108,    2, 0x08 /* Private */,
      16,    1,  113,    2, 0x08 /* Private */,
      18,    0,  116,    2, 0x08 /* Private */,
      19,    0,  117,    2, 0x08 /* Private */,
      20,    1,  118,    2, 0x08 /* Private */,
      22,    0,  121,    2, 0x08 /* Private */,
      23,    0,  122,    2, 0x08 /* Private */,
      24,    0,  123,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14,   13,   15,
    QMetaType::Void, 0x80000000 | 17,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SubsystemClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SubsystemClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->subsystemStarted(); break;
        case 1: _t->subsystemStopped(); break;
        case 2: _t->subsystemError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->connected(); break;
        case 4: _t->disconnected(); break;
        case 5: _t->connectionError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->responseReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->onProcessStarted(); break;
        case 8: _t->onProcessFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 9: _t->onProcessError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 10: _t->onSocketConnected(); break;
        case 11: _t->onSocketDisconnected(); break;
        case 12: _t->onSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 13: _t->onSocketReadyRead(); break;
        case 14: _t->onProcessStdOutput(); break;
        case 15: _t->onProcessStdError(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SubsystemClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SubsystemClient::subsystemStarted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SubsystemClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SubsystemClient::subsystemStopped)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SubsystemClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SubsystemClient::subsystemError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SubsystemClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SubsystemClient::connected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SubsystemClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SubsystemClient::disconnected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SubsystemClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SubsystemClient::connectionError)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SubsystemClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SubsystemClient::responseReceived)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SubsystemClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SubsystemClient.data,
    qt_meta_data_SubsystemClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SubsystemClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SubsystemClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SubsystemClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SubsystemClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void SubsystemClient::subsystemStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SubsystemClient::subsystemStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SubsystemClient::subsystemError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SubsystemClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SubsystemClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SubsystemClient::connectionError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SubsystemClient::responseReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
