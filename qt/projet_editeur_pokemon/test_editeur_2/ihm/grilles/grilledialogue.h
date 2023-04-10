#ifndef GRILLEDIALOGUE_H
#define GRILLEDIALOGUE_H
#include <QLabel>
#include "serialisable/base_donnees/hashmap.h"
class TuileGraphique;
class QMouseEvent;
class Plateau;
/**contient le plateau courant, avec un QGridLayout, ce layout contient des TuileGraphique.*/
class GrilleDialogue: public QLabel{

	Q_OBJECT

	/**coordonnées sélectionnées.*/
	QPair<QPair<int,int>,QPair<int,int> > coordonnees;

	/***/
	HashMap<QPair<int,int>,TuileGraphique*> tuiles;

	HashMap<QPair<int,int>,int> liens_lieux;

	/***/
	int largeur;

public:

	enum LienLieux{RIEN,GAUCHE,DROITE,HAUT,BAS};
	GrilleDialogue();

	void ajouter_lignes(int);

	void ajouter_colonnes(int);

	int nb_lignes()const;

	int nb_colonnes()const;

	void init();

	TuileGraphique *tuile(int,int);

	virtual ~GrilleDialogue();

	virtual void paintEvent(QPaintEvent *);

	virtual void mouseReleaseEvent(QMouseEvent* _event);

	void table_rase();

	void reinit_liens();

	void maj_dir_lieux(int,int,int);

	void maj_liens_plateau_ligue(QPair<QPair<int,int>,QPair<int,int> >*,QPair<QPair<int,int>,QPair<int,int> >*);

	void maj_liens_plateau_ligue(const QPair<QPair<int,int>,QPair<int,int> >&,QPair<QPair<int,int>,QPair<int,int> >*);

	void maj_liens_plateau_ligue(QPair<QPair<int,int>,QPair<int,int> >*,const QPair<QPair<int,int>,QPair<int,int> >&);

	void maj_liens_plateau_ligue(const QPair<QPair<int,int>,QPair<int,int> >&,const QPair<QPair<int,int>,QPair<int,int> >&);

signals:

	void selection(const QPair<QPair<int,int>,QPair<int,int> >&);

};
#endif



