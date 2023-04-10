#ifndef PARAMETRESLOGICIEL_H
#define PARAMETRESLOGICIEL_H
#include "flux/flux.h"

/***/
class ParametresLogiciel{

	/**langue du logiciel*/
	QString langue;

	/***/
	QString der_sauvegarde;

	/***/
	bool lancer_der_sauvegarde;

	/***/
	bool clic_sur_bouton;

public:

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const ParametresLogiciel&);
Flux & operator >>(Flux&,ParametresLogiciel&);

#endif


