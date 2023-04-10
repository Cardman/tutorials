#include "serialisable/personnages/personnage.h"
Personnage::Personnage(){
	;
}

bool Personnage::egal(const Personnage& _autre)const{
	return nom_miniature==_autre.nom_miniature&&nom==_autre.nom&&orientation==_autre.orientation;
}

QString* Personnage::adr_nom(){
	return &nom;
}

QString* Personnage::adr_nom_miniature(){
	return &nom_miniature;;
}

QPair<int,int>* Personnage::adr_orientation(){
	return &orientation;
}

QString Personnage::exporter_attributs(int _nb_tab_attr)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<NomP>"+nom+"</NomP>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Nom>"+nom_miniature+"</Nom>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<O>"+QString::number(orientation.first)+","+QString::number(orientation.second)+"</O>\n";
	return formattage_;
}

QString Personnage::exporter(int _nb_tab_attr,const QPair<int,int>& _coords)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Pers coords=\""+QString::number(_coords.first)+","+QString::number(_coords.second)+"\">\n";
	formattage_+=Personnage::exporter_attributs(_nb_tab_attr+1);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="</Pers>\n";
	return formattage_;
}

bool operator==(const Personnage& a,const Personnage& b){
	return a.egal(b);
}

void Personnage::serialiser(Flux& _out)const{
	_out<<nom;
	_out<<nom_miniature;
	_out<<orientation;
}

void Personnage::deserialiser(Flux& _in){
	_in>>nom;
	_in>>nom_miniature;
	_in>>orientation;
}

Flux & operator <<(Flux& out,const Personnage& _Personnage){
	_Personnage.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Personnage& _Personnage){
	_Personnage.deserialiser(in);
	return in;
}



