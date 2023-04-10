/****************************************************************************
** Meta object code from reading C++ file 'grilledialogue.h'
**
** Created: Tue Jun 26 23:40:38 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/grilles/grilledialogue.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'grilledialogue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GrilleDialogue[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_GrilleDialogue[] = {
    "GrilleDialogue\0\0"
    "selection(QPair<QPair<int,int>,QPair<int,int> >)\0"
};

const QMetaObject GrilleDialogue::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_GrilleDialogue,
      qt_meta_data_GrilleDialogue, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GrilleDialogue::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GrilleDialogue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GrilleDialogue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GrilleDialogue))
        return static_cast<void*>(const_cast< GrilleDialogue*>(this));
    return QLabel::qt_metacast(_clname);
}

int GrilleDialogue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selection((*reinterpret_cast< const QPair<QPair<int,int>,QPair<int,int> >(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void GrilleDialogue::selection(const QPair<QPair<int,int>,QPair<int,int> > & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
