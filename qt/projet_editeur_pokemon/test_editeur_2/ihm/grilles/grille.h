#ifndef GRILLE_H
#define GRILLE_H
#include <QLabel>
#include "serialisable/base_donnees/hashmap.h"
class TuileGraphique;
class QMouseEvent;
class Plateau;
/**contient le plateau courant, avec un QGridLayout, ce layout contient des TuileGraphique.*/
class Grille: public QLabel{

	Q_OBJECT

	/***/
	HashMap<QPair<int,int>,TuileGraphique*> tuiles;

	/***/
	int largeur;

	/***/
	QPair<QPair<int,int>,QPair<int,int> > rectangle_nv_env;

public:

	Grille();

	void ajouter_lignes(int);

	void ajouter_colonnes(int);

	int nb_lignes()const;

	int nb_colonnes()const;

	void init();

	TuileGraphique *tuile(int,int);

	virtual ~Grille();

	virtual void paintEvent(QPaintEvent *);

	virtual void mouseReleaseEvent(QMouseEvent* _event);

	void affecter_rectangle_nv_env(const QPair<QPair<int,int>,QPair<int,int> >&);

	void table_rase();

	void decaler_vers_droite(int);

	void decaler_vers_bas(int);

/*private slots:

	void maj_coords(const QPair<QPair<int,int>,QPair<int,int> >&);*/

signals:

	void selection(const QPair<QPair<int,int>,QPair<int,int> >&);

/*public slots:

	void maj_dims_env(const QPair<int,int>&);

	void maj_dims_env();*/
};
#endif



