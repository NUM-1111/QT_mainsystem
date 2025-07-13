/****************************************************************************
** Meta object code from reading C++ file 'usermanagerdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../usermanagerdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usermanagerdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UserManagerDialog_t {
    QByteArrayData data[16];
    char stringdata0[345];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UserManagerDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UserManagerDialog_t qt_meta_stringdata_UserManagerDialog = {
    {
QT_MOC_LITERAL(0, 0, 17), // "UserManagerDialog"
QT_MOC_LITERAL(1, 18, 21), // "on_btnRefresh_clicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 21), // "on_btnAddUser_clicked"
QT_MOC_LITERAL(4, 63, 24), // "on_btnDeleteUser_clicked"
QT_MOC_LITERAL(5, 88, 34), // "on_tableUsers_itemSelectionCh..."
QT_MOC_LITERAL(6, 123, 33), // "on_comboGroup_currentIndexCha..."
QT_MOC_LITERAL(7, 157, 5), // "index"
QT_MOC_LITERAL(8, 163, 26), // "on_checkSubsystem1_toggled"
QT_MOC_LITERAL(9, 190, 7), // "checked"
QT_MOC_LITERAL(10, 198, 26), // "on_checkSubsystem2_toggled"
QT_MOC_LITERAL(11, 225, 26), // "on_checkSubsystem3_toggled"
QT_MOC_LITERAL(12, 252, 26), // "on_checkSubsystem4_toggled"
QT_MOC_LITERAL(13, 279, 26), // "on_checkSubsystem5_toggled"
QT_MOC_LITERAL(14, 306, 18), // "on_btnSave_clicked"
QT_MOC_LITERAL(15, 325, 19) // "on_btnReset_clicked"

    },
    "UserManagerDialog\0on_btnRefresh_clicked\0"
    "\0on_btnAddUser_clicked\0on_btnDeleteUser_clicked\0"
    "on_tableUsers_itemSelectionChanged\0"
    "on_comboGroup_currentIndexChanged\0"
    "index\0on_checkSubsystem1_toggled\0"
    "checked\0on_checkSubsystem2_toggled\0"
    "on_checkSubsystem3_toggled\0"
    "on_checkSubsystem4_toggled\0"
    "on_checkSubsystem5_toggled\0"
    "on_btnSave_clicked\0on_btnReset_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserManagerDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    1,   78,    2, 0x08 /* Private */,
       8,    1,   81,    2, 0x08 /* Private */,
      10,    1,   84,    2, 0x08 /* Private */,
      11,    1,   87,    2, 0x08 /* Private */,
      12,    1,   90,    2, 0x08 /* Private */,
      13,    1,   93,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UserManagerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserManagerDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnRefresh_clicked(); break;
        case 1: _t->on_btnAddUser_clicked(); break;
        case 2: _t->on_btnDeleteUser_clicked(); break;
        case 3: _t->on_tableUsers_itemSelectionChanged(); break;
        case 4: _t->on_comboGroup_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_checkSubsystem1_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_checkSubsystem2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_checkSubsystem3_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_checkSubsystem4_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_checkSubsystem5_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_btnSave_clicked(); break;
        case 11: _t->on_btnReset_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UserManagerDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_UserManagerDialog.data,
    qt_meta_data_UserManagerDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UserManagerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserManagerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UserManagerDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int UserManagerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
