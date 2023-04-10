#include "ihm/combat/etiquettes/etiquettecreatcombat.h"
#include "ihm/combat/etiquettes/barre.h"
#include "serialisable/combat/creaturecombat.h"
#include "base_donnees/donnees.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QPainter>

EtiquetteCreatCombat::EtiquetteCreatCombat(const Combattant& _combattant,const CreatureCombat& _cr_c,Donnees *_d){
	combattant=_combattant;
	QHBoxLayout *lay_=new QHBoxLayout();
	QVBoxLayout *lay_2_=new QVBoxLayout();
	ico_pk=new QLabel();
	ico_pk->setPixmap(QPixmap::fromImage(_d->val_miniatures().valeur(_cr_c.fiche_pokemon(_d)->num())));
	lay_2_->addWidget(ico_pk);
	ico_ball=new QLabel();
	if(_cr_c.ball_capt()!=""){
		ico_ball->setPixmap(QPixmap::fromImage(_d->val_images_objets().valeur(_cr_c.ball_capt())));
	}else if(_combattant.equipe()==_d->val_ut()){
		ico_ball->setPixmap(QPixmap::fromImage(_d->val_images_objets().valeur("POKE_BALL")));
	}
	lay_2_->addWidget(ico_ball);
	lay_->addLayout(lay_2_);
	lay_2_=new QVBoxLayout();
	QHBoxLayout *lay_3_=new QHBoxLayout();
	nom_pk=new QLabel(_cr_c.nom_pk_act());
	lay_3_->addWidget(nom_pk);
	genre_pk=new QLabel(QString(_cr_c.genre_pk()[0]));
	lay_3_->addWidget(genre_pk);
	uchar niv_=_cr_c.niveau_pk();
	niveau_pk=new QLabel(QString::number(niv_));
	lay_3_->addWidget(niveau_pk);
	lay_2_->addLayout(lay_3_);
	lay_3_=new QHBoxLayout();
	barre_vie=new Barre(QColor(0,128,0,255));
	Taux pv_rest_=_cr_c.pv_restants_pk();
	Taux pv_max_=_cr_c.pv_max();
	barre_vie->maj_pourcent(pv_rest_/pv_max_);
	lay_3_->addWidget(barre_vie);
	lay_2_->addLayout(lay_3_);
	lay_3_=new QHBoxLayout();
	pv_pk=new QLabel(pv_rest_.evaluer(3)+"/"+pv_max_.evaluer(3));
	lay_3_->addWidget(pv_pk);
	statut_pk=new QLabel(_cr_c.statut_pk());
	lay_3_->addWidget(statut_pk);
	lay_2_->addLayout(lay_3_);
	lay_3_=new QHBoxLayout();
	barre_pts=new Barre(QColor(0,0,255,255));
	Taux nb_pts_total_dem_=_cr_c.fiche_pokemon_b(_d)->diff_pts_niveaux(niv_+1);
	Taux nb_pts_restants_=nb_pts_total_dem_-_cr_c.exp_gagnee();
	barre_pts->maj_pourcent(nb_pts_restants_/nb_pts_total_dem_);
	lay_3_->addWidget(barre_pts);
	lay_2_->addLayout(lay_3_);
	lay_3_=new QHBoxLayout();
	pts_pk=new QLabel(nb_pts_restants_.evaluer(3)+"/"+nb_pts_total_dem_.evaluer(3));
	lay_3_->addWidget(pts_pk);
	lay_2_->addLayout(lay_3_);
	lay_->addLayout(lay_2_);
	setLayout(lay_);
	choisi=false;
	valide=true;
	setMinimumSize(100,100);
}

EtiquetteCreatCombat::EtiquetteCreatCombat(){
	ico_pk=NULL;
	ico_ball=NULL;
	nom_pk=NULL;
	genre_pk=NULL;
	niveau_pk=NULL;
	barre_vie=NULL;
	pv_pk=NULL;
	statut_pk=NULL;
	barre_pts=NULL;
	pts_pk=NULL;
	choisi=false;
	valide=false;
	setMinimumSize(100,100);
}

void EtiquetteCreatCombat::maj_choix(bool _choix){
	choisi=_choix;
}

void EtiquetteCreatCombat::mouseReleaseEvent(QMouseEvent *){
	emit clic(combattant);
}

void EtiquetteCreatCombat::maj_ico_pk(const QImage& _img){
	ico_pk->setPixmap(QPixmap::fromImage(_img));
}

void EtiquetteCreatCombat::maj_ico_ball(const QImage& _img){
	ico_ball->setPixmap(QPixmap::fromImage(_img));
}

void EtiquetteCreatCombat::maj_nom_pk(const QString& _nom){
	nom_pk->setText(_nom);
}

void EtiquetteCreatCombat::maj_genre_pk(const QString& _genre){
	genre_pk->setText(_genre);
}

void EtiquetteCreatCombat::maj_niveau_pk(uchar _niveau){
	niveau_pk->setText(QString::number(_niveau));
}

void EtiquetteCreatCombat::maj_pv_pk(const Taux& _pv_r,const Taux& _pv_m){
	Taux tx_=_pv_r/_pv_m;
	if(tx_>=Taux(1LL,2LL)){
		barre_vie->maj_couleur(QColor(0,128,0,255));
	}else if(tx_>=Taux(1LL,4LL)){
		barre_vie->maj_couleur(QColor(255,128,0,255));
	}else{
		barre_vie->maj_couleur(QColor(128,0,0,255));
	}
	barre_vie->maj_pourcent(tx_);
	barre_vie->repaint();
	pv_pk->setText(_pv_r.evaluer(3)+"/"+_pv_m.evaluer(3));
}

void EtiquetteCreatCombat::maj_pts_pk(const Taux& _pts_r,const Taux& _pts_m){
	barre_pts->maj_pourcent(_pts_r/_pts_m);
	barre_pts->repaint();
	pts_pk->setText(_pts_r.evaluer(3)+"/"+_pts_m.evaluer(3));
}

void EtiquetteCreatCombat::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	if(choisi){
		paint_.setPen(QColor(255,0,0,255));
	}else{
		paint_.setPen(QColor(0,0,0,255));
	}
	if(!valide){
		paint_.fillRect(0,0,width(),height(),QColor(255,255,255,255));
	}
	paint_.drawRect(0,0,width()-1,height()-1);
}
