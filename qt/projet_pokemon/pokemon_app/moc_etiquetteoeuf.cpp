/****************************************************************************
** Meta object code from reading C++ file 'etiquetteoeuf.h'
**
** Created: Fri Jul 13 10:22:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/hors_combat/etiquettes/etiquetteoeuf.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'etiquetteoeuf.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EtiquetteOeuf[] = {

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
      15,   14,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_EtiquetteOeuf[] = {
    "EtiquetteOeuf\0\0clic(uchar)\0"
};

const QMetaObject EtiquetteOeuf::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_EtiquetteOeuf,
      qt_meta_data_EtiquetteOeuf, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EtiquetteOeuf::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EtiquetteOeuf::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EtiquetteOeuf::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EtiquetteOeuf))
        return static_cast<void*>(const_cast< EtiquetteOeuf*>(this));
    return QLabel::qt_metacast(_clname);
}

int EtiquetteOeuf::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clic((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void EtiquetteOeuf::clic(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
