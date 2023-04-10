/****************************************************************************
** Meta object code from reading C++ file 'dialogueequipe.h'
**
** Created: Tue Jun 26 23:40:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialogueequipe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogueequipe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueEquipe[] = {

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
      16,   15,   15,   15, 0x08,
      34,   15,   15,   15, 0x08,
      52,   15,   15,   15, 0x08,
      72,   15,   15,   15, 0x08,
      89,   15,   15,   15, 0x08,
     103,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueEquipe[] = {
    "DialogueEquipe\0\0ajouter_pokemon()\0"
    "inserer_pokemon()\0supprimer_pokemon()\0"
    "editer_pokemon()\0acceptation()\0"
    "maj_description(int)\0"
};

const QMetaObject DialogueEquipe::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueEquipe,
      qt_meta_data_DialogueEquipe, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueEquipe::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueEquipe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueEquipe::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueEquipe))
        return static_cast<void*>(const_cast< DialogueEquipe*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueEquipe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ajouter_pokemon(); break;
        case 1: inserer_pokemon(); break;
        case 2: supprimer_pokemon(); break;
        case 3: editer_pokemon(); break;
        case 4: acceptation(); break;
        case 5: maj_description((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
