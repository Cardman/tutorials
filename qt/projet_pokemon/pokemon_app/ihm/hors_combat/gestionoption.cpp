#include "ihm/hors_combat/gestionoption.h"
#include "ihm/curseurs/curseur.h"
#include "ihm/boutons/claviernumerique.h"
#include "ihm/boutons/boutonchoix.h"
#include "ihm/boutons/bouton.h"
#include "base_donnees/donnees.h"
#include <QVBoxLayout>
#include <QMetaEnum>

GestionOption::GestionOption(Donnees *_d){
	donnees=_d;
	QVBoxLayout *lay_=new QVBoxLayout();
	lay_->addWidget(new QLabel("Nombre maximal de pokemon dans l'equipe"));
	nom_pk_max=new Curseur();
	connect(nom_pk_max,SIGNAL(nouvelle_valeur(int)),this,SLOT(maj_nom_pk_max(int)));
	nom_pk_max->maj_intervalle(donnees->constante_numerique("MIN_PKEQ"),donnees->constante_numerique("MAX_PKEQ"));
	lay_->addWidget(nom_pk_max);
	lay_->addWidget(new QLabel("Valeur individuelle par pokemon du joueur"));
	iv_ut=new Curseur();
	connect(iv_ut,SIGNAL(nouvelle_valeur(int)),this,SLOT(maj_iv_ut(int)));
	iv_ut->maj_intervalle(0,donnees->constante_numerique("MAX_IV"));
	lay_->addWidget(iv_ut);
	lay_->addWidget(new QLabel("Valeur individuelle par pokemon des adversaires"));
	iv_adv=new Curseur();
	connect(iv_adv,SIGNAL(nouvelle_valeur(int)),this,SLOT(maj_iv_adv(int)));
	iv_adv->maj_intervalle(0,donnees->constante_numerique("MAX_IV"));
	lay_->addWidget(iv_adv);
	lay_->addWidget(new QLabel("Valeur de bonheur necessaire a avoir pour une evolution liee au bonheur"));
	valeur_nec_evo_bonheur=new Curseur();
	connect(valeur_nec_evo_bonheur,SIGNAL(nouvelle_valeur(int)),this,SLOT(maj_valeur_nec_evo_bonheur(int)));
	valeur_nec_evo_bonheur->maj_intervalle(0,donnees->constante_numerique("MAX_BONHEUR"));
	lay_->addWidget(valeur_nec_evo_bonheur);
	ko_capt=new BoutonChoix();
	connect(ko_capt,SIGNAL(clic(bool)),this,SLOT(maj_ko_capt(bool)));
	ko_capt->maj_texte("Possibilite de capturer un pokemon KO");
	ko_capt->maj_couleur_choix(QColor(255,0,0,255));
	ko_capt->maj_couleur_fond(QColor(255,255,255,255));
	ko_capt->maj_couleur_rectangle(QColor(0,0,255,255));
	ko_capt->maj_couleur_texte(QColor(0,0,255,255));
	lay_->addWidget(ko_capt);
	fuite=new BoutonChoix();
	connect(fuite,SIGNAL(clic(bool)),this,SLOT(maj_fuite(bool)));
	fuite->maj_texte("Fuite toujours possible");
	fuite->maj_couleur_choix(QColor(255,0,0,255));
	fuite->maj_couleur_fond(QColor(255,255,255,255));
	fuite->maj_couleur_rectangle(QColor(0,0,255,255));
	fuite->maj_couleur_texte(QColor(0,0,255,255));
	lay_->addWidget(fuite);
	adj_act=new BoutonChoix();
	connect(adj_act,SIGNAL(clic(bool)),this,SLOT(maj_adj_act(bool)));
	adj_act->maj_texte("Adjacence active");
	adj_act->maj_couleur_choix(QColor(255,0,0,255));
	adj_act->maj_couleur_fond(QColor(255,255,255,255));
	adj_act->maj_couleur_rectangle(QColor(0,0,255,255));
	adj_act->maj_couleur_texte(QColor(0,0,255,255));
	lay_->addWidget(adj_act);
	appar_alea=new BoutonChoix();
	connect(appar_alea,SIGNAL(clic(bool)),this,SLOT(maj_appar_alea(bool)));
	appar_alea->maj_texte("Apparition aleatoire");
	appar_alea->maj_couleur_choix(QColor(255,0,0,255));
	appar_alea->maj_couleur_fond(QColor(255,255,255,255));
	appar_alea->maj_couleur_rectangle(QColor(0,0,255,255));
	appar_alea->maj_couleur_texte(QColor(0,0,255,255));
	lay_->addWidget(appar_alea);
	lay_->addWidget(new QLabel("Coefficient de gain de points d'experience"));
	coeff_gain_pts_exp=new ClavierNumerique(false,_d);
	connect(coeff_gain_pts_exp,SIGNAL(valider(Taux)),this,SLOT(maj_coeff_gain_pts_exp(Taux)));
	lay_->addWidget(coeff_gain_pts_exp);
	lay_->addWidget(new QLabel("Rapport prix d'achat sur la base de prix d'achat"));
	coeff_achat_base=new ClavierNumerique(false,_d);
	connect(coeff_achat_base,SIGNAL(valider(Taux)),this,SLOT(maj_coeff_achat_base(Taux)));
	lay_->addWidget(coeff_achat_base);
	lay_->addWidget(new QLabel("Rapport prix de vente sur le prix d'achat"));
	coeff_vente_achat=new ClavierNumerique(false,_d);
	connect(coeff_vente_achat,SIGNAL(valider(Taux)),this,SLOT(maj_coeff_vente_achat(Taux)));
	lay_->addWidget(coeff_vente_achat);
	lay_->addWidget(new QLabel("Difficulte de gain de points d'experience"));
	diffic_gain_exp=new Curseur();
	connect(diffic_gain_exp,SIGNAL(nouvelle_valeur(int)),this,SLOT(maj_diffic_gain_exp(int)));
	QMetaObject infos_=Difficulte::staticMetaObject;
	diffic_gain_exp->maj_intervalle(0,infos_.enumerator(infos_.indexOfEnumerator("GainPtExp")).keyCount()-1);
	lay_->addWidget(diffic_gain_exp);
	lay_->addWidget(new QLabel("Difficulte lie a l'ecart des degats en tant normal pour le joueur"));
	choix_loi_ut=new Curseur();
	connect(choix_loi_ut,SIGNAL(nouvelle_valeur(int)),this,SLOT(maj_choix_loi_ut(int)));
	choix_loi_ut->maj_intervalle(0,infos_.enumerator(infos_.indexOfEnumerator("Modele")).keyCount()-1);
	lay_->addWidget(choix_loi_ut);
	lay_->addWidget(new QLabel("Difficulte lie a l'ecart des degats en tant normal pour les adversaires"));
	choix_loi_adv=new Curseur();
	connect(choix_loi_adv,SIGNAL(nouvelle_valeur(int)),this,SLOT(maj_choix_loi_adv(int)));
	choix_loi_adv->maj_intervalle(0,infos_.enumerator(infos_.indexOfEnumerator("Modele")).keyCount()-1);
	lay_->addWidget(choix_loi_adv);
	lay_->addWidget(new QLabel("Difficulte lie a l'ecart des degats en tant de confusion pour le joueur"));
	choix_loi_conf_ut=new Curseur();
	connect(choix_loi_conf_ut,SIGNAL(nouvelle_valeur(int)),this,SLOT(maj_choix_loi_conf_ut(int)));
	choix_loi_conf_ut->maj_intervalle(0,infos_.enumerator(infos_.indexOfEnumerator("Modele")).keyCount()-1);
	lay_->addWidget(choix_loi_conf_ut);
	lay_->addWidget(new QLabel("Difficulte lie a l'ecart des degats en tant de confusion pour les adversaires"));
	choix_loi_conf_adv=new Curseur();
	connect(choix_loi_conf_adv,SIGNAL(nouvelle_valeur(int)),this,SLOT(maj_choix_loi_conf_adv(int)));
	choix_loi_conf_adv->maj_intervalle(0,infos_.enumerator(infos_.indexOfEnumerator("Modele")).keyCount()-1);
	lay_->addWidget(choix_loi_conf_adv);
	lay_->addWidget(new QLabel("Rapport gain d'argent sur la base du gain d'argent"));
	coeff_gain_argent_base=new ClavierNumerique(false,_d);
	connect(coeff_gain_argent_base,SIGNAL(valider(Taux)),this,SLOT(maj_coeff_gain_argent_base(Taux)));
	lay_->addWidget(coeff_gain_argent_base);
	lay_->addWidget(new QLabel("Rapport perte d'argent sur gain d'argent"));
	coeff_perte_argent_gain=new ClavierNumerique(false,_d);
	connect(coeff_perte_argent_gain,SIGNAL(valider(Taux)),this,SLOT(maj_coeff_perte_argent_gain(Taux)));
	lay_->addWidget(coeff_perte_argent_gain);
	lay_->addWidget(new QLabel("Rapport maximal d'egalite entre deux statistiques pour une evolution dependant des statistiques"));
	rapport_max_egal_stat_evo=new ClavierNumerique(false,_d);
	connect(rapport_max_egal_stat_evo,SIGNAL(valider(Taux)),this,SLOT(maj_rapport_max_egal_stat_evo(Taux)));
	lay_->addWidget(rapport_max_egal_stat_evo);//affichage_restreint_inventaire
	pp_rest_fin_combat=new BoutonChoix();
	connect(pp_rest_fin_combat,SIGNAL(clic(bool)),this,SLOT(maj_pp_rest_fin_combat(bool)));
	pp_rest_fin_combat->maj_texte("Points de pouvoir restores en fin de combat");
	pp_rest_fin_combat->maj_couleur_choix(QColor(255,0,0,255));
	pp_rest_fin_combat->maj_couleur_fond(QColor(255,255,255,255));
	pp_rest_fin_combat->maj_couleur_rectangle(QColor(0,0,255,255));
	pp_rest_fin_combat->maj_couleur_texte(QColor(0,0,255,255));
	lay_->addWidget(pp_rest_fin_combat);
	affichage_restreint_inventaire=new BoutonChoix();
	connect(affichage_restreint_inventaire,SIGNAL(clic(bool)),this,SLOT(maj_affichage_restreint_inventaire(bool)));
	affichage_restreint_inventaire->maj_texte("Restreindre l'affichage de l'inventaire aux objets dont la quantite est non nulle");
	affichage_restreint_inventaire->maj_couleur_choix(QColor(255,0,0,255));
	affichage_restreint_inventaire->maj_couleur_fond(QColor(255,255,255,255));
	affichage_restreint_inventaire->maj_couleur_rectangle(QColor(0,0,255,255));
	affichage_restreint_inventaire->maj_couleur_texte(QColor(0,0,255,255));
	lay_->addWidget(affichage_restreint_inventaire);
	Bouton *valider_=new Bouton();
	connect(valider_,SIGNAL(clic()),this,SLOT(valider()));
	valider_->maj_texte("Valider");
	valider_->maj_couleur_fond(QColor(255,255,255,255));
	valider_->maj_couleur_rectangle(QColor(0,0,255,255));
	valider_->maj_couleur_texte(QColor(0,0,255,255));
	lay_->addWidget(valider_);
	setLayout(lay_);
	setMinimumHeight(3000);
	setMinimumWidth(1200);
	nb_pk_eq=0;
}

void GestionOption::maj_fiche(const Difficulte& _diff,int _nb_pk_eq){
	difficultes=_diff;
	nb_pk_eq=_nb_pk_eq;
	nom_pk_max->maj_valeur(difficultes.r_nb_max_pk_par_equipe());
	iv_ut->maj_valeur(difficultes.r_iv_ut());
	iv_adv->maj_valeur(difficultes.r_iv_adv());
	valeur_nec_evo_bonheur->maj_valeur(difficultes.r_niv_evo_bonheur_nec());
	diffic_gain_exp->maj_valeur(difficultes.r_difficulte_gain_pts_exp_combat());
	choix_loi_ut->maj_valeur(difficultes.r_choix_lois().first);
	choix_loi_adv->maj_valeur(difficultes.r_choix_lois().second);
	choix_loi_conf_ut->maj_valeur(difficultes.r_choix_lois_conf().first);
	choix_loi_conf_adv->maj_valeur(difficultes.r_choix_lois_conf().second);
	ko_capt->maj_choix(difficultes.r_autorise_ko_capture());
	fuite->maj_choix(difficultes.r_fuite_toujours_possible());
	adj_act->maj_choix(difficultes.r_adjacence_active());
	appar_alea->maj_choix(difficultes.r_appar_alea());
	pp_rest_fin_combat->maj_choix(difficultes.r_attaques_rechargees_fin_combat());
	affichage_restreint_inventaire->maj_choix(difficultes.r_affichage());
	coeff_gain_pts_exp->maj_texte(difficultes.r_coeff_gain_pts_exp_combat().chaine());
	coeff_achat_base->maj_texte(difficultes.r_coeff_achat_par_rapport_base().chaine());
	coeff_vente_achat->maj_texte(difficultes.r_coeff_vente_par_rapport_achat().chaine());
	coeff_gain_argent_base->maj_texte(difficultes.r_taux_gain_argent_base().chaine());
	coeff_perte_argent_gain->maj_texte(difficultes.r_taux_perte_argent_gain().chaine());
	rapport_max_egal_stat_evo->maj_texte(difficultes.r_rapport_max_egalite().chaine());
}

void GestionOption::maj_nom_pk_max(int _nb){
	if(_nb<nb_pk_eq){
		return;
	}
	difficultes.r_nb_max_pk_par_equipe()=_nb;
}

//TODO void GestionOption::maj_diff_gain_cbt_vitesse(){

//}

//void GestionOption::maj_diff_gain_cbt_match_nul(){

//}

void GestionOption::maj_iv_ut(int _nb){
	difficultes.r_iv_ut()=_nb;
}

void GestionOption::maj_iv_adv(int _nb){
	difficultes.r_iv_adv()=_nb;
}

void GestionOption::maj_valeur_nec_evo_bonheur(int _nb){
	difficultes.r_niv_evo_bonheur_nec()=_nb;
}

void GestionOption::maj_ko_capt(bool _capt){
	difficultes.r_autorise_ko_capture()=_capt;
}

void GestionOption::maj_fuite(bool _capt){
	difficultes.r_fuite_toujours_possible()=_capt;
}

void GestionOption::maj_adj_act(bool _capt){
	difficultes.r_adjacence_active()=_capt;
}

void GestionOption::maj_appar_alea(bool _capt){
	difficultes.r_appar_alea()=_capt;
}

void GestionOption::maj_coeff_gain_pts_exp(const Taux& _taux){
	if(_taux<Taux(1LL,3LL)){
		return;
	}
	if(_taux>Taux(3LL)){
		return;
	}
	difficultes.r_coeff_courbe_exp_nec()=_taux;
	//difficultes.r_appar_alea()=_capt;
}

void GestionOption::maj_coeff_achat_base(const Taux& _taux){
	if(_taux<Taux(1LL,3LL)){
		return;
	}
	if(_taux>Taux(3LL)){
		return;
	}
	difficultes.r_coeff_achat_par_rapport_base()=_taux;
}

void GestionOption::maj_coeff_vente_achat(const Taux& _taux){
	if(_taux<Taux(1LL,3LL)){
		return;
	}
	if(_taux>Taux(3LL)){
		return;
	}
	difficultes.r_coeff_vente_par_rapport_achat()=_taux;
}

void GestionOption::maj_diffic_gain_exp(int _diff){
	difficultes.r_difficulte_gain_pts_exp_combat()=_diff;
}

void GestionOption::maj_choix_loi_ut(int _diff){
	difficultes.r_choix_lois().first=_diff;
}

void GestionOption::maj_choix_loi_adv(int _diff){
	difficultes.r_choix_lois().second=_diff;
}

void GestionOption::maj_choix_loi_conf_ut(int _diff){
	difficultes.r_choix_lois_conf().first=_diff;
}

void GestionOption::maj_choix_loi_conf_adv(int _diff){
	difficultes.r_choix_lois_conf().second=_diff;
}

void GestionOption::maj_coeff_gain_argent_base(const Taux& _taux){
	if(_taux<Taux(1LL,3LL)){
		return;
	}
	if(_taux>Taux(3LL)){
		return;
	}
	difficultes.r_taux_gain_argent_base()=_taux;
}

void GestionOption::maj_coeff_perte_argent_gain(const Taux& _taux){
	if(_taux<Taux(1LL,3LL)){
		return;
	}
	if(_taux>Taux(3LL)){
		return;
	}
	difficultes.r_taux_perte_argent_gain()=_taux;
}

void GestionOption::maj_rapport_max_egal_stat_evo(const Taux& _taux){
	if(_taux<Taux(1LL,4LL)){
		return;
	}
	if(_taux>Taux(4LL)){
		return;
	}
	difficultes.r_rapport_max_egalite()=_taux;
}

void GestionOption::maj_pp_rest_fin_combat(bool _rest){
	difficultes.r_attaques_rechargees_fin_combat()=_rest;
}

void GestionOption::maj_affichage_restreint_inventaire(bool _affichage_rest){
	difficultes.r_affichage()=_affichage_rest;
}

void GestionOption::valider(){
	emit maj_diff(difficultes);
}
