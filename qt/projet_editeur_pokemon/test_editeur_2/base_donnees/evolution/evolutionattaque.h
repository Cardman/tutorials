#ifndef EVOLUTIONATTAQUE_H
#define EVOLUTIONATTAQUE_H
#include "base_donnees/evolution/evolution.h"
#include <QString>

/**Le pokemon doit connaitre une attaque particuliere pour pouvoir evoluer.*/
class EvolutionAttaque: public Evolution{

	Q_OBJECT

	/***/
	QString nom_attaque;

public:

	/**@param _nom_attaque*/
	EvolutionAttaque(const QString&);

	/**@return la valeur de nom_attaque*/
	QString attaque()const;

	/***/
	virtual QString description(const QString&,const QString&,int)const;
};
#endif



