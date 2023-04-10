#ifndef CHAMPION_H
#define CHAMPION_H
#include "base_donnees/personnages/dresseur1.h"

/***/
class Champion: public Dresseur1{

	Q_OBJECT

	/**badge permettant d'utiliser une CS et d'avancer vers la ligue.*/
	QString badge;

	/**capsule technique donnee par le champion d'arene*/
	uchar ct;

	/**Si cette variable ne vaut pas 0, alors cette variable vaut le numero de la capsule secrete autorisee*/
	uchar cs;

	static QStringList sous_attributs(const QStringList&);

public:

	Champion(const QStringList&);

	uchar val_cs()const;

	uchar val_ct()const;
};
#endif


