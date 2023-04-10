#ifndef DRESSEURLIGUE_H
#define DRESSEURLIGUE_H
#include "serialisable/personnages/dresseur.h"
#include "serialisable/pokemon/pokemondresse.h"

/***/
class DresseurLigue: public Dresseur{

	QList<PokemonDresse> equipe;

	int recompense_base;

protected:

	/**Cette méthode exporte les attributs de la classe
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@return une chaîne formatée contenant tous les attributs*/
	virtual QString exporter_attributs(int)const;

public:

	DresseurLigue();

	virtual bool egal(const DresseurLigue&)const;

	QList<PokemonDresse> *adr_equipe();

	int *adr_recompense_base();

	bool est_valide()const;

	/**Cette méthode exporte toute la classe, avec les balises d'ouverture et de fermeture
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@return une chaîne formatée contenant tous les attributs et les balises d'ouverture et de fermeture*/
	QString exporter(int)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

bool operator==(const DresseurLigue&,const DresseurLigue&);

Flux & operator <<(Flux&,const DresseurLigue&);
Flux & operator >>(Flux&,DresseurLigue&);

#endif



