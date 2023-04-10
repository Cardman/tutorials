/****************************************************************************
** Meta object code from reading C++ file 'dialogueediteurmap.h'
**
** Created: Tue Jun 26 23:40:24 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialogueediteurmap.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogueediteurmap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueEditeurMap[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      47,   19,   19,   19, 0x08,
      75,   19,   19,   19, 0x08,
     104,   19,   19,   19, 0x08,
     133,   19,   19,   19, 0x08,
     161,   19,   19,   19, 0x08,
     190,   19,   19,   19, 0x08,
     220,   19,   19,   19, 0x08,
     250,   19,   19,   19, 0x08,
     272,   19,   19,   19, 0x08,
     296,   19,   19,   19, 0x08,
     318,   19,   19,   19, 0x08,
     339,   19,   19,   19, 0x08,
     366,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueEditeurMap[] = {
    "DialogueEditeurMap\0\0ajouter_ligne_ht_plateau()\0"
    "ajouter_ligne_bas_plateau()\0"
    "ajouter_col_gauche_plateau()\0"
    "ajouter_col_droite_plateau()\0"
    "ajouter_lignes_ht_plateau()\0"
    "ajouter_lignes_bas_plateau()\0"
    "ajouter_cols_gauche_plateau()\0"
    "ajouter_cols_droite_plateau()\0"
    "supprimer_ligne_map()\0supprimer_colonne_map()\0"
    "supprimer_tuile_map()\0maj_tuile_courante()\0"
    "maj_coords(QPair<int,int>)\0acceptation()\0"
};

const QMetaObject DialogueEditeurMap::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueEditeurMap,
      qt_meta_data_DialogueEditeurMap, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueEditeurMap::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueEditeurMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueEditeurMap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueEditeurMap))
        return static_cast<void*>(const_cast< DialogueEditeurMap*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueEditeurMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ajouter_ligne_ht_plateau(); break;
        case 1: ajouter_ligne_bas_plateau(); break;
        case 2: ajouter_col_gauche_plateau(); break;
        case 3: ajouter_col_droite_plateau(); break;
        case 4: ajouter_lignes_ht_plateau(); break;
        case 5: ajouter_lignes_bas_plateau(); break;
        case 6: ajouter_cols_gauche_plateau(); break;
        case 7: ajouter_cols_droite_plateau(); break;
        case 8: supprimer_ligne_map(); break;
        case 9: supprimer_colonne_map(); break;
        case 10: supprimer_tuile_map(); break;
        case 11: maj_tuile_courante(); break;
        case 12: maj_coords((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 13: acceptation(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
