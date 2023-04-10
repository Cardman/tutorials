#include "ihm/dialogue/dialogueliaisons.h"
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
#include <QFormLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QComboBox>

const HashMap<QString,QStringList> DialogueLiaisons::_elements_ihm_=DialogueLiaisons::init_elements_ihm();

HashMap<QString,QStringList> DialogueLiaisons::init_elements_ihm(){
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

QString DialogueLiaisons::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString DialogueLiaisons::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueLiaisons::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueLiaisons::DialogueLiaisons(int _langue,QWidget* _parent,DialogueLiaisons::TypesLiaisons _type):QDialog(_parent){
	acceptable_coords=false;
	acceptable_coords_dest=false;
	type=_type;
	langue=_langue;
	donnees=qobject_cast<Fenetre*>(_parent)->adr_donnees();
	if(type!=DialogueLiaisons::LIEN_PLATEAU_LIGUE){
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
		cles_lieux_dest=donnees->lieux_c();
		nb_pl_=cles_lieux_dest.size();
		table_lieux_dest=new QTableWidget(nb_pl_,etiquettes_.size());
		table_lieux_dest->setHorizontalHeaderLabels(etiquettes_);
		for(int i=0;i<nb_pl_;i++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText(texte_aff_.valeur(i).first);
			table_lieux_dest->setItem(i,0,element_);
			element_=new QTableWidgetItem();
			element_->setText(traduire(Import::_type_lieux_,texte_aff_.valeur(i).second,langue));
			table_lieux_dest->setItem(i,1,element_);
		}
		connect(table_lieux_dest,SIGNAL(cellClicked(int,int)),this,SLOT(maj_table_dest(int)));
		split_->addWidget(table_lieux_dest);
		cles_plateaux_dest=QList<int>();
		table_plateaux_dest=new QTableWidget(1,1);
		element_=new QTableWidgetItem();
		element_->setText("");
		table_plateaux_dest->setItem(0,0,element_);
		connect(table_plateaux_dest,SIGNAL(cellClicked(int,int)),this,SLOT(maj_grille_dest(int)));
		split_->addWidget(table_plateaux_dest);
		asc_=new QScrollArea();
		grille_dest=new GrilleDialogue();
		connect(grille_dest,SIGNAL(selection(const QPair<QPair<int,int>,QPair<int,int> >&)),this,SLOT(maj_coords_dest(const QPair<QPair<int,int>,QPair<int,int> >&)));
		asc_->setWidget(grille_dest);
		grille_dest->init();
		grille_dest->repaint();
		split_->addWidget(asc_);
		split_c_->addWidget(split_);
		QVBoxLayout *centre_=new QVBoxLayout();
		centre_->addWidget(split_c_);
		if(type==DialogueLiaisons::LIEN_PLATEAU){
			foreach(int l,donnees->lieux_c()){
				Lieu *lieu_=donnees->lieu(l);
				foreach(int p,lieu_->plateaux_c()){
					Plateau *plateau_=lieu_->plateau(p);
					plateau_->aff_noms_images_liens_tmp();
					plateau_->aff_liens_vers_autres_plateau_tmp();
				}
			}
			setWindowTitle(traduire("TITRE_P"));
			QPushButton *lier_=new QPushButton(traduire("LIER_PL"));
			connect(lier_,SIGNAL(clicked()),this,SLOT(lier_plateaux()));
			centre_->addWidget(lier_);
			QPushButton *delier_=new QPushButton(traduire("DELIER_PL"));
			connect(delier_,SIGNAL(clicked()),this,SLOT(delier_plateaux()));
			centre_->addWidget(delier_);
		}else{
			typedef QPair<int,QPair<QPair<int,int>,QPair<int,int> > > OrigineLien;
			foreach(int l,donnees->lieux_c()){
				Lieu *lieu_=donnees->lieu(l);
				lieu_->aff_liens_vers_autres_lieux_tmp();
			}
			setWindowTitle(traduire("TITRE_L"));
			QPushButton *lier_=new QPushButton(traduire("SOUDER_L"));
			connect(lier_,SIGNAL(clicked()),this,SLOT(souder_lieux()));
			centre_->addWidget(lier_);
			QPushButton *delier_=new QPushButton(traduire("DESOUDER_L"));
			connect(delier_,SIGNAL(clicked()),this,SLOT(desouder_lieux()));
			centre_->addWidget(delier_);
		}
		/*coords=_coords_depart
		coords_et=new QLabel(_coords_depart.formater())
		centre_->addWidget(coords_et)*/
		QPushButton *valider_=new QPushButton(traduire("VALIDER"));
		connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
		centre_->addWidget(valider_);
		setLayout(centre_);
	}else{
	//LIEN_PLATEAU_LIGUE
		foreach(int l,donnees->ligues_c()){
			Ligue *ligue_=donnees->ligue(l);
			acces.ajouter_cle_valeur(l,*ligue_->adr_acces());
			origine.ajouter_cle_valeur(l,*ligue_->adr_origine());
			int nb_pl_l_=ligue_->nb_plateaux();
			for(int i=0;i<nb_pl_l_;i++){
				Coordonnees c_;
				*c_.adr_lieu_plateau()=QPair<int,int>(l,i);
				PlateauLigue *plateau_=ligue_->plateau(i);
				*c_.adr_environnement()=plateau_->adr_orig_lien_vers_plateau_suivant()->second;
				*c_.adr_tuile()=plateau_->adr_orig_lien_vers_plateau_suivant()->first;
				QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > orig_dest_;
				orig_dest_.first=*plateau_->adr_orig_lien_vers_plateau_suivant();
				orig_dest_.second=*plateau_->adr_dest_lien_vers_plateau_suivant();
				lien_vers_plateau_suivant.ajouter_cle_valeur(QPair<int,int>(l,i),orig_dest_);
			}
		}
		setWindowTitle(traduire("TITRE_PL"));
		QSplitter *split_c_=new QSplitter();
		QSplitter *split_=new QSplitter(Qt::Vertical);
		cles_lieux=donnees->ligues_c();
		//HashMap<int,QPair<QString,QString> > texte_aff_=donnees->nom_type_lieux()
		int nb_pl_=cles_lieux.size();
		table_lieux=new QTableWidget(nb_pl_,1);
		for(int i=0;i<nb_pl_;i++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText(QString::number(i));
			table_lieux->setItem(i,0,element_);
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
		//DROITE
		split_=new QSplitter(Qt::Vertical);
		QPushButton *maj_acces_=new QPushButton(traduire("EDITER_COORDS_ACCES"));
		connect(maj_acces_,SIGNAL(clicked()),this,SLOT(maj_coords_acces()));
		split_->addWidget(maj_acces_);
		QPushButton *maj_origine_=new QPushButton(traduire("EDITER_ORIGINE_LIGUE"));
		connect(maj_origine_,SIGNAL(clicked()),this,SLOT(maj_coords_origine()));
		split_->addWidget(maj_origine_);
		QPushButton *suppr_acces_=new QPushButton(traduire("SUPPRIMER_COORDS_ACCES"));
		connect(suppr_acces_,SIGNAL(clicked()),this,SLOT(suppr_coords_acces()));
		split_->addWidget(suppr_acces_);
		QPushButton *suppr_origine_=new QPushButton(traduire("SUPPRIMER_ORIGINE_LIGUE"));
		connect(suppr_origine_,SIGNAL(clicked()),this,SLOT(suppr_coords_origine()));
		split_->addWidget(suppr_origine_);
		grille_dest=new GrilleDialogue();
		connect(grille_dest,SIGNAL(selection(const QPair<QPair<int,int>,QPair<int,int> >&)),this,SLOT(maj_coords_dest(const QPair<QPair<int,int>,QPair<int,int> >&)));
		asc_=new QScrollArea();
		asc_->setWidget(grille_dest);
		grille_dest->init();
		grille_dest->repaint();
		split_->addWidget(asc_);
		table_lieux_dest=NULL;
		table_plateaux_dest=NULL;
		split_c_->addWidget(split_);
		QVBoxLayout *centre_=new QVBoxLayout();
		centre_->addWidget(split_c_);
		QPushButton *lier_=new QPushButton(traduire("LIER_PL_L"));
		connect(lier_,SIGNAL(clicked()),this,SLOT(lier_plateaux_ligues()));
		centre_->addWidget(lier_);
		QPushButton *delier_=new QPushButton(traduire("DELIER_PL_L"));
		connect(delier_,SIGNAL(clicked()),this,SLOT(delier_plateaux_ligues()));
		centre_->addWidget(delier_);
		QPushButton *valider_=new QPushButton(traduire("VALIDER"));
		connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
		centre_->addWidget(valider_);
		setLayout(centre_);
	}
	//	enum TypesLiaisons{LIEN_PLATEAU,LIEN_PLATEAU_LIGUE,LIEUX_A_SOUDER}

}

HashMap<QPair<int,int>,QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > > DialogueLiaisons::maj_lien_vers_plateau_suivant()const{
	return lien_vers_plateau_suivant;
}
	;
HashMap<int,Coordonnees> DialogueLiaisons::maj_acces()const{
	return acces;
}

HashMap<int,Coordonnees> DialogueLiaisons::maj_origine()const{
	return origine;
}

void DialogueLiaisons::maj_grille_lien(GrilleDialogue *grille,Donnees *donnees,const Coordonnees& coords){
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


void DialogueLiaisons::souder_lieux(){
	if(!acceptable_coords||!acceptable_coords_dest){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
		return;
	}
	donnees->relier_lieux(coords.lieu(),coords_dest.lieu(),coords.coords_par_rap_lieu(),coords_dest.coords_par_rap_lieu());
	maj_grille_lien(grille,donnees,coords);
	maj_grille_lien(grille_dest,donnees,coords_dest);
	grille->repaint();
	grille_dest->repaint();
	QMessageBox::information(this,traduire("SUCCES"),traduire("LIEUX_SOUDES"));
	//relier_lieux
}

void DialogueLiaisons::desouder_lieux(){
//desouder_lieux_plateau(
	donnees->desouder_lieux_plateau(coords.lieu(),coords_dest.lieu(),coords.plateau(),coords_dest.plateau());
	grille->reinit_liens();
	grille->repaint();
	grille_dest->reinit_liens();
	grille_dest->repaint();
	QMessageBox::information(this,traduire("SUCCES"),traduire("LIEUX_DESSOUDES"));
}

void DialogueLiaisons::lier_plateaux(){
	if(!acceptable_coords||!acceptable_coords_dest){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
		return;
	}
	Plateau *pl_=donnees->lieu(coords.lieu())->plateau(coords.plateau());
	//TODO demander une image pour l'extremite d'origine
	QDialog *dial_=new QDialog(this);
	dial_->setWindowTitle(traduire("TITRE_DIAL"));
	QFormLayout *lay_=new QFormLayout();
	QComboBox *combo_=new QComboBox();
	foreach(QString l,Import::_liens_.cles()){
		combo_->addItem(QPixmap::fromImage(Import::_liens_.valeur(l)),l);
	}
	combo_->setEditable(true);
	lay_->addRow(traduire("LIEN"),combo_);
	QPushButton *bouton_=new QPushButton(traduire("OK"));
	connect(bouton_,SIGNAL(clicked()),dial_,SLOT(accept()));
	QPushButton *bouton_a_=new QPushButton(traduire("ANNULER"));
	connect(bouton_a_,SIGNAL(clicked()),dial_,SLOT(reject()));
	lay_->addRow(bouton_,bouton_a_);
	dial_->setLayout(lay_);
	dial_->exec();
	bool accept_=dial_->result()==QDialog::Accepted;
	QString texte_=combo_->currentText();
	delete dial_;
	dial_=NULL;
	if(!accept_){
		return;
	}
	if(!Import::_liens_.cles().contains(texte_)){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("CHOIX_INVALIDE_PL"));
		return;
	}
	pl_->ajouter_image_origine_liaison(coords.coords_par_rap_plateau(),texte_);
	pl_->ajouter_dest_autre_plateau(coords.coords_par_rap_plateau(),coords_dest);
	QPair<int,int> env_=coords.coords_environnement();
	QPair<int,int> tuile_=coords.coords_tuile();
	TuileGraphique *tuile_g_=grille->tuile(env_.first+tuile_.first,env_.second+tuile_.second);
	tuile_g_->maj_lien(QPair<QImage,bool>(Import::_liens_.valeur(texte_),true));
	grille->repaint();
	QMessageBox::information(this,traduire("SUCCES"),traduire("PLATEAUX_LIES"));
}

void DialogueLiaisons::delier_plateaux(){
	Plateau *pl_=donnees->lieu(coords.lieu())->plateau(coords.plateau());
	QList<QPair<QPair<int,int>,QPair<int,int> > > liaisons_=pl_->liaisons_vers_autres_plateaux();
	if(!liaisons_.contains(coords.coords_par_rap_plateau())){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("CHOIX_INVALIDE_PL"));
		return;
	}
	pl_->supprimer_dest_autre_plateau_tmp(coords.coords_par_rap_plateau());
	QPair<int,int> env_=coords.coords_environnement();
	QPair<int,int> tuile_=coords.coords_tuile();
	TuileGraphique *tuile_g_=grille->tuile(env_.first+tuile_.first,env_.second+tuile_.second);
	tuile_g_->maj_lien(QPair<QImage,bool>(QImage(),false));
	grille->repaint();
	QMessageBox::information(this,traduire("SUCCES"),traduire("PLATEAUX_DELIES"));
}

void DialogueLiaisons::maj_table(int _lieu){
	acceptable_coords=false;
	if(type!=DialogueLiaisons::LIEN_PLATEAU_LIGUE){
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
	}else{
		coords.adr_lieu_plateau()->first=cles_lieux[_lieu];
		//coords_et->setText(coords.formater())
		cles_plateaux.clear();
		int nb_pl_l_=donnees->ligue(cles_lieux[_lieu])->nb_plateaux();
		for(int i=0;i<nb_pl_l_;i++){
			cles_plateaux<<i;
		}
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
}

void DialogueLiaisons::maj_table_dest(int _lieu){
	acceptable_coords_dest=false;
	coords_dest.adr_lieu_plateau()->first=cles_lieux_dest[_lieu];
	//coords_et->setText(coords.formater())
	cles_plateaux_dest=donnees->lieu(cles_lieux_dest[_lieu])->plateaux_c();
	int nb_pl_=cles_plateaux_dest.size();
	int nb_l_=table_plateaux_dest->rowCount();
	if(nb_l_<nb_pl_){
		table_plateaux_dest->setRowCount(nb_pl_);
		for(int i=nb_l_;i<nb_pl_;i++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText(QString::number(i));
			table_plateaux_dest->setItem(i,0,element_);
		}
	}
	for(int i=0;i<nb_pl_;i++){
		table_plateaux_dest->item(i,0)->setText(QString::number(i));
	}
	for(int i=nb_pl_;i<nb_l_;i++){
		table_plateaux_dest->item(i,0)->setText("");
	}
	grille_dest->table_rase();
}

void DialogueLiaisons::maj_grille(int _plateau){
	grille->table_rase();
	acceptable_coords=false;
	if(type!=DialogueLiaisons::LIEN_PLATEAU_LIGUE){
		if(_plateau>=cles_plateaux.size()){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
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
	}else{
		if(_plateau>=cles_plateaux.size()){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
			return;
		}
		coords.adr_lieu_plateau()->second=cles_plateaux[_plateau];
		//coords_et->setText(coords.formater())
		PlateauLigue *pl_=donnees->ligue(coords.lieu())->plateau(cles_plateaux[_plateau]);
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
					tuile_g_->maj_coords(QPair<int,int>(i,j));
					Tuile *tuile_=env_->tuile(QPair<int,int>(i,j));
					tuile_g_->maj_image(Import::_tuiles_importees_.valeur(*tuile_->adr_nom_image()));
				}
			}
		}
		Ligue *ligue_=donnees->ligue(coords.lieu());
		QPair<int,int> coords_=*pl_->adr_coords_dresseur();
		if(coords_.first<grille->nb_colonnes()&&coords_.second<grille->nb_lignes()){
			TuileGraphique *tuile_g_=grille->tuile(coords_.first,coords_.second);
			DresseurLigue *dr_=pl_->adr_dresseur_ligue();
			if(Import::_dresseurs_micros_.cles().contains(*dr_->adr_nom_miniature())){
				tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*dr_->adr_nom_miniature()),*dr_->adr_orientation()));
			}
		}
		bool suppr_=false;
		QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > *orig_dest_=lien_vers_plateau_suivant.valeur(*coords.adr_lieu_plateau(),suppr_);
		if(coords.plateau()>0){
			QPair<int,int> cle_=QPair<int,int>(coords.lieu(),coords.plateau()-1);
			grille->maj_liens_plateau_ligue(lien_vers_plateau_suivant.valeur(cle_).second,orig_dest_->first);
		}else{
			Coordonnees *acces_=ligue_->adr_acces();
			if(acces_->plateau()>=0){
				grille->maj_liens_plateau_ligue(acces_->coords_par_rap_plateau(),orig_dest_->first);
			}else{
				grille->maj_liens_plateau_ligue(NULL,&orig_dest_->first);
			}
		}	
		/*if(_plateau>0){
			//
			grille->maj_liens_plateau_ligue(lien_vers_plateau_suivant.valeur(QPair<int,int>(coords.lieu(),_plateau-1)).first,lien_vers_plateau_suivant.valeur(QPair<int,int>(coords.lieu(),_plateau)).second)
			//grille->maj_liens_plateau_ligue(ligue_->plateau(_plateau-1)->adr_orig_lien_vers_plateau_suivant(),pl_->adr_dest_lien_vers_plateau_suivant())
		}else{
			Coordonnees acces_=acces.valeur(coords.lieu())
			if(acces_.plateau()>=0){
				grille->maj_liens_plateau_ligue(acces_.coords_par_rap_plateau(),lien_vers_plateau_suivant.valeur(QPair<int,int>(coords.lieu(),_plateau)).second)
			}else{
				grille->maj_liens_plateau_ligue(NULL,lien_vers_plateau_suivant.valeur(QPair<int,int>(coords.lieu(),_plateau)).second)
			}
			
			Coordonnees *acces_=ligue_->adr_acces()
			if(acces_->plateau()>=0){
				grille->maj_liens_plateau_ligue(acces_->coords_par_rap_plateau(),pl_->adr_dest_lien_vers_plateau_suivant())
			}else{
				grille->maj_liens_plateau_ligue(NULL,pl_->adr_dest_lien_vers_plateau_suivant())
			}
		}*/
		if(_plateau<cles_plateaux.size()-1){
			maj_grille_dest(_plateau+1);
		}else{
			grille_dest->table_rase();
		}
	}
	grille->repaint();
}

void DialogueLiaisons::maj_grille_dest(int _plateau){
	grille_dest->table_rase();
	if(type!=DialogueLiaisons::LIEN_PLATEAU_LIGUE){
		if(_plateau>=cles_plateaux_dest.size()){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
			return;
		}
		coords_dest.adr_lieu_plateau()->second=cles_plateaux_dest[_plateau];
		//coords_et->setText(coords.formater())
		Plateau *pl_=donnees->lieu(coords_dest.lieu())->plateau(cles_plateaux_dest[_plateau]);
		QPair<int,int> dims_=pl_->dimensions();
		if(grille_dest->nb_lignes()<dims_.second){
			grille_dest->ajouter_lignes(dims_.second-grille_dest->nb_lignes());
		}
		if(grille_dest->nb_colonnes()<dims_.first){
			grille_dest->ajouter_colonnes(dims_.first-grille_dest->nb_colonnes());
		}
		typedef QPair<QPair<int,int>,QPair<int,int> > OrigineLien;
		foreach(OrigineLien o,pl_->liaisons_vers_autres_plateaux()){
			TuileGraphique *tuile_g_=grille_dest->tuile(o.second.first+o.first.first,o.second.second+o.first.second);
			tuile_g_->maj_lien(QPair<QImage,bool>(Import::_liens_.valeur(pl_->image_origine_liaison(o)),true));
		}
		typedef QPair<int,int> Origine;
		foreach(Origine o,pl_->coins_gauche()){
			bool suppr_=false;
			Environnement *env_=pl_->environnement(o,suppr_);
			QPair<int,int> dims_env_=env_->dimensions();
			for(int i=0;i<dims_env_.first;i++){
				for(int j=0;j<dims_env_.second;j++){
					TuileGraphique *tuile_g_=grille_dest->tuile(i+o.first,j+o.second);
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
		maj_grille_lien(grille_dest,donnees,coords_dest);
	}else{
		if(_plateau>=cles_plateaux.size()){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
			return;
		}
		coords_dest.adr_lieu_plateau()->second=cles_plateaux[_plateau];
		//coords_et->setText(coords.formater())
		PlateauLigue *pl_=donnees->ligue(coords.lieu())->plateau(cles_plateaux[_plateau]);
		QPair<int,int> dims_=pl_->dimensions();
		if(grille_dest->nb_lignes()<dims_.second){
			grille_dest->ajouter_lignes(dims_.second-grille_dest->nb_lignes());
		}
		if(grille_dest->nb_colonnes()<dims_.first){
			grille_dest->ajouter_colonnes(dims_.first-grille_dest->nb_colonnes());
		}
		typedef QPair<int,int> Origine;
		foreach(Origine o,pl_->coins_gauche()){
			bool suppr_=false;
			EnvironnementLigue *env_=pl_->environnement(o,suppr_);
			QPair<int,int> dims_env_=env_->dimensions();
			for(int i=0;i<dims_env_.first;i++){
				for(int j=0;j<dims_env_.second;j++){
					TuileGraphique *tuile_g_=grille_dest->tuile(i+o.first,j+o.second);
					tuile_g_->maj_coords(QPair<int,int>(i,j));
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
		//if(coords.plateau()+1<cles_plateaux.size()){
		//QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > *orig_dest_=lien_vers_plateau_suivant.valeur(*coords.adr_lieu_plateau(),suppr_)
		QPair<int,int> cle_=QPair<int,int>(coords.lieu(),coords.plateau()+1);
		grille_dest->maj_liens_plateau_ligue(lien_vers_plateau_suivant.valeur(*coords.adr_lieu_plateau()).second,lien_vers_plateau_suivant.valeur(cle_).first);
		//}
		//grille_dest->maj_liens_plateau_ligue(lien_vers_plateau_suivant.valeur(QPair<int,int>(coords.lieu(),_plateau-1)).first,lien_vers_plateau_suivant.valeur(QPair<int,int>(coords.lieu(),_plateau)).second)
		//grille_dest->maj_liens_plateau_ligue(donnees->ligue(coords.lieu())->plateau(_plateau-1)->adr_orig_lien_vers_plateau_suivant(),pl_->adr_dest_lien_vers_plateau_suivant())
	}
	grille_dest->repaint();
}

void DialogueLiaisons::maj_coords(const QPair<QPair<int,int>,QPair<int,int> >& _coords){
	if(type!=DialogueLiaisons::LIEN_PLATEAU_LIGUE){
		if(!donnees->lieu(coords.lieu())->plateau(coords.plateau())->coins_gauche().contains(_coords.first)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
			return;
		}
		acceptable_coords=true;
		*coords.adr_environnement()=_coords.first;
		*coords.adr_tuile()=_coords.second;
		//coords_et->setText(coords.formater())
	}else{
		if(!donnees->ligue(coords.lieu())->plateau(coords.plateau())->coins_gauche().contains(_coords.first)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
			return;
		}
		acceptable_coords=true;
		*coords.adr_environnement()=_coords.first;
		*coords.adr_tuile()=_coords.second;
	}
}

void DialogueLiaisons::maj_coords_dest(const QPair<QPair<int,int>,QPair<int,int> >& _coords){
	if(type!=DialogueLiaisons::LIEN_PLATEAU_LIGUE){
		if(!donnees->lieu(coords_dest.lieu())->plateau(coords_dest.plateau())->coins_gauche().contains(_coords.first)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
			return;
		}
		acceptable_coords_dest=true;
		*coords_dest.adr_environnement()=_coords.first;
		*coords_dest.adr_tuile()=_coords.second;
		//coords_et->setText(coords.formater())
	}else{
		if(!donnees->ligue(coords.lieu())->plateau(coords.plateau())->coins_gauche().contains(_coords.first)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
			return;
		}
		acceptable_coords_dest=true;
		*coords_dest.adr_environnement()=_coords.first;
		*coords_dest.adr_tuile()=_coords.second;
	}
}


void DialogueLiaisons::lier_plateaux_ligues(){
	if(!acceptable_coords||!acceptable_coords_dest){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
		return;
	}
	bool suppr_=false;
	QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > *orig_dest_=lien_vers_plateau_suivant.valeur(*coords.adr_lieu_plateau(),suppr_);
	orig_dest_->first=coords.coords_par_rap_plateau();
	if(coords.plateau()+1<cles_plateaux.size()){
		orig_dest_->second=coords_dest.coords_par_rap_plateau();
	}
	/*Ligue *ligue_=donnees->ligue(coords.lieu())
	PlateauLigue *pl_=ligue_->plateau(coords.plateau())
	*pl_->adr_orig_lien_vers_plateau_suivant()=coords.coords_par_rap_plateau()
	if(coords.plateau()+1<cles_plateaux.size()){
		*pl_->adr_dest_lien_vers_plateau_suivant()=coords_dest.coords_par_rap_plateau()
	}
	orig_dest_->second
	lien_vers_plateau_suivant.valeur(cle_)
	*/
	//QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > lien_=
	if(coords.plateau()>0){
		QPair<int,int> cle_=QPair<int,int>(coords.lieu(),coords.plateau()-1);
		grille->maj_liens_plateau_ligue(lien_vers_plateau_suivant.valeur(cle_).second,orig_dest_->first);
	}else{
		Coordonnees acces_=acces.valeur(coords.lieu());
		if(acces_.plateau()>=0){
			grille->maj_liens_plateau_ligue(acces_.coords_par_rap_plateau(),orig_dest_->first);
		}else{
			grille->maj_liens_plateau_ligue(NULL,&orig_dest_->first);
		}
	}
	if(coords.plateau()+1<cles_plateaux.size()){
		QPair<int,int> cle_=QPair<int,int>(coords.lieu(),coords.plateau()+1);
		grille_dest->maj_liens_plateau_ligue(orig_dest_->second,lien_vers_plateau_suivant.valeur(cle_).first);
	}
	grille->repaint();
	grille_dest->repaint();
	QMessageBox::information(this,traduire("SUCCES"),traduire("PLATEAUX_LIGUE_LIES"));
}

void DialogueLiaisons::delier_plateaux_ligues(){
	bool suppr_=false;
	int coords_inval_=Tuile::_coords_invalide_;
	QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > *orig_dest_=lien_vers_plateau_suivant.valeur(*coords.adr_lieu_plateau(),suppr_);
	orig_dest_->first=QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(coords_inval_,coords_inval_),QPair<int,int>(coords_inval_,coords_inval_));
	orig_dest_->second=QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(coords_inval_,coords_inval_),QPair<int,int>(coords_inval_,coords_inval_));
	/*PlateauLigue *pl_=donnees->ligue(coords.lieu())->plateau(coords.plateau())
	*pl_->adr_orig_lien_vers_plateau_suivant()=QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(coords_inval_,coords_inval_),QPair<int,int>(coords_inval_,coords_inval_))
	*pl_->adr_dest_lien_vers_plateau_suivant()=QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(coords_inval_,coords_inval_),QPair<int,int>(coords_inval_,coords_inval_))*/
	QMessageBox::information(this,traduire("SUCCES"),traduire("PLATEAUX_LIGUE_DELIES"));
}

void DialogueLiaisons::maj_coords_acces(){
	if(!acceptable_coords){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_INVALIDE"));
		return;
	}
	if(coords.plateau()>0){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PLATEAU_LIGUE_NON_PREMIER"));
		return;
	}
	acces.ajouter_cle_valeur(coords.lieu(),coords);
	/*Ligue *ligue_=donnees->ligue(coords.lieu())
	*ligue_->adr_acces()=coords*/
	QPair<int,int> cle_=QPair<int,int>(coords.lieu(),0);
	grille->maj_liens_plateau_ligue(acces.valeur(coords.lieu()).coords_par_rap_plateau(),lien_vers_plateau_suivant.valeur(cle_).first);
	QMessageBox::information(this,traduire("SUCCES"),traduire("COORDS_ACCES_LIES"));
}

void DialogueLiaisons::maj_coords_origine(){
	DialogueCoords *dial_=new DialogueCoords(langue,*donnees->ligue(coords.lieu())->adr_origine(),donnees,this,DialogueCoords::LIAISON);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_&&dial_->acceptable()){
		//*donnees->ligue(coords.lieu())->adr_origine()=dial_->coordonnees()
		origine.ajouter_cle_valeur(coords.lieu(),dial_->coordonnees());
	}
	delete dial_;
	dial_=NULL;
}

void DialogueLiaisons::suppr_coords_acces(){
	if(donnees->ligues_c().contains(coords.lieu())){
		//*donnees->ligue(coords.lieu())->adr_acces()=Coordonnees()
		acces.ajouter_cle_valeur(coords.lieu(),Coordonnees());
		QMessageBox::information(this,traduire("SUCCES"),traduire("COORDS_ACCES_SUPPR"));
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("LIGUE_NON_SELECT"));
	}
}

void DialogueLiaisons::suppr_coords_origine(){
	if(donnees->ligues_c().contains(coords.lieu())){
		//*donnees->ligue(coords.lieu())->adr_origine()=Coordonnees()
		origine.ajouter_cle_valeur(coords.lieu(),Coordonnees());
		QMessageBox::information(this,traduire("SUCCES"),traduire("COORDS_ORIGINE_SUPPR"));
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("LIGUE_NON_SELECT"));
	}
}


