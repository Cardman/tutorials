#ifndef GRILLEVISUELLE_H
#define GRILLEVISUELLE_H
#include <QLabel>
#include "serialisable/base_donnees/hashmap.h"
class TuileGraphique;
/**contient le plateau sélectionné, avec un QGridLayout, ce layout contient des TuileGraphique.*/
class GrilleVisuelle: public QLabel{

	/***/
	HashMap<QPair<int,int>,TuileGraphique*> tuiles;

	/***/
	int largeur;

public:

	GrilleVisuelle();

	void ajouter_lignes(int);

	void ajouter_colonnes(int);

	int nb_lignes()const;

	int nb_colonnes()const;

	void init();

	TuileGraphique *tuile(int,int);

	virtual ~GrilleVisuelle();

	virtual void paintEvent(QPaintEvent *);

	void table_rase();
};
#endif



