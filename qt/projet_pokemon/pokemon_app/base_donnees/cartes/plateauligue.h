#ifndef PLATEAULIGUE_H
#define PLATEAULIGUE_H
#include "serialisable/base_donnees/hashmap.h"
#include "base_donnees/cartes/environnementligue.h"
#include "base_donnees/personnages/dresseurligue.h"

/***/
class PlateauLigue{

	/***/
	HashMap<QPair<int,int>,EnvironnementLigue*> environnements;

	/***/
	//HashMap<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<QPair<int,int>,QPair<int,int> >,int> > liens_vers_autres_plateau_meme_lieu;
	QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > lien_vers_plateau_suivant;

	/**Coordonnées du dresseur de la ligue*/
	QPair<int,int> coords_dresseur;

	/**dresseur présent dans une salle de la ligue.*/
	DresseurLigue *dresseur_ligue;

public:

	PlateauLigue(const QStringList&);

	QPair<int,int> val_coords_dresseur()const;

	QList<QPair<int,int> > coords_env()const;

	/**Méthode récupérant l'adresse d'un environnement
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
	@return l'adresse de l'environnement aux coordonnées indiquées*/
	EnvironnementLigue *environnement(const QPair<int,int>&)const;

	DresseurLigue *val_dresseur_ligue()const;

	QPair<QPair<int,int>,QPair<int,int> > dest_lien_vers_plateau_suivant()const;

	QPair<QPair<int,int>,QPair<int,int> > orig_lien_vers_plateau_suivant()const;

	virtual ~PlateauLigue();
};
#endif


