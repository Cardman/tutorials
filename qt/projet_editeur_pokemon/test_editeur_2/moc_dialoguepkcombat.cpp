/****************************************************************************
** Meta object code from reading C++ file 'dialoguepkcombat.h'
**
** Created: Tue Jun 26 23:40:35 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialoguepkcombat.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoguepkcombat.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialoguePkCombat[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      35,   17,   17,   17, 0x08,
      55,   17,   17,   17, 0x08,
      86,   17,   17,   17, 0x08,
     102,   17,   17,   17, 0x08,
     124,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialoguePkCombat[] = {
    "DialoguePkCombat\0\0maj_fct_nom_pk()\0"
    "maj_fct_niveau_pk()\0maj_fct_categ_attaques_pk(int)\0"
    "ajout_attaque()\0suppression_attaque()\0"
    "acceptation()\0"
};

const QMetaObject DialoguePkCombat::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialoguePkCombat,
      qt_meta_data_DialoguePkCombat, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialoguePkCombat::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialoguePkCombat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialoguePkCombat::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialoguePkCombat))
        return static_cast<void*>(const_cast< DialoguePkCombat*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialoguePkCombat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: maj_fct_nom_pk(); break;
        case 1: maj_fct_niveau_pk(); break;
        case 2: maj_fct_categ_attaques_pk((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: ajout_attaque(); break;
        case 4: suppression_attaque(); break;
        case 5: acceptation(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
