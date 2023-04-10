/****************************************************************************
** Meta object code from reading C++ file 'bouton.h'
**
** Created: Thu Jul 12 22:41:47 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/boutons/bouton.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bouton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Bouton[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      15,    7,    7,    7, 0x05,
      31,   29,    7,    7, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Bouton[] = {
    "Bouton\0\0clic()\0clic(QString)\0,\0"
    "clic(QString,int)\0"
};

const QMetaObject Bouton::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_Bouton,
      qt_meta_data_Bouton, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Bouton::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Bouton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Bouton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Bouton))
        return static_cast<void*>(const_cast< Bouton*>(this));
    return QLabel::qt_metacast(_clname);
}

int Bouton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clic(); break;
        case 1: clic((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: clic((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Bouton::clic()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Bouton::clic(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Bouton::clic(const QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
