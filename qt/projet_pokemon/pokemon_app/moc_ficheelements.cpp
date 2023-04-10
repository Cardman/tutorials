/****************************************************************************
** Meta object code from reading C++ file 'ficheelements.h'
**
** Created: Wed Jul 18 22:15:49 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/combat/fiches/ficheelements.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ficheelements.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FicheElements[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      32,   14,   14,   14, 0x08,
      54,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FicheElements[] = {
    "FicheElements\0\0maj_fiche(uchar)\0"
    "maj_fiche(Combattant)\0maj_fiche(QPair<int,int>)\0"
};

const QMetaObject FicheElements::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_FicheElements,
      qt_meta_data_FicheElements, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FicheElements::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FicheElements::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FicheElements::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FicheElements))
        return static_cast<void*>(const_cast< FicheElements*>(this));
    return QLabel::qt_metacast(_clname);
}

int FicheElements::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: maj_fiche((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 1: maj_fiche((*reinterpret_cast< const Combattant(*)>(_a[1]))); break;
        case 2: maj_fiche((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
