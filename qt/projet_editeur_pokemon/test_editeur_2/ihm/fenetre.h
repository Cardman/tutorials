#ifndef FENETRE_H
#define FENETRE_H
#include "serialisable/donnees.h"
#include <QMainWindow>
class Menu;
class Action;
class QLabel;
class Grille;
class PanneauEditerEnv;
class PanneauDresseurLigue;
class QScrollArea;
class QProgressBar;
class InitBDD;
enum ChoixEnv{NOUVEAU,DEPLACER,SUPPRIMER,SELECTION};
/***/
class Fenetre: public QMainWindow{
	Q_OBJECT

	QProgressBar *progression;

	InitBDD *init_bdd_th;

	int ind_lieu_tmp;

	/***/
	int langue;

	/***/
	Donnees donnees;

	/***/
	Donnees anciennes_donnees;

	/***/
	ChoixEnv choix_env;

	/***/
	QPair<QPair<int,int>,QPair<int,int> > coordonnees_act;

	/***/
	QPair<QPair<int,int>,QPair<int,int> > rectangle_nv_env;

	/***/
	int ind_lieu;

	/***/
	int ind_plateau;

	/***/
	Grille *grille;

	QScrollArea *ascenseur_panneau;

	PanneauEditerEnv *panneau_editeur_env;

	PanneauDresseurLigue *panneau_editeur_ligue;

	/**chemin absolu*/
	QString rep_travail;

	/**chemin absolu*/
	QString rep_export;

	//QString nom_fichier_export;

	/**chemin absolu*/
	QString nom_fichier_flux;

	//bool chargement_fait;

	//bool chargement_selection_faits;
	/***/
	//void maj_langue(int);

	/***/
	QLabel *et_stat;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	void maj_plateau();

	void maj_plateau_ligue();

public:

	/***/
	static Lieu *_lieu_precedent_;

	/***/
	static Lieu *_lieu_en_cours_;

	/***/
	static Ligue *_ligue_en_cours_;

	/***/
	static Plateau *_plateau_en_cours_;

	static PlateauLigue *_plateau_ligue_en_cours_;
	/**
	static HashMap<QString,QImage> _tuiles_importees_;

	static HashMap<QString,QImage> _dresseurs_macros_;

	static HashMap<QString,QImage> _dresseurs_micros_;

	static HashMap<QString,QImage> _arbres_;

	static HashMap<QString,QImage> _rochers_destructibles_;

	static HashMap<QString,QImage> _rochers_amovibles_;

	static HashMap<QString,QImage> _tourbillons_;*/

	/**Construit la fenêtre au début du lancement du programme.*/
	Fenetre(int);

	/***/
	Donnees *adr_donnees();

	void init_bdd();

	/***/
	virtual void closeEvent(QCloseEvent*);

	/**Destructeur permettant de libérer la mémoire allouée à des éléments statiques.*/
	virtual ~Fenetre();

public slots:

	void finir_bdd();

	void selection_coords(const QPair<QPair<int,int>,QPair<int,int> >&);

	void maj_image_tuile(const QImage&);

	void maj_dims_env(const QPair<int,int>&);

	void maj_dims_env2();

	/***/
	void nouvelles_donnees();

	/***/
	Donnees donnees_actuelles()const;

	/***/
	bool nouveau_lieu();

	/***/
	void nouveau_lieu_edite();

	void maj_nom_type_lieu();

	/**tente de valider les actions de l'utilisateur*/
	//void valider_tuile();

	/**Methode permettant de valider un environnement.*/
	//void valider_environnement();

	/**Tente d'insérer un plateau dans un lieu.
Ce slot est connecté à une action sur un bouton de menu.*/
	void inserer_plateau();

	/***/
	void selection_lieu();

	/***/
	void suppression_lieu();

	/***/
	void select_plateau();

	/***/
	void suppression_plateau();

	/***/
	void ajouter_ligne_ht_plateau();

	/***/
	void ajouter_ligne_bas_plateau();

	/***/
	void ajouter_col_gauche_plateau();

	/***/
	void ajouter_col_droite_plateau();

	/***/
	void ajouter_lignes_ht_plateau();

	/***/
	void ajouter_lignes_bas_plateau();

	/***/
	void ajouter_cols_gauche_plateau();

	/***/
	void ajouter_cols_droite_plateau();

	/***/
	void nv_env();

	/***/
	void deplacer_env();

	/***/
	void selection_env();

	/***/
	void supprimer_env();

	/***/
	//void ajout_ligne_ht_env();

	/***/
	//void ajout_ligne_bas_env();

	/***/
	//void ajout_ligne_en_dessous_env();

	/***/
	//void ajout_lignes_en_dessous_env();

	/***/
	//void ajout_lignes_ht_env();

	/***/
	//void ajout_lignes_bas_env();

	/***/
	void modifier_hauteur_env();

	/***/
	void insert_ligne_env();

	/***/
	void insert_supprimer_lignes_env();

	/***/
	void supprimer_ligne_env();

	/***/
	void modifier_largeur_env();

	/***/
	void insert_colonne_env();

	/***/
	void insert_supprimer_colonnes_env();

	/***/
	void supprimer_colonne_env();

	/***/
	void nouvelle_ligue();

	/***/
	void selection_ligue();

	/***/
	void suppression_ligue();

	/***/
	void nouveau_plateau_ligue();

	/***/
	void select_plateau_ligue();

	/***/
	//void inserer_plateau_ligue();

	/***/
	void suppression_plateau_ligue();

	/**Cette méthode fait apparaître une boîte de dialogue montrant tous les plateaux du lieu courant. En fonction de ce que fait l'utilisateur, un message d'erreur apparaît si c'est invalide.*/
	void lier_plateaux();

	void lier_plateaux_ligue();

	void souder_lieux();

	/**Si le nom de la dernière sauvegarde est non vide,
charge le fichier de ce nom, puis met en place l'ihm en fonction de l'état de la partie.
Sinon, met en place une boîte de dialogue de chargement, si l'utilisateur choisit un fichier existant, alors met en place l'ihm en fonction de l'état de la partie.

Cette méthode ne fait rien si un thread est en train de tourner.*/
	void charger_rapidement();

	/**met en place une boîte de dialogue. L'utilisateur choisit un nom de fichier, si ce fichier existe, alors met en place l'ihm en fonction de la partie chargée.

Cette méthode ne fait rien si un thread est en train de tourner.*/
	void charger();

	/**Cette méthode importe des données externes et les place dans des variables statiques.*/
	//void importer();

	/**Si le nom de la dernière sauvegarde est non vide,
sauvegarde la partie avec ce nom de fichier.
Sinon, met en place une boîte de dialogue de chargement, si l'utilisateur choisit un fichier non vide alors sauvegarde la partie avec ce nom de fichier.

Cette méthode ne fait rien si un thread est en train de tourner.*/
	void sauvegarder_rapidement();

	/**met en place une boîte de dialogue de chargement, si l'utilisateur choisit un fichier non vide alors sauvegarde la partie avec ce nom de fichier.

Cette méthode ne fait rien si un thread est en train de tourner.*/
	void sauvegarder();

	/**Permet d'exporter les données en format XML.*/
	void exporter();

	/***/
	void valider();

	void ajouter_pk_marche();
	
	void inserer_pk_marche();
	
	void editer_pk_marche();
	
	void supprimer_pk_marche();

	void ajouter_pk_canne();
	
	void inserer_pk_canne();
	
	void editer_pk_canne();
	
	void supprimer_pk_canne();

	void ajouter_pk_super_canne();
	
	void inserer_pk_super_canne();
	
	void editer_pk_super_canne();
	
	void supprimer_pk_super_canne();

	void ajouter_pk_mega_canne();
	
	void inserer_pk_mega_canne();
	
	void editer_pk_mega_canne();
	
	void supprimer_pk_mega_canne();

	void maj_personnage();

	void maj_dresseur();

	void maj_champion();
	
	void editer_pk_leg();
	
	void editer_pk_don();

	void editer_objet();

	void confirmer_echange_pk_boites();
	
	void confirmer_obstacle_arbre(const QString& _nv_obst="");

	void confirmer_obstacle_rochers_destructibles(const QString& _nv_obst="");

	void confirmer_obstacle_rochers_amovibles(const QString& _nv_obst="");

	void confirmer_obstacle_tourbillons(const QString& _nv_obst="");

	void supprimer_elt_tuile();

	void ajouter_pk();

	void inserer_pk();

	void editer_pk();

	void supprimer_pk();

	void editer_coords_depart();

	void editer_pk_depart();

	void changer_nb_max_attaques();

	void editer_map();

	void lier_map();

	void ajouter_supprimer_condition_ligue();

	void ajouter_supprimer_condition_champions();

	void voir_donnees();

	void utilisation_logiciel();

	void base_de_donnees();

	/*void desouder_lieux();

	void desouder_plateaux();

	void desouder_ligue();

	void desouder_plateaux_ligue();*/
};
#endif



