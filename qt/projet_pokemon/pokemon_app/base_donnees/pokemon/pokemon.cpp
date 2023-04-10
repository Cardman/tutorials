#include "base_donnees/pokemon/pokemon.h"
#include <QStringList>

Pokemon::Pokemon(){

}

Pokemon::Pokemon(const QStringList& _lignes){
	nom=_lignes[0].split(">")[1].split("<")[0];
	niveau=(uchar)_lignes[1].split(">")[1].split("<")[0].toUInt();
	genre=_lignes[2].split(">")[1].split("<")[0];
	capacite=_lignes[3].split(">")[1].split("<")[0];
	nom_objet=_lignes[4].split(">")[1].split("<")[0];
	//statut="OK"
}

QString Pokemon::n_pk()const{
	return nom;
}

uchar Pokemon::niv_pk()const{
	return niveau;
}

QString Pokemon::genre_pk()const{
	return genre;
}

QString Pokemon::capacite_pk()const{
	return capacite;
}

QString Pokemon::objet()const{
	return nom_objet;
}



