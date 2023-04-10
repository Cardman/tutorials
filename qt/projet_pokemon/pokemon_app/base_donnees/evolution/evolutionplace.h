#ifndef EVOLUTIONPLACE_H
#define EVOLUTIONPLACE_H
#include "base_donnees/evolution/evolution.h"
#include <QString>

/**Pokemon supplementaire a avoir dans l'equipe pour l'evolution.*/
class EvolutionPlace: public Evolution{

	Q_OBJECT

	/***/
	QString nom_pokemon;

public:

	/**@param _nom*/
	EvolutionPlace(const QString&);

	/**@return la valeur de nom_pokemon*/
	QString nom()const;

	/***/
	virtual QString description(const QString&,const QString&,int,Donnees* _d)const;
};
#endif



