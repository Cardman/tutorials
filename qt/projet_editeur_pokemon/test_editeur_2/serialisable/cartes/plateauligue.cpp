#include "serialisable/cartes/plateauligue.h"
PlateauLigue::PlateauLigue(){
	int coords_inval_=Tuile::_coords_invalide_;
	lien_vers_plateau_suivant.first.first.first=coords_inval_;
	lien_vers_plateau_suivant.first.first.second=coords_inval_;
	lien_vers_plateau_suivant.first.second.first=coords_inval_;
	lien_vers_plateau_suivant.first.second.second=coords_inval_;
	lien_vers_plateau_suivant.second.first.first=coords_inval_;
	lien_vers_plateau_suivant.second.first.second=coords_inval_;
	lien_vers_plateau_suivant.second.second.first=coords_inval_;
	lien_vers_plateau_suivant.second.second.second=coords_inval_;
}

void PlateauLigue::supprimer_lien_vers_plateau_suivant(){
	int coords_inval_=Tuile::_coords_invalide_;
	lien_vers_plateau_suivant.first.first.first=coords_inval_;
	lien_vers_plateau_suivant.first.first.second=coords_inval_;
	lien_vers_plateau_suivant.first.second.first=coords_inval_;
	lien_vers_plateau_suivant.first.second.second=coords_inval_;
	lien_vers_plateau_suivant.second.first.first=coords_inval_;
	lien_vers_plateau_suivant.second.first.second=coords_inval_;
	lien_vers_plateau_suivant.second.second.first=coords_inval_;
	lien_vers_plateau_suivant.second.second.second=coords_inval_;
}

bool PlateauLigue::egal(const PlateauLigue& _autre)const{
	bool egal_;
	egal_=environnements==_autre.environnements;
	egal_&=coords_dresseur==_autre.coords_dresseur;
	egal_&=dresseur_ligue==_autre.dresseur_ligue;
	egal_&=lien_vers_plateau_suivant==_autre.lien_vers_plateau_suivant;
	return egal_;
}

QPair<int,int> PlateauLigue::val_coords_dresseur()const{
	return coords_dresseur;
}

bool PlateauLigue::est_valide(QList<QPair<int,int> >& _tuiles_inexistantes)const{
	bool valide_=dresseur_ligue.est_valide();
	QPair<QPair<int,int>,QPair<int,int> > bords_=bords();
	valide_&=coords_dresseur.first>=bords_.first.first&&coords_dresseur.first<=bords_.second.first;
	valide_&=coords_dresseur.second>=bords_.first.second&&coords_dresseur.second<=bords_.second.second;
	typedef QPair<int,int> Position;
	typedef QPair<int,int> Dimension;
	HashMap<Position,bool> tuiles_exist_;
	Position plus_petit_coin_h_g_=QPair<int,int>(0,0);
	Position plus_grand_coin_b_d_g_=QPair<int,int>(0,0);
	QList<Position> cles_=environnements.cles();
	if(cles_.isEmpty()){
		_tuiles_inexistantes<<QPair<int,int>(Tuile::_coords_invalide_,Tuile::_coords_invalide_);
		return false;
	}
	foreach(Position p,cles_){
		plus_petit_coin_h_g_=p;
		plus_grand_coin_b_d_g_=p;
	}
	foreach(Position p,cles_){
		if(p.first<plus_petit_coin_h_g_.first){
			plus_petit_coin_h_g_.first=p.first;
		}
		if(p.second<plus_petit_coin_h_g_.second){
			plus_petit_coin_h_g_.second=p.second;
		}
		EnvironnementLigue env_cour_=environnements.valeur(p);
		Dimension dims_cour_=env_cour_.dimensions();
		int tmp_=p.first+dims_cour_.first-1;
		if(tmp_>plus_grand_coin_b_d_g_.first){
			plus_grand_coin_b_d_g_.first=tmp_;
		}
		tmp_=p.second+dims_cour_.second-1;
		if(tmp_>plus_grand_coin_b_d_g_.second){
			plus_grand_coin_b_d_g_.second=tmp_;
		}
	}
	Dimension dims_pl_=Dimension(plus_grand_coin_b_d_g_.first-plus_petit_coin_h_g_.first+1,plus_grand_coin_b_d_g_.second-plus_petit_coin_h_g_.second+1);
	int largeur_=dims_pl_.first;
	int hauteur_=dims_pl_.second;
	for(int i=0;i<largeur_;i++){
		for(int j=0;j<hauteur_;j++){
			//tuiles_exist_.ajouter_cle_valeur(Position(i,j),false)
			tuiles_exist_.ajouter_cle_valeur(Position(i+plus_petit_coin_h_g_.first,j+plus_petit_coin_h_g_.second),false);
		}
	}
	foreach(Position p,cles_){
		EnvironnementLigue env_cour_=environnements.valeur(p);
		Dimension dims_cour_=env_cour_.dimensions();
		largeur_=dims_cour_.first;
		hauteur_=dims_cour_.second;
		int ind_dep_x_=p.first;
		int ind_fin_x_=ind_dep_x_+largeur_;
		int ind_dep_y_=p.second;
		int ind_fin_y_=ind_dep_y_+hauteur_;
		for(int i=ind_dep_x_;i<ind_fin_x_;i++){
			for(int j=ind_dep_y_;j<ind_fin_y_;j++){
				tuiles_exist_.ajouter_cle_valeur(Position(i,j),true);
			}
		}
	}
	cles_=tuiles_exist_.cles();
	foreach(Position p,cles_){
		if(!tuiles_exist_.valeur(p)){
			_tuiles_inexistantes<<p;
		}
	}
	//lien_vers_plateau_suivant.first
	QPair<Position,Position> lien_=lien_vers_plateau_suivant.first;
	Position lien_or_=Position(lien_.first.first+lien_.second.first,lien_.first.second+lien_.second.second);
	if(lien_or_==coords_dresseur){
		return false;
	}
	valide_&=lien_or_.first>=bords_.first.first&&lien_or_.first<=bords_.second.first;
	valide_&=lien_or_.second>=bords_.first.second&&lien_or_.second<=bords_.second.second;
	return valide_&&_tuiles_inexistantes.isEmpty();
}

DresseurLigue *PlateauLigue::adr_dresseur_ligue(){
	return &dresseur_ligue;
}

QPair<int,int> *PlateauLigue::adr_coords_dresseur(){
	return &coords_dresseur;
}

void PlateauLigue::supprimer_environnement(const QPair<int,int>& _id){
	environnements.supprimer_cle_valeur(_id);
}

void PlateauLigue::decaler_vers_bas(int _nb_lignes){
	typedef QPair<int,int> CoordonneesEnv;
	typedef QPair<QPair<int,int>,QPair<int,int> > LienPlat;
	QList<CoordonneesEnv> cles_env_=environnements.cles();
	HashMap<CoordonneesEnv,CoordonneesEnv> depl_;
	foreach(CoordonneesEnv c,cles_env_){
		depl_.ajouter_cle_valeur(c,CoordonneesEnv(c.first,c.second+_nb_lignes));
	}
	while(!cles_env_.isEmpty()){
		foreach(CoordonneesEnv c,cles_env_){
			CoordonneesEnv dest_=depl_.valeur(c);
			if(!cles_env_.contains(dest_)){
				deplacer(c,dest_);
				depl_.supprimer_cle_valeur(c);
			}
		}
		cles_env_=depl_.cles();
	}
	coords_dresseur.second+=_nb_lignes;
	//TODO changer les liens
	//liens_vers_autres_plateau
}

void PlateauLigue::decaler_vers_droite(int _nb_colonnes){
	typedef QPair<int,int> CoordonneesEnv;
	typedef QPair<QPair<int,int>,QPair<int,int> > LienPlat;
	QList<CoordonneesEnv> cles_env_=environnements.cles();
	HashMap<CoordonneesEnv,CoordonneesEnv> depl_;
	foreach(CoordonneesEnv c,cles_env_){
		depl_.ajouter_cle_valeur(c,CoordonneesEnv(c.first+_nb_colonnes,c.second));
	}
	while(!cles_env_.isEmpty()){
		foreach(CoordonneesEnv c,cles_env_){
			CoordonneesEnv dest_=depl_.valeur(c);
			if(!cles_env_.contains(dest_)){
				deplacer(c,dest_);
				depl_.supprimer_cle_valeur(c);
			}
		}
		cles_env_=depl_.cles();
	}
	coords_dresseur.first+=_nb_colonnes;
}

QPair<int,int> PlateauLigue::dimensions()const{
	/*typedef QPair<int,int> Position
	typedef QPair<int,int> Dimension
	Position plus_petit_coin_h_g_=QPair<int,int>(0,0)
	Position plus_grand_coin_b_d_g_=QPair<int,int>(0,0)
	QList<Position> cles_=environnements.cles()
	foreach(Position p,cles_){
		plus_petit_coin_h_g_=p
		plus_grand_coin_b_d_g_=p
	}
	foreach(Position p,cles_){
		if(p.first<plus_petit_coin_h_g_.first){
			plus_petit_coin_h_g_.first=p.first
		}
		if(p.second<plus_petit_coin_h_g_.second){
			plus_petit_coin_h_g_.second=p.second
		}
		Environnement env_cour_=environnements.valeur(p)
		Dimension dims_cour_=env_cour_.dimensions()
		int tmp_=p.first+dims_cour_.first-1
		if(tmp_>plus_grand_coin_b_d_g_.first){
			plus_grand_coin_b_d_g_.first=tmp_
		}
		tmp_=p.second+dims_cour_.second-1
		if(tmp_>plus_grand_coin_b_d_g_.second){
			plus_grand_coin_b_d_g_.second=tmp_
		}
	}*/
	QPair<QPair<int,int>,QPair<int,int> > bords_=bords();
	return QPair<int,int>(bords_.second.first-bords_.first.first+1,bords_.second.second-bords_.first.second+1);
	//return Dimension(plus_grand_coin_b_d_g_.first-plus_petit_coin_h_g_.first+1,plus_grand_coin_b_d_g_.second-plus_petit_coin_h_g_.second+1)
}

QPair<QPair<int,int>,QPair<int,int> > PlateauLigue::bords()const{
	typedef QPair<int,int> Position;
	typedef QPair<int,int> Dimension;
	Position plus_petit_coin_h_g_=QPair<int,int>(0,0);
	Position plus_grand_coin_b_d_g_=QPair<int,int>(0,0);
	QList<Position> cles_=environnements.cles();
	foreach(Position p,cles_){
		plus_petit_coin_h_g_=p;
		plus_grand_coin_b_d_g_=p;
	}
	foreach(Position p,cles_){
		if(p.first<plus_petit_coin_h_g_.first){
			plus_petit_coin_h_g_.first=p.first;
		}
		if(p.second<plus_petit_coin_h_g_.second){
			plus_petit_coin_h_g_.second=p.second;
		}
		EnvironnementLigue env_cour_=environnements.valeur(p);
		Dimension dims_cour_=env_cour_.dimensions();
		int tmp_=p.first+dims_cour_.first-1;
		if(tmp_>plus_grand_coin_b_d_g_.first){
			plus_grand_coin_b_d_g_.first=tmp_;
		}
		tmp_=p.second+dims_cour_.second-1;
		if(tmp_>plus_grand_coin_b_d_g_.second){
			plus_grand_coin_b_d_g_.second=tmp_;
		}
	}
	return QPair<Position,Position>(plus_petit_coin_h_g_,plus_grand_coin_b_d_g_);
}

bool PlateauLigue::peut_contenir_nv_env(const QPair<int,int>& _id,const QPair<int,int>& _dims,QList<QPair<int,int> >& _id_vs)const{
	typedef QPair<int,int> Position;
	typedef QPair<int,int> Dimension;
	QList<Position> cles_=environnements.cles();
	foreach(Position p,cles_){
		Dimension dims_voisin_=environnements.valeur(p).dimensions();
		QPair<QPair<int,int>,QPair<int,int> > coins_bord_=EnvironnementLigue::intersection(p,dims_voisin_,_id,_dims);
		if(coins_bord_.first.first>=0){
			_id_vs<<p;
		}
	}
	return _id_vs.isEmpty();
}

QList<QPair<int,int> > PlateauLigue::coins_gauche()const{
	return environnements.cles();
}

void PlateauLigue::deplacer(const QPair<int,int>& _origine,const QPair<int,int>& _destination){
	EnvironnementLigue env_depl_=environnements.valeur(_origine);
	environnements.supprimer_cle_valeur(_origine);
	environnements.ajouter_cle_valeur(_destination,env_depl_);
}

void PlateauLigue::ajouter_environnement(const QPair<int,int>& _id,const EnvironnementLigue& _nv_env){
	environnements.ajouter_cle_valeur(_id,_nv_env);
}

EnvironnementLigue PlateauLigue::environnement(const QPair<int,int>& _id){
	return environnements.valeur(_id);
}

EnvironnementLigue *PlateauLigue::environnement(const QPair<int,int>& _id,bool& _n_inst){
	return environnements.valeur(_id,_n_inst);
}

QPair<QPair<int,int>,QPair<int,int> > *PlateauLigue::adr_dest_lien_vers_plateau_suivant(){
	return &(lien_vers_plateau_suivant.second);
}

QPair<QPair<int,int>,QPair<int,int> > PlateauLigue::dest_lien_vers_plateau_suivant()const{
	return lien_vers_plateau_suivant.second;
}

QPair<QPair<int,int>,QPair<int,int> > *PlateauLigue::adr_orig_lien_vers_plateau_suivant(){
	return &(lien_vers_plateau_suivant.first);
}

QPair<QPair<int,int>,QPair<int,int> > PlateauLigue::orig_lien_vers_plateau_suivant()const{
	return lien_vers_plateau_suivant.first;
}

/*bool PlateauLigue::est_valide(QList<QPair<int,int> >& _tuiles_inexistantes)const{
	typedef QPair<int,int> Position
	typedef QPair<int,int> Dimension
	HashMap<Position,bool> tuiles_exist_
	Position plus_petit_coin_h_g_=QPair<int,int>(0,0)
	Position plus_grand_coin_b_d_g_=QPair<int,int>(0,0)
	QList<Position> cles_=environnements.cles()
	foreach(Position p,cles_){
		plus_petit_coin_h_g_=p
		plus_grand_coin_b_d_g_=p
	}
	foreach(Position p,cles_){
		if(p.first<plus_petit_coin_h_g_.first){
			plus_petit_coin_h_g_.first=p.first
		}
		if(p.second<plus_petit_coin_h_g_.second){
			plus_petit_coin_h_g_.second=p.second
		}
		EnvironnementLigue env_cour_=environnements.valeur(p)
		Dimension dims_cour_=env_cour_.dimensions()
		int tmp_=p.first+dims_cour_.first-1
		if(tmp_>plus_grand_coin_b_d_g_.first){
			plus_grand_coin_b_d_g_.first=tmp_
		}
		tmp_=p.second+dims_cour_.second-1
		if(tmp_>plus_grand_coin_b_d_g_.second){
			plus_grand_coin_b_d_g_.second=tmp_
		}
	}
	Dimension dims_pl_=Dimension(plus_grand_coin_b_d_g_.first-plus_petit_coin_h_g_.first+1,plus_grand_coin_b_d_g_.second-plus_petit_coin_h_g_.second+1)
	int largeur_=dims_pl_.first
	int hauteur_=dims_pl_.second
	for(int i=0;i<largeur_;i++){
		for(int j=0;j<hauteur_;j++){
			tuiles_exist_.ajouter_cle_valeur(Position(i,j),false)
		}
	}
	foreach(Position p,cles_){
		EnvironnementLigue env_cour_=environnements.valeur(p)
		Dimension dims_cour_=env_cour_.dimensions()
		largeur_=dims_cour_.first
		hauteur_=dims_cour_.second
		int ind_dep_x_=p.first
		int ind_fin_x_=ind_dep_x_+largeur_
		int ind_dep_y_=p.second
		int ind_fin_y_=ind_dep_y_+hauteur_
		for(int i=ind_dep_x_;i<ind_fin_x_;i++){
			for(int j=ind_dep_y_;j<ind_fin_y_;j++){
				tuiles_exist_.ajouter_cle_valeur(Position(i,j),true)
			}
		}
	}
	cles_=tuiles_exist_.cles()
	foreach(Position p,cles_){
		if(!tuiles_exist_.valeur(p)){
			_tuiles_inexistantes<<p
		}
	}
	if(coords_dresseur.first>plus_petit_coin_h_g_.first+plus_grand_coin_b_d_g_.first-plus_petit_coin_h_g_.first){
		return false
	}
	if(coords_dresseur.second>plus_petit_coin_h_g_.second+plus_grand_coin_b_d_g_.second-plus_petit_coin_h_g_.second){
		return false
	}
	return _tuiles_inexistantes.isEmpty()
}*/

QString PlateauLigue::exporter_environnements_voisins(int _nb_tab_env,const QPair<int,int>& _id,const EnvironnementLigue& _environnement)const{
	typedef QPair<int,int> Position;
	typedef QPair<int,int> Dimension;
	QList<QPair<Position,Dimension> > coords_voisins_;
	QList<QPair<Position,Dimension> > bords_=_environnement.bords(_id);
	QList<Position> cles_=environnements.cles();
	QString formattage_;
	int coords_inval_=Tuile::_coords_invalide_;
	int nb_bords_=Tuile::_nb_bords_;
	for(int i=0;i<nb_bords_;i++){
		bool existe_inter=false;
		Position pos_bord_=bords_[i].first;
		Dimension dims_bord_=bords_[i].second;
		int indice_recherche_=coords_voisins_.size();
		foreach(Position p,cles_){
			EnvironnementLigue env_cour_=environnements.valeur(p);
			Dimension dims_voisin_=env_cour_.dimensions();
			QPair<QPair<int,int>,QPair<int,int> > coins_bord_=EnvironnementLigue::intersection(p,dims_voisin_,pos_bord_,dims_bord_);
			if(coins_bord_.first.first==coords_inval_){
				//Si l'intersection est vide on n'ajoute rien dans les résultats
				continue;
			}
			existe_inter=true;
			Position coin_gauche_inter_=coins_bord_.first;
			Position coin_droit_inter_=coins_bord_.second;
			int nb_pts_commun_=(coin_droit_inter_.first-coin_gauche_inter_.first+1)*(coin_droit_inter_.second-coin_gauche_inter_.second+1);
			switch(i){
				case 0:{
					int cote_droit_v_=p.second+dims_voisin_.second-1;
					int indice_insertion_=coords_voisins_.size();
					/*Au cas où, il existe des coordonnées d'environnement voisin déjà insérér mais pas dans le bon ordre il faut 
					insérer un intervalle de donnée à l'indice indice_insertion_*/
					for(int j=indice_insertion_-1;j>=indice_recherche_;j--){
						Position vois_deja_pres_=coords_voisins_[j].first;
						EnvironnementLigue env_cour_2_=environnements.valeur(vois_deja_pres_);
						int coin_bas_droit_v_=vois_deja_pres_.second;
						if(coin_bas_droit_v_>cote_droit_v_){
							indice_insertion_=j;
						}
					}
					for(int j=0;j<nb_pts_commun_;j++){
						coords_voisins_.insert(indice_insertion_+j,QPair<Position,Position>(p,Position(coin_gauche_inter_.first,coin_gauche_inter_.second+j)));
					}
					}
					break;
				case 1:{
					int cote_haut_v_=p.first+dims_voisin_.first-1;
					int indice_insertion_=coords_voisins_.size();
					for(int j=indice_insertion_-1;j>=indice_recherche_;j--){
						Position vois_deja_pres_=coords_voisins_[j].first;
						EnvironnementLigue env_cour_2_=environnements.valeur(vois_deja_pres_);
						int coin_bas_droit_v_=vois_deja_pres_.first;
						if(coin_bas_droit_v_>cote_haut_v_){
							indice_insertion_=j;
						}
					}
					for(int j=0;j<nb_pts_commun_;j++){
						coords_voisins_.insert(indice_insertion_+j,QPair<Position,Position>(p,Position(coin_gauche_inter_.first+j,coin_gauche_inter_.second)));
					}
					}
					break;
				case 2:{
					int cote_gauche_v_=p.second;
					int indice_insertion_=coords_voisins_.size();
					for(int j=indice_insertion_-1;j>=indice_recherche_;j--){
						Position vois_deja_pres_=coords_voisins_[j].first;
						EnvironnementLigue env_cour_2_=environnements.valeur(vois_deja_pres_);
						Dimension dims_voisin_2_=env_cour_2_.dimensions();
						int coin_bas_droit_v_=vois_deja_pres_.second+dims_voisin_2_.second-1;
						if(coin_bas_droit_v_<cote_gauche_v_){
							indice_insertion_=j;
						}
					}
					for(int j=0;j<nb_pts_commun_;j++){
						coords_voisins_.insert(indice_insertion_+j,QPair<Position,Position>(p,Position(coin_droit_inter_.first,coin_droit_inter_.second-j)));
					}
					}
					break;
				default:{;
					int cote_bas_v_=p.first;
					int indice_insertion_=coords_voisins_.size();
					for(int j=indice_insertion_-1;j>=indice_recherche_;j--){
						Position vois_deja_pres_=coords_voisins_[j].first;
						EnvironnementLigue env_cour_2_=environnements.valeur(vois_deja_pres_);
						Dimension dims_voisin_2_=env_cour_2_.dimensions();
						int coin_bas_droit_v_=vois_deja_pres_.first+dims_voisin_2_.first-1;
						if(coin_bas_droit_v_<cote_bas_v_){
							indice_insertion_=j;
						}
					}
					for(int j=0;j<nb_pts_commun_;j++){
						coords_voisins_.insert(indice_insertion_+j,QPair<Position,Position>(p,Position(coin_droit_inter_.first-j,coin_droit_inter_.second)));
					}
				}
			}
		}
		if(!existe_inter){
			int nb_pts_bords_=dims_bord_.first*dims_bord_.second;
			for(int j=0;j<nb_pts_bords_;j++){
				coords_voisins_<<QPair<Position,Position>(Position(coords_inval_,coords_inval_),Position(coords_inval_,coords_inval_));
			}
		}
	}
	//_nb_tab_env=2
	typedef QPair<Position,Dimension> Coords_voisin;
	foreach(Coords_voisin c,coords_voisins_){
		int nb_tab_env_att_=_nb_tab_env+1;
		for(int i=0;i<nb_tab_env_att_;i++){
			formattage_+="\t";
		}
		if(c.first.first!=coords_inval_){
			formattage_+="<V>"+QString::number(c.first.first)+","+QString::number(c.first.second)+";";
			formattage_+=QString::number(c.second.first)+","+QString::number(c.second.second)+"</V>\n";
		}else{
			formattage_+="<V/>\n";
		}
	}
	for(int i=0;i<_nb_tab_env;i++){
		formattage_+="\t";
	}
	formattage_+="</EnvLigue>\n";
	return formattage_;
}

QString PlateauLigue::exporter(int _nb_tab_env)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_env;i++){
		formattage_+="\t";
	}
	formattage_+="<Plat>\n";
	typedef QPair<int,int> Position;
	typedef QPair<int,int> Dimension;
	QList<Position> cles_=environnements.cles();
	foreach(Position p,cles_){
		EnvironnementLigue env_=environnements.valeur(p);
		formattage_+=env_.exporter(_nb_tab_env+1,p);
		formattage_+=exporter_environnements_voisins(_nb_tab_env+1,p,env_);
	}
	for(int i=0;i<_nb_tab_env;i++){
		formattage_+="\t";
	}
	formattage_+="<CoordsDres>"+QString::number(coords_dresseur.first)+","+QString::number(coords_dresseur.second)+"</CoordsDres>\n";
	formattage_+=dresseur_ligue.exporter(_nb_tab_env+1);
	typedef QPair<QPair<int,int>,QPair<int,int> > Origine;
	typedef QPair<QPair<int,int>,QPair<int,int> > Arrivee;
	for(int i=0;i<_nb_tab_env;i++){
		formattage_+="\t";
	}
	Origine p_=lien_vers_plateau_suivant.first;
	formattage_+="<L>"+QString::number(p_.first.first)+","+QString::number(p_.first.second)+",";
	formattage_+=QString::number(p_.second.first)+","+QString::number(p_.second.second)+";";
	Arrivee arr_=lien_vers_plateau_suivant.second;
	formattage_+=QString::number(arr_.first.first)+","+QString::number(arr_.first.second)+",";
	formattage_+=QString::number(arr_.second.first)+","+QString::number(arr_.second.second)+"</L>\n";
	for(int i=0;i<_nb_tab_env;i++){
		formattage_+="\t";
	}
	formattage_+="</Plat>\n";
	return formattage_;
}

bool operator==(const PlateauLigue& a,const PlateauLigue& b){
	return a.egal(b);
}

void PlateauLigue::serialiser(Flux& _out)const{
	_out<<environnements;
	_out<<coords_dresseur;
	_out<<dresseur_ligue;
	_out<<lien_vers_plateau_suivant;
}

void PlateauLigue::deserialiser(Flux& _in){
	_in>>environnements;
	_in>>coords_dresseur;
	_in>>dresseur_ligue;
	_in>>lien_vers_plateau_suivant;
}

Flux & operator <<(Flux& out,const PlateauLigue& _PlateauLigue){
	_PlateauLigue.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,PlateauLigue& _PlateauLigue){
	_PlateauLigue.deserialiser(in);
	return in;
}



