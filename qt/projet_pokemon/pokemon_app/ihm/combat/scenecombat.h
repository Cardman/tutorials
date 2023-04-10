#ifndef SCENECOMBAT_H
#define SCENECOMBAT_H

#include <QSplitter>
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/combat/combattant.h"

class CreatureCombat;
class ElementsCombat;
class Difficulte;
class FicheActions;
class FicheCreature;
class FicheElements;
class EtiquetteCreatCombat;
class EtiquetteAttaque;
class Donnees;
class QLabel;
class QGridLayout;
class QTextEdit;
class QVBoxLayout;
class QGroupBox;
class QScrollArea;
class Inventaire;
class SceneCombat : public QSplitter{

	QLabel *type_combat;

	QLabel *type_environnement;

	QGridLayout *coeur_combat;

	HashMap<Combattant,EtiquetteCreatCombat*> fronts;

	QTextEdit *commentaire_tour;

	QScrollArea *asc_actions_combat_sauvage;

	QGroupBox *groupe_actions_combat_sauvage;

	QVBoxLayout *actions_combat_sauvage;

	HashMap<QString,EtiquetteAttaque*> actions_sauvage;

	QGroupBox *groupe_pokemon_utilisateur;

	QVBoxLayout *pokemon_utilisateur;

	HashMap<Combattant,EtiquetteCreatCombat*> creat_ut;

	QGroupBox *groupe_pokemon_adverse;

	QVBoxLayout *pokemon_adverse;

	HashMap<Combattant,EtiquetteCreatCombat*> creat_adv;

	QVBoxLayout *actions_flux;

	QTextEdit *actions_choisies_utilisateur;

	QScrollArea *asc_erreur;

	QTextEdit *erreur_utilisateur;

	QGroupBox *resultats;

	QLabel *resultats_bis;

	QScrollArea *conteneur_actions_combat;

	FicheActions *actions_combat;

	QScrollArea *conteneur_creature_combat;

	FicheCreature *fiche_creature_combat;

	QScrollArea *conteneur_elements_combat;

	FicheElements *fiche_elements_combat;

	QScrollArea *conteneur_evo;

	QGroupBox *evolution;

	Q_OBJECT
public:
	SceneCombat(Donnees*);

	void maj_fiche(const Combattant&,ElementsCombat&,Inventaire&,const Difficulte&,bool,bool,Donnees*);

	void afficher_attaques_objets(bool);

	void afficher_actions_sauvage(bool);

	void afficher_evolutions(bool);

	void maj_fiche(const Combattant&,ElementsCombat&,bool,bool,Donnees*);

	void raz_scene_combat();

	void maj_attaque_combat(const Combattant&,const Combattant&,ElementsCombat&,const QString&,Donnees*);

	void maj_erreur(const QString&);

	void maj_commentaire(const QString&);

	void ajout_commentaire(const QString&);

signals:

	void change_fiche_creature(const Combattant&);

	void clic_attaque_combat_sauvage(const QString&);

	void clic_action(const Combattant&,const QString&);

	void clic_attaque(int);

	void clic_attaque(const Combattant&,const Combattant&,const QString&);

	//void clic_attaque_apprendre(const Combattant&,const QString&);

	void clic_ball(const QString&);

	void clic_remplacant(const Combattant&,const Combattant&);

	void evoluer();

	void ne_pas_evoluer();

	void clic_fuite();

	void valider();

public slots:

	void ne_pas_capturer();

	void maj_ball(const QString&);

	void maj_attaque_combat_sauvage(const QString&);

	void maj_action(const Combattant&,const QString&);

	//void maj_attaque(const Combattant&,const QString&);

	void maj_attaque(int);

	void maj_remplacant(const Combattant&,const Combattant&);

	void maj_fiche(const Combattant&);

	void valider_actions();

	void faire_evoluer();

	void ne_pas_faire_evoluer();

	void tentative_fuite();

	void maj_attaque_combat(const Combattant&,const Combattant&,const QString&);
};

#endif // SCENECOMBAT_H
