#ifndef EFFETCLIMAT_H
#define EFFETCLIMAT_H
#include "base_donnees/attaques/effets/effet.h"
#include <QString>

/***/
class EffetClimat: public Effet{

	Q_OBJECT

	/**Nom du climat*/
	QString nom_climat;

public:

	/**@param _ligne*/
	EffetClimat(const QString&);

	/**@return la valeur de nom_climat*/
	QString cl()const;

	/**Donne la description d'un objet.
	@param _langue langue de destination*/
	virtual QString description(int,Donnees*)const;
};
#endif



