#ifndef EFFETANTIIMMU_H
#define EFFETANTIIMMU_H
#include "base_donnees/attaques/effets/effet.h"
#include <QPair>
#include <QString>

/***/
class EffetAntiImmu: public Effet{

	/***/
	QList<QPair<QString,QString> > types;

public:

	/**@param _ligne*/
	EffetAntiImmu(const QString&);

	/**@return la valeur de types*/
	QList<QPair<QString,QString> > tp()const;

	/**Donne la description d'un objet.
	@param _langue langue de destination*/
	virtual QString description(int)const;
};
#endif



