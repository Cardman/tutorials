#include "ihm/dialogue/dialoguenenvir.h"
#include "ihm/fenetre.h"
#include "serialisable/cartes/environnement.h"
#include "serialisable/cartes/environnementligue.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QStringList>
#include <QComboBox>
#include <QString>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

const HashMap<QString,QStringList> DialogueNEnvir::_elements_ihm_=DialogueNEnvir::init_elements_ihm();

HashMap<QString,QStringList> DialogueNEnvir::init_elements_ihm(){
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

QString DialogueNEnvir::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}


QString DialogueNEnvir::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueNEnvir::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueNEnvir::DialogueNEnvir(int _langue,QWidget *_parent):QDialog(_parent){
	langue=_langue;
	setWindowTitle(traduire("TITRE"));
	type=new QComboBox();//TODO traduire de la langue vers le francais pour le retour
	foreach(QString l,Import::_noms_envir_){
		type->addItem(l.split("\t")[langue]);
	}
	type->addItem("");
	Fenetre *parent_=qobject_cast<Fenetre*>(_parent);
	QFormLayout *form_=new QFormLayout();
	form_->addRow(traduire("TYPE"),type);
	largeur=new QSpinBox();
	largeur->setRange(1,255);
	largeur->setValue(1);
	//TODO slot pour changer l'aspect de la grille
	form_->addRow(traduire("LARGEUR"),largeur);
	connect(largeur,SIGNAL(valueChanged(int)),this,SLOT(fin_ecriture_dims()));
	hauteur=new QSpinBox();
	hauteur->setRange(1,255);
	hauteur->setValue(1);
	//TODO slot pour changer l'aspect de la grille
	form_->addRow(traduire("HAUTEUR"),hauteur);
	connect(hauteur,SIGNAL(valueChanged(int)),this,SLOT(fin_ecriture_dims()));
	connect(this,SIGNAL(dims(const QPair<int,int>&)),parent_,SLOT(maj_dims_env(const QPair<int,int>&)));
	connect(this,SIGNAL(rejected()),parent_,SLOT(maj_dims_env2()));
	connect(this,SIGNAL(accepted()),parent_,SLOT(maj_dims_env2()));
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	form_->addRow("",valider_);
	setLayout(form_);
}

void DialogueNEnvir::fin_ecriture_dims(){
	emit dims(QPair<int,int>(largeur->value(),hauteur->value()));
}

Environnement DialogueNEnvir::nv_envir()const{
	QString type_env_=type->currentText();
	if(type_env_==""){
		return Environnement(largeur->value(),hauteur->value(),"");
	}
	return Environnement(largeur->value(),hauteur->value(),traduire_revert(Import::_noms_envir_,type_env_,langue));
}

EnvironnementLigue DialogueNEnvir::nv_envir_ligue()const{
	QString type_env_=type->currentText();
	if(type_env_==""){
		return EnvironnementLigue(largeur->value(),hauteur->value(),"");
	}
	return EnvironnementLigue(largeur->value(),hauteur->value(),traduire_revert(Import::_noms_envir_,type_env_,langue));
}


