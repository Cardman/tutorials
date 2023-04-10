#ifndef DONNEES_H
#define DONNEES_H
#include "serialisable/cartes/lieu.h"
#include "serialisable/cartes/ligue.h"
#include "serialisable/coordonnees/coordonnees.h"
#include "serialisable/base_donnees/hashmap.h"
#include "base_donnees/import.h"

/**Contient les elements qui ne changent pas du tout au cours du jeu (excepte les acces a certains de la carte)
//TODO possibilité de supprimer les éléments, changer certains éléments en fonction des déplacements d'environnement ou de plateau
TODO fonction bool est_valide(const Import&)const*
TODO delier_plateaux_lieux_diff à recoder*/
class Donnees{

	/**Nombre maximal d'attaques (entre 2 et 8 compris).*/
	uchar nb_attaques_max;

	/***/
	HashMap<int,QPair<QString,QString> > nom_types_lieux;

	/***/
	HashMap<int,Lieu> lieux;

	/***/
	HashMap<int,Ligue> ligues;

	HashMap<Coordonnees,QList<int> > acces_fct_ligues;

	HashMap<int,QList<Coordonnees> > champions_battre_ligue;

	HashMap<Coordonnees,Champion> champions_battre;

	/**Pour que pendant le jeu, l'utilisateur puisse voler à certains endroit en regardant une carte globale*/
	HashMap<QPair<int,int>,Coordonnees> lieux_vols;

	/***/
	HashMap<QPair<int,int>,QString> images_minimap;

	/***/
	Coordonnees coords_depart;

	/***/
	Pokemon pk_depart;

	/***/
	//int ligue_tmp;

public:

	//static uchar _nb_attaques_max_;

	/**Constructeur premttant de sérialiser les données*/
	Donnees();

	bool egal(const Donnees&)const;

	bool est_valide()const;

	HashMap<Coordonnees,QList<int> > *adr_acces_fct_ligues();

	//int *adr_ligue_tmp();

	/**@return l'adresse de coords_depart*/
	Coordonnees *adr_coords_depart();

	/**@return l'adresse de coords_depart*/
	Pokemon *adr_pk_depart();

	/**@return l'adresse de nb_attaques_max*/
	uchar *adr_nb_attaques_max();

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	Lieu *lieu(int);

	/**@param _indice l'indice du lieu
	@param _lieu le nouveau lieu*/
	void ajouter_lieu(int,const Lieu&);

	/**@param _indice l'indice du lieu*/
	void supprimer_lieu(int);

	/***/
	QList<int> lieux_c()const;

	HashMap<int,QPair<QString,QString> > nom_type_lieux()const;

	void maj_nom_type_lieu(int,const QPair<QString,QString>&);

	HashMap<int,QList<Coordonnees> > *adr_champions_battre_ligue();

	HashMap<Coordonnees,Champion> val_champions_battre()const;

	void maj_champions_battre(const Coordonnees&,const Champion&);

	void supprimer_champions_battre(const Coordonnees&);

	/***/
	bool peuvent_etre_lies_lieux(int,int,int,int,Lieu::Orientation)const;

	/***/
	void enlever_tous_liens_vers_plat(int,int);

	/**appelle Plateau::supprimer_dest_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >&)*/
	void delier_plateaux_lieux_diff(int,int,const QPair<QPair<int,int>,QPair<int,int> >&);

	/**appelle Plateau::supprimer_dest_autre_plateau(const QPair<QPair<int,int>,QPair<int,int> >&)*/
	void delier_plateaux_lieux_diff_double(int,int,const QPair<QPair<int,int>,QPair<int,int> >&);

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	Ligue *ligue(int);

	/**@param _indice l'indice du lieu
	@param _ligue le nouveau lieu*/
	void ajouter_ligue(int,const Ligue&);

	/**@param _indice l'indice du lieu*/
	void supprimer_ligue(int);

	
	QList<int> ligues_c()const;

	HashMap<QPair<int,int>,Coordonnees> vols()const;

	void maj_vols(const HashMap<QPair<int,int>,Coordonnees>&);

	HashMap<QPair<int,int>,QString> minimap()const;

	void maj_minimap(const HashMap<QPair<int,int>,QString>&);

	/**@param _coords
	@param _n_instance
	@return l'adresse du lieu d'indice _indice*/
	QString *image_minimap(const QPair<int,int>&,bool&);

	/**@param _coords
	@return l'adresse du lieu d'indice _indice*/
	QString image_minimap(const QPair<int,int>&)const;

	/***/
	void ajouter_image_minimap(const QPair<int,int>&,const QString&);

	
	void supprimer_image_minimap(const QPair<int,int>&);

	
	QList<QPair<int,int> > origines_images_minimap()const;

	/**@param _coords
	@param _n_instance
	@return l'adresse du lieu d'indice _indice*/
	Coordonnees *lieu_vols(const QPair<int,int>&,bool&);

	/**@param _coords
	@return l'adresse du lieu d'indice _indice*/
	Coordonnees lieu_vols(const QPair<int,int>&)const;

	/***/
	void ajouter_lieu_vols(const QPair<int,int>&,const Coordonnees&);

	
	void supprimer_lieu_vols(const QPair<int,int>&);

	
	QList<QPair<int,int> > origines_vols()const;

	/**Algo bis reliant deux plateaux du même lieu à l'aide des coordonnées d'environnement et de tuiles
	Les lieux doivent être collés
	@param _indice_l indice du premier lieu contenant le premier plateau
	@param _indice_l_2 indice du deuxieme lieu contenant le deuxieme plateau
	@param _coords coordonnées du premier plateau à lier avec un autre plateau
	@param _coords_2 coordonnées du deuxieme plateau à lier avec un autre plateau
	*/
	void relier_lieux(int,int,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&);

	/**Algo reliant deux plateaux du même lieu à l'aide des coordonnées d'environnement et de tuiles
	Les lieux doivent être collés
	@param _indice_l indice du premier lieu contenant le premier plateau
	@param _indice_l_2 indice du deuxieme lieu contenant le deuxieme plateau
	@param _coords coordonnées du premier plateau à lier avec un autre plateau
	@param _coords_2 coordonnées du deuxieme plateau à lier avec un autre plateau
	@param _futurs_cles clés pour remplir une première hashmap
	@param _futurs_cles_2 clés pour remplir une deuxième hashmap
	*/
	void relier_lieux(int,int,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&,const QList<QPair<QPair<int,int>,QPair<int,int> > >&,const QList<QPair<QPair<int,int>,QPair<int,int> > >&);

	/**Méthode déliant des lieux
	@param _indice indice du premier lieu
	@param _indice_2 indice du deuxième lieu*/
	void delier_lieux(int,int);

	/***/
	void desouder_lieux_plateau(int,int,int,int);

	/**Méthode exportant toutes les données du jeu en cartographie
	avec le format XML
	@return la chaîne de caractères qui va être écrite dans le fichier de ressources*/
	QString exporter()const;

	void sauvegarder(const QString&)const;

	void charger(const QString&);

	//static Donnees charger_statique(const QString&);

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const Donnees&);
Flux & operator >>(Flux&,Donnees&);

#endif



