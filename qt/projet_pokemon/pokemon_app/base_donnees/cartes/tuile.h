#ifndef TUILE_H
#define TUILE_H
#include <QStringList>
#include <QList>
#include <QPair>
#include <QString>

/***/
class Tuile{

	/**Nom de fichier contenant une ressource sur l'image à utiliser pour représenter la tuile*/
	QString nom_image;

	/**Nom de fichier contenant une ressource sur l'image à utiliser pour représenter la tuile
	TODO changer en QPair<QString,int> pour indiquer le type d'obstacle separement*/
	QPair<QString,int> nom_image_obstacle;

public:

	/**Constante arbitraire indiquant des coordonnées invalides*/
	const static int _coords_invalide_;

	enum Obstacles{RIEN,ARBRE,ROCHER_AMOVIBLE,ROCHER_DESTRUCTIBLE,TOURBILLON};

	/**Parseur d'une tuile*/
	Tuile(const QString&);

	/**@return la valeur de nom_image*/
	QString val_nom_image();

	/**@return la valeur de nom_image_obstacle*/
	QPair<QString,int> val_nom_image_obst();

};
#endif


