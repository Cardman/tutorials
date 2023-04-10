/****************************************************************************
** Meta object code from reading C++ file 'dialoguesql.h'
**
** Created: Tue Jun 12 11:16:25 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialoguesql.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoguesql.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueSql[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DialogueSql[] = {
    "DialogueSql\0\0resultat()\0"
};

const QMetaObject DialogueSql::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueSql,
      qt_meta_data_DialogueSql, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueSql::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueSql::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueSql::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueSql))
        return static_cast<void*>(const_cast< DialogueSql*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueSql::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: resultat(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
