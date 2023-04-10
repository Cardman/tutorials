#ifndef SOINPV_H
#define SOINPV_H
#include "base_donnees/objets/soin.h"
#include "math/taux.h"

/***/
class SoinPV: public Soin{

	Q_OBJECT

	/**Maximum de points de vie restaures*/
	Taux pv_max_rest;
public:

	/**@param _effets
	@param _pv_max_rest
	@param _prix_achat*/
	SoinPV(const QStringList&,const Taux&,int);

	/**@return la valeur de pv_max_rest*/
	Taux pv_m_res()const;

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;
};
#endif



