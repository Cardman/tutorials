#include "ihm/combat/etiquettes/etiquetteposition.h"
#include <QPainter>

EtiquettePosition::EtiquettePosition(int _equipe,int _position,int _arriere,int _equipe_ut){
	position.first=_equipe;
	position.second=_position;
	QString texte_;
	if(_equipe==_equipe_ut){
		texte_+="EQUIPE DU JOUEUR, ";
	}else{
		texte_+="EQUIPE ADVERSE, ";
	}
	if(_position!=_arriere){
		texte_+="position: "+QString::number(_position);
	}else{
		texte_+="position arriere";
	}
	setText(texte_);
	setFixedHeight(font().pointSize());
	setMinimumWidth(10+QFontMetrics(font()).width(text()));
	choisi=false;
}

void EtiquettePosition::mouseReleaseEvent(QMouseEvent *){
	emit clic(position);
}

void EtiquettePosition::maj_choix(bool _choix){
	choisi=_choix;
}

void EtiquettePosition::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	paint_.fillRect(0,0,width(),height(),QColor(255,255,255,255));
	if(choisi){
		paint_.fillRect(0,0,8,height(),QColor(255,0,0,255));
	}
	paint_.setPen(QColor(0,0,0,255));
	paint_.drawText(10,font().pointSize(),text());
}
