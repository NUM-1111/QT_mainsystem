/****************************************************************************
** Meta object code from reading C++ file 'groupmanagerdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../groupmanagerdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'groupmanagerdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GroupManagerDialog_t {
    QByteArrayData data[13];
    char stringdata0[287];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GroupManagerDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GroupManagerDialog_t qt_meta_stringdata_GroupManagerDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "GroupManagerDialog"
QT_MOC_LITERAL(1, 19, 22), // "on_btnAddGroup_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 25), // "on_btnDeleteGroup_clicked"
QT_MOC_LITERAL(4, 69, 18), // "on_btnSave_clicked"
QT_MOC_LITERAL(5, 88, 19), // "on_btnReset_clicked"
QT_MOC_LITERAL(6, 108, 35), // "on_tableGroups_itemSelectionC..."
QT_MOC_LITERAL(7, 144, 26), // "on_checkSubsystem1_toggled"
QT_MOC_LITERAL(8, 171, 7), // "checked"
QT_MOC_LITERAL(9, 179, 26), // "on_checkSubsystem2_toggled"
QT_MOC_LITERAL(10, 206, 26), // "on_checkSubsystem3_toggled"
QT_MOC_LITERAL(11, 233, 26), // "on_checkSubsystem4_toggled"
QT_MOC_LITERAL(12, 260, 26) // "on_checkSubsystem5_toggled"

    },
    "GroupManagerDialog\0on_btnAddGroup_clicked\0"
    "\0on_btnDeleteGroup_clicked\0"
    "on_btnSave_clicked\0on_btnReset_clicked\0"
    "on_tableGroups_itemSelectionChanged\0"
    "on_checkSubsystem1_toggled\0checked\0"
    "on_checkSubsystem2_toggled\0"
    "on_checkSubsystem3_toggled\0"
    "on_checkSubsystem4_toggled\0"
    "on_checkSubsystem5_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GroupManagerDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    1,   69,    2, 0x08 /* Private */,
       9,    1,   72,    2, 0x08 /* Private */,
      10,    1,   75,    2, 0x08 /* Private */,
      11,    1,   78,    2, 0x08 /* Private */,
      12,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void GroupManagerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroupManagerDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnAddGroup_clicked(); break;
        case 1: _t->on_btnDeleteGroup_clicked(); break;
        case 2: _t->on_btnSave_clicked(); break;
        case 3: _t->on_btnReset_clicked(); break;
        case 4: _t->on_tableGroups_itemSelectionChanged(); break;
        case 5: _t->on_checkSubsystem1_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_checkSubsystem2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_checkSubsystem3_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_checkSubsystem4_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_checkSubsystem5_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GroupManagerDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_GroupManagerDialog.data,
    qt_meta_data_GroupManagerDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GroupManagerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GroupManagerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GroupManagerDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int GroupManagerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
