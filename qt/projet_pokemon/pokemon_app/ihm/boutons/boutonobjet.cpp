#include "ihm/boutons/boutonobjet.h"
#include "base_donnees/donnees.h"
#include "serialisable/utilisateur/inventaire.h"
#include <QPainter>

BoutonObjet::BoutonObjet(const QString& _nom,int _numero,Inventaire& _inv,Donnees *_d,int _sous_action){
	contenu=Taux(0);
	numero=0;
	ico_actif=false;
	sous_action=_sous_action;
	int hauteur_=font().pointSize()*2;
	if(_numero>0){
		nom=_nom;
		numero=_numero;
		quantite=_inv.ct_ut().valeur(numero);
	}else if(_numero<0){
		nom=_nom;
		numero=-_numero;
		if(_inv.cs_ut().valeur(numero)){
			quantite=1;
			obtenu="OUI";
		}else{
			quantite=0;
			obtenu="NON";
		}
	}else if(_inv.objets_soins_ut().cles().contains(_nom)){
		nom=_nom;
		ico=_d->val_images_objets().valeur(_nom);
		if(ico.height()>hauteur_){
			hauteur_=ico.height();
		}
		ico_actif=true;
		quantite=_inv.objets_soins_ut().valeur(_nom)[_sous_action].first;
		contenu=_inv.objets_soins_ut().valeur(_nom)[_sous_action].second;
	}else if(_inv.boost_statistiques_ut().cles().contains(_nom)){
		nom=_nom;
		ico=_d->val_images_objets().valeur(_nom);
		if(ico.height()>hauteur_){
			hauteur_=ico.height();
		}
		ico_actif=true;
		quantite=_inv.boost_statistiques_ut().valeur(_nom)[_sous_action].first;
	}else{
		nom=_nom;
		ico=_d->val_images_objets().valeur(_nom);
		if(ico.height()>hauteur_){
			hauteur_=ico.height();
		}
		ico_actif=true;
		quantite=_inv.quantite(_nom);
	}
	int marge_=0;
	if(ico_actif){
		marge_=ico.width()+2;
	}
	QString texte_;
	if(nom!=""){
		texte_+=nom;
	}else{
		texte_+=QString::number(numero);
		if(obtenu!=""){
			texte_+=" "+_d->val_cs().valeur(numero)+" ";
		}else{
			texte_+=" "+_d->val_ct().valeur(numero)+" ";
		}
	}
	if(obtenu==""){
		texte_+=" "+QString::number(quantite);
	}else{
		texte_+=" "+obtenu;
	}
	if(sous_action!=-1){
		texte_+=" "+contenu.evaluer(3);
	}
	setMinimumWidth(marge_+QFontMetrics(font()).width(texte_));
	setFixedHeight(hauteur_);
	setText(texte_);
}

void BoutonObjet::maj_texte(const QString& _texte){
	QFont fond_=font();
	fond_.setPointSize(20);
	setText(_texte);
	setFixedHeight(2*fond_.pointSize());
	QFontMetrics fond_m_(fond_);
	setMinimumWidth(fond_m_.width(_texte));
	setFont(fond_);
}

void BoutonObjet::maj_couleur_texte(const QColor& _couleur){
	couleur_texte=_couleur;
}

void BoutonObjet::maj_couleur_fond(const QColor& _couleur){
	couleur_fond=_couleur;
}

void BoutonObjet::maj_couleur_rectangle(const QColor& _couleur){
	couleur_rectangle=_couleur;
}


void BoutonObjet::mouseReleaseEvent(QMouseEvent *){
	if(sous_action==-1){
		if(nom==""){
			emit clic();
		}else{
			emit clic(nom);
		}
	}else{
		emit clic(nom,sous_action);
	}
}

void BoutonObjet::paintEvent(QPaintEvent *){
	QPainter paint_(this);
	paint_.fillRect(0,0,width(),height(),couleur_fond);//QColor(255,255,255,255)
	if(ico_actif){
		paint_.drawImage(QPoint(0,0),ico);
		paint_.setPen(couleur_texte);// QColor(0,0,255,255)
		paint_.drawText(ico.width()+2,font().pointSize()*3/2,text());
	}else{
		paint_.setPen(couleur_texte);// QColor(0,0,255,255)
		paint_.drawText(0,font().pointSize()*3/2,text());
	}
	paint_.setPen(couleur_rectangle);
	paint_.drawRect(0,0,width()-1,height()-1);
	//paint_.drawImage(QPoint(0,0),pixmap()->toImage());
}

