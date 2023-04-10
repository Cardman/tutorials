#ifndef CLAVIERNUMERIQUE_H
#define CLAVIERNUMERIQUE_H

#include <QLabel>
#include "serialisable/math/entier.h"

class Bouton;
class Taux;
class Entier;
class Donnees;
class ClavierNumerique : public QLabel{

	QString texte;

	QRegExp exp_taux;

	QRegExp exp_entier;

	bool entier;

	Entier valeur;

	Bouton *champ;

	Q_OBJECT
public:

	ClavierNumerique(bool,Donnees*);

	QString texte_ecrit()const;

	void maj_texte(const QString&);

signals:

	void valider(const Taux&);

	void valider(const Entier&);
public slots:

	void vider_champ();

private slots:

	void incrementer();

	void decrementer();

	void maj_valider();

	/**Insertion*/
	void maj_champ(const QString&);

};

#endif // CLAVIERNUMERIQUE_H
