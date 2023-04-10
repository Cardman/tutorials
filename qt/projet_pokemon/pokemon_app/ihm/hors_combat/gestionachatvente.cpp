#include "ihm/hors_combat/gestionachatvente.h"
#include "ihm/boutons/claviernumerique.h"
#include "ihm/boutons/bouton.h"
#include "ihm/boutons/boutonachatvente.h"
#include "serialisable/utilisateur/utilisateur.h"
#include "base_donnees/donnees.h"
#include <QGroupBox>
#include <QLabel>
#include <QTextEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>

GestionAchatVente::GestionAchatVente(int _langue,Donnees *_d){
	valeur_argent=Entier(0);
	langue=_langue;
	donnees=_d;
	type_achat=GestionAchatVente::RIEN;
	QSplitter *gestion_=new QSplitter(Qt::Vertical);
	asc_objets=new QScrollArea();
	QGroupBox *groupe_=new QGroupBox("Objets:");
	objets=new QVBoxLayout();
	groupe_->setLayout(objets);
	asc_objets->setWidget(groupe_);
	gestion_->addWidget(asc_objets);
	groupe_=new QGroupBox("Actions:");
	QHBoxLayout *lay_actions_=new QHBoxLayout();
	QVBoxLayout *lay_actions_v_=new QVBoxLayout();
	argent=new QLabel();
	lay_actions_v_->addWidget(argent);
	total_achat=new QLabel();
	lay_actions_v_->addWidget(total_achat);
	Bouton *bouton_=new Bouton();
	bouton_->maj_texte("Valider achat/vente");
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	connect(bouton_,SIGNAL(clic()),this,SLOT(valider_achats_vente()));
	lay_actions_v_->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("Finir");
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	connect(bouton_,SIGNAL(clic()),this,SLOT(finir_gestion()));
	lay_actions_v_->addWidget(bouton_);
	lay_actions_->addLayout(lay_actions_v_);
	clavier=new ClavierNumerique(true,_d);
	connect(clavier,SIGNAL(valider(Entier)),this,SLOT(valider_achats_vente(Entier)));
	lay_actions_->addWidget(clavier);
	groupe_->setLayout(lay_actions_);
	QScrollArea *asc_=new QScrollArea();
	asc_->setWidget(groupe_);
	gestion_->addWidget(asc_);
	addWidget(gestion_);
	asc_=new QScrollArea();
	description=new QTextEdit();
	asc_->setWidget(description);
	addWidget(asc_);
	indice=0;

}

uchar GestionAchatVente::type_gestion()const{
	return type_achat;
}

void GestionAchatVente::maj_fiche(uchar _type,const Utilisateur& _utilisateur,const QStringList& _objets){
	type_achat=_type;
	inv=_utilisateur.inv();
	foreach(QString o,liste_objets.cles()){
		liste_objets.valeur(o)->deleteLater();
		objets->removeWidget(liste_objets.valeur(o));
	}
	typedef QPair<QString,int> ObjetIndice;
	foreach(ObjetIndice o,liste_objets_vente.cles()){
		liste_objets_vente.valeur(o)->deleteLater();
		objets->removeWidget(liste_objets_vente.valeur(o));
	}
	foreach(uchar c,liste_capsules.cles()){
		liste_capsules.valeur(c)->deleteLater();
		objets->removeWidget(liste_capsules.valeur(c));
	}
	liste_objets.tout_supprimer();
	liste_objets_vente.tout_supprimer();
	liste_capsules.tout_supprimer();
	valeur_argent=_utilisateur.val_argent();
	argent->setText("argent: "+valeur_argent.chaine());
	if(objets->count()>0){
		objets->itemAt(0)->widget()->deleteLater();
		objets->removeItem(objets->itemAt(0));
	}
	int l_=100;
	if(type_achat==GestionAchatVente::ACHAT_OBJET){
		objets->addWidget(new QLabel("Icone\tNom\tPrix\tQuantite a acheter\tPrix partiel\tEffectif"));
		foreach(QString o,_objets){
			BoutonAchatVente *bouton_=new BoutonAchatVente();
			bouton_->maj_type(type_achat);
			if(quantites_achat.cles().contains(o)){
				bouton_->maj_texte(o,0,inv,donnees,quantites_achat.valeur(o),quantites_achat.valeur(o)*donnees->val_objets().valeur(o)->prix());
			}else{
				quantites_achat.ajouter_cle_valeur(o,0);
				bouton_->maj_texte(o,0,inv,donnees,0,0);
			}
			l_=Utilitaire::max_min<int>(l_,bouton_->minimumWidth()+20).first;
			bouton_->maj_couleur_texte(QColor(0,0,255,255));
			bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
			bouton_->maj_couleur_rectangle_choix(QColor(255,0,0,255));
			bouton_->maj_couleur_fond(QColor(255,255,255,255));
			connect(bouton_,SIGNAL(clic(QString)),this,SLOT(selection_objet(QString)));
			objets->addWidget(bouton_);
			liste_objets.ajouter_cle_valeur(o,bouton_);
		}
	}else if(type_achat==GestionAchatVente::VENTE_OBJET){
		objets->addWidget(new QLabel("Icone\tNom\tPrix\tQuantite a vendre\tPrix partiel\tEffectif"));
		typedef QPair<QString,int> ObjetIndice;
		foreach(ObjetIndice o,quantites_vente.cles()){
			quantites_vente.valeur(o)=0;
		}
		foreach(QString o,donnees->val_objets().cles()){
			if(inv.quantite(o)==0){
				continue;
			}
			if(inv.objets_soins_ut().cles().contains(o)){
				QList<QPair<uchar,Taux> > liste_=inv.objets_soins_ut().valeur(o);
				for(int i=0;i<liste_.size();i++){
					QPair<QString,int> cle_(o,i);
					BoutonAchatVente *bouton_=new BoutonAchatVente();
					bouton_->maj_type(type_achat);
					if(quantites_vente.cles().contains(cle_)){
						bouton_->maj_texte(o,0,inv,donnees,quantites_vente.valeur(cle_),quantites_vente.valeur(cle_)*donnees->val_objets().valeur(o)->prix(),i);
					}else{
						quantites_vente.ajouter_cle_valeur(cle_,0);
						bouton_->maj_texte(o,0,inv,donnees,0,0,i);
					}
					l_=Utilitaire::max_min<int>(l_,bouton_->minimumWidth()+20).first;
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle_choix(QColor(255,0,0,255));
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					connect(bouton_,SIGNAL(clic(QString,int)),this,SLOT(selection_objet(QString,int)));
					objets->addWidget(bouton_);
					liste_objets_vente.ajouter_cle_valeur(cle_,bouton_);
				}
			}else if(inv.boost_statistiques_ut().cles().contains(o)){
				QList<QPair<uchar,uchar> > liste_=inv.boost_statistiques_ut().valeur(o);
				for(int i=0;i<liste_.size();i++){
					QPair<QString,int> cle_(o,i);
					BoutonAchatVente *bouton_=new BoutonAchatVente();
					bouton_->maj_type(type_achat);
					if(quantites_vente.cles().contains(cle_)){
						bouton_->maj_texte(o,0,inv,donnees,quantites_vente.valeur(cle_),quantites_vente.valeur(cle_)*donnees->val_objets().valeur(o)->prix(),i);
					}else{
						quantites_vente.ajouter_cle_valeur(cle_,0);
						bouton_->maj_texte(o,0,inv,donnees,0,0,i);
					}
					l_=Utilitaire::max_min<int>(l_,bouton_->minimumWidth()+20).first;
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle_choix(QColor(255,0,0,255));
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					connect(bouton_,SIGNAL(clic(QString,int)),this,SLOT(selection_objet(QString,int)));
					objets->addWidget(bouton_);
					liste_objets_vente.ajouter_cle_valeur(cle_,bouton_);
				}
			}else{
				BoutonAchatVente *bouton_=new BoutonAchatVente();
				bouton_->maj_type(type_achat);
				QPair<QString,int> cle_(o,0);
				if(quantites_vente.cles().contains(cle_)){
					bouton_->maj_texte(o,0,inv,donnees,quantites_vente.valeur(cle_),quantites_vente.valeur(cle_)*donnees->val_objets().valeur(o)->prix(),0);
				}else{
					quantites_vente.ajouter_cle_valeur(cle_,0);
					bouton_->maj_texte(o,0,inv,donnees,0,0,0);
				}
				l_=Utilitaire::max_min<int>(l_,bouton_->minimumWidth()+20).first;
				bouton_->maj_couleur_texte(QColor(0,0,255,255));
				bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
				bouton_->maj_couleur_rectangle_choix(QColor(255,0,0,255));
				bouton_->maj_couleur_fond(QColor(255,255,255,255));
				connect(bouton_,SIGNAL(clic(QString,int)),this,SLOT(selection_objet(QString,int)));
				objets->addWidget(bouton_);
				liste_objets_vente.ajouter_cle_valeur(cle_,bouton_);
				//liste_objets.ajouter_cle_valeur(o,bouton_);
			}
		}
	}
	objets->itemAt(0)->widget()->setFixedHeight(20);
	if(objets->count()>1){
		objets->parentWidget()->setFixedHeight(objets->itemAt(0)->widget()->height()+objets->itemAt(1)->widget()->height()*(objets->count()-1));
	}else{
		objets->parentWidget()->setFixedHeight(objets->itemAt(0)->widget()->height());
	}
	objets->parentWidget()->setMinimumWidth(l_);
	//
}

void GestionAchatVente::maj_fiche_c(uchar _type,const Utilisateur& _utilisateur,const QList<uchar>& _objets){
	type_achat=_type;
	//
	inv=_utilisateur.inv();
	foreach(QString o,liste_objets.cles()){
		liste_objets.valeur(o)->deleteLater();
		objets->removeWidget(liste_objets.valeur(o));
	}
	typedef QPair<QString,int> ObjetIndice;
	foreach(ObjetIndice o,liste_objets_vente.cles()){
		liste_objets_vente.valeur(o)->deleteLater();
		objets->removeWidget(liste_objets_vente.valeur(o));
	}
	foreach(uchar c,liste_capsules.cles()){
		liste_capsules.valeur(c)->deleteLater();
		objets->removeWidget(liste_capsules.valeur(c));
	}
	if(objets->count()>0){
		objets->itemAt(0)->widget()->deleteLater();
		objets->removeItem(objets->itemAt(0));
	}
	liste_objets.tout_supprimer();
	liste_objets_vente.tout_supprimer();
	liste_capsules.tout_supprimer();
	valeur_argent=_utilisateur.val_argent();
	argent->setText("argent: "+valeur_argent.chaine());
	int l_=100;
	if(type_achat==GestionAchatVente::ACHAT_CT){
		objets->addWidget(new QLabel("Numero\tNom attaque\tPrix\tQuantite a acheter\tPrix partiel\tEffectif"));
		foreach(uchar c,_objets){
			BoutonAchatVente *bouton_=new BoutonAchatVente();
			bouton_->maj_type(type_achat);
			if(quantites_ct.cles().contains(c)){
				bouton_->maj_texte("",c,inv,donnees,quantites_ct.valeur(c),quantites_ct.valeur(c)*1000);
			}else{
				quantites_ct.ajouter_cle_valeur(c,0);
				bouton_->maj_texte("",c,inv,donnees,0,0);
			}
			l_=Utilitaire::max_min<int>(l_,bouton_->minimumWidth()+20).first;
			bouton_->maj_couleur_texte(QColor(0,0,255,255));
			bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
			bouton_->maj_couleur_rectangle_choix(QColor(255,0,0,255));
			bouton_->maj_couleur_fond(QColor(255,255,255,255));
			connect(bouton_,SIGNAL(clic(QString)),this,SLOT(selection_capsule(QString)));
			objets->addWidget(bouton_);
			liste_capsules.ajouter_cle_valeur(c,bouton_);
		}
	}else if(type_achat==GestionAchatVente::VENTE_CT){
		foreach(uchar c,quantites_ct.cles()){
			quantites_ct.valeur(c)=0;
		}
		objets->addWidget(new QLabel("Numero\tNom attaque\tPrix\tQuantite a vendre\tPrix partiel\tEffectif"));
		foreach(uchar c,donnees->val_ct().cles()){
			if(inv.ct_ut().valeur(c)==0){
				continue;
			}
			BoutonAchatVente *bouton_=new BoutonAchatVente();
			bouton_->maj_type(type_achat);
			if(quantites_ct.cles().contains(c)){
				bouton_->maj_texte("",c,inv,donnees,quantites_ct.valeur(c),quantites_ct.valeur(c)*1000);
			}else{
				quantites_ct.ajouter_cle_valeur(c,0);
				bouton_->maj_texte("",c,inv,donnees,0,0);
			}
			l_=Utilitaire::max_min<int>(l_,bouton_->minimumWidth()+20).first;
			bouton_->maj_couleur_texte(QColor(0,0,255,255));
			bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
			bouton_->maj_couleur_rectangle_choix(QColor(255,0,0,255));
			bouton_->maj_couleur_fond(QColor(255,255,255,255));
			connect(bouton_,SIGNAL(clic(QString)),this,SLOT(selection_capsule(QString)));
			objets->addWidget(bouton_);
			liste_capsules.ajouter_cle_valeur(c,bouton_);
		}
	}
	objets->itemAt(0)->widget()->setFixedHeight(20);
	if(objets->count()>1){
		objets->parentWidget()->setFixedHeight(objets->itemAt(0)->widget()->height()+objets->itemAt(1)->widget()->height()*(objets->count()-1));
	}else{
		objets->parentWidget()->setFixedHeight(objets->itemAt(0)->widget()->height());
	}
	objets->parentWidget()->setMinimumWidth(l_);
}

HashMap<QString,uchar> GestionAchatVente::val_quantites_achat()const{
	return quantites_achat;
}

HashMap<QPair<QString,int>,uchar> GestionAchatVente::val_quantites_vente()const{
	return quantites_vente;
}

HashMap<uchar,uchar> GestionAchatVente::val_quantites_ct()const{
	return quantites_ct;
}


void GestionAchatVente::valider_achats_vente(){
	if(quantites_ct.total()==0&&(type_achat==GestionAchatVente::ACHAT_CT||type_achat==GestionAchatVente::VENTE_CT)){
		return;
	}
	if(quantites_achat.total()==0&&type_achat==GestionAchatVente::ACHAT_OBJET){
		return;
	}
	if(quantites_vente.total()==0&&type_achat==GestionAchatVente::VENTE_OBJET){
		return;
	}
	Entier somme_(0);
	if(type_achat==GestionAchatVente::ACHAT_CT){
		foreach(uchar c,quantites_ct.cles()){
			somme_+=Entier(quantites_ct.valeur(c))*Entier(1000);
		}
	}else if(type_achat==GestionAchatVente::ACHAT_OBJET){
		foreach(QString o,quantites_achat.cles()){
			somme_+=Entier(quantites_achat.valeur(o))*Entier(donnees->val_objets().valeur(o)->prix());
		}
	}
	if(type_achat==GestionAchatVente::ACHAT_CT||type_achat==GestionAchatVente::ACHAT_OBJET){
		if(somme_>valeur_argent){
			emit erreur_achat();
		}else{
			emit achat();
		}
	}else{
		bool manque_=false;
		if(type_achat==GestionAchatVente::VENTE_CT){
			foreach(uchar c,quantites_ct.cles()){
				if(quantites_ct.valeur(c)>inv.ct_ut().valeur(c)){
					manque_=true;
					break;
				}
			}
		}else{
			typedef QPair<QString,int> ObjetIndice;
			foreach(ObjetIndice o,quantites_vente.cles()){
				if(quantites_vente.valeur(o)>inv.quantite(o.first,o.second)){
					manque_=true;
					break;
				}
			}
		}
		if(manque_){
			emit erreur_vente();
		}else{
			/*if(type_achat==GestionAchatVente::VENTE_CT){
				foreach(uchar c,quantites_ct.cles()){
					quantites_ct.valeur(c)=0;
				}
			}else{
				typedef QPair<QString,int> ObjetIndice;
				foreach(ObjetIndice o,quantites_vente.cles()){
					quantites_vente.valeur(o)=0;
				}
			}*/
			emit vente();
		}
	}
}

void GestionAchatVente::valider_achats_vente(const Entier& _quantite){
	if(type_achat==GestionAchatVente::ACHAT_CT||type_achat==GestionAchatVente::VENTE_CT){
		if(quantites_ct.total()==0){
			calcul_somme();
			return;
		}
		quantites_ct.valeur(capsule)=_quantite.modulo_absolu_base();
		liste_capsules.valeur(capsule)->maj_texte(objet,capsule,inv,donnees,_quantite.modulo_absolu_base(),_quantite.modulo_absolu_base()*1000);
		liste_capsules.valeur(capsule)->repaint();
	}else if(type_achat==GestionAchatVente::ACHAT_OBJET){
		if(quantites_achat.total()==0){
			calcul_somme();
			return;
		}
		quantites_achat.valeur(objet)=_quantite.modulo_absolu_base();
		liste_objets.valeur(objet)->maj_texte(objet,0,inv,donnees,_quantite.modulo_absolu_base(),_quantite.modulo_absolu_base()*donnees->val_objets().valeur(objet)->prix());
		liste_objets.valeur(objet)->repaint();
	}else if(type_achat==GestionAchatVente::VENTE_OBJET){
		if(quantites_vente.total()==0){
			calcul_somme();
			return;
		}
		quantites_vente.valeur(QPair<QString,int>(objet,indice))=_quantite.modulo_absolu_base();
		liste_objets_vente.valeur(QPair<QString,int>(objet,indice))->maj_texte(objet,0,inv,donnees,_quantite.modulo_absolu_base(),_quantite.modulo_absolu_base()*donnees->val_objets().valeur(objet)->prix(),indice);
		liste_objets_vente.valeur(QPair<QString,int>(objet,indice))->repaint();
	}
	calcul_somme();
}

void GestionAchatVente::calcul_somme(){
	Entier somme_(0);
	foreach(QString o,quantites_achat.cles()){
		somme_+=Entier(quantites_achat.valeur(o))*Entier(donnees->val_objets().valeur(o)->prix());
	}
	foreach(uchar c,quantites_ct.cles()){
		somme_+=Entier(quantites_ct.valeur(c))*Entier(1000);
	}
	if(type_achat==GestionAchatVente::ACHAT_CT||type_achat==GestionAchatVente::ACHAT_OBJET){
		if(valeur_argent>=somme_){
			total_achat->setText("> "+somme_.chaine());
		}else{
			total_achat->setText("< "+somme_.chaine());
		}
	}else{
		total_achat->setText(somme_.chaine());
	}
}

void GestionAchatVente::finir_gestion(){
	type_achat=GestionAchatVente::RIEN;
	valeur_argent=Entier(0);
	quantites_achat.tout_supprimer();
	quantites_ct.tout_supprimer();
	quantites_vente.tout_supprimer();
	emit fin_gestion();
}

void GestionAchatVente::selection_objet(const QString& _objet){
	objet=_objet;
	clavier->maj_texte(QString::number(quantites_achat.valeur(_objet)));
	description->setPlainText(donnees->val_objets().valeur(_objet)->description(langue,donnees));
	foreach(QString o,liste_objets.cles()){
		liste_objets.valeur(o)->maj_choix(false);
	}
	liste_objets.valeur(objet)->maj_choix(true);
	foreach(QString o,liste_objets.cles()){
		liste_objets.valeur(o)->repaint();
	}
}

void GestionAchatVente::selection_objet(const QString& _objet,int _indice){
	objet=_objet;
	indice=_indice;
	clavier->maj_texte(QString::number(quantites_vente.valeur(QPair<QString,int>(_objet,_indice))));
	description->setPlainText(donnees->val_objets().valeur(_objet)->description(langue,donnees));
	typedef QPair<QString,int> ObjetIndice;
	foreach(ObjetIndice o,liste_objets_vente.cles()){
		liste_objets_vente.valeur(o)->maj_choix(false);
	}
	liste_objets_vente.valeur(QPair<QString,int>(_objet,_indice))->maj_choix(true);
	foreach(ObjetIndice o,liste_objets_vente.cles()){
		liste_objets_vente.valeur(o)->repaint();
	}
}

void GestionAchatVente::selection_capsule(const QString& _capsule){
	selection_capsule(_capsule.toInt());
}

void GestionAchatVente::selection_capsule(uchar _capsule){
	capsule=_capsule;
	clavier->maj_texte(QString::number(quantites_ct.valeur(_capsule)));
	QString attaque_=donnees->val_ct().valeur(_capsule);
	description->setPlainText(donnees->val_attaques().valeur(attaque_)->description(attaque_,langue,donnees));
	foreach(uchar c,liste_capsules.cles()){
		liste_capsules.valeur(c)->maj_choix(false);
	}
	liste_capsules.valeur(capsule)->maj_choix(true);
	foreach(uchar c,liste_capsules.cles()){
		liste_capsules.valeur(c)->repaint();
	}
}
