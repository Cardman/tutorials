#include "ihm/dialogue/dialogueobjet.h"
#include "base_donnees/import.h"
#include "base_donnees/objets/baie.h"
#include "base_donnees/objets/ball.h"
#include "base_donnees/objets/boost.h"
#include "base_donnees/objets/fossile.h"
#include "base_donnees/objets/objetattachablecombat.h"
#include "base_donnees/objets/objetevo.h"
#include "base_donnees/objets/pierreevo.h"
#include "base_donnees/objets/plaque.h"
#include "base_donnees/objets/module.h"
#include "base_donnees/objets/repousse.h"
#include "base_donnees/objets/revente.h"
#include "base_donnees/objets/soinpvstatut.h"
#include "base_donnees/objets/soinpv.h"
#include "base_donnees/objets/soinpp.h"
#include "autre/utilitaire.h"
#include <QStringList>
#include <QComboBox>
#include <QString>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>

const HashMap<QString,QStringList> DialogueObjet::_elements_ihm_=DialogueObjet::init_elements_ihm();

HashMap<QString,QStringList> DialogueObjet::init_elements_ihm(){
	HashMap<QString,QStringList> elements_ihm_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/ihm_texte/"+QString(__FILE__).split(QRegExp("\\\\|/")).last().split(".")[0]).split("\n");
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/ihm_texte/"+QString(__FILE__).split("/").last().split(".")[0]+".txt").split("\n");
#endif
	foreach(QString l,lignes_){
		QStringList infos_l_=l.split("\t");
		elements_ihm_.ajouter_cle_valeur(infos_l_[0],QStringList(infos_l_.mid(1)));
	}
	return elements_ihm_;
}

QString DialogueObjet::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString DialogueObjet::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueObjet::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueObjet::DialogueObjet(int _langue,QWidget *_parent):QDialog(_parent){
	langue=_langue;
	setWindowTitle(traduire("TITRE"));
	objet=new QComboBox();//TODO traduire de la langue vers le francais pour le retour
	foreach(QString l,Import::_objets_.cles()){
		objet->addItem(traduire(Import::_noms_objets_,l,langue));
	}
	objet->setEditable(true);
	QFormLayout *form_=new QFormLayout();
	connect(objet,SIGNAL(editTextChanged(QString)),this,SLOT(descr_obj()));
	form_->addRow(traduire("NOM"),objet);
	type=new QLabel();
	form_->addRow(traduire("TYPE"),type);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	form_->addRow("",valider_);
	setLayout(form_);
}

void DialogueObjet::editer_objet(const QString& _obj){
	setWindowTitle(traduire("TITRE_2"));
	objet->setEditText(traduire(Import::_noms_objets_,_obj,langue));
	Objet *obj_=Import::_objets_.valeur(_obj);
	if(qobject_cast<Ball*>(obj_)){
		type->setText(traduire("BALL"));
	}else if(qobject_cast<Baie*>(obj_)){
		type->setText(traduire("BAIE"));
	}else if(qobject_cast<Boost*>(obj_)){
		type->setText(traduire("BOOST"));
	}else if(qobject_cast<Fossile*>(obj_)){
		type->setText(traduire("FOSSILE"));
	}else if(qobject_cast<Module*>(obj_)){
		type->setText(traduire("MODULE"));
	}else if(qobject_cast<ObjetAttachableCombat*>(obj_)){
		type->setText(traduire("OBJET_CBT_ATTAC"));
	}else if(qobject_cast<ObjetEvo*>(obj_)){
		type->setText(traduire("OBJET_EVO"));
	}else if(qobject_cast<PierreEvo*>(obj_)){
		type->setText(traduire("PIERRE_EVO"));
	}else if(qobject_cast<Plaque*>(obj_)){
		type->setText(traduire("PLAQUE"));
	}else if(qobject_cast<Repousse*>(obj_)){
		type->setText(traduire("REPOUSSE"));
	}else if(qobject_cast<Revente*>(obj_)){
		type->setText(traduire("REVENTE"));
	}else if(qobject_cast<SoinPP*>(obj_)){
		type->setText(traduire("SOIN_PP"));
	}else if(qobject_cast<SoinPVStatut*>(obj_)){
		type->setText(traduire("SOIN_PV_STATUT"));
	}else if(qobject_cast<SoinPV*>(obj_)){
		type->setText(traduire("SOIN_PV"));
	}else if(qobject_cast<SoinStatut*>(obj_)){
		type->setText(traduire("SOIN_STATUT"));
	}else if(qobject_cast<Soin*>(obj_)){
		type->setText(traduire("SOIN_TOTAL"));
	}
}

void DialogueObjet::descr_obj(){
	if(objet->findText(objet->currentText())<0){
		return;
	}
	QString obj_fr_=traduire_revert(Import::_noms_objets_,objet->currentText(),langue);
	if(Import::_objets_.cles().contains(obj_fr_)){
		editer_objet(obj_fr_);
	}
}

QString DialogueObjet::nv_obj()const{
	if(objet->findText(objet->currentText())<0){
		return "";
	}
	QString obj_fr_=traduire_revert(Import::_noms_objets_,objet->currentText(),langue);
	if(!Import::_objets_.cles().contains(obj_fr_)){
		return "";
	}
	return obj_fr_;
}


