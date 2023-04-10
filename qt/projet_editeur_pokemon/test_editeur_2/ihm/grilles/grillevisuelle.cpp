#include "ihm/grilles/grillevisuelle.h"
#include "pseudo_ihm/tuilegraphique.h"
#include <QGridLayout>
#include <QPainter>

GrilleVisuelle::GrilleVisuelle():QLabel(){
	largeur=0;
}

void GrilleVisuelle::table_rase(){
	typedef QPair<int,int> Origine;
	foreach(Origine o,tuiles.cles()){
		tuiles.valeur(o)->reinit();
	}
	repaint();
}

void GrilleVisuelle::init(){
	TuileGraphique *tuile_=new TuileGraphique(QPair<int,int>(0,0));
	tuiles.ajouter_cle_valeur(QPair<int,int>(0,0),tuile_);
	repaint();
	resize(tuile_->imag().size());
	largeur=1;
}

void GrilleVisuelle::ajouter_lignes(int _nb){
	int nb_lignes_=nb_lignes();
	int nb_colonnes_=nb_colonnes();
	for(int j=0;j<_nb;j++){
		for(int i=0;i<nb_colonnes_;i++){
			TuileGraphique *tuile_=new TuileGraphique(QPair<int,int>(0,0));
			tuiles.ajouter_cle_valeur(QPair<int,int>(i,nb_lignes_+j),tuile_);
		}
	}
	QSize taille_=tuile(0,0)->imag().size();
	resize(taille_.width()*nb_colonnes(),taille_.height()*nb_lignes());
	repaint(0,nb_lignes_*taille_.height(),nb_colonnes_*taille_.width(),_nb*taille_.height());
}

void GrilleVisuelle::ajouter_colonnes(int _nb){
	int nb_lignes_=nb_lignes();
	int nb_colonnes_=nb_colonnes();
	for(int j=0;j<_nb;j++){
		for(int i=0;i<nb_lignes_;i++){
			TuileGraphique *tuile_=new TuileGraphique(QPair<int,int>(0,0));
			tuiles.ajouter_cle_valeur(QPair<int,int>(nb_colonnes_+j,i),tuile_);
		}
	}
	largeur+=_nb;
	QSize taille_=tuile(0,0)->imag().size();
	resize(taille_.width()*nb_colonnes(),taille_.height()*nb_lignes());
	repaint(nb_colonnes_*taille_.width(),0,_nb*taille_.width(),nb_lignes_*taille_.height());
}

int GrilleVisuelle::nb_lignes()const{
	if(largeur==0){
		return 0;
	}
	return tuiles.total()/largeur;
}

int GrilleVisuelle::nb_colonnes()const{
	return largeur;
}

void GrilleVisuelle::paintEvent(QPaintEvent *ev){
	QPainter paint_(this);
	typedef QPair<int,int> Origine;
	QList<Origine> cles_=tuiles.cles();
	QSize taille_;
	foreach(Origine o,cles_){
		TuileGraphique *t_=tuiles.valeur(o);
		taille_=t_->imag().size();
		paint_.drawImage(QPoint(o.first*taille_.width(),o.second*taille_.height()),t_->imag());
		QPair<QImage,bool> obst_=t_->obst();
		if(obst_.second){
			paint_.drawImage(QPoint(o.first*taille_.width(),o.second*taille_.height()),obst_.first);
		}
		QPair<QImage,bool> lien_=t_->lien();
		if(lien_.second){
			paint_.drawImage(QPoint(o.first*taille_.width(),o.second*taille_.height()),lien_.first);
		}
		QPair<QImage,bool> obj_=t_->obj();
		if(obj_.second){
			paint_.drawImage(QPoint(o.first*taille_.width(),o.second*taille_.height()),obj_.first);
		}
		QPair<QImage,QPair<int,int> > perso_=t_->perso();
		if(perso_.second!=QPair<int,int>(0,0)){
			paint_.drawImage(QPoint(o.first*taille_.width(),o.second*taille_.height()),perso_.first);
		}
	}
}

TuileGraphique *GrilleVisuelle::tuile(int _x,int _y){
	return tuiles.valeur(QPair<int,int>(_x,_y));
}

GrilleVisuelle::~GrilleVisuelle(){
	typedef QPair<int,int> Origine;
	QList<Origine> cles_=tuiles.cles();
	foreach(Origine o,cles_){
		TuileGraphique *t_=tuiles.valeur(o);
		delete t_;
		t_=NULL;
		tuiles.supprimer_cle_valeur(o);
	}
}



