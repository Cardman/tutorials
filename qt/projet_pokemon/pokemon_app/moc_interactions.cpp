/****************************************************************************
** Meta object code from reading C++ file 'interactions.h'
**
** Created: Wed Jul 11 14:58:00 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/hors_combat/interactions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interactions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Interactions[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Interactions[] = {
    "Interactions\0\0,,\0clic(uchar,uchar,QString)\0"
    "cliquer(QString)\0"
};

const QMetaObject Interactions::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_Interactions,
      qt_meta_data_Interactions, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Interactions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Interactions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Interactions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Interactions))
        return static_cast<void*>(const_cast< Interactions*>(this));
    return QLabel::qt_metacast(_clname);
}

int Interactions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clic((*reinterpret_cast< uchar(*)>(_a[1])),(*reinterpret_cast< uchar(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 1: cliquer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Interactions::clic(uchar _t1, uchar _t2, const QString & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
