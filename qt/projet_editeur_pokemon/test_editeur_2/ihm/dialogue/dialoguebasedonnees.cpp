#include "ihm/dialogue/dialoguebasedonnees.h"
#include "base_donnees/import.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/capacites/fichecapacite.h"
#include "base_donnees/objets/objet.h"
#include "base_donnees/attaques/ficheattaque.h"
#include "autre/utilitaire.h"
#include <QTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>

const HashMap<QString,QStringList> DialogueBaseDonnees::_elements_ihm_=DialogueBaseDonnees::init_elements_ihm();

HashMap<QString,QStringList> DialogueBaseDonnees::init_elements_ihm(){
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

QString DialogueBaseDonnees::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString DialogueBaseDonnees::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueBaseDonnees::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueBaseDonnees::DialogueBaseDonnees(int _langue,QWidget* _parent):QDialog(_parent){
	langue=_langue;
	setWindowTitle(traduire("TITRE"));
	QGridLayout *lay_=new QGridLayout();
	lay_->addWidget(new QLabel(traduire("NOM_POKEMON")),0,0);
	combo_pk=new QComboBox();
	foreach(QString n,Import::_pokedex_.cles()){
		combo_pk->addItem(traduire(Import::_noms_pk_,n,langue));
	}
	combo_pk->setEditable(true);
	connect(combo_pk,SIGNAL(editTextChanged(QString)),this,SLOT(maj_descr_pk()));
	lay_->addWidget(combo_pk,0,1);
	lay_->addWidget(new QLabel(traduire("DESCRIPTION_POKEMON")),0,2);
	descr_pk=new QTextEdit();
	lay_->addWidget(descr_pk,0,3);
	lay_->addWidget(new QLabel(traduire("NOM_CAPACITE")),1,0);
	combo_capac=new QComboBox();
	foreach(QString n,Import::_capacites_.cles()){
		combo_capac->addItem(traduire(Import::_noms_capacites_,n,langue));
	}
	combo_capac->setEditable(true);
	connect(combo_capac,SIGNAL(editTextChanged(QString)),this,SLOT(maj_descr_capac()));
	lay_->addWidget(combo_capac,1,1);
	lay_->addWidget(new QLabel(traduire("DESCRIPTION_CAPACITE")),1,2);
	descr_capac=new QTextEdit();
	lay_->addWidget(descr_capac,1,3);
	lay_->addWidget(new QLabel(traduire("NOM_ATTAQUE")),2,0);
	combo_att=new QComboBox();
	foreach(QString n,Import::_attaques_.cles()){
		combo_att->addItem(traduire(Import::_noms_attaques_,n,langue));
	}
	combo_att->setEditable(true);
	connect(combo_att,SIGNAL(editTextChanged(QString)),this,SLOT(maj_descr_att()));
	lay_->addWidget(combo_att,2,1);
	lay_->addWidget(new QLabel(traduire("DESCRIPTION_ATTAQUE")),2,2);
	descr_att=new QTextEdit();
	lay_->addWidget(descr_att,2,3);
	lay_->addWidget(new QLabel(traduire("NOM_OBJET")),3,0);
	combo_obj=new QComboBox();
	foreach(QString n,Import::_objets_.cles()){
		combo_obj->addItem(traduire(Import::_noms_objets_,n,langue));
	}
	combo_obj->setEditable(true);
	connect(combo_obj,SIGNAL(editTextChanged(QString)),this,SLOT(maj_descr_obj()));
	lay_->addWidget(combo_obj,3,1);
	lay_->addWidget(new QLabel(traduire("DESCRIPTION_OBJET")),3,2);
	descr_obj=new QTextEdit();
	lay_->addWidget(descr_obj,3,3);
	setLayout(lay_);
}

void DialogueBaseDonnees::maj_descr_pk(){
	if(combo_pk->findText(combo_pk->currentText())<0){
		return;
	}
	QString nom_pk_fr_=traduire_revert(Import::_noms_pk_,combo_pk->currentText(),langue);
	FichePokemon *fiche_pk_=Import::_pokedex_.valeur(nom_pk_fr_);
	descr_pk->setPlainText(fiche_pk_->description(nom_pk_fr_,langue));
}

void DialogueBaseDonnees::maj_descr_capac(){
	if(combo_capac->findText(combo_capac->currentText())<0){
		return;
	}
	FicheCapacite *fiche_capac_=Import::_capacites_.valeur(traduire_revert(Import::_noms_capacites_,combo_capac->currentText(),langue));
	descr_capac->setPlainText(fiche_capac_->description(langue));
}

void DialogueBaseDonnees::maj_descr_obj(){
	if(combo_obj->findText(combo_obj->currentText())<0){
		return;
	}
	QString nom_objet_fr_=traduire_revert(Import::_noms_objets_,combo_obj->currentText(),langue);
	Objet *fiche_obj_=Import::_objets_.valeur(nom_objet_fr_);
	descr_obj->setPlainText(fiche_obj_->description(langue));
}

void DialogueBaseDonnees::maj_descr_att(){
	if(combo_att->findText(combo_att->currentText())<0){
		return;
	}
	QString nom_attaque_fr_=traduire_revert(Import::_noms_attaques_,combo_att->currentText(),langue);
	FicheAttaque *fiche_att_=Import::_attaques_.valeur(traduire_revert(Import::_noms_attaques_,nom_attaque_fr_,langue));
	descr_att->setPlainText(fiche_att_->description(nom_attaque_fr_,langue));
}


