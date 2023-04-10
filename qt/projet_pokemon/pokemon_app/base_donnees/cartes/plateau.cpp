#include "base_donnees/cartes/plateau.h"
#include <QStringList>

Plateau::Plateau(const QStringList& _lignes){
	int ind_=0;
	while(!_lignes[ind_].contains("<Env coords")){
		ind_++;
	}
	while(_lignes[ind_].contains("<Env coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		ind_++;
		int ind_deb_=ind_;
		while(!_lignes[ind_].contains("</Env>")){
			ind_++;
		}
		environnements.ajouter_cle_valeur(x_y_,new Environnement(_lignes.mid(ind_deb_,ind_-ind_deb_)));
		ind_++;
		if(ind_>=_lignes.size()){
			return;
		}
	}
	while(_lignes[ind_].contains("<P>")){
		QStringList coords_=_lignes[ind_].split(">")[1].split("<")[0].split("_");
		QPair<QPair<int,int>,QPair<int,int> > x_y_;
		QStringList coords_2_=coords_[0].split(",");
		x_y_.first.first=coords_2_[0].toInt();
		x_y_.first.second=coords_2_[1].toInt();
		x_y_.second.first=coords_2_[2].toInt();
		x_y_.second.second=coords_2_[3].toInt();
		liens_vers_autres_plateau.ajouter_cle_valeur(x_y_,Coordonnees(coords_[1]));
		ind_++;
		noms_images_liens.ajouter_cle_valeur(x_y_,_lignes[ind_].split(">")[1].split("<")[0]);
		ind_++;
		if(ind_>=_lignes.size()){
			break;
		}
	}
}

QList<QPair<QPair<int,int>,QPair<int,int> > > Plateau::origines_liens()const{
	return liens_vers_autres_plateau.cles();
}

QList<QPair<int,int> > Plateau::coords_env()const{
	return environnements.cles();
}

Environnement *Plateau::environnement(const QPair<int,int>& _id)const{
	return environnements.valeur(_id);
}


bool Plateau::contient_lien(const QPair<QPair<int,int>,QPair<int,int> >& _origine)const{
	return liens_vers_autres_plateau.cles().contains(_origine);
}

Coordonnees Plateau::destination_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine)const{
	return liens_vers_autres_plateau.valeur(_origine);
}

QString Plateau::image_destination_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine)const{
	return noms_images_liens.valeur(_origine);
}

Plateau::~Plateau(){
	typedef QPair<int,int> Origine;
	foreach(Origine o,environnements.cles()){
		Environnement *env_=environnements.valeur(o);
		delete env_;
		env_=NULL;
	}
}


