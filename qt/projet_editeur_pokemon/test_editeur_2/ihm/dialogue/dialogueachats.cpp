#include "ihm/dialogue/dialogueachats.h"
#include "base_donnees/import.h"
#include "base_donnees/objets/baie.h"
#include "base_donnees/objets/ball.h"
#include "base_donnees/objets/boost.h"
#include "base_donnees/objets/fossile.h"
#include "base_donnees/objets/objetattachablecombat.h"
#include "base_donnees/objets/objetevo.h"
#include "base_donnees/objets/pierreevo.h"
#include "base_donnees/objets/plaque.h"
#include "base_donnees/objets/module.h"
#include "base_donnees/objets/repousse.h"
#include "base_donnees/objets/revente.h"
#include "base_donnees/objets/soinpvstatut.h"
#include "base_donnees/objets/soinpv.h"
#include "base_donnees/objets/soinpp.h"
#include "autre/utilitaire.h"
#include <QComboBox>
#include <QTableWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QCloseEvent>
#include <QMessageBox>

const HashMap<QString,QStringList> DialogueAchats::_elements_ihm_=DialogueAchats::init_elements_ihm();

HashMap<QString,QStringList> DialogueAchats::init_elements_ihm(){
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

QString DialogueAchats::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString DialogueAchats::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueAchats::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueAchats::DialogueAchats(int _langue,QWidget* _parent):QDialog(_parent){
	langue=_langue;
	setWindowTitle(traduire("TITRE"));
	rejeter=true;
	QFormLayout *centre_=new QFormLayout();
	nom_objet=new QComboBox();
	foreach(QString l,Import::_objets_.cles()){
		Objet *obj_=Import::_objets_.valeur(l);
		if(obj_->estAchetable()){
			nom_objet->addItem(traduire(Import::_noms_objets_,l,langue));
		}
	}
	nom_objet->setEditable(true);
	centre_->addRow(traduire("ETIQUETTE_OBJET"),nom_objet);
	QStringList ls_;
	ls_<<traduire("ETIQUETTE_OBJET_2");
	ls_<<traduire("ETIQUETTE_PRIX");
	ls_<<traduire("ETIQUETTE_TYPE");
	table_objets=new QTableWidget(1,ls_.size());
	table_objets->setHorizontalHeaderLabels(ls_);
	for(int i=0;i<ls_.size();i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText("");
		table_objets->setItem(0,i,element_);
	}
	centre_->addRow(table_objets);
	QPushButton *bouton_;
	bouton_=new QPushButton(traduire("AJOUTER_OBJ"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajout_objet()));
	QPushButton *bouton_2_;
	bouton_2_=new QPushButton(traduire("SUPPRIMER_OBJ"));
	connect(bouton_2_,SIGNAL(clicked()),this,SLOT(suppression_objet()));
	centre_->addRow(bouton_,bouton_2_);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(acceptation()));
	centre_->addRow("",valider_);
	setLayout(centre_);
	;
}


void DialogueAchats::maj_liste(const QStringList& _liste){
	setWindowTitle(traduire("TITRE_2"));
	objets=_liste;
	int nb_objs_=objets.size();
	table_objets->setRowCount(nb_objs_);
	int nb_cols_=table_objets->columnCount();
	for(int i=1;i<nb_objs_;i++){
		for(int j=0;j<nb_cols_;j++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText("");
			table_objets->setItem(i,j,element_);
		}
	}
	for(int i=0;i<nb_objs_;i++){
		table_objets->item(i,0)->setText(traduire(Import::_noms_objets_,objets[i],langue));
		Objet *obj_=Import::_objets_.valeur(objets[i]);
		table_objets->item(i,1)->setText(QString::number(obj_->prix()));
		if(qobject_cast<Ball*>(obj_)){
			table_objets->item(i,2)->setText(traduire("BALL"));
		}else if(qobject_cast<Baie*>(obj_)){
			table_objets->item(i,2)->setText(traduire("BAIE"));
		}else if(qobject_cast<Boost*>(obj_)){
			table_objets->item(i,2)->setText(traduire("BOOST"));
		}else if(qobject_cast<Fossile*>(obj_)){
			table_objets->item(i,2)->setText(traduire("FOSSILE"));
		}else if(qobject_cast<Module*>(obj_)){
			table_objets->item(i,2)->setText(traduire("MODULE"));
		}else if(qobject_cast<ObjetAttachableCombat*>(obj_)){
			table_objets->item(i,2)->setText(traduire("OBJET_CBT_ATTAC"));
		}else if(qobject_cast<ObjetEvo*>(obj_)){
			table_objets->item(i,2)->setText(traduire("OBJET_EVO"));
		}else if(qobject_cast<PierreEvo*>(obj_)){
			table_objets->item(i,2)->setText(traduire("PIERRE_EVO"));
		}else if(qobject_cast<Plaque*>(obj_)){
			table_objets->item(i,2)->setText(traduire("PLAQUE"));
		}else if(qobject_cast<Repousse*>(obj_)){
			table_objets->item(i,2)->setText(traduire("REPOUSSE"));
		}else if(qobject_cast<Revente*>(obj_)){
			table_objets->item(i,2)->setText(traduire("REVENTE"));
		}else if(qobject_cast<SoinPP*>(obj_)){
			table_objets->item(i,2)->setText(traduire("SOIN_PP"));
		}else if(qobject_cast<SoinPVStatut*>(obj_)){
			table_objets->item(i,2)->setText(traduire("SOIN_PV_STATUT"));
		}else if(qobject_cast<SoinPV*>(obj_)){
			table_objets->item(i,2)->setText(traduire("SOIN_PV"));
		}else if(qobject_cast<SoinStatut*>(obj_)){
			table_objets->item(i,2)->setText(traduire("SOIN_STATUT"));
		}else if(qobject_cast<Soin*>(obj_)){
			table_objets->item(i,2)->setText(traduire("SOIN"));
		}
	}
}

QStringList DialogueAchats::nv_liste()const{
	return objets;
}

bool DialogueAchats::rejete()const{
	return rejeter;
}

void DialogueAchats::ajout_objet(){
	if(nom_objet->findText(nom_objet->currentText())<0){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("OBJ_INEX"));
		return;
	}	
	QString objet_fr_=traduire_revert(Import::_noms_objets_,nom_objet->currentText(),langue);
	if(objets.contains(objet_fr_)){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("OBJ_DEJA_PRESENT"));
		return;
	}
	//if(!Import::_attaques_.cles().contains(attaque_)){//||nom_attaque_pk.findText(attaque_)<0
	Objet *fiche_obj_=Import::_objets_.valeur(objet_fr_);
	int nb_objets_=objets.size();
	int nb_lignes_=table_objets->rowCount();
	if(nb_objets_==nb_lignes_){
		table_objets->setRowCount(nb_objets_+1);
		int nb_cols_=table_objets->columnCount();
		for(int j=0;j<nb_cols_;j++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText("");
			table_objets->setItem(nb_objets_,j,element_);
		}
	}
	QTableWidgetItem *element_=table_objets->item(nb_objets_,0);
	element_->setText(nom_objet->currentText());
	element_=table_objets->item(nb_objets_,1);
	element_->setText(QString::number(fiche_obj_->prix()));
	element_=table_objets->item(nb_objets_,2);
	if(qobject_cast<Ball*>(fiche_obj_)){
		element_->setText(traduire("BALL"));
	}else if(qobject_cast<Baie*>(fiche_obj_)){
		element_->setText(traduire("BAIE"));
	}else if(qobject_cast<Boost*>(fiche_obj_)){
		element_->setText(traduire("BOOST"));
	}else if(qobject_cast<Fossile*>(fiche_obj_)){
		element_->setText(traduire("FOSSILE"));
	}else if(qobject_cast<Module*>(fiche_obj_)){
		element_->setText(traduire("MODULE"));
	}else if(qobject_cast<ObjetAttachableCombat*>(fiche_obj_)){
		element_->setText(traduire("OBJET_CBT_ATTAC"));
	}else if(qobject_cast<ObjetEvo*>(fiche_obj_)){
		element_->setText(traduire("OBJET_EVO"));
	}else if(qobject_cast<PierreEvo*>(fiche_obj_)){
		element_->setText(traduire("PIERRE_EVO"));
	}else if(qobject_cast<Plaque*>(fiche_obj_)){
		element_->setText(traduire("PLAQUE"));
	}else if(qobject_cast<Repousse*>(fiche_obj_)){
		element_->setText(traduire("REPOUSSE"));
	}else if(qobject_cast<Revente*>(fiche_obj_)){
		element_->setText(traduire("REVENTE"));
	}else if(qobject_cast<SoinPP*>(fiche_obj_)){
		element_->setText(traduire("SOIN_PP"));
	}else if(qobject_cast<SoinPVStatut*>(fiche_obj_)){
		element_->setText(traduire("SOIN_PV_STATUT"));
	}else if(qobject_cast<SoinPV*>(fiche_obj_)){
		element_->setText(traduire("SOIN_PV"));
	}else if(qobject_cast<SoinStatut*>(fiche_obj_)){
		element_->setText(traduire("SOIN_STATUT"));
	}else if(qobject_cast<Soin*>(fiche_obj_)){
		element_->setText(traduire("SOIN"));
	}
	objets<<objet_fr_;
	QMessageBox::critical(this,traduire("SUCCES"),traduire("OBJET_AJ"));
}

void DialogueAchats::suppression_objet(){
	if(table_objets->currentRow()<0||table_objets->currentRow()>=objets.size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("OBJ_INEX"));
		return;
	}
	int indice_=table_objets->currentRow();
	int nb_objets_=objets.size()-1;
	int nb_c_=table_objets->columnCount();
	for(int i=indice_;i<nb_objets_;i++){
		for(int j=0;j<nb_c_;j++){
			QTableWidgetItem *element_=table_objets->item(i,j);
			element_->setText(table_objets->item(i+1,j)->text());
		}
	}
	int nb_l_=table_objets->rowCount();
	for(int i=nb_objets_;i<nb_l_;i++){
		for(int j=0;j<nb_c_;j++){
			QTableWidgetItem *element_=table_objets->item(i,j);
			element_->setText("");
		}
	}
	objets.removeAt(indice_);
	QMessageBox::critical(this,traduire("SUCCES"),traduire("OBJET_SUPPR"));
}

void DialogueAchats::acceptation(){
	rejeter=false;
	close();
}

void DialogueAchats::closeEvent(QCloseEvent* _ev){
	if(rejeter){
		return;
	}
	QString err_;
	if(objets.isEmpty()){
		err_+=traduire("PAS_OBJET");
	}
	if(err_!=""){
		rejeter=true;
		_ev->ignore();
		QMessageBox::critical(this,traduire("ERREUR"),err_);
	}
}


