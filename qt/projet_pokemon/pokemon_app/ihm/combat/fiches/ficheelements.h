#ifndef FICHEELEMENTS_H
#define FICHEELEMENTS_H

#include <QLabel>
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/combat/combattant.h"
#include "serialisable/difficulte/difficulte.h"
class CreatureCombat;
class ElementsCombat;
class Donnees;
class QGridLayout;
class QVBoxLayout;
class EtiquetteEquipe;
class EtiquettePosition;
class EtiquetteCombattant;
class FicheElements : public QLabel{

	/**Variation d'argent*/
	QLabel *argent;

	/**Nombre total de tentative de fuite (combat contre un pokemon sauvage)*/
	QLabel *fuite;

	/**Multiplicite du combat*/
	QLabel *multiplicite;

	/**Nom du climat*/
	QLabel *nom_climat;

	/**Nombre de tours du climat (Indefini si eternel)*/
	QLabel *nombre_tours_climat;

	/**Nombre de tours minimal du climat*/
	QLabel *nombre_tours_min_climat;

	/**Nombre de tours maximal du climat*/
	QLabel *nombre_tours_max_climat;

	/**Activite du climat*/
	QLabel *climat_actif;

	/**Attaques globales*/
	QStringList attaques_globales;

	/**Effets globaux*/
	QGridLayout *effets_globaux;

	/***/
	uchar equipe_ut;

	/***/
	EtiquetteEquipe *bouton_ut;

	/***/
	EtiquetteEquipe *bouton_adv;

	/**Attaques par equipe*/
	QStringList attaques_equipes;

	/**Effets des attaques par equipe*/
	QGridLayout *effets_attaques_equipes;

	HashMap<uchar,HashMap<QString,QPair<uchar,bool> > > nb_tour_attaque_equipe;

	QLabel *vengeance_effet;

	HashMap<uchar,QPair<bool,bool> > vengeance_actif;

	/**Attaques par equipe*/
	QStringList lancers_attaques_equipes;

	/**Nombre de lancers des attaques par equipe*/
	QGridLayout *nb_lancers_attaques_equipes;

	HashMap<QPair<QString,uchar>,uchar> nb_utilisation_attaques;

	/**Attaques voeu, prescience, carnareket*/
	QVBoxLayout *positions;

	HashMap<QPair<int,int>,EtiquettePosition*> liste_positions;

	/**Tableau des effets de l'attaque voeu*/
	QGridLayout *voeu_attaque;

	/***/
	HashMap<QPair<uchar,uchar>,QPair<uchar,QPair<bool,bool> > > voeu_gl;

	/**Tableau des effets des attaques prescience, carnareket*/
	QGridLayout *presc_carnar_attaque;

	/***/
	HashMap<QPair<QString,QPair<uchar,uchar> >,QPair<QPair<Taux,uchar>,QPair<uchar,uchar> > > attaques_prepa_tours;

	/**Boutons portant sur les adversaires combattus par les pokemons de l'utilisateur*/
	QVBoxLayout *boutons_adv;

	HashMap<Combattant,EtiquetteCombattant*> liste_combattants;

	/**Boutons portant sur les pokemons de l'utilisateur ayant combattu le pokémon adverse selectionné*/
	QVBoxLayout *boutons_ut;

	HashMap<uchar,QList<uchar> > combattants_adverses;

	HashMap<Combattant,QPair<uchar,uchar> > positions_places;

	HashMap<Combattant,QString> noms_combattants;

	HashMap<Combattant,Taux> pv_restants;

	int arriere;

	Difficulte difficulte;

	Q_OBJECT
public:
	FicheElements(Donnees*);

	void maj_fiche(const ElementsCombat&,const Difficulte&,Donnees*);

signals:

private slots:

	void maj_fiche(uchar);

	void maj_fiche(const Combattant&);

	void maj_fiche(const QPair<int,int>&);
};

#endif // FICHEELEMENTS_H
