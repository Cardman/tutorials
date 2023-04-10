#ifndef FICHEACTIONS_H
#define FICHEACTIONS_H

#include <QLabel>
#include "serialisable/combat/creaturecombat.h"
#include "ihm/combat/etiquettes/etiquetteattaque.h"
class ElementsCombat;
class Difficulte;
class Donnees;
class QVBoxLayout;
class QHBoxLayout;
class QScrollArea;
class EtiquetteAttaque;
class EtiquetteCombattant;
class FicheActions : public QLabel{

	Combattant combattant;

	CreatureCombat creature;

	bool mettre_a_jour_cr;

	QVBoxLayout *actions_possibles;

	EtiquetteAttaque *attaquer;

	EtiquetteAttaque *switcher;

	EtiquetteAttaque *soin;

	EtiquetteAttaque *ne_rien_faire;

	HashMap<QString,EtiquetteAttaque*> liste_actions;
	//bool mettre_a_jour_elt;

	HashMap<Combattant,CreatureCombat> autres_creatures;

	HashMap<Combattant,QString> noms_combattants;

	QString attaque_selectionnee;

	QString objet_selectionnee;

	QVBoxLayout *attaques_possibles;

	HashMap<QString,EtiquetteAttaque*> liste_attaques;

	QVBoxLayout *attaques_act_possibles;

	HashMap<QString,EtiquetteAttaque*> liste_act_attaques;

	QScrollArea *conteneur_objets;

	QVBoxLayout *objets_possibles;

	HashMap<QString,EtiquetteAttaque*> liste_objets;

	HashMap<QString,QList<QPair<uchar,Taux> > > objets;

	QVBoxLayout *cibles_possibles;

	HashMap<Combattant,EtiquetteCombattant*> liste_cibles;

	QVBoxLayout *remplacants_possibles;

	HashMap<Combattant,EtiquetteCombattant*> liste_remplacants;

	HashMap<Combattant,QPair<uchar,uchar> > positions_combattants;

	QList<Combattant> ordre_de_jeu;

	bool apprende_attaque;

	bool remplacer_fin_tour;

	Q_OBJECT
public:
	FicheActions();

	void maj_fiche(const Combattant&,ElementsCombat&,bool,bool,Donnees*);

	void maj_ordre_jeu(const QList<Combattant>&);

signals:

	void clic_action(const Combattant&,const QString&);

	void clic_attaque(const Combattant&,const Combattant&,const QString&);

	/**Remplacement d'une attaque*/
	void clic_attaque(int);

	void changer_remplacant(const Combattant&,const Combattant&);

	void clic_objet(const Combattant&,const QString&);

public slots:

	void maj_fiche_fct_action(const QString&);

	void maj_attaque_a_lancer(const QString&);

	void maj_attaque_a_apprendre(const QString&);

	void maj_cible(const Combattant&);

	void maj_remplacant(const Combattant&);

	void maj_objet(const QString&);

	void fin_combat_ou_ajout_cr();
};

#endif // FICHEACTIONS_H
