/****************************************************************************
** Meta object code from reading C++ file 'evolution.h'
**
** Created: Tue Jun 26 23:39:59 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "base_donnees/evolution/evolution.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'evolution.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Evolution[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_Evolution[] = {
    "Evolution\0"
};

const QMetaObject Evolution::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Evolution,
      qt_meta_data_Evolution, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Evolution::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Evolution::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Evolution::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Evolution))
        return static_cast<void*>(const_cast< Evolution*>(this));
    return QObject::qt_metacast(_clname);
}

int Evolution::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE