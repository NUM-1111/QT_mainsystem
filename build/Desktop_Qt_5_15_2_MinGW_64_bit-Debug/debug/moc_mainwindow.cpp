/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[338];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 24), // "on_btnSubsystem1_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 24), // "on_btnSubsystem2_clicked"
QT_MOC_LITERAL(4, 62, 24), // "on_btnSubsystem3_clicked"
QT_MOC_LITERAL(5, 87, 24), // "on_btnSubsystem4_clicked"
QT_MOC_LITERAL(6, 112, 24), // "on_btnSubsystem5_clicked"
QT_MOC_LITERAL(7, 137, 23), // "on_btnViewUsers_clicked"
QT_MOC_LITERAL(8, 161, 24), // "on_btnViewGroups_clicked"
QT_MOC_LITERAL(9, 186, 18), // "onSubsystemStarted"
QT_MOC_LITERAL(10, 205, 18), // "onSubsystemStopped"
QT_MOC_LITERAL(11, 224, 16), // "onSubsystemError"
QT_MOC_LITERAL(12, 241, 5), // "error"
QT_MOC_LITERAL(13, 247, 11), // "onConnected"
QT_MOC_LITERAL(14, 259, 14), // "onDisconnected"
QT_MOC_LITERAL(15, 274, 17), // "onConnectionError"
QT_MOC_LITERAL(16, 292, 18), // "onResponseReceived"
QT_MOC_LITERAL(17, 311, 8), // "response"
QT_MOC_LITERAL(18, 320, 17) // "onConnectionTimer"

    },
    "MainWindow\0on_btnSubsystem1_clicked\0"
    "\0on_btnSubsystem2_clicked\0"
    "on_btnSubsystem3_clicked\0"
    "on_btnSubsystem4_clicked\0"
    "on_btnSubsystem5_clicked\0"
    "on_btnViewUsers_clicked\0"
    "on_btnViewGroups_clicked\0onSubsystemStarted\0"
    "onSubsystemStopped\0onSubsystemError\0"
    "error\0onConnected\0onDisconnected\0"
    "onConnectionError\0onResponseReceived\0"
    "response\0onConnectionTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    1,   98,    2, 0x08 /* Private */,
      13,    0,  101,    2, 0x08 /* Private */,
      14,    0,  102,    2, 0x08 /* Private */,
      15,    1,  103,    2, 0x08 /* Private */,
      16,    1,  106,    2, 0x08 /* Private */,
      18,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnSubsystem1_clicked(); break;
        case 1: _t->on_btnSubsystem2_clicked(); break;
        case 2: _t->on_btnSubsystem3_clicked(); break;
        case 3: _t->on_btnSubsystem4_clicked(); break;
        case 4: _t->on_btnSubsystem5_clicked(); break;
        case 5: _t->on_btnViewUsers_clicked(); break;
        case 6: _t->on_btnViewGroups_clicked(); break;
        case 7: _t->onSubsystemStarted(); break;
        case 8: _t->onSubsystemStopped(); break;
        case 9: _t->onSubsystemError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->onConnected(); break;
        case 11: _t->onDisconnected(); break;
        case 12: _t->onConnectionError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->onResponseReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->onConnectionTimer(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
