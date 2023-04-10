#ifndef LIGUE_H
#define LIGUE_H
#include "serialisable/coordonnees/coordonnees.h"
#include "base_donnees/cartes/plateauligue.h"

/***/
class Ligue{

	/**Lieu d'accès à la ligue*/
	Coordonnees acces;

	Coordonnees origine;

	QString nom_ligue;

	/***/
	QList<PlateauLigue*> plateaux;

public:

	Ligue(const QStringList&);

	QString nom()const;

	Coordonnees acces_c()const;

	Coordonnees origine_c()const;

	PlateauLigue *plateau(int)const;

	int nb_plateaux()const;

	virtual ~Ligue();
};
#endif


