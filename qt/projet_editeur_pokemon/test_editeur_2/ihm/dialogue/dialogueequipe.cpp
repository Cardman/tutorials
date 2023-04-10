#include "ihm/dialogue/dialogueequipe.h"
#include "ihm/dialogue/dialoguepkcombat.h"
#include "base_donnees/import.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "autre/utilitaire.h"
#include "math/taux.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QGroupBox>
#include <QRegExpValidator>
#include <QRegExp>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>

const HashMap<QString,QStringList> DialogueEquipe::_elements_ihm_=DialogueEquipe::init_elements_ihm();

HashMap<QString,QStringList> DialogueEquipe::init_elements_ihm(){
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

QString DialogueEquipe::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString DialogueEquipe::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueEquipe::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueEquipe::DialogueEquipe(int _langue,QWidget* _parent):QDialog(_parent){
	langue=_langue;
	rejeter=true;
	setWindowTitle(traduire("TITRE"));
	QHBoxLayout *lay_h_=new QHBoxLayout();
	QStringList etiquettes_;
	etiquettes_<<traduire("ETIQUETTE_NOM");
	etiquettes_<<traduire("ETIQUETTE_NIVEAU");
	table_equipe=new QTableWidget(1,etiquettes_.size());
	for(int i=0;i<etiquettes_.size();i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText("");
		table_equipe->setItem(0,i,element_);
	}
	connect(table_equipe,SIGNAL(cellClicked(int,int)),this,SLOT(maj_description(int)));
	lay_h_->addWidget(table_equipe);
	QVBoxLayout *lay_v_=new QVBoxLayout();
	nom=new QLabel();
	lay_v_->addWidget(nom);
	niveau=new QLabel();
	lay_v_->addWidget(niveau);
	genre=new QLabel();
	lay_v_->addWidget(genre);
	capacite=new QLabel();
	lay_v_->addWidget(capacite);
	objet=new QLabel();
	lay_v_->addWidget(objet);
	attaques=new QTextEdit();
	lay_v_->addWidget(attaques);
	QGroupBox *groupe_=new QGroupBox(traduire("PK_COURS"));
	groupe_->setLayout(lay_v_);
	lay_h_->addWidget(groupe_);
	QVBoxLayout *centre_=new QVBoxLayout();
	centre_->addLayout(lay_h_);
	QGridLayout *groupe_boutons_=new QGridLayout();
	QPushButton *bouton_=new QPushButton(traduire("AJOUTER_PK"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajouter_pokemon()));
	groupe_boutons_->addWidget(bouton_,0,0);
	bouton_=new QPushButton(traduire("EDITER_PK"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(editer_pokemon()));
	groupe_boutons_->addWidget(bouton_,0,1);
	bouton_=new QPushButton(traduire("SUPPRIMER_PK"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(supprimer_pokemon()));
	groupe_boutons_->addWidget(bouton_,0,2);
	bouton_=new QPushButton(traduire("INSERER_PK"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(inserer_pokemon()));
	groupe_boutons_->addWidget(bouton_,1,0);
	centre_->addLayout(groupe_boutons_);
	champ_recompense=new QLineEdit();
	QRegExpValidator *exp_reg_=new QRegExpValidator(0);
	exp_reg_->setRegExp(QRegExp(Import::constante("EXP_REG_ENTIER")));
	champ_recompense->setText(Import::constante("DEF_RECOMPENSE"));
	champ_recompense->setValidator(exp_reg_);
	lay_h_=new QHBoxLayout();
	lay_h_->addWidget(new QLabel(traduire("RECOMPENSE")));
	lay_h_->addWidget(champ_recompense);
	centre_->addLayout(lay_h_);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(acceptation()));
	centre_->addWidget(valider_);
	setLayout(centre_);
}

void DialogueEquipe::maj_equipe(){
//table_equipe
	int nb_act_l_=table_equipe->rowCount();
	int nb_membre_=equipe.size();
	if(nb_act_l_==nb_membre_){
		for(int i=0;i<nb_act_l_;i++){
			QString n_pk_=*equipe[i].adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_equipe->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_equipe->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_equipe->item(i,1)->setText(QString::number(*equipe[i].adr_niveau()));
		}
	}else if(nb_act_l_<nb_membre_){
		for(int i=0;i<nb_act_l_;i++){
			QString n_pk_=*equipe[i].adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_equipe->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_equipe->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_equipe->item(i,1)->setText(QString::number(*equipe[i].adr_niveau()));
		}
		table_equipe->setRowCount(nb_act_l_+1);
		QTableWidgetItem *element_;
		element_=new QTableWidgetItem();
		QString n_pk_=*equipe[nb_act_l_].adr_nom();
		int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
		element_->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
		element_->setText(traduire(Import::_noms_pk_,n_pk_,langue));
		table_equipe->setItem(nb_act_l_,0,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*equipe[nb_act_l_].adr_niveau()));
		table_equipe->setItem(nb_act_l_,1,element_);
	}else{
		int nb_act_c_=table_equipe->columnCount();
		for(int i=0;i<nb_act_l_-1;i++){
			table_equipe->item(i,0)->setIcon(table_equipe->item(i+1,0)->icon());
			for(int j=0;j<nb_act_c_;j++){
				table_equipe->item(i,j)->setText(table_equipe->item(i+1,j)->text());
			}
		}
		table_equipe->item(nb_act_l_-1,0)->setIcon(QIcon());
		for(int j=0;j<nb_act_c_;j++){
			table_equipe->item(nb_act_l_-1,j)->setText("");
		}
	}
}

void DialogueEquipe::maj_description(int _ligne){
	if(_ligne>=equipe.size()){
		return;
	}
	PokemonDresse pk_=equipe[_ligne];
	nom->setText(traduire(Import::_noms_pk_,*pk_.adr_nom(),langue));
	niveau->setText(QString::number(*pk_.adr_niveau()));
	genre->setText(traduire(Import::_noms_genres_,*pk_.adr_genre(),langue));
	capacite->setText(traduire(Import::_noms_capacites_,*pk_.adr_capacite(),langue));
	objet->setText(traduire(Import::_noms_objets_,*pk_.adr_nom_objet(),langue));
	QStringList attaques_=*pk_.adr_attaques();
	QStringList attaques_2_;
	foreach(QString a,attaques_){
		attaques_2_<<traduire(Import::_noms_attaques_,a,langue);
	}
	attaques->setPlainText(attaques_2_.join("\n"));
}

void DialogueEquipe::ajouter_pokemon(){
	int nb_membre_=equipe.size();
	int nb_pk_max_=(int)Import::constante_numerique("MAX_PKEQ");
	if(nb_membre_>=nb_pk_max_){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("MAX_EQ"));
		return;
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_DRESSE,this,DialoguePkCombat::RIEN);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		equipe<<dial_->nv_pk_dresse();
		maj_equipe();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void DialogueEquipe::inserer_pokemon(){
	int nb_membre_=equipe.size();
	int nb_pk_max_=(int)Import::constante_numerique("MAX_PKEQ");
	if(nb_membre_>nb_pk_max_||table_equipe->currentRow()<0||table_equipe->currentRow()>equipe.size()){
		QString err_;
		if(nb_membre_>=nb_pk_max_){
			err_+=traduire("MAX_EQ")+"\n";
		}
		if(table_equipe->currentRow()<0||table_equipe->currentRow()>equipe.size()){
			err_+=traduire("INDICE_INSERT_INV");
		}
		QMessageBox::critical(this,traduire("ERREUR"),err_);
		return;
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_DRESSE,this,DialoguePkCombat::RIEN);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		equipe.insert(table_equipe->currentRow(),dial_->nv_pk_dresse());
		maj_equipe();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void DialogueEquipe::supprimer_pokemon(){
	if(table_equipe->currentRow()<0||table_equipe->currentRow()>=equipe.size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_SUPPR_INV"));
		return;
	}
	equipe.removeAt(table_equipe->currentRow());
	maj_equipe();
}

void DialogueEquipe::editer_pokemon(){
	if(table_equipe->currentRow()<0||table_equipe->currentRow()>=equipe.size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_EDIT_INV"));
		return;
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_DRESSE,this,DialoguePkCombat::RIEN);
	dial_->maj_pk_dresse_edite(&equipe[table_equipe->currentRow()]);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		equipe[table_equipe->currentRow()]=dial_->nv_pk_dresse();
		maj_equipe();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void DialogueEquipe::maj_equipe_recompense(const QPair<QList<PokemonDresse>,int>& _equipe_rec){
	setWindowTitle(traduire("TITRE_2"));
	equipe=_equipe_rec.first;
	recompense=_equipe_rec.second;
	champ_recompense->setText(QString::number(recompense));
	table_equipe->setRowCount(equipe.size());
	int nb_act_l_=equipe.size();
	int nb_act_c_=table_equipe->columnCount();
	for(int i=1;i<nb_act_l_;i++){
		for(int j=0;j<nb_act_c_;j++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText("");
			table_equipe->setItem(i,j,element_);
		}
	}
	for(int i=0;i<nb_act_l_;i++){
		int num_pk_=Import::_pokedex_.valeur(*equipe[i].adr_nom())->num();
		table_equipe->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
		table_equipe->item(i,0)->setText(traduire(Import::_noms_pk_,*equipe[i].adr_nom(),langue));
		table_equipe->item(i,1)->setText(QString::number(*equipe[i].adr_niveau()));
	}
}

QPair<QList<PokemonDresse>,int> DialogueEquipe::equipe_recompense()const{
	return QPair<QList<PokemonDresse>,int>(equipe,champ_recompense->text().toInt());
}

bool DialogueEquipe::rejete()const{
	return rejeter;
}

void DialogueEquipe::acceptation(){
	rejeter=false;
	close();
}

void DialogueEquipe::closeEvent(QCloseEvent* _ev){
	if(rejeter){
		return;
	}
	QString erreur_;
	if(equipe.isEmpty()){
		erreur_+=traduire("EQUIPE_VIDE")+"\n";
	}
	int i_=0;
	QString ch_=champ_recompense->text();
	if(champ_recompense->validator()->validate(ch_,i_)!=QValidator::Acceptable){
		QStringList args_;
		args_<<ch_;
		args_<<QString::number(i_);
		erreur_+=Utilitaire::formatter(traduire("RECOMPENSE_INVALIDE"),args_);
	}
	if(erreur_!=""){
		_ev->ignore();
		rejeter=true;
		QMessageBox::information(this,traduire("ERREUR"),erreur_);
	}
}



