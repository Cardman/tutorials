#ifndef SOINPVSTATUT_H
#define SOINPVSTATUT_H
#include "serialisable/math/taux.h"
#include "base_donnees/objets/soinstatut.h"

/***/
class SoinPVStatut: public SoinStatut{

	Q_OBJECT

	/**taux de soin des pv sur les pv max*/
	Taux taux_soin;

public:

	/**@param _effets
	@param _statuts
	@param _taux_soin
	@param _prix_achat*/
	SoinPVStatut(const QStringList&,const QStringList&,const Taux&,int);

	/**@return la valeur de taux_soin*/
	Taux tx_soin()const;

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int,Donnees*)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;
};
#endif



