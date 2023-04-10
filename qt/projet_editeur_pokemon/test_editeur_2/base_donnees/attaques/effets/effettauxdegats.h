#ifndef EFFETTAUXDEGATS_H
#define EFFETTAUXDEGATS_H
#include "base_donnees/attaques/effets/effettaux.h"

/***/
class EffetTauxDegats: public EffetTaux{

public:

	/**@param _ligne*/
	EffetTauxDegats(const QString&);

	/**Donne la description d'un objet.
	@param _langue langue de destination*/
	virtual QString description(int)const;
};
#endif



