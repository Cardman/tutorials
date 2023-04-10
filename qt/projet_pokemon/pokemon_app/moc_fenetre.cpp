/****************************************************************************
** Meta object code from reading C++ file 'fenetre.h'
**
** Created: Wed Jul 25 21:24:48 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/fenetre.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Fenetre[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      53,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      32,    8,    8,    8, 0x08,
      70,   68,    8,    8, 0x08,
     101,    8,    8,    8, 0x08,
     126,  123,    8,    8, 0x08,
     176,   68,    8,    8, 0x08,
     214,    8,    8,    8, 0x08,
     232,    8,    8,    8, 0x08,
     259,    8,    8,    8, 0x08,
     273,    8,    8,    8, 0x08,
     296,    8,    8,    8, 0x08,
     310,    8,    8,    8, 0x08,
     328,    8,    8,    8, 0x08,
     342,    8,    8,    8, 0x08,
     364,    8,    8,    8, 0x08,
     391,    8,    8,    8, 0x08,
     415,    8,    8,    8, 0x08,
     444,    8,    8,    8, 0x08,
     465,    8,    8,    8, 0x08,
     491,    8,    8,    8, 0x08,
     519,  123,    8,    8, 0x08,
     569,  123,    8,    8, 0x08,
     609,    8,    8,    8, 0x08,
     628,    8,    8,    8, 0x08,
     639,    8,    8,    8, 0x08,
     655,    8,    8,    8, 0x08,
     671,    8,    8,    8, 0x08,
     684,    8,    8,    8, 0x08,
     696,    8,    8,    8, 0x08,
     713,    8,    8,    8, 0x08,
     730,   68,    8,    8, 0x08,
     753,    8,    8,    8, 0x08,
     778,    8,    8,    8, 0x08,
     793,    8,    8,    8, 0x08,
     816,  123,    8,    8, 0x08,
     849,   68,    8,    8, 0x08,
     904,   68,    8,    8, 0x08,
     957,    8,    8,    8, 0x08,
     993,   68,    8,    8, 0x08,
    1035,    8,    8,    8, 0x08,
    1071,    8,    8,    8, 0x08,
    1108,    8,    8,    8, 0x08,
    1130,    8,    8,    8, 0x08,
    1138,    8,    8,    8, 0x08,
    1146,    8,    8,    8, 0x08,
    1154,    8,    8,    8, 0x08,
    1169,    8,    8,    8, 0x08,
    1184,    8,    8,    8, 0x08,
    1212,    8,    8,    8, 0x08,
    1235,    8,    8,    8, 0x08,
    1244,    8,    8,    8, 0x08,
    1254,    8,    8,    8, 0x08,
    1275,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Fenetre[] = {
    "Fenetre\0\0finir_initialisation()\0"
    "maj_attaque_combat_sauvage(QString)\0"
    ",\0maj_action(Combattant,QString)\0"
    "maj_fiche(Combattant)\0,,\0"
    "maj_attaque_combat(Combattant,Combattant,QString)\0"
    "maj_remplacant(Combattant,Combattant)\0"
    "tentative_fuite()\0tentative_capture(QString)\0"
    "tour_combat()\0apprendre_attaque(int)\0"
    "traiter_evo()\0traiter_non_evo()\0"
    "nouveau_jeu()\0redessiner_ihm(uchar)\0"
    "maj_texte_clavier(QString)\0"
    "maj_sexe_heros(QString)\0"
    "maj_position(QPair<int,int>)\0"
    "retrait_objet(uchar)\0maj_objet(QPair<int,int>)\0"
    "maj_pension(QPair<int,int>)\0"
    "tentative_apprendre_move_tutor(QString,uchar,int)\0"
    "apprendre_move_tutor(QString,uchar,int)\0"
    "gerer_inventaire()\0attacher()\0"
    "attacher(uchar)\0utiliser(uchar)\0"
    "boost(uchar)\0soin(uchar)\0soin_baie(uchar)\0"
    "apprendre(uchar)\0evoluer(QString,uchar)\0"
    "finir_gerer_inventaire()\0gerer_equipe()\0"
    "finir_gestion_equipe()\0"
    "interaction(uchar,uchar,QString)\0"
    "echanger_pokemons_boite(QPair<int,int>,QPair<int,int>)\0"
    "echanger_objets_boite(QPair<int,int>,QPair<int,int>)\0"
    "ranger_objets_boite(QPair<int,int>)\0"
    "deposer_pokemon(uchar,QPair<uchar,uchar>)\0"
    "retrait_pokemon(QPair<uchar,uchar>)\0"
    "relacher_pokemon(QPair<uchar,uchar>)\0"
    "finir_gestion_boite()\0voler()\0achat()\0"
    "vente()\0erreur_achat()\0erreur_vente()\0"
    "finir_gestion_achat_vente()\0"
    "vivre_fossile(QString)\0joueur()\0"
    "options()\0maj_diff(Difficulte)\0"
    "maj_coords_vol(Coordonnees)\0"
};

const QMetaObject Fenetre::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Fenetre,
      qt_meta_data_Fenetre, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Fenetre::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Fenetre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Fenetre::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Fenetre))
        return static_cast<void*>(const_cast< Fenetre*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Fenetre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finir_initialisation(); break;
        case 1: maj_attaque_combat_sauvage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: maj_action((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: maj_fiche((*reinterpret_cast< const Combattant(*)>(_a[1]))); break;
        case 4: maj_attaque_combat((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const Combattant(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 5: maj_remplacant((*reinterpret_cast< const Combattant(*)>(_a[1])),(*reinterpret_cast< const Combattant(*)>(_a[2]))); break;
        case 6: tentative_fuite(); break;
        case 7: tentative_capture((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: tour_combat(); break;
        case 9: apprendre_attaque((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: traiter_evo(); break;
        case 11: traiter_non_evo(); break;
        case 12: nouveau_jeu(); break;
        case 13: redessiner_ihm((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 14: maj_texte_clavier((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: maj_sexe_heros((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: maj_position((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 17: retrait_objet((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 18: maj_objet((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 19: maj_pension((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 20: tentative_apprendre_move_tutor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uchar(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 21: apprendre_move_tutor((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uchar(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 22: gerer_inventaire(); break;
        case 23: attacher(); break;
        case 24: attacher((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 25: utiliser((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 26: boost((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 27: soin((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 28: soin_baie((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 29: apprendre((*reinterpret_cast< uchar(*)>(_a[1]))); break;
        case 30: evoluer((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uchar(*)>(_a[2]))); break;
        case 31: finir_gerer_inventaire(); break;
        case 32: gerer_equipe(); break;
        case 33: finir_gestion_equipe(); break;
        case 34: interaction((*reinterpret_cast< uchar(*)>(_a[1])),(*reinterpret_cast< uchar(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 35: echanger_pokemons_boite((*reinterpret_cast< const QPair<int,int>(*)>(_a[1])),(*reinterpret_cast< const QPair<int,int>(*)>(_a[2]))); break;
        case 36: echanger_objets_boite((*reinterpret_cast< const QPair<int,int>(*)>(_a[1])),(*reinterpret_cast< const QPair<int,int>(*)>(_a[2]))); break;
        case 37: ranger_objets_boite((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 38: deposer_pokemon((*reinterpret_cast< uchar(*)>(_a[1])),(*reinterpret_cast< const QPair<uchar,uchar>(*)>(_a[2]))); break;
        case 39: retrait_pokemon((*reinterpret_cast< const QPair<uchar,uchar>(*)>(_a[1]))); break;
        case 40: relacher_pokemon((*reinterpret_cast< const QPair<uchar,uchar>(*)>(_a[1]))); break;
        case 41: finir_gestion_boite(); break;
        case 42: voler(); break;
        case 43: achat(); break;
        case 44: vente(); break;
        case 45: erreur_achat(); break;
        case 46: erreur_vente(); break;
        case 47: finir_gestion_achat_vente(); break;
        case 48: vivre_fossile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 49: joueur(); break;
        case 50: options(); break;
        case 51: maj_diff((*reinterpret_cast< const Difficulte(*)>(_a[1]))); break;
        case 52: maj_coords_vol((*reinterpret_cast< const Coordonnees(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 53;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
