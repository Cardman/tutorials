#ifndef POKEMON_H
#define POKEMON_H
#include <QString>
#include <QPair>
//#include <QVariant>
//#include <QSettings>
#include "flux/flux.h"

/**Classe permettant de modeliser un pokemon (sauvage, utilisateur, dresse)
en combat (ou en aventure pour le cas de l'utilisateur). Un pokemon sauvage ou dresse dans cet uml, est un pokemon adverse.
la portée protected des attributs ne sert qu'à la sérialiser des objets qui dérivent*/
class Pokemon{

	/**Nom du pokémon à créer*/
	QString nom;

	/**Niveau compris entre 1 et 255 du pokémon*/
	uchar niveau;

	/**MALE, FEMEL ou <vide>*/
	QString genre;

	/**Capacité du pokémon à créer.*/
	QString capacite;

	/**si la chaine de caractere est vide alors le pokemon ne porte pas d'objet, sinon cette chaine vaut le nom de l'objet. */
	QString nom_objet;

protected:

	/**Cette méthode exporte les attributs de la classe
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@return une chaîne formatée contenant tous les attributs*/
	virtual QString exporter_attributs(int)const;

public:

	/**Constructeur permettant de sérialiser un pokémon quelconque*/
	Pokemon();

	/**Construit un pokemon a l'aide de son nom, de son genre (MALE, FEMEL, ), de son niveau et de sa capacite.
@param _nom
@param _genre
@param _niveau
@param _capacite
@param _nom_objet*/
	//Pokemon(const QString&,const QString&,uchar,const QString&,const QString&);

	/**@return l'adresse de nom*/
	QString* adr_nom();

	/**@return l'adresse de niveau*/
	uchar* adr_niveau();

	/**@return l'adresse de genre*/
	QString* adr_genre();

	/**@return l'adresse de capacite*/
	QString* adr_capacite();

	/**@return l'adresse de nom_objet*/
	QString* adr_nom_objet();

	/**Opérateur de comparaison pour l'égalité
	@param _autre un autre pokémon*/
	virtual bool operator==(const Pokemon&)const;

	/**Cette méthode exporte toute la classe, avec les balises d'ouverture et de fermeture
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@return une chaîne formatée contenant tous les attributs et les balises d'ouverture et de fermeture*/
	virtual QString exporter(int)const;

	/**Cette méthode exporte toute la classe, avec les balises d'ouverture et de fermeture
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@param _coords les coordonnées du personnage
	@return une chaîne formatée contenant tous les attributs et les balises d'ouverture et de fermeture*/
	QString exporter(int,const QPair<int,int>&)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const Pokemon&);
Flux & operator >>(Flux&,Pokemon&);

#endif



