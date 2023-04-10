#ifndef LIEU_H
#define LIEU_H
#include "base_donnees/cartes/plateau.h"
#include "serialisable/coordonnees/coordonnees.h"

/***/
class Lieu{

	/***/
	QString nom;

	/***/
	QString type;

	/***/
	HashMap<int,Plateau*> plateaux;

	HashMap<QPair<int,QPair<QPair<int,int>,QPair<int,int> > >,Coordonnees> liens_vers_autres_lieux;

public:

	Lieu(const QStringList&);

	QString val_nom()const;

	QString val_type()const;

	QList<QPair<int,QPair<QPair<int,int>,QPair<int,int> > > > cles_liens()const;

	bool contient_lien(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&)const;

	Coordonnees lien_vers(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&)const;

	/***/
	QList<int> plateaux_c()const;

	/**Mthode rcuprant l'adresse d'un plateau
	@param _indice indice du plateau dont on veut rcuprer l'adresse*/
	Plateau *plateau(int);

	virtual ~Lieu();
};
#endif


