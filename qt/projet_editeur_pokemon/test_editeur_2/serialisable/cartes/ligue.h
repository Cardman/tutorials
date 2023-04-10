#ifndef LIGUE_H
#define LIGUE_H
#include "serialisable/coordonnees/coordonnees.h"
#include "serialisable/cartes/plateauligue.h"

/***/
class Ligue{

	/**Lieu d'accès à la ligue (premiere salle)*/
	Coordonnees acces;

	/**Lieu d'origine de la ligue (pour y entrer)*/
	Coordonnees origine;

	/**plateaux constituant la ligue*/
	QList<PlateauLigue> plateaux;

	//TODO nom de la ligue
	QString nom_ligue;
	//QPair<int,PlateauLigue> plateau_en_cours;

public:

	/**Constructeur permettant de sérialiser la ligue pokémon*/
	Ligue();

	bool egal(const Ligue&)const;

	bool est_valide()const;

	//QPair<int,PlateauLigue> *adr_plateau_en_cours();
	QString *adr_nom_ligue();

	/**@return l'adresse de acces*/
	Coordonnees *adr_acces();

	/**@return l'adresse de acces*/
	Coordonnees *adr_origine();

	/**@param _indice indice du plateau dont on veut récupérer l'adresse
	@return l'adresse d'un élément de "plateaux" */
	PlateauLigue *plateau(int);

	/***/
	int nb_plateaux()const;

	void inserer_plateau(int _indice,const PlateauLigue&);

	/**Méthode ajoutant un plateau à la suite d'un autre
	Pour relier un plateau à la ligue il faut d'abord indiquer une origine valide si ce n'est pas le dernier
	L'origine du lien est déjà éditée avant l'appel de cette méthode
	@param _indice indice d'insertion du plateau
	@param _plateau plateau à insérer
	@param _point_de_raccord le point de raccord pour le plateau précédent s'il existe, sinon pour le plateau à insérer*/
	//void ajouter_plateau(int,PlateauLigue&,const QPair<QPair<int,int>,QPair<int,int> >&);

	//void ajouter_lien_plateau(int,PlateauLigue&,const QPair<QPair<int,int>,QPair<int,int> >&);

	void supprimer_plateau_reindexer(int);

	/**Méthode supprimant un plateau
	@param _indice indice de suppression du plateau*/
	//void supprimer_plateau(int);

	/**@return vrai si et seulement si tous les plateaux de la ligue sont valides et il existe un plateau de la ligue et les coordonnées de l'origine et de l'accès sont valides*/
	bool est_valide();

	/**Cette méthode exporte sous forme de chaîne de caractères les caractéristiques
de la ligue pokémon
Cette méthode ne ferme pas la balise EnvLigue
@param _nb_tab_env le nombre de tabulation à donner pour indenter les lignes.
@return la chaîne de caractères décrivant l'environnement en format XML*/
	QString exporter(int)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

bool operator==(const Ligue&,const Ligue&);

Flux & operator <<(Flux&,const Ligue&);
Flux & operator >>(Flux&,Ligue&);

#endif



