#include "ihm/dialogue/dialoguedresseur.h"
#include "ihm/dialogue/dialogueequipe.h"
#include "serialisable/personnages/champion.h"
#include "serialisable/personnages/dresseur1.h"
#include "base_donnees/import.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "autre/utilitaire.h"
#include "math/taux.h"
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QTextEdit>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>

const HashMap<QString,QStringList> DialogueDresseur::_elements_ihm_=DialogueDresseur::init_elements_ihm();

HashMap<QString,QStringList> DialogueDresseur::init_elements_ihm(){
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

QString DialogueDresseur::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}


QString DialogueDresseur::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueDresseur::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueDresseur::DialogueDresseur(int _langue,bool _est_champion,QWidget* _parent):QDialog(_parent){
	langue=_langue;
	setWindowTitle(traduire("TITRE_D"));
	rejeter=true;
	indice_eq=0;
	QFormLayout *centre_=new QFormLayout();
	foreach(QString l,Import::_langues_.cles()){
		QLineEdit *nom_=new QLineEdit();
		QStringList args_;
		args_<<Import::_langues_.valeur(l)[langue];
		//QString et_=formatter(traduire("NOM"),args_)
		//QString n_="Nom"
		//centre_->addRow(n_+", "+Import::_langues_.valeur(l)[_langue],nom_)
		centre_->addRow(Utilitaire::formatter(traduire("NOM"),args_),nom_);
		noms<<nom_;
	}
	nom_miniature=new QComboBox();
	foreach(QString s,Import::_dresseurs_micros_.cles()){
		nom_miniature->addItem(QPixmap::fromImage(Import::_dresseurs_micros_.valeur(s)),s);
	}
	nom_miniature->setEditable(true);
	centre_->addRow(traduire("NOM_MINIATURE"),nom_miniature);
	orientation_h=new QSpinBox();
	orientation_h->setRange(-1,1);
	orientation_h->setValue(0);
	centre_->addRow(traduire("ORIENTATION_H"),orientation_h);
	orientation_v=new QSpinBox();
	orientation_v->setRange(-1,1);
	orientation_v->setValue(1);
	centre_->addRow(traduire("ORIENTATION_V"),orientation_v);
	table_equipes=new QTableWidget(1,1);
	QTableWidgetItem *element_=new QTableWidgetItem();
	element_->setText("");
	table_equipes->setItem(0,0,element_);
	connect(table_equipes,SIGNAL(cellClicked(int,int)),this,SLOT(maj_equipe(int)));
	QStringList etiquettes_;
	etiquettes_<<traduire("ETIQUETTE_NOM");
	etiquettes_<<traduire("ETIQUETTE_NIVEAU");
	int nb_pk_max_=(int)Import::constante_numerique("MAX_PKEQ");
	table_equipe=new QTableWidget(nb_pk_max_,etiquettes_.size());
	for(int i=0;i<nb_pk_max_;i++){
		for(int j=0;j<etiquettes_.size();j++){
			element_=new QTableWidgetItem();
			element_->setText("");
			table_equipe->setItem(i,j,element_);
		}
	}
	centre_->addRow(table_equipes,table_equipe);
	QGridLayout *groupe_boutons_=new QGridLayout();
	QPushButton *bouton_=new QPushButton(traduire("AJOUTER_EQ"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajouter_equipe()));
	groupe_boutons_->addWidget(bouton_,0,0);
	bouton_=new QPushButton(traduire("EDITER_EQ"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(editer_equipe()));
	groupe_boutons_->addWidget(bouton_,0,1);
	bouton_=new QPushButton(traduire("SUPPRIMER_EQ"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(supprimer_equipe()));
	groupe_boutons_->addWidget(bouton_,0,2);
	bouton_=new QPushButton(traduire("INSERER_EQ"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(inserer_equipe()));
	groupe_boutons_->addWidget(bouton_,1,0);
	centre_->addRow(groupe_boutons_);
	nom_image=new QComboBox();
	foreach(QString s,Import::_dresseurs_macros_.cles()){
		nom_image->addItem(QPixmap::fromImage(Import::_dresseurs_macros_.valeur(s)),s);
	}
	nom_image->setEditable(true);
	centre_->addRow(traduire("NOM_IMAGE"),nom_image);
	message_fin_combat=new QTextEdit();
	centre_->addRow(traduire("MESSAGE_FIN_CBT"),message_fin_combat);
	message_debut_combat=new QTextEdit();
	centre_->addRow(traduire("MESSAGE_DEBUT_CBT"),message_debut_combat);
	multiplicite_combat=new QSpinBox();
	int max_mult_cbt_=(int)Import::constante_numerique("MAX_MULTIPLICITE_CBT");
	int min_mult_cbt_=(int)Import::constante_numerique("MIN_MULTIPLICITE_CBT");
	int def_mult_cbt_=(int)Import::constante_numerique("DEF_MULTIPLICITE_CBT");
	multiplicite_combat->setRange(min_mult_cbt_,max_mult_cbt_);
	multiplicite_combat->setValue(def_mult_cbt_);
	centre_->addRow(traduire("MULT_CBT"),multiplicite_combat);
	if(_est_champion){
		setWindowTitle(traduire("TITRE_C"));
		foreach(QString l,Import::_langues_.cles()){
			QLineEdit *badge_=new QLineEdit();
			QStringList args_;
			args_<<Import::_langues_.valeur(l)[langue];
			centre_->addRow(Utilitaire::formatter(traduire("BADGE"),args_),badge_);
			badges<<badge_;
		}
		ct=new QComboBox();
		ct->addItem(Utilitaire::constante(Import::_constantes_,"CT_INVALIDE"));
		foreach(uchar s,Import::_ct_.cles()){
			ct->addItem(QString::number(s));
		}
		ct->setEditable(true);
		connect(ct,SIGNAL(editTextChanged(QString)),this,SLOT(maj_ct(QString)));
		QStringList args_;
		args_<<traduire("TECHNIQUE");
		centre_->addRow(Utilitaire::formatter(traduire("NUMERO_CAPSULE"),args_),ct);
		attaque_ct=new QLabel();
		args_.clear();
		args_<<traduire("TECHNIQUE");
		centre_->addRow(Utilitaire::formatter(traduire("NOM_ATTAQUE_LIE"),args_),attaque_ct);
		cs=new QComboBox();
		cs->addItem(Utilitaire::constante(Import::_constantes_,"CS_INVALIDE"));
		foreach(uchar s,Import::_cs_.cles()){
			cs->addItem(QString::number(s));
		}
		cs->setEditable(true);
		connect(cs,SIGNAL(editTextChanged(QString)),this,SLOT(maj_cs(QString)));
		args_.clear();
		args_<<traduire("SECRETE");
		centre_->addRow(Utilitaire::formatter(traduire("NUMERO_CAPSULE"),args_),cs);
		attaque_cs=new QLabel();
		args_.clear();
		args_<<traduire("SECRETE");
		centre_->addRow(Utilitaire::formatter(traduire("NOM_ATTAQUE_LIE"),args_),attaque_cs);
	}else{
		ct=NULL;
		cs=NULL;
		attaque_ct=NULL;
		attaque_cs=NULL;
	}
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(acceptation()));
	centre_->addRow("",valider_);
	setLayout(centre_);
}

void DialogueDresseur::maj_dresseur(Dresseur1 *_dresseur){
	setWindowTitle(traduire("TITRE_D_2"));
	int nb_champs_=noms.size();
	QStringList ls_=_dresseur->adr_nom()->split("\t");
	for(int i=0;i<nb_champs_;i++){
		noms[i]->setText(ls_[i]);
	}
	nom_miniature->setEditText(*_dresseur->adr_nom_miniature());
	orientation_h->setValue(_dresseur->adr_orientation()->first);
	orientation_v->setValue(_dresseur->adr_orientation()->second);
	table_equipes->setRowCount(_dresseur->adr_equipes()->size());
	nom_image->setEditText(*_dresseur->adr_nom_image());
	QString message_=*_dresseur->adr_message_fin_combat();
	//message_.replace("\\\\n","\\n")
	message_fin_combat->setPlainText(message_.replace("\\n","\n"));
	message_=*_dresseur->adr_message_debut_combat();
	//message_.replace("\\\\n","\\n")
	message_debut_combat->setPlainText(message_.replace("\\n","\n"));
	multiplicite_combat->setValue(*_dresseur->adr_multiplicite_combat());
	equipes=*_dresseur->adr_equipes();
	QList<PokemonDresse> equipe_=equipes[0].first;
	int nb_membres_=equipe_.size();
	for(int i=1;i<nb_membres_;i++){
		for(int j=0;j<table_equipe->columnCount();j++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText("");
			table_equipe->setItem(i,j,element_);
		}
	}
	for(int i=0;i<nb_membres_;i++){
		QString n_pk_=*equipe_[i].adr_nom();
		int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
		table_equipe->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
		table_equipe->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
		table_equipe->item(i,1)->setText(QString::number(*equipe_[i].adr_niveau()));
	}
	nb_membres_=equipes.size();
	table_equipes->item(0,0)->setText("0");
	for(int i=1;i<nb_membres_;i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText(QString::number(i));
		table_equipes->setItem(i,0,element_);
	}
	//TODO table_equipe
}

void DialogueDresseur::maj_champion(Champion *_champion){
	maj_dresseur(_champion);
	setWindowTitle(traduire("TITRE_C_2"));
	int nb_champs_=badges.size();
	QStringList ls_=_champion->adr_badge()->split("\t");
	for(int i=0;i<nb_champs_;i++){
		badges[i]->setText(ls_[i]);
	}
	ct->setEditText(QString::number(*_champion->adr_ct()));
	if(*_champion->adr_ct()!=(uchar)Import::constante_numerique("CT_INVALIDE")){
		attaque_ct->setText(Import::_ct_.valeur(*_champion->adr_ct()));
	}else{
		attaque_ct->setText("");
	}
	cs->setEditText(QString::number(*_champion->adr_cs()));
	if(*_champion->adr_cs()!=(uchar)Import::constante_numerique("CS_INVALIDE")){
		attaque_cs->setText(Import::_cs_.valeur(*_champion->adr_cs()));
	}else{
		attaque_cs->setText("");
	}
}

Dresseur1 DialogueDresseur::nv_dresseur()const{
	Dresseur1 dr_;
	QString noms_=noms[0]->text();
	int nb_champs_=noms.size();
	for(int i=1;i<nb_champs_;i++){
		noms_+="\t"+noms[i]->text();
	}
	*dr_.adr_nom()=noms_;
	*dr_.adr_nom_miniature()=nom_miniature->currentText();
	*dr_.adr_orientation()=QPair<int,int>(orientation_h->value(),orientation_v->value());
	*dr_.adr_equipes()=equipes;
	*dr_.adr_nom_image()=nom_image->currentText();
	QString message_=message_fin_combat->toPlainText();
	*dr_.adr_message_fin_combat()=message_.replace("\n","\\n");
	message_=message_debut_combat->toPlainText();
	*dr_.adr_message_debut_combat()=message_.replace("\n","\\n");
	*dr_.adr_multiplicite_combat()=multiplicite_combat->value();
	return dr_;
}

Champion DialogueDresseur::nv_champion()const{
	Champion ch_=Champion(nv_dresseur());
	QString noms_=badges[0]->text();
	int nb_champs_=badges.size();
	for(int i=1;i<nb_champs_;i++){
		noms_+="\t"+badges[i]->text();
	}
	*ch_.adr_badge()=noms_;
	*ch_.adr_ct()=(uchar)ct->currentText().toUInt();
	*ch_.adr_cs()=(uchar)cs->currentText().toUInt();
	return ch_;
}

void DialogueDresseur::maj_equipe(int _equipe){
	if(_equipe>equipes.size()){
		return;
	}
	indice_eq=_equipe;
	maj_equipe();
}

void DialogueDresseur::maj_equipe(){
	if(indice_eq<0||indice_eq>=equipes.size()){
		return;
	}
//table_equipe
	int nb_act_l_=table_equipe->rowCount();
	QList<PokemonDresse> equipe_=equipes[indice_eq].first;
	int nb_equipe_=equipe_.size();
	for(int i=0;i<nb_equipe_;i++){
		QString n_pk_=*equipe_[i].adr_nom();
		int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
		table_equipe->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
		table_equipe->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
		table_equipe->item(i,1)->setText(QString::number(*equipe_[i].adr_niveau()));
	}
	for(int i=nb_equipe_;i<nb_act_l_;i++){
		table_equipe->item(i,0)->setIcon(QIcon());
		table_equipe->item(i,0)->setText("");
		table_equipe->item(i,1)->setText("");
	}
	//int nb_equipes_=equipes.size()
	nb_act_l_=table_equipes->rowCount();
	int nb_equipes_=equipes.size();
	if(nb_act_l_==nb_equipes_){
		for(int i=0;i<nb_act_l_;i++){
			table_equipes->item(i,0)->setText(QString::number(i));
		}
	}else if(nb_act_l_<nb_equipes_){
		for(int i=0;i<nb_act_l_;i++){
			table_equipes->item(i,0)->setText(QString::number(i));
		}
		table_equipes->setRowCount(nb_act_l_+1);
		QTableWidgetItem *element_;
		element_=new QTableWidgetItem();
		element_->setText(QString::number(nb_act_l_));
		table_equipes->setItem(nb_act_l_,0,element_);
	}else{
		table_equipes->item(indice_eq,0)->setText("");
	}
	/*else{
		for(int i=0;i<nb_act_l_-1;i++){
			table_equipes->item(i,0)->setText(table_equipes->item(i+1,0)->text())
		}
		table_equipes->item(nb_act_l_-1,0)->setText("")
	}*/
}

void DialogueDresseur::ajouter_equipe(){
	DialogueEquipe *dial_=new DialogueEquipe(langue,this);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		indice_eq=equipes.size();
		equipes<<dial_->equipe_recompense();
		maj_equipe();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void DialogueDresseur::inserer_equipe(){
	if(table_equipes->currentRow()<0||table_equipes->currentRow()>equipes.size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_INSERT_INV"));
		return;
	}
	DialogueEquipe *dial_=new DialogueEquipe(langue,this);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		indice_eq=table_equipes->currentRow();
		equipes.insert(table_equipes->currentRow(),dial_->equipe_recompense());
		maj_equipe();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void DialogueDresseur::supprimer_equipe(){
	if(table_equipes->currentRow()<0||table_equipes->currentRow()>=equipes.size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_SUPPR_INV"));
		return;
	}
	if(table_equipes->currentRow()<=indice_eq){
		indice_eq=0;
	}
	equipes.removeAt(table_equipes->currentRow());
	maj_equipe();
}

void DialogueDresseur::editer_equipe(){
	if(table_equipes->currentRow()<0||table_equipes->currentRow()>=equipes.size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_EDIT_INV"));
		return;
	}
	DialogueEquipe *dial_=new DialogueEquipe(langue,this);
	dial_->maj_equipe_recompense(equipes[table_equipes->currentRow()]);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		indice_eq=table_equipes->currentRow();
		equipes[table_equipes->currentRow()]=dial_->equipe_recompense();
		maj_equipe();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void DialogueDresseur::maj_ct(const QString& _ct){
	if(Import::_ct_.cles().contains((uchar)_ct.toUInt())){
		attaque_ct->setText(Import::_ct_.valeur((uchar)_ct.toUInt()));
	}else if(_ct==Import::constante("CT_INVALIDE")){
		attaque_ct->setText("");
	}
}

void DialogueDresseur::maj_cs(const QString& _cs){
	if(Import::_cs_.cles().contains((uchar)_cs.toUInt())){
		attaque_cs->setText(Import::_cs_.valeur((uchar)_cs.toUInt()));
	}else if(_cs==Import::constante("CS_INVALIDE")){
		attaque_cs->setText("");
	}
}

bool DialogueDresseur::rejete()const{
	return rejeter;
}

void DialogueDresseur::acceptation(){
	rejeter=false;
	close();
}

void DialogueDresseur::closeEvent(QCloseEvent* _ev){
	if(rejeter){
		return;
	}
	QString erreur_;
	if(equipes.isEmpty()){
		erreur_+=traduire("PAS_EQUIPES")+"\n";
	}
	int i_=0;
	QList<QString> cles_langue_=Import::_langues_.cles();
	foreach(QLineEdit *l,noms){
		QStringList args_;
		args_<<Import::_langues_.valeur(cles_langue_[i_])[langue];
		if(l->text()==""){
			erreur_+=Utilitaire::formatter(traduire("PAS_NOM"),args_)+"\n";
		}
		i_++;
	}
	if(!badges.isEmpty()){
		i_=0;
		foreach(QLineEdit *l,badges){
			QStringList args_;
			args_<<Import::_langues_.valeur(cles_langue_[i_])[langue];
			if(l->text()==""){
				erreur_+=Utilitaire::formatter(traduire("PAS_BADGE"),args_)+"\n";
			}
			i_++;
		}
	}
	int somme_c_=orientation_h->value()*orientation_h->value()+orientation_v->value()*orientation_v->value();
	if(somme_c_!=1){
		erreur_+=traduire("ERR_ORIENTATION")+"\n";
	}
	if(erreur_!=""){
		_ev->ignore();
		rejeter=true;
		QMessageBox::critical(this,traduire("ERREUR"),erreur_);
	}
}



