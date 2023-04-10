#ifndef COMBATTANT_H
#define COMBATTANT_H
#include "flux/flux.h"

/***/
class Combattant{

	/**position par rapport à l'équipe juste avant le combat. Les deux coordonnées sont positives ou nulles.*/
	QPair<uchar,uchar> coordonnees_equipe_totale;

public:

	Combattant();

	Combattant(uchar,uchar);

	uchar equipe()const;

	uchar position()const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

bool operator==(const Combattant&,const Combattant&);

bool operator!=(const Combattant&,const Combattant&);

Flux & operator <<(Flux&,const Combattant&);
Flux & operator >>(Flux&,Combattant&);

#endif


