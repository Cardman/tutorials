#include "ihm/boutons/boutonchoix.h"
#include <QPainter>

BoutonChoix::BoutonChoix(){
	choisi=false;
}

void BoutonChoix::maj_choix(bool _choisi){
	choisi=_choisi;
}

void BoutonChoix::maj_texte(const QString& _texte){
	QFont fond_=font();
	fond_.setPointSize(20);
	setText(_texte);
	setFixedHeight(2*fond_.pointSize());
	QFontMetrics fond_m_(fond_);
	setMinimumWidth(10+fond_m_.width(_texte));
	setFont(fond_);
}

void BoutonChoix::maj_couleur_texte(const QColor& _couleur){
	couleur_texte=_couleur;
}

void BoutonChoix::maj_couleur_choix(const QColor& _couleur){
	couleur_choix=_couleur;
}

void BoutonChoix::maj_couleur_fond(const QColor& _couleur){
	couleur_fond=_couleur;
}

void BoutonChoix::maj_couleur_rectangle(const QColor& _couleur){
	couleur_rectangle=_couleur;
}


void BoutonChoix::mouseReleaseEvent(QMouseEvent *){
	choisi=!choisi;
	repaint();
	emit clic(choisi);
}

void BoutonChoix::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	paint_.fillRect(0,0,width(),height(),couleur_fond);//QColor(255,255,255,255)
	if(choisi){
		paint_.fillRect(0,0,8,height(),couleur_choix);
	}
	paint_.setPen(couleur_texte);// QColor(0,0,255,255)
	paint_.drawText(10,font().pointSize()*3/2,text());
	paint_.setPen(couleur_rectangle);
	paint_.drawRect(0,0,width()-1,height()-1);
	//paint_.drawImage(QPoint(0,0),pixmap()->toImage());
}
