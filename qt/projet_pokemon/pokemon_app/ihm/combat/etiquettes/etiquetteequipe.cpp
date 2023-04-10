#include "ihm/combat/etiquettes/etiquetteequipe.h"
#include <QMouseEvent>
#include <QPainter>

EtiquetteEquipe::EtiquetteEquipe(uchar _equipe){
	equipe=_equipe;
	choisi=false;
}

void EtiquetteEquipe::maj_choix(bool _choisi){
	choisi=_choisi;
}

void EtiquetteEquipe::redim(){
	setMinimumWidth(20+QFontMetrics(font()).width(text()));
}

void EtiquetteEquipe::mouseReleaseEvent(QMouseEvent *){
	emit clic(equipe);
}

void EtiquetteEquipe::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	paint_.fillRect(0,0,width(),height(),QColor(255,255,255,255));
	if(choisi){
		paint_.fillRect(0,0,8,height(),QColor(255,0,0,255));
	}
	paint_.setPen(QColor(0,0,0,255));
	paint_.drawText(10,font().pointSize(),text());
}
