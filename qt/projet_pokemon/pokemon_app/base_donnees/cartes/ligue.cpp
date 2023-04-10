#include "base_donnees/cartes/ligue.h"

Ligue::Ligue(const QStringList& _lignes){
	//<Plat>
	int ind_=0;
	while(!_lignes[ind_].contains("<Plat>")){
		ind_++;
	}
	while(_lignes[ind_].contains("<Plat>")){
		ind_++;
		int ind_deb_=ind_;
		while(!_lignes[ind_].contains("</Plat>")){
			ind_++;
		}
		plateaux<<new PlateauLigue(_lignes.mid(ind_deb_,ind_-ind_deb_));
		ind_++;
		if(ind_>=_lignes.size()){
			return;
		}
	}
	nom_ligue=_lignes[ind_].split(">")[1].split("<")[0];
	ind_++;
	acces=Coordonnees(_lignes[ind_].split(">")[1].split("<")[0]);
	ind_++;
	origine=Coordonnees(_lignes[ind_].split(">")[1].split("<")[0]);
}

QString Ligue::nom()const{
	return nom_ligue;
}

Coordonnees Ligue::acces_c()const{
	return acces;
}

Coordonnees Ligue::origine_c()const{
	return origine;
}

PlateauLigue *Ligue::plateau(int _indice)const{
	return plateaux[_indice];
}

int Ligue::nb_plateaux()const{
	return plateaux.size();
}

Ligue::~Ligue(){
	foreach(PlateauLigue *p,plateaux){
		delete p;
		p=NULL;
	}
}


