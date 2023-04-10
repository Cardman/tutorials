#include "ihm/dialogue/dialogueediteurmap.h"
#include "ihm/dialogue/dialoguegrille.h"
#include "ihm/grilles/grillemap.h"
#include "pseudo_ihm/tuilemap.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QComboBox>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSplitter>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>

const HashMap<QString,QStringList> DialogueEditeurMap::_elements_ihm_=DialogueEditeurMap::init_elements_ihm();

HashMap<QString,QStringList> DialogueEditeurMap::init_elements_ihm(){
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

QString DialogueEditeurMap::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}


DialogueEditeurMap::DialogueEditeurMap(int _langue,QWidget* _parent,const HashMap<QPair<int,int>,QString>& _images_minimap):QDialog(_parent){
	langue=_langue;
	setWindowTitle(traduire("TITRE"));
	images_minimap=_images_minimap;
	rejete=true;
	QSplitter *split_=new QSplitter();
	QScrollArea *asc_=new QScrollArea();
	grille=new GrilleMap();
	connect(grille,SIGNAL(selection(const QPair<int,int>&)),this,SLOT(maj_coords(const QPair<int,int>&)));
	grille->init();
	asc_->setWidget(grille);
	split_->addWidget(asc_);
	QList<QPair<int,int> > cles_=images_minimap.cles();
	Utilitaire::trier<QPair<int,int> >(cles_,false);
	if(!cles_.isEmpty()){
		QPair<int,int> dims_=QPair<int,int>(cles_[0].first+1,cles_[0].second+1);
		if(grille->nb_lignes()<dims_.second){
			grille->ajouter_lignes(dims_.second-grille->nb_lignes());
		}
		if(grille->nb_colonnes()<dims_.first){
			grille->ajouter_colonnes(dims_.first-grille->nb_colonnes());
		}
		typedef QPair<int,int> Origine;
		foreach(Origine o,cles_){
			TuileMap *tuile_g_=grille->tuile(o.first,o.second);
			tuile_g_->maj_image(Import::_elements_map_.valeur(images_minimap.valeur(o)));
		}
	}
	grille->repaint();
	QGridLayout *lay_bout_=new QGridLayout();
	QPushButton *bouton_=new QPushButton(traduire("AJ_LIGNE_H"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajouter_ligne_ht_plateau()));
	lay_bout_->addWidget(bouton_,0,0);
	bouton_=new QPushButton(traduire("AJ_LIGNE_B"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajouter_ligne_bas_plateau()));
	lay_bout_->addWidget(bouton_,0,1);
	bouton_=new QPushButton(traduire("AJ_COL_G"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajouter_col_gauche_plateau()));
	lay_bout_->addWidget(bouton_,0,2);
	bouton_=new QPushButton(traduire("AJ_COL_D"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajouter_col_droite_plateau()));
	lay_bout_->addWidget(bouton_,0,3);
	bouton_=new QPushButton(traduire("AJ_LIGNES_H"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajouter_lignes_ht_plateau()));
	lay_bout_->addWidget(bouton_,1,0);
	bouton_=new QPushButton(traduire("AJ_LIGNES_B"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajouter_lignes_bas_plateau()));
	lay_bout_->addWidget(bouton_,1,1);
	bouton_=new QPushButton(traduire("AJ_COLS_G"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajouter_cols_gauche_plateau()));
	lay_bout_->addWidget(bouton_,1,2);
	bouton_=new QPushButton(traduire("AJ_COLS_D"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(ajouter_cols_droite_plateau()));
	lay_bout_->addWidget(bouton_,1,3);
	bouton_=new QPushButton(traduire("SUPPR_LIGNE"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(supprimer_ligne_map()));
	lay_bout_->addWidget(bouton_,2,0);
	bouton_=new QPushButton(traduire("SUPPR_TUILE"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(supprimer_tuile_map()));
	lay_bout_->addWidget(bouton_,2,1);
	bouton_=new QPushButton(traduire("SUPPR_COL"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(supprimer_colonne_map()));
	lay_bout_->addWidget(bouton_,2,2);
	elements_map=new QComboBox();
	foreach(QString s,Import::_elements_map_.cles()){
		elements_map->addItem(QPixmap::fromImage(Import::_elements_map_.valeur(s)),s);
	}
	elements_map->setEditable(true);
	connect(elements_map,SIGNAL(editTextChanged(QString)),this,SLOT(maj_tuile_courante()));
	lay_bout_->addWidget(elements_map,2,3);
	asc_=new QScrollArea();
	QWidget *boutons_=new QWidget();
	boutons_->setLayout(lay_bout_);
	asc_->setWidget(boutons_);
	split_->addWidget(asc_);
	QVBoxLayout *centre_=new QVBoxLayout();
	centre_->addWidget(split_);
	bouton_=new QPushButton(traduire("VALIDER"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(acceptation()));
	centre_->addWidget(bouton_);
	setLayout(centre_);
}

void DialogueEditeurMap::ajouter_ligne_ht_plateau(){
	grille->decaler_vers_bas(1);
	QList<QPair<int,int> > cles_=images_minimap.cles();
	Utilitaire::trier<QPair<int,int> >(cles_,false);
	typedef QPair<int,int> Origine;
	foreach(Origine o,cles_){
		QString valeur_=images_minimap.valeur(o);
		images_minimap.supprimer_cle_valeur(o);
		images_minimap.ajouter_cle_valeur(QPair<int,int>(o.first,o.second+1),valeur_);
	}
	grille->repaint();
}

void DialogueEditeurMap::ajouter_ligne_bas_plateau(){
	grille->ajouter_lignes(1);
}

void DialogueEditeurMap::ajouter_col_gauche_plateau(){
	grille->decaler_vers_droite(1);
	QList<QPair<int,int> > cles_=images_minimap.cles();
	Utilitaire::trier<QPair<int,int> >(cles_,false);
	typedef QPair<int,int> Origine;
	foreach(Origine o,cles_){
		QString valeur_=images_minimap.valeur(o);
		images_minimap.supprimer_cle_valeur(o);
		images_minimap.ajouter_cle_valeur(QPair<int,int>(o.first+1,o.second),valeur_);
	}
	grille->repaint();
}

void DialogueEditeurMap::ajouter_col_droite_plateau(){
	grille->ajouter_colonnes(1);
}

void DialogueEditeurMap::ajouter_lignes_ht_plateau(){
	DialogueGrille *dialogue_=new DialogueGrille(langue,DialogueGrille::AJOUT_LGS_HAUT,this);
	dialogue_->exec();
	bool accepter_=dialogue_->result()==QDialog::Accepted;
	if(accepter_){
		int nb_lgs_=dialogue_->valeur();
		grille->decaler_vers_bas(nb_lgs_);
		QList<QPair<int,int> > cles_=images_minimap.cles();
		Utilitaire::trier<QPair<int,int> >(cles_,false);
		typedef QPair<int,int> Origine;
		foreach(Origine o,cles_){
			QString valeur_=images_minimap.valeur(o);
			images_minimap.supprimer_cle_valeur(o);
			images_minimap.ajouter_cle_valeur(QPair<int,int>(o.first,o.second+nb_lgs_),valeur_);
		}
		grille->repaint();
	}
	delete dialogue_;
	dialogue_=NULL;
}

void DialogueEditeurMap::ajouter_lignes_bas_plateau(){
	DialogueGrille *dialogue_=new DialogueGrille(langue,DialogueGrille::AJOUT_LGS_BAS,this);
	dialogue_->exec();
	bool accepter_=dialogue_->result()==QDialog::Accepted;
	if(accepter_){
		grille->ajouter_lignes(dialogue_->valeur());
		grille->repaint();
	}
	delete dialogue_;
	dialogue_=NULL;
}

void DialogueEditeurMap::ajouter_cols_gauche_plateau(){
	DialogueGrille *dialogue_=new DialogueGrille(langue,DialogueGrille::AJOUT_COLS_GAUCHE,this);
	dialogue_->exec();
	bool accepter_=dialogue_->result()==QDialog::Accepted;
	if(accepter_){
		int nb_lgs_=dialogue_->valeur();
		QList<QPair<int,int> > cles_=images_minimap.cles();
		Utilitaire::trier<QPair<int,int> >(cles_,false);
		typedef QPair<int,int> Origine;
		foreach(Origine o,cles_){
			QString valeur_=images_minimap.valeur(o);
			images_minimap.supprimer_cle_valeur(o);
			images_minimap.ajouter_cle_valeur(QPair<int,int>(o.first+nb_lgs_,o.second),valeur_);
		}
		grille->decaler_vers_droite(nb_lgs_);
		grille->repaint();
	}
	delete dialogue_;
	dialogue_=NULL;
}

void DialogueEditeurMap::ajouter_cols_droite_plateau(){
	DialogueGrille *dialogue_=new DialogueGrille(langue,DialogueGrille::AJOUT_COLS_DROITE,this);
	dialogue_->exec();
	bool accepter_=dialogue_->result()==QDialog::Accepted;
	if(accepter_){
		grille->ajouter_colonnes(dialogue_->valeur());
		grille->repaint();
	}
	delete dialogue_;
	dialogue_=NULL;
}

void DialogueEditeurMap::supprimer_ligne_map(){
	int ligne_courante_=coords.second;
	QList<QPair<int,int> > cles_=images_minimap.cles();
	typedef QPair<int,int> Origine;
	foreach(Origine o,cles_){
		if(o.second==ligne_courante_){
			images_minimap.supprimer_cle_valeur(o);
		}
	}
	Utilitaire::trier<QPair<int,int> >(cles_,true);
	foreach(Origine o,cles_){
		if(o.second>ligne_courante_){
			QString valeur_=images_minimap.valeur(o);
			images_minimap.supprimer_cle_valeur(o);
			images_minimap.ajouter_cle_valeur(QPair<int,int>(o.first,o.second-1),valeur_);
		}
	}
	grille->table_rase();
	int max_=-1;
	foreach(Origine o,cles_){
		if(o.second>ligne_courante_){
			max_=o.second;
			TuileMap *tuile_g_=grille->tuile(o.first,o.second-1);
			TuileMap *tuile_g_2_=grille->tuile(o.first,o.second);
			tuile_g_->affecter(tuile_g_2_);
		}
	}
	foreach(Origine o,cles_){
		if(o.second==max_){
			TuileMap *tuile_g_=grille->tuile(o.first,o.second);
			tuile_g_->reinit();
		}
	}
	grille->repaint();
}

void DialogueEditeurMap::supprimer_colonne_map(){
	int ligne_courante_=coords.first;
	QList<QPair<int,int> > cles_=images_minimap.cles();
	typedef QPair<int,int> Origine;
	foreach(Origine o,cles_){
		if(o.first==ligne_courante_){
			images_minimap.supprimer_cle_valeur(o);
		}
	}
	Utilitaire::trier<QPair<int,int> >(cles_,true);
	foreach(Origine o,cles_){
		if(o.first>ligne_courante_){
			QString valeur_=images_minimap.valeur(o);
			images_minimap.supprimer_cle_valeur(o);
			images_minimap.ajouter_cle_valeur(QPair<int,int>(o.first-1,o.second),valeur_);
		}
	}
	grille->table_rase();
	int max_=-1;
	foreach(Origine o,cles_){
		if(o.first>ligne_courante_){
			max_=o.first;
			TuileMap *tuile_g_=grille->tuile(o.first-1,o.second);
			TuileMap *tuile_g_2_=grille->tuile(o.first,o.second);
			tuile_g_->affecter(tuile_g_2_);
		}
	}
	foreach(Origine o,cles_){
		if(o.first==max_){
			TuileMap *tuile_g_=grille->tuile(o.first,o.second);
			tuile_g_->reinit();
		}
	}
	grille->repaint();
}

void DialogueEditeurMap::supprimer_tuile_map(){
	QList<QPair<int,int> > cles_=images_minimap.cles();
	if(cles_.contains(coords)){
		images_minimap.supprimer_cle_valeur(coords);
		TuileMap *tuile_g_=grille->tuile(coords.first,coords.second);
		tuile_g_->reinit();
		grille->repaint();
	}
}

void DialogueEditeurMap::maj_tuile_courante(){
	if(elements_map->findText(elements_map->currentText())<0){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("NOM_INEX"));
		return;
	}
	images_minimap.ajouter_cle_valeur(coords,elements_map->currentText());
	TuileMap *tuile_g_=grille->tuile(coords.first,coords.second);
	tuile_g_->maj_image(Import::_elements_map_.valeur(elements_map->currentText()));
	grille->repaint();
}

void DialogueEditeurMap::maj_coords(const QPair<int,int>& _coords){
	coords=_coords;
	grille->repaint();
}

bool DialogueEditeurMap::carte_valide()const{
	QList<QPair<int,int> > cles_=images_minimap.cles();
	if(!cles_.contains(QPair<int,int>(0,0))){
		return false;
	}
	Utilitaire::trier<QPair<int,int> >(cles_,false);
	QPair<int,int> dims_=QPair<int,int>(cles_[0].first+1,cles_[0].second+1);
	return dims_.first*dims_.second==cles_.size();
}

bool DialogueEditeurMap::rejet()const{
	return rejete;
}

HashMap<QPair<int,int>,QString> DialogueEditeurMap::carte_modif()const{
	return images_minimap;
}

void DialogueEditeurMap::acceptation(){
	rejete=false;
	close();
}

void DialogueEditeurMap::closeEvent(QCloseEvent* _event){
	if(rejete){
		return;
	}
	if(!carte_valide()){
		rejete=true;
		_event->ignore();
		QMessageBox::critical(this,traduire("ERREUR"),traduire("MESSAGE_ERR"));
	}
}


