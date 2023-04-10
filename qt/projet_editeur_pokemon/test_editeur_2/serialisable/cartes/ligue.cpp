#include "serialisable/cartes/ligue.h"
Ligue::Ligue(){
	acces.adr_lieu_plateau()->second=-1;
}

bool Ligue::egal(const Ligue& _autre)const{
	bool egal_;
	egal_=acces==_autre.acces;
	egal_&=origine==_autre.origine;
	egal_&=plateaux==_autre.plateaux;
	return egal_;
}

/*QPair<int,PlateauLigue> *Ligue::adr_plateau_en_cours(){
	return &plateau_en_cours
}*/

bool Ligue::est_valide()const{
	if(plateaux.isEmpty()){
		return false;
	}
	bool valide_=true;
	int nb_pl_=nb_plateaux();
	for(int i=0;i<nb_pl_;i++){
		QList<QPair<int,int> > tuiles_inex_;
		if(!plateaux[i].est_valide(tuiles_inex_)){
			return false;
		}
		if(i<nb_pl_-1){
			QPair<QPair<int,int>,QPair<int,int> > dest_=plateaux[i].dest_lien_vers_plateau_suivant();
			QPair<QPair<int,int>,QPair<int,int> > bords_=plateaux[i+1].bords();
			QPair<int,int> coords_dr_=plateaux[i+1].val_coords_dresseur();
			QPair<int,int> dest_abs_=QPair<int,int>(dest_.first.first+dest_.second.first,dest_.first.second+dest_.second.second);
			if(dest_abs_==coords_dr_){
				return false;
			}
			if(dest_abs_.first<bords_.first.first){
				return false;
			}
			if(dest_abs_.second<bords_.first.second){
				return false;
			}
			if(dest_abs_.first>bords_.second.first){
				return false;
			}
			if(dest_abs_.second>bords_.second.second){
				return false;
			}
		}
	}
	QPair<QPair<int,int>,QPair<int,int> > dest_=QPair<QPair<int,int>,QPair<int,int> >(acces.coords_environnement(),acces.coords_tuile());
	QPair<QPair<int,int>,QPair<int,int> > bords_=plateaux[0].bords();
	QPair<int,int> coords_dr_=plateaux[0].val_coords_dresseur();
	QPair<int,int> dest_abs_=QPair<int,int>(dest_.first.first+dest_.second.first,dest_.first.second+dest_.second.second);
	if(dest_abs_==coords_dr_){
		return false;
	}
	if(dest_abs_.first<bords_.first.first){
		return false;
	}
	if(dest_abs_.second<bords_.first.second){
		return false;
	}
	if(dest_abs_.first>bords_.second.first){
		return false;
	}
	if(dest_abs_.second>bords_.second.second){
		return false;
	}
	QPair<QPair<int,int>,QPair<int,int> > orig_=plateaux[0].orig_lien_vers_plateau_suivant();
	QPair<int,int> orig_abs_=QPair<int,int>(orig_.first.first+orig_.second.first,orig_.first.second+orig_.second.second);
	if(orig_abs_==dest_abs_){
		return false;
	}
	/*QPair<int,int> acces_env_=acces.coords_environnement()
	QPair<int,int> acces_tuile_=acces.coords_tuile()
	QPair<int,int> acces_abs_=QPair<int,int>(acces_env_.first+acces_tuile_.first,acces_env_.second+acces_tuile_.second)
	if(acces_abs_==plateaux[0].val_coords_dresseur()){
		return false
	}*/
	//if(acces_abs_==
	//if(
	return valide_;
}

QString *Ligue::adr_nom_ligue(){
	return &nom_ligue;
}

Coordonnees *Ligue::adr_acces(){
	return &acces;
}

Coordonnees *Ligue::adr_origine(){
	return &origine;
}

PlateauLigue *Ligue::plateau(int _indice){
	return &plateaux[_indice];
}

int Ligue::nb_plateaux()const{
	return plateaux.size();
}

void Ligue::inserer_plateau(int _indice,const PlateauLigue& _plateau){
	plateaux.insert(_indice,_plateau);
}



void Ligue::supprimer_plateau_reindexer(int _indice){
	if(_indice>0){
		PlateauLigue *pl_suppr_=plateau(_indice);
		PlateauLigue *pl_2_=plateau(_indice-1);
		if(_indice<plateaux.size()-1){
			*pl_2_->adr_dest_lien_vers_plateau_suivant()=*pl_suppr_->adr_dest_lien_vers_plateau_suivant();
		}else{
			pl_2_->adr_dest_lien_vers_plateau_suivant()->first=QPair<int,int>(Tuile::_coords_invalide_,Tuile::_coords_invalide_);
			pl_2_->adr_dest_lien_vers_plateau_suivant()->second=QPair<int,int>(Tuile::_coords_invalide_,Tuile::_coords_invalide_);
		}
	}
	plateaux.removeAt(_indice);
}

/*void Ligue::supprimer_plateau(int _indice){
	if(_indice>0){
		PlateauLigue *pl_suppr_=plateau(_indice)
		PlateauLigue *pl_2_=plateau(_indice-1)
		//QPair<QPair<int,int>,QPair<int,int> > *dest_=pl_2_.adr_dest_lien_vers_plateau_suivant()
		//QPair<QPair<int,int>,QPair<int,int> > *dest_n_=pl_suppr_.adr_dest_lien_vers_plateau_suivant()
		if(plateaux.cles().contains(_indice-1)){
			*pl_2_->adr_dest_lien_vers_plateau_suivant()=*pl_suppr_->adr_dest_lien_vers_plateau_suivant()
		}else{
			pl_2_->adr_dest_lien_vers_plateau_suivant()->first.first=Tuile::_coords_invalide_
			pl_2_->adr_dest_lien_vers_plateau_suivant()->first.second=Tuile::_coords_invalide_
			pl_2_->adr_dest_lien_vers_plateau_suivant()->second.first=Tuile::_coords_invalide_
			pl_2_->adr_dest_lien_vers_plateau_suivant()->second.second=Tuile::_coords_invalide_
		}
	}
	plateaux.supprimer_cle_valeur(_indice)
}*/

bool Ligue::est_valide(){
	bool valide_=!plateaux.isEmpty();
	/*QList<QPair<int,int> > tuiles
	foreach(PlateauLigue p,plateaux){
		valide_&=p.est_valide(tuiles)
	}*/
	//TODO les coordonnées de l'origine et de l'accès sont valides
	return valide_;
}

QString Ligue::exporter(int _nb_tab_env)const{
	QString descr_;
	for(int i=0;i<_nb_tab_env;i++){
		descr_+="\t";
	}
	descr_+="<Lig>\n";
	int _nb_tab_env_att=_nb_tab_env+1;
	int nb_pl_=plateaux.size();
	for(int i=0;i<nb_pl_;i++){
		descr_+=plateaux[i].exporter(_nb_tab_env_att);
	}
	for(int i=0;i<_nb_tab_env_att;i++){
		descr_+="\t";
	}
	descr_+="<N>"+nom_ligue+"</N>\n";
	for(int i=0;i<_nb_tab_env_att;i++){
		descr_+="\t";
	}
	descr_+="<C>"+acces.formater()+"</C>\n";
	for(int i=0;i<_nb_tab_env_att;i++){
		descr_+="\t";
	}
	descr_+="<C>"+origine.formater()+"</C>\n";
	for(int i=0;i<_nb_tab_env;i++){
		descr_+="\t";
	}
	descr_+="</Lig>\n";
	return descr_;
}

bool operator==(const Ligue& a,const Ligue& b){
	return a.egal(b);
}

void Ligue::serialiser(Flux& _out)const{
	_out<<acces;
	_out<<origine;
	_out<<plateaux;
	_out<<nom_ligue;
	//_out<<plateau_en_cours
}

void Ligue::deserialiser(Flux& _in){
	_in>>acces;
	_in>>origine;
	_in>>plateaux;
	_in>>nom_ligue;
	//_in>>plateau_en_cours
}

Flux & operator <<(Flux& out,const Ligue& _Ligue){
	_Ligue.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Ligue& _Ligue){
	_Ligue.deserialiser(in);
	return in;
}



