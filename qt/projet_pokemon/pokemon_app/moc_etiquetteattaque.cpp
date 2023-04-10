/****************************************************************************
** Meta object code from reading C++ file 'etiquetteattaque.h'
**
** Created: Tue Jul 10 13:27:18 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/combat/etiquettes/etiquetteattaque.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'etiquetteattaque.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EtiquetteAttaque[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_EtiquetteAttaque[] = {
    "EtiquetteAttaque\0\0clic(QString)\0"
};

const QMetaObject EtiquetteAttaque::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_EtiquetteAttaque,
      qt_meta_data_EtiquetteAttaque, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EtiquetteAttaque::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EtiquetteAttaque::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EtiquetteAttaque::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EtiquetteAttaque))
        return static_cast<void*>(const_cast< EtiquetteAttaque*>(this));
    return QLabel::qt_metacast(_clname);
}

int EtiquetteAttaque::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clic((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void EtiquetteAttaque::clic(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
