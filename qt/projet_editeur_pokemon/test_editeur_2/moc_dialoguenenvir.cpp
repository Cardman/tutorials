/****************************************************************************
** Meta object code from reading C++ file 'dialoguenenvir.h'
**
** Created: Tue Jun 26 23:40:32 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialoguenenvir.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoguenenvir.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueNEnvir[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueNEnvir[] = {
    "DialogueNEnvir\0\0dims(QPair<int,int>)\0"
    "fin_ecriture_dims()\0"
};

const QMetaObject DialogueNEnvir::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueNEnvir,
      qt_meta_data_DialogueNEnvir, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueNEnvir::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueNEnvir::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueNEnvir::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueNEnvir))
        return static_cast<void*>(const_cast< DialogueNEnvir*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueNEnvir::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dims((*reinterpret_cast< const QPair<int,int>(*)>(_a[1]))); break;
        case 1: fin_ecriture_dims(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DialogueNEnvir::dims(const QPair<int,int> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
