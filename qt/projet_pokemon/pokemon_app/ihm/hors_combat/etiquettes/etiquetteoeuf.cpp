#include "ihm/hors_combat/etiquettes/etiquetteoeuf.h"
#include "base_donnees/donnees.h"
#include "serialisable/pokemon/oeufpokemon.h"
#include <QPainter>

EtiquetteOeuf::EtiquetteOeuf(uchar _position,const OeufPokemon& _oeuf,Donnees *_d){
	QFont fond_=font();
	fond_.setPointSize(10);
	setFont(fond_);
	QString texte_="L'oeuf contient:\n"+_oeuf.nom_pk();
	QStringList lignes_=texte_.split("\n",QString::SkipEmptyParts);
	int max_=0;
	foreach(QString l,lignes_){
		max_=Utilitaire::max_min<int>(max_,QFontMetrics(font()).width(l)).first;
	}
	setText(lignes_.join("\n"));
	image_oeuf=_d->val_miniatures().valeur(0);
	position=_position;
	choisi=false;
	setFixedHeight(150);
	setMinimumWidth(max_);
	setMaximumWidth(190);
}

void EtiquetteOeuf::mouseReleaseEvent(QMouseEvent *){
	emit clic(position);
}

void EtiquetteOeuf::maj_choix(bool _choix){
	choisi=_choix;
}

void EtiquetteOeuf::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	paint_.fillRect(0,0,width()-1,height()-1,QColor(255,255,255,255));
	if(choisi){
		paint_.setPen(QColor(255,0,0,255));
	}else{
		paint_.setPen(QColor(0,0,0,255));
	}
	paint_.drawRect(0,0,width()-1,height()-1);
	paint_.setPen(QColor(255,0,0,255));
	paint_.drawImage(QPoint(0,0),image_oeuf);
	QStringList lignes_=text().split("\n");
	int i_=0;
	foreach(QString l,lignes_){
		paint_.drawText(image_oeuf.width()+4,font().pointSize()*(i_+1)*3/2,l);
		i_++;
	}
}

