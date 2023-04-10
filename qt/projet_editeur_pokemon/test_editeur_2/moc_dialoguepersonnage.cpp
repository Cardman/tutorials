/****************************************************************************
** Meta object code from reading C++ file 'dialoguepersonnage.h'
**
** Created: Tue Jun 26 23:40:34 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialoguepersonnage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoguepersonnage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialoguePersonnage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      40,   19,   19,   19, 0x08,
      59,   19,   19,   19, 0x08,
      80,   19,   19,   19, 0x08,
      99,   19,   19,   19, 0x08,
     116,   19,   19,   19, 0x08,
     134,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialoguePersonnage[] = {
    "DialoguePersonnage\0\0activer_bouton(int)\0"
    "maj_achat_objets()\0maj_achat_capsules()\0"
    "maj_don_capsules()\0maj_don_objets()\0"
    "maj_don_pokemon()\0acceptation()\0"
};

const QMetaObject DialoguePersonnage::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialoguePersonnage,
      qt_meta_data_DialoguePersonnage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialoguePersonnage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialoguePersonnage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialoguePersonnage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialoguePersonnage))
        return static_cast<void*>(const_cast< DialoguePersonnage*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialoguePersonnage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: activer_bouton((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: maj_achat_objets(); break;
        case 2: maj_achat_capsules(); break;
        case 3: maj_don_capsules(); break;
        case 4: maj_don_objets(); break;
        case 5: maj_don_pokemon(); break;
        case 6: acceptation(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
