#include "serialisable/pokemon/pokemondresse.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include "math/taux.h"
uchar PokemonDresse::_nb_attaques_max_=4;//(uchar)Taux::parse_taux(Utilitaire::constante(Import::_constantes_,"DEF_MAX_ATT"));

PokemonDresse::PokemonDresse(){
	;
}

PokemonDresse::PokemonDresse(const Pokemon& _pk,const QStringList& _attaq){
	attaques=_attaq;
	Pokemon pk_=_pk;
	*adr_nom()=*pk_.adr_nom();
	*adr_niveau()=*pk_.adr_niveau();
	*adr_genre()=*pk_.adr_genre();
	*adr_capacite()=*pk_.adr_capacite();
	*adr_nom_objet()=*pk_.adr_nom_objet();
}

bool PokemonDresse::operator==(const PokemonDresse& _autre)const{
	return Pokemon::operator==(_autre)&&attaques==_autre.attaques;
}

QStringList* PokemonDresse::adr_attaques(){
	return &attaques;
}

QString PokemonDresse::exporter_attributs(int _nb_tab_attr)const{
	QString formattage_=Pokemon::exporter_attributs(_nb_tab_attr);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Att>"+QStringList(attaques.mid(0,PokemonDresse::_nb_attaques_max_)).join(";")+"</Att>\n";
	return formattage_;
}

QString PokemonDresse::exporter(int _nb_tab_attr)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Pok>\n";
	formattage_+=PokemonDresse::exporter_attributs(_nb_tab_attr+1);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="</Pok>\n";
	return formattage_;
}

void PokemonDresse::serialiser(Flux& _out)const{
	Pokemon::serialiser(_out);
	_out<<attaques;
}

void PokemonDresse::deserialiser(Flux& _in){
	Pokemon::deserialiser(_in);
	_in>>attaques;
}

Flux & operator <<(Flux& out,const PokemonDresse& _Pokemon){
	_Pokemon.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,PokemonDresse& _Pokemon){
	_Pokemon.deserialiser(in);
	return in;
}



