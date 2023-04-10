#ifndef CURSEUR_H
#define CURSEUR_H

#include <QLabel>
#include "serialisable/math/entier.h"

class Curseur : public QLabel{

	int orientation;

	int taille;

	int mini;

	int valeur;

	int maxi;

	void traiter_event(QMouseEvent*);

	Q_OBJECT

public:

	Curseur(int=Qt::Horizontal,int=400);

	void maj_intervalle(int,int);

	void maj_valeur(int);

	void mouseReleaseEvent(QMouseEvent*);

	void mouseMoveEvent(QMouseEvent*);

	void paintEvent(QPaintEvent *);

signals:

	void nouvelle_valeur(int);
};

#endif // CURSEUR_H
