#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <QString>
#include <QPair>
//#include <QVariant>
//#include <QSettings>
#include "flux/flux.h"

/***/
//class Personnage: virtual public QObject{
class Personnage{

	/**Nom du personnage*/
	QString nom;

	//Q_OBJECT
	/**nom de la miniature du personnage a utiliser*/
	QString nom_miniature;

	/**orientation du personnage*/
	QPair<int,int> orientation;

protected:

	/**Cette méthode exporte les attributs de la classe
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@return une chaîne formatée contenant tous les attributs*/
	virtual QString exporter_attributs(int)const;

public:

	/**Constructeur permettant de sérialiser un personnage*/
	Personnage();

	virtual bool egal(const Personnage&)const;

	/**@return l'adresse de nom*/
	QString* adr_nom();

	/**@return l'adresse de nom_miniature*/
	QString* adr_nom_miniature();

	/**@return l'adresse de orientation*/
	QPair<int,int>* adr_orientation();

	/**Cette méthode exporte toute la classe, avec les balises d'ouverture et de fermeture
	@param _nb_tab_attr le nombre de tabulations à utiliser pour l'indentation
	@param _coords les coordonnées du personnage
	@return une chaîne formatée contenant tous les attributs et les balises d'ouverture et de fermeture*/
	virtual QString exporter(int,const QPair<int,int>&)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

bool operator==(const Personnage&,const Personnage&);

Flux & operator <<(Flux&,const Personnage&);
Flux & operator >>(Flux&,Personnage&);

#endif



