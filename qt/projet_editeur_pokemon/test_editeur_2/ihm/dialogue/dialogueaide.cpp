#include "ihm/dialogue/dialogueaide.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QTextEdit>
#include <QVBoxLayout>

const QStringList DialogueAide::_aide_=DialogueAide::init_aide();

const QStringList DialogueAide::_titre_=DialogueAide::init_titre();

QStringList DialogueAide::init_titre(){
	QStringList titre_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/ihm_texte/"+QString(__FILE__).split(QRegExp("\\\\|/")).last().split(".")[0]).split("\n");
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/ihm_texte/"+QString(__FILE__).split("/").last().split(".")[0]+".txt").split("\n");
#endif
	foreach(QString l,lignes_){
		QStringList infos_l_=l.split("\t");
		titre_<<infos_l_;
	}
	return titre_;
}

QStringList DialogueAide::init_aide(){
	QStringList aide_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/ihm/aide").split("\n");
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/ihm/aide.txt").split("\n");
#endif
	int nb_langues_=lignes_[0].count("\t")+1;
	for(int i=0;i<nb_langues_;i++){
		aide_<<"";
	}
	for(int i=0;i<nb_langues_;i++){
		foreach(QString l,lignes_){
			if(l!=""){
				aide_[i]+=Utilitaire::formatter(l.split("\t")[i],QStringList());
			}
			aide_[i]+="\n";
		}
	}
	return aide_;
}

DialogueAide::DialogueAide(int _langue,QWidget* _parent):QDialog(_parent){
	setWindowTitle(_titre_[_langue]);
	QTextEdit *aide_=new QTextEdit();
	aide_->setPlainText(_aide_[_langue]);
	aide_->setReadOnly(true);
	QVBoxLayout *lay_=new QVBoxLayout();
	lay_->addWidget(aide_);
	setLayout(lay_);
}


