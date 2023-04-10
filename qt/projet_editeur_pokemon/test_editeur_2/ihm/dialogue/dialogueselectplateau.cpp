#include "ihm/dialogue/dialogueselectplateau.h"
#include "ihm/grilles/grillevisuelle.h"
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

const HashMap<QString,QStringList> DialogueSelectPlateau::_elements_ihm_=DialogueSelectPlateau::init_elements_ihm();

HashMap<QString,QStringList> DialogueSelectPlateau::init_elements_ihm(){
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

QString DialogueSelectPlateau::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

DialogueSelectPlateau::DialogueSelectPlateau(int _langue,bool _a_suppr,QWidget* _parent,bool _lieu,bool _aj_suppl):QDialog(_parent){
	langue=_langue;
	lieu_select=_lieu;
	if(_a_suppr){
		setWindowTitle(traduire("TITRE_S"));
	}else{
		setWindowTitle(traduire("TITRE"));
	}
	QSplitter *split_=new QSplitter();
	aj_suppl=false;
	if(lieu_select){
		cles_plateaux=Fenetre::_lieu_en_cours_->plateaux_c();
	}else{
		int nb_pl_=Fenetre::_ligue_en_cours_->nb_plateaux();
		for(int i=0;i<nb_pl_;i++){
			cles_plateaux<<i;
		}
		aj_suppl=_aj_suppl;
		if(_aj_suppl){
			cles_plateaux<<nb_pl_;
		}
	}
	int nb_pl_=cles_plateaux.size();
	table=new QTableWidget(nb_pl_,1);
	for(int i=0;i<nb_pl_;i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText(QString::number(i));
		table->setItem(i,0,element_);
	}
	connect(table,SIGNAL(cellClicked(int,int)),this,SLOT(maj_grille(int)));
	split_->addWidget(table);
	QScrollArea *asc_=new QScrollArea();
	grille=new GrilleVisuelle();
	asc_->setWidget(grille);
	grille->init();
	grille->repaint();
	split_->addWidget(asc_);
	QVBoxLayout *centre_=new QVBoxLayout();
	centre_->addWidget(split_);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	centre_->addWidget(valider_);
	setLayout(centre_);
}

int DialogueSelectPlateau::plateau_select()const{
	if(table->currentRow()<0||table->currentRow()>=cles_plateaux.size()){
		return -1;
	}
	return cles_plateaux[table->currentRow()];
}

void DialogueSelectPlateau::maj_grille(int _indice){
	grille->table_rase();
	if(lieu_select){
		Plateau *pl_=Fenetre::_lieu_en_cours_->plateau(cles_plateaux[_indice]);
		QPair<int,int> dims_=pl_->dimensions();
		QPair<int,int> coin_gauche_pl_=pl_->bords().first;
		if(grille->nb_lignes()<coin_gauche_pl_.second+dims_.second){
			grille->ajouter_lignes(coin_gauche_pl_.second+dims_.second-grille->nb_lignes());
		}
		if(grille->nb_colonnes()<coin_gauche_pl_.first+dims_.first){
			grille->ajouter_colonnes(coin_gauche_pl_.first+dims_.first-grille->nb_colonnes());
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
	}else{
		if(_indice+1==cles_plateaux.size()&&aj_suppl){
			return;
		}
		PlateauLigue *pl_=Fenetre::_ligue_en_cours_->plateau(cles_plateaux[_indice]);
		QPair<int,int> dims_=pl_->dimensions();
		if(grille->nb_lignes()<dims_.second){
			grille->ajouter_lignes(dims_.second-grille->nb_lignes());
		}
		if(grille->nb_colonnes()<dims_.first){
			grille->ajouter_colonnes(dims_.first-grille->nb_colonnes());
		}
		typedef QPair<int,int> Origine;
		foreach(Origine o,pl_->coins_gauche()){
			bool suppr_=false;
			EnvironnementLigue *env_=pl_->environnement(o,suppr_);
			QPair<int,int> dims_env_=env_->dimensions();
			for(int i=0;i<dims_env_.first;i++){
				for(int j=0;j<dims_env_.second;j++){
					TuileGraphique *tuile_g_=grille->tuile(i+o.first,j+o.second);
					Tuile *tuile_=env_->tuile(QPair<int,int>(i,j));
					tuile_g_->maj_image(Import::_tuiles_importees_.valeur(*tuile_->adr_nom_image()));
				}
			}
		}
		QPair<int,int> coords_=*pl_->adr_coords_dresseur();
		if(coords_.first<grille->nb_colonnes()&&coords_.second<grille->nb_lignes()){
			TuileGraphique *tuile_g_=grille->tuile(coords_.first,coords_.second);
			DresseurLigue *dr_=pl_->adr_dresseur_ligue();
			if(Import::_dresseurs_micros_.cles().contains(*dr_->adr_nom_miniature())){
				tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*dr_->adr_nom_miniature()),*dr_->adr_orientation()));
			}
		}
	}
	grille->repaint();
}


