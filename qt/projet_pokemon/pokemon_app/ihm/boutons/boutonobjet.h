#ifndef BOUTONOBJET_H
#define BOUTONOBJET_H

#include <QLabel>
#include "serialisable/math/taux.h"

class Inventaire;
class Donnees;
class BoutonObjet : public QLabel{

	QImage ico;

	bool ico_actif;

	int numero;

	int sous_action;

	QString nom;

	QString obtenu;

	uchar quantite;

	Taux contenu;

	QColor couleur_texte;

	QColor couleur_fond;

	QColor couleur_rectangle;

	Q_OBJECT
public:

	BoutonObjet(const QString&,int,Inventaire&,Donnees*,int=-1);

	void maj_texte(const QString&);

	void maj_couleur_texte(const QColor&);

	void maj_couleur_fond(const QColor&);

	void maj_couleur_rectangle(const QColor&);

	virtual void mouseReleaseEvent(QMouseEvent *);

	virtual void paintEvent(QPaintEvent *);

signals:

	void clic();

	void clic(const QString&);

	void clic(const QString&,int);
};

#endif // BOUTONOBJET_H
