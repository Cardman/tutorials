#include "ihm/boutons/boutonachatvente.h"
#include "base_donnees/donnees.h"
#include "serialisable/utilisateur/inventaire.h"
#include "ihm/hors_combat/gestionachatvente.h"
#include <QPainter>
#include <iostream>

BoutonAchatVente::BoutonAchatVente(){
	contenu=Taux(0);
	//sous_action=_sous_action;
	//int hauteur_=font().pointSize()*2;
	maj_type(GestionAchatVente::RIEN);
	/*QString prix_;
	if(_numero>0){
		numero=_numero;
		quantite=_inv.ct_ut().valeur(numero);
		prix_="1000";
	}else if(_inv.objets_soins_ut().cles().contains(_nom)){
		nom=_nom;
		ico=_d->val_images_objets().valeur(_nom);
		if(ico.height()>hauteur_){
			hauteur_=ico.height();
		}
		ico_actif=true;
		quantite=_inv.objets_soins_ut().valeur(_nom)[_sous_action].first;
		contenu=_inv.objets_soins_ut().valeur(_nom)[_sous_action].second;
		prix_=QString::number(_d->val_objets().valeur(_nom)->prix());
	}else if(_inv.boost_statistiques_ut().cles().contains(_nom)){
		nom=_nom;
		ico=_d->val_images_objets().valeur(_nom);
		if(ico.height()>hauteur_){
			hauteur_=ico.height();
		}
		ico_actif=true;
		quantite=_inv.boost_statistiques_ut().valeur(_nom)[_sous_action].first;
		prix_=QString::number(_d->val_objets().valeur(_nom)->prix());
	}else{
		nom=_nom;
		ico=_d->val_images_objets().valeur(_nom);
		if(ico.height()>hauteur_){
			hauteur_=ico.height();
		}
		ico_actif=true;
		quantite=_inv.quantite(_nom);
		prix_=QString::number(_d->val_objets().valeur(_nom)->prix());
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
		texte_+="\t"+_d->val_ct().valeur(numero);
	}
	texte_+="\t"+prix_+"\t0\t0";
	texte_+="\t"+QString::number(quantite);
	if(sous_action!=-1){
		texte_+="\t"+contenu.evaluer(3);
	}
	setMinimumWidth(marge_+QFontMetrics(font()).width(texte_));
	setText(texte_);*/
	//maj_texte(_nom,_numero,_inv,_d,0,0,sous_action);
	//setFixedHeight(hauteur_);
	choisi=false;
}

void BoutonAchatVente::maj_texte(const QString& _nom,int _numero,Inventaire& _inv,Donnees *_d,int _quant_achat_vente,int _prix_part,int _sous_action){
	sous_action=_sous_action;
	int hauteur_=font().pointSize()*2;
	if(type==GestionAchatVente::ACHAT_CT||type==GestionAchatVente::ACHAT_OBJET||type==GestionAchatVente::RIEN){
		contenu=Taux(0);
		QString prix_;
		if(_numero>0){
			ico_actif=false;
			quantite=_inv.ct_ut().valeur(_numero);
			prix_="1000";
		}else{
			nom=_nom;
			ico=_d->val_images_objets().valeur(_nom);
			if(ico.height()>hauteur_){
				hauteur_=ico.height();
			}
			ico_actif=true;
			quantite=_inv.quantite(_nom);
			prix_=QString::number(_d->val_objets().valeur(_nom)->prix());
		}
		int marge_=0;
		if(ico_actif){
			marge_=ico.width()+2;
		}
		QString texte_;
		if(_numero<=0){
			texte_+=nom;
		}else{
			nom=QString::number(_numero);
			texte_+=QString::number(_numero);
			texte_+="\t"+_d->val_ct().valeur(_numero);
		}
		texte_+="\t"+prix_+"\t"+QString::number(_quant_achat_vente)+"\t"+QString::number(_prix_part);
		texte_+="\t"+QString::number(quantite);
		setText(texte_);
		setMinimumWidth(marge_+QFontMetrics(font()).width(texte_));
	}else{
		contenu=Taux(0);
		QString prix_;
		if(_numero>0){
			ico_actif=false;
			quantite=_inv.ct_ut().valeur(_numero);
			prix_="1000";
		}else if(_inv.objets_soins_ut().cles().contains(_nom)){
			nom=_nom;
			ico=_d->val_images_objets().valeur(_nom);
			if(ico.height()>hauteur_){
				hauteur_=ico.height();
			}
			ico_actif=true;
			quantite=_inv.objets_soins_ut().valeur(_nom)[_sous_action].first;
			contenu=_inv.objets_soins_ut().valeur(_nom)[_sous_action].second;
			prix_=QString::number(_d->val_objets().valeur(_nom)->prix());
		}else if(_inv.boost_statistiques_ut().cles().contains(_nom)){
			nom=_nom;
			ico=_d->val_images_objets().valeur(_nom);
			if(ico.height()>hauteur_){
				hauteur_=ico.height();
			}
			ico_actif=true;
			quantite=_inv.boost_statistiques_ut().valeur(_nom)[_sous_action].first;
			prix_=QString::number(_d->val_objets().valeur(_nom)->prix());
		}else{
			nom=_nom;
			ico=_d->val_images_objets().valeur(_nom);
			if(ico.height()>hauteur_){
				hauteur_=ico.height();
			}
			ico_actif=true;
			quantite=_inv.quantite(_nom);
			prix_=QString::number(_d->val_objets().valeur(_nom)->prix());
		}
		int marge_=0;
		if(ico_actif){
			marge_=ico.width()+2;
		}
		QString texte_;
		if(_numero<=0){
			texte_+=nom;
		}else{
			nom=QString::number(_numero);
			texte_+=QString::number(_numero);
			texte_+="\t"+_d->val_ct().valeur(_numero);
		}
		texte_+="\t"+prix_+"\t"+QString::number(_quant_achat_vente)+"\t"+QString::number(_prix_part);
		texte_+="\t"+QString::number(quantite);
		if(sous_action!=-1){
			texte_+="\t"+contenu.evaluer(3);
		}
		setText(texte_);
		setMinimumWidth(marge_+QFontMetrics(font()).width(texte_));
	}
	setFixedHeight(hauteur_);
	/*if(font()==QFont()){//VRAI
		std::cout<<"egaux:"+font().toString().toStdString()<<"\n";//==Sans,10,-1,5,50,0,0,0,0,0 (Linux)
	}else{
		std::cout<<"diff:"+QFont().toString().toStdString()<<",";
		std::cout<<font().toString().toStdString()<<"\n";
	}*/
}

void BoutonAchatVente::maj_type(uchar _type){
	type=_type;
}

void BoutonAchatVente::maj_choix(bool _choix){
	choisi=_choix;
}

void BoutonAchatVente::maj_texte(const QString& _texte){
	QFont fond_=font();
	fond_.setPointSize(20);
	setText(_texte);
	setFixedHeight(2*fond_.pointSize());
	QFontMetrics fond_m_(fond_);
	setMinimumWidth(fond_m_.width(_texte));
	setFont(fond_);
}

void BoutonAchatVente::maj_couleur_texte(const QColor& _couleur){
	couleur_texte=_couleur;
}

void BoutonAchatVente::maj_couleur_fond(const QColor& _couleur){
	couleur_fond=_couleur;
}

void BoutonAchatVente::maj_couleur_rectangle(const QColor& _couleur){
	couleur_rectangle=_couleur;
}

void BoutonAchatVente::maj_couleur_rectangle_choix(const QColor& _couleur){
	couleur_rectangle_choix=_couleur;
}

void BoutonAchatVente::mouseReleaseEvent(QMouseEvent *){
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

void BoutonAchatVente::paintEvent(QPaintEvent *){
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
	if(choisi){
		paint_.setPen(couleur_rectangle_choix);
	}else{
		paint_.setPen(couleur_rectangle);
	}
	paint_.drawRect(0,0,width()-1,height()-1);
	//paint_.drawImage(QPoint(0,0),pixmap()->toImage());
}

