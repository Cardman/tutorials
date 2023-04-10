#ifndef PLATEAU_H
#define PLATEAU_H
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/cartes/environnement.h"
#include "serialisable/coordonnees/coordonnees.h"

/**TODO traiter l'édition des liens entre plateaux et lieux
L'origine (coin haut gauche du plateau) a pour coordonnées 0,0
par rapport au plateau
//TODO contraintes >= 0 pour les coordonnées.
//TODO ajouter_ligne, ajouter_colonne,supprimer_ligne,supprimer_colonne
conditions pour pouvoir supprimer une ligne ou une colonne*/
class Plateau{

	/***/
	HashMap<QPair<int,int>,Environnement> environnements;

	/***/
	HashMap<QPair<QPair<int,int>,QPair<int,int> >,Coordonnees> liens_vers_autres_plateau;

	/***/
	HashMap<QPair<QPair<int,int>,QPair<int,int> >,QString> noms_images_liens;

	/***/
	HashMap<QPair<QPair<int,int>,QPair<int,int> >,Coordonnees> liens_vers_autres_plateau_tmp;

	/***/
	HashMap<QPair<QPair<int,int>,QPair<int,int> >,QString> noms_images_liens_tmp;

	/**clé: couple id lieu, id plateau voisins
valeur:
	premier: coords_tuile_relatif à ce plateau
	deuxième: coords_tuile_relatif au plateau voisin*/
	//HashMap<QPair<int,int>,QPair<QPair<int,int>,QPair<int,int> > > liens_vers_autres_lieux;
public:

	/**Constructeur permettant de sérialiser un plateau*/
	Plateau();

	bool egal(const Plateau&)const;

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

	void deplacer_liens(const QPair<int,int>&,const QPair<int,int>&);

	/**@param _nb_lignes*/
	void decaler_vers_bas(int);

	/**@param _nb_colonnes*/
	void decaler_vers_droite(int);

	/**@return les positions des coins gauche de chaque environnement*/
	QList<QPair<int,int> > coins_gauche()const;

	/**@return les clés de liens_vers_autres_plateau*/
	QList<QPair<QPair<int,int>,QPair<int,int> > > liaisons_vers_autres_plateaux()const;

	/**Méthode ajoutant un environnement dans la hashmap environnements
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
	@param _nv_env le nouvel environnement à ajouter dans environnements*/
	void ajouter_environnement(const QPair<int,int>&,const Environnement&);

	/**Méthode supprimant un environnement dans la hashmap environnements
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient*/
	void supprimer_environnement(const QPair<int,int>&);

	/**Méthode récupérant un environnement
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
	@return l'adresse de l'environnement aux coordonnées indiquées*/
	Environnement environnement(const QPair<int,int>&)const;

	/**Méthode récupérant l'adresse d'un environnement
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
	@param _n_inst un paramètre modifiable (de sortie seule) indiquant s'il faut libérer la mémoire ou non
	@return l'adresse de l'environnement aux coordonnées indiquées*/
	Environnement *environnement(const QPair<int,int>&,bool&);

	/**Méthode donnant les dimensions du plateau supposé valide
	@return les dimensions largeur hauteur du plateau*/
	QPair<int,int> dimensions()const;

	/***/
	QPair<QPair<int,int>,QPair<int,int> > bords()const;

	/**Méthode récupérant l'adresse d'un lien vers un autre plateau
	@param _origine
	@param _n_inst un paramètre modifiable (de sortie seule) indiquant s'il faut libérer la mémoire ou non
	@return l'adresse d'un lien vers un autre plateau*/
	QString *image_origine_liaison(const QPair<QPair<int,int>,QPair<int,int> >& _origine,bool& _n_inst);

	/**Méthode récupérant un lien vers un autre plateau
	@param _origine
	@return l'adresse d'un lien vers un autre plateau*/
	QString image_origine_liaison(const QPair<QPair<int,int>,QPair<int,int> >& _origine);

	/**Méthode ajoutant un lien vers un autre plateau
	@param _origine
	@param _lien l'adresse d'un lien vers un autre plateau*/
	void ajouter_image_origine_liaison(const QPair<QPair<int,int>,QPair<int,int> >& _origine,const QString&);

	/**Méthode récupérant l'adresse d'un lien vers un autre plateau
	@param _origine
	@param _n_inst un paramètre modifiable (de sortie seule) indiquant s'il faut libérer la mémoire ou non
	@return l'adresse d'un lien vers un autre plateau*/
	Coordonnees *destination_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine,bool& _n_inst);

	/**Méthode récupérant un lien vers un autre plateau
	@param _origine
	@return l'adresse d'un lien vers un autre plateau*/
	Coordonnees destination_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine);

	/**Méthode ajoutant un lien vers un autre plateau
	@param _origine
	@param _lien l'adresse d'un lien vers un autre plateau*/
	void ajouter_dest_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >& _origine,const Coordonnees&);

	/***/
	void supprimer_dest_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >&);

	/***/
	void supprimer_dest_autre_plateau_tmp(const QPair<QPair<int,int>,QPair<int,int> >&);

	/***/
	void supprimer_toutes_dest_autre_plateau();

	/***/
	void aff_liens_vers_autres_plateau();

	/***/
	void aff_liens_vers_autres_plateau_tmp();

	/***/
	void aff_noms_images_liens();

	/***/
	void aff_noms_images_liens_tmp();

	/**@param _tuiles_inexistantes l'ensemble des tuiles inexistantes dans le plus petit rectangle contenant le plateau (exprimées dans le repère du plateau)
	@return vrai si et seulement si le plateau est valide c'est à dire si le recouvrement des environnements constitue un rectangle
	(autrement dit si _tuiles_inexistantes est vide)*/
	bool est_valide(QList<QPair<int,int> >&)const;

	/**Exporte les environnements voisins de _environnement à l'aide des données sur les emplacements
des environnements
Ceci permet de limiter le temps de calcul pour le chargement du jeu.
Donc en contre partie, il faut attribuer plus de place pour les ressources.
	@param _nb_tab_env le nombre de tabulations à utiliser pour l'indentation des lignes
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
@param _environnement l'environnement dont on veut récupérer les environnements voisins avec les tuiles
adjacentes.
@return la liste des coordonnées des environnements voisins avec les coordonnées des tuiles adjacentes sous
forme de chaine dans un XML.*/
	QString exporter_environnements_voisins(int,const QPair<int,int>&,const Environnement&)const;

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

bool operator==(const Plateau&,const Plateau&);

Flux & operator <<(Flux&,const Plateau&);
Flux & operator >>(Flux&,Plateau&);

#endif



