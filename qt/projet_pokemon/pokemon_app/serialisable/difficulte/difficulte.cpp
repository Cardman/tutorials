#include "serialisable/difficulte/difficulte.h"
#include "base_donnees/donnees.h"

Difficulte::Difficulte(){

}

Difficulte::Difficulte(Donnees* _d){
	nb_max_pk_par_equipe=_d->constante_numerique("DEF_PKEQ");
	autorise_ko_capture=true;
	choix_loi_capture_classique=true;
	coeff_gain_pts_exp_combat=Taux(1);
	coeff_courbe_exp_nec=Taux(1);
	coeff_achat_par_rapport_base=Taux(1);
	coeff_vente_par_rapport_achat=Taux(1);

	//uchar difficulte_gain_vitesse_combat;
	choix_lois.first=Difficulte::CONSTANT_MAX;//ut
	choix_lois.second=Difficulte::CONSTANT_MIN;//adv
	choix_lois_conf.first=Difficulte::CONSTANT_MIN;
	choix_lois_conf.second=Difficulte::CONSTANT_MAX;
	//uchar difficulte_gain_combat_nul;

	taux_gain_argent_base=Taux(1);
	taux_perte_argent_gain=Taux(1);

	niv_max_bonheur=_d->constante_numerique("MAX_BONHEUR");
	niv_evo_bonheur_nec=_d->constante_numerique("EVO_BONHEUR");;

	max_ev=_d->constante_numerique("MAX_EV");;

	iv_ut=_d->constante_numerique("MAX_IV");
	iv_adv=0;
	fuite_toujours_possible=true;
	rapport_max_egalite=Taux(1LL,4LL);
	appar_alea=false;
	attaques_rechargees_fin_combat=false;
	difficulte_gain_pts_exp_combat=Difficulte::DIFFICILE;
	affichage=true;
	/***/
	//bool presence_objets_repousse;

	/**Les attaques dépendant des positions sont différentes en fonction de cette variable*/
	adjacence_active=true;
}

uchar& Difficulte::r_nb_max_pk_par_equipe(){
	return nb_max_pk_par_equipe;
}

bool& Difficulte::r_autorise_ko_capture(){
	return autorise_ko_capture;
}

bool& Difficulte::r_choix_loi_capture_classique(){
	return choix_loi_capture_classique;
}

uchar& Difficulte::r_difficulte_gain_pts_exp_combat(){
	return difficulte_gain_pts_exp_combat;
}

Taux& Difficulte::r_coeff_gain_pts_exp_combat(){
	return coeff_gain_pts_exp_combat;
}

Taux& Difficulte::r_coeff_courbe_exp_nec(){
	return coeff_courbe_exp_nec;
}

Taux& Difficulte::r_coeff_achat_par_rapport_base(){
	return coeff_achat_par_rapport_base;
}

Taux& Difficulte::r_coeff_vente_par_rapport_achat(){
	return coeff_vente_par_rapport_achat;
}

uchar& Difficulte::r_difficulte_gain_vitesse_combat(){
	return difficulte_gain_vitesse_combat;
}

QPair<uchar,uchar>& Difficulte::r_choix_lois(){
	return choix_lois;
}

QPair<uchar,uchar>& Difficulte::r_choix_lois_conf(){
	return choix_lois_conf;
}

uchar& Difficulte::r_difficulte_gain_combat_nul(){
	return difficulte_gain_combat_nul;
}

Taux& Difficulte::r_taux_gain_argent_base(){
	return taux_gain_argent_base;
}

Taux& Difficulte::r_taux_perte_argent_gain(){
	return taux_perte_argent_gain;
}

int& Difficulte::r_niv_max_bonheur(){
	return niv_max_bonheur;
}

int& Difficulte::r_niv_evo_bonheur_nec(){
	return niv_evo_bonheur_nec;
}

int& Difficulte::r_max_ev(){
	return max_ev;
}

uchar& Difficulte::r_iv_ut(){
	return iv_ut;
}

uchar& Difficulte::r_iv_adv(){
	return iv_adv;
}

bool& Difficulte::r_fuite_toujours_possible(){
	return fuite_toujours_possible;
}

bool& Difficulte::r_attaques_rechargees_fin_combat(){
	return attaques_rechargees_fin_combat;
}

bool& Difficulte::r_presence_objets_repousse(){
	return presence_objets_repousse;
}

bool& Difficulte::r_adjacence_active(){
	return adjacence_active;
}

bool& Difficulte::r_appar_alea(){
	return appar_alea;
}

bool& Difficulte::r_affichage(){
	return affichage;
}

Taux& Difficulte::r_rapport_max_egalite(){
	return rapport_max_egalite;
}

uchar Difficulte::r_nb_max_pk_par_equipe()const{
	return nb_max_pk_par_equipe;
}

bool Difficulte::r_autorise_ko_capture()const{
	return autorise_ko_capture;
}

bool Difficulte::r_choix_loi_capture_classique()const{
	return choix_loi_capture_classique;
}

uchar Difficulte::r_difficulte_gain_pts_exp_combat()const{
	return difficulte_gain_pts_exp_combat;
}

Taux Difficulte::r_coeff_gain_pts_exp_combat()const{
	return coeff_gain_pts_exp_combat;
}

Taux Difficulte::r_coeff_courbe_exp_nec()const{
	return coeff_courbe_exp_nec;
}

Taux Difficulte::r_coeff_achat_par_rapport_base()const{
	return coeff_achat_par_rapport_base;
}

Taux Difficulte::r_coeff_vente_par_rapport_achat()const{
	return coeff_vente_par_rapport_achat;
}

uchar Difficulte::r_difficulte_gain_vitesse_combat()const{
	return difficulte_gain_vitesse_combat;
}

QPair<uchar,uchar> Difficulte::r_choix_lois()const{
	return choix_lois;
}

QPair<uchar,uchar> Difficulte::r_choix_lois_conf()const{
	return choix_lois_conf;
}

uchar Difficulte::r_difficulte_gain_combat_nul()const{
	return difficulte_gain_combat_nul;
}

Taux Difficulte::r_taux_gain_argent_base()const{
	return taux_gain_argent_base;
}

Taux Difficulte::r_taux_perte_argent_gain()const{
	return taux_perte_argent_gain;
}

int Difficulte::r_niv_max_bonheur()const{
	return niv_max_bonheur;
}

int Difficulte::r_niv_evo_bonheur_nec()const{
	return niv_evo_bonheur_nec;
}

int Difficulte::r_max_ev()const{
	return max_ev;
}

uchar Difficulte::r_iv_ut()const{
	return iv_ut;
}

uchar Difficulte::r_iv_adv()const{
	return iv_adv;
}

bool Difficulte::r_fuite_toujours_possible()const{
	return fuite_toujours_possible;
}

bool Difficulte::r_attaques_rechargees_fin_combat()const{
	return attaques_rechargees_fin_combat;
}

bool Difficulte::r_presence_objets_repousse()const{
	return presence_objets_repousse;
}

bool Difficulte::r_adjacence_active()const{
	return adjacence_active;
}

bool Difficulte::r_appar_alea()const{
	return appar_alea;
}

Taux Difficulte::r_rapport_max_egalite()const{
	return rapport_max_egalite;
}

bool Difficulte::r_affichage()const{
	return affichage;
}

Taux Difficulte::taux_gain(uchar _niveau_perdant,uchar _niveau_gagnant){
	Taux tx_(1);
	if(difficulte_gain_pts_exp_combat==Difficulte::TRES_FACILE){
		if(_niveau_perdant>_niveau_gagnant){
			tx_*=Taux((long long)_niveau_perdant,(long long)_niveau_gagnant)^Entier(3);
		}
	}
	if(difficulte_gain_pts_exp_combat==Difficulte::FACILE){
		tx_*=Taux((long long)_niveau_perdant,(long long)_niveau_gagnant)^Entier(3);
	}
	if(difficulte_gain_pts_exp_combat==Difficulte::TRES_DIFFICILE){
		if(_niveau_perdant<_niveau_gagnant){
			tx_*=Taux((long long)_niveau_perdant,(long long)_niveau_gagnant)^Entier(3);
		}
	}
	return tx_;
}

void Difficulte::serialiser(Flux& _out)const{
	_out<<nb_max_pk_par_equipe;
	_out<<autorise_ko_capture;
	_out<<choix_loi_capture_classique;
	_out<<coeff_gain_pts_exp_combat;
	_out<<coeff_courbe_exp_nec;
	_out<<coeff_achat_par_rapport_base;
	_out<<coeff_vente_par_rapport_achat;
	_out<<difficulte_gain_vitesse_combat;
	_out<<choix_lois;
	_out<<choix_lois_conf;
	_out<<difficulte_gain_combat_nul;
	_out<<taux_gain_argent_base;
	_out<<taux_perte_argent_gain;
	_out<<niv_max_bonheur;
	_out<<niv_evo_bonheur_nec;
	_out<<max_ev;
	_out<<iv_ut;
	_out<<iv_adv;
	_out<<fuite_toujours_possible;
	_out<<presence_objets_repousse;
	_out<<adjacence_active;
	_out<<appar_alea;
	_out<<rapport_max_egalite;
	_out<<attaques_rechargees_fin_combat;
	_out<<affichage;
}

void Difficulte::deserialiser(Flux& _in){
	_in>>nb_max_pk_par_equipe;
	_in>>autorise_ko_capture;
	_in>>choix_loi_capture_classique;
	_in>>coeff_gain_pts_exp_combat;
	_in>>coeff_courbe_exp_nec;
	_in>>coeff_achat_par_rapport_base;
	_in>>coeff_vente_par_rapport_achat;
	_in>>difficulte_gain_vitesse_combat;
	_in>>choix_lois;
	_in>>choix_lois_conf;
	_in>>difficulte_gain_combat_nul;
	_in>>taux_gain_argent_base;
	_in>>taux_perte_argent_gain;
	_in>>niv_max_bonheur;
	_in>>niv_evo_bonheur_nec;
	_in>>max_ev;
	_in>>iv_ut;
	_in>>iv_adv;
	_in>>fuite_toujours_possible;
	_in>>presence_objets_repousse;
	_in>>adjacence_active;
	_in>>appar_alea;
	_in>>rapport_max_egalite;
	_in>>attaques_rechargees_fin_combat;
	_in>>affichage;
}

Flux & operator <<(Flux& out,const Difficulte& _Difficulte){
	_Difficulte.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Difficulte& _Difficulte){
	_Difficulte.deserialiser(in);
	return in;
}


