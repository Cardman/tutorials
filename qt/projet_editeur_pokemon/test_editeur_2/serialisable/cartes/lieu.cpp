#include "serialisable/cartes/lieu.h"
#include "autre/utilitaire.h"
Lieu::Lieu(){
	;
}

bool Lieu::egal(const Lieu& _autre)const{
	bool egal_;
	egal_=nom==_autre.nom;
	egal_&=type==_autre.type;
	egal_&=plateaux==_autre.plateaux;
	egal_&=liens_vers_autres_lieux==_autre.liens_vers_autres_lieux;
	return egal_;
}

bool Lieu::est_valide()const{
	if(plateaux.total()==0){
		return false;
	}
	//bool valide_
	foreach(int i,plateaux.cles()){
		QList<QPair<int,int> > tuiles_inex_;
		if(!plateaux.valeur(i).est_valide(tuiles_inex_)){
			return false;
		}
		//liaisons_vers_autres_plateaux()
	}
	return true;
}

QString *Lieu::adr_nom(){
	return &nom;
}

QString *Lieu::adr_type(){
	return &type;
}

void Lieu::ajout_plateau(int _indice,const Plateau& _plateau){
	plateaux.ajouter_cle_valeur(_indice,_plateau);
}

void Lieu::suppression_plateau(int _indice){
	plateaux.supprimer_cle_valeur(_indice);
}

QList<int> Lieu::plateaux_c()const{
	return plateaux.cles();
}

Plateau *Lieu::plateau(int _indice){
	bool suppr_=false;
	return plateaux.valeur(_indice,suppr_);
}

void Lieu::aff_liens_vers_autres_lieux(){
	liens_vers_autres_lieux=liens_vers_autres_lieux_tmp;
}

void Lieu::aff_liens_vers_autres_lieux_tmp(){
	liens_vers_autres_lieux_tmp=liens_vers_autres_lieux;
}

Coordonnees *Lieu::destination_autre_lieu(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _origine,bool& _n_inst){
	return liens_vers_autres_lieux.valeur(_origine,_n_inst);
}

Coordonnees Lieu::destination_autre_lieu(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _origine){
	return liens_vers_autres_lieux.valeur(_origine);
}

void Lieu::ajouter_dest_autre_lieu(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _origine,const Coordonnees& _lien){
	liens_vers_autres_lieux.ajouter_cle_valeur(_origine,_lien);
}

void Lieu::supprimer_dest_autre_lieu(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _origine){
	liens_vers_autres_lieux.supprimer_cle_valeur(_origine);
}

QList<QPair<int,QPair<QPair<int,int>,QPair<int,int> > > > Lieu::liaisons_vers_autres_lieux()const{
	return liens_vers_autres_lieux.cles();
}

void Lieu::relier_plateaux_m_lieu(int _indice_l,int _indice,int _indice_2,const QPair<QPair<int,int>,QPair<int,int> >& _coords,const QPair<QPair<int,int>,QPair<int,int> >& _coords_2){
	Plateau *pl_1_=plateau(_indice);
	Plateau *pl_2_=plateau(_indice_2);
	//bool suppr_=false
	//QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > lien_1_
	//QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > lien_2_
	Coordonnees lien_1_;
	*lien_1_.adr_environnement()=_coords_2.first;
	*lien_1_.adr_tuile()=_coords_2.second;
	*lien_1_.adr_lieu_plateau()=QPair<int,int>(_indice_l,_indice_2);
	Coordonnees lien_2_;
	*lien_2_.adr_environnement()=_coords.first;
	*lien_2_.adr_tuile()=_coords.second;
	*lien_2_.adr_lieu_plateau()=QPair<int,int>(_indice_l,_indice);
	//lien_1_.first=_coords_2
	//lien_1_.second.first=_indice_l
	//lien_1_.second.second=_indice_2
	//lien_2_.first=_coords
	//lien_2_.second.first=_indice_l
	//lien_2_.second.second=_indice
	pl_1_->ajouter_dest_autre_plateau(_coords,lien_1_);
	pl_2_->ajouter_dest_autre_plateau(_coords_2,lien_2_);
}

void Lieu::delier_plateaux_m_lieu(int _indice,const QPair<QPair<int,int>,QPair<int,int> >& _coords){
	Plateau *pl_1_=plateau(_indice);
	bool suppr_=false;
	Coordonnees *lien_1_=pl_1_->destination_autre_plateau(_coords,suppr_);
	Plateau *pl_2_=plateau(lien_1_->plateau());
	pl_1_->supprimer_dest_autre_plateau(_coords);
	pl_2_->supprimer_dest_autre_plateau(lien_1_->coords_par_rap_plateau());
}

void Lieu::relier_plateaux_lieux_diff(int _indice_l,int _indice_l_2,int _indice,int _indice_2,const QPair<QPair<int,int>,QPair<int,int> >& _coords,const QPair<QPair<int,int>,QPair<int,int> >& _coords_2){
	Plateau *pl_1_=plateau(_indice);
	Plateau *pl_2_=plateau(_indice_2);
	//bool suppr_=false
	/*QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > lien_1_
	QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > lien_2_
	lien_1_.first=_coords_2
	lien_1_.second.first=_indice_l_2
	lien_1_.second.second=_indice_2
	lien_2_.first=_coords
	lien_2_.second.first=_indice_l
	lien_2_.second.second=_indice*/
	Coordonnees lien_1_;
	*lien_1_.adr_environnement()=_coords_2.first;
	*lien_1_.adr_tuile()=_coords_2.second;
	*lien_1_.adr_lieu_plateau()=QPair<int,int>(_indice_l_2,_indice_2);
	Coordonnees lien_2_;
	*lien_2_.adr_environnement()=_coords.first;
	*lien_2_.adr_tuile()=_coords.second;
	*lien_2_.adr_lieu_plateau()=QPair<int,int>(_indice_l,_indice);
	pl_1_->ajouter_dest_autre_plateau(_coords,lien_1_);
	pl_2_->ajouter_dest_autre_plateau(_coords_2,lien_2_);
}

void Lieu::delier_plateaux_lieux_diff(int _indice,const QPair<QPair<int,int>,QPair<int,int> >& _coords){
	Plateau *pl_1_=plateau(_indice);
	//bool suppr_=false
	//QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > *lien_1_=pl_1_->destination_autre_plateau(_coords,suppr_)
	//Plateau *pl_2_=&(plateaux[lien_1_->second.second])
	pl_1_->supprimer_dest_autre_plateau(_coords);
	//pl_2_->supprimer_dest_autre_plateau(lien_1_->first)
}

QList<QPair<QPair<int,int>,QPair<int,int> > > Lieu::futures_cles(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords,const Plateau& _autre_plateau,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords_2)const{
	QList<QPair<QPair<int,int>,QPair<int,int> > > futures_cles_;
	//QPair<int,int> dimensions_courant_=plateau(_coords.first)->dimensions()
	//QPair<int,int> dimensions_autre_=_autre_plateau.dimensions()
	Plateau pl_cour_=plateaux.valeur(_coords.first);
	QPair<QPair<int,int>,QPair<int,int> > bords_courant_=pl_cour_.bords();
	QPair<QPair<int,int>,QPair<int,int> > bords_autre_=_autre_plateau.bords();
	typedef QPair<int,int> Position;
	int nb_pts_commun_;
	Position plus_petit_coin_h_g_courant_=bords_courant_.first;
	Position plus_grand_coin_b_d_courant_=bords_courant_.second;
	Position plus_petit_coin_h_g_autre_=bords_autre_.first;
	Position plus_grand_coin_b_d_autre_=bords_autre_.second;
	if(_coords.second.first.first+_coords.second.second.first==plus_petit_coin_h_g_courant_.first){
		//gauche
		int distance_x_coin_h_g_=_coords.second.first.second+_coords.second.second.second-plus_petit_coin_h_g_courant_.second;
		int distance_x_coin_h_g_2_=_coords_2.second.first.second+_coords_2.second.second.second-plus_petit_coin_h_g_autre_.second;
		int min_distance_=Utilitaire::max_min<int>(distance_x_coin_h_g_,distance_x_coin_h_g_2_).second;
		/*if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			min_distance_=distance_x_coin_h_g_2_
		}else{
			min_distance_=distance_x_coin_h_g_
		}*/
		int distance_x_coin_h_d_=plus_grand_coin_b_d_courant_.second-(_coords.second.first.second+_coords.second.second.second);
		int distance_x_coin_h_d_2_=plus_grand_coin_b_d_autre_.second-(_coords_2.second.first.second+_coords_2.second.second.second);
		int min_distance_2_=Utilitaire::max_min<int>(distance_x_coin_h_d_,distance_x_coin_h_d_2_).second;
		/*if(distance_x_coin_h_d_>distance_x_coin_h_d_2_){
			min_distance_2_=distance_x_coin_h_d_2_
		}else{
			min_distance_2_=distance_x_coin_h_d_
		}*/
		nb_pts_commun_=min_distance_+min_distance_2_+1;
		QPair<QPair<int,int>,QPair<int,int> > intervalle_;
		intervalle_.first=plus_petit_coin_h_g_courant_;
		//intervalle_.first.second=0
		if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			//intervalle_.first=plus_petit_coin_h_g_courant_//QPair<int,int>(0,0)
		//}else{
			//intervalle_.first=QPair<int,int>(plus_petit_coin_h_g_courant_.first,distance_x_coin_h_g_-distance_x_coin_h_g_2_)
			intervalle_.first.second+=distance_x_coin_h_g_-distance_x_coin_h_g_2_;//+1
		}
		intervalle_.second=QPair<int,int>(1,nb_pts_commun_);
		QList<Position> coins_gauche_courant_=pl_cour_.coins_gauche();
		foreach(Position p,coins_gauche_courant_){
			if(p.first>plus_petit_coin_h_g_courant_.first){
				continue;
			}
			Environnement env_=pl_cour_.environnement(p);
			QPair<QPair<int,int>,QPair<int,int> > intersection_=Environnement::intersection(p,env_.dimensions(),intervalle_.first,intervalle_.second);
			int nb_cases_=intersection_.second.second-intersection_.first.second+1;
			for(int i=0;i<nb_cases_;i++){
				futures_cles_<<QPair<QPair<int,int>,QPair<int,int> >(p,QPair<int,int>(intersection_.first.first,intersection_.first.second+i));
			}
		}
	}else if(_coords.second.first.second+_coords.second.second.second==plus_petit_coin_h_g_courant_.second){
		//haut
		int distance_x_coin_h_g_=_coords.second.first.first+_coords.second.second.first-plus_petit_coin_h_g_courant_.first;
		int distance_x_coin_h_g_2_=_coords_2.second.first.first+_coords_2.second.second.first-plus_petit_coin_h_g_autre_.first;
		/*if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			min_distance_=distance_x_coin_h_g_2_
		}else{
			min_distance_=distance_x_coin_h_g_
		}*/
		int min_distance_=Utilitaire::max_min<int>(distance_x_coin_h_g_,distance_x_coin_h_g_2_).second;
		int distance_x_coin_h_d_=plus_grand_coin_b_d_courant_.first-(_coords.second.first.first+_coords.second.second.first);
		int distance_x_coin_h_d_2_=plus_grand_coin_b_d_autre_.first-(_coords_2.second.first.first+_coords_2.second.second.first);
		/*if(distance_x_coin_h_d_>distance_x_coin_h_d_2_){
			min_distance_2_=distance_x_coin_h_d_2_
		}else{
			min_distance_2_=distance_x_coin_h_d_
		}*/
		int min_distance_2_=Utilitaire::max_min<int>(distance_x_coin_h_d_,distance_x_coin_h_d_2_).second;
		nb_pts_commun_=min_distance_+min_distance_2_+1;
		QPair<QPair<int,int>,QPair<int,int> > intervalle_;
		intervalle_.first=plus_petit_coin_h_g_courant_;
		//intervalle_.first.first=0
		if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			//intervalle_.first=QPair<int,int>(0,0)
		//}else{
			intervalle_.first.first+=distance_x_coin_h_g_-distance_x_coin_h_g_2_;//+1
		}
		intervalle_.second=QPair<int,int>(nb_pts_commun_,1);
		QList<Position> coins_gauche_courant_=pl_cour_.coins_gauche();
		foreach(Position p,coins_gauche_courant_){
			//if(p.first>plus_petit_coin_h_g_courant_.second){
			if(p.second>plus_petit_coin_h_g_courant_.second){
				continue;
			}
			Environnement env_=pl_cour_.environnement(p);
			QPair<QPair<int,int>,QPair<int,int> > intersection_=Environnement::intersection(p,env_.dimensions(),intervalle_.first,intervalle_.second);
			int nb_cases_=intersection_.second.first-intersection_.first.first+1;
			for(int i=0;i<nb_cases_;i++){
				futures_cles_<<QPair<QPair<int,int>,QPair<int,int> >(p,QPair<int,int>(intersection_.first.first+i,intersection_.first.second));
			}
		}
	//}else if(_coords.second.first.first+_coords.second.second.first+1==dimensions_courant_.first){
	}else if(_coords.second.first.first+_coords.second.second.first==plus_grand_coin_b_d_courant_.first){
	//plus_grand_coin_b_d_courant_
		//droite
		//int min_distance_
		int distance_x_coin_h_g_=_coords.second.first.second+_coords.second.second.second-plus_petit_coin_h_g_courant_.second;
		int distance_x_coin_h_g_2_=_coords_2.second.first.second+_coords_2.second.second.second-plus_petit_coin_h_g_autre_.second;
		/*if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			min_distance_=distance_x_coin_h_g_2_
		}else{
			min_distance_=distance_x_coin_h_g_
		}*/
		int min_distance_=Utilitaire::max_min<int>(distance_x_coin_h_g_,distance_x_coin_h_g_2_).second;
		//int min_distance_2_
		int distance_x_coin_h_d_=plus_grand_coin_b_d_courant_.second-(_coords.second.first.second+_coords.second.second.second);
		int distance_x_coin_h_d_2_=plus_grand_coin_b_d_autre_.second-(_coords_2.second.first.second+_coords_2.second.second.second);
		/*if(distance_x_coin_h_d_>distance_x_coin_h_d_2_){
			min_distance_2_=distance_x_coin_h_d_2_
		}else{
			min_distance_2_=distance_x_coin_h_d_
		}*/
		int min_distance_2_=Utilitaire::max_min<int>(distance_x_coin_h_d_,distance_x_coin_h_d_2_).second;
		nb_pts_commun_=min_distance_+min_distance_2_+1;
		QPair<QPair<int,int>,QPair<int,int> > intervalle_;
		intervalle_.first=plus_grand_coin_b_d_courant_;
		intervalle_.first.second=plus_petit_coin_h_g_courant_.second;
		if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			//intervalle_.first=QPair<int,int>(_coords.second.second.first+_coords.second.first.first,distance_x_coin_h_g_-distance_x_coin_h_g_2_)
			intervalle_.first.second+=distance_x_coin_h_g_-distance_x_coin_h_g_2_;//+1
		//}else{
			//intervalle_.first=QPair<int,int>(_coords.second.second.first+_coords.second.first.first,0)
		}
		intervalle_.second=QPair<int,int>(1,nb_pts_commun_);
		QList<Position> coins_gauche_courant_=pl_cour_.coins_gauche();
		foreach(Position p,coins_gauche_courant_){
			Environnement env_=pl_cour_.environnement(p);
			QPair<int,int> dims_=env_.dimensions();
			if(p.first+dims_.first<=plus_grand_coin_b_d_courant_.first){//dimensions_courant_.first){
				continue;
			}
			QPair<QPair<int,int>,QPair<int,int> > intersection_=Environnement::intersection(p,dims_,intervalle_.first,intervalle_.second);
			int nb_cases_=intersection_.second.second-intersection_.first.second+1;
			for(int i=0;i<nb_cases_;i++){
				futures_cles_<<QPair<QPair<int,int>,QPair<int,int> >(p,QPair<int,int>(intersection_.first.first,intersection_.first.second+i));
			}
		}
	}else{
		//bas
		//int min_distance_
		int distance_x_coin_h_g_=_coords.second.first.first+_coords.second.second.first-plus_petit_coin_h_g_courant_.first;
		int distance_x_coin_h_g_2_=_coords_2.second.first.first+_coords_2.second.second.first-plus_petit_coin_h_g_autre_.first;
		/*if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			min_distance_=distance_x_coin_h_g_2_
		}else{
			min_distance_=distance_x_coin_h_g_
		}*/
		int min_distance_=Utilitaire::max_min<int>(distance_x_coin_h_g_,distance_x_coin_h_g_2_).second;
		//int min_distance_2_
		int distance_x_coin_h_d_=plus_grand_coin_b_d_courant_.first-(_coords.second.first.first+_coords.second.second.first);
		int distance_x_coin_h_d_2_=plus_grand_coin_b_d_autre_.first-(_coords_2.second.first.first+_coords_2.second.second.first);
		/*if(distance_x_coin_h_d_>distance_x_coin_h_d_2_){
			min_distance_2_=distance_x_coin_h_d_2_
		}else{
			min_distance_2_=distance_x_coin_h_d_
		}*/
		int min_distance_2_=Utilitaire::max_min<int>(distance_x_coin_h_d_,distance_x_coin_h_d_2_).second;
		nb_pts_commun_=min_distance_+min_distance_2_+1;
		QPair<QPair<int,int>,QPair<int,int> > intervalle_;
		intervalle_.first=plus_grand_coin_b_d_courant_;
		intervalle_.first.first=plus_petit_coin_h_g_courant_.first;
		if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			intervalle_.first.first+=distance_x_coin_h_g_-distance_x_coin_h_g_2_;//+1
			//intervalle_.first=QPair<int,int>(distance_x_coin_h_g_-distance_x_coin_h_g_2_,_coords.second.first.second+_coords.second.second.second)
		//}else{
			//intervalle_.first=QPair<int,int>(0,_coords.second.first.second+_coords.second.second.second)
		}
		intervalle_.second=QPair<int,int>(nb_pts_commun_,1);
		QList<Position> coins_gauche_courant_=pl_cour_.coins_gauche();
		foreach(Position p,coins_gauche_courant_){
			Environnement env_=pl_cour_.environnement(p);
			if(p.second+env_.dimensions().second<=plus_grand_coin_b_d_courant_.second){
			//if(p.first>0){
				continue;
			}
			QPair<QPair<int,int>,QPair<int,int> > intersection_=Environnement::intersection(p,env_.dimensions(),intervalle_.first,intervalle_.second);
			int nb_cases_=intersection_.second.first-intersection_.first.first+1;
			for(int i=0;i<nb_cases_;i++){
				futures_cles_<<QPair<QPair<int,int>,QPair<int,int> >(p,QPair<int,int>(intersection_.first.first+i,intersection_.first.second));
			}
		}
	}
	return futures_cles_;
}

bool Lieu::peuvent_etre_lie_avec(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords,const Plateau& _autre_plateau,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords_2,QList<QPair<QPair<int,int>,QPair<int,int> > >& _futurs_cles)const{
	//QPair<int,int> dimensions_courant_=plateaux[_coords.first].dimensions()
	//QPair<int,int> dimensions_autre_=_autre_plateau.dimensions()
	QPair<QPair<int,int>,QPair<int,int> > bords_courant_=plateaux.valeur(_coords.first).bords();
	QPair<int,int> coin_gauche_cour_=bords_courant_.first;
	QPair<int,int> coin_droite_cour_=bords_courant_.second;
	QPair<QPair<int,int>,QPair<int,int> > bords_autre_=_autre_plateau.bords();
	QPair<int,int> coin_gauche_autre_=bords_autre_.first;
	QPair<int,int> coin_droite_autre_=bords_autre_.second;
	bool nec_1_=_coords.second.first.first+_coords.second.second.first==coin_gauche_cour_.first&&_coords_2.second.first.first+_coords_2.second.second.first==coin_droite_autre_.first;
	nec_1_|=_coords.second.first.second+_coords.second.second.second==coin_gauche_cour_.second&&_coords_2.second.first.second+_coords_2.second.second.second==coin_droite_autre_.second;
	nec_1_|=_coords.second.first.first+_coords.second.second.first==coin_droite_cour_.first&&_coords_2.second.first.first+_coords_2.second.second.first==coin_gauche_autre_.first;
	nec_1_|=_coords.second.first.second+_coords.second.second.second==coin_droite_cour_.second&&_coords_2.second.first.second+_coords_2.second.second.second==coin_gauche_autre_.second;
	if(!nec_1_){
		return false;
	}
	QList<QPair<QPair<int,int>,QPair<int,int> > > futures_cles_=futures_cles(_coords,_autre_plateau,_coords_2);
	_futurs_cles=futures_cles_;
	if(liens_vers_autres_lieux_tmp.total()==0){
		return true;
	}
	QList<QPair<int,QPair<QPair<int,int>,QPair<int,int> > > > cles_=liens_vers_autres_lieux_tmp.cles();
	QList<QPair<int,QPair<QPair<int,int>,QPair<int,int> > > > futures_cles_2_;
	int nb_cles_=futures_cles_.size();
	for(int i=0;i<nb_cles_;i++){
		QPair<int,QPair<QPair<int,int>,QPair<int,int> > > valeur_;
		valeur_.first=_coords.first;
		valeur_.second=futures_cles_[i];
		futures_cles_2_<<valeur_;
	}
	for(int i=0;i<nb_cles_;i++){
		if(cles_.contains(futures_cles_2_[i])){
			return false;
		}
	}
	return true;
	//return futures_cles_2_.toSet().insersect(cles_.toSet()).isEmpty()
}

void Lieu::relier_avec_autre_lieu(int _indice_l_2,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords,const Plateau& _autre_plateau,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords_2,const QList<QPair<QPair<int,int>,QPair<int,int> > >& _futurs_cles){
	//QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > *
	typedef QPair<int,int> Position;
	//Plateau *pl_1_=&(plateaux[_coords.first])//vite une copie du plateau
	//Plateau *pl_2_=&(plateaux[_coords_2.first])
	//QPair<int,int> dimensions_courant_=pl_1_->dimensions()
	//QPair<int,int> dimensions_autre_=_autre_plateau.dimensions()
	//Position plus_petit_coin_h_g_=QPair<int,int>(0,0)
	int nb_pts_commun_;
	int nb_cles_valeurs_;
	QList<QPair<QPair<int,int>,QPair<int,int> > > futures_cles_=_futurs_cles;
	QList<QPair<QPair<int,int>,QPair<int,int> > > futures_valeurs_;
	QPair<QPair<int,int>,QPair<int,int> > bords_courant_=plateau(_coords.first)->bords();
	QPair<QPair<int,int>,QPair<int,int> > bords_autre_=_autre_plateau.bords();
	Position plus_petit_coin_h_g_courant_=bords_courant_.first;
	Position plus_grand_coin_b_d_courant_=bords_courant_.second;
	Position plus_petit_coin_h_g_autre_=bords_autre_.first;
	Position plus_grand_coin_b_d_autre_=bords_autre_.second;
	if(_coords.second.first.first+_coords.second.second.first==plus_petit_coin_h_g_courant_.first){
		//gauche
		//int min_distance_
		int distance_x_coin_h_g_=_coords.second.first.second+_coords.second.second.second-plus_petit_coin_h_g_courant_.second;
		int distance_x_coin_h_g_2_=_coords_2.second.first.second+_coords_2.second.second.second-plus_petit_coin_h_g_autre_.second;
		/*if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			min_distance_=distance_x_coin_h_g_2_
		}else{
			min_distance_=distance_x_coin_h_g_
		}*/
		int min_distance_=Utilitaire::max_min<int>(distance_x_coin_h_g_,distance_x_coin_h_g_2_).second;
		//int min_distance_2_
		int distance_x_coin_h_d_=plus_grand_coin_b_d_courant_.second-(_coords.second.first.second+_coords.second.second.second);
		int distance_x_coin_h_d_2_=plus_grand_coin_b_d_autre_.second-(_coords_2.second.first.second+_coords_2.second.second.second);
		int min_distance_2_=Utilitaire::max_min<int>(distance_x_coin_h_d_,distance_x_coin_h_d_2_).second;
		/*if(distance_x_coin_h_d_>distance_x_coin_h_d_2_){
			min_distance_2_=distance_x_coin_h_d_2_
		}else{
			min_distance_2_=distance_x_coin_h_d_
		}*/
		nb_pts_commun_=min_distance_+min_distance_2_+1;
		QList<Position> coins_gauche_autre_=_autre_plateau.coins_gauche();
		QPair<QPair<int,int>,QPair<int,int> > intervalle_2_;
		intervalle_2_.first=plus_grand_coin_b_d_autre_;
		intervalle_2_.first.second=plus_petit_coin_h_g_autre_.second;
		//intervalle_2_.first.second=0
		if(distance_x_coin_h_g_<distance_x_coin_h_g_2_){
			//intervalle_2_.first=QPair<int,int>(_coords_2.second.second.first+_coords_2.second.first.first,distance_x_coin_h_g_2_-distance_x_coin_h_g_)
			intervalle_2_.first.second+=distance_x_coin_h_g_2_-distance_x_coin_h_g_;//+1
		//}else{
			//intervalle_2_.first=QPair<int,int>(_coords_2.second.second.first+_coords_2.second.first.first,0)
		}
		intervalle_2_.second=QPair<int,int>(1,nb_pts_commun_);
		foreach(Position p,coins_gauche_autre_){
			Environnement env_=_autre_plateau.environnement(p);
			QPair<int,int> dims_=env_.dimensions();
			if(p.first+dims_.first<=plus_grand_coin_b_d_autre_.first){
				continue;
			}
			QPair<QPair<int,int>,QPair<int,int> > intersection_=Environnement::intersection(p,dims_,intervalle_2_.first,intervalle_2_.second);
			int nb_cases_=intersection_.second.second-intersection_.first.second+1;
			for(int i=0;i<nb_cases_;i++){
				futures_valeurs_<<QPair<QPair<int,int>,QPair<int,int> >(p,QPair<int,int>(intersection_.first.first,intersection_.first.second+i));
			}
		}
	}else if(_coords.second.first.second+_coords.second.second.second==plus_petit_coin_h_g_courant_.second){
		//haut
		//int min_distance_
		int distance_x_coin_h_g_=_coords.second.first.first+_coords.second.second.first-plus_petit_coin_h_g_courant_.first;
		int distance_x_coin_h_g_2_=_coords_2.second.first.first+_coords_2.second.second.first-plus_petit_coin_h_g_autre_.first;
		/*if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			min_distance_=distance_x_coin_h_g_2_
		}else{
			min_distance_=distance_x_coin_h_g_
		}*/
		int min_distance_=Utilitaire::max_min<int>(distance_x_coin_h_g_,distance_x_coin_h_g_2_).second;
		int distance_x_coin_h_d_=plus_grand_coin_b_d_courant_.first-(_coords.second.first.first+_coords.second.second.first);
		int distance_x_coin_h_d_2_=plus_grand_coin_b_d_autre_.first-(_coords_2.second.first.first+_coords_2.second.second.first);
		int min_distance_2_=Utilitaire::max_min<int>(distance_x_coin_h_d_,distance_x_coin_h_d_2_).second;
		/*if(distance_x_coin_h_d_>distance_x_coin_h_d_2_){
			min_distance_2_=distance_x_coin_h_d_2_
		}else{
			min_distance_2_=distance_x_coin_h_d_
		}*/
		nb_pts_commun_=min_distance_+min_distance_2_+1;
		QList<Position> coins_gauche_autre_=_autre_plateau.coins_gauche();
		QPair<QPair<int,int>,QPair<int,int> > intervalle_2_;
		intervalle_2_.first=plus_grand_coin_b_d_autre_;
		intervalle_2_.first.first=plus_petit_coin_h_g_autre_.first;
		//intervalle_2_.first.first=0
		if(distance_x_coin_h_g_<distance_x_coin_h_g_2_){
			intervalle_2_.first.first+=distance_x_coin_h_g_2_-distance_x_coin_h_g_;//+1
			//intervalle_2_.first=QPair<int,int>(distance_x_coin_h_g_2_-distance_x_coin_h_g_,_coords_2.second.first.second+_coords_2.second.second.second)
		//}else{
			//intervalle_2_.first=QPair<int,int>(0,_coords_2.second.first.second+_coords_2.second.second.second)
		}
		intervalle_2_.second=QPair<int,int>(nb_pts_commun_,1);
		foreach(Position p,coins_gauche_autre_){
			Environnement env_=_autre_plateau.environnement(p);
			QPair<int,int> dims_=env_.dimensions();
			if(p.second+dims_.second<=plus_grand_coin_b_d_autre_.second){
				continue;
			}
			QPair<QPair<int,int>,QPair<int,int> > intersection_=Environnement::intersection(p,dims_,intervalle_2_.first,intervalle_2_.second);
			int nb_cases_=intersection_.second.first-intersection_.first.first+1;
			for(int i=0;i<nb_cases_;i++){
				futures_valeurs_<<QPair<QPair<int,int>,QPair<int,int> >(p,QPair<int,int>(intersection_.first.first+i,intersection_.first.second));
			}
		}
	}else if(_coords.second.first.first+_coords.second.second.first==plus_grand_coin_b_d_courant_.first){
		//droite
		//int min_distance_
		int distance_x_coin_h_g_=_coords.second.first.second+_coords.second.second.second-plus_petit_coin_h_g_courant_.second;
		int distance_x_coin_h_g_2_=_coords_2.second.first.second+_coords_2.second.second.second-plus_petit_coin_h_g_autre_.second;
		/*if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			min_distance_=distance_x_coin_h_g_2_
		}else{
			min_distance_=distance_x_coin_h_g_
		}*/
		int min_distance_=Utilitaire::max_min<int>(distance_x_coin_h_g_,distance_x_coin_h_g_2_).second;
		//int min_distance_2_
		int distance_x_coin_h_d_=plus_grand_coin_b_d_courant_.second-(_coords.second.first.second+_coords.second.second.second);
		int distance_x_coin_h_d_2_=plus_grand_coin_b_d_autre_.second-(_coords_2.second.first.second+_coords_2.second.second.second);
		int min_distance_2_=Utilitaire::max_min<int>(distance_x_coin_h_d_,distance_x_coin_h_d_2_).second;
		/*if(distance_x_coin_h_d_>distance_x_coin_h_d_2_){
			min_distance_2_=distance_x_coin_h_d_2_
		}else{
			min_distance_2_=distance_x_coin_h_d_
		}*/
		nb_pts_commun_=min_distance_+min_distance_2_+1;
		QList<Position> coins_gauche_autre_=_autre_plateau.coins_gauche();
		QPair<QPair<int,int>,QPair<int,int> > intervalle_2_;
		intervalle_2_.first=plus_petit_coin_h_g_autre_;
		if(distance_x_coin_h_g_<distance_x_coin_h_g_2_){//distance_x_coin_h_g_>distance_x_coin_h_g_2_
			//intervalle_2_.first=QPair<int,int>(0,distance_x_coin_h_g_2_-distance_x_coin_h_g_)
			intervalle_2_.first.second+=distance_x_coin_h_g_2_-distance_x_coin_h_g_;//+1
		//}else{
			//intervalle_2_.first=QPair<int,int>(0,0)
		}
		intervalle_2_.second=QPair<int,int>(1,nb_pts_commun_);
		foreach(Position p,coins_gauche_autre_){
			if(p.first>plus_petit_coin_h_g_autre_.first){
				continue;
			}
			Environnement env_=_autre_plateau.environnement(p);
			QPair<int,int> dims_=env_.dimensions();
			QPair<QPair<int,int>,QPair<int,int> > intersection_=Environnement::intersection(p,dims_,intervalle_2_.first,intervalle_2_.second);
			int nb_cases_=intersection_.second.second-intersection_.first.second+1;
			for(int i=0;i<nb_cases_;i++){
				futures_valeurs_<<QPair<QPair<int,int>,QPair<int,int> >(p,QPair<int,int>(intersection_.first.first,intersection_.first.second+i));
			}
		}
	}else{
		//bas
		//int min_distance_
		int distance_x_coin_h_g_=_coords.second.first.first+_coords.second.second.first-plus_petit_coin_h_g_courant_.first;
		int distance_x_coin_h_g_2_=_coords_2.second.first.first+_coords_2.second.second.first-plus_petit_coin_h_g_autre_.first;
		int min_distance_=Utilitaire::max_min<int>(distance_x_coin_h_g_,distance_x_coin_h_g_2_).second;
		/*if(distance_x_coin_h_g_>distance_x_coin_h_g_2_){
			min_distance_=distance_x_coin_h_g_2_
		}else{
			min_distance_=distance_x_coin_h_g_
		}*/
		//int min_distance_2_
		int distance_x_coin_h_d_=plus_grand_coin_b_d_courant_.first-(_coords.second.first.first+_coords.second.second.first);
		int distance_x_coin_h_d_2_=plus_grand_coin_b_d_autre_.first-(_coords_2.second.first.first+_coords_2.second.second.first);
		int min_distance_2_=Utilitaire::max_min<int>(distance_x_coin_h_d_,distance_x_coin_h_d_2_).second;
		/*if(distance_x_coin_h_d_>distance_x_coin_h_d_2_){
			min_distance_2_=distance_x_coin_h_d_2_
		}else{
			min_distance_2_=distance_x_coin_h_d_
		}*/
		nb_pts_commun_=min_distance_+min_distance_2_+1;
		QList<Position> coins_gauche_autre_=_autre_plateau.coins_gauche();
		QPair<QPair<int,int>,QPair<int,int> > intervalle_2_;
		intervalle_2_.first=plus_petit_coin_h_g_autre_;
		/*if(distance_x_coin_h_g_>=distance_x_coin_h_g_2_){
			intervalle_2_.first=QPair<int,int>(0,0)
		}else{
			intervalle_2_.first=QPair<int,int>(distance_x_coin_h_g_2_-distance_x_coin_h_g_,0)
		}*/
		//intervalle_2_.first.first=plus_petit_coin_h_g_autre_.first
		if(distance_x_coin_h_g_<distance_x_coin_h_g_2_){
			//intervalle_2_.first=QPair<int,int>(0,0)
			intervalle_2_.first.first+=distance_x_coin_h_g_2_-distance_x_coin_h_g_;//+1
		//}else{
			//intervalle_2_.first=QPair<int,int>(distance_x_coin_h_g_2_-distance_x_coin_h_g_,0)
		}
		intervalle_2_.second=QPair<int,int>(nb_pts_commun_,1);
		foreach(Position p,coins_gauche_autre_){
			Environnement env_=_autre_plateau.environnement(p);
			QPair<int,int> dims_=env_.dimensions();
			if(p.second>plus_petit_coin_h_g_autre_.second){
			//if(p.second+dims_.second<dimensions_autre_.second){
				continue;
			}
			QPair<QPair<int,int>,QPair<int,int> > intersection_=Environnement::intersection(p,dims_,intervalle_2_.first,intervalle_2_.second);
			int nb_cases_=intersection_.second.first-intersection_.first.first+1;
			for(int i=0;i<nb_cases_;i++){
				futures_valeurs_<<QPair<QPair<int,int>,QPair<int,int> >(p,QPair<int,int>(intersection_.first.first+i,intersection_.first.second));
			}
		}
	}
	Utilitaire::trier<QPair<QPair<int,int>,QPair<int,int> > >(futures_cles_,true);
	Utilitaire::trier<QPair<QPair<int,int>,QPair<int,int> > >(futures_valeurs_,true);
	int nb_cles_=futures_cles_.size();
	/*for(int i=0;i<nb_cles_;i++){
		for(int j=i+1;j<nb_cles_;j++){
			if(futures_cles_[i]<futures_cles_[j]){
				futures_cles_.swap(i,j)
			}
		}
	}*/
	int nb_valeurs_=futures_valeurs_.size();
	/*for(int i=0;i<nb_valeurs_;i++){
		for(int j=i+1;j<nb_valeurs_;j++){
			if(futures_valeurs_[i]<futures_valeurs_[j]){
				futures_valeurs_.swap(i,j)
			}
		}
	}*/
	if(nb_valeurs_<nb_cles_){
		nb_cles_valeurs_=nb_valeurs_;
	}else{
		nb_cles_valeurs_=nb_cles_;
	}
	for(int i=0;i<nb_cles_valeurs_;i++){
		QPair<int,QPair<QPair<int,int>,QPair<int,int> > > cle_;
		cle_.first=_coords.first;
		cle_.second=futures_cles_[i];
		/*QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > valeur_
		valeur_.first=futures_valeurs_[i]
		valeur_.second=QPair<int,int>(_indice_l_2,_coords_2.first)*/
		Coordonnees valeur_;
		*valeur_.adr_environnement()=futures_valeurs_[i].first;
		*valeur_.adr_tuile()=futures_valeurs_[i].second;
		*valeur_.adr_lieu_plateau()=QPair<int,int>(_indice_l_2,_coords_2.first);
		liens_vers_autres_lieux_tmp.ajouter_cle_valeur(cle_,valeur_);
	}
	//liens_vers_autres_lieux
}

	/**Algo reliant deux plateaux du mme lieu  l'aide des coordonnes d'environnement et de tuiles
	TODO
	@param _indice indice du premier plateau  lier avec un autre plateau
	@param _coords coordonnes du plateau  delier avec un autre plateau*/
void Lieu::delier_lieux(int _indice_l){
	int i_=0;
	bool suppr_=false;
	QList<QPair<int,QPair<QPair<int,int>,QPair<int,int> > > > cles_=liens_vers_autres_lieux_tmp.cles();
	while(i_<liens_vers_autres_lieux_tmp.total()){
		Coordonnees *valeur_=liens_vers_autres_lieux_tmp.valeur(cles_[i_],suppr_);
		if(valeur_->lieu()==_indice_l){
			liens_vers_autres_lieux_tmp.supprimer_cle_valeur(cles_[i_]);
		}else{
			i_++;
		}
	}
}

QString Lieu::exporter(int _nb_tab_env)const{
	QString descr_;
	for(int i=0;i<_nb_tab_env;i++){
		descr_+="\t";
	}
	descr_+="<Lieu>\n";
	int nb_tab_env_attr_=_nb_tab_env+1;
	for(int i=0;i<nb_tab_env_attr_;i++){
		descr_+="\t";
	}
	descr_+="<N>"+nom+"</N>\n";
	for(int i=0;i<nb_tab_env_attr_;i++){
		descr_+="\t";
	}
	descr_+="<T>"+type+"</T>\n";
	foreach(int c,plateaux.cles()){
		for(int i=0;i<nb_tab_env_attr_;i++){
			descr_+="\t";
		}
		descr_+=QString::number(c)+":\n";
		descr_+=plateaux.valeur(c).exporter(nb_tab_env_attr_);
	}
	/*for(int i=0;i<_nb_tab_env;i++){
		descr_+="\t"
	}*/
	typedef QPair<int,QPair<QPair<int,int>,QPair<int,int> > > Origine;
	//typedef QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > Arrivee
	foreach(Origine o,liens_vers_autres_lieux.cles()){
		Coordonnees arr_2_=liens_vers_autres_lieux.valeur(o);
		for(int i=0;i<nb_tab_env_attr_;i++){
			descr_+="\t";
		}
		QPair<QPair<int,int>,QPair<int,int> > p_=o.second;
		//QPair<QPair<int,int>,QPair<int,int> > arr_=arr_2_.first
		descr_+="<L>"+QString::number(o.first)+";";
		descr_+=QString::number(p_.first.first)+","+QString::number(p_.first.second)+",";
		descr_+=QString::number(p_.second.first)+","+QString::number(p_.second.second)+"_";
		descr_+=arr_2_.formater()+"</L>\n";
		/*descr_+=QString::number(arr_.first.first)+","+QString::number(arr_.first.second)+","
		descr_+=QString::number(arr_.second.first)+","+QString::number(arr_.second.second)+";"
		descr_+=QString::number(arr_2_.second.first)+","+QString::number(arr_2_.second.second)+"</L>\n"*/
	}
	descr_+="</Lieu>\n";
	return descr_;
}

bool operator==(const Lieu& a,const Lieu& b){
	return a.egal(b);
}

void Lieu::serialiser(Flux& _out)const{
	_out<<nom;
	_out<<type;
	_out<<plateaux;
	_out<<liens_vers_autres_lieux;
}

void Lieu::deserialiser(Flux& _in){
	_in>>nom;
	_in>>type;
	_in>>plateaux;
	_in>>liens_vers_autres_lieux;
}

Flux & operator <<(Flux& out,const Lieu& _Lieu){
	_Lieu.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Lieu& _Lieu){
	_Lieu.deserialiser(in);
	return in;
}



