#ifndef POKEMONDRESSE_H
#define POKEMONDRESSE_H
#include "serialisable/pokemon/pokemon.h"
#include <QStringList>

/**Comme les attributs de cette classe sont privés alors la classe est finale sans héritage*/
class PokemonDresse: public Pokemon{

	/***/
	QStringList attaques;

protected:

	/**Cette méthode exporte les attributs de la classe
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@return une chaîne formatée contenant tous les attributs*/
	virtual QString exporter_attributs(int)const;

public:

	static uchar _nb_attaques_max_;

	/**Constructeur permettant de sérialiser un pokémon dressé*/
	PokemonDresse();

	/***/
	PokemonDresse(const Pokemon&,const QStringList&);

	virtual bool operator==(const PokemonDresse&)const;

	/**@return l'adresse de attaques*/
	QStringList* adr_attaques();

	/**Cette méthode exporte toute la classe, avec les balises d'ouverture et de fermeture
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@return une chaîne formatée contenant tous les attributs et les balises d'ouverture et de fermeture*/
	virtual QString exporter(int)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const PokemonDresse&);
Flux & operator >>(Flux&,PokemonDresse&);

#endif



