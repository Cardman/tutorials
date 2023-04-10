#ifndef FICHECAPACITE_H
#define FICHECAPACITE_H
#include <QStringList>
#include "math/montecarlo/montecarlo.h"
#include "serialisable/math/taux.h"
class Donnees;
/***/
class FicheCapacite{

	/***/
	bool anti_climat;

	/***/
	bool anti_fuite;

	/***/
	QPair<bool,QStringList> anti_fuite_type;

	/***/
	QList<QPair<QString,QString> > anti_immu_attaque;

	/***/
	HashMap<QString,qint8> baisse_statistique_adversaire;

	/***/
	bool bloque_conso_baies_adv;

	/***/
	HashMap<QString,QString> changement_type_si_climat;

	/***/
	bool changement_type_si_degats;

	/***/
	QString climat;

	/***/
	bool copie_capacite;

	/***/
	Taux degats_recul_adv;

	/***/
	Taux degats_recul_adv_si_ko;

	/***/
	QPair<QString,Taux> degats_statut;

	/***/
	int diminue_pas_eclosion;

	/***/
	int divise_tour_sommeil;

	/***/
	HashMap<QString,Taux> gain_pv_si_climat;

	/***/
	HashMap<QString,Taux> gain_pv_type;

	/***/
	QStringList ign_capacite;

	/***/
	QStringList ignore_attaque;

	/***/
	QStringList ignore_boost_statistique_adv;

	/***/
	QStringList immu_anti_fuite;

	/***/
	QStringList immu_attaque;

	/***/
	QStringList immu_attaque_type;

	/***/
	QStringList immu_baisse_statistique;

	/***/
	QList<QPair<QString,QString> > immu_baisse_statistique_si_statut;

	/***/
	bool immu_cc;

	/***/
	QStringList immu_climat;

	/***/
	bool immu_degats_attaques_piegeantes;

	/***/
	bool immu_degats_cauchemar;

	/***/
	bool immu_degats_malediction_2;

	/***/
	bool immu_degats_part;

	/***/
	bool immu_degats_recul;

	/***/
	bool immu_degats_vampigraine;

	/***/
	QStringList immu_capacite;

	/***/
	bool immu_paralysie_totale;

	/***/
	bool immu_picots;

	/***/
	bool immu_piege_de_roc;

	/***/
	bool immu_recharger_tour;

	/**cle climat,pseudo_statut*/
	HashMap<QString,QStringList> immu_statut;

	/***/
	bool lenteur_vitesse;

	/***/
	HashMap<QString,Taux> mult_degats_adv;

	/***/
	Taux mult_degats_cc;

	/***/
	Taux mult_degats_part;

	/***/
	HashMap<bool,Taux> mult_degats_recu;

	/***/
	HashMap<QString,Taux> mult_degats_statut;

	/***/
	Taux mult_proba_cc;

	/***/
	HashMap<bool,Taux> mult_proba_effet_sec;

	/***/
	HashMap<QString,Taux> mult_puissance_attaque_categorie;

	/***/
	HashMap<QString,Taux> mult_puissance_attaques;

	/***/
	Taux mult_puissance_toutes_attaques;

	/***/
	HashMap<QString,Taux> mult_puissance_attaque_type;

	/***/
	HashMap<bool,Taux> mult_puissance_attaque_si_egalite_genre;

	/***/
	QPair<int,Taux> mult_puissance_si_inf_eg;

	/***/
	HashMap<QPair<QString,QString>,Taux> mult_puissance_type_si_climat;

	/***/
	HashMap<QString,QPair<Taux,Taux> >  mult_puissance_type_inf_eg;

	/***/
	Taux mult_stab;

	/***/
	HashMap<QString,QPair<Taux,bool> > mult_statistique;

	/***/
	HashMap<QString,Taux> mult_statistique_part;

	/***/
	HashMap<QString,qint8> mult_statistique_si_adv_ko;

	/***/
	HashMap<QString,qint8> mult_statistique_si_baisse_statistique;

	/***/
	HashMap<QPair<QString,QString>,Taux> mult_statistique_si_categorie;

	/***/
	HashMap<QPair<QString,QString>,Taux> mult_statistique_si_climat;

	/***/
	HashMap<QString,Taux> mult_statistique_si_dernier;

	/***/
	HashMap<QString,Taux> mult_statistique_si_perd_objet;

	/***/
	QPair<HashMap<QString,QPair<QString,qint8> >,QPair<QString,QString> > mult_statistique_si_statistique_adv;

	/***/
	QList<QPair<QString,QPair<QString,Taux> > > mult_statistique_si_statut_coeff;

	/***/
	QList<QPair<QString,QPair<QString,qint8> > > mult_statistique_si_statut_cran;

	/***/
	HashMap<QString,QList<QPair<QString,qint8> > > mult_statistique_si_touche_categorie;

	/***/
	HashMap<QString,QPair<QString,qint8> > mult_statistique_si_touche_type;

	/***/
	char mult_taux_degats_adv_absorb;

	/***/
	Taux mult_variation_cran;

	/***/
	int nb_pp_utilise;

	/***/
	bool nombre_coups;

	/***/
	bool passe_abri;

	/***/
	bool plaque;

	/***/
	bool soin_statut_si_switch;

	/***/
	Taux soin_taux_pvmax_si_switch;

	/***/
	HashMap<QString,uchar> somme_prio;

	/***/
	QStringList statistiques_maximales_si_cc;

	/***/
	Taux statut_ok;

	/***/
	Taux statut_ok_part;

	/***/
	MonteCarlo<MonteCarlo<QString> > statut;

	/***/
	MonteCarlo<QString> statut_simple;

	/***/
	bool touche_pseudo_invulnerable;

	/***/
	HashMap<QString,QString> transfert_statut;

	/***/
	QString type_attaques;

	/***/
	Taux utilise_baie_soin_pv;

	/***/
	bool momie;

	/***/
	Taux coeff_att_peu_eff;

	/***/
	const static HashMap<QString,QString> _descriptions_capacites_;

	/***/
	static HashMap<QString,QString> init_descriptions_capacites();

public:

	/**@param _effets effets de la capacité*/
	FicheCapacite(const QStringList&,Donnees*);

	/**@return la valeur de anti_climat*/
	bool ant_clim()const;

	/**@return la valeur de anti_fuite*/
	bool ant_fuite()const;

	/**@return la valeur de anti_fuite_type*/
	QPair<bool,QStringList> type_anti_fuite()const;

	/**@return la valeur de anti_immu_attaque*/
	QList<QPair<QString,QString> > anti_immu_att()const;

	/**@return la valeur de baisse_statistique_adversaire*/
	HashMap<QString,qint8> baisse_stat_adv()const;

	/**@return la valeur de bloque_conso_baies_adv*/
	bool anti_conso_baies_adv()const;

	/**@return la valeur de changement_type_si_climat*/
	HashMap<QString,QString> chgt_type_clim()const;

	/**@return la valeur de changement_type_si_degats*/
	bool chgt_type_deg()const;

	/**@return la valeur de climat*/
	QString clim()const;

	/**@return la valeur de copie_capacite*/
	bool capac()const;

	/**@return la valeur de degats_recul_adv*/
	Taux deg_recul_adv()const;

	/**@return la valeur de degats_recul_adv_si_ko*/
	Taux deg_recul_adv_ko()const;

	/**@return la valeur de degats_statut*/
	QPair<QString,Taux> deg_statu()const;

	/**@return la valeur de diminue_pas_eclosion*/
	int dim_pas_ecl()const;

	/**@return la valeur de divise_tour_sommeil*/
	int div_tr_som()const;

	/**@return la valeur de gain_pv_si_climat*/
	HashMap<QString,Taux> gain_pv_clim()const;

	/**@return la valeur de gain_pv_type*/
	HashMap<QString,Taux> gain_pv_t()const;

	/**@return la valeur de ign_capacite*/
	QStringList capac_ign()const;

	/**@return la valeur de ignore_attaque*/
	QStringList att_ign()const;

	/**@return la valeur de ignore_boost_statistique_adv*/
	QStringList boost_adv_ign()const;

	/**@return la valeur de immu_anti_fuite*/
	QStringList immu_anti_fuit()const;

	/**@return la valeur de immu_attaque*/
	QStringList immu_att()const;

	/**@return la valeur de immu_attaque_type*/
	QStringList immu_att_t()const;

	/**@return la valeur de immu_baisse_statistique*/
	QStringList immu_bais_statis()const;

	/**@return la valeur de immu_baisse_statistique_si_statut*/
	QList<QPair<QString,QString> > immu_bais_statis_stat()const;

	/**@return la valeur de immu_cc*/
	bool immu_c()const;

	/**@return la valeur de immu_climat*/
	QStringList immu_cl()const;

	/**@return la valeur de immu_degats_attaques_piegeantes*/
	bool immu_deg_att_pieg()const;

	/**@return la valeur de immu_degats_cauchemar*/
	bool immu_deg_cauch()const;

	/**@return la valeur de immu_degats_malediction_2*/
	bool immu_deg_maled()const;

	/**@return la valeur de immu_degats_part*/
	bool immu_deg_part()const;

	/**@return la valeur de immu_degats_recul*/
	bool immu_deg_recul()const;

	/**@return la valeur de immu_degats_vampigraine*/
	bool immu_deg_vampig()const;

	/**@return la valeur de immu_capacite*/
	QStringList immu_cap()const;

	/**@return la valeur de immu_paralysie_totale*/
	bool immu_para_tot()const;

	/**@return la valeur de immu_picots*/
	bool immu_pic()const;

	/**@return la valeur de immu_piege_de_roc*/
	bool immu_pieg()const;

	/**@return la valeur de immu_recharger_tour*/
	bool immu_recharg()const;

	/**@return la valeur de immu_statut*/
	HashMap<QString,QStringList> immu_stat()const;

	/**@return la valeur de lenteur_vitesse*/
	bool lent()const;

	/**@return la valeur de mult_degats_adv*/
	HashMap<QString,Taux> mult_deg_adv()const;

	/**@return la valeur de mult_degats_cc*/
	Taux mult_deg_c()const;

	/**@return la valeur de mult_degats_part*/
	Taux mult_deg_part()const;

	/**@return la valeur de mult_degats_recu*/
	HashMap<bool,Taux> mult_deg_rec()const;

	/**@return la valeur de mult_degats_statut*/
	HashMap<QString,Taux> mult_deg_statut()const;

	/**@return la valeur de mult_proba_cc*/
	Taux mult_pr_cc()const;

	/**@return la valeur de mult_proba_effet_sec*/
	HashMap<bool,Taux> mult_pr_eff_sec()const;

	/**@return la valeur de mult_puissance_attaque_categorie*/
	HashMap<QString,Taux> mult_puis_att_categ()const;

	/**@return la valeur de mult_puissance_attaques*/
	HashMap<QString,Taux> mult_puis_att()const;

	/**@return la valeur de mult_puissance_toutes_attaques*/
	Taux mult_puis_t_att()const;

	/**@return la valeur de mult_puissance_attaque_type*/
	HashMap<QString,Taux> mult_puis_att_t()const;

	/**@return la valeur de mult_puissance_attaque_si_egalite_genre*/
	HashMap<bool,Taux> mult_puis_att_eg_genre()const;

	/**@return la valeur de mult_puissance_si_inf_eg*/
	QPair<int,Taux> mult_puis_inf_eg()const;

	/**@return la valeur de mult_puissance_type_si_climat*/
	HashMap<QPair<QString,QString>,Taux> mult_puis_typ_cl()const;

	/**@return la valeur de mult_puissance_type_inf_eg*/
	HashMap<QString,QPair<Taux,Taux> >  mult_puis_typ_inf_eg()const;

	/**@return la valeur de mult_stab*/
	Taux mult_st()const;

	/**@return la valeur de mult_statistique*/
	HashMap<QString,QPair<Taux,bool> > mult_statis()const;

	/**@return la valeur de mult_statistique_part*/
	HashMap<QString,Taux> mult_statis_part()const;

	/**@return la valeur de mult_statistique_si_adv_ko*/
	HashMap<QString,qint8> mult_statis_adv_ko()const;

	/**@return la valeur de mult_statistique_si_baisse_statistique*/
	HashMap<QString,qint8> mult_statis_bais_stat()const;

	/**@return la valeur de mult_statistique_si_categorie*/
	HashMap<QPair<QString,QString>,Taux> mult_statis_categ()const;

	/**@return la valeur de mult_statistique_si_climat*/
	HashMap<QPair<QString,QString>,Taux> mult_statis_clim()const;

	/**@return la valeur de mult_statistique_si_dernier*/
	HashMap<QString,Taux> mult_statis_der()const;

	/**@return la valeur de mult_statistique_si_perd_objet*/
	HashMap<QString,Taux> mult_statis_perd_obj()const;

	/**@return la valeur de mult_statistique_si_statistique_adv*/
	QPair<HashMap<QString,QPair<QString,qint8> >,QPair<QString,QString> > mult_statis_statis_adv()const;

	/**@return la valeur de mult_statistique_si_statut_coeff*/
	QList<QPair<QString,QPair<QString,Taux> > > mult_statis_statut_coef()const;

	/**@return la valeur de mult_statistique_si_statut_cran*/
	QList<QPair<QString,QPair<QString,qint8> > > mult_statis_statut_cran()const;

	/**@return la valeur de mult_statistique_si_touche_categorie*/
	HashMap<QString,QList<QPair<QString,qint8> > > mult_statis_to_categ()const;

	/**@return la valeur de mult_statistique_si_touche_type*/
	HashMap<QString,QPair<QString,qint8> > mult_statis_to_t()const;

	/**@return la valeur de mult_taux_degats_adv_absorb*/
	char mult_tx_deg_adv_abs()const;

	/**@return la valeur de mult_variation_cran*/
	Taux mult_var_cran()const;

	/**@return la valeur de nb_pp_utilise*/
	int nb_pp_ut()const;

	/**@return la valeur de nombre_coups*/
	bool nb_coups()const;

	/**@return la valeur de passe_abri*/
	bool abri()const;

	/**@return la valeur de plaque*/
	bool plaq()const;

	/**@return la valeur de soin_statut_si_switch*/
	bool soin_statut_sw()const;

	/**@return la valeur de soin_taux_pvmax_si_switch*/
	Taux soin_tx_pvmax_sw()const;

	/**@return la valeur de somme_prio*/
	HashMap<QString,uchar> som_pr()const;

	/**@return la valeur de statistiques_maximales_si_cc*/
	QStringList statis_max_cc()const;

	/**@return la valeur de statut_ok*/
	Taux statut_o()const;

	/**@return la valeur de statut_ok_part*/
	Taux statut_o_p()const;

	/**@return la valeur de statut*/
	MonteCarlo<MonteCarlo<QString> > statut_l()const;
	
	/**@return la valeur de statut_simple*/
	MonteCarlo<QString> statut_sim()const;

	/**@return la valeur de touche_pseudo_invulnerable*/
	bool to_pseud_invul()const;

	/**@return la valeur de transfert_statut*/
	HashMap<QString,QString> transf_statut()const;

	/**@return la valeur de type_attaques*/
	QString t_att()const;

	/**@return la valeur de utilise_baie_soin_pv*/
	Taux ut_baie_soin_pv()const;

	/**@return la valeur de momie*/
	bool mom()const;

	/**@return coeff_att_peu_eff*/
	Taux co_att_pef()const;

	Taux taux_act(bool _neg)const;

	/**Donne la description d'un objet.
	appelle description_part
	@param _langue langue de destination*/
	QString description(int,Donnees*)const;

	/**@param _effet l'effet dont on veut récupérer les éléments (_effet est une chaîne de départ) on recherche en boucle
	si le retour est vide alors l'effet n'est pas présent*/
	//QList<QStringList> elements(const QString&)const;
};

#endif



