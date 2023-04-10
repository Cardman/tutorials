#include "ihm/dialogue/dialogueaccescarte.h"
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
#include <QFormLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QComboBox>

const HashMap<QString,QStringList> DialogueAccesCarte::_elements_ihm_=DialogueAccesCarte::init_elements_ihm();

HashMap<QString,QStringList> DialogueAccesCarte::init_elements_ihm(){
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

QString DialogueAccesCarte::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueAccesCarte::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

QString DialogueAccesCarte::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

DialogueAccesCarte::DialogueAccesCarte(int _langue,QWidget* _parent):QDialog(_parent){
	acceptable_coords=false;
	acceptable_coords_dest=false;
	langue=_langue;
	setWindowTitle(traduire("TITRE"));
	donnees=qobject_cast<Fenetre*>(_parent)->adr_donnees();
	QSplitter *split_c_=new QSplitter();
	QSplitter *split_=new QSplitter(Qt::Vertical);
	cles_lieux=donnees->lieux_c();
	HashMap<int,QPair<QString,QString> > texte_aff_=donnees->nom_type_lieux();
	int nb_pl_=cles_lieux.size();
	QStringList etiquettes_;
	etiquettes_<<traduire("ETIQUETTE_NOM");
	etiquettes_<<traduire("ETIQUETTE_TYPE");
	table_lieux=new QTableWidget(nb_pl_,etiquettes_.size());
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
	split_c_->addWidget(split_);
	//Droite
	split_=new QSplitter(Qt::Vertical);
	cles_ligues=donnees->ligues_c();
	nb_pl_=cles_ligues.size();
	table_ligues=new QTableWidget(nb_pl_,1);
	for(int i=0;i<nb_pl_;i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText(QString::number(i));
		table_ligues->setItem(i,0,element_);
	}
	split_->addWidget(table_ligues);
	QPushButton *ajout_ligue_=new QPushButton(traduire("AJOUT_LIGUE"));
	connect(ajout_ligue_,SIGNAL(clicked()),this,SLOT(ajouter_condition_ligue()));
	split_->addWidget(ajout_ligue_);
	QPushButton *supprimer_ligue_=new QPushButton(traduire("SUPPRIMER_LIGUE"));
	connect(supprimer_ligue_,SIGNAL(clicked()),this,SLOT(supprimer_condition_ligue()));
	split_->addWidget(supprimer_ligue_);
	table_ligues_ajoutees=new QTableWidget(nb_pl_,1);
	for(int i=0;i<nb_pl_;i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText("");
		table_ligues_ajoutees->setItem(i,0,element_);
	}
	split_->addWidget(table_ligues_ajoutees);
	QPushButton *maj_condition_=new QPushButton(traduire("MAJ_CONDITION"));
	connect(maj_condition_,SIGNAL(clicked()),this,SLOT(ajouter_condition_acces_coords()));
	split_->addWidget(maj_condition_);
	QPushButton *suppr_condition_=new QPushButton(traduire("SUPPR_CONDITION"));
	connect(suppr_condition_,SIGNAL(clicked()),this,SLOT(supprimer_condition_acces_coords()));
	split_->addWidget(suppr_condition_);
	split_c_->addWidget(split_);
	QVBoxLayout *centre_=new QVBoxLayout();
	centre_->addWidget(split_c_);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	centre_->addWidget(valider_);
	setLayout(centre_);
}

void DialogueAccesCarte::conditions_acces_coords(const HashMap<Coordonnees,QList<int> >& _acces_fct_ligues){
	acces_fct_ligues=_acces_fct_ligues;
}

HashMap<Coordonnees,QList<int> > DialogueAccesCarte::conditions_acces_coords()const{
	return acces_fct_ligues;
}

void DialogueAccesCarte::maj_grille_lien(GrilleDialogue *grille,Donnees *donnees,const Coordonnees& coords){
	typedef QPair<int,QPair<QPair<int,int>,QPair<int,int> > > OrigineLienLieu;
	QList<OrigineLienLieu> liens_=donnees->lieu(coords.lieu())->liaisons_vers_autres_lieux();
	QList<OrigineLienLieu> liens_bis_;
	foreach(OrigineLienLieu o,liens_){
		if(o.first==coords.plateau()){
			liens_bis_<<o;
		}
	}
	HashMap<int,int> gauche_;
	HashMap<int,int> droite_;
	HashMap<int,int> bas_;
	HashMap<int,int> haut_;
	QList<OrigineLienLieu> l_gauche_;
	QList<OrigineLienLieu> l_droite_;
	QList<OrigineLienLieu> l_bas_;
	QList<OrigineLienLieu> l_haut_;
	QPair<QPair<int,int>,QPair<int,int> > bords_=donnees->lieu(coords.lieu())->plateau(coords.plateau())->bords();
	foreach(OrigineLienLieu o,liens_bis_){
		if(o.second.first.first+o.second.second.first==bords_.first.first){
			l_gauche_<<o;
		}else if(o.second.first.first+o.second.second.first==bords_.second.first){
			l_droite_<<o;
		}else if(o.second.first.second+o.second.second.second==bords_.second.second){
			l_bas_<<o;
		}else if(o.second.first.second+o.second.second.second==bords_.first.second){
			l_haut_<<o;
		}
	}
	Utilitaire::trier<OrigineLienLieu>(l_gauche_,true);
	Utilitaire::trier<OrigineLienLieu>(l_droite_,true);
	Utilitaire::trier<OrigineLienLieu>(l_bas_,true);
	Utilitaire::trier<OrigineLienLieu>(l_haut_,true);
	int i_=0;
	while(i_<l_gauche_.size()){
		int nb_=1;
		int cle_=l_gauche_[i_].second.first.second+l_gauche_[i_].second.second.second;
		while(i_+1<l_gauche_.size()){
			OrigineLienLieu or_=l_gauche_[i_];
			OrigineLienLieu or_2_=l_gauche_[i_+1];
			if(or_.second.first.second+or_.second.second.second+1<or_2_.second.first.second+or_2_.second.second.second){
				break;
			}
			nb_++;
			i_++;
		}
		i_++;
		gauche_.ajouter_cle_valeur(cle_,nb_);
		nb_=1;
	}
	foreach(int c,gauche_.cles()){
		grille->maj_dir_lieux(GrilleDialogue::GAUCHE,c,gauche_.valeur(c));
	}
	i_=0;
	while(i_<l_droite_.size()){
		int nb_=1;
		int cle_=l_droite_[i_].second.first.second+l_droite_[i_].second.second.second;
		while(i_+1<l_droite_.size()){
			OrigineLienLieu or_=l_droite_[i_];
			OrigineLienLieu or_2_=l_droite_[i_+1];
			if(or_.second.first.second+or_.second.second.second+1<or_2_.second.first.second+or_2_.second.second.second){
				break;
			}
			nb_++;
			i_++;
		}
		i_++;
		droite_.ajouter_cle_valeur(cle_,nb_);
		nb_=1;
	}
	foreach(int c,droite_.cles()){
		grille->maj_dir_lieux(GrilleDialogue::DROITE,c,droite_.valeur(c));
	}
	i_=0;
	while(i_<l_haut_.size()){
		int nb_=1;
		int cle_=l_haut_[i_].second.first.first+l_haut_[i_].second.second.first;
		while(i_+1<l_haut_.size()){
			OrigineLienLieu or_=l_haut_[i_];
			OrigineLienLieu or_2_=l_haut_[i_+1];
			if(or_.second.first.first+or_.second.second.first+1<or_2_.second.first.first+or_2_.second.second.first){
				break;
			}
			nb_++;
			i_++;
		}
		i_++;
		haut_.ajouter_cle_valeur(cle_,nb_);
		nb_=1;
	}
	foreach(int c,haut_.cles()){
		grille->maj_dir_lieux(GrilleDialogue::HAUT,c,haut_.valeur(c));
	}
	i_=0;
	while(i_<l_bas_.size()){
		int nb_=1;
		int cle_=l_bas_[i_].second.first.first+l_bas_[i_].second.second.first;
		while(i_+1<l_bas_.size()){
			OrigineLienLieu or_=l_bas_[i_];
			OrigineLienLieu or_2_=l_bas_[i_+1];
			if(or_.second.first.first+or_.second.second.first+1<or_2_.second.first.first+or_2_.second.second.first){
				break;
			}
			nb_++;
			i_++;
		}
		i_++;
		bas_.ajouter_cle_valeur(cle_,nb_);
		nb_=1;
	}
	foreach(int c,bas_.cles()){
		grille->maj_dir_lieux(GrilleDialogue::BAS,c,bas_.valeur(c));
	}
}

void DialogueAccesCarte::maj_ligues(){
	int nb_lignes_=table_ligues_ajoutees->rowCount();
	int nb_ligues_=ligues_select.size();
	for(int i=0;i<nb_ligues_;i++){
		table_ligues_ajoutees->item(i,0)->setText(QString::number(i));
	}
	for(int i=nb_ligues_;i<nb_lignes_;i++){
		table_ligues_ajoutees->item(i,0)->setText("");
	}
	//int nb_ligues_=table_ligues
}

void DialogueAccesCarte::maj_table(int _lieu){
	acceptable_coords=false;
	coords.adr_lieu_plateau()->first=cles_lieux[_lieu];
	//coords_et->setText(coords.formater())
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
}

void DialogueAccesCarte::maj_grille(int _plateau){
	grille->table_rase();
	acceptable_coords=false;
	if(_plateau>=cles_plateaux.size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("MAUVAISES_COORDS"));
		return;
	}
	coords.adr_lieu_plateau()->second=cles_plateaux[_plateau];
	//coords_et->setText(coords.formater())
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
	//HashMap<Coordonnees,QList<int> > acces_fct_ligues
	foreach(Coordonnees c,acces_fct_ligues.cles()){
		if(c.lieu()==coords.lieu()&&c.plateau()==coords.plateau()&&!acces_fct_ligues.valeur(c).isEmpty()){
			QPair<int,int> coords_env_=c.coords_environnement();
			QPair<int,int> coords_tuile_=c.coords_tuile();
			TuileGraphique *tuile_g_=grille->tuile(coords_env_.first+coords_tuile_.first,coords_env_.second+coords_tuile_.second);
			tuile_g_->maj_cond_ligue(true);
		}
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
	maj_grille_lien(grille,donnees,coords);
	grille->repaint();
}

void DialogueAccesCarte::maj_coords(const QPair<QPair<int,int>,QPair<int,int> >& _coords){
	if(!donnees->lieu(coords.lieu())->plateau(coords.plateau())->coins_gauche().contains(_coords.first)){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("MAUVAISES_COORDS"));
		return;
	}
	acceptable_coords=true;
	*coords.adr_environnement()=_coords.first;
	*coords.adr_tuile()=_coords.second;
	if(acces_fct_ligues.cles().contains(coords)){
		ligues_select=acces_fct_ligues.valeur(coords);
		maj_ligues();
	}
}

void DialogueAccesCarte::ajouter_condition_ligue(){
	if(!acceptable_coords){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("MAUVAISES_COORDS"));
		return;
	}
	if(table_ligues->currentRow()<0||table_ligues->currentRow()>=table_ligues->rowCount()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("LIGUE_NON_SELECT"));
		return;
	}
	if(ligues_select.contains(cles_ligues[table_ligues->currentRow()])){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("CONDITION_DEJA_PRESENTE"));
		return;
	}
	ligues_select<<cles_ligues[table_ligues->currentRow()];
	maj_ligues();
	QPair<int,int> coords_env_=coords.coords_environnement();
	QPair<int,int> coords_tuile_=coords.coords_tuile();
	TuileGraphique *tuile_g_=grille->tuile(coords_env_.first+coords_tuile_.first,coords_env_.second+coords_tuile_.second);
	tuile_g_->maj_cond_ligue(true);
	grille->repaint();
	//if(cles_ligues.cont
}

void DialogueAccesCarte::supprimer_condition_ligue(){
	if(table_ligues_ajoutees->currentRow()<0||table_ligues_ajoutees->currentRow()>=ligues_select.size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("LIGUE_NON_SELECT"));
		return;
	}
	ligues_select.removeAt(table_ligues_ajoutees->currentRow());
	maj_ligues();
	if(acces_fct_ligues.valeur(coords).isEmpty()){
		QPair<int,int> coords_env_=coords.coords_environnement();
		QPair<int,int> coords_tuile_=coords.coords_tuile();
		TuileGraphique *tuile_g_=grille->tuile(coords_env_.first+coords_tuile_.first,coords_env_.second+coords_tuile_.second);
		tuile_g_->maj_cond_ligue(false);
		grille->repaint();
	}
}

void DialogueAccesCarte::ajouter_condition_acces_coords(){
	if(!acceptable_coords||table_ligues->currentRow()<0||table_ligues->currentRow()>=table_ligues->rowCount()){
		QString err_;
		if(!acceptable_coords){
			err_+=traduire("MAUVAISES_COORDS")+"\n";
		}
		if(table_ligues->currentRow()<0||table_ligues->currentRow()>=table_ligues->rowCount()){
			err_+=traduire("LIGUE_NON_SELECT");
		}
		QMessageBox::critical(this,traduire("ERREUR"),err_);
		return;
	}
	//acces_fct_ligues.ajouter_cle_valeur(coords,table_ligues->currentRow())CONDITION_AJOUTEE
	acces_fct_ligues.ajouter_cle_valeur(coords,ligues_select);
	QMessageBox::information(this,traduire("SUCCES"),traduire("CONDITION_AJOUTEE"));
}

void DialogueAccesCarte::supprimer_condition_acces_coords(){
	if(acces_fct_ligues.cles().contains(coords)){
		acces_fct_ligues.supprimer_cle_valeur(coords);
		//ligues_select.clear()
		QMessageBox::information(this,traduire("SUCCES"),traduire("CONDITION_SUPPRIMEE"));
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_NON_SELECT"));
	}
}



