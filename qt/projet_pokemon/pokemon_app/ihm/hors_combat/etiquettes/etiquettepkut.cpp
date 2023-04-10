#include "ihm/hors_combat/etiquettes/etiquettepkut.h"
#include "ihm/combat/etiquettes/barre.h"
#include "serialisable/pokemon/pokemonutilisateur.h"
#include "base_donnees/donnees.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QPainter>

EtiquettePkUt::EtiquettePkUt(uchar _position,const PokemonUtilisateur& _pk,Donnees* _d,const QString& _apte){
	position=_position;
	QHBoxLayout *lay_=new QHBoxLayout();
	lay_->setSpacing(0);
	QVBoxLayout *lay_2_=new QVBoxLayout();
	ico_pk=new QLabel();
	FichePokemon *f_pk_=_d->val_pokedex().valeur(_pk.n_pk());
	ico_pk->setPixmap(QPixmap::fromImage(_d->val_miniatures().valeur(f_pk_->num())));
	lay_2_->addWidget(ico_pk);
	ico_ball=new QLabel();
	if(_pk.ball_capt()!=""){
		ico_ball->setPixmap(QPixmap::fromImage(_d->val_images_objets().valeur(_pk.ball_capt())));
	}else{
		ico_ball->setPixmap(QPixmap::fromImage(_d->val_images_objets().valeur("POKE_BALL")));
	}
	lay_2_->addWidget(ico_ball);
	lay_->addLayout(lay_2_);
	lay_2_=new QVBoxLayout();
	QHBoxLayout *lay_3_=new QHBoxLayout();
	nom_pk=new QLabel(_pk.n_pk());
	lay_3_->addWidget(nom_pk);
	genre_pk=new QLabel(QString(_pk.genre_pk()[0]));
	lay_3_->addWidget(genre_pk);
	uchar niv_=_pk.niv_pk();
	niveau_pk=new QLabel(QString::number(niv_));
	lay_3_->addWidget(niveau_pk);
	lay_2_->addLayout(lay_3_);
	lay_3_=new QHBoxLayout();
	barre_vie=new Barre(QColor(0,128,0,255));
	Taux pv_rest_=_pk.pv_rest();
	Taux pv_max_=f_pk_->stat(_pk.niv_pk(),"PV",_pk.ev_stat().valeur("PV"),_pk.iv_stat().valeur("PV"));
	barre_vie->maj_pourcent(pv_rest_/pv_max_);
	lay_3_->addWidget(barre_vie);
	lay_2_->addLayout(lay_3_);
	lay_3_=new QHBoxLayout();
	pv_pk=new QLabel(pv_rest_.evaluer(3)+"/"+pv_max_.evaluer(3));
	lay_3_->addWidget(pv_pk);
	statut_pk=new QLabel(_pk.statut_pk());
	lay_3_->addWidget(statut_pk);
	lay_2_->addLayout(lay_3_);
	lay_3_=new QHBoxLayout();
	barre_pts=new Barre(QColor(0,0,255,255));
	Taux nb_pts_total_dem_=f_pk_->diff_pts_niveaux(niv_+1);
	Taux nb_pts_restants_=nb_pts_total_dem_-_pk.exp_gagne();
	barre_pts->maj_pourcent(nb_pts_restants_/nb_pts_total_dem_);
	lay_3_->addWidget(barre_pts);
	lay_2_->addLayout(lay_3_);
	lay_3_=new QHBoxLayout();
	pts_pk=new QLabel(nb_pts_restants_.evaluer(3)+"/"+nb_pts_total_dem_.evaluer(3));
	lay_3_->addWidget(pts_pk);
	lay_2_->addLayout(lay_3_);
	objet_pk=new QLabel();
	objet_pk->setText("objet: "+_pk.objet());
	lay_2_->addWidget(objet_pk);
	if(_apte==""){
		choisi=false;
		setFixedHeight(150);
	}else{
		lay_2_->addWidget(new QLabel(_apte));
		choisi=false;
		setFixedHeight(190);
	}
	lay_->addLayout(lay_2_);
	setLayout(lay_);
	setMinimumWidth(170);
	setMaximumWidth(190);

}

void EtiquettePkUt::mouseReleaseEvent(QMouseEvent *){
	emit clic(position);
}

void EtiquettePkUt::maj_choix(bool _choix){
	choisi=_choix;
}

void EtiquettePkUt::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	if(choisi){
		paint_.setPen(QColor(255,0,0,255));
	}else{
		paint_.setPen(QColor(0,0,0,255));
	}
	paint_.drawRect(0,0,width()-1,height()-1);
}
