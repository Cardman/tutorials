#include "bouton.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

Bouton::Bouton(){
	action="";
	sous_action=-1;
}

Bouton::Bouton(const QString& _texte){
	maj_texte(_texte);
	action=_texte;
	sous_action=-1;
}

Bouton::Bouton(const QString& _texte,int _sous_action){
	maj_texte(_texte);
	action=_texte;
	sous_action=_sous_action;
}

void Bouton::maj_texte(const QString& _texte){
	QFont fond_=font();
	fond_.setPointSize(20);
	setText(_texte);
	setFixedHeight(2*fond_.pointSize());
	QFontMetrics fond_m_(fond_);
	setMinimumWidth(fond_m_.width(_texte));
	setFont(fond_);
}

void Bouton::maj_couleur_texte(const QColor& _couleur){
	couleur_texte=_couleur;
}

void Bouton::maj_couleur_fond(const QColor& _couleur){
	couleur_fond=_couleur;
}

void Bouton::maj_couleur_rectangle(const QColor& _couleur){
	couleur_rectangle=_couleur;
}


void Bouton::mouseReleaseEvent(QMouseEvent *){
	if(sous_action==-1){
		if(action==""){
			emit clic();
		}else{
			emit clic(action);
		}
	}else{
		emit clic(action,sous_action);
	}
}

void Bouton::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	paint_.fillRect(0,0,width(),height(),couleur_fond);//QColor(255,255,255,255)
	paint_.setPen(couleur_texte);// QColor(0,0,255,255)
	paint_.drawText(0,font().pointSize()*3/2,text());
	paint_.setPen(couleur_rectangle);
	paint_.drawRect(0,0,width()-1,height()-1);
	//paint_.drawImage(QPoint(0,0),pixmap()->toImage());
}
