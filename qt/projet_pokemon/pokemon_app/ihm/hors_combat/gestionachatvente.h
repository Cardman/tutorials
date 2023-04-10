#ifndef GESTIONACHATVENTE_H
#define GESTIONACHATVENTE_H

#include <QSplitter>
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/utilisateur/inventaire.h"

class ClavierNumerique;
class QVBoxLayout;
class QLabel;
class QScrollArea;
class QTextEdit;
class Utilisateur;
class Donnees;
class Coordonnees;
class Entier;
class BoutonAchatVente;
class GestionAchatVente : public QSplitter{

	Donnees *donnees;

	Inventaire inv;

	int langue;

	uchar type_achat;

	QScrollArea *asc_objets;

	QVBoxLayout *objets;

	HashMap<QString,BoutonAchatVente*> liste_objets;

	HashMap<QPair<QString,int>,BoutonAchatVente*> liste_objets_vente;

	HashMap<uchar,BoutonAchatVente*> liste_capsules;

	QTextEdit *description;

	QLabel *argent;

	Entier valeur_argent;

	QLabel *total_achat;

	ClavierNumerique *clavier;

	QString objet;

	int indice;

	uchar capsule;

	HashMap<QString,uchar> quantites_achat;

	HashMap<QPair<QString,int>,uchar> quantites_vente;

	HashMap<uchar,uchar> quantites_ct;

	void calcul_somme();

	Q_OBJECT
public:

	enum TypeAchatVente{ACHAT_OBJET,VENTE_OBJET,ACHAT_CT,VENTE_CT,RIEN};
	GestionAchatVente(int,Donnees*);

	uchar type_gestion()const;

	void maj_fiche(uchar,const Utilisateur&,const QStringList& =QStringList());

	void maj_fiche_c(uchar,const Utilisateur&,const QList<uchar>& =QList<uchar>());

	HashMap<QString,uchar> val_quantites_achat()const;

	HashMap<QPair<QString,int>,uchar> val_quantites_vente()const;

	HashMap<uchar,uchar> val_quantites_ct()const;

signals:

	void achat();

	void vente();

	void erreur_achat();

	void erreur_vente();

	void fin_gestion();

private slots:

	void valider_achats_vente();

	void valider_achats_vente(const Entier&);

	void finir_gestion();

	void selection_objet(const QString&);

	void selection_objet(const QString&,int);

	void selection_capsule(const QString&);

	void selection_capsule(uchar);
};

#endif // GESTIONVENTE_H
