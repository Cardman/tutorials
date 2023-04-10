/****************************************************************************
** Meta object code from reading C++ file 'dialoguedresseur.h'
**
** Created: Tue Jun 26 23:40:23 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialoguedresseur.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoguedresseur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueDresseur[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      35,   17,   17,   17, 0x08,
      52,   17,   17,   17, 0x08,
      71,   17,   17,   17, 0x08,
      87,   17,   17,   17, 0x08,
     101,   17,   17,   17, 0x08,
     117,   17,   17,   17, 0x08,
     133,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueDresseur[] = {
    "DialogueDresseur\0\0ajouter_equipe()\0"
    "inserer_equipe()\0supprimer_equipe()\0"
    "editer_equipe()\0acceptation()\0"
    "maj_equipe(int)\0maj_ct(QString)\0"
    "maj_cs(QString)\0"
};

const QMetaObject DialogueDresseur::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueDresseur,
      qt_meta_data_DialogueDresseur, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueDresseur::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueDresseur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueDresseur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueDresseur))
        return static_cast<void*>(const_cast< DialogueDresseur*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueDresseur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ajouter_equipe(); break;
        case 1: inserer_equipe(); break;
        case 2: supprimer_equipe(); break;
        case 3: editer_equipe(); break;
        case 4: acceptation(); break;
        case 5: maj_equipe((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: maj_ct((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: maj_cs((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
