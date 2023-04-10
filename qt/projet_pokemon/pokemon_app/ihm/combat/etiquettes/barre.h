#ifndef BARRE_H
#define BARRE_H

#include <QLabel>
#include "serialisable/math/taux.h"

class Barre : public QLabel{

	QColor couleur;

	Taux pourcent;

	QString texte;
public:

	Barre(const QColor&);

	void maj_couleur(const QColor&);

	void maj_pourcent(const Taux&);

	void paintEvent(QPaintEvent *);
};

#endif // BARRE_H
