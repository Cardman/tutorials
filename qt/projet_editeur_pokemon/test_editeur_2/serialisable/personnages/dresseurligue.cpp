#include "serialisable/personnages/dresseurligue.h"
DresseurLigue::DresseurLigue(){
	;
}

bool DresseurLigue::egal(const DresseurLigue& _autre)const{
	bool egal_;
	egal_=Dresseur::egal(_autre);
	egal_&=equipe==_autre.equipe;
	egal_&=recompense_base==_autre.recompense_base;
	return egal_;
}

QList<PokemonDresse> *DresseurLigue::adr_equipe(){
	return &equipe;
}

int *DresseurLigue::adr_recompense_base(){
	return &recompense_base;
}

bool DresseurLigue::est_valide()const{
	return !equipe.isEmpty()&&recompense_base>0;
}

QString DresseurLigue::exporter_attributs(int _nb_tab_attr)const{
	QString formattage_=Dresseur::exporter_attributs(_nb_tab_attr);
	for(int j=0;j<_nb_tab_attr;j++){
		formattage_+="\t";
	}
	formattage_+="<E>\n";
	int _nb_tab_attr_2=_nb_tab_attr+1;
	int nb_pk_=equipe.size();
	for(int j=0;j<nb_pk_;j++){
		formattage_+=equipe[j].exporter(_nb_tab_attr_2);
	}
	for(int j=0;j<_nb_tab_attr_2;j++){
		formattage_+="\t";
	}
	formattage_+="<R>"+QString::number(recompense_base)+"</R>\n";
	for(int j=0;j<_nb_tab_attr;j++){
		formattage_+="\t";
	}
	formattage_+="</E>\n";
	return formattage_;
}

QString DresseurLigue::exporter(int _nb_tab_attr)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<DresL>\n";
	formattage_+=DresseurLigue::exporter_attributs(_nb_tab_attr+1);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="</DresL>\n";
	return formattage_;
}

bool operator==(const DresseurLigue& a,const DresseurLigue& b){
	return a.egal(b);
}

void DresseurLigue::serialiser(Flux& _out)const{
	Dresseur::serialiser(_out);
	_out<<equipe;
	_out<<recompense_base;
}

void DresseurLigue::deserialiser(Flux& _in){
	Dresseur::deserialiser(_in);
	_in>>equipe;
	_in>>recompense_base;
}

Flux & operator <<(Flux& out,const DresseurLigue& _DresseurLigue){
	_DresseurLigue.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,DresseurLigue& _DresseurLigue){
	_DresseurLigue.deserialiser(in);
	return in;
}



