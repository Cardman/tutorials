#ifndef FICHEPARTIE_H
#define FICHEPARTIE_H

#include <QLabel>
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/math/taux.h"
#include "serialisable/coordonnees/coordonnees.h"
#include "serialisable/pokemon/pokemonutilisateur.h"

class Partie;
class Donnees;
class QGroupBox;
class QVBoxLayout;
class FichePartie : public QLabel{

	QLabel *et_pseudo;

	QString pseudo;

	QLabel *et_argent;

	Entier argent;

	QGroupBox *groupe_pokemon;

	QVBoxLayout *pokemons;

	HashMap<QString,bool> pokemon_attrapes;

	QLabel *et_ligue;

	bool ligue;

	int ligues_deja_battues;

	/**nombre de dresseurs de la ligue battus (remis a zero une fois la ligue battue)*/
	uchar stade_ligue;

	QGroupBox *groupe_pokemon_pens;

	QVBoxLayout *pokemons_pens;

	/***/
	HashMap<Coordonnees,QPair<QPair<PokemonUtilisateur,PokemonUtilisateur>,int> > pokemon_pension;

	QLabel *et_repousse;

	/***/
	bool repousse_actif;

	/***/
	int pas_restants_repousse;

	//TODO QLabel *et_apparition;

	HashMap<QString,uint> indice_periode_peche;

	uint indice_periode;

	uint indice_pas;

public:

	FichePartie(Donnees*);

	void maj_fiche(const Partie&,Donnees*);
};

#endif // FICHEPARTIE_H
