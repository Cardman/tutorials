#ifndef EFFETSTATISTIQUE_H
#define EFFETSTATISTIQUE_H
#include "base_donnees/attaques/effets/effet.h"
#include "serialisable/math/taux.h"
#include <QList>
#include <QPair>
#include <QString>

/***/
class EffetStatistique: public Effet{

	Q_OBJECT

	/***/
	HashMap<QString,qint8> statis_var_crans;

	/**proba relative que l'effet ait lieu*/
	Taux proba_actif;

public:

	/**Construction de l'effet à partir d'une chaine lue d'un fichier
	@param _ligne*/
	EffetStatistique(const QString&);

	/**@return la valeur de statis_var_crans*/
	HashMap<QString,qint8> stat_cr()const;

	/**@return la valeur de proba_actif*/
	Taux pr_ac()const;

	/**Donne la description d'un objet.
	@param _langue langue de destination*/
	virtual QString description(int,Donnees*)const;
};
#endif



