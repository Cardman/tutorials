#include "ihm/combat/etiquettes/barre.h"
#include <QPainter>

Barre::Barre(const QColor& _couleur){
	maj_pourcent(Taux(1));
	maj_couleur(_couleur);
	QFont style_=font();
	style_.setPointSize(10);
	setFont(style_);
	setFixedHeight(15);
}

void Barre::maj_couleur(const QColor& _couleur){
	couleur=_couleur;
}

void Barre::maj_pourcent(const Taux& _taux){
	pourcent=_taux;
	texte=QString::number(pourcent*Taux(100))+" %";
}

void Barre::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	int police_=font().pointSize();
	paint_.setPen(couleur);
	paint_.drawText(0,police_,texte);
	int h_=2;
	int xh_=height()-h_;
	paint_.fillRect(0,xh_,Taux(width())*pourcent,h_,couleur);
}
