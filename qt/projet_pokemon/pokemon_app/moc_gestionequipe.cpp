/****************************************************************************
** Meta object code from reading C++ file 'gestionequipe.h'
**
** Created: Tue Jul 17 11:33:28 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/hors_combat/gestionequipe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gestionequipe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GestionEquipe[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      21,   14,   14,   14, 0x05,
      35,   14,   14,   14, 0x05,
      65,   14,   14,   14, 0x05,
      96,   14,   14,   14, 0x05,
     119,   14,   14,   14, 0x05,
     146,  143,   14,   14, 0x05,
     184,  143,   14,   14, 0x05,
     217,  215,   14,   14, 0x05,
     240,   14,   14,   14, 0x05,
     256,   14,   14,   14, 0x05,
     269,   14,   14,   14, 0x05,
     281,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     298,   14,   14,   14, 0x08,
     308,   14,   14,   14, 0x08,
     324,   14,   14,   14, 0x08,
     343,   14,   14,   14, 0x08,
     360,   14,   14,   14, 0x08,
     378,   14,   14,   14, 0x08,
     402,   14,   14,   14, 0x08,
     425,  215,   14,   14, 0x08,
     460,   14,   14,   14, 0x08,
     481,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GestionEquipe[] = {
    "GestionEquipe\0\0vol()\0fin_gestion()\0"
    "echange_place(QPair<int,int>)\0"
    "echange_objets(QPair<int,int>)\0"
    "rangement_objet(uchar)\0pension(QPair<int,int>)\0"
    ",,\0appris_move_tutors(QString,uchar,int)\0"
    "move_tutors(QString,uchar,int)\0,\0"
    "evoluer(QString,uchar)\0attacher(uchar)\0"
    "boost(uchar)\0soin(uchar)\0soin_baie(uchar)\0"
    "annuler()\0finir_gestion()\0echange_position()\0"
    "echange_objets()\0rangement_objet()\0"
    "voir_fiche_pk_ut(uchar)\0voir_fiche_oeuf(uchar)\0"
    "apprendre_move_tutors(QString,int)\0"
    "move_tutors(QString)\0voler()\0"
};

const QMetaObject GestionEquipe::staticMetaObject = {
    { &QSplitter::staticMetaObject, qt_meta_stringdata_GestionEquipe,
      qt_meta_data_GestionEquipe, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GestionEquipe::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GestionEquipe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GestionEquipe::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GestionEquipe))
        return static_cast<void*>(const_cast< GestionEquipe*>(this));
    return QSplitter::qt_metacast(_clname);
}

int GestionEquipe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplitter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: vol(); break;
        case 1: fin_gestion(); break;
        case 2: echange_place((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 3: echange_objets((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 4: rangement_objet((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 5: pension((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 6: appris_move_tutors((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uchar(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: move_tutors((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uchar(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: evoluer((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uchar(*)>(_a[2]))); break;
        case 9: attacher((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 10: boost((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 11: soin((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 12: soin_baie((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 13: annuler(); break;
        case 14: finir_gestion(); break;
        case 15: echange_position(); break;
        case 16: echange_objets(); break;
        case 17: rangement_objet(); break;
        case 18: voir_fiche_pk_ut((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 19: voir_fiche_oeuf((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 20: apprendre_move_tutors((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 21: move_tutors((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: voler(); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void GestionEquipe::vol()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GestionEquipe::fin_gestion()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GestionEquipe::echange_place(const QPair<int,int> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GestionEquipe::echange_objets(const QPair<int,int> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GestionEquipe::rangement_objet(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GestionEquipe::pension(const QPair<int,int> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GestionEquipe::appris_move_tutors(const QString & _t1, uchar _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GestionEquipe::move_tutors(const QString & _t1, uchar _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void GestionEquipe::evoluer(const QString & _t1, uchar _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void GestionEquipe::attacher(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void GestionEquipe::boost(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void GestionEquipe::soin(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void GestionEquipe::soin_baie(uchar _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_END_MOC_NAMESPACE
