/****************************************************************************
** Meta object code from reading C++ file 'claviernumerique.h'
**
** Created: Mon Jul 16 19:38:07 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ihm/boutons/claviernumerique.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'claviernumerique.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClavierNumerique[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      32,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   17,   17,   17, 0x0a,
      62,   17,   17,   17, 0x08,
      76,   17,   17,   17, 0x08,
      90,   17,   17,   17, 0x08,
     104,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ClavierNumerique[] = {
    "ClavierNumerique\0\0valider(Taux)\0"
    "valider(Entier)\0vider_champ()\0"
    "incrementer()\0decrementer()\0maj_valider()\0"
    "maj_champ(QString)\0"
};

const QMetaObject ClavierNumerique::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_ClavierNumerique,
      qt_meta_data_ClavierNumerique, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClavierNumerique::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClavierNumerique::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClavierNumerique::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClavierNumerique))
        return static_cast<void*>(const_cast< ClavierNumerique*>(this));
    return QLabel::qt_metacast(_clname);
}

int ClavierNumerique::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valider((*reinterpret_cast< const Taux(*)>(_a[1]))); break;
        case 1: valider((*reinterpret_cast< const Entier(*)>(_a[1]))); break;
        case 2: vider_champ(); break;
        case 3: incrementer(); break;
        case 4: decrementer(); break;
        case 5: maj_valider(); break;
        case 6: maj_champ((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ClavierNumerique::valider(const Taux & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClavierNumerique::valider(const Entier & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
