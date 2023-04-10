#include "ihm/dialogue/dialogueselectligue.h"
#include "ihm/fenetre.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QTableWidget>
#include <QSplitter>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStringList>

const HashMap<QString,QStringList> DialogueSelectLigue::_elements_ihm_=DialogueSelectLigue::init_elements_ihm();

HashMap<QString,QStringList> DialogueSelectLigue::init_elements_ihm(){
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

QString DialogueSelectLigue::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

DialogueSelectLigue::DialogueSelectLigue(int _langue,bool _a_suppr,QWidget* _parent):QDialog(_parent){
	langue=_langue;
	if(_a_suppr){
		setWindowTitle(traduire("TITRE_S"));
	}else{
		setWindowTitle(traduire("TITRE"));
	}
	cles_ligues=qobject_cast<Fenetre*>(_parent)->donnees_actuelles().ligues_c();
	int nb_pl_=cles_ligues.size();
	QVBoxLayout *centre_=new QVBoxLayout();
	table=new QTableWidget(nb_pl_,1);
	for(int i=0;i<nb_pl_;i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText(QString::number(i));
		table->setItem(i,0,element_);
	}
	centre_->addWidget(table);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	centre_->addWidget(valider_);
	setLayout(centre_);
}

int DialogueSelectLigue::ligue_select()const{
	if(table->currentRow()<0||table->currentRow()>=cles_ligues.size()){
		return -1;
	}
	return cles_ligues[table->currentRow()];
}


