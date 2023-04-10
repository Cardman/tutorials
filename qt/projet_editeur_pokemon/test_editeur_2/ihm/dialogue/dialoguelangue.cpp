#include "ihm/dialogue/dialoguelangue.h"
#include "base_donnees/import.h"
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>

DialogueLangue::DialogueLangue():QDialog(NULL){
	QList<QString> cles_l_=Import::_langues_.cles();
	setWindowTitle("\t");
	QVBoxLayout *lay_=new QVBoxLayout();
	choix=new QButtonGroup();
	int nb_langues_=cles_l_.size();
	for(int i=0;i<nb_langues_;i++){
		QRadioButton *radio_=new QRadioButton(Import::_langues_.valeur(cles_l_[i])[i]);
		connect(radio_,SIGNAL(clicked()),this,SLOT(choix_de_langue()));
		choix->addButton(radio_,i);
		lay_->addWidget(radio_);
	}
	setLayout(lay_);
}

int DialogueLangue::choix_b(){
	DialogueLangue *dial_=new DialogueLangue();
	dial_->exec();
	int langue_=dial_->choix_l;
	delete dial_;
	dial_=NULL;
	return langue_;
}

void DialogueLangue::choix_de_langue(){
	choix_l=choix->checkedId();
	close();
}

DialogueLangue::~DialogueLangue(){
	delete choix;
	choix=NULL;
}


