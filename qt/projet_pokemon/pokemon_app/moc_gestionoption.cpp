/****************************************************************************
** Meta object code from reading C++ file 'gestionoption.h'
**
** Created: Wed Jul 18 22:15:51 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/hors_combat/gestionoption.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gestionoption.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GestionOption[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   14,   14,   14, 0x08,
      56,   14,   14,   14, 0x08,
      71,   14,   14,   14, 0x08,
      87,   14,   14,   14, 0x08,
     119,   14,   14,   14, 0x08,
     137,   14,   14,   14, 0x08,
     153,   14,   14,   14, 0x08,
     171,   14,   14,   14, 0x08,
     192,   14,   14,   14, 0x08,
     221,   14,   14,   14, 0x08,
     248,   14,   14,   14, 0x08,
     276,   14,   14,   14, 0x08,
     301,   14,   14,   14, 0x08,
     323,   14,   14,   14, 0x08,
     346,   14,   14,   14, 0x08,
     373,   14,   14,   14, 0x08,
     401,   14,   14,   14, 0x08,
     434,   14,   14,   14, 0x08,
     468,   14,   14,   14, 0x08,
     504,   14,   14,   14, 0x08,
     533,   14,   14,   14, 0x08,
     574,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GestionOption[] = {
    "GestionOption\0\0maj_diff(Difficulte)\0"
    "maj_nom_pk_max(int)\0maj_iv_ut(int)\0"
    "maj_iv_adv(int)\0maj_valeur_nec_evo_bonheur(int)\0"
    "maj_ko_capt(bool)\0maj_fuite(bool)\0"
    "maj_adj_act(bool)\0maj_appar_alea(bool)\0"
    "maj_coeff_gain_pts_exp(Taux)\0"
    "maj_coeff_achat_base(Taux)\0"
    "maj_coeff_vente_achat(Taux)\0"
    "maj_diffic_gain_exp(int)\0maj_choix_loi_ut(int)\0"
    "maj_choix_loi_adv(int)\0"
    "maj_choix_loi_conf_ut(int)\0"
    "maj_choix_loi_conf_adv(int)\0"
    "maj_coeff_gain_argent_base(Taux)\0"
    "maj_coeff_perte_argent_gain(Taux)\0"
    "maj_rapport_max_egal_stat_evo(Taux)\0"
    "maj_pp_rest_fin_combat(bool)\0"
    "maj_affichage_restreint_inventaire(bool)\0"
    "valider()\0"
};

const QMetaObject GestionOption::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_GestionOption,
      qt_meta_data_GestionOption, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GestionOption::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GestionOption::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GestionOption::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GestionOption))
        return static_cast<void*>(const_cast< GestionOption*>(this));
    return QLabel::qt_metacast(_clname);
}

int GestionOption::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: maj_diff((*reinterpret_cast< const Difficulte(*)>(_a[1]))); break;
        case 1: maj_nom_pk_max((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: maj_iv_ut((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: maj_iv_adv((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: maj_valeur_nec_evo_bonheur((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: maj_ko_capt((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: maj_fuite((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: maj_adj_act((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: maj_appar_alea((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: maj_coeff_gain_pts_exp((*reinterpret_cast< const Taux(*)>(_a[1]))); break;
        case 10: maj_coeff_achat_base((*reinterpret_cast< const Taux(*)>(_a[1]))); break;
        case 11: maj_coeff_vente_achat((*reinterpret_cast< const Taux(*)>(_a[1]))); break;
        case 12: maj_diffic_gain_exp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: maj_choix_loi_ut((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: maj_choix_loi_adv((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: maj_choix_loi_conf_ut((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: maj_choix_loi_conf_adv((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: maj_coeff_gain_argent_base((*reinterpret_cast< const Taux(*)>(_a[1]))); break;
        case 18: maj_coeff_perte_argent_gain((*reinterpret_cast< const Taux(*)>(_a[1]))); break;
        case 19: maj_rapport_max_egal_stat_evo((*reinterpret_cast< const Taux(*)>(_a[1]))); break;
        case 20: maj_pp_rest_fin_combat((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: maj_affichage_restreint_inventaire((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: valider(); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void GestionOption::maj_diff(const Difficulte & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
