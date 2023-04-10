#ifndef DRESSEUR_H
#define DRESSEUR_H
#include "serialisable/personnages/personnage.h"
#include "serialisable/pokemon/pokemondresse.h"

/**La portée protected indique qu'il existe une classe dérivant de celle-ci*/
class Dresseur: public Personnage{

	/**Nom de l'image a utiliser pour afficher la face du dresseur*/
	QString nom_image;

	/**message de fin de combat*/
	QString message_fin_combat;

	/**message de début de combat*/
	QString message_debut_combat;

	/**1 si combat simple (1 vs 1, a la fois), la plupart des cas
2 si combat double (2 vs 2, a la fois),
...
*/
	uchar multiplicite_combat;

	/**gain d'argent de base après le combat.TODO à faire diparaître et à placer dans Champion*/
	//int recompense_base;

	/**Equipes du dresseur.
	ensemble des duos equipes des pokemon - recompense en fonction du numero de la ligue si le dresseur fait partie de la ligue*/
	//QList<QPair<QList<PokemonDresse>,int> > equipes;

protected:

	/**Cette méthode exporte les attributs de la classe
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@return une chaîne formatée contenant tous les attributs*/
	virtual QString exporter_attributs(int)const;

public:

	/**Constructeur permettant de sérialiser un dresseur*/
	Dresseur();

	virtual bool egal(const Dresseur&)const;

	/**@return l'adresse de nom_image*/
	QString* adr_nom_image();

	/**@return l'adresse de message_fin_combat*/
	QString* adr_message_fin_combat();

	/**@return l'adresse de message_debut_combat*/
	QString* adr_message_debut_combat();

	/**@return l'adresse de multiplicite_combat*/
	uchar* adr_multiplicite_combat();

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

bool operator==(const Dresseur&,const Dresseur&);

Flux & operator <<(Flux&,const Dresseur&);
Flux & operator >>(Flux&,Dresseur&);

#endif



