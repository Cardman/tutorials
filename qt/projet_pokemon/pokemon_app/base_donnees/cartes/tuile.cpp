#include "base_donnees/cartes/tuile.h"
#include <QStringList>
const int Tuile::_coords_invalide_=-1;

Tuile::Tuile(const QString& _ligne){
	//nb_pokemon_attr_nec_dist=0//Par défaut, il n'est pas nécessaire d'avoir attrapé un pokémon pour avancer.
	nom_image_obstacle.second=Tuile::RIEN;
	if(_ligne.contains("<ImageObst id")){
	//ImageObst
		int ind_=_ligne.indexOf("<ImageObst");
		QString attr_=_ligne.mid(ind_,_ligne.indexOf("</ImageObst")-ind_);
		nom_image_obstacle.second=attr_.split("\"")[1].toUInt();
		nom_image_obstacle.first=attr_.split(">")[1];
	}
	int ind_=_ligne.indexOf("<Image>");
	QString attr_=_ligne.mid(ind_,_ligne.indexOf("</Image>")-ind_);
	nom_image=attr_.split(">")[1];
}

QString Tuile::val_nom_image(){
	return nom_image;
}

QPair<QString,int> Tuile::val_nom_image_obst(){
	return nom_image_obstacle;
}



