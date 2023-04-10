#include "ihm/grilles/grilledialogue.h"
#include "pseudo_ihm/tuilegraphique.h"
#include <QGridLayout>
#include <QPainter>
#include <QMouseEvent>

GrilleDialogue::GrilleDialogue():QLabel(){
	largeur=0;
	coordonnees=QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(0,0),QPair<int,int>(0,0));
}

void GrilleDialogue::table_rase(){
	typedef QPair<int,int> Origine;
	foreach(Origine o,tuiles.cles()){
		tuiles.valeur(o)->reinit();
		liens_lieux.ajouter_cle_valeur(o,GrilleDialogue::RIEN);
	}
	repaint();
}

void GrilleDialogue::reinit_liens(){
	typedef QPair<int,int> Origine;
	foreach(Origine o,tuiles.cles()){
		liens_lieux.ajouter_cle_valeur(o,GrilleDialogue::RIEN);
	}
}

void GrilleDialogue::init(){
	TuileGraphique *tuile_=new TuileGraphique(QPair<int,int>(0,0));
	tuiles.ajouter_cle_valeur(QPair<int,int>(0,0),tuile_);
	liens_lieux.ajouter_cle_valeur(QPair<int,int>(0,0),GrilleDialogue::RIEN);
	repaint();
	resize(tuile_->imag().size());
	largeur=1;
}

void GrilleDialogue::mouseReleaseEvent(QMouseEvent* _event){
	QPoint pos_=_event->pos();
	if(tuiles.total()>0){
		QSize taille_=tuiles.valeur(QPair<int,int>(0,0))->imag().size();
		int x_=pos_.x()/taille_.width();
		int y_=pos_.y()/taille_.height();
		if(x_<largeur&&y_<nb_lignes()){
			QPair<int,int> coords_tuile_=tuiles.valeur(QPair<int,int>(x_,y_))->coords();
			QPair<int,int> coords_env_=QPair<int,int>(x_-coords_tuile_.first,y_-coords_tuile_.second);
			coordonnees=QPair<QPair<int,int>,QPair<int,int> >(coords_env_,coords_tuile_);
			emit selection(coordonnees);
		}
	}
}

void GrilleDialogue::ajouter_lignes(int _nb){
	int nb_lignes_=nb_lignes();
	int nb_colonnes_=nb_colonnes();
	for(int j=0;j<_nb;j++){
		for(int i=0;i<nb_colonnes_;i++){
			TuileGraphique *tuile_=new TuileGraphique(QPair<int,int>(0,0));
			tuiles.ajouter_cle_valeur(QPair<int,int>(i,nb_lignes_+j),tuile_);
			liens_lieux.ajouter_cle_valeur(QPair<int,int>(i,nb_lignes_+j),GrilleDialogue::RIEN);
		}
	}
	QSize taille_=tuile(0,0)->imag().size();
	resize(taille_.width()*nb_colonnes(),taille_.height()*nb_lignes());
	repaint(0,nb_lignes_*taille_.height(),nb_colonnes_*taille_.width(),_nb*taille_.height());
}

void GrilleDialogue::ajouter_colonnes(int _nb){
	int nb_lignes_=nb_lignes();
	int nb_colonnes_=nb_colonnes();
	for(int j=0;j<_nb;j++){
		for(int i=0;i<nb_lignes_;i++){
			TuileGraphique *tuile_=new TuileGraphique(QPair<int,int>(0,0));
			tuiles.ajouter_cle_valeur(QPair<int,int>(nb_colonnes_+j,i),tuile_);
			liens_lieux.ajouter_cle_valeur(QPair<int,int>(nb_colonnes_+j,i),GrilleDialogue::RIEN);
		}
	}
	largeur+=_nb;
	QSize taille_=tuile(0,0)->imag().size();
	resize(taille_.width()*nb_colonnes(),taille_.height()*nb_lignes());
	repaint(nb_colonnes_*taille_.width(),0,_nb*taille_.width(),nb_lignes_*taille_.height());
}

int GrilleDialogue::nb_lignes()const{
	if(largeur==0){
		return 0;
	}
	return tuiles.total()/largeur;
}

int GrilleDialogue::nb_colonnes()const{
	return largeur;
}

void GrilleDialogue::maj_dir_lieux(int _dir,int _position,int _longueur){
	if(_dir==GrilleDialogue::GAUCHE){
		for(int i=0;i<_longueur;i++){
			liens_lieux.ajouter_cle_valeur(QPair<int,int>(0,i+_position),_dir);
		}
	}else if(_dir==GrilleDialogue::DROITE){
		for(int i=0;i<_longueur;i++){
			liens_lieux.ajouter_cle_valeur(QPair<int,int>(largeur-1,i+_position),_dir);
		}
	}else if(_dir==GrilleDialogue::HAUT){
		for(int i=0;i<_longueur;i++){
			liens_lieux.ajouter_cle_valeur(QPair<int,int>(i+_position,0),_dir);
		}
	}else if(_dir==GrilleDialogue::BAS){
		int nb_l_=nb_lignes();
		for(int i=0;i<_longueur;i++){
			liens_lieux.ajouter_cle_valeur(QPair<int,int>(i+_position,nb_l_-1),_dir);
		}
	}
}

void GrilleDialogue::maj_liens_plateau_ligue(QPair<QPair<int,int>,QPair<int,int> >* _or,QPair<QPair<int,int>,QPair<int,int> >* _dest){
	if(_or!=NULL){
		liens_lieux.ajouter_cle_valeur(QPair<int,int>(_or->first.first+_or->second.first,_or->first.second+_or->second.second),GrilleDialogue::BAS);
	}
	if(_dest->first.first>0){
		liens_lieux.ajouter_cle_valeur(QPair<int,int>(_dest->first.first+_dest->second.first,_dest->first.second+_dest->second.second),GrilleDialogue::HAUT);
	}
}

void GrilleDialogue::maj_liens_plateau_ligue(const QPair<QPair<int,int>,QPair<int,int> >& _or,QPair<QPair<int,int>,QPair<int,int> >* _dest){
	liens_lieux.ajouter_cle_valeur(QPair<int,int>(_or.first.first+_or.second.first,_or.first.second+_or.second.second),GrilleDialogue::BAS);
	if(_dest->first.first>0){
		liens_lieux.ajouter_cle_valeur(QPair<int,int>(_dest->first.first+_dest->second.first,_dest->first.second+_dest->second.second),GrilleDialogue::HAUT);
	}
}

void GrilleDialogue::maj_liens_plateau_ligue(QPair<QPair<int,int>,QPair<int,int> >* _or,const QPair<QPair<int,int>,QPair<int,int> >& _dest){
	if(_or!=NULL){
		liens_lieux.ajouter_cle_valeur(QPair<int,int>(_or->first.first+_or->second.first,_or->first.second+_or->second.second),GrilleDialogue::BAS);
	}
	if(_dest.first.first>0){
		liens_lieux.ajouter_cle_valeur(QPair<int,int>(_dest.first.first+_dest.second.first,_dest.first.second+_dest.second.second),GrilleDialogue::HAUT);
	}
}

void GrilleDialogue::maj_liens_plateau_ligue(const QPair<QPair<int,int>,QPair<int,int> >& _or,const QPair<QPair<int,int>,QPair<int,int> >& _dest){
	liens_lieux.ajouter_cle_valeur(QPair<int,int>(_or.first.first+_or.second.first,_or.first.second+_or.second.second),GrilleDialogue::BAS);
	if(_dest.first.first>0){
		liens_lieux.ajouter_cle_valeur(QPair<int,int>(_dest.first.first+_dest.second.first,_dest.first.second+_dest.second.second),GrilleDialogue::HAUT);
	}
}

void GrilleDialogue::paintEvent(QPaintEvent *ev){
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
		if(t_->cond_ligue()){
			paint_.drawEllipse(o.first*taille_.width(),o.second*taille_.height(),taille_.width(),taille_.height());
		}
		int dir_lien_=liens_lieux.valeur(o);
		if(dir_lien_!=GrilleDialogue::RIEN){
			//rotate:degres, horaire
			paint_.setPen(QColor(0,0,0,128));
			paint_.drawRect(o.first*taille_.width(),o.second*taille_.height(),taille_.width(),taille_.height());
		}
		if(dir_lien_==GrilleDialogue::GAUCHE||dir_lien_==GrilleDialogue::DROITE){
			paint_.setPen(QColor(0,0,0,128));
			paint_.drawLine(o.first*taille_.width(),o.second*taille_.height()+taille_.height()/2,(o.first+1)*taille_.width(),o.second*taille_.height()+taille_.height()/2);//taille_.width(),0)
		}
		if(dir_lien_==GrilleDialogue::HAUT||dir_lien_==GrilleDialogue::BAS){
			paint_.setPen(QColor(0,0,0,128));
			//paint_.drawLine(o.first*taille_.width()+taille_.width()/2,o.second*taille_.height(),0,taille_.height())
			paint_.drawLine(o.first*taille_.width()+taille_.width()/2,o.second*taille_.height(),o.first*taille_.width()+taille_.width()/2,(o.second+1)*taille_.height());
		}
		if(dir_lien_==GrilleDialogue::GAUCHE||dir_lien_==GrilleDialogue::HAUT){
			paint_.setPen(QColor(0,0,0,128));
			//paint_.drawLine(o.first*taille_.width(),o.second*taille_.height()+taille_.height()/2,taille_.width()/2,-taille_.height()/2)
			paint_.drawLine(o.first*taille_.width(),o.second*taille_.height()+taille_.height()/2,o.first*taille_.width()+taille_.width()/2,o.second*taille_.height());
		}
		if(dir_lien_==GrilleDialogue::DROITE||dir_lien_==GrilleDialogue::BAS){
			paint_.setPen(QColor(0,0,0,128));
			//paint_.drawLine(o.first*taille_.width()+taille_.width()/2,(1+o.second)*taille_.height(),taille_.width()/2,-taille_.height()/2)
			paint_.drawLine(o.first*taille_.width()+taille_.width()/2,(1+o.second)*taille_.height(),(o.first+1)*taille_.width(),o.second*taille_.height()+taille_.height()/2);
		}
		if(dir_lien_==GrilleDialogue::GAUCHE||dir_lien_==GrilleDialogue::BAS){
			paint_.setPen(QColor(0,0,0,128));
			//paint_.drawLine(o.first*taille_.width(),o.second*taille_.height()+taille_.height()/2,taille_.width()/2,taille_.height()/2)
			paint_.drawLine(o.first*taille_.width(),o.second*taille_.height()+taille_.height()/2,o.first*taille_.width()+taille_.width()/2,(o.second+1)*taille_.height());
		}
		if(dir_lien_==GrilleDialogue::DROITE||dir_lien_==GrilleDialogue::HAUT){
			paint_.setPen(QColor(0,0,0,128));
			//paint_.drawLine(o.first*taille_.width()+taille_.width()/2,o.second*taille_.height(),taille_.width()/2,taille_.height()/2)
			paint_.drawLine(o.first*taille_.width()+taille_.width()/2,o.second*taille_.height(),(o.first+1)*taille_.width(),o.second*taille_.height()+taille_.height()/2);
		}
	}
}

TuileGraphique *GrilleDialogue::tuile(int _x,int _y){
	return tuiles.valeur(QPair<int,int>(_x,_y));
}

GrilleDialogue::~GrilleDialogue(){
	typedef QPair<int,int> Origine;
	QList<Origine> cles_=tuiles.cles();
	foreach(Origine o,cles_){
		TuileGraphique *t_=tuiles.valeur(o);
		delete t_;
		t_=NULL;
		tuiles.supprimer_cle_valeur(o);
	}
}



