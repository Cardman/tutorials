#include "serialisable/partie/partie.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include "base_donnees/personnages/champion.h"

Partie::Partie(){

}

Partie::Partie(Donnees* _d){
	difficultes=Difficulte(_d);
	int nb_boites_=_d->constante_numerique("NB_BOITES");
	for(int i=0;i<nb_boites_;i++){
		noms_boites<<"Boite n°"+QString::number(i);
	}
	coordonnees_utilisateur=_d->val_coords_depart();
	orientation_utilisateur.first=0;
	orientation_utilisateur.second=1;
	QPair<QPair<PokemonUtilisateur,PokemonUtilisateur>,int> triplet_(QPair<PokemonUtilisateur,PokemonUtilisateur>(PokemonUtilisateur(),PokemonUtilisateur()),0);
	Coordonnees c_;
	typedef QPair<int,int> Coin;
	foreach(Coin c,_d->val_lieux_vols().cles()){
		lieux_visites.ajouter_cle_valeur(_d->val_lieux_vols().valeur(c).lieu(),false);
	}
	foreach(int l,_d->val_lieux().cles()){
		Lieu *l_=_d->val_lieux().valeur(l);
		c_.lieu()=l;
		foreach(int p,l_->plateaux_c()){
			Plateau *p_=l_->plateau(p);
			typedef QPair<int,int> Position;
			c_.plateau()=p;
			foreach(Coin e,p_->coords_env()){
				Environnement *e_=p_->environnement(e);
				c_.coords_environnement()=e;
				foreach(Position p2,e_->coords_lieux_dons_pokemon()){
					c_.coords_tuile()=p2;
					pokemon_pris.ajouter_cle_valeur(c_,false);
				}
				foreach(Position p2,e_->coords_pokemon_legendaire()){
					c_.coords_tuile()=p2;
					pokemon_pris.ajouter_cle_valeur(c_,false);
				}
				foreach(Position p2,e_->coords_objets_donnes_ramasses()){
					c_.coords_tuile()=p2;
					objets_ramasses.ajouter_cle_valeur(c_,false);
				}
				foreach(Position p2,e_->coords_autres_persos()){
					Dresseur1 *dr_=qobject_cast<Dresseur1*>(e_->perso(p2));
					if(dr_){
						c_.coords_tuile()=p2;
						int nb_eq_=dr_->nb_equipes();
						for(int i=0;i<nb_eq_;i++){
							dresseurs_battus.ajouter_cle_valeur(QPair<Coordonnees,int>(c_,i),false);
						}
					}
				}
				QPair<int,int> dims_=e_->dimensions();
				for(int i=0;i<dims_.first;i++){
					for(int j=0;j<dims_.second;j++){
						if(e_->contient_pension(QPair<int,int>(i,j))){
							c_.coords_tuile()=QPair<int,int>(i,j);
							pokemon_pension.ajouter_cle_valeur(c_,triplet_);
						}
						Tuile *t_=e_->tuile(QPair<int,int>(i,j));
						if(t_->val_nom_image_obst().second==Tuile::ARBRE){
							c_.coords_tuile()=QPair<int,int>(i,j);
							arbres_coupes.ajouter_cle_valeur(c_,false);
						}else if(t_->val_nom_image_obst().second==Tuile::ROCHER_AMOVIBLE){
							c_.coords_tuile()=QPair<int,int>(i,j);
							position_actuelle_rochers_deplacables.ajouter_cle_valeur(c_,c_);
						}else if(t_->val_nom_image_obst().second==Tuile::ROCHER_DESTRUCTIBLE){
							c_.coords_tuile()=QPair<int,int>(i,j);
							rochers_detruits.ajouter_cle_valeur(c_,false);
						}else if(t_->val_nom_image_obst().second==Tuile::TOURBILLON){
							c_.coords_tuile()=QPair<int,int>(i,j);
							tourbillons_siphones.ajouter_cle_valeur(c_,false);
						}
					}
				}
			}
		}
	}
	indice_pas=0;
	indice_periode=0;
	indice_periode_peche.ajouter_cle_valeur(Environnement::_canne_,0);
	indice_periode_peche.ajouter_cle_valeur(Environnement::_super_canne_,0);
	indice_periode_peche.ajouter_cle_valeur(Environnement::_mega_canne_,0);
	stade_ligue=0;
	ligue=false;
}

void Partie::incrementer_per_peche(const QString& _canne){
	indice_periode_peche.valeur(_canne)++;
}

void Partie::reinit_per_peche(const QString& _canne){
	indice_periode_peche.valeur(_canne)=0;
}

uint Partie::periode_peche(const QString& _canne)const{
	return indice_periode_peche.valeur(_canne);
}

QString& Partie::commentaire_r(){
	return commentaire;
}

bool Partie::present_ligue()const{
	return ligue;
}

bool& Partie::present_ligue(){
	return ligue;
}

bool Partie::lieu_visite(int _lieu)const{
	return lieux_visites.valeur(_lieu);
}

Coordonnees Partie::coords_util()const{
	return coordonnees_utilisateur;
}

Coordonnees& Partie::coords_util(){
	return coordonnees_utilisateur;
}

bool Partie::contient_champions(const QList<Coordonnees>& _liste)const{
	QList<QPair<Coordonnees,int> > dres_battus_=dresseurs_battus.cles(true);
	QList<Coordonnees> dres_battus_une_fois_;
	typedef QPair<Coordonnees,int> DresseurBattu;
	foreach(DresseurBattu d,dres_battus_){
		dres_battus_une_fois_<<d.first;
	}
	return Utilitaire::contient<Coordonnees>(dres_battus_une_fois_,_liste);
}

uchar Partie::nb_dresseur_ligue_battus()const{
	return stade_ligue;
}

uchar& Partie::nb_dresseur_ligue_battus(){
	return stade_ligue;
}

QList<uchar> Partie::ligues_battues()const{
	return ligues_deja_battues;
}

QList<uchar>& Partie::ligues_battues(){
	return ligues_deja_battues;
}

QList<Coordonnees> Partie::arbres_non_coupes()const{
	return arbres_coupes.cles(false);
}

QList<Coordonnees> Partie::tourbillon_non_siphones()const{
	return tourbillons_siphones.cles(false);
}

QList<Coordonnees> Partie::rochers_non_detruits()const{
	return rochers_detruits.cles(false);
}

QList<Coordonnees> Partie::rocher_a_position(const Coordonnees& _coords)const{
	return position_actuelle_rochers_deplacables.cles(_coords);
}

void Partie::prendre_pokemon(const Coordonnees& _coords){
	pokemon_pris.valeur(_coords)=true;
}

bool Partie::element_absent(const Coordonnees& _coords)const{
	if(pokemon_pris.cles().contains(_coords)){
		return pokemon_pris.valeur(_coords);
	}
	if(objets_ramasses.cles().contains(_coords)){
		return objets_ramasses.valeur(_coords);
	}
	return false;
}

QPair<int,int> Partie::orientation()const{
	return orientation_utilisateur;
}

Difficulte Partie::diff()const{
	return difficultes;
}

Difficulte& Partie::diff(){
	return difficultes;
}

Utilisateur Partie::utilis()const{
	return utilisateur;
}

Utilisateur& Partie::utilis(){
	return utilisateur;
}

bool Partie::existe_pokemon_avec_capsule(const QString& _capsule)const{
	typedef QPair<uchar,PokemonUtilisateur> PositionPokemon;
	typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
	foreach(PositionPokemon p,utilisateur.equipe_ut()){
		foreach(AttaquePP a,p.second.attaques_apprises()){
			if(a.first==_capsule){
				return true;
			}
		}
	}
	return false;
}

bool Partie::pension_disponible(const Coordonnees& _coords)const{
	return pokemon_pension.valeur(_coords).first.first.niv_pk()==0;
}

QString Partie::compatibles_pensions(uchar _pos_1,uchar _pos_2,Donnees *_d)const{
	if(_pos_1==_pos_2){
		return "meme pokemon";
	}
	int ind_=-1;
	int ind_2_=-1;
	QList<QPair<uchar,PokemonUtilisateur> > equipe_=utilisateur.equipe_ut();
	int nb_eq_=equipe_.size();
	for(int i=0;i<nb_eq_;i++){
		if(equipe_[i].first==_pos_1){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return "pokemon inexistant";
	}
	for(int i=0;i<nb_eq_;i++){
		if(equipe_[i].first==_pos_2){
			ind_2_=i;
			break;
		}
	}
	if(ind_2_<0){
		return "pokemon inexistant";
	}
	//
	PokemonUtilisateur pk_1_=equipe_[ind_].second;
	PokemonUtilisateur pk_2_=equipe_[ind_2_].second;
	FichePokemon *f_pk_1_=_d->val_pokedex().valeur(pk_1_.n_pk());
	QStringList groupes_1_=f_pk_1_->gps_o();
	FichePokemon *f_pk_2_=_d->val_pokedex().valeur(pk_2_.n_pk());
	QStringList groupes_2_=f_pk_2_->gps_o();
	QString erreur_;
	bool traite_=false;
	if(pk_1_.genre_pk()=="ASSEXUE"){
		if(!groupes_2_.contains("METAMORPH")||_d->genres_non_assexues().contains(pk_2_.genre_pk())){
			traite_=true;
			erreur_+="pokemon assexue avec un pokemon ne faisant pas partie du groupe metamorph\n";
		}
	}
	if(pk_2_.genre_pk()=="ASSEXUE"){
		if(!groupes_1_.contains("METAMORPH")||_d->genres_non_assexues().contains(pk_1_.genre_pk())){
			traite_=true;
			erreur_+="pokemon assexue avec un pokemon ne faisant pas partie du groupe metamorph\n";
		}
	}
	if(!traite_){
		if(_d->genres_non_assexues().contains(pk_1_.genre_pk())){
			traite_=true;
			if(!_d->genres_non_assexues().contains(pk_2_.genre_pk())){
				erreur_+="pokemon assexue avec un pokemon non assexue\n";
			}else{
				if(pk_1_.genre_pk()==pk_2_.genre_pk()){
					erreur_+="pokemons de meme sexe\n";
				}else{
					if(Utilitaire::intersection<QString>(groupes_1_,groupes_2_).isEmpty()){
						erreur_+="pokemons n'ayant aucun groupe d'oeufs en commun\n";
					}
				}
			}
		}else{
			erreur_+="pokemon assexue avec un pokemon non assexue\n";
		}
	}
	return erreur_;
}

void Partie::deposer_pokemons_pension(uchar _pos_1,uchar _pos_2,const Coordonnees& _coords){
	int ind_=-1;
	int ind_2_=-1;
	QList<QPair<uchar,PokemonUtilisateur> >& equipe_=utilisateur.equipe_ut();
	QList<QPair<uchar,OeufPokemon> >& oeufs_=utilisateur.oeufs();
	int nb_eq_=equipe_.size();
	for(int i=0;i<nb_eq_;i++){
		if(equipe_[i].first==_pos_1){
			ind_=i;
			break;
		}
	}
	for(int i=0;i<nb_eq_;i++){
		if(equipe_[i].first==_pos_2){
			ind_2_=i;
			break;
		}
	}
	QPair<QPair<PokemonUtilisateur,PokemonUtilisateur>,int>& valeur_=pokemon_pension.valeur(_coords);
	uchar pos_1_=equipe_[ind_].first;
	uchar pos_2_=equipe_[ind_2_].first;
	valeur_.first.first=equipe_[ind_].second;
	valeur_.first.second=equipe_[ind_2_].second;
	valeur_.second=0;
	QPair<uchar,uchar> max_min_=Utilitaire::max_min<uchar>(ind_,ind_2_);
	QPair<uchar,uchar> max_min_2_=Utilitaire::max_min<uchar>(pos_1_,pos_2_);
	equipe_.removeAt(max_min_.first);
	nb_eq_--;
	for(int i=max_min_.first;i<nb_eq_;i++){
		equipe_[i].first--;
	}
	for(int i=0;i<oeufs_.size();i++){
		if(oeufs_[i].first>max_min_2_.first){
			oeufs_[i].first--;
		}
	}
	equipe_.removeAt(max_min_.second);
	nb_eq_--;
	for(int i=max_min_.second;i<nb_eq_;i++){
		equipe_[i].first--;
	}
	for(int i=0;i<oeufs_.size();i++){
		if(oeufs_[i].first>max_min_2_.second){
			oeufs_[i].first--;
		}
	}
}

bool Partie::recuperer_pokemons_pension(const Coordonnees& _coords){
	QPair<QPair<PokemonUtilisateur,PokemonUtilisateur>,int>& valeur_=pokemon_pension.valeur(_coords);
	QList<QPair<uchar,PokemonUtilisateur> >& equipe_=utilisateur.equipe_ut();
	if(equipe_.size()+2>difficultes.r_nb_max_pk_par_equipe()){
		return false;
	}
	int pos_=equipe_.size()+utilisateur.oeufs().size();
	equipe_<<QPair<uchar,PokemonUtilisateur>(pos_,valeur_.first.first);
	equipe_<<QPair<uchar,PokemonUtilisateur>(pos_+1,valeur_.first.second);
	valeur_.first.first=PokemonUtilisateur();
	valeur_.first.second=PokemonUtilisateur();
	valeur_.second=0;
	return true;
}

void Partie::augmenter_pas_vers_ponte(){
	foreach(Coordonnees c,pokemon_pension.cles()){
		QPair<QPair<PokemonUtilisateur,PokemonUtilisateur>,int>& valeur_=pokemon_pension.valeur(c);
		if(valeur_.first.first.niv_pk()!=0){
			if(valeur_.second<1024){
				valeur_.second++;
			}
		}
	}
}

int Partie::nombre_pas_restants(const Coordonnees& _coords,Donnees *_d)const{
	QPair<QPair<PokemonUtilisateur,PokemonUtilisateur>,int> valeur_=pokemon_pension.valeur(_coords);
	QPair<PokemonUtilisateur,PokemonUtilisateur> couple_=valeur_.first;
	FichePokemon *f_pk_1_=_d->val_pokedex().valeur(couple_.first.n_pk());
	FichePokemon *f_pk_2_=_d->val_pokedex().valeur(couple_.second.n_pk());
	if(f_pk_1_->b_ev()==f_pk_2_->b_ev()){
		return 256-valeur_.second;
	}
	return 1024-valeur_.second;
}

bool Partie::possibilite_de_recuperer_oeuf(const Coordonnees& _coords,Donnees *_d)const{
	QPair<QPair<PokemonUtilisateur,PokemonUtilisateur>,int> valeur_=pokemon_pension.valeur(_coords);
	QPair<PokemonUtilisateur,PokemonUtilisateur> couple_=valeur_.first;
	if(couple_.first.n_pk()==""){
		return false;
	}
	FichePokemon *f_pk_1_=_d->val_pokedex().valeur(couple_.first.n_pk());
	FichePokemon *f_pk_2_=_d->val_pokedex().valeur(couple_.second.n_pk());
	if(f_pk_1_->b_ev()==f_pk_2_->b_ev()){
		return valeur_.second>=256;
	}
	return valeur_.second>=1024;
}

OeufPokemon Partie::oeuf_produit(const Coordonnees& _coords,Donnees *_d)const{
	QPair<PokemonUtilisateur,PokemonUtilisateur> couple_=pokemon_pension.valeur(_coords).first;
	if(couple_.first.genre_pk()=="FEMELLE"){
		OeufPokemon(couple_.first.n_pk(),_d);
	}
	if(couple_.first.genre_pk()=="MALE"&&couple_.second.genre_pk()=="FEMELLE"){
		OeufPokemon(couple_.second.n_pk(),_d);
	}
	return OeufPokemon(couple_.first.n_pk(),_d);
}

void Partie::prendre_oeuf_produit(const Coordonnees& _coords){
	pokemon_pension.valeur(_coords).second=0;
}

HashMap<QPair<Coordonnees,int>,bool>& Partie::r_dresseurs_battus(){
	return dresseurs_battus;
}

uchar Partie::deplacement(const QPair<int,int>& _direction,QPair<int,int>& _coords_muret,QPair<int,int>& _deplacement,Donnees* _d){
	augmenter_pas_vers_ponte();
	if(_direction!=orientation_utilisateur){
		orientation_utilisateur=_direction;
		if(!ligue){
			Coordonnees voisin_=_d->tuile_voisine(coordonnees_utilisateur,_direction,ligue);
			if(voisin_==Coordonnees()){
				return Partie::RIEN;
			}
			int lieu_v_=voisin_.lieu();
			int plateau_v_=voisin_.plateau();
			QPair<int,int> environnement_v_=voisin_.coords_environnement();
			QPair<int,int> tuile_v_=voisin_.coords_tuile();
			Environnement *env_=_d->val_lieux().valeur(lieu_v_)->plateau(plateau_v_)->environnement(environnement_v_);
			if(env_->contient_centre_poke(tuile_v_)){
				return Partie::SOIN_PK;
			}
			if(env_->contient_echange_poke_boites(tuile_v_)){
				return Partie::ECH_BOITE;
			}
			if(env_->contient_lieu_fossile(tuile_v_)){
				return Partie::FOSSILE;
			}
			if(env_->contient_pension(tuile_v_)){
				return Partie::PENSION;
			}
			if(env_->contient_move_tutor(tuile_v_)){
				return Partie::MOVE_TUTORS;
			}
			if(env_->coords_lieux_dons_pokemon().contains(tuile_v_)&&!pokemon_pris.valeur(voisin_)){
				return Partie::DON_PK;
			}
			if(env_->coords_objets_donnes_ramasses().contains(tuile_v_)){
				return Partie::OBJ_RAMAS;
			}
			if(env_->coords_achat_objets().contains(tuile_v_)){
				return Partie::ACHATS;
			}
			if(env_->coords_achat_ct().contains(tuile_v_)){
				return Partie::ACHATS_CT;
			}
			if(env_->coords_don_cs().contains(tuile_v_)){
				return Partie::DON_CS;
			}
			if(env_->coords_objets().contains(tuile_v_)){
				return Partie::DON_OBJET;
			}
			if(env_->coords_pokemon_legendaire().contains(tuile_v_)&&!pokemon_pris.valeur(voisin_)){
				return Partie::PK_LEG;
			}
			if(env_->coords_autres_persos().contains(tuile_v_)){
				Dresseur1 *dresseur_=qobject_cast<Dresseur1*>(env_->perso(tuile_v_));
				bool battu_=true;
				int nb_=0;
				typedef QPair<Coordonnees,int> DresseurNb;
				foreach(DresseurNb d,dresseurs_battus.cles()){
					if(d.first==voisin_){
						if(!dresseurs_battus.valeur(DresseurNb(d.first,nb_))){
							battu_=false;
							break;
						}
						nb_++;
					}
				}
				if(dresseur_&&!battu_){
					return Partie::DRESSEUR;
				}
				return Partie::PERSONNAGE;
			}
			if(env_->peut_etre_une_zone_de_peche()){
				return Partie::PECHE;
			}
		}
		return Partie::RIEN;
	}
	Coordonnees obstacle_detruit_;
	QPair<Coordonnees,Coordonnees> coord_rocher_;
	_d->deplacement(*this,_direction,ligue,coordonnees_utilisateur,coord_rocher_,_coords_muret,obstacle_detruit_,_deplacement);
	if(arbres_coupes.cles().contains(obstacle_detruit_)){
		arbres_coupes.valeur(obstacle_detruit_)=true;
	}else if(rochers_detruits.cles().contains(obstacle_detruit_)){
		rochers_detruits.valeur(obstacle_detruit_)=true;
	}else if(tourbillons_siphones.cles().contains(obstacle_detruit_)){
		tourbillons_siphones.valeur(obstacle_detruit_)=true;
	}
	Coordonnees voisin_=_d->tuile_voisine(coordonnees_utilisateur,_direction,ligue);
	if(coord_rocher_.first!=Coordonnees()){
		position_actuelle_rochers_deplacables.valeur(coord_rocher_.first)=coord_rocher_.second;
	}
	utilisateur.deplacement(Taux(_deplacement.first).absolu()+Taux(_deplacement.second).absolu(),_d,commentaire);
	int lieu_v_=voisin_.lieu();
	int plateau_v_=voisin_.plateau();
	QPair<int,int> environnement_v_=voisin_.coords_environnement();
	QPair<int,int> tuile_v_=voisin_.coords_tuile();
	int lieu_c_=coordonnees_utilisateur.lieu();
	int plateau_c_=coordonnees_utilisateur.plateau();
	QPair<int,int> environnement_c_=coordonnees_utilisateur.coords_environnement();
	if(!ligue){
		if(lieux_visites.cles().contains(lieu_c_)){
			lieux_visites.valeur(lieu_c_)=true;
		}
		Environnement *env_=_d->val_lieux().valeur(lieu_c_)->plateau(plateau_c_)->environnement(environnement_c_);
		//indice_periode indice_pas
		if(!difficultes.r_appar_alea()){
			if(env_->nb_pas_pour_appar()>0&&!utilisateur.repous_act()){
				if(indice_pas==env_->nb_pas_pour_appar()){
					QList<PokemonSauvage*> periode_=env_->apparition_p_pok();
					bool existe_leg_=false;
					foreach(PokemonSauvage *p,periode_){
						if(utilisateur.present_pk(p->n_pk())){
							FichePokemon *f_pk_=_d->val_pokedex().valeur(p->n_pk());
							if(f_pk_->rep_genr()=="<LEG>"){
								existe_leg_=true;
								break;
							}
						}
					}
					if(existe_leg_){
						periode_=env_->apparition_p_sans_leg_pok();
					}
					elements_combat=ElementsCombat(utilisateur,difficultes,periode_[indice_periode],_d);
					if(indice_periode+1==(uint)periode_.size()){
						indice_periode=0;
					}else{
						indice_periode++;
					}
					indice_pas=0;
					return Partie::COMBAT_PK_SAUV;
				}
				indice_pas++;
			}else{
				indice_pas=0;
				indice_periode=0;
			}
		}else if(!utilisateur.repous_act()){
			indice_periode=0;
			indice_pas=0;
			QList<PokemonSauvage*> periode_=env_->apparition_p_pok();
			bool existe_leg_=false;
			foreach(PokemonSauvage *p,periode_){
				if(utilisateur.present_pk(p->n_pk())){
					FichePokemon *f_pk_=_d->val_pokedex().valeur(p->n_pk());
					if(f_pk_->rep_genr()=="<LEG>"){
						existe_leg_=true;
						break;
					}
				}
			}
			PokemonSauvage* pk_alea_=NULL;
			if(existe_leg_){
				pk_alea_=env_->apparition_a_sans_leg_pok().tirage();
			}else{
				pk_alea_=env_->apparition_a_pok().tirage();
			}
			if(pk_alea_->n_pk()!=""){
				elements_combat=ElementsCombat(utilisateur,difficultes,pk_alea_,_d);
				return Partie::COMBAT_PK_SAUV;
			}
		}
		if(voisin_!=Coordonnees()){
			env_=_d->val_lieux().valeur(lieu_v_)->plateau(plateau_v_)->environnement(environnement_v_);
			if(env_->contient_centre_poke(tuile_v_)){
				return Partie::SOIN_PK;
			}
			if(env_->contient_echange_poke_boites(tuile_v_)){
				return Partie::ECH_BOITE;
			}
			if(env_->contient_lieu_fossile(tuile_v_)){
				return Partie::FOSSILE;
			}
			if(env_->contient_pension(tuile_v_)){
				return Partie::PENSION;
			}
			if(env_->contient_move_tutor(tuile_v_)){
				return Partie::MOVE_TUTORS;
			}
			if(env_->coords_lieux_dons_pokemon().contains(tuile_v_)&&!pokemon_pris.valeur(voisin_)){
				return Partie::DON_PK;
			}
			if(env_->coords_objets_donnes_ramasses().contains(tuile_v_)){
				return Partie::OBJ_RAMAS;
			}
			if(env_->coords_achat_objets().contains(tuile_v_)){
				return Partie::ACHATS;
			}
			if(env_->coords_achat_ct().contains(tuile_v_)){
				return Partie::ACHATS_CT;
			}
			if(env_->coords_don_cs().contains(tuile_v_)){
				return Partie::DON_CS;
			}
			if(env_->coords_objets().contains(tuile_v_)){
				return Partie::DON_OBJET;
			}
			if(env_->coords_pokemon_legendaire().contains(tuile_v_)&&!pokemon_pris.valeur(voisin_)){
				return Partie::PK_LEG;
			}
			if(env_->coords_autres_persos().contains(tuile_v_)){
				Dresseur1 *dresseur_=qobject_cast<Dresseur1*>(env_->perso(tuile_v_));
				bool battu_=true;
				int nb_=0;
				typedef QPair<Coordonnees,int> DresseurNb;
				foreach(DresseurNb d,dresseurs_battus.cles()){
					if(d.first==voisin_){
						if(!dresseurs_battus.valeur(DresseurNb(d.first,nb_))){
							battu_=false;
							break;
						}
						nb_++;
					}
				}
				if(dresseur_&&!battu_){
					return Partie::DRESSEUR;
				}
				return Partie::PERSONNAGE;
			}
			if(env_->peut_etre_une_zone_de_peche()){
				return Partie::PECHE;
			}
		}
		return Partie::RIEN;
	}else{
		if(voisin_!=Coordonnees()){
			PlateauLigue *plateau_=_d->val_ligues().valeur(lieu_v_)->plateau(plateau_v_);
			QPair<int,int> coords_;
			coords_.first=voisin_.coords_environnement().first+voisin_.coords_tuile().first;
			coords_.second=voisin_.coords_environnement().second+voisin_.coords_tuile().second;
			if(plateau_->val_coords_dresseur()==coords_&&stade_ligue==plateau_v_){
				return Partie::DRESSEUR;
			}
			return Partie::PERSONNAGE;
		}
	}
	//r_appar_alea
	return Partie::RIEN;
}

ElementsCombat& Partie::combat(){
	return elements_combat;
}

bool Partie::partie_finie(Donnees* _d)const{
	bool attrape_=true;
	foreach(QString p,_d->val_pokedex().cles()){
		attrape_&=utilisateur.present_pk(p);
	}
	if(!attrape_){
		return false;
	}
	return ligues_deja_battues.size()==_d->val_ligues().total();
}

void Partie::serialiser(Flux& _out)const{
	_out<<utilisateur;
	//_out<<nom_rival;
	_out<<ligues_deja_battues;
	_out<<stade_ligue;
	_out<<dresseurs_battus;
	_out<<objets_ramasses;
	_out<<arbres_coupes;
	_out<<rochers_detruits;
	_out<<position_actuelle_rochers_deplacables;
	_out<<tourbillons_siphones;
	_out<<pokemon_pris;
	_out<<objets_ramasses;
	_out<<ligue;
	_out<<coordonnees_utilisateur;
	_out<<orientation_utilisateur;
	_out<<dernier_ctre_poke_vis;
	_out<<pokemon_pension;
	_out<<elements_combat;
	_out<<difficultes;
	_out<<total_captures;
	_out<<noms_boites;
	_out<<indice_periode;
	_out<<indice_pas;
	_out<<indice_periode_peche;
	_out<<lieux_visites;
}

void Partie::deserialiser(Flux& _in){
	_in>>utilisateur;
	//_in>>nom_rival;
	_in>>ligues_deja_battues;
	_in>>stade_ligue;
	_in>>dresseurs_battus;
	_in>>objets_ramasses;
	_in>>arbres_coupes;
	_in>>rochers_detruits;
	_in>>position_actuelle_rochers_deplacables;
	_in>>tourbillons_siphones;
	_in>>pokemon_pris;
	_in>>objets_ramasses;
	_in>>ligue;
	_in>>coordonnees_utilisateur;
	_in>>orientation_utilisateur;
	_in>>dernier_ctre_poke_vis;
	_in>>pokemon_pension;
	_in>>elements_combat;
	_in>>difficultes;
	_in>>total_captures;
	_in>>noms_boites;
	_in>>indice_periode;
	_in>>indice_pas;
	_in>>indice_periode_peche;
	_in>>lieux_visites;
}

Flux & operator <<(Flux& out,const Partie& _Partie){
	_Partie.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Partie& _Partie){
	_Partie.deserialiser(in);
	return in;
}


