/****************************************************************************
** Meta object code from reading C++ file 'panneaudresseurligue.h'
**
** Created: Tue Jun 26 23:40:40 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/panneau/panneaudresseurligue.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'panneaudresseurligue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PanneauDresseurLigue[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   21,   21,   21, 0x08,
      65,   21,   21,   21, 0x08,
      81,   21,   21,   21, 0x08,
     103,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PanneauDresseurLigue[] = {
    "PanneauDresseurLigue\0\0image_tuile_changee(QImage)\0"
    "maj_type_env()\0maj_equipe(int)\0"
    "maj_dresseur_revert()\0maj_image_tuile(QString)\0"
};

const QMetaObject PanneauDresseurLigue::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_PanneauDresseurLigue,
      qt_meta_data_PanneauDresseurLigue, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PanneauDresseurLigue::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PanneauDresseurLigue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PanneauDresseurLigue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PanneauDresseurLigue))
        return static_cast<void*>(const_cast< PanneauDresseurLigue*>(this));
    return QLabel::qt_metacast(_clname);
}

int PanneauDresseurLigue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: image_tuile_changee((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: maj_type_env(); break;
        case 2: maj_equipe((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: maj_dresseur_revert(); break;
        case 4: maj_image_tuile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PanneauDresseurLigue::image_tuile_changee(const QImage & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
