#ifndef EVOLUTIONPIERREEVOLUTIVE_H
#define EVOLUTIONPIERREEVOLUTIVE_H
#include "base_donnees/evolution/evolution.h"
#include <QString>

/**Classe permettant de decrire l'evolution d'un pokemon en lui donnant une pierre evolutive.*/
class EvolutionPierreEvolutive: public Evolution{

	/***/
	QString pierre;

	Q_OBJECT
public:

	/**@param _pierre*/
	EvolutionPierreEvolutive(const QString&);

	/**@return la valeur de pierre*/
	QString nom_pierre()const;

	/***/
	virtual QString description(const QString&,const QString&,int)const;
};
#endif



