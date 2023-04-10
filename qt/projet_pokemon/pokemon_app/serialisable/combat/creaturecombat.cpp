#include "serialisable/combat/creaturecombat.h"
#include "serialisable/pokemon/pokemonutilisateur.h"
#include "serialisable/difficulte/difficulte.h"
#include "base_donnees/pokemon/pokemondresse.h"
#include "base_donnees/pokemon/pokemonsauvage.h"
#include "base_donnees/donnees.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/evolution/evolutionattaque.h"
#include "base_donnees/evolution/evolutionbonheur.h"
#include "base_donnees/evolution/evolutionconditionstat.h"
#include "base_donnees/evolution/evolutionniveaugenre.h"
#include "base_donnees/evolution/evolutionobjet.h"
#include "base_donnees/evolution/evolutionplace.h"
#include "base_donnees/evolution/evolutionpierreevolutive.h"
#include "base_donnees/objets/plaque.h"
#include "base_donnees/objets/module.h"
#include "base_donnees/objets/baie.h"
#include "base_donnees/objets/soin.h"
#include "base_donnees/objets/objetattachablecombat.h"
#include "base_donnees/capacites/fichecapacite.h"
#include "base_donnees/attaques/ficheattaque.h"
#include "base_donnees/attaques/effets/effetantiimmu.h"
#include "combat/transfertrelais.h"

CreatureCombat::CreatureCombat(){
	;
}

/*CreatureCombat::CreatureCombat(const CreatureCombat& _copie){
	
}*/

CreatureCombat::CreatureCombat(const PokemonUtilisateur& _pokemon,Donnees *_d){
	nom=_pokemon.n_pk();
	pseudo=_pokemon.pseudo_pk();
	niveau=_pokemon.niv_pk();
	genre=_pokemon.genre_pk();
	nom_objet=_pokemon.objet();
	capacite=_pokemon.capacite_pk();
	ball_capture=_pokemon.ball_capt();
	capacite_act=capacite;
	attaques=_pokemon.attaques_apprises();
	attaques_act=attaques;
	ev_statistiques=_pokemon.ev_stat();
	iv_statistiques=_pokemon.iv_stat();
	pv_restants=_pokemon.pv_rest();
	exp_gagnee_depuis_der_niveau=_pokemon.exp_gagne();
	bonheur=_pokemon.bonheur_pk();
	init_creature(_d);
	statut=_pokemon.statut_pk();
}

CreatureCombat::CreatureCombat(PokemonDresse *_pokemon,Donnees *_d){
	nom=_pokemon->n_pk();
	pseudo=nom;
	bonheur=_d->constante_numerique("DEF_BONHEUR_CAPT");
	niveau=_pokemon->niv_pk();
	genre=_pokemon->genre_pk();
	nom_objet=_pokemon->objet();
	capacite=_pokemon->capacite_pk();
	capacite_act=capacite;
	foreach(QString a,_pokemon->attaq()){
		FicheAttaque *f_att_=_d->val_attaques().valeur(a);
		uchar pp_=f_att_->pps();
		attaques<<QPair<QString,QPair<uchar,uchar> >(a,QPair<uchar,uchar>(pp_,pp_));
	}
	attaques_act=attaques;
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	foreach(QString s,f_pk_->stat_ev().cles()){
		ev_statistiques.ajouter_cle_valeur(s,0);
		iv_statistiques.ajouter_cle_valeur(s,0);
	}
	exp_gagnee_depuis_der_niveau=Taux(0);
	init_creature(_d);
	pv_restants=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
	statut="OK";
}

CreatureCombat::CreatureCombat(PokemonSauvage* _pokemon,Donnees *_d){
	nom=_pokemon->n_pk();
	pseudo=nom;
	bonheur=_d->constante_numerique("DEF_BONHEUR_CAPT");
	niveau=_pokemon->niv_pk();
	genre=_pokemon->genre_pk();
	nom_objet=_pokemon->objet();
	capacite=_pokemon->capacite_pk();
	capacite_act=capacite;
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	QList<QPair<uchar,QString> > attaques_=f_pk_->atts();
	int i_plus_petit_niveau_=-1;;
	for(int i=attaques_.size()-1;i>-1;i--){
		if(attaques_[i].first<=niveau){
			i_plus_petit_niveau_=i;
			break;
		}
	}
	int nb_attaques_=0;
	while(nb_attaques_<_d->nb_att_max()){
		if(i_plus_petit_niveau_<nb_attaques_){
			break;
		}
		QString attaque_=attaques_[i_plus_petit_niveau_-nb_attaques_].second;
		FicheAttaque *f_att_=_d->val_attaques().valeur(attaque_);
		uchar pp_=f_att_->pps();
		attaques<<QPair<QString,QPair<uchar,uchar> >(attaque_,QPair<uchar,uchar>(pp_,pp_));
		nb_attaques_++;
	}
	attaques_act=attaques;
	f_pk_=_d->val_pokedex().valeur(nom);
	foreach(QString s,f_pk_->stat_ev().cles()){
		ev_statistiques.ajouter_cle_valeur(s,0);
		iv_statistiques.ajouter_cle_valeur(s,0);
	}
	exp_gagnee_depuis_der_niveau=Taux(0);
	init_creature(_d);
	pv_restants=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
	statut="OK";
}

void CreatureCombat::init_creature(Donnees *_d){
	nom_act=nom;
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom_act);
	types=f_pk_->typs();//TODO attention a la plaque
	foreach(QString s,f_pk_->stat_ev().cles()){
		statistiques_combat.ajouter_cle_valeur(s,f_pk_->stat_ev().valeur(s).first);
		statistiques_valeurs.ajouter_cle_valeur(s,s);
		boosts_statistiques.ajouter_cle_valeur(s,_d->constante_numerique("DEF_BOOST"));
	}
	boosts_statistiques.ajouter_cle_valeur("PRECISION",_d->constante_numerique("DEF_BOOST"));
	boosts_statistiques.ajouter_cle_valeur("ESQUIVE",_d->constante_numerique("DEF_BOOST"));
	boost_cc=_d->constante_numerique("DEF_BOOST_CC");
	non_switch_force=true;
	a_joue=false;
	masse=f_pk_->m_pk();
	der_attaque_lance="";
	der_attaque_reussi="";
	att_reussi=false;
	nb_tours_terrain=0;
	nb_tours_poison_grave=0;
	confusion.first=0;
	confusion.second=false;
	clone=Taux(0);
	prepa_tour=false;
	disparait=false;
	nec_recharg=false;
	nb_tours_sommeil_non_repos=0;
	attaque_choisie="";
	action_choisie="";
	coeff_roulade_ball_glace=1;
	patience.first=0;
	patience.second.first=Taux(0);
	patience.second.second=false;
	derniere_attaque_subie.first.first=Taux(0);
	derniere_attaque_subie.first.second=Taux(0);
	derniere_attaque_subie.second="";
	nb_succes_abris=0;
	gain_exper=Taux(0);
	peur=false;
	vient_de_perdre_objet=false;
	copie.first="";
	copie.second=0;
	nb_repet_att_succ=0;
	torche=false;
	atterrissage_lance.first=false;
	atterrissage_lance.second=false;
	pur_vol=false;
	//astuce_force_apres_zone_etrange=false
	utilise_baie=false;
	der_objet_ut="";
	foreach(QString t,_d->val_noms_types_fr()){
		coeff_att_types_subies.ajouter_cle_valeur(t,Taux(1));
		coeff_att_types_subies_2.ajouter_cle_valeur(t,Taux(1));
		coeff_att_types_lancees.ajouter_cle_valeur(t,Taux(1));
		immu_attaques_types.ajouter_cle_valeur(t,false);
	}
	QStringList attaques_act_ind_;
	attaques_act_ind_<<"CLAIRVOYANCE";
	attaques_act_ind_<<"OEIL_MIRACLE";
	attaques_act_ind_<<"FLAIR";
	attaques_act_ind_<<"LILLIPUT";
	attaques_act_ind_<<"ANTI_AIR";
	attaques_act_ind_<<"MAUDIT";
	attaques_act_ind_<<"VAMPIGRAINE";
	attaques_act_ind_<<"MORPHING";
	attaques_act_ind_<<"RACINES";
	attaques_act_ind_<<"COUP_D_MAIN";
	attaques_act_ind_<<"MOI_D_ABORD";
	attaques_act_ind_<<"DETREMPAGE";
	attaques_act_ind_<<"RANCUNE";
	attaques_act_ind_<<"PRLVT_DESTIN";
	attaques_act_ind_<<"TOURMENTE";
	attaques_act_ind_<<"ANNEAU_HYDRO";
	foreach(QString e,attaques_act_ind_){
		attaques_actives.ajouter_cle_valeur(e,false);
	}
	QStringList attaques_act_def_;
	attaques_act_def_<<"VOL_MAGNETIK";
	attaques_act_def_<<"LEVIKINESIE";
	attaques_act_def_<<"REPOS";
	attaques_act_def_<<"EMBARGO";
	attaques_act_def_<<"ANTI_SOIN";
	attaques_act_def_<<"AIR_VEINARD";
	attaques_act_def_<<"PROVOC";
	attaques_act_def_<<"BAILLE";
	attaques_act_def_<<"ROULADE";
	attaques_act_def_<<"BALL_GLACE";
	attaques_act_def_<<"MANIA";
	attaques_act_def_<<"COLERE";
	attaques_act_def_<<"DANSE_FLEUR";
	attaques_act_def_<<"BROUHAHA";
	foreach(QString e,attaques_act_def_){
		nb_tours_effets_attaques.ajouter_cle_valeur(e,QPair<uchar,bool>(0,false));
	}
	nb_lancers_attaques.ajouter_cle_valeur("STOCKAGE",0);
	nb_lancers_attaques.ajouter_cle_valeur("TAILLADE",0);
	maj_coeff_types_att_subie(_d);
}


void CreatureCombat::init_creature(const QList<Combattant>& _cbts,const HashMap<QString,QList<QPair<uchar,Taux> > >& _objets,Donnees* _d){
	objets=_objets;
	QStringList relations_combattants_;
	relations_combattants_<<"AMOUR";
	relations_combattants_<<"ANTI_FUITE";
	relations_combattants_<<"CAUCHEMAR";
	relations_combattants_<<"VERROUILLAGE";
	relations_combattants_<<"LIRE_ESPRIT";
	HashMap<Combattant,bool> rel_;
	foreach(Combattant c,_cbts){
		rel_.ajouter_cle_valeur(c,false);
		attaques_sur_combat_att.ajouter_cle_valeur(QPair<QString,Combattant>("ENCORE",c),QPair<QString,QPair<bool,uchar> >("",QPair<bool,uchar>(false,0)));
		attaques_sur_combat_att.ajouter_cle_valeur(QPair<QString,Combattant>("ENTRAVE",c),QPair<QString,QPair<bool,uchar> >("",QPair<bool,uchar>(false,0)));
		attaques_possessif.ajouter_cle_valeur(c,QStringList());
		foreach(QString a,_d->val_attaques_piegeantes()){
			attaques_piegeantes.ajouter_cle_valeur(QPair<Combattant,QString>(c,a),QPair<bool,uchar>(false,0));
		}
	}
	foreach(QString e,relations_combattants_){
		relations_comb.ajouter_cle_valeur(e,rel_);
	}
	init_table_eff(_cbts,_d);
}

void CreatureCombat::transfer_relais(const TransfertRelais& _elements){
	statistiques_valeurs=_elements.statistiques_valeurs;
	//capacite_act=_elements.capacite_act
	boosts_statistiques=_elements.boosts_statistiques;
	boost_cc=_elements.boost_cc;
	table_types=_elements.table_types;
	nb_lancers_attaques=_elements.nb_lancers_attaques;
	confusion=_elements.confusion;
	clone=_elements.clone;
	attaques_sur_combat_att=_elements.attaques_sur_combat_att;
	////coeff_roulade_ball_glace=_elements.coeff_roulade_ball_glace
	nb_tours_effets_attaques=_elements.nb_tours_effets_attaques;
	attaques_piegeantes=_elements.attaques_piegeantes;
	attaques_possessif=_elements.attaques_possessif;
	relations_comb=_elements.relations_comb;
	derniere_attaque_subie=_elements.derniere_attaque_subie;
	attaques_actives=_elements.attaques_actives;
	immu_attaques_types=_elements.immu_attaques_types;
	coeff_att_types_subies=_elements.coeff_att_types_subies;
	coeff_att_types_subies_2=_elements.coeff_att_types_subies_2;
	coeff_att_types_lancees=_elements.coeff_att_types_lancees;
	vient_de_perdre_objet=_elements.vient_de_perdre_objet;
	copie=_elements.copie;
	nb_repet_att_succ=_elements.nb_repet_att_succ;
	////torche=_elements.torche
	atterrissage_lance=_elements.atterrissage_lance;
	pur_vol=_elements.pur_vol;
	der_objet_ut=_elements.der_objet_ut;
}

TransfertRelais CreatureCombat::relais()const{
	TransfertRelais retour_;
	retour_.statistiques_valeurs=statistiques_valeurs;
	//retour_.//capacite_act=capacite_act
	retour_.boosts_statistiques=boosts_statistiques;
	retour_.boost_cc=boost_cc;
	retour_.table_types=table_types;
	retour_.nb_lancers_attaques=nb_lancers_attaques;
	retour_.confusion=confusion;
	retour_.clone=clone;
	retour_.attaques_sur_combat_att=attaques_sur_combat_att;
	//retour_.////coeff_roulade_ball_glace=coeff_roulade_ball_glace
	retour_.nb_tours_effets_attaques=nb_tours_effets_attaques;
	retour_.attaques_piegeantes=attaques_piegeantes;
	retour_.attaques_possessif=attaques_possessif;
	retour_.relations_comb=relations_comb;
	retour_.derniere_attaque_subie=derniere_attaque_subie;
	retour_.attaques_actives=attaques_actives;
	retour_.immu_attaques_types=immu_attaques_types;
	retour_.coeff_att_types_subies=coeff_att_types_subies;
	retour_.coeff_att_types_subies_2=coeff_att_types_subies_2;
	retour_.coeff_att_types_lancees=coeff_att_types_lancees;
	retour_.vient_de_perdre_objet=vient_de_perdre_objet;
	retour_.copie=copie;
	retour_.nb_repet_att_succ=nb_repet_att_succ;
	//retour_.////torche=torche
	retour_.atterrissage_lance=atterrissage_lance;
	retour_.pur_vol=pur_vol;
	retour_.der_objet_ut=der_objet_ut;
	return retour_;
}

void CreatureCombat::reinit_coeff_types_att(Donnees *_d){
	foreach(QString t,_d->val_noms_types_fr()){
		coeff_att_types_subies.ajouter_cle_valeur(t,Taux(1));
		coeff_att_types_subies_2.ajouter_cle_valeur(t,Taux(1));
		coeff_att_types_lancees.ajouter_cle_valeur(t,Taux(1));
	}
}

void CreatureCombat::maj_coeff_types_att_subie(Donnees *_d){
	foreach(QString t,coeff_att_types_subies.cles()){
		coeff_att_types_subies.ajouter_cle_valeur(t,Taux(1));
	}
	FicheCapacite *capac_=fiche_capacite(_d);
	if(capac_){
		foreach(QString t,capac_->immu_att_t()){
			coeff_att_types_subies.ajouter_cle_valeur(t,Taux(0));
		}
		foreach(QString t,capac_->mult_deg_adv().cles()){
			coeff_att_types_subies.valeur(t)*=capac_->mult_deg_adv().valeur(t);
		}
	}
}

QString CreatureCombat::nom_pk()const{
	return nom;
}

QString CreatureCombat::nom_pk_act()const{
	return nom_act;
}

QString CreatureCombat::pseudo_pk()const{
	return pseudo;
}

QString& CreatureCombat::pseudo_pk(){
	return pseudo;
}

QString CreatureCombat::genre_pk()const{
	return genre;
}

QStringList& CreatureCombat::types_pk(){
	return types;
}

QStringList CreatureCombat::types_pk()const{
	return types;
}

QString& CreatureCombat::ball_capt(){
	return ball_capture;
}

QString CreatureCombat::ball_capt()const{
	return ball_capture;
}

void CreatureCombat::morphing(const CreatureCombat& _creature,Donnees *_d){
	nom_act=_creature.nom_act;
	types=_creature.types;
	genre=_creature.genre;
	attaques_act.clear();
	for(int i=_creature.attaques_act.size()-1;i>-1;i--){
		attaques_act<<QPair<QString,QPair<uchar,uchar> >(_creature.attaques_act[i].first,QPair<uchar,uchar>(5,5));
	}
	FichePokemon *f_pk_=fiche_pokemon(_d);
	foreach(QString s,f_pk_->stat_ev().cles()){
		if(s!="PV"){
			statistiques_combat.ajouter_cle_valeur(s,f_pk_->stat_ev().valeur(s).first);
			boosts_statistiques.ajouter_cle_valeur(s,_creature.boosts_statistiques.valeur(s));
		}
	}
	masse=_creature.masse;
	capacite_act=_creature.capacite_act;
	attaques_actives.ajouter_cle_valeur("MORPHING",true);
}

Taux CreatureCombat::vitesse(bool _aire_eau_herbre,bool _zone_magique,bool _vent_arriere,const QPair<QPair<QString,uchar>,QPair<bool,bool> >& _climat,Donnees *_d)const{
	Taux vit_=statistique_mod_globale("VITESSE",ev_mod("VITESSE"),iv_mod("VITESSE"));
	qint8 cran_=boost("VITESSE");
	if(peut_utiliser_objet(_zone_magique)){
		ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(fiche_objet(_d));
		if(obj_){
			foreach(QString s,obj_->mult_stat().cles()){
				if(s=="VITESSE"){
					QPair<Taux,bool> val_=obj_->mult_stat().valeur(s);
					if(!val_.second){
						cran_+=val_.first;
					}
				}
			}
		}
	}
	if(_aire_eau_herbre){
		vit_*=coeff_boost(cran_-1);
	}else{
		vit_*=coeff_boost(cran_);
	}
	FicheCapacite *f_capac_=fiche_capacite(_d);
	if(f_capac_){
		if(_climat.second.first){
			typedef QPair<QString,QString> CoupleChaine;
			foreach(CoupleChaine c,f_capac_->mult_statis_clim().cles()){
				if(c.first=="VITESSE"&&c.second==_climat.first.first){
					vit_*=f_capac_->mult_statis_clim().valeur(c);
				}
			}
		}
		if(vient_de_perdre_objet){
			foreach(QString s,f_capac_->mult_statis_perd_obj().cles()){
				vit_*=f_capac_->mult_statis_perd_obj().valeur(s);
			}
		}
		typedef QPair<QString,QPair<QString,Taux> > TripletChainesCoeff;
		foreach(TripletChainesCoeff t,f_capac_->mult_statis_statut_coef()){
			if(t.first=="VITESSE"&&t.second.first==statut){
				vit_*=t.second.second;
			}
		}
	}
	if(statut=="PARALYSIE"){
		typedef QPair<QString,QString> StatistiqueStatut;
		bool existe_immu_=false;
		foreach(StatistiqueStatut s,f_capac_->immu_bais_statis_stat()){
			if(s.first=="VITESSE"&&s.second==statut){
				existe_immu_=true;
				break;
			}
		}
		if(!existe_immu_){
			vit_*=_d->constante_numerique("MULT_VITESSE_PAR");
		}
	}
	if(peut_utiliser_objet(_zone_magique)){
		ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(fiche_objet(_d));
		if(obj_){
			typedef QPair<QString,QString> StatNom;
			foreach(StatNom s,obj_->mult_stat_pk_co().cles()){
				if(s.first=="VITESSE"&&s.second==nom_act){
					vit_*=obj_->mult_stat_pk_co().valeur(s);
				}
			}
			foreach(QString s,obj_->mult_stat().cles()){
				if(s=="VITESSE"){
					QPair<Taux,bool> val_=obj_->mult_stat().valeur(s);
					if(val_.second){
						vit_*=val_.first;
					}
				}
			}
		}
	}
	if(_vent_arriere){
		vit_*=Taux(2);
	}
	//MULT_VITESSE_PAR
	//mult_statis_statut_coef()
	return vit_;
}

bool& CreatureCombat::non_switch_force_pk(){
	return non_switch_force;
}

bool& CreatureCombat::a_joue_pk(){
	return a_joue;
}

void CreatureCombat::echanger_statistiques(const QString& _nom_stat_1,const QString& _nom_stat_2){
	QString valeur_=statistiques_valeurs.valeur(_nom_stat_1);
	statistiques_valeurs.valeur(_nom_stat_1)=statistiques_valeurs.valeur(_nom_stat_2);
	statistiques_valeurs.valeur(_nom_stat_2)=valeur_;
}

Taux CreatureCombat::clone_pk()const{
	return clone;
}

Taux& CreatureCombat::clone_pk(){
	return clone;
}

Taux CreatureCombat::pv_max()const{
	return statistique_globale("PV",ev("PV"),iv("PV"));
}

Taux CreatureCombat::statistique_globale(const QString& _nom_stat,uchar _ev,uchar _iv)const{
	Taux stat_=(Taux(2)*statistiques_combat.valeur(_nom_stat)+Taux(_ev)/Taux(4)+Taux(_iv))*Taux(niveau,100LL)+Taux(5);
	if(_nom_stat=="PV"){
		stat_+=Taux(niveau+5);
	}
	return stat_;
}

Taux CreatureCombat::statistique_mod_globale(const QString& _nom_stat,uchar _ev,uchar _iv)const{
	return statistique_globale(statistiques_valeurs.valeur(_nom_stat),_ev,_iv);
}

uchar CreatureCombat::ev_mod(const QString& _nom_stat)const{
	return ev(statistiques_valeurs.valeur(_nom_stat));
}

uchar CreatureCombat::ev(const QString& _nom_stat)const{
	return ev_statistiques.valeur(_nom_stat);
}

uchar CreatureCombat::iv_mod(const QString& _nom_stat)const{
	return iv(statistiques_valeurs.valeur(_nom_stat));
}

uchar CreatureCombat::iv(const QString& _nom_stat)const{
	return iv_statistiques.valeur(_nom_stat);
}

Taux CreatureCombat::statistique(const QString& _nom_stat)const{
	return statistiques_combat.valeur(statistiques_valeurs.valeur(_nom_stat));
}

void CreatureCombat::mod_statistique(const QString& _nom_stat,const Taux& _valeur_stat){
	statistiques_combat.valeur(statistiques_valeurs.valeur(_nom_stat))=_valeur_stat;
}

HashMap<QString,uchar> CreatureCombat::ev_statistiques_pk()const{
	return ev_statistiques;
}

void CreatureCombat::gain_ev_statistique(const QString& _nom_stat,uchar _valeur_ev,uchar _max_ev){
	uchar& valeur_=ev_statistiques.valeur(_nom_stat);
	if(valeur_+_valeur_ev<_max_ev){
		valeur_+=_valeur_ev;
	}else{
		valeur_=_max_ev;
	}
	//statistiques_combat
}

Taux CreatureCombat::exp_gagnee()const{
	return exp_gagnee_depuis_der_niveau;
}

void CreatureCombat::gain_exp(const Taux& _val_exp){
	gain_exper+=_val_exp;
}

void CreatureCombat::reinit_gain_exp(){
	exp_gagnee_depuis_der_niveau=Taux(0);
}

uchar CreatureCombat::bonheur_pk()const{
	return bonheur;
}

void CreatureCombat::maj_bonheur_niveau(bool _montee_niveau,const QPair<uchar,uchar>& _soin,Donnees* _d){
	Taux mult_((long long int)1);
	ObjetAttachableCombat *obj_=NULL;
	if(nom_objet!=""){
		obj_=qobject_cast<ObjetAttachableCombat*>(fiche_objet(_d));
	}
	if(obj_&&obj_->mult_gain_bonh()>Taux((long long int)0)){
		mult_*=obj_->mult_gain_bonh();
	}
	if(_montee_niveau){
		mult_*=_d->constante_numerique("GAIN_BONHEUR_NIV");
	}
	if(luxe_ball()){
		mult_*=_d->constante_numerique("MULT_BONHEUR_LUXEBALL");
		if(_soin.second>0){
			mult_*=Taux((long long int)_soin.second);
		}
	}else{
		if(_soin.first>0){
			mult_*=Taux((long long int)_soin.first);
		}
	}
	if(Taux((long long int)bonheur)+mult_<=_d->constante_numerique("MAX_BONHEUR")){
		bonheur+=mult_;
	}else{
		bonheur=_d->constante_numerique("MAX_BONHEUR");
	}
	//bonheur+=
	//MULT_BONHEUR_LUXEBALL
}

void CreatureCombat::mettre_jour_pv_restants2(Donnees *_d,const Taux& _pv_max_anc){
	FichePokemon *f_pk_=fiche_pokemon_b(_d);
	if(!_pv_max_anc.estNul()){
		pv_restants+=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"))-_pv_max_anc;
	}else{
		pv_restants=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
	}
}

bool CreatureCombat::luxe_ball()const{
	return ball_capture=="LUXE_BALL";
}

QString CreatureCombat::capacite_pk_ini()const{
	return capacite;
}

QString& CreatureCombat::capacite_pk_act(){
	return capacite_act;
}

QString CreatureCombat::capacite_pk_act()const{
	return capacite_act;
}

FicheCapacite *CreatureCombat::fiche_capacite(Donnees *_d)const{
	if(capacite_act==""){
		return NULL;
	}
	return _d->val_capacites().valeur(capacite_act);
}

FichePokemon *CreatureCombat::fiche_pokemon(Donnees *_d)const{
	return _d->val_pokedex().valeur(nom_act);
}

FichePokemon *CreatureCombat::fiche_pokemon_b(Donnees *_d)const{
	return _d->val_pokedex().valeur(nom);
}

Objet *CreatureCombat::fiche_objet(Donnees *_d)const{
	return _d->val_objets().valeur(nom_objet);
}

uchar CreatureCombat::niveau_pk()const{
	return niveau;
}

void CreatureCombat::gain_niveau_pk(){
	niveau++;
}

Taux CreatureCombat::gain_exp_combat()const{
	return gain_exper;
}

void CreatureCombat::gain_niveau_exp(const Taux& _exp_gagne){
	//gain_exper+=_exp_gagne
	exp_gagnee_depuis_der_niveau+=_exp_gagne;
}

void CreatureCombat::reinit_pts_exp(){
	gain_exper=Taux(0);
}

bool& CreatureCombat::attaques_actives_ind(const QString& _nom_att){
	return attaques_actives.valeur(_nom_att);
}

bool CreatureCombat::attaques_actives_ind(const QString& _nom_att)const{
	return attaques_actives.valeur(_nom_att);
}

uchar& CreatureCombat::ordre_att(){
	return ordre;
}

QString& CreatureCombat::objet(){
	return nom_objet;
}

QString CreatureCombat::objet()const{
	return nom_objet;
}

bool CreatureCombat::peut_utiliser_objet(bool _zone_magique)const{
	return !_zone_magique&&!nb_tours_effets_attaques.valeur("EMBARGO").second&&nom_objet!="";
}

HashMap<QString,QList<QPair<uchar,Taux> > >& CreatureCombat::objets_pk(){
	return objets;
}

HashMap<QString,QList<QPair<uchar,Taux> > > CreatureCombat::objets_pk()const{
	return objets;
}

Taux& CreatureCombat::masse_pk(){
	return masse;
}

Taux CreatureCombat::masse_pk()const{
	return masse;
}

QString& CreatureCombat::statut_pk(){
	return statut;
}

QString CreatureCombat::statut_pk()const{
	return statut;
}

Taux& CreatureCombat::pv_restants_pk(){
	return pv_restants;
}

Taux CreatureCombat::pv_restants_pk()const{
	return pv_restants;
}

Taux CreatureCombat::soin_tout_pv(){
	Taux diff_=pv_max()-pv_restants_pk();
	pv_restants_pk()=pv_max();
	return diff_;
}

void CreatureCombat::gain_bonheur(Soin* _soin,Donnees* _d){
	uchar max_bonh_=_d->constante_numerique("MAX_BONHEUR");
	uchar tx_=1;
	if(luxe_ball()){
		tx_*=_soin->bonh().first;
	}else{
		tx_*=_soin->bonh().second;
	}
	ObjetAttachableCombat *obj_=NULL;
	if(nom_objet!=""){
		obj_=qobject_cast<ObjetAttachableCombat*>(fiche_objet(_d));
	}
	if(obj_&&obj_->mult_gain_bonh()>Taux((long long int)0)){
		tx_*=(int)obj_->mult_gain_bonh();
	}
	if(bonheur+tx_<=max_bonh_){
		bonheur+=tx_;
	}else{
		bonheur=max_bonh_;
	}
}

void CreatureCombat::soin_pv(const Taux& _pv,Taux& _pv_soignes,Donnees *_d){
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom_act);
	Taux pv_max_=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
	if(_pv+pv_restants<=pv_max_){
		_pv_soignes=_pv;
		pv_restants+=_pv;
	}else{
		_pv_soignes=pv_max_-pv_restants;
		pv_restants=pv_max_;
	}
}

void CreatureCombat::supprimer_pp(const QString& _attaque){
	for(int i=attaques_act.size()-1;i>-1;i--){
		if(attaques_act[i].first==_attaque){
			attaques_act[i].second.first=0;
		}
	}
}

void CreatureCombat::utiliser_pp(const QString& _attaque,uchar _pp){
	if(copie.first==_attaque){
		if(copie.second>=_pp){
			copie.second-=_pp;
		}else{
			copie.second=0;
		}
		return;
	}
	for(int i=attaques_act.size()-1;i>-1;i--){
		if(attaques_act[i].first==_attaque){
			if(attaques_act[i].second.first>=_pp){
				attaques_act[i].second.first-=_pp;
			}else{
				attaques_act[i].second.first=0;
			}
		}
	}
}

uchar CreatureCombat::soin_pp(const QString& _attaque,uchar _pp){
	uchar pp_rest_=0;
	for(int i=attaques_act.size()-1;i>-1;i--){
		if(attaques_act[i].first==_attaque){
			pp_rest_=attaques_act[i].second.second-attaques_act[i].second.first;
			if(attaques_act[i].second.first+_pp<=attaques_act[i].second.second){
				attaques_act[i].second.first+=_pp;
			}else{
				attaques_act[i].second.first=attaques_act[i].second.second;
			}
		}
	}
	return pp_rest_;
}

QStringList CreatureCombat::soin_pp(uchar _pp){
	QStringList attaques_;
	for(int i=attaques_act.size()-1;i>-1;i--){
		if(attaques_act[i].second.first<attaques_act[i].second.second){
			attaques_<<attaques_act[i].first;
			if(attaques_act[i].second.first+_pp<=attaques_act[i].second.second){
				attaques_act[i].second.first+=_pp;
			}else{
				attaques_act[i].second.first=attaques_act[i].second.second;
			}
		}
	}
	return attaques_;
}

uchar CreatureCombat::soin_pp(const QString& _attaque){
	uchar pp_rest_=0;
	for(int i=attaques_act.size()-1;i>-1;i--){
		if(attaques_act[i].first==_attaque){
			pp_rest_=attaques_act[i].second.second-attaques_act[i].second.first;
			attaques_act[i].second.first=attaques_act[i].second.second;
		}
	}
	return pp_rest_;
}

HashMap<QString,uchar> CreatureCombat::soin_pp(){
	HashMap<QString,uchar> attaq_rest_;
	for(int i=attaques_act.size()-1;i>-1;i--){
		uchar pp_rest_=attaques_act[i].second.second-attaques_act[i].second.first;
		attaques_act[i].second.first=attaques_act[i].second.second;
		attaq_rest_.ajouter_cle_valeur(attaques_act[i].first,pp_rest_);
	}
	return attaq_rest_;
}


int CreatureCombat::attaque_apprise_niveau(int _indice,Donnees* _d)const{
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom_act);
	QList<QPair<uchar,QString> > attaques_=f_pk_->atts();
	int nb_att_=attaques_.size();
	for(int i=_indice+1;i<nb_att_;i++){
		if(attaques_[i].first==niveau){
			bool deja_appris_=false;
			for(int j=attaques.size()-1;j>-1;j--){
				if(attaques[j].first==attaques_[i].second){
					deja_appris_=true;
					break;
				}
			}
			if(!deja_appris_){
				return i;
			}
		}
	}
	return -1;
}

QString CreatureCombat::type_attaque_lanceur_2(const QPair<QPair<QString,uchar>,QPair<bool,bool> >& _climat,const QString& _attaque_lanceur,bool _zone_magique,Donnees *_d)const{
	FicheAttaque *f_att_=_d->val_attaques().valeur(_attaque_lanceur);
	if(_attaque_lanceur=="DON_NATUREL"){
		if(!peut_utiliser_objet(_zone_magique)){
			return f_att_->tp();
		}
		Baie *baie_=qobject_cast<Baie*>(fiche_objet(_d));
		if(baie_){
			return baie_->type_puis_dn().first;
		}
		return f_att_->tp();
	}
	if(_attaque_lanceur=="JUGEMENT"){
		if(nom_objet==""){
			return f_att_->tp();
		}
		Plaque *plaque_=qobject_cast<Plaque*>(fiche_objet(_d));
		if(plaque_){
			return plaque_->tp_pl();
		}
		return f_att_->tp();
	}
	if(_attaque_lanceur=="PUIS_CACHEE"){
		return tirage_type(_d);
	}
	if(_attaque_lanceur=="BALL_METEO"){
		if(!_climat.second.first){
			return f_att_->tp();
		}
		return _d->val_types_ball_meteo().valeur(_climat.first.first);
		//TODO
	}
	if(_attaque_lanceur=="TECHNO_BUSTER"){
		if(nom_objet==""){
			return f_att_->tp();
		}
		Module *module_=qobject_cast<Module*>(fiche_objet(_d));
		if(module_){
			return module_->type();
		}
	}
	return f_att_->tp();
}

QString CreatureCombat::type_attaque_lanceur(const QPair<QPair<QString,uchar>,QPair<bool,bool> >& _climat,const QString& _attaque_lanceur,bool _zone_magique,Donnees *_d)const{
	FicheCapacite *f_capac_=fiche_capacite(_d);
	if(f_capac_){
		QString _type=f_capac_->t_att();
		if(_type!=""){
			return _type;
		}
	}
	return type_attaque_lanceur_2(_climat,_attaque_lanceur,_zone_magique,_d);
}

void CreatureCombat::apprendre_copie(const QString& _attaque){
	copie.first=_attaque;
	copie.second=5;
}

void CreatureCombat::reinit_copie(){
	copie.first="";
	copie.second=0;
}

void CreatureCombat::apprendre_attaque(const QString& _nv_att,Donnees* _d){
	uchar pp_=_d->val_attaques().valeur(_nv_att)->pps();
	for(int i=attaques_act.size();i>-1;i--){
		if(attaques_act[i].first=="GRIBOUILLE"){
			attaques_act[i].first=_nv_att;
			attaques_act[i].second=QPair<uchar,uchar>(pp_,pp_);
			for(int j=attaques.size();j>-1;j--){
				if(attaques[j].first=="GRIBOUILLE"){
					attaques[j].first=_nv_att;
					attaques[j].second=QPair<uchar,uchar>(pp_,pp_);
					break;
				}
			}
			break;
		}
	}
}

void CreatureCombat::apprendre_attaque(const QString& _nv_att,int _indice,Donnees *_d,QString& _anc_att){
	uchar pp_=_d->val_attaques().valeur(_nv_att)->pps();
	if(attaques_act!=attaques){
		if(_indice>=attaques.size()){
			attaques<<QPair<QString,QPair<uchar,uchar> >(_nv_att,QPair<uchar,uchar>(pp_,pp_));
		}else{
			_anc_att=attaques[_indice].first;
			attaques[_indice].first=_nv_att;
			attaques[_indice].second=QPair<uchar,uchar>(pp_,pp_);
		}
	}else if(_indice>=attaques.size()){
		attaques<<QPair<QString,QPair<uchar,uchar> >(_nv_att,QPair<uchar,uchar>(pp_,pp_));
		attaques_act<<QPair<QString,QPair<uchar,uchar> >(_nv_att,QPair<uchar,uchar>(pp_,pp_));
	}else{
		_anc_att=attaques[_indice].first;
		attaques[_indice].first=_nv_att;
		attaques[_indice].second=QPair<uchar,uchar>(pp_,pp_);
		attaques_act[_indice].first=_nv_att;
		attaques_act[_indice].second=QPair<uchar,uchar>(pp_,pp_);
	}
}

QStringList CreatureCombat::noms_attaques_act()const{
	typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
	QStringList liste_;
	foreach(AttaquePP a,attaques_act){
		if(a.first=="COPIE"&&copie.first!=""){
			liste_<<copie.first;
		}else{
			liste_<<a.first;
		}
	}
	return liste_;
}

uchar CreatureCombat::nb_pp_max(const QString& _attaque)const{
	if(_attaque==copie.first){
		return 5;
	}
	uchar nb_=0;
	typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
	foreach(AttaquePP a,attaques_act){
		if(a.first==_attaque){
			nb_=a.second.second;
			break;
		}
	}
	return nb_;
}

uchar CreatureCombat::nb_pp(const QString& _attaque)const{
	if(_attaque==copie.first){
		return copie.second;
	}
	uchar nb_=0;
	typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
	foreach(AttaquePP a,attaques_act){
		if(a.first==_attaque){
			nb_=a.second.first;
			break;
		}
	}
	return nb_;
}

QList<QPair<QString,QPair<uchar,uchar> > > CreatureCombat::attaques_pk()const{
	return attaques;
}

QList<QPair<QString,QPair<uchar,uchar> > > CreatureCombat::attaques_act_pk()const{
	return attaques_act;
}

uchar& CreatureCombat::r_boost_cc(){
	return boost_cc;
}

uchar CreatureCombat::r_boost_cc()const{
	return boost_cc;
}

QList<QString> CreatureCombat::statis_boost()const{
	return boosts_statistiques.cles();
}

qint8 CreatureCombat::boost(const QString& _nom_stat)const{
	return boosts_statistiques.valeur(_nom_stat);
}

void CreatureCombat::reinit_boost(const QString& _nom_stat,Donnees* _d){
	boosts_statistiques.ajouter_cle_valeur(_nom_stat,_d->constante_numerique("DEF_BOOST"));
}

void CreatureCombat::var_boost(const QString& _nom_stat,qint8 _var,Donnees* _d){
	qint8& valeur_=boosts_statistiques.valeur(_nom_stat);
	qint8 n_valeur_=valeur_+_var;
	int borne_;
	Taux borne_tx_;
	if(_var>0){
		borne_tx_=_d->constante_numerique("MAX_BOOST");
	}else{
		borne_tx_=_d->constante_numerique("MIN_BOOST");
	}
	if(borne_tx_>=Taux(0)){
		borne_=borne_tx_;
	}else{
		borne_=(uchar)(-borne_tx_);
		borne_=-borne_;
	}
	if(n_valeur_*_var<borne_*_var){
		valeur_+=_var;
	}else{
		valeur_=borne_;
	}
}

void CreatureCombat::init_table_eff(const QList<Combattant>& _ls_cbt,Donnees* _d){
	foreach(Combattant c,_ls_cbt){
		ajouter_table_eff(c,_d);
	}
}

void CreatureCombat::reinit_table_eff(Donnees* _d,int _arriere){
	foreach(Combattant c,table_types.cles()){
		if(c.position()!=_arriere){
			ajouter_table_eff(c,_d);
		}
	}
}

void CreatureCombat::mise_a_jour_coeff_eff(const QString& _attaque,const HashMap<Combattant,QPair<uchar,uchar> >& _positions_places,Donnees *_d,int _arriere){
	//TODO a tester plus tard
	typedef QPair<uchar,uchar> PosPlace;
	foreach(PosPlace c,cibles_choisies){
		QList<Combattant> cles_=_positions_places.cles(c);
		if(cles_.isEmpty()||cles_[0].position()==_arriere){
			continue;
		}
		foreach(Effet *e,_d->val_attaques().valeur(_attaque)->effs()){
			EffetAntiImmu *effet_=qobject_cast<EffetAntiImmu*>(e);
			if(effet_){
				typedef QPair<QString,QString> AntiImm;
				foreach(AntiImm a,effet_->tp()){
					table_eff(cles_[0],a)=Taux((long long int)1);
				}
			}
		}
	}
}

void CreatureCombat::ajouter_table_eff(const Combattant& _cbt,Donnees *_d){
	table_types.ajouter_cle_valeur(_cbt,_d->val_table_types_base());
}

HashMap<Combattant,HashMap<QPair<QString,QString>,Taux> > CreatureCombat::table()const{
	return table_types;
}

Taux& CreatureCombat::table_eff(const Combattant& _cbt,const QPair<QString,QString>& _couple_types){
	return table_types.valeur(_cbt).valeur(_couple_types);
}

Taux CreatureCombat::table_eff(const Combattant& _cbt,const QPair<QString,QString>& _couple_types)const{
	return table_types.valeur(_cbt).valeur(_couple_types);
}

QString& CreatureCombat::der_att_lancee(){
	return der_attaque_lance;
}

QString CreatureCombat::der_att_lancee()const{
	return der_attaque_lance;
}

QString& CreatureCombat::der_att_reussie(){
	return der_attaque_reussi;
}

QString CreatureCombat::der_att_reussie()const{
	return der_attaque_reussi;
}

bool& CreatureCombat::att_reussie(){
	return att_reussi;
}

bool CreatureCombat::att_reussie()const{
	return att_reussi;
}

int& CreatureCombat::nb_lancer(const QString& _nom_attaque){
	return nb_lancers_attaques.valeur(_nom_attaque);
}

int CreatureCombat::nb_lancer(const QString& _nom_attaque)const{
	return nb_lancers_attaques.valeur(_nom_attaque);
}

void CreatureCombat::gain_nb_tours_terrain_pk(){
	nb_tours_terrain++;
}

void CreatureCombat::reinit_tours_terrain(){
	nb_tours_terrain=0;
}

uchar CreatureCombat::nb_tours_terrain_pk()const{
	return nb_tours_terrain;
}

void CreatureCombat::gain_nb_tours_poison_grave(){
	nb_tours_poison_grave++;
}

void CreatureCombat::reinit_nb_tours_poison_grave(){
	nb_tours_poison_grave=0;
}

uchar CreatureCombat::nb_tours_poison_grave_pk()const{
	return nb_tours_poison_grave;
}

QPair<uchar,bool>& CreatureCombat::attaques_actives_def(const QString& _nom_attaque){
	return nb_tours_effets_attaques.valeur(_nom_attaque);
}

QPair<uchar,bool> CreatureCombat::attaques_actives_def(const QString& _nom_attaque)const{
	return nb_tours_effets_attaques.valeur(_nom_attaque);
}

QPair<uchar,bool>& CreatureCombat::confusion_pk(){
	return confusion;
}

QPair<uchar,bool> CreatureCombat::confusion_pk()const{
	return confusion;
}

Taux& CreatureCombat::pv_clone(){
	return clone;
}

bool& CreatureCombat::prepa_tour_pk(){
	return prepa_tour;
}

bool CreatureCombat::prepa_tour_pk()const{
	return prepa_tour;
}

bool& CreatureCombat::disparition_pk(){
	return disparait;
}

bool CreatureCombat::disparition_pk()const{
	return disparait;
}

bool& CreatureCombat::nec_recharg_pk(){
	return nec_recharg;
}

bool CreatureCombat::nec_recharg_pk()const{
	return nec_recharg;
}

uchar& CreatureCombat::sommeil_non_repos(){
	return nb_tours_sommeil_non_repos;
}

uchar CreatureCombat::sommeil_non_repos()const{
	return nb_tours_sommeil_non_repos;
}

QString& CreatureCombat::att_choisie(){
	return attaque_choisie;
}

QString CreatureCombat::att_choisie()const{
	return attaque_choisie;
}

QString& CreatureCombat::act_choisie(){
	return action_choisie;
}

QString CreatureCombat::act_choisie()const{
	return action_choisie;
}

HashMap<QPair<QString,Combattant>,QPair<QString,QPair<bool,uchar> > > CreatureCombat::attaques_sur_cible()const{
	return attaques_sur_combat_att;
}

QPair<QString,QPair<bool,uchar> >& CreatureCombat::cible_atts(const QPair<QString,Combattant>& _cible){
	return attaques_sur_combat_att.valeur(_cible);
}

QPair<QString,QPair<bool,uchar> > CreatureCombat::cible_atts(const QPair<QString,Combattant>& _cible)const{
	return attaques_sur_combat_att.valeur(_cible);
}

uchar& CreatureCombat::coeff_roul_ballglace(){
	return coeff_roulade_ball_glace;
}

uchar CreatureCombat::coeff_roul_ballglace()const{
	return coeff_roulade_ball_glace;
}

HashMap<QPair<Combattant,QString>,QPair<bool,uchar> > CreatureCombat::h_attaques_piegeantes()const{
	return attaques_piegeantes;
}

QList<QPair<Combattant,QString> > CreatureCombat::val_attaques_piegeantes()const{
	return attaques_piegeantes.cles();
}

QPair<bool,uchar>& CreatureCombat::att_pieg(const QPair<Combattant,QString>& _cible_attaque){
	return attaques_piegeantes.valeur(_cible_attaque);
}

HashMap<Combattant,QStringList> CreatureCombat::possessif()const{
	return attaques_possessif;
}

QStringList& CreatureCombat::poss_pk(const Combattant& _cible){
	return attaques_possessif.valeur(_cible);
}

HashMap<QString,HashMap<Combattant,bool> > CreatureCombat::relations()const{
	return relations_comb;
}

bool& CreatureCombat::att_active_cible(const QString& _nom_attaque,const Combattant& _cible){
	return relations_comb.valeur(_nom_attaque).valeur(_cible);
}

bool CreatureCombat::att_active_cible(const QString& _nom_attaque,const Combattant& _cible)const{
	return relations_comb.valeur(_nom_attaque).valeur(_cible);
}

QPair<QPair<Taux,Taux>,QString>& CreatureCombat::att_deg_subie(){
	return derniere_attaque_subie;
}

QPair<QPair<Taux,Taux>,QString> CreatureCombat::att_deg_subie()const{
	return derniere_attaque_subie;
}

void CreatureCombat::gain_nb_succes_abris(){
	nb_succes_abris++;
}

void CreatureCombat::reinit_nb_succes_abris(){
	nb_succes_abris=0;
}

uchar CreatureCombat::succes_abris()const{
	return nb_succes_abris;
}

void CreatureCombat::gain_nb_utilisation_attaques(){
	nb_repet_att_succ++;
}

void CreatureCombat::reinit_nb_utilisation_attaques(){
	nb_repet_att_succ=0;
}

uchar CreatureCombat::util_attaques_succ()const{
	return  nb_repet_att_succ;
}

QList<QPair<uchar,uchar> >& CreatureCombat::cibles(){
	return cibles_choisies;
}

QList<QPair<uchar,uchar> > CreatureCombat::cibles()const{
	return cibles_choisies;
}

Combattant& CreatureCombat::remplacant(){
	return envoye;
}

Combattant CreatureCombat::remplacant()const{
	return envoye;
}

bool& CreatureCombat::peur_pk(){
	return peur;
}

/*void CreatureCombat::maj_coeff_att_types_subies(const QString& _nom_type){
	coeff_att_types_subies.valeur(_nom_type)=Taux(1)
}

void CreatureCombat::maj_coeff_att_types_subies(const QString& _nom_type,const Taux& _coeff){
	coeff_att_types_subies.valeur(_nom_type)*=_coeff
}*/

Taux CreatureCombat::coeff_att_type(const QString& _nom_type)const{
	return coeff_att_types_subies.valeur(_nom_type);
}

Taux& CreatureCombat::coeff_att_type(const QString& _nom_type){
	return coeff_att_types_subies.valeur(_nom_type);
}

void CreatureCombat::reinit_immu_attaques_type(){
	foreach(QString t,immu_attaques_types.cles()){
		immu_attaques_types.valeur(t)=false;
	}
}

bool CreatureCombat::immu_att_type(const QString& _nom_type)const{
	return immu_attaques_types.valeur(_nom_type);
}

bool& CreatureCombat::immu_att_type(const QString& _nom_type){
	return immu_attaques_types.valeur(_nom_type);
}

Taux& CreatureCombat::r_coeff_att_types_lancees(const QString& _nom){
	return coeff_att_types_lancees.valeur(_nom);
}

Taux CreatureCombat::r_coeff_att_types_lancees(const QString& _nom)const{
	return coeff_att_types_lancees.valeur(_nom);
}

void CreatureCombat::maj_coeff_att_types_subies_2(const QString& _nom_type){
	coeff_att_types_subies_2.valeur(_nom_type)=Taux(1);
}

void CreatureCombat::maj_coeff_att_types_subies_2(const QString& _nom_type,const Taux& _coeff){
	coeff_att_types_subies_2.valeur(_nom_type)*=_coeff;
}

Taux CreatureCombat::coeff_att_type_2(const QString& _nom_type)const{
	return coeff_att_types_subies_2.valeur(_nom_type);
}

bool& CreatureCombat::perte_objet(){
	return vient_de_perdre_objet;
}

QPair<QString,uchar>& CreatureCombat::att_copie(){
	return copie;
}

QPair<QString,uchar> CreatureCombat::att_copie()const{
	return copie;
}

bool& CreatureCombat::torche_pk(){
	return torche;
}

bool CreatureCombat::torche_pk()const{
	return torche;
}

QPair<bool,bool>& CreatureCombat::atterrissage(){
	return atterrissage_lance;
}

QPair<bool,bool> CreatureCombat::atterrissage()const{
	return atterrissage_lance;
}

bool& CreatureCombat::pur_vol_atterr(){
	return pur_vol;
}

/*bool* CreatureCombat::ast_force_ap_z_etr(){
	
}*/

QPair<uchar,QPair<Taux,bool> >& CreatureCombat::patience_pk(){
	return patience;
}

QPair<uchar,QPair<Taux,bool> > CreatureCombat::patience_pk()const{
	return patience;
}

void CreatureCombat::evoluer(FichePokemon *_f_pk,int _indice_evo,Donnees *_d){
	bool egal_=nom==nom_act;
	nom=_f_pk->pokemons_evolues()[_indice_evo];
	if(egal_){
		nom_act=nom;
	}
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	masse*=f_pk_->m_pk()/_f_pk->m_pk();
	Taux pv_max_base_=statistique_globale("PV",ev("PV"),iv("PV"));
	foreach(QString s,statistiques_combat.cles()){
		statistiques_combat.ajouter_cle_valeur(s,f_pk_->stat_ev().valeur(s).first);
	}
	Taux pv_max_evo_=statistique_globale("PV",ev("PV"),iv("PV"));
	if(pv_max_evo_>=pv_max_base_){
		pv_restants+=pv_max_evo_-pv_max_base_;
	}else if(pv_restants>pv_max_evo_){
		pv_restants=pv_max_evo_;
	}
	QStringList capacs_=f_pk_->capac();
	egal_=capacite==capacite_act;
	if(capacs_.size()==1){
		capacite=capacs_[0];
	}else if(!capacs_.contains(capacite)){
		//QStringList capacites_=f_pk_->capac()
		MonteCarlo<QString> loi_capac_;
		foreach(QString c,capacs_){
			loi_capac_.ajouter_event(QPair<QString,Entier>(c,Entier(1)));
		}
		capacite=loi_capac_.tirage();
	}
	if(egal_){
		capacite_act=capacite;
	}
	QStringList types_b_=types;
	types_b_.sort();
	QStringList types_e_=_f_pk->typs();
	types_e_.sort();
	egal_=types_b_==types_e_;
	if(egal_){
		types=f_pk_->typs();
	}
}

int CreatureCombat::existence_evolution_niveau(FichePokemon *_f_pk,const QStringList& _noms_pk_ut,int _indice_evo,const Taux& _rapport,Donnees *_d)const{
	QStringList pk_evos_=_f_pk->pokemons_evolues();
	int nb_evos_=pk_evos_.size();
	for(int i=_indice_evo+1;i<nb_evos_;i++){
		if(peut_evoluer(_f_pk->facon_evoluer(pk_evos_[i]),_noms_pk_ut,_rapport,_d)){
			return i;
		}
	}
	return -1;
}

bool CreatureCombat::peut_evoluer(Evolution *_evo,const QStringList& _noms_pk_ut,const Taux& _rapport,Donnees *_d)const{
	EvolutionNiveau* evo_niv_=qobject_cast<EvolutionNiveau*>(_evo);
	if(evo_niv_){
		EvolutionNiveauGenre* evo_niv_genre_=qobject_cast<EvolutionNiveauGenre*>(evo_niv_);
		if(evo_niv_genre_){
			if(evo_niv_genre_->gr()!=genre||niveau<evo_niv_genre_->niv()){
				return false;
			}
		}else{
			EvolutionConditionStat* evo_niv_cond_=qobject_cast<EvolutionConditionStat*>(evo_niv_);
			if(evo_niv_cond_){
				Taux stat_att_=statistique_globale("ATTAQUE",ev("ATTAQUE"),iv("ATTAQUE"));
				Taux stat_def_=statistique_globale("DEFENSE",ev("DEFENSE"),iv("DEFENSE"));
				Taux rapport_=(stat_att_-stat_def_).absolu()/Utilitaire::max_min<Taux>(stat_att_,stat_def_).first;
				Taux rapport_max_=_rapport;
				if(evo_niv_cond_->stat()==""){
					if(rapport_>rapport_max_){
						return false;
					}
				}
				if(evo_niv_cond_->stat()=="ATTAQUE"){
					if(rapport_<=rapport_max_||stat_att_<=stat_def_){
						return false;
					}
				}
				if(evo_niv_cond_->stat()=="DEFENSE"){
					if(rapport_<=rapport_max_||stat_att_>=stat_def_){
						return false;
					}
				}
				if(niveau<evo_niv_cond_->niv()){
					return false;
				}
			}else{
				if(niveau<evo_niv_->niv()){
					return false;
				}
			}
		}
	}
	EvolutionBonheur *evo_bon_=qobject_cast<EvolutionBonheur*>(_evo);
	if(evo_bon_){
		if(bonheur<(int)_d->constante_numerique("EVO_BONHEUR")){
			return false;
		}
	}
	EvolutionAttaque *evo_attaque_=qobject_cast<EvolutionAttaque*>(_evo);
	if(evo_attaque_){
		bool existe_att_=false;
		for(int i=attaques.size()-1;i>-1;i--){
			if(attaques[i].first==evo_attaque_->attaque()){
				existe_att_=true;
			}
		}
		if(!existe_att_){
			return false;
		}
	}
	EvolutionObjet *evo_objet_=qobject_cast<EvolutionObjet*>(_evo);
	if(evo_objet_){
		if(evo_objet_->nom_objet()!=nom_objet){
			return false;
		}
	}
	EvolutionPlace *evo_place_=qobject_cast<EvolutionPlace*>(_evo);
	if(evo_place_){
		if(!_noms_pk_ut.contains(evo_place_->nom())){
			return false;
		}
	}
	if(qobject_cast<EvolutionPierreEvolutive*>(_evo)){
		return false;
	}
	return true;
}


void CreatureCombat::activer_baie(Baie* _baie,Donnees *_d,Taux& _pv_soignes){
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom_act);
	FicheCapacite *f_capac_=_d->val_capacites().valeur(capacite);
	if(_baie->s_pp().first!=""){
		int nb_pp_=Taux::parse_taux(_baie->s_pp().first);
		for(int i=attaques.size()-1;i>-1;i--){
			if(attaques[i].first==attaques_act[i].first&&attaques_act[i].first==der_attaque_lance){
				if(attaques[i].second.second>=nb_pp_+attaques[i].second.first){
					attaques[i].second.first+=nb_pp_;
				}else{
					attaques[i].second.first=attaques[i].second.second;
				}
			}
		}
	}
	if(_baie->mult_stat().total()>0){
		foreach(QString s,_baie->mult_stat().cles()){
			//boosts_statistiques.valeur
			qint8 valeur_=_baie->mult_stat().valeur(s).second;
			var_boost(s,f_capac_->taux_act(valeur_<0)*Taux(valeur_),_d);
		}
	}
	if(_baie->s_pv().first!=Taux(0)){
		//_baie->s_pv().second*
		Taux taux_=f_capac_->ut_baie_soin_pv();
		if(taux_.estNul()){
			taux_=Taux(1);
		}
		if(_baie->s_pv().second/taux_*f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"))>=pv_restants){
			soin_pv(_baie->s_pv().first,_pv_soignes,_d);
		}
	}
	if(_baie->s_statut().contains(statut)){
		statut="OK";
	}
	if(_baie->s_statut().contains("CONFUSION")){
		confusion.first=0;
		confusion.second=false;
	}
	if(_baie->s_tx_pv().first!=Taux(0)){
		Taux pv_=_baie->s_tx_pv().first*f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
		soin_pv(pv_,_pv_soignes,_d);
	}
	if(_baie->gain_pv_sup_ef()!=Taux(0)){
		Taux pv_=_baie->gain_pv_sup_ef()*f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
		soin_pv(pv_,_pv_soignes,_d);
	}
	utilise_baie=true;
}

void CreatureCombat::activer_capacite(bool _activer,Donnees *_d,const HashMap<Combattant,QPair<uchar,uchar> >& _creatures,bool zone_magique,int _arriere,QPair<QPair<QString,uchar>,QPair<bool,bool> >& _climat,Taux& _pv_soignes){
	if(!_activer){
		return;
	}
	FicheCapacite *f_capac_=_d->val_capacites().valeur(capacite);
	if(f_capac_->ant_clim()){
		_climat.second.first=false;
	}
	typedef QPair<QString,QString> CoupleTypes;
	foreach(CoupleTypes c,f_capac_->anti_immu_att()){
		foreach(Combattant c2,table_types.cles()){
			if(_creatures.valeur(c2).second==_arriere){
				continue;
			}
			table_eff(c2,c)=Taux(1);
		}
	}
	if(f_capac_->div_tr_som()>0){
		QPair<uchar,bool>& valeur_=nb_tours_effets_attaques.valeur("REPOS");
		if(valeur_.first==2){
			statut="OK";
			valeur_.first=0;
			valeur_.second=false;
		}else if(nb_tours_sommeil_non_repos*f_capac_->div_tr_som()==(int)_d->constante_numerique("MAX_SOMMEIL")){
			statut="OK";
			nb_tours_sommeil_non_repos=0;
		}
	}
	typedef QPair<QString,QString> StatistiqueStatut;
	int def_boost_=_d->constante_numerique("DEF_BOOST");
	foreach(QString s,f_capac_->immu_bais_statis()){
		qint8& boost_=boosts_statistiques.valeur(s);
		if(boost_<def_boost_){
			boost_=def_boost_;
		}
	}
	foreach(StatistiqueStatut s,f_capac_->immu_bais_statis_stat()){
		if(s.second==statut){
			qint8& boost_=boosts_statistiques.valeur(s.first);
			if(boost_<def_boost_){
				boost_=def_boost_;
			}
		}
	}
	Taux taux_=f_capac_->ut_baie_soin_pv();
	if(!taux_.estNul()){
		if(!nb_tours_effets_attaques.valeur("EMBARGO").second&&!zone_magique){
			if(nom_objet!=""){
				Baie *baie_=qobject_cast<Baie*>(_d->val_objets().valeur(nom_objet));
				if(baie_&&baie_->s_pv().second/taux_*pv_max()>=pv_restants){
					activer_baie(baie_,_d,_pv_soignes);
				}
			}
		}
	}
	//attaques_actives
	//immu_bais_statis_stat()
	//
	if(_climat.second.first||_climat.first.first==""){
		foreach(QString c,f_capac_->immu_stat().cles()){
			if(f_capac_->immu_stat().valeur(c).contains(statut)&&c==_climat.first.first){
				if(Utilitaire::traduisible(_d->val_noms_statuts(),statut)){
					statut="OK";
				}
			}else if(f_capac_->immu_stat().valeur(c).contains("CONFUSION")&&c==_climat.first.first){
				confusion.first=0;
				confusion.second=false;
			}else if(f_capac_->immu_stat().valeur(c).contains("AMOUR")&&c==_climat.first.first){
				foreach(Combattant _cbt,relations_comb.valeur("AMOUR").cles()){
					relations_comb.valeur("AMOUR").valeur(_cbt)=false;
				}
			}
		}
	}
	if(_climat.second.first){
		foreach(QString s,f_capac_->chgt_type_clim().cles()){
			if(s==_climat.first.first){
				types.clear();
				types<<f_capac_->chgt_type_clim().valeur(s);
			}
		}
	}
}

void CreatureCombat::desactiver_capacite(bool _suc,const HashMap<Combattant,QPair<uchar,uchar> >& _creatures,int _arriere,Donnees *_d,QPair<QPair<QString,uchar>,QPair<bool,bool> >& _climat){
	if(capacite_act==capacite&&!_suc){
		return;
	}
	FicheCapacite *f_capac_=_d->val_capacites().valeur(capacite);
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom_act);
	if(f_capac_->ant_clim()){
		if(_climat.first.first!=""){
			_climat.second.first=true;
		}
	}
	foreach(QString t,coeff_att_types_subies.cles()){
		coeff_att_types_subies.ajouter_cle_valeur(t,Taux(1));
	}
	typedef QPair<QString,QString> CoupleTypes;
	foreach(CoupleTypes c,f_capac_->anti_immu_att()){
		foreach(Combattant c2,table_types.cles()){
			if(_creatures.valeur(c2).second==_arriere){
				continue;
			}
			table_eff(c2,c)=Taux(0);
		}
	}
	if(f_capac_->chgt_type_clim().total()>0||f_capac_->chgt_type_deg()){
		types=f_pk_->typs();
	}
}

void CreatureCombat::annuler_patience(){
	patience.first=0;
	patience.second.first=Taux(0);
	patience.second.second=false;
}

QStringList CreatureCombat::attaques_avec_pp()const{
	QStringList attaques_;
	for(int i=attaques_act.size()-1;i>-1;i--){
		if(attaques_act[i].second.first>0){
			attaques_<<attaques_act[i].first;
		}
	}
	return attaques_;
}

bool CreatureCombat::existence_attaques_lanceur_un_pp_max()const{
	for(int i=attaques_act.size()-1;i>-1;i--){
		if(attaques_act[i].second.first<attaques_act[i].second.second){
			return true;
		}
	}
	return false;
}

Taux CreatureCombat::calcul_picots(int _nb_picots)const{
	return statistique_globale("PV",ev("PV"),iv("PV"))*Taux((long long int)(_nb_picots+1),(long long int)16);
}

Taux CreatureCombat::calcul_pieges_roche(Donnees* _d)const{
	Taux degats_=statistique_globale("PV",ev("PV"),iv("PV"));
	foreach(QString t,types){
		degats_*=_d->val_table_types_base().valeur(QPair<QString,QString>("ROCHE",t));
	}
	return degats_/Taux((long long int)8);
}

bool& CreatureCombat::utilisation_baie(){
	return utilise_baie;
}

bool CreatureCombat::bloque()const{
	bool bloque_=attaques_actives_def("MANIA")==QPair<uchar,bool>(0,false);
	bloque_|=attaques_actives_def("COLERE")==QPair<uchar,bool>(0,false);
	bloque_|=attaques_actives_def("DANSE_FLEUR")==QPair<uchar,bool>(0,false);
	bloque_|=attaques_actives_def("ROULADE")==QPair<uchar,bool>(0,false);
	bloque_|=attaques_actives_def("BALL_GLACE")==QPair<uchar,bool>(0,false);
	return bloque_||prepa_tour||nec_recharg||patience.second.second;
}

/*void CreatureCombat::affecterPkUt(const PokemonUtilisateur& _pokemon){
	
}

void CreatureCombat::affecterPkDr(const PokemonDresse& _pokemon){
	
}

void CreatureCombat::affecterPkSa(const PokemonSauvage& _pokemon){
	
}*/

/*CreatureCombat CreatureCombat::operator=(const CreatureCombat& _autre){
	
}*/

Taux CreatureCombat::calcul_degats_confusion(const QPair<QPair<QString,uchar>,QPair<bool,bool> >& _climat,bool _zone_magique,uchar _modele,Donnees *_d)const{
	Taux puissance_base_(40);
	Taux hh_(1);
	if(attaques_actives.valeur("COUP_D_MAIN")){
		hh_*=Taux(3,2LL);
	}
	Taux puissance_=hh_*puissance_base_;
	QString nom_stat_="ATTAQUE";
	Taux att_=statistique_mod_globale(nom_stat_,ev_mod(nom_stat_),iv_mod(nom_stat_));
	qint8 max_b_=_d->constante_numerique("MAX_BOOST");
	qint8 cran_=boost(nom_stat_);
	if(peut_utiliser_objet(_zone_magique)){
		ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(fiche_objet(_d));
		if(obj_){
			foreach(QString s,obj_->mult_stat().cles()){
				if(s==nom_stat_){
					QPair<Taux,bool> val_=obj_->mult_stat().valeur(s);
					if(!val_.second){
						cran_+=val_.first;
					}
				}
			}
		}
	}
	Taux boost_;
	if(cran_<=max_b_){
		boost_=coeff_boost(cran_);
	}else{
		boost_=coeff_boost(max_b_);
	}
	Taux am_(1);
	FicheCapacite *f_capac_=fiche_capacite(_d);
	if(f_capac_){
		foreach(QString s,f_capac_->mult_statis().cles()){
			if(s==nom_stat_){
				QPair<Taux,bool> valeur_=f_capac_->mult_statis().valeur(s);
				if(valeur_.second){
					am_*=valeur_.first;
				}
			}
		}
		typedef QPair<QString,QPair<QString,Taux> > StatistiqueStatutCoeff;
		foreach(StatistiqueStatutCoeff t,f_capac_->mult_statis_statut_coef()){
			if(t.first==nom_stat_&&t.second.first==statut){
				am_*=t.second.second;
			}
		}
		if(_climat.second.first){
			typedef QPair<QString,QString> CoupleChaine;
			foreach(CoupleChaine c,f_capac_->mult_statis_clim().cles()){
				if(c.first==nom_stat_&&c.second==_climat.first.first){
					am_*=f_capac_->mult_statis_clim().valeur(c);
				}
			}
		}
	}
	Taux im_(1);
	if(peut_utiliser_objet(_zone_magique)){
		ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(fiche_objet(_d));
		if(obj_){
			typedef QPair<QString,QString> StatNom;
			foreach(StatNom s,obj_->mult_stat_pk_co().cles()){
				if(s.first==nom_stat_&&s.second==nom_act){
					im_*=obj_->mult_stat_pk_co().valeur(s);
				}
			}
			foreach(QString s,obj_->mult_stat().cles()){
				if(s==nom_stat_){
					QPair<Taux,bool> val_=obj_->mult_stat().valeur(s);
					if(val_.second){
						im_*=val_.first;
					}
				}
			}
		}
	}
	att_*=am_*im_;
	nom_stat_="DEFENSE";
	Taux def_=statistique_mod_globale(nom_stat_,ev_mod(nom_stat_),iv_mod(nom_stat_));
	cran_=boost(nom_stat_)+nb_lancer("STOCKAGE");
	if(peut_utiliser_objet(_zone_magique)){
		ObjetAttachableCombat *obj_=qobject_cast<ObjetAttachableCombat*>(fiche_objet(_d));
		if(obj_){
			foreach(QString s,obj_->mult_stat().cles()){
				if(s==nom_stat_){
					QPair<Taux,bool> val_=obj_->mult_stat().valeur(s);
					if(!val_.second){
						cran_+=val_.first;
					}
				}
			}
		}
	}
	def_*=coeff_boost(Utilitaire::max_min<qint8>(max_b_,cran_).second);
	Taux degats_=Taux(niveau+5,125LL)*puissance_*att_/def_;
	degats_+=Taux(2);
	MonteCarloNombre loi_=loi_random(_modele);
	if(degats_*loi_.minimum()>=pv_restants){
		return degats_;
	}
	degats_*=loi_.tirage();
	return degats_;
}

bool CreatureCombat::tirage_confusion_nb_tour(Donnees *_d)const{
	if(confusion.first==(int)_d->constante_numerique("MAX_CONFUSION")){
		return true;
	}
	MonteCarlo<bool> loi_;
	Taux proba_=_d->constante_numerique("PROBA_CONFUSION");
	Entier proba_1_=proba_.gnumerateur();
	Entier proba_2_=proba_.gdenominateur()-proba_1_;
	loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi_.tirage();
}

bool CreatureCombat::tirage_effet_continuer(const MonteCarloNombre& loi,const Taux& event){
	return loi.loi_sachant_sup(event).tirage();
}

QStringList CreatureCombat::types_conversion_2(const QString& _derniere_attaque_subie,Donnees *_d)const{
	QStringList types_;
	QString type_=_d->val_attaques().valeur(_derniere_attaque_subie)->tp();
	foreach(QString t,_d->val_noms_types_fr()){
		if(_d->val_table_types_base().valeur(QPair<QString,QString>(type_,t))<Taux(1)&&!types_.contains(t)&&!types.contains(t)){
			types_<<t;
		}
	}
	return types_;
}

QString CreatureCombat::tirage_conversion_2(const QString& _derniere_attaque_subie,Donnees *_d)const{
	MonteCarlo<QString> loi_;
	foreach(QString t,types_conversion_2(_derniere_attaque_subie,_d)){
		loi_.ajouter_event(QPair<QString,Entier>(t,Entier(1)));
	}
	return loi_.tirage();
}

bool CreatureCombat::tirage_auto_inflige(Donnees *_d)const{
	MonteCarlo<bool> loi_;
	Taux proba_=_d->constante_numerique("PROBA_AUTO_INFL");
	Entier proba_1_=proba_.gnumerateur();
	Entier proba_2_=proba_.gdenominateur()-proba_1_;
	loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi_.tirage();
}

QStringList CreatureCombat::types_adaptation(Donnees *_d)const{
	QStringList types_t_;
	for(int i=attaques_act.size()-1;i>-1;i--){
		QString type_=_d->val_attaques().valeur(attaques_act[i].first)->tp();
		if(!types_t_.contains(type_)&&attaques_act[i].first!="MALEDICTION"&&!types.contains(type_)){
			types_t_<<type_;
		}
	}
	return types_t_;
}

bool CreatureCombat::existe_boost_acupression(Donnees *_d)const{
	qint8 max_boost_=_d->constante_numerique("MAX_BOOST");
	bool existe_stat_non_max_=false;
	foreach(QString s,boosts_statistiques.cles()){
		if(boosts_statistiques.valeur(s)<max_boost_){
			existe_stat_non_max_=true;
		}
	}
	return existe_stat_non_max_;
}

QString CreatureCombat::tirage_acupression(Donnees *_d)const{
	MonteCarlo<QString> loi_;
	qint8 max_boost_=_d->constante_numerique("MAX_BOOST");
	bool existe_stat_non_max_=false;
	foreach(QString s,boosts_statistiques.cles()){
		if(boosts_statistiques.valeur(s)<max_boost_){
			loi_.ajouter_event(QPair<QString,Entier>(s,Entier(1)));
			existe_stat_non_max_=true;
		}
	}
	if(!existe_stat_non_max_){
		return "";
	}
	return loi_.tirage();
}

QString CreatureCombat::calcul_pics_toxik(uchar nb_pics_toxik){
	if(nb_pics_toxik==1){
		return "POISON";
	}
	return "POISON_GRAVE";
}

Taux CreatureCombat::calcul_avale()const{
	return Taux(1,2LL)^Entier(3-nb_lancer("STOCKAGE"));
}

Taux CreatureCombat::calcul_degommage(Donnees *_d)const{
	QList<QString> objets_=_d->val_puissance_degommage().cles();
	if(!objets_.contains(nom_objet)){
		return Taux(0);
	}
	return _d->val_puissance_degommage().valeur(nom_objet);
}

bool CreatureCombat::tirage_amoureux(Donnees *donnees){
	MonteCarlo<bool> loi;
	Taux proba_=donnees->constante_numerique("TIRAGE_AMOUREUX");
	Entier proba_1_=proba_.gnumerateur();
	Entier proba_2_=proba_.gdenominateur()-proba_1_;
	loi.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi.tirage();
}

bool CreatureCombat::tirage_degel(Donnees *donnees){
	MonteCarlo<bool> loi_;
	Taux proba_=donnees->constante_numerique("TIRAGE_DEGEL");
	Entier proba_1_=proba_.gnumerateur();
	Entier proba_2_=proba_.gdenominateur()-proba_1_;
	loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi_.tirage();
}

bool CreatureCombat::tirage_precision(const Taux& taux_precision){
	MonteCarlo<bool> loi_;
	Entier proba_1_=taux_precision.gnumerateur();
	Entier proba_2_=taux_precision.gdenominateur()-proba_1_;
	loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi_.tirage();
}

bool CreatureCombat::tirage_paralysie(Donnees *donnees){
	MonteCarlo<bool> loi_;
	Taux proba_=donnees->constante_numerique("PROBA_PARAL");
	Entier proba_1_=proba_.gnumerateur();
	Entier proba_2_=proba_.gdenominateur()-proba_1_;
	loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi_.tirage();
}

Taux CreatureCombat::tirage_excuse(){
	MonteCarloNombre loi;
	loi.ajouter_event(QPair<Taux,Entier>(Taux(40),Entier(4)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(80),Entier(3)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(120),Entier(1)));
	loi.ajouter_event(QPair<Taux,Entier>(-Taux(80),Entier(2)));
	return loi.tirage();
}

bool CreatureCombat::tirage_effet_fin_tour(const QString& nom_attaque,uint nb_tours,Donnees *donnees){
	QPair<QPair<uint,uint>,MonteCarlo<bool> > loi_min_max_=donnees->val_lois_fin_tour().valeur(nom_attaque);
	if(nb_tours<loi_min_max_.first.first){
		return true;
	}
	if(nb_tours==loi_min_max_.first.second){
		return false;
	}
	return loi_min_max_.second.tirage();
}

bool CreatureCombat::tirage_echange_vit_egales(Donnees *donnees){
	MonteCarlo<bool> loi_;
	Taux proba_=donnees->constante_numerique("ECHANGE_VIT_EGALES");
	Entier proba_1_=proba_.gnumerateur();
	Entier proba_2_=proba_.gdenominateur()-proba_1_;
	loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi_.tirage();
}

bool CreatureCombat::tirage_vive_griffe(Donnees *donnees){
	MonteCarlo<bool> loi_;
	Taux proba_=donnees->constante_numerique("TIRAGE_VIVE_GRIFFRE");
	Entier proba_1_=proba_.gnumerateur();
	Entier proba_2_=proba_.gdenominateur()-proba_1_;
	loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi_.tirage();
}

QString CreatureCombat::tirage_attaque(const QStringList& attaques){
	MonteCarlo<QString> loi_;
	foreach(QString t,attaques){
		loi_.ajouter_event(QPair<QString,Entier>(t,Entier(1)));
	}
	return loi_.tirage();
}

QString CreatureCombat::tirage_attaques_blabladodo(const QStringList& _liste)const{
	QStringList copie_attaques_act_;
	typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
	foreach(AttaquePP a,attaques_act){
		if(!_liste.contains(a.first)){
			copie_attaques_act_<<a.first;
		}
	}
	int nb_=copie_attaques_act_.size();
	MonteCarlo<QString> loi_;
	for(int i=0;i<nb_;i++){
		loi_.ajouter_event(QPair<QString,Entier>(copie_attaques_act_[i],Entier(1)));
	}
	return loi_.tirage();
}

QString CreatureCombat::tirage_adaptation(const QStringList& _types)const{
	QStringList types_;
	foreach(QString t,_types){
		if(!types_.contains(t)&&!types.contains(t)){
			types_<<t;
		}
	}
	MonteCarlo<QString> loi_;
	foreach(QString t,types_){
		loi_.ajouter_event(QPair<QString,Entier>(t,Entier(1)));
	}
	return loi_.tirage();
}

bool CreatureCombat::tirage_reveil(Donnees *_d)const{
	FicheCapacite *f_capac_=fiche_capacite(_d);
	if(f_capac_){
		int div_som_=f_capac_->div_tr_som();
		int max_som_=_d->constante_numerique("MAX_SOMMEIL");
		if(div_som_>0&&nb_tours_sommeil_non_repos*div_som_>=max_som_){
			return true;
		}else if(div_som_==0&&nb_tours_sommeil_non_repos>=max_som_){
			return true;
		}
	}else{
		if(nb_tours_sommeil_non_repos>=(int)_d->constante_numerique("MAX_SOMMEIL")){
			return true;
		}
	}
	MonteCarlo<bool> loi_;
	Taux proba_=_d->constante_numerique("PROBA_REVEIL");
	Entier proba_1_=proba_.gnumerateur();
	Entier proba_2_=proba_.gdenominateur()-proba_1_;
	loi_.ajouter_event(QPair<bool,Entier>(true,proba_1_));
	loi_.ajouter_event(QPair<bool,Entier>(false,proba_2_));
	return loi_.tirage();
}

MonteCarloNombre CreatureCombat::loi_cc(const Taux& _proba,Donnees *_d)const{
	FicheCapacite *f_capac_=fiche_capacite(_d);
	Taux copie_proba_=_proba;
	Taux val_cc_=_d->constante_numerique("DEF_VAL_CC");
	if(f_capac_){
		if(f_capac_->mult_pr_cc()!=Taux(0)){
			copie_proba_*=f_capac_->mult_pr_cc();
		}
		if(f_capac_->mult_deg_c()!=Taux(0)){
			val_cc_*=f_capac_->mult_deg_c();
		}
	}
	if(copie_proba_>=Taux(1)){
		MonteCarloNombre loi_;
		loi_.ajouter_event(QPair<Taux,Entier>(val_cc_,Entier(1)));
		return loi_;
	}
	Entier proba_1_=copie_proba_.gnumerateur();
	Entier proba_2_=copie_proba_.gdenominateur()-proba_1_;
	MonteCarloNombre loi_;
	loi_.ajouter_event(QPair<Taux,Entier>(val_cc_,proba_1_));
	loi_.ajouter_event(QPair<Taux,Entier>(Taux(1),proba_2_));
	return loi_;
}

QString CreatureCombat::tirage_type(Donnees *donnees){
	QStringList types_=donnees->val_noms_types_fr();
	MonteCarlo<QString> loi_;
	foreach(QString s,types_){
		loi_.ajouter_event(QPair<QString,Entier>(s,Entier(1)));
	}
	return loi_.tirage();
}

MonteCarloNombre CreatureCombat::loi_puissance_cachee(){
	MonteCarloNombre loi;
	loi.ajouter_event(QPair<Taux,Entier>(Taux(10),Entier(1)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(30),Entier(2)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(50),Entier(4)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(70),Entier(6)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(80),Entier(4)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(110),Entier(2)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(150),Entier(1)));
	return loi;
}

MonteCarloNombre CreatureCombat::loi_puissance_cachee(Donnees *_d)const{
	MonteCarloNombre loi_;
	FicheCapacite *f_capac_=fiche_capacite(_d);
	if(f_capac_){
		QPair<int,Taux> mult_puis_infeg_=f_capac_->mult_puis_inf_eg();
		if(mult_puis_infeg_.second!=Taux(0)){
			MonteCarloNombre loi_puissance_cachee_=loi_puissance_cachee();
			foreach(Taux e,loi_puissance_cachee_.events()){
				if(e<=Taux(mult_puis_infeg_.first)){
					loi_.ajouter_event(QPair<Taux,Entier>(e*mult_puis_infeg_.second,loi_puissance_cachee_.proba_event(e)));
				}else{
					loi_.ajouter_event(QPair<Taux,Entier>(e,loi_puissance_cachee_.proba_event(e)));
				}
			}
		}else{
			loi_=loi_puissance_cachee();
		}
	}else{
		loi_=loi_puissance_cachee();
	}
	return loi_;
}

MonteCarloNombre CreatureCombat::loi_ampleur(){
	MonteCarloNombre loi;
	loi.ajouter_event(QPair<Taux,Entier>(Taux(10),Entier(1)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(30),Entier(2)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(50),Entier(4)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(70),Entier(6)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(80),Entier(4)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(110),Entier(2)));
	loi.ajouter_event(QPair<Taux,Entier>(Taux(150),Entier(1)));
	return loi;
}

MonteCarloNombre CreatureCombat::loi_ampleur(Donnees *_d)const{
	MonteCarloNombre loi_;
	FicheCapacite *f_capac_=fiche_capacite(_d);
	if(f_capac_){
		QPair<int,Taux> mult_puis_infeg_=f_capac_->mult_puis_inf_eg();
		if(mult_puis_infeg_.second!=Taux(0)){
			MonteCarloNombre loi_ampleur_=loi_ampleur();
			foreach(Taux e,loi_ampleur_.events()){
				if(e<=Taux(mult_puis_infeg_.first)){
					loi_.ajouter_event(QPair<Taux,Entier>(e*mult_puis_infeg_.second,loi_ampleur_.proba_event(e)));
				}else{
					loi_.ajouter_event(QPair<Taux,Entier>(e,loi_ampleur_.proba_event(e)));
				}
			}
		}else{
			loi_=loi_ampleur();
		}
	}else{
		loi_=loi_ampleur();
	}
	return loi_;
}

//nb_coups()
MonteCarloNombre CreatureCombat::loi_repet_coups(const QString& _nom_attaque,Donnees *_d)const{
	FicheAttaque *f_att_=_d->val_attaques().valeur(_nom_attaque);
	FicheCapacite *f_capac_=fiche_capacite(_d);
	if(f_capac_&&f_capac_->nb_coups()){
		MonteCarloNombre loi_;
		loi_.ajouter_event(QPair<Taux,Entier>(f_att_->loi_rep_coup().maximum(),Entier(1)));
		return loi_;
	}
	return f_att_->loi_rep_coup();
}

MonteCarloNombre CreatureCombat::loi_random(uchar _modele){
	if(_modele==Difficulte::UNIFORME){
		MonteCarloNombre loi;
		for(int i=0;i<16;i++){
			loi.ajouter_event(QPair<Taux,Entier>(Taux(100-i,100LL),Entier(1)));
		}
		return loi;
	}
	if(_modele==Difficulte::CROISSANT){
		MonteCarloNombre loi;
		for(int i=0;i<16;i++){
			loi.ajouter_event(QPair<Taux,Entier>(Taux(100-i,100LL),Entier(16-i)));
		}
		return loi;
	}
	if(_modele==Difficulte::DECROISSANT){
		MonteCarloNombre loi;
		for(int i=0;i<16;i++){
			loi.ajouter_event(QPair<Taux,Entier>(Taux(100-i,100LL),Entier(i)));
		}
		return loi;
	}
	if(_modele==Difficulte::CONSTANT_MIN){
		MonteCarloNombre loi;
		loi.ajouter_event(QPair<Taux,Entier>(Taux(85,100LL),Entier(1)));
		return loi;
	}
	//CONSTANT_MAX
	MonteCarloNombre loi;
	loi.ajouter_event(QPair<Taux,Entier>(Taux(1),Entier(1)));
	return loi;
}


Taux CreatureCombat::coeff_boost(qint8 var){
	if(var<0){
		return Taux(2LL,2LL-var);
	}
	return Taux(2+var,2LL);
}

Taux CreatureCombat::coeff_pre(qint8 var){
	if(var<0){
		return Taux(3LL,3LL-var);
	}
	return Taux(3+var,3LL);
}

Taux CreatureCombat::coeff_esq(qint8 var){
	if(var<0){
		return Taux(3-var,3LL);
	}
	return Taux(3LL,3LL+var);
}

QString& CreatureCombat::val_der_objet_ut(){
	return der_objet_ut;
}

QString CreatureCombat::val_der_objet_ut()const{
	return der_objet_ut;
}

void CreatureCombat::serialiser(Flux& _out)const{
	_out<<nom;
	_out<<nom_act;
	_out<<pseudo;
	_out<<genre;
	_out<<types;
	_out<<statistiques_combat;
	_out<<statistiques_valeurs;
	_out<<ev_statistiques;
	_out<<iv_statistiques;
	_out<<exp_gagnee_depuis_der_niveau;
	_out<<bonheur;
	_out<<ordre;
	_out<<ball_capture;
	_out<<capacite;
	_out<<capacite_act;
	_out<<niveau;
	_out<<non_switch_force;
	_out<<a_joue;
	_out<<nom_objet;
	_out<<masse;
	_out<<statut;
	_out<<pv_restants;
	_out<<attaques;
	_out<<attaques_act;
	_out<<boosts_statistiques;
	_out<<boost_cc;
	_out<<table_types;
	_out<<der_attaque_lance;
	_out<<der_attaque_reussi;
	_out<<att_reussi;
	_out<<nb_tours_terrain;
	_out<<nb_tours_poison_grave;
	_out<<nb_lancers_attaques;
	_out<<confusion;
	_out<<clone;
	_out<<prepa_tour;
	_out<<disparait;
	_out<<nec_recharg;
	_out<<nb_tours_sommeil_non_repos;
	_out<<attaque_choisie;
	_out<<action_choisie;
	_out<<attaques_sur_combat_att;
	_out<<coeff_roulade_ball_glace;
	_out<<nb_tours_effets_attaques;
	_out<<patience;
	_out<<attaques_piegeantes;
	_out<<attaques_possessif;
	_out<<relations_comb;
	_out<<derniere_attaque_subie;
	_out<<nb_succes_abris;
	_out<<gain_exper;
	_out<<attaques_actives;
	_out<<cibles_choisies;
	_out<<envoye;
	_out<<peur;
	_out<<immu_attaques_types;
	_out<<coeff_att_types_subies;
	_out<<coeff_att_types_subies_2;
	_out<<coeff_att_types_lancees;
	_out<<vient_de_perdre_objet;
	_out<<copie;
	_out<<nb_repet_att_succ;
	_out<<torche;
	_out<<atterrissage_lance;
	_out<<pur_vol;
	//_out<<astuce_force_apres_zone_etrange
	_out<<objets;
	_out<<utilise_baie;
	_out<<der_objet_ut;
}

void CreatureCombat::deserialiser(Flux& _in){
	_in>>nom;
	_in>>nom_act;
	_in>>pseudo;
	_in>>genre;
	_in>>types;
	_in>>statistiques_combat;
	_in>>statistiques_valeurs;
	_in>>ev_statistiques;
	_in>>iv_statistiques;
	_in>>exp_gagnee_depuis_der_niveau;
	_in>>ordre;
	_in>>bonheur;
	_in>>ball_capture;
	_in>>capacite;
	_in>>capacite_act;
	_in>>niveau;
	_in>>non_switch_force;
	_in>>a_joue;
	_in>>nom_objet;
	_in>>masse;
	_in>>statut;
	_in>>pv_restants;
	_in>>attaques;
	_in>>attaques_act;
	_in>>boosts_statistiques;
	_in>>boost_cc;
	_in>>table_types;
	_in>>der_attaque_lance;
	_in>>der_attaque_reussi;
	_in>>att_reussi;
	_in>>nb_tours_terrain;
	_in>>nb_tours_poison_grave;
	_in>>nb_lancers_attaques;
	_in>>confusion;
	_in>>clone;
	_in>>prepa_tour;
	_in>>disparait;
	_in>>nec_recharg;
	_in>>nb_tours_sommeil_non_repos;
	_in>>attaque_choisie;
	_in>>action_choisie;
	_in>>attaques_sur_combat_att;
	_in>>coeff_roulade_ball_glace;
	_in>>nb_tours_effets_attaques;
	_in>>patience;
	_in>>attaques_piegeantes;
	_in>>attaques_possessif;
	_in>>relations_comb;
	_in>>derniere_attaque_subie;
	_in>>nb_succes_abris;
	_in>>gain_exper;
	_in>>attaques_actives;
	_in>>cibles_choisies;
	_in>>envoye;
	_in>>peur;
	_in>>immu_attaques_types;
	_in>>coeff_att_types_subies;
	_in>>coeff_att_types_subies_2;
	_in>>coeff_att_types_lancees;
	_in>>vient_de_perdre_objet;
	_in>>copie;
	_in>>nb_repet_att_succ;
	_in>>torche;
	_in>>atterrissage_lance;
	_in>>pur_vol;
	//_in>>astuce_force_apres_zone_etrange
	_in>>objets;
	_in>>utilise_baie;
	_in>>der_objet_ut;
}

Flux & operator <<(Flux& out,const CreatureCombat& _CreatureCombat){
	_CreatureCombat.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,CreatureCombat& _CreatureCombat){
	_CreatureCombat.deserialiser(in);
	return in;
}


