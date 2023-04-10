#ifndef GESTIONINVENTAIRE_H
#define GESTIONINVENTAIRE_H

#include <QSplitter>
#include "serialisable/utilisateur/inventaire.h"

class QGridLayout;
class QVBoxLayout;
class QTextEdit;
class QLabel;
class QGroupBox;
class GestionInventaire : public QSplitter{

	/**Par defaut: SOIN*/
	uchar type_objet;

	QString objet_selectionne;

	int quantite_selectionnee;

	QString objet;

	int langue;

	Inventaire inventaire;

	Donnees *donnees;

	/**contient les actions ATTACHER, APPRENDRE, UTILISER (BAIE,BOOST,PIERRE_EVO,REPOUSSE,SOIN), ANNULER, FINIR*/
	QVBoxLayout *actions;

	QGroupBox *objets_particuliers;

	QVBoxLayout *objets;

	HashMap<QPair<QString,int>,uchar> liste_objets_presents;

	QLabel *et_objet;

	HashMap<QString,QString> fiche_description;

	QTextEdit *description;

	Q_OBJECT
public:

	enum TypeObjet{BAIE,BALL,BOOST,FOSSILE,PLAQUE,OBJET_ATTACHABLE,OBJET_EVO,PIERRE_EVO,REPOUSSE,REVENTE,SOIN,CT,CS,RIEN};
	GestionInventaire(Donnees*);

	bool gestion_en_cours()const;

	QPair<QString,int> obj_select()const;

	void maj_fiche(const Inventaire&,int,uchar=GestionInventaire::SOIN);

signals:

	void attacher_obj();

	void utiliser(uchar);

	void apprendre(uchar);

	void gestion_finie();

private slots:

	void maj_action(uchar);

	void maj_objet(const QString&);

	void maj_objet(const QString&,int);

	void attacher();

	void utiliser();

	void annuler();

	void finir();
	//void apprendre();
};

#endif // GESTIONINVENTAIRE_H
