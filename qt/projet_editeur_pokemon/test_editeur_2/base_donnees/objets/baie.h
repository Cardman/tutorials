#ifndef BAIE_H
#define BAIE_H
#include "base_donnees/objets/objet.h"
#include "math/taux.h"
#include <QPair>
#include <QString>

/***/
class Baie: public Objet{

	Q_OBJECT
	/***/
	QPair<QString,uchar> type_puiss_dn;

	/***/
	Taux gain_pv_super_eff;
	
	/***/
	Taux loi_proba_premier;
	
	/***/
	HashMap<QString,Taux> mult_degats_adv;
	
	/***/
	HashMap<QString,QPair<Taux,qint8> > mult_statistique_si;
	
	/***/
	bool sans_echec;
	
	/***/
	QPair<QString,QString> soin_pp;
	
	/***/
	QPair<Taux,Taux> soin_pv;
	
	/***/
	QStringList soin_statut;
	
	/***/
	QPair<Taux,Taux> soin_taux_pv_pvmax;
	
	/***/
	HashMap<QString,Taux> taux_degats_recul_adv;

	/***/
	const static HashMap<QString,QString> _descriptions_baies_;

	/***/
	static HashMap<QString,QString> init_descriptions_baies();

public:

	/**@param _effets
	@param _type_puiss_dn type et puissance de don naturel
	@param _prix_achat*/
	Baie(const QStringList&,const QPair<QString,uchar>&,int);

	/**Donne la description d'un objet.*/
	virtual QString description(int)const;

	//virtual QList<QStringList> elements(const QString&)const;

	/**@return la valeur de type_puiss_dn*/
	QPair<QString,uchar> type_puis_dn()const;

	/**@return la valeur de gain_pv_super_eff*/
	Taux gain_pv_sup_ef()const;

	/**@return la valeur de loi_proba_premier*/
	Taux loi_pr()const;

	/**@return la valeur de mult_degats_adv*/
	HashMap<QString,Taux> mult_deg_ad()const;

	/**@return la valeur de mult_statistique_si*/
	HashMap<QString,QPair<Taux,qint8> > mult_stat()const;

	/**@return la valeur de sans_echec*/
	bool reu()const;

	/**@return la valeur de soin_pp*/
	QPair<QString,QString> s_pp()const;

	/**@return la valeur de soin_pv*/
	QPair<Taux,Taux> s_pv()const;

	/**@return la valeur de soin_statut*/
	QStringList s_statut()const;

	/**@return la valeur de soin_taux_pv_pvmax*/
	QPair<Taux,Taux> s_tx_pv()const;

	/**@return la valeur de taux_degats_recul_adv*/
	HashMap<QString,Taux> tx_deg_recul_ad()const;
};
#endif



