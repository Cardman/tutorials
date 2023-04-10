#ifndef DRESSEURLIGUE_H
#define DRESSEURLIGUE_H
#include "base_donnees/personnages/dresseur.h"
#include "base_donnees/pokemon/pokemondresse.h"

/***/
class DresseurLigue: public Dresseur{

	Q_OBJECT

	/**equipe des pokemon*/
	QList<PokemonDresse*> equipe;

	/**recompense*/
	int recompense_base;

public:

	DresseurLigue(const QStringList&);

	QList<PokemonDresse*> eq()const;

	int recompense()const;

	virtual ~DresseurLigue();
};
#endif


