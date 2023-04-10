#ifndef REVENTE_H
#define REVENTE_H
#include "base_donnees/objets/objet.h"
/***/
class Revente:public Objet{

	Q_OBJECT
	
	const static QStringList _descriptions_renventes_;

	
	static QStringList init_descriptions_renventes();

public:

	/**@param _prix_vente*/
	Revente(int);

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;
};

#endif



