#ifndef ENVIRONNEMENTLIGUE_H
#define ENVIRONNEMENTLIGUE_H
#include "serialisable/cartes/tuile.h"

/**Puisque un dresseur de la ligue est unique dans un plateau de la ligue et qu'il n'y a rien d'autre
à la ligue pokémon, on n'a pas besoin d'obstacles sur un environnement, ni d'objets, ni de pokémon
sauvage, sinon cela paraîtra bizarre.*/
class EnvironnementLigue{

	/**Largeur de l'environnement en nombre de tuile sur une ligne.*/
	int largeur;

	/**Cette attribut joue le même rôle que l'attribut type_environnement de Environnement*/
	QString type_environnement;

	/**Tuiles représentant l'environnement de la ligue*/
	QList<Tuile> tuiles;

public:

	/**constructeur permettant de sérialiser les données.*/
	EnvironnementLigue();

	/**constructeur permettant d'intialiser une instance de la classe avec les
	informations apportées par l'utilisateur (largeur,type_environnement) et une information indirectement stockée
	dans l'instance qui est la hauteur.
	Le nombre d'éléments de l'attribut tuiles est de _largeur * _hauteur
	@param _largeur pour assigner la valeur de largeur et calculer le nombre d'éléments de tuiles
	@param _hauteur pour calculer le nombre d'éléments de tuiles
	@param _type_environnement pour assigner la valeur de type_environnement*/
	EnvironnementLigue(int,int,const QString&);

	bool egal(const EnvironnementLigue&)const;

	/**Il faut calculer l'indice de la tuile à récupérer en fonction des coordonnées de la tuile à récupérer et des dimensions de l'environnement.

Dépend de la largeur.
indice = x + l * y, où x est l'abscisse de la tuile, y est l'abscisse de l'ordonnée et l la largeur de l'environnement.
@param _coords_tuile coordonnées de la tuile récupérer
@return L'adresse de la tuile à éditer.*/
	Tuile* tuile(const QPair<int,int>&);

	bool est_vide(const QPair<int,int>&)const;

	/**Cette méthode ajoute une ligne de tuiles standard à l'environnement à l'indice _indice.
Le nombre de tuiles ajoutées vaut la largeur de l'environnement.
La méthode ne modifie pas la largeur.
La méthode modifie certains attributs (ceux qui ont une ordonnée supérieur ou égal à _indice) pour incrémenter l'ordonnée de 1.

Dépend de la largeur.
@param _indice indice de la ligne par insertion*/
	void inserer_ligne(int);

	/**Cette méthode ajoute une ligne de tuiles standard à l'environnement à l'indice _indice.
Le nombre de tuiles ajoutées vaut le nombre total de tuiles sur la largeur de l'environnement.
La méthode incrémente la largeur de 1.
La méthode modifie certains attributs (ceux qui ont une abscisse supérieur ou égal à _indice) pour incrémenter l'abscisse de 1.

Dépend de la largeur.
@param _indice indice de la colonne à ajouter.*/
	void inserer_colonne(int);

	/**supprime tous les éléments sur la ligne et change les coordonnées (en ordonnée) de certains éléments.
@param _indice indice de la ligne à supprimer*/
	void supprimer_ligne(int);

	/**supprime tous les éléments sur la colonne et change les coordonnées (en abscisse) de certains éléments.

Décrémente de 1, la largeur.
@param _indice indice de la colonne à supprimer*/
	void supprimer_colonne(int);

	/**
@return L'adresse de type_environnement.*/
	QString* type_env();

	/**Cette méthode donne les dimensions de l'environnement (la hauteur est le quotient entier du nombre de tuiles sur
	la largeur, puisque le nombre de tuiles est un multiple de la largeur.)
	@return les dimensions largeur,hauteur de l'environnement*/
	QPair<int,int> dimensions()const;

	/**Cette méthode donne les dimensions et la position des 4 bords uniligne ou unicolonne de l'environnement (la hauteur est le quotient entier du nombre de tuiles sur
	la largeur, puisque le nombre de tuiles est un multiple de la largeur.)
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
	@return la position de les dimensions des 4 bords (extérieurs) de l'environnement*/
	QList<QPair<QPair<int,int>,QPair<int,int> > > bords(const QPair<int,int>&)const;

	/**Cette méthode calcule l'intersection entre 2 environnements
	@param id les coordonnées de l'environnement par rapport au plateau qui le contient
	@param dims les dimensions de l'environnement
	@param id_v les coordonnées de l'environnement voisin par rapport au plateau qui le contient
	@param dims_v les dimensions de l'environnement voisin
	@return les positions des coins extremes de l'intersection par rapport à l'environnement si elle existe, des données invalides sinon*/
	static QPair<QPair<int,int>,QPair<int,int> > intersection(const QPair<int,int>&,const QPair<int,int>&,const QPair<int,int>&,const QPair<int,int>&);

	/**Cette méthode exporte sous forme de chaîne de caractères les caractéristiques
de l'environnement situé à la ligue pokémon
appelle la fonction Tuile::exporter()const
Cette méthode ne ferme pas la balise EnvLigue
@param _nb_tab_env le nombre de tabulation à donner pour indenter les lignes.
@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
@return la chaîne de caractères décrivant l'environnement en format XML*/
	QString exporter(int,const QPair<int,int>&)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

bool operator==(const EnvironnementLigue&,const EnvironnementLigue&);

Flux & operator <<(Flux&,const EnvironnementLigue&);
Flux & operator >>(Flux&,EnvironnementLigue&);

#endif



