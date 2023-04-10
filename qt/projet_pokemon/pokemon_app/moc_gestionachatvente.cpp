/****************************************************************************
** Meta object code from reading C++ file 'gestionachatvente.h'
**
** Created: Tue Jul 17 13:01:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/hors_combat/gestionachatvente.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gestionachatvente.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GestionAchatVente[] = {

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
      19,   18,   18,   18, 0x05,
      27,   18,   18,   18, 0x05,
      35,   18,   18,   18, 0x05,
      50,   18,   18,   18, 0x05,
      65,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   18,   18,   18, 0x08,
     102,   18,   18,   18, 0x08,
     131,   18,   18,   18, 0x08,
     147,   18,   18,   18, 0x08,
     174,  172,   18,   18, 0x08,
     203,   18,   18,   18, 0x08,
     230,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GestionAchatVente[] = {
    "GestionAchatVente\0\0achat()\0vente()\0"
    "erreur_achat()\0erreur_vente()\0"
    "fin_gestion()\0valider_achats_vente()\0"
    "valider_achats_vente(Entier)\0"
    "finir_gestion()\0selection_objet(QString)\0"
    ",\0selection_objet(QString,int)\0"
    "selection_capsule(QString)\0"
    "selection_capsule(uchar)\0"
};

const QMetaObject GestionAchatVente::staticMetaObject = {
    { &QSplitter::staticMetaObject, qt_meta_stringdata_GestionAchatVente,
      qt_meta_data_GestionAchatVente, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GestionAchatVente::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GestionAchatVente::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GestionAchatVente::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GestionAchatVente))
        return static_cast<void*>(const_cast< GestionAchatVente*>(this));
    return QSplitter::qt_metacast(_clname);
}

int GestionAchatVente::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplitter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: achat(); break;
        case 1: vente(); break;
        case 2: erreur_achat(); break;
        case 3: erreur_vente(); break;
        case 4: fin_gestion(); break;
        case 5: valider_achats_vente(); break;
        case 6: valider_achats_vente((*reinterpret_cast< const Entier(*)>(_a[1]))); break;
        case 7: finir_gestion(); break;
        case 8: selection_objet((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: selection_objet((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: selection_capsule((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: selection_capsule((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void GestionAchatVente::achat()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GestionAchatVente::vente()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GestionAchatVente::erreur_achat()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GestionAchatVente::erreur_vente()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void GestionAchatVente::fin_gestion()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
