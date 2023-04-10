#ifndef SOINPP_H
#define SOINPP_H
#include "base_donnees/objets/soin.h"
#include <QPair>
#include <QString>

/***/
class SoinPP: public Soin{

	Q_OBJECT

	/***/
	QPair<QString,QString> effets_sec;

public:

	/**@param _effets
	@param _effets_sec
	@param _prix_achat*/
	SoinPP(const QStringList&,const QPair<QString,QString>&,int);

	/**@return la valeur de effets_sec*/
	QPair<QString,QString> effs_se()const;

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int,Donnees*)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;
};
#endif



