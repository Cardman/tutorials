/****************************************************************************
** Meta object code from reading C++ file 'dialogueliaisons.h'
**
** Created: Tue Jun 26 23:40:30 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialogueliaisons.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogueliaisons.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueLiaisons[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      33,   17,   17,   17, 0x08,
      53,   17,   17,   17, 0x08,
      69,   17,   17,   17, 0x08,
      90,   17,   17,   17, 0x08,
     140,   17,   17,   17, 0x08,
     195,   17,   17,   17, 0x08,
     210,   17,   17,   17, 0x08,
     227,   17,   17,   17, 0x08,
     243,   17,   17,   17, 0x08,
     261,   17,   17,   17, 0x08,
     284,   17,   17,   17, 0x08,
     309,   17,   17,   17, 0x08,
     328,   17,   17,   17, 0x08,
     349,   17,   17,   17, 0x08,
     370,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueLiaisons[] = {
    "DialogueLiaisons\0\0maj_table(int)\0"
    "maj_table_dest(int)\0maj_grille(int)\0"
    "maj_grille_dest(int)\0"
    "maj_coords(QPair<QPair<int,int>,QPair<int,int> >)\0"
    "maj_coords_dest(QPair<QPair<int,int>,QPair<int,int> >)\0"
    "souder_lieux()\0desouder_lieux()\0"
    "lier_plateaux()\0delier_plateaux()\0"
    "lier_plateaux_ligues()\0delier_plateaux_ligues()\0"
    "maj_coords_acces()\0maj_coords_origine()\0"
    "suppr_coords_acces()\0suppr_coords_origine()\0"
};

const QMetaObject DialogueLiaisons::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueLiaisons,
      qt_meta_data_DialogueLiaisons, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueLiaisons::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueLiaisons::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueLiaisons::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueLiaisons))
        return static_cast<void*>(const_cast< DialogueLiaisons*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueLiaisons::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: maj_table((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: maj_table_dest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: maj_grille((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: maj_grille_dest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: maj_coords((*reinterpret_cast< const QPair<QPair<int,int>,QPair<int,int> >(*)>(_a[1]))); break;
        case 5: maj_coords_dest((*reinterpret_cast< const QPair<QPair<int,int>,QPair<int,int> >(*)>(_a[1]))); break;
        case 6: souder_lieux(); break;
        case 7: desouder_lieux(); break;
        case 8: lier_plateaux(); break;
        case 9: delier_plateaux(); break;
        case 10: lier_plateaux_ligues(); break;
        case 11: delier_plateaux_ligues(); break;
        case 12: maj_coords_acces(); break;
        case 13: maj_coords_origine(); break;
        case 14: suppr_coords_acces(); break;
        case 15: suppr_coords_origine(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
