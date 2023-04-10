#include "ihm/dialogue/dialoguenlieu.h"
#include "base_donnees/import.h"
#include "serialisable/cartes/lieu.h"
#include "autre/utilitaire.h"
#include <QLineEdit>
#include <QString>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

const HashMap<QString,QStringList> DialogueNLieu::_elements_ihm_=DialogueNLieu::init_elements_ihm();

HashMap<QString,QStringList> DialogueNLieu::init_elements_ihm(){
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

QString DialogueNLieu::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString DialogueNLieu::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueNLieu::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueNLieu::DialogueNLieu(int _langue,QWidget *_parent):QDialog(_parent){
	langue=_langue;
	setWindowTitle(traduire("TITRE"));
	//accepte=false
	QFormLayout *form_=new QFormLayout();
	foreach(QString l,Import::_langues_.cles()){
		QLineEdit *nom_=new QLineEdit();
		QStringList args_;
		args_<<Import::_langues_.valeur(l)[langue];
		form_->addRow(Utilitaire::formatter(traduire("NOM"),args_),nom_);
		noms<<nom_;
	}
	/*nom=new QLineEdit()
	form_->addRow("Nom :",nom)*/
	type=new QComboBox();
	foreach(QString l,Import::_type_lieux_){
		type->addItem(l.split("\t")[langue]);
		//type->addItem(traduire(Import::_type_lieux_,l,langue))
	}
	//TODO ajouter type de lieux
	form_->addRow(traduire("TYPE"),type);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	//connect(valider_,SIGNAL(clicked()),this,SLOT(accepter()))
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	form_->addRow("",valider_);
	setLayout(form_);
}

/*void DialogueNLieu::accepter(){
	accepte=true
	close()
}

bool DialogueNLieu::acceptation(){
	return accepte
}*/

void DialogueNLieu::maj_nom_type(const QPair<QString,QString>& _nom_type){
	setWindowTitle(traduire("TITRE_2"));
	int nb_champs_=noms.size();
	QStringList ls_=_nom_type.first.split("\t");
	for(int i=0;i<nb_champs_;i++){
		noms[i]->setText(ls_[i]);
	}
	type->setCurrentIndex(type->findText(traduire(Import::_type_lieux_,_nom_type.second,langue)));
}

QPair<QString,QString> DialogueNLieu::nom_type()const{
	QString noms_=noms[0]->text();
	int nb_champs_=noms.size();
	for(int i=1;i<nb_champs_;i++){
		noms_+="\t"+noms[i]->text();
	}
	return QPair<QString,QString>(noms_,traduire_revert(Import::_type_lieux_,type->currentText(),langue));
}

Lieu DialogueNLieu::nv_lieu()const{
	Lieu lieu_;
	QString noms_=noms[0]->text();
	int nb_champs_=noms.size();
	for(int i=1;i<nb_champs_;i++){
		noms_+="\t"+noms[i]->text();
	}
	*lieu_.adr_nom()=noms_;
	//*lieu_.adr_nom()=nom->text()
	*lieu_.adr_type()=traduire_revert(Import::_type_lieux_,type->currentText(),langue);
	return lieu_;
}


