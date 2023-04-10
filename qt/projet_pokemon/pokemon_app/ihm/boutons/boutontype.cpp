#include "ihm/boutons/boutontype.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

BoutonType::BoutonType(const QString& _texte,uchar _type){
	maj_texte(_texte);
	type_action=_type;
}

void BoutonType::maj_texte(const QString& _texte){
	QFont fond_=font();
	fond_.setPointSize(20);
	setText(_texte);
	setFixedHeight(2*fond_.pointSize());
	setMinimumWidth(_texte.size()*20);
	setFont(fond_);
}

void BoutonType::maj_couleur_texte(const QColor& _couleur){
	couleur_texte=_couleur;
}

void BoutonType::maj_couleur_fond(const QColor& _couleur){
	couleur_fond=_couleur;
}

void BoutonType::maj_couleur_rectangle(const QColor& _couleur){
	couleur_rectangle=_couleur;
}


void BoutonType::mouseReleaseEvent(QMouseEvent *){
	emit clic(type_action);
}

void BoutonType::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	paint_.fillRect(0,0,width(),height(),couleur_fond);//QColor(255,255,255,255)
	paint_.setPen(couleur_texte);// QColor(0,0,255,255)
	paint_.drawText(0,font().pointSize()*3/2,text());
	paint_.setPen(couleur_rectangle);
	paint_.drawRect(0,0,width()-1,height()-1);
	//paint_.drawImage(QPoint(0,0),pixmap()->toImage());
}
