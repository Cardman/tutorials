#ifndef EVOLUTIONOBJET_H
#define EVOLUTIONOBJET_H
#include "base_donnees/evolution/evolution.h"
#include <QString>

/**Le pokemon doit porter un objet et monter d'un niveau avec pour pouvoir evoluer.*/
class EvolutionObjet: public Evolution{

	/***/
	QString objet;

	Q_OBJECT
public:

	/**@param _objet*/
	EvolutionObjet(const QString&);

	/**@return la valeur de objet*/
	QString nom_objet()const;

	/***/
	virtual QString description(const QString&,const QString&,int,Donnees* _d)const;
};
#endif



