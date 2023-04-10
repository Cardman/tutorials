/****************************************************************************
** Meta object code from reading C++ file 'difficulte.h'
**
** Created: Wed Jul 18 22:15:47 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serialisable/difficulte/difficulte.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'difficulte.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Difficulte[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       2,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
      11, 0x0,    5,   22,
      18, 0x0,    4,   32,

 // enum data: key, value
      28, uint(Difficulte::CONSTANT_MIN),
      41, uint(Difficulte::CROISSANT),
      51, uint(Difficulte::UNIFORME),
      60, uint(Difficulte::DECROISSANT),
      72, uint(Difficulte::CONSTANT_MAX),
      85, uint(Difficulte::TRES_FACILE),
      97, uint(Difficulte::FACILE),
     104, uint(Difficulte::DIFFICILE),
     114, uint(Difficulte::TRES_DIFFICILE),

       0        // eod
};

static const char qt_meta_stringdata_Difficulte[] = {
    "Difficulte\0Modele\0GainPtExp\0CONSTANT_MIN\0"
    "CROISSANT\0UNIFORME\0DECROISSANT\0"
    "CONSTANT_MAX\0TRES_FACILE\0FACILE\0"
    "DIFFICILE\0TRES_DIFFICILE\0"
};

const QMetaObject Difficulte::staticMetaObject = {
    { 0, qt_meta_stringdata_Difficulte,
      qt_meta_data_Difficulte, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Difficulte::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION
QT_END_MOC_NAMESPACE
