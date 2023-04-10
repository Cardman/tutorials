#ifndef OEUFPOKEMON_H
#define OEUFPOKEMON_H
#include "flux/flux.h"

class Donnees;

/**Classe permettant de modeliser un oeuf  de pokemon lors de l'eclosion un nouveau pokemon apparait dans l'equipe de l'utilisateur au niveau 1.*/
class OeufPokemon{

	/**nom du pokemon a donner lors de l'eclosion*/
	QString nom;

	/**nom du pokémon ayant produit l'oeuf.*/
	QString nom_parent;

	/**nombre de pas depuis l'obtention de l'oeuf.*/
	int nombre_pas;
public:

	/**Si l'utilisateur fait plus de pas que la valeur de cette variable avec l'oeuf dans l'equipe, alors l'oeuf eclot.*/
	const static int max_pas_eclore;

	/**constructeur par défaut.*/
	OeufPokemon();

	/**constructeur appelé lorsque l'utilisateur reçoit un oeuf dans l'équipe.
@param _nom nom du pokémon qui a produit l'oeuf.*/
	OeufPokemon(const QString&,Donnees*);

	/**incrémente le nombre de pas de _coeff
@param _coeff coefficient d'incrément du nombre de pas pour l'éclosion de l'oeuf.*/
	void vers_eclosion(uchar);

	int nb_pas()const;

	/**Nom du pokemon qui va eclore*/
	QString nom_pk()const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const OeufPokemon&);
Flux & operator >>(Flux&,OeufPokemon&);

#endif


