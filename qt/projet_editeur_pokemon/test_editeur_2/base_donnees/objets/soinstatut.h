#ifndef SOINSTATUT_H
#define SOINSTATUT_H
#include "base_donnees/objets/soin.h"
#include <QString>

/***/
class SoinStatut: public Soin{

	Q_OBJECT

	/**Ensemble des statuts qui peuvent etre soignes.*/
	QStringList statuts;

	/***/
	bool soin_ko;

public:

	/**@param _effets
	@param _statuts
	@param _prix_achat*/
	SoinStatut(const QStringList&,const QStringList&,int);

	/**@return la valeur de statuts*/
	QStringList stats()const;

	/**@return la valeur de soin_ko*/
	bool s_ko()const;

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;
};
#endif



