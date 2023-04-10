#ifndef EFFETMULTPUISSATTAQUE_H
#define EFFETMULTPUISSATTAQUE_H
#include "base_donnees/attaques/effets/effet.h"
#include "serialisable/math/taux.h"
#include <QString>

/***/
class EffetMultPuissAttaque: public Effet{

	Q_OBJECT

	/***/
	QString type;

	/***/
	Taux coeff;

	/**Pour les attaques du lanceur
	si le booléen est vrai alors ce sont les attaques du lanceur qui auront leur puissance multiplié
	sinon ce sont les attaques touchant le lanceur*/
	bool non_subi;

public:

	/**@param _ligne*/
	EffetMultPuissAttaque(const QString&);

	/**@return la valeur de type*/
	QString tp()const;

	/**@return la valeur de coeff*/
	Taux co()const;

	/**@return la valeur de non_subi*/
	bool n_subi()const;

	/**Donne la description d'un objet.
	@param _langue langue de destination*/
	virtual QString description(int,Donnees*)const;
};
#endif



