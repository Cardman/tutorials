#include "base_donnees/cartes/environnementligue.h"

EnvironnementLigue::EnvironnementLigue(const QStringList& _lignes){
	largeur=_lignes[0].split(">")[1].split("<")[0].toInt();
	type_environnement=_lignes[1].split(">")[1].split("<")[0];
	int ind_=2;
	while(_lignes[ind_].contains("<Tuile>")){
		tuiles<<new Tuile(_lignes[ind_]);
		ind_++;
	}
	QPair<int,int> dims_=dimensions();
	int per_=2*(dims_.first+dims_.second);
	//dimensions()
	//while(ind_<nb_vois_){//environnements_voisins.size()<2*(dims_.first+dims_.second)
	while(environnements_voisins.size()<per_){
		if(_lignes[ind_].contains("<V/>")){
			environnements_voisins<<QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(-1,-1),QPair<int,int>(-1,-1));
		}else{
			QStringList coords_=_lignes[ind_].split(">")[1].split("<")[0].split(";");
			QStringList coords_1_=coords_[0].split(",");
			QStringList coords_2_=coords_[1].split(",");
			QPair<QPair<int,int>,QPair<int,int> > vois_;
			vois_.first.first=coords_1_[0].toInt();
			vois_.first.second=coords_1_[1].toInt();
			vois_.second.first=coords_2_[0].toInt();
			vois_.second.second=coords_2_[1].toInt();
			environnements_voisins<<vois_;
		}
		ind_++;
	}
}

bool EnvironnementLigue::existe(const QPair<int,int>& _id)const{
	QPair<int,int> dims_=dimensions();
	if(_id.first<0||_id.first>=dims_.first){
		return false;
	}
	if(_id.second<0||_id.second>=dims_.second){
		return false;
	}
	return true;
}

QPair<int,int> EnvironnementLigue::dimensions()const{
	return QPair<int,int>(largeur,tuiles.size()/largeur);
}

QPair<QPair<int,int>,QPair<int,int> > EnvironnementLigue::voisin(const QPair<int,int>& _coords_tuile,const QPair<int,int>& _direction)const{
	int cte_=(_direction.second-_direction.first-1)/2;
	int ax_=_direction.second;
	int ay_=-_direction.first;
	int h_=_direction.second*(_direction.second+1)/2-2*cte_;
	int l_=_direction.second*(_direction.second-1)/2-cte_;
	QPair<int,int> dims_=dimensions();
	return environnements_voisins[l_*dims_.first+h_*dims_.second+_coords_tuile.first*ax_+_coords_tuile.second*ay_+cte_];
}

QString EnvironnementLigue::type()const{
	return type_environnement;
}

Tuile* EnvironnementLigue::tuile(const QPair<int,int>& _coords_tuile)const{
	return tuiles[_coords_tuile.first+largeur*_coords_tuile.second];
}

EnvironnementLigue::~EnvironnementLigue(){
	foreach(Tuile *t,tuiles){
		delete t;
		t=NULL;
	}
}


