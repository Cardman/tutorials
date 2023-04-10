#include "ihm/panneau/panneaudresseurligue.h"
#include "ihm/fenetre.h"
#include "serialisable/personnages/dresseurligue.h"
#include "base_donnees/import.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "autre/utilitaire.h"
#include "math/taux.h"
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QTextEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>
#include <QGroupBox>

EnvironnementLigue *PanneauDresseurLigue::_environnement_ligue_en_cours_=NULL;

Tuile *PanneauDresseurLigue::_tuile_en_cours_=NULL;

const HashMap<QString,QStringList> PanneauDresseurLigue::_elements_ihm_=PanneauDresseurLigue::init_elements_ihm();

HashMap<QString,QStringList> PanneauDresseurLigue::init_elements_ihm(){
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

QString PanneauDresseurLigue::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString PanneauDresseurLigue::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString PanneauDresseurLigue::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

PanneauDresseurLigue::PanneauDresseurLigue(int _langue,Fenetre* _parent){
	langue=_langue;
	QFormLayout *centre_=new QFormLayout();
	foreach(QString l,Import::_langues_.cles()){
		QLineEdit *nom_=new QLineEdit();
		QStringList args_;
		args_<<Import::_langues_.valeur(l)[langue];
		connect(nom_,SIGNAL(editingFinished()),this,SLOT(maj_dresseur_revert()));
		centre_->addRow(Utilitaire::formatter(traduire("NOM_LIGUE"),args_),nom_);
		noms_ligues<<nom_;
	}
	type_env=new QComboBox();
	foreach(QString e,Import::_images_env_def_.cles()){
		if(e!=""){
			type_env->addItem(QPixmap::fromImage(Import::_images_env_def_.valeur(e)),traduire(Import::_noms_envir_,e,langue));
		}else{
			type_env->addItem(QPixmap::fromImage(Import::_images_env_def_.valeur(e)),e);
		}
	}
	type_env->addItem("");
	type_env->setEditable(true);
	connect(type_env,SIGNAL(editTextChanged(QString)),this,SLOT(maj_type_env()));
	centre_->addRow(traduire("TYPE_ENV"),type_env);
	foreach(QString l,Import::_langues_.cles()){
		QLineEdit *nom_=new QLineEdit();
		QStringList args_;
		args_<<Import::_langues_.valeur(l)[langue];
		connect(nom_,SIGNAL(editingFinished()),this,SLOT(maj_dresseur_revert()));
		centre_->addRow(Utilitaire::formatter(traduire("NOM"),args_),nom_);
		noms<<nom_;
	}
	nom_miniature=new QComboBox();
	foreach(QString s,Import::_dresseurs_micros_.cles()){
		nom_miniature->addItem(QPixmap::fromImage(Import::_dresseurs_micros_.valeur(s)),s);
	}
	nom_miniature->setEditable(true);
	connect(nom_miniature,SIGNAL(editTextChanged(QString)),this,SLOT(maj_dresseur_revert()));
	centre_->addRow(traduire("NOM_MINIATURE"),nom_miniature);
	orientation_h=new QSpinBox();
	orientation_h->setRange(-1,1);
	orientation_h->setValue(0);
	connect(orientation_h,SIGNAL(valueChanged(int)),this,SLOT(maj_dresseur_revert()));
	centre_->addRow(traduire("ORIENTATION_H"),orientation_h);
	orientation_v=new QSpinBox();
	orientation_v->setRange(-1,1);
	orientation_v->setValue(1);
	connect(orientation_v,SIGNAL(valueChanged(int)),this,SLOT(maj_dresseur_revert()));
	centre_->addRow(traduire("ORIENTATION_V"),orientation_v);
	coord_h=new QSpinBox();
	coord_h->setMinimum(0);
	coord_h->setValue(0);
	connect(coord_h,SIGNAL(valueChanged(int)),this,SLOT(maj_dresseur_revert()));
	centre_->addRow(traduire("COORD_H_DRESSEUR"),coord_h);
	coord_v=new QSpinBox();
	coord_v->setMinimum(0);
	coord_v->setValue(0);
	connect(coord_v,SIGNAL(valueChanged(int)),this,SLOT(maj_dresseur_revert()));
	centre_->addRow(traduire("COORD_V_DRESSEUR"),coord_v);
	centre_->addRow(new QLabel(traduire("EQUIPE")));
	QStringList etiquettes_;
	etiquettes_<<traduire("ETIQUETTE_NOM");
	etiquettes_<<traduire("ETIQUETTE_NIVEAU");
	int nb_pk_max_=(int)Import::constante_numerique("MAX_PKEQ");
	table_equipes=new QTableWidget(nb_pk_max_,etiquettes_.size());
	for(int i=0;i<nb_pk_max_;i++){
		for(int j=0;j<etiquettes_.size();j++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText("");
			table_equipes->setItem(i,j,element_);
		}
	}
	connect(table_equipes,SIGNAL(cellClicked(int,int)),this,SLOT(maj_equipe(int)));
	QGroupBox *pk_act_=new QGroupBox(traduire("PK_SELECT"));
	QVBoxLayout *lay_pk_act_=new QVBoxLayout();
	nom_pk=new QLabel("");
	lay_pk_act_->addWidget(nom_pk);
	niveau=new QLabel("");
	lay_pk_act_->addWidget(niveau);
	genre=new QLabel("");
	lay_pk_act_->addWidget(genre);
	capacite=new QLabel("");
	lay_pk_act_->addWidget(capacite);
	objet=new QLabel("");
	lay_pk_act_->addWidget(objet);
	attaques=new QTextEdit();
	lay_pk_act_->addWidget(attaques);
	pk_act_->setLayout(lay_pk_act_);
	centre_->addRow(table_equipes,pk_act_);
	QGridLayout *groupe_boutons_=new QGridLayout();
	QPushButton *bouton_=new QPushButton(traduire("AJOUTER_PK"));
	connect(bouton_,SIGNAL(clicked()),_parent,SLOT(ajouter_pk()));
	groupe_boutons_->addWidget(bouton_,0,0);
	bouton_=new QPushButton(traduire("EDITER_PK"));
	connect(bouton_,SIGNAL(clicked()),_parent,SLOT(editer_pk()));
	groupe_boutons_->addWidget(bouton_,0,1);
	bouton_=new QPushButton(traduire("SUPPRIMER_PK"));
	connect(bouton_,SIGNAL(clicked()),_parent,SLOT(supprimer_pk()));
	groupe_boutons_->addWidget(bouton_,0,2);
	bouton_=new QPushButton(traduire("INSERER_PK"));
	connect(bouton_,SIGNAL(clicked()),_parent,SLOT(inserer_pk()));
	groupe_boutons_->addWidget(bouton_,1,0);
	centre_->addRow(groupe_boutons_);
	champ_recompense=new QLineEdit();
	QRegExpValidator *exp_reg_=new QRegExpValidator(0);
	exp_reg_->setRegExp(QRegExp(Utilitaire::constante(Import::_constantes_,"EXP_REG_ENTIER")));
	champ_recompense->setText(Utilitaire::constante(Import::_constantes_,"DEF_RECOMPENSE"));
	champ_recompense->setValidator(exp_reg_);
	connect(champ_recompense,SIGNAL(editingFinished()),this,SLOT(maj_dresseur_revert()));
	centre_->addRow(traduire("RECOMPENSE"),champ_recompense);
	nom_image=new QComboBox();
	foreach(QString s,Import::_dresseurs_macros_.cles()){
		nom_image->addItem(QPixmap::fromImage(Import::_dresseurs_macros_.valeur(s)),s);
	}
	nom_image->setEditable(true);
	connect(nom_image,SIGNAL(editTextChanged(QString)),this,SLOT(maj_dresseur_revert()));
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
	connect(multiplicite_combat,SIGNAL(valueChanged(int)),this,SLOT(maj_dresseur_revert()));
	centre_->addRow(traduire("MULT_CBT"),multiplicite_combat);
	choix_imgs_tuiles=new QComboBox();
	foreach(QString s,Import::_tuiles_importees_.cles()){
		choix_imgs_tuiles->addItem(QPixmap::fromImage(Import::_tuiles_importees_.valeur(s)),s);
	}
	choix_imgs_tuiles->setEditable(true);
	connect(choix_imgs_tuiles,SIGNAL(editTextChanged(QString)),this,SLOT(maj_image_tuile(QString)));
	//const QImage&
	centre_->addRow(traduire("IMAGE_FOND_TUILE"),choix_imgs_tuiles);
	setLayout(centre_);
}

void PanneauDresseurLigue::maj_dresseur(){
	DresseurLigue *dresseur_=Fenetre::_plateau_ligue_en_cours_->adr_dresseur_ligue();
	int nb_champs_=noms.size();
	QStringList ls_=dresseur_->adr_nom()->split("\t");
	for(int i=0;i<nb_champs_;i++){
		noms[i]->setText(ls_[i]);
	}
	nom_miniature->setEditText(*dresseur_->adr_nom_miniature());
	nb_champs_=noms_ligues.size();
	ls_=Fenetre::_ligue_en_cours_->adr_nom_ligue()->split("\t");
	for(int i=0;i<nb_champs_;i++){
		noms_ligues[i]->setText(ls_[i]);
	}
	QPair<int,int> h_v_;
	h_v_.first=dresseur_->adr_orientation()->first;
	h_v_.second=dresseur_->adr_orientation()->second;
	orientation_h->setValue(h_v_.first);
	orientation_v->setValue(h_v_.second);
	h_v_.first=Fenetre::_plateau_ligue_en_cours_->adr_coords_dresseur()->first;
	h_v_.second=Fenetre::_plateau_ligue_en_cours_->adr_coords_dresseur()->second;
	coord_h->setValue(h_v_.first);
	coord_v->setValue(h_v_.second);
	nom_image->setEditText(*dresseur_->adr_nom_image());
	QString message_=*dresseur_->adr_message_fin_combat();
	message_fin_combat->setPlainText(message_.replace("\\n","\n"));
	message_=*dresseur_->adr_message_debut_combat();
	message_debut_combat->setPlainText(message_.replace("\\n","\n"));
	int val_=*dresseur_->adr_multiplicite_combat();
	multiplicite_combat->setValue(val_);
	champ_recompense->setText(QString::number(*dresseur_->adr_recompense_base()));
	QList<PokemonDresse> equipe_=*dresseur_->adr_equipe();
	int nb_membres_=equipe_.size();
	int nb_pk_max_=(int)Import::constante_numerique("MAX_PKEQ");
	for(int i=0;i<nb_pk_max_;i++){
		table_equipes->item(i,0)->setIcon(QIcon());
		table_equipes->item(i,0)->setText("");
		table_equipes->item(i,1)->setText("");
	}
	for(int i=0;i<nb_membres_;i++){
		QString n_pk_=*equipe_[i].adr_nom();
		int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
		table_equipes->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
		table_equipes->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
		table_equipes->item(i,1)->setText(QString::number(*equipe_[i].adr_niveau()));
	}
	nom_pk->setText("");
	niveau->setText("");
	capacite->setText("");
	genre->setText("");
	objet->setText("");
	attaques->setPlainText("");
	//TODO table_equipe
}

int PanneauDresseurLigue::ligne_courante()const{
	return table_equipes->currentRow();
}

void PanneauDresseurLigue::maj_equipe(int _equipe){
	QList<PokemonDresse> *equipe_=Fenetre::_plateau_ligue_en_cours_->adr_dresseur_ligue()->adr_equipe();
	if(_equipe>equipe_->size()){
		return;
	}
	indice_eq=_equipe;
	maj_equipe();
}

void PanneauDresseurLigue::maj_equipe(){
	QList<PokemonDresse> equipe_=*Fenetre::_plateau_ligue_en_cours_->adr_dresseur_ligue()->adr_equipe();
	if(indice_eq<0||indice_eq>=equipe_.size()){
		return;
	}
	equipe=equipe_;
//table_equipe
	int nb_act_l_=table_equipes->rowCount();
	int nb_equipe_=equipe_.size();
	for(int i=0;i<nb_equipe_;i++){
		QString n_pk_=*equipe_[i].adr_nom();
		int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
		table_equipes->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
		table_equipes->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
		table_equipes->item(i,1)->setText(QString::number(*equipe_[i].adr_niveau()));
	}
	for(int i=nb_equipe_;i<nb_act_l_;i++){
		table_equipes->item(i,0)->setIcon(QIcon());
		table_equipes->item(i,0)->setText("");
		table_equipes->item(i,1)->setText("");
	}
	nom_pk->setText(traduire(Import::_noms_pk_,*equipe_[indice_eq].adr_nom(),langue));
	niveau->setText(QString::number(*equipe_[indice_eq].adr_niveau()));
	capacite->setText(traduire(Import::_noms_capacites_,*equipe_[indice_eq].adr_capacite(),langue));
	genre->setText(traduire(Import::_noms_genres_,*equipe_[indice_eq].adr_genre(),langue));
	objet->setText(traduire(Import::_noms_objets_,*equipe_[indice_eq].adr_nom_objet(),langue));
	QStringList attaques_=*equipe_[indice_eq].adr_attaques();
	QStringList attaques_2_;
	foreach(QString a,attaques_){
		attaques_2_<<traduire(Import::_noms_attaques_,a,langue);
	}
	attaques->setPlainText(attaques_2_.join("\n"));
	//attaques->setPlainText(equipe_[indice_eq].adr_attaques()->join("\n"))
}

void PanneauDresseurLigue::decrementer_ind_pk(){
	if(indice_eq+1>=equipe.size()){
		indice_eq--;
	}
}
/*void PanneauDresseurLigue::supprimer_pk(){
	QList<PokemonDresse> *equipe_=Fenetre::_plateau_ligue_en_cours_->adr_dresseur_ligue()->adr_equipe()
	if(table_equipes->currentRow()<0||table_equipes->currentRow()>=equipe_->size()){
		return
	}
	if(table_equipes->currentRow()<=indice_eq){
		indice_eq=0
	}
	equipe_->removeAt(table_equipes->currentRow())
	maj_equipe()
}*/

void PanneauDresseurLigue::maj_type_env(){
	if(PanneauDresseurLigue::_environnement_ligue_en_cours_==NULL){
		return;
	}
	if(type_env->findText(type_env->currentText())<0){
		return;
	}
	if(type_env->currentText()==""){
		*_environnement_ligue_en_cours_->type_env()="";
		return;
	}
	*_environnement_ligue_en_cours_->type_env()=traduire_revert(Import::_noms_envir_,type_env->currentText(),langue);
}

void PanneauDresseurLigue::maj_dresseur_revert(){
	DresseurLigue *dresseur_=Fenetre::_plateau_ligue_en_cours_->adr_dresseur_ligue();
	QString noms_=noms[0]->text();
	int nb_champs_=noms.size();
	for(int i=1;i<nb_champs_;i++){
		noms_+="\t"+noms[i]->text();
	}
	*dresseur_->adr_nom()=noms_;
	noms_=noms_ligues[0]->text();
	nb_champs_=noms_ligues.size();
	for(int i=1;i<nb_champs_;i++){
		noms_+="\t"+noms_ligues[i]->text();
	}
	*Fenetre::_ligue_en_cours_->adr_nom_ligue()=noms_;
	*dresseur_->adr_nom_miniature()=nom_miniature->currentText();
	dresseur_->adr_orientation()->first=orientation_h->value();
	dresseur_->adr_orientation()->second=orientation_v->value();
	Fenetre::_plateau_ligue_en_cours_->adr_coords_dresseur()->first=coord_h->value();
	Fenetre::_plateau_ligue_en_cours_->adr_coords_dresseur()->second=coord_v->value();
	*dresseur_->adr_nom_image()=nom_image->currentText();
	//*dresseur_->adr_equipe()=equipe
	*dresseur_->adr_recompense_base()=champ_recompense->text().toInt();
	QString message_=message_fin_combat->toPlainText();
	message_.replace("\n","\\n");
	*dresseur_->adr_message_fin_combat()=message_;
	message_=message_debut_combat->toPlainText();
	message_.replace("\n","\\n");
	*dresseur_->adr_message_debut_combat()=message_;
	*dresseur_->adr_multiplicite_combat()=multiplicite_combat->value();
}

void PanneauDresseurLigue::maj_image_tuile(const QString& _tuile){
	int _indice=choix_imgs_tuiles->findText(_tuile);
	if(_indice>-1&&PanneauDresseurLigue::_tuile_en_cours_!=NULL){
		*PanneauDresseurLigue::_tuile_en_cours_->adr_nom_image()=choix_imgs_tuiles->currentText();
		emit image_tuile_changee(Import::_tuiles_importees_.valeur(*PanneauDresseurLigue::_tuile_en_cours_->adr_nom_image()));
	}
}

void PanneauDresseurLigue::maj_env(const QPair<QPair<int,int>,QPair<int,int> >& _coords){
	if(Fenetre::_plateau_ligue_en_cours_!=NULL){
		bool suppr_=false;
		_environnement_ligue_en_cours_=Fenetre::_plateau_ligue_en_cours_->environnement(_coords.first,suppr_);
		PanneauDresseurLigue::_tuile_en_cours_=_environnement_ligue_en_cours_->tuile(_coords.second);
		//TODO maj totale du panneau en fonction de l'environnement
		int indice_=choix_imgs_tuiles->findText(*PanneauDresseurLigue::_tuile_en_cours_->adr_nom_image());
		if(indice_>-1){
			choix_imgs_tuiles->setCurrentIndex(indice_);
		}
		if(*_environnement_ligue_en_cours_->type_env()==""){
			type_env->setCurrentIndex(type_env->findText(""));
		}else{
			type_env->setCurrentIndex(type_env->findText(traduire(Import::_noms_envir_,*_environnement_ligue_en_cours_->type_env(),langue)));
		}
	}
}


