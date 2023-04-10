#include "serialisable/pokemon/pokemonutilisateur.h"
#include "base_donnees/pokemon/pokemonsauvage.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/attaques/ficheattaque.h"
#include "serialisable/combat/creaturecombat.h"
#include "base_donnees/objets/fossile.h"
#include "base_donnees/donnees.h"
#include "serialisable/pokemon/oeufpokemon.h"
#include "base_donnees/evolution/evolutionpierreevolutivegenre.h"
#include "base_donnees/objets/soinpv.h"
#include "base_donnees/objets/soinpvstatut.h"
#include "base_donnees/objets/objetattachablecombat.h"

//Entier PokemonUtilisateur::total_captures=Entier(0);
PokemonUtilisateur::PokemonUtilisateur(){
	niveau=0;
	bonheur=0;
	nombre_pas_tete_equipe=0;
	nom="";
}

void PokemonUtilisateur::obtention(){
	exp_gagne_der_niv=Taux(0);
	nombre_pas_tete_equipe=0;
	/*numero_capture=total_captures
	total_captures+=Entier(1)*/
}

PokemonUtilisateur::PokemonUtilisateur(PokemonSauvage*_pokemon_donne,Donnees* _d,const QString& _genre){
	nom=_pokemon_donne->n_pk();
	niveau=_pokemon_donne->niv_pk();
	if(_genre==""){
		genre=_pokemon_donne->genre_pk();
	}else{
		genre=_genre;
	}
	capacite=_pokemon_donne->capacite_pk();
	nom_objet=_pokemon_donne->objet();
	statut="OK";
	init_attaques(_d);
	pseudo=nom;
	ball_capture="";
	bonheur=_d->constante_numerique("DEF_BONHEUR_CAPT");
	obtention();
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	pv_restants=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
}

PokemonUtilisateur::PokemonUtilisateur(const CreatureCombat& _pokemon_sauvage,Donnees* _d){
	nom=_pokemon_sauvage.nom_pk();
	niveau=_pokemon_sauvage.niveau_pk();
	genre=_pokemon_sauvage.genre_pk();
	nom_objet=_pokemon_sauvage.objet();
	capacite=_pokemon_sauvage.capacite_pk_act();
	ball_capture=_pokemon_sauvage.ball_capt();
	bonheur=_pokemon_sauvage.bonheur_pk();
	statut=_pokemon_sauvage.statut_pk();
	pv_restants=_pokemon_sauvage.pv_restants_pk();
	init_attaques(_d);
	obtention();
}

PokemonUtilisateur::PokemonUtilisateur(Fossile *_fossile,Donnees* _d){
	nom=_fossile->nom_pk();
	niveau=_fossile->niv();
	nom_objet="";
	statut="OK";
	pseudo=nom;
	init_attaques(_d);
	init_alea_capacite_genre(_d);
	ball_capture="";
	bonheur=_d->constante_numerique("DEF_BONHEUR_CAPT");
	obtention();
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	pv_restants=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
}

PokemonUtilisateur::PokemonUtilisateur(const OeufPokemon& _oeuf,Donnees* _d){
	nom=_oeuf.nom_pk();
	niveau=_d->constante_numerique("NIVEAU_PK_ECLOSION");
	nom_objet="";
	statut="OK";
	pseudo=nom;
	init_attaques(_d);
	init_alea_capacite_genre(_d);
	bonheur=_d->constante_numerique("DEF_BONHEUR_ECL");
	obtention();
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	pv_restants=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
}

void PokemonUtilisateur::init_alea_capacite_genre(Donnees* _d){
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	QString repartition_genre_=f_pk_->rep_genr();
	if(repartition_genre_=="MIXTE"){
		MonteCarlo<QString> loi_genre_;
		foreach(QString g,_d->genres_non_assexues()){
			if(g!="ASSEXUE"){
				loi_genre_.ajouter_event(QPair<QString,Entier>(g,Entier(1)));
			}
		}
		genre=loi_genre_.tirage();
	}else{
		genre=repartition_genre_;
	}
	QStringList capacites_=f_pk_->capac();
	if(capacites_.size()>1){
		MonteCarlo<QString> loi_capac_;
		foreach(QString c,capacites_){
			loi_capac_.ajouter_event(QPair<QString,Entier>(c,Entier(1)));
		}
		capacite=loi_capac_.tirage();
	}else{
		capacite=capacites_[0];
	}
}

void PokemonUtilisateur::init_attaques(Donnees *_d){
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
	foreach(QString s,f_pk_->stat_ev().cles()){
		ev_statistiques.ajouter_cle_valeur(s,0);
		iv_statistiques.ajouter_cle_valeur(s,_d->constante_numerique("MAX_IV"));
	}
}

void PokemonUtilisateur::deplacement(int _nb_pas,Donnees *_d){
	if(nombre_pas_tete_equipe+_nb_pas>=256){
		Taux mult_(1);
		ObjetAttachableCombat *obj_=NULL;
		if(nom_objet!=""){
			obj_=qobject_cast<ObjetAttachableCombat*>(_d->val_objets().valeur(nom_objet));
		}
		if(obj_&&obj_->mult_gain_bonh()>Taux((long long int)0)){
			mult_*=obj_->mult_gain_bonh();
		}
		if(ball_capt()=="LUXE_BALL"){
			mult_*=_d->constante_numerique("MULT_BONHEUR_LUXEBALL");
		}
		if(Taux((long long int)bonheur)+mult_<=_d->constante_numerique("MAX_BONHEUR")){
			bonheur+=mult_;
		}else{
			bonheur=_d->constante_numerique("MAX_BONHEUR");
		}
		nombre_pas_tete_equipe=nombre_pas_tete_equipe+_nb_pas-256;
	}else{
		nombre_pas_tete_equipe+=_nb_pas;
	}
}

QStringList PokemonUtilisateur::move_tutors(Donnees* _d){
	QStringList mt_=_d->val_pokedex().valeur(nom)->mt();
	for(int i=attaques.size()-1;i>-1;i--){
		mt_.removeOne(attaques[i].first);
	}
	return mt_;
}

bool PokemonUtilisateur::attaque_deja_connue(const QString& _nom_attaque)const{
	for(int i=attaques.size()-1;i>-1;i--){
		if(attaques[i].first==_nom_attaque){
			return true;
		}
	}
	return false;
}

QList<QPair<QString,QPair<uchar,uchar> > > PokemonUtilisateur::attaques_apprises()const{
	return attaques;
}

QString PokemonUtilisateur::apprendre_attaque(const QString& _nv_att,uchar _indice,Donnees *_d){
	uchar pp_=_d->val_attaques().valeur(_nv_att)->pps();
	if(_indice==attaques.size()){
		attaques<<QPair<QString,QPair<uchar,uchar> >(_nv_att,QPair<uchar,uchar>(pp_,pp_));
		return "";
	}
	QString anc_att_=attaques[_indice].first;
	attaques[_indice]=QPair<QString,QPair<uchar,uchar> >(_nv_att,QPair<uchar,uchar>(pp_,pp_));
	return anc_att_;
}

QString PokemonUtilisateur::ball_capt()const{
	return ball_capture;
}

QString& PokemonUtilisateur::ball_capt(){
	return ball_capture;
}

uchar PokemonUtilisateur::bonheur_pk()const{
	return bonheur;
}

void PokemonUtilisateur::affecter_bonheur_pk(uchar _bonheur){
	bonheur=_bonheur;
}

uchar PokemonUtilisateur::pas_tete_equipe()const{
	return nombre_pas_tete_equipe;
}

void PokemonUtilisateur::evoluer(const QString& _evo,Donnees *_d){
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	Taux pv_max_=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
	nom=_evo;
	f_pk_=_d->val_pokedex().valeur(nom);
	QStringList capacs_=f_pk_->capac();
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
	Taux pv_max_n_=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
	if(pv_max_n_>pv_max_){
		pv_restants+=pv_max_n_-pv_max_;
	}else if(pv_restants>=pv_max_n_){
		pv_restants=pv_max_n_;
	}
}

void PokemonUtilisateur::soin_total(Donnees *_d){
	soin_statut();
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	soin_pv(f_pk_);
	for(int i=attaques.size()-1;i>-1;i--){
		attaques[i].second.first=attaques[i].second.second;
	}
}

QString PokemonUtilisateur::statut_pk()const{
	return statut;
}

void PokemonUtilisateur::soin_statut(){
	statut="OK";
}

Taux PokemonUtilisateur::pv_rest()const{
	return pv_restants;
}

void PokemonUtilisateur::soin_pv_baie(const Taux& _pv,Donnees* _d,Taux& _pv_soignes){
	if(pv_restants+_pv>pv_max(_d)){
		_pv_soignes=pv_max(_d)-pv_restants;
	}else{
		_pv_soignes=_pv;
	}
	pv_restants+=_pv_soignes;
}

void PokemonUtilisateur::soin_pp_baie(uchar _pp,const QString& _attaque,uchar& _pp_soignes){
	uchar nb_pp_=0;
	uchar nb_pp_max_=0;
	int indice_=-1;
	for(int i=attaques.size();i>-1;i--){
		if(attaques[i].first==_attaque){
			nb_pp_=attaques[i].second.first;
			nb_pp_max_=attaques[i].second.second;
			indice_=i;
			break;
		}
	}
	if(indice_==-1){
		return;
	}
	if(nb_pp_+_pp>nb_pp_max_){
		_pp_soignes=nb_pp_max_-_pp;
	}else{
		_pp_soignes=nb_pp_;
	}
	attaques[indice_].second.first+=_pp_soignes;
}

Taux PokemonUtilisateur::pv_max(Donnees* _d)const{
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	return f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
}

void PokemonUtilisateur::soin_pv(FichePokemon *f_pk_){
	pv_restants=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
}

Taux PokemonUtilisateur::soin_pv(SoinPVStatut *_soin,Donnees *_d){
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	Taux pv_max_=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
	Taux pv_soignes_(0);
	if(_soin->tx_soin()*pv_max_+pv_restants>=pv_max_){
		pv_soignes_=pv_max_-pv_restants;
		pv_restants=pv_max_;
	}else{
		pv_soignes_=_soin->tx_soin()*pv_max_;
		pv_restants+=pv_soignes_;
	}
	return pv_soignes_;
}

Taux PokemonUtilisateur::soin_pv(SoinPV *_soin,Donnees *_d){
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	Taux pv_max_=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
	Taux pv_soignes_=_soin->pv_m_res();
	if(pv_restants+_soin->pv_m_res()<=pv_max_){
		pv_restants+=_soin->pv_m_res();
	}else{
		pv_soignes_=pv_max_-pv_restants;
		pv_restants=pv_max_;
	}
	Taux mult_(1);
	ObjetAttachableCombat *obj_=NULL;
	if(nom_objet!=""){
		obj_=qobject_cast<ObjetAttachableCombat*>(_d->val_objets().valeur(nom_objet));
	}
	if(obj_&&obj_->mult_gain_bonh()>Taux((long long int)0)){
		mult_*=obj_->mult_gain_bonh();
	}
	if(ball_capt()=="LUXE_BALL"){
		mult_*=_d->constante_numerique("MULT_BONHEUR_LUXEBALL");
		mult_*=Taux(_soin->bonh().second);
	}else{
		mult_*=Taux(_soin->bonh().first);
	}
	if(Taux((long long int)bonheur)+mult_<=_d->constante_numerique("MAX_BONHEUR")){
		bonheur+=mult_;
	}else{
		bonheur=_d->constante_numerique("MAX_BONHEUR");
	}
	return pv_soignes_;
	//pv_m_res()
}

Taux PokemonUtilisateur::soin_pv(const Taux& _pv,const QPair<uchar,uchar>& _bonheur,Donnees* _d){
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	Taux pv_max_=f_pk_->stat(niveau,"PV",ev_statistiques.valeur("PV"),iv_statistiques.valeur("PV"));
	Taux pv_soignes_=_pv;
	if(pv_restants+_pv<=pv_max_){
		pv_restants+=_pv;
	}else{
		pv_soignes_=pv_max_-pv_restants;
		pv_restants=pv_max_;
	}
	Taux mult_(1);
	ObjetAttachableCombat *obj_=NULL;
	if(nom_objet!=""){
		obj_=qobject_cast<ObjetAttachableCombat*>(_d->val_objets().valeur(nom_objet));
	}
	if(obj_&&obj_->mult_gain_bonh()>Taux((long long int)0)){
		mult_*=obj_->mult_gain_bonh();
	}
	if(ball_capt()=="LUXE_BALL"){
		mult_*=_d->constante_numerique("MULT_BONHEUR_LUXEBALL");
		mult_*=Taux(_bonheur.second);
	}else{
		mult_*=Taux(_bonheur.first);
	}
	if(Taux((long long int)bonheur)+mult_<=_d->constante_numerique("MAX_BONHEUR")){
		bonheur+=mult_;
	}else{
		bonheur=_d->constante_numerique("MAX_BONHEUR");
	}
	return pv_soignes_;

}

uchar PokemonUtilisateur::soin_pp(const QString& _nom_attaque,uchar _quantite){
	uchar pp_=0;
	for(int i=attaques.size()-1;i>-1;i--){
		if(attaques[i].first==_nom_attaque){
			if(attaques[i].second.first+_quantite>=attaques[i].second.second){
				pp_=attaques[i].second.second-attaques[i].second.first;
				attaques[i].second.first=attaques[i].second.second;
			}else{
				pp_=_quantite;
				attaques[i].second.first+=_quantite;
			}
			break;
		}
	}
	return pp_;
}

uchar PokemonUtilisateur::soin_pp(const QString& _nom_attaque){
	uchar pp_=0;
	for(int i=attaques.size()-1;i>-1;i--){
		if(attaques[i].first==_nom_attaque){
			pp_=attaques[i].second.second-attaques[i].second.first;
			attaques[i].second.first=attaques[i].second.second;
			break;
		}
	}
	return pp_;
}

QStringList PokemonUtilisateur::soin_pp(uchar _quantite){
	QStringList attaques_;
	for(int i=attaques.size()-1;i>-1;i--){
		if(attaques[i].second.first<attaques[i].second.second){
			attaques_<<attaques[i].first;
			if(attaques[i].second.first+_quantite>=attaques[i].second.second){
				attaques[i].second.first=attaques[i].second.second;
			}else{
				attaques[i].second.first+=_quantite;
			}
		}
	}
	return attaques_;
}

HashMap<QString,uchar> PokemonUtilisateur::soin_pp(){
	HashMap<QString,uchar> attaques_;
	for(int i=attaques.size()-1;i>-1;i--){
		attaques_.ajouter_cle_valeur(attaques[i].first,attaques[i].second.second-attaques[i].second.first);
		attaques[i].second.first=attaques[i].second.second;
	}
	return attaques_;
}

bool PokemonUtilisateur::gain_pp_max(const QString& _attaque,uchar _gain,uchar _max){
	bool ret_=false;
	for(int i=attaques.size()-1;i>-1;i--){
		if(attaques[i].first==_attaque){
			if(attaques[i].second.second<_max){
				ret_=true;
			}
			if(attaques[i].second.second+_gain<_max){
				attaques[i].second.second+=_gain;
				attaques[i].second.first+=_gain;
			}else{
				attaques[i].second.first+=_max-attaques[i].second.second;
				attaques[i].second.second=_max;
			}
		}
	}
	return ret_;
}

Taux PokemonUtilisateur::exp_gagne()const{
	return exp_gagne_der_niv;
}



QString PokemonUtilisateur::peut_evoluer(const QString& _pierre_evo,Donnees *_d)const{
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	QList<QString> cles_=f_pk_->evos().cles();
	if(cles_.isEmpty()){
		return nom;
	}
	QList<QString> cles_p_;
	foreach(QString e,cles_){
		EvolutionPierreEvolutive *evo_pierre_=qobject_cast<EvolutionPierreEvolutive*>(f_pk_->evos().valeur(e));
		if(evo_pierre_){
			cles_p_<<e;
		}
	}
	if(cles_p_.isEmpty()){
		return nom;
	}
	foreach(QString e,cles_p_){
		EvolutionPierreEvolutive *evo_pierre_=qobject_cast<EvolutionPierreEvolutive*>(f_pk_->evos().valeur(e));
		if(evo_pierre_->nom_pierre()==_pierre_evo){
			EvolutionPierreEvolutiveGenre *evo_pierre_g_=qobject_cast<EvolutionPierreEvolutiveGenre*>(evo_pierre_);
			if(evo_pierre_g_&&evo_pierre_g_->gr()!=genre){
				return nom;
			}
			return e;
		}
	}
	return nom;
}

QString PokemonUtilisateur::n_pk()const{
	return nom;
}

uchar PokemonUtilisateur::niv_pk()const{
	return niveau;
}

QString PokemonUtilisateur::genre_pk()const{
	return genre;
}

QString PokemonUtilisateur::capacite_pk()const{
	return capacite;
}

QString& PokemonUtilisateur::objet(){
	return nom_objet;
}

QString PokemonUtilisateur::objet()const{
	return nom_objet;
}

QString& PokemonUtilisateur::pseudo_pk(){
	return pseudo;
}

QString PokemonUtilisateur::pseudo_pk()const{
	return pseudo;
}

/*void PokemonUtilisateur::affecterCreatureCombat(const CreatureCombat& _pokemon){
	
}*/

void PokemonUtilisateur::finCombat(const CreatureCombat& _pokemon){
	nom=_pokemon.nom_pk();
	niveau=_pokemon.niveau_pk();
	capacite=_pokemon.capacite_pk_ini();
	nom_objet=_pokemon.objet();
	bonheur=_pokemon.bonheur_pk();
	ev_statistiques=_pokemon.ev_statistiques_pk();
	pv_restants=_pokemon.pv_restants_pk();
	statut=_pokemon.statut_pk();
	attaques=_pokemon.attaques_pk();
	exp_gagne_der_niv=_pokemon.exp_gagnee();
}

void PokemonUtilisateur::tmp_exp_gagne_der_niv(Donnees* _d){
	FichePokemon *f_pk_=_d->val_pokedex().valeur(nom);
	exp_gagne_der_niv=f_pk_->diff_pts_niveaux(niveau+1)-Taux(1);
}

HashMap<QString,uchar> PokemonUtilisateur::iv_stat()const{
	return iv_statistiques;
}

HashMap<QString,uchar> PokemonUtilisateur::ev_stat()const{
	return ev_statistiques;
}

uchar PokemonUtilisateur::gain_ev(const QString& _stat,uchar _increment,const QPair<uchar,uchar>& _gain_bonheur,uchar _max_ev,Donnees *_d){
	uchar res_;
	uchar& valeur_=ev_statistiques.valeur(_stat);
	if(valeur_+_increment<_max_ev){
		valeur_+=_increment;
		res_=_increment;
	}else{
		res_=_max_ev-valeur_;
		valeur_=_max_ev;
	}
	Taux mult_(1);
	ObjetAttachableCombat *obj_=NULL;
	if(nom_objet!=""){
		obj_=qobject_cast<ObjetAttachableCombat*>(_d->val_objets().valeur(nom_objet));
	}
	if(obj_&&obj_->mult_gain_bonh()>Taux((long long int)0)){
		mult_*=obj_->mult_gain_bonh();
	}
	if(ball_capt()=="LUXE_BALL"){
		mult_*=_d->constante_numerique("MULT_BONHEUR_LUXEBALL");
		mult_*=Taux(_gain_bonheur.second);
	}else{
		mult_*=Taux(_gain_bonheur.first);
	}
	if(Taux((long long int)bonheur)+mult_<=_d->constante_numerique("MAX_BONHEUR")){
		bonheur+=mult_;
	}else{
		bonheur=_d->constante_numerique("MAX_BONHEUR");
	}
	return res_;
}

void PokemonUtilisateur::serialiser(Flux& _out)const{
	_out<<nom;
	_out<<niveau;
	_out<<genre;
	_out<<capacite;
	_out<<nom_objet;
	_out<<statut;
	_out<<pseudo;
	_out<<attaques;
	_out<<ev_statistiques;
	_out<<exp_gagne_der_niv;
	_out<<bonheur;
	_out<<ball_capture;
	_out<<nombre_pas_tete_equipe;
	_out<<numero_capture;
}

void PokemonUtilisateur::deserialiser(Flux& _in){
	_in>>nom;
	_in>>niveau;
	_in>>genre;
	_in>>capacite;
	_in>>nom_objet;
	_in>>statut;
	_in>>pseudo;
	_in>>attaques;
	_in>>ev_statistiques;
	_in>>exp_gagne_der_niv;
	_in>>bonheur;
	_in>>ball_capture;
	_in>>nombre_pas_tete_equipe;
	_in>>numero_capture;
}


Flux & operator <<(Flux& out,const PokemonUtilisateur& _PokemonUtilisateur){
	_PokemonUtilisateur.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,PokemonUtilisateur& _PokemonUtilisateur){
	_PokemonUtilisateur.deserialiser(in);
	return in;
}


