#include "ihm/grilles/grille.h"
#include "pseudo_ihm/tuilegraphique.h"
#include <QGridLayout>
#include <QPainter>
#include <QMouseEvent>

Grille::Grille():QLabel(){
	largeur=0;
	rectangle_nv_env=QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(0,0),QPair<int,int>(-1,-1));
}

void Grille::table_rase(){
	typedef QPair<int,int> Origine;
	foreach(Origine o,tuiles.cles()){
		tuiles.valeur(o)->reinit();
	}
	repaint();
}

void Grille::init(){
	TuileGraphique *tuile_=new TuileGraphique(QPair<int,int>(0,0));
	tuiles.ajouter_cle_valeur(QPair<int,int>(0,0),tuile_);
	repaint();
	resize(tuile_->imag().size());
	largeur=1;
}

void Grille::mouseReleaseEvent(QMouseEvent* _event){
	QPoint pos_=_event->pos();
	if(tuiles.total()>0){
		QSize taille_=tuiles.valeur(QPair<int,int>(0,0))->imag().size();
		int x_=pos_.x()/taille_.width();
		int y_=pos_.y()/taille_.height();
		if(x_<largeur&&y_<nb_lignes()){
			QPair<int,int> coords_tuile_=tuiles.valeur(QPair<int,int>(x_,y_))->coords();
			QPair<int,int> coords_env_=QPair<int,int>(x_-coords_tuile_.first,y_-coords_tuile_.second);
			emit selection(QPair<QPair<int,int>,QPair<int,int> >(coords_env_,coords_tuile_));
		}
	}
}

void Grille::ajouter_lignes(int _nb){
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

void Grille::decaler_vers_bas(int _nb_lgs){
	int hauteur_=nb_lignes();
	ajouter_lignes(_nb_lgs);
	int nb_lignes_=nb_lignes();
	int nb_colonnes_=nb_colonnes();
	for(int i=nb_lignes_-1;i>nb_lignes_-hauteur_-1;i--){
		for(int j=0;j<nb_colonnes_;j++){
			TuileGraphique *tuile_=tuile(j,i);
			TuileGraphique *tuile_2_=tuile(j,i-_nb_lgs);
			tuile_->affecter(tuile_2_);
		}
	}
	for(int i=nb_lignes_-hauteur_-1;i>-1;i--){
		for(int j=0;j<nb_colonnes_;j++){
			TuileGraphique *tuile_=tuile(j,i);
			tuile_->reinit();
		}
	}
}

void Grille::ajouter_colonnes(int _nb){
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

void Grille::decaler_vers_droite(int _nb_col){
	int largeur_=largeur;
	ajouter_colonnes(_nb_col);
	int nb_lignes_=nb_lignes();
	int nb_colonnes_=nb_colonnes();
	for(int i=nb_colonnes_-1;i>nb_colonnes_-largeur_-1;i--){
		for(int j=0;j<nb_lignes_;j++){
			TuileGraphique *tuile_=tuile(i,j);
			TuileGraphique *tuile_2_=tuile(i-_nb_col,j);
			tuile_->affecter(tuile_2_);
		}
	}
	for(int i=nb_colonnes_-largeur_-1;i>-1;i--){
		for(int j=0;j<nb_lignes_;j++){
			TuileGraphique *tuile_=tuile(i,j);
			tuile_->reinit();
		}
	}
}

int Grille::nb_lignes()const{
	if(largeur==0){
		return 0;
	}
	return tuiles.total()/largeur;
}

int Grille::nb_colonnes()const{
	return largeur;
}

void Grille::affecter_rectangle_nv_env(const QPair<QPair<int,int>,QPair<int,int> >& _rect){
	rectangle_nv_env=_rect;
}

void Grille::paintEvent(QPaintEvent *ev){
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
	if(rectangle_nv_env.second.first>0){
		paint_.setBrush(QBrush(QColor(0,0,0)));
		paint_.fillRect(rectangle_nv_env.first.first,rectangle_nv_env.first.second,rectangle_nv_env.second.first,rectangle_nv_env.second.second,QColor(0,0,0,128));
	}
}

TuileGraphique *Grille::tuile(int _x,int _y){
	return tuiles.valeur(QPair<int,int>(_x,_y));
}

Grille::~Grille(){
	typedef QPair<int,int> Origine;
	QList<Origine> cles_=tuiles.cles();
	foreach(Origine o,cles_){
		TuileGraphique *t_=tuiles.valeur(o);
		delete t_;
		t_=NULL;
		tuiles.supprimer_cle_valeur(o);
	}
}



