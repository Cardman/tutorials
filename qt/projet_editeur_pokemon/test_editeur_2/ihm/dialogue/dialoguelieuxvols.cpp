#include "ihm/dialogue/dialoguelieuxvols.h"
#include "ihm/dialogue/dialoguecoords.h"
#include "ihm/grilles/grillemap.h"
#include "pseudo_ihm/tuilemap.h"
#include "base_donnees/import.h"
#include "serialisable/donnees.h"
#include "autre/utilitaire.h"
#include <QComboBox>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>

const HashMap<QString,QStringList> DialogueLieuxVols::_elements_ihm_=DialogueLieuxVols::init_elements_ihm();

HashMap<QString,QStringList> DialogueLieuxVols::init_elements_ihm(){
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

QString DialogueLieuxVols::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}


DialogueLieuxVols::DialogueLieuxVols(int _langue,QWidget* _parent,Donnees* _donnees,const HashMap<QPair<int,int>,Coordonnees>& _lieux_vols):QDialog(_parent){
	lieux_vols=_lieux_vols;
	langue=_langue;
	donnees=_donnees;
	rejete=true;
	setWindowTitle(traduire("TITRE"));
	QSplitter *split_=new QSplitter();
	QScrollArea *asc_=new QScrollArea();
	grille=new GrilleMap();//donnees.minimap()
	connect(grille,SIGNAL(selection(const QPair<int,int>&)),this,SLOT(maj_coords(const QPair<int,int>&)));
	grille->init();
	asc_->setWidget(grille);
	split_->addWidget(asc_);
	HashMap<QPair<int,int>,QString> images_minimap_=donnees->minimap();
	QList<QPair<int,int> > cles_=images_minimap_.cles();
	Utilitaire::trier<QPair<int,int> >(cles_,false);
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
		tuile_g_->maj_image(Import::_elements_map_.valeur(images_minimap_.valeur(o)));
	}
	grille->repaint();
	QVBoxLayout *lay_b_=new QVBoxLayout();
	coord_donnees=new QLabel();
	coord_donnees->setText("");
	lay_b_->addWidget(coord_donnees);
	QPushButton *bouton_=new QPushButton(traduire("EDITER_LIEN"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(maj_lien()));
	lay_b_->addWidget(bouton_);
	bouton_=new QPushButton(traduire("SUPPRIMER_LIEN_COURANT"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(supprimer_lien()));
	lay_b_->addWidget(bouton_);
	bouton_=new QPushButton(traduire("VALIDER"));
	connect(bouton_,SIGNAL(clicked()),this,SLOT(acceptation()));
	lay_b_->addWidget(bouton_);
	QWidget *boutons_=new QWidget();
	boutons_->setLayout(lay_b_);
	asc_=new QScrollArea();
	asc_->setWidget(boutons_);
	split_->addWidget(asc_);
	QVBoxLayout *centre_=new QVBoxLayout();
	centre_->addWidget(split_);
	setLayout(centre_);
}

HashMap<QPair<int,int>,Coordonnees> DialogueLieuxVols::vols()const{
	return lieux_vols;
}

bool DialogueLieuxVols::rejet()const{
	return rejete;
}

void DialogueLieuxVols::closeEvent(QCloseEvent* _event){
	if(rejete){
		return;
	}
	if(lieux_vols.total()==0){
		rejete=true;
		_event->ignore();
		QMessageBox::critical(this,traduire("ERREUR"),traduire("MESS_ERREUR"));
	}
}

void DialogueLieuxVols::maj_coords(const QPair<int,int>& _coords){
	coords=_coords;
	grille->repaint();
}

void DialogueLieuxVols::supprimer_lien(){
	if(lieux_vols.cles().contains(coords)){
		lieux_vols.supprimer_cle_valeur(coords);
	}
}

void DialogueLieuxVols::maj_lien(){
	DialogueCoords *dial_=new DialogueCoords(langue,coord_act,donnees,this,DialogueCoords::LIEU_VOL);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_&&dial_->acceptable()){
		//*donnees->ligue(coords.lieu())->adr_origine()=dial_->coordonnees()
		coord_act=dial_->coordonnees();
		coord_donnees->setText(coord_act.formater());
		lieux_vols.ajouter_cle_valeur(coords,coord_act);
	}
	delete dial_;
	dial_=NULL;
}

void DialogueLieuxVols::acceptation(){
	rejete=false;
	close();
}

