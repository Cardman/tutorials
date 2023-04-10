/****************************************************************************
** Meta object code from reading C++ file 'dialoguecoords.h'
**
** Created: Tue Jun 26 23:40:22 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialoguecoords.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoguecoords.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueCoords[] = {

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
      31,   15,   15,   15, 0x08,
      47,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueCoords[] = {
    "DialogueCoords\0\0maj_table(int)\0"
    "maj_grille(int)\0"
    "maj_coords(QPair<QPair<int,int>,QPair<int,int> >)\0"
};

const QMetaObject DialogueCoords::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueCoords,
      qt_meta_data_DialogueCoords, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueCoords::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueCoords::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueCoords::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueCoords))
        return static_cast<void*>(const_cast< DialogueCoords*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueCoords::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: maj_table((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: maj_grille((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: maj_coords((*reinterpret_cast< const QPair<QPair<int,int>,QPair<int,int> >(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
