#ifndef THREAD_H
#define THREAD_H

#include "mesthread.h"
#include <QMap>
#include <QList>
#include <QPair>
#include <QStringList>

class Thread : public MesThread
{
Q_OBJECT
	QMap<QString,QList<QPair<int,QString> > > lignes;
	QString nomDossier;
	QStringList nomsFichiers;
	QStringList extensions;
	QStringList extensionsBase;
	int rangRecursivite;
	QString dateTot;
	QString dateTard;
	int intervalleTemps;
	QString minOctets;
	QString maxOctets;
	QString contenuNomFichiers;
	QString expRegNomFichiers;
	bool casseNomFichiers;
	bool motsEntiersNomFichiers;
	QString contenuLignes;
	QString expRegLignes;
	bool casseLignes;
	bool motsEntiersLignes;

	QMap<QString,long long> tailles;
	QString prefixeCommun;
	const static QString separateurFichiers;

	//static QString echapperChaine(const QString&);
	static const QPair<QStringList,QStringList> motsEtSeparateursMots(const QString&);
	static bool chaineAPrendre(const QString&,const QString&,Qt::CaseSensitivity);
	static QString lireFichier(const QString&);
	//static void ecrireFichier(const QString& _nom,const QString& lignes_);
	void filtrerFichiers();
	void filtrerLignes();
	void filtrerLignesSansLireFichier();

	void rechercheFichiers();
	void rechercheSysteme();
    void rechercheLignes();
public:
    explicit Thread(const QMap<QString,QList<QPair<int,QString> > >& _lignes,
			const QString& _nomDossier,
			const QStringList& _nomsFichiers,
			const QStringList& _extensions,
			const QStringList& _extensionsBase,
			const int& _rangRecursivite,
			const QString& _dateTot,
			const QString& _dateTard,
			const int& _intervalleTemps,
			const QString& _minOctets,
			const QString& _maxOctets,
			const QString& _contenuNomFichiers,
			const QString& _expRegNomFichiers,
			const bool& _casseNomFichiers,
			const bool& _motsEntiersNomFichiers,
			const QString& _contenuLignes,
			const QString& _expRegLignes,
			const bool& _casseLignes,
			const bool& _motsEntiersLignes,QObject *parent = 0);
    QMap<QString,QList<QPair<int,QString> > > valLignes()const;
    QStringList valNomsFichiers()const;
    QString valPrefixeCommun()const;
    void majPrefixeCommun(const QString&);
    QMap<QString,long long> valTailles()const;
    void majTailles(const QMap<QString,long long>&);
    static QString prefixe(const QStringList&);
	void run();
};

#endif // THREAD_H
