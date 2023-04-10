#ifndef PLATEAULIGUE_H
#define PLATEAULIGUE_H
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/cartes/environnementligue.h"
#include "serialisable/personnages/dresseurligue.h"

/***/
class PlateauLigue{

	/***/
	HashMap<QPair<int,int>,EnvironnementLigue> environnements;

	/**Coordonnées du dresseur de la ligue*/
	QPair<int,int> coords_dresseur;

	/**dresseur présent dans une salle de la ligue.*/
	DresseurLigue dresseur_ligue;

	/**Les plateaux DE LA LIGUE sont LINEAIREMENT LIES, donc il suffit de connaitre le point de raccord*/
	//HashMap<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<QPair<int,int>,QPair<int,int> >,int> > liens_vers_autres_plateau_meme_lieu;
	QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > lien_vers_plateau_suivant;
public:

	/**Constructeur permettant de sérialiser un plateau de ligue*/
	PlateauLigue();

	bool egal(const PlateauLigue&)const;

	DresseurLigue *adr_dresseur_ligue();

	void supprimer_lien_vers_plateau_suivant();

	QPair<int,int> *adr_coords_dresseur();

	QPair<int,int> val_coords_dresseur()const;

	/**Méthode donnant les dimensions du plateau supposé valide
	@return les dimensions largeur hauteur du plateau*/
	QPair<int,int> dimensions()const;

	QPair<QPair<int,int>,QPair<int,int> > bords()const;

	/**Méthode permettant de relever des erreurs pour insertion du nouvel environnement
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
	@param _dims les dimensions à attribuer à l'environnement
	@param _id_vs les éventuels voisins qui gênent
	@return vrai si et seulement si l'environnement peut être insérer dans la hashmap environnements*/
	bool peut_contenir_nv_env(const QPair<int,int>&,const QPair<int,int>&,QList<QPair<int,int> >&)const;

	/**Méthode déplaçant (translation) un environnement dans la hashmap d'une position d'origine à une position de destination
	@param _origine l'ancienne origine de l'environnement
	@param _destination la nouvelle origine de l'environnement*/
	void deplacer(const QPair<int,int>&,const QPair<int,int>&);

	/**@return les positions des coins gauche de chaque environnement*/
	QList<QPair<int,int> > coins_gauche()const;

	/**Méthode ajoutant un environnement dans la hashmap environnements
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
	@param _nv_env le nouvel environnement à ajouter dans environnements*/
	void ajouter_environnement(const QPair<int,int>&,const EnvironnementLigue&);

	/**Méthode récupérant l'adresse d'un environnement
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
	@return l'adresse de l'environnement aux coordonnées indiquées*/
	EnvironnementLigue environnement(const QPair<int,int>&);

	/**Méthode récupérant l'adresse d'un environnement
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
	@param _n_inst un paramètre modifiable (de sortie seule) indiquant s'il faut libérer la mémoire ou non
	@return l'adresse de l'environnement aux coordonnées indiquées*/
	EnvironnementLigue *environnement(const QPair<int,int>&,bool&);

	/**Méthode supprimant un environnement dans la hashmap environnements
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient*/
	void supprimer_environnement(const QPair<int,int>&);

	/**@param _nb_lignes*/
	void decaler_vers_bas(int);

	/**@param _nb_colonnes*/
	void decaler_vers_droite(int);

	/**@return l'adresse de l'élément second de lien_vers_plateau_suivant*/
	QPair<QPair<int,int>,QPair<int,int> > *adr_dest_lien_vers_plateau_suivant();

	/**@return l'adresse de l'élément second de lien_vers_plateau_suivant*/
	QPair<QPair<int,int>,QPair<int,int> > dest_lien_vers_plateau_suivant()const;

	/**@return l'adresse de l'élément premier de lien_vers_plateau_suivant*/
	QPair<QPair<int,int>,QPair<int,int> > *adr_orig_lien_vers_plateau_suivant();

	/**@return l'adresse de l'élément second de lien_vers_plateau_suivant*/
	QPair<QPair<int,int>,QPair<int,int> > orig_lien_vers_plateau_suivant()const;

	/**@param _tuiles_inexistantes l'ensemble des tuiles inexistantes dans le plus petit rectangle contenant le plateau (exprimées dans le repère du plateau)
	@return vrai si et seulement si le plateau est valide c'est à dire si le recouvrement des environnements constitue un rectangle
	(autrement dit si _tuiles_inexistantes est vide)*/
	bool est_valide(QList<QPair<int,int> >&)const;

	/**Exporte les environnements voisins de _environnement à l'aide des données sur les emplacements
des environnements
Ceci permet de limiter le temps de calcul pour le chargement du jeu.
Donc en contre partie, il faut attribuer plus de place pour les ressources.
On commence par la gauche, puis on continue par le bas, puis par la droite, et enfin par le haut
Cette méthode ferme la balise EnvLigue
@param _nb_tab_env le nombre de tabulations à utiliser pour l'indentation des lignes
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
@param _environnement l'environnement dont on veut récupérer les environnements voisins avec les tuiles
adjacentes.
@return la liste des coordonnées des environnements voisins avec les coordonnées des tuiles adjacentes sous
forme de chaine dans un XML.*/
	QString exporter_environnements_voisins(int,const QPair<int,int>&,const EnvironnementLigue&)const;

	/**Exporte les informations sur le plateau de la ligue
	@param _nb_tab_env le nombre de tabulations à utiliser pour l'indentation des lignes
	@return la liste des coordonnées des environnements voisins avec les coordonnées des tuiles adjacentes sous
	forme de chaine dans un XML.*/
	QString exporter(int)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

bool operator==(const PlateauLigue&,const PlateauLigue&);

Flux & operator <<(Flux&,const PlateauLigue&);
Flux & operator >>(Flux&,PlateauLigue&);

#endif



