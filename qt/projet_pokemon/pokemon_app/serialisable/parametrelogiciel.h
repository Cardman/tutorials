#ifndef PARAMETRELOGICIEL_H
#define PARAMETRELOGICIEL_H
#include "flux/flux.h"

class Donnees;
class ParametreLogiciel{

	/**langue du logiciel*/
	int langue;

	/***/
	QString der_sauvegarde;

	/***/
	bool lancer_der_sauvegarde;

public:

	ParametreLogiciel(Donnees* =NULL);

	void init(Donnees*);

	int val_langue()const;

	QString val_der_sauvegarde()const;

	bool val_lancer_der_sauvegarde()const;

	int& val_langue();

	QString& val_der_sauvegarde();

	bool& val_lancer_der_sauvegarde();

	void sauvegarder(Donnees*)const;

	void charger(Donnees*);

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

#endif // PARAMETRELOGICIEL_H
