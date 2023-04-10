#include "base_donnees/personnages/champion.h"
#include <QStringList>

Champion::Champion(const QStringList& _lignes):Dresseur1(sous_attributs(_lignes)){
	int ind_=_lignes.size()-3;
	badge=_lignes[ind_].split(">")[1].split("<")[0];
	ct=(uchar)_lignes[ind_+1].split(">")[1].split("<")[0].toUInt();
	cs=(uchar)_lignes[ind_+2].split(">")[1].split("<")[0].toUInt();
}

QStringList Champion::sous_attributs(const QStringList& attributs){
	int i_=0;
	int nb_attr_=attributs.size();
	while(i_<nb_attr_){
		if(attributs[i_].contains("<B>")){
			break;
		}
		i_++;
	}
	return attributs.mid(0,i_);
}

uchar Champion::val_cs()const{
	return cs;
}

uchar Champion::val_ct()const{
	return ct;
}


