#ifndef GESTIONOPTION_H
#define GESTIONOPTION_H

#include <QLabel>
#include "serialisable/difficulte/difficulte.h"

class Curseur;
class BoutonChoix;
class ClavierNumerique;
class GestionOption : public QLabel{

	Donnees *donnees;

	int nb_pk_eq;

	Difficulte difficultes;

	Curseur *nom_pk_max;

	//TODO Curseur *diff_gain_cbt_vitesse;

	//Curseur *diff_gain_cbt_match_nul;

	Curseur *iv_ut;

	Curseur *iv_adv;

	Curseur *valeur_nec_evo_bonheur;

	BoutonChoix *ko_capt;

	BoutonChoix *fuite;

	BoutonChoix *adj_act;

	BoutonChoix *appar_alea;

	ClavierNumerique *coeff_gain_pts_exp;

	ClavierNumerique *coeff_achat_base;

	ClavierNumerique *coeff_vente_achat;

	Curseur *diffic_gain_exp;

	Curseur *choix_loi_ut;

	Curseur *choix_loi_adv;

	Curseur *choix_loi_conf_ut;

	Curseur *choix_loi_conf_adv;

	ClavierNumerique *coeff_gain_argent_base;

	ClavierNumerique *coeff_perte_argent_gain;

	ClavierNumerique *rapport_max_egal_stat_evo;

	BoutonChoix *pp_rest_fin_combat;

	BoutonChoix *affichage_restreint_inventaire;

	Q_OBJECT

public:

	GestionOption(Donnees*);

	void maj_fiche(const Difficulte&,int);

signals:

	void maj_diff(const Difficulte&);

private slots:

	void maj_nom_pk_max(int);

	//TODO void maj_diff_gain_cbt_vitesse();

	//void maj_diff_gain_cbt_match_nul();

	void maj_iv_ut(int);

	void maj_iv_adv(int);

	void maj_valeur_nec_evo_bonheur(int);

	void maj_ko_capt(bool);

	void maj_fuite(bool);

	void maj_adj_act(bool);

	void maj_appar_alea(bool);

	void maj_coeff_gain_pts_exp(const Taux&);

	void maj_coeff_achat_base(const Taux&);

	void maj_coeff_vente_achat(const Taux&);

	void maj_diffic_gain_exp(int);

	void maj_choix_loi_ut(int);

	void maj_choix_loi_adv(int);

	void maj_choix_loi_conf_ut(int);

	void maj_choix_loi_conf_adv(int);

	void maj_coeff_gain_argent_base(const Taux&);

	void maj_coeff_perte_argent_gain(const Taux&);

	void maj_rapport_max_egal_stat_evo(const Taux&);

	void maj_pp_rest_fin_combat(bool);

	void maj_affichage_restreint_inventaire(bool);

	void valider();
};

#endif // GESTIONOPTION_H
