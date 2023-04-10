#ifndef FICHECREATURE_H
#define FICHECREATURE_H

#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/math/taux.h"
#include <QLabel>
class Combattant;
class CreatureCombat;
class ElementsCombat;
class Donnees;
class QGridLayout;
class QVBoxLayout;
class QGroupBox;
class EtiquetteCombattant;
class EtiquetteAttaque;
class FicheCreature : public QLabel{

	/**Image macroscopique associée à la forme actuelle pokémon sur le combat*/
	QLabel *image_pk;

	/**Types actuels du pokémon*/
	QLabel *types_pk;

	/**Pseudo du pokemon*/
	QLabel *pseudo;

	/**Capacité actuelle*/
	QLabel *capacite_act;

	/**Capacité de base avant le combat*/
	QLabel *capacite;

	/**Bonheur du pokemon*/
	QLabel *bonheur;

	/**Préparation d'une attaque du pokemon sur un tour comme VOL,TUNNEL,...*/
	QLabel *prepa_tour;

	/**Rechargement nécessaire après utilisation d'une attaque du pokemon sur un tour comme ULTRALASER,...*/
	QLabel *nec_recharg;

	/**Noms des statistiques*/
	QStringList noms_statistiques;

	/**Statistiques du pokemon (y compris PV,PRECISION,ESQUIVE,COUP CRITIQUE)*/
	QGridLayout *statistiques;

	/**Noms des attaques ayant des effets sur plusieurs tours subi ou non*/
	QStringList noms_attaques;

	/**Attaques ayant des effets sur plusieurs tours subi ou non*/
	QGridLayout *attaques;

	/**Pv du clone*/
	QLabel *clone_pk;

	/**Vitesse globale du pokémon*/
	QLabel *vitesse;

	/**Attaque remplaçant éventuellement copie avec les points de pouvoir restants*/
	QLabel *copie;

	/**Nombre de tours depuis le début de la confusion subie par le pokémon, nombre de tours minimal, nombre de tours maximal*/
	QLabel *confusion;

	/**Nombre de tours depuis le début de l'utilisation de patience par le pokémon, nombre de tours minimal, nombre de tours maximal et dégâts encaissés*/
	QLabel *patience;

	/**Coefficient de puissance de roulade et de ball glace*/
	QLabel *coefficient_roul_ball_glace;

	/**Nombre de succès des attaques ABRI,DETECTION,TENACITE,GARDE_LARGE et PREVENTION lancées par le pokémon*/
	QLabel *succes_abris;

	/**Noms des attaques dont le nombre d'utilisations est à retenir*/
	QStringList noms_attaques_lancees;

	/**Attaques dont le nombre d'utilisations est à retenir*/
	QGridLayout *attaques_lancees;

	HashMap<QString,EtiquetteAttaque*> liste_attaques;

	/**Noms des types*/
	QStringList noms_types;

	/**Coefficents des types des attaques subies ou lancées et immunisation au type*/
	QGridLayout *coeff_types;

	/**Nombre de tours du sommeil ne provenant pas de l'attaque REPOS*/
	QLabel *sommeil_non_repos;

	/**Nombre de tours depuis la soumission au poison grave*/
	QLabel *poison_grave;

	/**Combattants actuellement presents dans les equipes*/
	QVBoxLayout *combattants;

	HashMap<Combattant,EtiquetteCombattant*> liste_combattants;

	/**Noms des attaques mettant en jeu une relation pendant plusieurs tours*/
	QStringList noms_attaques_rel_combattants;

	/**Attaques mettant en jeu une relation pendant plusieurs tours*/
	QGridLayout *attaques_rel_combattants;

	HashMap<QPair<QString,Combattant>,QPair<QString,QPair<bool,uchar> > > attaques_sur_combat_att;

	/**non subi*/
	HashMap<QPair<Combattant,QString>,QPair<bool,uchar> > attaques_piegeantes;

	HashMap<QString,HashMap<Combattant,bool> > relations_comb;

	/**Table des types dependant de deux pokemons (le lanceur et la cible)*/
	QGridLayout *table_types;

	HashMap<Combattant,HashMap<QPair<QString,QString>,Taux> > h_table_types;

	/**Attaques sous l'effet de POSSESSIF que les autres n'ont pas le droit d'utiliser*/
	QLabel *attaques_possedees;

	/**non subi*/
	HashMap<Combattant,QStringList> attaques_possessif;

	QGroupBox *groupe_cibles;

	/**Cibles choisies et attaque si le combat est contre un pokemon sauvage*/
	QGridLayout *cibles;

	/**action choisie par le pokemon*/
	QLabel *action_choisie;

	/**attaque choisie par le pokemon*/
	QLabel *attaque_choisie;

	/**pokemon remplaçant le pokemon actuel*/
	QLabel *envoye;

	/**derniere attaque lancee par le pokemon*/
	QLabel *der_att_lancee;

	/**derniere attaque reussie par le pokemon*/
	QLabel *der_att_reussie;

	/**dernier objet utilise par le pokemon*/
	QLabel *der_objet_utilise;

	Q_OBJECT
public:
	FicheCreature(Donnees*);

	void maj_fiche(const Combattant&,const CreatureCombat&,const ElementsCombat&,Donnees*);

	virtual ~FicheCreature();
signals:

	void clic_attaque(const QString&);

private slots:
	void maj_fiche(const Combattant&);

	void attaque_cliquee(const QString&);
};

#endif // FICHECREATURE_H
