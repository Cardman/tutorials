#include "serialisable/cartes/tuile.h"
const int Tuile::_coords_invalide_=-1;
const int Tuile::_nb_bords_=4;
const QString Tuile::_arbre_="ARBRE";
const QString Tuile::_rochers_dest_="ROCHERS_DEST";
const QString Tuile::_rochers_amov_="ROCHERS_AMOV";
const QString Tuile::_siphon_="SIPHON";

Tuile::Tuile(){
	//nb_pokemon_attr_nec_dist=0//Par défaut, il n'est pas nécessaire d'avoir attrapé un pokémon pour avancer.
	nom_image_obstacle.second=Tuile::RIEN;
}

bool Tuile::egal(const Tuile& _autre)const{
	return nom_image==_autre.nom_image&&nom_image_obstacle==_autre.nom_image_obstacle;
}

/*int *Tuile::adr_nb_pokemon_attr_nec_dist(){
	return &nb_pokemon_attr_nec_dist
}*/

QString *Tuile::adr_nom_image(){
	return &nom_image;
}

QPair<QString,int> *Tuile::adr_nom_image_obst(){
	return &nom_image_obstacle;
}

QString Tuile::exporter()const{
	QString descr_="<Tuile>";//<NbPkNec>"+QString::number(nb_pokemon_attr_nec_dist)+"</NbPkNec>"
	if(nom_image_obstacle.first!=""){
		descr_+="<ImageObst id\""+QString::number(nom_image_obstacle.second)+"\">"+nom_image_obstacle.first+"</ImageObst>";
	}
	descr_+="<Image>"+nom_image+"</Image><Tuile>\n";
	return descr_;
}

bool operator==(const Tuile& a,const Tuile& b){
	return a.egal(b);
}

void Tuile::serialiser(Flux& _out)const{
	//_out<<nb_pokemon_attr_nec_dist
	_out<<nom_image;
	_out<<nom_image_obstacle;
}

void Tuile::deserialiser(Flux& _in){
	//_in>>nb_pokemon_attr_nec_dist
	_in>>nom_image;
	_in>>nom_image_obstacle;
}

Flux & operator <<(Flux& out,const Tuile& _Tuile){
	_Tuile.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Tuile& _Tuile){
	_Tuile.deserialiser(in);
	return in;
}



