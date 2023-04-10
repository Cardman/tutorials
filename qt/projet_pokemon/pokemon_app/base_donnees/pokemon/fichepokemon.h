#ifndef FICHEPOKEMON_H
#define FICHEPOKEMON_H
#include "serialisable/math/taux.h"
#include "serialisable/base_donnees/hashmap.h"
#include <QString>
#include <QStringList>

class Donnees;
class Evolution;

/**Classe decrivant un pokemon dans le
 pokedex. Une fiche pokemon contient:
	-un nom
	-un numero
	-une liste de couple nom de pokemon - d'evolution
	-un ensemble de couple niveau - nom d'attaque
	-un ensemble de numeros de CT
	-un ensemble de numeros de CS
	-un ensemble de types (1 ou 2)
	-un ensemble de capacites (1 ou 2)
	-une base d'experience
	-une masse
	-une taille
	-une repartition de genre
	-une base d'evolution
	-un ensemble de move tutors
	-une attaque de base
	-une defense de base
	-une attaque speciale de base
	-une defense speciale de base
	-une vitesse de base
	-des points de vie de base
Tous ces attributs ne peuvent pas etre modifies.*/
class FichePokemon{

	/***/
	QString nom;

	/**numero du pokemon*/
	int numero;

	/**masse de base (en kg) du pokemon*/
	Taux masse;

	/**Ensemble des noms des types du pokemon (maximum 2)*/
	QStringList types;

	
	HashMap<QString,QPair<uchar,uchar> > statistiques_ev;

	/**ensemble des duos niveau-nom d'attaque*/
	QList<QPair<uchar,QString> > attaques;

	/**Vaut une des valeurs suivantes:
	-MALE
	-FEMEL
	-MIXTE
	-ASSEXUE
	-<LEG>*/
	QString repartition_genre;

	/**Ensemble des capacites possibles a maitriser (un pokemon dans le combat n'est maitre que d'une seule capacite)*/
	QStringList capacites;

	/**Ensemble des attaques non apprises par montee de niveau mais en demandant a un personnage.*/
	QStringList move_tutors;

	/**Ensemble des capsules secretes apprenable par le pokemon. Une CS peut etre enseignee a autant de pokemon que l'utilisateur veut. Une CS n'est pas achetable.*/
	QList<uchar> capsules_secretes;

	/**Ensemble des capsules technique apprenable par le pokemon. Une fois utilise la CT ne fait plus partie du sac. Une CT est achetable.*/
	QList<uchar> capsules_techniques;

	/**nom du pokemon a donner a l'oeuf en cas de reproduction possible*/
	QString base_evo;

	/**HashMap des evolutions ayant pour identifiant la forme evoluee et la condition d'evolution.*/
	HashMap<QString,Evolution*> evolutions;

	/**taux de capture en cas de choix de la formule classique.*/
	uchar taux_capture;

	/**taille de base (en m) du pokemon*/
	Taux taille;

	/**Courbe d'expérience*/
	QString courbe;

	/**Pts exp de base*/
	uint pts_exp_adv_base;

	/**Groupes d'oeuf auxquels appartient le pokémon*/
	QStringList g_oeufs;

	/**Nombre de pas à faire pour l'éclosion de l'oeuf contenant ce pokémon*/
	Entier pas_eclosion;

	static QStringList _description_fiche_;

	static QStringList init_descriptions_fiches();

public:

	typedef Taux (*Courbe)(uchar);

	Courbe courbe_evo;

	/**Algo chargeant un pokémon dans la base de données
	@param _lignes lignes du fichier de données*/
	FichePokemon(const QStringList&);

	/**@return la valeur de nom*/
	QString n_pk()const;

	/**@return la valeur de numero*/
	int num()const;

	/**@return la valeur de masse*/
	Taux m_pk()const;

	/**@return la valeur de types*/
	QStringList typs()const;

	/**@return la valeur de statistiques_ev*/
	HashMap<QString,QPair<uchar,uchar> > stat_ev()const;

	/**@return la valeur de attaques*/
	QList<QPair<uchar,QString> > atts()const;

	/**@return la valeur de repartition_genre*/
	QString rep_genr()const;

	/**@return la valeur de capacites*/
	QStringList capac()const;

	/**@return la valeur de move_tutors*/
	QStringList mt()const;

	/**@return la valeur de capsules_secretes*/
	QList<uchar> cs()const;

	/**@return la valeur de capsules_techniques*/
	QList<uchar> ct()const;

	/**@return la valeur de base_evo*/
	QString b_ev()const;

	/**@return la valeur de evolutions*/
	HashMap<QString,Evolution*> evos()const;

	/**@return la valeur de taux_capture*/
	uchar tx_capt()const;

	/**@return la valeur de taille*/
	Taux t_pk()const;

	/**@return la valeur de courbe*/
	QString cb()const;

	/**@return la valeur de pts_exp_adv_base*/
	uint pt_base()const;

	/**@return la valeur de g_oeufs*/
	QStringList gps_o()const;

	/**@return la valeur de pas_eclosion*/
	Entier pas_ecl()const;

	
	QStringList pokemons_evolues()const;

	
	Evolution* facon_evoluer(const QString&)const;

	Taux stat(uchar,const QString&,uchar,uchar)const;

	QString description(const QString&,int,Donnees*);

	/**@param _niveau a atteindre*/
	Taux diff_pts_niveaux(uchar)const;

	/**Libère la mémoire allouée aux évolutions du pokémon*/
	~FichePokemon();
};

Taux rapide(uchar);
Taux moyenne(uchar);
Taux parabolique(uchar);
Taux lente(uchar);
Taux erratique(uchar);
Taux fluctuante(uchar);

#endif



