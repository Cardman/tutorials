#ifndef EVOLUTIONNIVEAU_H
#define EVOLUTIONNIVEAU_H
#include "base_donnees/evolution/evolution.h"

/**Contient le niveau d'evolution a obtenir pour faire evoluer le pokemon*/
class EvolutionNiveau: public Evolution{

	Q_OBJECT

	/***/
	uchar niveau;

public:

	/**@param _niveau*/
	EvolutionNiveau(uchar);

	/**@return la valeur de niveau*/
	uchar niv()const;

	/***/
	virtual QString description(const QString&,const QString&,int)const;
};
#endif



