#ifndef OBJETEVO_H
#define OBJETEVO_H
#include "base_donnees/objets/objet.h"
#include <QStringList>
#include <QString>

/***/
class ObjetEvo: public Objet{

	Q_OBJECT

	/**Ensemble des pokemons pouvant evoluer en tenant cet objet et en montant d'un niveau.*/
	QStringList pokemon_compatibles;

	
	const static QStringList _descriptions_objets_evo_;

	
	static QStringList init_descriptions_objets_evo();

public:

	/**@param _pokemon_compatibles
	@param _prix_achat*/
	ObjetEvo(const QStringList&,int);

	/**@return la valeur de pokemon_compatibles*/
	QStringList pks()const;

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;
};
#endif



