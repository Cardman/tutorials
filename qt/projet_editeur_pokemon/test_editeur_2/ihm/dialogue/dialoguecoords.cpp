#include "ihm/dialogue/dialoguecoords.h"
#include "ihm/grilles/grilledialogue.h"
#include "ihm/fenetre.h"
#include "pseudo_ihm/tuilegraphique.h"
#include "base_donnees/import.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "autre/utilitaire.h"
#include <QTableWidget>
#include <QSplitter>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

const HashMap<QString,QStringList> DialogueCoords::_elements_ihm_=DialogueCoords::init_elements_ihm();

HashMap<QString,QStringList> DialogueCoords::init_elements_ihm(){
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

QString DialogueCoords::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString DialogueCoords::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueCoords::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueCoords::DialogueCoords(int _langue,const Coordonnees& _coords_depart,Donnees* _donnees,QWidget* _parent,int _type):QDialog(_parent){
	langue=_langue;
	acceptable_coords=false;
	donnees=_donnees;
	QStringList args_;
	if(_type==DialogueCoords::DEPART){
		args_<<traduire("DEPART");
	}else if(_type==DialogueCoords::LIAISON){
		args_<<traduire("LIAISON");
	}else if(_type==DialogueCoords::LIEU_VOL){
		args_<<traduire("LIEU_VOL");
	}
	setWindowTitle(Utilitaire::formatter(traduire("TITRE"),args_));
	cles_lieux=donnees->lieux_c();
	HashMap<int,QPair<QString,QString> > texte_aff_=donnees->nom_type_lieux();
	int nb_pl_=cles_lieux.size();
	QSplitter *split_=new QSplitter(Qt::Vertical);
	QStringList etiquettes_;
	etiquettes_<<traduire("ETIQUETTE_NOM");
	etiquettes_<<traduire("ETIQUETTE_TYPE");
	table_lieux=new QTableWidget(nb_pl_,2);
	table_lieux->setHorizontalHeaderLabels(etiquettes_);
	for(int i=0;i<nb_pl_;i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText(texte_aff_.valeur(i).first.split("\t")[langue]);
		table_lieux->setItem(i,0,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_type_lieux_,texte_aff_.valeur(i).second,langue));
		table_lieux->setItem(i,1,element_);
	}
	connect(table_lieux,SIGNAL(cellClicked(int,int)),this,SLOT(maj_table(int)));
	split_->addWidget(table_lieux);
	cles_plateaux=QList<int>();
	table_plateaux=new QTableWidget(1,1);
	QTableWidgetItem *element_=new QTableWidgetItem();
	element_->setText("");
	table_plateaux->setItem(0,0,element_);
	connect(table_plateaux,SIGNAL(cellClicked(int,int)),this,SLOT(maj_grille(int)));
	split_->addWidget(table_plateaux);
	QScrollArea *asc_=new QScrollArea();
	grille=new GrilleDialogue();
	connect(grille,SIGNAL(selection(const QPair<QPair<int,int>,QPair<int,int> >&)),this,SLOT(maj_coords(const QPair<QPair<int,int>,QPair<int,int> >&)));
	asc_->setWidget(grille);
	grille->init();
	grille->repaint();
	split_->addWidget(asc_);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	split_->addWidget(valider_);
	QVBoxLayout *centre_=new QVBoxLayout();
	centre_->addWidget(split_);
	coords=_coords_depart;
	coords_et=new QLabel(_coords_depart.formater());
	centre_->addWidget(coords_et);
	setLayout(centre_);
}

Coordonnees DialogueCoords::coordonnees()const{
	return coords;
}

bool DialogueCoords::acceptable()const{
	return acceptable_coords;
}

void DialogueCoords::maj_table(int _lieu){
	acceptable_coords=false;
	coords.adr_lieu_plateau()->first=cles_lieux[_lieu];
	coords_et->setText(coords.formater());
	cles_plateaux=donnees->lieu(cles_lieux[_lieu])->plateaux_c();
	int nb_pl_=cles_plateaux.size();
	int nb_l_=table_plateaux->rowCount();
	if(nb_l_<nb_pl_){
		table_plateaux->setRowCount(nb_pl_);
		for(int i=nb_l_;i<nb_pl_;i++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText(QString::number(i));
			table_plateaux->setItem(i,0,element_);
		}
	}
	for(int i=0;i<nb_pl_;i++){
		table_plateaux->item(i,0)->setText(QString::number(i));
	}
	for(int i=nb_pl_;i<nb_l_;i++){
		table_plateaux->item(i,0)->setText("");
	}
	grille->table_rase();
	//table=new QTableWidget(nb_pl_,1)
}

void DialogueCoords::maj_grille(int _plateau){
	acceptable_coords=false;
	if(_plateau>=cles_plateaux.size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("MAUVAISES_COORDS"));
		return;
	}
	coords.adr_lieu_plateau()->second=cles_plateaux[_plateau];
	coords_et->setText(coords.formater());
	Plateau *pl_=donnees->lieu(coords.lieu())->plateau(cles_plateaux[_plateau]);
	QPair<int,int> dims_=pl_->dimensions();
	if(grille->nb_lignes()<dims_.second){
		grille->ajouter_lignes(dims_.second-grille->nb_lignes());
	}
	if(grille->nb_colonnes()<dims_.first){
		grille->ajouter_colonnes(dims_.first-grille->nb_colonnes());
	}
	typedef QPair<QPair<int,int>,QPair<int,int> > OrigineLien;
	foreach(OrigineLien o,pl_->liaisons_vers_autres_plateaux()){
		TuileGraphique *tuile_g_=grille->tuile(o.second.first+o.first.first,o.second.second+o.first.second);
		tuile_g_->maj_lien(QPair<QImage,bool>(Import::_liens_.valeur(pl_->image_origine_liaison(o)),true));
	}
	typedef QPair<int,int> Origine;
	foreach(Origine o,pl_->coins_gauche()){
		bool suppr_=false;
		Environnement *env_=pl_->environnement(o,suppr_);
		QPair<int,int> dims_env_=env_->dimensions();
		for(int i=0;i<dims_env_.first;i++){
			for(int j=0;j<dims_env_.second;j++){
				TuileGraphique *tuile_g_=grille->tuile(i+o.first,j+o.second);
				tuile_g_->maj_coords(QPair<int,int>(i,j));
				Tuile *tuile_=env_->tuile(QPair<int,int>(i,j));
				tuile_g_->maj_image(Import::_tuiles_importees_.valeur(*tuile_->adr_nom_image()));
				QString nom_obstacle_=tuile_->adr_nom_image_obst()->first;
				if(Import::_arbres_.cles().contains(nom_obstacle_)){
					tuile_g_->maj_obst(QPair<QImage,bool>(Import::_arbres_.valeur(nom_obstacle_),true));
				}else if(Import::_rochers_destructibles_.cles().contains(nom_obstacle_)){
					tuile_g_->maj_obst(QPair<QImage,bool>(Import::_rochers_destructibles_.valeur(nom_obstacle_),true));
				}else if(Import::_rochers_amovibles_.cles().contains(nom_obstacle_)){
					tuile_g_->maj_obst(QPair<QImage,bool>(Import::_rochers_amovibles_.valeur(nom_obstacle_),true));
				}else if(Import::_tourbillons_.cles().contains(nom_obstacle_)){
					tuile_g_->maj_obst(QPair<QImage,bool>(Import::_tourbillons_.valeur(nom_obstacle_),true));
				}
				if(env_->coords_autres_persos().contains(QPair<int,int>(i,j))){
					Personnage *perso_=env_->personnage(QPair<int,int>(i,j),suppr_);
					tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*perso_->adr_nom_miniature()),*perso_->adr_orientation()));
				}else if(env_->coords_dresseurs().contains(QPair<int,int>(i,j))){
					Dresseur1 *perso_=env_->dresseur(QPair<int,int>(i,j),suppr_);
					tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*perso_->adr_nom_miniature()),*perso_->adr_orientation()));
				}else if(env_->coords_champions().contains(QPair<int,int>(i,j))){
					Champion *perso_=env_->champion(QPair<int,int>(i,j),suppr_);
					tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*perso_->adr_nom_miniature()),*perso_->adr_orientation()));
				}else if(env_->coords_objets().contains(QPair<int,int>(i,j))){
					bool suppr_=false;
					QString *objet_=env_->objet(QPair<int,int>(i,j),suppr_);
					tuile_g_->maj_obst(QPair<QImage,bool>(Import::_images_objets_.valeur(*objet_),true));
				}else if(env_->coords_pokemon_legendaire().contains(QPair<int,int>(i,j))){
					bool suppr_=false;
					Pokemon *pokemon_=env_->pokemon_legendaire(QPair<int,int>(i,j),suppr_);
					int num_pk_=Import::_pokedex_.valeur(*pokemon_->adr_nom())->num();
					tuile_g_->maj_obst(QPair<QImage,bool>(Import::_miniatures_.valeur(num_pk_),true));
				}else if(env_->coords_lieux_dons_pokemon().contains(QPair<int,int>(i,j))){
					tuile_g_->maj_obst(QPair<QImage,bool>(Import::_pk_trouve_,true));
				}
			}
		}
	}
	grille->repaint();
}

void DialogueCoords::maj_coords(const QPair<QPair<int,int>,QPair<int,int> >& _coords){
	if(!donnees->lieu(coords.lieu())->plateau(coords.plateau())->coins_gauche().contains(_coords.first)){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("MAUVAISES_COORDS"));
		return;
	}
	acceptable_coords=true;
	*coords.adr_environnement()=_coords.first;
	*coords.adr_tuile()=_coords.second;
	coords_et->setText(coords.formater());
}


