#ifndef EFFETTAUXPVPVMAX_H
#define EFFETTAUXPVPVMAX_H
#include "base_donnees/attaques/effets/effettaux.h"
#include <QString>

/***/
class EffetTauxPVPVMax: public EffetTaux{

	/***/
	QString climat;

public:

	/**@param _ligne*/
	EffetTauxPVPVMax(const QString&);

	/**@return la valeur de climat*/
	QString cl()const;

	/**Donne la description d'un objet.
	@param _langue langue de destination*/
	virtual QString description(int)const;
};
#endif



