/****************************************************************************
** Meta object code from reading C++ file 'gestioninventaire.h'
**
** Created: Tue Jul 17 13:01:25 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/hors_combat/gestioninventaire.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gestioninventaire.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GestionInventaire[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      34,   18,   18,   18, 0x05,
      50,   18,   18,   18, 0x05,
      67,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      83,   18,   18,   18, 0x08,
     101,   18,   18,   18, 0x08,
     122,  120,   18,   18, 0x08,
     145,   18,   18,   18, 0x08,
     156,   18,   18,   18, 0x08,
     167,   18,   18,   18, 0x08,
     177,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GestionInventaire[] = {
    "GestionInventaire\0\0attacher_obj()\0"
    "utiliser(uchar)\0apprendre(uchar)\0"
    "gestion_finie()\0maj_action(uchar)\0"
    "maj_objet(QString)\0,\0maj_objet(QString,int)\0"
    "attacher()\0utiliser()\0annuler()\0finir()\0"
};

const QMetaObject GestionInventaire::staticMetaObject = {
    { &QSplitter::staticMetaObject, qt_meta_stringdata_GestionInventaire,
      qt_meta_data_GestionInventaire, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GestionInventaire::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GestionInventaire::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GestionInventaire::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GestionInventaire))
        return static_cast<void*>(const_cast< GestionInventaire*>(this));
    return QSplitter::qt_metacast(_clname);
}

int GestionInventaire::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplitter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: attacher_obj(); break;
        case 1: utiliser((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 2: apprendre((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 3: gestion_finie(); break;
        case 4: maj_action((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 5: maj_objet((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: maj_objet((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: attacher(); break;
        case 8: utiliser(); break;
        case 9: annuler(); break;
        case 10: finir(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void GestionInventaire::attacher_obj()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GestionInventaire::utiliser(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GestionInventaire::apprendre(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GestionInventaire::gestion_finie()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
