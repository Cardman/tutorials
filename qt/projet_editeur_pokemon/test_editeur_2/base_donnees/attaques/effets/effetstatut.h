#ifndef EFFETSTATUT_H
#define EFFETSTATUT_H
#include "base_donnees/attaques/effets/effet.h"
#include "math/montecarlo/montecarlo.h"
#include <QString>

/***/
class EffetStatut: public Effet{

	/***/
	bool pseudo_statut;

	/***/
	MonteCarlo<MonteCarlo<QString> > loi_proba_statuts;
public:

	/**@param _ligne*/
	EffetStatut(const QString&);

	/**@return la valeur de loi_proba_statuts*/
	MonteCarlo<MonteCarlo<QString> > loi_st()const;

	/**@return la valeur de pseudo_statut*/
	bool ps_stat()const;

	/***/
	//QString statut()const;

	/**renvoie l'ensemble des statuts:
	s'il n'y a qu'un statut pas de tirage aleatoire
	sinon il y a tirage aleatoire*/
	QStringList statuts_possibles_non_ok()const;

	/**Donne la description d'un objet.
	@param _langue langue de destination*/
	virtual QString description(int)const;
};
#endif



