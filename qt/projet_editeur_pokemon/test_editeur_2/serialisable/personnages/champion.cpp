#include "serialisable/personnages/champion.h"
Champion::Champion(){
	;
}

Champion::Champion(const Dresseur1& _dresseur){
	Dresseur1 dr_=_dresseur;
	*adr_nom_image()=*dr_.adr_nom_image();
	*adr_message_fin_combat()=*dr_.adr_message_fin_combat();
	*adr_message_debut_combat()=*dr_.adr_message_debut_combat();
	*adr_multiplicite_combat()=*dr_.adr_multiplicite_combat();
	*adr_equipes()=*dr_.adr_equipes();
	*adr_nom()=*dr_.adr_nom();
	*adr_nom_miniature()=*dr_.adr_nom_miniature();
	*adr_orientation()=*dr_.adr_orientation();
}

bool Champion::egal(const Champion& _autre)const{
	bool egal_;
	egal_=Dresseur1::egal(_autre);
	egal_&=ct==_autre.ct;
	egal_&=cs==_autre.cs;
	egal_&=badge==_autre.badge;
	return egal_;
}

QString* Champion::adr_badge(){
	return &badge;
}

uchar* Champion::adr_ct(){
	return &ct;
}

uchar* Champion::adr_cs(){
	return &cs;
}

QString Champion::exporter_attributs(int _nb_tab_attr)const{
	QString formattage_=Dresseur1::exporter_attributs(_nb_tab_attr);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<B>"+badge+"</B>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<CT>"+QString::number(ct)+"</CT>\n";
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<CS>"+QString::number(cs)+"</CS>\n";
	return formattage_;
}

QString Champion::exporter(int _nb_tab_attr,const QPair<int,int>& _coords)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Champ coords=\""+QString::number(_coords.first)+","+QString::number(_coords.second)+"\">\n";
	formattage_+=Champion::exporter_attributs(_nb_tab_attr+1);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="</Champ>\n";
	return formattage_;
}

bool operator==(const Champion& a,const Champion& b){
	return a.egal(b);
}

void Champion::serialiser(Flux& _out)const{
	Dresseur1::serialiser(_out);
	_out<<badge;
	_out<<ct;
	_out<<cs;
}

void Champion::deserialiser(Flux& _in){
	Dresseur1::deserialiser(_in);
	_in>>badge;
	_in>>ct;
	_in>>cs;
}

Flux & operator <<(Flux& out,const Champion& _Champion){
	_Champion.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Champion& _Champion){
	_Champion.deserialiser(in);
	return in;
}



