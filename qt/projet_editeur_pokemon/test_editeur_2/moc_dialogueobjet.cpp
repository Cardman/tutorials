/****************************************************************************
** Meta object code from reading C++ file 'dialogueobjet.h'
**
** Created: Tue Jun 26 23:40:33 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/dialogue/dialogueobjet.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogueobjet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogueObjet[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogueObjet[] = {
    "DialogueObjet\0\0descr_obj()\0"
};

const QMetaObject DialogueObjet::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogueObjet,
      qt_meta_data_DialogueObjet, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogueObjet::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogueObjet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogueObjet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogueObjet))
        return static_cast<void*>(const_cast< DialogueObjet*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogueObjet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: descr_obj(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
