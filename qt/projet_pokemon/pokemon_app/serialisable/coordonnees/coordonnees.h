#ifndef COORDONNEES_H
#define COORDONNEES_H
#include <QPair>
#include "flux/flux.h"

/***/
class Coordonnees{

	/***/
	QPair<int,int> lieu_plateau;

	/***/
	QPair<int,int> environnement;

	/***/
	QPair<int,int> tuile;

public:

	Coordonnees();

	/**Parseur de coordonnées, attention la chaîne doit être de la forme
	<entier int>,<entier int>;<entier int>,<entier int>;<entier int>,<entier int>*/
	Coordonnees(const QString&);

	/**
@return le lieu correspondant aux coordonnées.*/
	int lieu()const;

	int& lieu();

	/**
@return le plateau du lieu correspondant.*/
	int plateau()const;

	int& plateau();

	QPair<int,int> val_lieu_plateau()const;
	/**@return l'adresse de lieu_plateau.first*/
	//int *adr_lieu();

	/**@return l'adresse de lieu_plateau.second*/
	//int *adr_plateau();

	/**@return l'adresse de lieu_plateau*/
	//QPair<int,int> *adr_lieu_plateau();

	/**
@return les coordonnées de l'environnement par rapport au plateau qui le contient.*/
	QPair<int,int> coords_environnement()const;

	QPair<int,int>& coords_environnement();

	/**@return l'adresse de environnement*/
	//QPair<int,int> *adr_environnement();

	/**
@return les coordonnées de la tuile par rapport à l'environnement qui la contient.*/
	QPair<int,int> coords_tuile()const;

	QPair<int,int>& coords_tuile();

	/**@return l'adresse de tuile*/
	//QPair<int,int> *adr_tuile();

	/***/
	QPair<QPair<int,int>,QPair<int,int> > coords_par_rap_plateau()const;

	/***/
	QPair<int,QPair<QPair<int,int>,QPair<int,int> > > coords_par_rap_lieu()const;

	/**@return une chaîne formatée contenant les informations sur les coordonnées*/
	QString formater()const;

	bool operator==(const Coordonnees&)const;

	bool operator!=(const Coordonnees&)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const Coordonnees&);
Flux & operator >>(Flux&,Coordonnees&);

#endif


