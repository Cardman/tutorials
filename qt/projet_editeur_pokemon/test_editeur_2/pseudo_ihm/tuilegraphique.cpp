#include "pseudo_ihm/tuilegraphique.h"

TuileGraphique::TuileGraphique(const QPair<int,int>& _coords,const QImage& _img){
	image=_img;
	coordonnees=_coords;
	obstacle=QPair<QImage,bool>(QImage(),false);
	objet=QPair<QImage,bool>(QImage(),false);
	lien_img=QPair<QImage,bool>(QImage(),false);
	personnage=QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0));
	condition_ligue=false;
}

void TuileGraphique::maj_obj(const QPair<QImage,bool>& _obj){
	objet=_obj;
}

QPair<QImage,bool> TuileGraphique::obj()const{
	return objet;
}

void TuileGraphique::maj_cond_ligue(bool _condition_ligue){
	condition_ligue=_condition_ligue;
}

bool TuileGraphique::cond_ligue()const{
	return condition_ligue;
}

void TuileGraphique::maj_lien(const QPair<QImage,bool>& _lien){
	lien_img=_lien;
}

QPair<QImage,bool> TuileGraphique::lien()const{
	return lien_img;
}


void TuileGraphique::maj_perso(const QPair<QImage,QPair<int,int> >& _perso){
	personnage=_perso;
}

QPair<QImage,QPair<int,int> > TuileGraphique::perso()const{
	return personnage;
}

void TuileGraphique::maj_obst(const QPair<QImage,bool>& _obst){
	obstacle=_obst;
}

QPair<QImage,bool> TuileGraphique::obst()const{
	return obstacle;
}

void TuileGraphique::maj_image(const QImage& _img){
	image=_img;
}

QImage TuileGraphique::imag()const{
	return image;
}

void TuileGraphique::maj_coords(const QPair<int,int>& _coords){
	coordonnees=_coords;
}

QPair<int,int> TuileGraphique::coords()const{
	return coordonnees;
}

void TuileGraphique::affecter(TuileGraphique* _autre,const QPair<int,int>& _coords){
	image=_autre->image;
	coordonnees=_coords;
	obstacle=_autre->obstacle;
	personnage=_autre->personnage;
	objet=_autre->objet;
	lien_img=_autre->lien_img;
	condition_ligue=_autre->condition_ligue;
}

void TuileGraphique::affecter(TuileGraphique* _autre){
	image=_autre->image;
	coordonnees=_autre->coordonnees;
	obstacle=_autre->obstacle;
	personnage=_autre->personnage;
	objet=_autre->objet;
	lien_img=_autre->lien_img;
	condition_ligue=_autre->condition_ligue;
}

void TuileGraphique::init(){
	obstacle=QPair<QImage,bool>(QImage(),false);
	personnage=QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0));
	objet=QPair<QImage,bool>(QImage(),false);
	lien_img=QPair<QImage,bool>(QImage(),false);
	condition_ligue=false;
}

void TuileGraphique::reinit(){
	image=Import::_tuile_invalide_;
	coordonnees=QPair<int,int>(0,0);
	obstacle=QPair<QImage,bool>(QImage(),false);
	lien_img=QPair<QImage,bool>(QImage(),false);
	personnage=QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0));
	objet=QPair<QImage,bool>(QImage(),false);
	condition_ligue=false;
}


