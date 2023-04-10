#ifndef GESTIONFOSSILE_H
#define GESTIONFOSSILE_H

#include <QSplitter>
#include "serialisable/base_donnees/hashmap.h"
class Donnees;
class QGroupBox;
class QVBoxLayout;
class QTextEdit;
class Inventaire;

class GestionFossile : public QSplitter{

	QString objet;

	int langue;

	HashMap<QString,uchar> fossiles;

	Donnees *donnees;

	QGroupBox *objets_particuliers;

	QVBoxLayout *objets;

	HashMap<QString,QString> fiche_description;

	QTextEdit *description;

	Q_OBJECT
public:

	GestionFossile(Donnees*);

	void maj_fiche(const HashMap<QString,uchar>&,Inventaire&,int,int,int);
signals:

	void tentative_vivre_fossile(const QString&);

private slots:

	void maj_objet(const QString&);
};

#endif // GESTIONFOSSILE_H
