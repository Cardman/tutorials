#ifndef EVOLUTIONPIERREEVOLUTIVEGENRE_H
#define EVOLUTIONPIERREEVOLUTIVEGENRE_H
#include "base_donnees/evolution/evolutionpierreevolutive.h"

/**Classe combinant la necessite d'avoir un genre particulier et la necissite de donner une pierre evolutive.*/
class EvolutionPierreEvolutiveGenre: public EvolutionPierreEvolutive{

	/***/
	QString genre;

public:

	/**@param _genre
	@param _pierre*/
	EvolutionPierreEvolutiveGenre(const QString&,const QString&);

	/**@return la valeur de genre*/
	QString gr()const;

	/***/
	virtual QString description(const QString&,const QString&,int)const;
};
#endif



