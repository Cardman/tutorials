#ifndef EFFETTAUXPVRESTANTS_H
#define EFFETTAUXPVRESTANTS_H
#include "base_donnees/attaques/effets/effettaux.h"

/***/
class EffetTauxPVRestants: public EffetTaux{

	Q_OBJECT

public:

	/**@param _ligne*/
	EffetTauxPVRestants(const QString&);

	/**Donne la description d'un objet.
	@param _langue langue de destination*/
	virtual QString description(int,Donnees*)const;
};
#endif



