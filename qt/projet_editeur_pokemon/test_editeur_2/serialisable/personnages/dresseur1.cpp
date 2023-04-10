#include "serialisable/personnages/dresseur1.h"
Dresseur1::Dresseur1(){
	;
}

bool Dresseur1::egal(const Dresseur1& _autre)const{
	bool egal_;
	egal_=Dresseur::egal(_autre);
	egal_&=equipes==_autre.equipes;
	return egal_;
}

QList<QPair<QList<PokemonDresse>,int> >* Dresseur1::adr_equipes(){
	return &equipes;
}

QString Dresseur1::exporter_attributs(int _nb_tab_attr)const{
	QString formattage_=Dresseur::exporter_attributs(_nb_tab_attr);
	int nb_equipe_=equipes.size();
	for(int i=0;i<nb_equipe_;i++){
		for(int j=0;j<_nb_tab_attr;j++){
			formattage_+="\t";
		}
		formattage_+="<E>\n";
		int _nb_tab_attr_2=_nb_tab_attr+1;
		int nb_pk_=equipes[i].first.size();
		for(int j=0;j<nb_pk_;j++){
			formattage_+=equipes[i].first[j].exporter(_nb_tab_attr_2);
		}
		for(int j=0;j<_nb_tab_attr_2;j++){
			formattage_+="\t";
		}
		formattage_+="<R>"+QString::number(equipes[i].second)+"</R>\n";
		for(int j=0;j<_nb_tab_attr;j++){
			formattage_+="\t";
		}
		formattage_+="</E>\n";
	}
	return formattage_;
}

QString Dresseur1::exporter(int _nb_tab_attr,const QPair<int,int>& _coords)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="<Dres coords=\""+QString::number(_coords.first)+","+QString::number(_coords.second)+"\">\n";
	formattage_+=Dresseur1::exporter_attributs(_nb_tab_attr+1);
	for(int i=0;i<_nb_tab_attr;i++){
		formattage_+="\t";
	}
	formattage_+="</Dres>\n";
	return formattage_;
}

bool operator==(const Dresseur1& a,const Dresseur1& b){
	return a.egal(b);
}

void Dresseur1::serialiser(Flux& _out)const{
	Dresseur::serialiser(_out);
	_out<<equipes;
}

void Dresseur1::deserialiser(Flux& _in){
	Dresseur::deserialiser(_in);
	_in>>equipes;
}

Flux & operator <<(Flux& out,const Dresseur1& _Dresseur1){
	_Dresseur1.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Dresseur1& _Dresseur1){
	_Dresseur1.deserialiser(in);
	return in;
}



