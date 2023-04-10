#include "ihm/boutons/choixheros.h"
#include "base_donnees/donnees.h"
#include <QPainter>

ChoixHeros::ChoixHeros(const QString& _sexe,Donnees* _d) : QLabel(){
	sexe=_sexe;
	QImage img_=_d->val_debut_heros().valeur(_sexe);
	setFixedSize(img_.size());
	setPixmap(QPixmap::fromImage(img_));
	choix=false;
}

void ChoixHeros::maj_choix(bool _choix){
	choix=_choix;
}

void ChoixHeros::mouseReleaseEvent(QMouseEvent *){
	emit clic(sexe);
}

void ChoixHeros::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	paint_.fillRect(0,0,width(),height(),QColor(255,255,255,255));
	paint_.drawImage(QPoint(0,0),pixmap()->toImage());
	if(choix){
		paint_.setPen(QColor(0,0,0,255));
		paint_.drawRect(0,0,width()-2,height()-1);
	}
}
