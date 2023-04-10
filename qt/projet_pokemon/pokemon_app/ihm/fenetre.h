#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include "serialisable/partie/partie.h"
#include "serialisable/parametrelogiciel.h"

class QCloseEvent;
class QKeyEvent;
class Donnees;
class Lieu;
class Ligue;
class Plateau;
class PlateauLigue;
class InitDonnees;
class Bouton;
class QLabel;
class QSplitter;
class SceneHorsCombat;
class SceneCombat;
class QProgressBar;
class QScrollArea;
class FicheActions;
class FicheCreature;
class FicheElements;
class FichePartie;
class ChoixHeros;
class Clavier;
class GestionEquipe;
class GestionBoite;
class GestionInventaire;
class GestionAchatVente;
class GestionFossile;
class GestionOption;
class GestionVol;
class Interactions;
class Fenetre : public QMainWindow{

	int langue;

	Partie par;

	ParametreLogiciel parametre;

	SceneCombat *scene_c;

	SceneHorsCombat *scene_hc;

	Interactions *interactions;

	QSplitter *centre;

	QLabel *patience;

	QLabel *menu;

	GestionFossile *gestion_f;

	GestionAchatVente *gestion_a;

	GestionInventaire *gestion_i;

	GestionEquipe *gestion;

	GestionBoite *gestion_b;

	QScrollArea *asc_gestion_o;

	GestionOption *gestion_o;

	QScrollArea *asc_gestion_v;

	GestionVol *gestion_v;

	Coordonnees coords_vol;

	QLabel *choix_heros;

	HashMap<QString,ChoixHeros*> choix_h;

	QString sexe_heros;

	QProgressBar *avancement;

	/**Donnees du jeu immuables*/
	Donnees *donnees;

	Clavier *clavier;

	QScrollArea *asc_cl;

	Lieu *lieu;

	Ligue *ligue;

	Plateau *plateau;

	PlateauLigue *plateau_ligue;

	/**Permet d'initialiser les donnees*/
	InitDonnees *initialisateur;

	Bouton *bouton;

	bool debut_jeu;

	bool en_deplacement;

	QScrollArea *asc_fiche_partie;

	FichePartie *fiche_partie;
	//QSplitter *combat_infos;

	//FicheActions *actions_combat;

	//FicheCreature *fiche_creature_combat;

	//FicheElements *fiche_elements_combat;

Q_OBJECT
public:
	Fenetre();

	/***/
	void init();

	void deplacement(QKeyEvent *);

	virtual void keyPressEvent(QKeyEvent *);

	virtual void keyReleaseEvent(QKeyEvent *);

	virtual void closeEvent(QCloseEvent *);

	~Fenetre();
signals:

private slots:
	void finir_initialisation();

	void maj_attaque_combat_sauvage(const QString&);

	void maj_action(const Combattant&,const QString&);

	void maj_fiche(const Combattant&);

	void maj_attaque_combat(const Combattant&,const Combattant&,const QString&);

	void maj_remplacant(const Combattant&,const Combattant&);

	void tentative_fuite();

	void tentative_capture(const QString&);

	void tour_combat();

	void apprendre_attaque(int);

	void traiter_evo();

	void traiter_non_evo();

	void nouveau_jeu();

	void redessiner_ihm(uchar);

	void maj_texte_clavier(const QString&);

	void maj_sexe_heros(const QString&);

	void maj_position(const QPair<int,int>&);

	void retrait_objet(uchar);

	void maj_objet(const QPair<int,int>&);

	void maj_pension(const QPair<int,int>&);

	void tentative_apprendre_move_tutor(const QString&,uchar,int);

	void apprendre_move_tutor(const QString&,uchar,int);

	void gerer_inventaire();

	void attacher();

	void attacher(uchar);

	void utiliser(uchar);

	void boost(uchar);

	void soin(uchar);

	void soin_baie(uchar);

	void apprendre(uchar);

	void evoluer(const QString&,uchar);

	void finir_gerer_inventaire();

	void gerer_equipe();

	void finir_gestion_equipe();

	void interaction(uchar,uchar,const QString&);

	void echanger_pokemons_boite(const QPair<int,int>&,const QPair<int,int>&);

	void echanger_objets_boite(const QPair<int,int>&,const QPair<int,int>&);

	void ranger_objets_boite(const QPair<int,int>&);

	void deposer_pokemon(uchar,const QPair<uchar,uchar>&);

	void retrait_pokemon(const QPair<uchar,uchar>&);

	void relacher_pokemon(const QPair<uchar,uchar>&);

	void finir_gestion_boite();

	void voler();

	void achat();

	void vente();

	void erreur_achat();

	void erreur_vente();

	void finir_gestion_achat_vente();

	void vivre_fossile(const QString&);

	void joueur();

	void options();

	void maj_diff(const Difficulte&);

	void maj_coords_vol(const Coordonnees&);
};

#endif // FENETRE_H
