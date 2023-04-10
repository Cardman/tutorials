#ifndef POKEMONDRESSE_H
#define POKEMONDRESSE_H
#include "base_donnees/pokemon/pokemon.h"
#include <QStringList>

/***/
class PokemonDresse: public Pokemon{

	/***/
	QStringList attaques;

public:

	/**Parseur d'un pokémon dressé*/
	PokemonDresse(const QStringList&);

	QStringList attaq()const;
};
#endif


