/****************************************************************************
** Meta object code from reading C++ file 'scenecombat.h'
**
** Created: Fri Jul 13 13:34:23 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/combat/scenecombat.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scenecombat.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SceneCombat[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      47,   12,   12,   12, 0x05,
      86,   84,   12,   12, 0x05,
     118,   12,   12,   12, 0x05,
     139,  136,   12,   12, 0x05,
     183,   12,   12,   12, 0x05,
     202,   84,   12,   12, 0x05,
     241,   12,   12,   12, 0x05,
     251,   12,   12,   12, 0x05,
     268,   12,   12,   12, 0x05,
     281,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     291,   12,   12,   12, 0x0a,
     309,   12,   12,   12, 0x0a,
     327,   12,   12,   12, 0x0a,
     363,   84,   12,   12, 0x0a,
     394,   12,   12,   12, 0x0a,
     411,   84,   12,   12, 0x0a,
     449,   12,   12,   12, 0x0a,
     471,   12,   12,   12, 0x0a,
     489,   12,   12,   12, 0x0a,
     505,   12,   12,   12, 0x0a,
     528,   12,   12,   12, 0x0a,
     546,  136,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SceneCombat[] = {
    "SceneCombat\0\0change_fiche_creature(Combattant)\0"
    "clic_attaque_combat_sauvage(QString)\0"
    ",\0clic_action(Combattant,QString)\0"
    "clic_attaque(int)\0,,\0"
    "clic_attaque(Combattant,Combattant,QString)\0"
    "clic_ball(QString)\0"
    "clic_remplacant(Combattant,Combattant)\0"
    "evoluer()\0ne_pas_evoluer()\0clic_fuite()\0"
    "valider()\0ne_pas_capturer()\0"
    "maj_ball(QString)\0maj_attaque_combat_sauvage(QString)\0"
    "maj_action(Combattant,QString)\0"
    "maj_attaque(int)\0maj_remplacant(Combattant,Combattant)\0"
    "maj_fiche(Combattant)\0valider_actions()\0"
    "faire_evoluer()\0ne_pas_faire_evoluer()\0"
    "tentative_fuite()\0"
    "maj_attaque_combat(Combattant,Combattant,QString)\0"
};

const QMetaObject SceneCombat::staticMetaObject = {
    { &QSplitter::staticMetaObject, qt_meta_stringdata_SceneCombat,
      qt_meta_data_SceneCombat, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SceneCombat::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SceneCombat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SceneCombat::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SceneCombat))
        return static_cast<void*>(const_cast< SceneCombat*>(this));
    return QSplitter::qt_metacast(_clname);
}

int SceneCombat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplitter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: change_fiche_creature((*reinterpret_cast< const Combattant(*)>(_a[1]))); break;
        case 1: clic_attaque_combat_sauvage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: clic_action((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: clic_attaque((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: clic_attaque((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const Combattant(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 5: clic_ball((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: clic_remplacant((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const Combattant(*)>(_a[2]))); break;
        case 7: evoluer(); break;
        case 8: ne_pas_evoluer(); break;
        case 9: clic_fuite(); break;
        case 10: valider(); break;
        case 11: ne_pas_capturer(); break;
        case 12: maj_ball((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: maj_attaque_combat_sauvage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: maj_action((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: maj_attaque((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: maj_remplacant((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const Combattant(*)>(_a[2]))); break;
        case 17: maj_fiche((*reinterpret_cast< const Combattant(*)>(_a[1]))); break;
        case 18: valider_actions(); break;
        case 19: faire_evoluer(); break;
        case 20: ne_pas_faire_evoluer(); break;
        case 21: tentative_fuite(); break;
        case 22: maj_attaque_combat((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const Combattant(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void SceneCombat::change_fiche_creature(const Combattant & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SceneCombat::clic_attaque_combat_sauvage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SceneCombat::clic_action(const Combattant & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SceneCombat::clic_attaque(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SceneCombat::clic_attaque(const Combattant & _t1, const Combattant & _t2, const QString & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SceneCombat::clic_ball(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SceneCombat::clic_remplacant(const Combattant & _t1, const Combattant & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SceneCombat::evoluer()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void SceneCombat::ne_pas_evoluer()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void SceneCombat::clic_fuite()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void SceneCombat::valider()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}
QT_END_MOC_NAMESPACE
