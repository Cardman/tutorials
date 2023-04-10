#include "base_donnees/cartes/lieu.h"

Lieu::Lieu(const QStringList& _lignes){
	int ind_=0;
	while(!_lignes[ind_].contains("<N>")){
		ind_++;
	}
	nom=_lignes[ind_].split(">")[1].split("<")[0];
	ind_++;
	type=_lignes[ind_].split(">")[1].split("<")[0];
	ind_++;
	while(_lignes[ind_].endsWith(":")){
		//int cle_=_lignes[ind_].left(_lignes[ind_].size()-1)
		QString ligne_=_lignes[ind_];
		ligne_.chop(1);
		while(ligne_[0]<'0'||ligne_[0]>'9'){
			ligne_.remove(0,1);
		}
		int cle_=ligne_.toInt();
		ind_++;
		int ind_deb_=ind_;
		while(!_lignes[ind_].contains("</Plat>")){
			ind_++;
		}
		plateaux.ajouter_cle_valeur(cle_,new Plateau(_lignes.mid(ind_deb_,ind_-ind_deb_)));
		ind_++;
		if(ind_>=_lignes.size()){
			return;
		}
	}
	while(_lignes[ind_].contains("<L>")){
		QStringList coords_=_lignes[ind_].split(">")[1].split("<")[0].split("_");
		QPair<int,QPair<QPair<int,int>,QPair<int,int> > > x_y_;
		QStringList coords_2_=coords_[0].split(";");
		x_y_.first=coords_2_[0].toInt();
		coords_2_=coords_2_[1].split(",");
		x_y_.second.first.first=coords_2_[0].toInt();
		x_y_.second.first.second=coords_2_[1].toInt();
		x_y_.second.second.first=coords_2_[2].toInt();
		x_y_.second.second.second=coords_2_[3].toInt();
		liens_vers_autres_lieux.ajouter_cle_valeur(x_y_,Coordonnees(coords_[1]));
		ind_++;
		if(ind_>=_lignes.size()){
			return;
		}
	}
}

QString Lieu::val_nom()const{
	return nom;
}

QString Lieu::val_type()const{
	return type;
}

QList<QPair<int,QPair<QPair<int,int>,QPair<int,int> > > > Lieu::cles_liens()const{
	return liens_vers_autres_lieux.cles();
}

bool Lieu::contient_lien(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords)const{
	return liens_vers_autres_lieux.cles().contains(_coords);
}

Coordonnees Lieu::lien_vers(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords)const{
	return liens_vers_autres_lieux.valeur(_coords);
}

QList<int> Lieu::plateaux_c()const{
	return plateaux.cles();
}

Plateau *Lieu::plateau(int _indice){
	return plateaux.valeur(_indice);
}

Lieu::~Lieu(){
	foreach(int p,plateaux.cles()){
		Plateau *pl_=plateaux.valeur(p);
		delete pl_;
		pl_=NULL;
	}
}


