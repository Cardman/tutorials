#include "ihm/dialogue/dialoguecapsules.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QLabel>
#include <QComboBox>
#include <QTableWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QCloseEvent>
#include <QMessageBox>

const HashMap<QString,QStringList> DialogueCapsules::_elements_ihm_=DialogueCapsules::init_elements_ihm();

HashMap<QString,QStringList> DialogueCapsules::init_elements_ihm(){
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

QString DialogueCapsules::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}


DialogueCapsules::DialogueCapsules(int _langue,bool _ct,QWidget* _parent):QDialog(_parent){
	langue=_langue;
	rejeter=true;
	ct=_ct;
	QFormLayout *centre_=new QFormLayout();
	nom_capsule=new QComboBox();
	QStringList args_;
	if(ct){
		args_<<traduire("TECHNIQUES");
		setWindowTitle(Utilitaire::formatter(traduire("TITRE"),args_));
		foreach(uchar l,Import::_ct_.cles()){
			nom_capsule->addItem(QString::number(l));
		}
		nom_capsule->setEditable(true);
		connect(nom_capsule,SIGNAL(editTextChanged(QString)),this,SLOT(maj_capsule(QString)));
		args_.clear();
		args_<<traduire("TECHNIQUE");
		centre_->addRow(Utilitaire::formatter(traduire("NUMERO_CAPSULE"),args_),nom_capsule);
		capsule=new QLabel(Import::_ct_.valeur(nom_capsule->currentText().toUInt()));
		centre_->addRow(Utilitaire::formatter(traduire("NOM_ATTAQUE"),args_),capsule);
	}else{
		args_<<traduire("SECRETES");
		setWindowTitle(Utilitaire::formatter(traduire("TITRE"),args_));
		foreach(uchar l,Import::_cs_.cles()){
			nom_capsule->addItem(QString::number(l));
		}
		nom_capsule->setEditable(true);
		connect(nom_capsule,SIGNAL(editTextChanged(QString)),this,SLOT(maj_capsule(QString)));
		args_.clear();
		args_<<traduire("TECHNIQUE");
		centre_->addRow(Utilitaire::formatter(traduire("NUMERO_CAPSULE"),args_),nom_capsule);
		capsule=new QLabel(Import::_cs_.valeur(nom_capsule->currentText().toUInt()));
		centre_->addRow(Utilitaire::formatter(traduire("NOM_ATTAQUE"),args_),capsule);
	}
	QStringList ls_;
	ls_<<traduire("ETIQUETTE_NUMERO_CAPSULE");
	ls_<<traduire("ETIQUETTE_NOM_ATTAQUE");
	table_capsules=new QTableWidget(1,ls_.size());
	table_capsules->setHorizontalHeaderLabels(ls_);
	for(int i=0;i<ls_.size();i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText("");
		table_capsules->setItem(0,i,element_);
	}
	centre_->addRow(table_capsules);
	QPushButton *bouton_;
	bouton_=new QPushButton(traduire("AJOUTER_CAPSULE"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajout_capsule()));
	QPushButton *bouton_2_;
	bouton_2_=new QPushButton(traduire("SUPPRIMER_CAPSULE"));
	connect(bouton_2_,SIGNAL(clicked()),this,SLOT(suppression_capsule()));
	centre_->addRow(bouton_,bouton_2_);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(acceptation()));
	centre_->addRow("",valider_);
	setLayout(centre_);
}


void DialogueCapsules::maj_liste(const QList<uchar>& _liste){
	capsules=_liste;
	int nb_objs_=capsules.size();
	table_capsules->setRowCount(nb_objs_);
	int nb_cols_=table_capsules->columnCount();
	for(int i=1;i<nb_objs_;i++){
		for(int j=0;j<nb_cols_;j++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText("");
			table_capsules->setItem(i,j,element_);
		}
	}
	QStringList args_;
	if(ct){
		args_<<traduire("TECHNIQUES");
		setWindowTitle(Utilitaire::formatter(traduire("TITRE_2"),args_));
		for(int i=0;i<nb_objs_;i++){
			table_capsules->item(i,0)->setText(QString::number(capsules[i]));
			table_capsules->item(i,1)->setText(Import::_ct_.valeur(capsules[i]));
		}
	}else{
		args_<<traduire("SECRETES");
		setWindowTitle(Utilitaire::formatter(traduire("TITRE_2"),args_));
		for(int i=0;i<nb_objs_;i++){
			table_capsules->item(i,0)->setText(QString::number(capsules[i]));
			table_capsules->item(i,1)->setText(Import::_cs_.valeur(capsules[i]));
		}
	}
}

QList<uchar> DialogueCapsules::nv_liste()const{
	return capsules;
}

bool DialogueCapsules::rejete()const{
	return rejeter;
}

void DialogueCapsules::maj_capsule(const QString& _capsule){
	if(nom_capsule->findText(_capsule)<0){
		return;
	}
	QString nom_attaque_;
	if(ct){
		nom_attaque_=Import::_ct_.valeur(_capsule.toUInt());
	}else{
		nom_attaque_=Import::_cs_.valeur(_capsule.toUInt());
	}
	capsule->setText(nom_attaque_);
}

void DialogueCapsules::ajout_capsule(){
	QString capsule_=nom_capsule->currentText();
	//if(!Import::_attaques_.cles().contains(attaque_)){//||nom_attaque_pk.findText(attaque_)<0
	if(nom_capsule->findText(capsule_)<0){
		if(ct){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("CAPSULE_T_INEX"));
		}else{
			QMessageBox::critical(this,traduire("ERREUR"),traduire("CAPSULE_S_INEX"));
		}
		return;
	}
	if(capsules.contains(nom_capsule->currentText().toUInt())){
		if(ct){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("CAPSULE_T_DEJA_PRESENTE"));
		}else{
			QMessageBox::critical(this,traduire("ERREUR"),traduire("CAPSULE_S_DEJA_PRESENTE"));
		}
		return;
	}
	QString nom_attaque_;
	if(ct){
		nom_attaque_=Import::_ct_.valeur(capsule_.toUInt());
	}else{
		nom_attaque_=Import::_cs_.valeur(capsule_.toUInt());
	}
	int nb_capsules_=capsules.size();
	int nb_lignes_=table_capsules->rowCount();
	if(nb_capsules_==nb_lignes_){
		table_capsules->setRowCount(nb_capsules_+1);
		int nb_cols_=table_capsules->columnCount();
		for(int j=0;j<nb_cols_;j++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText("");
			table_capsules->setItem(nb_capsules_,j,element_);
		}
	}
	QTableWidgetItem *element_=table_capsules->item(nb_capsules_,0);
	element_->setText(capsule_);
	element_=table_capsules->item(nb_capsules_,1);
	element_->setText(nom_attaque_);
	capsules<<capsule_.toUInt();
	if(ct){
		QMessageBox::information(this,traduire("SUCCES"),traduire("CAPSULE_T_AJ"));
	}else{
		QMessageBox::information(this,traduire("SUCCES"),traduire("CAPSULE_S_AJ"));
	}
}

void DialogueCapsules::suppression_capsule(){
	if(table_capsules->currentRow()<0||table_capsules->currentRow()>=capsules.size()){
		if(ct){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("CAPSULE_T_INEX"));
		}else{
			QMessageBox::critical(this,traduire("ERREUR"),traduire("CAPSULE_S_INEX"));
		}
		return;
	}
	int indice_=table_capsules->currentRow();
	int nb_capsules_=capsules.size()-1;
	int nb_c_=table_capsules->columnCount();
	for(int i=indice_;i<nb_capsules_;i++){
		for(int j=0;j<nb_c_;j++){
			QTableWidgetItem *element_=table_capsules->item(i,j);
			element_->setText(table_capsules->item(i+1,j)->text());
		}
	}
	int nb_l_=table_capsules->rowCount();
	for(int i=nb_capsules_;i<nb_l_;i++){
		for(int j=0;j<nb_c_;j++){
			QTableWidgetItem *element_=table_capsules->item(i,j);
			element_->setText("");
		}
	}
	capsules.removeAt(indice_);
	if(ct){
		QMessageBox::information(this,traduire("SUCCES"),traduire("CAPSULE_T_SUPPR"));
	}else{
		QMessageBox::information(this,traduire("SUCCES"),traduire("CAPSULE_S_SUPPR"));
	}
}

void DialogueCapsules::acceptation(){
	rejeter=false;
	close();
}

void DialogueCapsules::closeEvent(QCloseEvent* _ev){
	if(rejeter){
		return;
	}
	QString err_;
	if(capsules.isEmpty()){
		err_+=traduire("PAS_CAPSULE");
	}
	if(err_!=""){
		rejeter=true;
		_ev->ignore();
		QMessageBox::critical(this,traduire("ERREUR"),err_);
	}
}


