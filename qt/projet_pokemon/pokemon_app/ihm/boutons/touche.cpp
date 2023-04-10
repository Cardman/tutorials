#include "ihm/boutons/touche.h"
#include <QPainter>

Touche::Touche(const QChar& _caractere) : QLabel(){
	setText(_caractere);
	setFixedSize(font().pointSize()*2,font().pointSize()*2);
}

void Touche::maj_couleur_texte(const QColor& _couleur){
	couleur_texte=_couleur;
}

void Touche::maj_couleur_fond(const QColor& _couleur){
	couleur_fond=_couleur;
}

void Touche::maj_couleur_rectangle(const QColor& _couleur){
	couleur_rectangle=_couleur;
}

void Touche::mouseReleaseEvent(QMouseEvent *){
	emit clic(text());
}

void Touche::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	//std::cout<<text().toStdString()<<":"<<QString::number(width()).toStdString()<<";"<<QString::number(height()).toStdString()<<"\n";
	paint_.fillRect(0,0,width(),height(),couleur_fond);//QColor(255,255,255,255)
	paint_.setPen(couleur_texte);// QColor(0,0,255,255)
	paint_.drawText(width()/4,font().pointSize()*3/2,text());
	paint_.setPen(couleur_rectangle);
	paint_.drawRect(0,0,width()-1,height()-1);
	//paint_.drawImage(QPoint(0,0),pixmap()->toImage());
	//std::cout<<QString::number(font().pointSize()).toStdString()<<"\n";
}
