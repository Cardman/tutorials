/****************************************************************************
** Meta object code from reading C++ file 'dialoguelieuxvols.h'
**
** Created: Tue Jun 26 23:40:31 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialoguelieuxvols.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoguelieuxvols.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueLieuxVols[] = {

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
      19,   18,   18,   18, 0x08,
      46,   18,   18,   18, 0x08,
      63,   18,   18,   18, 0x08,
      74,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueLieuxVols[] = {
    "DialogueLieuxVols\0\0maj_coords(QPair<int,int>)\0"
    "supprimer_lien()\0maj_lien()\0acceptation()\0"
};

const QMetaObject DialogueLieuxVols::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueLieuxVols,
      qt_meta_data_DialogueLieuxVols, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueLieuxVols::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueLieuxVols::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueLieuxVols::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueLieuxVols))
        return static_cast<void*>(const_cast< DialogueLieuxVols*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueLieuxVols::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: maj_coords((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 1: supprimer_lien(); break;
        case 2: maj_lien(); break;
        case 3: acceptation(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
