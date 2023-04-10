#ifndef EFFETTAUX_H
#define EFFETTAUX_H
#include "base_donnees/attaques/effets/effet.h"
#include "serialisable/math/taux.h"

/**classe abstraite*/
class EffetTaux: public Effet{

	Q_OBJECT

	/***/
	Taux taux;

public:

	/**@param _ligne*/
	EffetTaux(const QString&);

	/**@return la valeur de taux*/
	Taux tx()const;
};
#endif



