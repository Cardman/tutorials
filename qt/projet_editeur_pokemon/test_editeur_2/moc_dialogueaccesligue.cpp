/****************************************************************************
** Meta object code from reading C++ file 'dialogueaccesligue.h'
**
** Created: Tue Jun 26 23:40:18 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialogueaccesligue.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogueaccesligue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueAccesLigue[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      35,   19,   19,   19, 0x08,
      64,   19,   19,   19, 0x08,
      95,   19,   19,   19, 0x08,
     127,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueAccesLigue[] = {
    "DialogueAccesLigue\0\0maj_table(int)\0"
    "ajouter_condition_champion()\0"
    "supprimer_condition_champion()\0"
    "ajouter_condition_acces_ligue()\0"
    "supprimer_condition_acces_ligue()\0"
};

const QMetaObject DialogueAccesLigue::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueAccesLigue,
      qt_meta_data_DialogueAccesLigue, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueAccesLigue::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueAccesLigue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueAccesLigue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueAccesLigue))
        return static_cast<void*>(const_cast< DialogueAccesLigue*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueAccesLigue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: maj_table((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: ajouter_condition_champion(); break;
        case 2: supprimer_condition_champion(); break;
        case 3: ajouter_condition_acces_ligue(); break;
        case 4: supprimer_condition_acces_ligue(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
