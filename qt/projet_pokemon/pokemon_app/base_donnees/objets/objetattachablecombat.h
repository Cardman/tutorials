#ifndef OBJETATTACHABLECOMBAT_H
#define OBJETATTACHABLECOMBAT_H
#include "base_donnees/objets/objet.h"
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/math/taux.h"
#include "math/montecarlo/montecarlo.h"

/***/
class ObjetAttachableCombat: public Objet{

	Q_OBJECT
	/***/
	//QStringList infos;

	/***/
	bool annule_immu_type;

	/***/
	bool anti_evo;

	/***/
	bool attaque_dernier;

	/***/
	bool calcul_experience;

	/***/
	//bool changement_forme;

	/***/
	bool fuite_reussie;

	/***/
	bool immu_amour;

	/***/
	bool immu_baisse_statistique;

	/***/
	bool nb_tours_pieges;

	/***/
	bool prepa_vite;

	/***/
	bool repousse_sauvages;

	/***/
	bool switch_reussi;

	/***/
	bool synchro_amour;

	/***/
	bool usage_unique;

	/***/
	Taux anti_ko;

	/***/
	Taux anti_ko_si_tous_pv;

	/***/
	Taux degats_recul;

	/***/
	Taux draine_taux_degats;

	/***/
	HashMap<QString,uchar> gain_ev_combat;

	/***/
	Taux gain_pv_tous;

	/***/
	HashMap<QString,Taux> gain_pv_sel;

	/***/
	MonteCarlo<bool> loi_proba_premier;

	/***/
	Taux mult_degats_att_piegeante;

	/***/
	Taux mult_gain_argent;

	/***/
	Taux mult_gain_bonheur;

	/***/
	Taux mult_gain_ev;

	/***/
	Taux mult_gain_experience;

	/***/
	Taux mult_puissance_attaque;

	/***/
	Taux mult_puissance_attaque_sup_eff;

	/***/
	HashMap<QString,Taux> mult_puissance_attaque_categorie;

	/***/
	Taux mult_puissance_attaque_consecutive;

	/**nom_pk,type*/
	HashMap<QPair<QString,QString>,Taux> mult_puissance_attaque_pokemon_types;

	/***/
	HashMap<QString,Taux> mult_puissance_attaque_type;

	/***/
	Taux mult_pv_draines;

	/***/
	Taux deg_recul;

	/***/
	HashMap<QString,QPair<Taux,bool> > mult_statistique_adv;

	/**vrai <=> coeff*/
	HashMap<QString,QPair<Taux,bool> > mult_statistique;

	/**nom_pk,statis*/
	HashMap<QPair<QString,QString>,Taux> mult_statistique_pokemon_coeff;

	/**nom_pk,statis*/
	HashMap<QPair<QString,QString>,qint8> mult_statistique_pokemon_cran;

	/***/
	HashMap<QString,Taux> mult_statistique_si_dernier;

	/***/
	QStringList nb_tours_climat;

	/***/
	int nb_tours_protection;

	/***/
	QStringList reproduction;

	/***/
	QStringList sensible_type;

	/***/
	QString statut_fin_tour_lanceur;

	/***/
	QStringList immu_type;

	/***/
	bool detruit_si_contact;

	/***/
	bool switch_possible_si_touche;

	/***/
	bool switch_force_adv_si_touche;

	/***/
	HashMap<QString,Taux> mult_statistique_pre_evo;

	/***/
	Taux mult_masse;

	/***/
	QStringList sans_effet_capacite;

	/***/
	bool transfert_obj_si_contact;

	/***/
	const static HashMap<QString,QString> _descriptions_objets_;

	/***/
	static HashMap<QString,QString> init_descriptions_objetsatt();

public:

	/**@param _effets
	@param _prix_achat*/
	ObjetAttachableCombat(const QStringList&,int _prix_achat=0);
	/*@param _effets
	@param _infos
	@param _prix_achat*/
	//ObjetAttachableCombat(const QStringList&,const QStringList&,int _prix_achat=0);

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int,Donnees*)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;

	/**@return la valeur de anti_ko*/
	Taux a_ko()const;

	/**@return la valeur de anti_ko_si_tous_pv*/
	Taux a_ko_pv()const;

	/**@return la valeur de degats_recul*/
	Taux deg_rec()const;

	/**@return la valeur de draine_taux_degats*/
	Taux dr_tx_deg()const;

	/**@return la valeur de gain_ev_combat*/
	HashMap<QString,uchar> gain_ev_cbt()const;

	/**@return la valeur de gain_pv_tous*/
	Taux gain_pv_t()const;

	/**@return la valeur de gain_pv_sel*/
	HashMap<QString,Taux> gain_pv_s()const;

	/**@return la valeur de loi_proba_premier*/
	MonteCarlo<bool> loi_prem()const;

	/**@return la valeur de mult_degats_att_piegeante*/
	Taux mult_deg_pieg()const;

	/**@return la valeur de mult_gain_argent*/
	Taux mult_gain_arg()const;

	/**@return la valeur de mult_gain_bonheur*/
	Taux mult_gain_bonh()const;

	/**@return la valeur de mult_gain_ev*/
	Taux mult_gn_ev()const;

	/**@return la valeur de mult_gain_experience*/
	Taux mult_gain_exp()const;

	/**@return la valeur de mult_puissance_attaque*/
	Taux mult_puiss_att()const;

	/**@return la valeur de mult_puissance_attaque_sup_eff*/
	Taux mult_puiss_att_sup_eff()const;

	/**@return la valeur de mult_puissance_attaque_categorie*/
	HashMap<QString,Taux> mult_puiss_att_categ()const;

	/**@return la valeur de mult_puissance_attaque_consecutive*/
	Taux mult_puiss_att_consec()const;

	/**@return la valeur de mult_puissance_attaque_pokemon_types*/
	HashMap<QPair<QString,QString>,Taux> mult_puiss_att_pk_types()const;

	/**@return la valeur de mult_puissance_attaque_type*/
	HashMap<QString,Taux> mult_puiss_att_type()const;

	/**@return la valeur de mult_pv_draines*/
	Taux mult_pv_drai()const;

	/**@return la valeur de deg_recul*/
	Taux recul()const;

	/**@return la valeur de mult_statistique_adv*/
	HashMap<QString,QPair<Taux,bool> > mult_stat_adv()const;

	/**@return la valeur de mult_statistique*/
	HashMap<QString,QPair<Taux,bool> > mult_stat()const;

	/**@return la valeur de mult_statistique_pokemon_coeff*/
	HashMap<QPair<QString,QString>,Taux> mult_stat_pk_co()const;

	/**@return la valeur de mult_statistique_pokemon_cran*/
	HashMap<QPair<QString,QString>,qint8> mult_stat_pk_cr()const;

	/**@return la valeur de mult_statistique_si_dernier*/
	HashMap<QString,Taux> mult_stat_der()const;

	/**@return la valeur de nb_tours_climat*/
	QStringList nb_trs_cl()const;

	/**@return la valeur de nb_tours_protection*/
	int nb_trs_prot()const;

	/**@return la valeur de reproduction*/
	QStringList reprod()const;

	/**@return la valeur de sensible_type*/
	QStringList sens_type()const;

	/**@return la valeur de statut_fin_tour_lanceur*/
	QString statut_tr_lanc()const;

	/**@return la valeur de annule_immu_type*/
	bool annule_immu_t()const;

	/**@return la valeur de anti_evo*/
	bool anti_ev()const;

	/**@return la valeur de attaque_dernier*/
	bool att_der()const;

	/**@return la valeur de calcul_experience*/
	bool calc_exp()const;

	/**@return la valeur de fuite_reussie*/
	bool fuite_re()const;

	/**@return la valeur de immu_amour*/
	bool immu_am()const;

	/**@return la valeur de immu_baisse_statistique*/
	bool immu_bais_stat()const;

	/**@return la valeur de nb_tours_pieges*/
	bool nb_trs_pieg()const;

	/**@return la valeur de prepa_vite*/
	bool prepa_v()const;

	/**@return la valeur de repousse_sauvages*/
	bool rep_sauv()const;

	/**@return la valeur de switch_reussi*/
	bool switch_re()const;

	/**@return la valeur de synchro_amour*/
	bool sync_am()const;

	/**@return la valeur de usage_unique*/
	bool us_uniq()const;

	bool exp_ev()const;
};
#endif



