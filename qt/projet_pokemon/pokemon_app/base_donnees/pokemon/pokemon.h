#ifndef POKEMON_H
#define POKEMON_H
#include "serialisable/math/taux.h"
#include "serialisable/base_donnees/hashmap.h"
#include <QString>

/**Classe permettant de modeliser un pokemon (sauvage, utilisateur, dresse)
en combat (ou en aventure pour le cas de l'utilisateur). Un pokemon sauvage ou dresse dans cet uml, est un pokemon adverse.*/
class Pokemon{

	/***/
	QString nom;

	/***/
	uchar niveau;

	/***/
	QString genre;

	/**non modifiable une fois affecte a l'objet.*/
	QString capacite;

	/**si la chaine de caractere est vide alors le pokemon ne porte pas d'objet, sinon cette chaine vaut le nom de l'objet. */
	QString nom_objet;

	/***/
	//Taux pv_restants;

	/***/
	//QString statut;

	/***/
	//HashMap<QString,uchar> iv_statistiques;
public:

	Pokemon();

	Pokemon(const Pokemon&);

	/**Parseur d'un pokémon*/
	Pokemon(const QStringList&);

	/**Construit un pokemon a l'aide de son nom, de son genre (MALE, FEMEL, ), de son niveau et de sa capacite.
@param nom
@param genre
@param niveau
@param capacite*/
	//Pokemon(const QString&,const QString&,uchar,const QString&);

	QString n_pk()const;

	uchar niv_pk()const;

	QString genre_pk()const;

	QString capacite_pk()const;

	QString objet()const;

	//Taux pv_rest()const;

};

#endif


