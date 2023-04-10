#include "base_donnees/personnages/dresseur1.h"
#include <QStringList>

Dresseur1::Dresseur1(const QStringList& _lignes):Dresseur(sous_attributs(_lignes,"<M>")){
	int ind_=7;
	int nb_attr_=_lignes.size();
	while(ind_<nb_attr_){
		//int deb_=ind_
		//int fin_=deb_
		QList<PokemonDresse*> ls_;
		int recompense_=1;
		while(!_lignes[ind_].contains("<R>")){
			//fin_++
			while(!_lignes[ind_].contains("<Pok>")){
				ind_++;
			}
			int deb_pk_=ind_+1;
			int fin_pk_=deb_pk_;
			while(!_lignes[ind_].contains("</Pok>")){
				//fin_++
				fin_pk_++;
				ind_++;
			}
			ls_<<new PokemonDresse(_lignes.mid(deb_pk_,fin_pk_-deb_pk_-1));
			ind_++;;
		}
		recompense_=_lignes[ind_].split(">")[1].split("<")[0].toInt();
		equipe<<QPair<QList<PokemonDresse*>,int>(ls_,recompense_);
		ind_+=2;
	}
}

int Dresseur1::nb_equipes()const{
	return equipe.size();
}

QList<PokemonDresse*> Dresseur1::eq(int _indice)const{
	return equipe[_indice].first;
}

int Dresseur1::recompense(int _indice)const{
	return equipe[_indice].second;
}

Dresseur1::~Dresseur1(){
	int nb_eq_=equipe.size();
	for(int i=0;i<nb_eq_;i++){
		foreach(PokemonDresse *p,equipe[i].first){
			delete p;
			p=NULL;
		}
	}
}


