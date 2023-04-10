#include "ihm/combat/etiquettes/etiquetteattaque.h"
#include <QMouseEvent>
#include <QPainter>

EtiquetteAttaque::EtiquetteAttaque(const QString& _action,const QString& _texte){
	action=_action;
	actif=true;
	choisi=false;
	setText(_texte);
	setFixedHeight(font().pointSize());
	setMinimumWidth(10+QFontMetrics(font()).width(_texte));
}

void EtiquetteAttaque::maj_choix(bool _choisi){
	choisi=_choisi;
}

void EtiquetteAttaque::maj_actif(bool _actif){
	actif=_actif;
}

void EtiquetteAttaque::mouseReleaseEvent(QMouseEvent *){
	if(actif){
		emit clic(action);
	}
}

void EtiquetteAttaque::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	paint_.fillRect(0,0,width(),height(),QColor(255,255,255,255));
	if(choisi){
		paint_.fillRect(0,0,8,height(),QColor(255,0,0,255));
	}
	if(actif){
		paint_.setPen(QColor(0,0,0,255));
	}else{
		paint_.setPen(QColor(127,127,127,255));
	}
	paint_.drawText(10,font().pointSize(),text());
}
