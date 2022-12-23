/****************************************************************************
** Meta object code from reading C++ file 'texteditor_self.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../texteditor_self.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'texteditor_self.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Texteditor_self_t {
    QByteArrayData data[8];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Texteditor_self_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Texteditor_self_t qt_meta_stringdata_Texteditor_self = {
    {
QT_MOC_LITERAL(0, 0, 15), // "Texteditor_self"
QT_MOC_LITERAL(1, 16, 8), // "SaveFile"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "LoadFile"
QT_MOC_LITERAL(4, 35, 4), // "Undo"
QT_MOC_LITERAL(5, 40, 4), // "Redo"
QT_MOC_LITERAL(6, 45, 23), // "on_textEdit_textChanged"
QT_MOC_LITERAL(7, 69, 9) // "initstack"

    },
    "Texteditor_self\0SaveFile\0\0LoadFile\0"
    "Undo\0Redo\0on_textEdit_textChanged\0"
    "initstack"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Texteditor_self[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Texteditor_self::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Texteditor_self *_t = static_cast<Texteditor_self *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SaveFile(); break;
        case 1: _t->LoadFile(); break;
        case 2: _t->Undo(); break;
        case 3: _t->Redo(); break;
        case 4: _t->on_textEdit_textChanged(); break;
        case 5: _t->initstack(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Texteditor_self::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Texteditor_self.data,
      qt_meta_data_Texteditor_self,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Texteditor_self::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Texteditor_self::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Texteditor_self.stringdata0))
        return static_cast<void*>(const_cast< Texteditor_self*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Texteditor_self::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
