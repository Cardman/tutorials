#include "serialisable/cartes/plateau.h"
Plateau::Plateau(){
	;
}

bool Plateau::egal(const Plateau& _autre)const{
	bool egal_;
	egal_=environnements==_autre.environnements;
	egal_&=liens_vers_autres_plateau==_autre.liens_vers_autres_plateau;
	egal_&=noms_images_liens==_autre.noms_images_liens;
	return egal_;
}

void Plateau::aff_liens_vers_autres_plateau(){
	liens_vers_autres_plateau=liens_vers_autres_plateau_tmp;
}

void Plateau::aff_liens_vers_autres_plateau_tmp(){
	liens_vers_autres_plateau_tmp=liens_vers_autres_plateau;
}

void Plateau::aff_noms_images_liens(){
	noms_images_liens=noms_images_liens_tmp;
}

void Plateau::aff_noms_images_liens_tmp(){
	noms_images_liens_tmp=noms_images_liens;
}

bool Plateau::peut_contenir_nv_env(const QPair<int,int>& _id,const QPair<int,int>& _dims,QList<QPair<int,int> >& _id_vs)const{
	typedef QPair<int,int> Position;
	typedef QPair<int,int> Dimension;
	QList<Position> cles_=environnements.cles();
	foreach(Position p,cles_){
		Dimension dims_voisin_=environnements.valeur(p).dimensions();
		QPair<QPair<int,int>,QPair<int,int> > coins_bord_=Environnement::intersection(p,dims_voisin_,_id,_dims);
		if(coins_bord_.first.first>=0){
			_id_vs<<p;
		}
	}
	return _id_vs.isEmpty();
}

void Plateau::deplacer(const QPair<int,int>& _origine,const QPair<int,int>& _destination){
	Environnement env_depl_=environnements.valeur(_origine);
	environnements.supprimer_cle_valeur(_origine);
	environnements.ajouter_cle_valeur(_destination,env_depl_);
}

void Plateau::deplacer_liens(const QPair<int,int>& _origine,const QPair<int,int>& _destination){
	typedef QPair<int,int> Origine;
	typedef QPair<Origine,Origine> OrigineLien;
	QPair<int,int> sens_;
	sens_.first=_destination.first-_origine.first;
	sens_.second=_destination.second-_origine.second;
	QList<OrigineLien> liens_=liens_vers_autres_plateau.cles();
	HashMap<OrigineLien,OrigineLien> depl_liens_;
	foreach(OrigineLien c,liens_){
		if(c.second==_origine){
			depl_liens_.ajouter_cle_valeur(c,OrigineLien(c.first,QPair<int,int>(c.second.first+sens_.first,c.second.second+sens_.second)));
		}
	}
	while(!liens_.isEmpty()){
		foreach(OrigineLien c,liens_){
			OrigineLien dest_=depl_liens_.valeur(c);
			if(!liens_.contains(dest_)){
				Coordonnees env_depl_=liens_vers_autres_plateau.valeur(c);
				liens_vers_autres_plateau.supprimer_cle_valeur(c);
				liens_vers_autres_plateau.ajouter_cle_valeur(dest_,env_depl_);
				depl_liens_.supprimer_cle_valeur(c);
			}
		}
		liens_=depl_liens_.cles();
	}
	liens_=noms_images_liens.cles();
	foreach(OrigineLien c,liens_){
		if(c.second==_origine){
			depl_liens_.ajouter_cle_valeur(c,OrigineLien(c.first,QPair<int,int>(c.second.first+sens_.first,c.second.second+sens_.second)));
		}
	}
	while(!liens_.isEmpty()){
		foreach(OrigineLien c,liens_){
			OrigineLien dest_=depl_liens_.valeur(c);
			if(!liens_.contains(dest_)){
				QString env_depl_=noms_images_liens.valeur(c);
				noms_images_liens.supprimer_cle_valeur(c);
				noms_images_liens.ajouter_cle_valeur(dest_,env_depl_);
				depl_liens_.supprimer_cle_valeur(c);
			}
		}
		liens_=depl_liens_.cles();
	}
}

void Plateau::decaler_vers_bas(int _nb_lignes){
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
	QList<LienPlat> liens_=liaisons_vers_autres_plateaux();
	HashMap<LienPlat,LienPlat> depl_liens_;
	foreach(LienPlat c,liens_){
		depl_liens_.ajouter_cle_valeur(c,LienPlat(QPair<int,int>(c.first.first,c.first.second+_nb_lignes),c.second));
	}
	while(!liens_.isEmpty()){
		foreach(LienPlat c,liens_){
			LienPlat dest_=depl_liens_.valeur(c);
			if(!liens_.contains(dest_)){
				Coordonnees env_depl_=liens_vers_autres_plateau.valeur(c);
				QString nom_image_=noms_images_liens.valeur(c);
				liens_vers_autres_plateau.supprimer_cle_valeur(c);
				noms_images_liens.supprimer_cle_valeur(c);
				liens_vers_autres_plateau.ajouter_cle_valeur(dest_,env_depl_);
				noms_images_liens.ajouter_cle_valeur(dest_,nom_image_);
				depl_liens_.supprimer_cle_valeur(c);
			}
		}
		liens_=depl_liens_.cles();
	}
	//liens_vers_autres_plateau
}

void Plateau::decaler_vers_droite(int _nb_colonnes){
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
	QList<LienPlat> liens_=liaisons_vers_autres_plateaux();
	HashMap<LienPlat,LienPlat> depl_liens_;
	foreach(LienPlat c,liens_){
		depl_liens_.ajouter_cle_valeur(c,LienPlat(QPair<int,int>(c.first.first+_nb_colonnes,c.first.second),c.second));
	}
	while(!liens_.isEmpty()){
		foreach(LienPlat c,liens_){
			LienPlat dest_=depl_liens_.valeur(c);
			if(!liens_.contains(dest_)){
				Coordonnees env_depl_=liens_vers_autres_plateau.valeur(c);
				QString nom_image_=noms_images_liens.valeur(c);
				liens_vers_autres_plateau.supprimer_cle_valeur(c);
				noms_images_liens.supprimer_cle_valeur(c);
				liens_vers_autres_plateau.ajouter_cle_valeur(dest_,env_depl_);
				noms_images_liens.ajouter_cle_valeur(dest_,nom_image_);
				depl_liens_.supprimer_cle_valeur(c);
			}
		}
		liens_=depl_liens_.cles();
	}
}

QList<QPair<int,int> > Plateau::coins_gauche()const{
	return environnements.cles();
}

QList<QPair<QPair<int,int>,QPair<int,int> > > Plateau::liaisons_vers_autres_plateaux()const{
	return liens_vers_autres_plateau.cles();
}

void Plateau::ajouter_environnement(const QPair<int,int>& _id,const Environnement& _nv_env){
	environnements.ajouter_cle_valeur(_id,_nv_env);
}

Environnement Plateau::environnement(const QPair<int,int>& _id)const{
	return environnements.valeur(_id);
}

Environnement *Plateau::environnement(const QPair<int,int>& _id,bool& _n_inst){
	return environnements.valeur(_id,_n_inst);
}

void Plateau::supprimer_environnement(const QPair<int,int>& _id){
	environnements.supprimer_cle_valeur(_id);
}

QPair<int,int> Plateau::dimensions()const{
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

QPair<QPair<int,int>,QPair<int,int> > Plateau::bords()const{
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
		Environnement env_cour_=environnements.valeur(p);
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

QString *Plateau::image_origine_liaison(const QPair<QPair<int,int>,QPair<int,int> >& _origine,bool& _n_inst){
	return noms_images_liens.valeur(_origine,_n_inst);
}

QString Plateau::image_origine_liaison(const QPair<QPair<int,int>,QPair<int,int> >& _origine){
	return noms_images_liens.valeur(_origine);
}

void Plateau::ajouter_image_origine_liaison(const QPair<QPair<int,int>,QPair<int,int> >& _origine,const QString& _nom){
	noms_images_liens_tmp.ajouter_cle_valeur(_origine,_nom);
}

Coordonnees* Plateau::destination_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine,bool& _n_inst){
	return liens_vers_autres_plateau.valeur(_origine,_n_inst);
}

Coordonnees Plateau::destination_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine){
	return liens_vers_autres_plateau.valeur(_origine);
}

void Plateau::ajouter_dest_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine,const Coordonnees& _lien){
	liens_vers_autres_plateau_tmp.ajouter_cle_valeur(_origine,_lien);
}

void Plateau::supprimer_dest_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine){
	liens_vers_autres_plateau.supprimer_cle_valeur(_origine);
	noms_images_liens.supprimer_cle_valeur(_origine);
}

void Plateau::supprimer_dest_autre_plateau_tmp(const QPair<QPair<int,int>,QPair<int,int> >& _origine){
	liens_vers_autres_plateau_tmp.supprimer_cle_valeur(_origine);
	noms_images_liens_tmp.supprimer_cle_valeur(_origine);
}

void Plateau::supprimer_toutes_dest_autre_plateau(){
	typedef QPair<QPair<int,int>,QPair<int,int> > Origine;
	QList<Origine> liaisons_=liaisons_vers_autres_plateaux();
	foreach(Origine o,liaisons_){
		supprimer_dest_autre_plateau(o);
	}
}

bool Plateau::est_valide(QList<QPair<int,int> >& _tuiles_inexistantes)const{
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
		Environnement env_cour_=environnements.valeur(p);
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
		Environnement env_cour_=environnements.valeur(p);
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
	typedef QPair<QPair<int,int>,QPair<int,int> > Liaison;
	QList<Liaison> cles_liais_=liaisons_vers_autres_plateaux();
	foreach(Liaison l,cles_liais_){
		if(!environnements.valeur(l.first).est_vide(l.second)){
			return false;
		}
	}
	return _tuiles_inexistantes.isEmpty();
}

QString Plateau::exporter_environnements_voisins(int _nb_tab_env,const QPair<int,int>& _id,const Environnement& _environnement)const{
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
			Environnement env_cour_=environnements.valeur(p);
			Dimension dims_voisin_=env_cour_.dimensions();
			QPair<QPair<int,int>,QPair<int,int> > coins_bord_=Environnement::intersection(p,dims_voisin_,pos_bord_,dims_bord_);
			if(coins_bord_.first.first==coords_inval_){
				//Si l'intersection est vide on n'ajoute rien dans les rsultats
				continue;
			}
			existe_inter=true;
			Position coin_gauche_inter_=coins_bord_.first;
			Position coin_droit_inter_=coins_bord_.second;
			int nb_pts_commun_=(coin_droit_inter_.first-coin_gauche_inter_.first+1)*(coin_droit_inter_.second-coin_gauche_inter_.second+1);
			int indice_insertion_=coords_voisins_.size();
			switch(i){
				case 0:{
					int cote_droit_v_=p.second+dims_voisin_.second-1;
					/*Au cas o, il existe des coordonnes d'environnement voisin dj insrr mais pas dans le bon ordre il faut 
					insrer un intervalle de donne  l'indice indice_insertion_*/
					for(int j=indice_insertion_-1;j>=indice_recherche_;j--){
						Position vois_deja_pres_=coords_voisins_[j].first;
						Environnement env_cour_2_=environnements.valeur(vois_deja_pres_);
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
					for(int j=indice_insertion_-1;j>=indice_recherche_;j--){
						Position vois_deja_pres_=coords_voisins_[j].first;
						Environnement env_cour_2_=environnements.valeur(vois_deja_pres_);
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
					for(int j=indice_insertion_-1;j>=indice_recherche_;j--){
						Position vois_deja_pres_=coords_voisins_[j].first;
						Environnement env_cour_2_=environnements.valeur(vois_deja_pres_);
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
					for(int j=indice_insertion_-1;j>=indice_recherche_;j--){
						Position vois_deja_pres_=coords_voisins_[j].first;
						Environnement env_cour_2_=environnements.valeur(vois_deja_pres_);
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
		/*formattage_+="<Vois>"+QString::number(c.first.first)+","+QString::number(c.first.second)+";"
		formattage_+=QString::number(c.second.first)+","+QString::number(c.second.second)+"</Vois>\n"*/
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
	formattage_+="</Env>\n";
	return formattage_;
}

QString Plateau::exporter(int _nb_tab_env)const{
	QString formattage_;
	for(int i=0;i<_nb_tab_env;i++){
		formattage_+="\t";
	}
	formattage_+="<Plat>\n";
	typedef QPair<int,int> Position;
	typedef QPair<int,int> Dimension;
	QList<Position> cles_=environnements.cles();
	foreach(Position p,cles_){
		Environnement env_=environnements.valeur(p);
		formattage_+=env_.exporter(_nb_tab_env+1,p);
		formattage_+=exporter_environnements_voisins(_nb_tab_env+1,p,env_);
	}
	/*for(int i=0;i<_nb_tab_env;i++){
		formattage_+="\t"
	}*/
	typedef QPair<QPair<int,int>,QPair<int,int> > Origine;
	//typedef QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > Arrivee
	foreach(Origine o,liens_vers_autres_plateau.cles()){
		Coordonnees arr_2_=liens_vers_autres_plateau.valeur(o);
		for(int i=0;i<_nb_tab_env;i++){
			formattage_+="\t";
		}
		Origine p_=o;
		//QPair<QPair<int,int>,QPair<int,int> > arr_=arr_2_.first
		formattage_+="<P>"+QString::number(p_.first.first)+","+QString::number(p_.first.second)+",";
		formattage_+=QString::number(p_.second.first)+","+QString::number(p_.second.second)+"_";
		formattage_+=arr_2_.formater()+"</P>\n";
		for(int i=0;i<_nb_tab_env;i++){
			formattage_+="\t";
		}
		formattage_+="<I>"+noms_images_liens.valeur(o)+"<I>\n";
		//_out<<noms_images_liens
		//formattage_+=QString::number(arr_.first.first)+","+QString::number(arr_.first.second)+","
		//formattage_+=QString::number(arr_.second.first)+","+QString::number(arr_.second.second)+";"
		//formattage_+=QString::number(arr_2_.second.first)+","+QString::number(arr_2_.second.second)+"</P>\n"
	}
	//typedef QPair<int,int> Origine2
	//typedef QPair<QPair<int,int>,QPair<int,int> > Arrivee2
	/*foreach(Origine2 o,liens_vers_autres_lieux.cles()){
		Arrivee2 arr_=liens_vers_autres_lieux.valeur(o)
		for(int i=0;i<_nb_tab_env;i++){
			formattage_+="\t"
		}
		Origine2 p_=o
		formattage_+="<L>"+QString::number(p_.first)+","+QString::number(p_.second)+";"
		formattage_+=QString::number(arr_.first.first)+","+QString::number(arr_.first.second)+","
		formattage_+=QString::number(arr_.second.first)+","+QString::number(arr_.second.second)+"</L>\n"
	}*/
	for(int i=0;i<_nb_tab_env;i++){
		formattage_+="\t";
	}
	formattage_+="</Plat>\n";
	return formattage_;
}

bool operator==(const Plateau& a,const Plateau& b){
	return a.egal(b);
}

void Plateau::serialiser(Flux& _out)const{
	_out<<environnements;
	_out<<liens_vers_autres_plateau;
	_out<<noms_images_liens;
	//_out<<liens_vers_autres_lieux
}

void Plateau::deserialiser(Flux& _in){
	_in>>environnements;
	_in>>liens_vers_autres_plateau;
	_in>>noms_images_liens;
	//_in>>liens_vers_autres_lieux
}

Flux & operator <<(Flux& out,const Plateau& _PlateauLigue){
	_PlateauLigue.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Plateau& _PlateauLigue){
	_PlateauLigue.deserialiser(in);
	return in;
}



