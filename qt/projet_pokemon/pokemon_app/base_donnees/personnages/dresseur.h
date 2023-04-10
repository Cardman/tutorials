#ifndef DRESSEUR_H
#define DRESSEUR_H
#include "base_donnees/personnages/personnage.h"
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/math/taux.h"

/***/
class Dresseur: public Personnage{

	Q_OBJECT

	/**Nom de l'image a utiliser pour afficher la face du dresseur*/
	QString nom_image;

	/**message de fin de combat*/
	QString message_fin_combat;

	/**message de début de combat*/
	QString message_debut_combat;

	/**1 si combat simple (1 vs 1, a la fois), la plupart des cas
2 si combat double (2 vs 2, a la fois),
...
*/

	uchar multiplicite_combat;

	/**le rival (sauf à la ligue) et les personnages de la Team Rocket disparaissent après le combat.*/
	//bool disparait_apres_combat;

	/**gain d'argent a la fin du combat.*/
	//int recompense_base;

	/***/
	//HashMap<QString,QList<QPair<uchar,Taux> > > inventaire_soin;

public:

	Dresseur(const QStringList&);

	uchar mult_comb()const;
};
#endif


