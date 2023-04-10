#include "serialisable/personnages/dresseur.h"
Dresseur::Dresseur(){
	multiplicite_combat=1;
}

bool Dresseur::egal(const Dresseur& _autre)const{
	bool egal_;
	egal_=Personnage::egal(_autre);
	egal_&=nom_image==_autre.nom_image;
	egal_&=message_fin_combat==_autre.message_fin_combat;
	egal_&=message_debut_combat==_autre.message_debut_combat;
	egal_&=multiplicite_combat==_autre.multiplicite_combat;
	return egal_;
}

QString* Dresseur::adr_nom_image(){
	return &nom_image;
}

QString* Dresseur::adr_message_fin_combat(){
	return &message_fin_combat;
}

QString* Dresseur::adr_message_debut_combat(){
	return &message_debut_combat;
}

uchar* Dresseur::adr_multiplicite_combat(){
	return &multiplicite_combat;
}

QString Dresseur::exporter_attributs(int _nb_tab_attr)const{
	QString formattage_=Personnage::exporter_attributs(_nb_tab_attr);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<NomI>"+nom_image+"</NomI>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<MF>"+message_fin_combat+"</MF>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<MD>"+message_debut_combat+"</MD>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<M>"+QString::number(multiplicite_combat)+"</M>\n";
	return formattage_;
}

QString Dresseur::exporter(int _nb_tab_attr,const QPair<int,int>& _coords)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Dres coords=\""+QString::number(_coords.first)+","+QString::number(_coords.second)+"\">\n";
	formattage_+=Dresseur::exporter_attributs(_nb_tab_attr+1);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="</Dres>\n";
	return formattage_;
}

bool operator==(const Dresseur& a,const Dresseur& b){
	return a.egal(b);
}

void Dresseur::serialiser(Flux& _out)const{
	Personnage::serialiser(_out);
	_out<<nom_image;
	_out<<message_fin_combat;
	_out<<message_debut_combat;
	_out<<multiplicite_combat;
}

void Dresseur::deserialiser(Flux& _in){
	Personnage::deserialiser(_in);
	_in>>nom_image;
	_in>>message_fin_combat;
	_in>>message_debut_combat;
	_in>>multiplicite_combat;
}

Flux & operator <<(Flux& out,const Dresseur& _Dresseur){
	_Dresseur.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Dresseur& _Dresseur){
	_Dresseur.deserialiser(in);
	return in;
}



