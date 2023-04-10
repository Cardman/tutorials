#include "ihm/hors_combat/scenehorscombat.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "serialisable/partie/partie.h"
#include <QPaintEvent>
#include <QPainter>

SceneHorsCombat::SceneHorsCombat(Donnees* _d){
	//lieu=NULL;
	int largeur_ecran_=(int)(_d->constante_numerique("ESPACE_GAUCHE_ECRAN")+Taux(1)+_d->constante_numerique("ESPACE_DROITE_ECRAN"));
	int hauteur_ecran_=(int)(_d->constante_numerique("ESPACE_HAUT_ECRAN")+Taux(1)+_d->constante_numerique("ESPACE_BAS_ECRAN"));
	coords_heros.first=_d->constante_numerique("ESPACE_GAUCHE_ECRAN");
	coords_heros.second=_d->constante_numerique("ESPACE_HAUT_ECRAN");
	setFixedSize(largeur_ecran_*32,hauteur_ecran_*32);
}

void SceneHorsCombat::maj_orientation(const QPair<int,int>& _or){
	orientation_heros=_or;
}

void SceneHorsCombat::maj_tuiles(const Partie& _partie,const Coordonnees& _coords,bool _ligue,Donnees* _d){
	tuiles=_d->intersection_avec_ecran(_coords,_ligue);
	replacer(_partie,_ligue,_d);
	heros=_d->val_miniatures_heros().valeur(_partie.utilis().sexe());
}

void SceneHorsCombat::maj_camera(const Partie& _partie,const QPair<int,int>& _direction,bool _ligue,Donnees* _d){
	_d->deplacer_camera(tuiles,_direction,_ligue);
	replacer(_partie,_ligue,_d);
}

void SceneHorsCombat::replacer(const Partie& _partie,bool _ligue,Donnees* _d){
	HashMap<QString,QImage> tuiles_imgs_=_d->val_tuiles_importees();
	HashMap<QString,QImage> perso_micro_=_d->val_dresseurs_micros();
	HashMap<int,QImage> miniatures_=_d->val_miniatures();
	HashMap<QString,QImage> objets_=_d->val_images_objets();
	HashMap<QString,QImage> arbres_=_d->val_arbres();
	QList<QString> cles_arbres_=arbres_.cles();
	HashMap<QString,QImage> rochers_d_=_d->val_rochers_destructibles();
	QList<QString> cles_rochers_d_=rochers_d_.cles();
	HashMap<QString,QImage> rochers_a_=_d->val_rochers_amovibles();
	QList<QString> cles_rochers_a_=rochers_a_.cles();
	HashMap<QString,QImage> tourbillons_=_d->val_tourbillons();
	QList<QString> cles_tourbillons_=tourbillons_.cles();
	typedef QPair<int,int> Coin;
	foreach(Coin c,tuiles.cles()){
		Coordonnees coords_=tuiles.valeur(c);
		if(coords_==Coordonnees()){
			tuiles_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
			/*perso_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
			persos.ajouter_cle_valeur(c,false);*/
			premier_plan_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
			premier_plan.ajouter_cle_valeur(c,false);
			continue;
		}
		Tuile *t_;
		if(_ligue){
			premier_plan_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
			premier_plan.ajouter_cle_valeur(c,false);
			PlateauLigue *pl_=_d->val_ligues().valeur(coords_.lieu())->plateau(coords_.plateau());
			QPair<int,int> coords_dr_l_=pl_->val_coords_dresseur();
			if(coords_dr_l_.first==coords_.coords_environnement().first+coords_.coords_tuile().first){
				if(coords_dr_l_.second==coords_.coords_environnement().second+coords_.coords_tuile().second){
					premier_plan_g.ajouter_cle_valeur(c,perso_micro_.valeur(pl_->val_dresseur_ligue()->miniature()));
					premier_plan.ajouter_cle_valeur(c,true);
				}else{
					premier_plan_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
					premier_plan.ajouter_cle_valeur(c,false);
				}
			}else{
				premier_plan_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
				premier_plan.ajouter_cle_valeur(c,false);
			}
			t_=pl_->environnement(coords_.coords_environnement())->tuile(coords_.coords_tuile());
		}else{
			Plateau *pl_=_d->val_lieux().valeur(coords_.lieu())->plateau(coords_.plateau());
			Environnement *env_=pl_->environnement(coords_.coords_environnement());
			Personnage *perso_=env_->perso(coords_.coords_tuile());
			/*if(perso_){
				perso_g.ajouter_cle_valeur(c,perso_micro_.valeur(perso_->miniature()));
				persos.ajouter_cle_valeur(c,true);
			}else{
				perso_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
				persos.ajouter_cle_valeur(c,false);
			}*/
			if(env_->coords_pokemon_legendaire().contains(coords_.coords_tuile())){
				if(!_partie.element_absent(coords_)){
					QString nom_pk_leg_=env_->pokemon_legendaire(coords_.coords_tuile())->n_pk();
					premier_plan_g.ajouter_cle_valeur(c,miniatures_.valeur(_d->val_pokedex().valeur(nom_pk_leg_)->num()));
					premier_plan.ajouter_cle_valeur(c,true);
				}else{
					premier_plan_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
					premier_plan.ajouter_cle_valeur(c,false);
				}
			/*}else if(env_->coords_objets_donnes_ramasses().contains(coords_.coords_tuile())){
				if(!_partie.element_absent(coords_)){
					QString nom_objet_=env_->objet_donne_ramasse(coords_.coords_tuile());
					pk_leg_g.ajouter_cle_valeur(c,objets_.valeur(nom_objet_));
					pks_leg.ajouter_cle_valeur(c,true);
				}else{
					pk_leg_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
					pks_leg.ajouter_cle_valeur(c,false);
				}*/
			}else if(env_->coords_objets().contains(coords_.coords_tuile())){
				if(!_partie.element_absent(coords_)){
					QString nom_objet_=env_->objet(coords_.coords_tuile());
					premier_plan_g.ajouter_cle_valeur(c,objets_.valeur(nom_objet_));
					premier_plan.ajouter_cle_valeur(c,true);
				}else{
					premier_plan_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
					premier_plan.ajouter_cle_valeur(c,false);
				}
			}else if(env_->coords_lieux_dons_pokemon().contains(coords_.coords_tuile())){
				if(!_partie.element_absent(coords_)){
					premier_plan_g.ajouter_cle_valeur(c,_d->val_pk_trouve());
					premier_plan.ajouter_cle_valeur(c,true);
				}else{
					premier_plan_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
					premier_plan.ajouter_cle_valeur(c,false);
				}
			}else if(env_->contient_echange_poke_boites(coords_.coords_tuile())){
				premier_plan_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("autres_obstacles/ordi_echange0_0_"));
				premier_plan.ajouter_cle_valeur(c,true);
			}else if(_partie.arbres_non_coupes().contains(coords_)){
				premier_plan_g.ajouter_cle_valeur(c,arbres_.valeur(cles_arbres_[0]));
				premier_plan.ajouter_cle_valeur(c,true);
			}else if(_partie.rochers_non_detruits().contains(coords_)){
				premier_plan_g.ajouter_cle_valeur(c,rochers_d_.valeur(cles_rochers_d_[0]));
				premier_plan.ajouter_cle_valeur(c,true);
			}else if(_partie.tourbillon_non_siphones().contains(coords_)){
				premier_plan_g.ajouter_cle_valeur(c,tourbillons_.valeur(cles_tourbillons_[0]));
				premier_plan.ajouter_cle_valeur(c,true);
			}else if(!_partie.rocher_a_position(coords_).isEmpty()){
				premier_plan_g.ajouter_cle_valeur(c,rochers_a_.valeur(cles_rochers_a_[0]));
				premier_plan.ajouter_cle_valeur(c,true);
			}else{
				premier_plan_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur("ihm/VIDE"));
				premier_plan.ajouter_cle_valeur(c,false);
			}//val_pk_trouve()coords_lieux_dons_pokemon()
			if(perso_){
				premier_plan_g.ajouter_cle_valeur(c,perso_micro_.valeur(perso_->miniature()));
				premier_plan.ajouter_cle_valeur(c,true);
			}
			t_=env_->tuile(coords_.coords_tuile());
		}
		tuiles_g.ajouter_cle_valeur(c,tuiles_imgs_.valeur(t_->val_nom_image()));
	}
}

void SceneHorsCombat::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	typedef QPair<int,int> Coin;
	foreach(Coin c,tuiles_g.cles()){
		QPoint coin_=QPoint(c.first*32,c.second*32);
		paint_.drawImage(coin_,tuiles_g.valeur(c));
		if(premier_plan.valeur(c)){
			paint_.drawImage(coin_,premier_plan_g.valeur(c));
		}
		/*if(persos.valeur(c)){
			paint_.drawImage(coin_,perso_g.valeur(c));
		}*/
	}
	/*int largeur_ecran_=5;
	int hauteur_ecran_=5;
	paint_.fillRect(largeur_ecran_*32,hauteur_ecran_*32,32,32,QColor(0,0,0,255));*/
	if(orientation_heros.first==0){
		if(orientation_heros.second==-1){
			//HAUT
			paint_.translate(QPoint(coords_heros.first*32+16,coords_heros.second*32+16));
			paint_.rotate(180);
			paint_.translate(QPoint(-coords_heros.first*32-16,-coords_heros.second*32-16));
		}
	}else if(orientation_heros.first==-1){
		//GAUCHE
		paint_.translate(QPoint(coords_heros.first*32+16,coords_heros.second*32+16));
		paint_.rotate(90);
		paint_.translate(QPoint(-coords_heros.first*32-16,-coords_heros.second*32-16));
	}else{
		//DROITE
		paint_.translate(QPoint(coords_heros.first*32+16,coords_heros.second*32+16));
		paint_.rotate(-90);
		paint_.translate(QPoint(-coords_heros.first*32-16,-coords_heros.second*32-16));
	}
	//paint_.rotate();
	paint_.drawImage(QPoint(coords_heros.first*32,coords_heros.second*32),heros);
}
