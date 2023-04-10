#ifndef CHAMPION_H
#define CHAMPION_H
#include "serialisable/personnages/dresseur1.h"

/***/
class Champion: public Dresseur1{

	/**badge permettant d'utiliser une CS et d'avancer vers la ligue.*/
	QString badge;

	/**capsule technique donnee par le champion d'arene*/
	uchar ct;

	/**Si cette variable ne vaut pas 0, alors cette variable vaut le numero de la capsule secrete autorisee*/
	uchar cs;

	/**Cette méthode exporte les attributs de la classe
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@return une chaîne formatée contenant tous les attributs*/
	virtual QString exporter_attributs(int)const;

public:

	/**Constructeur permettant de sérialiser la classe*/
	Champion();

	/***/
	Champion(const Dresseur1&);

	virtual bool egal(const Champion&)const;

	/**@return l'adresse de badge*/
	QString* adr_badge();

	/**@return l'adresse de ct*/
	uchar* adr_ct();

	/**@return l'adresse de cs*/
	uchar* adr_cs();

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

bool operator==(const Champion&,const Champion&);

Flux & operator <<(Flux&,const Champion&);
Flux & operator >>(Flux&,Champion&);

#endif



