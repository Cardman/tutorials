#include "serialisable/pokemon/oeufpokemon.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/donnees.h"

const int OeufPokemon::max_pas_eclore=10000;
OeufPokemon::OeufPokemon(){
	;
}

OeufPokemon::OeufPokemon(const QString& _nom,Donnees *_d){
	nom_parent=_nom;
	nombre_pas=0;
	nom=_d->val_pokedex().valeur(nom_parent)->b_ev();
}

QString OeufPokemon::nom_pk()const{
	return nom;
}

void OeufPokemon::vers_eclosion(uchar _coeff){
	nombre_pas+=_coeff;
}

int OeufPokemon::nb_pas()const{
	return nombre_pas;
}

void OeufPokemon::serialiser(Flux& _out)const{
	_out<<nom;
	_out<<nom_parent;
	_out<<nombre_pas;
}

void OeufPokemon::deserialiser(Flux& _in){
	_in>>nom;
	_in>>nom_parent;
	_in>>nombre_pas;
}

Flux & operator <<(Flux& out,const OeufPokemon& _OeufPokemon){
	_OeufPokemon.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,OeufPokemon& _OeufPokemon){
	_OeufPokemon.deserialiser(in);
	return in;
}


