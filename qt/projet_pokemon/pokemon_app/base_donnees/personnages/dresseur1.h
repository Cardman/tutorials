#ifndef DRESSEUR1_H
#define DRESSEUR1_H
#include "base_donnees/personnages/dresseur.h"
#include "base_donnees/pokemon/pokemondresse.h"

/***/
class Dresseur1: public Dresseur{

	Q_OBJECT

	/**Equipes du dresseur.*/
	QList<QPair<QList<PokemonDresse*>,int> > equipe;

public:

	Dresseur1(const QStringList&);

	int nb_equipes()const;

	QList<PokemonDresse*> eq(int)const;

	int recompense(int)const;

	virtual ~Dresseur1();
};
#endif


