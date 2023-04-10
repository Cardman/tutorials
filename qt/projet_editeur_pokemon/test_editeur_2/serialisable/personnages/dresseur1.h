#ifndef DRESSEUR1_H
#define DRESSEUR1_H
#include "serialisable/personnages/dresseur.h"
#include "serialisable/pokemon/pokemondresse.h"

/***/
class Dresseur1: public Dresseur{

	/**gain d'argent de base après le combat.TODO à faire diparaître et à placer dans Champion*/
	//int recompense_base;

	/**Equipes du dresseur.
	ensemble des duos equipes des pokemon - recompense en fonction du numero de la ligue si le dresseur fait partie de la ligue*/
	QList<QPair<QList<PokemonDresse>,int> > equipes;

protected:

	/**Cette méthode exporte les attributs de la classe
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@return une chaîne formatée contenant tous les attributs*/
	virtual QString exporter_attributs(int)const;

public:

	Dresseur1();

	virtual bool egal(const Dresseur1&)const;

	/**@return l'adresse de equipes*/
	QList<QPair<QList<PokemonDresse>,int> >* adr_equipes();

	/**Cette méthode exporte toute la classe, avec les balises d'ouverture et de fermeture
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@param _coords les coordonnées du personnage
	@return une chaîne formatée contenant tous les attributs et les balises d'ouverture et de fermeture*/
	virtual QString exporter(int,const QPair<int,int>&)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

bool operator==(const Dresseur1&,const Dresseur1&);

Flux & operator <<(Flux&,const Dresseur1&);
Flux & operator >>(Flux&,Dresseur1&);

#endif



