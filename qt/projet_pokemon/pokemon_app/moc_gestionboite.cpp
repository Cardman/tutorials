/****************************************************************************
** Meta object code from reading C++ file 'gestionboite.h'
**
** Created: Tue Jul 17 11:33:29 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/hors_combat/gestionboite.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gestionboite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GestionBoite[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      32,   30,   13,   13, 0x05,
      79,   30,   13,   13, 0x05,
     125,   13,   13,   13, 0x05,
     155,   30,   13,   13, 0x05,
     187,   13,   13,   13, 0x05,
     215,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     244,   13,   13,   13, 0x08,
     260,   13,   13,   13, 0x08,
     287,   13,   13,   13, 0x08,
     314,   13,   13,   13, 0x08,
     338,   13,   13,   13, 0x08,
     364,  361,   13,   13, 0x08,
     413,  361,   13,   13, 0x08,
     462,   13,   13,   13, 0x08,
     480,   13,   13,   13, 0x08,
     497,   13,   13,   13, 0x08,
     513,   13,   13,   13, 0x08,
     521,   13,   13,   13, 0x08,
     531,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GestionBoite[] = {
    "GestionBoite\0\0gestion_finie()\0,\0"
    "echange_pokemon(QPair<int,int>,QPair<int,int>)\0"
    "echange_objets(QPair<int,int>,QPair<int,int>)\0"
    "ranger_objets(QPair<int,int>)\0"
    "depos(uchar,QPair<uchar,uchar>)\0"
    "retrait(QPair<uchar,uchar>)\0"
    "relacher(QPair<uchar,uchar>)\0"
    "finir_gestion()\0maj_indice_boite_1(Entier)\0"
    "maj_indice_boite_2(Entier)\0"
    "voir_fiche_pk_ut(uchar)\0voir_fiche_oeuf(uchar)\0"
    ",,\0voir_fiche_boite_1(QPair<uchar,uchar>,bool,bool)\0"
    "voir_fiche_boite_2(QPair<uchar,uchar>,bool,bool)\0"
    "echange_pokemon()\0echange_objets()\0"
    "ranger_objets()\0depos()\0retrait()\0"
    "relacher()\0"
};

const QMetaObject GestionBoite::staticMetaObject = {
    { &QSplitter::staticMetaObject, qt_meta_stringdata_GestionBoite,
      qt_meta_data_GestionBoite, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GestionBoite::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GestionBoite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GestionBoite::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GestionBoite))
        return static_cast<void*>(const_cast< GestionBoite*>(this));
    return QSplitter::qt_metacast(_clname);
}

int GestionBoite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplitter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: gestion_finie(); break;
        case 1: echange_pokemon((*reinterpret_cast< const QPair<int,int>(*)>(_a[1])),(*reinterpret_cast< const QPair<int,int>(*)>(_a[2]))); break;
        case 2: echange_objets((*reinterpret_cast< const QPair<int,int>(*)>(_a[1])),(*reinterpret_cast< const QPair<int,int>(*)>(_a[2]))); break;
        case 3: ranger_objets((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 4: depos((*reinterpret_cast< uchar(*)>(_a[1])),(*reinterpret_cast< const QPair<uchar,uchar>(*)>(_a[2]))); break;
        case 5: retrait((*reinterpret_cast< const QPair<uchar,uchar>(*)>(_a[1]))); break;
        case 6: relacher((*reinterpret_cast< const QPair<uchar,uchar>(*)>(_a[1]))); break;
        case 7: finir_gestion(); break;
        case 8: maj_indice_boite_1((*reinterpret_cast< const Entier(*)>(_a[1]))); break;
        case 9: maj_indice_boite_2((*reinterpret_cast< const Entier(*)>(_a[1]))); break;
        case 10: voir_fiche_pk_ut((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 11: voir_fiche_oeuf((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 12: voir_fiche_boite_1((*reinterpret_cast< const QPair<uchar,uchar>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 13: voir_fiche_boite_2((*reinterpret_cast< const QPair<uchar,uchar>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 14: echange_pokemon(); break;
        case 15: echange_objets(); break;
        case 16: ranger_objets(); break;
        case 17: depos(); break;
        case 18: retrait(); break;
        case 19: relacher(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void GestionBoite::gestion_finie()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GestionBoite::echange_pokemon(const QPair<int,int> & _t1, const QPair<int,int> & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GestionBoite::echange_objets(const QPair<int,int> & _t1, const QPair<int,int> & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GestionBoite::ranger_objets(const QPair<int,int> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GestionBoite::depos(uchar _t1, const QPair<uchar,uchar> & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GestionBoite::retrait(const QPair<uchar,uchar> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GestionBoite::relacher(const QPair<uchar,uchar> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
