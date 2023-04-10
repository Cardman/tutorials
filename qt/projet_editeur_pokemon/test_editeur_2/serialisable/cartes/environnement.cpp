#include "serialisable/cartes/environnement.h"
#include "base_donnees/import.h"
#include "base_donnees/pokemon/fichepokemon.h"
const QString Environnement::_canne_="CANNE";
const QString Environnement::_super_canne_="SUPER_CANNE";
const QString Environnement::_mega_canne_="MEGA_CANNE";
const QString Environnement::_roche_="ROCHE";
const QString Environnement::_herbe_="HERBE";
const QString Environnement::_route_="ROUTE";
const QString Environnement::_eau_="EAU";
const QString Environnement::_batiment_="BATIMENT";
const QString Environnement::_neige_="NEIGE";
const QString Environnement::_glace_="GLACE";
const QString Environnement::_cascade_="CASCADE";

Environnement::Environnement(){
	apparition_per_pok_peche.ajouter_cle_valeur(_canne_,QList<Pokemon>());
	apparition_per_pok_peche.ajouter_cle_valeur(_super_canne_,QList<Pokemon>());
	apparition_per_pok_peche.ajouter_cle_valeur(_mega_canne_,QList<Pokemon>());
	largeur=1;
	muret=QPair<int,int>(0,0);
}

Environnement::Environnement(int _largeur,int _hauteur,const QString& _type_environnement){
	largeur=_largeur;
	type_environnement=_type_environnement;
	int nb_tuiles_=_largeur*_hauteur;
	for(int i=0;i<nb_tuiles_;i++){
		tuiles<<Tuile();
		*tuiles.last().adr_nom_image()="ihm/"+_type_environnement;
	}
	apparition_per_pok_peche.ajouter_cle_valeur(_canne_,QList<Pokemon>());
	apparition_per_pok_peche.ajouter_cle_valeur(_super_canne_,QList<Pokemon>());
	apparition_per_pok_peche.ajouter_cle_valeur(_mega_canne_,QList<Pokemon>());
	nb_pas_moyen_pour_appar=1;
	muret=QPair<int,int>(0,0);
}

bool Environnement::egal(const Environnement& _autre)const{
	bool egal_;
	egal_=largeur==_autre.largeur;
	egal_&=type_environnement==_autre.type_environnement;
	egal_&=tuiles==_autre.tuiles;
	egal_&=champions==_autre.champions;
	egal_&=dresseurs1==_autre.dresseurs1;
	egal_&=autres_persos==_autre.autres_persos;
	egal_&=objets==_autre.objets;
	egal_&=centres_poke.size()==_autre.centres_poke.size();
	if(!egal_){
		return false;
	}
	typedef QPair<int,int> Origine;
	foreach(Origine o,centres_poke){
		if(!_autre.centres_poke.contains(o)){
			return false;
		}
	}
	egal_&=echanges_poke_boites.size()==_autre.echanges_poke_boites.size();
	if(!egal_){
		return false;
	}
	foreach(Origine o,echanges_poke_boites){
		if(!_autre.echanges_poke_boites.contains(o)){
			return false;
		}
	}
	egal_&=pensions.size()==_autre.pensions.size();
	if(!egal_){
		return false;
	}
	foreach(Origine o,pensions){
		if(!_autre.pensions.contains(o)){
			return false;
		}
	}
	egal_&=move_tutors.size()==_autre.move_tutors.size();
	if(!egal_){
		return false;
	}
	foreach(Origine o,move_tutors){
		if(!_autre.move_tutors.contains(o)){
			return false;
		}
	}
	egal_&=lieu_faire_revivre_fossile.size()==_autre.lieu_faire_revivre_fossile.size();
	if(!egal_){
		return false;
	}
	foreach(Origine o,lieu_faire_revivre_fossile){
		if(!_autre.lieu_faire_revivre_fossile.contains(o)){
			return false;
		}
	}
	egal_&=objets_donnes_ramasses==_autre.objets_donnes_ramasses;
	egal_&=lieux_dons_pokemon==_autre.lieux_dons_pokemon;
	egal_&=achats_objets==_autre.achats_objets;
	egal_&=achats_ct==_autre.achats_ct;
	egal_&=dons_cs==_autre.dons_cs;
	egal_&=apparition_per_pok==_autre.apparition_per_pok;
	egal_&=nb_pas_moyen_pour_appar==_autre.nb_pas_moyen_pour_appar;
	egal_&=apparition_per_pok_peche==_autre.apparition_per_pok_peche;
	egal_&=pokemon_legendaires==_autre.pokemon_legendaires;
	egal_&=muret==_autre.muret;
	//pensions
	return egal_;
}

bool Environnement::existe(const QPair<int,int>& _id)const{
	return _id.first+largeur*_id.second<tuiles.size()&&_id.first+largeur*_id.second>=0;
}

bool Environnement::est_vide(const QPair<int,int>& _id)const{
	if(_id.first+largeur*_id.second>=tuiles.size()||_id.first+largeur*_id.second<0){
		return false;
	}
	Tuile t_=tuiles[_id.first+largeur*_id.second];
	if(t_.adr_nom_image_obst()->first!=""){
		return false;
	}
	if(champions.cles().contains(_id)){
		return false;
	}
	if(dresseurs1.cles().contains(_id)){
		return false;
	}
	if(autres_persos.cles().contains(_id)){
		return false;
	}
	if(objets.cles().contains(_id)){
		return false;
	}
	if(pokemon_legendaires.cles().contains(_id)){
		return false;
	}
	if(centres_poke.contains(_id)){
		return false;
	}
	if(echanges_poke_boites.contains(_id)){
		return false;
	}
	if(pensions.contains(_id)){
		return false;
	}
	if(move_tutors.contains(_id)){
		return false;
	}
	if(lieu_faire_revivre_fossile.contains(_id)){
		return false;
	}
	if(objets_donnes_ramasses.cles().contains(_id)){
		return false;
	}
	if(lieux_dons_pokemon.cles().contains(_id)){
		return false;
	}
	if(achats_objets.cles().contains(_id)){
		return false;
	}
	if(achats_ct.cles().contains(_id)){
		return false;
	}
	if(dons_cs.cles().contains(_id)){
		return false;
	}
	return true;
}

bool Environnement::peut_etre_une_zone_de_peche()const{
	return type_environnement==_eau_||type_environnement==_cascade_;
}

bool Environnement::peut_etre_une_zone_de_peche(const QString& _n_type_env)const{
	if(_n_type_env==_eau_||_n_type_env==_cascade_){
		return true;
	}
	bool poss_=apparition_per_pok_peche.valeur(_canne_).isEmpty();
	poss_&=apparition_per_pok_peche.valeur(_super_canne_).isEmpty();
	poss_&=apparition_per_pok_peche.valeur(_mega_canne_).isEmpty();
	return poss_;
}

void Environnement::modifier_champion(const QPair<int,int>& _coords_ajout,const Champion& _champion){
	supprimer_elements(_coords_ajout);
	champions.ajouter_cle_valeur(_coords_ajout,_champion);
}

Champion *Environnement::champion(const QPair<int,int>& _coords_ajout,bool& _n_instance){
	return champions.valeur(_coords_ajout,_n_instance);
}

QList<QPair<int,int> > Environnement::coords_champions()const{
	return champions.cles();
}

void Environnement::modifier_dresseur(const QPair<int,int>& _coords_ajout,const Dresseur1& _dresseur){
	supprimer_elements(_coords_ajout);
	dresseurs1.ajouter_cle_valeur(_coords_ajout,_dresseur);
}

Dresseur1 *Environnement::dresseur(const QPair<int,int>& _coords_ajout,bool& _n_instance){
	return dresseurs1.valeur(_coords_ajout,_n_instance);
}

QList<QPair<int,int> > Environnement::coords_dresseurs()const{
	return dresseurs1.cles();
}

void Environnement::modifier_personnage(const QPair<int,int>& _coords_ajout,const Personnage& _personnage){
	supprimer_elements(_coords_ajout);
	autres_persos.ajouter_cle_valeur(_coords_ajout,_personnage);
}

Personnage *Environnement::personnage(const QPair<int,int>& _coords_ajout,bool& _n_instance){
	return autres_persos.valeur(_coords_ajout,_n_instance);
}

QList<QPair<int,int> > Environnement::coords_autres_persos()const{
	return autres_persos.cles();
}

/*void Environnement::modifier_obstacle(const QPair<int,int>& _coords_ajout,const QString& _nature_obstacle){
	supprimer_elements(_coords_ajout)
	if(_nature_obstacle==Tuile::_arbre_){
		arbres<<_coords_ajout
	}else if(_nature_obstacle==Tuile::_rochers_dest_){
		rochers_destructibles<<_coords_ajout
	}else if(_nature_obstacle==Tuile::_rochers_amov_){
		rochers_deplacables<<_coords_ajout
	}else{
		tourbillons<<_coords_ajout
	}
}

QPair<int,int> *Environnement::obstacle(int _indice,const QString& _nature_obstacle){
	if(_nature_obstacle==Tuile::_arbre_){
		return &(arbres[_indice])
	}else if(_nature_obstacle==Tuile::_rochers_dest_){
		return &(rochers_destructibles[_indice])
	}else if(_nature_obstacle==Tuile::_rochers_amov_){
		return &(rochers_deplacables[_indice])
	}else{
		return &(tourbillons[_indice])
	}
}

int Environnement::nb_obstacle(const QString& _nature_obstacle)const{
	if(_nature_obstacle==Tuile::_arbre_){
		return arbres.size()
	}else if(_nature_obstacle==Tuile::_rochers_dest_){
		return rochers_destructibles.size()
	}else if(_nature_obstacle==Tuile::_rochers_amov_){
		return rochers_deplacables.size()
	}else{
		return tourbillons.size()
	}
}
*/
void Environnement::modifier_objet(const QPair<int,int>& _coords_ajout,const QString& _nom_objet){
	supprimer_elements(_coords_ajout,false);
	objets.ajouter_cle_valeur(_coords_ajout,_nom_objet);
}

QString *Environnement::objet(const QPair<int,int>& _coords_ajout,bool& _n_instance){
	return objets.valeur(_coords_ajout,_n_instance);
}

QList<QPair<int,int> > Environnement::coords_objets()const{
	return objets.cles();
}

void Environnement::modifier_pokemon_legendaire(const QPair<int,int>& _coords,const Pokemon& _pokemon){
	supprimer_elements(_coords);
	pokemon_legendaires.ajouter_cle_valeur(_coords,_pokemon);
}

Pokemon *Environnement::pokemon_legendaire(const QPair<int,int>& _coords_ajout,bool& _n_instance){
	return pokemon_legendaires.valeur(_coords_ajout,_n_instance);
}

QList<QPair<int,int> > Environnement::coords_pokemon_legendaire()const{
	return pokemon_legendaires.cles();
}

Tuile* Environnement::tuile(const QPair<int,int>& _coords_tuile){
	return &(tuiles[_coords_tuile.first+largeur*_coords_tuile.second]);
}

void Environnement::decaler_ligne_elements(int _indice,int _sens){
	//typedef QPair<int,int> Position
	decaler_hashmap<Champion>(champions,QPair<int,int>(0,_sens));
	decaler_hashmap<Dresseur1>(dresseurs1,QPair<int,int>(0,_sens));
	decaler_hashmap<Personnage>(autres_persos,QPair<int,int>(0,_sens));
	decaler_hashmap<QString>(objets,QPair<int,int>(0,_sens));
	decaler_hashmap<QStringList>(achats_objets,QPair<int,int>(0,_sens));
	decaler_hashmap<QList<uchar> >(achats_ct,QPair<int,int>(0,_sens));
	decaler_hashmap<Pokemon>(pokemon_legendaires,QPair<int,int>(0,_sens));
	decaler_hashmap<Pokemon>(lieux_dons_pokemon,QPair<int,int>(0,_sens));
	decaler_hashmap<QString>(objets_donnes_ramasses,QPair<int,int>(0,_sens));
	//
	/*QList<Position> cles_=champions.cles()
	foreach(Position p,cles_){
		if(p.second>=_indice){
			Champion ch_=champions.valeur(p)
			champions.supprimer_cle_valeur(p)
			champions.ajouter_cle_valeur(Position(p.first,p.second+_sens),ch_)
		}
	}
	cles_=dresseurs1.cles()
	foreach(Position p,cles_){
		if(p.second>=_indice){
			Dresseur1 dr_=dresseurs1.valeur(p)
			dresseurs1.supprimer_cle_valeur(p)
			dresseurs1.ajouter_cle_valeur(Position(p.first,p.second+_sens),dr_)
		}
	}
	cles_=autres_persos.cles()
	foreach(Position p,cles_){
		if(p.second>=_indice){
			Personnage perso_=autres_persos.valeur(p)
			autres_persos.supprimer_cle_valeur(p)
			autres_persos.ajouter_cle_valeur(Position(p.first,p.second+_sens),perso_)
		}
	}
	cles_=objets.cles()
	foreach(Position p,cles_){
		if(p.second>=_indice){
			QString objet_=objets.valeur(p)
			objets.supprimer_cle_valeur(p)
			objets.ajouter_cle_valeur(Position(p.first,p.second+_sens),objet_)
		}
	}*/
	int nb_obst_;//=arbres.size()
	/*for(int i=0;i<nb_obst_;i++){
		if(arbres[i].second>=_indice){
			arbres[i].second+=_sens
		}
	}
	nb_obst_=rochers_destructibles.size()
	for(int i=0;i<nb_obst_;i++){
		if(rochers_destructibles[i].second>=_indice){
			rochers_destructibles[i].second+=_sens
		}
	}
	nb_obst_=rochers_deplacables.size()
	for(int i=0;i<nb_obst_;i++){
		if(rochers_deplacables[i].second>=_indice){
			rochers_deplacables[i].second+=_sens
		}
	}
	nb_obst_=tourbillons.size()
	for(int i=0;i<nb_obst_;i++){
		if(tourbillons[i].second>=_indice){
			tourbillons[i].second+=_sens
		}
	}*/
	nb_obst_=centres_poke.size();
	for(int i=0;i<nb_obst_;i++){
		if(centres_poke[i].second>=_indice){
			centres_poke[i].second+=_sens;
		}
	}
	nb_obst_=echanges_poke_boites.size();
	for(int i=0;i<nb_obst_;i++){
		if(echanges_poke_boites[i].second>=_indice){
			echanges_poke_boites[i].second+=_sens;
		}
	}
	nb_obst_=pensions.size();
	for(int i=0;i<nb_obst_;i++){
		if(pensions[i].second>=_indice){
			pensions[i].second+=_sens;
		}
	}
	nb_obst_=move_tutors.size();
	for(int i=0;i<nb_obst_;i++){
		if(move_tutors[i].second>=_indice){
			move_tutors[i].second+=_sens;
		}
	}
	nb_obst_=lieu_faire_revivre_fossile.size();
	for(int i=0;i<nb_obst_;i++){
		if(lieu_faire_revivre_fossile[i].second>=_indice){
			lieu_faire_revivre_fossile[i].second+=_sens;
		}
	}
	//TODO a faire disparaitre
	/*nb_obst_=objets_donnes_ramasses.size()
	for(int i=0;i<nb_obst_;i++){
		if(objets_donnes_ramasses[i].first.second>=_indice){
			objets_donnes_ramasses[i].first.second+=_sens
		}
	}
	nb_obst_=lieux_dons_pokemon.size()
	for(int i=0;i<nb_obst_;i++){
		if(lieux_dons_pokemon[i].first.second>=_indice){
			lieux_dons_pokemon[i].first.second+=_sens
		}
	}*/
	/*cles_=achats_objets.cles()
	foreach(Position p,cles_){
		if(p.second>=_indice){
			QStringList obj_=achats_objets.valeur(p)
			achats_objets.supprimer_cle_valeur(p)
			achats_objets.ajouter_cle_valeur(Position(p.first,p.second+_sens),obj_)
		}
	}
	cles_=achats_ct.cles()
	foreach(Position p,cles_){
		if(p.second>=_indice){
			QList<uchar> obj_=achats_ct.valeur(p)
			achats_ct.supprimer_cle_valeur(p)
			achats_ct.ajouter_cle_valeur(Position(p.first,p.second+_sens),obj_)
		}
	}
	cles_=pokemon_legendaires.cles()
	foreach(Position p,cles_){
		if(p.second>=_indice){
			Pokemon pk_=pokemon_legendaires.valeur(p)
			pokemon_legendaires.supprimer_cle_valeur(p)
			pokemon_legendaires.ajouter_cle_valeur(Position(p.first,p.second+_sens),pk_)
		}
	}*/
}

void Environnement::decaler_colonne_elements(int _indice,int _sens){
	//typedef QPair<int,int> Position
	decaler_hashmap<Champion>(champions,QPair<int,int>(_sens,0));
	decaler_hashmap<Dresseur1>(dresseurs1,QPair<int,int>(_sens,0));
	decaler_hashmap<Personnage>(autres_persos,QPair<int,int>(_sens,0));
	decaler_hashmap<QString>(objets,QPair<int,int>(_sens,0));
	decaler_hashmap<QStringList>(achats_objets,QPair<int,int>(_sens,0));
	decaler_hashmap<QList<uchar> >(achats_ct,QPair<int,int>(_sens,0));
	decaler_hashmap<Pokemon>(pokemon_legendaires,QPair<int,int>(_sens,0));
	decaler_hashmap<Pokemon>(lieux_dons_pokemon,QPair<int,int>(_sens,0));
	decaler_hashmap<QString>(objets_donnes_ramasses,QPair<int,int>(_sens,0));
	//QList<Position> cles_=champions.cles()
	/*foreach(Position p,cles_){
		if(p.first>=_indice){
			Champion ch_=champions.valeur(p)
			champions.supprimer_cle_valeur(p)
			champions.ajouter_cle_valeur(Position(p.first+_sens,p.second),ch_)
		}
	}
	cles_=dresseurs1.cles()
	foreach(Position p,cles_){
		if(p.first>=_indice){
			Dresseur1 dr_=dresseurs1.valeur(p)
			dresseurs1.supprimer_cle_valeur(p)
			dresseurs1.ajouter_cle_valeur(Position(p.first+_sens,p.second),dr_)
		}
	}
	cles_=autres_persos.cles()
	foreach(Position p,cles_){
		if(p.first>=_indice){
			Personnage perso_=autres_persos.valeur(p)
			autres_persos.supprimer_cle_valeur(p)
			autres_persos.ajouter_cle_valeur(Position(p.first+_sens,p.second),perso_)
		}
	}
	cles_=objets.cles()
	foreach(Position p,cles_){
		if(p.first>=_indice){
			QString objet_=objets.valeur(p)
			objets.supprimer_cle_valeur(p)
			objets.ajouter_cle_valeur(Position(p.first+_sens,p.second),objet_)
		}
	}*/
	int nb_obst_;//=arbres.size()
	/*for(int i=0;i<nb_obst_;i++){
		if(arbres[i].first>=_indice){
			arbres[i].first+=_sens
		}
	}
	nb_obst_=rochers_destructibles.size()
	for(int i=0;i<nb_obst_;i++){
		if(rochers_destructibles[i].first>=_indice){
			rochers_destructibles[i].first+=_sens
		}
	}
	nb_obst_=rochers_deplacables.size()
	for(int i=0;i<nb_obst_;i++){
		if(rochers_deplacables[i].first>=_indice){
			rochers_deplacables[i].first+=_sens
		}
	}
	nb_obst_=tourbillons.size()
	for(int i=0;i<nb_obst_;i++){
		if(tourbillons[i].first>=_indice){
			tourbillons[i].first+=_sens
		}
	}*/
	nb_obst_=centres_poke.size();
	for(int i=0;i<nb_obst_;i++){
		if(centres_poke[i].first>=_indice){
			centres_poke[i].first+=_sens;
		}
	}
	nb_obst_=echanges_poke_boites.size();
	for(int i=0;i<nb_obst_;i++){
		if(echanges_poke_boites[i].first>=_indice){
			echanges_poke_boites[i].first+=_sens;
		}
	}
	nb_obst_=pensions.size();
	for(int i=0;i<nb_obst_;i++){
		if(pensions[i].first>=_indice){
			pensions[i].first+=_sens;
		}
	}
	nb_obst_=move_tutors.size();
	for(int i=0;i<nb_obst_;i++){
		if(move_tutors[i].first>=_indice){
			move_tutors[i].first+=_sens;
		}
	}
	nb_obst_=lieu_faire_revivre_fossile.size();
	for(int i=0;i<nb_obst_;i++){
		if(lieu_faire_revivre_fossile[i].first>=_indice){
			lieu_faire_revivre_fossile[i].first+=_sens;
		}
	}
	//TODO a changer
	/*nb_obst_=objets_donnes_ramasses.size()
	for(int i=0;i<nb_obst_;i++){
		if(objets_donnes_ramasses[i].first.first>=_indice){
			objets_donnes_ramasses[i].first.first+=_sens
		}
	}
	nb_obst_=lieux_dons_pokemon.size()
	for(int i=0;i<nb_obst_;i++){
		if(lieux_dons_pokemon[i].first.first>=_indice){
			lieux_dons_pokemon[i].first.first+=_sens
		}
	}*/
	/*cles_=achats_objets.cles()
	foreach(Position p,cles_){
		if(p.first>=_indice){
			QStringList obj_=achats_objets.valeur(p)
			achats_objets.supprimer_cle_valeur(p)
			achats_objets.ajouter_cle_valeur(Position(p.first+_sens,p.second),obj_)
		}
	}
	cles_=achats_ct.cles()
	foreach(Position p,cles_){
		if(p.first>=_indice){
			QList<uchar> obj_=achats_ct.valeur(p)
			achats_ct.supprimer_cle_valeur(p)
			achats_ct.ajouter_cle_valeur(Position(p.first+_sens,p.second),obj_)
		}
	}
	cles_=pokemon_legendaires.cles()
	foreach(Position p,cles_){
		if(p.first>=_indice){
			Pokemon pk_=pokemon_legendaires.valeur(p)
			pokemon_legendaires.supprimer_cle_valeur(p)
			pokemon_legendaires.ajouter_cle_valeur(Position(p.first+_sens,p.second),pk_)
		}
	}*/
}

QPair<int,int> *Environnement::centre_poke(int _indice){
	return &(centres_poke[_indice]);
}

int Environnement::nb_centres_poke()const{
	return centres_poke.size();
}

bool Environnement::contient_centre_poke(const QPair<int,int>& _centre_poke){
	return centres_poke.contains(_centre_poke);
}

void Environnement::ajouter_centre_poke(const QPair<int,int>& _centre_poke){
	supprimer_elements(_centre_poke,false);
	centres_poke<<_centre_poke;
}

QPair<int,int> *Environnement::echange_poke_boites(int _indice){
	return &(echanges_poke_boites[_indice]);
}

int Environnement::nb_echanges_poke_boites()const{
	return echanges_poke_boites.size();
}

bool Environnement::contient_echange_poke_boites(const QPair<int,int>& _ech){
	return echanges_poke_boites.contains(_ech);
}

void Environnement::ajouter_echange_poke_boites(const QPair<int,int>& _echange_poke_boites){
	supprimer_elements(_echange_poke_boites);
	echanges_poke_boites<<_echange_poke_boites;
}

QPair<int,int> *Environnement::pension(int _indice){
	return &(pensions[_indice]);
}

int Environnement::nb_pensions()const{
	return pensions.size();
}

bool Environnement::contient_pension(const QPair<int,int>& _pension){
	return pensions.contains(_pension);
}

void Environnement::ajouter_pension(const QPair<int,int>& _pension){
	supprimer_elements(_pension,false);
	pensions<<_pension;
}

QPair<int,int> *Environnement::move_tutor(int _indice){
	return &(move_tutors[_indice]);
}

int Environnement::nb_move_tutors()const{
	return move_tutors.size();
}

bool Environnement::contient_move_tutor(const QPair<int,int>& _move_tutor){
	return move_tutors.contains(_move_tutor);
}

void Environnement::ajouter_move_tutor(const QPair<int,int>& _move_tutor){
	supprimer_elements(_move_tutor,false);
	move_tutors<<_move_tutor;
}

QPair<int,int> *Environnement::adr_lieu_faire_revivre_fossile(int _indice){
	return &(lieu_faire_revivre_fossile[_indice]);
}

int Environnement::nb_lieu_faire_revivre_fossile()const{
	return lieu_faire_revivre_fossile.size();
}

bool Environnement::contient_lieu_fossile(const QPair<int,int>& _lieu_fossile){
	return lieu_faire_revivre_fossile.contains(_lieu_fossile);
}

void Environnement::ajouter_lieu_faire_revivre_fossile(const QPair<int,int>& _lieu_faire_revivre_fossile){
	supprimer_elements(_lieu_faire_revivre_fossile,false);
	lieu_faire_revivre_fossile<<_lieu_faire_revivre_fossile;
}

/*QPair<QPair<int,int>,Pokemon> *Environnement::lieu_dons_pokemon(int _indice){
	return &(lieux_dons_pokemon[_indice])
}*/

Pokemon *Environnement::don_pokemon(const QPair<int,int>& _coords){
	bool suppr_=false;
	return lieux_dons_pokemon.valeur(_coords,suppr_);
}

/*int Environnement::nb_lieux_dons_pokemon()const{
	return lieux_dons_pokemon.size()
}*/

QList<QPair<int,int> > Environnement::coords_lieux_dons_pokemon()const{
	return lieux_dons_pokemon.cles();
}


/*void Environnement::ajouter_lieu_dons_pokemon(const QPair<QPair<int,int>,Pokemon>& _lieu_dons_pokemon){
	supprimer_elements(_lieu_dons_pokemon.first,false)
	lieux_dons_pokemon<<_lieu_dons_pokemon
}*/


void Environnement::ajouter_lieu_dons_pokemon(const QPair<int,int>& _coords,const Pokemon& _pokemon){
	supprimer_elements(_coords,false);
	lieux_dons_pokemon.ajouter_cle_valeur(_coords,_pokemon);
}


/*QPair<QPair<int,int>,QString> *Environnement::objet_donne_ramasse(int _indice){
	return &(objets_donnes_ramasses[_indice])
}*/

QString *Environnement::objet_donne_ramasse(const QPair<int,int>& _coords){
	bool suppr_=false;
	return objets_donnes_ramasses.valeur(_coords,suppr_);
}


/*int Environnement::nb_objets_donnes_ramasses()const{
	return objets_donnes_ramasses.size()
}*/

QList<QPair<int,int> > Environnement::coords_objets_donnes_ramasses()const{
	return objets_donnes_ramasses.cles();
}

/*void Environnement::ajouter_objet_donne_ramasse(const QPair<QPair<int,int>,QString>& _objet_donne_ramasse){
	supprimer_elements(_objet_donne_ramasse.first,false)
	objets_donnes_ramasses<<_objet_donne_ramasse
}*/

void Environnement::ajouter_objet_donne_ramasse(const QPair<int,int>& _coords,const QString& _objet_donne_ramasse){
	supprimer_elements(_coords,false);
	objets_donnes_ramasses.ajouter_cle_valeur(_coords,_objet_donne_ramasse);
}

QStringList *Environnement::achat_objets(const QPair<int,int>& _coords,bool& _n_instance){
	return achats_objets.valeur(_coords,_n_instance);
}

QStringList Environnement::achat_objets(const QPair<int,int>& _coords)const{
	return achats_objets.valeur(_coords);
}

QList<QPair<int,int> > Environnement::coords_achat_objets()const{
	return achats_objets.cles();
}

void Environnement::ajouter_achat_objets(const QPair<int,int>& _coords,const QStringList& _objets){
	supprimer_elements(_coords,false);
	achats_objets.ajouter_cle_valeur(_coords,_objets);
}

void Environnement::ajouter_achat_ct(const QPair<int,int>& _coords,const QList<uchar>& _ct){
	supprimer_elements(_coords,false);
	achats_ct.ajouter_cle_valeur(_coords,_ct);
}

QList<QPair<int,int> > Environnement::coords_achat_ct()const{
	return achats_ct.cles();
}

QList<uchar> *Environnement::achat_ct(const QPair<int,int>& _coords,bool& _n_instance){
	return achats_ct.valeur(_coords,_n_instance);
}

QList<uchar> Environnement::achat_ct(const QPair<int,int>& _coords)const{
	return achats_ct.valeur(_coords);
}

void Environnement::ajouter_don_cs(const QPair<int,int>& _coords,const QList<uchar>& _cs){
	supprimer_elements(_coords,false);
	dons_cs.ajouter_cle_valeur(_coords,_cs);
}

QList<QPair<int,int> > Environnement::coords_don_cs()const{
	return dons_cs.cles();
}

QList<uchar> *Environnement::don_cs(const QPair<int,int>& _coords,bool& _n_instance){
	return dons_cs.valeur(_coords,_n_instance);
}

QList<uchar> Environnement::don_cs(const QPair<int,int>& _coords)const{
	return dons_cs.valeur(_coords);
}

void Environnement::inserer_ligne(int _indice){
	decaler_ligne_elements(_indice,1);
	int indice_depart_=_indice*largeur;
	for(int i=0;i<largeur;i++){
		Tuile t_=Tuile();
		*t_.adr_nom_image()="ihm/"+type_environnement;
		tuiles.insert(indice_depart_,t_);//on pousse les nouvelles tuiles vers le bas sur une ligne
	}
}

void Environnement::inserer_colonne(int _indice){
	decaler_colonne_elements(_indice,1);
	int nb_tuiles_aj_=tuiles.size()/largeur;
	largeur++;
	int indice_depart_=_indice;
	for(int i=0;i<nb_tuiles_aj_;i++){
		Tuile t_=Tuile();
		*t_.adr_nom_image()="ihm/"+type_environnement;
		tuiles.insert(i*largeur+indice_depart_,t_);//on coupe l'environnement en deux et on ajoute une colonne
	}
	/*for(int i=indice_depart_;i<tuiles.size();i+=largeur){
		tuiles.insert(i,Tuile())
	}*/
}

void Environnement::supprimer_ligne(int _indice){
	typedef QPair<int,int> Position;
	QList<Position> cles_=champions.cles();
	foreach(Position p,cles_){
		if(p.second==_indice){
			champions.supprimer_cle_valeur(p);
		}
	}
	cles_=dresseurs1.cles();
	foreach(Position p,cles_){
		if(p.second==_indice){
			dresseurs1.supprimer_cle_valeur(p);
		}
	}
	cles_=autres_persos.cles();
	foreach(Position p,cles_){
		if(p.second==_indice){
			autres_persos.supprimer_cle_valeur(p);
		}
	}
	cles_=objets.cles();
	foreach(Position p,cles_){
		if(p.second==_indice){
			objets.supprimer_cle_valeur(p);
		}
	}
	int i_=0;
	/*while(i_<arbres.size()){
		if(arbres[i_].second==_indice){
			arbres.removeAt(i_)
		}else{
			i_++
		}
	}
	i_=0
	while(i_<rochers_destructibles.size()){
		if(rochers_destructibles[i_].second==_indice){
			rochers_destructibles.removeAt(i_)
		}else{
			i_++
		}
	}
	i_=0
	while(i_<rochers_deplacables.size()){
		if(rochers_deplacables[i_].second==_indice){
			rochers_deplacables.removeAt(i_)
		}else{
			i_++
		}
	}
	i_=0
	while(i_<tourbillons.size()){
		if(tourbillons[i_].second==_indice){
			tourbillons.removeAt(i_)
		}else{
			i_++
		}
	}*/
	i_=0;
	while(i_<centres_poke.size()){
		if(centres_poke[i_].second==_indice){
			centres_poke.removeAt(i_);
		}else{
			i_++;
		}
	}
	i_=0;
	while(i_<echanges_poke_boites.size()){
		if(echanges_poke_boites[i_].second==_indice){
			echanges_poke_boites.removeAt(i_);
		}else{
			i_++;
		}
	}
	i_=0;
	while(i_<pensions.size()){
		if(pensions[i_].second==_indice){
			pensions.removeAt(i_);
		}else{
			i_++;
		}
	}
	i_=0;
	while(i_<move_tutors.size()){
		if(move_tutors[i_].second==_indice){
			move_tutors.removeAt(i_);
		}else{
			i_++;
		}
	}
	i_=0;
	while(i_<lieu_faire_revivre_fossile.size()){
		if(lieu_faire_revivre_fossile[i_].second==_indice){
			lieu_faire_revivre_fossile.removeAt(i_);
		}else{
			i_++;
		}
	}
	/*i_=0
	while(i_<objets_donnes_ramasses.size()){
		if(objets_donnes_ramasses[i_].first.second==_indice){
			objets_donnes_ramasses.removeAt(i_)
		}else{
			i_++
		}
	}
	i_=0
	while(i_<lieux_dons_pokemon.size()){
		if(lieux_dons_pokemon[i_].first.second==_indice){
			lieux_dons_pokemon.removeAt(i_)
		}else{
			i_++
		}
	}*/
	cles_=objets_donnes_ramasses.cles();
	foreach(Position p,cles_){
		if(p.second==_indice){
			objets_donnes_ramasses.supprimer_cle_valeur(p);
		}
	}
	cles_=lieux_dons_pokemon.cles();
	foreach(Position p,cles_){
		if(p.second==_indice){
			lieux_dons_pokemon.supprimer_cle_valeur(p);
		}
	}
	cles_=achats_objets.cles();
	foreach(Position p,cles_){
		if(p.second==_indice){
			achats_objets.supprimer_cle_valeur(p);
		}
	}
	cles_=achats_ct.cles();
	foreach(Position p,cles_){
		if(p.second==_indice){
			achats_ct.supprimer_cle_valeur(p);
		}
	}
	cles_=dons_cs.cles();
	foreach(Position p,cles_){
		if(p.second==_indice){
			dons_cs.supprimer_cle_valeur(p);
		}
	}
	cles_=pokemon_legendaires.cles();
	foreach(Position p,cles_){
		if(p.second==_indice){
			pokemon_legendaires.supprimer_cle_valeur(p);
		}
	}
	decaler_ligne_elements(_indice,-1);
	int indice_depart_=_indice*largeur;
	for(int i=0;i<largeur;i++){
		tuiles.removeAt(indice_depart_);//on pousse les nouvelles tuiles vers la droite sur une ligne
	}
}

void Environnement::supprimer_colonne(int _indice){
	typedef QPair<int,int> Position;
	QList<Position> cles_=champions.cles();
	foreach(Position p,cles_){
		if(p.first==_indice){
			champions.supprimer_cle_valeur(p);
		}
	}
	cles_=dresseurs1.cles();
	foreach(Position p,cles_){
		if(p.first==_indice){
			dresseurs1.supprimer_cle_valeur(p);
		}
	}
	cles_=autres_persos.cles();
	foreach(Position p,cles_){
		if(p.first==_indice){
			autres_persos.supprimer_cle_valeur(p);
		}
	}
	cles_=objets.cles();
	foreach(Position p,cles_){
		if(p.first==_indice){
			objets.supprimer_cle_valeur(p);
		}
	}
	int i_=0;
	/*while(i_<arbres.size()){
		if(arbres[i_].first==_indice){
			arbres.removeAt(i_)
		}else{
			i_++
		}
	}
	i_=0
	while(i_<rochers_destructibles.size()){
		if(rochers_destructibles[i_].first==_indice){
			rochers_destructibles.removeAt(i_)
		}else{
			i_++
		}
	}
	i_=0
	while(i_<rochers_deplacables.size()){
		if(rochers_deplacables[i_].first==_indice){
			rochers_deplacables.removeAt(i_)
		}else{
			i_++
		}
	}
	i_=0
	while(i_<tourbillons.size()){
		if(tourbillons[i_].first==_indice){
			tourbillons.removeAt(i_)
		}else{
			i_++
		}
	}*/
	i_=0;
	while(i_<centres_poke.size()){
		if(centres_poke[i_].first==_indice){
			centres_poke.removeAt(i_);
		}else{
			i_++;
		}
	}
	i_=0;
	while(i_<echanges_poke_boites.size()){
		if(echanges_poke_boites[i_].first==_indice){
			echanges_poke_boites.removeAt(i_);
		}else{
			i_++;
		}
	}
	i_=0;
	while(i_<pensions.size()){
		if(pensions[i_].first==_indice){
			pensions.removeAt(i_);
		}else{
			i_++;
		}
	}
	i_=0;
	while(i_<move_tutors.size()){
		if(move_tutors[i_].first==_indice){
			move_tutors.removeAt(i_);
		}else{
			i_++;
		}
	}
	i_=0;
	while(i_<lieu_faire_revivre_fossile.size()){
		if(lieu_faire_revivre_fossile[i_].first==_indice){
			lieu_faire_revivre_fossile.removeAt(i_);
		}else{
			i_++;
		}
	}
	/*i_=0
	while(i_<objets_donnes_ramasses.size()){
		if(objets_donnes_ramasses[i_].first.first==_indice){
			objets_donnes_ramasses.removeAt(i_)
		}else{
			i_++
		}
	}
	i_=0
	while(i_<lieux_dons_pokemon.size()){
		if(lieux_dons_pokemon[i_].first.first==_indice){
			lieux_dons_pokemon.removeAt(i_)
		}else{
			i_++
		}
	}*/
	cles_=objets_donnes_ramasses.cles();
	foreach(Position p,cles_){
		if(p.first==_indice){
			objets_donnes_ramasses.supprimer_cle_valeur(p);
		}
	}
	cles_=lieux_dons_pokemon.cles();
	foreach(Position p,cles_){
		if(p.first==_indice){
			lieux_dons_pokemon.supprimer_cle_valeur(p);
		}
	}
	cles_=achats_objets.cles();
	foreach(Position p,cles_){
		if(p.first==_indice){
			achats_objets.supprimer_cle_valeur(p);
		}
	}
	cles_=achats_ct.cles();
	foreach(Position p,cles_){
		if(p.first==_indice){
			achats_ct.supprimer_cle_valeur(p);
		}
	}
	cles_=dons_cs.cles();
	foreach(Position p,cles_){
		if(p.first==_indice){
			dons_cs.supprimer_cle_valeur(p);
		}
	}
	cles_=pokemon_legendaires.cles();
	foreach(Position p,cles_){
		if(p.first==_indice){
			pokemon_legendaires.supprimer_cle_valeur(p);
		}
	}
	decaler_colonne_elements(_indice,-1);
	int indice_depart_=_indice+tuiles.size()-largeur;
	for(int i=indice_depart_;i>-1;i-=largeur){
		tuiles.removeAt(i);
	}
	largeur--;
}

QString* Environnement::type_env(){
	return &type_environnement;
}

int Environnement::periode_appar()const{
	return apparition_per_pok.size();
}

void Environnement::inserer_pk_appar(const Pokemon& _pokemon,int _indice){
	apparition_per_pok.insert(_indice,_pokemon);
}

void Environnement::supprimer_pk_appar(int _indice){
	apparition_per_pok.removeAt(_indice);
}

Pokemon *Environnement::pokemon(int _indice){
	return &(apparition_per_pok[_indice]);
}

uchar* Environnement::adr_nb_pas_moyen_pour_appar(){
	return &nb_pas_moyen_pour_appar;
}

int Environnement::periode_appar(const QString& _canne)const{
	return apparition_per_pok_peche.valeur(_canne).size();
}

void Environnement::inserer_pk_appar_peche(const QString& _canne,const Pokemon& _pokemon,int _indice){
	bool suppr_=false;
	apparition_per_pok_peche.valeur(_canne,suppr_)->insert(_indice,_pokemon);
}

void Environnement::supprimer_pk_appar_peche(const QString& _canne,int _indice){
	bool suppr_=false;
	apparition_per_pok_peche.valeur(_canne,suppr_)->removeAt(_indice);
}

Pokemon *Environnement::pokemon_peche(const QString& _canne,int _indice){
	bool suppr_=false;
	return &((*apparition_per_pok_peche.valeur(_canne,suppr_))[_indice]);
}

QPair<int,int>* Environnement::adr_muret(){
	return &muret;
}

QPair<int,int> Environnement::dimensions()const{
	return QPair<int,int>(largeur,tuiles.size()/largeur);
}

QList<QPair<QPair<int,int>,QPair<int,int> > > Environnement::bords(const QPair<int,int>& _id)const{
	QPair<int,int> dims_=dimensions();
	QList<QPair<QPair<int,int>,QPair<int,int> > > bords_;
	bords_<<QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(_id.first-1,_id.second),QPair<int,int>(1,dims_.second));
	bords_<<QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(_id.first,_id.second+dims_.second),QPair<int,int>(dims_.first,1));
	bords_<<QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(_id.first+dims_.first,_id.second),QPair<int,int>(1,dims_.second));
	bords_<<QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(_id.first,_id.second-1),QPair<int,int>(dims_.first,1));
	return bords_;
}

QPair<QPair<int,int>,QPair<int,int> > Environnement::intersection(const QPair<int,int>& id,const QPair<int,int>& dims,const QPair<int,int>& id_v,const QPair<int,int>& dims_v){
	QPair<int,int> dr_=QPair<int,int>(id.first+dims.first-1,id.second+dims.second-1);
	QPair<int,int> dr_vois_=QPair<int,int>(id_v.first+dims_v.first-1,id_v.second+dims_v.second-1);
	QPair<int,int> g_int_;
	QPair<int,int> d_int_;
	int inval_=Tuile::_coords_invalide_;
	QPair<QPair<int,int>,QPair<int,int> > retour=QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(inval_,inval_),QPair<int,int>(inval_,inval_));
	if(id.first>id_v.first){
		g_int_.first=id.first;
	}else{
		g_int_.first=id_v.first;
	}
	if(id.second>id_v.second){
		g_int_.second=id.second;
	}else{
		g_int_.second=id_v.second;
	}
	if(dr_.first<dr_vois_.first){
		d_int_.first=dr_.first;
	}else{
		d_int_.first=dr_vois_.first;
	}
	if(dr_.second<dr_vois_.second){
		d_int_.second=dr_.second;
	}else{
		d_int_.second=dr_vois_.second;
	}
	if(d_int_.first<g_int_.first||d_int_.second<g_int_.second){
		return retour;
	}
	retour.first=QPair<int,int>(g_int_.first-id.first,g_int_.second-id.second);
	retour.second=QPair<int,int>(d_int_.first-id.first,d_int_.second-id.second);
	return retour;
}

void Environnement::supprimer_elements(const QPair<int,int>& _coords_suppression,bool _y_compris_perso){
	champions.supprimer_cle_valeur(_coords_suppression);
	dresseurs1.supprimer_cle_valeur(_coords_suppression);
	if(_y_compris_perso){
		autres_persos.supprimer_cle_valeur(_coords_suppression);
	}
	tuile(_coords_suppression)->adr_nom_image_obst()->first="";
	/*arbres.removeOne(_coords_suppression)
	rochers_destructibles.removeOne(_coords_suppression)
	rochers_deplacables.removeOne(_coords_suppression)
	tourbillons.removeOne(_coords_suppression)*/
	objets.supprimer_cle_valeur(_coords_suppression);
	pokemon_legendaires.supprimer_cle_valeur(_coords_suppression);
	centres_poke.removeOne(_coords_suppression);
	echanges_poke_boites.removeOne(_coords_suppression);
	pensions.removeOne(_coords_suppression);
	move_tutors.removeOne(_coords_suppression);
	lieu_faire_revivre_fossile.removeOne(_coords_suppression);
	/*int i_=0
	while(i_<objets_donnes_ramasses.size()){
		if(objets_donnes_ramasses[i_].first==_coords_suppression){
			objets_donnes_ramasses.removeAt(i_)
		}else{
			i_++
		}
	}
	i_=0
	while(i_<lieux_dons_pokemon.size()){
		if(lieux_dons_pokemon[i_].first==_coords_suppression){
			lieux_dons_pokemon.removeAt(i_)
		}else{
			i_++
		}
	}*/
	objets_donnes_ramasses.supprimer_cle_valeur(_coords_suppression);
	lieux_dons_pokemon.supprimer_cle_valeur(_coords_suppression);
	achats_objets.supprimer_cle_valeur(_coords_suppression);
	achats_ct.supprimer_cle_valeur(_coords_suppression);
	dons_cs.supprimer_cle_valeur(_coords_suppression);
}

QString Environnement::exporter_obstacles(int nb_tab_env_att,const QString& nom_balise,const QList<QPair<int,int> >& obstacles){
	QString descr_;
	typedef QPair<int,int> Position;
	//_nb_tab_env=2
	for(int i=0;i<nb_tab_env_att;i++){
		descr_+="\t";
	}
	descr_+="<"+nom_balise+">";
	foreach(Position p,obstacles){
		descr_+=QString::number(p.first)+","+QString::number(p.second)+";";
	}
	if(!obstacles.isEmpty()){
		descr_.remove(descr_.size()-1,1);
	}
	descr_+="</"+nom_balise+">\n";
	return descr_;
}

QString Environnement::deduire_aleatoire(int nb_tab_env_att,const QList<Pokemon>& periode,int nb_pas_moyen_pour_appar,const QString& attribut_balise){
	QString descr_;
	for(int i=0;i<nb_tab_env_att;i++){
		descr_+="\t";
	}
	descr_+="<ApparAlea"+attribut_balise+">\n";
	QList<Pokemon> copie_periode=periode;
	int i_=0;
	while(i_<copie_periode.size()){
		Pokemon pk_=copie_periode[i_];
		int j_=i_+1;
		while(j_<copie_periode.size()){
			if(copie_periode[j_]==pk_){
				copie_periode.removeAt(j_);
			}else{
				j_++;
			}
		}
		i_++;
	}
	int nb_tab_env_att_=nb_tab_env_att+1;
	foreach(Pokemon p,copie_periode){
		descr_+=p.exporter(nb_tab_env_att_);
		descr_+="<Proba>"+QString::number(periode.count(p))+"</Proba>\n";
	}
	if(nb_pas_moyen_pour_appar>1){
		descr_+=Pokemon().exporter(nb_tab_env_att_);
		descr_+="<Proba>"+QString::number((nb_pas_moyen_pour_appar-1)*periode.size())+"</Proba>\n";
	}
	for(int i=0;i<nb_tab_env_att;i++){
		descr_+="\t";
	}
	descr_+="</ApparAlea>\n";
	return descr_;
}

bool Environnement::est_valide()const{
	if(muret.first!=0&&muret.second!=0){
		foreach(Tuile t,tuiles){
			if(t.adr_nom_image_obst()->first!=""){
				return false;
			}
		}
		bool valide_=type_environnement==""&&tuiles.size()==1;
		valide_&=autres_persos.total()==0&&dresseurs1.total()==0;
		valide_&=objets.total()==0;//&&arbres.isEmpty()
		valide_&=centres_poke.isEmpty()&&echanges_poke_boites.isEmpty();
		valide_&=pensions.isEmpty()&&move_tutors.isEmpty();
		valide_&=lieu_faire_revivre_fossile.isEmpty();//&&objets_donnes_ramasses.isEmpty()
		//valide_&=rochers_destructibles.isEmpty()&&rochers_deplacables.isEmpty()
		//valide_&=lieux_dons_pokemon.isEmpty()&&
		valide_&=achats_objets.total()==0;
		valide_&=lieux_dons_pokemon.total()==0&&objets_donnes_ramasses.total()==0;
		valide_&=achats_ct.total()==0;
		valide_&=dons_cs.total()==0;
		//valide_&=tourbillons.isEmpty()&&
		valide_&=apparition_per_pok.isEmpty();
		valide_&=pokemon_legendaires.total()==0&&apparition_per_pok_peche.valeur(_canne_).isEmpty();
		valide_&=apparition_per_pok_peche.valeur(_super_canne_).isEmpty()&&apparition_per_pok_peche.valeur(_mega_canne_).isEmpty();
		return valide_;
	}
	if(muret.first!=0||muret.second!=0){
		foreach(Tuile t,tuiles){
			if(t.adr_nom_image_obst()->first!=""){
				return false;
			}
		}
		bool valide_=type_environnement==""&&champions.total()==0;
		valide_&=largeur==1||largeur==tuiles.size();
		valide_&=autres_persos.total()==0&&dresseurs1.total()==0;
		valide_&=objets.total()==0;//&&arbres.isEmpty()
		valide_&=centres_poke.isEmpty()&&echanges_poke_boites.isEmpty();
		valide_&=pensions.isEmpty()&&move_tutors.isEmpty();
		valide_&=lieu_faire_revivre_fossile.isEmpty();//&&objets_donnes_ramasses.isEmpty()
		//valide_&=rochers_destructibles.isEmpty()&&rochers_deplacables.isEmpty()
		//valide_&=lieux_dons_pokemon.isEmpty()&&
		valide_&=achats_objets.total()==0;
		valide_&=lieux_dons_pokemon.total()==0&&objets_donnes_ramasses.total()==0;
		valide_&=achats_ct.total()==0;
		valide_&=dons_cs.total()==0;
		//valide_&=tourbillons.isEmpty()&&
		valide_&=apparition_per_pok.isEmpty();
		valide_&=pokemon_legendaires.total()==0&&apparition_per_pok_peche.valeur(_canne_).isEmpty();
		valide_&=apparition_per_pok_peche.valeur(_super_canne_).isEmpty()&&apparition_per_pok_peche.valeur(_mega_canne_).isEmpty();
		return valide_;
	}
	if(type_environnement==""){
		bool valide_=muret.first==0&&muret.second==0&&champions.total()==0;
		valide_&=autres_persos.total()==0&&dresseurs1.total()==0;
		valide_&=objets.total()==0;//&&arbres.isEmpty()
		valide_&=centres_poke.isEmpty()&&echanges_poke_boites.isEmpty();
		valide_&=pensions.isEmpty()&&move_tutors.isEmpty();
		valide_&=lieu_faire_revivre_fossile.isEmpty();//&&objets_donnes_ramasses.isEmpty()
		//valide_&=rochers_destructibles.isEmpty()&&rochers_deplacables.isEmpty()
		//valide_&=lieux_dons_pokemon.isEmpty()&&
		valide_&=achats_objets.total()==0;
		valide_&=lieux_dons_pokemon.total()==0&&objets_donnes_ramasses.total()==0;
		valide_&=achats_ct.total()==0;
		valide_&=dons_cs.total()==0;
		//valide_&=tourbillons.isEmpty()&&
		valide_&=apparition_per_pok.isEmpty();
		valide_&=pokemon_legendaires.total()==0&&apparition_per_pok_peche.valeur(_canne_).isEmpty();
		valide_&=apparition_per_pok_peche.valeur(_super_canne_).isEmpty()&&apparition_per_pok_peche.valeur(_mega_canne_).isEmpty();
		return valide_;
	}
	if(!peut_etre_une_zone_de_peche()){
		bool valide_=apparition_per_pok_peche.valeur(_canne_).isEmpty();
		valide_&=apparition_per_pok_peche.valeur(_super_canne_).isEmpty()&&apparition_per_pok_peche.valeur(_mega_canne_).isEmpty();
		return valide_;
	}
	return true;
}

QList<Pokemon> Environnement::pokemon_obtensible()const{
	//lieux_dons_pokemon,apparition_per_pok,apparition_per_pok_peche,pokemon_legendaires
	typedef QPair<int,int> Position;
	QList<Pokemon> retour_;
	foreach(Position p,lieux_dons_pokemon.cles()){
		retour_<<lieux_dons_pokemon.valeur(p);
	}
	foreach(Position p,pokemon_legendaires.cles()){
		retour_<<lieux_dons_pokemon.valeur(p);
	}
	retour_<<apparition_per_pok;
	retour_<<apparition_per_pok_peche.valeur(_canne_);
	retour_<<apparition_per_pok_peche.valeur(_super_canne_);
	retour_<<apparition_per_pok_peche.valeur(_mega_canne_);
	return retour_;
}

QString Environnement::exporter(int _nb_tab_env,const QPair<int,int>& _id)const{
	QString descr_;
	typedef QPair<int,int> Position;
	//_nb_tab_env=2
	for(int i=0;i<_nb_tab_env;i++){
		descr_+="\t";
	}
	descr_+="<Env coords=\""+QString::number(_id.first)+","+QString::number(_id.second)+"\">\n";
	int nb_tab_env_att_=_nb_tab_env+1;
	for(int i=0;i<nb_tab_env_att_;i++){
		descr_+="\t";
	}
	descr_+="<Largeur>"+QString::number(largeur)+"</Largeur>\n";
	for(int i=0;i<nb_tab_env_att_;i++){
		descr_+="\t";
	}
	descr_+="<Type>"+type_environnement+"</Type>\n";
	int nb_tuiles_=tuiles.size();
	for(int i=0;i<nb_tuiles_;i++){
		for(int j=0;j<nb_tab_env_att_;j++){
			descr_+="\t";
		}
		descr_+=tuiles[i].exporter();
	}
	QList<Position> cles_=champions.cles();
	foreach(Position p,cles_){
		descr_+=champions.valeur(p).exporter(nb_tab_env_att_,p);
	}
	cles_=dresseurs1.cles();
	foreach(Position p,cles_){
		descr_+=dresseurs1.valeur(p).exporter(nb_tab_env_att_,p);
	}
	cles_=autres_persos.cles();
	foreach(Position p,cles_){
		descr_+=autres_persos.valeur(p).exporter(nb_tab_env_att_,p);
	}
	cles_=objets.cles();
	foreach(Position p,cles_){
		for(int i=0;i<nb_tab_env_att_;i++){
			descr_+="\t";
		}
		descr_+="<Obj coords=\""+QString::number(p.first)+","+QString::number(p.second)+"\">"+objets.valeur(p)+"</Obj>\n";
	}
	/*int nb_dons_=objets_donnes_ramasses.size()
	for(int i=0;i<nb_dons_;i++){
		for(int j=0;j<nb_tab_env_att_;j++){
			descr_+="\t"
		}
		Position p_=objets_donnes_ramasses[i].first
		descr_+="<DonObj coords=\""+QString::number(p_.first)+","+QString::number(p_.second)+"\">"+objets_donnes_ramasses[i].second+"</DonObj>\n"
	}
	nb_dons_=lieux_dons_pokemon.size()
	for(int i=0;i<nb_dons_;i++){
		for(int j=0;j<nb_tab_env_att_;j++){
			descr_+="\t"
		}
		Position p_=lieux_dons_pokemon[i].first
		descr_+="<DonPk coords=\""+QString::number(p_.first)+","+QString::number(p_.second)+"\">"
		descr_+=lieux_dons_pokemon[i].second.exporter(nb_tab_env_att_+1)
		for(int j=0;j<nb_tab_env_att_;j++){
			descr_+="\t"
		}
		descr_+="</DonPk>\n"
	}*/
	cles_=objets_donnes_ramasses.cles();
	foreach(Position p,cles_){
		for(int i=0;i<nb_tab_env_att_;i++){
			descr_+="\t";
		}
		descr_+="<DonObj coords=\""+QString::number(p.first)+","+QString::number(p.second)+"\">";
		descr_+=objets_donnes_ramasses.valeur(p)+"</DonObj>\n";
	}
	cles_=lieux_dons_pokemon.cles();
	foreach(Position p,cles_){
		for(int i=0;i<nb_tab_env_att_;i++){
			descr_+="\t";
		}
		descr_+="<DonPk coords=\""+QString::number(p.first)+","+QString::number(p.second)+"\">\n";
		descr_+=lieux_dons_pokemon.valeur(p).exporter(nb_tab_env_att_+1);
		for(int j=0;j<nb_tab_env_att_;j++){
			descr_+="\t";
		}
		descr_+="</DonPk>\n";
	}
	cles_=achats_objets.cles();
	foreach(Position p,cles_){
		for(int i=0;i<nb_tab_env_att_;i++){
			descr_+="\t";
		}
		descr_+="<AchObj coords=\""+QString::number(p.first)+","+QString::number(p.second)+"\">"+achats_objets.valeur(p).join(";")+"</AchObj>\n";
	}
	cles_=achats_ct.cles();
	foreach(Position p,cles_){
		for(int i=0;i<nb_tab_env_att_;i++){
			descr_+="\t";
		}
		descr_+="<AchCt coords=\""+QString::number(p.first)+","+QString::number(p.second)+"\">";
		foreach(uchar c,achats_ct.valeur(p)){
			descr_+=QString::number(c)+",";
		}
		descr_=descr_.left(descr_.size()-1);
		descr_+="</AchCt>\n";
	}
	cles_=dons_cs.cles();
	foreach(Position p,cles_){
		for(int i=0;i<nb_tab_env_att_;i++){
			descr_+="\t";
		}
		descr_+="<DonCs coords=\""+QString::number(p.first)+","+QString::number(p.second)+"\">";
		foreach(uchar c,dons_cs.valeur(p)){
			descr_+=QString::number(c)+",";
		}
		descr_=descr_.left(descr_.size()-1);
		descr_+="</DonCs>\n";
	}
	/*descr_+=exporter_obstacles(nb_tab_env_att_,"Arb",arbres)
	descr_+=exporter_obstacles(nb_tab_env_att_,"RocD",rochers_destructibles)
	descr_+=exporter_obstacles(nb_tab_env_att_,"RocM",rochers_deplacables)
	descr_+=exporter_obstacles(nb_tab_env_att_,"Tourb",tourbillons)*/
	descr_+=exporter_obstacles(nb_tab_env_att_,"CtrePk",centres_poke);
	descr_+=exporter_obstacles(nb_tab_env_att_,"EchPk",echanges_poke_boites);
	descr_+=exporter_obstacles(nb_tab_env_att_,"Pens",pensions);
	descr_+=exporter_obstacles(nb_tab_env_att_,"MT",move_tutors);
	descr_+=exporter_obstacles(nb_tab_env_att_,"LFoss",lieu_faire_revivre_fossile);
	for(int i=0;i<nb_tab_env_att_;i++){
		descr_+="\t";
	}
	descr_+="<Mur>"+QString::number(muret.first)+","+QString::number(muret.second)+"</Mur>\n";
	for(int i=0;i<nb_tab_env_att_;i++){
		descr_+="\t";
	}
	descr_+="<ApparPer>\n";
	foreach(Pokemon p,apparition_per_pok){
		descr_+=p.exporter(nb_tab_env_att_+1);
	}
	for(int i=0;i<nb_tab_env_att_;i++){
		descr_+="\t";
	}
	descr_+="</ApparPer>\n";
	QList<Pokemon> copie_appar_per_pok_;
	foreach(Pokemon p,apparition_per_pok){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*p.adr_nom());
		if(fiche_pk_->rep_genr()!="<LEG>"){
			copie_appar_per_pok_<<p;
		}
	}
	if(!apparition_per_pok.isEmpty()){
		descr_+=deduire_aleatoire(nb_tab_env_att_,apparition_per_pok,nb_pas_moyen_pour_appar);
	}
	if(!copie_appar_per_pok_.isEmpty()){
		descr_+="<ApparPerSansLeg>\n";
		foreach(Pokemon p,copie_appar_per_pok_){
			descr_+=p.exporter(nb_tab_env_att_+1);
		}
		for(int i=0;i<nb_tab_env_att_;i++){
			descr_+="\t";
		}
		descr_+="</ApparPerSansLeg>\n";
	}
	if(!copie_appar_per_pok_.isEmpty()){
		descr_+=deduire_aleatoire(nb_tab_env_att_,copie_appar_per_pok_,nb_pas_moyen_pour_appar);
	}
	QList<QString> cles_canne_=apparition_per_pok_peche.cles();
	int nb_tab_env_att_2_=nb_tab_env_att_+1;
	for(int i=0;i<nb_tab_env_att_;i++){
		descr_+="\t";
	}
	descr_+="<Peche>\n";
	foreach(QString c,cles_canne_){
		QList<Pokemon> apparition_per_pok_p_=apparition_per_pok_peche.valeur(c);
		for(int i=0;i<nb_tab_env_att_2_;i++){
			descr_+="\t";
		}
		descr_+="<ApparPer canne=\""+c+"\">\n";
		foreach(Pokemon p,apparition_per_pok_p_){
			descr_+=p.exporter(nb_tab_env_att_2_+1);
		}
		for(int i=0;i<nb_tab_env_att_2_;i++){
			descr_+="\t";
		}
		descr_+="</ApparPer>\n";
		if(!apparition_per_pok_p_.isEmpty()){
			descr_+=deduire_aleatoire(nb_tab_env_att_2_,apparition_per_pok_p_,0," canne=\""+c+"\"");
		}
		QList<Pokemon> copie_apparition_per_pok_p_;
		foreach(Pokemon p,apparition_per_pok_p_){
			FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*p.adr_nom());
			if(fiche_pk_->rep_genr()!="<LEG>"){
				copie_apparition_per_pok_p_<<p;
			}
		}
		if(!copie_apparition_per_pok_p_.isEmpty()){
			descr_+="<ApparPerSansLeg canne=\""+c+"\">\n";
			foreach(Pokemon p,copie_apparition_per_pok_p_){
				descr_+=p.exporter(nb_tab_env_att_+1);
			}
			for(int i=0;i<nb_tab_env_att_;i++){
				descr_+="\t";
			}
			descr_+="</ApparPerSansLeg>\n";
		}
		if(!copie_apparition_per_pok_p_.isEmpty()){
			descr_+=deduire_aleatoire(nb_tab_env_att_2_,copie_apparition_per_pok_p_,0," canne=\""+c+"\"");
		}
	}
	for(int i=0;i<nb_tab_env_att_;i++){
		descr_+="\t";
	}
	descr_+="</Peche>\n";
	cles_=pokemon_legendaires.cles();
	foreach(Position p,cles_){
		descr_+=pokemon_legendaires.valeur(p).exporter(nb_tab_env_att_,p);
	}
	return descr_;
}

bool operator==(const Environnement& a,const Environnement& b){
	return a.egal(b);
}

void Environnement::serialiser(Flux& _out)const{
	_out<<largeur;
	_out<<type_environnement;
	_out<<tuiles;
	_out<<champions;
	_out<<dresseurs1;
	_out<<autres_persos;
	_out<<objets;
	/*_out<<arbres
	_out<<rochers_destructibles
	_out<<rochers_deplacables
	_out<<tourbillons*/
	_out<<centres_poke;
	_out<<echanges_poke_boites;
	_out<<pensions;
	_out<<move_tutors;
	_out<<lieu_faire_revivre_fossile;
	_out<<objets_donnes_ramasses;
	_out<<lieux_dons_pokemon;
	_out<<achats_objets;
	_out<<achats_ct;
	_out<<dons_cs;
	_out<<apparition_per_pok;
	_out<<nb_pas_moyen_pour_appar;
	_out<<apparition_per_pok_peche;
	_out<<pokemon_legendaires;
	_out<<muret;
}

void Environnement::deserialiser(Flux& _in){
	_in>>largeur;
	_in>>type_environnement;
	_in>>tuiles;
	_in>>champions;
	_in>>dresseurs1;
	_in>>autres_persos;
	_in>>objets;
	/*_in>>arbres
	_in>>rochers_destructibles
	_in>>rochers_deplacables
	_in>>tourbillons*/
	_in>>centres_poke;
	_in>>echanges_poke_boites;
	_in>>pensions;
	_in>>move_tutors;
	_in>>lieu_faire_revivre_fossile;
	_in>>objets_donnes_ramasses;
	_in>>lieux_dons_pokemon;
	_in>>achats_objets;
	_in>>achats_ct;
	_in>>dons_cs;
	_in>>apparition_per_pok;
	_in>>nb_pas_moyen_pour_appar;
	_in>>apparition_per_pok_peche;
	_in>>pokemon_legendaires;
	_in>>muret;
}

Flux & operator <<(Flux& out,const Environnement& _Environnement){
	_Environnement.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Environnement& _Environnement){
	_Environnement.deserialiser(in);
	return in;
}



