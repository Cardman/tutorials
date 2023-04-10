#include "ihm/grilles/grillemap.h"
#include "pseudo_ihm/tuilemap.h"
#include <QPainter>
#include <QMouseEvent>

GrilleMap::GrilleMap():QLabel(){
	largeur=0;
	rectangle_nv_env=QPair<int,int>(-1,-1);
}

void GrilleMap::table_rase(){
	typedef QPair<int,int> Origine;
	foreach(Origine o,tuiles.cles()){
		tuiles.valeur(o)->reinit();
	}
	repaint();
}

void GrilleMap::init(){
	TuileMap *tuile_=new TuileMap();
	tuiles.ajouter_cle_valeur(QPair<int,int>(0,0),tuile_);
	repaint();
	resize(tuile_->imag().size());
	largeur=1;
}

void GrilleMap::mouseReleaseEvent(QMouseEvent* _event){
	QPoint pos_=_event->pos();
	if(tuiles.total()>0){
		QSize taille_=tuiles.valeur(QPair<int,int>(0,0))->imag().size();
		int x_=pos_.x()/taille_.width();
		int y_=pos_.y()/taille_.height();
		if(x_<largeur&&y_<nb_lignes()){
			rectangle_nv_env=QPair<int,int>(x_,y_);
			emit selection(rectangle_nv_env);
		}
	}
}

void GrilleMap::ajouter_lignes(int _nb){
	int nb_lignes_=nb_lignes();
	int nb_colonnes_=nb_colonnes();
	for(int j=0;j<_nb;j++){
		for(int i=0;i<nb_colonnes_;i++){
			TuileMap *tuile_=new TuileMap();
			tuiles.ajouter_cle_valeur(QPair<int,int>(i,nb_lignes_+j),tuile_);
		}
	}
	QSize taille_=tuile(0,0)->imag().size();
	resize(taille_.width()*nb_colonnes(),taille_.height()*nb_lignes());
	repaint(0,nb_lignes_*taille_.height(),nb_colonnes_*taille_.width(),_nb*taille_.height());
}

void GrilleMap::decaler_vers_bas(int _nb_lgs){
	int hauteur_=nb_lignes();
	ajouter_lignes(_nb_lgs);
	int nb_lignes_=nb_lignes();
	int nb_colonnes_=nb_colonnes();
	for(int i=nb_lignes_-1;i>nb_lignes_-hauteur_-1;i--){
		for(int j=0;j<nb_colonnes_;j++){
			TuileMap *tuile_=tuile(j,i);
			TuileMap *tuile_2_=tuile(j,i-_nb_lgs);
			tuile_->affecter(tuile_2_);
		}
	}
	for(int i=nb_lignes_-hauteur_-1;i>-1;i--){
		for(int j=0;j<nb_colonnes_;j++){
			TuileMap *tuile_=tuile(j,i);
			tuile_->reinit();
		}
	}
}

void GrilleMap::ajouter_colonnes(int _nb){
	int nb_lignes_=nb_lignes();
	int nb_colonnes_=nb_colonnes();
	for(int j=0;j<_nb;j++){
		for(int i=0;i<nb_lignes_;i++){
			TuileMap *tuile_=new TuileMap();
			tuiles.ajouter_cle_valeur(QPair<int,int>(nb_colonnes_+j,i),tuile_);
		}
	}
	largeur+=_nb;
	QSize taille_=tuile(0,0)->imag().size();
	resize(taille_.width()*nb_colonnes(),taille_.height()*nb_lignes());
	repaint(nb_colonnes_*taille_.width(),0,_nb*taille_.width(),nb_lignes_*taille_.height());
}

void GrilleMap::decaler_vers_droite(int _nb_col){
	int largeur_=largeur;
	ajouter_colonnes(_nb_col);
	int nb_lignes_=nb_lignes();
	int nb_colonnes_=nb_colonnes();
	for(int i=nb_colonnes_-1;i>nb_colonnes_-largeur_-1;i--){
		for(int j=0;j<nb_lignes_;j++){
			TuileMap *tuile_=tuile(i,j);
			TuileMap *tuile_2_=tuile(i-_nb_col,j);
			tuile_->affecter(tuile_2_);
		}
	}
	for(int i=nb_colonnes_-largeur_-1;i>-1;i--){
		for(int j=0;j<nb_lignes_;j++){
			TuileMap *tuile_=tuile(i,j);
			tuile_->reinit();
		}
	}
}

int GrilleMap::nb_lignes()const{
	if(largeur==0){
		return 0;
	}
	return tuiles.total()/largeur;
}

int GrilleMap::nb_colonnes()const{
	return largeur;
}

void GrilleMap::paintEvent(QPaintEvent *ev){
	QPainter paint_(this);
	typedef QPair<int,int> Origine;
	QList<Origine> cles_=tuiles.cles();
	QSize taille_;
	foreach(Origine o,cles_){
		TuileMap *t_=tuiles.valeur(o);
		taille_=t_->imag().size();
		paint_.drawImage(QPoint(o.first*taille_.width(),o.second*taille_.height()),t_->imag());
	}
	if(rectangle_nv_env.first>=0){
		paint_.setBrush(QBrush(QColor(0,0,0)));
		paint_.fillRect(rectangle_nv_env.first*taille_.width(),rectangle_nv_env.second*taille_.height(),taille_.width(),taille_.height(),QColor(0,0,0,128));
	}
}

TuileMap *GrilleMap::tuile(int _x,int _y){
	return tuiles.valeur(QPair<int,int>(_x,_y));
}

GrilleMap::~GrilleMap(){
	typedef QPair<int,int> Origine;
	QList<Origine> cles_=tuiles.cles();
	foreach(Origine o,cles_){
		TuileMap *t_=tuiles.valeur(o);
		delete t_;
		t_=NULL;
		tuiles.supprimer_cle_valeur(o);
	}
}



