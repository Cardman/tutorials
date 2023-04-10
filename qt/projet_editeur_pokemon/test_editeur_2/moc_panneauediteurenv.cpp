/****************************************************************************
** Meta object code from reading C++ file 'panneauediteurenv.h'
**
** Created: Wed Jun 27 12:11:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/panneau/panneauediteurenv.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'panneauediteurenv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PanneauEditerEnv[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   17,   17,   17, 0x08,
      66,   17,   17,   17, 0x08,
      91,   17,   17,   17, 0x08,
     104,   17,   17,   17, 0x08,
     116,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PanneauEditerEnv[] = {
    "PanneauEditerEnv\0\0image_tuile_changee(QImage)\0"
    "activer_bouton(int)\0maj_image_tuile(QString)\0"
    "maj_nb_pas()\0maj_muret()\0maj_type_env()\0"
};

const QMetaObject PanneauEditerEnv::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PanneauEditerEnv,
      qt_meta_data_PanneauEditerEnv, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PanneauEditerEnv::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PanneauEditerEnv::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PanneauEditerEnv::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PanneauEditerEnv))
        return static_cast<void*>(const_cast< PanneauEditerEnv*>(this));
    return QWidget::qt_metacast(_clname);
}

int PanneauEditerEnv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: image_tuile_changee((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: activer_bouton((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: maj_image_tuile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: maj_nb_pas(); break;
        case 4: maj_muret(); break;
        case 5: maj_type_env(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PanneauEditerEnv::image_tuile_changee(const QImage & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
