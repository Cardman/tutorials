#ifndef PLAQUE_H
#define PLAQUE_H
#include "base_donnees/objets/objet.h"
#include "serialisable/math/taux.h"
/***/
class Plaque:public Objet{

	Q_OBJECT
	/***/
	QString type_plaque;

	/***/
	QString type_pk;

	/***/
	Taux coeff;

	
	const static QStringList _descriptions_plaques_;

	
	static QStringList init_descriptions_plaques();

public:

	/**
	@param _type_plaque
	@param _type_pk
	@param _coeff
	@param _prix
	*/
	Plaque(const QString&,const QString&,const Taux&,int);

	/**@return la valeur de type_plaque*/
	QString tp_pl()const;

	/**@return la valeur de type_pk*/
	QString tp_pk()const;

	/**@return la valeur de coeff*/
	Taux co()const;

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int,Donnees*)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;
};

#endif



