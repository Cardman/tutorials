#ifndef EVOLUTIONCONDITIONSTAT_H
#define EVOLUTIONCONDITIONSTAT_H
#include "base_donnees/evolution/evolutionniveau.h"
#include <QString>

/**Classe permettant de dire quelle statistique faire dominer entre attaque physique et defense physique pour l'evolution. Si l'attribut est une chaine de caracteres vide alors il doit y avoir egalite entre l'attaque physique et la defense physique.*/
class EvolutionConditionStat: public EvolutionNiveau{

	Q_OBJECT

	/***/
	QString statistique;

public:

	/**@param _niveau
	@param _stat*/
	EvolutionConditionStat(uchar,const QString&);

	/**@return la valeur de statistique*/
	QString stat()const;

	/***/
	virtual QString description(const QString&,const QString&,int,Donnees* _d)const;
};
#endif



