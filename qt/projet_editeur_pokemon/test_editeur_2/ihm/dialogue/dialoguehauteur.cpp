#include "ihm/dialogue/dialoguehauteur.h"
#include "ihm/panneau/panneauediteurenv.h"
#include "ihm/panneau/panneaudresseurligue.h"
#include "ihm/fenetre.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QStringList>
#include <QString>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>

const HashMap<QString,QStringList> DialogueHauteur::_elements_ihm_=DialogueHauteur::init_elements_ihm();

HashMap<QString,QStringList> DialogueHauteur::init_elements_ihm(){
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

QString DialogueHauteur::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}


DialogueHauteur::DialogueHauteur(int _langue,int _hauteur,QWidget *_parent):QDialog(_parent){
	langue=_langue;
	setWindowTitle(traduire("TITRE"));
	Fenetre *parent_=qobject_cast<Fenetre*>(_parent);
	QFormLayout *form_=new QFormLayout();
	hauteur=new QSpinBox();
	hauteur->setRange(1,255);
	hauteur->setValue(_hauteur);
	connect(hauteur,SIGNAL(valueChanged(int)),this,SLOT(fin_ecriture_dims()));
	form_->addRow(traduire("HAUTEUR"),hauteur);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(this,SIGNAL(dims(const QPair<int,int>&)),parent_,SLOT(maj_dims_env(const QPair<int,int>&)));
	connect(this,SIGNAL(rejected()),parent_,SLOT(maj_dims_env2()));
	connect(this,SIGNAL(accepted()),parent_,SLOT(maj_dims_env2()));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	form_->addRow("",valider_);
	setLayout(form_);
}

void DialogueHauteur::fin_ecriture_dims(){
	if(PanneauEditerEnv::_environnement_en_cours_!=NULL){
		emit dims(QPair<int,int>(PanneauEditerEnv::_environnement_en_cours_->dimensions().first,hauteur->value()));
	}else{
		emit dims(QPair<int,int>(PanneauDresseurLigue::_environnement_ligue_en_cours_->dimensions().first,hauteur->value()));
	}
}

int DialogueHauteur::hauteur_v()const{
	return hauteur->value();
}


