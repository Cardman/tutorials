#include "ihm/hors_combat/etiquettes/miniature.h"
#include "base_donnees/donnees.h"
#include <QPainter>

Miniature::Miniature(const QPair<uchar,uchar>& _position,Donnees *_d){
	position=_position;
	vide=true;
	valide=false;
	choisi=false;
	setPixmap(QPixmap());
	int pr_=_d->val_miniatures().cles()[0];
	setFixedSize(_d->val_miniatures().valeur(pr_).size());
}

void Miniature::maj_choix(bool _choix){
	choisi=_choix;
}

void Miniature::maj_miniature(int _numero,Donnees* _d){
	vide=_numero==-1;
	oeuf=_numero==0;
	valide=_numero>=-1;
	if(!vide){
		setPixmap(QPixmap::fromImage(_d->val_miniatures().valeur(_numero)));
	}else{
		setPixmap(QPixmap());
	}
}

void Miniature::mouseReleaseEvent(QMouseEvent *){
	if(valide){
		emit clic(position,oeuf,vide);
	}
}

void Miniature::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	paint_.fillRect(0,0,width()-1,height()-1,QColor(255,255,255,255));
	paint_.drawImage(QPoint(0,0),pixmap()->toImage());
	if(choisi){
		paint_.setPen(QColor(255,0,0,255));
		paint_.drawRect(0,0,width()-1,height()-1);
	}
}
