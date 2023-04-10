#ifndef MODULE_H
#define MODULE_H
#include "base_donnees/objets/objet.h"
/***/
class Module:public Objet{

	Q_OBJECT
	
	const static QStringList _descriptions_modules_;

	QString type_techno_buster;

	/***/
	static QStringList init_descriptions_modules();

public:

	/**@param _prix_vente*/
	Module(const QString&,int);

	QString type()const;

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int,Donnees*)const;

};

#endif

