#ifndef EFFET_H
#define EFFET_H
#include <QObject>
#include <QStringList>
#include "serialisable/base_donnees/hashmap.h"
/***/
class Donnees;
class Effet: public QObject{

	/**vrai si et seulement si le lanceur est affecté par l'effet*/
	bool lanceur;

	/***/
	static HashMap<QString,QString> init_descriptions_effets();

protected:

	/***/
	const static HashMap<QString,QString> _descriptions_effets_;


public:

	/**@param _lanceur*/
	Effet(bool _lanceur=false,QObject *parent=0);

	/**@param _lanceur*/
	void maj_lanceur(bool);

	/**Donne la description d'un objet.
	@param _langue langue de destination*/
	virtual QString description(int _langue,Donnees* _d)const;

	/**@return la valeur de lanceur*/
	bool qui()const;
};
#endif


