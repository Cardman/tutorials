/****************************************************************************
** Meta object code from reading C++ file 'ficheactions.h'
**
** Created: Fri Jul 13 12:49:25 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/combat/fiches/ficheactions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ficheactions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FicheActions[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   14,   13,   13, 0x05,
      51,   48,   13,   13, 0x05,
      95,   13,   13,   13, 0x05,
     113,   14,   13,   13, 0x05,
     155,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     186,   13,   13,   13, 0x0a,
     216,   13,   13,   13, 0x0a,
     246,   13,   13,   13, 0x0a,
     279,   13,   13,   13, 0x0a,
     301,   13,   13,   13, 0x0a,
     328,   13,   13,   13, 0x0a,
     347,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FicheActions[] = {
    "FicheActions\0\0,\0clic_action(Combattant,QString)\0"
    ",,\0clic_attaque(Combattant,Combattant,QString)\0"
    "clic_attaque(int)\0"
    "changer_remplacant(Combattant,Combattant)\0"
    "clic_objet(Combattant,QString)\0"
    "maj_fiche_fct_action(QString)\0"
    "maj_attaque_a_lancer(QString)\0"
    "maj_attaque_a_apprendre(QString)\0"
    "maj_cible(Combattant)\0maj_remplacant(Combattant)\0"
    "maj_objet(QString)\0fin_combat_ou_ajout_cr()\0"
};

const QMetaObject FicheActions::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_FicheActions,
      qt_meta_data_FicheActions, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FicheActions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FicheActions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FicheActions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FicheActions))
        return static_cast<void*>(const_cast< FicheActions*>(this));
    return QLabel::qt_metacast(_clname);
}

int FicheActions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clic_action((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: clic_attaque((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const Combattant(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 2: clic_attaque((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: changer_remplacant((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const Combattant(*)>(_a[2]))); break;
        case 4: clic_objet((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: maj_fiche_fct_action((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: maj_attaque_a_lancer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: maj_attaque_a_apprendre((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: maj_cible((*reinterpret_cast< const Combattant(*)>(_a[1]))); break;
        case 9: maj_remplacant((*reinterpret_cast< const Combattant(*)>(_a[1]))); break;
        case 10: maj_objet((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: fin_combat_ou_ajout_cr(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void FicheActions::clic_action(const Combattant & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FicheActions::clic_attaque(const Combattant & _t1, const Combattant & _t2, const QString & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FicheActions::clic_attaque(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FicheActions::changer_remplacant(const Combattant & _t1, const Combattant & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FicheActions::clic_objet(const Combattant & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
