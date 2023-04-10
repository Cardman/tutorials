#include "ihm/dialogue/dialoguegrille.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QStringList>
#include <QString>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>

const HashMap<QString,QStringList> DialogueGrille::_elements_ihm_=DialogueGrille::init_elements_ihm();

HashMap<QString,QStringList> DialogueGrille::init_elements_ihm(){
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

QString DialogueGrille::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

DialogueGrille::DialogueGrille(int _langue,Fonction _fct,QWidget *_parent):QDialog(_parent){
	QFormLayout *form_=new QFormLayout();
	langue=_langue;
	colonnes_lignes=new QSpinBox();
	colonnes_lignes->setRange(1,255*255);
	colonnes_lignes->setValue(1);
	if(_fct==AJOUT_LGS_HAUT){
		setWindowTitle(traduire("TITRE_L_H"));
		form_->addRow(traduire("NOMBRE_L"),colonnes_lignes);
	}else if(_fct==AJOUT_COLS_GAUCHE){
		setWindowTitle(traduire("TITRE_C_G"));
		form_->addRow(traduire("NOMBRE_C"),colonnes_lignes);
	}else if(_fct==AJOUT_LGS_BAS){
		setWindowTitle(traduire("TITRE_L_B"));
		form_->addRow(traduire("NOMBRE_L"),colonnes_lignes);
	}else{
		setWindowTitle(traduire("TITRE_C_D"));
		form_->addRow(traduire("NOMBRE_C"),colonnes_lignes);
	}
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	form_->addRow("",valider_);
	setLayout(form_);
}

int DialogueGrille::valeur()const{
	return colonnes_lignes->value();
}


