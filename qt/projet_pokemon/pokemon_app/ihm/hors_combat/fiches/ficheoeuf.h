#ifndef FICHEOEUF_H
#define FICHEOEUF_H

#include <QLabel>

class Barre;
class QLabel;
class OeufPokemon;
class Donnees;
class FicheOeuf : public QLabel{

	QLabel *nom_futur_pokemon;

	//QLabel *nom_parent_ayant_pondu_oeuf;

	Barre *taux_pas_restants;

	QLabel *pas_restants;

public:
	FicheOeuf();

	void maj_fiche(const OeufPokemon&,Donnees*);
};

#endif // FICHEOEUF_H
