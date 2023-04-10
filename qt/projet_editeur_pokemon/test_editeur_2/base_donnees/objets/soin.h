#ifndef SOIN_H
#define SOIN_H
#include "base_donnees/objets/objet.h"

/***/
class Soin: public Objet{

	Q_OBJECT

	/***/
	QPair<uchar,uchar> bonheur;

	/***/
	bool soin_equipe;

protected:

	
	const static HashMap<QString,QString> _descriptions_soins_;

	
	static HashMap<QString,QString> init_descriptions_soins();

public:

	/**@param _effets
	@param _prix_achat*/
	Soin(const QStringList&,int);

	/**@return la valeur de bonheur*/
	QPair<uchar,uchar> bonh()const;

	/**@return la valeur de soin_equipe*/
	bool soin_eq()const;

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;
};
#endif



