#include "base_donnees/cartes/plateauligue.h"

PlateauLigue::PlateauLigue(const QStringList& _lignes){
	int ind_=0;
	while(!_lignes[ind_].contains("<EnvLigue coords")){
		ind_++;
	}
	while(_lignes[ind_].contains("<EnvLigue coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		ind_++;
		int ind_deb_=ind_;
		while(!_lignes[ind_].contains("</EnvLigue>")){
			ind_++;
		}
		environnements.ajouter_cle_valeur(x_y_,new EnvironnementLigue(_lignes.mid(ind_deb_,ind_-ind_deb_)));
		ind_++;
	}
	while(!_lignes[ind_].contains("<CoordsDres>")){
		ind_++;
	}
	QStringList coords_=_lignes[ind_].split(">")[1].split("<")[0].split(",");
	coords_dresseur.first=coords_[0].toInt();
	coords_dresseur.second=coords_[1].toInt();
	while(!_lignes[ind_].contains("<DresL>")){
		ind_++;
	}
	int ind_deb_=ind_+1;
	while(!_lignes[ind_].contains("</DresL>")){
		ind_++;
	}
	dresseur_ligue=new DresseurLigue(_lignes.mid(ind_deb_,ind_-ind_deb_));
	ind_++;
	coords_=_lignes[ind_].split(">")[1].split("<")[0].split(";");
	QStringList coords_2_=coords_[0].split(",");
	lien_vers_plateau_suivant.first.first.first=coords_2_[0].toInt();
	lien_vers_plateau_suivant.first.first.second=coords_2_[1].toInt();
	lien_vers_plateau_suivant.first.second.first=coords_2_[2].toInt();
	lien_vers_plateau_suivant.first.second.second=coords_2_[3].toInt();
	coords_2_=coords_[1].split(",");
	lien_vers_plateau_suivant.second.first.first=coords_2_[0].toInt();
	lien_vers_plateau_suivant.second.first.second=coords_2_[1].toInt();
	lien_vers_plateau_suivant.second.second.first=coords_2_[2].toInt();
	lien_vers_plateau_suivant.second.second.second=coords_2_[3].toInt();
}

QList<QPair<int,int> > PlateauLigue::coords_env()const{
	return environnements.cles();
}

EnvironnementLigue *PlateauLigue::environnement(const QPair<int,int>& _id)const{
	return environnements.valeur(_id);
}

QPair<int,int> PlateauLigue::val_coords_dresseur()const{
	return coords_dresseur;
}

DresseurLigue *PlateauLigue::val_dresseur_ligue()const{
	return dresseur_ligue;
}

QPair<QPair<int,int>,QPair<int,int> > PlateauLigue::dest_lien_vers_plateau_suivant()const{
	return lien_vers_plateau_suivant.second;
}

QPair<QPair<int,int>,QPair<int,int> > PlateauLigue::orig_lien_vers_plateau_suivant()const{
	return lien_vers_plateau_suivant.first;
}

PlateauLigue::~PlateauLigue(){
	typedef QPair<int,int> Origine;
	foreach(Origine o,environnements.cles()){
		EnvironnementLigue *env_=environnements.valeur(o);
		delete env_;
		env_=NULL;
	}
	delete dresseur_ligue;
	dresseur_ligue=NULL;
}


