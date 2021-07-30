#ifndef THREADMODIF_H
#define THREADMODIF_H

#include "mesthread.h"
#include <QMap>
#include <QStringList>
#include <QPair>

class ThreadModif:public MesThread
{
    QString prefixeCommun;
    QStringList nomsFichiers;
    QMap<QString,QList<QPair<int,QString> > > lignesAModifier;
    QString regLignes;
    bool casseLignes;
    bool motsEntiersLignes;
    QString chaineRemplacement;
    bool backup;
	static QString lireFichier(const QString&);
    static void ecrireFichier(const QString& _nom,const QString& lignes_);
public:
    ThreadModif(const QString&,
                const QStringList&,
                const QMap<QString,QList<QPair<int,QString> > >&,
                const QString&,
                bool,bool,const QString&,bool,QObject *parent = 0);
	void run();

};

#endif // THREADMODIF_H
