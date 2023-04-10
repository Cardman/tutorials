#ifndef REPOUSSE_H
#define REPOUSSE_H
#include "base_donnees/objets/objet.h"
/***/
class Repousse:public Objet{

	Q_OBJECT
	
	const static QStringList _descriptions_repousses_;

	uint nb_pas;

	/***/
	static QStringList init_descriptions_repousses();

public:

	/**@param _prix_vente*/
	Repousse(uint,int);

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int)const;

};

#endif

