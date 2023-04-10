/****************************************************************************
** Meta object code from reading C++ file 'dialoguebasedonnees.h'
**
** Created: Tue Jun 26 23:40:20 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialoguebasedonnees.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoguebasedonnees.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueBaseDonnees[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x08,
      36,   20,   20,   20, 0x08,
      54,   20,   20,   20, 0x08,
      70,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueBaseDonnees[] = {
    "DialogueBaseDonnees\0\0maj_descr_pk()\0"
    "maj_descr_capac()\0maj_descr_obj()\0"
    "maj_descr_att()\0"
};

const QMetaObject DialogueBaseDonnees::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueBaseDonnees,
      qt_meta_data_DialogueBaseDonnees, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueBaseDonnees::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueBaseDonnees::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueBaseDonnees::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueBaseDonnees))
        return static_cast<void*>(const_cast< DialogueBaseDonnees*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueBaseDonnees::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: maj_descr_pk(); break;
        case 1: maj_descr_capac(); break;
        case 2: maj_descr_obj(); break;
        case 3: maj_descr_att(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
