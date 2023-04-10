#ifndef PLATEAU_H
#define PLATEAU_H
#include "serialisable/base_donnees/hashmap.h"
#include "base_donnees/cartes/environnement.h"
#include "serialisable/coordonnees/coordonnees.h"

/***/
class Plateau{

	/***/
	HashMap<QPair<int,int>,Environnement*> environnements;

	/***/
	HashMap<QPair<QPair<int,int>,QPair<int,int> >,QString> noms_images_liens;

	/***/
	HashMap<QPair<QPair<int,int>,QPair<int,int> >,Coordonnees> liens_vers_autres_plateau;

public:

	Plateau(const QStringList&);

	QList<QPair<QPair<int,int>,QPair<int,int> > > origines_liens()const;

	bool contient_lien(const QPair<QPair<int,int>,QPair<int,int> >&)const;

	Coordonnees destination_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine)const;

	QString image_destination_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine)const;

	QList<QPair<int,int> > coords_env()const;

	Environnement *environnement(const QPair<int,int>& _id)const;

	virtual ~Plateau();
};
#endif


