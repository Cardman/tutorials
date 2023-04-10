#ifndef BOOST_H
#define BOOST_H
#include "base_donnees/objets/objet.h"
#include "serialisable/math/taux.h"
#include <QString>

/**Boost d'une statistique ou des points de pouvoir.*/
class Boost: public Objet{

	Q_OBJECT

	/**valeurs possibles:
	-ATT
	-DEF
	-ATT_SPE
	-DEF_SPE
	-VIT
	-PV
	-PP*/
	//QString effet;

	/***/
	Taux gain_pp;

	/***/
	QPair<uchar,uchar> bonheur;

	/***/
	QPair<QString,Taux> gain_ev;

	
	const static HashMap<QString,QString> _descriptions_boosts_;

	
	static HashMap<QString,QString> init_descriptions_boosts();

public:

	/**@param _effets
	@param _effet
	@param _prix_achat*/
	Boost(const QStringList& _effets,const QString&,int);

	/**@return la valeur de gain_pp*/
	Taux g_pp()const;

	/**@return la valeur de bonheur*/
	QPair<uchar,uchar> bonh()const;

	/**@return la valeur de gain_ev*/
	QPair<QString,Taux> g_ev()const;

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int,Donnees*)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;
};
#endif



