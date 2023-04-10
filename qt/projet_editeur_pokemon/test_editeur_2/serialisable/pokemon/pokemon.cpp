#include "serialisable/pokemon/pokemon.h"
Pokemon::Pokemon(){
	niveau=1;
}

/*Pokemon::Pokemon(const QString& _nom,const QString& _genre,uchar _niveau,const QString& _capacite,const QString& _nom_objet){
	
}*/

QString* Pokemon::adr_nom(){
	return &nom;
}

uchar* Pokemon::adr_niveau(){
	return &niveau;
}

QString* Pokemon::adr_genre(){
	return &genre;
}

QString* Pokemon::adr_capacite(){
	return &capacite;
}

QString* Pokemon::adr_nom_objet(){
	return &nom_objet;
}

bool Pokemon::operator==(const Pokemon& _autre)const{
	bool egal_=nom==_autre.nom;
	egal_&=niveau==_autre.niveau;
	egal_&=genre==_autre.genre;
	egal_&=capacite==_autre.capacite;
	egal_&=nom_objet==_autre.nom_objet;
	return egal_;
}

QString Pokemon::exporter_attributs(int _nb_tab_attr)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Nom>"+nom+"</Nom>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Niv>"+QString::number(niveau)+"</Niv>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<G>"+genre+"</G>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<C>"+capacite+"</C>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<O>"+nom_objet+"</O>\n";
	return formattage_;
}

QString Pokemon::exporter(int _nb_tab_attr)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Pok>\n";
	formattage_+=Pokemon::exporter_attributs(_nb_tab_attr+1);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="</Pok>\n";
	return formattage_;
}

QString Pokemon::exporter(int _nb_tab_attr,const QPair<int,int>& _coords)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Pok coords=\""+QString::number(_coords.first)+","+QString::number(_coords.second)+"\">\n";
	formattage_+=Pokemon::exporter_attributs(_nb_tab_attr+1);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="</Pok>\n";
	return formattage_;
}

void Pokemon::serialiser(Flux& _out)const{
	_out<<nom;
	_out<<niveau;
	_out<<genre;
	_out<<capacite;
	_out<<nom_objet;
}

void Pokemon::deserialiser(Flux& _in){
	_in>>nom;
	_in>>niveau;
	_in>>genre;
	_in>>capacite;
	_in>>nom_objet;
}

Flux & operator <<(Flux& out,const Pokemon& _Pokemon){
	_Pokemon.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Pokemon& _Pokemon){
	_Pokemon.deserialiser(in);
	return in;
}



