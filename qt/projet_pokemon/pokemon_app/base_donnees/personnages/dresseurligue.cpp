#include "base_donnees/personnages/dresseurligue.h"
#include <QStringList>

DresseurLigue::DresseurLigue(const QStringList& _lignes):Dresseur(sous_attributs(_lignes,"<M>")){
	int ind_=7;
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
		equipe<<new PokemonDresse(_lignes.mid(deb_pk_,fin_pk_-deb_pk_-1));
		ind_++;
	}
	recompense_base=_lignes[ind_].split(">")[1].split("<")[0].toInt();
}

QList<PokemonDresse*> DresseurLigue::eq()const{
	return equipe;
}

int DresseurLigue::recompense()const{
	return recompense_base;
}

DresseurLigue::~DresseurLigue(){
	foreach(PokemonDresse *p,equipe){
		delete p;
		p=NULL;
	}
}


