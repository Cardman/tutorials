#include "ihm/hors_combat/gestioninventaire.h"
#include "base_donnees/donnees.h"
#include "base_donnees/attaques/ficheattaque.h"
#include "ihm/boutons/bouton.h"
#include "ihm/boutons/boutonobjet.h"
#include "ihm/boutons/boutontype.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QLabel>
#include <QGroupBox>

GestionInventaire::GestionInventaire(Donnees* _d){
	donnees=_d;
	quantite_selectionnee=-1;
	QSplitter *type_objets_=new QSplitter(Qt::Vertical);
	QScrollArea *asc_=new QScrollArea();
	QGroupBox *groupe_=new QGroupBox("Categorie d'objets");
	QVBoxLayout *lay_objets_=new QVBoxLayout();
	BoutonType *bouton_=new BoutonType("Baies",GestionInventaire::BAIE);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Balls pour la capture",GestionInventaire::BALL);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Objets de boost de statistiques",GestionInventaire::BOOST);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Plaques et modules",GestionInventaire::PLAQUE);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Objets attachables en combat",GestionInventaire::OBJET_ATTACHABLE);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Objets d'evolution si attache",GestionInventaire::OBJET_EVO);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Pierres evolutives",GestionInventaire::PIERRE_EVO);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Objets de repousse des pokemons sauvages",GestionInventaire::REPOUSSE);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Objets de valeur pouvant etre revendu",GestionInventaire::REVENTE);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Objets de soin",GestionInventaire::SOIN);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Capsules techniques",GestionInventaire::CT);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	bouton_=new BoutonType("Capsules secretes",GestionInventaire::CS);
	connect(bouton_,SIGNAL(clic(uchar)),this,SLOT(maj_action(uchar)));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	lay_objets_->addWidget(bouton_);
	groupe_->setLayout(lay_objets_);
	asc_->setWidget(groupe_);
	type_objets_->addWidget(asc_);
	asc_=new QScrollArea();
	groupe_=new QGroupBox("Actions");
	actions=new QVBoxLayout();

	groupe_->setLayout(actions);
	asc_->setWidget(groupe_);
	type_objets_->addWidget(asc_);
	addWidget(type_objets_);
	asc_=new QScrollArea();
	objets_particuliers=new QGroupBox("Objets");
	objets=new QVBoxLayout();
	objets_particuliers->setLayout(objets);
	asc_->setWidget(objets_particuliers);
	addWidget(asc_);
	QLabel *conteneur_=new QLabel();
	QVBoxLayout *lay_=new QVBoxLayout();
	et_objet=new QLabel();
	lay_->addWidget(et_objet);
	description=new QTextEdit();
	lay_->addWidget(description);
	conteneur_->setLayout(lay_);
	addWidget(conteneur_);
	type_objet=GestionInventaire::RIEN;
}

QPair<QString,int> GestionInventaire::obj_select()const{
	return QPair<QString,int>(objet_selectionne,quantite_selectionnee);
}

bool GestionInventaire::gestion_en_cours()const{
	return type_objet==GestionInventaire::RIEN;
}

void GestionInventaire::maj_fiche(const Inventaire& _inv,int _langue,uchar _type){
	inventaire=_inv;
	langue=_langue;
	maj_action(_type);
}

void GestionInventaire::maj_action(uchar _type){
	type_objet=_type;
	objet_selectionne="";
	quantite_selectionnee=-1;
	fiche_description.tout_supprimer();
	int nb_=actions->count();
	for(int i=0;i<nb_;i++){
		actions->itemAt(i)->widget()->deleteLater();
	}
	for(int i=0;i<nb_;i++){
		actions->removeItem(actions->itemAt(0));
	}
	nb_=objets->count();
	for(int i=0;i<nb_;i++){
		objets->itemAt(i)->widget()->deleteLater();
	}
	for(int i=0;i<nb_;i++){
		objets->removeItem(objets->itemAt(0));
	}
	Bouton *bouton_act_=NULL;
	if(type_objet!=GestionInventaire::CT&&type_objet!=GestionInventaire::CS){
		bouton_act_=new Bouton("Attacher");
		connect(bouton_act_,SIGNAL(clic(QString)),this,SLOT(attacher()));
		bouton_act_->maj_couleur_fond(QColor(255,255,255,255));
		bouton_act_->maj_couleur_rectangle(QColor(0,0,255,255));
		bouton_act_->maj_couleur_texte(QColor(0,0,255,255));
		actions->addWidget(bouton_act_);
		if(type_objet==GestionInventaire::SOIN||type_objet==GestionInventaire::BOOST){
			objets->addWidget(new QLabel("Icone / nom / quantite / contenu"));
			if(type_objet==GestionInventaire::SOIN){
				foreach(QString s,inventaire.objets_soins_ut().cles()){
					typedef QPair<uchar,Taux> EffectifQuantite;
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					int j_=0;
					foreach(EffectifQuantite e,inventaire.objets_soins_ut().valeur(s)){
						BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees,j_);
						bouton_->maj_couleur_fond(QColor(255,255,255,255));
						bouton_->maj_couleur_texte(QColor(0,0,255,255));
						bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
						connect(bouton_,SIGNAL(clic(QString,int)),this,SLOT(maj_objet(QString,int)));
						objets->addWidget(bouton_);
						j_++;
					}
				}
				//foreach(EffectifQuantite e,inventaire.objets_soins_ut())
			}else{
				foreach(QString s,inventaire.boost_statistiques_ut().cles()){
					typedef QPair<uchar,uchar> EffectifQuantite;
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					int j_=0;
					foreach(EffectifQuantite e,inventaire.boost_statistiques_ut().valeur(s)){
						BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees,j_);
						bouton_->maj_couleur_fond(QColor(255,255,255,255));
						bouton_->maj_couleur_texte(QColor(0,0,255,255));
						bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
						connect(bouton_,SIGNAL(clic(QString,int)),this,SLOT(maj_objet(QString,int)));
						objets->addWidget(bouton_);
						j_++;
					}
				}
			}
		}else{
			objets->addWidget(new QLabel("Icone / nom / quantite"));
			if(type_objet==GestionInventaire::BAIE){
				foreach(QString s,inventaire.baies_ut().cles()){
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees);
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
					objets->addWidget(bouton_);
				}
			}else if(type_objet==GestionInventaire::BALL){
				foreach(QString s,inventaire.balls_ut().cles()){
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees);
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
					objets->addWidget(bouton_);
				}
			}else if(type_objet==GestionInventaire::FOSSILE){
				foreach(QString s,inventaire.fossiles_ut().cles()){
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees);
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
					objets->addWidget(bouton_);
				}
			}else if(type_objet==GestionInventaire::PLAQUE){
				foreach(QString s,inventaire.plaques_ut().cles()){
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees);
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
					objets->addWidget(bouton_);
				}
			}else if(type_objet==GestionInventaire::OBJET_ATTACHABLE){
				foreach(QString s,inventaire.objets_attacher_ut().cles()){
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees);
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
					objets->addWidget(bouton_);
				}
			}else if(type_objet==GestionInventaire::OBJET_EVO){
				foreach(QString s,inventaire.objets_attacher_evolution_ut().cles()){
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees);
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
					objets->addWidget(bouton_);
				}
			}else if(type_objet==GestionInventaire::PIERRE_EVO){
				foreach(QString s,inventaire.pierres_evo_ut().cles()){
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees);
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
					objets->addWidget(bouton_);
				}
			}else if(type_objet==GestionInventaire::REPOUSSE){
				foreach(QString s,inventaire.repousse_ut().cles()){
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees);
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
					objets->addWidget(bouton_);
				}
			}else if(type_objet==GestionInventaire::REVENTE){
				foreach(QString s,inventaire.objets_reventes_ut().cles()){
					fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
					BoutonObjet *bouton_=new BoutonObjet(s,0,inventaire,donnees);
					bouton_->maj_couleur_fond(QColor(255,255,255,255));
					bouton_->maj_couleur_texte(QColor(0,0,255,255));
					bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
					connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
					objets->addWidget(bouton_);
				}
			}
		}
	}else{
		if(type_objet!=GestionInventaire::CS){
			objets->addWidget(new QLabel("Numero / nom / quantite"));
		}else{
			objets->addWidget(new QLabel("Numero / nom / obtenue"));
		}
		if(type_objet==GestionInventaire::CT){
			foreach(uchar c,inventaire.ct_ut().cles()){
				QString attaque_=donnees->val_ct().valeur(c);
				fiche_description.ajouter_cle_valeur(attaque_,donnees->val_attaques().valeur(attaque_)->description(attaque_,langue,donnees));
				BoutonObjet *bouton_=new BoutonObjet(attaque_,c,inventaire,donnees);
				bouton_->maj_couleur_fond(QColor(255,255,255,255));
				bouton_->maj_couleur_texte(QColor(0,0,255,255));
				bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
				connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
				objets->addWidget(bouton_);
			}
			//foreach(EffectifQuantite e,inventaire.objets_soins_ut())
		}else{
			foreach(uchar c,inventaire.cs_ut().cles()){
				QString attaque_=donnees->val_cs().valeur(c);
				fiche_description.ajouter_cle_valeur(attaque_,donnees->val_attaques().valeur(attaque_)->description(attaque_,langue,donnees));
				BoutonObjet *bouton_=new BoutonObjet(attaque_,-c,inventaire,donnees);
				bouton_->maj_couleur_fond(QColor(255,255,255,255));
				bouton_->maj_couleur_texte(QColor(0,0,255,255));
				bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
				connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
				objets->addWidget(bouton_);
			}
		}
	}
	objets->itemAt(0)->widget()->setFixedHeight(20);
	objets->parentWidget()->setFixedHeight(20+objets->count()*objets->itemAt(1)->widget()->height());
	objets->parentWidget()->setMinimumWidth(300);
	switch(type_objet){
		case GestionInventaire::BAIE:
		case GestionInventaire::BOOST:
		case GestionInventaire::PIERRE_EVO:
		case GestionInventaire::REPOUSSE:
		case GestionInventaire::SOIN:{
			bouton_act_=new Bouton("Utiliser");
			connect(bouton_act_,SIGNAL(clic(QString)),this,SLOT(utiliser()));
			bouton_act_->maj_couleur_fond(QColor(255,255,255,255));
			bouton_act_->maj_couleur_rectangle(QColor(0,0,255,255));
			bouton_act_->maj_couleur_texte(QColor(0,0,255,255));
			actions->addWidget(bouton_act_);
		}
		default:
		break;
	}
	/*switch(type_objet){
		case GestionInventaire::CT:
		case GestionInventaire::CS:{
			bouton_act_=new Bouton("Apprendre");
			bouton_act_->maj_couleur_fond(QColor(255,255,255,255));
			bouton_act_->maj_couleur_rectangle(QColor(0,0,255,255));
			bouton_act_->maj_couleur_texte(QColor(0,0,255,255));
			actions->addWidget(bouton_act_);
		}
		default:
		break;
	}*/
	bouton_act_=new Bouton("Annuler");
	connect(bouton_act_,SIGNAL(clic(QString)),this,SLOT(annuler()));
	bouton_act_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_act_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_act_->maj_couleur_texte(QColor(0,0,255,255));
	actions->addWidget(bouton_act_);
	bouton_act_=new Bouton("Finir");
	connect(bouton_act_,SIGNAL(clic(QString)),this,SLOT(finir()));
	bouton_act_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_act_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_act_->maj_couleur_texte(QColor(0,0,255,255));
	actions->addWidget(bouton_act_);
	actions->parentWidget()->setMinimumHeight(actions->count()*40);
	actions->parentWidget()->setMinimumWidth(80);
	/*switch(type_objet){
		case GestionInventaire::BAIE:
		case GestionInventaire::BOOST:
		case GestionInventaire::PIERRE_EVO:
		case GestionInventaire::REPOUSSE:
		case GestionInventaire::SOIN:{
			bouton_act_=new Bouton("Utiliser");
			bouton_act_->maj_couleur_fond(QColor(255,255,255,255));
			bouton_act_->maj_couleur_rectangle(QColor(0,0,255,255));
			bouton_act_->maj_couleur_texte(QColor(0,0,255,255));
			actions->addWidget(bouton_act_);
		}
		default:
		break;
	}*/
	//BAIE,BALL,BOOST,FOSSILE,PLAQUE,OBJET_ATTACHABLE,OBJET_EVO,PIERRE_EVO,REPOUSSE,REVENTE,SOIN
	/**contient les actions ATTACHER, UTILISER (BAIE,BOOST,PIERRE_EVO,REPOUSSE,SOIN), ANNULER, FINIR*/
	/*Bouton *bouton_act_=new Bouton("Attacher");
	bouton_act_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_act_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_act_->maj_couleur_texte(QColor(0,0,255,255));
	actions->addWidget(bouton_act_);*/
}

void GestionInventaire::maj_objet(const QString& _obj){
	objet_selectionne=_obj;
	quantite_selectionnee=-1;
	if(type_objet!=GestionInventaire::CT&&type_objet!=GestionInventaire::CS){
		description->setPlainText(_obj+":\n"+fiche_description.valeur(_obj));
	}else{
		description->setPlainText(_obj+":\n"+fiche_description.valeur(_obj));
		emit apprendre(type_objet);
	}
}

void GestionInventaire::maj_objet(const QString& _obj,int _quantite){
	objet_selectionne=_obj;
	quantite_selectionnee=_quantite;
	description->setPlainText(_obj+":\n"+fiche_description.valeur(_obj));
}

void GestionInventaire::attacher(){
	if(objet_selectionne!=""){
		emit attacher_obj();
	}
}

void GestionInventaire::utiliser(){
	if(objet_selectionne!=""){
		emit utiliser(type_objet);
	}
}

void GestionInventaire::annuler(){
	objet_selectionne="";
	quantite_selectionnee=-1;
	description->setPlainText("");
}

void GestionInventaire::finir(){
	objet_selectionne="";
	quantite_selectionnee=-1;
	description->setPlainText("");
	emit gestion_finie();
}

/*void GestionInventaire::apprendre(){
	if(objet_selectionne!=""){
		emit apprendre(type_objet);
	}
}*/
