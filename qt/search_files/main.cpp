#include <QApplication>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    //qt_fr.qm to in install files
#ifdef QT_NO_DEBUG
    translator.load(":/ressources/qt_fr");
#else
    translator.load("qt_fr.qm");
#endif
    a.installTranslator(&translator);
    MainWindow w;
    w.show();
    return a.exec();
}
