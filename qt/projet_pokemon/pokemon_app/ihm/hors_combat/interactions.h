#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include <QLabel>
#include "serialisable/base_donnees/hashmap.h"
class Donnees;
class Bouton;
class QVBoxLayout;
class Interactions : public QLabel
{
	QLabel *commentaire;

	QVBoxLayout *lay_boutons;

	HashMap<uchar,Bouton*> boutons;

	HashMap<uchar,QString> act_boutons;

	Q_OBJECT
public:
	Interactions(Donnees*);

	void maj_interaction(uchar,const QStringList&);

	void raz_interaction();

	void maj_commentaire(const QString&);
signals:

	void clic(uchar,uchar,const QString&);

private slots:

	void cliquer(const QString&);
};

#endif // INTERACTIONS_H
