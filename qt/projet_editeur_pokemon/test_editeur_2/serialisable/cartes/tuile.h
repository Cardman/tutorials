#ifndef TUILE_H
#define TUILE_H
#include "flux/flux.h"
#include <QStringList>
#include <QList>
#include <QPair>
#include <QString>
//#include <QVariant>

//#include <QSettings>

/***/
class Tuile{

	/**Nombre nécessaire de pokémon de nom différent pour accéder à cette tuile*/
	//int nb_pokemon_attr_nec_dist;

	/**Nom de fichier contenant une ressource sur l'image à utiliser pour représenter la tuile*/
	QString nom_image;

	/**Nom de fichier contenant une ressource sur l'image à utiliser pour représenter la tuile
	TODO changer en QPair<QString,int> pour indiquer le type d'obstacle separement*/
	QPair<QString,int> nom_image_obstacle;

public:

	/**Constante arbitraire indiquant des coordonnées invalides*/
	const static int _coords_invalide_;

	/**Nombre de bords autour d'un environnement*/
	const static int _nb_bords_;

	/**Constante arbitraire indiquant un type d'obstacle*/
	const static QString _arbre_;

	/**Constante arbitraire indiquant un type d'obstacle*/
	const static QString _rochers_dest_;

	/**Constante arbitraire indiquant un type d'obstacle*/
	const static QString _rochers_amov_;

	/**Constante arbitraire indiquant un type d'obstacle*/
	const static QString _siphon_;

	enum Obstacles{RIEN,ARBRE,ROCHER_AMOVIBLE,ROCHER_DESTRUCTIBLE,TOURBILLON};

	/**Constructeur par défaut permettant de sérialiser une tuile*/
	Tuile();

	bool egal(const Tuile&)const;

	/**@return l'adresse de nb_pokemon_attr_nec_dist*/
	//int *adr_nb_pokemon_attr_nec_dist();

	/**@return l'adresse de nom_image*/
	QString *adr_nom_image();

	/**@return l'adresse de nom_image_obstacle*/
	QPair<QString,int> *adr_nom_image_obst();

	/** Cette méthode permet d'exporter une tuile sous une chaîne de caractère en format XML
	@return une chaîne de caractères formatée en XML, décrivant une tuile.*/
	QString exporter()const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const Tuile&);
Flux & operator >>(Flux&,Tuile&);

bool operator==(const Tuile&,const Tuile&);

#endif



