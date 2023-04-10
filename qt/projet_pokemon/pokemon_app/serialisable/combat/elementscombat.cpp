#include "serialisable/combat/elementscombat.h"
#include "serialisable/utilisateur/utilisateur.h"
#include "base_donnees/personnages/champion.h"
#include "base_donnees/personnages/dresseurligue.h"
#include "base_donnees/pokemon/pokemonsauvage.h"
#include "base_donnees/donnees.h"
#include "base_donnees/capacites/fichecapacite.h"
#include "base_donnees/objets/objetattachablecombat.h"
#include "base_donnees/objets/baie.h"
#include "base_donnees/objets/ball.h"
#include "base_donnees/objets/plaque.h"
#include "base_donnees/objets/pierreevo.h"
#include "base_donnees/objets/soinpp.h"
#include "base_donnees/objets/soinpv.h"
#include "base_donnees/objets/soinpvstatut.h"
#include "base_donnees/objets/soinstatut.h"
#include "base_donnees/evolution/evolutionpierreevolutive.h"
#include "base_donnees/attaques/effets/effetantiimmu.h"
#include "base_donnees/attaques/effets/effetstatistique.h"
#include "base_donnees/attaques/effets/effetstatut.h"
#include "base_donnees/attaques/effets/effetclimat.h"
#include "base_donnees/attaques/effets/effetdegats.h"
#include "base_donnees/attaques/effets/effetmultpuissattaque.h"
#include "base_donnees/attaques/effets/effettauxpvrestants.h"
#include "base_donnees/attaques/effets/effettauxpvpvmax.h"
#include "base_donnees/attaques/effets/effettauxdegats.h"
#include "serialisable/coordonnees/coordonnees.h"
#include "combat/transfertrelais.h"
#include "serialisable/partie/partie.h"
#include "serialisable/utilisateur/inventaire.h"

ElementsCombat::ElementsCombat(){
	;
}

void ElementsCombat::init_combat(Donnees *_d,const Utilisateur& _utilisateur){
	a_evolue=false;
	situation=ElementsCombat::NORMAL;
	indice_capture=-1;
	Inventaire inv_=_utilisateur.inv();
	fuite=0;
	climat.first.first="";
	climat.first.second=0;
	climat.second.first=false;
	climat.second.second=false;
	indice_pk=-1;
	indice_attaque=-1;
	indice_evolution=-1;
	base_evolution="";
	derniere_attaque_lancee="";
	derniere_attaque_reussie="";
	commentaire_recent="";
	nb_tours_terrain=0;
	QStringList effets_globaux_;
	effets_globaux_<<"GRAVITE";
	effets_globaux_<<"REQUIEM";
	effets_globaux_<<"DISTORSION";
	effets_globaux_<<"ZONE_MAGIQUE";
	effets_globaux_<<"ZONE_ETRANGE";
	foreach(QString e,effets_globaux_){
		effets_globaux.ajouter_cle_valeur(e,QPair<uchar,bool>(0,false));
	}
	QList<Combattant> cbts_=creatures_act.cles();
	foreach(Combattant c,cbts_){
		HashMap<QString,QList<QPair<uchar,Taux> > > objets_;
		if(c.equipe()==adv){
			combattants_contre_adv.ajouter_cle_valeur(c.position(),QList<uchar>());
			creatures_act.valeur(c).init_creature(cbts_,objets_,_d);
		}
		if(c.equipe()==ut){
			actions_choisies_ut.ajouter_cle_valeur(c.position(),"");
			foreach(QString o,inv_.baies_ut().cles()){
				QList<QPair<uchar,Taux> > liste_obj_;
				liste_obj_<<QPair<uchar,Taux>(inv_.baies_ut().valeur(o),Taux(1));
				objets_.ajouter_cle_valeur(o,liste_obj_);
			}
			foreach(QString o,inv_.objets_soins_ut().cles()){
				objets_.ajouter_cle_valeur(o,inv_.objets_soins_ut().valeur(o));
			}
			creatures_act.valeur(c).init_creature(cbts_,objets_,_d);
			gain_exp_tmp.ajouter_cle_valeur(c.position(),Taux(0));
		}
		QPair<uchar,uchar> position_place_=positions_places.valeur(c);
		if(position_place_.second!=arriere){
			numeros_front<<c;
			voeu.ajouter_cle_valeur(position_place_,QPair<uchar,QPair<bool,bool> >(0,QPair<bool,bool>(false,false)));
			soin_total.ajouter_cle_valeur(position_place_,QPair<uchar,bool>(0,false));
			prescience_carnar.ajouter_cle_valeur(QPair<QString,QPair<uchar,uchar> >("PRESCIENCE",position_place_),QPair<QPair<Taux,uchar>,QPair<uchar,uchar> >(QPair<Taux,uchar>(Taux(0),0),QPair<uchar,uchar>(arriere,arriere)));
			prescience_carnar.ajouter_cle_valeur(QPair<QString,QPair<uchar,uchar> >("CARNAREKET",position_place_),QPair<QPair<Taux,uchar>,QPair<uchar,uchar> >(QPair<Taux,uchar>(Taux(0),0),QPair<uchar,uchar>(arriere,arriere)));
		}
		lanceur_saisie.ajouter_cle_valeur(c,Combattant());
	}
	QStringList attaques_eq_;
	attaques_eq_<<"PROTECTION";
	attaques_eq_<<"MUR_LUMIERE";
	attaques_eq_<<"VENT_ARRIERE";
	attaques_eq_<<"RUNE_PROTECT";
	attaques_eq_<<"BRUME";
	attaques_eq_<<"AIR_VEINARD";
	attaques_eq_<<"ANTI_SOIN";
	attaques_eq_<<"AIRE_EAU_FEU";
	attaques_eq_<<"AIRE_EAU_HERBE";
	attaques_eq_<<"AIRE_FEU_HERBE";
	attaques_eq_<<"PICOTS";
	attaques_eq_<<"PICS_TOXIKS";
	attaques_eq_<<"PIEGE_DE_ROC";
	HashMap<QString,QPair<uchar,bool> > nb_tour_attaque_equipe_;
	foreach(QString s,attaques_eq_){
		nb_tour_attaque_equipe_.ajouter_cle_valeur(s,QPair<uchar,bool>(0,false));
	}
	nb_tour_attaque_equipe.ajouter_cle_valeur(ut,nb_tour_attaque_equipe_);
	nb_tour_attaque_equipe.ajouter_cle_valeur(adv,nb_tour_attaque_equipe_);
	vengeance_actif.ajouter_cle_valeur(ut,QPair<bool,bool>(false,false));
	vengeance_actif.ajouter_cle_valeur(adv,QPair<bool,bool>(false,false));
	attaques_eq_.clear();
	attaques_eq_<<"ECHO";
	attaques_eq_<<"CHANT_CANON";
	foreach(QString s,attaques_eq_){
		nb_utilisation_attaques.ajouter_cle_valeur(QPair<QString,uchar>(s,ut),0);
		nb_utilisation_attaques.ajouter_cle_valeur(QPair<QString,uchar>(s,adv),0);
	}
	lanceur_par_ici.ajouter_cle_valeur(ut,arriere);
	lanceur_par_ici.ajouter_cle_valeur(adv,arriere);
	foreach(QString s,_d->val_objets().cles()){
		objets_utilisateur_perdus.ajouter_cle_valeur(s,Entier(0));
	}
	capture.first="";
	capture.second=false;
	prochaine_evolution=CreatureCombat();
	foreach(Combattant c,cbts_){
		if(c.equipe()==ut){
			continue;
		}
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		envoi(c,creatures_act.valeur(c),true,_d);
	}
	foreach(Combattant c,cbts_){
		if(c.equipe()==adv){
			continue;
		}
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		envoi(c,creatures_act.valeur(c),true,_d);
	}
	foreach(Combattant c,cbts_){
		if(c.equipe()==ut){
			continue;
		}
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		intimidation(creatures_act.valeur(c).fiche_capacite(_d),ut,_d);
	}
	foreach(Combattant c,cbts_){
		if(c.equipe()==adv){
			continue;
		}
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		intimidation(creatures_act.valeur(c).fiche_capacite(_d),adv,_d);
	}
}

ElementsCombat::ElementsCombat(const Utilisateur& _utilisateur,const Difficulte& _diff,Dresseur *_dresseur,Donnees *_d,int _numero){
	ut=_d->val_ut();
	adv=_d->val_adv();
	arriere=_d->constante_numerique("ARRIERE");
	diff=_diff;
	type_combat="DRESSEUR";
	multiplicite=_dresseur->mult_comb();
	typedef QPair<uchar,PokemonUtilisateur> PositionPokemon;
	QList<QPair<uchar,PokemonUtilisateur> > equipe_ut_=_utilisateur.equipe_ut();
	uchar i_=0;
	foreach(PositionPokemon p,equipe_ut_){
		creatures_act.ajouter_cle_valeur(Combattant(ut,p.first),CreatureCombat(p.second,_d));
		if(i_<multiplicite&&p.second.statut_pk()!="KO"){
			positions_places.ajouter_cle_valeur(Combattant(ut,p.first),QPair<uchar,uchar>(ut,i_));
			positions_places_bis.ajouter_cle_valeur(Combattant(ut,p.first),QPair<uchar,uchar>(ut,i_));
			i_++;
		}else{
			positions_places.ajouter_cle_valeur(Combattant(ut,p.first),QPair<uchar,uchar>(ut,arriere));
			positions_places_bis.ajouter_cle_valeur(Combattant(ut,p.first),QPair<uchar,uchar>(ut,arriere));
		}
	}
	if(_numero<0){
		coords_adversaire.second=0;
		DresseurLigue *dresseur_=qobject_cast<DresseurLigue*>(_dresseur);
		type_combat="DRESSEUR_LIGUE";
		i_=0;
		foreach(PokemonDresse *p,dresseur_->eq()){
			creatures_act.ajouter_cle_valeur(Combattant(adv,i_),CreatureCombat(p,_d));
			QString nom_=creatures_act.valeur(Combattant(adv,i_)).nom_pk();
			if(_utilisateur.present_pk(nom_)){
				creatures_act.valeur(Combattant(adv,i_)).ball_capt()="POKE_BALL";
			}
			if(i_<multiplicite){
				positions_places_bis.ajouter_cle_valeur(Combattant(adv,i_),QPair<uchar,uchar>(adv,i_));
				positions_places.ajouter_cle_valeur(Combattant(adv,i_),QPair<uchar,uchar>(adv,i_));
			}else{
				positions_places_bis.ajouter_cle_valeur(Combattant(adv,i_),QPair<uchar,uchar>(adv,arriere));
				positions_places.ajouter_cle_valeur(Combattant(adv,i_),QPair<uchar,uchar>(adv,arriere));
			}
			i_++;
		}
	}else{
		coords_adversaire.second=_numero;
		Dresseur1 *dresseur_=qobject_cast<Dresseur1*>(_dresseur);
		i_=0;
		foreach(PokemonDresse *p,dresseur_->eq(_numero)){
			creatures_act.ajouter_cle_valeur(Combattant(adv,i_),CreatureCombat(p,_d));
			QString nom_=creatures_act.valeur(Combattant(adv,i_)).nom_pk();
			if(_utilisateur.present_pk(nom_)){
				creatures_act.valeur(Combattant(adv,i_)).ball_capt()="POKE_BALL";
			}
			if(i_<multiplicite){
				positions_places_bis.ajouter_cle_valeur(Combattant(adv,i_),QPair<uchar,uchar>(adv,i_));
				positions_places.ajouter_cle_valeur(Combattant(adv,i_),QPair<uchar,uchar>(adv,i_));
			}else{
				positions_places_bis.ajouter_cle_valeur(Combattant(adv,i_),QPair<uchar,uchar>(adv,arriere));
				positions_places.ajouter_cle_valeur(Combattant(adv,i_),QPair<uchar,uchar>(adv,arriere));
			}
			i_++;
		}
	}
	init_combat(_d,_utilisateur);
}

ElementsCombat::ElementsCombat(const Utilisateur& _utilisateur,const Difficulte& _diff,PokemonSauvage* _pokemon,Donnees *_d){
	ut=_d->val_ut();
	adv=_d->val_adv();
	arriere=_d->constante_numerique("ARRIERE");
	diff=_diff;
	type_combat="SAUVAGE";
	multiplicite=1;
	typedef QPair<uchar,PokemonUtilisateur> PositionPokemon;
	uchar i_=0;
	foreach(PositionPokemon p,_utilisateur.equipe_ut()){
		creatures_act.ajouter_cle_valeur(Combattant(ut,p.first),CreatureCombat(p.second,_d));
		if(i_<multiplicite&&p.second.statut_pk()!="KO"){
			positions_places_bis.ajouter_cle_valeur(Combattant(ut,p.first),QPair<uchar,uchar>(ut,i_));
			positions_places.ajouter_cle_valeur(Combattant(ut,p.first),QPair<uchar,uchar>(ut,i_));
			i_++;
		}else{
			positions_places_bis.ajouter_cle_valeur(Combattant(ut,p.first),QPair<uchar,uchar>(ut,arriere));
			positions_places.ajouter_cle_valeur(Combattant(ut,p.first),QPair<uchar,uchar>(ut,arriere));
		}
	}
	creatures_act.ajouter_cle_valeur(Combattant(adv,0),CreatureCombat(_pokemon,_d));
	if(_utilisateur.present_pk(_pokemon->n_pk())){
		creatures_act.valeur(Combattant(adv,0)).ball_capt()="POKE_BALL";
	}
	positions_places_bis.ajouter_cle_valeur(Combattant(adv,0),QPair<uchar,uchar>(adv,0));
	positions_places.ajouter_cle_valeur(Combattant(adv,0),QPair<uchar,uchar>(adv,0));
	init_combat(_d,_utilisateur);
}

Coordonnees& ElementsCombat::maj_coords_leg(){
	return coords_leg;
}

void ElementsCombat::init_type_env(const Coordonnees& _coords,const Coordonnees& _coords_adv,bool _ligue,Donnees* _d){
	if(!_ligue){
		type_environnement=_d->val_lieux().valeur(_coords.lieu())->plateau(_coords.plateau())->environnement(_coords.coords_environnement())->type();
	}else{
		type_environnement=_d->val_ligues().valeur(_coords.lieu())->plateau(_coords.plateau())->environnement(_coords.coords_environnement())->type();
	}
	coords_adversaire.first=_coords_adv;
}

QString ElementsCombat::type_env()const{
	return type_environnement;
}

Taux ElementsCombat::argent()const{
	return var_argent;
}

uchar ElementsCombat::adversaire(uchar _eq)const{
	if(_eq==adv){
		return ut;
	}
	return adv;
}

void ElementsCombat::reinit_constantes(const Partie& _partie,Donnees* _d){
	ut=_d->val_ut();
	adv=_d->val_adv();
	arriere=_d->constante_numerique("ARRIERE");
	diff=_partie.diff();
}

/*ElementsCombat::ElementsCombat(const ElementsCombat& _copie){
	
}*/

HashMap<Combattant,CreatureCombat> ElementsCombat::creatures_combats()const{
	return creatures_act;
}

CreatureCombat& ElementsCombat::creature_combat(const Combattant& _cbt){
	return creatures_act.valeur(_cbt);
}

void ElementsCombat::ajouter_combattant(){

}

QList<Combattant> ElementsCombat::combattants_a_position(const QPair<uchar,uchar>& _position)const{
	return positions_places.cles(_position);
}

QPair<uchar,uchar> ElementsCombat::position(const Combattant& _pokemon)const{
	return positions_places.valeur(_pokemon);
}

HashMap<uchar,QString>& ElementsCombat::actions_choisies(){
	return actions_choisies_ut;
}

int ElementsCombat::nb_fuite()const{
	return fuite;
}

HashMap<uchar,QString> ElementsCombat::actions_choisies()const{
	return actions_choisies_ut;
}

QString ElementsCombat::type_cbt()const{
	return type_combat;
}

void ElementsCombat::fin_cbt(){
	type_combat="";
	combattants_contre_adv.tout_supprimer();
}

bool ElementsCombat::existence_anti_climat_actif(Donnees *_d)const{
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		FicheCapacite *f_capac_=creatures_act.valeur(c).fiche_capacite(_d);
		if(f_capac_&&f_capac_->ant_clim()){
			return true;
		}
	}
	return false;
}

QPair<QPair<QString,uchar>,QPair<bool,bool> > ElementsCombat::climat_gl()const{
	return climat;
}

qint8& ElementsCombat::indice_pos_pk(){
	return indice_pk;
}

qint8& ElementsCombat::indice_pos_attaque(){
	return indice_attaque;
}

qint8& ElementsCombat::indice_pos_evolution(){
	return indice_evolution;
}

int& ElementsCombat::indice_pos_boite(){
	return indice_capture;
}

QString ElementsCombat::base_evo()const{
	return base_evolution;
}

uchar& ElementsCombat::situation_cbt(){
	return situation;
}

HashMap<uchar,QList<uchar> > ElementsCombat::combattants_ut()const{
	return combattants_contre_adv;
}

QList<uchar> ElementsCombat::combattants_ut(uchar _adversaire)const{
	return combattants_contre_adv.valeur(_adversaire);
}

void ElementsCombat::maj_liste_cbts(uchar _adversaire,const QList<uchar>& _liste_combattants){
	combattants_contre_adv.valeur(_adversaire)=_liste_combattants;
}

QList<Combattant> ElementsCombat::fronts()const{
	return numeros_front;
}

HashMap<QString,Entier> ElementsCombat::objets_ut_perdus()const{
	return objets_utilisateur_perdus;
}

void ElementsCombat::stocker_dans_inventaire_perdu(const QString& _objet){
	++objets_utilisateur_perdus.valeur(_objet);
}

QString ElementsCombat::der_att_lancee()const{
	return derniere_attaque_lancee;
}

QString ElementsCombat::der_att_reussie()const{
	return derniere_attaque_reussie;
}

HashMap<uchar,HashMap<QString,QPair<uchar,bool> > > ElementsCombat::attaques_equipes()const{
	return nb_tour_attaque_equipe;
}

QPair<uchar,bool> ElementsCombat::attaque_equipe(uchar _equipe,const QString& _nom_attaque)const{
	return nb_tour_attaque_equipe.valeur(_equipe).valeur(_nom_attaque);
}

QPair<uchar,bool>& ElementsCombat::attaque_equipe(uchar _equipe,const QString& _nom_attaque){
	return nb_tour_attaque_equipe.valeur(_equipe).valeur(_nom_attaque);
}

HashMap<QString,QPair<uchar,bool> > ElementsCombat::attaques_globales()const{
	return effets_globaux;
}

QPair<uchar,bool> ElementsCombat::effet_global(const QString& _effet)const{
	return effets_globaux.valeur(_effet);
}
/*void ElementsCombat::maj_attaque_equipe(uchar _equipe,const QString& _nom_attaque,const QPair<uchar,bool>& _activite){
	
}*/

QPair<Coordonnees,int> ElementsCombat::adversaire()const{
	return coords_adversaire;
}

HashMap<QPair<uchar,uchar>,QPair<uchar,QPair<bool,bool> > > ElementsCombat::voeu_gl()const{
	return voeu;
}

HashMap<QPair<uchar,uchar>,QPair<uchar,bool> > ElementsCombat::soin_total_gl()const{
	return soin_total;
}

HashMap<QPair<QString,QPair<uchar,uchar> >,QPair<QPair<Taux,uchar>,QPair<uchar,uchar> > > ElementsCombat::attaques_prepa_tours()const{
	return prescience_carnar;
}

void ElementsCombat::gain_nb_tours_terrain(){
	nb_tours_terrain++;
}

uchar ElementsCombat::nb_tours_terrain_gl()const{
	return nb_tours_terrain;
}

HashMap<uchar,QPair<bool,bool> > ElementsCombat::vengeance()const{
	return vengeance_actif;
}

HashMap<QPair<QString,uchar>,uchar> ElementsCombat::nb_util_attaq()const{
	return nb_utilisation_attaques;
}

QString& ElementsCombat::maj_commentaire_tour(){
	return commentaire_recent;
}

uchar ElementsCombat::mult_cbt()const{
	return multiplicite;
}

QPair<QString,bool> ElementsCombat::capture_pk_sa()const{
	return capture;
}

QList<Combattant> ElementsCombat::cibles_possible_lanceur_bis(const Combattant& _lanceur,const QStringList& _attaques,Donnees *_d)const{
	QList<Combattant> liste_;
	foreach(QString a,_attaques){
		foreach(Combattant c,cibles_possible_lanceur(_lanceur,_d->val_attaques().valeur(a))){
			if(!liste_.contains(c)){
				liste_<<c;
			}
		}
	}
	for(int i=0;i<liste_.size();i++){
		for(int j=i+1;j<liste_.size();j++){
			if(liste_[i].equipe()<liste_[j].equipe()){
				liste_.swap(i,j);
			}else if(liste_[i].equipe()==liste_[j].equipe()){
				if(liste_[i].position()<liste_[j].position()){
					liste_.swap(i,j);
				}
			}
		}
	}
	int i_=0;
	while(i_<liste_.size()){
		Combattant cbt_=liste_[i_];
		int j_=i_+1;
		while(j_<liste_.size()){
			if(liste_[j_]!=cbt_){
				break;
			}
			liste_.removeAt(j_);
		}
		i_=j_;
	}
	return liste_;
}

QList<Combattant> ElementsCombat::cibles_possible_lanceur(const Combattant& _lanceur,const QStringList& _attaques,Donnees *_d)const{
	QList<Combattant> liste_;
	foreach(QString a,_attaques){
		foreach(Combattant c,cibles_lanceur(_lanceur,_d->val_attaques().valeur(a))){
			if(!liste_.contains(c)){
				liste_<<c;
			}
		}
	}
	return liste_;
}

QList<Combattant> ElementsCombat::cibles_lanceur(const Combattant& _lanceur,Donnees *_d)const{//elt
	CreatureCombat cr_l_=creatures_act.valeur(_lanceur);
	if(cr_l_.act_choisie()!="ATTAQUE"){
		return QList<Combattant>();
	}
	return cibles_lanceur(_lanceur,_d->val_attaques().valeur(cr_l_.att_choisie()));
}

QList<Combattant> ElementsCombat::cibles_possible_lanceur(const Combattant& _lanceur,FicheAttaque *_attaque)const{//elt
	QList<Combattant> liste_;
	if(_attaque->qi().contains("UNIQUE IMPORTE")){
		foreach(Combattant c,creatures_act.cles()){
			uchar pos_=positions_places.valeur(c).second;
			if(pos_!=arriere&&creatures_act.valeur(c).statut_pk()!="KO"){
				liste_<<c;
			}
		}
	}else if(_attaque->qi().contains("UNIQ")){
		if(!diff.r_adjacence_active()||_attaque->qi().contains("AUTRE")){
			foreach(Combattant c,creatures_act.cles()){
				uchar pos_=positions_places.valeur(c).second;
				if(pos_!=arriere&&creatures_act.valeur(c).statut_pk()!="KO"){
					liste_<<c;
				}
			}
			liste_.removeOne(_lanceur);
		}else{
			liste_=combattants_adjacents(_lanceur,true,true);
		}
	}else if(_attaque->qi().contains("MULT")){
		if(_attaque->qi().contains("ADJ")&&diff.r_adjacence_active()){
			liste_=combattants_adjacents(_lanceur,true,true);
		}else{
			foreach(Combattant c,creatures_act.cles()){
				uchar pos_=positions_places.valeur(c).second;
				if(pos_!=arriere&&creatures_act.valeur(c).statut_pk()!="KO"){
					liste_<<c;
				}
			}
			liste_.removeOne(_lanceur);
		}
	}else if(_attaque->qi().contains("ADV")){
		if(_attaque->qi().contains("ADJ")&&diff.r_adjacence_active()){
			liste_=combattants_adjacents(_lanceur,true,false);
		}else{
			foreach(Combattant c,creatures_act.cles()){
				uchar pos_=positions_places.valeur(c).second;
				if(pos_!=arriere&&c.equipe()!=_lanceur.equipe()){
					if(creatures_act.valeur(c).statut_pk()!="KO"){
						liste_<<c;
					}
				}
			}
		}
	}else if(_attaque->qi().contains("PSEUDO GLOBALE")){
		foreach(Combattant c,creatures_act.cles()){
			uchar pos_=positions_places.valeur(c).second;
			if(pos_!=arriere&&creatures_act.valeur(c).statut_pk()!="KO"){
				liste_<<c;
			}
		}
		liste_.removeOne(_lanceur);
	}else if(_attaque->qi().contains("ALLIES")||_attaque->qi().contains("GLOBALE")||_attaque->qi().contains("LANCEUR")){
		liste_<<_lanceur;
	}else{//ALLIE
		foreach(Combattant c,creatures_act.cles()){
			uchar pos_=positions_places.valeur(c).second;
			if(pos_!=arriere&&c.equipe()==_lanceur.equipe()){
				if(creatures_act.valeur(c).statut_pk()!="KO"){
					liste_<<c;
				}
			}
		}
		liste_.removeOne(_lanceur);
	}
	return liste_;
}

QList<Combattant> ElementsCombat::cibles_lanceur(const Combattant& _lanceur,FicheAttaque *_attaque)const{//elt
	QList<Combattant> liste_;
	if(_attaque->qi().contains("UNIQUE IMPORTE")){
		liste_<<positions_places.cles(creatures_act.valeur(_lanceur).cibles()[0])[0];
	}else if(_attaque->qi().contains("UNIQ")){
		CreatureCombat cr_l_=creatures_act.valeur(_lanceur);
		uchar adv_=adversaire(_lanceur.equipe());
		uchar position_c_=cr_l_.cibles()[0].second;
		if(lanceur_par_ici.valeur(adv_)!=arriere){
			if(!diff.r_adjacence_active()){
				QList<Combattant> cibles_=positions_places.cles(QPair<uchar,uchar>(adv_,lanceur_par_ici.valeur(adv_)));
				if(!cibles_.isEmpty()){
					liste_<<cibles_[0];
				}
			}else{
				Taux abs_=(Taux(lanceur_par_ici.valeur(adv_))-Taux(position_c_)).absolu();
				if(abs_<=Taux(1)){
					QList<Combattant> cibles_=positions_places.cles(QPair<uchar,uchar>(adv_,lanceur_par_ici.valeur(adv_)));
					if(!cibles_.isEmpty()){
						liste_<<cibles_[0];
					}
				}else{
					QList<Combattant> cibles_=positions_places.cles(cr_l_.cibles()[0]);
					if(!cibles_.isEmpty()){
						liste_<<cibles_[0];
					}
				}
			}
		}else{
			QList<Combattant> cibles_=positions_places.cles(cr_l_.cibles()[0]);
			if(!cibles_.isEmpty()){
				liste_<<cibles_[0];
			}
		}
	}else if(_attaque->qi().contains("MULT")){
		if(_attaque->qi().contains("ADJ")&&diff.r_adjacence_active()){
			liste_=combattants_adjacents(_lanceur,true,true);
		}else{
			foreach(Combattant c,creatures_act.cles()){
				uchar pos_=positions_places.valeur(c).second;
				if(pos_!=arriere&&c!=_lanceur){
					if(creatures_act.valeur(c).statut_pk()!="KO"){
						liste_<<c;
					}
				}
			}
		}
	}else if(_attaque->qi().contains("ADV")){
		if(_attaque->qi().contains("ADJ")&&diff.r_adjacence_active()){
			liste_=combattants_adjacents(_lanceur,true,false);
		}else{
			foreach(Combattant c,creatures_act.cles()){
				uchar pos_=positions_places.valeur(c).second;
				if(pos_!=arriere&&c.equipe()!=_lanceur.equipe()){
					if(creatures_act.valeur(c).statut_pk()!="KO"){
						liste_<<c;
					}
				}
			}
		}
	}else if(_attaque->qi().contains("PSEUDO GLOBALE")){
		foreach(Combattant c,creatures_act.cles()){
			uchar pos_=positions_places.valeur(c).second;
			if(pos_!=arriere&&c!=_lanceur){
				if(creatures_act.valeur(c).statut_pk()!="KO"){
					liste_<<c;
				}
			}
		}
	}else if(_attaque->qi().contains("ALLIES")||_attaque->qi().contains("GLOBALE")||_attaque->qi().contains("LANCEUR")){
		liste_<<_lanceur;
	}else{//ALLIE
		QList<Combattant> cibles_=positions_places.cles(creatures_act.valeur(_lanceur).cibles()[0]);
		if(!cibles_.isEmpty()){
			liste_<<cibles_[0];
		}
	}
	return liste_;
}

QList<Combattant> ElementsCombat::combattants_adjacents(const Combattant& _qui,bool _adv_seul,bool _all_seul)const{
	QList<Combattant> combattants_adj_;
	uchar pos_qui_=positions_places.valeur(_qui).second;
	if(_adv_seul==_all_seul){
		foreach(Combattant c,creatures_act.cles()){
			uchar pos_=positions_places.valeur(c).second;
			if(pos_!=arriere&&c!=_qui){
				if((Taux(pos_)-Taux(pos_qui_)).absolu()<=Taux(1)&&creatures_act.valeur(c).statut_pk()!="KO"){
					combattants_adj_<<c;
				}
			}
		}
	}else if(_adv_seul){
		foreach(Combattant c,creatures_act.cles()){
			uchar pos_=positions_places.valeur(c).second;
			if(pos_!=arriere&&c.equipe()!=_qui.equipe()){
				if((Taux(pos_)-Taux(pos_qui_)).absolu()<=Taux(1)&&creatures_act.valeur(c).statut_pk()!="KO"){
					combattants_adj_<<c;
				}
			}
		}
	}else{
		foreach(Combattant c,creatures_act.cles()){
			uchar pos_=positions_places.valeur(c).second;
			if(pos_!=arriere&&c.equipe()==_qui.equipe()&&c.position()!=_qui.position()){
				if((Taux(pos_)-Taux(pos_qui_)).absolu()<=Taux(1)&&creatures_act.valeur(c).statut_pk()!="KO"){
					combattants_adj_<<c;
				}
			}
		}
	}
	return combattants_adj_;
}

bool ElementsCombat::existence_adversaire_non_ko(const QList<Combattant>& _cibles,const Combattant& _combattant)const{
	foreach(Combattant c,_cibles){
		if(c.position()!=arriere&&c.equipe()!=_combattant.equipe()&&creatures_act.valeur(c).statut_pk()!="KO"){
			return true;
		}
	}
	return false;
}

bool ElementsCombat::existence_cible_non_ko(const Combattant& _lanceur,FicheAttaque *_f_att)const{
	typedef QPair<uchar,uchar> Position;
	//cibles_lanceur(const Combattant& _lanceur,FicheAttaque *_attaque)
	QList<Combattant> cibles_=cibles_lanceur(_lanceur,_f_att);//creatures_act.valeur(_lanceur).cibles()
	if(_f_att->qi().contains("MULT")||_f_att->qi().contains("ADV")||_f_att->qi().contains("PSEUDO GLOBALE")){
		foreach(Combattant c,cibles_){
			if(creatures_act.valeur(c).statut_pk()!="KO"&&c.equipe()!=_lanceur.equipe()){
				return true;
			}
		}
		return false;
	}
	if(_f_att->qi().contains("ALLIES")||_f_att->qi().contains("LANCEUR")||_f_att->qi().contains("GLOBALE")){
		return true;
	}
	foreach(Combattant c,cibles_){
		if(creatures_act.valeur(c).statut_pk()!="KO"){
			return true;
		}
	}
	return false;
}

bool ElementsCombat::existence_cible_dort(const Combattant& _lanceur,Donnees *_d)const{
	CreatureCombat cr_l_=creatures_act.valeur(_lanceur);
	foreach(Combattant c,creatures_act.cles()){
		if(cibles_lanceur(_lanceur,_d).contains(c)&&creatures_act.valeur(c).statut_pk()=="SOMMEIL"){
			return true;
		}
	}
	return false;
}

bool ElementsCombat::existence_combattant_ut_non_ko_contre_1_adv()const{
	foreach(uchar c,combattants_contre_adv.cles()){
		foreach(uchar c2,combattants_contre_adv.valeur(c)){
			if(creatures_act.valeur(Combattant(ut,c2)).statut_pk()!="KO"&&positions_places.valeur(Combattant(ut,c2)).second!=arriere){
				return true;
			}
		}
	}
	return false;
}

bool ElementsCombat::existence_ut_non_ko()const{
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==ut&&creatures_act.valeur(c).statut_pk()!="KO"){
			return true;
		}
	}
	return false;
}

bool ElementsCombat::existence_ut_non_ko_contre_1_adv()const{
	foreach(uchar c,combattants_contre_adv.cles()){
		foreach(uchar c2,combattants_contre_adv.valeur(c)){
			if(creatures_act.valeur(Combattant(ut,c2)).statut_pk()!="KO"){
				return true;
			}
		}
	}
	return false;
}

bool ElementsCombat::existence_entrave(const Combattant& _lanceur,const QString& _attaque_lanceur)const{
	foreach(Combattant c,creatures_act.cles()){
		QPair<QString,QPair<bool,uchar> > entr_=creatures_act.valeur(c).cible_atts(QPair<QString,Combattant>("ENTRAVE",_lanceur));
		if(entr_.first==_attaque_lanceur&&entr_.second.first){
			return true;
		}
	}
	return false;
}

QPair<bool,bool> ElementsCombat::existence_eq_ko()const{
	QPair<bool,bool> ko_(false,false);
	bool eq_ko_=true;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==adv&&creatures_act.valeur(c).statut_pk()!="KO"){
			eq_ko_=false;
			break;
		}
	}
	ko_.first=eq_ko_;
	eq_ko_=true;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==ut&&creatures_act.valeur(c).statut_pk()!="KO"){
			eq_ko_=false;
			break;
		}
	}
	ko_.second=eq_ko_;
	return ko_;
}

bool ElementsCombat::existence_attaque_meme_eq(const Combattant& _cible,const QString& _attaque)const{
	foreach(Combattant c,creatures_act.cles()){
		if(_cible.equipe()==c.equipe()){
			CreatureCombat cr_c_=creatures_act.valeur(c);
			if(cr_c_.att_choisie()==_attaque&&cr_c_.att_reussie()){
				return true;
			}
		}
	}
	return false;
}

bool ElementsCombat::existence_pk_arriere_non_ko(const Combattant& _cible)const{
	foreach(Combattant c,creatures_act.cles()){
		if(_cible.equipe()==c.equipe()&&positions_places.valeur(c).second==arriere&&creatures_act.valeur(c).statut_pk()!="KO"){
			return true;
		}
	}
	return false;
}

bool ElementsCombat::existence_partenaire_non_ko(const Combattant& _cible)const{
	foreach(Combattant c,creatures_act.cles()){
		if(_cible.equipe()==c.equipe()&&positions_places.valeur(c).second!=arriere&&creatures_act.valeur(c).statut_pk()!="KO"){
			return true;
		}
	}
	return false;
}

bool ElementsCombat::existence_partenaire_front(const Combattant& _cible)const{
	foreach(Combattant c,creatures_act.cles()){
		if(_cible.equipe()==c.equipe()&&positions_places.valeur(c).second!=arriere&&c!=_cible){
			return true;
		}
	}
	return false;
}

QPair<QString,uchar> ElementsCombat::existence_pk_eq_lumargile_non_embargo(uchar _equipe,Donnees *_d)const{
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==_equipe){
			CreatureCombat cr_c_=creatures_act.valeur(c);
			if(cr_c_.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
				ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_c_.fiche_objet(_d));
				if(obj_&&obj_->nb_trs_prot()>0){
					return QPair<QString,uchar>(cr_c_.objet(),obj_->nb_trs_prot());
				}
			}		
		}
	}
	return QPair<QString,uchar>("",0);
}

//il existe un pokemon ayant l'objet permettant d'augmenter le nombre de tour pour ce climat et pas sous embargo
bool ElementsCombat::existence_pk_eq_climat_non_embargo(Donnees *_d)const{
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat cr_c_=creatures_act.valeur(c);
		if(cr_c_.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
			ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_c_.fiche_objet(_d));
			if(obj_&&obj_->nb_trs_cl().contains(valeur_climat())){
				return true;
			}
		}
	}
	return false;
}

bool ElementsCombat::existe_pk_ut_rempl()const{
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==ut&&positions_places.valeur(c).second==arriere){
			return true;
		}
	}
	return false;
}

Combattant ElementsCombat::tirage_envoi(uchar _equipe)const{
	MonteCarlo<Combattant> loi_;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==_equipe&&positions_places.valeur(c).second==arriere&&creatures_act.valeur(c).statut_pk()!="KO"){
			loi_.ajouter_event(QPair<Combattant,Entier>(c,Entier(1)));
		}
	}
	return loi_.tirage();
}

Combattant ElementsCombat::tirage_front_adv(uchar _equipe)const{
	MonteCarlo<Combattant> loi_;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==_equipe&&positions_places.valeur(c).second!=arriere&&creatures_act.valeur(c).statut_pk()!="KO"){
			loi_.ajouter_event(QPair<Combattant,Entier>(c,Entier(1)));
		}
	}
	return loi_.tirage();
}

bool ElementsCombat::tirage_capture(const Taux& coeff,uchar nb_rebond_max){
	Taux proba_(1);
	for(int i=0;i<nb_rebond_max;i++){
		proba_*=coeff;
	}
	MonteCarlo<bool> loi_;
	Entier proba_1_=proba_.gnumerateur();
	Entier proba_2_=proba_.gdenominateur()-proba_1_;
	loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi_.tirage();
}

bool ElementsCombat::tirage_fuite(const Taux& coeff){
	MonteCarlo<bool> loi_;
	Entier proba_1_=coeff.gnumerateur();
	Entier proba_2_=coeff.gdenominateur()-proba_1_;
	loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi_.tirage();
}

bool ElementsCombat::existe_pk_avec_statut_non_ko(uchar _equipe)const{
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==_equipe){
			QString statut_=creatures_act.valeur(c).statut_pk();
			if(statut_!="OK"&&statut_!="KO"){
				return true;
			}
		}
	}
	return false;
}

bool ElementsCombat::cible_de_a_la_queue(const Combattant& _combattant,Donnees *_d)const{
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat cr_c_=creatures_act.valeur(c);
		if(cibles_lanceur(c,_d).contains(_combattant)&&cr_c_.att_choisie()=="A_LA_QUEUE"&&cr_c_.att_reussie()&&cr_c_.statut_pk()!="KO"){
			return true;
		}
	}
	return false;
}

QList<Combattant> ElementsCombat::ordre_non_joue(Donnees *_d,bool _a_la_queue)const{
	QList<Combattant> ls_;
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat cr_c_=creatures_act.valeur(c);
		if(cr_c_.act_choisie()=="ATTAQUE"){
			FicheAttaque *f_att_=_d->val_attaques().valeur(cr_c_.att_choisie());;
			if(existence_cible_non_ko(c,f_att_)&&cr_c_.statut_pk()!="KO"&&_a_la_queue==cible_de_a_la_queue(c,_d)){
				if(!cr_c_.peur_pk()&&cr_c_.non_switch_force_pk()&&!cr_c_.a_joue_pk()){
					ls_<<c;;
				}
			}
		}else{
			if((cr_c_.act_choisie()=="SWITCH"||cr_c_.act_choisie()=="SOIN")&&(cr_c_.statut_pk()!="KO"||cr_c_.act_choisie()=="SOIN")&&_a_la_queue==cible_de_a_la_queue(c,_d)){
				if(!cr_c_.peur_pk()&&cr_c_.non_switch_force_pk()&&!cr_c_.a_joue_pk()){
					ls_<<c;;
				}
			}
		}
	}
	return ls_;
}

Combattant ElementsCombat::chercher_cible_apres_vous(const Combattant& _dernier_lanceur,Donnees *_d)const{
	QList<Combattant> cibles_=cibles_lanceur(_dernier_lanceur,_d);
	if(cibles_.isEmpty()){
		return Combattant();
	}
	Combattant cible_=cibles_[0];
	QList<Combattant> cbts_=ordre_non_joue(_d,true);
	cbts_<<ordre_non_joue(_d,false);
	CreatureCombat cr_l_=creatures_act.valeur(_dernier_lanceur);
	if(cible_!=Combattant()&&cbts_.contains(cible_)&&cr_l_.att_choisie()=="APRES_VOUS"&&cr_l_.att_reussie()){
		return cible_;
	}
	return Combattant();
}

QStringList ElementsCombat::calcul_attaques_equipe(const Combattant& _lanceur)const{
	QStringList ls_;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe() == _lanceur.equipe()){
			CreatureCombat cr_c_=creatures_act.valeur(c);
			if(cr_c_.act_choisie()=="ATTAQUE"){
				ls_<<cr_c_.att_choisie();
			}
		}
	}
	return ls_;
}

QList<Combattant> ElementsCombat::trier_ordre_non_joue(bool _a_la_queue,Donnees *_d)const{
	QList<Combattant> ls_=ordre_non_joue(_d,_a_la_queue);
	if(ls_.isEmpty()){
		return ls_;
	}
	int nb_=ls_.size();
	bool zone_magique_=effet_global("ZONE_MAGIQUE").second;
	bool distorsion_=effet_global("DISTORSION").second;
	for(int i=0;i<nb_;i++){
		for(int j=i+1;j<nb_;j++){//j>i
			Combattant cb1_=ls_[i];
			uchar eq1_=cb1_.equipe();;
			CreatureCombat cr_cb1_=creatures_act.valeur(cb1_);
			QString action1_=cr_cb1_.act_choisie();
			QString attaque1_=cr_cb1_.att_choisie();
			QList<Combattant> cibles1_=cibles_lanceur(cb1_,_d);
			FicheCapacite *capac1_=cr_cb1_.fiche_capacite(_d);
			ObjetAttachableCombat *obj1_=NULL;
			bool peut_att_der_1_=false;
			bool lent1_=capac1_&&capac1_->lent();
			if(cr_cb1_.objet()!=""){
				obj1_=qobject_cast<ObjetAttachableCombat*>(cr_cb1_.fiche_objet(_d));
				peut_att_der_1_=cr_cb1_.peut_utiliser_objet(zone_magique_)&&obj1_&&obj1_->att_der();
			}
			Combattant cb2_=ls_[j];
			uchar eq2_=cb2_.equipe();;
			CreatureCombat cr_cb2_=creatures_act.valeur(cb2_);
			QString action2_=cr_cb2_.act_choisie();
			QString attaque2_=cr_cb2_.att_choisie();
			QList<Combattant> cibles2_=cibles_lanceur(cb2_,_d);
			FicheCapacite *capac2_=cr_cb2_.fiche_capacite(_d);
			ObjetAttachableCombat *obj2_=NULL;
			bool peut_att_der_2_=false;
			bool lent2_=capac2_&&capac2_->lent();
			if(cr_cb2_.objet()!=""){
				obj2_=qobject_cast<ObjetAttachableCombat*>(cr_cb2_.fiche_objet(_d));
				peut_att_der_2_=cr_cb2_.peut_utiliser_objet(zone_magique_)&&obj2_&&obj2_->att_der();
			}
			if(action2_=="SOIN"&&action1_=="SOIN"){
				if(attaque2_=="SOIN_EQUIPE"&&attaque1_!="SOIN_EQUIPE"&&cb1_.equipe()==cb2_.equipe()){
					ls_.swap(i,j);
				}
			}else if(action2_=="SOIN"&&action1_!="SOIN"){
				ls_.swap(i,j);
			}else if(action2_!="SOIN"&&action1_!="SOIN"){
				if(attaque2_=="POURSUITE"&&creatures_act.valeur(cibles2_[0]).act_choisie()=="SWITCH"){
					if(attaque1_!="POURSUITE"||creatures_act.valeur(cibles1_[0]).act_choisie()!="SWITCH"){
						ls_.swap(i,j);
					}else{
						Taux vitesse1_=cr_cb1_.vitesse(attaque_equipe(adversaire(eq1_),"AIRE_EAU_HERBE").second,zone_magique_,attaque_equipe(eq1_,"VENT_ARRIERE").second,climat,_d);
						Taux vitesse2_=cr_cb2_.vitesse(attaque_equipe(adversaire(eq2_),"AIRE_EAU_HERBE").second,zone_magique_,attaque_equipe(eq2_,"VENT_ARRIERE").second,climat,_d);
						if(lent1_&&!lent2_){
							ls_.swap(i,j);
						}else if(lent1_==lent2_){
							if(peut_att_der_1_&&!peut_att_der_2_){
								ls_.swap(i,j);
							}else if(peut_att_der_1_==peut_att_der_2_){
								if(vitesse2_>vitesse1_){
									ls_.swap(i,j);
								}
							}
						}
					}
				}else if(attaque2_!="POURSUITE"||creatures_act.valeur(cibles2_[0]).act_choisie()!="SWITCH"){
					if(attaque1_!="POURSUITE"||creatures_act.valeur(cibles1_[0]).act_choisie()!="SWITCH"){
						if(action1_!="SWITCH"&&action2_=="SWITCH"){
							ls_.swap(i,j);
						}else if(action1_=="SWITCH"&&action2_=="SWITCH"){
							Taux vitesse1_=cr_cb1_.vitesse(attaque_equipe(adversaire(eq1_),"AIRE_EAU_HERBE").second,zone_magique_,attaque_equipe(eq1_,"VENT_ARRIERE").second,climat,_d);
							Taux vitesse2_=cr_cb2_.vitesse(attaque_equipe(adversaire(eq2_),"AIRE_EAU_HERBE").second,zone_magique_,attaque_equipe(eq2_,"VENT_ARRIERE").second,climat,_d);
							;
							if(vitesse2_<vitesse1_){
								ls_.swap(i,j);
							}
						}else if(action1_!="SWITCH"&&action2_!="SWITCH"){
							FicheAttaque *f_att_1_=_d->val_attaques().valeur(attaque1_);
							FicheAttaque *f_att_2_=_d->val_attaques().valeur(attaque2_);
							int nb1_=0;
							int nb2_=0;
							if(capac1_&&capac1_->som_pr().cles().contains(f_att_1_->cat())){
								nb1_+=capac1_->som_pr().valeur(f_att_1_->cat());
							}
							if(capac2_&&capac2_->som_pr().cles().contains(f_att_2_->cat())){
								nb2_+=capac2_->som_pr().valeur(f_att_2_->cat());
							}
							if(f_att_2_->prio()+nb2_>f_att_1_->prio()+nb1_){
								ls_.swap(i,j);
							}else if(f_att_2_->prio()+nb2_==f_att_1_->prio()+nb1_){
								if(lent1_&&!lent2_){
									ls_.swap(i,j);
								}else if(lent1_==lent2_){
									if(peut_att_der_1_&&!peut_att_der_2_){
										ls_.swap(i,j);
									}else if(peut_att_der_1_==peut_att_der_2_){
										Taux vitesse1_=cr_cb1_.vitesse(attaque_equipe(adversaire(eq1_),"AIRE_EAU_HERBE").second,zone_magique_,attaque_equipe(eq1_,"VENT_ARRIERE").second,climat,_d);
										Taux vitesse2_=cr_cb2_.vitesse(attaque_equipe(adversaire(eq2_),"AIRE_EAU_HERBE").second,zone_magique_,attaque_equipe(eq2_,"VENT_ARRIERE").second,climat,_d);
										if((vitesse2_>vitesse1_)!=distorsion_&&vitesse2_!=vitesse1_){
											ls_.swap(i,j);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return ls_;
}

void ElementsCombat::calcul_experience_ev(const QList<Combattant>& _ensemble_front,const Combattant& _adversaire,Donnees *_d,uchar _max_niv,uchar _max_ev){
	QList<Combattant> ensemble_front_;
	foreach(Combattant c,_ensemble_front){
		if(creatures_act.valeur(c).niveau_pk()<_max_niv){
			ensemble_front_<<c;
		}
	}
	if(ensemble_front_.isEmpty()){
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==ut&&creatures_act.valeur(c).niveau_pk()<_max_niv){
				ensemble_front_<<c;
			}
		}
	}
	if(ensemble_front_.isEmpty()){
		return;
	}
	CreatureCombat& cr_a_=creatures_act.valeur(_adversaire);
	FichePokemon *f_adv_=cr_a_.fiche_pokemon(_d);
	uchar niv_adv_=cr_a_.niveau_pk();
	Taux base_exp_=Taux(f_adv_->pt_base()*niv_adv_)*diff.r_coeff_gain_pts_exp_combat();
	if(type_combat.startsWith("DRESSEUR")){
		base_exp_*=Taux(3,2LL)*Taux(multiplicite);
	}
	Taux taux_exp_mult_exp_(0);
	int nb_porteurs_=nb_pk_ut_multiexp_niv(_d,_max_niv);
	if(nb_porteurs_>0){
		taux_exp_mult_exp_=Taux(1,1LL+nb_porteurs_);
	}
	Taux exp_mult_exp_=taux_exp_mult_exp_*base_exp_;
	Taux exp_mult_exp_reste_=base_exp_-exp_mult_exp_*Taux(nb_porteurs_);
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==ut){
			CreatureCombat& cr_=creatures_act.valeur(c);
			if(cr_.objet()!=""){
				ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_.fiche_objet(_d));
				if(obj_&&obj_->calc_exp()){
					uchar niv_=cr_.niveau_pk();
					if(niv_<_max_niv){
						cr_.gain_exp((exp_mult_exp_*diff.taux_gain(niv_adv_,niv_)).partie_entiere()+Entier(1));
					}
					foreach(QString s,cr_.ev_statistiques_pk().cles()){
						if(!obj_->mult_gn_ev().estNul()){
							cr_.gain_ev_statistique(s,Taux(f_adv_->stat_ev().valeur(s).second)*obj_->mult_gn_ev(),_max_ev);
						}else{
							cr_.gain_ev_statistique(s,f_adv_->stat_ev().valeur(s).second,_max_ev);
						}
					}
				}
			}
		}
	}
	foreach(Combattant c,ensemble_front_){
		CreatureCombat& cr_=creatures_act.valeur(c);
		uchar niv_=cr_.niveau_pk();
		Taux exp_mult_exp_reste_ut_=exp_mult_exp_reste_*diff.taux_gain(niv_adv_,niv_);
		if(cr_.objet()!=""){
			ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_.fiche_objet(_d));
			if(obj_&&!obj_->mult_gain_exp().estNul()){
				cr_.gain_exp((exp_mult_exp_reste_ut_*obj_->mult_gain_exp()*Taux(1LL,(long long)ensemble_front_.size())).partie_entiere()+Entier(1));
			}else{
				cr_.gain_exp((exp_mult_exp_reste_ut_*Taux(1LL,(long long)ensemble_front_.size())).partie_entiere()+Entier(1));
			}
		}else{
			cr_.gain_exp((exp_mult_exp_reste_ut_*Taux(1LL,(long long)ensemble_front_.size())).partie_entiere()+Entier(1));
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==ut){
			CreatureCombat& cr_=creatures_act.valeur(c);
			Taux pv_=cr_.pv_max();
			if(ensemble_front_.contains(c)){
				if(cr_.objet()!=""){
					ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_.fiche_objet(_d));
					if(obj_&&obj_->calc_exp()){
						foreach(QString s,cr_.ev_statistiques_pk().cles()){
							if(!obj_->mult_gn_ev().estNul()){
								cr_.gain_ev_statistique(s,Taux(f_adv_->stat_ev().valeur(s).second)*obj_->mult_gn_ev(),_max_ev);
							}else{
								cr_.gain_ev_statistique(s,f_adv_->stat_ev().valeur(s).second,_max_ev);
							}
						}
					}else{
						foreach(QString s,cr_.ev_statistiques_pk().cles()){
							cr_.gain_ev_statistique(s,f_adv_->stat_ev().valeur(s).second,_max_ev);
						}
					}
				}else{
					foreach(QString s,cr_.ev_statistiques_pk().cles()){
						cr_.gain_ev_statistique(s,f_adv_->stat_ev().valeur(s).second,_max_ev);
					}
				}
			}
			if(cr_.objet()!=""){
				ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_.fiche_objet(_d));
				if(obj_){
					foreach(QString s,obj_->gain_ev_cbt().cles()){
						cr_.gain_ev_statistique(s,obj_->gain_ev_cbt().valeur(s),_max_ev);
					}
				}
			}
			cr_.mettre_jour_pv_restants2(_d,pv_);
		}
	}
}


int ElementsCombat::nb_pk_ut_multiexp_niv(Donnees *_d,uchar _max_niv)const{
	int nb_=0;
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat cr_=creatures_act.valeur(c);
		if(c.equipe()==ut&&cr_.objet()!=""&&cr_.niveau_pk()<_max_niv){
			ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_.fiche_objet(_d));
			if(obj_&&obj_->calc_exp()){
				nb_++;
			}
		}
	}
	return nb_;
}

Taux ElementsCombat::calcul_coeff_fuite(Donnees *_d)const{
	CreatureCombat cr_u_=creatures_act.valeur(positions_places.cles(QPair<uchar,uchar>(ut,0))[0]);
	CreatureCombat cr_a_=creatures_act.valeur(positions_places.cles(QPair<uchar,uchar>(adv,0))[0]);
	bool zone_magique_=effet_global("ZONE_MAGIQUE").second;
	Taux coeff_=cr_u_.vitesse(attaque_equipe(ut,"AIRE_EAU_HERBE").second,zone_magique_,attaque_equipe(ut,"VENT_ARRIERE").second,climat,_d)*Taux(256);
	coeff_/=cr_a_.vitesse(attaque_equipe(adv,"AIRE_EAU_HERBE").second,zone_magique_,attaque_equipe(adv,"VENT_ARRIERE").second,climat,_d);
	return coeff_+Taux(30*fuite);
}

bool ElementsCombat::protege_contre_amour(const CreatureCombat& _cible,const CreatureCombat& _lanceur,const QString& _n_capac_c,FicheCapacite *_f_capac_c,FicheCapacite *_f_capac_l)const{
	if(_cible.genre_pk()==_lanceur.genre_pk()){
		return true;
	}
	if(_cible.genre_pk()=="ASSEXUE"||_lanceur.genre_pk()=="ASSEXUE"){
		return true;
	}
	if(!_f_capac_c){
		return false;
	}
	//if(!climat.second.first){
	if(_f_capac_c->immu_stat().cles().contains(valeur_climat())){
		if(!_f_capac_c->immu_stat().valeur(valeur_climat()).contains("AMOUR")){
			return false;
		}
	}
	if(!_f_capac_l){
		return true;
	}
	return !_f_capac_l->capac_ign().contains(_n_capac_c);
}

bool ElementsCombat::ne_peut_pas_dormir(const CreatureCombat& _cr,Donnees *_d)const{
	FicheCapacite *f_capac_=_cr.fiche_capacite(_d);
	if(f_capac_&&f_capac_->immu_att().contains("BROUHAHA")){
		return false;
	}
	if(_cr.statut_pk()=="SOMMEIL"){
		return false;
	}
	foreach(Combattant c,creatures_act.cles()){
		if(creatures_act.valeur(c).attaques_actives_def("BROUHAHA").second){
			return true;
		}
	}
	return false;
}

QString ElementsCombat::valeur_climat()const{
	if(climat.second.first){
		return climat.first.first;
	}
	return "";
}

bool ElementsCombat::traiter_reussite_seul_effet_statut(const CreatureCombat& _lanceur,FicheCapacite *_f_capac_l,const CreatureCombat& _cible,const QString& _capac_c,FicheCapacite *_f_capac_c,uchar _equipe_c,const QString& _att_lanc,const QString& _statut,bool _effet_l,const QStringList& _statuts_poss,bool _pseudo_statut,Donnees *_d)const{
	bool reussi_=true;
	if(_effet_l){
		if(_lanceur.statut_pk()==_statut){
			reussi_=false;
		}else if(_f_capac_l&&_f_capac_l->immu_stat().cles().contains(valeur_climat())){
			if(_f_capac_l->immu_stat().valeur(valeur_climat()).contains(_statut)){
				reussi_=false;
			}else if(ne_peut_pas_dormir(_cible,_d)&&_statuts_poss==QStringList("SOMMEIL")){
				reussi_=false;
			}
		}else if(ne_peut_pas_dormir(_cible,_d)&&_statuts_poss==QStringList("SOMMEIL")){
			reussi_=false;
		}
	}else{
		if(attaque_equipe(_equipe_c,"RUNE_PROTECT").second&&!_f_capac_l->att_ign().contains("RUNE_PROTECT")){
			reussi_=false;
		}else if(_cible.statut_pk()!="OK"&&!_pseudo_statut){
			reussi_=false;
		}else if(!_cible.clone_pk().estNul()&&_att_lanc!="VENT_VIOLENT"){
			reussi_=false;
		}else if(!_f_capac_l||!_f_capac_l->capac_ign().contains(_capac_c)){
			if(_f_capac_c&&_f_capac_c->immu_stat().cles().contains(valeur_climat())){
				if(_f_capac_l->immu_stat().valeur(valeur_climat()).contains(_statut)){
					if(!_pseudo_statut||_cible.confusion_pk().second){
						reussi_=false;
					}
				}
			}else{
				if(Utilitaire::intersection<QString>(_d->val_types_immu().valeur("TYPES_IMMU_"+_statut),_cible.types_pk()).isEmpty()){
					reussi_=false;
				}else if(valeur_climat()=="SOLEIL"&&_statut=="GEL"){
					reussi_=false;
				}
			}
		}
	}
	return reussi_;
}

bool ElementsCombat::traiter_reussite_seul_effet_statut(const CreatureCombat& _cible,FicheCapacite *_f_capac_c,uchar _equipe_c,const QString& _statut,bool _pseudo_statut,Donnees *_d,bool _effet_l,bool _ignore)const{
	bool reussi_=true;
	if(_effet_l){
		if(_cible.statut_pk()==_statut){
			reussi_=false;
		}else if(_f_capac_c&&_f_capac_c->immu_stat().cles().contains(valeur_climat())){
			if(_f_capac_c->immu_stat().valeur(valeur_climat()).contains(_statut)){
				reussi_=false;
			}else if(ne_peut_pas_dormir(_cible,_d)&&_statut=="SOMMEIL"){
				reussi_=false;
			}
		}else if(ne_peut_pas_dormir(_cible,_d)&&_statut=="SOMMEIL"){
			reussi_=false;
		}
	}else{
		if(attaque_equipe(_equipe_c,"RUNE_PROTECT").second){
			reussi_=false;
		}else if(_cible.statut_pk()!="OK"&&!_pseudo_statut){
			reussi_=false;
		}else if(!_cible.clone_pk().estNul()){
			reussi_=false;
		}else if(!_ignore&&_f_capac_c&&_f_capac_c->immu_stat().cles().contains(valeur_climat())){
			if(_f_capac_c->immu_stat().valeur(valeur_climat()).contains(_statut)){
				if(!_pseudo_statut||_cible.confusion_pk().second){
					reussi_=false;
				}
			}
		}else{
			if(Utilitaire::intersection<QString>(_d->val_types_immu().valeur("TYPES_IMMU_"+_statut),_cible.types_pk()).isEmpty()){
				reussi_=false;
			}else if(valeur_climat()=="SOLEIL"&&_statut=="GEL"){
				reussi_=false;
			}
		}
	}
	return reussi_;
}

QList<Combattant> ElementsCombat::choix_ia_envoi_remplacement()const{
	QList<Combattant> liste_;
	int nb_front_adv_non_ko_=0;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==adv&&positions_places.valeur(c).second!=arriere&&creatures_act.valeur(c).statut_pk()!="KO"){
			nb_front_adv_non_ko_++;
		}
	}
	int nb_front_a_envoyer_=multiplicite-nb_front_adv_non_ko_;
	QList<uchar> liste_tmp_;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==adv&&positions_places.valeur(c).second==arriere&&creatures_act.valeur(c).statut_pk()!="KO"){
			liste_tmp_<<c.position();
		}
	}
	Utilitaire::trier<uchar>(liste_tmp_,true);
	int nb_pk_=Utilitaire::max_min<uchar>(liste_tmp_.size(),nb_front_a_envoyer_).second;
	for(int i=0;i<nb_pk_;i++){
		liste_<<Combattant(adv,liste_tmp_[i]);
	}
	return liste_;
}

QStringList ElementsCombat::traiter_reussite_effet_statistiques(const CreatureCombat& _cible,FicheCapacite *_f_capac_l,uchar _equipe_c,FicheCapacite *_f_capac_c,const QString& _capac_c,FicheAttaque *_att_lanceur,Donnees *_d)const{
	QStringList liste_;
	foreach(Effet *e,_att_lanceur->effs()){
		EffetStatistique *e_=qobject_cast<EffetStatistique*>(e);
		if(e_){
			foreach(QString s,e_->stat_cr().cles()){
				if((_cible.attaques_actives_ind("CLAIRVOYANCE")||_cible.attaques_actives_ind("FLAIR")||_cible.attaques_actives_ind("OEIL_MIRACLE"))&&s=="ESQUIVE"&&e_->stat_cr().valeur(s)>0&&e_->qui()){
					continue;
				}
				if(traiter_reussite_effet_statistique(_cible,_f_capac_l,_equipe_c,_f_capac_c,_capac_c,s,e_->stat_cr().valeur(s),!e_->qui(),_d))
				{
					liste_<<s;
				}
			}
		}
	}
	liste_.removeDuplicates();
	return liste_;
}

bool ElementsCombat::traiter_reussite_effet_statistique(const CreatureCombat& _cible,FicheCapacite *_f_capac_l,uchar _equipe_c,FicheCapacite *_f_capac_c,const QString& _capac_c,const QString& _statistique,qint8 _var,bool _concerne_cible,Donnees *_d)const{
	bool reussi_=true;
	if(attaque_equipe(_equipe_c,"BRUME").second&&!_f_capac_l->att_ign().contains("BRUME")&&_var<0&&_concerne_cible){
		reussi_=false;
	}else if(_f_capac_c->immu_bais_statis().contains(_statistique)){
		if(!_concerne_cible||!_f_capac_l->capac_ign().contains(_capac_c)){
			reussi_=false;
		}
	}else if(_f_capac_c->immu_bais_statis_stat().contains(QPair<QString,QString>(_statistique,_cible.statut_pk()))){
		if(!_concerne_cible||!_f_capac_l->capac_ign().contains(_capac_c)){
			reussi_=false;
		}
	}else if(!_cible.clone_pk().estNul()&&_concerne_cible){
		reussi_=false;
	}else if(_cible.boost(_statistique)==(int)_d->constante_numerique("MIN_BOOST")&&_var<0){
		reussi_=false;
	}else if(_cible.boost(_statistique)==(int)_d->constante_numerique("MAX_BOOST")&&_var>0){
		reussi_=false;
	}
	return reussi_;
}

void ElementsCombat::intimidation(FicheCapacite *_f_capac,uchar _equipe_int,Donnees *_d){
	if(!_f_capac){
		return;
	}
	foreach(QString s,_f_capac->baisse_stat_adv().cles()){
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==_equipe_int&&c.position()!=arriere){
				CreatureCombat& cr_c_=creatures_act.valeur(c);
				FicheCapacite *f_capac_=cr_c_.fiche_capacite(_d);
				if(f_capac_){
					if(f_capac_->mult_statis_bais_stat().cles().contains(s)){
						foreach(QString s2,f_capac_->mult_statis_bais_stat().cles()){
							cr_c_.var_boost(s2,f_capac_->mult_statis_bais_stat().valeur(s2),_d);
						}
					}
					if(!f_capac_->immu_bais_statis().contains(s)){
						if(!f_capac_->immu_bais_statis_stat().contains(QPair<QString,QString>(s,cr_c_.statut_pk()))){
							cr_c_.var_boost(s,-_f_capac->baisse_stat_adv().valeur(s),_d);
						}
					}
				}else{
					cr_c_.var_boost(s,-_f_capac->baisse_stat_adv().valeur(s),_d);
				}
			}
		}
	}
}

void ElementsCombat::reinit(const Combattant& _ch,CreatureCombat& _choix,Donnees *_d){
	if(_choix.att_choisie()=="ATTERRISSAGE"&&_choix.att_reussie()){
		if(_choix.pur_vol_atterr()){
			_choix.types_pk().removeOne("NORMAL");
			_choix.pur_vol_atterr()=false;
		}
		if(_choix.atterrissage().second){
			_choix.types_pk()<<"VOL";
			_choix.atterrissage().second=false;
		}
		_choix.atterrissage().first=false;
	}
	foreach(QString s,_choix.statis_boost()){
		_choix.reinit_boost(s,_d);
	}
	_choix.reinit_immu_attaques_type();
	_choix.attaques_actives_ind("DETREMPAGE")=false;
	_choix.attaques_actives_ind("ANTI_AIR")=false;
	_choix.attaques_actives_ind("TOURMENTE")=false;
	_choix.attaques_actives_ind("RACINES")=false;
	_choix.attaques_actives_ind("VAMPIGRAINE")=false;
	_choix.attaques_actives_ind("MAUDIT")=false;
	_choix.attaques_actives_def("VOL_MAGNETIK")=QPair<uchar,bool>(0,false);
	_choix.attaques_actives_def("EMBARGO")=QPair<uchar,bool>(0,false);
	_choix.attaques_actives_def("BAILLE")=QPair<uchar,bool>(0,false);
	_choix.attaques_actives_def("PROVOC")=QPair<uchar,bool>(0,false);
	_choix.attaques_actives_def("BROUHAHA")=QPair<uchar,bool>(0,false);
	_choix.reinit_nb_tours_poison_grave();
	_choix.reinit_tours_terrain();
	_choix.nb_lancer("STOCKAGE")=0;
	_choix.confusion_pk()=QPair<uchar,bool>(0,false);
	_choix.der_att_lancee()="";
	_choix.reinit_nb_succes_abris();
	_choix.clone_pk()=Taux(0);
	_choix.nec_recharg_pk()=false;
	_choix.disparition_pk()=false;
	_choix.prepa_tour_pk()=false;
	_choix.attaques_actives_def("MANIA")=QPair<uchar,bool>(0,false);
	_choix.attaques_actives_def("COLERE")=QPair<uchar,bool>(0,false);
	_choix.attaques_actives_def("DANSE_FLEUR")=QPair<uchar,bool>(0,false);
	_choix.attaques_actives_def("ROULADE")=QPair<uchar,bool>(0,false);
	_choix.attaques_actives_def("BALL_GLACE")=QPair<uchar,bool>(0,false);
	_choix.coeff_roul_ballglace()=1;
	_choix.annuler_patience();
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		cr_c_.att_active_cible("AMOUR",_ch)=false;
		_choix.att_active_cible("AMOUR",c)=false;
		cr_c_.att_active_cible("CAUCHEMAR",_ch)=false;
		_choix.att_active_cible("CAUCHEMAR",c)=false;
		cr_c_.att_active_cible("VERROUILLAGE",_ch)=false;
		_choix.att_active_cible("VERROUILLAGE",c)=false;
		cr_c_.att_active_cible("LIRE_ESPRIT",_ch)=false;
		_choix.att_active_cible("LIRE_ESPRIT",c)=false;
		cr_c_.att_active_cible("ANTI_FUITE",_ch)=false;
		_choix.att_active_cible("ANTI_FUITE",c)=false;
		cr_c_.poss_pk(_ch).clear();
		_choix.poss_pk(c).clear();
		cr_c_.cible_atts(QPair<QString,Combattant>("ENTRAVE",_ch))=QPair<QString,QPair<bool,uchar> >("",QPair<bool,uchar>(false,0));
		_choix.cible_atts(QPair<QString,Combattant>("ENTRAVE",c))=QPair<QString,QPair<bool,uchar> >("",QPair<bool,uchar>(false,0));
		_choix.cible_atts(QPair<QString,Combattant>("ENCORE",c))=QPair<QString,QPair<bool,uchar> >("",QPair<bool,uchar>(false,0));
	}
	_choix.reinit_copie();
	if(!_choix.attaques_actives_ind("MORPHING")){
		_choix.types_pk()=_choix.fiche_pokemon(_d)->typs();
		_choix.capacite_pk_act()=_choix.capacite_pk_ini();
	}
	typedef QPair<Combattant,QString> CombattantAttaque;
	foreach(CombattantAttaque c,_choix.val_attaques_piegeantes()){
		CreatureCombat& cr_c_=creatures_act.valeur(c.first);
		_choix.att_pieg(c)=QPair<bool,uchar>(false,0);
		cr_c_.att_pieg(QPair<Combattant,QString>(_ch,c.second))=QPair<bool,uchar>(false,0);
	}
}

void ElementsCombat::mise_a_ko(const Combattant& _ch,CreatureCombat& _choix,Donnees *_d){
	reinit(_ch,_choix,_d);
	vengeance_actif.valeur(_ch.equipe()).second=true;
	commentaire_recent+=_choix.nom_pk_act()+" est ko!\n";
	_choix.perte_objet()=false;
	_choix.nb_lancer("TAILLADE")=0;
	_choix.attaques_actives_ind("LILLIPUT")=false;
	_choix.statut_pk()="KO";
	_choix.pv_restants_pk()=Taux(0);
	if(_ch.equipe()==ut){
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==adv){
				combattants_contre_adv.valeur(c.position()).removeOne(_ch.position());
			}
		}
	}
}

void ElementsCombat::retrait(const Combattant& _ch,CreatureCombat& _choix,Donnees *_d){
	FicheCapacite *_f_capac=_choix.fiche_capacite(_d);
	if(_f_capac){
		if(_f_capac->soin_statut_sw()){
			_choix.statut_pk()="OK";
		}
		if(!_f_capac->soin_tx_pvmax_sw().estNul()){
			Taux pv_soignes_(0);
			_choix.soin_pv(_choix.pv_max(),pv_soignes_,_d);
		}
	}
	_choix.desactiver_capacite(false,positions_places,arriere,_d,climat);
	reinit(_ch,_choix,_d);
}

/*void ElementsCombat::traiter_effet_statut(CreatureCombat& _cible,uchar _eq_c,const QString& _capac_c,FicheCapacite *_f_capac_c,CreatureCombat& _lanceur,uchar _eq_l,FicheCapacite *_f_capac_l,EffetStatut *_effet,const QString& _att_l,bool _primaire,Donnees *_d){
	MonteCarlo<QString> loi_
	if(_f_capac_l&&_f_capac_l->mult_pr_eff_sec().cles().contains(true)){
		loi_=_effet->tirage_statut(_f_capac_l->mult_pr_eff_sec().valeur(true),attaque_equipe(_eq_l,"AIRE_EAU_FEU").second,_primaire)
	}else{
		loi_=_effet->tirage_statut(1,attaque_equipe(_eq_l,"AIRE_EAU_FEU").second,_primaire)
		TODO a inserer cas effet d'attaque
	}*/

void ElementsCombat::traiter_effet_statut(const Combattant& _cible_i,CreatureCombat& _cible,uchar _eq_c,CreatureCombat& _lanceur,uchar _eq_l,const MonteCarlo<QString>& _loi,const QString& _att_l,bool _effet_lanceur,Donnees *_d){
	if(_loi.events().contains("OK")){
		return;
	}
	MonteCarlo<QString>  statuts_possibles_;
	QStringList statuts_possibles_2_=_loi.events();
	QString capac_l_=_lanceur.capacite_pk_act();
	QString capac_c_=_cible.capacite_pk_act();
	FicheCapacite *f_capac_c_=_cible.fiche_capacite(_d);
	FicheCapacite *f_capac_l_=_lanceur.fiche_capacite(_d);
	bool pseudo_statut_=true;
	foreach(QString s,_loi.events()){
		pseudo_statut_=_d->val_noms_statuts().filter(QRegExp("^"+s+"\\b")).isEmpty();
		if(traiter_reussite_seul_effet_statut(_lanceur,f_capac_l_,_cible,capac_c_,f_capac_c_,_eq_c,_att_l,s,_effet_lanceur,statuts_possibles_2_,pseudo_statut_,_d)){
			statuts_possibles_.ajouter_event(QPair<QString,Entier>(s,_loi.proba_event(s)));
		}
	}
	if(statuts_possibles_.events().isEmpty()){
		return;
	}
	QString statut_=_loi.tirage();
	pseudo_statut_=_d->val_noms_statuts().filter(QRegExp("^"+statut_+"\\b")).isEmpty();
	if(_att_l=="REPOS"){
		_lanceur.pv_restants_pk()=_lanceur.pv_max();
		_lanceur.statut_pk()="SOMMEIL";
		return;
	}
	if(_cible.statut_pk()=="OK"&&!pseudo_statut_){
		_cible.statut_pk()=statut_;
		if(traiter_reussite_seul_effet_statut(_cible,f_capac_c_,_lanceur,capac_l_,f_capac_l_,_eq_l,_att_l,statut_,_effet_lanceur,statuts_possibles_2_,pseudo_statut_,_d)){
			if(f_capac_c_&&f_capac_c_->transf_statut().cles().contains(statut_)){
				_lanceur.statut_pk()=f_capac_c_->transf_statut().valeur(statut_);
			}
		}
	}
	if(pseudo_statut_&&statut_=="CONFUSION"&&traiter_reussite_seul_effet_statut(_lanceur,f_capac_l_,_cible,capac_c_,f_capac_c_,_eq_c,_att_l,statut_,_effet_lanceur,statuts_possibles_2_,pseudo_statut_,_d)){
		_cible.confusion_pk()=QPair<uchar,bool>(0,true);
	}
	if(_cible.clone_pk().estNul()&&!_cible.peur_pk()&&statut_=="PEUR"&&(ordre_non_joue(_d,true).contains(_cible_i)||ordre_non_joue(_d,false).contains(_cible_i))){
		bool passe_=false;
		if(!f_capac_c_||!f_capac_c_->immu_stat().cles().contains(valeur_climat())){
			passe_=true;
		}else if(!f_capac_c_->immu_stat().valeur(valeur_climat()).contains(statut_)){
			passe_=true;
		}else if(f_capac_l_&&f_capac_l_->capac_ign().contains(capac_c_)){
			passe_=true;
		}
		if(passe_){
			_cible.peur_pk()=true;
			_cible.annuler_patience();
			if(f_capac_c_){
				typedef QPair<QString,QPair<QString,qint8> > StatistiqueStatut;
				foreach(StatistiqueStatut s,f_capac_c_->mult_statis_statut_cran()){
					if(s.second.first=="PEUR"){
						_cible.var_boost(s.first,s.second.second,_d);
					}
				}
			}
		}
	}
}

void ElementsCombat::traiter_effet_statist(CreatureCombat& _cible,CreatureCombat& _lanceur,uchar _eq_l,EffetStatistique *_effet_en_cours,bool _primaire,Donnees *_d){
	bool continuer_=true;
	if(!_primaire){
		Taux mult_(1);
		if(attaque_equipe(_eq_l,"AIRE_EAU_FEU").second){
			mult_*=Taux(2);
		}
		FicheCapacite *f_capac_l_=_lanceur.fiche_capacite(_d);
		if(f_capac_l_&&f_capac_l_->mult_pr_eff_sec().cles().contains(true)){
			mult_*=f_capac_l_->mult_pr_eff_sec().valeur(true);
		}
		Taux pr_act_=_effet_en_cours->pr_ac()*mult_;
		if(pr_act_<Taux(1)){
			Entier proba_1_=pr_act_.gnumerateur();
			Entier proba_2_=pr_act_.gdenominateur()-proba_1_;
			MonteCarlo<bool> loi_;
			loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
			loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
			continuer_=loi_.tirage();
		}
	}
	if(!continuer_){
		return;
	}
	if(!_effet_en_cours->qui()){
		//HashMap<QString,qint8> stat_cr()const
		bool existe_baisse_=false;
		foreach(QString s,_effet_en_cours->stat_cr().cles()){
			if(_effet_en_cours->stat_cr().valeur(s)<0){
				existe_baisse_=true;
			}
		}
		FicheCapacite *f_capac_c_=_cible.fiche_capacite(_d);
		if(existe_baisse_&&f_capac_c_){
			existe_baisse_=false;
			foreach(QString s,_effet_en_cours->stat_cr().cles()){
				if(_effet_en_cours->stat_cr().valeur(s)<0&&f_capac_c_->mult_statis_bais_stat().cles().contains(s)){
					existe_baisse_=true;
				}
			}
			if(existe_baisse_){
				foreach(QString s,f_capac_c_->mult_statis_bais_stat().cles()){
					if(s!="COUP_CRITIQUE"){
						_cible.var_boost(s,f_capac_c_->mult_statis_bais_stat().valeur(s),_d);
					}else{
						_cible.r_boost_cc()+=f_capac_c_->mult_statis_bais_stat().valeur(s);
					}
				}
			}
		}
		if(!existe_baisse_||!_cible.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
			foreach(QString s,_effet_en_cours->stat_cr().cles()){
				if(s!="COUP_CRITIQUE"){
					_cible.var_boost(s,_effet_en_cours->stat_cr().valeur(s),_d);
				}else{
					_cible.r_boost_cc()+=_effet_en_cours->stat_cr().valeur(s);
				}
			}
		}else{
			ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(_cible.fiche_objet(_d));
			if(!obj_||!obj_->immu_bais_stat()){
				foreach(QString s,_effet_en_cours->stat_cr().cles()){
					if(s!="COUP_CRITIQUE"){
						_cible.var_boost(s,_effet_en_cours->stat_cr().valeur(s),_d);
					}else{
						_cible.r_boost_cc()+=_effet_en_cours->stat_cr().valeur(s);
					}
				}
			}else{
				_cible.val_der_objet_ut()=_cible.objet();
				_cible.objet()="";
				_cible.perte_objet()=true;
			}
		}
	}else{
		FicheCapacite *f_capac_l_=_lanceur.fiche_capacite(_d);
		foreach(QString s,_effet_en_cours->stat_cr().cles()){
			qint8 cran_=_effet_en_cours->stat_cr().valeur(s);
			Taux mult_(1);
			if(f_capac_l_){
				mult_*=f_capac_l_->taux_act(cran_<0);
			}
			mult_*=Taux(cran_);
			if(s!="COUP_CRITIQUE"){
				_lanceur.var_boost(s,mult_,_d);
			}else{
				_lanceur.r_boost_cc()+=mult_;
			}
		}
		if(_primaire){
			QString nom_att_=_lanceur.att_choisie();
			FicheAttaque *f_att_=_d->val_attaques().valeur(nom_att_);
			for(int i=1;i<f_att_->effs().size();i++){
				EffetMultPuissAttaque *effet_sec_=qobject_cast<EffetMultPuissAttaque*>(f_att_->effs()[i]);
				if(effet_sec_&&effet_sec_->n_subi()){
					_lanceur.r_coeff_att_types_lancees(effet_sec_->tp())*=effet_sec_->co();
				}
			}
		}
	}
}

void ElementsCombat::ss_methode_envoi(const Combattant& _ch,CreatureCombat& _choix,bool _capac_act,Donnees *_d){
	//changer numero front
	uchar equipe_adv_=adversaire(_ch.equipe());
	_choix.reinit_table_eff(_d,arriere);
	FicheCapacite *f_capac_=_choix.fiche_capacite(_d);
	if(_choix.statut_pk()=="SOMMEIL"){
		foreach(Combattant c,creatures_act.cles()){
			if(creatures_act.valeur(c).attaques_actives_def("BROUHAHA").second){
				if(!_capac_act||!f_capac_||!f_capac_->immu_att().contains("BROUHAHA")){
					_choix.statut_pk()="OK";
				}
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		creatures_act.valeur(c).ajouter_table_eff(_ch,_d);
	}
	if(_capac_act){
		if(f_capac_&&f_capac_->clim()!=""){
			if(climat.first.first!=""){
				climat.first.second=0;
			}
			climat.first.first=f_capac_->clim();
			climat.second.second=true;
			climat.second.first=!existence_anti_climat_actif(_d);
			if(climat.second.first){
				QString n_cl_=climat.first.first;
				foreach(Combattant c,creatures_act.cles()){
					//chgt_type_clim()
					CreatureCombat& cr_c_=creatures_act.valeur(c);
					FicheCapacite *f_capac_c_=cr_c_.fiche_capacite(_d);
					if(f_capac_c_&&f_capac_c_->chgt_type_clim().cles().contains(n_cl_)){
						cr_c_.types_pk().clear();
						cr_c_.types_pk()<<f_capac_c_->chgt_type_clim().valeur(f_capac_c_->chgt_type_clim().valeur(n_cl_));
					}
				}
				if(climat.first.first=="SOLEIL"){
					foreach(Combattant c,creatures_act.cles()){
						CreatureCombat& cr_c_=creatures_act.valeur(c);
						if(cr_c_.statut_pk()=="GEL"){
							cr_c_.statut_pk()="OK";
						}
					}
				}
			}
		}
		if(f_capac_&&f_capac_->ant_clim()){
			climat.second.first=false;
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				CreatureCombat& cr_c_=creatures_act.valeur(c);
				FicheCapacite *f_capac_c_=cr_c_.fiche_capacite(_d);
				if(f_capac_c_&&f_capac_c_->chgt_type_clim().total()>0){
					cr_c_.types_pk()=cr_c_.fiche_pokemon(_d)->typs();
				}
			}
		}
		if(f_capac_&&f_capac_->capac()){
			//changer les types des pokemon ayant meteo
			_choix.capacite_pk_act()=creatures_act.valeur(tirage_front_adv(equipe_adv_)).capacite_pk_act();
			if(_choix.capacite_pk_act()!=""){
				Taux pv_soignes_(0);
				_choix.activer_capacite(true,_d,positions_places,effet_global("ZONE_MAGIQUE").second,arriere,climat,pv_soignes_);
			}
		}
		if(f_capac_&&f_capac_->mult_statis_statis_adv().first.total()>0){
			HashMap<QString,QPair<QString,qint8> > ajout_cran_=f_capac_->mult_statis_statis_adv().first;
			CreatureCombat& cr_c_=creatures_act.valeur(tirage_front_adv(equipe_adv_));
			QString n_stat1_=f_capac_->mult_statis_statis_adv().second.second;
			Taux stat1_=cr_c_.statistique_mod_globale(n_stat1_,cr_c_.ev_mod(n_stat1_),cr_c_.iv_mod(n_stat1_));
			QString n_stat2_=f_capac_->mult_statis_statis_adv().second.first;
			Taux stat2_=cr_c_.statistique_mod_globale(n_stat2_,cr_c_.ev_mod(n_stat2_),cr_c_.iv_mod(n_stat2_));
			if(stat1_>stat2_&&ajout_cran_.cles().contains("SUP")){
				QPair<QString,qint8> valeur_=ajout_cran_.valeur("SUP");
				_choix.var_boost(valeur_.first,valeur_.second,_d);
			}else if(stat1_<stat2_&&ajout_cran_.cles().contains("INF")){
				QPair<QString,qint8> valeur_=ajout_cran_.valeur("INF");
				_choix.var_boost(valeur_.first,valeur_.second,_d);
			}else if(stat1_==stat2_&&ajout_cran_.cles().contains("EGA")){
				QPair<QString,qint8> valeur_=ajout_cran_.valeur("EGA");
				_choix.var_boost(valeur_.first,valeur_.second,_d);
			}
		}else if(f_capac_){
			Taux pv_soignes_(0);
			_choix.activer_capacite(true,_d,positions_places,effet_global("ZONE_MAGIQUE").second,arriere,climat,pv_soignes_);
		}
	}else{
		_choix.capacite_pk_act()="";
	}
	_choix.reinit_coeff_types_att(_d);
	_choix.maj_coeff_types_att_subie(_d);
	if(effet_global("GRAVITE").second){
		_choix.coeff_att_type("SOL")=Taux(1);
		_choix.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
	}
	uchar nb_picots_=attaque_equipe(equipe_adv_,"PICOTS").first;
	if(nb_picots_>0){
		if(effet_global("GRAVITE").second){
			Taux deg_=_choix.calcul_picots(nb_picots_);
			if(deg_>=_choix.pv_restants_pk()){
				mise_a_ko(_ch,_choix,_d);
			}else{
				_choix.pv_restants_pk()-=deg_;
			}
		}else if(!_choix.coeff_att_type("SOL").estNul()&&!_choix.attaques_actives_def("LEVIKINESIE").second){
			if(!_choix.attaques_actives_def("VOL_MAGNETIK").second&&!_choix.types_pk().contains("VOL")){
				Taux deg_=_choix.calcul_picots(nb_picots_);
				if(deg_>=_choix.pv_restants_pk()){
					mise_a_ko(_ch,_choix,_d);
				}else{
					_choix.pv_restants_pk()-=deg_;
				}
			}
		}
	}
	if(attaque_equipe(equipe_adv_,"PIEGE_DE_ROC").first>0){
		if(_choix.statut_pk()!="KO"&&!_choix.attaques_actives_def("LEVIKINESIE").second){
			if(!_choix.attaques_actives_def("VOL_MAGNETIK").second&&!_choix.fiche_capacite(_d)->immu_pieg()){
				Taux deg_=_choix.calcul_pieges_roche(_d);
				if(deg_>=_choix.pv_restants_pk()){
					mise_a_ko(_ch,_choix,_d);
				}else{
					_choix.pv_restants_pk()-=deg_;
				}
			}
		}
	}
}

void ElementsCombat::envoi(const Combattant& _ch,CreatureCombat& _choix,bool _capac_act,Donnees *_d,const Combattant& _lc,bool _envoi_de_force){
	ss_methode_envoi(_ch,_choix,_capac_act,_d);
	uchar equipe_adv_=adversaire(_ch.equipe());
	QPair<uchar,bool>& val_pics_tx_=attaque_equipe(equipe_adv_,"PICS_TOXIKS");
	if(val_pics_tx_.first>0&&_choix.statut_pk()!="KO"){
		if(_choix.types_pk().contains("POISON")){
			val_pics_tx_=QPair<uchar,bool>(0,false);
		}else if(!_choix.types_pk().contains("ACIER")){
			if((!_capac_act&&!_choix.coeff_att_type("SOL").estNul()&&!_choix.types_pk().contains("VOL"))||effet_global("GRAVITE").second){
				QString statut_=CreatureCombat::calcul_pics_toxik(equipe_adv_);
				FicheCapacite *f_capac_c_=_choix.fiche_capacite(_d);
				bool reussi_=traiter_reussite_seul_effet_statut(_choix,f_capac_c_,_ch.equipe(),statut_,false,_d);
				if(reussi_){
					_choix.statut_pk()=statut_;
					if(_envoi_de_force&&f_capac_c_&&f_capac_c_->transf_statut().cles().contains(statut_)){
						CreatureCombat& lanceur_=creatures_act.valeur(_lc);
						FicheCapacite *f_capac_l_=lanceur_.fiche_capacite(_d);
						QString capac_l_=lanceur_.capacite_pk_act();
						QString att_l_=lanceur_.att_choisie();
						if(traiter_reussite_seul_effet_statut(_choix,f_capac_c_,lanceur_,capac_l_,f_capac_l_,_lc.equipe(),att_l_,statut_,false,QStringList(statut_),false,_d)){
							lanceur_.statut_pk()=f_capac_c_->transf_statut().valeur(statut_);
						}
					}
				}
			}
		}
	}
	if(_choix.statut_pk()!="KO"){
		if(_ch.equipe()==ut){
			foreach(Combattant c,creatures_act.cles()){
				if(c.equipe()==adv){
					combattants_contre_adv.valeur(c.position())<<_ch.position();
				}
			}
		}
	}
}

QPair<bool,bool> ElementsCombat::condition_reussite(const Combattant& _lc,const CreatureCombat& _lanceur,const Combattant& _cb,const CreatureCombat& _cible,const QString& _att_lanc,const QString& _type_att,Donnees *_d)const{
	bool reussi_=true;
	bool effet_echec_=false;
	if(_att_lanc=="SYNCHROPEINE"&&Utilitaire::intersection<QString>(_lanceur.types_pk(),_cible.types_pk()).isEmpty()){
		reussi_=false;
	}
	if(_lanceur.attaques_actives_def("VOL_MAGNETIK").second||_lanceur.attaques_actives_def("LEVIKINESIE").second){
		if(_att_lanc=="RACINES"){
			reussi_=false;
		}
	}
	QString capac_c_=_cible.capacite_pk_act();
	FicheCapacite *f_capac_c_=_cible.fiche_capacite(_d);
	FicheCapacite *f_capac_l_=_lanceur.fiche_capacite(_d);
	if((_att_lanc=="SEDUCTION"||_att_lanc=="ATTRACTION")&&protege_contre_amour(_cible,_lanceur,_cible.capacite_pk_act(),f_capac_c_,f_capac_l_)){
		reussi_=false;
	}
	FicheAttaque *f_att_=_d->val_attaques().valeur(_att_lanc);
	if(f_att_->effs().size()==0){
		return QPair<bool,bool>(false,false);
	}
	QStringList attaques_;
	attaques_<<"CHUTE_LIBRE";
	attaques_<<"ANTI_AIR";
	attaques_<<"BAIN_DE_SMOG";
	attaques_<<"PASSE_CADEAU";
	if(attaques_.contains(_att_lanc)){
		if(!_cible.clone_pk().estNul()){
			reussi_=false;
		}
	}
	if(_att_lanc=="ANTI_AIR"){
		if(_cible.atterrissage().first){
			reussi_=false;
		}
	}
	attaques_.clear();
	attaques_<<"COPIE_TYPE";
	attaques_<<"DETREMPAGE";
	attaques_<<"RAYON_SIMPLE";
	attaques_<<"TEN_DANSE";
	if(attaques_.contains(_att_lanc)){
		if(f_capac_c_&&f_capac_c_->plaq()){
			reussi_=false;
		}
	}
	if(_att_lanc=="VIBRA_SOIN"){
		if(attaque_equipe(adversaire(_cb.equipe()),"ANTI_SOIN").second||_cible.pv_restants_pk()==_cible.pv_max()){
			reussi_=false;
		}
	}
	if(_att_lanc=="INTERVERSION"){
		if(multiplicite<2||existence_partenaire_front(_lc)){
			reussi_=false;
		}
	}
	attaques_.clear();
	attaques_<<"APRES_VOUS";
	attaques_<<"A_LA_QUEUE";
	if(attaques_.contains(_att_lanc)){
		if((!ordre_non_joue(_d,false).contains(_cb)&&!ordre_non_joue(_d,true).contains(_cb))||multiplicite<2){
			reussi_=false;
		}else{
			uchar nb_fronts_=0;
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second!=arriere){
					nb_fronts_++;
				}
			}
			if(nb_fronts_<=2){
				reussi_=false;
			}
		}
	}
	if(_att_lanc=="PASSE_CADEAU"){
		if(_cible.objet()!=""||_lanceur.objet()==""||(_cible.att_choisie()=="REFLET_MAGIK"&&_cible.att_reussie())){
			reussi_=false;
		}
	}
	bool existe_cbt_chute_libre_sur_lanceur_=false;
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat cr_c_=creatures_act.valeur(c);
		if(cr_c_.att_choisie()=="CHUTE_LIBRE"&&cibles_lanceur(c,_d).contains(_lc)){
			if(cr_c_.prepa_tour_pk()){
				existe_cbt_chute_libre_sur_lanceur_=true;
			}
		}
	}
	if(existe_cbt_chute_libre_sur_lanceur_){
		reussi_=false;
	}
	if(_cible.disparition_pk()&&(!f_capac_l_||!f_capac_l_->to_pseud_invul())&&!f_att_->touch_pk_disp().contains(_cible.att_choisie())){
		if(!_lanceur.att_active_cible("VERROUILLAGE",_cb)&&!_lanceur.att_active_cible("LIRE_ESPRIT",_cb)){
			bool existe_cbt_chute_libre_sur_cible_=false;
			foreach(Combattant c,creatures_act.cles()){
				CreatureCombat cr_c_=creatures_act.valeur(c);
				if(cr_c_.att_choisie()=="CHUTE_LIBRE"&&cibles_lanceur(c,_d).contains(_cb)){
					if(cr_c_.prepa_tour_pk()){
						existe_cbt_chute_libre_sur_cible_=true;
					}
				}
			}
			if(_cible.att_choisie()=="CHUTE_LIBRE"||existe_cbt_chute_libre_sur_cible_){
				reussi_=false;
			}else if(!f_att_->effs()[0]->qui()){
				attaques_.clear();
				attaques_<<"PICOTS";
				attaques_<<"PICS_TOXIK";
				attaques_<<"PIEGE_DE_ROC";
				if(!attaques_.contains(_att_lanc)){
					reussi_=false;
				}
			}
		}
	}
	if(_cible.immu_att_type(_type_att)){
	//if(_cible.attaques_actives_def("VOL_MAGNETIK").second&&_type_att=="SOL"){
		reussi_=false;
	}
	attaques_.clear();
	attaques_<<"RIPOSTE";
	attaques_<<"VOILE_MIROIR";
	attaques_<<"FULMIFER";
	attaques_<<"CLONAGE";
	if(!_lanceur.clone_pk().estNul()&&attaques_.contains(_att_lanc)){
		reussi_=false;
	}
	if(!_cible.clone_pk().estNul()){
		if(_d->val_clonage_bloc().contains(_att_lanc)){
			reussi_=false;
		}
		if(!_d->val_clonage_non_bloc().contains(_att_lanc)&&_cb!=_lc&&f_att_->cat()=="AUTRE"){
			reussi_=false;
		}
	}
	if(_att_lanc=="RELACHE"&&_lanceur.nb_lancer("STOCKAGE")==0){
		reussi_=false;
	}
	if(_att_lanc=="ACROBATIE"&&_lanceur.objet()=="BALLE_FER"){
		reussi_=false;
	}
	if(_d->val_attaques_anti_soin().contains(_att_lanc)){
		if(attaque_equipe(adversaire(_lc.equipe()),"ANTI_SOIN").second){
			reussi_=false;
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere||c.equipe()==_lc.equipe()){
			continue;
		}
		if(creatures_act.valeur(c).poss_pk(_lc).contains(_att_lanc)){
			reussi_=false;
		}
	}
	if(existence_attaque_meme_eq(_cb,"GARDE_LARGE")&&!f_att_->qi().contains("UNIQ")){
		if(!_lanceur.att_active_cible("VERROUILLAGE",_cb)&&!_lanceur.att_active_cible("LIRE_ESPRIT",_cb)){
			if(!f_capac_l_||!f_capac_l_->abri()){
				reussi_=false;
			}
		}
	}
	if(existence_attaque_meme_eq(_cb,"PREVENTION")&&f_att_->prio()>0&&_att_lanc!="RUSE"){
		if(!_lanceur.att_active_cible("VERROUILLAGE",_cb)&&!_lanceur.att_active_cible("LIRE_ESPRIT",_cb)){
			if(!f_capac_l_||!f_capac_l_->abri()){
				reussi_=false;
			}
		}
	}
	if((_cible.att_choisie()=="ABRI"||_cible.att_choisie()=="DETECTION")&&_cible.att_reussie()){
		if(!_d->val_abri_attaques().contains(_att_lanc)){
			if(!_lanceur.att_active_cible("VERROUILLAGE",_cb)&&!_lanceur.att_active_cible("LIRE_ESPRIT",_cb)){
				if(!f_capac_l_||!f_capac_l_->abri()){
					reussi_=false;
				}
			}
		}
	}
	if(_cible.att_choisie()=="TENACITE"&&_cible.att_reussie()&&f_att_->ohko()){
		reussi_=false;
	}
	if(_cible.att_choisie()=="PROVOC"&&_cible.att_reussie()){
		if(f_att_->cat()=="AUTRE"){
			attaques_.clear();
			attaques_<<"RIPOSTE";
			attaques_<<"VOILE_MIROIR";
			attaques_<<"FULMIFER";
			attaques_<<"EFFORT";
			attaques_<<"FORCE_NATURE";
			if(!attaques_.contains(_att_lanc)){
				reussi_=false;
			}
		}
	}
	if(existence_entrave(_lc,_att_lanc)){
		reussi_=false;
	}
	if(_lanceur.attaques_actives_ind("TOURMENTE")&&_lanceur.der_att_reussie()==_att_lanc){
		reussi_=false;
	}
	if(effet_global("GRAVITE").second&&_d->val_gravite().contains(_att_lanc)){
		reussi_=false;
	}
	if(_att_lanc=="VOL_MAGNETIK"&&(_lanceur.coeff_att_type("SOL").estNul()||_lanceur.attaques_actives_ind("RACINES"))){
		reussi_=false;
	}
	if(_att_lanc=="LEVIKINESIE"&&(_cible.coeff_att_type("SOL").estNul()||_cible.attaques_actives_ind("RACINES")||_cible.types_pk().contains("VOL"))){
		reussi_=false;
	}
	//si attaque_lanceur appartient a switch_force et ((cible.capacite est IMMU_ATTAQUE[lanceur.derniere_attaque] et lanceur.capacite n'ignore pas cible.capacite) ou cible.racines.actif ou il n'est aucun pokemon non combattant non KO)
	if(_d->val_switch_force().contains(_att_lanc)){
		if(f_capac_c_&&f_capac_c_->immu_att().contains(_att_lanc)&&(!f_capac_l_||!f_capac_l_->capac_ign().contains(capac_c_))){
			reussi_=false;
		}else if(_cible.attaques_actives_ind("RACINES")||!existence_pk_arriere_non_ko(_cb)||!_cible.clone_pk().estNul()){
			reussi_=false;
		}
	}
	Effet *effet_primaire_=f_att_->effs()[0];
	//TODO et (lanceur.objet != PT_DE_MIRE ou lanceur.embargo_subi.actif)
	if(f_capac_c_&&f_capac_c_->immu_att().contains(_att_lanc)&&(!f_capac_l_||!f_capac_l_->capac_ign().contains(capac_c_))){
		if(!_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
			reussi_=false;
		}else{
			ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(_lanceur.fiche_objet(_d));
			if(!obj_||!obj_->annule_immu_t()){
				reussi_=false;
			}
		}
	}else if(_att_lanc=="REPOS"){
		if(_lanceur.pv_restants_pk()==_lanceur.pv_max()){
			reussi_=false;
		}else{
			reussi_=traiter_reussite_seul_effet_statut(_lanceur,f_capac_l_,_lc.equipe(),"SOMMEIL",false,_d);
		}
	}else if(_att_lanc=="BAILLEMENT"){
		if(!_cible.clone_pk().estNul()){
			reussi_=false;
		}else if(attaque_equipe(_cb.equipe(),"RUNE_PROTECT").second){
			reussi_=false;
		}else if(_cible.statut_pk()!="OK"){
			reussi_=false;
		}
	}else if(qobject_cast<EffetStatut*>(effet_primaire_)){
		EffetStatut *effet_=qobject_cast<EffetStatut*>(effet_primaire_);
		bool existe_=false;
		QStringList statuts_=effet_->statuts_possibles_non_ok();
		foreach(QString s,statuts_){
			bool pseudo_statut_=_d->val_noms_statuts().filter(QRegExp("^"+s+"\\b")).isEmpty();
			existe_|=traiter_reussite_seul_effet_statut(_lanceur,f_capac_l_,_cible,capac_c_,f_capac_c_,_cb.equipe(),_att_lanc,s,effet_->qui(),statuts_,pseudo_statut_,_d);
		}
		if(!existe_){
			reussi_=false;
		}
		if(f_capac_c_&&f_capac_c_->immu_stat().cles().contains(valeur_climat())){
			if(f_capac_c_->immu_stat().valeur(valeur_climat()).contains("CONFUSION")){
				if(_att_lanc=="VANTARDISE"||_att_lanc=="FLATTERIE"){
					if(!f_capac_l_||!f_capac_l_->capac_ign().contains(capac_c_)){
						effet_echec_=true;
					}
				}
			}
		}
	}else if(qobject_cast<EffetStatistique*>(effet_primaire_)){
		reussi_=!traiter_reussite_effet_statistiques(_cible,f_capac_l_,_cb.equipe(),f_capac_c_,capac_c_,f_att_,_d).isEmpty();
	}else if(_att_lanc=="ABRI"||_att_lanc=="DETECTION"||_att_lanc=="TENACITE"||_att_lanc=="GARDE_LARGE"||_att_lanc=="PREVENTION"){
		return QPair<bool,bool>(reussi_,effet_echec_);
	}else if(f_att_->effs().size()==1&&f_att_->descr_suppl()){
		if(_att_lanc=="CLONAGE"&&_lanceur.pv_max()*Taux(1,4LL)<=_lanceur.pv_restants_pk()){
			reussi_=false;
		}else if(_att_lanc=="ACUPRESSION"&&!_cible.existe_boost_acupression(_d)){
			reussi_=false;
		}else if((_att_lanc=="AVALE"||_att_lanc=="RELACHE")&&_lanceur.nb_lancer("STOCKAGE")==0){
			reussi_=false;
		}else if(_att_lanc=="ADAPTATION"&&_lanceur.types_adaptation(_d).isEmpty()){
			reussi_=false;
		}else if(_att_lanc=="CONVERSION_2"&&(_lanceur.att_deg_subie().second==""||_lanceur.types_conversion_2(_lanceur.att_deg_subie().second,_d).isEmpty())){
			reussi_=false;
		}else if(_att_lanc=="COPIE"&&(_cible.nb_tours_terrain_pk()==0||_d->val_copie_attaques().contains(_cible.der_att_lancee())||_lanceur.noms_attaques_act().contains(_cible.der_att_lancee()))){
			reussi_=false;
		}else if(_att_lanc=="DEPIT"){
			if(_cible.nb_tours_terrain_pk()==0||!_cible.attaques_avec_pp().contains(_cible.der_att_lancee())){
				reussi_=false;
			}
		}else if(_att_lanc=="GRIBOUILLE"){
			if(_cible.der_att_lancee()=="GRIBOUILLE"||_cible.der_att_lancee()=="LUTTE"||_cible.der_att_lancee()==""){
				reussi_=false;
			}else if(_cible.att_choisie()=="GRIBOUILLE"||_cible.att_choisie()=="LUTTE"){
				reussi_=false;
			}
		}else if(_att_lanc=="ENCORE"){
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				if(creatures_act.valeur(c).cible_atts(QPair<QString,Combattant>("ENCORE",_cb)).second.first){
					reussi_=false;
				}
			}
			if(_cible.nb_tours_terrain_pk()==0||_d->val_encore_attaques().contains(_cible.der_att_lancee())){
				reussi_=false;
			}
		}else if(_att_lanc=="ENTRAVE"){
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				if(creatures_act.valeur(c).cible_atts(QPair<QString,Combattant>("ENTRAVE",_cb)).second.first){
					reussi_=false;
				}
			}
			if(_cible.nb_tours_terrain_pk()==0||!_cible.attaques_avec_pp().contains(_cible.der_att_lancee())){
				reussi_=false;
			}
		}else if(_att_lanc=="IMITATION"||_att_lanc=="ECHANGE"){
			if(_cible.capacite_pk_act()=="GARDE_MYSTIK"||_cible.capacite_pk_act()=="MULTI_TYPE"){
				reussi_=false;
			}
		}else if(_att_lanc=="MIMIQUE"){
			if(_d->val_mimique_attaques().contains(_lanceur.att_deg_subie().second)||_lanceur.att_deg_subie().second==""){
				reussi_=false;
			}
		}else if(_att_lanc=="PASSE_PASSE"||_att_lanc=="TOUR_MAGIK"){
			if(_cible.capacite_pk_act()=="GLUE"||_cible.capacite_pk_act()=="MULTITYPE"){
				reussi_=false;
			}
		}else if(_att_lanc=="PHOTOCOPIE"){
			if(!_cible.att_reussie()||_cible.att_choisie()=="PHOTOCOPIE"){
				reussi_=false;
			}
		}else if(_att_lanc=="RIPOSTE"&&_lanceur.att_deg_subie().first.first.estNul()){
			reussi_=false;
		}else if(_att_lanc=="VOILE_MIROIR"&&_lanceur.att_deg_subie().first.second.estNul()){
			reussi_=false;
		}else if(_att_lanc=="FULMIFER"){
			if((_lanceur.att_deg_subie().first.second+_lanceur.att_deg_subie().first.first).estNul()){
				reussi_=false;
			}
		}else if(_att_lanc=="ECHANGE_PSY"){
			if(_lanceur.statut_pk()=="OK"||_cible.statut_pk()!="OK"){
				reussi_=false;
			}else{
				reussi_=traiter_reussite_seul_effet_statut(_lanceur,f_capac_l_,_cible,capac_c_,f_capac_c_,_cb.equipe(),_att_lanc,_lanceur.statut_pk(),false,QStringList(_lanceur.statut_pk()),false,_d);
			}
		}else if(_att_lanc=="MOI_D_ABORD"){
			if(_cible.act_choisie()=="ATTAQUE"&&_d->val_attaques().valeur(_cible.att_choisie())->cat()=="AUTRE"){
				reussi_=false;
			}else{
				attaques_.clear();
				attaques_<<"RIPOSTE";
				attaques_<<"VOILE_MIROIR";
				attaques_<<"FULMIFER";
				attaques_<<"EFFORT";
				attaques_<<"FORCE_NATURE";
				if(attaques_.contains(_cible.att_choisie())||_cible.att_choisie()!="ATTAQUE"){
					reussi_=false;
				}
			}
		}else if(_att_lanc=="EFFORT"&&_lanceur.pv_restants_pk()>=_cible.pv_restants_pk()){
			reussi_=false;
		}else if(_att_lanc=="RECYCLAGE"&&(_lanceur.objet()!=""||_lanceur.val_der_objet_ut()=="")){
			reussi_=false;
		}else if(_att_lanc=="DEGOMMAGE"&&_lanceur.calcul_degommage(_d).estNul()){
			reussi_=false;
		}else if(_att_lanc=="DANSE_LUNE"||_att_lanc=="VOEU_SOIN"){//existence_pk_arriere_non_ko
			if(!existence_pk_arriere_non_ko(_lc)){
				reussi_=false;
			}
		}else if(_att_lanc=="SOUVENIR"){
			if(!existence_partenaire_non_ko(_lc)&&!existence_pk_arriere_non_ko(_lc)){
				reussi_=false;
			}
		}
	}else if(f_att_->cat()!="AUTRE"){
		if(f_capac_c_&&f_capac_c_->immu_att_t().contains(f_att_->tp())){
			if(!f_capac_l_||!f_capac_l_->capac_ign().contains(capac_c_)){
				if(!_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
					reussi_=false;
					effet_echec_=true;
				}else{
					ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(_lanceur.fiche_objet(_d));
					if(!obj_||!obj_->annule_immu_t()){
						reussi_=false;
						effet_echec_=true;
					}
				}
			}
		}
	}
	return QPair<bool,bool>(reussi_,effet_echec_);
}


/*void CreatureCombat::reinit_coeff_types_att(Donnees *_d){
	foreach(QString t,_d->val_noms_types_fr()){
		coeff_att_types_subies.ajouter_cle_valeur(t,Taux(1))
		coeff_att_types_subies_2.ajouter_cle_valeur(t,Taux(1))
		coeff_att_types_lancees.ajouter_cle_valeur(t,Taux(1))
	}
}*/

/*void ElementsCombat::envoi(const Combattant& _lc,const Combattant& _ch,CreatureCombat& _choix,bool _capac_act,bool _envoi_de_force,Donnees* _d){
	ss_methode_envoi(_ch,_choix,_capac_act,_d)
	uchar equipe_adv_=adversaire(_ch.equipe())
	QPair<uchar,bool>& val_pics_tx_=attaque_equipe(equipe_adv_,"PICS_TOXIKS")
	if(val_pics_tx_.first>0&&_choix.statut_pk()!="KO"){
		if(_choix.types_pk().contains("POISON")){
			val_pics_tx_=QPair<uchar,bool>(0,false)
		}else if(!_choix.types_pk().contains("ACIER")){
			if((!_capac_act&&!_choix.coeff_att_type("SOL").estNul()&&!_choix.types_pk().contains("VOL"))||effet_global("GRAVITE").second){
				QString statut_=CreatureCombat::calcul_pics_toxik(equipe_adv_)
				FicheCapacite *f_capac_c_=_choix.fiche_capacite(_d)
				bool reussi_=traiter_reussite_seul_effet_statut(_choix,f_capac_c_,_ch.equipe(),statut_,false,_d)
				if(!reussi_){
					_choix.statut_pk()=statut_
					if(_envoi_de_force&&f_capac_c_&&f_capac_c_->transf_statut().cles().contains(statut_)){
						CreatureCombat& lanceur_=creatures_act.valeur(_lc)
						FicheCapacite *f_capac_l_=lanceur_.fiche_capacite(_d)
						QString capac_l_=lanceur_.capacite_pk_act()
						QString att_l_=lanceur_.att_choisie()
						if(traiter_reussite_seul_effet_statut(_choix,f_capac_c_,lanceur_,capac_l_,f_capac_l_,_lc.equipe(),att_l_,statut_,false,QStringList(statut_),false,_d)){
							lanceur_.statut_pk()=f_capac_c_->transf_statut().valeur(statut_)
						}
					}
				}
			}
		}
	}	
}*/

Taux ElementsCombat::calcul_precision(const Combattant& _lc,const CreatureCombat& _lanceur,const QString& _nom_att_l,FicheAttaque *_att_lanc,const Combattant& _cb,const CreatureCombat& _cible,uchar _statistique,bool& _ut_prec_att_suivante,bool& _lanceur_baie,Donnees *_d)const{
	QStringList attaques_l_;
	attaques_l_<<"ABRI";
	attaques_l_<<"DETECTION";
	attaques_l_<<"TENACITE";
	attaques_l_<<"GARDE_LARGE";
	attaques_l_<<"PREVENTION";
	if(attaques_l_.contains(_nom_att_l)){
		Taux prec_=Taux(100)*Taux(2)^Entier(-_lanceur.succes_abris());
		if(prec_==Taux(100)){
			if(_statistique!=ElementsCombat::VAR){
				return Taux(1);
			}else{
				return Taux(0);
			}
		}
		if(_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
			Baie *baie_=qobject_cast<Baie*>(_lanceur.fiche_objet(_d));
			FicheCapacite *f_capac_c_=_cible.fiche_capacite(_d);
			if(baie_&&baie_->reu()&&prec_<Taux(100)&&(!f_capac_c_||!f_capac_c_->anti_conso_baies_adv())){
				_lanceur_baie=true;
				if(_statistique!=ElementsCombat::VAR){
					return Taux(1);
				}
				return Taux(0);
			}
		}
		if(prec_>=Taux(100)){
			if(_statistique!=ElementsCombat::VAR){
				return Taux(1);
			}
			return Taux(0);
		}
		if(_statistique==ElementsCombat::MINI){
			return Taux(0);
		}
		if(_statistique==ElementsCombat::MAXI){
			return Taux(1);
		}
		if(_statistique==ElementsCombat::MOY){
			return prec_/Taux(100);
		}
		Taux moy_=prec_/Taux(100);
		if(_statistique==ElementsCombat::VAR){
			return moy_*(Taux(1)-moy_);
		}
		Entier proba_1_=moy_.gnumerateur();
		Entier proba_2_=moy_.gdenominateur()-proba_1_;
		MonteCarloNombre loi_;
		loi_.ajouter_event(QPair<Taux,Entier>(Taux(1),proba_1_));
		loi_.ajouter_event(QPair<Taux,Entier>(Taux(0),proba_2_));
		return loi_.tirage();
	}
	Taux prec_=_att_lanc->prec();
	if(_att_lanc->ohko()){
		prec_=Utilitaire::max_min<uchar>(0,_lanceur.niveau_pk()-_cible.niveau_pk()).first;
	}else if(_cible.attaques_actives_def("LEVIKINESIE").second){
		prec_=Taux(100);
	}
	if(prec_.estNul()){
		return prec_;
	}
	if(_nom_att_l=="FATAL_FOUDRE"||_nom_att_l=="VENT_VIOLENT"){
		if(valeur_climat()=="PLUIE"){
			prec_=Taux(101);
		}
	}
	if(_nom_att_l=="BLIZZARD"){
		if(valeur_climat()=="GRELE"){
			prec_=Taux(101);
		}
	}
	if(_nom_att_l=="FATAL_FOUDRE"||_nom_att_l=="VENT_VIOLENT"){
		if(valeur_climat()=="SOLEIL"){
			prec_=Taux(50);
		}
	}
	if(_nom_att_l=="BLIZZARD"){
		if(valeur_climat()=="SOLEIL"){
			prec_=Taux(50);
		}
	}
	if(prec_==Taux(101)){
		if(_statistique!=ElementsCombat::VAR){
			return Taux(1);
		}
		return Taux(0);
	}
	FicheCapacite *f_capac_l_=_lanceur.fiche_capacite(_d);
	if(f_capac_l_&&f_capac_l_->abri()){
		if((_cible.att_choisie()!="ABRI"&&_cible.att_choisie()!="DETECTION")||!_cible.att_reussie()){
			if(_statistique!=ElementsCombat::VAR){
				return Taux(1);
			}
			return Taux(0);
		}
		if(!existence_attaque_meme_eq(_cb,"GARDE_LARGE")||_att_lanc->qi().contains("UNIQ")){
			if(_statistique!=ElementsCombat::VAR){
				return Taux(1);
			}
			return Taux(0);
		}
		if(!existence_attaque_meme_eq(_cb,"PREVENTION")||_att_lanc->prio()<=0||_nom_att_l=="RUSE"){
			if(_statistique!=ElementsCombat::VAR){
				return Taux(1);
			}
			return Taux(0);
		}
	}
	//MINI,MAXI,ALEA,VAR,MOY
	prec_*=CreatureCombat::coeff_pre(_lanceur.boost("PRECISION"));
	QList<Combattant> cbts_;
	foreach(Combattant c,ordre_non_joue(_d,true)){
		cbts_<<c;
	}
	foreach(Combattant c,ordre_non_joue(_d,false)){
		if(!cbts_.contains(c)){
			cbts_<<c;
		}
	}
	if(cbts_.size()==1&&f_capac_l_&&f_capac_l_->mult_statis_der().cles().contains("PRECISION")){
		prec_*=f_capac_l_->mult_statis_der().valeur("PRECISION");
	}
	attaques_l_.clear();
	attaques_l_<<"ATTRITION";
	attaques_l_<<"LAME_SAINTE";
	if(!attaques_l_.contains(_nom_att_l)){
		prec_*=CreatureCombat::coeff_esq(_cible.boost("ESQUIVE"));
		if(!f_capac_l_||!f_capac_l_->capac_ign().contains(_cible.capacite_pk_act())){
			FicheCapacite *f_capac_c_=_cible.fiche_capacite(_d);
			if(f_capac_c_&&f_capac_c_->mult_statis_clim().cles().contains(QPair<QString,QString>("ESQUIVE",valeur_climat()))){
				prec_/=f_capac_c_->mult_statis_clim().valeur(QPair<QString,QString>("ESQUIVE",valeur_climat()));
			}
			if(f_capac_c_){
				typedef QPair<QString,QPair<QString,Taux> > StatistiqueStatut;
				foreach(StatistiqueStatut s,f_capac_c_->mult_statis_statut_coef()){
					if(s.first=="ESQUIVE"&&(s.second.first==_cible.statut_pk()||(s.second.first=="CONFUSION"&&_cible.confusion_pk().second))){
						prec_/=s.second.second;
					}
				}
				typedef QPair<QString,QString> StatistiqueCateg;
				foreach(StatistiqueCateg s,f_capac_c_->mult_statis_categ().cles()){
					if(s.first=="ESQUIVE"&&s.second==_att_lanc->cat()){
						prec_/=f_capac_c_->mult_statis_categ().valeur(s);
					}
				}
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==_lc.equipe()){
			FicheCapacite *f_capac_p_=creatures_act.valeur(c).fiche_capacite(_d);
			if(f_capac_p_&&f_capac_p_->mult_statis_part().cles().contains("PRECISION")){
				prec_*=f_capac_p_->mult_statis_part().valeur("PRECISION");
			}
		}
	}
	if(effet_global("GRAVITE").second){
		prec_*=Taux(8LL,5LL);
	}
	if(f_capac_l_){
		if(f_capac_l_->mult_statis().cles().contains("PRECISION")){
			QPair<Taux,bool> val_=f_capac_l_->mult_statis().valeur("PRECISION");
			if(val_.second){
				prec_*=val_.first;
			}
		}
	}
	if(_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
		ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(_lanceur.fiche_objet(_d));
		if(obj_&&obj_->mult_stat().cles().contains("PRECISION")){
			QPair<Taux,bool> val_=obj_->mult_stat().valeur("PRECISION");
			if(val_.second){
				prec_*=val_.first;
			}
		}
		if(obj_&&obj_->mult_stat_der().cles().contains("PRECISION")){
			if(cbts_.size()==1){
				prec_*=obj_->mult_stat_der().valeur("PRECISION");
			}
		}
	}
	if(_cible.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
		ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(_cible.fiche_objet(_d));
		if(obj_&&obj_->mult_stat_adv().cles().contains("PRECISION")&&!_d->val_non_affecte_poudre_claire().contains(_nom_att_l)){
			QPair<Taux,bool> val_=obj_->mult_stat_adv().valeur("PRECISION");
			if(val_.second){
				prec_*=val_.first;
			}
		}
	}
	if(_lanceur.att_active_cible("VERROUILLAGE",_cb)||_lanceur.att_active_cible("LIRE_ESPRIT",_cb)){
		QStringList attaques_c_;
		attaques_c_<<"ABRI";
		attaques_c_<<"DETECTION";
		attaques_c_<<"TENACITE";
		attaques_c_<<"GARDE_LARGE";
		attaques_c_<<"PREVENTION"		;
		if(!attaques_c_.contains(_cible.att_choisie())||!_cible.att_reussie()){
			if(prec_<Taux(100)&&_nom_att_l!="PRESCIENCE"&&_nom_att_l!="CARNAREKET"){
				_ut_prec_att_suivante=true;
				if(_statistique!=ElementsCombat::VAR){
					return Taux(1);
				}
				return Taux(0);
			}
		}
	}
	if(_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
		Baie *baie_=qobject_cast<Baie*>(_lanceur.fiche_objet(_d));
		FicheCapacite *f_capac_c_=_cible.fiche_capacite(_d);
		if(baie_&&baie_->reu()&&prec_<Taux(100)&&(!f_capac_c_||!f_capac_c_->anti_conso_baies_adv())){
			_lanceur_baie=true;
			if(_statistique!=ElementsCombat::VAR){
				return Taux(1);
			}
			return Taux(0);
		}
	}
	if(prec_>=Taux(100)){
		if(_statistique!=ElementsCombat::VAR){
			return Taux(1);
		}
		return Taux(0);
	}
	if(_statistique==ElementsCombat::MINI){
		return Taux(0);
	}
	if(_statistique==ElementsCombat::MAXI){
		return Taux(1);
	}
	if(_statistique==ElementsCombat::MOY){
		return prec_/Taux(100);
	}
	Taux moy_=prec_/Taux(100);
	if(_statistique==ElementsCombat::VAR){
		return moy_*(Taux(1)-moy_);
	}
	Entier proba_1_=moy_.gnumerateur();
	Entier proba_2_=moy_.gdenominateur()-proba_1_;
	MonteCarloNombre loi_;
	loi_.ajouter_event(QPair<Taux,Entier>(Taux(1),proba_1_));
	loi_.ajouter_event(QPair<Taux,Entier>(Taux(0),proba_2_));
	return loi_.tirage();
}

Taux ElementsCombat::calcul_puissance(const QString& _n_att,FicheAttaque *_att_lanc,const Combattant& _lc,const CreatureCombat& _lanceur,const Combattant& _cb,const CreatureCombat& _cible,uchar _statistique,Donnees *_d)const{
	if(_n_att=="AMPLEUR"){
		if(_statistique==ElementsCombat::MINI){
			return _lanceur.loi_ampleur(_d).minimum();
		}
		if(_statistique==ElementsCombat::MAXI){
			return _lanceur.loi_ampleur(_d).maximum();
		}
		if(_statistique==ElementsCombat::MOY){
			return _lanceur.loi_ampleur(_d).esperance();
		}
		if(_statistique==ElementsCombat::VAR){
			return _lanceur.loi_ampleur(_d).variance();
		}
		return _lanceur.loi_ampleur(_d).tirage();
	}else if(_n_att=="PUIS_CACHEE"){
		if(_statistique==ElementsCombat::MINI){
			return _lanceur.loi_puissance_cachee(_d).minimum();
		}
		if(_statistique==ElementsCombat::MAXI){
			return _lanceur.loi_puissance_cachee(_d).maximum();
		}
		if(_statistique==ElementsCombat::MOY){
			return _lanceur.loi_puissance_cachee(_d).esperance();
		}
		if(_statistique==ElementsCombat::VAR){
			return _lanceur.loi_puissance_cachee(_d).variance();
		}
		return _lanceur.loi_puissance_cachee(_d).tirage();
	}
	if(_statistique==ElementsCombat::VAR){
		return Taux(0);
	}
	Taux puis_(1);
	if(_att_lanc->puis()>0){
		puis_*=_att_lanc->puis();
	}
	if(_n_att=="VENGEANCE"){
		if(vengeance_actif.valeur(_lc.equipe()).first||vengeance_actif.valeur(_lc.equipe()).second){
			puis_*=Taux(2);
		}
	}
	if(_n_att=="AIRE_D_EAU"||_n_att=="AIRE_DE_FEU"||_n_att=="AIRE_D_HERBE"){
		int nb_=1;
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==_lc.equipe()&&c!=_lc){
				if(positions_places.valeur(c).second!=arriere){
					CreatureCombat cr_c_=creatures_act.valeur(c);
					if(cr_c_.att_choisie()=="AIRE_D_EAU"||cr_c_.att_choisie()=="AIRE_DE_FEU"||cr_c_.att_choisie()=="AIRE_D_HERBE"){
						if(cr_c_.att_reussie()){
							nb_++;
						}
					}
				}
			}
		}
		puis_*=Taux(nb_);
	}
	if(_n_att=="LANCE_SOLEIL"){
		if(valeur_climat()!="SOLEIL"&&valeur_climat()!=""){
			puis_/=Taux(2);
		}
	}
	QStringList attaq_=calcul_attaques_equipe(_lc);
	if(_n_att=="ECLAIR_CROIX"){
		if(attaq_.contains("FLAMME_CROIX")){
			puis_*=Taux(2);
		}
	}
	if(_n_att=="FLAMME_CROIX"){
		if(attaq_.contains("ECLAIR_CROIX")){
			puis_*=Taux(2);
		}
	}
	if((_n_att=="PICORE"||_n_att=="PIQURE")&&_cible.clone_pk().estNul()&&_cible.objet()!=""&&qobject_cast<Baie*>(_cible.fiche_objet(_d))){
		puis_*=Taux(2);
	}
	if(_n_att=="ECHO"||_n_att=="CHANT_CANON"){
		puis_*=Taux(nb_utilisation_attaques.valeur(QPair<QString,uchar>(_n_att,_lc.equipe())));
	}
	if(_d->val_attaques_touchant_pseudo_invuln().cles().contains(QPair<QString,QString>(_n_att,_cible.att_choisie()))&&_cible.prepa_tour_pk()){
		puis_*=Taux(_d->val_attaques_touchant_pseudo_invuln().valeur(QPair<QString,QString>(_n_att,_cible.att_choisie())));
	}
	if(_d->val_attaques_lilliput().cles().contains(_n_att)&&_cible.attaques_actives_ind("LILLIPUT")){
		puis_*=Taux(_d->val_attaques_lilliput().valeur(_n_att));
	}
	if(_n_att=="ACROBATIE"&&_cible.objet()==""){
		puis_*=Taux(2);
	}
	if(_n_att=="CHATIMENT"&&_cible.statut_pk()!="OK"){
		puis_*=Taux(2);
	}
	if(_n_att=="CHOC_VENIN"&&(_cible.statut_pk()=="POISON"||_cible.statut_pk()=="POISON_GRAVE")){
		puis_*=Taux(2);
	}
	if(_n_att=="AVALANCHE"||_n_att=="VENDETTA"||_n_att=="REPRESAILLES"){
		QPair<Taux,Taux> val_=_lanceur.att_deg_subie().first;
		if(!(val_.first+val_.second).estNul()){
			puis_*=Taux(2);
		}
	}
	if(_n_att=="ASSURANCE"){
		QPair<Taux,Taux> val_=_cible.att_deg_subie().first;
		if(!(val_.first+val_.second).estNul()){
			puis_*=Taux(2);
		}
	}
	if(_n_att=="ROULADE"||_n_att=="BALL_GLACE"){
		puis_*=_lanceur.coeff_roul_ballglace();
	}
	if(_n_att=="BALL_METEO"&&valeur_climat()!=""){
		puis_*=Taux(2);
	}
	if(_n_att=="BASTON"){
		puis_=Taux(10);
	}
	if(_n_att=="ERUPTION"||_n_att=="GICLEDO"){
		puis_*=_lanceur.pv_restants_pk()/_lanceur.pv_max();
	}
	if(_n_att=="FACADE"&&_lanceur.statut_pk()!="OK"){
		puis_*=Taux(2);
	}
	if(_n_att=="SAUMURE"&&_cible.pv_restants_pk()*Taux(2)<=_cible.pv_max()){
		puis_*=Taux(2);
	}
	if(_n_att=="TAILLADE"){
		puis_*=Taux(2)^Entier(Utilitaire::max_min<int>(_lanceur.nb_lancer("TAILLADE")-1,4).second);
	}
	if(_n_att=="REVEIL_FORCE"&&_cible.clone_pk().estNul()&&_cible.statut_pk()=="SOMMEIL"){
		puis_*=Taux(2);
	}
	if(_n_att=="STIMULANT"&&_cible.clone_pk().estNul()&&_cible.statut_pk()=="PARALYSIE"){
		puis_*=Taux(2);
	}
	if(_n_att=="ATOUT"){
		uchar pp_=0;
		typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
		foreach(AttaquePP a,_lanceur.attaques_act_pk()){
			if(a.first=="ATOUT"){
				pp_=a.second.first;
			}
		}
		if(pp_<=1){
			puis_*=Taux(200);
		}else if(pp_==2){
			puis_*=Taux(80);
		}else if(pp_==3){
			puis_*=Taux(60);
		}else if(pp_==4){
			puis_*=Taux(50);
		}else{
			puis_*=Taux(40);
		}
	}
	if(_n_att=="BALAYAGE"||_n_att=="NOEUD_HERBE"){
		if(_cible.masse_pk()<Taux(10)){
			puis_*=Taux(20);
		}else if(_cible.masse_pk()<Taux(25)){
			puis_*=Taux(40);
		}else if(_cible.masse_pk()<Taux(50)){
			puis_*=Taux(60);
		}else if(_cible.masse_pk()<Taux(100)){
			puis_*=Taux(80);
		}else if(_cible.masse_pk()<Taux(200)){
			puis_*=Taux(100);
		}else{
			puis_*=Taux(120);
		}
	}
	if(_n_att=="CONTRE"||_n_att=="FLEAU"){
		uchar n_=Taux(64)*_lanceur.pv_restants_pk()/_lanceur.pv_max();
		if(n_<2){
			puis_*=Taux(200);
		}else if(n_<6){
			puis_*=Taux(150);
		}else if(n_<13){
			puis_*=Taux(100);
		}else if(n_<22){
			puis_*=Taux(80);
		}else if(n_<43){
			puis_*=Taux(40);
		}else{
			puis_*=Taux(20);
		}
	}
	if(_n_att=="DON_NATUREL"){
		if(_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
			Baie *baie_=qobject_cast<Baie*>(_lanceur.fiche_objet(_d));
			if(baie_){
				puis_*=Taux(baie_->type_puis_dn().second);
			}else{
				puis_=Taux(1);
			}
		}else{
			puis_=Taux(1);
		}
	}
	if(_n_att=="ESSORAGE"||_n_att=="PRESSE"){
		puis_=Taux(1)+Taux(120)*_cible.pv_restants_pk()/_cible.pv_max();
	}
	if(_n_att=="GYROBALLE"){
		uchar eq_l_=_lc.equipe();
		uchar eq_c_=_cb.equipe();
		Taux vit_l_=_lanceur.vitesse(attaque_equipe(adversaire(eq_l_),"AIRE_EAU_HERBE").second,effet_global("ZONE_MAGIQUE").second,attaque_equipe(eq_l_,"VENT_ARRIERE").second,climat,_d);
		Taux vit_c_=_cible.vitesse(attaque_equipe(adversaire(eq_c_),"AIRE_EAU_HERBE").second,effet_global("ZONE_MAGIQUE").second,attaque_equipe(eq_c_,"VENT_ARRIERE").second,climat,_d);
		puis_=Taux(1)+Taux(25)*vit_c_/vit_l_;
	}
	if(_n_att=="BOULE_ELEK"){
		uchar eq_l_=_lc.equipe();
		uchar eq_c_=_cb.equipe();
		Taux vit_l_=_lanceur.vitesse(attaque_equipe(adversaire(eq_l_),"AIRE_EAU_HERBE").second,effet_global("ZONE_MAGIQUE").second,attaque_equipe(eq_l_,"VENT_ARRIERE").second,climat,_d);
		Taux vit_c_=_cible.vitesse(attaque_equipe(adversaire(eq_c_),"AIRE_EAU_HERBE").second,effet_global("ZONE_MAGIQUE").second,attaque_equipe(eq_c_,"VENT_ARRIERE").second,climat,_d);
		Taux rapp_=vit_c_/vit_l_;
		if(rapp_<=Taux(1LL,4LL)){
			puis_*=Taux(150);
		}else if(rapp_<=Taux(1LL,3LL)){
			puis_*=Taux(120);
		}else if(rapp_<=Taux(1LL,2LL)){
			puis_*=Taux(80);
		}else{
			puis_*=Taux(60);
		}
	}
	if(_n_att=="PUNITION"){
		uchar nb_=0;
		foreach(QString s,_cible.statis_boost()){
			qint8 boost_=_cible.boost(s);
			if(boost_>0){
				nb_+=boost_;
			}
		}
		puis_*=Utilitaire::max_min<Taux>(Taux(200),Taux(60)+Taux(20*nb_)).second;
	}
	if(_n_att=="FORCE_AJOUTEE"){
		uchar nb_=0;
		foreach(QString s,_lanceur.statis_boost()){
			qint8 boost_=_lanceur.boost(s);
			if(boost_>0){
				nb_+=boost_;
			}
		}
		puis_*=Taux(20)+Taux(20*nb_);
	}
	if(_n_att=="TACLE_FEU"||_n_att=="TACLE_LOURD"){
		Taux rapport_=_cible.masse_pk()/_lanceur.masse_pk();
		int ent_=rapport_.inv();
		puis_*=Taux(20)*Taux(1+Utilitaire::max_min<int>(Utilitaire::max_min<int>(1,ent_).first,5).second);
	}
	if(_n_att=="RELACHE"){
		puis_*=_lanceur.nb_lancer("STOCKAGE");
	}
	if(_n_att=="RETOUR"){
		puis_*=Taux(_lanceur.bonheur_pk()*2LL,5LL)+Taux(1);
	}
	if(_n_att=="DEGOMMAGE"){
		puis_*=_lanceur.calcul_degommage(_d);
	}
	return puis_;
}

QPair<Taux,Taux> ElementsCombat::esperance_carree_variance_prod(const QPair<Taux,Taux>& cp_1,const QPair<Taux,Taux>& cp_2){
	QPair<Taux,Taux> retour_;
	retour_.first=cp_1.first*cp_2.first;
	retour_.second=cp_1.second*cp_2.second-cp_1.first*cp_2.second-cp_1.second*cp_2.first;
	return retour_;
}

Taux ElementsCombat::calcul_degats(const QString& _n_att,FicheAttaque *_att_lanc,const QString& _type_att,const Combattant& _lc,const CreatureCombat& _lanceur,const Combattant& _cb,const CreatureCombat& _cible,const Taux& _excuse,uchar _statistique,bool& _utilise_baie,bool& _utilise_baie_c,bool& _cc,Donnees *_d)const{
	QString nom_l_=_lanceur.nom_pk_act();
	FicheCapacite *f_capac_c_=_cible.fiche_capacite(_d);
	FicheCapacite *f_capac_l_=_lanceur.fiche_capacite(_d);
	ObjetAttachableCombat *obj_l_=NULL;
	Plaque *pl_l_=NULL;
	ObjetAttachableCombat *obj_c_=NULL;
	if(_lc.equipe()==_cb.equipe()){
		if(f_capac_c_&&f_capac_c_->immu_deg_part()){
			return Taux(0);
		}
	}
	EffetDegats *eff_=qobject_cast<EffetDegats*>(_att_lanc->effs()[0]);
	if(eff_&&eff_->deg_fixe()){
		if(_statistique!=ElementsCombat::VAR){
			return eff_->puis();
		}
		return Taux(0);
	}
	Taux niv_(_lanceur.niveau_pk());
	if(_n_att=="TENEBRES"||_n_att=="FRAPPE_ATLAS"){
		if(_statistique!=ElementsCombat::VAR){
			return niv_;
		}
		return Taux(0);
	}
	if(_n_att=="VAGUE_PSY"){
		MonteCarloNombre loi_;
		for(int i=-5;i<=5;i++){
			loi_.ajouter_event(QPair<Taux,Entier>(Taux((10LL+i)*(int)niv_,10LL),Entier(1)));
		}
		if(_statistique==ElementsCombat::MINI){
			return loi_.minimum();
		}
		if(_statistique==ElementsCombat::MAXI){
			return loi_.maximum();
		}
		if(_statistique==ElementsCombat::MOY){
			return loi_.esperance();
		}
		if(_statistique==ElementsCombat::VAR){
			return loi_.variance();
		}
		return loi_.tirage();
	}
	Taux puiss_base_;
	Taux moy_puiss_base_=calcul_puissance(_n_att,_att_lanc,_lc,_lanceur,_cb,_cible,ElementsCombat::MOY,_d);
	if(_n_att=="EXCUSE"){
		puiss_base_=_excuse;
	}else{
		puiss_base_=calcul_puissance(_n_att,_att_lanc,_lc,_lanceur,_cb,_cible,_statistique,_d);
	}
	if(_n_att=="DON_NATUREL"){
		if(_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
			Baie *baie_=qobject_cast<Baie*>(_lanceur.fiche_objet(_d));
			if(baie_){
				_utilise_baie=true;
			}
		}
	}
	Taux hh_(1);
	if(_lanceur.attaques_actives_ind("COUP_D_MAIN")){
		hh_*=Taux(3LL,2LL);
	}
	Taux it_(1);
	if(_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
		obj_l_=qobject_cast<ObjetAttachableCombat*>(_lanceur.fiche_objet(_d));
		if(obj_l_){
			foreach(QString t,obj_l_->mult_puiss_att_type().cles()){
				if(t==_type_att){
					it_*=obj_l_->mult_puiss_att_type().valeur(t);
				}
			}
			foreach(QString c,obj_l_->mult_puiss_att_categ().cles()){
				if(c==_att_lanc->cat()){
					it_*=obj_l_->mult_puiss_att_categ().valeur(c);
				}
			}
			typedef QPair<QString,QString> NomType;
			foreach(NomType n,obj_l_->mult_puiss_att_pk_types().cles()){
				if(n.first==nom_l_&&n.second==_type_att){
					it_*=obj_l_->mult_puiss_att_pk_types().valeur(n);
				}
			}
		}
		pl_l_=qobject_cast<Plaque*>(_lanceur.fiche_objet(_d));
		if(pl_l_&&pl_l_->tp_pl()==_type_att){
			it_*=pl_l_->co();
		}
	}
	Taux chg_=_lanceur.r_coeff_att_types_lancees(_type_att);
	Taux msws_=_cible.coeff_att_type_2(_type_att);
	Taux ua_(1);
	if(f_capac_l_){
		if(_lanceur.genre_pk()!="ASSEXUE"&&_cible.genre_pk()!="ASSEXUE"){
			if(f_capac_l_->mult_puis_att_eg_genre().cles().contains(true)&&_lanceur.genre_pk()==_cible.genre_pk()){
				ua_*=f_capac_l_->mult_puis_att_eg_genre().valeur(true);
			}
			if(f_capac_l_->mult_puis_att_eg_genre().cles().contains(false)&&_lanceur.genre_pk()!=_cible.genre_pk()){
				ua_*=f_capac_l_->mult_puis_att_eg_genre().valeur(false);
			}
		}
		if(f_capac_l_->mult_puis_typ_inf_eg().cles().contains(_type_att)){
			QPair<Taux,Taux> val_=f_capac_l_->mult_puis_typ_inf_eg().valeur(_type_att);
			if(val_.first*_lanceur.pv_max()>=_lanceur.pv_restants_pk()){
				ua_*=val_.second;
			}
		}
		if(_n_att!="AMPLEUR"&&_n_att!="PUIS_CACHEE"){
			QPair<int,Taux> mult_puis_infeg_=f_capac_l_->mult_puis_inf_eg();
			if(mult_puis_infeg_.second!=Taux(0)){
				if(puiss_base_<=Taux(mult_puis_infeg_.first)){
					puiss_base_*=mult_puis_infeg_.second;
					moy_puiss_base_*=mult_puis_infeg_.second;
				}
			}
		}
		if(f_capac_l_->mult_puis_att().cles().contains(_n_att)){
			ua_*=f_capac_l_->mult_puis_att().valeur(_n_att);
		}
	}
	Taux fa_(1);
	if(!f_capac_l_||!f_capac_l_->capac_ign().contains(_cible.capacite_pk_act())){
		if(f_capac_c_&&f_capac_c_->mult_deg_adv().cles().contains(_type_att)){
			fa_*=f_capac_c_->mult_deg_adv().valeur(_type_att);
		}
	}
	Taux force_sable_(1);
	if(f_capac_l_&&f_capac_l_->mult_puis_typ_cl().cles().contains(QPair<QString,QString>(valeur_climat(),_type_att))){
		force_sable_*=f_capac_l_->mult_puis_typ_cl().valeur(QPair<QString,QString>(valeur_climat(),_type_att));
	}
	Taux sans_limite_(1);
	if(f_capac_l_&&!f_capac_l_->mult_puis_t_att().estNul()){
		sans_limite_*=f_capac_l_->mult_puis_t_att();
	}
	Taux puiss_=hh_*it_*chg_*msws_*ua_*fa_*force_sable_*sans_limite_;
	Taux moy_puiss_=hh_*moy_puiss_base_*it_*chg_*msws_*ua_*fa_*force_sable_*sans_limite_;
	Taux att_;
	QString statis_;
	QString statis_a_;
	if(_att_lanc->st_atts().second){
		if(_att_lanc->cat()=="PHYSIQUE"){
			statis_="ATTAQUE";
		}else{
			statis_="ATTAQUE_SPECIALE";
		}
	}else{
		if(_att_lanc->cat()=="PHYSIQUE"){
			statis_="ATTAQUE_SPECIALE";
		}else{
			statis_="ATTAQUE";
		}
	}
	statis_a_=statis_;
	if(_att_lanc->st_atts().first){
		att_=_lanceur.statistique_mod_globale(statis_,_lanceur.ev_mod(statis_),_lanceur.iv_mod(statis_));
	}else{
		att_=_cible.statistique_mod_globale(statis_,_cible.ev_mod(statis_),_cible.iv_mod(statis_));
	}
	qint8 boost_=_lanceur.boost(statis_);
	if(boost_<=0||!f_capac_c_||!f_capac_c_->boost_adv_ign().contains(statis_)||(f_capac_l_&&f_capac_l_->capac_ign().contains(_cible.capacite_pk_act()))){
		att_*=CreatureCombat::coeff_boost(boost_);
	}
	Taux am_(1);
	if(f_capac_l_){
		if(f_capac_l_->mult_statis().cles().contains(statis_)){
			QPair<Taux,bool> val_=f_capac_l_->mult_statis().valeur(statis_);
			if(val_.second){
				am_*=val_.first;
			}
		}
		typedef QPair<QString,QPair<QString,Taux> > StatistiqueStatut;
		foreach(StatistiqueStatut s,f_capac_l_->mult_statis_statut_coef()){
			if(s.first==statis_&&s.second.first==_lanceur.statut_pk()){
				am_*=s.second.second;
			}
		}
		typedef QPair<QString,QString> StatistiqueClimat;
		foreach(StatistiqueClimat s,f_capac_l_->mult_statis_clim().cles()){
			if(s.first==statis_&&s.second==valeur_climat()){
				am_*=f_capac_l_->mult_statis_clim().valeur(s);
			}
		}
	}
	Taux im_(1);
	if(_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
		if(obj_l_){
			typedef QPair<QString,QString> NomSatist;
			foreach(NomSatist n,obj_l_->mult_stat_pk_co().cles()){
				if(n.second==nom_l_&&n.first==statis_){
					im_*=obj_l_->mult_stat_pk_co().valeur(n);
				}
			}
			foreach(QString s,obj_l_->mult_stat().cles()){
				QPair<Taux,bool> val_=obj_l_->mult_stat().valeur(s);
				if(val_.second&&s==statis_){
					im_*=val_.first;
				}
			}
		}
	}
	att_*=am_*im_;
	QList<Combattant> cbts_;
	foreach(Combattant c,ordre_non_joue(_d,true)){
		cbts_<<c;
	}
	foreach(Combattant c,ordre_non_joue(_d,false)){
		if(!cbts_.contains(c)){
			cbts_<<c;
		}
	}
	if(f_capac_l_&&cbts_.size()==1){
		if(f_capac_l_->mult_statis_der().cles().contains(statis_)){
			att_*=f_capac_l_->mult_statis_der().valeur(statis_);
		}
	}
	Taux def_;
	if(_att_lanc->st_def().second){
		if(_att_lanc->cat()=="PHYSIQUE"){
			statis_="DEFENSE";
		}else{
			statis_="DEFENSE_SPECIALE";
		}
	}else{
		if(_att_lanc->cat()=="PHYSIQUE"){
			statis_="DEFENSE_SPECIALE";
		}else{
			statis_="DEFENSE";
		}
	}
	if(_att_lanc->st_def().first){
		def_=_cible.statistique_mod_globale(statis_,_cible.ev_mod(statis_),_cible.iv_mod(statis_));
	}else{
		def_=_lanceur.statistique_mod_globale(statis_,_lanceur.ev_mod(statis_),_lanceur.iv_mod(statis_));
	}
	if(_n_att!="LAME_SAINTE"){
		boost_=Utilitaire::max_min<qint8>(_cible.boost(statis_)+_cible.nb_lancer("STOCKAGE"),_d->constante_numerique("MAX_BOOST")).second;
		if(boost_<=0){
			def_*=CreatureCombat::coeff_boost(boost_);
		}else if(_n_att!="ATTRITION"){
			if(!f_capac_l_||!f_capac_l_->boost_adv_ign().contains(statis_)||(f_capac_c_&&f_capac_c_->capac_ign().contains(_lanceur.capacite_pk_act()))){
				def_*=CreatureCombat::coeff_boost(boost_);
			}
		}
	}
	Taux sx_(1);
	if(_n_att=="DESTRUCTION"||_n_att=="EXPLOSION"){
		sx_*=Taux(1LL,2LL);
	}
	am_=Taux(1);
	if(f_capac_c_){
		if(f_capac_c_->mult_statis().cles().contains(statis_)){
			QPair<Taux,bool> val_=f_capac_c_->mult_statis().valeur(statis_);
			if(val_.second){
				am_*=val_.first;
			}
		}
		typedef QPair<QString,QPair<QString,Taux> > StatistiqueStatut;
		foreach(StatistiqueStatut s,f_capac_c_->mult_statis_statut_coef()){
			if(s.first==statis_&&s.second.first==_cible.statut_pk()){
				am_*=s.second.second;
			}
		}
		typedef QPair<QString,QString> StatistiqueClimat;
		foreach(StatistiqueClimat s,f_capac_c_->mult_statis_clim().cles()){
			if(s.first==statis_&&s.second==valeur_climat()){
				am_*=f_capac_c_->mult_statis_clim().valeur(s);
			}
		}
	}
	im_=Taux(1);
	if(_cible.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
		obj_c_=qobject_cast<ObjetAttachableCombat*>(_cible.fiche_objet(_d));
		if(obj_c_){
			typedef QPair<QString,QString> NomSatist;
			foreach(NomSatist n,obj_c_->mult_stat_pk_co().cles()){
				if(n.second==nom_l_&&n.first==statis_){
					im_*=obj_c_->mult_stat_pk_co().valeur(n);
				}
			}
			foreach(QString s,obj_c_->mult_stat().cles()){
				QPair<Taux,bool> val_=obj_c_->mult_stat().valeur(s);
				if(val_.second&&s==statis_){
					im_*=val_.first;
				}
			}
		}
	}
	Taux tps_(1);
	if(valeur_climat()=="TEMPETE_SABLE"&&_cible.types_pk().contains("ROCHE")&&statis_=="DEFENSE_SPECIALE"){
		tps_*=Taux(3LL,2LL);
	}
	def_*=sx_*am_*im_*tps_;
	//puiss_
	Taux degats_=Taux(5LL+(int)niv_,125LL)*att_/def_;
	Taux moy_degats_=Taux(5LL+(int)niv_,125LL)*moy_puiss_*att_/def_;
	Taux brn_(1);
	bool existe_=false;
	if(f_capac_l_){
		typedef QPair<QString,QString> StatistiqueStatutImmu;
		foreach(StatistiqueStatutImmu s,f_capac_l_->immu_bais_statis_stat()){
			if(s.first==statis_a_&&s.second==_lanceur.statut_pk()){
				existe_=true;
			}
		}
	}
	if(!existe_){
		brn_*=Taux(1LL,2LL);
	}
	Taux rl_(1);
	if(f_capac_l_){
		if(!f_capac_l_->att_ign().contains("MUR_LUMIERE")&&attaque_equipe(_cb.equipe(),"MUR_LUMIERE").second&&_att_lanc->cat()=="SPECIALE"){
			if(multiplicite>1&&cibles_lanceur(_lc,_d).size()>1){
				rl_*=Taux(2LL,3LL);
			}else{
				rl_*=Taux(1LL,2LL);
			}
		}else if(!f_capac_l_->att_ign().contains("PROTECTION")&&attaque_equipe(_cb.equipe(),"PROTECTION").second&&_att_lanc->cat()=="PHYSIQUE"){
			if(multiplicite>1&&cibles_lanceur(_lc,_d).size()>1){
				rl_*=Taux(2LL,3LL);
			}else{
				rl_*=Taux(1LL,2LL);
			}
		}
	}
	Taux mvm_(1);
	if(multiplicite>1&&cibles_lanceur(_lc,_d).size()>1){
		mvm_*=Taux(3LL,4LL);
	}
	Taux sr_(1);
	if(valeur_climat()=="PLUIE"){
		if(_type_att=="EAU"){
			sr_*=Taux(3LL,2LL);
		}else if(_type_att=="FEU"){
			sr_*=Taux(1LL,2LL);
		}
	}else if(valeur_climat()=="SOLEIL"){
		if(_type_att=="EAU"){
			sr_*=Taux(1LL,2LL);
		}else if(_type_att=="FEU"){
			sr_*=Taux(3LL,2LL);
		}
	}
	/*Taux ff_(1)
	if(_lanceur.torche_pk()){
		if(f_capac_l_&&f_capac_l_->mult_puis_att_t().cles().contains(_type_att)){
			ff_*=f_capac_l_->mult_puis_att_t().valeur(_type_att)
		}
	}*/
	Taux mod1_=brn_*rl_*mvm_*sr_;//*ff_
	degats_*=mod1_;
	moy_degats_*=mod1_;
	moy_degats_+=Taux(2);
	if(_statistique==ElementsCombat::VAR){
		degats_*=degats_*puiss_base_*puiss_;
	}
	Taux mod2_(1);
	if(_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
		if(obj_l_){
			if(!obj_l_->mult_puiss_att().estNul()){
				mod2_*=obj_l_->mult_puiss_att();
			}
			if(!obj_l_->mult_puiss_att_consec()){
				int nb_l_=_lanceur.util_attaques_succ()-1;
				mod2_*=Utilitaire::max_min<Taux>(Taux(2),Taux(10LL+nb_l_,10LL)).second;
			}
		}
	}
	if(_lanceur.attaques_actives_ind("MOI_D_ABORD")){
		mod2_*=Taux(3LL,2LL);
	}
	degats_*=mod2_;
	moy_degats_*=mod2_;
	if(_statistique==ElementsCombat::VAR){
		degats_*=mod2_;
	}
	Taux mod3_(1);
	Taux coeff_eff_(1);
	foreach(QString t,_cible.types_pk()){
		coeff_eff_*=_lanceur.table_eff(_cb,QPair<QString,QString>(_type_att,t));
	}
	if(coeff_eff_>Taux(1)&&f_capac_c_&&f_capac_c_->mult_deg_rec().cles().contains(true)){
		mod3_*=f_capac_c_->mult_deg_rec().valeur(true);
	}
	if(_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
		if(obj_l_){
			if(!obj_l_->mult_puiss_att_sup_eff().estNul()&&coeff_eff_>Taux(1)){
				mod3_*=obj_l_->mult_puiss_att_sup_eff();
			}
		}
	}
	if(coeff_eff_<Taux(1)&&f_capac_l_&&f_capac_l_->mult_deg_rec().cles().contains(false)){
		mod3_*=f_capac_l_->mult_deg_rec().valeur(false);
	}
	if(_cible.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
		Baie *baie_=qobject_cast<Baie*>(_cible.fiche_objet(_d));
		if(baie_&&baie_->mult_deg_ad().cles().contains(_type_att)){
			if(_type_att=="NORMAL"||coeff_eff_>Taux(1)){
				mod3_*=baie_->mult_deg_ad().valeur(_type_att);
				_utilise_baie_c=true;
				/*
				cible.utilise_baie <- vrai
				cible.vient_de_perdre_objet <- vrai
				*/
			}
		}
	}
	degats_*=mod3_;
	moy_degats_*=mod3_;
	if(_statistique==ElementsCombat::VAR){
		degats_*=mod3_;
	}
	if(_n_att=="PRESCIENCE"||_n_att=="CARNAREKET"){
		return degats_;
	}
	degats_*=coeff_eff_;
	moy_degats_*=coeff_eff_;
	if(_statistique==ElementsCombat::VAR){
		degats_*=coeff_eff_;
	}
	Taux stab_(1);
	if(_lanceur.types_pk().contains(_type_att)){
		stab_*=Taux(3LL,2LL);
		if(f_capac_l_&&!f_capac_l_->mult_st().estNul()){
			stab_*=f_capac_l_->mult_st();
		}
	}
	degats_*=stab_;
	moy_degats_*=stab_;
	if(_statistique==ElementsCombat::VAR){
		degats_*=stab_;
	}
	if(_lc.equipe()==_cb.equipe()){
		if(f_capac_l_&&!f_capac_l_->mult_deg_part().estNul()){
			degats_*=f_capac_l_->mult_deg_part();
			moy_degats_*=f_capac_l_->mult_deg_part();
			if(_statistique==ElementsCombat::VAR){
				degats_*=f_capac_l_->mult_deg_part();
			}
		}
	}
	MonteCarloNombre loi_rand_;
	Taux rand_min_;
	if(_lc.equipe()==ut){
		loi_rand_=CreatureCombat::loi_random(diff.r_choix_lois().first);
	}else{
		loi_rand_=CreatureCombat::loi_random(diff.r_choix_lois().second);
	}
	if(_n_att!="RELACHE"){
		rand_min_=loi_rand_.minimum();
	}else{
		rand_min_=loi_rand_.maximum();
	}
	Taux proba_cc_(0);
	uchar boost_cc_=0;
	if(!attaque_equipe(_cb.equipe(),"AIR_VEINARD").second){
		if(!f_capac_c_||!f_capac_c_->immu_c()){
			proba_cc_=Taux(1);
			boost_cc_=_lanceur.r_boost_cc();
		}else if(f_capac_c_&&f_capac_c_->capac_ign().contains(_lanceur.capacite_pk_act())){
			proba_cc_=Taux(1);
			boost_cc_=_lanceur.r_boost_cc();
		}
		if(!proba_cc_.estNul()){
			if(_lanceur.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
				if(obj_l_){
					if(obj_l_->mult_stat_pk_cr().cles().contains(QPair<QString,QString>(nom_l_,"COUP_CRITIQUE"))){
						boost_cc_+=obj_l_->mult_stat_pk_cr().valeur(QPair<QString,QString>(nom_l_,"COUP_CRITIQUE"));
					}
					if(obj_l_->mult_stat().cles().contains("COUP_CRITIQUE")){
						QPair<Taux,bool> val_=obj_l_->mult_stat().valeur("COUP_CRITIQUE");
						if(!val_.second){
							boost_cc_+=val_.first;
						}
					}
				}
				Baie *baie_=qobject_cast<Baie*>(_lanceur.fiche_objet(_d));
				if(baie_){
					if(baie_->mult_stat().cles().contains("COUP_CRITIQUE")){
						QPair<Taux,qint8> val_=baie_->mult_stat().valeur("COUP_CRITIQUE");
						if(val_.first*_lanceur.pv_max()>=_lanceur.pv_restants_pk()){
							boost_cc_+=val_.second;
						}
					}
				}
				//mult_stat()
			}
			if(qobject_cast<EffetDegats*>(_att_lanc->effs()[0])){
				boost_cc_+=qobject_cast<EffetDegats*>(_att_lanc->effs()[0])->tx_cc();
			}
		}
	}
	Taux cc_(1);
	MonteCarloNombre loi_cc_;
	//if(boost_cc_>0){
	if(!proba_cc_.estNul()){
		proba_cc_=Taux(2)^Entier(boost_cc_-4);
		loi_cc_=_lanceur.loi_cc(proba_cc_,_d);
	}else{
		loi_cc_.ajouter_event(QPair<Taux,Entier>(Taux(1),Entier(1)));
	}
	//Taux moy_cc=loi_cc_.esperance()
	if(_statistique==ElementsCombat::MINI){
		cc_=loi_cc_.minimum();
	}
	if(_statistique==ElementsCombat::MAXI){
		cc_=loi_cc_.maximum();
	}
	if(_statistique==ElementsCombat::MOY){
		cc_=loi_cc_.esperance();
	}
	if(_statistique==ElementsCombat::VAR){
		cc_=loi_cc_.esperance();
	}
	if(_cb!=_lc){
		if(moy_degats_*rand_min_*loi_cc_.minimum()>=_cible.pv_restants_pk()){
			if(_statistique==ElementsCombat::VAR){
				return Taux(0);
			}
			if(loi_cc_.minimum()>Taux(1)){
				_cc=true;
			}
			return moy_degats_*rand_min_*loi_cc_.minimum();
		}
		if(_statistique==ElementsCombat::MOY){
			return moy_degats_*loi_rand_.esperance()*cc_;
		}
		if(_statistique==ElementsCombat::MINI){
			if(loi_cc_.minimum()>Taux(1)){
				_cc=true;
			}
			return moy_degats_*rand_min_*cc_;
		}
		if(_statistique==ElementsCombat::MAXI){
			if(loi_cc_.maximum()>Taux(1)){
				_cc=true;
			}
			return moy_degats_*loi_rand_.maximum()*cc_;
		}
		if(_statistique==ElementsCombat::VAR){
			QPair<Taux,Taux> esp_car_var_(moy_degats_*moy_degats_,degats_-moy_degats_*moy_degats_);
			esp_car_var_=esperance_carree_variance_prod(esp_car_var_,QPair<Taux,Taux>(loi_rand_.esperance(),loi_rand_.variance()));
			esp_car_var_=esperance_carree_variance_prod(esp_car_var_,QPair<Taux,Taux>(loi_cc_.esperance(),loi_cc_.variance()));
			return esp_car_var_.second;
		}
		Taux rand_=loi_rand_.tirage();
		if(moy_degats_*rand_*loi_cc_.minimum()>=_cible.pv_restants_pk()){
			return moy_degats_*rand_*loi_cc_.minimum();
		}
		cc_=loi_cc_.tirage();
		if(cc_>Taux(1)){
			_cc=true;
		}
		return moy_degats_*rand_*cc_;
	}
	if(moy_degats_*rand_min_>=_lanceur.pv_restants_pk()){
		if(_statistique==ElementsCombat::VAR){
			return Taux(0);
		}
		return moy_degats_*rand_min_;
	}
	if(_statistique==ElementsCombat::MOY){
		return moy_degats_*loi_rand_.esperance();
	}
	if(_statistique==ElementsCombat::MINI){
		return moy_degats_*rand_min_;
	}
	if(_statistique==ElementsCombat::MAXI){
		return moy_degats_*loi_rand_.maximum();
	}
	if(_statistique==ElementsCombat::VAR){
		QPair<Taux,Taux> esp_car_var_(moy_degats_*moy_degats_,degats_-moy_degats_*moy_degats_);
		esp_car_var_=esperance_carree_variance_prod(esp_car_var_,QPair<Taux,Taux>(loi_rand_.esperance(),loi_rand_.variance()));
		return esp_car_var_.second;
	}
	Taux rand_=loi_rand_.tirage();
	if(moy_degats_*rand_>=_lanceur.pv_restants_pk()){
		return moy_degats_*rand_*loi_cc_.minimum();
	}
	return moy_degats_*rand_;
}

Taux ElementsCombat::calcul_degats(const MonteCarloNombre& _repet_coups,const QString& _n_att,FicheAttaque *_att_lanc,const QString& _type_att,const Combattant& _lc,const CreatureCombat& _lanceur,const Combattant& _cb,const CreatureCombat& _cible,const Taux& _excuse,uchar _statistique,HashMap<Combattant,bool>& _utilise_baie,HashMap<Combattant,bool>& _cc,Donnees *_d,const Taux& _nb_coups_tires)const{
	Taux nb_repet_coup_;
	Taux degats_(0);
	if(_statistique==ElementsCombat::MINI){
		nb_repet_coup_=_repet_coups.minimum();
	}else if(_statistique==ElementsCombat::MAXI){
		nb_repet_coup_=_repet_coups.maximum();
	}else if(_statistique==ElementsCombat::MOY){
		nb_repet_coup_=_repet_coups.esperance();
	}else if(_statistique==ElementsCombat::VAR){
		nb_repet_coup_=_repet_coups.variance();
	}else{
		nb_repet_coup_=_nb_coups_tires;
	}
	if(_n_att=="BASTON"&&_statistique!=ElementsCombat::ALEA){
		bool cc_=false;
		bool utilise_baie_=false;
		bool utilise_baie_c_=false;
		_utilise_baie.ajouter_cle_valeur(_cb,false);
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==_lc.equipe()&&creatures_act.valeur(c).statut_pk()=="OK"){
				degats_+=calcul_degats(_n_att,_att_lanc,_type_att,c,creatures_act.valeur(c),_cb,_cible,_excuse,_statistique,utilise_baie_,utilise_baie_c_,cc_,_d);
				_utilise_baie.ajouter_cle_valeur(c,utilise_baie_);
				_utilise_baie.valeur(_cb)|=utilise_baie_c_;
				_cc.ajouter_cle_valeur(c,cc_);
			}
		}
	}else{
		_utilise_baie.ajouter_cle_valeur(_cb,false);
		bool cc_=false;
		bool utilise_baie_=false;
		bool utilise_baie_c_=false;
		if(_statistique==ElementsCombat::VAR){
			Taux moy_nb_repet_coup_=_repet_coups.esperance();
			Taux moy_degats_=calcul_degats(_n_att,_att_lanc,_type_att,_lc,_lanceur,_cb,_cible,_excuse,ElementsCombat::MOY,utilise_baie_,utilise_baie_c_,cc_,_d);
			Taux var_nb_repet_coup_=nb_repet_coup_;
			Taux var_degats_=calcul_degats(_n_att,_att_lanc,_type_att,_lc,_lanceur,_cb,_cible,_excuse,_statistique,utilise_baie_,utilise_baie_c_,cc_,_d);
			degats_=esperance_carree_variance_prod(QPair<Taux,Taux>(moy_nb_repet_coup_*moy_nb_repet_coup_,var_nb_repet_coup_),QPair<Taux,Taux>(moy_degats_*moy_degats_,var_degats_)).second;
		}else{
			degats_=nb_repet_coup_*calcul_degats(_n_att,_att_lanc,_type_att,_lc,_lanceur,_cb,_cible,_excuse,_statistique,utilise_baie_,utilise_baie_c_,cc_,_d);
		}
		_utilise_baie.valeur(_cb)=utilise_baie_c_;
		_cc.ajouter_cle_valeur(_lc,cc_);
	}
	return degats_;
}


bool ElementsCombat::existe_anti_fuite(const Combattant& _c_cbt,const CreatureCombat& _cbt,Donnees *_d)const{
	//const CreatureCombat& _cbt_2
	bool existe_anti_fuite_=false;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==_c_cbt.equipe()){
			continue;
		}
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat cr_=creatures_act.valeur(c);
		if(cr_.att_active_cible("ANTI_FUITE",_c_cbt)){
			existe_anti_fuite_=true;
		}else{
			FicheCapacite *f_capac_cr_=cr_.fiche_capacite(_d);
			if(f_capac_cr_){
				FicheCapacite *f_capac_cbt_=_cbt.fiche_capacite(_d);
				if(f_capac_cr_->ant_fuite()){
					if(!f_capac_cbt_||!f_capac_cbt_->immu_anti_fuit().contains(cr_.capacite_pk_act())){
						existe_anti_fuite_=true;
					}
				}
				if(!f_capac_cr_->type_anti_fuite().first){
					if(!f_capac_cr_->type_anti_fuite().second.isEmpty()){
						if(Utilitaire::intersection<QString>(f_capac_cr_->type_anti_fuite().second,_cbt.types_pk()).isEmpty()){
							if(!f_capac_cbt_||!f_capac_cbt_->immu_anti_fuit().contains(cr_.capacite_pk_act())){
								if(!_cbt.attaques_actives_def("VOL_MAGNETIK").second&&!_cbt.attaques_actives_def("LEVIKINESIE").second){
									existe_anti_fuite_=true;
								}
							}else if(effet_global("GRAVITE").second){
								existe_anti_fuite_=true;
							}
						}else if(effet_global("GRAVITE").second){
							existe_anti_fuite_=true;
						}
					}
				}else{
					if(!f_capac_cr_->type_anti_fuite().second.isEmpty()){
						if(!Utilitaire::intersection<QString>(f_capac_cr_->type_anti_fuite().second,_cbt.types_pk()).isEmpty()){
							existe_anti_fuite_=true;
						}
					}
				}
			}
		}
	}
	if(!existe_anti_fuite_){
		return false;
	}
	if(_cbt.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
		ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(_cbt.fiche_objet(_d));
		if(obj_){
			if(obj_->switch_re()||obj_->fuite_re()){
				return false;
			}
		}
	}
	return true;
}

HashMap<Combattant,HashMap<QString,QStringList> > ElementsCombat::actions_possibles(uchar _qui,Donnees *_d)const{
	HashMap<Combattant,HashMap<QString,QStringList> > liste_;
	uchar adv_=adversaire(_qui);
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()!=_qui){
			continue;
		}
		typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
		CreatureCombat cr_c_=creatures_act.valeur(c);
		HashMap<QString,QStringList> liste_c_;
		liste_c_.ajouter_cle_valeur("ATTAQUE",QStringList());
		liste_c_.ajouter_cle_valeur("SWITCH",QStringList());
		liste_c_.ajouter_cle_valeur("SOIN",QStringList());
		liste_c_.ajouter_cle_valeur("",QStringList());
		if(positions_places.valeur(c).second!=arriere){
			if(cr_c_.att_copie().first!=""&&cr_c_.att_copie().second>0){
				liste_c_.valeur("ATTAQUE")<<cr_c_.att_copie().first;
			}
			liste_c_.valeur("ATTAQUE")<<cr_c_.attaques_avec_pp();
			if(cr_c_.nec_recharg_pk()){
				liste_c_.valeur("ATTAQUE").clear();
				if(!existe_anti_fuite(c,cr_c_,_d)){
					liste_c_.valeur("SWITCH")<<"SWITCH";
				}
				liste_.ajouter_cle_valeur(c,liste_c_);
				continue;
			}
			if(cr_c_.prepa_tour_pk()||(cr_c_.bloque()&&cr_c_.att_reussie())){
				liste_c_.valeur("ATTAQUE").clear();
				liste_c_.valeur("ATTAQUE")<<cr_c_.der_att_lancee();
				if(!existe_anti_fuite(c,cr_c_,_d)){
					liste_c_.valeur("SWITCH")<<"SWITCH";
				}
				if(!cr_c_.attaques_actives_def("EMBARGO").second&&!cr_c_.bloque()&&!cr_c_.prepa_tour_pk()){
					foreach(QString s,cr_c_.objets_pk().cles()){
						liste_c_.valeur("SOIN")<<s;
					}
				}
				liste_.ajouter_cle_valeur(c,liste_c_);
				continue;
			}
			if(!cr_c_.clone_pk().estNul()){
				liste_c_.valeur("ATTAQUE").removeOne("PATIENCE");
			}
			foreach(Combattant c2,creatures_act.cles()){
				if(c2.equipe()!=_qui){
					continue;
				}
				if(positions_places.valeur(c2).second==arriere){
					continue;
				}
				if(prescience_carnar.valeur(QPair<QString,QPair<uchar,uchar> >("PRESCIENCE",positions_places.valeur(c2))).second.second!=arriere){
					liste_c_.valeur("ATTAQUE").removeOne("PRESCIENCE");
					liste_c_.valeur("ATTAQUE").removeOne("CARNAREKET");
				}else if(prescience_carnar.valeur(QPair<QString,QPair<uchar,uchar> >("CARNAREKET",positions_places.valeur(c2))).second.second!=arriere){
					liste_c_.valeur("ATTAQUE").removeOne("PRESCIENCE");
					liste_c_.valeur("ATTAQUE").removeOne("CARNAREKET");
				}
			}
			if(attaque_equipe(adv_,"ANTI_SOIN").second){
				foreach(QString a,_d->val_attaques_anti_soin()){
					liste_c_.valeur("ATTAQUE").removeOne(a);
				}
			}
			if(cr_c_.attaques_actives_def("PROVOC").second){
				QStringList& attaques_=liste_c_.valeur("ATTAQUE");
				int i_=0;
				while(i_<attaques_.size()){
					if(_d->val_attaques().valeur(attaques_[i_])->cat()=="AUTRE"){
						attaques_.removeAt(i_);
					}else{
						i_++;
					}
				}
			}
			foreach(Combattant c2,creatures_act.cles()){
				CreatureCombat cr_c_2_=creatures_act.valeur(c2);
				QPair<QString,QPair<bool,uchar> >& entr_=cr_c_2_.cible_atts(QPair<QString,Combattant>("ENTRAVE",c));
				if(entr_.second.first){
					liste_c_.valeur("ATTAQUE").removeOne(entr_.first);
				}
				if(c2.equipe()!=c.equipe()){
					foreach(QString a,cr_c_2_.poss_pk(c)){
						liste_c_.valeur("ATTAQUE").removeOne(a);
					}
				}
			}
			QStringList& attaques_=liste_c_.valeur("ATTAQUE");
			if(attaques_.isEmpty()){
				attaques_<<"LUTTE";
				if(!existe_anti_fuite(c,cr_c_,_d)){
					liste_c_.valeur("SWITCH")<<"SWITCH";
				}
				if(!cr_c_.attaques_actives_def("EMBARGO").second){
					foreach(QString s,cr_c_.objets_pk().cles()){
						liste_c_.valeur("SOIN")<<s;
					}
				}
				liste_.ajouter_cle_valeur(c,liste_c_);
				continue;
			}
			QString attaque_encore_;
			foreach(Combattant c2,creatures_act.cles()){
				CreatureCombat cr_c_2_=creatures_act.valeur(c2);
				if(c2.equipe()!=c.equipe()){
					QPair<QString,QPair<bool,uchar> >& encore_=cr_c_2_.cible_atts(QPair<QString,Combattant>("ENCORE",c));
					if(encore_.second.first&&encore_.first!=""){
						attaque_encore_=encore_.first;
					}
				}
			}
			if(attaque_encore_!=""){
				bool utiliser_lutte_=false;
				if(attaque_equipe(adv_,"ANTI_SOIN").second&&_d->val_attaques_anti_soin().contains(attaque_encore_)){
					utiliser_lutte_=true;
				}else if(cr_c_.attaques_actives_def("PROVOC").second&&_d->val_attaques().valeur(attaque_encore_)->cat()=="AUTRE"){
					utiliser_lutte_=true;
				}else{
					QStringList ens_;
					foreach(Combattant c2,creatures_act.cles()){
						CreatureCombat cr_c_2_=creatures_act.valeur(c2);
						QPair<QString,QPair<bool,uchar> >& entr_=cr_c_2_.cible_atts(QPair<QString,Combattant>("ENTRAVE",c));
						if(entr_.second.first){
							ens_<<entr_.first;
						}
						if(c2.equipe()!=c.equipe()){
							foreach(QString a,cr_c_2_.poss_pk(c)){
								ens_<<a;
							}
						}
					}
					if(ens_.contains(attaque_encore_)){
						utiliser_lutte_=true;
					}else if(cr_c_.attaques_actives_ind("TOURMENTE")&&cr_c_.att_reussie()){
						utiliser_lutte_=true;
					}else if(!liste_c_.valeur("ATTAQUE").contains(attaque_encore_)){
						utiliser_lutte_=true;
					}
				}
				liste_c_.valeur("ATTAQUE").clear();
				if(utiliser_lutte_){
					liste_c_.valeur("ATTAQUE")<<"LUTTE";
				}else{
					liste_c_.valeur("ATTAQUE")<<attaque_encore_;
				}
			}else if(cr_c_.attaques_actives_ind("TOURMENTE")&&cr_c_.att_reussie()){
				QString der_att_=cr_c_.der_att_lancee();
				liste_c_.valeur("ATTAQUE").removeOne(der_att_);
				bool utiliser_lutte_=false;
				if(attaque_equipe(adv_,"ANTI_SOIN").second&&_d->val_attaques_anti_soin().contains(der_att_)){
					utiliser_lutte_=true;
				}else{
					bool existe_degats_=false;
					foreach(QString a,liste_c_.valeur("ATTAQUE")){
						if(_d->val_attaques().valeur(a)->cat()!="AUTRE"){
							existe_degats_=true;
							break;
						}
					}
					if(!existe_degats_&&cr_c_.attaques_actives_def("PROVOC").second){
						utiliser_lutte_=true;
					}else{
						QStringList ens_;
						foreach(Combattant c2,creatures_act.cles()){
							CreatureCombat cr_c_2_=creatures_act.valeur(c2);
							QPair<QString,QPair<bool,uchar> >& entr_=cr_c_2_.cible_atts(QPair<QString,Combattant>("ENTRAVE",c));
							if(entr_.second.first){
								ens_<<entr_.first;
							}
							if(c2.equipe()!=c.equipe()){
								foreach(QString a,cr_c_2_.poss_pk(c)){
									ens_<<a;
								}
							}
						}
						bool existe_att_util_=false;
						foreach(QString a,liste_c_.valeur("ATTAQUE")){
							if(!ens_.contains(a)){
								existe_att_util_=true;
								break;
							}
						}
						if(!existe_att_util_){
							utiliser_lutte_=true;
						}
					}
				}
				if(utiliser_lutte_){
					liste_c_.valeur("ATTAQUE").clear();
					liste_c_.valeur("ATTAQUE")<<"LUTTE";
				}
			}
			if(!existe_anti_fuite(c,cr_c_,_d)){
				liste_c_.valeur("SWITCH")<<"SWITCH";
			}
			if(!cr_c_.attaques_actives_def("EMBARGO").second&&!cr_c_.bloque()&&!cr_c_.prepa_tour_pk()){
				foreach(QString s,cr_c_.objets_pk().cles()){
					liste_c_.valeur("SOIN")<<s;
				}
			}
		}else{
			//TODO soin
			foreach(QString s,cr_c_.objets_pk().cles()){
				liste_c_.valeur("SOIN")<<s;
			}
			//objets_pk()
		}
		liste_.ajouter_cle_valeur(c,liste_c_);
		//TODO soin
	}
	return liste_;
}

QPair<QString,HashMap<Combattant,QPair<QPair<QString,QString>,Combattant> > > ElementsCombat::jouable_utilisateur(Donnees *_d)const{
	QString erreur_;
	HashMap<Combattant,HashMap<QString,QStringList> > actions_possibles_=actions_possibles(ut,_d);
	HashMap<Combattant,QPair<QPair<QString,QString>,Combattant> > actions_choisies_;
	QStringList att_switch_;
	att_switch_<<"RELAIS";
	att_switch_<<"CHANGE_ECLAIR";
	att_switch_<<"DEMI_TOUR";
	att_switch_<<"VOEU_SOIN";
	att_switch_<<"DANSE_LUNE";
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()!=ut){
			continue;
		}
		QPair<QPair<QString,QString>,Combattant> action_chosie_;
		CreatureCombat cr_c_=creatures_act.valeur(c);
		action_chosie_.first.first=cr_c_.act_choisie();
		if(cr_c_.act_choisie()!="SWITCH"){
			action_chosie_.first.second=cr_c_.att_choisie();
		}else{
			action_chosie_.second=cr_c_.remplacant();
		}
		if(cr_c_.act_choisie()=="ATTAQUE"){
			if(att_switch_.contains(action_chosie_.first.second)){
				action_chosie_.second=cr_c_.remplacant();
			}
		}
		actions_choisies_.ajouter_cle_valeur(c,action_chosie_);
	}
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()!=ut){
			continue;
		}
		CreatureCombat cr_c_=creatures_act.valeur(c);
		if(cr_c_.act_choisie()==""&&positions_places.valeur(c).second==arriere){
			continue;
		}
		HashMap<QString,QStringList>& actions_possibles_cr_c_=actions_possibles_.valeur(c);
		QStringList& actions_possibles_cr_c_2_=actions_possibles_cr_c_.valeur(cr_c_.act_choisie());
		if(!actions_possibles_cr_c_2_.contains(cr_c_.att_choisie())){
			erreur_+="action impossible\n";
			continue;
		}
		if(cr_c_.act_choisie()=="ATTAQUE"){
			if(positions_places.valeur(c).second==arriere){
				erreur_+="action impossible\n";
			}else if(!cibles_possible_lanceur(c,actions_possibles_cr_c_2_,_d).isEmpty()&&cr_c_.cibles()[0].second==arriere){
				erreur_+="action impossible\n";
			}else if(actions_possibles_cr_c_2_.size()==1&&actions_possibles_cr_c_2_[0]=="LUTTE"){
				actions_choisies_.valeur(c).first.second=actions_possibles_cr_c_2_[0];
			}else if(cr_c_.nec_recharg_pk()){
				actions_choisies_.valeur(c).first.second=cr_c_.der_att_lancee();
			}else if(cr_c_.prepa_tour_pk()||(cr_c_.bloque()&&cr_c_.att_reussie())){
				actions_choisies_.valeur(c).first.second=actions_possibles_cr_c_2_[0];
			}else if(att_switch_.contains(cr_c_.att_choisie())){
				Combattant& rempl_=actions_choisies_.valeur(c).second;
				if(rempl_!=Combattant()&&positions_places.valeur(rempl_).second!=arriere){
					erreur_+="action impossible\n";
				}else{
					bool existe_=existence_pk_arriere_non_ko(c);
					if(existe_){
						if(rempl_==Combattant()){
							erreur_+="action impossible\n";
						}else if(creatures_act.valeur(rempl_).statut_pk()=="KO"){
							erreur_+="action impossible\n";
						}
					}
				}
			}
		}else if(cr_c_.act_choisie()=="SWITCH"){
			if(positions_places.valeur(c).second==arriere){
				erreur_+="action impossible\n";
			}
			Combattant& rempl_=actions_choisies_.valeur(c).second;
			if(rempl_!=Combattant()){
				if(positions_places.valeur(rempl_).second!=arriere){
					erreur_+="action impossible\n";
				}
				if(creatures_act.valeur(rempl_).statut_pk()=="KO"){
					erreur_+="action impossible\n";
				}
			}else{
				erreur_+="action impossible\n";
			}
		}
	}
	int nb_act_=0;
	int nb_non_ko_=0;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()!=ut){
			continue;
		}
		if(actions_choisies_.valeur(c).first.first!=""){
			nb_act_++;
			if(creatures_act.valeur(c).statut_pk()!="KO"){
				nb_non_ko_++;
			}
		}
		/*if(creatures_act.valeur(c).statut_pk()!="KO"&&actions_choisies_.valeur(c).first.first!=""){
			nb_non_ko_++;
		}*/
	}
	if(nb_non_ko_>multiplicite||(nb_act_!=multiplicite&&nb_act_!=nb_non_ko_)){
		erreur_+="action impossible\n";
	}
	HashMap<QString,uint> inv_soin_;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()!=ut){
			continue;
		}
		typedef QPair<uchar,Taux> EffectifReste;
		CreatureCombat cr_c_=creatures_act.valeur(c);
		HashMap<QString,QList<EffectifReste> >& objets_=cr_c_.objets_pk();
		foreach(QString s,objets_.cles()){
			inv_soin_.ajouter_cle_valeur(s,0);
			foreach(EffectifReste s2,objets_.valeur(s)){
				inv_soin_.valeur(s)+=s2.first;
			}
		}
		break;
	}
	HashMap<QString,uint> ut_soin_;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()!=ut){
			continue;
		}
		typedef QPair<uchar,Taux> EffectifReste;
		CreatureCombat cr_c_=creatures_act.valeur(c);
		HashMap<QString,QList<EffectifReste> >& objets_=cr_c_.objets_pk();
		foreach(QString s,objets_.cles()){
			ut_soin_.ajouter_cle_valeur(s,0);
		}
		break;
	}
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()!=ut){
			continue;
		}
		CreatureCombat cr_c_=creatures_act.valeur(c);
		if(cr_c_.act_choisie()=="SOIN"){
			ut_soin_.valeur(cr_c_.att_choisie())++;
		}
	}
	foreach(QString s,ut_soin_.cles()){
		if(ut_soin_.valeur(s)>inv_soin_.valeur(s)){
			erreur_+="action impossible\n";
		}
	}
	return QPair<QString,HashMap<Combattant,QPair<QPair<QString,QString>,Combattant> > >(erreur_,actions_choisies_);
}

HashMap<Combattant,QPair<QString,QPair<Combattant,Combattant> > > ElementsCombat::choix_ia_attaque(Donnees *_d)const{
	HashMap<Combattant,QPair<QString,QPair<Combattant,Combattant> > > actions_choisies_;
	HashMap<Combattant,HashMap<QString,QStringList> > actions_possibles_=actions_possibles(adv,_d);
	if(type_combat=="SAUVAGE"){
		actions_choisies_.ajouter_cle_valeur(Combattant(adv,0),QPair<QString,QPair<Combattant,Combattant> >("",QPair<Combattant,Combattant>(Combattant(),Combattant())));
		actions_choisies_.valeur(Combattant(adv,0)).second.first=positions_places.cles(QPair<uchar,uchar>(ut,0))[0];
		MonteCarlo<QString> loi_;
		foreach(QString a,actions_possibles_.valeur(Combattant(adv,0)).valeur("ATTAQUE")){
			loi_.ajouter_event(QPair<QString,Entier>(a,Entier(1)));
		}
		actions_choisies_.valeur(Combattant(adv,0)).first=loi_.tirage();
		return actions_choisies_;
	}
	QStringList att_switch_;
	att_switch_<<"RELAIS";
	att_switch_<<"CHANGE_ECLAIR";
	att_switch_<<"DEMI_TOUR";
	att_switch_<<"VOEU_SOIN";
	att_switch_<<"DANSE_LUNE";
	QList<Combattant> cibles_pot_;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==ut){
			if(positions_places.valeur(c).second!=arriere){
				cibles_pot_<<c;
			}
			continue;
		}
		actions_choisies_.ajouter_cle_valeur(c,QPair<QString,QPair<Combattant,Combattant> >("",QPair<Combattant,Combattant>(Combattant(),Combattant())));
	}
	QList<QPair<QPair<QPair<Taux,Taux>,QPair<Taux,Taux> >,QPair<QString,uchar> > > val_attaques_;
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==ut){
			continue;
		}
		int pos_=positions_places.valeur(c).second;
		if(pos_==arriere){
			continue;
		}
		CreatureCombat cr_c_=creatures_act.valeur(c);
		QStringList& attaques_possibles_cr_=actions_possibles_.valeur(c).valeur("ATTAQUE");
		QStringList attaques_off_;
		foreach(QString a,attaques_possibles_cr_){
			FicheAttaque *attaque_=_d->val_attaques().valeur(a);
			if(attaque_->cat()!="AUTRE"&&!cibles_possible_lanceur(c,attaque_).isEmpty()){
				attaques_off_<<a;
			}
		}
		if(attaques_possibles_cr_.size()==1||attaques_off_.size()<2){
			if(attaques_off_.isEmpty()){
				actions_choisies_.valeur(c).first=attaques_possibles_cr_[0];
			}else{
				actions_choisies_.valeur(c).first=attaques_off_[0];
			}
			FicheAttaque *attaque_=_d->val_attaques().valeur(actions_choisies_.valeur(c).first);
			QList<Combattant> cbts_=cibles_possible_lanceur(c,attaque_);
			int i_=0;
			while(i_<cbts_.size()){
				if(cbts_[i_].equipe()!=ut){
					cbts_.removeAt(i_);
				}else{
					i_++;
				}
			}
			if(!cbts_.isEmpty()&&cibles_pot_.contains(cbts_[0])){
				actions_choisies_.valeur(c).second.first=cbts_[0];
				cibles_pot_.removeOne(cbts_[0]);
			}else{
				actions_choisies_.valeur(c).second.first=Combattant();
			}
			if(att_switch_.contains(attaques_possibles_cr_[0])){
				foreach(Combattant c2,creatures_act.cles()){
					if(c2.equipe()==ut){
						continue;
					}
					if(positions_places.valeur(c2).second==arriere&&creatures_act.valeur(c2).statut_pk()!="KO"){
						actions_choisies_.valeur(c).second.second=c2;
						break;
					}
				}
			}
			continue;
		}
		QList<Combattant> cbts_=cibles_possible_lanceur_bis(c,attaques_off_,_d);
		int i_=0;
		while(i_<cbts_.size()){
			if(cbts_[i_].equipe()!=ut&&!cibles_pot_.contains(cbts_[i_])){
				cbts_.removeAt(i_);
			}else{
				i_++;
			}
		}
		if(cbts_.isEmpty()){
			actions_choisies_.valeur(c).second.first=Combattant();
			continue;
		}
		bool param_=false;
		HashMap<Combattant,bool> param_2_;
		foreach(Combattant c2,cbts_){
			CreatureCombat cible_=creatures_act.valeur(c2);
			foreach(QString a,attaques_off_){
				FicheAttaque *f_att_=_d->val_attaques().valeur(a);
				Taux prec_min_=calcul_precision(c,cr_c_,a,f_att_,c2,cible_,ElementsCombat::MINI,param_,param_,_d);
				Taux prec_max_=calcul_precision(c,cr_c_,a,f_att_,c2,cible_,ElementsCombat::MAXI,param_,param_,_d);
				Taux prec_moy_=calcul_precision(c,cr_c_,a,f_att_,c2,cible_,ElementsCombat::MOY,param_,param_,_d);
				Taux prec_var_=calcul_precision(c,cr_c_,a,f_att_,c2,cible_,ElementsCombat::VAR,param_,param_,_d);
				QString type_att_=cr_c_.type_attaque_lanceur(climat,a,effet_global("ZONE_MAGIQUE").second,_d);
				MonteCarloNombre loi_=cr_c_.loi_repet_coups(a,_d);
				Taux deg_min_=calcul_degats(loi_,a,f_att_,type_att_,c,cr_c_,c2,cible_,Taux(0),ElementsCombat::MINI,param_2_,param_2_,_d);
				Taux deg_max_=calcul_degats(loi_,a,f_att_,type_att_,c,cr_c_,c2,cible_,Taux(0),ElementsCombat::MAXI,param_2_,param_2_,_d);
				Taux deg_moy_=calcul_degats(loi_,a,f_att_,type_att_,c,cr_c_,c2,cible_,Taux(0),ElementsCombat::MOY,param_2_,param_2_,_d);
				Taux deg_var_=calcul_degats(loi_,a,f_att_,type_att_,c,cr_c_,c2,cible_,Taux(0),ElementsCombat::VAR,param_2_,param_2_,_d);
				Taux total_min_=prec_min_*deg_min_;
				Taux total_max_=prec_max_*deg_max_;
				Taux total_moy_=prec_moy_*deg_moy_;
				Taux total_var_=esperance_carree_variance_prod(QPair<Taux,Taux>(prec_moy_*prec_moy_,prec_var_),QPair<Taux,Taux>(deg_moy_*deg_moy_,deg_var_)).second;
				QPair<QPair<QPair<Taux,Taux>,QPair<Taux,Taux> >,QPair<QString,uchar> > valeur_;
				valeur_.first.first.first=total_min_;
				valeur_.first.first.second=total_max_;
				valeur_.first.second.first=total_moy_;
				valeur_.first.second.second=-total_var_;
				valeur_.second.first=a;
				valeur_.second.second=c2.position();
				val_attaques_<<valeur_;
			}
		}
		Utilitaire::trier<QPair<QPair<QPair<Taux,Taux>,QPair<Taux,Taux> >,QPair<QString,uchar> > >(val_attaques_,true);
		QPair<QString,uchar> val_=val_attaques_[0].second;
		actions_choisies_.valeur(c).first=val_.first;
		if(att_switch_.contains(val_.first)){
			foreach(Combattant c2,creatures_act.cles()){
				if(c2.equipe()==ut){
					continue;
				}
				if(positions_places.valeur(c2).second==arriere&&creatures_act.valeur(c2).statut_pk()!="KO"){
					actions_choisies_.valeur(c).second.second=c2;
					break;
				}
			}
		}
		actions_choisies_.valeur(c).second.first=Combattant(ut,val_.second);
		cibles_pot_.removeOne(Combattant(ut,val_.second));
	}
	return actions_choisies_;
}

bool ElementsCombat::perdre_dresseur()const{
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==ut&&creatures_act.valeur(c).statut_pk()!="KO"){
			return false;
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==adv&&creatures_act.valeur(c).statut_pk()!="KO"){
			return true;
		}
	}
	return false;
}

bool ElementsCombat::gagner_dresseur()const{
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==adv&&creatures_act.valeur(c).statut_pk()!="KO"){
			return false;
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()==ut&&creatures_act.valeur(c).statut_pk()!="KO"){
			return true;
		}
	}
	return false;
}

bool ElementsCombat::match_nul()const{
	foreach(Combattant c,creatures_act.cles()){
		if(creatures_act.valeur(c).statut_pk()!="KO"){
			return false;
		}
	}
	return true;
}

//On suppose que le lanceur possède au moins une cible
void ElementsCombat::tour_lanceur(const Combattant& _lc,CreatureCombat& _lanceur,Donnees *_d){
	bool boul_armure_der_=_lanceur.der_att_lancee()=="BOUL_ARMURE"&&_lanceur.att_reussie();
	_lanceur.attaques_actives_ind("PRLVT_DESTIN")=false;
	_lanceur.attaques_actives_ind("RANCUNE")=false;
	QString att_lanc_=_lanceur.att_choisie();
	if(att_lanc_!=_lanceur.der_att_lancee()){
		_lanceur.reinit_nb_utilisation_attaques();
	}
	//si lanceur.attaques_blocantes contient la clé lanceur.derniere_attaque et lanceur.derniere_attaque != attaque_lanceur et le lanceur n'est pas immunisé à la confusion
	QStringList atts_bloc_;
	atts_bloc_<<"DANSE_FLEUR";
	atts_bloc_<<"MANIA";
	atts_bloc_<<"COLERE";
	FicheAttaque *f_att_l_=_d->val_attaques().valeur(att_lanc_);
	FicheCapacite *f_capac_l_=_lanceur.fiche_capacite(_d);
	QString climat_=valeur_climat();
	bool zone_magique_=effet_global("ZONE_MAGIQUE").second;
	uchar eq_lc_=_lc.equipe();
	Baie *baie_=NULL;
	ObjetAttachableCombat *obj_=NULL;
	Objet *f_obj_=NULL;
	if(_lanceur.objet()!=""){
		f_obj_=_lanceur.fiche_objet(_d);
	}
	bool utilise_baie_=false;
	bool peut_util_obj_lc_=_lanceur.peut_utiliser_objet(zone_magique_);
	if(!atts_bloc_.contains(_lanceur.der_att_lancee())&&_lanceur.der_att_lancee()!=att_lanc_){
		if(!f_capac_l_||!f_capac_l_->immu_stat().cles().contains(climat_)||!f_capac_l_->immu_stat().valeur(climat_).contains("CONFUSION")){
			//le lanceur n'est pas immunisé à la confusion
			if(!attaque_equipe(eq_lc_,"RUNE_PROTECT").second){
				if(peut_util_obj_lc_){
					baie_=qobject_cast<Baie*>(f_obj_);
					if(baie_&&baie_->s_statut().contains("CONFUSION")){
						utilise_baie_=true;
						_lanceur.perte_objet()=true;
					}else{
						_lanceur.confusion_pk()=QPair<uchar,bool>(0,true);
					}
				}
			}
		}
	}
	if(att_lanc_=="PATIENCE"){
		//TODO etre plus generique sur le nombre de tours
		QPair<uchar,QPair<Taux,bool> >& pati_=_lanceur.patience_pk();
		if(pati_.first==2){
			_lanceur.prepa_tour_pk()=false;
			pati_.first=0;
		}else{
			_lanceur.prepa_tour_pk()=true;
			return;
		}
	}else if(_lanceur.prepa_tour_pk()){
		_lanceur.prepa_tour_pk()=false;
		_lanceur.disparition_pk()=false;
	}else if(f_att_l_->prepa()){
		bool sort_confusion_=true;
		bool auto_infli_=false;
		QPair<uchar,bool>& conf_lc_=_lanceur.confusion_pk();
		if(conf_lc_.second){
			sort_confusion_=_lanceur.tirage_confusion_nb_tour(_d);
		}
		if(!sort_confusion_){
			//TODO CreatureCombat::tirage_auto_inflige(_d)
			auto_infli_=_lanceur.tirage_auto_inflige(_d);
			conf_lc_.first++;
			if(auto_infli_){
				_lanceur.prepa_tour_pk()=false;
				_lanceur.disparition_pk()=false;
				_lanceur.reinit_nb_utilisation_attaques();
				Taux degats_(0);
				if(_lc.equipe()==ut){			
					degats_=_lanceur.calcul_degats_confusion(climat,zone_magique_,diff.r_choix_lois_conf().first,_d);
				}else{
					degats_=_lanceur.calcul_degats_confusion(climat,zone_magique_,diff.r_choix_lois_conf().second,_d);
				}
				if(degats_>=_lanceur.pv_restants_pk()){
					_lanceur.pv_restants_pk()=Taux(0);
					mise_a_ko(_lc,_lanceur,_d);
				}else{
					_lanceur.pv_restants_pk()-=degats_;
				}
				return;
			}
		}else{
			conf_lc_.first=0;
			conf_lc_.second=false;
		}
		if(!(att_lanc_=="LANCE_SOLEIL"&&climat_=="SOLEIL")){
			if(!f_capac_l_||!f_capac_l_->immu_recharg()){
				if(peut_util_obj_lc_){
					obj_=qobject_cast<ObjetAttachableCombat*>(f_obj_);
					if(obj_&&obj_->prepa_v()){
						_lanceur.val_der_objet_ut()=_lanceur.objet();
						_lanceur.objet()="";
						_lanceur.perte_objet()=true;
					}else{
						_lanceur.prepa_tour_pk()=true;
						_lanceur.disparition_pk()=f_att_l_->dispa();
						_lanceur.reinit_nb_utilisation_attaques();
					}
				}else{
					_lanceur.prepa_tour_pk()=true;
					_lanceur.disparition_pk()=f_att_l_->dispa();
					_lanceur.reinit_nb_utilisation_attaques();
				}
			}
		}
	}else if(_lanceur.nec_recharg_pk()){
		_lanceur.nec_recharg_pk()=false;
		return;
	}
	if(_lanceur.nb_pp(att_lanc_)>0&&att_lanc_!="PRESCIENCE"&&att_lanc_!="CARNAREKET"){
		if(!_lanceur.attaques_actives_def("ROULADE").second&&!_lanceur.attaques_actives_def("BALL_GLACE").second){
			_lanceur.utiliser_pp(att_lanc_,1);
		}
	}
	if(existence_entrave(_lc,att_lanc_)){
		_lanceur.annuler_patience();//il existe une cible ayant entrave qui entrave attaque_lanceur
		return;
	}
	QString att_de_lanc_=att_lanc_;
	if(att_lanc_=="MALEDICTION"){
		if(_lanceur.types_pk().contains("SPECTRE")){
			att_lanc_="MALEDICTION_2";
		}else{
			att_lanc_="MALEDICTION_1";
		}
	}
	bool peut_attaque_paralysie_=true;
	if(!f_capac_l_||!f_capac_l_->immu_para_tot()){
		if(_lanceur.statut_pk()=="PARALYSIE"){
			peut_attaque_paralysie_=CreatureCombat::tirage_paralysie(_d);
		}
	}
	if(!peut_attaque_paralysie_){
		return;
	}
	bool reveil_=false;
	if(_lanceur.statut_pk()!="SOMMEIL"){
		reveil_=true;
	}else if(!_lanceur.attaques_actives_def("REPOS").second){
		reveil_=_lanceur.tirage_reveil(_d);
	}else{
		//TODO SOMMEIL_REPOS==2
		QPair<uchar,bool>& repos_=_lanceur.attaques_actives_def("REPOS");
		uchar nb_tours_repos_=repos_.first;
		uchar som_repos_=2;
		if(nb_tours_repos_==som_repos_+1||!f_capac_l_){
			reveil_=true;
			repos_.first=0;
			repos_.second=false;
		}else{
			int div_som_=f_capac_l_->div_tr_som();
			if(nb_tours_repos_==som_repos_/div_som_+1){
				reveil_=true;
				repos_.first=0;
				repos_.second=false;
			}
		}
	}
	if(reveil_&&_lanceur.statut_pk()=="SOMMEIL"){
		_lanceur.statut_pk()="OK";
	}
	if(reveil_==f_att_l_->lanc_som()){
		return;
	}
	bool degel_=false;
	if(_lanceur.statut_pk()!="GEL"){
		degel_=true;
	}else if(_d->val_auto_degel().contains(att_lanc_)){
		degel_=true;
	}else{
		degel_=CreatureCombat::tirage_degel(_d);
	}
	if(!degel_){
		return;
	}
	if(_lanceur.statut_pk()=="GEL"){
		_lanceur.statut_pk()="OK";
	}
	bool sort_confusion_=true;
	bool auto_infli_=false;
	QPair<uchar,bool>& conf_lc_=_lanceur.confusion_pk();
	if(conf_lc_.second){
		sort_confusion_=_lanceur.tirage_confusion_nb_tour(_d);
	}
	if(!sort_confusion_){
		//TODO CreatureCombat::tirage_auto_inflige(_d)
		auto_infli_=_lanceur.tirage_auto_inflige(_d);
		conf_lc_.first++;
		if(auto_infli_){
			_lanceur.reinit_nb_utilisation_attaques();
			Taux degats_(0);
			if(_lc.equipe()==ut){			
				degats_=_lanceur.calcul_degats_confusion(climat,zone_magique_,diff.r_choix_lois_conf().first,_d);
			}else{
				degats_=_lanceur.calcul_degats_confusion(climat,zone_magique_,diff.r_choix_lois_conf().second,_d);
			}
			if(degats_>=_lanceur.pv_restants_pk()){
				_lanceur.pv_restants_pk()=Taux(0);
				mise_a_ko(_lc,_lanceur,_d);
			}else{
				_lanceur.pv_restants_pk()-=degats_;
			}
			return;
		}
	}else{
		conf_lc_.first=0;
		conf_lc_.second=false;
	}
	if(reveil_==f_att_l_->lanc_som()){
		return;
	}
	if(f_att_l_->cible_som()&&!existence_cible_dort(_lc,_d)){//aucune cible ne dort
		return;
	}
	QString type_att_;
	QStringList atts_ind_;
	atts_ind_<<"MIMIQUE";
	atts_ind_<<"MOI_D_ABORD";
	atts_ind_<<"BLABLA_DODO";
	atts_ind_<<"ASSISTANCE";
	atts_ind_<<"METRONOME";
	atts_ind_<<"GRIBOUILLE";
	atts_ind_<<"FORCE_NATURE";
	if(atts_ind_.contains(att_lanc_)){
		type_att_=_lanceur.type_attaque_lanceur(climat,att_lanc_,zone_magique_,_d);
	}
	if(atts_ind_.contains(att_lanc_)){
		QList<Combattant> cibles_=cibles_lanceur(_lc,f_att_l_);
		CreatureCombat& cible_=creatures_act.valeur(cibles_[0]);
		QPair<bool,bool> res_=condition_reussite(_lc,_lanceur,cibles_[0],cible_,att_lanc_,type_att_,_d);
		if(!res_.first){
			return;
		}
		if(att_lanc_=="MIMIQUE"){
			att_lanc_=_lanceur.att_deg_subie().second;
		}
		if(att_lanc_=="GRIBOUILLE"){
			if(cible_.der_att_lancee()!=""){
				_lanceur.apprendre_attaque(cible_.der_att_lancee(),_d);
			}else if(cible_.act_choisie()=="ATTAQUE"){
				_lanceur.apprendre_attaque(cible_.att_choisie(),_d);
			}
			//TODO apprendre attaque
		}
		if(att_lanc_=="MOI_D_ABORD"){
			if(ordre_non_joue(_d,false).contains(cibles_[0])){
				_lanceur.attaques_actives_ind("MOI_D_ABORD")=true;
			}else if(ordre_non_joue(_d,true).contains(cibles_[0])){
				_lanceur.attaques_actives_ind("MOI_D_ABORD")=true;
			}
			if(cible_.act_choisie()=="ATTAQUE"){
				att_lanc_=cible_.att_choisie();
			}
		}
		if(att_lanc_=="PHOTOCOPIE"){
			if(cible_.act_choisie()=="ATTAQUE"){
				att_lanc_=cible_.att_choisie();
			}
		}
		if(att_lanc_=="BLABLA_DODO"){
			if(!_lanceur.attaques_actives_def("PROVOC").second&&_lanceur.statut_pk()=="SOMMEIL"){
				att_lanc_=_lanceur.tirage_attaques_blabladodo(_d->val_blabla_dodo_attaques());
			}else{
				return;
			}
		}
		if(att_lanc_=="ASSISTANCE"){
			if(_lanceur.attaques_actives_def("PROVOC").second){
				return;
			}
			QStringList attaques_part_;
			foreach(Combattant c,creatures_act.cles()){
				if(c!=_lc&&c.equipe()==_lc.equipe()){
					attaques_part_<<creatures_act.valeur(c).noms_attaques_act();
				}
			}
			attaques_part_.removeDuplicates();
			QStringList attaques_act_l_=_lanceur.noms_attaques_act()<<_d->val_assistance_attaques();
			attaques_act_l_.removeDuplicates();
			QStringList complement_attaques_act_l_;
			foreach(QString a,_d->val_attaques().cles()){
				if(!attaques_act_l_.contains(a)){
					complement_attaques_act_l_<<a;
				}
			}
			QStringList attaques_appel_assist_;
			foreach(QString a,attaques_part_){
				if(complement_attaques_act_l_.contains(a)){
					attaques_appel_assist_<<a;
				}
			}
			if(attaques_appel_assist_.isEmpty()){
				return;
			}
			att_lanc_=CreatureCombat::tirage_attaque(attaques_appel_assist_);
		}
		if(att_lanc_=="METRONOME"){
			if(_lanceur.attaques_actives_def("PROVOC").second){
				return;
			}
			QStringList attaques_act_l_=_lanceur.noms_attaques_act()<<_d->val_metronome();
			attaques_act_l_.removeDuplicates();
			QStringList complement_attaques_act_l_;
			foreach(QString a,_d->val_attaques().cles()){
				if(!attaques_act_l_.contains(a)){
					complement_attaques_act_l_<<a;
				}
			}
			att_lanc_=CreatureCombat::tirage_attaque(complement_attaques_act_l_);
		}
		if(att_lanc_=="FORCE_NATURE"){
			att_lanc_=_d->val_force_nature().valeur(type_environnement);
		}
	}
	_lanceur.att_choisie()=att_lanc_;
	type_att_=_lanceur.type_attaque_lanceur(climat,att_lanc_,zone_magique_,_d);
	f_att_l_=_d->val_attaques().valeur(att_lanc_);
	QList<Combattant> cibles_=cibles_lanceur(_lc,f_att_l_);
	//bool util_baie_=false
	HashMap<Combattant,bool> cc_min_;
	HashMap<Combattant,bool> util_baie_;
	foreach(Combattant c,creatures_act.cles()){
		util_baie_.ajouter_cle_valeur(c,false);
		cc_min_.ajouter_cle_valeur(c,false);
	}
	foreach(Combattant c,cibles_){//cible peut valoir lanceur, Ex: armure,...
	//plus tard debut de la boucle des cibles
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		bool util_att_prec_suiv_=false;
		bool peut_att_amour_=true;
		if(_lanceur.att_active_cible("AMOUR",c)){
			peut_att_amour_=CreatureCombat::tirage_amoureux(_d);
		}
		if(!peut_att_amour_){
			continue;
		}
		FicheCapacite *f_capac_c_=cr_c_.fiche_capacite(_d);
		QPair<bool,bool> res_=condition_reussite(_lc,_lanceur,c,cr_c_,att_lanc_,type_att_,_d);
		if(!res_.first){
			commentaire_recent+=_lanceur.nom_pk_act()+" a rate l'attaque "+att_lanc_+"\n";
			if(att_lanc_=="TAILLADE"){
				_lanceur.nb_lancer(att_lanc_)=0;
			}
			_lanceur.reinit_nb_utilisation_attaques();
			if(res_.second){
				//immu attaque types
				if(calcul_precision(_lc,_lanceur,att_lanc_,f_att_l_,c,cr_c_,ElementsCombat::ALEA,util_att_prec_suiv_,util_baie_.valeur(_lc),_d).estNul()){
					continue;
				}
				EffetStatut *eff_=NULL;
				int nb_=f_att_l_->effs().size();
				if(nb_>1){
					eff_=qobject_cast<EffetStatut*>(f_att_l_->effs()[0]);
				}
				bool traiter_conf_=false;
				if(eff_&&eff_->statuts_possibles_non_ok().contains("CONFUSION")){
					if(f_capac_c_&&f_capac_c_->immu_stat().cles().contains(valeur_climat())){
						if(f_capac_c_->immu_stat().valeur(valeur_climat()).contains("CONFUSION")){
							traiter_conf_=true;
						}
					}
				}
				if(cr_c_.confusion_pk().second||attaque_equipe(c.equipe(),"RUNE_PROTECT").second){
					traiter_conf_=true;
				}
				derniere_attaque_reussie=att_lanc_;
				_lanceur.der_att_reussie()=att_lanc_;
				_lanceur.att_reussie()=true;
				if(traiter_conf_){
					if(cr_c_.att_choisie()=="REFLET_MAGIK"&&_lc!=c){
						MonteCarlo<QString> loi_;
						EffetStatut *effet_=qobject_cast<EffetStatut*>(f_att_l_->effs()[0]);
						if(f_capac_c_&&f_capac_c_->mult_pr_eff_sec().cles().contains(true)){
							loi_=effet_->tirage_statut(f_capac_c_->mult_pr_eff_sec().valeur(true),attaque_equipe(c.equipe(),"AIRE_EAU_FEU").second,true);
						}else{
							loi_=effet_->tirage_statut(1,attaque_equipe(c.equipe(),"AIRE_EAU_FEU").second,true);
							//TODO a inserer cas effet d'attaque
						}
						traiter_effet_statut(_lc,_lanceur,_lc.equipe(),cr_c_,c.equipe(),loi_,att_lanc_,false,_d);
					}		
					EffetStatistique *eff_statist_=qobject_cast<EffetStatistique*>(f_att_l_->effs()[1]);
					if(eff_statist_){
						traiter_effet_statist(cr_c_,_lanceur,_lc.equipe(),eff_statist_,false,_d)		;
					}
				}
				if(f_capac_c_&&f_capac_c_->immu_att_t().contains(type_att_)){
					if(f_capac_c_->gain_pv_t().cles().contains(type_att_)){
						if(!attaque_equipe(adversaire(c.equipe()),"ANTI_SOIN").second){
							Taux pv_soignes_(0);
							cr_c_.soin_pv(cr_c_.pv_max()*f_capac_c_->gain_pv_t().valeur(type_att_),pv_soignes_,_d);
						}
					}
					foreach(QString s,f_capac_c_->mult_statis().cles()){
						QPair<Taux,bool> valeur_=f_capac_c_->mult_statis().valeur(s);
						if(!valeur_.second){
							cr_c_.var_boost(s,valeur_.first,_d);
						}
					}
					if(f_capac_c_&&f_capac_c_->mult_puis_att_t().cles().contains(type_att_)){
						cr_c_.r_coeff_att_types_lancees(type_att_)*=f_capac_c_->mult_puis_att_t().valeur(type_att_);
						if(type_att_=="FEU"&&cr_c_.statut_pk()=="GEL"){
							cr_c_.statut_pk()="OK";
						}
					}
				}
			}
			continue;
		}
		Taux coeff_eff_(1);
		foreach(QString t,cr_c_.types_pk()){
			coeff_eff_*=_lanceur.table_eff(c,QPair<QString,QString>(type_att_,t));
		}
		//todo traiter coeff_eff == 0 lorsque effet_specifique
		//lanceur:brise_moule cible:levitation type_attaque:sol => condition fausse
		//lanceur:brise_moule cible:torche type_attaque:feu => condition fausse
		//lanceur.capacite ignore cible.capacite et cible.capacite contient IMMU[TYPE et cible.puissance_attaque_subie[type_attaque] == 0 ==> faux
		//lanceur:levitation cible:levitation type_attaque:sol => condition vraie
		//lanceur.capacite n'ignore pas cible.capacite et cible.capacite contient IMMU[TYPE et cible.puissance_attaque_subie[type_attaque] == 0 ==> vrai
		//cible_type:vol type_attaque:sol pas de gravité, ni de racines, ni de anti_air => condition vraie
		//cible_type:vol type_attaque:sol anti_air => condition fausse
		//cible_type:vol type_attaque:sol racines => condition fausse
		//cible_type:vol type_attaque:sol gravité => condition fausse
		//lanceur:levitation cible:levitation type_attaque:sol anti_air => condition faux
		QStringList attaques_excep_;
		attaques_excep_<<"LUTTE";
		attaques_excep_<<"PATIENCE";
		attaques_excep_<<"BASTON";
		bool traiter_ineff_=false;
		if(!attaques_excep_.contains(att_lanc_)&&f_att_l_->cat()!="AUTRE"){
			traiter_ineff_=true;
		}
		if(traiter_ineff_){
			if(_lanceur.peut_utiliser_objet(zone_magique_)){
				obj_=qobject_cast<ObjetAttachableCombat*>(f_obj_);
				if(obj_&&obj_->annule_immu_t()){
					traiter_ineff_=false;
				}
			}
		}
		if(traiter_ineff_){
			if(!cr_c_.immu_att_type(type_att_)&&coeff_eff_>Taux(0)){
				traiter_ineff_=false;
			}
		}
		if(traiter_ineff_){
			if(f_att_l_->effs().isEmpty()){
				continue;
			}
			if(f_att_l_->effs()[0]->qui()){
				traiter_ineff_=false;
			}
		}
		if(traiter_ineff_){
			if(f_att_l_->eff_n_deg()){
				if(calcul_precision(_lc,_lanceur,att_lanc_,f_att_l_,c,cr_c_,ElementsCombat::ALEA,util_att_prec_suiv_,util_baie_.valeur(_lc),_d).estNul()){
					commentaire_recent+=_lanceur.nom_pk_act()+" a rate l'attaque "+att_lanc_+" par manque de precision\n";
					continue;
				}
				if(att_lanc_=="CASSE_BRIQUE"){
					derniere_attaque_reussie=att_lanc_;
					_lanceur.der_att_reussie()=att_lanc_;
					_lanceur.att_reussie()=true;
					attaque_equipe(c.equipe(),"MUR_LUMIERE")=QPair<uchar,bool>(0,false);
					attaque_equipe(c.equipe(),"PROTECTION")=QPair<uchar,bool>(0,false);
				}
				if(att_lanc_=="TOUR_RAPIDE"){
					derniere_attaque_reussie=att_lanc_;
					_lanceur.der_att_reussie()=att_lanc_;
					_lanceur.att_reussie()=true;
					_lanceur.attaques_actives_ind("VAMPIGRAINE")=false;
					attaque_equipe(c.equipe(),"PICOTS")=QPair<uchar,bool>(0,false);
					attaque_equipe(c.equipe(),"PICS_TOXIKS")=QPair<uchar,bool>(0,false);
					attaque_equipe(c.equipe(),"PIEGE_DE_ROC")=QPair<uchar,bool>(0,false);
					typedef QPair<Combattant,QString> CombattantAttaquePieg;
					foreach(Combattant c2,creatures_act.cles()){
						if(c2.equipe()==_lc.equipe()){
							continue;
						}
						CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
						foreach(CombattantAttaquePieg c3,cr_c_2_.val_attaques_piegeantes()){
							if(c3.first==_lc){
								cr_c_2_.att_pieg(c3)=QPair<bool,uchar>(false,0);
							}
						}
					}
				}
			}
			if(att_lanc_=="BROUHAHA"){
				_lanceur.attaques_actives_def("BROUHAHA")=QPair<uchar,bool>(true,0);
				foreach(Combattant c2,creatures_act.cles()){
					CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
					if(cr_c_2_.statut_pk()=="SOMMEIL"){
						FicheCapacite *f_capac_c_3_=cr_c_2_.fiche_capacite(_d);
						if(!f_capac_c_3_||!f_capac_c_3_->immu_att().contains(att_lanc_)){
							cr_c_2_.statut_pk()="OK";
							cr_c_2_.attaques_actives_def("REPOS")=QPair<uchar,bool>(false,0);
							cr_c_2_.sommeil_non_repos()=0;
						}
					}
				}
			}
			commentaire_recent+=_lanceur.nom_pk_act()+" a rate l'attaque "+att_lanc_+" par inefficacite\n";
			continue;
		}
		ObjetAttachableCombat *obj_c_=NULL;
		Objet *f_obj_c_=cr_c_.fiche_objet(_d);
		Baie *baie_c_=NULL;
		if(cr_c_.peut_utiliser_objet(zone_magique_)){
			baie_c_=qobject_cast<Baie*>(cr_c_.fiche_objet(_d));
		}
		if(coeff_eff_>Taux(1)&&f_att_l_->cat()!="AUTRE"){
		//baie enigma
			if(baie_c_&&!baie_c_->gain_pv_sup_ef().estNul()){
				if(!f_capac_l_||!f_capac_l_->anti_conso_baies_adv()){
					Taux pv_soignes_(0);
					cr_c_.soin_pv(baie_c_->gain_pv_sup_ef()*cr_c_.pv_max(),pv_soignes_,_d);
					if(!pv_soignes_.estNul()){
						cr_c_.perte_objet()=true;
						cr_c_.utilisation_baie()=true;
					}			
					commentaire_recent+=_lanceur.nom_pk_act()+" a rate l'attaque "+att_lanc_+" par baie enigma su cible\n";
					continue;
				}
			}
		}
		attaques_excep_.clear();
		if(!attaques_excep_.contains(att_lanc_)&&f_att_l_->cat()!="AUTRE"&&coeff_eff_<=Taux(1)){
		//coeff_eff <= 1 <=> cible.capacite.eff == attaque_lanceur.eff
		//garde mystik
			if(f_capac_c_&&f_capac_c_->mult_deg_rec().cles().contains(false)){
				if(f_capac_c_->mult_deg_rec().valeur(false).estNul()){
					if(f_att_l_->eff_n_deg()){
						if(calcul_precision(_lc,_lanceur,att_lanc_,f_att_l_,c,cr_c_,ElementsCombat::ALEA,util_att_prec_suiv_,util_baie_.valeur(_lc),_d).estNul()){
							commentaire_recent+=_lanceur.nom_pk_act()+" a rate l'attaque "+att_lanc_+" par manque de precision\n";
							continue;
						}
						if(att_lanc_=="CASSE_BRIQUE"){
							derniere_attaque_reussie=att_lanc_;
							_lanceur.der_att_reussie()=att_lanc_;
							_lanceur.att_reussie()=true;
							attaque_equipe(c.equipe(),"MUR_LUMIERE")=QPair<uchar,bool>(0,false);
							attaque_equipe(c.equipe(),"PROTECTION")=QPair<uchar,bool>(0,false);
						}
						if(att_lanc_=="TOUR_RAPIDE"){
							derniere_attaque_reussie=att_lanc_;
							_lanceur.der_att_reussie()=att_lanc_;
							_lanceur.att_reussie()=true;
							_lanceur.attaques_actives_ind("VAMPIGRAINE")=false;
							attaque_equipe(c.equipe(),"PICOTS")=QPair<uchar,bool>(0,false);
							attaque_equipe(c.equipe(),"PICS_TOXIKS")=QPair<uchar,bool>(0,false);
							attaque_equipe(c.equipe(),"PIEGE_DE_ROC")=QPair<uchar,bool>(0,false);
							typedef QPair<Combattant,QString> CombattantAttaquePieg;
							foreach(Combattant c2,creatures_act.cles()){
								if(c2.equipe()==_lc.equipe()){
									continue;
								}
								CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
								foreach(CombattantAttaquePieg c3,cr_c_2_.val_attaques_piegeantes()){
									if(c3.first==_lc){
										cr_c_2_.att_pieg(c3)=QPair<bool,uchar>(false,0);
									}
								}
							}
						}
					}
					commentaire_recent+=_lanceur.nom_pk_act()+" a rate l'attaque "+att_lanc_+" par garde mystik\n";
					continue;
				}
			}
		}
		attaques_excep_.clear();
		attaques_excep_<<"PRESCIENCE";
		attaques_excep_<<"CARNAREKET";
		attaques_excep_<<"PATIENCE";
		if(!attaques_excep_.contains(att_lanc_)&&calcul_precision(_lc,_lanceur,att_lanc_,f_att_l_,c,cr_c_,ElementsCombat::ALEA,util_att_prec_suiv_,util_baie_.valeur(_lc),_d).estNul()){
			if(att_lanc_=="TAILLADE"){
				_lanceur.nb_lancer(att_lanc_)=0;
			}
			_lanceur.reinit_nb_utilisation_attaques();
			commentaire_recent+=_lanceur.nom_pk_act()+" a rate l'attaque "+att_lanc_+" par manque de precision\n";
			continue;
		}
		bool existe_saisie_2_=false;
		Combattant cbt_reflet_m_;
		Combattant lc_=_lc;
		Combattant cb_=c;
		bool chgt_=false;
		bool reflet_mag_=false;
		if(f_att_l_->qi().contains("TOUS ADV")){
			foreach(Combattant c2,creatures_act.cles()){
				if(positions_places.valeur(c2).second==arriere){
					continue;
				}
				CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
				if(cr_c_2_.att_choisie()=="REFLET_MAGIK"&&cr_c_2_.att_reussie()&&_d->val_reflet_magik().contains(att_lanc_)){
					cbt_reflet_m_=_lc;
					lc_=c2;
					chgt_=true;
					reflet_mag_=true;
					break;
				}
			}
		}else if(cr_c_.att_choisie()=="REFLET_MAGIK"&&cr_c_.att_reussie()&&_d->val_reflet_magik().contains(att_lanc_)){
			Combattant tmp_=cb_;
			cb_=lc_;
			lc_=tmp_;
			reflet_mag_=true;
			chgt_=true;
		}else{
			if(c==_lc||att_lanc_=="BOOST"){
				foreach(Combattant c2,creatures_act.cles()){
					if(positions_places.valeur(c2).second==arriere){
						continue;
					}
					if(lanceur_saisie.valeur(lc_)==c2&&creatures_act.valeur(c2).statut_pk()!="KO"&&_d->val_saisie_attaques().contains(att_lanc_)){
						existe_saisie_2_=true;
					}
				}
			}
			if(existe_saisie_2_){
				chgt_=true;
				cb_=lc_;
				lc_=lanceur_saisie.valeur(lc_);
			}
		}
		CreatureCombat& cible_=creatures_act.valeur(cb_);
		CreatureCombat& lanceur_=creatures_act.valeur(lc_);
		bool existe_anti_immu_=false;
		int ind_=-1;
		foreach(Effet *e,f_att_l_->effs()){
			ind_++;
			if(qobject_cast<EffetAntiImmu*>(e)){
				existe_anti_immu_=true;
				break;
			}
		}
		if(existe_anti_immu_){//tp()
			qint8 boost_=cible_.boost("ESQUIVE");
			if(boost_>0){
				cible_.reinit_boost("ESQUIVE",_d);
			}
			cible_.attaques_actives_ind(att_lanc_)=true;
			//lanceur.clairvoyance_actif[cible] <- vrai
			//lanceur.flair_actif[cible] <- vrai
			//lanceur.oeil_miracle_actif[cible] <- vrai
			EffetAntiImmu *eff_anti_im_=qobject_cast<EffetAntiImmu*>(f_att_l_->effs()[ind_]);
			typedef QPair<QString,QString> AntiImmu;
			foreach(AntiImmu a,eff_anti_im_->tp()){
				Taux& taux_=lanceur_.table_eff(cb_,a);
				if(taux_.estNul()){
					taux_=Taux(1);
				}
			}
		}
		lanceur_.att_reussie()=true;
		//todo permuttant les valeur de lanceur et de cible pour un lanceur de reflet_magik qui est cible d'une attaque concernée par reflet_magik
		//todo permuttant les valeur de lanceur et de cible pour un lanceur de saisie sur le lanceur d'une attaque concernée par saisie
		//TODO etre plus generique
		if((type_att_=="FEU"||att_lanc_=="EBULLITION")&&cible_.statut_pk()=="GEL"){
			cible_.statut_pk()="OK";
		}
		if(att_lanc_=="TAILLADE"){
			lanceur_.nb_lancer(att_lanc_)++;
		}
		typedef QPair<QString,uchar> AttaqueEquipe;
		foreach(AttaqueEquipe a,nb_utilisation_attaques.cles()){
			if(a.first==att_lanc_&&a.second==lc_.equipe()){
				nb_utilisation_attaques.valeur(a)++;
			}
		}
		if(att_lanc_=="LILLIPUT"){
			lanceur_.attaques_actives_ind(att_lanc_)=true;
		}
		if(att_lanc_=="BAIN_DE_SMOG"){
			foreach(QString s,cible_.statis_boost()){
				cible_.reinit_boost(s,_d);
			}
		}
		FicheCapacite *f_capac_c_2_=cible_.fiche_capacite(_d);
		FicheCapacite *f_capac_l_2_=lanceur_.fiche_capacite(_d);
		if(att_lanc_=="CHUTE_LIBRE"&&!cible_.attaques_actives_ind("ANTI_AIR")){
			if(cible_.types_pk().contains("VOL")){
				continue;
			}
			if(cible_.capacite_pk_act()=="LEVITATION"&&(!f_capac_l_2_||!f_capac_l_2_->capac_ign().contains(cible_.capacite_pk_act()))){
				continue;
			}
		}
		if(att_lanc_=="TEMPRETTE"){
			continue;
		}
		lanceur_.der_att_reussie()=att_lanc_;
		lanceur_.gain_nb_utilisation_attaques();
		derniere_attaque_reussie=att_lanc_;
		if(cb_!=lc_){
			cible_.att_deg_subie().second=att_lanc_;
		}
		if(!chgt_){
			if(lanceur_.nb_pp(att_de_lanc_)>0&&f_capac_c_2_&&f_capac_c_2_->nb_pp_ut()>0){
				if(lc_.equipe()!=cb_.equipe()&&att_de_lanc_!="CARNAREKET"&&att_de_lanc_!="PRESCIENCE"){
					if(!_lanceur.attaques_actives_def("ROULADE").second&&!_lanceur.attaques_actives_def("BALL_GLACE").second){
						lanceur_.utiliser_pp(att_de_lanc_,f_capac_c_2_->nb_pp_ut());
					}
				}
			}
		}
		if(f_att_l_->bloc_lan()&&f_att_l_->loi_rep_tour().maximum()==Taux(1)){
			if((!f_capac_l_2_||!f_capac_l_2_->immu_recharg())&&lanceur_.statut_pk()!="SOMMEIL"){
				lanceur_.nec_recharg_pk()=true;
			}
		}
		Effet *effet_prim_=NULL;
		if(!f_att_l_->effs().isEmpty()){
			effet_prim_=f_att_l_->effs()[0];
		}
		Taux degats_2_(0);
		Taux degats_(0);
		Taux excuse_(0);
		if(att_lanc_=="EXCUSE"){
			excuse_=CreatureCombat::tirage_excuse();
		}
		if(att_lanc_=="ALLEGEMENT"){
			lanceur_.masse_pk()/=Taux(2);
		}
		if(att_lanc_=="PAR_ICI"||att_lanc_=="POUDREFUREUR"){
			lanceur_par_ici.valeur(lc_.equipe())=lc_.position();
		}else if(att_lanc_=="COPIE_TYPE"){
			lanceur_.types_pk()=cible_.types_pk();
			if(lanceur_.types_pk().contains("VOL")){
				lanceur_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
			}
		}else if(att_lanc_=="PARTAGE_FORCE"){
			//TODO ajouter cas ev et iv
			Taux moy_=(lanceur_.statistique("ATTAQUE")+cible_.statistique("ATTAQUE"))*Taux(1LL,2LL);
			lanceur_.mod_statistique("ATTAQUE",moy_);
			cible_.mod_statistique("ATTAQUE",moy_);
			moy_=(lanceur_.statistique("ATTAQUE_SPECIALE")+cible_.statistique("ATTAQUE_SPECIALE"))*Taux(1LL,2LL);
			lanceur_.mod_statistique("ATTAQUE_SPECIALE",moy_);
			cible_.mod_statistique("ATTAQUE_SPECIALE",moy_);
		}else if(att_lanc_=="PARTAGE_GARDE"){
			//TODO ajouter cas ev et iv
			Taux moy_=(lanceur_.statistique("DEFENSE")+cible_.statistique("DEFENSE"))*Taux(1LL,2LL);
			lanceur_.mod_statistique("DEFENSE",moy_);
			cible_.mod_statistique("DEFENSE",moy_);
			moy_=(lanceur_.statistique("DEFENSE_SPECIALE")+cible_.statistique("DEFENSE_SPECIALE"))*Taux(1LL,2LL);
			lanceur_.mod_statistique("DEFENSE_SPECIALE",moy_);
			cible_.mod_statistique("DEFENSE_SPECIALE",moy_);
		}else if(att_lanc_=="PASSE_CADEAU"){
			cible_.objet()=lanceur_.objet();
			if(lc_.equipe()==ut){
				++objets_utilisateur_perdus.valeur(lanceur_.objet());
			}
			if(cible_.objet()=="BALLE_FER"){
				cible_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
			}
			lanceur_.val_der_objet_ut()=lanceur_.objet();
			lanceur_.objet()="";
		}else if(att_lanc_=="VIBRA_SOIN"){
			Taux pv_soignes_(0);
			cible_.soin_pv(cible_.pv_max(),pv_soignes_,_d);
		}else if(att_lanc_=="A_LA_QUEUE"){
			/*
			TODO a voir
			if(reflet_mag_){
				cible_.cibles().clear()
				cible_.cibles()<<positions_places.valeur(lanceur_)
			}*/
		}else if(att_lanc_=="INTERVERSION"){
			uchar pos_=positions_places.valeur(cb_).second;
			positions_places.valeur(cb_).second=positions_places.valeur(_lc).second;
			positions_places.valeur(_lc).second=pos_;
			pos_=positions_places_bis.valeur(cb_).second;
			positions_places_bis.valeur(cb_).second=positions_places_bis.valeur(_lc).second;
			positions_places_bis.valeur(_lc).second=pos_;
		}else if(att_lanc_=="TOUT_OU_RIEN"){
			degats_2_=lanceur_.pv_restants_pk();
			if(degats_2_>=cible_.pv_restants_pk()){
				if(!f_att_l_->pas_ko()&&!(cible_.att_choisie()=="TENACITE"&&cible_.att_reussie())){
					mise_a_ko(cb_,cible_,_d);
				}else{
					if(f_att_l_->cat()=="PHYSIQUE"){
						cible_.att_deg_subie().first.first+=cible_.pv_restants_pk()-Taux(1);
					}else if(f_att_l_->cat()=="SPECIALE"){
						cible_.att_deg_subie().first.second+=cible_.pv_restants_pk()-Taux(1);
					}
					cible_.pv_restants_pk()=Taux(1);
				}
			}else{
				cible_.pv_restants_pk()-=degats_2_;
			}
			mise_a_ko(lc_,lanceur_,_d);
		}else if(att_lanc_=="COUP_D_MAIN"){
			cible_.attaques_actives_ind(att_lanc_)=true;
		}else if(qobject_cast<EffetStatistique*>(effet_prim_)){
			foreach(Effet *e,f_att_l_->effs()){
				EffetStatistique *effet_sec_=qobject_cast<EffetStatistique*>(e);
				if(effet_sec_){
					traiter_effet_statist(cible_,lanceur_,_lc.equipe(),effet_sec_,true,_d);
				}
			}
		}else if(att_lanc_=="BAILLEMENT"){
			cible_.attaques_actives_def(att_lanc_)=QPair<uchar,bool>(0,true);
		}else if(att_lanc_=="VANTARDISE"||att_lanc_=="FLATTERIE"){
			MonteCarlo<QString> loi_;
			EffetStatut *effet_=qobject_cast<EffetStatut*>(f_att_l_->effs()[0]);
			if(f_capac_l_2_&&f_capac_l_2_->mult_pr_eff_sec().cles().contains(true)){
				loi_=effet_->tirage_statut(f_capac_l_2_->mult_pr_eff_sec().valeur(true),attaque_equipe(lc_.equipe(),"AIRE_EAU_FEU").second,true);
			}else{
				loi_=effet_->tirage_statut(1,attaque_equipe(lc_.equipe(),"AIRE_EAU_FEU").second,true);
				//TODO a inserer cas effet d'attaque
			}
			traiter_effet_statut(cb_,cible_,cb_.equipe(),lanceur_,lc_.equipe(),loi_,att_lanc_,false,_d);
			traiter_effet_statist(cible_,lanceur_,_lc.equipe(),qobject_cast<EffetStatistique*>(f_att_l_->effs()[1]),true,_d);
		}else if(qobject_cast<EffetStatut*>(effet_prim_)){
			MonteCarlo<QString> loi_;
			EffetStatut *effet_=qobject_cast<EffetStatut*>(effet_prim_);
			if(f_capac_l_2_&&f_capac_l_2_->mult_pr_eff_sec().cles().contains(true)){
				loi_=effet_->tirage_statut(f_capac_l_2_->mult_pr_eff_sec().valeur(true),attaque_equipe(lc_.equipe(),"AIRE_EAU_FEU").second,true);
			}else{
				loi_=effet_->tirage_statut(1,attaque_equipe(lc_.equipe(),"AIRE_EAU_FEU").second,true);
				//TODO a inserer cas effet d'attaque
			}
			traiter_effet_statut(cb_,cible_,cb_.equipe(),lanceur_,lc_.equipe(),loi_,att_lanc_,false,_d);
		}else if(qobject_cast<EffetMultPuissAttaque*>(effet_prim_)){
			EffetMultPuissAttaque *effet_mult_=qobject_cast<EffetMultPuissAttaque*>(effet_prim_);
			if(effet_mult_->n_subi()){
				lanceur_.r_coeff_att_types_lancees(effet_mult_->tp())*=effet_mult_->co();
			}else{
				lanceur_.maj_coeff_att_types_subies_2(effet_mult_->tp(),effet_mult_->co());
			}
		}else if(qobject_cast<EffetClimat*>(effet_prim_)){
		//n_subi()
			climat.first.first=qobject_cast<EffetClimat*>(effet_prim_)->cl();
			climat.first.second=0;
			climat.second.second=false;
			climat.second.first=!existence_anti_climat_actif(_d);
			if(climat.second.first){
				QList<Combattant> cbts_=creatures_act.cles();
				foreach(Combattant c2,creatures_act.cles()){
					Taux pv_soignes_2_(0);
					CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
					cr_c_2_.activer_capacite(cr_c_2_.capacite_pk_act()!="",_d,positions_places,zone_magique_,arriere,climat,pv_soignes_2_);
					if(positions_places.valeur(c2).second!=arriere&&cr_c_2_.statut_pk()=="GEL"&&climat.first.first=="SOLEIL"){
						cr_c_2_.statut_pk()="OK";
					}
				}
			}
		}else if(f_att_l_->cat()!="AUTRE"&&excuse_>=Taux(0)){
			Taux nombre_coup_repet_(1);
			if(att_de_lanc_==att_lanc_){
				if(att_lanc_=="ROULADE"||att_lanc_=="BALL_GLACE"){
					if(!lanceur_.attaques_actives_def(att_lanc_).second){
						if(boul_armure_der_){//TODO
							lanceur_.coeff_roul_ballglace()=2;
						}else{//TODO
							lanceur_.coeff_roul_ballglace()=1;
						}
						lanceur_.attaques_actives_def(att_lanc_)=QPair<uchar,bool>(0,true);
					}else{//TODO
						lanceur_.coeff_roul_ballglace()*=2;
					}
				}
				if(att_lanc_=="MANIA"||att_lanc_=="DANSE_FLEUR"||att_lanc_=="COLERE"){
					if(!lanceur_.attaques_actives_def(att_lanc_).second){
						lanceur_.attaques_actives_def(att_lanc_)=QPair<uchar,bool>(0,true);
					}
				}
			}
			if(att_lanc_=="CASSE_BRIQUE"){
				attaque_equipe(cb_.equipe(),"MUR_LUMIERE")=QPair<uchar,bool>(0,false);
				attaque_equipe(cb_.equipe(),"PROTECTION")=QPair<uchar,bool>(0,false);
			}
			if(att_lanc_=="JACKPOT"){
				var_argent+=Taux((cible_.niveau_pk()+lanceur_.niveau_pk())*(int)40);
			}
			MonteCarloNombre loi_repet_coup_=lanceur_.loi_repet_coups(att_lanc_,_d);
			Taux nombre_coup_repet_min_=loi_repet_coup_.minimum();
			degats_=calcul_degats(loi_repet_coup_,att_lanc_,f_att_l_,type_att_,lc_,lanceur_,cb_,cible_,excuse_,ElementsCombat::MINI,util_baie_,cc_min_,_d);
			degats_2_=Utilitaire::max_min<Taux>(degats_,cible_.pv_restants_pk()).second;
			Taux degats_clone_=degats_;
			Taux degats_presc_carnar_(0);
			if(att_lanc_=="PRESCIENCE"||att_lanc_=="CARNAREKET"){
				degats_presc_carnar_=calcul_degats(loi_repet_coup_,att_lanc_,f_att_l_,type_att_,lc_,lanceur_,cb_,cible_,excuse_,ElementsCombat::ALEA,util_baie_,cc_min_,_d,nombre_coup_repet_min_);
			}else if(nombre_coup_repet_min_==Taux(1)&&!cible_.clone_pk().estNul()){
				if(f_capac_c_2_){
					foreach(QString s,f_capac_c_2_->mult_statis_to_t().cles()){
						if(s==type_att_){
							QPair<QString,qint8> val_=f_capac_c_2_->mult_statis_to_t().valeur(s);
							cible_.var_boost(val_.first,val_.second,_d);
						}
					}
				}
				if(degats_>=cible_.clone_pk()){
					degats_clone_=cible_.clone_pk();
					cible_.clone_pk()=Taux(0);
					if(f_att_l_->bloc_lan()&&f_att_l_->loi_rep_tour().maximum()==Taux(1)){
						if((!f_capac_l_2_||!f_capac_l_2_->immu_recharg())){
							lanceur_.nec_recharg_pk()=false;
						}
					}
				}else{
					cible_.clone_pk()-=degats_;
				}
			}else if(degats_>=cible_.pv_restants_pk()){
				degats_clone_=Taux(0);
				if(!f_att_l_->pas_ko()&&!(cible_.att_choisie()=="TENACITE"&&cible_.att_reussie())){
					mise_a_ko(cb_,cible_,_d);
				}else{
					if(f_att_l_->cat()=="PHYSIQUE"){
						cible_.att_deg_subie().first.first+=cible_.pv_restants_pk()-Taux(1);
					}else if(f_att_l_->cat()=="SPECIALE"){
						cible_.att_deg_subie().first.second+=cible_.pv_restants_pk()-Taux(1);
					}
					cible_.pv_restants_pk()=Taux(1);
				}
			}else if(loi_repet_coup_.minimum()<loi_repet_coup_.maximum()){
				nombre_coup_repet_min_=loi_repet_coup_.tirage();
				degats_2_=Taux(0);
				degats_clone_=Taux(0);
				for(int i=0;i<(int)nombre_coup_repet_min_;i++){
					if(degats_2_>=cible_.pv_restants_pk()){
						break;
					}
					Taux degats_tmp_=calcul_degats(loi_repet_coup_,att_lanc_,f_att_l_,type_att_,lc_,lanceur_,cb_,cible_,excuse_,ElementsCombat::ALEA,util_baie_,cc_min_,_d,Taux(1));
					if(f_capac_c_2_&&cc_min_.valeur(lc_)){
						if(!f_capac_l_2_||!f_capac_l_2_->capac_ign().contains(cible_.capacite_pk_act())){
							foreach(QString s,f_capac_c_2_->statis_max_cc()){
								cible_.reinit_boost(s,_d);
								cible_.var_boost(s,_d->constante_numerique("MAX_BOOST"),_d);
							}
						}
					}
					if(f_capac_c_2_){
						foreach(QString s,f_capac_c_2_->mult_statis_to_categ().cles()){
							if(s==f_att_l_->cat()){
								typedef QPair<QString,qint8> StatBoost;
								foreach(StatBoost s2,f_capac_c_2_->mult_statis_to_categ().valeur(s)){
									cible_.var_boost(s2.first,s2.second,_d);
								}
							}
						}
						foreach(QString s,f_capac_c_2_->mult_statis_to_t().cles()){
							if(s==type_att_){
								QPair<QString,qint8> val_=f_capac_c_2_->mult_statis_to_t().valeur(s);
								cible_.var_boost(val_.first,val_.second,_d);
							}
						}
					}
					if(!cible_.clone_pk().estNul()){
						if(cible_.clone_pk()+degats_tmp_>=cible_.clone_pk()){
							degats_clone_=cible_.clone_pk();
							cible_.clone_pk()=Taux(0);
							if(f_att_l_->bloc_lan()&&f_att_l_->loi_rep_tour().maximum()==Taux(1)){
								if((!f_capac_l_2_||!f_capac_l_2_->immu_recharg())){
									lanceur_.nec_recharg_pk()=false;
								}
							}
						}else{
							degats_clone_+=degats_tmp_;
						}
					}else{
						degats_2_+=degats_tmp_;
						if(f_att_l_->cat()=="PHYSIQUE"){
							cible_.att_deg_subie().first.first+=degats_tmp_;
						}else if(f_att_l_->cat()=="SPECIALE"){
							cible_.att_deg_subie().first.second+=degats_tmp_;
						}
					}
				}
			}else{
				degats_2_=Taux(0);
				degats_clone_=Taux(0);
				if(att_lanc_=="BASTON"){
					foreach(Combattant c2,creatures_act.cles()){
						CreatureCombat& cr_l_2_=creatures_act.valeur(c2);
						if(c2.equipe()!=lc_.equipe()||cr_l_2_.statut_pk()!="OK"){
							continue;
						}
						if(degats_2_>=cible_.pv_restants_pk()){
							break;
						}
						Taux degats_tmp_=calcul_degats(loi_repet_coup_,att_lanc_,f_att_l_,type_att_,c2,cr_l_2_,cb_,cible_,excuse_,ElementsCombat::ALEA,util_baie_,cc_min_,_d,Taux(1));
						if(f_capac_c_2_&&cc_min_.valeur(lc_)){
							if(!f_capac_l_2_||!f_capac_l_2_->capac_ign().contains(cible_.capacite_pk_act())){
								foreach(QString s,f_capac_c_2_->statis_max_cc()){
									cible_.reinit_boost(s,_d);
									cible_.var_boost(s,_d->constante_numerique("MAX_BOOST"),_d);
								}
							}
						}
						if(f_capac_c_2_){
							foreach(QString s,f_capac_c_2_->mult_statis_to_categ().cles()){
								if(s==f_att_l_->cat()){
									typedef QPair<QString,qint8> StatBoost;
									foreach(StatBoost s2,f_capac_c_2_->mult_statis_to_categ().valeur(s)){
										cible_.var_boost(s2.first,s2.second,_d);
									}
								}
							}
							foreach(QString s,f_capac_c_2_->mult_statis_to_t().cles()){
								if(s==type_att_){
									QPair<QString,qint8> val_=f_capac_c_2_->mult_statis_to_t().valeur(s);
									cible_.var_boost(val_.first,val_.second,_d);
								}
							}
						}
						if(!cible_.clone_pk().estNul()){
							if(cible_.clone_pk()+degats_tmp_>=cible_.clone_pk()){
								degats_clone_=cible_.clone_pk();
								cible_.clone_pk()=Taux(0);
							}else{
								degats_clone_+=degats_tmp_;
							}
						}else{
							degats_2_+=degats_tmp_;
							if(f_att_l_->cat()=="PHYSIQUE"){
								cible_.att_deg_subie().first.first+=degats_tmp_;
							}else if(f_att_l_->cat()=="SPECIALE"){
								cible_.att_deg_subie().first.second+=degats_tmp_;
							}
						}
					}
				}else{
					for(int i=0;i<(int)nombre_coup_repet_min_;i++){
						if(degats_2_>=cible_.pv_restants_pk()){
							break;
						}
						Taux degats_tmp_=calcul_degats(loi_repet_coup_,att_lanc_,f_att_l_,type_att_,lc_,lanceur_,cb_,cible_,excuse_,ElementsCombat::ALEA,util_baie_,cc_min_,_d,Taux(1));
						if(f_capac_c_2_&&cc_min_.valeur(lc_)){
							if(!f_capac_l_2_||!f_capac_l_2_->capac_ign().contains(cible_.capacite_pk_act())){
								foreach(QString s,f_capac_c_2_->statis_max_cc()){
									cible_.reinit_boost(s,_d);
									cible_.var_boost(s,_d->constante_numerique("MAX_BOOST"),_d);
								}
							}
						}
						if(f_capac_c_2_){
							foreach(QString s,f_capac_c_2_->mult_statis_to_categ().cles()){
								if(s==f_att_l_->cat()){
									typedef QPair<QString,qint8> StatBoost;
									foreach(StatBoost s2,f_capac_c_2_->mult_statis_to_categ().valeur(s)){
										cible_.var_boost(s2.first,s2.second,_d);
									}
								}
							}
							foreach(QString s,f_capac_c_2_->mult_statis_to_t().cles()){
								if(s==type_att_){
									QPair<QString,qint8> val_=f_capac_c_2_->mult_statis_to_t().valeur(s);
									cible_.var_boost(val_.first,val_.second,_d);
								}
							}
						}
						if(!cible_.clone_pk().estNul()){
							if(cible_.clone_pk()+degats_tmp_>=cible_.clone_pk()){
								degats_clone_=cible_.clone_pk();
								cible_.clone_pk()=Taux(0);
							}else{
								degats_clone_+=degats_tmp_;
							}
						}else{
							degats_2_+=degats_tmp_;
							if(f_att_l_->cat()=="PHYSIQUE"){
								cible_.att_deg_subie().first.first+=degats_tmp_;
							}else if(f_att_l_->cat()=="SPECIALE"){
								cible_.att_deg_subie().first.second+=degats_tmp_;
							}
						}
					}
				}
			}
			if(att_lanc_=="PRESCIENCE"||att_lanc_=="CARNAREKET"){
				QPair<QPair<Taux,uchar>,QPair<uchar,uchar> >& res_=prescience_carnar.valeur(QPair<QString,QPair<uchar,uchar> >(att_lanc_,positions_places.valeur(lc_)));
				res_.first.first=degats_presc_carnar_;
				res_.first.second=0;
				res_.second=positions_places.valeur(cb_);
				continue;
			}
			/*si lanceur.chargeur_actif et attaque_lanceur.type == CHARGEUR.EFFET_MULT_PUISS_ATT.type
				lanceur.chargeur_actif <- faux
			fin si*/
			Taux degats_recul_(0);
			Taux pv_soignes_(0);
			if(att_lanc_=="TOUR_RAPIDE"){
				_lanceur.attaques_actives_ind("VAMPIGRAINE")=false;
				attaque_equipe(c.equipe(),"PICOTS")=QPair<uchar,bool>(0,false);
				attaque_equipe(c.equipe(),"PICS_TOXIKS")=QPair<uchar,bool>(0,false);
				attaque_equipe(c.equipe(),"PIEGE_DE_ROC")=QPair<uchar,bool>(0,false);
				typedef QPair<Combattant,QString> CombattantAttaquePieg;
				foreach(Combattant c2,creatures_act.cles()){
					if(c2.equipe()==_lc.equipe()){
						continue;
					}
					CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
					foreach(CombattantAttaquePieg c3,cr_c_2_.val_attaques_piegeantes()){
						if(c3.first==_lc){
							cr_c_2_.att_pieg(c3)=QPair<bool,uchar>(false,0);
						}
					}
				}
			}
			QString objet_lance_;
			if(att_lanc_=="DEGOMMAGE"){
				objet_lance_=lanceur_.objet();
				++objets_utilisateur_perdus.valeur(objet_lance_);
				obj_=qobject_cast<ObjetAttachableCombat*>(f_obj_);
				if(!obj_||!obj_->exp_ev()||lc_.equipe()!=ut){
				//CALCUL_EXPERIENCE,MULT_GAIN_EXPERIENCE,GAIN_EV_COMBAT,MULT_GAIN_EV
					lanceur_.val_der_objet_ut()=objet_lance_;
					lanceur_.objet()="";
				}
			}
			bool existe_effet_second_=false;
			for(int i=1;i<f_att_l_->effs().size();i++){
				if(f_att_l_->effs()[i]->qui()){
					existe_effet_second_=true;
					break;
				}
			}//il existe un effet secondaire sur le lanceur
			bool traiter_effet_sec_=false;
			if(degats_2_<cible_.pv_restants_pk()||existe_effet_second_){
				traiter_effet_sec_=true;
			}
			if(traiter_effet_sec_){
				if(f_capac_c_2_&&f_capac_c_2_->mult_pr_eff_sec().cles().contains(false)){
					if(!f_capac_l_2_||!f_capac_l_2_->capac_ign().contains(cible_.capacite_pk_act())){
						traiter_effet_sec_=false;
					}
				}
			}
			if(traiter_effet_sec_){
				if(att_lanc_=="DEGOMMAGE"){
					Baie *baie_lancee_=qobject_cast<Baie*>(_d->val_objets().valeur(objet_lance_));
					if(baie_lancee_&&(!f_capac_l_2_||!f_capac_l_2_->anti_conso_baies_adv())){//et lanceur.capacite != TENSION
						Taux pv_soignes_2_(0);
						cible_.activer_baie(baie_lancee_,_d,pv_soignes_2_);
					}else if(_d->val_effets_ec_degommage().cles().contains(objet_lance_)){
						QString val_=_d->val_effets_ec_degommage().valeur(objet_lance_);
						if(!_d->val_noms_statuts().filter(QRegExp("^"+val_+"\\b")).isEmpty()){
							if(traiter_reussite_seul_effet_statut(cible_,f_capac_c_2_,cb_.equipe(),val_,false,_d)){
								cible_.statut_pk()=val_;
								if(f_capac_c_2_&&f_capac_c_2_->transf_statut().cles().contains(val_)){
									lanceur_.statut_pk()=f_capac_c_2_->transf_statut().valeur(val_);
								}
							}
						}else if(val_=="PEUR"){
							if(ordre_non_joue(_d,true).contains(cb_)||ordre_non_joue(_d,false).contains(cb_)){
								bool passe_=false;
								if(!f_capac_c_2_||!f_capac_c_2_->immu_stat().cles().contains(valeur_climat())){
									passe_=true;
								}else if(!f_capac_c_2_->immu_stat().valeur(valeur_climat()).contains(val_)){
									passe_=true;
								}else if(f_capac_l_2_&&f_capac_l_2_->capac_ign().contains(cible_.capacite_pk_act())){
									passe_=true;
								}
								if(passe_){
									cible_.peur_pk()=true;
									cible_.annuler_patience();
									if(f_capac_c_2_){
										typedef QPair<QString,QPair<QString,qint8> > StatistiqueStatut;
										foreach(StatistiqueStatut s,f_capac_c_2_->mult_statis_statut_cran()){
											if(s.second.first=="PEUR"){
												cible_.var_boost(s.first,s.second.second,_d);
											}
										}
									}
								}
							}
						}else if(val_.startsWith("ANNULE")){
							if(val_.contains("AMOUR")){
								cible_.att_active_cible("AMOUR",lc_)=false;
							}else if(val_.contains("BAISSES_STATISTIQUES")){
								foreach(QString s,cible_.statis_boost()){
									qint8 boost_=cible_.boost(s);
									if(boost_<0){
										cible_.reinit_boost(s,_d);
									}
								}
							}
						}
					}//effet secondaires de DEGOMMAGE
				}else if(att_lanc_=="FORCE_CACHEE"){
					//TODO etre plus generique
					QString statut_a_lancer_;
					QString statistique_;
					bool effet_peur_=false;
					MonteCarlo<QString> loi_1_;
					MonteCarlo<QString> loi_2_;
					MonteCarlo<bool> loi_3_;
					if(type_environnement=="BATIMENT"){
						statut_a_lancer_="PARALYSIE";
					}else if(type_environnement=="ROUTE"||type_environnement=="DESERT"){
						statistique_="PRECISION";
					}else if(type_environnement=="HERBE"){
						statut_a_lancer_="SOMMEIL";
					}else if(type_environnement=="EAU"){
						statistique_="ATTAQUE";
					}else if(type_environnement=="ROCHE"){
						effet_peur_=true;
					}else{//si lieu_actuel_type appartient à [NEIGE]
						statut_a_lancer_="GEL";
					}
					if(!f_capac_c_2_||!f_capac_c_2_->mult_pr_eff_sec().cles().contains(false)){
						if(statut_a_lancer_!=""){
							if(traiter_reussite_seul_effet_statut(cible_,f_capac_c_2_,cb_.equipe(),statut_a_lancer_,false,_d)){
								Taux proba_(3LL,10LL);
								if(f_capac_l_2_&&f_capac_l_2_->mult_pr_eff_sec().cles().contains(true)){
									proba_*=f_capac_l_2_->mult_pr_eff_sec().valeur(true);
								}
								if(proba_>=Taux(1)){
									cible_.statut_pk()=statut_a_lancer_;
									if(f_capac_c_2_&&f_capac_c_2_->transf_statut().cles().contains(statut_a_lancer_)){
										lanceur_.statut_pk()=f_capac_c_2_->transf_statut().valeur(statut_a_lancer_);
									}
								}else{
									Entier proba_1_=proba_.gnumerateur();
									Entier proba_2_=proba_.gdenominateur()-proba_1_;
									loi_1_.ajouter_event(QPair<QString,Entier>(statut_a_lancer_,proba_1_));
									loi_1_.ajouter_event(QPair<QString,Entier>("OK",proba_2_));
									QString tirage_=loi_1_.tirage();
									if(tirage_!="OK"){
										cible_.statut_pk()=tirage_;
										if(f_capac_c_2_&&f_capac_c_2_->transf_statut().cles().contains(tirage_)){
											lanceur_.statut_pk()=f_capac_c_2_->transf_statut().valeur(tirage_);
										}
									}
								}
							}
						}
						if(statistique_!=""){
							if(traiter_reussite_effet_statistique(cible_,f_capac_l_2_,cb_.equipe(),f_capac_c_2_,cible_.capacite_pk_act(),statistique_,-1,true,_d)){
								Taux proba_(3LL,10LL);
								if(f_capac_l_2_&&f_capac_l_2_->mult_pr_eff_sec().cles().contains(true)){
									proba_*=f_capac_l_2_->mult_pr_eff_sec().valeur(true);
								}
								if(proba_>=Taux(1)){
									cible_.var_boost(statistique_,-1,_d);
								}else{
									Entier proba_1_=proba_.gnumerateur();
									Entier proba_2_=proba_.gdenominateur()-proba_1_;
									loi_2_.ajouter_event(QPair<QString,Entier>(statistique_,proba_1_));
									loi_2_.ajouter_event(QPair<QString,Entier>("",proba_2_));
									QString tirage_=loi_2_.tirage();
									if(tirage_!=""){
										cible_.var_boost(statistique_,-1,_d);
									}
								}
							}
						}
						if(effet_peur_){
							if(ordre_non_joue(_d,true).contains(cb_)||ordre_non_joue(_d,false).contains(cb_)){
								bool passe_=false;
								if(!f_capac_c_2_||!f_capac_c_2_->immu_stat().cles().contains(valeur_climat())){
									passe_=true;
								}else if(!f_capac_c_2_->immu_stat().valeur(valeur_climat()).contains("PEUR")){
									passe_=true;
								}else if(f_capac_l_2_&&f_capac_l_2_->capac_ign().contains(cible_.capacite_pk_act())){
									passe_=true;
								}
								if(passe_){
									bool traiter_peur_=false;
									Taux proba_(3LL,10LL);
									if(f_capac_l_2_&&f_capac_l_2_->mult_pr_eff_sec().cles().contains(true)){
										proba_*=f_capac_l_2_->mult_pr_eff_sec().valeur(true);
									}
									if(proba_>=Taux(1)){
										traiter_peur_=true;
									}
									if(!traiter_peur_){
										Entier proba_1_=proba_.gnumerateur();
										Entier proba_2_=proba_.gdenominateur()-proba_1_;
										loi_3_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
										loi_3_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
										traiter_peur_=loi_3_.tirage();
									}
									if(traiter_peur_){
										cible_.peur_pk()=true;
										cible_.annuler_patience();
										if(f_capac_c_2_){
											typedef QPair<QString,QPair<QString,qint8> > StatistiqueStatut;
											foreach(StatistiqueStatut s,f_capac_c_2_->mult_statis_statut_cran()){
												if(s.second.first=="PEUR"){
													cible_.var_boost(s.first,s.second.second,_d);
												}
											}
										}
									}
								}
							}
						}
					}
				}else if(!f_capac_l_2_||!f_capac_l_2_->mult_pr_eff_sec().cles().contains(true)||!f_capac_l_2_->mult_pr_eff_sec().valeur(true).estNul()){
					for(int i=1;i<f_att_l_->effs().size();i++){
						Effet *effet_en_cours_=f_att_l_->effs()[i];
						if(qobject_cast<EffetStatistique*>(effet_en_cours_)){
							if(!effet_en_cours_->qui()){
								if(!f_capac_c_2_||!f_capac_c_2_->mult_pr_eff_sec().cles().contains(false)){
									QStringList liste_=traiter_reussite_effet_statistiques(cible_,f_capac_l_2_,cb_.equipe(),f_capac_c_2_,cible_.capacite_pk_act(),f_att_l_,_d);
									if(!liste_.isEmpty()&&cible_.statut_pk()!="KO"){
										traiter_effet_statist(cible_,lanceur_,lc_.equipe(),qobject_cast<EffetStatistique*>(effet_en_cours_),false,_d);
									}
								}
							}else{
								QStringList liste_=traiter_reussite_effet_statistiques(lanceur_,f_capac_l_2_,lc_.equipe(),f_capac_l_2_,lanceur_.capacite_pk_act(),f_att_l_,_d);
								if(!liste_.isEmpty()){
									traiter_effet_statist(lanceur_,lanceur_,lc_.equipe(),qobject_cast<EffetStatistique*>(effet_en_cours_),false,_d);
								}
							}
						}else if(qobject_cast<EffetStatut*>(effet_en_cours_)){
							EffetStatut *effet_statut_=qobject_cast<EffetStatut*>(effet_en_cours_);
							bool existe_=false;
							QStringList statuts_=effet_statut_->statuts_possibles_non_ok();
							foreach(QString s,statuts_){
								bool pseudo_statut_=_d->val_noms_statuts().filter(QRegExp("^"+s+"\\b")).isEmpty();
								existe_|=traiter_reussite_seul_effet_statut(lanceur_,f_capac_l_2_,cible_,cible_.capacite_pk_act(),f_capac_c_2_,cb_.equipe(),att_lanc_,s,effet_statut_->qui(),statuts_,pseudo_statut_,_d);
							}
							if(existe_){
								MonteCarlo<QString> loi_;
								if(f_capac_l_2_&&f_capac_l_2_->mult_pr_eff_sec().cles().contains(true)){
									loi_=effet_statut_->tirage_statut(f_capac_l_2_->mult_pr_eff_sec().valeur(true),attaque_equipe(lc_.equipe(),"AIRE_EAU_FEU").second,false);
								}else{
									loi_=effet_statut_->tirage_statut(1,attaque_equipe(lc_.equipe(),"AIRE_EAU_FEU").second,false);
									//TODO a inserer cas effet d'attaque
								}
								if(!f_capac_c_2_||!f_capac_c_2_->mult_pr_eff_sec().cles().contains(false)||effet_statut_->qui()){
									traiter_effet_statut(cb_,cible_,cb_.equipe(),lanceur_,lc_.equipe(),loi_,att_lanc_,false,_d);
								}
							}
						}else if(qobject_cast<EffetTauxPVRestants*>(effet_en_cours_)){
							if(effet_en_cours_->qui()&&qobject_cast<EffetTauxPVRestants*>(effet_en_cours_)->tx()==Taux(1)){
								mise_a_ko(lc_,lanceur_,_d);
							}
						}else if(qobject_cast<EffetTauxDegats*>(effet_en_cours_)){
							Taux tx_=qobject_cast<EffetTauxDegats*>(effet_en_cours_)->tx();
							if((!f_capac_l_2_||!f_capac_l_2_->immu_deg_recul())&&tx_<Taux(0)){
								degats_recul_-=degats_2_*tx_;//Utilitaire::max_min<Taux>(degats_2_,cible_.pv_restants_pk()).second*tx_
							}
							if(tx_>Taux(0)){
								if(!attaque_equipe(adversaire(lc_.equipe()),"ANTI_SOIN").second){
									if(!f_capac_c_2_||f_capac_c_2_->mult_tx_deg_adv_abs()==0){
										if(degats_clone_.estNul()){
											Taux val_degats_=degats_2_;//Utilitaire::max_min<Taux>(degats_2_,cible_.pv_restants_pk()).second
											if(lanceur_.peut_utiliser_objet(zone_magique_)){
												obj_=qobject_cast<ObjetAttachableCombat*>(f_obj_);
												if(obj_&&!obj_->mult_pv_drai().estNul()){
													pv_soignes_+=val_degats_*tx_*obj_->mult_pv_drai();
												}else{
													pv_soignes_+=val_degats_*tx_;
												}
												//Les attaques qui absorbent des PV en absorbent lorsqu'utilisées sur un Clone.
											}
										}else{
											if(lanceur_.peut_utiliser_objet(zone_magique_)){
												obj_=qobject_cast<ObjetAttachableCombat*>(f_obj_);
												if(obj_&&!obj_->mult_pv_drai().estNul()){
													pv_soignes_+=degats_clone_*tx_*obj_->mult_pv_drai();
												}else{
													pv_soignes_+=degats_clone_*tx_;
												}
											}
										}
									}else{
										if(degats_clone_.estNul()){
											degats_recul_+=degats_2_*tx_;//Utilitaire::max_min<Taux>(degats_2_,cible_.pv_restants_pk()).second*tx_
										}else{
											degats_recul_+=degats_clone_*tx_;
										}
									}
								}
							}
						}
					}
				}
			}
			if(lanceur_.peut_utiliser_objet(zone_magique_)&&cb_.equipe()!=lc_.equipe()){
				obj_=qobject_cast<ObjetAttachableCombat*>(f_obj_);
				if(obj_&&obj_->dr_tx_deg()>Taux(0)){
					Taux pv_=Utilitaire::max_min<Taux>(cible_.pv_restants_pk(),cible_.pv_max()*obj_->dr_tx_deg()).second;
					if(cible_.patience_pk().second.second){
						cible_.patience_pk().second.first+=pv_;
					}
					if(!attaque_equipe(adversaire(lc_.equipe()),"ANTI_SOIN").second){
						if(!f_capac_c_2_||f_capac_c_2_->mult_tx_deg_adv_abs()==0){
							degats_recul_+=pv_;
						}else{
							pv_soignes_+=pv_;
						}
					}
				}
			}
			traiter_apres_degats(att_lanc_,cb_,cible_,lc_,lanceur_,degats_,degats_2_,degats_clone_,pv_soignes_,degats_recul_,type_att_,_d);
			/*if(cible_.objet()!=""&&qobject_cast<Baie*>(cible_.fiche_objet(_d))&&att_lanc_=="CALCINATION"){
				cible_.val_der_objet_ut()=cible_.objet()
				cible_.objet()=""
				cible_.perte_objet()=true
			}
			if(att_lanc_=="REBONDIFEU"){
				if(diff.r_adjacence_active()){
					foreach(Combattant c2,creatures_act.cles()){
						if(c2==cb_||c2.equipe()==lc_.equipe()||positions_places.valeur(c2).second==arriere){
							continue
						}
						if((Taux(c2.position())-Taux(cb_.position())).absolu()>Taux(1)){
							continue
						}
						CreatureCombat& cr_c_2_=creatures_act.valeur(c2)
						if(cr_c_2_.pv_restants_pk()*Taux(8)<cr_c_2_.pv_max()){
							cr_c_2_.pv_restants_pk()=Taux(0)
							mise_a_ko(c2,cr_c_2_,_d)
						}else{
							cr_c_2_.pv_restants_pk()-=cr_c_2_.pv_max()*Taux(1LL,8LL)
						}
					}
				}else{
					foreach(Combattant c2,creatures_act.cles()){
						if(c2==cb_||c2.equipe()==lc_.equipe()||positions_places.valeur(c2).second==arriere){
							continue
						}
						CreatureCombat& cr_c_2_=creatures_act.valeur(c2)
						if(cr_c_2_.pv_restants_pk()*Taux(8)<cr_c_2_.pv_max()){
							cr_c_2_.pv_restants_pk()=Taux(0)
							mise_a_ko(c2,cr_c_2_,_d)
						}else{
							cr_c_2_.pv_restants_pk()-=cr_c_2_.pv_max()*Taux(1LL,8LL)
						}
					}
				}
			}
			if(att_lanc_=="ANTI_AIR"){
				if(!cible_.disparition_pk()||(cible_.att_choisie()!="VOL"&&cible_.att_choisie()!="REBOND"&&cible_.att_choisie()!="CHUTE_LIBRE")){
					cible_.attaques_actives_ind(att_lanc_)=true
					cible_.immu_att_type("SOL")=false
					cible_.attaques_actives_def("LEVIKINSIE")=QPair<uchar,bool>(0,false)
					cible_.attaques_actives_def("VOL_MAGNETIK")=QPair<uchar,bool>(0,false)
				}else{
					cible_.disparition_pk()=false
					cible_.prepa_tour_pk()=false
				}
			}
			if(cible_.clone_pk().estNul()){
				if(degats_2_>Taux(0)){
					if(degats_<cible_.pv_restants_pk()){
						if(degats_2_>=cible_.pv_restants_pk()){
							bool traiter_ko_cible_=false
							if(!f_att_l_->pas_ko()){
								traiter_ko_cible_=true
							}
							if(traiter_ko_cible_){
								if(cible_.att_choisie()=="TENACITE"&&cible_.att_reussie()){
									traiter_ko_cible_=false
								}
							}
							if(traiter_ko_cible_){
								if(cible_.peut_utiliser_objet(zone_magique_)){
									obj_=qobject_cast<ObjetAttachableCombat*>(f_obj_)
									if(obj_&&!obj_->a_ko().estNul()){
										traiter_ko_cible_=false
									}
									if(traiter_ko_cible_){
										if(obj_&&!obj_->a_ko_pv().estNul()&&cible_.pv_restants_pk()==cible_.pv_max()){
											traiter_ko_cible_=false
										}
									}
								}
							}
							if(traiter_ko_cible_){
								mise_a_ko(cb_,cible_,_d)
							}else{
								if(f_att_l_->cat()=="PHYSIQUE"){
									cible_.att_deg_subie().first.first+=cible_.pv_restants_pk()-Taux(1)
								}else if(f_att_l_->cat()=="SPECIALE"){
									cible_.att_deg_subie().first.second+=cible_.pv_restants_pk()-Taux(1)
								}
								cible_.pv_restants_pk()=Taux(1)
								if(f_capac_c_2_&&f_capac_c_2_->chgt_type_deg()){
									cible_.types_pk().clear()
									cible_.types_pk()<<type_att_
								}
							}
						}else{
							cible_.pv_restants_pk()-=degats_2_
							if(f_att_l_->cat()=="PHYSIQUE"){
								cible_.att_deg_subie().first.first+=degats_2_
							}else if(f_att_l_->cat()=="SPECIALE"){
								cible_.att_deg_subie().first.second+=degats_2_
							}
							if(f_capac_c_2_&&f_capac_c_2_->chgt_type_deg()){
								cible_.types_pk().clear()
								cible_.types_pk()<<type_att_
							}
						}
					}
				}
			}else{
				cible_.clone_pk()-=degats_clone_
			}
			if(att_lanc_=="RELACHE"){
				lanceur_.nb_lancer("STOCKAGE")=0
			}
			if(cible_.pv_restants_pk()>Taux(0)){
				if(cible_.patience_pk().second.second){
					cible_.patience_pk().second.first+=degats_2_
				}
				if(cible_.peut_utiliser_objet(zone_magique_)&&(!f_capac_l_2_||!f_capac_l_2_->anti_conso_baies_adv())){
					Baie *baie_cons_=qobject_cast<Baie*>(cible_.fiche_objet(_d))
					Taux pv_soignes_baie_(0)
					Taux taux_
					if(f_capac_c_2_&&f_capac_c_2_->ut_baie_soin_pv()>Taux(0)){
						taux_=f_capac_c_2_->ut_baie_soin_pv()
					}else{
						taux_=Taux(1)
					}
					if(baie_cons_&&baie_cons_->s_pv().second/taux_*cible_.pv_max()>=cible_.pv_restants_pk()){
						cible_.activer_baie(baie_cons_,_d,pv_soignes_baie_)
					}
				}
				if(f_capac_l_2_&&f_att_l_->dir()){
					//MonteCarlo<QString> event_=f_capac_l_2_->statut_l().events()[0]
					MonteCarlo<QString> event_=f_capac_l_2_->statut_sim()
					QList<QString> events_=event_.events()
					if(events_.size()==2&&events_.contains("PEUR")){
					//lanceur.capacite == PUANTEUR
						bool passe_=false
						if(!f_capac_c_2_||!f_capac_c_2_->immu_stat().cles().contains(valeur_climat())){
							passe_=true
						}else if(!f_capac_c_2_->immu_stat().valeur(valeur_climat()).contains("PEUR")&&!f_capac_c_2_->mult_pr_eff_sec().cles().contains(false)){
							passe_=true
						}else if(f_capac_l_2_&&f_capac_l_2_->capac_ign().contains(cible_.capacite_pk_act())){
							passe_=true
						}
						if(passe_){
							// ((cible.capacite != IMMU[PEUR] et cible.capacite != ECRAN_POUDRE) ou lanceur.capacite ignore cible.capacite)
							if(cible_.clone_pk().estNul()&&!cible_.peur_pk()){
								//cible.clone == 0 et non cible.peur
								if(ordre_non_joue(_d,true).contains(cb_)||ordre_non_joue(_d,false).contains(cb_)){
									//cible appartient a ordre_non_joue(creat_comb.cles(),vrai).union(ordre_non_joue(creat_comb.cles(),faux))
									Taux proba_(event_.proba_event("PEUR"),event_.somme())
									if(f_capac_l_2_&&f_capac_l_2_->mult_pr_eff_sec().cles().contains(true)){
										proba_*=f_capac_l_2_->mult_pr_eff_sec().valeur(true)
									}
									if(proba_>Taux(1)){
										cible_.peur_pk()=true
									}else{
										MonteCarlo<bool> loi_
										Entier proba_1_=proba_.gnumerateur()
										Entier proba_2_=proba_.gdenominateur()-proba_1_
										loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_))
										loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_))
										cible_.peur_pk()=loi_.tirage()
									}
									if(cible_.peur_pk()){
										cible_.annuler_patience()
										if(f_capac_c_2_){
											typedef QPair<QString,QPair<QString,qint8> > StatistiqueStatut
											foreach(StatistiqueStatut s,f_capac_c_2_->mult_statis_statut_cran()){
												if(s.second.first=="PEUR"){
													cible_.var_boost(s.first,s.second.second,_d)
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			if(att_lanc_=="PICORE"||att_lanc_=="PIQURE"){
				Baie *baie_ut_=qobject_cast<Baie*>(cible_.fiche_objet(_d))
				if(baie_ut_&&(!f_capac_c_2_||!f_capac_c_2_->anti_conso_baies_adv())&&!zone_magique_){
					if(!lanceur_.attaques_actives_def("EMBARGO").second){
						bool util_=_lanceur.utilisation_baie()
						Taux pv_soignes_baie_(0)
						lanceur_.activer_baie(baie_ut_,_d,pv_soignes_baie_)
						lanceur_.utilisation_baie()=util_
					}
				}
				cible_.utilisation_baie()=true
				cible_.perte_objet()=true
			}
			bool traiter_prise_obj_=false
			if(att_lanc_=="IMPLORE"||att_lanc_=="LARCIN"||att_lanc_=="SABOTAGE"){
				if(cible_.clone_pk().estNul()&&(!f_capac_c_2_||!f_capac_c_2_->immu_att().contains(att_lanc_))){
					QString objet_pris_=cible_.objet()
					if(objet_pris_!=""){
						++objets_utilisateur_perdus.valeur(objet_pris_)
					}
					if(att_lanc_!="IMPLORE"||lanceur_.objet()==""){
						traiter_prise_obj_=true
					}
				}
			}
			if(traiter_prise_obj_){	
				ObjetAttachableCombat *obj_cible_=NULL
				if(cible_.objet()!=""){
					obj_cible_=qobject_cast<ObjetAttachableCombat*>(cible_.fiche_objet(_d))
				}
				QString objet_pris_=cible_.objet()
				cible_.val_der_objet_ut()=objet_pris_
				if(att_lanc_=="IMPLORE"){
					lanceur_.objet()=objet_pris_
				}
				cible_.objet()=""
				if(lanceur_.objet()=="BALLE_FER"){
					lanceur_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false)
				}
				if(!obj_cible_||!obj_cible_->exp_ev()||lc_.equipe()!=ut){
				//CALCUL_EXPERIENCE,MULT_GAIN_EXPERIENCE,GAIN_EV_COMBAT,MULT_GAIN_EV
					cible_.val_der_objet_ut()=cible_.objet()
					cible_.objet()=""
				}
				cible_.perte_objet()=true
			}
			if(cible_.clone_pk().estNul()){
				typedef QPair<Combattant,QString> CombattantAttaquePieg
				foreach(CombattantAttaquePieg a,lanceur_.val_attaques_piegeantes()){
					if(a.first==cb_&&a.second==att_lanc_){
						lanceur_.att_pieg(a)=QPair<bool,uchar>(0,true)
					}
				}
			}
			if(att_lanc_=="BROUHAHA"){
				lanceur_.attaques_actives_def(att_lanc_)=QPair<uchar,bool>(0,true)
				foreach(Combattant c2,creatures_act.cles()){
					CreatureCombat& cr_c_2_=creatures_act.valeur(c2)
					if(cr_c_2_.statut_pk()=="SOMMEIL"){
						FicheCapacite *f_capac_c_3_=cr_c_2_.fiche_capacite(_d)
						if(!f_capac_c_3_||!f_capac_c_3_->immu_att().contains(att_lanc_)){
							cr_c_2_.statut_pk()="OK"
							cr_c_2_.attaques_actives_def("REPOS")=QPair<uchar,bool>(false,0)
							cr_c_2_.sommeil_non_repos()=0
						}
					}
				}
			}
			if(cible_.statut_pk()=="KO"){
				if(cible_.attaques_actives_ind("RANCUNE")){
					lanceur_.supprimer_pp(att_lanc_)
				}
				if(cible_.attaques_actives_ind("PRLV_DESTIN")&&cb_.equipe()!=lc_.equipe()){
					mise_a_ko(lc_,lanceur_,_d)
				}
			}else if(att_lanc_=="REVEIL_FORCE"&&cible_.statut_pk()=="SOMMEIL"&&cible_.clone_pk().estNul()){
				cible_.statut_pk()="OK"
				cible_.attaques_actives_def("REPOS")=QPair<uchar,bool>(false,0)
				cible_.sommeil_non_repos()=0
			}else if(att_lanc_=="STIMULANT"&&cible_.statut_pk()=="PARALYSIE"&&cible_.clone_pk().estNul()){
				cible_.statut_pk()="OK"
			}
			if(lanceur_.statut_pk()!="KO"){
				Taux pv_soignes_totaux_(0)
				lanceur_.soin_pv(pv_soignes_,pv_soignes_totaux_,_d)
				if(degats_recul_>=lanceur_.pv_restants_pk()){
					mise_a_ko(lc_,lanceur_,_d)
				}else{
					lanceur_.pv_restants_pk()-=degats_recul_
				}
				if(f_capac_c_2_&&!f_capac_c_2_->deg_recul_adv().estNul()&&cible_.statut_pk()!="KO"&&f_att_l_->dir()){
					lanceur_.pv_restants_pk()=Utilitaire::max_min<Taux>(lanceur_.pv_restants_pk()-lanceur_.pv_max()*f_capac_c_2_->deg_recul_adv(),Taux(0)).first
					if(lanceur_.pv_restants_pk().estNul()){
						mise_a_ko(lc_,lanceur_,_d)
					}
				}
				ObjetAttachableCombat *obj_cible_=NULL
				if(cible_.objet()!=""){
					obj_cible_=qobject_cast<ObjetAttachableCombat*>(cible_.fiche_objet(_d))
				}
				if(obj_cible_&&!obj_cible_->recul().estNul()&&cible_.statut_pk()!="KO"&&f_att_l_->dir()){
					lanceur_.pv_restants_pk()=Utilitaire::max_min<Taux>(lanceur_.pv_restants_pk()-lanceur_.pv_max()*f_capac_c_2_->deg_recul_adv(),Taux(0)).first
					if(lanceur_.pv_restants_pk().estNul()){
						mise_a_ko(lc_,lanceur_,_d)
					}
				}
				if(lanceur_.statut_pk()!="KO"){
					if(f_capac_c_2_&&f_att_l_->dir()){
					//cible.capacite.categorie == attaque_lanceur.categorie
						MonteCarlo<QString> event_=f_capac_c_2_->statut_sim()
						QStringList statuts_=event_.events()
						//TODO calculer la nouvelle loi de proba avec des prob d'effets mult.
						QStringList statuts_poss_
						foreach(QString s,statuts_){
							if(s=="AMOUR"){
								if(!protege_contre_amour(lanceur_,cible_,lanceur_.capacite_pk_act(),f_capac_l_2_,f_capac_c_2_)){
									//IMMU_AMOUR 
									if(!lanceur_.peut_utiliser_objet(zone_magique_)){
										statuts_poss_<<s
									}else{
										ObjetAttachableCombat *obj_lanceur_=qobject_cast<ObjetAttachableCombat*>(lanceur_.fiche_objet(_d))
										if(!obj_lanceur_||!obj_lanceur_->immu_am()){
											statuts_poss_<<s
										}
									}
								}
							}else if(s!="PEUR"){
								bool pseudo_statut_=_d->val_noms_statuts().filter(QRegExp("^"+s+"\\b")).isEmpty()
								if(traiter_reussite_seul_effet_statut(cible_,f_capac_c_2_,lanceur_,lanceur_.capacite_pk_act(),f_capac_l_2_,lc_.equipe(),att_lanc_,s,true,statuts_,pseudo_statut_,_d)){
									statuts_poss_<<s
								}
							}
						}
						statuts_poss_.removeOne("OK")
						if(!statuts_poss_.isEmpty()){
							bool existe_statut_=false
							foreach(QString s,statuts_poss_){
								if(event_.events().contains(s)){
									existe_statut_=true
								}
							}
							if(existe_statut_){
								QString statut_=event_.tirage()
								bool pseudo_statut_=_d->val_noms_statuts().filter(QRegExp("^"+statut_+"\\b")).isEmpty()
								if(statut_=="AMOUR"){
									if(!protege_contre_amour(lanceur_,cible_,lanceur_.capacite_pk_act(),f_capac_l_2_,f_capac_c_2_)){
										//IMMU_AMOUR
										bool tombe_amoueux_=false
										if(!lanceur_.peut_utiliser_objet(zone_magique_)){
											tombe_amoueux_=true
										}else{
											ObjetAttachableCombat *obj_lanceur_=qobject_cast<ObjetAttachableCombat*>(lanceur_.fiche_objet(_d))
											if(!obj_lanceur_||!obj_lanceur_->immu_am()){
												tombe_amoueux_=true
											}
										}
										if(tombe_amoueux_){
											lanceur_.att_active_cible("AMOUR",cb_)=true
											if(lanceur_.peut_utiliser_objet(zone_magique_)){
												ObjetAttachableCombat *obj_lanceur_=qobject_cast<ObjetAttachableCombat*>(lanceur_.fiche_objet(_d))
												if(obj_lanceur_&&obj_lanceur_->sync_am()){
													cible_.att_active_cible("AMOUR",lc_)=true
												}
											}
										}
									}									
								}else if(traiter_reussite_seul_effet_statut(cible_,f_capac_c_2_,lanceur_,lanceur_.capacite_pk_act(),f_capac_l_2_,lc_.equipe(),att_lanc_,statut_,true,statuts_,pseudo_statut_,_d)){
									if(statut_!="PEUR"){
										traiter_effet_statut(lc_,lanceur_,lc_.equipe(),cible_,cb_.equipe(),event_,att_lanc_,false,_d)
									}
								}
							}
						}
					}else if(cible_.statut_pk()=="KO"&&f_att_l_->dir()&&f_capac_c_2_&&!f_capac_c_2_->deg_recul_adv_ko().estNul()){
						//sinon si cible.capacite == BOOM_FINAL et cible.statut == KO et attaque_lanceur.directe//et attaque_lanceur.categorie == physique
						Taux degats_boom_=lanceur_.pv_max()*f_capac_c_2_->deg_recul_adv_ko()
						if(degats_boom_>lanceur_.pv_restants_pk()){
							mise_a_ko(lc_,lanceur_,_d)
						}else{
							lanceur_.pv_restants_pk()-=degats_boom_
							if(f_att_l_->cat()=="PHYSIQUE"){
								lanceur_.att_deg_subie().first.first+=degats_boom_
							}else if(f_att_l_->cat()=="SPECIALE"){
								lanceur_.att_deg_subie().first.second+=degats_boom_
							}
						}
					}
				}
			}//mom()
			if(cible_.statut_pk()!="KO"){
				if(f_capac_c_2_&&f_capac_c_2_->mom()&&f_att_l_->dir()&&(!f_capac_l_2_||!f_capac_l_2_->plaq())){
					//et attaque_lanceur.categorie == PHYSIQUE
					lanceur_.capacite_pk_act()=cible_.capacite_pk_act()
				}
			}
			if(cible_.statut_pk()=="KO"){
				if(f_capac_l_2_){
					foreach(QString s,f_capac_l_2_->mult_statis_adv_ko().cles()){
						lanceur_.var_boost(s,f_capac_l_2_->mult_statis_adv_ko().valeur(s),_d)
					}
				}
			}*/
		}else if(qobject_cast<EffetTauxPVRestants*>(effet_prim_)){
			Taux tx_=qobject_cast<EffetTauxPVRestants*>(effet_prim_)->tx();
			if(tx_==Taux(1)){
				if(cible_.statut_pk()=="KO"){
					if(cible_.attaques_actives_ind("RANCUNE")){
						lanceur_.supprimer_pp(att_lanc_);
					}
					if(cible_.attaques_actives_ind("PRLVT_DESTIN")&&cb_.equipe()!=lc_.equipe()){
						mise_a_ko(lc_,lanceur_,_d);
					}
				}
				mise_a_ko(cb_,cible_,_d);
			}else{
				degats_2_=cible_.pv_restants_pk()*tx_;
				cible_.pv_restants_pk()-=degats_2_;
				if(f_att_l_->cat()=="PHYSIQUE"){
					cible_.att_deg_subie().first.first+=degats_2_;
				}else if(f_att_l_->cat()=="SPECIALE"){
					cible_.att_deg_subie().first.second+=degats_2_;
				}
			}
		}else if(qobject_cast<EffetTauxPVPVMax*>(effet_prim_)){//EffetTauxPVPVMax
			foreach(Effet *e,f_att_l_->effs()){
				Taux tx_=qobject_cast<EffetTauxPVPVMax*>(e)->tx();
				QString cl_=qobject_cast<EffetTauxPVPVMax*>(e)->cl();
				if(cl_==valeur_climat()){
					Taux pv_soignes_cl_(0);
					lanceur_.soin_pv(lanceur_.pv_max()*tx_,pv_soignes_cl_,_d);
				}
			}
		}else{
			//sinon si effet_primaire est EFFET_SPECIFIQUE
			if(att_lanc_=="SAISIE"){
				lanceur_saisie.valeur(cb_)=lc_;
				//lanceur_de_saisie[cible] <- lanceur
			}else if(att_lanc_=="ACUPRESSION"){
				if(lc_==lanceur_saisie.valeur(cb_)){
					QString nom_statistique_=lanceur_.tirage_acupression(_d);
					if(nom_statistique_!=""){
						Taux mult_(2);
						if(f_capac_l_2_){
							mult_*=f_capac_l_2_->taux_act(false);
						}
						lanceur_.var_boost(nom_statistique_,(int)mult_,_d);
					}
				}else{
					QString nom_statistique_=cible_.tirage_acupression(_d);
					if(nom_statistique_!=""){
						Taux mult_(2);
						if(f_capac_c_2_){
							mult_*=f_capac_c_2_->taux_act(false);
						}
						cible_.var_boost(nom_statistique_,(int)mult_,_d);
					}
				}
			}else if(att_lanc_=="AIR_VEINARD"){
				attaque_equipe(lc_.equipe(),att_lanc_)=QPair<uchar,bool>(0,true);
			}else if(att_lanc_=="ATTERRISSAGE"){
				lanceur_.atterrissage().second=lanceur_.types_pk().contains("VOL");
				if(lanceur_.atterrissage().second){
					lanceur_.types_pk().removeOne("VOL");
				}
				lanceur_.atterrissage().first=true;
				if(lanceur_.types_pk().isEmpty()){
					lanceur_.types_pk()<<"NORMAL";
					lanceur_.pur_vol_atterr()=true;
				}
				Taux pv_soignes_att_(0);
				lanceur_.soin_pv(lanceur_.pv_max()*Taux(1LL,2LL),pv_soignes_att_,_d);
			}else if(att_lanc_=="PROVOC"){
				cible_.attaques_actives_def(att_lanc_)=QPair<uchar,bool>(0,true);
			}else if(att_lanc_=="ENCORE"){
				QPair<QString,QPair<bool,uchar> >& encore_=lanceur_.cible_atts(QPair<QString,Combattant>(att_lanc_,cb_));
				encore_.first=cible_.der_att_lancee();
				encore_.second=QPair<bool,uchar>(true,0);
			}else if(att_lanc_=="ANTI_BRUME"){
				if(!attaque_equipe(cb_.equipe(),"RUNE_PROTECT").second){
					Taux mult_(2);
					if(f_capac_c_2_){
						mult_*=f_capac_c_2_->taux_act(true);
					}
					cible_.var_boost("ESQUIVE",(int)-mult_,_d);
				}
				attaque_equipe(cb_.equipe(),"MUR_LUMIERE")=QPair<uchar,bool>(0,false);
				attaque_equipe(cb_.equipe(),"PROTECTION")=QPair<uchar,bool>(0,false);
				attaque_equipe(cb_.equipe(),"RUNE_PROTECT")=QPair<uchar,bool>(0,false);
				attaque_equipe(cb_.equipe(),"BRUME")=QPair<uchar,bool>(0,false);
				attaque_equipe(cb_.equipe(),"PICOTS")=QPair<uchar,bool>(0,false);
				attaque_equipe(cb_.equipe(),"PIEGE_DE_ROC")=QPair<uchar,bool>(0,false);
				attaque_equipe(cb_.equipe(),"PICS_TOXIKS")=QPair<uchar,bool>(0,false);
			}else if(att_lanc_=="ANTI_SOIN"){
				attaque_equipe(lc_.equipe(),att_lanc_)=QPair<uchar,bool>(0,false);
			}else if(att_lanc_=="DETREMPAGE"){
				cible_.types_pk().clear();
				cible_.types_pk()<<"EAU";
				cible_.attaques_actives_ind(att_lanc_)=true;
			}else if(att_lanc_=="RAYON_SIMPLE"){
				cible_.desactiver_capacite(true,positions_places,arriere,_d,climat);
				cible_.capacite_pk_act()="SIMPLE";
				Taux pv_soignes_baie_(0);
				cible_.activer_capacite(true,_d,positions_places,zone_magique_,arriere,climat,pv_soignes_baie_);
			}else if(att_lanc_=="TEN_DANSE"){
				cible_.desactiver_capacite(true,positions_places,arriere,_d,climat);
				cible_.capacite_pk_act()=lanceur_.capacite_pk_act();
				if(cible_.capacite_pk_act()=="LEVITATION"){
					//TODO etre plus generique
					cible_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
				}
				Taux pv_soignes_baie_(0);
				cible_.activer_capacite(true,_d,positions_places,zone_magique_,arriere,climat,pv_soignes_baie_);
			}else if(att_lanc_=="SOUCIGRAINE"){
				cible_.desactiver_capacite(true,positions_places,arriere,_d,climat);
				cible_.capacite_pk_act()="INSOMNIA";
				Taux pv_soignes_baie_(0);
				cible_.activer_capacite(true,_d,positions_places,zone_magique_,arriere,climat,pv_soignes_baie_);
			}else if(att_lanc_=="ABRI"||att_lanc_=="DETECTION"||att_lanc_=="TENACITE"||att_lanc_=="GARDE_LARGE"||att_lanc_=="PREVENTION"){
				lanceur_.gain_nb_succes_abris();
				//calcul de la nouvelle precision de ABRI, DETECTION, TENACITE
			}else if(att_lanc_=="ADAPTATION"){
				//Puissance Cachée et Ball'Meteo => type normal ici
				//types_adaptation(lanceur.types,lanceur.attaques_act.types)
				/*types_t <- vide
				pour chaque attaque de lanceur.attaques_act
					si non types_t.contient(attaque.type)
						types_t.ajouter(attaque.type)
					fin si
				fin pour*/
				QString type_=lanceur_.tirage_adaptation(lanceur_.types_adaptation(_d));
				//type <- tirage_adaptation(lanceur.types,types_t)
				if(type_=="VOL"){
					lanceur_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
				}
				lanceur_.types_pk().clear();
				lanceur_.types_pk()<<type_;
			}else if(att_lanc_=="CONVERSION_2"){
				QString type_=lanceur_.tirage_conversion_2(lanceur_.att_deg_subie().second,_d);
				//tirage_conversion_2
				//type <- tirage_conversion_2(lanceur.types_act,lanceur.derniere_attaque_subie)
				if(type_=="VOL"){
					lanceur_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
				}
				lanceur_.types_pk().clear();
				lanceur_.types_pk()<<type_;
			}else if(att_lanc_=="ANNEAU_HYDRO"){
				lanceur_.attaques_actives_ind(att_lanc_)=true;
			}else if(att_lanc_=="RACINES"){
				lanceur_.attaques_actives_ind(att_lanc_)=true;
				/*si lanceur.puissance_attaque_subie[SOL] == 0
					lanceur.puissance_attaque_subie[SOL] <- 1
				fin si*/
			}else if(att_lanc_=="ASTUCE_FORCE"){
				lanceur_.attaques_actives_ind(att_lanc_)=!lanceur_.attaques_actives_ind(att_lanc_);
				lanceur_.echanger_statistiques("ATTAQUE","DEFENSE");
				//lanceur.astuce_force_actif_apres_zone_etrange <- zone_etrange.actif
			}else if(att_lanc_=="ATTRACTION"){
				bool tombe_amoueux_=false;
				if(!lanceur_.peut_utiliser_objet(zone_magique_)){
					tombe_amoueux_=true;
				}else{
					ObjetAttachableCombat *obj_lanceur_=qobject_cast<ObjetAttachableCombat*>(lanceur_.fiche_objet(_d));
					if(!obj_lanceur_||!obj_lanceur_->immu_am()){
						tombe_amoueux_=true;
					}
				}
				if(tombe_amoueux_){
					cible_.att_active_cible("AMOUR",lc_)=true;
					if(lanceur_.peut_utiliser_objet(zone_magique_)){
						ObjetAttachableCombat *obj_lanceur_=qobject_cast<ObjetAttachableCombat*>(lanceur_.fiche_objet(_d));
						if(obj_lanceur_&&obj_lanceur_->sync_am()){
							lanceur_.att_active_cible("AMOUR",cb_)=true;
						}
					}
				}
				/*si cible.objet est IMMU_AMOUR et non cible.embargo_subi.actif et non zone_magique.actif
					cible.dernier_objet <- cible.objet
					cible.objet <- ""
					cible.vient_de_perdre_objet <- vrai
				fin si*/
			}else if(att_lanc_=="AVALE"){
				Taux tx_=lanceur_.calcul_avale();
				Taux pv_soignes_avale_(0);
				lanceur_.soin_pv(tx_*lanceur_.pv_max(),pv_soignes_avale_,_d);
				lanceur_.nb_lancer("STOCKAGE")=0;
			}else if(att_lanc_=="BALANCE"){
				Taux moy_=(lanceur_.pv_restants_pk()+cible_.pv_restants_pk())*Taux(1LL,2LL);
				lanceur_.pv_restants_pk()=Utilitaire::max_min<Taux>(lanceur_.pv_max(),moy_).second;
				cible_.pv_restants_pk()=Utilitaire::max_min<Taux>(cible_.pv_max(),moy_).second;
			}else if(att_lanc_=="BARRAGE"||att_lanc_=="REGARD_NOIR"||att_lanc_=="TOILE"){
				lanceur_.att_active_cible("ANTI_FUITE",cb_)=true;
			}else if(att_lanc_=="BOOST"){
				foreach(QString s,lanceur_.statis_boost()){
					lanceur_.reinit_boost(s,_d);
					lanceur_.var_boost(s,cible_.boost(s),_d);
				}
			}else if(att_lanc_=="BUEE_NOIRE"){
				foreach(Combattant c2,creatures_act.cles()){
					CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
					foreach(QString s,cr_c_2_.statis_boost()){
						cr_c_2_.reinit_boost(s,_d);
					}
				}
			}else if(att_lanc_=="CAMOUFLAGE"){
				lanceur_.types_pk().clear();
				lanceur_.types_pk()<<_d->val_camouflage().valeur(type_environnement);
			}else if(att_lanc_=="CAUCHEMAR"){
				lanceur_.att_active_cible(att_lanc_,cb_)=true;
			}else if(att_lanc_=="CLONAGE"){
				Taux pv_clone_=lanceur_.pv_max()*Taux(1LL,4LL);
				lanceur_.pv_restants_pk()-=pv_clone_;
				lanceur_.clone_pk()=pv_clone_;
			//}else if(att_lanc_=="TENACITE"){
				//lanceur.peut_etre_ko_par_attaque_adv <- faux
			}else if(att_lanc_=="COPIE"){
				lanceur_.att_copie()=QPair<QString,uchar>(cible_.der_att_lancee(),5);
			}else if(att_lanc_=="DEPIT"){
				if(cible_.nb_pp(cible_.der_att_lancee())<4){
					cible_.supprimer_pp(cible_.der_att_lancee());
				}else{
					cible_.utiliser_pp(cible_.der_att_lancee(),4);
				}
			}else if(att_lanc_=="ENTRAVE"){
				QPair<QString,QPair<bool,uchar> >& entrave_=lanceur_.cible_atts(QPair<QString,Combattant>(att_lanc_,cb_));
				entrave_.first=cible_.der_att_lancee();
				entrave_.second=QPair<bool,uchar>(true,0);
			}else if(att_lanc_=="EXCUSE"){
				/*si cible.pv_restants + 80 >= cible.pv_max
					cible.pv_restants <- cible.pv_max
				sinon
					cible.pv_restants += 80
				fin si*/
			}else if(att_lanc_=="GRAVITE"){
				effets_globaux.valeur(att_lanc_)=QPair<uchar,bool>(0,true);
				foreach(Combattant c2,creatures_act.cles()){
					CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
					foreach(Combattant c3,creatures_act.cles()){
						cr_c_2_.table_eff(c3,QPair<QString,QString>("SOL","VOL"))=Taux(1);
					}
					if(positions_places.valeur(c2).second==arriere){
						continue;
					}
					cr_c_2_.immu_att_type("SOL")=false;
					cr_c_2_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
					cr_c_2_.attaques_actives_def("VOL_MAGNETIK")=QPair<uchar,bool>(0,false);
					/*si combattant.puissance_attaque_subie[SOL] == 0
						combattant.puissance_attaque_subie[SOL] <- 1
					fin si*/
					if((cr_c_2_.att_choisie()=="VOL"||cr_c_2_.att_choisie()=="REBOND"||cr_c_2_.att_choisie()=="CHUTE_LIBRE")&&cr_c_2_.prepa_tour_pk()){
						cr_c_2_.disparition_pk()=false;
						cr_c_2_.prepa_tour_pk()=false;
					}
				}
			}else if(att_lanc_=="VOL_MAGNETIK"||att_lanc_=="LEVIKINESIE"){
				lanceur_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,true);
				lanceur_.immu_att_type("SOL")=true;
			}else if(att_lanc_=="IMITATION"){
				lanceur_.desactiver_capacite(true,positions_places,arriere,_d,climat);
				lanceur_.capacite_pk_act()=cible_.capacite_pk_act();
				if(lanceur_.capacite_pk_act()!=""){
					Taux pv_soignes_baie_(0);
					lanceur_.activer_capacite(true,_d,positions_places,zone_magique_,arriere,climat,pv_soignes_baie_);
				}
				if(lanceur_.capacite_pk_act()=="LEVITATION"){
					//TODO etre plus generique
					lanceur_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
				}
				lanceur_.maj_coeff_types_att_subie(_d);
				/*si gravite.actif et lanceur.capacite == LEVITATION
					lanceur.puissance_attaque_subie[SOL] <- 1
				fin si*/
			}else if(att_lanc_=="MORPHING"){
				lanceur_.morphing(cible_,_d);
				/*lanceur.creature_combat.nom <- cible.nom
				lanceur.creature_combat.types <- cible.types
				pour chaque attaque de cible.attaques_act
					lanceur.creature_combat.attaques_act.ajouter(n_attaque(attaque.nom,5,5))
				fin pour
				lanceur.creature_combat.poids <- cible.poids
				lanceur.creature_combat.capacite <- cible.capacite
				lanceur.morphing_actif <- vrai*/
			}else if(att_lanc_=="PASSE_PASSE"||att_lanc_=="TOUR_MAGIK"){
				++objets_utilisateur_perdus.valeur(lanceur_.objet());
				++objets_utilisateur_perdus.valeur(cible_.objet());
				QString objet_lanceur_=lanceur_.objet();
				lanceur_.objet()=cible_.objet();
				cible_.objet()=objet_lanceur_;
				if(lanceur_.objet()=="BALLE_FER"){
					lanceur_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
				}
				if(cible_.objet()=="BALLE_FER"){
					cible_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
				}
			}else if(att_lanc_=="PICOTS"){
				QPair<uchar,bool>& picots_=attaque_equipe(lc_.equipe(),att_lanc_);
				if(picots_.first<3){
					picots_.first++;
				}else if(!picots_.second){
					picots_.second=true;
				}
			}else if(att_lanc_=="PICS_TOXIKS"){
				QPair<uchar,bool>& pics_tox_=attaque_equipe(lc_.equipe(),att_lanc_);
				if(pics_tox_.first<2){
					pics_tox_.first++;
				}else if(!pics_tox_.second){
					pics_tox_.second=true;
				}
			}else if(att_lanc_=="PIEGE_DE_ROC"){
				attaque_equipe(lc_.equipe(),att_lanc_)=QPair<uchar,bool>(1,true);
			}else if(att_lanc_=="LIRE_ESPRIT"||att_lanc_=="VERROUILLAGE"){
				lanceur_.att_active_cible(att_lanc_,cb_)=true;
			}else if(att_lanc_=="STOCKAGE"){
				int& nb_ut_st_=lanceur_.nb_lancer(att_lanc_);
				if(nb_ut_st_<3){
					nb_ut_st_++;
				}
			}else if(att_lanc_=="TOURMENTE"){
				cible_.attaques_actives_ind(att_lanc_)=true;
			}else if(att_lanc_=="VAMPIGRAINE"){
				cible_.attaques_actives_ind(att_lanc_)=true;
			}else if(att_lanc_=="SUC_DIGESTIF"){
				cible_.desactiver_capacite(true,positions_places,arriere,_d,climat);
				cible_.capacite_pk_act()="";
			}else if(att_lanc_=="RIPOSTE"||att_lanc_=="VOILE_MIROIR"||att_lanc_=="FULMIFER"){
				degats_2_=Taux(0);
				if(att_lanc_=="RIPOSTE"){
					degats_2_=Taux(2)*lanceur_.att_deg_subie().first.first;
				}else if(att_lanc_=="VOILE_MIROIR"){
					degats_2_=Taux(2)*lanceur_.att_deg_subie().first.second;
				}else{//FULMIFER
					degats_2_=Taux(3LL,2LL)*(lanceur_.att_deg_subie().first.first+lanceur_.att_deg_subie().first.second);
				}
				//const QString& _att_lanc,const Combattant& _cb,CreatureCombat& _cible,const Combattant& _lc,CreatureCombat& _lanceur,
				//const Taux& _degats,const Taux& _degats_2,Taux& _degats_clone,Taux& _pv_soignes
				//Taux& _degats_recul,const QString& _type_att,Donnees *_d
				Taux degats_clone_(0);
				Taux pv_soignes_(0);
				Taux degats_recul_(0);
				traiter_apres_degats(att_lanc_,cb_,cible_,lc_,lanceur_,degats_,degats_2_,degats_clone_,pv_soignes_,degats_recul_,type_att_,_d);
				//traiter_apres_degats(att_lanc_,cb_,cible_,lc_,lanceur_,degats_,degats_2_,degats_clone_,pv_soignes_,degats_recul_,type_att_,_d)
				/*TODO generique
				si degats >= cible.pv_restants
					si non attaque_lanceur.ne_peut_pas_mettre_ko et non (cible.attaque_choisie == TENACITE et cible.attaque_reussie)
						mise_a_ko(cible)
					sinon si
						si cible.patience.actif
							cible.patience.degats += degats
						fin si
						cible.touche[attaque_lanceur.categorie] <- cible.pv_restants - 1
						cible.pv_restants <- 1
						si cible.capacite est CHANGEMENT_TYPE_SI_DEGATS
							cible.types <- type_attaque
						fin si
					fin si
				sinon
					si cible.patience.actif
						cible.patience.degats += degats
					fin si
					cible.pv_restants <- cible.pv_restants - degats
					cible.touche[attaque_lanceur.categorie] <- degats
					si cible.capacite est CHANGEMENT_TYPE_SI_DEGATS
						cible.types <- type_attaque
					fin si
				fin si
				si cible.statut == KO
					si cible.rancune.actif
						lanceur.nb_pp[attaque_lanceur] <- 0
					fin si
					si cible.prelevement_destin.actif et cible.equipe != lanceur.equipe
						mise_a_ko(lanceur)
					fin si
				fin si
				si cible.capacite est DEGATS_RECUL_ADV
					lanceur.pv_restants <- max(lanceur.pv_restants - lanceur.pv_max * cible.capacite.taux,0)
					si lanceur.pv_restants == 0
						mise_a_ko(lanceur)
					fin si
				fin si
				si lanceur.statut != KO
					si cible.capacite est EFFET_STATUT et cible.capacite.categorie == attaque_lanceur.categorie
						effet_en_cours <- cible.capacite.effet
						si cible.capacite == JOLI_SOURIRE et non protege_contre_amour(lanceur,cible)
							si non(lanceur.objet est IMMU_AMOUR et non lanceur.embargo_subi.actif et non zone_magique.actif)
								lanceur.amoureux[cible] <- vrai
								si lanceur.objet est SYNCHRO_AMOUR et non lanceur.embargo_subi.actif et non zone_magique.actif et non protege_contre_amour(cible,lanceur)
									cible.amoureux[lanceur] <- vrai
								fin si
							sinon si lanceur.objet est IMMU_AMOUR et non lanceur.embargo_subi.actif et non zone_magique.actif
								lanceur.dernier_objet <- lanceur.objet
								lanceur.objet <- ""
								lanceur.vient_de_perdre_objet <- vrai
							fin si
						sinon si traiter_reussite_un_seul_effet_statut(cible,lanceur,attaque_lanceur,effet_en_cours.statut)
							traiter_effet_statut(cible,lanceur,effet_en_cours,attaque_lanceur,faux)
						fin si
					sinon si cible.capacite == BOOM_FINAL et cible.statut == KO et attaque_lanceur.categorie == physique
						degats_boom <- lanceur.pv_max * cible.capacite.taux
						si degats_boom > lanceur.pv_restants
							mise_a_ko(lanceur)
						sinon
							lanceur.pv_restants -= degats_boom
							lanceur.touche[attaque_lanceur.categorie] <- degats_boom
						fin si
					fin si
					si cible.pv_restants > 0
						if(cible_.peut_utiliser_objet(zone_magique_)&&(!f_capac_l_2_||!f_capac_l_2_->anti_conso_baies_adv())){
							Baie *baie_cons_=qobject_cast<Baie*>(cible_.fiche_objet(_d))
							Taux pv_soignes_baie_(0)
							Taux taux_
							if(f_capac_c_2_&&f_capac_c_2_->ut_baie_soin_pv()>Taux(0)){
								taux_=f_capac_c_2_->ut_baie_soin_pv()
							}else{
								taux_=Taux(1)
							}
							if(baie_cons_&&baie_cons_->s_pv().second/taux_*cible_.pv_max()>=cible_.pv_restants_pk()){
								cible_.activer_baie(baie_cons_,_d,pv_soignes_baie_)
							}
						}
					fin si
				fin si
				si cible.statut != KO
					si cible.capacite == ARMUROUILLEE et cible.capacite.categorie == attaque_lanceur.categorie
						cible.boost[defense]--
						cible.boost[vitesse]++
					fin si
				fin si
				si cible.statut != KO
					si cible.capacite == COEUR_NOBLE et type_attaque == TENEBRE
						cible.boost[attaque]++
					sinon si cible.capacite == MOMIE et lanceur.capacite != MULTITYPE et attaque_lanceur.categorie == PHYSIQUE
						lanceur.capacite <- cible.capacite
					fin si
				fin si
				si cible.statut != KO
					si cible.capacite == PHOBIQUE et type_attaque appartient a [TENEBRE,INSECTE,SPECTRE]
						cible.boost[vitesse]++
					fin si
				sinon si lanceur.capacite == IMPUDENCE
					lanceur.boost[attaque]++
				fin si*/
			}else if(att_lanc_=="DANSE_LUNE"||att_lanc_=="VOEU_SOIN"){
				mise_a_ko(lc_,lanceur_,_d);
			}else if(att_lanc_=="SOUVENIR"){
				mise_a_ko(lc_,lanceur_,_d);
				Taux mult_(2);
				if(f_capac_c_2_){
					mult_*=f_capac_c_2_->taux_act(true);
				}
				cible_.var_boost("ATTAQUE",(int)-mult_,_d);
				cible_.var_boost("ATTAQUE_SPECIALE",(int)-mult_,_d);
			}else if(att_lanc_=="ECHANGE_PSY"){
				cible_.statut_pk()=lanceur_.statut_pk();
				lanceur_.statut_pk()="OK";
			}else if(att_lanc_=="ECHANGE"){
				lanceur_.desactiver_capacite(false,positions_places,arriere,_d,climat);
				cible_.desactiver_capacite(false,positions_places,arriere,_d,climat);
				QString capac_lanceur_=lanceur_.capacite_pk_act();
				lanceur_.capacite_pk_act()=cible_.capacite_pk_act();
				cible_.capacite_pk_act()=capac_lanceur_;
				;
				if(lanceur_.capacite_pk_act()!=""){
					Taux pv_soignes_baie_(0);
					lanceur_.activer_capacite(true,_d,positions_places,zone_magique_,arriere,climat,pv_soignes_baie_);
				}
				if(cible_.capacite_pk_act()!=""){
					Taux pv_soignes_baie_(0);
					cible_.activer_capacite(true,_d,positions_places,zone_magique_,arriere,climat,pv_soignes_baie_);
				}
				lanceur_.maj_coeff_types_att_subie(_d);
				cible_.maj_coeff_types_att_subie(_d);
				if(lanceur_.capacite_pk_act()=="LEVITATION"){
					//TODO etre plus generique
					lanceur_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
				}
				if(cible_.capacite_pk_act()=="LEVITATION"){
					//TODO etre plus generique
					cible_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
				}
				/*maj_coeff_types_att_subie(lanceur)
				si gravite.actif et lanceur.capacite == LEVITATION
					lanceur.puissance_attaque_subie[SOL] <- 1
				fin s
				maj_coeff_types_att_subie(cible)
				si gravite.actif et cible.capacite == LEVITATION
					cible.puissance_attaque_subie[SOL] <- 1
				fin si*/
				//fait:traiter l'activité des capacités
			}else if(att_lanc_=="EFFORT"){
				degats_2_=cible_.pv_restants_pk()-lanceur_.pv_restants_pk();
				cible_.pv_restants_pk()=lanceur_.pv_restants_pk();
				Taux degats_clone_(0);
				Taux pv_soignes_(0);
				Taux degats_recul_(0);
				traiter_apres_degats(att_lanc_,cb_,cible_,lc_,lanceur_,degats_,degats_2_,degats_clone_,pv_soignes_,degats_recul_,type_att_,_d);
				//traiter_apres_degats(att_lanc_,cb_,cible_,lc_,lanceur_,degats_,degats_2_,degats_clone_,pv_soignes_,degats_recul_,type_att_,_d)
			}else if(att_lanc_=="MALEDICTION_2"){
				if(lanceur_.pv_max()>=lanceur_.pv_restants_pk()*Taux(2LL)){
					mise_a_ko(lc_,lanceur_,_d);
				}else{
					lanceur_.pv_restants_pk()-=lanceur_.pv_max()*Taux(1LL,2LL);
				}
				cible_.attaques_actives_ind("MAUDIT")=true;
			}else if(att_lanc_=="PERMUCOEUR"){
				QStringList statistiques_;
				statistiques_<<"ATTAQUE";
				statistiques_<<"ATTAQUE_SPECIALE";
				statistiques_<<"DEFENSE";
				statistiques_<<"DEFENSE_SPECIALE";
				foreach(QString s,statistiques_){
					qint8 boost_l_=lanceur_.boost(s);
					qint8 boost_c_=cible_.boost(s);
					lanceur_.reinit_boost(s,_d);
					cible_.reinit_boost(s,_d);
					lanceur_.var_boost(s,boost_c_,_d);
					cible_.var_boost(s,boost_l_,_d);
				}
			}else if(att_lanc_=="PERMUFORCE"){
				QStringList statistiques_;
				statistiques_<<"ATTAQUE";
				statistiques_<<"ATTAQUE_SPECIALE";
				foreach(QString s,statistiques_){
					qint8 boost_l_=lanceur_.boost(s);
					qint8 boost_c_=cible_.boost(s);
					lanceur_.reinit_boost(s,_d);
					cible_.reinit_boost(s,_d);
					lanceur_.var_boost(s,boost_c_,_d);
					cible_.var_boost(s,boost_l_,_d);
				}
			}else if(att_lanc_=="PERMUGARDE"){
				QStringList statistiques_;
				statistiques_<<"DEFENSE";
				statistiques_<<"DEFENSE_SPECIALE";
				foreach(QString s,statistiques_){
					qint8 boost_l_=lanceur_.boost(s);
					qint8 boost_c_=cible_.boost(s);
					lanceur_.reinit_boost(s,_d);
					cible_.reinit_boost(s,_d);
					lanceur_.var_boost(s,boost_c_,_d);
					cible_.var_boost(s,boost_l_,_d);
				}
			}else if(att_lanc_=="VOEU"){
				QPair<uchar,QPair<bool,bool> >& voeu_actif_=voeu.valeur(positions_places.valeur(lc_));
				voeu_actif_.first=0;
				voeu_actif_.second.second=voeu_actif_.second.first;
				voeu_actif_.second.first=true;
			}else if(att_lanc_=="AROMATHERAPI"||att_lanc_=="GLAS_DE_SOIN"){
				foreach(Combattant c2,creatures_act.cles()){
					if(c2.equipe()!=lc_.equipe()||positions_places.valeur(c2).second==arriere){
						continue;
					}
					creatures_act.valeur(c2).statut_pk()="OK";
				}
			}else if(att_lanc_=="RECYCLAGE"){
				lanceur_.objet()=lanceur_.val_der_objet_ut();//_utilise_usage_unique
			}else if(att_lanc_=="PATIENCE"){
				degats_2_=Taux(2)*lanceur_.patience_pk().second.first;
				lanceur_.annuler_patience();
				Taux degats_clone_(0);
				Taux pv_soignes_(0);
				Taux degats_recul_(0);
				traiter_apres_degats(att_lanc_,cb_,cible_,lc_,lanceur_,degats_,degats_2_,degats_clone_,pv_soignes_,degats_recul_,type_att_,_d);
				//traiter_apres_degats(att_lanc_,cb_,cible_,lc_,lanceur_,degats_,degats_2_,degats_clone_,pv_soignes_,degats_recul_,type_att_,_d)
				/*si degats >= cible.pv_restants
					si non (cible.attaque_choisie == TENACITE et cible.attaque_reussie)
						mise_a_ko(cible)
					sinon si
						si cible.patience.actif
							cible.patience.degats += degats
						fin si
						cible.touche[attaque_lanceur.categorie] <- cible.pv_restants - 1
						cible.pv_restants <- 1
						si cible.capacite est CHANGEMENT_TYPE_SI_DEGATS
							cible.types <- type_attaque
						fin si
					fin si
				sinon
					si cible.patience.actif
						cible.patience.degats += degats
					fin si
					cible.pv_restants <- cible.pv_restants - degats
					cible.touche[attaque_lanceur.categorie] <- degats
					si cible.capacite est CHANGEMENT_TYPE_SI_DEGATS
						cible.types <- type_attaque
					fin si
				fin si
				si cible.statut == KO
					si cible.rancune.actif
						lanceur.nb_pp[attaque_lanceur] <- 0
					fin si
					si cible.prelevement_destin.actif et cible.equipe != lanceur.equipe
						mise_a_ko(lanceur)
					fin si
				fin si
				si cible.capacite est DEGATS_RECUL_ADV
					lanceur.pv_restants <- max(lanceur.pv_restants - lanceur.pv_max * cible.capacite.taux,0)
					si lanceur.pv_restants == 0
						mise_a_ko(lanceur)
					fin si
				fin si
				si lanceur.statut == KO
					si cible.capacite est EFFET_STATUT et cible.capacite.categorie == attaque_lanceur.categorie
						effet_en_cours <- cible.capacite.effet
						si cible.capacite == JOLI_SOURIRE et non protege_contre_amour(lanceur,cible)
							si non(lanceur.objet est IMMU_AMOUR et non lanceur.embargo_subi.actif et non zone_magique.actif)
								lanceur.amoureux[cible] <- vrai
								si lanceur.objet est SYNCHRO_AMOUR et non lanceur.embargo_subi.actif et non zone_magique.actif et non protege_contre_amour(cible,lanceur)
									cible.amoureux[lanceur] <- vrai
								fin si
							sinon si lanceur.objet est IMMU_AMOUR et non lanceur.embargo_subi.actif et non zone_magique.actif
								lanceur.objet <- ""
								lanceur.vient_de_perdre_objet <- vrai
							fin si
						sinon si traiter_reussite_un_seul_effet_statut(cible,lanceur,attaque_lanceur,effet_en_cours.statut)
							traiter_effet_statut(cible,lanceur,effet_en_cours,attaque_lanceur,faux)
						fin si
					sinon si cible.capacite == BOOM_FINAL et cible.statut == KO et attaque_lanceur.categorie == physique
						degats_boom <- lanceur.pv_max * cible.capacite.taux
						si degats_boom > lanceur.pv_restants
							mise_a_ko(lanceur)
						sinon
							lanceur.pv_restants -= degats_boom
							lanceur.touche[attaque_lanceur.categorie] <- degats_boom
						fin si
					fin si
					si cible.pv_restants > 0
						if(cible_.peut_utiliser_objet(zone_magique_)&&(!f_capac_l_2_||!f_capac_l_2_->anti_conso_baies_adv())){
							Baie *baie_cons_=qobject_cast<Baie*>(cible_.fiche_objet(_d))
							Taux pv_soignes_baie_(0)
							Taux taux_
							if(f_capac_c_2_&&f_capac_c_2_->ut_baie_soin_pv()>Taux(0)){
								taux_=f_capac_c_2_->ut_baie_soin_pv()
							}else{
								taux_=Taux(1)
							}
							if(baie_cons_&&baie_cons_->s_pv().second/taux_*cible_.pv_max()>=cible_.pv_restants_pk()){
								cible_.activer_baie(baie_cons_,_d,pv_soignes_baie_)
							}
						}
					fin si
				fin si
				si cible.statut != KO
					si cible.capacite == ARMUROUILLEE et cible.capacite.categorie == attaque_lanceur.categorie
						cible.boost[defense]--
						cible.boost[vitesse]++
					fin si
				fin si
				si cible.statut != KO
					si cible.capacite == COEUR_NOBLE et type_attaque == TENEBRE
						cible.boost[attaque]++
					sinon si cible.capacite == MOMIE et lanceur.capacite != MULTITYPE et attaque_lanceur.categorie == PHYSIQUE
						lanceur.capacite <- cible.capacite
					fin si
				fin si
				si cible.statut != KO
					si cible.capacite == PHOBIQUE et type_attaque appartient a [TENEBRE,INSECTE,SPECTRE]
						cible.boost[vitesse]++
					fin si
				sinon si lanceur.capacite == IMPUDENCE
					lanceur.boost[attaque]++
				fin si*/
			}else if(att_lanc_=="REQUIEM"){
				effets_globaux.valeur(att_lanc_)=QPair<uchar,bool>(0,true);
			}else if(att_lanc_=="RANCUNE"||att_lanc_=="PRLVT_DESTIN"){
				lanceur_.attaques_actives_ind(att_lanc_)=true;
			}else if(att_lanc_=="EMBARGO"){
				cible_.attaques_actives_def(att_lanc_)=QPair<uchar,bool>(0,true);
			}else if(att_lanc_=="DISTORSION"||att_lanc_=="ZONE_MAGIQUE"){
				effets_globaux.valeur(att_lanc_).first=0;
				effets_globaux.valeur(att_lanc_).second=!effets_globaux.valeur(att_lanc_).second;
			}else if(att_lanc_=="ZONE_ETRANGE"){
				effets_globaux.valeur(att_lanc_).first=0;
				effets_globaux.valeur(att_lanc_).second=!effets_globaux.valeur(att_lanc_).second;
				foreach(Combattant c2,creatures_act.cles()){
					creatures_act.valeur(c2).echanger_statistiques("DEFENSE","DEFENSE_SPECIALE");
				}
			}else if(att_lanc_=="MUR_LUMIERE"||att_lanc_=="BRUME"||att_lanc_=="PROTECTION"||att_lanc_=="VENT_ARRIERE"){
				attaque_equipe(lc_.equipe(),att_lanc_)=QPair<uchar,bool>(0,true);
			}else if(att_lanc_=="RUNE_PROTECT"){
				attaque_equipe(lc_.equipe(),att_lanc_)=QPair<uchar,bool>(0,true);
				foreach(Combattant c2,creatures_act.cles()){
					if(c2.equipe()!=lc_.equipe()||positions_places.valeur(c2).second==arriere){
						continue;
					}
					CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
					if(cr_c_2_.statut_pk()=="KO"){
						continue;
					}
					cr_c_2_.statut_pk()="OK";
					cr_c_2_.confusion_pk()=QPair<uchar,bool>(0,false);
				}
			}else if(att_lanc_=="POSSESSIF"){
				lanceur_.poss_pk(cb_).clear();
				foreach(QString a,lanceur_.noms_attaques_act()){
					if(cible_.noms_attaques_act().contains(a)){
						lanceur_.poss_pk(cb_)<<a;
					}
				}
				//QStringList& CreatureCombat::poss_pk(cb_)
				//lanceur.possessif.actif <- vrai
			}
		}
		if(util_att_prec_suiv_&&lanceur_.att_reussie()&&att_lanc_!="VERROUILLAGE"&&att_lanc_!="LIRE_ESPRIT"){
			lanceur_.att_active_cible("VERROUILLAGE",cb_)=false;
			lanceur_.att_active_cible("LIRE_ESPRIT",cb_)=false;
		}
		cible_.utilisation_baie()|=util_baie_.valeur(cb_);
		lanceur_.utilisation_baie()|=util_baie_.valeur(lc_);
		/*si cible.utilise_baie et cible.objet est_du_type baie
			cible.dernier_objet <- cible.objet
			cible.objet <- ""
			cible.vient_de_perdre_objet <- vrai
		fin si
		cible.utilise_baie <- faux*/
		/*
		TODO pourquoi?
		si attaque_lanceur.cibles.contient(TOUS ADV) et cbt_reflet_m != INEXISTANT
			lanceur <- cbt_reflet_m
		sinon si lanceur.attaque_choisie == REFLET_MAGIK et lanceur.attaque_reussie et attaques_reflet_magik.contient(attaque_lanceur)
			tmp <- cible
			cible <- lanceur
			lanceur <- tmp
		sinon si existe_saisie2
			lanceur <- cible
		fin si*/
		//todo permuttant les valeur de lanceur et de cible pour un lanceur de reflet_magik qui est cible d'une attaque concernée par reflet_magik
		//todo permuttant les valeur de lanceur et de cible pour un lanceur de saisie sur le lanceur d'une attaque concernée par saisie
	}
	//plus tard fin de la boucle des cibles
	if(!_lanceur.att_reussie()){
		if(att_lanc_=="ROULADE"||att_lanc_=="BALL_GLACE"){
			_lanceur.coeff_roul_ballglace()=1;
			_lanceur.attaques_actives_def(att_lanc_)=QPair<uchar,bool>(0,false);
		}
		if(att_lanc_=="DESTRUCTION"||att_lanc_=="EXPLOSION"){
			mise_a_ko(_lc,_lanceur,_d);
		}else if(f_att_l_->eff_ech()){
			/*Taux degats_=calcul_degats(loi_repet_coup_,att_lanc_,f_att_l_,type_att_,lc_,lanceur_,cb_,cible_,Taux(0),ElementsCombat::ALEA,util_baie_,cc_min_,_d,Taux(1))*Taux(1LL,8LL)
			
			 <- calcul_degats(lanceur,cible,attaque_lanceur,type_attaque,faux,valeur_cadeau_degats)/8
			si degats >= lanceur.pv_restants
				mise_a_ko(lanceur)
			sinon
				lanceur.pv_restants -= degats
			fin si*/
		}
	}
	if(_lanceur.statut_pk()!="KO"){
		bool existe_bloque_conso_baie_=false;
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==_lc.equipe()){
				continue;
			}
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			FicheCapacite *f_capac_c_=creatures_act.valeur(c).fiche_capacite(_d);
			if(f_capac_c_&&f_capac_c_->anti_conso_baies_adv()){
				existe_bloque_conso_baie_=true;
				break;
			}
		}
		if(_lanceur.peut_utiliser_objet(zone_magique_)&&!existe_bloque_conso_baie_){
			Baie *baie_cons_=qobject_cast<Baie*>(_lanceur.fiche_objet(_d));
			Taux pv_soignes_baie_(0);
			Taux taux_;
			if(f_capac_l_&&f_capac_l_->ut_baie_soin_pv()>Taux(0)){
				taux_=f_capac_l_->ut_baie_soin_pv();
			}else{
				taux_=Taux(1);
			}
			if(baie_cons_&&baie_cons_->s_pv().second/taux_*_lanceur.pv_max()>=_lanceur.pv_restants_pk()){
				_lanceur.activer_baie(baie_cons_,_d,pv_soignes_baie_);
			}else if(baie_cons_&&baie_cons_->s_tx_pv().second/taux_*_lanceur.pv_max()>=_lanceur.pv_restants_pk()){
				_lanceur.activer_baie(baie_cons_,_d,pv_soignes_baie_);
			}
		}
		if(f_capac_l_){
			foreach(QString s,f_capac_l_->mult_statis().cles()){
				if(s=="VITESSE"){
					QPair<Taux,bool> val_=f_capac_l_->mult_statis().valeur(s);
					if(!val_.second){
						_lanceur.var_boost(s,val_.first,_d);
					}
				}
			}
		}
	}
	/*si lanceur.utilise_baie et lanceur.objet est_du_type baie
		lanceur.dernier_objet <- lanceur.objet
		lanceur.objet <- ""
		lanceur.vient_de_perdre_objet <- vrai
	fin si
	lanceur.utilise_baie <- faux*/
}

void ElementsCombat::traiter_apres_degats(const QString& _att_lanc,const Combattant& _cb,CreatureCombat& _cible,const Combattant& _lc,CreatureCombat& _lanceur,const Taux& _degats,const Taux& _degats_2,Taux& _degats_clone,Taux& _pv_soignes,Taux& _degats_recul,const QString& _type_att,Donnees *_d){
	FicheCapacite *f_capac_c_2_=_cible.fiche_capacite(_d);
	FicheCapacite *f_capac_l_2_=_lanceur.fiche_capacite(_d);
	FicheAttaque *f_att_l_=_d->val_attaques().valeur(_att_lanc);
	bool zone_magique_=effet_global("ZONE_MAGIQUE").second;
	if(_lanceur.peut_utiliser_objet(zone_magique_)&&_cb.equipe()!=_lc.equipe()){
		ObjetAttachableCombat *obj_lanceur_=qobject_cast<ObjetAttachableCombat*>(_lanceur.fiche_objet(_d));
		if(obj_lanceur_&&obj_lanceur_->dr_tx_deg()>Taux(0)){
			Taux pv_=Utilitaire::max_min<Taux>(_cible.pv_restants_pk(),_cible.pv_max()*obj_lanceur_->dr_tx_deg()).second;
			if(_cible.patience_pk().second.second){
				_cible.patience_pk().second.first+=pv_;
			}
			if(!attaque_equipe(adversaire(_lc.equipe()),"ANTI_SOIN").second){
				if(!f_capac_c_2_||f_capac_c_2_->mult_tx_deg_adv_abs()==0){
					_degats_recul+=pv_;
				}else{
					_pv_soignes+=pv_;
				}
			}
		}
	}
	if(_cible.objet()!=""&&qobject_cast<Baie*>(_cible.fiche_objet(_d))&&_att_lanc=="CALCINATION"){
		_cible.val_der_objet_ut()=_cible.objet();
		_cible.objet()="";
		_cible.perte_objet()=true;
	}
	if(_att_lanc=="REBONDIFEU"){
		if(diff.r_adjacence_active()){
			foreach(Combattant c2,creatures_act.cles()){
				if(c2==_cb||c2.equipe()==_lc.equipe()||positions_places.valeur(c2).second==arriere){
					continue;
				}
				if((Taux(c2.position())-Taux(_cb.position())).absolu()>Taux(1)){
					continue;
				}
				CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
				if(cr_c_2_.pv_restants_pk()*Taux(8)<cr_c_2_.pv_max()){
					cr_c_2_.pv_restants_pk()=Taux(0);
					mise_a_ko(c2,cr_c_2_,_d);
				}else{
					cr_c_2_.pv_restants_pk()-=cr_c_2_.pv_max()*Taux(1LL,8LL);
				}
			}
		}else{
			foreach(Combattant c2,creatures_act.cles()){
				if(c2==_cb||c2.equipe()==_lc.equipe()||positions_places.valeur(c2).second==arriere){
					continue;
				}
				CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
				if(cr_c_2_.pv_restants_pk()*Taux(8)<cr_c_2_.pv_max()){
					cr_c_2_.pv_restants_pk()=Taux(0);
					mise_a_ko(c2,cr_c_2_,_d);
				}else{
					cr_c_2_.pv_restants_pk()-=cr_c_2_.pv_max()*Taux(1LL,8LL);
				}
			}
		}
	}
	if(_att_lanc=="ANTI_AIR"){
		if(!_cible.disparition_pk()||(_cible.att_choisie()!="VOL"&&_cible.att_choisie()!="REBOND"&&_cible.att_choisie()!="CHUTE_LIBRE")){
			_cible.attaques_actives_ind(_att_lanc)=true;
			_cible.immu_att_type("SOL")=false;
			_cible.attaques_actives_def("LEVIKINSIE")=QPair<uchar,bool>(0,false);
			_cible.attaques_actives_def("VOL_MAGNETIK")=QPair<uchar,bool>(0,false);
		}else{
			_cible.disparition_pk()=false;
			_cible.prepa_tour_pk()=false;
		}
	}
	if(_cible.clone_pk().estNul()){
		if(_degats_2>Taux(0)){
			if(_degats<_cible.pv_restants_pk()){
				if(_degats_2>=_cible.pv_restants_pk()){
					bool traiter_ko_cible_=false;
					if(!f_att_l_->pas_ko()){
						traiter_ko_cible_=true;
					}
					if(traiter_ko_cible_){
						if(_cible.att_choisie()=="TENACITE"&&_cible.att_reussie()){
							traiter_ko_cible_=false;
						}
					}
					if(traiter_ko_cible_){
						if(_cible.peut_utiliser_objet(zone_magique_)){
							ObjetAttachableCombat *obj_cible_=qobject_cast<ObjetAttachableCombat*>(_cible.fiche_objet(_d));
							if(obj_cible_&&!obj_cible_->a_ko().estNul()){
								traiter_ko_cible_=false;
							}
							if(traiter_ko_cible_){
								if(obj_cible_&&!obj_cible_->a_ko_pv().estNul()&&_cible.pv_restants_pk()==_cible.pv_max()){
									traiter_ko_cible_=false;
								}
							}
						}
					}
					if(traiter_ko_cible_){
						mise_a_ko(_cb,_cible,_d);
					}else{
						if(f_att_l_->cat()=="PHYSIQUE"){
							_cible.att_deg_subie().first.first+=_cible.pv_restants_pk()-Taux(1);
						}else if(f_att_l_->cat()=="SPECIALE"){
							_cible.att_deg_subie().first.second+=_cible.pv_restants_pk()-Taux(1);
						}
						_cible.pv_restants_pk()=Taux(1);
						if(f_capac_c_2_&&f_capac_c_2_->chgt_type_deg()){
							_cible.types_pk().clear();
							_cible.types_pk()<<_type_att;
						}
					}
				}else{
					_cible.pv_restants_pk()-=_degats_2;
					if(f_att_l_->cat()=="PHYSIQUE"){
						_cible.att_deg_subie().first.first+=_degats_2;
					}else if(f_att_l_->cat()=="SPECIALE"){
						_cible.att_deg_subie().first.second+=_degats_2;
					}
					if(f_capac_c_2_&&f_capac_c_2_->chgt_type_deg()){
						_cible.types_pk().clear();
						_cible.types_pk()<<_type_att;
					}
				}
			}
		}
	}else{
		_cible.clone_pk()-=_degats_clone;
	}
	if(_cible.statut_pk()=="KO"){
		if(_cible.attaques_actives_ind("RANCUNE")){
			_lanceur.supprimer_pp(_att_lanc);
		}
		if(_cible.attaques_actives_ind("PRLVT_DESTIN")&&_cb.equipe()!=_lc.equipe()){
			mise_a_ko(_lc,_lanceur,_d);
		}
	}else if(_att_lanc=="REVEIL_FORCE"&&_cible.statut_pk()=="SOMMEIL"&&_cible.clone_pk().estNul()){
		_cible.statut_pk()="OK";
		_cible.attaques_actives_def("REPOS")=QPair<uchar,bool>(false,0);
		_cible.sommeil_non_repos()=0;
	}else if(_att_lanc=="STIMULANT"&&_cible.statut_pk()=="PARALYSIE"&&_cible.clone_pk().estNul()){
		_cible.statut_pk()="OK";
	}
	if(_lanceur.statut_pk()!="KO"){
		Taux pv_soignes_totaux_(0);
		_lanceur.soin_pv(_pv_soignes,pv_soignes_totaux_,_d);
		if(_degats_recul>=_lanceur.pv_restants_pk()){
			mise_a_ko(_lc,_lanceur,_d);
		}else{
			_lanceur.pv_restants_pk()-=_degats_recul;
		}
		if(f_capac_c_2_&&!f_capac_c_2_->deg_recul_adv().estNul()&&_cible.statut_pk()!="KO"&&f_att_l_->dir()){
			_lanceur.pv_restants_pk()=Utilitaire::max_min<Taux>(_lanceur.pv_restants_pk()-_lanceur.pv_max()*f_capac_c_2_->deg_recul_adv(),Taux(0)).first;
			if(_lanceur.pv_restants_pk().estNul()){
				mise_a_ko(_lc,_lanceur,_d);
			}
		}
		ObjetAttachableCombat *obj_cible_=NULL;
		if(_cible.objet()!=""){
			obj_cible_=qobject_cast<ObjetAttachableCombat*>(_cible.fiche_objet(_d));
		}
		if(obj_cible_&&!obj_cible_->recul().estNul()&&_cible.statut_pk()!="KO"&&f_att_l_->dir()){
			_lanceur.pv_restants_pk()=Utilitaire::max_min<Taux>(_lanceur.pv_restants_pk()-_lanceur.pv_max()*f_capac_c_2_->deg_recul_adv(),Taux(0)).first;
			if(_lanceur.pv_restants_pk().estNul()){
				mise_a_ko(_lc,_lanceur,_d);
			}
		}
		if(_lanceur.statut_pk()!="KO"){
			if(f_capac_c_2_&&f_att_l_->dir()){
			//cible.capacite.categorie == attaque_lanceur.categorie
				MonteCarlo<QString> event_=f_capac_c_2_->statut_sim();
				QStringList statuts_=event_.events();
				//TODO calculer la nouvelle loi de proba avec des prob d'effets mult.
				QStringList statuts_poss_;
				foreach(QString s,statuts_){
					if(s=="AMOUR"){
						if(!protege_contre_amour(_lanceur,_cible,_lanceur.capacite_pk_act(),f_capac_l_2_,f_capac_c_2_)){
							//IMMU_AMOUR 
							if(!_lanceur.peut_utiliser_objet(zone_magique_)){
								statuts_poss_<<s;
							}else{
								ObjetAttachableCombat *obj_lanceur_=qobject_cast<ObjetAttachableCombat*>(_lanceur.fiche_objet(_d));
								if(!obj_lanceur_||!obj_lanceur_->immu_am()){
									statuts_poss_<<s;
								}
							}
						}
					}else if(s!="PEUR"){
						bool pseudo_statut_=_d->val_noms_statuts().filter(QRegExp("^"+s+"\\b")).isEmpty();
						if(traiter_reussite_seul_effet_statut(_cible,f_capac_c_2_,_lanceur,_lanceur.capacite_pk_act(),f_capac_l_2_,_lc.equipe(),_att_lanc,s,true,statuts_,pseudo_statut_,_d)){
							statuts_poss_<<s;
						}
					}
				}
				statuts_poss_.removeOne("OK");
				if(!statuts_poss_.isEmpty()){
					bool existe_statut_=false;
					foreach(QString s,statuts_poss_){
						if(event_.events().contains(s)){
							existe_statut_=true;
						}
					}
					if(existe_statut_){
						QString statut_=event_.tirage();
						bool pseudo_statut_=_d->val_noms_statuts().filter(QRegExp("^"+statut_+"\\b")).isEmpty();
						if(statut_=="AMOUR"){
							if(!protege_contre_amour(_lanceur,_cible,_lanceur.capacite_pk_act(),f_capac_l_2_,f_capac_c_2_)){
								//IMMU_AMOUR
								bool tombe_amoueux_=false;
								if(!_lanceur.peut_utiliser_objet(zone_magique_)){
									tombe_amoueux_=true;
								}else{
									ObjetAttachableCombat *obj_lanceur_=qobject_cast<ObjetAttachableCombat*>(_lanceur.fiche_objet(_d));
									if(!obj_lanceur_||!obj_lanceur_->immu_am()){
										tombe_amoueux_=true;
									}
								}
								if(tombe_amoueux_){
									_lanceur.att_active_cible("AMOUR",_cb)=true;
									if(_lanceur.peut_utiliser_objet(zone_magique_)){
										ObjetAttachableCombat *obj_lanceur_=qobject_cast<ObjetAttachableCombat*>(_lanceur.fiche_objet(_d));
										if(obj_lanceur_&&obj_lanceur_->sync_am()){
											_cible.att_active_cible("AMOUR",_lc)=true;
										}
									}
								}
							}
						}else if(traiter_reussite_seul_effet_statut(_cible,f_capac_c_2_,_lanceur,_lanceur.capacite_pk_act(),f_capac_l_2_,_lc.equipe(),_att_lanc,statut_,true,statuts_,pseudo_statut_,_d)){
							if(statut_!="PEUR"){
								traiter_effet_statut(_lc,_lanceur,_lc.equipe(),_cible,_cb.equipe(),event_,_att_lanc,false,_d);
							}
						}
					}
				}
			}else if(_cible.statut_pk()=="KO"&&f_att_l_->dir()&&f_capac_c_2_&&!f_capac_c_2_->deg_recul_adv_ko().estNul()){
				//sinon si cible.capacite == BOOM_FINAL et cible.statut == KO et attaque_lanceur.directe//et attaque_lanceur.categorie == physique
				Taux degats_boom_=_lanceur.pv_max()*f_capac_c_2_->deg_recul_adv_ko();
				if(degats_boom_>_lanceur.pv_restants_pk()){
					mise_a_ko(_lc,_lanceur,_d);
				}else{
					_lanceur.pv_restants_pk()-=degats_boom_;
					if(f_att_l_->cat()=="PHYSIQUE"){
						_lanceur.att_deg_subie().first.first+=degats_boom_;
					}else if(f_att_l_->cat()=="SPECIALE"){
						_lanceur.att_deg_subie().first.second+=degats_boom_;
					}
				}
			}
		}
	}//mom()
	if(_cible.statut_pk()!="KO"){
		if(f_capac_c_2_&&f_capac_c_2_->mom()&&f_att_l_->dir()&&(!f_capac_l_2_||!f_capac_l_2_->plaq())){
			//et attaque_lanceur.categorie == PHYSIQUE
			_lanceur.capacite_pk_act()=_cible.capacite_pk_act();
		}
	}
	if(_cible.statut_pk()=="KO"){
		if(f_capac_l_2_){
			foreach(QString s,f_capac_l_2_->mult_statis_adv_ko().cles()){
				_lanceur.var_boost(s,f_capac_l_2_->mult_statis_adv_ko().valeur(s),_d);
			}
		}
	}
	if(_cible.peut_utiliser_objet(zone_magique_)&&(!f_capac_l_2_||!f_capac_l_2_->anti_conso_baies_adv())){
		Baie *baie_cons_=qobject_cast<Baie*>(_cible.fiche_objet(_d));
		Taux pv_soignes_baie_(0);
		Taux taux_;
		if(f_capac_c_2_&&f_capac_c_2_->ut_baie_soin_pv()>Taux(0)){
			taux_=f_capac_c_2_->ut_baie_soin_pv();
		}else{
			taux_=Taux(1);
		}
		if(baie_cons_&&baie_cons_->s_pv().second/taux_*_cible.pv_max()>=_cible.pv_restants_pk()){
			_cible.activer_baie(baie_cons_,_d,pv_soignes_baie_);
		}else if(baie_cons_&&baie_cons_->s_tx_pv().second/taux_*_cible.pv_max()>=_cible.pv_restants_pk()){
			_cible.activer_baie(baie_cons_,_d,pv_soignes_baie_);
		}
	}
	commentaire_recent+=_degats_2.evaluer(3)+" points de degats infliges a "+_cible.nom_pk_act()+"\n";
	commentaire_recent+=_pv_soignes.evaluer(3)+" points de vie soignes pour "+_lanceur.nom_pk_act()+"\n";
	commentaire_recent+=_degats_recul.evaluer(3)+" points de degats de recul inflige a "+_lanceur.nom_pk_act()+"\n";
	commentaire_recent+=_degats_clone.evaluer(3)+" points de degats inflige au clone de "+_cible.nom_pk_act()+"\n";
}

void ElementsCombat::effets_fin_tour(Donnees *_d){
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.att_choisie()=="ATTERRISSAGE"&&cr_c_.att_reussie()){
			cr_c_.atterrissage().first=false;
			if(cr_c_.pur_vol_atterr()){
				cr_c_.types_pk().removeOne("NORMAL");
				cr_c_.pur_vol_atterr()=false;
			}
			if(cr_c_.atterrissage().second){
				cr_c_.types_pk()<<"VOL";
				cr_c_.atterrissage().second=false;
				cr_c_.attaques_actives_def("LEVIKINESIE")=QPair<uchar,bool>(0,false);
			}
		}
	}
	typedef QPair<uchar,uchar> PositionPlace;
	typedef QPair<QString,PositionPlace> AttaquePosPlace;
	foreach(AttaquePosPlace a,prescience_carnar.cles()){
		QPair<QPair<Taux,uchar>,QPair<uchar,uchar> >& valeur_=prescience_carnar.valeur(a);
		if(valeur_.second.second==arriere){
			continue;
		}
		if(valeur_.first.second<2){
			valeur_.first.second++;
		}else{
			valeur_.first.second=0;
			//CreatureCombat& cr_lanceur_=creatures_act.valeur(a.second)
			//TODO gestion des pp pour le lanceur
			if(!positions_places.cles(valeur_.second).isEmpty()){
				Combattant c_=positions_places.cles(valeur_.second)[0];
				CreatureCombat& cr_cible_=creatures_act.valeur(c_);
				//TODO calcul precision
				//if(calcul_precision(_lc,_lanceur,att_lanc_,f_att_l_,c,cr_c_,ElementsCombat::ALEA,util_att_prec_suiv_,util_baie_,_d)
				MonteCarloNombre loi_;
				if(valeur_.second.first==adv){
					loi_=CreatureCombat::loi_random(diff.r_choix_lois().first);
				}else{
					loi_=CreatureCombat::loi_random(diff.r_choix_lois().second);
				}
				if(cr_cible_.clone_pk().estNul()){
					if(valeur_.first.first*loi_.minimum()>=cr_cible_.pv_restants_pk()){
						mise_a_ko(c_,cr_cible_,_d);
					}else{
						Taux degats_=valeur_.first.first*loi_.tirage();
						if(degats_>=cr_cible_.pv_restants_pk()){
							mise_a_ko(c_,cr_cible_,_d);
						}else{
							cr_cible_.pv_restants_pk()-=degats_;
						}
					}
				}else{
					if(valeur_.first.first*loi_.minimum()>=cr_cible_.clone_pk()){
						cr_cible_.clone_pk()=Taux(0);
					}else{
						Taux degats_=valeur_.first.first*loi_.tirage();
						if(degats_>=cr_cible_.clone_pk()){
							cr_cible_.clone_pk()=Taux(0);
						}else{
							cr_cible_.clone_pk()-=degats_;
						}
					}
				}
				valeur_.first.first=Taux(0);
				valeur_.second.first=arriere;
				valeur_.second.second=arriere;
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="SOMMEIL"){
			if(cr_c_.sommeil_non_repos()>0){
				cr_c_.sommeil_non_repos()++;
			}else{
				cr_c_.attaques_actives_def("REPOS").first++;
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.attaques_actives_def("BAILLE").second&&cr_c_.statut_pk()!="KO"){
			if(cr_c_.attaques_actives_def("BAILLE").first<1){
				cr_c_.attaques_actives_def("BAILLE").first++;
			}else{
				cr_c_.attaques_actives_def("BAILLE")=QPair<uchar,bool>(0,false);
				if(traiter_reussite_seul_effet_statut(cr_c_,cr_c_.fiche_capacite(_d),c.equipe(),"SOMMEIL",false,_d)){
					cr_c_.attaques_actives_def("REPOS").first=0;
					cr_c_.statut_pk()="SOMMEIL";
				}
			}
		}
	}
	if(effet_global("REQUIEM").second){
		QPair<uchar,bool>& eff_=effets_globaux.valeur("REQUIEM");
		if(eff_.first<3){
			eff_.first++;
		}else{
			eff_=QPair<uchar,bool>(0,false);
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				CreatureCombat& cr_c_=creatures_act.valeur(c);
				FicheCapacite *f_capac_=cr_c_.fiche_capacite(_d);
				if(f_capac_&&f_capac_->immu_att().contains("REQUIEM")){
					continue;
				}
				mise_a_ko(c,cr_c_,_d);
			}
		}
	}
	if(effet_global("DISTORSION").second){
		QPair<uchar,bool>& eff_=effets_globaux.valeur("DISTORSION");
		if(eff_.first<5){
			eff_.first++;
		}else{
			eff_=QPair<uchar,bool>(0,false);
		}
	}
	if(effet_global("ZONE_ETRANGE").second){
		QPair<uchar,bool>& eff_=effets_globaux.valeur("ZONE_ETRANGE");
		if(eff_.first<5){
			eff_.first++;
		}else{
			eff_=QPair<uchar,bool>(0,false);
			foreach(Combattant c,creatures_act.cles()){
				creatures_act.valeur(c).echanger_statistiques("DEFENSE","DEFENSE_SPECIALE");
			}
		}
	}
	if(effet_global("ZONE_MAGIQUE").second){
		QPair<uchar,bool>& eff_=effets_globaux.valeur("ZONE_MAGIQUE");
		if(eff_.first<5){
			eff_.first++;
		}else{
			eff_=QPair<uchar,bool>(0,false);
		}
	}
	if(effet_global("GRAVITE").second){
		QPair<uchar,bool>& eff_=effets_globaux.valeur("GRAVITE");
		if(eff_.first<5){
			eff_.first++;
		}else{
			eff_=QPair<uchar,bool>(0,false);
			foreach(Combattant c,creatures_act.cles()){
				CreatureCombat& cr_c_=creatures_act.valeur(c);
				foreach(Combattant c2,creatures_act.cles()){
					cr_c_.table_eff(c2,QPair<QString,QString>("SOL","VOL"))=Taux(0);
				}
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				cr_c_.immu_att_type("SOL")=false;
				/*si combattant.puissance_attaque_subie[SOL] == 0
					combattant.puissance_attaque_subie[SOL] <- 1
				fin si*/
			}
			/*pour chaque combattant
				si positions_places.valeur(combattant).place == ARRIERE
					continuer
				fin si
				pour chaque combattant2
					si positions_places.valeur(combattant2).place == ARRIERE
						continuer
					fin si
					combattant.tableau_eff[combattant2].maj([SOL,VOL],0)
					si combattant2.capacite == LEVITATION et non combattant2.racines.actif
						combattant2.puissance_attaque_subie[SOL] <- 0
					fin si
				fin pour
			fin pour*/
		}
	}
	QStringList attaques_equipes_;
	attaques_equipes_<<"AIR_VEINARD";
	attaques_equipes_<<"ANTI_SOIN";
	attaques_equipes_<<"BRUME";
	attaques_equipes_<<"RUNE_PROTECT";
	attaques_equipes_<<"VENT_ARRIERE";
	attaques_equipes_<<"PROTECTION";
	attaques_equipes_<<"MUR_LUMIERE";
	attaques_equipes_<<"AIRE_EAU_FEU";
	attaques_equipes_<<"AIRE_EAU_HERBE";
	attaques_equipes_<<"AIRE_FEU_HERBE";
	foreach(uchar e,nb_tour_attaque_equipe.cles()){
		foreach(QString a,nb_tour_attaque_equipe.valeur(e).cles()){
			if(!attaques_equipes_.contains(a)){
				continue;
			}
			QPair<uchar,bool>& eff_=nb_tour_attaque_equipe.valeur(e).valeur(a);
			if(eff_.second){
				if(a=="BRUME"||a=="RUNE_PROTECT"||a=="AIR_VEINARD"||a=="ANTI_SOIN"){
					if(eff_.first<5){
						eff_.first++;
					}else{
						eff_=QPair<uchar,bool>(0,false);
					}
				}else if(a=="VENT_ARRIERE"||a.startsWith("AIRE")){
					if(eff_.first<3){
						eff_.first++;
					}else{
						eff_=QPair<uchar,bool>(0,false);
					}
				}else{
					QPair<QString,uchar> lumarg_=existence_pk_eq_lumargile_non_embargo(e,_d);
					if((lumarg_.first!=""&&eff_.first<lumarg_.second)||eff_.first<5){
						eff_.first++;
					}else{
						eff_=QPair<uchar,bool>(0,false);
					}
				}
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="KO"){
			continue;
		}
		QStringList attaques_fin_tour_;
		attaques_fin_tour_<<"BROUHAHA";
		attaques_fin_tour_<<"COLERE";
		attaques_fin_tour_<<"DANSE_FLEUR";
		attaques_fin_tour_<<"MANIA";
		attaques_fin_tour_<<"ROULADE";
		attaques_fin_tour_<<"BALL_GLACE";
		foreach(QString a,attaques_fin_tour_){
			QPair<uchar,bool>& eff_=cr_c_.attaques_actives_def(a);
			if(eff_.second){
				if(CreatureCombat::tirage_effet_continuer(_d->val_attaques().valeur(a)->loi_rep_tour(),(long long)eff_.first)){
					eff_.first++;
				}else{
					eff_=QPair<uchar,bool>(0,false);
				}
			}
		}
		attaques_fin_tour_.clear();
		attaques_fin_tour_<<"EMBARGO";
		attaques_fin_tour_<<"VOL_MAGNETIK";
		attaques_fin_tour_<<"LEVIKINESIE";
		foreach(QString a,attaques_fin_tour_){
			QPair<uchar,bool>& eff_=cr_c_.attaques_actives_def(a);
			if(eff_.second){
				if(a=="LEVIKINESIE"){
					if(eff_.first<3){
						eff_.first++;
					}else{
						eff_=QPair<uchar,bool>(0,false);
					}
				}else{
					if(eff_.first<5){
						eff_.first++;
					}else{
						eff_=QPair<uchar,bool>(0,false);
					}
				}
			}
		}
		foreach(Combattant c2,creatures_act.cles()){
			QPair<QString,QPair<bool,uchar> >& entrave_=cr_c_.cible_atts(QPair<QString,Combattant>("ENTRAVE",c2));
			if(entrave_.second.first){
				if(CreatureCombat::tirage_effet_fin_tour("ENTRAVE",entrave_.second.second,_d)){
					entrave_.second.second++;
				}else{
					entrave_.second=QPair<bool,uchar>(false,0);
					entrave_.first="";
				}
			}
		}
		QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_.patience_pk();
		if(patience_.second.second){
			patience_.first++;
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="KO"){
			continue;
		}
		FicheCapacite *f_capac_=cr_c_.fiche_capacite(_d);
		if(f_capac_){
			if(cr_c_.statut_pk()!="OK"&&!f_capac_->statut_o().estNul()){
				Taux proba_=f_capac_->statut_o();
				Entier proba_1_=proba_.gnumerateur();
				Entier proba_2_=proba_.gdenominateur()-proba_1_;
				MonteCarlo<bool> loi_;
				loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
				loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
				if(loi_.tirage()){
					cr_c_.statut_pk()="OK";
				}
			}
			if(!f_capac_->statut_o_p().estNul()){
				Taux proba_=f_capac_->statut_o_p();
				Entier proba_1_=proba_.gnumerateur();
				Entier proba_2_=proba_.gdenominateur()-proba_1_;
				MonteCarlo<bool> loi_;
				loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
				loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
				if(loi_.tirage()){
					foreach(Combattant c2,creatures_act.cles()){
						if(c2.equipe()!=c.equipe()){
							continue;
						}
						if(creatures_act.valeur(c2).statut_pk()!="KO"){
							creatures_act.valeur(c2).statut_pk()="OK";
						}
					}
				}
			}
		}
	}
	foreach(PositionPlace p,voeu.cles()){
		QPair<uchar,QPair<bool,bool> >& valeur_=voeu.valeur(p);
		QList<Combattant> cbts_=positions_places.cles(p);
		if(cbts_.isEmpty()){
			continue;
		}
		if(valeur_.second.second){
			CreatureCombat& cr_c_=creatures_act.valeur(cbts_[0]);
			valeur_.second.second=false;
			if(valeur_.first<1){
				valeur_.first++;
			}
			if(cr_c_.statut_pk()!="KO"){
				Taux pv_soins_(0);
				cr_c_.soin_pv(cr_c_.pv_max()*Taux(1LL,2LL),pv_soins_,_d);
			}
		}else if(valeur_.second.first){
			if(valeur_.first<1){
				valeur_.first++;
			}else{
				valeur_.second.first=false;
				valeur_.first=0;
				CreatureCombat& cr_c_=creatures_act.valeur(cbts_[0]);
				if(cr_c_.statut_pk()!="KO"){
					Taux pv_soins_(0);
					cr_c_.soin_pv(cr_c_.pv_max()*Taux(1LL,2LL),pv_soins_,_d);
				}
			}
		}
	}
	if(climat.first.first!=""){
		if(!climat.second.second){
			if(climat.first.second<5||(existence_pk_eq_climat_non_embargo(_d)&&climat.first.second<8)){
				//il existe un pokemon ayant l'objet permettant d'augmenter le nombre de tour pour ce climat et pas sous embargo
				climat.first.second++;
			}else{
				climat.first.second=0;
				climat.second.first=false;
				climat.first.first="";
				foreach(Combattant c,creatures_act.cles()){
					CreatureCombat& cr_c_=creatures_act.valeur(c);
					FicheCapacite *f_capac_=cr_c_.fiche_capacite(_d);
					if(f_capac_&&f_capac_->chgt_type_clim().total()>0){
						cr_c_.types_pk().clear();
						cr_c_.types_pk()<<_d->val_pokedex().valeur(cr_c_.nom_pk_act())->typs();
					}
				}
			}
		}
	}
	attaques_equipes_.clear();
	attaques_equipes_<<"AIRE_FEU_HERBE";
	foreach(uchar e,nb_tour_attaque_equipe.cles()){
		foreach(QString a,nb_tour_attaque_equipe.valeur(e).cles()){
			if(!attaques_equipes_.contains(a)){
				continue;
			}
			if(!attaque_equipe(e,a).second){
				continue;
			}
			foreach(Combattant c,creatures_act.cles()){
				if(c.equipe()==e||positions_places.valeur(c).second==arriere){
					continue;
				}
				CreatureCombat& cr_c_=creatures_act.valeur(c);
				if(cr_c_.statut_pk()=="KO"){
					continue;
				}
				if(cr_c_.pv_restants_pk()*Taux(8)<=cr_c_.pv_max()){
					mise_a_ko(c,cr_c_,_d);
				}else{
					cr_c_.pv_restants_pk()-=cr_c_.pv_max()*Taux(1LL,8LL);
				}
			}
		}
	}
	if(valeur_climat()!=""){
		foreach(Combattant c,creatures_act.cles()){
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			CreatureCombat& cr_c_=creatures_act.valeur(c);
			if(cr_c_.statut_pk()=="KO"){
				continue;
			}
			FicheCapacite *f_capac_=cr_c_.fiche_capacite(_d);
			bool immu_climat_=false;
			if(f_capac_){
				if(f_capac_->gain_pv_clim().cles().contains(valeur_climat())){
					Taux tx_=f_capac_->gain_pv_clim().valeur(valeur_climat());
					if(tx_>Taux(0)){
						if(cr_c_.statut_pk()!="KO"){
							Taux pv_soins_(0);
							cr_c_.soin_pv(cr_c_.pv_max()*tx_,pv_soins_,_d);
						}
					}else{
						if(cr_c_.pv_restants_pk()+cr_c_.pv_max()*tx_<=Taux(0)){
							mise_a_ko(c,cr_c_,_d);
						}else{
							cr_c_.pv_restants_pk()+=cr_c_.pv_max()*tx_;
							QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_.patience_pk();
							if(patience_.second.second){
								patience_.second.first-=cr_c_.pv_max()*tx_;
							}
						}
					}
				}
				if(f_capac_->immu_cl().contains(valeur_climat())){
					immu_climat_=true;
				}
			}
			if(!immu_climat_){
				if(_d->val_types_immu().cles().contains("TYPES_IMMU_"+valeur_climat())){
					immu_climat_=!Utilitaire::intersection<QString>(_d->val_types_immu().valeur("TYPES_IMMU_"+valeur_climat()),cr_c_.types_pk()).isEmpty();
				}else{
					immu_climat_=true;
				}
			}
			if(!immu_climat_){
				Taux tx_(1LL,16LL);
				if(cr_c_.pv_restants_pk()-cr_c_.pv_max()*tx_<=Taux(0)){
					mise_a_ko(c,cr_c_,_d);
				}else{
					cr_c_.pv_restants_pk()-=cr_c_.pv_max()*tx_;
					QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_.patience_pk();
					if(patience_.second.second){
						patience_.second.first+=cr_c_.pv_max()*tx_;
					}
				}
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="KO"){
			continue;
		}
		foreach(Combattant c2,creatures_act.cles()){
			if(c2.equipe()==c.equipe()){
				continue;
			}
			CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
			if(cr_c_2_.statut_pk()=="KO"){
				continue;
			}
			if(!cr_c_2_.attaques_actives_ind("VAMPIGRAINE")){
				continue;
			}
			FicheCapacite *f_capac_2_=cr_c_2_.fiche_capacite(_d);
			if(f_capac_2_&&f_capac_2_->immu_deg_vampig()){
				continue;
			}
			Taux tx_(1LL,8LL);
			if(cr_c_.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
				ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_c_.fiche_objet(_d));
				if(obj_&&!obj_->mult_pv_drai().estNul()){
					tx_*=obj_->mult_pv_drai();
				}
			}
			Taux pv_=Utilitaire::max_min<Taux>(cr_c_2_.pv_restants_pk(),cr_c_2_.pv_max()*tx_).first;
			if(!cr_c_2_.types_pk().contains("PLANTE")){
				if(cr_c_2_.pv_restants_pk()-pv_<=Taux(0)){
					mise_a_ko(c2,cr_c_2_,_d);
				}else{
					cr_c_2_.pv_restants_pk()-=pv_;
					QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_2_.patience_pk();
					if(patience_.second.second){
						patience_.second.first+=pv_;
					}
				}
			}
			if(!attaque_equipe(c2.equipe(),"ANTI_SOIN").second){
				if(f_capac_2_&&f_capac_2_->mult_tx_deg_adv_abs()!=0){
					if(!cr_c_.types_pk().contains("PLANTE")){
						if(cr_c_.pv_restants_pk()-pv_<=Taux(0)){
							mise_a_ko(c,cr_c_,_d);
						}else{
							cr_c_.pv_restants_pk()-=pv_;
							QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_.patience_pk();
							if(patience_.second.second){
								patience_.second.first+=pv_;
							}
						}
					}
				}else{
					Taux pv_soignes_(0);
					cr_c_.soin_pv(pv_,pv_soignes_,_d);
				}
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="KO"){
			continue;
		}
		if(cr_c_.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
			ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_c_.fiche_objet(_d));
			if(obj_&&!obj_->gain_pv_t().estNul()){
				Taux pv_soignes_(0);
				cr_c_.soin_pv(cr_c_.pv_max()*obj_->gain_pv_t(),pv_soignes_,_d);
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="KO"){
			continue;
		}
		if(cr_c_.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
			ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_c_.fiche_objet(_d));
			if(obj_&&obj_->gain_pv_s().total()>0){
				QStringList types_communs_=Utilitaire::intersection<QString>(obj_->gain_pv_s().cles(),cr_c_.types_pk());
				QString cle_;
				Taux tx_;
				if(types_communs_.isEmpty()){
					tx_=obj_->gain_pv_s().valeur(cle_);
				}else{
					foreach(QString t,types_communs_){
						tx_+=obj_->gain_pv_s().valeur(t);
					}
				}
				if(tx_>=Taux(0)){
					Taux pv_soignes_(0);
					cr_c_.soin_pv(cr_c_.pv_max()*tx_,pv_soignes_,_d);
				}else{
					if(cr_c_.pv_restants_pk()+cr_c_.pv_max()*tx_<=Taux(0)){
						mise_a_ko(c,cr_c_,_d);
					}else{
						cr_c_.pv_restants_pk()+=cr_c_.pv_max()*tx_;
						QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_.patience_pk();
						if(patience_.second.second){
							patience_.second.first-=cr_c_.pv_max()*tx_;
						}
					}
				}
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="POISON_GRAVE"){
			cr_c_.gain_nb_tours_poison_grave();
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		FicheCapacite *f_capac_=cr_c_.fiche_capacite(_d);
		bool soin_poison_=false;
		if(f_capac_&&f_capac_->mult_deg_statut().cles().contains(cr_c_.statut_pk())){
			soin_poison_=f_capac_->mult_deg_statut().valeur(cr_c_.statut_pk())<Taux(0);
		}
		if(soin_poison_){
			Taux tx_(1LL,16LL);
			if(cr_c_.statut_pk()=="POISON_GRAVE"){
				tx_*=Taux(cr_c_.nb_tours_poison_grave_pk());
			}
			tx_*=-f_capac_->mult_deg_statut().valeur(cr_c_.statut_pk());
			Taux pv_soignes_(0);
			cr_c_.soin_pv(tx_*cr_c_.pv_max(),pv_soignes_,_d);
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="KO"){
			continue;
		}
		typedef QPair<Combattant,QString> CombattantPieg;
		foreach(CombattantPieg p,cr_c_.val_attaques_piegeantes()){
			if(positions_places.valeur(p.first).second==arriere){
				continue;
			}
			CreatureCombat& cr_c_2_=creatures_act.valeur(p.first);
			if(cr_c_2_.statut_pk()=="KO"){
				continue;
			}
			QPair<bool,uchar>& valeur_=cr_c_.att_pieg(p);
			if(valeur_.first){//immu_deg_att_pieg()
				FicheCapacite *f_capac_c_2_=cr_c_2_.fiche_capacite(_d);
				if(f_capac_c_2_&&f_capac_c_2_->immu_deg_att_pieg()){
					continue;
				}
				bool maximiser_tours_=false;
				if(cr_c_.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
					ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_c_.fiche_objet(_d));
					if(obj_&&obj_->nb_trs_pieg()){
					//(combattant[attaque_piegeante.nom,cible].nb_tours < 5 et non zone_magique.actif et non combattant.embargo_subi.actif et combattant.objet == ACCRO_GRIFFE)
						maximiser_tours_=true;
					}
				}
				bool degats_att_pieg_=false;
				if(maximiser_tours_){
					if(valeur_.second<(int)_d->val_attaques().valeur(p.second)->loi_rep_tour().maximum()){
						valeur_.second++;
						degats_att_pieg_=true;
					}else{
						valeur_=QPair<bool,uchar>(false,0);
					}
				}else if(CreatureCombat::tirage_effet_continuer(_d->val_attaques().valeur(p.second)->loi_rep_tour(),(long long)valeur_.second)){
					//combattant[attaque_piegeante.nom,cible].nb_tours < 2 ou  ou tirage_piegeante(combattant[attaque_piegeante.nom,cible].nb_tours,attaque_piegeante.loi)
					valeur_.second++;
					degats_att_pieg_=true;
				}
				if(degats_att_pieg_){
					Taux degats_=cr_c_2_.pv_max()*Taux(1LL,16LL);
					if(cr_c_.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
						ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_c_.fiche_objet(_d));
						if(obj_&&!obj_->mult_deg_pieg().estNul()){
							degats_*=obj_->mult_deg_pieg();
						}
					}
					if(cr_c_2_.pv_restants_pk()<=degats_){
						mise_a_ko(p.first,cr_c_2_,_d);
					}else{
						cr_c_2_.pv_restants_pk()-=degats_;
						QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_2_.patience_pk();
						if(patience_.second.second){
							patience_.second.first+=degats_;
						}
					}
				}
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="KO"){
			continue;
		}
		if(!cr_c_.clone_pk().estNul()){
			continue;
		}
		if(!cr_c_.peut_utiliser_objet(effet_global("ZONE_MAGIQUE").second)){
			continue;
		}
		ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(cr_c_.fiche_objet(_d));
		if(!obj_){
			continue;
		}
		FicheCapacite *f_capac_=cr_c_.fiche_capacite(_d);
		if(!obj_->deg_rec().estNul()&&(!f_capac_||!f_capac_->immu_deg_recul())){
			Taux degats_=cr_c_.pv_max()*Taux(1LL,10LL);
			if(cr_c_.pv_restants_pk()<=degats_){
				mise_a_ko(c,cr_c_,_d);
			}else{
				cr_c_.pv_restants_pk()-=degats_;
				QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_.patience_pk();
				if(patience_.second.second){
					patience_.second.first+=degats_;
				}
			}
		}
		if(obj_->statut_tr_lanc()=="BRULURE"&&traiter_reussite_seul_effet_statut(cr_c_,cr_c_.fiche_capacite(_d),c.equipe(),"BRULURE",false,_d)){
			cr_c_.statut_pk()="BRULURE";
		}
		if(obj_->statut_tr_lanc()=="POISON_GRAVE"&&traiter_reussite_seul_effet_statut(cr_c_,cr_c_.fiche_capacite(_d),c.equipe(),"POISON_GRAVE",false,_d)){
			cr_c_.statut_pk()="POISON_GRAVE";
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="KO"){
			continue;
		}
		FicheCapacite *f_capac_=cr_c_.fiche_capacite(_d);
		if(cr_c_.statut_pk()=="BRULURE"||cr_c_.statut_pk().startsWith("POISON")){//et combattant.capacite ne contient pas IMMU_DEGATS_BRULURE
			Taux degats_=Taux(1LL,8LL)*cr_c_.pv_max();
			if(f_capac_&&f_capac_->mult_deg_statut().cles().contains(cr_c_.statut_pk())){
				degats_*=f_capac_->mult_deg_statut().valeur(cr_c_.statut_pk());
			}
			if(cr_c_.statut_pk()=="POISON_GRAVE"){
				degats_*=Taux(cr_c_.nb_tours_poison_grave_pk());
			}
			if(degats_<=Taux(0)){
				continue;
			}
			if(cr_c_.pv_restants_pk()<=degats_){
				mise_a_ko(c,cr_c_,_d);
			}else{
				cr_c_.pv_restants_pk()-=degats_;
				QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_.patience_pk();
				if(patience_.second.second){
					patience_.second.first+=degats_;
				}
			}
		}else if(cr_c_.attaques_actives_ind("MAUDIT")){
			if(f_capac_&&f_capac_->immu_deg_maled()){
				continue;
			}
			Taux degats_=Taux(1LL,8LL)*cr_c_.pv_max();
			if(cr_c_.pv_restants_pk()<=degats_){
				mise_a_ko(c,cr_c_,_d);
			}else{
				cr_c_.pv_restants_pk()-=degats_;
				QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_.patience_pk();
				if(patience_.second.second){
					patience_.second.first+=degats_;
				}
			}
		}
		foreach(Combattant c2,creatures_act.cles()){
			if(positions_places.valeur(c2).second==arriere){
				continue;
			}
			CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
			if(cr_c_2_.statut_pk()!="SOMMEIL"){
				continue;
			}
			if(!cr_c_.att_active_cible("CAUCHEMAR",c2)){
				continue;
			}
			FicheCapacite *f_capac_2_=cr_c_2_.fiche_capacite(_d);
			if(f_capac_2_&&f_capac_2_->immu_deg_cauch()){
				cr_c_.att_active_cible("CAUCHEMAR",c2)=false;
				continue;
			}
			Taux degats_=Taux(1LL,4LL)*cr_c_2_.pv_max();
			if(cr_c_2_.pv_restants_pk()<=degats_){
				mise_a_ko(c2,cr_c_2_,_d);
			}else{
				cr_c_2_.pv_restants_pk()-=degats_;
				QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_2_.patience_pk();
				if(patience_.second.second){
					patience_.second.first+=degats_;
				}
			}
		}
		if(!f_capac_||f_capac_->deg_statu().second.estNul()){
			continue;
		}
		foreach(Combattant c2,creatures_act.cles()){
			if(positions_places.valeur(c2).second==arriere){
				continue;
			}
			CreatureCombat& cr_c_2_=creatures_act.valeur(c2);
			if(cr_c_2_.statut_pk()!=f_capac_->deg_statu().first){
				continue;
			}
			FicheCapacite *f_capac_2_=cr_c_2_.fiche_capacite(_d);
			if(f_capac_2_&&f_capac_2_->immu_cap().contains(cr_c_.capacite_pk_act())){
				continue;
			}
			Taux degats_=f_capac_->deg_statu().second*cr_c_2_.pv_max();
			if(cr_c_2_.pv_restants_pk()<=degats_){
				mise_a_ko(c2,cr_c_2_,_d);
			}else{
				cr_c_2_.pv_restants_pk()-=degats_;
				QPair<uchar,QPair<Taux,bool> >& patience_=cr_c_2_.patience_pk();
				if(patience_.second.second){
					patience_.second.first+=degats_;
				}
			}
		}
	}
	QStringList attaques_soins_;
	attaques_soins_<<"ANNEAU_HYDRO";
	attaques_soins_<<"RACINES";
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="KO"){
			continue;
		}
		if(attaque_equipe(adversaire(c.equipe()),"ANTI_SOIN").second){
			continue;
		}
		foreach(QString a,attaques_soins_){
			if(cr_c_.attaques_actives_ind(a)){
				Taux tx_;
				if(a=="ANNEAU_HYDRO"){
					tx_=Taux(1LL,16LL)*cr_c_.pv_max();
				}else{
					tx_=Taux(1LL,8LL)*cr_c_.pv_max();
				}
				Taux pv_soignes_(0);
				cr_c_.soin_pv(tx_,pv_soignes_,_d);
			}
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()=="KO"){
			continue;
		}
		foreach(Combattant c2,creatures_act.cles()){
			QPair<QString,QPair<bool,uchar> >& entrave_=cr_c_.cible_atts(QPair<QString,Combattant>("ENCORE",c2));
			if(entrave_.second.first){
				if(CreatureCombat::tirage_effet_fin_tour("ENCORE",entrave_.second.second,_d)){
					entrave_.second.second++;
				}else{
					entrave_.second=QPair<bool,uchar>(false,0);
					entrave_.first="";
				}
			}
		}
		QPair<uchar,bool>& eff_=cr_c_.attaques_actives_def("PROVOC");
		if(eff_.second){
			if(CreatureCombat::tirage_effet_continuer(_d->val_attaques().valeur("PROVOC")->loi_rep_tour(),(long long)eff_.first)){
				eff_.first++;
			}else{
				eff_=QPair<uchar,bool>(0,false);
			}
		}
	}
	vengeance_actif.valeur(ut).first=vengeance_actif.valeur(ut).second;
	vengeance_actif.valeur(adv).first=vengeance_actif.valeur(adv).second;
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.statut_pk()!="KO"){
			cr_c_.gain_nb_tours_terrain_pk();
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		if(cr_c_.att_choisie()!=""){
			cr_c_.der_att_lancee()=cr_c_.att_choisie();
		}
	}
}


Taux ElementsCombat::calcul_coeff_capture(Ball *_ball,bool _pk_capt,bool _peche,const CreatureCombat& _cr,Donnees *_d)const{//renvoie un nombre rationnel entre 0 et 1
	//si modele == CLASSIQUE ou adversaire.pv_restants * 4 >= adversaire.pv_max
	Taux bs_(1);
	if(_cr.statut_pk()=="PARALYSIE"||_cr.statut_pk()=="BRULURE"||_cr.statut_pk()=="POISON"||_cr.statut_pk()=="POISON_GRAVE"){
		bs_*=Taux(3LL,2LL);
	}else if(_cr.statut_pk()=="SOMMEIL"||_cr.statut_pk()=="GEL"){
		bs_*=Taux(2);
	}
	/*TAUX_FIXE	Le taux de capture sera toujours de $1.
	TAUX_NIVEAUX	Le taux de capture sera de $1, si le rapport du niveau du pokémon de l'utilisateur sur le combat sur le niveau du pokémon sauvage est compris entre $2 et $3.
	TAUX_PECHE	Le taux de capture sera de $1, si l'utilisateur a pêché.
	TAUX_PIERRE_EVO	Le taux de capture sera de $1, si le pokémon sauvage possède une évolution avec la pierre évolutive $1.
	TAUX_GENRE	Si le pokémon de l'utilisateur sur le terrain et le pokémon sauvage ont un genre, et que leurs genres sont opposés, alors le taux de capture sera de $1.
	TAUX_MASSE	Si le rapport de la masse du pokémon sauvage sur $4 est compris entre $2 et $3, alors le taux de capture sera de $1.
	TAUX_VITESSE	Si le rapport de la vitesse de base du pokémon sauvage sur $4 est compris entre $2 et $3, alors le taux de capture sera de $1.
	TAUX_DEJA_CAPTURE	Si le pokémon suavage avait déjà été obtenu par différents moyens, alors le taux de capture sera de $1.
	TAUX_TEMPS	Si le nombre de tours sur le terrain depuis le début du combat est compris entre $2 et $3, alors le taux de capture sera de $1.
	TAUX_NIVEAU_ADV	Si le niveau du pokémon suavage est compris entre $2 et $3, alors le taux de capture sera de $1.
	TAUX_TYPES	Si le pokémon possède les types $1, alors le taux de capture sera de $2.
	TAUX_LIEU	Si le type de lieu du combat est $1, alors le taux de capture sera de $2.*/
	Taux bb_(1);
	CreatureCombat cr_ut_=creatures_act.valeur(positions_places.cles(QPair<uchar,uchar>(ut,0))[0]);
	FichePokemon *f_pk_=_d->val_pokedex().valeur(_cr.nom_pk());
	//si ball.type_b n'est pas vide
	if(!_ball->tx_fix().estNul()){
		bb_*=_ball->tx_fix();
	}
	if(_ball->tx_niv().total()>0){
		Taux rapport_((long long)cr_ut_.niveau_pk(),(long long)_cr.niveau_pk());
		typedef QPair<Taux,Taux> Intervalle;
		foreach(Intervalle i,_ball->tx_niv().cles()){
			if(rapport_>=i.first&&rapport_<i.second){
				bb_*=_ball->tx_niv().valeur(i);
			}
		}
	}
	if(_ball->tx_pec().total()>0){
		if(_ball->tx_pec().cles().contains(_peche)){
			bb_*=_ball->tx_pec().valeur(_peche);
		}
	}
	foreach(QString e,f_pk_->evos().cles()){
		EvolutionPierreEvolutive *e_=qobject_cast<EvolutionPierreEvolutive*>(f_pk_->evos().valeur(e));
		if(e_&&_ball->tx_pier_evo().first.contains(e_->nom_pierre())){
			bb_*=_ball->tx_pier_evo().second;
		}
	}
	if(_ball->tx_gen().total()>0){
		if(_cr.genre_pk()!="ASSEXUE"&&cr_ut_.genre_pk()!="ASSEXUE"){
			if(_ball->tx_gen().cles().contains(_cr.genre_pk()!=cr_ut_.genre_pk())){
				bb_*=_ball->tx_gen().valeur(_cr.genre_pk()!=cr_ut_.genre_pk());
			}
		}
	}
	if(_ball->tx_m().total()>0){
		Taux rapport_=f_pk_->m_pk()/_d->val_masse_moy();//((long long)cr_ut_.niveau_pk(),(long long)_cr.niveau_pk())
		typedef QPair<Taux,Taux> Intervalle;
		foreach(Intervalle i,_ball->tx_m().cles()){
			if(rapport_>=i.first&&rapport_<i.second){
				bb_*=_ball->tx_m().valeur(i);
			}
		}
	}
	if(_ball->tx_v().total()>0){
		Taux rapport_(f_pk_->stat_ev().valeur("VITESSE").first);//((long long)cr_ut_.niveau_pk(),(long long)_cr.niveau_pk())
		typedef QPair<Taux,Taux> Intervalle;
		foreach(Intervalle i,_ball->tx_v().cles()){
			if(rapport_>=i.first&&rapport_<i.second){
				bb_*=_ball->tx_v().valeur(i);
			}
		}
	}
	if(_ball->tx_capt().total()>0){
		if(_ball->tx_capt().cles().contains(_pk_capt)){
			bb_*=_ball->tx_capt().valeur(_pk_capt);
		}
	}
	if(_ball->tx_tps().total()>0){
		typedef QPair<uchar,uchar> Intervalle;
		foreach(Intervalle i,_ball->tx_tps().cles()){
			if(nb_tours_terrain>=i.first&&nb_tours_terrain<i.second){
				bb_*=_ball->tx_tps().valeur(i);
			}
		}
	}
	if(_ball->niv_adv().total()>0){
		typedef QPair<uchar,uchar> Intervalle;
		foreach(Intervalle i,_ball->niv_adv().cles()){
			if(_cr.niveau_pk()>=i.first&&_cr.niveau_pk()<i.second){
				bb_*=_ball->niv_adv().valeur(i);
			}
		}
	}
	foreach(QString t,f_pk_->typs()){
		if(_ball->tx_types().first.contains(t)){
			bb_*=_ball->tx_types().second;
		}
	}
	if(_ball->tx_lieu().total()>0){
		foreach(QString l,_ball->tx_lieu().cles()){
			if(l==type_environnement){
				bb_*=_ball->tx_lieu().valeur(l);
			}
		}
	}
	//tx_lieu()
	//niv_adv()
	//tx_capt()
	//
	//tx_m()
	//fin si
	Taux taux_capt_adv_=f_pk_->tx_capt();
	Taux c_=Taux(4)*(Taux(3)*_cr.pv_max()-Taux(2)*_cr.pv_restants_pk())*taux_capt_adv_*bb_*bs_;
	Taux d_=Taux(12)*_cr.pv_max();
	if(c_>=d_*Taux(255)||(_cr.pv_restants_pk()<=Taux(1)&&!diff.r_autorise_ko_capture())){
		return Taux(1);
	}
	Taux racine_=(c_*(Taux(255)*d_)^Entier(3)).racine_abs(4);
	Taux b_=Utilitaire::max_min<Taux>(racine_+Taux(1),Entier(255)*d_.partie_entiere()).second/(Taux(255)*Taux(d_.partie_entiere()));
	//b <- min(257*(E(rac(255^3*c*d^3,4))+1),65535*E(d))/(65535*E(d))//(c/(255*d)).racine_abs(4)
	//b <- min(,255*E(d))/(255*E(d))//(c/(255*d)).racine_abs(4)
	//min(E((255^3*c*d^3).racine_abs(4))+1,255*E(d))/(255*E(d))
	//E(rac(255^3*c*d^3,4))+1
	return b_;
	//retour 1 cas autre
}

bool ElementsCombat::cas_switch_force(const Combattant& _lc,CreatureCombat& _lanceur,const Combattant& _cb,CreatureCombat& _cible,Donnees *_d){
	bool continuer_=true;
	if(type_combat!="SAUVAGE"){
		int nb_=0;
		FicheAttaque *f_att_=_d->val_attaques().valeur(_lanceur.att_choisie());
		if(f_att_->cat()!="AUTRE"){
			foreach(Combattant c,creatures_act.cles()){
				if(c.equipe()!=_lc.equipe()&&positions_places.valeur(c).second==arriere){
					nb_++;
				}
			}
			if(nb_==0){
				return continuer_;
			}
		}
		if(_cible.att_choisie()!="REFLET_MAGIK"||!_cible.att_reussie()||f_att_->cat()!="AUTRE"){
			_cible.non_switch_force_pk()=false;
			Combattant choix_=tirage_envoi(_cb.equipe());
			retrait(_cb,_cible,_d);
			positions_places_bis.valeur(choix_).second=_cb.position();
			positions_places.valeur(choix_).second=_cb.position();
			positions_places_bis.valeur(_cb).second=arriere;
			positions_places.valeur(_cb).second=arriere;
			numeros_front.removeOne(_cb);
			numeros_front<<choix_;
			CreatureCombat& _cr_choix=creatures_act.valeur(choix_);
			envoi(choix_,_cr_choix,true,_d,_lc,true);
			intimidation(_cr_choix.fiche_capacite(_d),adversaire(choix_.equipe()),_d);
		}else if(existence_pk_arriere_non_ko(_lc)){
			_lanceur.non_switch_force_pk()=false;
			Combattant choix_=tirage_envoi(_lc.equipe());
			retrait(_lc,_lanceur,_d);
			numeros_front.removeOne(_lc);
			numeros_front<<choix_;
			positions_places.valeur(choix_).second=_cb.position();
			positions_places.valeur(_lc).second=arriere;
			CreatureCombat& _cr_choix=creatures_act.valeur(choix_);
			envoi(choix_,_cr_choix,true,_d,_cb,true);
			intimidation(_cr_choix.fiche_capacite(_d),adversaire(choix_.equipe()),_d);
		}
	}else{
		//TODO fin_combat
		continuer_=false;
	}
	return continuer_;
}

uchar ElementsCombat::tour_combat(Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d){
	if(nb_tours_terrain<255){
		nb_tours_terrain++;
	}
	numeros_front.clear();
	commentaire_recent="";
	vengeance_actif.valeur(ut).second=false;
	vengeance_actif.valeur(adv).second=false;
	if(type_combat=="SAUVAGE"){
	//TODO si le combat est contre un pokemon sauvage et action != switch
	//	nb_fuite <- 0
	}
	lanceur_par_ici.valeur(ut)=arriere;
	lanceur_par_ici.valeur(adv)=arriere;
	nb_utilisation_attaques.valeur(QPair<QString,uchar>("CHANT_CANON",ut))=0;
	nb_utilisation_attaques.valeur(QPair<QString,uchar>("CHANT_CANON",adv))=0;
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second!=arriere){
			numeros_front<<c;
		}
		lanceur_saisie.valeur(c)=Combattant(arriere,arriere);
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		cr_c_.non_switch_force_pk()=true;
		cr_c_.att_deg_subie().first=QPair<Taux,Taux>(Taux(0),Taux(0));
		cr_c_.att_reussie()=false;
		cr_c_.peur_pk()=false;
		cr_c_.a_joue_pk()=false;
		if(c.equipe()==adv&&type_combat=="SAUVAGE"){
			QPair<QString,QPair<Combattant,Combattant> > choix_=choix_ia_attaque(_d).valeur(c);
			cr_c_.act_choisie()="ATTAQUE";
			cr_c_.att_choisie()=choix_.first;
			cr_c_.cibles().clear();
			cr_c_.cibles()<<QPair<uchar,uchar>(ut,0);
		}
	}
	uchar nb_=0;
	Combattant der_lanceur_(arriere,arriere);
	Combattant cible_(arriere,arriere);
	Combattant inex_(arriere,arriere);
	bool zone_magique_=effet_global("ZONE_MAGIQUE").second;
	bool distorsion_=effet_global("DISTORSION").second;
	forever{
		if(der_lanceur_!=inex_&&(cible_=chercher_cible_apres_vous(der_lanceur_,_d))!= inex_){
			der_lanceur_=cible_;
		}else{
			QList<Combattant> ceux_devant_jouer_=trier_ordre_non_joue(false,_d);
			if(ceux_devant_jouer_.isEmpty()){
				ceux_devant_jouer_=trier_ordre_non_joue(true,_d);
			}
			if(ceux_devant_jouer_.isEmpty()){
				break;
			}
			QList<Combattant> ceux_devant_jouer_2_;
			ceux_devant_jouer_2_<<ceux_devant_jouer_[0];
			//int indice_ch_=-1
			CreatureCombat& cr_c_pre_=creatures_act.valeur(ceux_devant_jouer_[0]);
			FicheCapacite *f_capac_pre_=cr_c_pre_.fiche_capacite(_d);
			ObjetAttachableCombat *obj1_=NULL;
			bool peut_att_der_1_=false;
			bool lent1_=f_capac_pre_&&f_capac_pre_->lent();
			if(cr_c_pre_.objet()!=""){
				obj1_=qobject_cast<ObjetAttachableCombat*>(cr_c_pre_.fiche_objet(_d));
				peut_att_der_1_=cr_c_pre_.peut_utiliser_objet(zone_magique_)&&obj1_&&obj1_->att_der();
			}
			QString action_=cr_c_pre_.act_choisie();
			QString attaque_=cr_c_pre_.att_choisie();
			if(attaque_=="POURSUITE"&&creatures_act.valeur(positions_places.cles(cr_c_pre_.cibles()[0])[0]).act_choisie()=="SWITCH"){
				for(int i=1;i<ceux_devant_jouer_.size();i++){
					CreatureCombat& cr_c_pre_2_=creatures_act.valeur(ceux_devant_jouer_[i]);
					QString attaque_2_=cr_c_pre_2_.att_choisie();
					if(attaque_2_=="POURSUITE"&&creatures_act.valeur(positions_places.cles(cr_c_pre_2_.cibles()[0])[0]).act_choisie()=="SWITCH"){
						FicheCapacite *f_capac_pre_2_=cr_c_pre_2_.fiche_capacite(_d);
						ObjetAttachableCombat *obj2_=NULL;
						bool peut_att_der_2_=false;
						bool lent2_=f_capac_pre_2_&&f_capac_pre_2_->lent();
						if(cr_c_pre_2_.objet()!=""){
							obj2_=qobject_cast<ObjetAttachableCombat*>(cr_c_pre_2_.fiche_objet(_d));
							peut_att_der_2_=cr_c_pre_.peut_utiliser_objet(zone_magique_)&&obj2_&&obj2_->att_der();
						}
						if(lent1_==lent2_&&peut_att_der_1_==peut_att_der_2_){
							ceux_devant_jouer_2_<<ceux_devant_jouer_[i];
						}else{
							break;
						}
					}else{
						break;
					}
				}
			}else if(action_!="SOIN"&&action_!="SWITCH"){
				FicheAttaque *f_att_1_=_d->val_attaques().valeur(attaque_);
				qint8 nb1_=0;
				if(f_capac_pre_&&f_capac_pre_->som_pr().cles().contains(f_att_1_->cat())){
					nb1_+=f_capac_pre_->som_pr().valeur(f_att_1_->cat());
				}
				qint8 somme_=f_att_1_->prio()+nb1_;
				for(int i=1;i<ceux_devant_jouer_.size();i++){
					CreatureCombat& cr_c_pre_2_=creatures_act.valeur(ceux_devant_jouer_[i]);
					QString action_2_=cr_c_pre_2_.act_choisie();
					if(action_2_!="SOIN"&&action_2_!="SWITCH"){
						FicheAttaque *f_att_2_=_d->val_attaques().valeur(attaque_);
						FicheCapacite *f_capac_pre_2_=cr_c_pre_2_.fiche_capacite(_d);
						qint8 nb2_=0;
						if(f_capac_pre_2_&&f_capac_pre_2_->som_pr().cles().contains(f_att_2_->cat())){
							nb2_+=f_capac_pre_2_->som_pr().valeur(f_att_2_->cat());
						}
						ObjetAttachableCombat *obj2_=NULL;
						bool peut_att_der_2_=false;
						bool lent2_=f_capac_pre_2_&&f_capac_pre_2_->lent();
						if(cr_c_pre_2_.objet()!=""){
							obj2_=qobject_cast<ObjetAttachableCombat*>(cr_c_pre_2_.fiche_objet(_d));
							peut_att_der_2_=cr_c_pre_.peut_utiliser_objet(zone_magique_)&&obj2_&&obj2_->att_der();
						}
						qint8 somme_2_=f_att_2_->prio()+nb2_;
						if(somme_==somme_2_){
							if(lent1_==lent2_&&peut_att_der_1_==peut_att_der_2_){
								ceux_devant_jouer_2_<<ceux_devant_jouer_[i];
							}else{
								break;
							}
						}else{
							break;
						}
					}
				}
			}else if(action_=="SWITCH"){
				for(int i=1;i<ceux_devant_jouer_.size();i++){
					CreatureCombat& cr_c_pre_2_=creatures_act.valeur(ceux_devant_jouer_[i]);
					QString action_2_=cr_c_pre_2_.act_choisie();
					if(action_2_=="SWITCH"){
						ceux_devant_jouer_2_<<ceux_devant_jouer_[i];
					}else{
						break;
					}
				}
			}
			QList<QList<Combattant> > liste_liste_tmp_;
			int i1_=0;
			int j1_=0;
			while(i1_<ceux_devant_jouer_2_.size()){
				Combattant elt_=ceux_devant_jouer_2_[i1_];
				CreatureCombat& cr_e_=creatures_act.valeur(elt_);
				Taux vitesse1_=cr_e_.vitesse(attaque_equipe(adversaire(elt_.equipe()),"AIRE_EAU_HERBE").second,zone_magique_,attaque_equipe(elt_.equipe(),"VENT_ARRIERE").second,climat,_d);
				liste_liste_tmp_<<QList<Combattant>();
				liste_liste_tmp_.last()<<elt_;
				j1_=i1_+1;
				while(j1_<ceux_devant_jouer_2_.size()){
					Combattant elt2_=ceux_devant_jouer_2_[j1_];
					CreatureCombat& cr_e_2_=creatures_act.valeur(elt2_);
					Taux vitesse2_=cr_e_2_.vitesse(attaque_equipe(adversaire(elt2_.equipe()),"AIRE_EAU_HERBE").second,zone_magique_,attaque_equipe(elt2_.equipe(),"VENT_ARRIERE").second,climat,_d);
					if(vitesse1_!=vitesse2_){
						break;
					}
					liste_liste_tmp_.last()<<elt2_;
					j1_++;
				}
				if(j1_==ceux_devant_jouer_2_.size()){
					break;
				}
				i1_=j1_;
			}
			QList<Combattant> liste_tmp2_;
			foreach(QList<Combattant> l,liste_liste_tmp_){
				QList<Combattant> l_=l;
				int i2_=0;
				while(i2_<l_.size()-1){
					MonteCarloNombre loi_;
					for(int i=0;i<l_.size();i++){
						loi_.ajouter_event(QPair<Taux,Entier>(i,Entier(1)));
					}
					liste_tmp2_<<l_.takeAt(loi_.tirage());
				}
				liste_tmp2_<<l_[0];
			}
			ceux_devant_jouer_2_=liste_tmp2_;
			;
			cr_c_pre_=creatures_act.valeur(ceux_devant_jouer_2_[0]);
			f_capac_pre_=cr_c_pre_.fiche_capacite(_d);
			lent1_=f_capac_pre_&&f_capac_pre_->lent();
			if(cr_c_pre_.objet()!=""){
				obj1_=qobject_cast<ObjetAttachableCombat*>(cr_c_pre_.fiche_objet(_d));
				peut_att_der_1_=cr_c_pre_.peut_utiliser_objet(zone_magique_)&&obj1_&&obj1_->att_der();
			}
			action_=cr_c_pre_.act_choisie();
			attaque_=cr_c_pre_.att_choisie();
			if(action_=="SWITCH"){
				ceux_devant_jouer_2_=QList<Combattant>()<<ceux_devant_jouer_2_[0];
			}
			if(ceux_devant_jouer_2_.size()>1){
				QList<Combattant> ceux_devant_jouer_3_;
				for(int i=0;i<ceux_devant_jouer_2_.size();i++){
					//TODO plus generique Taux loi_pr() dans Baie
					CreatureCombat& cr_c_pre_2_=creatures_act.valeur(ceux_devant_jouer_2_[i]);
					if(cr_c_pre_2_.objet()=="BAIE_CHERIM"){
						ceux_devant_jouer_3_<<ceux_devant_jouer_2_[i];
					}
				}
				if(ceux_devant_jouer_3_.isEmpty()){
					for(int i=0;i<ceux_devant_jouer_2_.size();i++){
						//TODO plus generique MonteCarlo<bool> loi_prem() dans Baie
						CreatureCombat& cr_c_pre_2_=creatures_act.valeur(ceux_devant_jouer_2_[i]);
						if(cr_c_pre_2_.objet()=="VIVE_GRIFFE"){
							ceux_devant_jouer_3_<<ceux_devant_jouer_2_[i];
						}
					}
					if(ceux_devant_jouer_3_.isEmpty()){
						der_lanceur_=ceux_devant_jouer_2_[0];
					}else{
						CreatureCombat& cr_c_pre_2_=creatures_act.valeur(ceux_devant_jouer_3_[0]);
						if(cr_c_pre_2_.objet()=="VIVE_GRIFFE"){
							der_lanceur_=ceux_devant_jouer_3_[0];
						}else{
							int nb_tir_=0;
							forever{
								if(nb_tir_==ceux_devant_jouer_3_.size()){
									der_lanceur_=ceux_devant_jouer_3_[0];
									break;
								}
								bool att_der_=CreatureCombat::tirage_vive_griffe(_d);
								if(!att_der_){
									der_lanceur_=ceux_devant_jouer_3_[nb_tir_];
									break;
								}
								nb_tir_++;
							}
						}
					}
				}else{
					der_lanceur_=ceux_devant_jouer_3_[0];
					if(cr_c_pre_.objet()!="BAIE_CHERIM"){
						/*der_lanceur.utilise_baie <- vrai TODO
						der_lanceur.vient_de_perdre_objet <- vrai*/
					}
				}
			}else{
				der_lanceur_=ceux_devant_jouer_2_[0];
			}
		}
		CreatureCombat& cr_c_pre_=creatures_act.valeur(der_lanceur_);
		bool continuer_=lancer(der_lanceur_,cr_c_pre_,_d);
		cr_c_pre_.a_joue_pk()=true;
		if(!continuer_){
			return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
		}
		QList<Combattant> fronts_ut_;
		foreach(Combattant c,creatures_act.cles()){
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			if(c.equipe()!=ut){
				continue;
			}
			if(creatures_act.valeur(c).statut_pk()!="KO"){
				fronts_ut_<<c;
				continue;
			}
			positions_places.valeur(c).second=arriere;
		}
		if(existence_combattant_ut_non_ko_contre_1_adv()){
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				if(c.equipe()==ut){
					continue;
				}
				if(creatures_act.valeur(c).statut_pk()!="KO"){
					continue;
				}
				QList<uchar> liste_=combattants_contre_adv.valeur(c.position());
				QList<Combattant> combattants_ut_;
				foreach(uchar p,liste_){
					combattants_ut_<<Combattant(ut,p);
				}
				calcul_experience_ev(combattants_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
			}
		}else if(existence_ut_non_ko()){
			QList<Combattant> equipe_ut_;
			foreach(Combattant c,creatures_act.cles()){
				if(c.equipe()!=ut){
					continue;
				}
				equipe_ut_<<c;
			}
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				if(c.equipe()==ut){
					continue;
				}
				if(creatures_act.valeur(c).statut_pk()!="KO"){
					continue;
				}
				calcul_experience_ev(equipe_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
			}
		}
		foreach(Combattant c,creatures_act.cles()){
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			if(c.equipe()==ut){
				continue;
			}
			if(creatures_act.valeur(c).statut_pk()!="KO"){
				continue;
			}
			positions_places.valeur(c).second=arriere;
		}
		QStringList attaques_ressies_;
		foreach(Combattant c,creatures_act.cles()){
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			if(c.equipe()!=der_lanceur_.equipe()){
				continue;
			}
			CreatureCombat& cr_c_=creatures_act.valeur(c);
			if(cr_c_.att_reussie()){
				attaques_ressies_<<cr_c_.att_choisie();
			}
		}
		if(attaques_ressies_.contains("AIRE_D_EAU")&&attaques_ressies_.contains("AIRE_DE_FEU")){
			attaque_equipe(der_lanceur_.equipe(),"AIRE_EAU_FEU")=QPair<uchar,bool>(0,true);
		}
		if(attaques_ressies_.contains("AIRE_D_EAU")&&attaques_ressies_.contains("AIRE_D_HERBE")){
			attaque_equipe(der_lanceur_.equipe(),"AIRE_EAU_HERBE")=QPair<uchar,bool>(0,true);
		}
		if(attaques_ressies_.contains("AIRE_D_FEU")&&attaques_ressies_.contains("AIRE_DE_HERBE")){
			attaque_equipe(der_lanceur_.equipe(),"AIRE_FEU_HERBE")=QPair<uchar,bool>(0,true);
		}

		//lanceurs.ajouter(lanceur)
		;
	}
	//pour chaque lanceur//ayant action_choisie non vide // autre que le premier
	//fin pour
		//plus tard fin de la boucle des lanceurs autre que le premier
	return traiter_apres_tour(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
}


bool ElementsCombat::lancer(const Combattant& _lc,CreatureCombat& _lanceur,Donnees *_d){
	bool continuer_=true;
	QString action_=_lanceur.act_choisie();
	QString attaque_=_lanceur.att_choisie();
	commentaire_recent+=_lanceur.nom_pk_act()+" utilise "+attaque_+"\n";
	if(attaque_=="TELEPORT"&&type_combat=="SAUVAGE"){
	//si action_choisie == TELEPORT et le combat est contre un pokemon sauvage
		continuer_=false;
		//fin d'un combat
	}else if(action_=="SWITCH"){
		retrait(_lc,_lanceur,_d);
		Combattant choix_=_lanceur.remplacant();
		numeros_front.removeOne(_lc);
		numeros_front<<choix_;
		positions_places_bis.valeur(choix_).second=positions_places_bis.valeur(_lc).second;
		positions_places.valeur(choix_).second=positions_places.valeur(_lc).second;
		positions_places_bis.valeur(_lc).second=arriere;
		positions_places.valeur(_lc).second=arriere;
		CreatureCombat& cr_choix_=creatures_act.valeur(choix_);
		envoi(choix_,cr_choix_,true,_d);
		FicheCapacite *f_capac_=cr_choix_.fiche_capacite(_d);
		if(f_capac_){
			intimidation(f_capac_,adversaire(_lc.equipe()),_d);
		}
		_lanceur.act_choisie()="";
	}else if(action_=="SOIN"){
		Baie *baie_=qobject_cast<Baie*>(_d->val_objets().valeur(attaque_));
		if(baie_){
			Taux pv_soignes_(0);
			_lanceur.activer_baie(baie_,_d,pv_soignes_);
		}
		Soin *soin_=qobject_cast<Soin*>(_d->val_objets().valeur(attaque_));
		if(soin_){
			if(soin_->soin_eq()){
				bool soin_fait_=false;
				foreach(Combattant c,creatures_act.cles()){
					if(c.equipe()!=_lc.equipe()){
						continue;
					}
					CreatureCombat& cr_c_=creatures_act.valeur(c);
					Taux pv_soignes_=cr_c_.soin_tout_pv();
					soin_fait_|=!pv_soignes_.estNul();
					HashMap<QString,uchar> attaques_=cr_c_.soin_pp();
					Entier somme_(0);
					foreach(QString a,attaques_.cles()){
						somme_+=Entier(attaques_.valeur(a));
					}
					soin_fait_|=!somme_.estNul();
					soin_fait_|=cr_c_.statut_pk()!="OK";
					cr_c_.statut_pk()="OK";
				}
				if(soin_fait_){
					foreach(Combattant c,creatures_act.cles()){
						if(c.equipe()!=_lc.equipe()){
							continue;
						}
						CreatureCombat& cr_c_=creatures_act.valeur(c);
						HashMap<QString,QList<QPair<uchar,Taux> > >& objets_=cr_c_.objets_pk();
						QList<QPair<uchar,Taux> >& quantites_=objets_.valeur(attaque_);
						quantites_[0].first--;
					}
				}
			}else if(qobject_cast<SoinPV*>(soin_)){
				SoinPV *soin_pv_=qobject_cast<SoinPV*>(soin_);
				if(_lanceur.pv_restants_pk()<_lanceur.pv_max()){
					_lanceur.gain_bonheur(soin_pv_,_d);
					if(soin_pv_->pv_m_res().estNul()){
						Taux pv_soignes_(0);
						_lanceur.soin_pv(_lanceur.pv_max(),pv_soignes_,_d);
						foreach(Combattant c,creatures_act.cles()){
							if(c.equipe()!=_lc.equipe()){
								continue;
							}
							CreatureCombat& cr_c_=creatures_act.valeur(c);
							HashMap<QString,QList<QPair<uchar,Taux> > >& objets_=cr_c_.objets_pk();
							QList<QPair<uchar,Taux> >& quantites_=objets_.valeur(attaque_);
							quantites_[0].first--;
						}
					}else{
						Taux pv_soignes_(0);
						Taux somme_quantites_(0);
						typedef QPair<uchar,Taux> EffectifPV;
						foreach(EffectifPV e,_lanceur.objets_pk().valeur(attaque_)){
							somme_quantites_+=Taux((long long)e.first)*e.second;
						}
						if(somme_quantites_>=soin_pv_->pv_m_res()){
							_lanceur.soin_pv(soin_pv_->pv_m_res(),pv_soignes_,_d);
						}else{
							_lanceur.soin_pv(somme_quantites_,pv_soignes_,_d);
						}
						foreach(Combattant c,creatures_act.cles()){
							if(c.equipe()!=_lc.equipe()){
								continue;
							}
							CreatureCombat& cr_c_=creatures_act.valeur(c);
							HashMap<QString,QList<QPair<uchar,Taux> > >& objets_=cr_c_.objets_pk();
							QList<EffectifPV>& quantites_=objets_.valeur(attaque_);
							int ind_=0;
							int ind_2_=0;
							Taux pv_dep_(0);
							bool sortir_db_boucle_=false;
							foreach(EffectifPV e,quantites_){
								ind_=0;
								for(int i=0;i<e.first;i++){
									if(pv_dep_>=pv_soignes_){
										sortir_db_boucle_=true;
										break;
									}
									pv_dep_+=e.second;
									ind_++;
								}
								if(sortir_db_boucle_){
									break;
								}
								ind_2_++;
							}
							int i_=0;
							while(i_<ind_2_){
								quantites_.removeAt(0);
								i_++;
							}
							if(!quantites_.isEmpty()){
								quantites_[0].first-=ind_;
								/*if(quantites_[0].first==0){
									quantites_.removeAt(0)
								}*/
							}
							if(quantites_.isEmpty()){
								quantites_<<EffectifPV(0,Taux(0));
							}
							i_=-1;
							for(int i=0;i<quantites_.size();i++){
								if(quantites_[i].second==pv_dep_-pv_soignes_){
									i_=i;
								}
							}
							if(pv_dep_!=pv_soignes_){
								if(i_<0){
									quantites_.prepend(EffectifPV(1,pv_dep_-pv_soignes_));
								}else{
									quantites_[i_].first++;
								}
							}
						}
					}
				}
			}else if(qobject_cast<SoinPVStatut*>(soin_)){
				SoinPVStatut *soin_pv_=qobject_cast<SoinPVStatut*>(soin_);
				if(_lanceur.pv_restants_pk()<_lanceur.pv_max()||(_lanceur.statut_pk()!="OK"&&_lanceur.statut_pk()!="KO")){
					_lanceur.gain_bonheur(soin_pv_,_d);
					Taux pv_soignes_(0);
					_lanceur.soin_pv(soin_pv_->tx_soin()*_lanceur.pv_max(),pv_soignes_,_d);
					_lanceur.statut_pk()="OK";
					foreach(Combattant c,creatures_act.cles()){
						if(c.equipe()!=_lc.equipe()){
							continue;
						}
						CreatureCombat& cr_c_=creatures_act.valeur(c);
						typedef QPair<uchar,Taux> EffectifPV;
						HashMap<QString,QList<EffectifPV> >& objets_=cr_c_.objets_pk();
						QList<EffectifPV>& quantites_=objets_.valeur(attaque_);
						quantites_[0].first--;
					}
				}
			}else if(qobject_cast<SoinStatut*>(soin_)){
				SoinStatut *soin_pv_=qobject_cast<SoinStatut*>(soin_);
				if(_lanceur.statut_pk()!="OK"&&_lanceur.statut_pk()!="KO"){
					_lanceur.gain_bonheur(soin_pv_,_d);
					_lanceur.statut_pk()="OK";
					foreach(Combattant c,creatures_act.cles()){
						if(c.equipe()!=_lc.equipe()){
							continue;
						}
						CreatureCombat& cr_c_=creatures_act.valeur(c);
						typedef QPair<uchar,Taux> EffectifPV;
						HashMap<QString,QList<EffectifPV> >& objets_=cr_c_.objets_pk();
						QList<EffectifPV>& quantites_=objets_.valeur(attaque_);
						quantites_[0].first--;
					}
				}
			}else if(qobject_cast<SoinPP*>(soin_)){
				SoinPP *soin_pp_=qobject_cast<SoinPP*>(soin_);
				QPair<QString,QString> effet_=soin_pp_->effs_se();
				if(effet_.first=="MAX"&&effet_.second=="MAX"){
					HashMap<QString,uchar> attaques_soignes_=_lanceur.soin_pp();
					foreach(Combattant c,creatures_act.cles()){
						if(c.equipe()!=_lc.equipe()){
							continue;
						}
						CreatureCombat& cr_c_=creatures_act.valeur(c);
						typedef QPair<uchar,Taux> EffectifPV;
						HashMap<QString,QList<EffectifPV> >& objets_=cr_c_.objets_pk();
						QList<EffectifPV>& quantites_=objets_.valeur(attaque_);
						quantites_[0].first--;
					}
				}else if(effet_.first=="MAX"){
					Taux somme_quantites_(0);
					typedef QPair<uchar,Taux> EffectifPV;
					foreach(EffectifPV e,_lanceur.objets_pk().valeur(attaque_)){
						somme_quantites_+=Taux((long long)e.first)*e.second;
					}
					uchar nb_=effet_.second.toUInt();
					if(Taux(nb_)>somme_quantites_){
						uchar pp_soignes_=_lanceur.soin_pp("");//TODO Nom de l'attaque a soigner
					}
				}else if(effet_.second=="MAX"){
				}else{
				}
			}
		}
		/*sinon si objet est_du_type SOIN
			sinon si objet.effet == SOIN_PP
				si objet.effet.nb_attaques == MAX_attaques
					si existence_attaques_lanceur_un_pp_max(lanceur)//le lanceur a au moins une attaque avec un nb pp < le max
						//objet.effectif --
						pour chaque element de creat_comb.cles()
							si element.equipe == lanceur.equipe
								element.objet --
							fin si
						fin pour
					fin si
					si objet.effet.nb_pp == MAX//MAX_de_tout_PP
						pour chaque attaque de lanceur
							attaque.nb_pp <- attaque.nb_pp_max
						fin pour
					sinon
						pour chaque attaque de lanceur
							attaque.nb_pp <- min(attaque.nb_pp_max,attaque.nb_pp+objet.effet.nb_pp)
						fin pour
					fin si
				sinon
					si attaque_soignee.nb_pp < attaque_soignee.nb_pp_max
						//objet.effectif --
						pour chaque element de creat_comb.cles()
							si element.equipe == lanceur.equipe
								element.objet --
							fin si
						fin pour
					fin si
					si objet.effet.nb_pp == MAX
						attaque_soignee.nb_pp <- attaque_soignee.nb_pp_max
					sinon
						attaque_soignee.nb_pp <- min(attaque_soignee.nb_pp_max,attaque_soignee.nb_pp+objet.effet.nb_pp)
					fin si
				fin si
			sinon si objet.effet == SOIN_KO et lanceur.statut == KO
				//objet.effectif --
				pour chaque element de creat_comb.cles()
					si element.equipe == lanceur.equipe
						element.objet --
					fin si
				fin pour
				lanceur.pv_restants <- lanceur.pv_max * objet.effet.taux
				lanceur.statut <- OK
			fin si
			si objet.effets > 1 et objet.effet_secondaire == BONHEUR et lanceur.equipe == ut
				mettre_jour_bonheur(lanceur,faux)
			fin si
		fin si*/
	}else if(attaque_!="RELAIS"){
		tour_lanceur(_lc,_lanceur,_d);
		if(_d->val_switch_force().contains(attaque_)&&_lanceur.att_reussie()){
			Combattant cb_=positions_places.cles(_lanceur.cibles()[0])[0];
			CreatureCombat& cible_=creatures_act.valeur(cb_);
			if(cible_.statut_pk()!="KO"){//CYCLONE,HURLEMENT,DRACOQUEUE,PROJECTION
				continuer_=cas_switch_force(_lc,_lanceur,cb_,cible_,_d);//la cible ne pourra pas attaquer
			}
		}
	}else{//RELAIS
		//lanceur.attaque_choisie <- action_choisie
		TransfertRelais trans_=_lanceur.relais();
		;
		/*
		TODO
		att_enc <- ""
		cbt <- INEXISTANT
		nb <- 0
		pour chaque combattant
			si positions_places.valeur(combattant).place == ARRIERE
				continuer
			fin si
			si combattant.encore[lanceur].nom != ""
				att_enc <- combattant.encore[lanceur].nom
				cbt <- combattant
				nb <- combattant.encore[lanceur].nb_tours
				sortir_boucle
			fin si
		fin pour*/
		//bool capac_active_=_lanceur.capacite_pk_act()!="";
		retrait(_lc,_lanceur,_d);
		Combattant choix_=_lanceur.remplacant();
		positions_places_bis.valeur(choix_).second=positions_places_bis.valeur(_lc).second;
		positions_places.valeur(choix_).second=positions_places.valeur(_lc).second;
		positions_places_bis.valeur(_lc).second=arriere;
		positions_places.valeur(_lc).second=arriere;
		CreatureCombat& cr_choix_=creatures_act.valeur(choix_);
		numeros_front.removeOne(_lc);
		numeros_front<<choix_;
		envoi(choix_,cr_choix_,trans_.capacite_act!="",_d);
		FicheCapacite *f_capac_=cr_choix_.fiche_capacite(_d);
		if(f_capac_){
			intimidation(f_capac_,adversaire(_lc.equipe()),_d);
		}
		cr_choix_.transfer_relais(trans_);
		if(!cr_choix_.clone_pk().estNul()&&cr_choix_.statut_pk().startsWith("POISON")){
			cr_choix_.statut_pk()="OK";
		}
		/*TODO
		ne_connait_pas_att_ss_encore <- vrai
		pour i=0;i<choix.attaques_act.taille;i++
			si choix.attaques_act[i].nom == elements_relais_transfert.encore[lanceur].nom
				ne_connait_pas_att_ss_encore <- faux
				sortir_boucle
			fin si
		fin pour
		si ne_connait_pas_att_ss_encore
			pour chaque combattant
				si positions_places.valeur(combattant).place == ARRIERE
					continuer
				fin si
				combattant.encore[choix].actif <- faux
				combattant.encore[choix].nom <- ""
				combattant.encore[choix].nb_tours <- 0
			fin pour
		sinon
			cbt.encore[choix].actif <- vrai
			cbt.encore[choix].nom <- att_enc
			cbt.encore[choix].nb_tours <- nb
		fin si*/
		//cas du relais
	}
	if((attaque_=="DANSE_LUNE"||attaque_=="VOEU_SOIN")&&_lanceur.att_reussie()&&_lanceur.statut_pk()=="KO"){
		//
		Combattant choix_=_lanceur.remplacant();
		positions_places_bis.valeur(choix_).second=positions_places_bis.valeur(_lc).second;
		positions_places.valeur(choix_).second=positions_places.valeur(_lc).second;
		positions_places_bis.valeur(_lc).second=arriere;
		positions_places.valeur(_lc).second=arriere;
		numeros_front.removeOne(_lc);
		numeros_front<<choix_;
		CreatureCombat& cr_choix_=creatures_act.valeur(choix_);
		envoi(choix_,cr_choix_,true,_d);
		FicheCapacite *f_capac_=cr_choix_.fiche_capacite(_d);
		if(f_capac_){
			intimidation(f_capac_,adversaire(_lc.equipe()),_d);
		}
		//envoi2(lanceur.equipe,adverse,lanceur.choix,vrai)
		//intimidation(lanceur.choix)
		_lanceur.act_choisie()="";
		Taux pv_soignes_=cr_choix_.soin_tout_pv();
		cr_choix_.statut_pk()="OK";
		HashMap<QString,uchar> attaques_=cr_choix_.soin_pp();
		//lanceur.choix.soin_total()
		//lanceur.choix <- vide
	}
	if((attaque_=="DEMI_TOUR"||attaque_=="CHANGE_ECLAIR")&&_lanceur.att_reussie()&&existence_adversaire_non_ko(creatures_act.cles(),_lc)){
		Combattant choix_=_lanceur.remplacant();
		if(choix_!=Combattant(arriere,arriere)){
			retrait(_lc,_lanceur,_d);
			positions_places_bis.valeur(choix_).second=positions_places_bis.valeur(_lc).second;
			positions_places.valeur(choix_).second=positions_places.valeur(_lc).second;
			positions_places_bis.valeur(_lc).second=arriere;
			positions_places.valeur(_lc).second=arriere;
			numeros_front.removeOne(_lc);
			numeros_front<<choix_;
			CreatureCombat& cr_choix_=creatures_act.valeur(choix_);
			envoi(choix_,cr_choix_,true,_d);
			FicheCapacite *f_capac_=cr_choix_.fiche_capacite(_d);
			if(f_capac_){
				intimidation(f_capac_,adversaire(_lc.equipe()),_d);
			}
			_lanceur.act_choisie()="";
		}
	}
	/*si action_choisie appartient a [DEMI_TOUR,CHANGE_ECLAIR] et existence_adversaire_non_ko(lanceur) et lanceur.attaque_reussie
		retrait(lanceur)
		si lanceur.equipe == UT
			choix.position <- lanceur.position
			lanceur.position <- -1
			envoi2(choix.equipe,adverse,choix,vrai)
			intimidation(choix)
		sinon
			//todo ia
			choix <- envoi_ia
			lanceur.position <- -1
			envoi2(choix.equipe,adverse,choix,vrai)
			intimidation(choix)
		fin si
	fin si*/
	return continuer_;
}

uchar ElementsCombat::tentative_capture(const QString& _nom_ball,Ball *_ball,Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d){
	if(nb_tours_terrain<255){
		nb_tours_terrain++;
	}
	commentaire_recent="";
	vengeance_actif.valeur(ut).second=false;
	vengeance_actif.valeur(adv).second=false;
	Inventaire& inventaire_=_utilisateur.inv();
	HashMap<QString,uchar>& balls_=inventaire_.balls_ut();
	balls_.valeur(_nom_ball)--;
	//si ball != SAFARI_BALL
	CreatureCombat& cr_adv_=creatures_act.valeur(Combattant(adv,0));
	if(cr_adv_.statut_pk()=="KO"){
		fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
		return capturer(_nom_ball,_utilisateur,_d);
	}
	Taux coeff_=calcul_coeff_capture(_ball,_utilisateur.present_pk(cr_adv_.nom_pk()),type_environnement=="EAU",cr_adv_,_d);//TODO
	if(coeff_>=Taux(1)){
		fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
		return capturer(_nom_ball,_utilisateur,_d);
	}
	bool capture_=tirage_capture(coeff_,4);//TODO etre plus generique
	if(capture_){
		fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
		return capturer(_nom_ball,_utilisateur,_d);
	}
	commentaire_recent+="La capture a echoue!\n";
	numeros_front.clear();
	numeros_front<<Combattant(adv,0);
	//coeff <- calcul_coeff_capture(ball,modele,pokemon_sauvage,front)
	HashMap<Combattant,QPair<QString,QPair<Combattant,Combattant> > > choix_=choix_ia_attaque(_d);
	QPair<QString,QPair<Combattant,Combattant> > choix_action_=choix_.valeur(Combattant(adv,0));
	Combattant cible_=choix_action_.second.first;
	numeros_front<<cible_;
	CreatureCombat& cr_ut_=creatures_act.valeur(cible_);
	cr_adv_.act_choisie()="ATTAQUE";
	cr_adv_.att_choisie()=choix_action_.first;
	cr_ut_.act_choisie()="";
	cr_ut_.att_choisie()="";
	nb_utilisation_attaques.valeur(QPair<QString,uchar>("CHANT_CANON",ut))=0;
	nb_utilisation_attaques.valeur(QPair<QString,uchar>("CHANT_CANON",adv))=0;
	cr_adv_.non_switch_force_pk()=true;
	cr_adv_.att_deg_subie().first=QPair<Taux,Taux>(Taux(0),Taux(0));
	cr_adv_.att_reussie()=false;
	cr_adv_.peur_pk()=false;
	cr_ut_.non_switch_force_pk()=true;
	cr_ut_.att_deg_subie().first=QPair<Taux,Taux>(Taux(0),Taux(0));
	cr_ut_.att_reussie()=false;
	cr_ut_.peur_pk()=false;
	//premier.non_switcher <- vrai pour tous
	//touche[PHYSIQUE] <- 0 pour tous
	//touche[SPECIALE] <- 0 pour tous
	//premier.peur <- faux pour tous
	QList<Combattant> ceux_devant_jouer_=trier_ordre_non_joue(false,_d);
	if(ceux_devant_jouer_.isEmpty()){
		ceux_devant_jouer_==trier_ordre_non_joue(true,_d);
	}
	QList<Combattant> ceux_devant_jouer_2_;
	ceux_devant_jouer_2_<<ceux_devant_jouer_[0];
	Combattant der_lanceur_=ceux_devant_jouer_2_[0];
	bool continuer_=lancer(der_lanceur_,cr_adv_,_d);
	cr_adv_.a_joue_pk()=true;
	if(!continuer_){
		return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
	}
	QList<Combattant> fronts_ut_;
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		if(c.equipe()!=ut){
			continue;
		}
		if(creatures_act.valeur(c).statut_pk()!="KO"){
			fronts_ut_<<c;
			continue;
		}
		positions_places.valeur(c).second=arriere;
	}
	if(existence_combattant_ut_non_ko_contre_1_adv()){
		foreach(Combattant c,creatures_act.cles()){
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			if(c.equipe()==ut){
				continue;
			}
			if(creatures_act.valeur(c).statut_pk()!="KO"){
				continue;
			}
			QList<uchar> liste_=combattants_contre_adv.valeur(c.position());
			QList<Combattant> combattants_ut_;
			foreach(uchar p,liste_){
				combattants_ut_<<Combattant(ut,p);
			}
			calcul_experience_ev(combattants_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
		}
	}else if(existence_ut_non_ko()){
		QList<Combattant> equipe_ut_;
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()!=ut){
				continue;
			}
			equipe_ut_<<c;
		}
		foreach(Combattant c,creatures_act.cles()){
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			if(c.equipe()==ut){
				continue;
			}
			if(creatures_act.valeur(c).statut_pk()!="KO"){
				continue;
			}
			calcul_experience_ev(equipe_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		if(c.equipe()==ut){
			continue;
		}
		if(creatures_act.valeur(c).statut_pk()!="KO"){
			continue;
		}
		positions_places.valeur(c).second=arriere;
	}
	//lanceurs.ajouter(lanceur)
	//continuer <- lancer(premier)
	//si non continuer
	//	fin_combat
	//	sortir
	//fin si
	return traiter_apres_tour(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);//TODO
}

uchar ElementsCombat::apprentissage_attaque_plus_evo(const Utilisateur& _utilisateur,Donnees *_d){
	foreach(Combattant c,creatures_act.cles()){
		if(c.equipe()!=ut){
			continue;
		}
		gain_exp_tmp.ajouter_cle_valeur(c.position(),creatures_act.valeur(c).gain_exp_combat());
	}
	//H <- hashmap des clé : position dans l'équipe, valeur: nb_pt_exp gagné
	foreach(uchar c,gain_exp_tmp.cles()){
		Taux& pts_=gain_exp_tmp.valeur(c);
		CreatureCombat& cr_ut_=creatures_act.valeur(Combattant(ut,c));
		if(cr_ut_.niveau_pk()==(int)_d->constante_numerique("NIVEAU_PK_MAX")){
			uchar nb_=0;
			foreach(uchar c2,gain_exp_tmp.cles()){
				CreatureCombat& cr_ut_2_=creatures_act.valeur(Combattant(ut,c2));
				if(cr_ut_2_.niveau_pk()<(int)_d->constante_numerique("NIVEAU_PK_MAX")&&gain_exp_tmp.valeur(c2)>Taux(0)){
					nb_++;
				}
			}
			if(nb_==0){
				continue;
			}
			foreach(uchar c2,gain_exp_tmp.cles()){
				CreatureCombat& cr_ut_2_=creatures_act.valeur(Combattant(ut,c2));
				if(cr_ut_2_.niveau_pk()<(int)_d->constante_numerique("NIVEAU_PK_MAX")&&gain_exp_tmp.valeur(c2)>Taux(0)){
					gain_exp_tmp.valeur(c2)+=gain_exp_tmp.valeur(c)*Taux(1LL,(long long)nb_);
				}
			}
			gain_exp_tmp.valeur(c)=Taux(0);
			continue;
		}
		if(pts_>Taux(0)){
			indice_pk=c;
			FichePokemon *f_pk_=_d->val_pokedex().valeur(cr_ut_.nom_pk());
			Taux nb_pts_requis_=f_pk_->diff_pts_niveaux(cr_ut_.niveau_pk()+1)-cr_ut_.exp_gagnee();
			//nb_pts_exp_demandés <- EXP(cle.nom,cle.niveau+1) - cle.nb_pts_exp_gagnés_depuis_der_passage_niveau
			Taux& copie_valeur_=pts_;
			if(pts_>=nb_pts_requis_){
				cr_ut_.reinit_gain_exp();
				while(copie_valeur_>=nb_pts_requis_){
					copie_valeur_-=nb_pts_requis_;
					Taux pv_=cr_ut_.pv_max();
					if(cr_ut_.niveau_pk()<(int)_d->constante_numerique("NIVEAU_PK_MAX")){
						cr_ut_.gain_niveau_pk();
						cr_ut_.mettre_jour_pv_restants2(_d,pv_);
						/*cle.attaque <- calcul_base(cle,attaque)
						cle.defense <- calcul_base(cle,defense)
						cle.attaque_speciale <- calcul_base(cle,attaque_speciale)
						cle.defense_speciale <- calcul_base(cle,defense_speciale)
						cle.vitesse <- calcul_base(cle,vitesse)*/
						//TODO cle.soin_total
					}
					cr_ut_.maj_bonheur_niveau(true,QPair<uchar,uchar>(0,0),_d);
					if(cr_ut_.niveau_pk()==(int)_d->constante_numerique("NIVEAU_PK_MAX")){
						uchar nb_=0;
						foreach(uchar c2,gain_exp_tmp.cles()){
							CreatureCombat& cr_ut_2_=creatures_act.valeur(Combattant(ut,c2));
							if(cr_ut_2_.niveau_pk()<(int)_d->constante_numerique("NIVEAU_PK_MAX")&&gain_exp_tmp.valeur(c2)>Taux(0)){
								nb_++;
							}
						}
						if(nb_>0){
							foreach(uchar c2,gain_exp_tmp.cles()){
								CreatureCombat& cr_ut_2_=creatures_act.valeur(Combattant(ut,c2));
								if(cr_ut_2_.niveau_pk()<(int)_d->constante_numerique("NIVEAU_PK_MAX")&&gain_exp_tmp.valeur(c2)>Taux(0)){
									gain_exp_tmp.valeur(c2)+=gain_exp_tmp.valeur(c)*Taux(1LL,(long long)nb_);
								}
							}
						}
						gain_exp_tmp.valeur(c)=Taux(0);
						//TODOcr_ut_.reinit_gain_exp()
						break;
					}
					nb_pts_requis_=f_pk_->diff_pts_niveaux(cr_ut_.niveau_pk()+1);
					//nb_pts_exp_demandés <- EXP(cle.nom,cle.niveau+1) - EXP(cle.nom,cle.niveau)
					indice_attaque=cr_ut_.attaque_apprise_niveau(indice_attaque,_d);
					while(indice_attaque>-1){	
					//tant que attaque_apprise_niveau(cle.niveau,indice_attaque,cle) > -1//il existe une attaque a apprendre a cle.niveau
						QString attaque_oubliee_;
						if(cr_ut_.attaques_pk().size()<_d->nb_att_max()){
							//apprendre_attaque
							cr_ut_.apprendre_attaque(f_pk_->atts()[indice_attaque].second,_d->nb_att_max(),_d,attaque_oubliee_);
						}else{
							cr_ut_.reinit_pts_exp();
							cr_ut_.gain_exp(copie_valeur_);
							return ElementsCombat::APPRENDRE_ATT;
						}
						indice_attaque=cr_ut_.attaque_apprise_niveau(indice_attaque,_d);
						/*si cle.nb_attaques < MAX_attaques
							ajouter_attaques(cle,indice_attaque)
							indice_attaque++
						sinon
							cle.gain_exp <- copie_valeur
							etat <- 2
							
						fin si*/
					}
				}
				cr_ut_.reinit_pts_exp();
				cr_ut_.reinit_gain_exp();
				cr_ut_.gain_niveau_exp(copie_valeur_);
				gain_exp_tmp.valeur(c)=Taux(0);
				indice_evolution=cr_ut_.existence_evolution_niveau(f_pk_,_utilisateur.nom_pk_equipe(),indice_evolution,diff.r_rapport_max_egalite(),_d);//TODO
				if(indice_evolution>-1){
					prochaine_evolution=cr_ut_;
				//si existence_evolution_niveau(cle,equipe_ut,indice_évolution)//'il existe evolution a cle.niveau et cle.objet != PIERRE_STASE
					//indice_evolution++
					//etat <- 3
					return ElementsCombat::EVOLUTION;
					//APPRENDRE_ATT,EVOLUTION,RIEN
				}
				a_evolue=false;
			}else{
				cr_ut_.gain_niveau_exp(pts_);
				gain_exp_tmp.valeur(c)=Taux(0);
				cr_ut_.reinit_pts_exp();
				indice_attaque=-1;
				indice_evolution=-1;
				//cle.nb_pts_exp_gagnés_depuis_der_passage_niveau += valeur
				//cle.gain_exp <- 0
			}
		}
	}
	return ElementsCombat::RIEN;
}

//Afficher les attaques (non act)
uchar ElementsCombat::traiter_apprentissage_attaque(uchar _type,const QString& _action,int _indice,Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d){
	Combattant c_(ut,indice_pk);
	CreatureCombat& cr_=creatures_act.valeur(c_);
	FichePokemon *f_pk_=_d->val_pokedex().valeur(cr_.nom_pk());
	if(_type==ElementsCombat::APPRENDRE_ATT){
		if(_action!=""){//pas de refus a la boite de dialogue => _action vaut une attaque
			QString attaque_oubliee_;
			cr_.apprendre_attaque(_action,_indice,_d,attaque_oubliee_);
			//apprendre_attaque_niveau(indice_attaque,action,cle)
			//maj_attaques à position_act
		}
		//indice_attaque++
		indice_attaque=cr_.attaque_apprise_niveau(indice_attaque,_d);
		if(indice_attaque>-1){
			//attaq_propos <- nom_att
			//mettre_en_place_ihm_apprentissage_attaque
			//etat <- 2
			return _type;
		}
		if(gain_exp_tmp.valeur(indice_pk)>Taux(0)){
			Taux nb_pts_requis_=f_pk_->diff_pts_niveaux(cr_.niveau_pk()+1)-cr_.exp_gagnee();
			//nb_pts_exp_demandés <- EXP(cle.nom,cle.niveau+1) - EXP(cle.nom,cle.niveau) - cle.nb_pts_exp_gagnés_depuis_der_passage_niveau
			Taux& copie_valeur_=gain_exp_tmp.valeur(indice_pk);// <- valeur
			if(copie_valeur_>=nb_pts_requis_){
				cr_.reinit_gain_exp();
				while(copie_valeur_>=nb_pts_requis_){
					copie_valeur_-=nb_pts_requis_;
					Taux pv_=cr_.pv_max();
					cr_.gain_niveau_pk();
					cr_.mettre_jour_pv_restants2(_d,pv_);
					/*cle.attaque <- calcul_base(cle,attaque)
					cle.defense <- calcul_base(cle,defense)
					cle.attaque_speciale <- calcul_base(cle,attaque_speciale)
					cle.defense_speciale <- calcul_base(cle,defense_speciale)
					cle.vitesse <- calcul_base(cle,vitesse)*/
					//TODO cle.soin_total
					cr_.maj_bonheur_niveau(true,QPair<uchar,uchar>(0,0),_d);
					nb_pts_requis_=f_pk_->diff_pts_niveaux(cr_.niveau_pk()+1);
					indice_attaque=cr_.attaque_apprise_niveau(indice_attaque,_d);
					while(indice_attaque>-1){
					//tant que attaque_apprise_niveau(cle.niveau,indice_attaque,cle) > -1//'il existe une attaque a apprendre a cle.niveau
						QString attaque_oubliee_;
						if(cr_.attaques_pk().size()<_d->nb_att_max()){
							//apprendre_attaque
							cr_.apprendre_attaque(f_pk_->atts()[indice_attaque].second,_d->nb_att_max(),_d,attaque_oubliee_);
						}else{
							cr_.reinit_pts_exp();
							cr_.gain_exp(copie_valeur_);
							return _type;
						}
						/*si cle.nb_attaques < MAX_attaques
							ajouter_attaques(cle,indice_attaque)
							indice_attaque ++
						sinon
							cle.gain_exp <- copie_valeur
							//mettre_en_place_ihm_apprentissage_attaque
							//etat <- 2
							return _type
						fin si*/
						indice_attaque=cr_.attaque_apprise_niveau(indice_attaque,_d);
					}
				}
				cr_.reinit_pts_exp();
				cr_.reinit_gain_exp();
				cr_.gain_niveau_exp(copie_valeur_);
				gain_exp_tmp.valeur(indice_pk)=Taux(0);
				//PKUT(cle).nb_pts_exp_gagnés_depuis_der_passage_niveau <- copie_valeur
				//cle.gain_exp <- 0
				indice_evolution=cr_.existence_evolution_niveau(f_pk_,_utilisateur.nom_pk_equipe(),indice_evolution,diff.r_rapport_max_egalite(),_d);//TODO
				if(indice_evolution>-1){
				//si existence_evolution_niveau(cle,equipe_ut,indice_évolution)//'il existe evolution a cle.niveau et cle.objet != PIERRE_STASE
					//indice_evolution++
					//etat <- 3
					prochaine_evolution=cr_;
					return ElementsCombat::EVOLUTION;
					//APPRENDRE_ATT,EVOLUTION,RIEN
				}
				a_evolue=false;
				/*si existence_evolution_niveau(cle,equipe_ut,indice_évolution) et cle.objet != PIERRE_STASE
				//s'il existe evolution a cle.niveau et cle.objet != PIERRE_STASE
					indice_évolution ++
					mettre_en_place_ihm_proposition_evolution
					etat <- 3
					sortir
				fin si*/
			}else{
				cr_.reinit_pts_exp();
				cr_.reinit_gain_exp();
				cr_.gain_niveau_exp(gain_exp_tmp.valeur(indice_pk));
				//PKUT(cle).nb_pts_exp_gagnés_depuis_der_passage_niveau <- valeur
				//cle.gain_exp <- 0
			}
		}
		if(prochaine_evolution.nom_pk()==""){
			prochaine_evolution=cr_;
		}
		indice_evolution=prochaine_evolution.existence_evolution_niveau(prochaine_evolution.fiche_pokemon_b(_d),_utilisateur.nom_pk_equipe(),indice_evolution,diff.r_rapport_max_egalite(),_d);//TODO
		if(indice_evolution>-1){
			//si existence_evolution_niveau(cle,equipe_ut,indice_évolution)//'il existe evolution a cle.niveau et cle.objet != PIERRE_STASE
			//indice_evolution++
			//etat <- 3
			return ElementsCombat::EVOLUTION;
		}
		a_evolue=false;
		uchar res_=apprentissage_attaque_plus_evo(_utilisateur,_d);
		//situation <- 1
		//res <- apprentissage_attaque_plus_evo
		if(res_==ElementsCombat::RIEN){
		//si res == 2
			QPair<bool,bool> kos_=existence_eq_ko();
			if(kos_.first||kos_.second){
				return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
			}
			if(existe_pk_ut_rempl()){
				return ElementsCombat::SWITCH_PROPOSE;
			}
			return ElementsCombat::PAS_SWITCH;
			/*si existence_eq_ko(creat_comb)
				fin_combat
			sinon si existe_pk_ut_rempl(positions_places)//il existe un pokemon de l'utilisateur pouvant remplacer
				mettre_en_place_ihm_pour_remplacement
				etat <- 1
			sinon
				mettre_en_place_choix_actions
				etat <- 0
			fin si*/
		}
		return res_;
	}else{// if(_type==ElementsCombat::EVOLUTION){
	//sinon si type == evolution
		if(_action!=""){
			//if(indice_evolution==0){
			if(!a_evolue){
				//a_evolue
				//si c'est la premiere evo...
				cr_.evoluer(f_pk_,indice_evolution,_d);
				a_evolue=true;
				indice_attaque=cr_.attaque_apprise_niveau(indice_attaque,_d);
				while(indice_attaque>-1){
				//tant que attaque_apprise_niveau(cle.niveau,indice_attaque,cle) > -1//'il existe une attaque a apprendre a cle.niveau
					QString attaque_oubliee_;
					if(cr_.attaques_pk().size()<_d->nb_att_max()){
						//apprendre_attaque
						cr_.apprendre_attaque(f_pk_->atts()[indice_attaque].second,_d->nb_att_max(),_d,attaque_oubliee_);
					}else{
						//TODO cr_.reinit_pts_exp()
						//TODO cr_.gain_exp(copie_valeur_)
						return ElementsCombat::APPRENDRE_ATT;
					}
					indice_attaque=cr_.attaque_apprise_niveau(indice_attaque,_d);
				}
				indice_evolution=cr_.existence_evolution_niveau(f_pk_,_utilisateur.nom_pk_equipe(),indice_evolution,diff.r_rapport_max_egalite(),_d);//TODO
				if(indice_evolution>-1){
					return _type;
				}
			}else{
				int nb_pl_=diff.r_nb_max_pk_par_equipe()-(_utilisateur.equipe_ut().size()+_utilisateur.oeufs().size());
				if(nb_pl_>0){
					CreatureCombat nouveau_=prochaine_evolution;
					f_pk_=_d->val_pokedex().valeur(nouveau_.nom_pk());
					nouveau_.evoluer(f_pk_,indice_evolution,_d);
					uchar pos_=_utilisateur.equipe_ut().size()+_utilisateur.oeufs().size();
					creatures_act.ajouter_cle_valeur(Combattant(ut,pos_),nouveau_);
					positions_places.ajouter_cle_valeur(Combattant(ut,pos_),QPair<uchar,uchar>(ut,arriere));
					CreatureCombat& r_nouveau_=creatures_act.valeur(Combattant(ut,pos_));
					indice_attaque=r_nouveau_.attaque_apprise_niveau(indice_attaque,_d);
					while(indice_attaque>-1){
					//tant que attaque_apprise_niveau(cle.niveau,indice_attaque,cle) > -1//'il existe une attaque a apprendre a cle.niveau
						QString attaque_oubliee_;
						if(r_nouveau_.attaques_pk().size()<_d->nb_att_max()){
							//apprendre_attaque
							FichePokemon *f_pk_2_=r_nouveau_.fiche_pokemon_b(_d);
							r_nouveau_.apprendre_attaque(f_pk_2_->atts()[indice_attaque].second,_d->nb_att_max(),_d,attaque_oubliee_);
						}else{
							//TODO cr_.reinit_pts_exp()
							//TODO cr_.gain_exp(copie_valeur_)
							return ElementsCombat::APPRENDRE_ATT;
						}
						indice_attaque=r_nouveau_.attaque_apprise_niveau(indice_attaque,_d);
					}
					FichePokemon *f_pk_2_=r_nouveau_.fiche_pokemon_b(_d);
					indice_evolution=r_nouveau_.existence_evolution_niveau(f_pk_2_,_utilisateur.nom_pk_equipe(),indice_evolution,diff.r_rapport_max_egalite(),_d);//TODO
					if(indice_evolution>-1){
						return _type;
					}
				}else{
					indice_evolution=-1;
					uchar res_=apprentissage_attaque_plus_evo(_utilisateur,_d);
					if(res_==ElementsCombat::RIEN){
					//si res == 2
						QPair<bool,bool> kos_=existence_eq_ko();
						if(kos_.first||kos_.second){
							return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
						}
						if(existe_pk_ut_rempl()){
							return ElementsCombat::SWITCH_PROPOSE;
						}
						return ElementsCombat::PAS_SWITCH;
					}
					return res_;
				}
				//prochaine_evolution.evoluer(f_pk_,indice_evolution,_d)
			}
		//si action == ACCEPT
			/**si indice_évolution == 0
				position_act.evoluer_actuelle_base_evo(indice_évolution)
				//position_act.evoluer de l'actuelle base d'évolution
			sinon
				si nb_places_libres_dans_equipe > 0
					ajouter_dans_l_equipe_evo
				sinon
					situation <- 2
					res <- apprentissage_attaque_plus_evo
					si res == 2
						si existence_eq_ko(creat_comb)//'il existe une equipe ko
							fin_combat
						sinon si existe_pk_ut_rempl(positions_places)// il existe un pokemon de l'utilisateur pouvant remplacer
							mettre_en_place_ihm_pour_remplacement
							etat <- 1
						sinon
							mettre_en_place_choix_actions
							etat <- 0
						fin si
					fin si
					sortir
				fin si
			fin si*/
			/*tant que attaque_apprise_niveau(cle.niveau,indice_attaque,cle) > -1//il existe une attaque a apprendre a cle.niveau
				si cle.nb_attaques < MAX_attaques
					ajouter_attaques(cle,indice_attaque)
					indice_attaque++
				sinon
					cle.gain_exp <- copie_valeur
					mettre_en_place_ihm_apprentissage_attaque
					etat <- 2//pour le chargment
					sortir
				fin si
			fin tant que*/
		}
		/*sinon
			indice_évolution ++
		fin si*/
		/*si existence_evolution_niveau(cle,equipe_ut,indice_évolution)//'il existe evolution a cle.niveau et nb_places_libres_dans_equipe > 0
			si action == ACCEPT
				indice_évolution ++
			fin si
			mettre_en_place_ihm_proposition_evolution
			etat <- 3
			sortir
		fin si*/
		uchar res_=apprentissage_attaque_plus_evo(_utilisateur,_d);
		if(res_==ElementsCombat::RIEN){
		//si res == 2
			QPair<bool,bool> kos_=existence_eq_ko();
			if(kos_.first||kos_.second){
				return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
			}
			if(existe_pk_ut_rempl()){
				return ElementsCombat::SWITCH_PROPOSE;
			}
			return ElementsCombat::PAS_SWITCH;
		}
		return res_;
		/*situation <- 2
		res <- apprentissage_attaque_plus_evo
		si res == 2
			si existence_eq_ko(creat_comb)//'il existe une equipe ko
				fin_combat
			sinon si existe_pk_ut_rempl(positions_places)// il existe un pokemon de l'utilisateur pouvant remplacer
				mettre_en_place_ihm_pour_remplacement
				etat <- 1
			sinon
				mettre_en_place_choix_actions
				etat <- 0
			fin si
		fin si
		sortir*/
	}
	//si situation == 1
}

uchar ElementsCombat::traiter_apres_tour(Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d){
	QPair<bool,bool> kos_=existence_eq_ko();
	if(!kos_.first&&!kos_.second){
		effets_fin_tour(_d);
		bool existe_ko_=false;
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==adv){
				continue;
			}
			CreatureCombat& cr_ut_=creatures_act.valeur(c);
			if(cr_ut_.statut_pk()!="KO"){
				continue;
			}
			/*if(positions_places.valeur(c).second==arriere){
				continue;
			}*/
			if(numeros_front.contains(c)){
				positions_places.valeur(c).second=arriere;
				existe_ko_=true;
			}
		}
		if(existence_combattant_ut_non_ko_contre_1_adv()){
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				if(c.equipe()==ut){
					continue;
				}
				if(creatures_act.valeur(c).statut_pk()!="KO"){
					continue;
				}
				QList<uchar> liste_=combattants_contre_adv.valeur(c.position());
				QList<Combattant> combattants_ut_;
				foreach(uchar p,liste_){
					combattants_ut_<<Combattant(ut,p);
				}
				calcul_experience_ev(combattants_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
			}
		}else if(existence_ut_non_ko()){
			QList<Combattant> equipe_ut_;
			foreach(Combattant c,creatures_act.cles()){
				if(c.equipe()!=ut){
					continue;
				}
				equipe_ut_<<c;
			}
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				if(c.equipe()==ut){
					continue;
				}
				if(creatures_act.valeur(c).statut_pk()!="KO"){
					continue;
				}
				calcul_experience_ev(equipe_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
			}
		}
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==ut){
				continue;
			}
			CreatureCombat& cr_ut_=creatures_act.valeur(c);
			if(cr_ut_.statut_pk()!="KO"){
				continue;
			}
			/*if(positions_places.valeur(c).second==arriere){
				continue;
			}*/
			if(numeros_front.contains(c)){
				positions_places.valeur(c).second=arriere;
				existe_ko_=true;
			}
		}
		//situation <- 3
		uchar res_=apprentissage_attaque_plus_evo(_utilisateur,_d);
		if(res_==ElementsCombat::RIEN){
			if(existe_ko_&&existe_pk_ut_rempl()){
				return ElementsCombat::SWITCH_PROPOSE;
				//mettre_en_place_ihm_pour_remplacement
				//etat <- 1
			}
			if(existe_ko_&&!existe_pk_ut_rempl()){
				return ElementsCombat::PAS_SWITCH;
			}
			return ElementsCombat::NORMAL;
			//mettre_en_place_choix_actions
			//etat <- 0
			//Si un pokemon est bloque ou prepa_tour ou nec_recharg, alors il ne peut pas attaquer avec une de ses attaques (excepté le switch le soin par objet)
			//sortir
		}
		return res_;
	}
	//gain experience si utilisateur gagne
	if(existence_combattant_ut_non_ko_contre_1_adv()){
		foreach(Combattant c,creatures_act.cles()){
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			if(c.equipe()==ut){
				continue;
			}
			if(creatures_act.valeur(c).statut_pk()!="KO"){
				continue;
			}
			QList<uchar> liste_=combattants_contre_adv.valeur(c.position());
			QList<Combattant> combattants_ut_;
			foreach(uchar p,liste_){
				combattants_ut_<<Combattant(ut,p);
			}
			calcul_experience_ev(combattants_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
		}
	}else if(existence_ut_non_ko()){
		QList<Combattant> equipe_ut_;
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()!=ut){
				continue;
			}
			equipe_ut_<<c;
		}
		foreach(Combattant c,creatures_act.cles()){
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			if(c.equipe()==ut){
				continue;
			}
			if(creatures_act.valeur(c).statut_pk()!="KO"){
				continue;
			}
			calcul_experience_ev(equipe_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
		}
	}
	//situation <- 4
	uchar res_=apprentissage_attaque_plus_evo(_utilisateur,_d);
	if(res_==ElementsCombat::RIEN){
		return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
	}
	return res_;
}

uchar ElementsCombat::tentative_fuite(Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d){
	if(nb_tours_terrain<255){
		nb_tours_terrain++;
	}
	if(fuite<255){
		fuite++;
	}
	commentaire_recent="";
	vengeance_actif.valeur(ut).second=false;
	vengeance_actif.valeur(adv).second=false;
	Taux coeff_=calcul_coeff_fuite(_d);
	if((int)coeff_>=255){
		return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
	}
	ObjetAttachableCombat *obj_=NULL;
	CreatureCombat& cr_u_=creatures_act.valeur(positions_places.cles(QPair<uchar,uchar>(ut,0))[0]);
	if(cr_u_.objet()!=""){
		obj_=qobject_cast<ObjetAttachableCombat*>(cr_u_.fiche_objet(_d));
		if(obj_&&obj_->fuite_re()){
			return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
		}
	}
	bool res_=tirage_fuite(coeff_/Taux(255));
	if(res_){
		return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
	}
	numeros_front.clear();
	numeros_front<<Combattant(adv,0);
	HashMap<Combattant,QPair<QString,QPair<Combattant,Combattant> > > choix_=choix_ia_attaque(_d);
	QPair<QString,QPair<Combattant,Combattant> > choix_action_=choix_.valeur(Combattant(adv,0));
	Combattant cible_=choix_action_.second.first;
	CreatureCombat& cr_adv_=creatures_act.valeur(Combattant(adv,0));
	commentaire_recent+="Fuite impossible car "+cr_adv_.nom_pk_act()+" est trop rapide!\n";
	CreatureCombat& cr_ut_=creatures_act.valeur(cible_);
	numeros_front<<cible_;
	cr_adv_.act_choisie()="ATTAQUE";
	cr_adv_.att_choisie()=choix_action_.first;
	cr_ut_.act_choisie()="";
	cr_ut_.att_choisie()="";
	nb_utilisation_attaques.valeur(QPair<QString,uchar>("CHANT_CANON",ut))=0;
	nb_utilisation_attaques.valeur(QPair<QString,uchar>("CHANT_CANON",adv))=0;
	cr_adv_.non_switch_force_pk()=true;
	cr_adv_.att_deg_subie().first=QPair<Taux,Taux>(Taux(0),Taux(0));
	cr_adv_.att_reussie()=false;
	cr_adv_.peur_pk()=false;
	cr_ut_.non_switch_force_pk()=true;
	cr_ut_.att_deg_subie().first=QPair<Taux,Taux>(Taux(0),Taux(0));
	cr_ut_.att_reussie()=false;
	cr_ut_.peur_pk()=false;
	//premier.non_switcher <- vrai pour tous
	//touche[PHYSIQUE] <- 0 pour tous
	//touche[SPECIALE] <- 0 pour tous
	//premier.peur <- faux pour tous
	QList<Combattant> ceux_devant_jouer_=trier_ordre_non_joue(false,_d);
	if(ceux_devant_jouer_.isEmpty()){
		ceux_devant_jouer_==trier_ordre_non_joue(true,_d);
	}
	QList<Combattant> ceux_devant_jouer_2_;
	ceux_devant_jouer_2_<<ceux_devant_jouer_[0];
	Combattant der_lanceur_=ceux_devant_jouer_2_[0];
	bool continuer_=lancer(der_lanceur_,cr_adv_,_d);
	cr_adv_.a_joue_pk()=true;
	if(!continuer_){
		return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
	}
	QList<Combattant> fronts_ut_;
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		if(c.equipe()!=ut){
			continue;
		}
		if(creatures_act.valeur(c).statut_pk()!="KO"){
			fronts_ut_<<c;
			continue;
		}
		positions_places.valeur(c).second=arriere;
	}
	if(existence_combattant_ut_non_ko_contre_1_adv()){
		foreach(Combattant c,creatures_act.cles()){
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			if(c.equipe()==ut){
				continue;
			}
			if(creatures_act.valeur(c).statut_pk()!="KO"){
				continue;
			}
			QList<uchar> liste_=combattants_contre_adv.valeur(c.position());
			QList<Combattant> combattants_ut_;
			foreach(uchar p,liste_){
				combattants_ut_<<Combattant(ut,p);
			}
			calcul_experience_ev(combattants_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
		}
	}else if(existence_ut_non_ko()){
		QList<Combattant> equipe_ut_;
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()!=ut){
				continue;
			}
			equipe_ut_<<c;
		}
		foreach(Combattant c,creatures_act.cles()){
			if(positions_places.valeur(c).second==arriere){
				continue;
			}
			if(c.equipe()==ut){
				continue;
			}
			if(creatures_act.valeur(c).statut_pk()!="KO"){
				continue;
			}
			calcul_experience_ev(equipe_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
		}
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		if(c.equipe()==ut){
			continue;
		}
		if(creatures_act.valeur(c).statut_pk()!="KO"){
			continue;
		}
		positions_places.valeur(c).second=arriere;
	}
	//lanceurs.ajouter(lanceur)
	//continuer <- lancer(premier)
	//si non continuer
	//	fin_combat
	//	sortir
	//fin si
	return traiter_apres_tour(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);//TODO
}


uchar ElementsCombat::fin_combat(Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d){
	_utilisateur.affecterFinCombat(*this,_d);
	if(type_combat=="SAUVAGE"){
		if(creatures_act.valeur(Combattant(adv,0)).statut_pk()=="KO"){
			if(diff.r_autorise_ko_capture()){
				return ElementsCombat::CAPTURE_KO;
			}
			return ElementsCombat::REDESSIN_SCENE;
		}
		if(perdre_dresseur()||match_nul()){
			return ElementsCombat::VILLE_DEPART;
		}
		return ElementsCombat::REDESSIN_SCENE;
		/*si combat.creature_combat_sauvage.statut == KO//l'utilisateur gagne le combat
			si autorise_capture_ko
				mettre_en_place_choix_capture_KO
				etat <- 4
			sinon
				redessiner_scene_utilisateur

			fin si
		sinon//si l'utilisateur perd le combat
			remettre_dernier_centre_poke_visite
		//sinon si capture_pk_adv
		//	mettre_en_place_choix_surnom
		//	etat <- 5
		//	capture_pk_adv <- faux
		//sinon
		//	redessiner_scene_utilisateur

		fin si
		sortir*/
	}
	if(gagner_dresseur()){
		Entier somme_niveau_(0);
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==ut){
				continue;
			}
			somme_niveau_+=creatures_act.valeur(c).niveau_pk();
		}
		Coordonnees coords_=coords_adversaire.first;
		if(type_combat=="DRESSEUR_LIGUE"){
			_stade_ligue++;
			Ligue *ligue_=_d->val_ligues().valeur(coords_.lieu());
			PlateauLigue *pl_=ligue_->plateau(coords_.plateau());
			var_argent+=Taux(somme_niveau_)*Taux(pl_->val_dresseur_ligue()->recompense())*Taux(10);
			int nb_plateaux_=ligue_->nb_plateaux();
			if(_stade_ligue==nb_plateaux_){
				if(!_ligues.contains(coords_.lieu())){
					_ligues<<coords_.lieu();
				}
			}
		}else{
			Environnement *env_=_d->val_lieux().valeur(coords_.lieu())->plateau(coords_.plateau())->environnement(coords_.coords_environnement());
			Dresseur1 *dresseur_=qobject_cast<Dresseur1*>(env_->perso(coords_.coords_tuile()));
			Champion *champion_=qobject_cast<Champion*>(dresseur_);
			if(champion_){
				var_argent+=Taux(somme_niveau_)*Taux(champion_->recompense(coords_adversaire.second))*Taux(4);
				Inventaire& inventaire_=_utilisateur.inv();
				inventaire_.ct_ut().valeur(champion_->val_ct())++;
				inventaire_.cs_ut().valeur(champion_->val_cs())=true;
			}else{
				var_argent+=Taux(somme_niveau_)*Taux(dresseur_->recompense(coords_adversaire.second))*Taux(2);
			}
			_dresseurs_battus.valeur(coords_adversaire)=true;
		}
		return ElementsCombat::REDESSIN_SCENE;
	}
	if(match_nul()){
		Entier somme_niveau_(0);
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==ut){
				continue;
			}
			somme_niveau_+=creatures_act.valeur(c).niveau_pk();
		}
		Coordonnees coords_=coords_adversaire.first;
		if(type_combat=="DRESSEUR_LIGUE"){
			Ligue *ligue_=_d->val_ligues().valeur(coords_.lieu());
			int nb_plateaux_=ligue_->nb_plateaux();
			if(_stade_ligue+1==nb_plateaux_){
				_stade_ligue=nb_plateaux_;
				PlateauLigue *pl_=ligue_->plateau(coords_.plateau());
				var_argent+=Taux(somme_niveau_)*Taux(pl_->val_dresseur_ligue()->recompense())*Taux(10);
				if(!_ligues.contains(coords_.lieu())){
					_ligues<<coords_.lieu();
				}
				return ElementsCombat::REDESSIN_SCENE;
			}
			return ElementsCombat::DEBUT_LIGUE;
		}
		//TODO match nul
	}
	if(type_combat=="DRESSEUR_LIGUE"){
		return ElementsCombat::DEBUT_LIGUE;
	}
	//TODO defaite
	//si le combat contre un pokemon sauvage
	/*sinon si match_nul(creat_comb)//les deux équipes sont KO
		gagne <- faux
		si le dresseur est un dresseur de la ligue
			nb_dress_bat_total <- dresseurs[ligue_battue.premier].taille
			//0 => 5, 1 => 9, 2 => 20
			si ligue_battue.premier == 0//ligue jamais battue
				si stade_ligue == nb_dress_bat_total//5
					ligue_battue.premier ++
					stade_ligue <- 0
					gagne <- vrai
				fin si
			sinon si ligue_battue.premier < MAX_PREMIER_LIGUE//MAX_PREMIER_LIGUE==3
				indice <- 1
				tant que indice < MAX_PREMIER_LIGUE
					si ligue_battue.premier == indice
						si ligue_battue.second == indice//mis à 1 après l'obention des 8 1ers badges
							si stade_ligue == dresseurs[indice-1].taille//5
								stade_ligue <- 0
								gagne <- vrai
							fin si
						sinon
							si stade_ligue == dresseurs[indice].taille//9
								stade_ligue <- 0
								gagne <- vrai
								ligue_battue.premier ++
							fin si
						fin si
					fin si
					indice++
				fin tant que
			sinon
				si stade_ligue == dresseurs[indice-1].taille//17
					stade_ligue <- 0
					gagne <- vrai
				fin si
			fin si
			//si ligue_battue.premier == 0//ligue jamais battue
			//	si stade_ligue == 5
			//		ligue_battue.premier ++
			//		stade_ligue <- 0
			//		gagne <- vrai
			//	fin si
			//sinon si ligue_battue.premier == 1
			//	si ligue_battue.second == 1//mis à 1 après l'obention des 8 1ers badges
			//		si stade_ligue == 5
			//			stade_ligue <- 0
			//			gagne <- vrai
			//		fin si
			//	sinon
			//		si stade_ligue == 9
			//			stade_ligue <- 0
			//			ligue_battue.premier ++
			//			gagne <- vrai
			//		fin si
			//	fin si
			//sinon si ligue_battue.premier == 2
			//	si ligue_battue.second == 2//mis à 2 après l'obention des 16 1ers badges
			//		si stade_ligue == 9
			//			stade_ligue <- 0
			//			gagne <- vrai
			//		fin si
			//	sinon
			//		si stade_ligue == 17
			//			stade_ligue <- 0
			//			ligue_battue.premier ++
			//			gagne <- vrai
			//		fin si
			//	fin si
			//sinon
			//	si stade_ligue == 17
			//		stade_ligue <- 0
			//		gagne <- vrai
			//	fin si
			//fin si
		sinon si le dresseur est un champion
			utilisateur.inventaire[CT,dresseur.ct] ++
			gagne <- vrai
		fin si
		si gagne
			utilisateur.dresseurs_battus[partie.coords_act] <- vrai
			si le dresseur est un dresseur de la ligue
				utilisateur.argent += dresseur.base_argent * somme des niveaux * 10
			sinon
				utilisateur.argent += dresseur.base_argent * somme des niveaux * 4
			fin si
		fin si
		partie.utilisateur <- combat.utilisateur
		si gagne
			si le dresseur est un champion d'arene
				replacer_utilisateur_centre_pk_ville_arene
			sinon
				replacer_utilisateur_centre_pk_ville_depart
			fin si
			sortir
		fin si
		remettre_dernier_centre_poke_visite //si existant sinon à la dernière ville visitée
	sinon
		si non facile
			si le dresseur est un dresseur de la ligue
				utilisateur.argent <- max(utilisateur.argent-dresseur.base_argent * somme des niveaux * 10,0)
			sinon si le dresseur est un champion
				utilisateur.argent <- max(utilisateur.argent-dresseur.base_argent * somme des niveaux * 4,0)
			sinon si c'est le rival
				utilisateur.argent <- max(utilisateur.argent-dresseur.base_argent * somme des niveaux * 4,0)
			sinon
				utilisateur.argent <- max(utilisateur.argent-dresseur.base_argent * somme des niveaux * 2,0)
			fin si
		fin si
		partie.utilisateur <- combat.utilisateur
		remettre_dernier_centre_poke_visite //si existant sinon à la dernière ville visitée
	fin si*/
	return ElementsCombat::VILLE_DEPART;
	//return ElementsCombat::REDESSIN_SCENE
	//TODO
}

uchar ElementsCombat::traiter_remplacement(Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d){
	//appelé par la validation du remplacement appelle choix_ia_envoi_remplacement
	bool existe_ko_=false;
	foreach(Combattant c,creatures_act.cles()){
	//parmi les pokémons de l'utilisateur et de l'adversaire envoyés
		if(c.equipe()==ut){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		Combattant rempl_=cr_c_.remplacant();
		if(rempl_==Combattant(arriere,arriere)){
			continue;
		}
		positions_places.valeur(rempl_).second=positions_places_bis.valeur(c).second;
		positions_places_bis.valeur(rempl_).second=positions_places_bis.valeur(c).second;
		positions_places.valeur(c).second=arriere;
		positions_places_bis.valeur(c).second=arriere;
		CreatureCombat& cr_r_=creatures_act.valeur(rempl_);
		if(cr_c_.statut_pk()!="KO"){
			retrait(c,cr_c_,_d);
		}
		envoi(rempl_,cr_r_,true,_d);
		if(cr_r_.statut_pk()=="KO"){
			existe_ko_=true;
		}
		cr_c_.act_choisie()="";
	}
	foreach(Combattant c,creatures_act.cles()){
	//parmi les pokémons de l'utilisateur et de l'adversaire envoyés
		if(c.equipe()==adv){
			continue;
		}
		CreatureCombat& cr_c_=creatures_act.valeur(c);
		Combattant rempl_=cr_c_.remplacant();
		if(rempl_==Combattant(arriere,arriere)){
			continue;
		}
		positions_places.valeur(rempl_).second=positions_places_bis.valeur(c).second;
		positions_places_bis.valeur(rempl_).second=positions_places_bis.valeur(c).second;
		positions_places.valeur(c).second=arriere;
		positions_places_bis.valeur(c).second=arriere;
		CreatureCombat& cr_r_=creatures_act.valeur(rempl_);
		if(cr_c_.statut_pk()!="KO"){
			retrait(c,cr_c_,_d);
		}
		envoi(rempl_,cr_r_,true,_d);
		if(cr_r_.statut_pk()=="KO"){
			existe_ko_=true;
		}
		cr_c_.act_choisie()="";
	}
	foreach(Combattant c,creatures_act.cles()){
		if(positions_places.valeur(c).second==arriere){
			continue;
		}
		FicheCapacite *f_capac_=creatures_act.valeur(c).fiche_capacite(_d);
		if(f_capac_){
			intimidation(f_capac_,adversaire(c.equipe()),_d);
		}
	}
	if(existe_ko_){
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==adv){
				continue;
			}
			CreatureCombat& cr_ut_=creatures_act.valeur(c);
			if(cr_ut_.statut_pk()!="KO"){
				continue;
			}
			positions_places.valeur(c).second=arriere;
		}
		if(existence_combattant_ut_non_ko_contre_1_adv()){
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				if(c.equipe()==ut){
					continue;
				}
				if(creatures_act.valeur(c).statut_pk()!="KO"){
					continue;
				}
				QList<uchar> liste_=combattants_contre_adv.valeur(c.position());
				QList<Combattant> combattants_ut_;
				foreach(uchar p,liste_){
					combattants_ut_<<Combattant(ut,p);
				}
				calcul_experience_ev(combattants_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
			}
		}else if(existence_ut_non_ko()){
			QList<Combattant> equipe_ut_;
			foreach(Combattant c,creatures_act.cles()){
				if(c.equipe()!=ut){
					continue;
				}
				equipe_ut_<<c;
			}
			foreach(Combattant c,creatures_act.cles()){
				if(positions_places.valeur(c).second==arriere){
					continue;
				}
				if(c.equipe()==ut){
					continue;
				}
				if(creatures_act.valeur(c).statut_pk()!="KO"){
					continue;
				}
				calcul_experience_ev(equipe_ut_,c,_d,_d->constante_numerique("NIVEAU_PK_MAX"),_d->constante_numerique("MAX_EV"));
			}
		}
		foreach(Combattant c,creatures_act.cles()){
			if(c.equipe()==ut){
				continue;
			}
			CreatureCombat& cr_ut_=creatures_act.valeur(c);
			if(cr_ut_.statut_pk()!="KO"){
				continue;
			}
			positions_places.valeur(c).second=arriere;
		}
		uchar res_=apprentissage_attaque_plus_evo(_utilisateur,_d);
		//situation <- 1
		//res <- apprentissage_attaque_plus_evo
		if(res_==ElementsCombat::RIEN){
		//si res == 2
			QPair<bool,bool> kos_=existence_eq_ko();
			if(kos_.first||kos_.second){
				return fin_combat(_utilisateur,_ligues,_stade_ligue,_dresseurs_battus,_d);
			}
			if(existe_pk_ut_rempl()){
				return ElementsCombat::SWITCH_PROPOSE;
			}
			return ElementsCombat::PAS_SWITCH;
		}
		return res_;
	}
	return ElementsCombat::NORMAL;
}


/**Appelé après la fin de combat*/
uchar ElementsCombat::capturer(const QString& _nom_ball,Utilisateur& _utilisateur,Donnees* _d){
	if(_nom_ball!=""){
		//Inventaire& inventaire_=_utilisateur.inv();
		//HashMap<QString,uchar>& balls_=inventaire_.balls_ut();
		//balls_.valeur(_nom_ball)--;
		CreatureCombat& cr_adv_=creatures_act.valeur(Combattant(adv,0));
		//si le combat contre un pokemon sauvage et 
		int indice_=_utilisateur.attraper_pk_sauvage(cr_adv_,_d,diff.r_nb_max_pk_par_equipe());
		bool ajout_=true;
		indice_capture=indice_;
		int nb_boites_=_d->constante_numerique("NB_BOITES");
		if(indice_<nb_boites_){
			//TODO ajout a la boite
			commentaire_recent+=cr_adv_.nom_pk()+" vient d'etre transfere dans la boite "+QString::number(indice_)+"\n";
		}else if(indice_==nb_boites_){
			//TODO ajout dans l'equipe
			commentaire_recent+=cr_adv_.nom_pk()+" viend d'etre ajoute a la fin de l'equipe\n";
		}else{
			commentaire_recent+="oups, ... plus de place dans les boites\n";
			ajout_=false;
			//TODO oups,....
		}
		bool deja_pris_=_utilisateur.attrape_pk(cr_adv_.nom_pk());
		cr_adv_.ball_capt()=_nom_ball;
		if(!deja_pris_){
			commentaire_recent+=cr_adv_.nom_pk()+" vient d'etre ajoute au pokedex\n";
			//TODO ajout dans le pokedex
		}
		/*attr <- utilisateur.attrape_pk(combat.creature_combat_sauvage.nom)
		si non attr
			mise_a_jour du pokedex
		fin si*/
		/*combat.creature_combat_sauvage.surnom <- combat.creature_combat_sauvage.nom
		pos <- utilisateur.equipe_ut().taille + utilisateur.oeufs().taille
		ajout <- faux
		si pos < partie.max_pk_equipe
		//ajout du pokemon capturé dans l'equipe de l'utilisateur si possible
		//HEAL_BALL
			utilisateur.attraper_pk_sauvage(pos,pokemon_utilisateur(combat.creature_combat_sauvage))
			ajout <- vrai
		sinon si non utilisateur.attraper_pk_sauvage(pokemon_utilisateur(combat.creature_combat_sauvage))
			//Oups plus du tout de place dans les boîtes
		sinon
		//ajout du pokemon capturé dans la 1ere boîte disponible incomplète
			ajout <- vrai
		fin si*/
		if(ajout_){
			return ElementsCombat::SURNOM;
		}
		/*si ajout
			mettre_en_place_choix_surnom
			etat <- 5
		fin si*/
	}
	return ElementsCombat::REDESSIN_SCENE;
}



void ElementsCombat::serialiser(Flux& _out)const{
	_out<<type_combat;
	_out<<type_environnement;
	_out<<creatures_act;
	_out<<positions_places;
	_out<<climat;
	_out<<indice_pk;
	_out<<indice_attaque;
	_out<<indice_evolution;
	_out<<base_evolution;
	_out<<situation;
	_out<<combattants_contre_adv;
	_out<<numeros_front;
	_out<<objets_utilisateur_perdus;
	_out<<derniere_attaque_lancee;
	_out<<nb_tour_attaque_equipe;
	_out<<derniere_attaque_reussie;
	_out<<coords_adversaire;
	_out<<gain_exp_tmp;
	//_out<<appats_lances
	//_out<<nb_safari_ball_possedes
	_out<<actions_choisies_ut;
	_out<<commentaire_recent;
	_out<<commentaires_combat;
	_out<<voeu;
	_out<<soin_total;
	_out<<prescience_carnar;
	_out<<nb_tours_terrain;
	_out<<vengeance_actif;
	_out<<nb_utilisation_attaques;
	_out<<effets_globaux;
	_out<<multiplicite;
	_out<<capture;
	_out<<lanceur_par_ici;
	_out<<lanceur_saisie;
	_out<<prochaine_evolution;
	_out<<fuite;
	_out<<var_argent;
	_out<<a_evolue;
	_out<<indice_capture;
	_out<<coords_leg;
	_out<<positions_places_bis;
}

void ElementsCombat::deserialiser(Flux& _in){
	_in>>type_combat;
	_in>>type_environnement;
	_in>>creatures_act;
	_in>>positions_places;
	_in>>climat;
	_in>>indice_pk;
	_in>>indice_attaque;
	_in>>indice_evolution;
	_in>>base_evolution;
	_in>>situation;
	_in>>combattants_contre_adv;
	_in>>numeros_front;
	_in>>objets_utilisateur_perdus;
	_in>>derniere_attaque_lancee;
	_in>>nb_tour_attaque_equipe;
	_in>>derniere_attaque_reussie;
	_in>>coords_adversaire;
	_in>>gain_exp_tmp;
	//_in>>appats_lances
	//_in>>nb_safari_ball_possedes
	_in>>actions_choisies_ut;
	_in>>commentaire_recent;
	_in>>commentaires_combat;
	_in>>voeu;
	_in>>soin_total;
	_in>>prescience_carnar;
	_in>>nb_tours_terrain;
	_in>>vengeance_actif;
	_in>>nb_utilisation_attaques;
	_in>>effets_globaux;
	_in>>multiplicite;
	_in>>capture;
	_in>>lanceur_par_ici;
	_in>>lanceur_saisie;
	_in>>prochaine_evolution;
	_in>>fuite;
	_in>>var_argent;
	_in>>a_evolue;
	_in>>indice_capture;
	_in>>coords_leg;
	_in>>positions_places_bis;
}

Flux & operator <<(Flux& out,const ElementsCombat& _ElementsCombat){
	_ElementsCombat.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,ElementsCombat& _ElementsCombat){
	_ElementsCombat.deserialiser(in);
	return in;
}


