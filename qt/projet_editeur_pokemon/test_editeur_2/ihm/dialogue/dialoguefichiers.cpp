#include "ihm/dialogue/dialoguefichiers.h"
#include "ihm/dialogue/liste/listefichiers.h"
#include "ihm/dialogue/liste/listedossiers.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QMessageBox>
#include <QLineEdit>

const HashMap<QString,QStringList> DialogueFichiers::_elements_ihm_=DialogueFichiers::init_elements_ihm();

HashMap<QString,QStringList> DialogueFichiers::init_elements_ihm(){
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

QString DialogueFichiers::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

DialogueFichiers::DialogueFichiers(const QString& _ch,int _langue,Actions _act,QWidget *_parent):QDialog(_parent){
	langue=_langue;
	if(_act==CHARGER){
		setWindowTitle(traduire("TITRE_C"));
	}else if(_act==SAUVEGARDER){
		setWindowTitle(traduire("TITRE_S"));
	}else{
		setWindowTitle(traduire("TITRE_E"));
	}
	action=_act;
	//setWhatsThis("boite de dialogue");
	clique_image=false;
	champ_fichier=NULL;
	QVBoxLayout *centre_;
	centre_=new QVBoxLayout();
	QSplitter *separateur_;
	QString rac_act_=_ch.left(_ch.indexOf(QDir::separator())+1);
	if(_act==SAUVEGARDER||_act==EXPORTER){
		ls_fichiers=new ListeFichiers(_ch);
		ls_dossiers=new ListeDossiers(_ch,rac_act_);
		connect(ls_dossiers,SIGNAL(dossier_selectionne(const QString&)),ls_fichiers,SLOT(maj_liste(const QString&)));
		separateur_=new QSplitter();
		separateur_->addWidget(ls_dossiers);
		separateur_->addWidget(ls_fichiers);
		centre_->addWidget(separateur_);
		champ_fichier=new QLineEdit();
		QRegExpValidator *exp_reg_=new QRegExpValidator(0);
		exp_reg_->setRegExp(QRegExp(Import::constante("EXP_REG_BASE_FICHIER")));
		champ_fichier->setValidator(exp_reg_);
		//champ_fichier->setPlaceholderText(traduire("CHAMP_FICHIER"))
		champ_fichier->setText(traduire("CHAMP_FICHIER"));
		connect(champ_fichier,SIGNAL(returnPressed()),this,SLOT(sauvegarde()));
		centre_->addWidget(champ_fichier);
	}else{
		ls_fichiers=new ListeFichiers(_ch);
		connect(ls_fichiers,SIGNAL(fichier_selectionne(QModelIndex)),this,SLOT(choix_fichier(QModelIndex)));
		ls_dossiers=new ListeDossiers(_ch,rac_act_);
		connect(ls_dossiers,SIGNAL(dossier_selectionne(const QString&)),ls_fichiers,SLOT(maj_liste(const QString&)));
		separateur_=new QSplitter();
		separateur_->addWidget(ls_dossiers);
		separateur_->addWidget(ls_fichiers);
		centre_->addWidget(separateur_);
	}
	setLayout(centre_);
	connect(this,SIGNAL(accepted()),this,SLOT(close()));
}

void DialogueFichiers::closeEvent(QCloseEvent* _event){
	if(!clique_image){
		nom_fichier="";
	}
	_event->accept();
}


void DialogueFichiers::choix_fichier(const QModelIndex& _indice){
	QFileSystemModel *modele_=qobject_cast<QFileSystemModel*>(ls_fichiers->model());
	if(action!=SAUVEGARDER&&action!=EXPORTER){
		//Ensemble des dossiers parent
		nom_fichier=modele_->filePath(_indice).replace('/',QDir::separator());
		if(action==CHARGER||nom_fichier.endsWith(".png")){
			clique_image=true;
			emit accepted();
		}
	}
}

void DialogueFichiers::sauvegarde(){
	QString fichier_sauver_=champ_fichier->text();
	QFileSystemModel *modele_=qobject_cast<QFileSystemModel*>(ls_dossiers->model());
	//dossiers
	QModelIndex indice_=ls_fichiers->currentIndex();
	QString fichier_=modele_->filePath(indice_).replace('/',QDir::separator());
	fichier_+=QDir::separator()+fichier_sauver_;
	if(action==EXPORTER){
		if(fichier_sauver_.contains(".")){
			if(!fichier_sauver_.endsWith(".xml")){
				return;
			}
		}else{
			fichier_+=".xml";
		}
	}
	if(!QFile::exists(fichier_)){
		clique_image=true;
		nom_fichier=fichier_;
		emit accepted();
	}else{
		QStringList args_;
		args_<<fichier_;
		int reponse_=QMessageBox::question(this,traduire("FICHIER_EXIST"),Utilitaire::formatter(traduire("ECRASER"),args_),QMessageBox::Yes|QMessageBox::No);
		if(reponse_==QMessageBox::Yes){
			clique_image=true;
			nom_fichier=fichier_;
			emit accepted();
		}
	}
}

QString DialogueFichiers::nom_fic()const{
	return nom_fichier;
}


