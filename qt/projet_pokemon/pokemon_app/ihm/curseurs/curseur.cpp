#include "ihm/curseurs/curseur.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>

Curseur::Curseur(int _orientation,int _taille){
	taille=_taille;
	orientation=_orientation;
	if(_orientation==Qt::Vertical){
		setFixedHeight(_taille);
		setFixedWidth(20);
	}else{
		setFixedWidth(_taille);
		setFixedHeight(20);
	}
	maxi=_taille/4-1;
	mini=0;
	//maj_intervalle(0,_taille/4-1);
	maj_valeur(0);
}

void Curseur::maj_intervalle(int _min,int _max){
	taille=taille*(_max+1-_min)/(maxi+1-mini);
	maxi=_max;
	mini=_min;
	if(orientation==Qt::Vertical){
		setFixedHeight(taille);
	}else{
		setFixedWidth(taille);
	}
	/*if((maxi+1-mini)*2>=taille){
		taille*=2;
		if(_orientation==Qt::Vertical){
			setFixedHeight(taille);
		}else{
			setFixedWidth(taille);
		}
	}*/
	repaint();
}

void Curseur::maj_valeur(int _valeur){
	valeur=_valeur;
	repaint();
}

void Curseur::traiter_event(QMouseEvent* _ev){
	int pos_=0;
	if(orientation==Qt::Horizontal){
		pos_=_ev->x();
	}else{
		pos_=_ev->y();
	}
	pos_=pos_*(maxi+1-mini)/taille;
	pos_+=mini;
	if(pos_>maxi){
		return;
	}
	if(pos_<mini){
		return;
	}
	maj_valeur(pos_);
	emit nouvelle_valeur(pos_);
}

void Curseur::mouseReleaseEvent(QMouseEvent *_ev){
	traiter_event(_ev);
}

void Curseur::mouseMoveEvent(QMouseEvent* _ev){
	traiter_event(_ev);
}

void Curseur::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	int pos_=(valeur-mini)*taille/(maxi+1-mini);
	if(orientation==Qt::Horizontal){
		paint_.fillRect(0,3,width(),4,QColor(0,0,0,255));
		paint_.fillRect(pos_,0,taille/(maxi+1-mini),10,QColor(255,0,0,255));
		paint_.setPen(QColor(0,0,255,255));
		paint_.drawText(0,height(),QString::number(mini));
		int l_=QFontMetrics(font()).width(QString::number(valeur));
		paint_.drawText((width()-l_)/2,height(),QString::number(valeur));
		l_=QFontMetrics(font()).width(QString::number(maxi));
		paint_.drawText(width()-l_,height(),QString::number(maxi));
	}else{
		paint_.fillRect(3,0,4,height(),QColor(0,0,0,255));
		paint_.fillRect(0,pos_,10,taille/(maxi+1-mini),QColor(255,0,0,255));
		paint_.setPen(QColor(0,0,255,255));
		int h_=QFontMetrics(font()).height();
		paint_.drawText(10,20,QString::number(mini));
		paint_.drawText(10,(height()+h_)/2,QString::number(valeur));
		paint_.drawText(10,height(),QString::number(maxi));
	}
}


