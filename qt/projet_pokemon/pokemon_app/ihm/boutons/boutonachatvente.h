#ifndef BOUTONACHATVENTE_H
#define BOUTONACHATVENTE_H

#include <QLabel>
#include "serialisable/math/taux.h"

class Inventaire;
class Donnees;
class BoutonAchatVente : public QLabel{

	QImage ico;

	bool ico_actif;

	int sous_action;

	QString nom;

	uchar quantite;

	uchar type;

	Taux contenu;

	QColor couleur_texte;

	QColor couleur_fond;

	QColor couleur_rectangle;

	QColor couleur_rectangle_choix;

	bool choisi;

	Q_OBJECT
public:

	BoutonAchatVente();

	void maj_choix(bool);

	void maj_type(uchar);

	void maj_texte(const QString&,int,Inventaire&,Donnees*,int=0,int=0,int=-1);

	void maj_texte(const QString&);

	void maj_couleur_texte(const QColor&);

	void maj_couleur_fond(const QColor&);

	void maj_couleur_rectangle(const QColor&);

	void maj_couleur_rectangle_choix(const QColor&);

	virtual void mouseReleaseEvent(QMouseEvent *);

	virtual void paintEvent(QPaintEvent *);

signals:

	void clic();

	void clic(const QString&);

	void clic(const QString&,int);
};

#endif // BOUTONACHATVENTE_H
