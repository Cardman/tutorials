/****************************************************************************
** Meta object code from reading C++ file 'dialogueachats.h'
**
** Created: Tue Jun 26 23:40:19 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialogueachats.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogueachats.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueAchats[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      30,   15,   15,   15, 0x08,
      50,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueAchats[] = {
    "DialogueAchats\0\0ajout_objet()\0"
    "suppression_objet()\0acceptation()\0"
};

const QMetaObject DialogueAchats::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueAchats,
      qt_meta_data_DialogueAchats, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueAchats::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueAchats::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueAchats::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueAchats))
        return static_cast<void*>(const_cast< DialogueAchats*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueAchats::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ajout_objet(); break;
        case 1: suppression_objet(); break;
        case 2: acceptation(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
