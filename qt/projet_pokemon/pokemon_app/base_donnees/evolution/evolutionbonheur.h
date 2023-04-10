#ifndef EVOLUTIONBONHEUR_H
#define EVOLUTIONBONHEUR_H
#include "base_donnees/evolution/evolution.h"

/**Classe sans attribut caracterisant l'obtention d'un niveau suffisant de bonheur pour pouvoir evoluer, en montant d'un niveau.*/
class EvolutionBonheur: public Evolution{

	Q_OBJECT

public:

	/***/
	EvolutionBonheur();

	/***/
	virtual QString description(const QString&,const QString&,int,Donnees* _d)const;
};
#endif



