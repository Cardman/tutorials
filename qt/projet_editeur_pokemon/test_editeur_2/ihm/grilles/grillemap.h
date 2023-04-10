#ifndef GRILLEMAP_H
#define GRILLEMAP_H
#include <QLabel>
#include "serialisable/base_donnees/hashmap.h"
class TuileMap;
class QMouseEvent;

/**contient le plateau courant, avec un QGridLayout, ce layout contient des TuileGraphique.*/
class GrilleMap: public QLabel{

	Q_OBJECT

	/***/
	HashMap<QPair<int,int>,TuileMap*> tuiles;

	/***/
	int largeur;

	/***/
	QPair<int,int> rectangle_nv_env;

public:

	GrilleMap();

	void ajouter_lignes(int);

	void ajouter_colonnes(int);

	int nb_lignes()const;

	int nb_colonnes()const;

	void init();

	TuileMap *tuile(int,int);

	virtual ~GrilleMap();

	virtual void paintEvent(QPaintEvent *);

	virtual void mouseReleaseEvent(QMouseEvent* _event);

	void table_rase();

	void decaler_vers_droite(int);

	void decaler_vers_bas(int);

signals:

	void selection(const QPair<int,int>&);
};
#endif



