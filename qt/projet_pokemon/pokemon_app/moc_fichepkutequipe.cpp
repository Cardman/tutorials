/****************************************************************************
** Meta object code from reading C++ file 'fichepkutequipe.h'
**
** Created: Thu Jul 19 21:44:08 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/hors_combat/fiches/fichepkutequipe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fichepkutequipe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FichePkUtEquipe[] = {

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
      19,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FichePkUtEquipe[] = {
    "FichePkUtEquipe\0\0,\0choix_attaque(QString,int)\0"
    "maj_description(QString)\0"
};

const QMetaObject FichePkUtEquipe::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_FichePkUtEquipe,
      qt_meta_data_FichePkUtEquipe, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FichePkUtEquipe::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FichePkUtEquipe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FichePkUtEquipe::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FichePkUtEquipe))
        return static_cast<void*>(const_cast< FichePkUtEquipe*>(this));
    return QLabel::qt_metacast(_clname);
}

int FichePkUtEquipe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: choix_attaque((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: maj_description((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FichePkUtEquipe::choix_attaque(const QString & _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
