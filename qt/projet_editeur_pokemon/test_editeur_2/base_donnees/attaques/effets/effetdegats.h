#ifndef EFFETDEGATS_H
#define EFFETDEGATS_H
#include "base_donnees/attaques/effets/effet.h"

/***/
class EffetDegats: public Effet{

	/***/
	int puissance;

	/***/
	char taux_cc;

	/***/
	bool degats_fixe;

	Q_OBJECT

public:

	/**Construction de l'effet à partir d'une chaine lue d'un fichier
	@param _ligne*/
	EffetDegats(const QString&);

	/**@return la valeur de puissance*/
	int puis()const;

	/**@return la valeur de taux_cc*/
	char tx_cc()const;

	/**@return la valeur de degats_fixe*/
	bool deg_fixe()const;

	/***/
	void fixer_degats();

	/**Donne la description d'un objet.
	@param _langue langue de destination*/
	virtual QString description(int)const;
};
#endif



