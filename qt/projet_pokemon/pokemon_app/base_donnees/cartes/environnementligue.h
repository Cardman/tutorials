#ifndef ENVIRONNEMENTLIGUE_H
#define ENVIRONNEMENTLIGUE_H
#include "base_donnees/cartes/tuile.h"

/***/
class EnvironnementLigue{

	/***/
	int largeur;

	/***/
	QString type_environnement;

	/***/
	QList<Tuile*> tuiles;

	/***/
	QList<QPair<QPair<int,int>,QPair<int,int> > > environnements_voisins;

public:

	EnvironnementLigue(const QStringList&);

	QPair<int,int> dimensions()const;

	bool existe(const QPair<int,int>&)const;

	QPair<QPair<int,int>,QPair<int,int> > voisin(const QPair<int,int>&,const QPair<int,int>&)const;

	QString type()const;

	Tuile* tuile(const QPair<int,int>&)const;

	virtual ~EnvironnementLigue();
};
#endif


