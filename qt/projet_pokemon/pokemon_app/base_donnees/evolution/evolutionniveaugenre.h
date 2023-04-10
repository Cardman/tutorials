#ifndef EVOLUTIONNIVEAUGENRE_H
#define EVOLUTIONNIVEAUGENRE_H
#include "base_donnees/evolution/evolutionniveau.h"

/**Classe combinant les conditions de necessite d'obtenir un niveau et un genre.*/
class EvolutionNiveauGenre: public EvolutionNiveau{

	Q_OBJECT

	/***/
	QString genre;

public:

	/**@param _niveau
	@param _genre*/
	EvolutionNiveauGenre(uchar,const QString&);

	/**@return la valeur de genre*/
	QString gr()const;

	/***/
	virtual QString description(const QString&,const QString&,int,Donnees* _d)const;
};
#endif



