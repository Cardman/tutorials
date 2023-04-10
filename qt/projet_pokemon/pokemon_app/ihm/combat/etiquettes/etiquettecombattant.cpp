#include "ihm/combat/etiquettes/etiquettecombattant.h"
#include "serialisable/combat/creaturecombat.h"
#include "base_donnees/donnees.h"
#include <QPainter>

EtiquetteCombattant::EtiquetteCombattant(const Combattant& _cbt,const CreatureCombat& _cr_c,int _position,Donnees* _d){
	combattant=_cbt;
	QString texte_=_cr_c.nom_pk_act()+" ";
	if(combattant.equipe()==_d->val_adv()){
		texte_+="adverse ";
	}
	if(_position==(int)_d->constante_numerique("ARRIERE")){
		texte_+=" arriere";
	}else{
		texte_+=" position "+QString::number(_position);
	}
	setText(texte_);
	setFixedHeight(font().pointSize());
	setMinimumWidth(10+QFontMetrics(font()).width(text()));
	choisi=false;
	actif=true;
}

EtiquetteCombattant::EtiquetteCombattant(const Combattant& _cbt,const QString& _nom_act,int _position,int _arriere){
	combattant=_cbt;
	QString texte_=_nom_act+" ";
	if(_position==_arriere){
		texte_+=" arriere";
	}else{
		texte_+=" position "+QString::number(_position);
	}
	setText(texte_);
	setFixedHeight(font().pointSize());
	setMinimumWidth(10+QFontMetrics(font()).width(text()));
	choisi=false;
	actif=true;
}

void EtiquetteCombattant::maj_choix(bool _choisi){
	choisi=_choisi;
}

void EtiquetteCombattant::maj_actif(bool _actif){
	actif=_actif;
}

void EtiquetteCombattant::mouseReleaseEvent(QMouseEvent *){
	if(actif){
		emit clic(combattant);
	}
}

void EtiquetteCombattant::paintEvent(QPaintEvent *){
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
