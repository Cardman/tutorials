#ifndef TUILEGRAPHIQUE_H
#define TUILEGRAPHIQUE_H
//#include <QLabel>
#include <QImage>
#include <QPair>
#include "base_donnees/import.h"

/***/
class TuileGraphique{

	/**image représentant la tuile réelle.*/
	QImage image;

	/**image représentant un éventuel ostacle si le booléen est vrai*/
	QPair<QImage,bool> obstacle;

	/***/
	QPair<QImage,bool> objet;

	/***/
	QPair<QImage,bool> lien_img;

	/***/
	QPair<QImage,QPair<int,int> > personnage;

	/**coordonnées de la tuile par rapport à l'environnement qui la contient mais pas besoin de coordonnées de l'environnement par rapport au plateau qui le contient car ces coordonnées sont déductibles par les indices de la tuile.*/
	QPair<int,int> coordonnees;

	bool condition_ligue;

public:

	/***/
	TuileGraphique(const QPair<int,int>&,const QImage& _img=Import::_tuile_invalide_);

	/***/
	void maj_image(const QImage&);

	/***/
	QImage imag()const;

	/***/
	void maj_obj(const QPair<QImage,bool>&);

	/***/
	QPair<QImage,bool> obj()const;

	void maj_cond_ligue(bool);

	bool cond_ligue()const;

	/***/
	void maj_lien(const QPair<QImage,bool>&);

	/***/
	QPair<QImage,bool> lien()const;

	/***/
	void maj_obst(const QPair<QImage,bool>&);

	/***/
	QPair<QImage,bool> obst()const;

	void maj_perso(const QPair<QImage,QPair<int,int> >&);

	QPair<QImage,QPair<int,int> > perso()const;

	/***/
	void maj_coords(const QPair<int,int>&);

	/***/
	QPair<int,int> coords()const;

	/***/
	void affecter(TuileGraphique*,const QPair<int,int>&);

	/***/
	void affecter(TuileGraphique*);

	/***/
	void init();

	/***/
	void reinit();

	/**Emet le signal clic(const QPair<QPair<int,int>,QPair<int,int>>&)
@param _event Evénement concernant le clic de souris.*/
	//virtual void mouseReleaseEvent(QMouseEvent*);

	/**
@param _event Evénement ayant lieu lors du changement d'image représentant la tuile.*/
	//virtual void paintEvent(QPaintEvent*);
//signals:

	/**Signal émis lors d'un clic sur la TuileGraphique.
@param _coordonnees_plateau Paramètre fournissant les coordonnées de la tuile par rapport au plateau.
Les deux premiers entiers sont les coordonnées de l'environnement par rapport au plateau. Les deux autres sont les coordonnées de la tuile par rapport à l'environnement.*/
	//void clic(const QPair<QPair<int,int>,QPair<int,int> >&);
};

#endif



