#ifndef DIFFICULTE_H
#define DIFFICULTE_H
#include "serialisable/math/taux.h"
#include "flux/flux.h"
#include <QPair>
class Donnees;

/**Decrit les parametres modifiable par rapport a la difficulte du jeu.
(bonheur max, niveau bonheur evolution, nombre de points d'experience donnes en combat, loi de probabilite sur la marge d'erreur, avantage en cas d'egalite (utilisateur ou adversaire ou aleatoire uniforme), capture des pokemons, possibilite de mise a KO pour capture, maximum ev, bonus statistique par iv, prix des objets (vente, achat), gain ou perte d'argent pendant les combats contre les dresseurs)*/
class Difficulte{

	/***/
	uchar nb_max_pk_par_equipe;

	/***/
	bool autorise_ko_capture;

	/***/
	bool choix_loi_capture_classique;

	uchar difficulte_gain_pts_exp_combat;

	/***/
	Taux coeff_gain_pts_exp_combat;

	/***/
	Taux coeff_courbe_exp_nec;

	/***/
	Taux coeff_achat_par_rapport_base;

	/***/
	Taux coeff_vente_par_rapport_achat;

	/***/
	uchar difficulte_gain_vitesse_combat;

	/***/
	QPair<uchar,uchar> choix_lois;

	/***/
	QPair<uchar,uchar> choix_lois_conf;

	/***/
	uchar difficulte_gain_combat_nul;

	/***/
	Taux taux_gain_argent_base;

	/***/
	Taux taux_perte_argent_gain;

	/***/
	int niv_max_bonheur;

	/***/
	int niv_evo_bonheur_nec;

	/***/
	int max_ev;

	/***/
	uchar iv_ut;

	/***/
	uchar iv_adv;

	/***/
	bool fuite_toujours_possible;

	bool attaques_rechargees_fin_combat;

	/***/
	bool presence_objets_repousse;

	/**Les attaques dépendant des positions sont différentes en fonction de cette variable*/
	bool adjacence_active;

	bool appar_alea;

	bool affichage;

	Taux rapport_max_egalite;

	Q_GADGET
	Q_ENUMS(Modele)
	Q_ENUMS(GainPtExp)

public:

	enum Modele{CONSTANT_MIN,CROISSANT,UNIFORME,DECROISSANT,CONSTANT_MAX};

	enum GainPtExp{TRES_FACILE,FACILE,DIFFICILE,TRES_DIFFICILE};

	Difficulte();

	Difficulte(Donnees*);

	/***/
	uchar& r_nb_max_pk_par_equipe();

	/***/
	bool& r_autorise_ko_capture();

	/***/
	bool& r_choix_loi_capture_classique();

	uchar& r_difficulte_gain_pts_exp_combat();

	/***/
	Taux& r_coeff_gain_pts_exp_combat();

	/***/
	Taux& r_coeff_courbe_exp_nec();

	/***/
	Taux& r_coeff_achat_par_rapport_base();

	/***/
	Taux& r_coeff_vente_par_rapport_achat();

	/***/
	uchar& r_difficulte_gain_vitesse_combat();

	/***/
	QPair<uchar,uchar>& r_choix_lois();

	/***/
	QPair<uchar,uchar>& r_choix_lois_conf();

	/***/
	uchar& r_difficulte_gain_combat_nul();

	/***/
	Taux& r_taux_gain_argent_base();

	/***/
	Taux& r_taux_perte_argent_gain();

	/***/
	int& r_niv_max_bonheur();

	/***/
	int& r_niv_evo_bonheur_nec();

	/***/
	int& r_max_ev();

	/***/
	uchar& r_iv_ut();

	/***/
	uchar& r_iv_adv();

	/***/
	bool& r_fuite_toujours_possible();

	bool& r_attaques_rechargees_fin_combat();

	/***/
	bool& r_presence_objets_repousse();

	/***/
	bool& r_adjacence_active();

	bool& r_appar_alea();

	bool& r_affichage();

	Taux& r_rapport_max_egalite();

	uchar r_nb_max_pk_par_equipe()const;

	/***/
	bool r_autorise_ko_capture()const;

	/***/
	bool r_choix_loi_capture_classique()const;

	uchar r_difficulte_gain_pts_exp_combat()const;

	/***/
	Taux r_coeff_gain_pts_exp_combat()const;

	/***/
	Taux r_coeff_courbe_exp_nec()const;

	/***/
	Taux r_coeff_achat_par_rapport_base()const;

	/***/
	Taux r_coeff_vente_par_rapport_achat()const;

	/***/
	uchar r_difficulte_gain_vitesse_combat()const;

	/***/
	QPair<uchar,uchar> r_choix_lois()const;

	/***/
	QPair<uchar,uchar> r_choix_lois_conf()const;

	/***/
	uchar r_difficulte_gain_combat_nul()const;

	/***/
	Taux r_taux_gain_argent_base()const;

	/***/
	Taux r_taux_perte_argent_gain()const;

	/***/
	int r_niv_max_bonheur()const;

	/***/
	int r_niv_evo_bonheur_nec()const;

	/***/
	int r_max_ev()const;

	/***/
	uchar r_iv_ut()const;

	/***/
	uchar r_iv_adv()const;

	/***/
	bool r_fuite_toujours_possible()const;

	bool r_attaques_rechargees_fin_combat()const;

	/***/
	bool r_presence_objets_repousse()const;

	/***/
	bool r_adjacence_active()const;

	bool r_appar_alea()const;

	bool r_affichage()const;

	Taux r_rapport_max_egalite()const;

	Taux taux_gain(uchar,uchar);
	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const Difficulte&);
Flux & operator >>(Flux&,Difficulte&);

#endif


