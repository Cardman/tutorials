#include "base_donnees/pokemon/pokemondresse.h"
#include "base_donnees/attaques/ficheattaque.h"

PokemonDresse::PokemonDresse(const QStringList& _lignes):Pokemon(_lignes.mid(0,_lignes.size()-1)){
	attaques=_lignes.last().split(">")[1].split("<")[0].split(";");
}

QStringList PokemonDresse::attaq()const{
	return attaques;
}


