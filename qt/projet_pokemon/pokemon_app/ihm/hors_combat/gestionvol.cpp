#include "ihm/hors_combat/gestionvol.h"
#include "base_donnees/donnees.h"
#include <QGridLayout>
#include <QMouseEvent>

GestionVol::GestionVol(Donnees* _d){
	donnees=_d;
	QGridLayout *lay_=new QGridLayout();
	lay_->setSpacing(0);
	typedef QPair<int,int> Tuile;
	int l_=0;
	int h_=0;
	foreach(Tuile t,_d->val_images_minimap().cles()){
		QLabel *t_=new QLabel();
		QImage img_=_d->val_elements_map().valeur(_d->val_images_minimap().valeur(t));
		l_=img_.width();
		h_=img_.height();
		t_->setPixmap(QPixmap::fromImage(img_));
		lay_->addWidget(t_,t.second,t.first);
	}
	dims.first=l_;
	dims.second=h_;
	setFixedSize(l_*lay_->columnCount(),h_*lay_->rowCount());
	setLayout(lay_);
}

void GestionVol::mouseReleaseEvent(QMouseEvent *_ev){
	int x_=_ev->x();
	int y_=_ev->y();
	int i_=x_/dims.first;
	int j_=y_/dims.second;
	if(donnees->val_lieux_vols().cles().contains(QPair<int,int>(i_,j_))){
		emit clic(donnees->val_lieux_vols().valeur(QPair<int,int>(i_,j_)));
	}
}
