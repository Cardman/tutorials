#include "ihm/fenetre.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include "pseudo_ihm/tuilegraphique.h"
#include "ihm/menus/menu.h"
#include "ihm/menus/action.h"
#include "ihm/dialogue/dialoguenlieu.h"
#include "ihm/dialogue/dialoguenenvir.h"
#include "ihm/panneau/panneauediteurenv.h"
#include "ihm/grilles/grille.h"
#include "ihm/dialogue/dialoguegrille.h"
#include "ihm/dialogue/dialogueaccescarte.h"
#include "ihm/dialogue/dialogueaccesligue.h"
#include "ihm/dialogue/dialoguelargeur.h"
#include "ihm/dialogue/dialoguehauteur.h"
#include "ihm/dialogue/dialoguefichiers.h"
#include "ihm/dialogue/dialogueselectplateau.h"
#include "ihm/dialogue/dialogueselectlieu.h"
#include "ihm/dialogue/dialogueselectlieuligue.h"
#include "ihm/dialogue/dialogueselectligue.h"
#include "ihm/dialogue/dialogueliaisons.h"
#include "ihm/dialogue/dialogueediteurmap.h"
#include "ihm/dialogue/dialoguelieuxvols.h"
#include "ihm/panneau/panneauediteurenv.h"
#include "ihm/dialogue/dialoguepkcombat.h"
#include "ihm/dialogue/dialogueobjet.h"
#include "ihm/dialogue/dialoguedresseur.h"
#include "ihm/dialogue/dialoguepersonnage.h"
#include "ihm/dialogue/dialogueequipe.h"
#include "ihm/dialogue/dialoguecoords.h"
#include "ihm/dialogue/dialogueaide.h"
#include "ihm/dialogue/dialoguesql.h"
#include "base_donnees/initbdd.h"
#include "ihm/dialogue/dialoguebasedonnees.h"
#include "ihm/panneau/panneaudresseurligue.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/import.h"
#include "serialisable/pokemon/pokemondresse.h"
#include <QDir>
#include <QString>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QSplitter>
#include <QScrollArea>
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>
#include <QSqlQuery>
#include <QProgressBar>

Lieu *Fenetre::_lieu_precedent_=NULL;

Lieu *Fenetre::_lieu_en_cours_=NULL;

Ligue *Fenetre::_ligue_en_cours_=NULL;

Plateau *Fenetre::_plateau_en_cours_=NULL;

PlateauLigue *Fenetre::_plateau_ligue_en_cours_=NULL;

const HashMap<QString,QStringList> Fenetre::_elements_ihm_=Fenetre::init_elements_ihm();

HashMap<QString,QStringList> Fenetre::init_elements_ihm(){
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

QString Fenetre::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

Fenetre::Fenetre(int _langue){
	langue=_langue;
	ind_lieu_tmp=0;
	ind_lieu=0;
	ind_plateau=0;
	choix_env=SELECTION;
	coordonnees_act.first=QPair<int,int>(Tuile::_coords_invalide_,Tuile::_coords_invalide_);
	coordonnees_act.second=QPair<int,int>(Tuile::_coords_invalide_,Tuile::_coords_invalide_);
	rep_travail=QApplication::applicationDirPath();
	rep_export=QApplication::applicationDirPath();
	nom_fichier_flux="";
	//nom_fichier_export=""

	QMenuBar *barre_menus_=new QMenuBar();
	Menu *menu_;
	Action *action_;
	menu_=new Menu("FICHIER",langue);//TODO a changer en fonction de l'import
	action_=new Action("\tNOUVELLES_DONNEES",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(nouvelles_donnees()));
	menu_->addAction(action_);
	action_=new Action("\tCHARGER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(charger()));
	menu_->addAction(action_);
	action_=new Action("\tCHARGER_RAPIDEMENT",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(charger_rapidement()));
	menu_->addAction(action_);
	action_=new Action("\tSAUVEGARDER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(sauvegarder_rapidement()));
	menu_->addAction(action_);
	action_=new Action("\tSAUVEGARDER_SOUS",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(sauvegarder()));
	menu_->addAction(action_);
	action_=new Action("\tVALIDER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(valider()));
	menu_->addAction(action_);
	action_=new Action("\tEXPORTER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(exporter()));
	menu_->addAction(action_);
	action_=new Action("\tQUITTER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(close()));
	menu_->addAction(action_);
	barre_menus_->addMenu(menu_);

	menu_=new Menu("GRILLE",langue);
	action_=new Action("\tAJOUTER_LIGNE_HAUT",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(ajouter_ligne_ht_plateau()));
	menu_->addAction(action_);
	action_=new Action("\tAJOUTER_LIGNE_BAS",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(ajouter_ligne_bas_plateau()));
	menu_->addAction(action_);
	action_=new Action("\tAJOUTER_COLONNE_GAUCHE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(ajouter_col_gauche_plateau()));
	menu_->addAction(action_);
	action_=new Action("\tAJOUTER_COLONNE_DROITE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(ajouter_col_droite_plateau()));
	menu_->addAction(action_);
	action_=new Action("\tAJOUTER_LIGNES_HAUT",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(ajouter_lignes_ht_plateau()));
	menu_->addAction(action_);
	action_=new Action("\tAJOUTER_LIGNES_BAS",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(ajouter_lignes_bas_plateau()));
	menu_->addAction(action_);
	action_=new Action("\tAJOUTER_COLONNES_GAUCHE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(ajouter_cols_gauche_plateau()));
	menu_->addAction(action_);
	action_=new Action("\tAJOUTER_COLONNES_DROITE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(ajouter_cols_droite_plateau()));
	menu_->addAction(action_);
	barre_menus_->addMenu(menu_);

	menu_=new Menu("LIEU",langue);//TODO ajouter une fonctionnalite qui cree un lieu et le selectionne
	action_=new Action("\tNOUVEAU",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(nouveau_lieu()));
	menu_->addAction(action_);
	action_=new Action("\tNOUVEAU_SELECT",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(nouveau_lieu_edite()));
	menu_->addAction(action_);
	action_=new Action("\tMODIFIER_NOM_TYPE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(maj_nom_type_lieu()));
	menu_->addAction(action_);
	action_=new Action("\tCHOISIR",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(selection_lieu()));
	menu_->addAction(action_);
	action_=new Action("\tSUPPRIMER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(suppression_lieu()));
	menu_->addAction(action_);
	barre_menus_->addMenu(menu_);

	menu_=new Menu("PLATEAU",langue);
	action_=new Action("\tNOUVEAU",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(inserer_plateau()));
	menu_->addAction(action_);
	action_=new Action("\tCHOISIR",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(select_plateau()));
	menu_->addAction(action_);
	action_=new Action("\tSUPPRIMER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(suppression_plateau()));
	menu_->addAction(action_);
	barre_menus_->addMenu(menu_);

	menu_=new Menu("ENVIRONNEMENT",langue);
	action_=new Action("\tNOUVEAU",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(nv_env()));
	menu_->addAction(action_);
	action_=new Action("\tDEPLACER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(deplacer_env()));
	menu_->addAction(action_);
	action_=new Action("\tSELECTION",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(selection_env()));
	menu_->addAction(action_);
	action_=new Action("\tSUPPRIMER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(supprimer_env()));
	menu_->addAction(action_);
	action_=new Action("\tMODIFIER_HAUTEUR",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(modifier_hauteur_env()));
	menu_->addAction(action_);
	action_=new Action("\tINSERER_LIGNE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(insert_ligne_env()));
	menu_->addAction(action_);
	action_=new Action("\tINSERER_SUPPRIMER_LIGNES",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(insert_supprimer_lignes_env()));
	menu_->addAction(action_);
	action_=new Action("\tSUPPRIMER_LIGNE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(supprimer_ligne_env()));
	menu_->addAction(action_);
	action_=new Action("\tMODIFIER_LARGEUR",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(modifier_largeur_env()));
	menu_->addAction(action_);
	action_=new Action("\tINSERER_COLONNE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(insert_colonne_env()));
	menu_->addAction(action_);
	action_=new Action("\tINSERER_SUPPRIMER_COLONNES",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(insert_supprimer_colonnes_env()));
	menu_->addAction(action_);
	action_=new Action("\tSUPPRIMER_COLONNE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(supprimer_colonne_env()));
	menu_->addAction(action_);
	barre_menus_->addMenu(menu_);

	menu_=new Menu("LIGUE",langue);//TODO ajouter une fonctionnalite qui cree un lieu et le selectionne
	action_=new Action("\tNOUVEAU",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(nouvelle_ligue()));
	/**
	Crée une ligue puis un plateau de ligue en faisant table rase et en remplaçant éventuellement un panneau a droite
	*/
	menu_->addAction(action_);
	action_=new Action("\tCHOISIR",langue);
	//Comme pour un lieu
	connect(action_,SIGNAL(triggered()),this,SLOT(selection_ligue()));
	menu_->addAction(action_);
	action_=new Action("\tSUPPRIMER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(suppression_ligue()));
	menu_->addAction(action_);
	barre_menus_->addMenu(menu_);

	/*menu_=new Menu("PLATEAU_LIGUE",langue)
	action_=new Action("\tNOUVEAU",langue)
	connect(action_,SIGNAL(triggered()),this,SLOT(nouveau_plateau_ligue()))
	Demande éventuellement un indice d'insertion avant une autre ligue
	menu_->addAction(action_)
	action_=new Action("\tCHOISIR",langue)
	connect(action_,SIGNAL(triggered()),this,SLOT(select_plateau_ligue()))
	menu_->addAction(action_)
	//INSERER
	action_=new Action("\tSUPPRIMER",langue)
	connect(action_,SIGNAL(triggered()),this,SLOT(suppression_plateau_ligue()))
	menu_->addAction(action_)
	barre_menus_->addMenu(menu_)*/

	menu_=new Menu("LIENS",langue);
	action_=new Action("\tINSERER_LIENS_ENTRE_PLATEAUX",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(lier_plateaux()));
	/**Demande éventuellement un indice d'insertion avant une autre ligue*/
	menu_->addAction(action_);
	action_=new Action("\tSOUDER_LIEUX_COTE_COTE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(souder_lieux()));
	menu_->addAction(action_);
	action_=new Action("\tLIAISONS_LIGUE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(lier_plateaux_ligue()));
	menu_->addAction(action_);
	action_=new Action("\tAJOUT_SUPPR_COND_LIGUE",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(ajouter_supprimer_condition_ligue()));
	menu_->addAction(action_);
	action_=new Action("\tAJOUT_SUPPR_COND_CHAMPIONS",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(ajouter_supprimer_condition_champions()));
	menu_->addAction(action_);
	barre_menus_->addMenu(menu_);

	menu_=new Menu("MAP",langue);
	action_=new Action("\tEDITER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(editer_map()));
	menu_->addAction(action_);
	action_=new Action("\tLIER",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(lier_map()));
	menu_->addAction(action_);
	barre_menus_->addMenu(menu_);

	menu_=new Menu("ELEMENTS_DEPART",langue);
	action_=new Action("\tCOORDONNEES",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(editer_coords_depart()));
	/**Demande éventuellement un indice d'insertion avant une autre ligue*/
	menu_->addAction(action_);
	action_=new Action("\tPOKEMON",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(editer_pk_depart()));
	menu_->addAction(action_);
	action_=new Action("\tNB_MAX_ATTAQUES",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(changer_nb_max_attaques()));
	menu_->addAction(action_);
	barre_menus_->addMenu(menu_);

	menu_=new Menu("AIDE",langue);
	action_=new Action("\tDONNEES",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(voir_donnees()));
	/**Demande éventuellement un indice d'insertion avant une autre ligue*/
	menu_->addAction(action_);
	action_=new Action("\tUTILISATION",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(utilisation_logiciel()));
	menu_->addAction(action_);
	action_=new Action("\tSQL",langue);
	connect(action_,SIGNAL(triggered()),this,SLOT(base_de_donnees()));
	menu_->addAction(action_);
	barre_menus_->addMenu(menu_);

	setMenuBar(barre_menus_);
	et_stat=new QLabel("");
	QStatusBar *status_=new QStatusBar();
	status_->addPermanentWidget(et_stat);
	setStatusBar(status_);
	QSplitter *split_=new QSplitter();
	grille=new Grille();
	connect(grille,SIGNAL(selection(const QPair<QPair<int,int>,QPair<int,int> >&)),this,SLOT(selection_coords(const QPair<QPair<int,int>,QPair<int,int> >&)));
	QScrollArea *conteneur_=new QScrollArea();
	conteneur_->setWidget(grille);
	split_->addWidget(conteneur_);
	;
	panneau_editeur_env=new PanneauEditerEnv(langue,this);
	connect(panneau_editeur_env,SIGNAL(image_tuile_changee(const QImage&)),this,SLOT(maj_image_tuile(const QImage&)));
	ascenseur_panneau=new QScrollArea();
	ascenseur_panneau->setWidget(panneau_editeur_env);
	split_->addWidget(ascenseur_panneau);
	;
	setCentralWidget(split_);
	panneau_editeur_ligue=new PanneauDresseurLigue(langue,this);
	connect(panneau_editeur_ligue,SIGNAL(image_tuile_changee(const QImage&)),this,SLOT(maj_image_tuile(const QImage&)));
	panneau_editeur_ligue->hide();
	QStringList pos_inv_=Import::constante("DEF_COIN_RECTANGLE_INVALIDE_FENETRE").split(",");
	rectangle_nv_env.first=QPair<int,int>(pos_inv_[0].toInt(),pos_inv_[1].toInt());
	QStringList dims_inv_=Import::constante("RECTANGLE_INVALIDE_FENETRE").split(",");
	rectangle_nv_env.second=QPair<int,int>(dims_inv_[0].toInt(),dims_inv_[1].toInt());
	//setMinimumSize(400,400)
	QStringList dims_=Import::constante("DIMENSIONS_FENETRE").split(",");
	setMinimumSize(dims_[0].toInt(),dims_[1].toInt());
	setWindowTitle(traduire("TITRE"));
	progression=NULL;
	init_bdd_th=NULL;
}

void Fenetre::init_bdd(){
	qulonglong avancement_=Import::_table_types_base_.total();
	avancement_+=Import::_attaques_.total();
	avancement_+=Import::_pokedex_.total();
	avancement_+=Import::_cs_.total();
	avancement_+=Import::_ct_.total();
	foreach(QString n,Import::_pokedex_.cles()){
		FichePokemon *f_pk_=Import::_pokedex_.valeur(n);
		avancement_+=f_pk_->evos().total();
		avancement_+=f_pk_->atts().size();
		avancement_+=f_pk_->typs().size();
		avancement_+=f_pk_->capac().size();
		avancement_+=f_pk_->ct().size();
		avancement_+=f_pk_->cs().size();
		avancement_+=f_pk_->mt().size();
	}
	progression=new QProgressBar(0);
	progression->setWindowTitle(traduire("CHARGEMENT_BDD"));
	progression->setRange(0,avancement_);
	progression->setValue(0);
	QPoint pt_=pos();
	pt_+=QPoint(width(),height());
	QString coords_=QString::number(pt_.x())+","+QString::number(pt_.y())+";";
	coords_+=QString::number(pos().x())+","+QString::number(pos().y());
	Utilitaire::ecrire_fichier("coords.txt",coords_);
	progression->move((pt_+pos())/2);
	init_bdd_th=new InitBDD(langue);
	connect(init_bdd_th,SIGNAL(nv_avanc(int)),progression,SLOT(setValue(int)));
	connect(init_bdd_th,SIGNAL(finished()),this,SLOT(finir_bdd()));
	progression->show();
	init_bdd_th->start();
	//finir_bdd
}

void Fenetre::finir_bdd(){
	progression->hide();
	progression->close();
	delete progression;
	progression=NULL;
	delete init_bdd_th;
	init_bdd_th=NULL;
	//finir_bdd
}

void Fenetre::nouvelles_donnees(){
	if(_plateau_en_cours_!=NULL||_plateau_ligue_en_cours_!=NULL){
		int rep_=QMessageBox::question(this,traduire("NOUVELLES_DONNEES"),traduire("CONTINUER_INT"),QMessageBox::Yes|QMessageBox::No);
		if(rep_==QMessageBox::No){
			return;
		}
	}
	//Demande s'il faut affecter le plateau ou non (oui,non,annuler)
	_plateau_en_cours_=NULL;
	_plateau_ligue_en_cours_=NULL;
	_lieu_en_cours_=NULL;
	_ligue_en_cours_=NULL;
	grille->table_rase();
	donnees=Donnees();
	PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
	anciennes_donnees=Donnees();
	nouveau_lieu();
	//Demande d'un lieu puis d'un plateau
}

Donnees *Fenetre::adr_donnees(){
	return &donnees;
}

Donnees Fenetre::donnees_actuelles()const{
	return donnees;
}

bool Fenetre::nouveau_lieu(){
	DialogueNLieu *dialogue_=new DialogueNLieu(langue,this);
	dialogue_->exec();
	bool accepter_=dialogue_->result()==QDialog::Accepted;
	if(accepter_){
		if(_ligue_en_cours_!=NULL){
			_plateau_ligue_en_cours_=NULL;
			_ligue_en_cours_=NULL;
			ascenseur_panneau->takeWidget();
			panneau_editeur_env->show();
			ascenseur_panneau->setWidget(panneau_editeur_env);
			grille->table_rase();
			//TODO
		}
		QList<int> lieux_=donnees.lieux_c();
		if(lieux_.isEmpty()){
			donnees.ajouter_lieu(0,dialogue_->nv_lieu());
			ind_lieu=0;
			if(grille->nb_lignes()==0){
				grille->init();
			}
			Lieu *lieu_=donnees.lieu(ind_lieu);
			_lieu_en_cours_=lieu_;
			ind_plateau=0;
			lieu_->ajout_plateau(ind_plateau,Plateau());
			_plateau_en_cours_=lieu_->plateau(ind_plateau);
		}else{
			Utilitaire::trier<int>(lieux_,true);
			int ind_=lieux_[0];
			if(ind_>0){
				donnees.ajouter_lieu(0,dialogue_->nv_lieu());
				ind_lieu=0;
			}else{
				for(int i=1;i<lieux_.size();i++){
					if(lieux_[i]-1!=lieux_[i-1]){
						ind_=lieux_[i-1]+1;
						break;
					}
				}
				if(lieux_.last()==lieux_.size()-1){
					ind_=lieux_.size();
				}
				donnees.ajouter_lieu(ind_,dialogue_->nv_lieu());
				ind_lieu=ind_;
			}
			Lieu *lieu_=donnees.lieu(ind_lieu);
			ind_plateau=0;
			lieu_->ajout_plateau(ind_plateau,Plateau());
		}
	}
	delete dialogue_;
	dialogue_=NULL;
	return accepter_;
}

void Fenetre::nouveau_lieu_edite(){
	DialogueNLieu *dialogue_=new DialogueNLieu(langue,this);
	dialogue_->exec();
	bool accepter_=dialogue_->result()==QDialog::Accepted;
	if(accepter_){
		QList<int> lieux_=donnees.lieux_c();
		PanneauEditerEnv::_environnement_en_cours_=NULL;
		PanneauEditerEnv::_tuile_en_cours_=NULL;
		_plateau_ligue_en_cours_=NULL;
		_ligue_en_cours_=NULL;
		if(lieux_.isEmpty()){
			donnees.ajouter_lieu(0,dialogue_->nv_lieu());
			ind_lieu=0;
			if(grille->nb_lignes()==0){
				grille->init();
			}
		}else{
			Utilitaire::trier<int>(lieux_,true);
			int ind_=lieux_[0];
			if(ind_>0){
				donnees.ajouter_lieu(0,dialogue_->nv_lieu());
				ind_lieu=0;
			}else{
				for(int i=1;i<lieux_.size();i++){
					if(lieux_[i]-1!=lieux_[i-1]){
						ind_=lieux_[i-1]+1;
						break;
					}
				}
				if(lieux_.last()==lieux_.size()-1){
					ind_=lieux_.size();
				}
				donnees.ajouter_lieu(ind_,dialogue_->nv_lieu());
				ind_lieu=ind_;
			}
		}
		Lieu *lieu_=donnees.lieu(ind_lieu);
		_lieu_en_cours_=lieu_;
		ind_plateau=0;
		lieu_->ajout_plateau(ind_plateau,Plateau());
		_plateau_en_cours_=lieu_->plateau(ind_plateau);
		grille->table_rase();
		grille->repaint();
		PanneauEditerEnv::_environnement_en_cours_=NULL;
		PanneauEditerEnv::_tuile_en_cours_=NULL;
		panneau_editeur_env->maj_env();
	}
	delete dialogue_;
	dialogue_=NULL;
}

void Fenetre::maj_nom_type_lieu(){
	if(_lieu_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIEU_EDITION"));
		return;
	}
	DialogueNLieu *dialogue_=new DialogueNLieu(langue,this);
	dialogue_->maj_nom_type(donnees.nom_type_lieux().valeur(ind_lieu));
	dialogue_->exec();
	bool accepter_=dialogue_->result()==QDialog::Accepted;
	if(accepter_){
		QPair<QString,QString> nom_type_=dialogue_->nom_type();
		*_lieu_en_cours_->adr_nom()=nom_type_.first;
		*_lieu_en_cours_->adr_type()=nom_type_.second;
		donnees.maj_nom_type_lieu(ind_lieu,nom_type_);
	}
	delete dialogue_;
	dialogue_=NULL;
}

void Fenetre::maj_dims_env(const QPair<int,int>& _dims){
	QSize taille_=grille->tuile(0,0)->imag().size();
	rectangle_nv_env.second=QPair<int,int>(_dims.first*taille_.width(),_dims.second*taille_.height());
	QPair<int,int> reg_;
	reg_.first=Utilitaire::max_min<int>(rectangle_nv_env.first.first+rectangle_nv_env.second.first,grille->nb_colonnes()*taille_.width()).first;
	reg_.second=Utilitaire::max_min<int>(rectangle_nv_env.first.second+rectangle_nv_env.second.second,grille->nb_lignes()*taille_.height()).first;
	grille->affecter_rectangle_nv_env(rectangle_nv_env);
	grille->resize(reg_.first,reg_.second);
	grille->repaint(rectangle_nv_env.first.first,rectangle_nv_env.first.second,rectangle_nv_env.second.first,rectangle_nv_env.second.second);
}

void Fenetre::maj_dims_env2(){
	QPair<int,int> dims_=rectangle_nv_env.second;
	QStringList dims_inv_=Utilitaire::constante(Import::_constantes_,"RECTANGLE_INVALIDE_FENETRE").split(",");
	rectangle_nv_env.second=QPair<int,int>(dims_inv_[0].toInt(),dims_inv_[1].toInt());
	grille->affecter_rectangle_nv_env(rectangle_nv_env);
	grille->repaint(rectangle_nv_env.first.first,rectangle_nv_env.first.second,dims_.first,dims_.second);
}

void Fenetre::selection_coords(const QPair<QPair<int,int>,QPair<int,int> >& _coords_sel){
	if(_plateau_en_cours_==NULL&&_plateau_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
		return;
	}
	if(choix_env!=DEPLACER){
		coordonnees_act=_coords_sel;
		if(choix_env==SELECTION){
			Coordonnees c_;
			*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
			*c_.adr_environnement()=coordonnees_act.first;
			*c_.adr_tuile()=coordonnees_act.second;
			et_stat->setText(c_.formater());
			if(_plateau_en_cours_!=NULL){
				if(_plateau_en_cours_->coins_gauche().contains(_coords_sel.first)){
					panneau_editeur_env->maj_env(coordonnees_act);
					//TODO changer les données à être éditées.
				}
			}else{
				if(_plateau_ligue_en_cours_->coins_gauche().contains(_coords_sel.first)){
					panneau_editeur_ligue->maj_env(coordonnees_act);
					//TODO changer les données à être éditées.
				}
			}
			return;
		}
		if(choix_env==NOUVEAU){
		//TODO agrandir si nécessaire
			if(_plateau_en_cours_!=NULL){
				if(_plateau_en_cours_->coins_gauche().contains(_coords_sel.first)){
					QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
					return;
				}
			}else{
				if(_plateau_ligue_en_cours_->coins_gauche().contains(_coords_sel.first)){
					QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
					return;
				}
			}
			QSize taille_=grille->tuile(0,0)->imag().size();
			rectangle_nv_env.second=QPair<int,int>(taille_.width(),taille_.height());
			rectangle_nv_env.first=QPair<int,int>(coordonnees_act.first.first*taille_.width(),coordonnees_act.first.second*taille_.height());
			grille->affecter_rectangle_nv_env(rectangle_nv_env);
			grille->repaint(rectangle_nv_env.first.first,rectangle_nv_env.first.second,rectangle_nv_env.second.first,rectangle_nv_env.second.second);
			DialogueNEnvir *dialogue_=new DialogueNEnvir(langue,this);
			dialogue_->exec();
			bool accepter_=dialogue_->result()==QDialog::Accepted;
			if(accepter_){
				if(_plateau_en_cours_!=NULL){
					Environnement env_=dialogue_->nv_envir();
					QPair<int,int> dims_=env_.dimensions();
					QList<QPair<int,int> > vois_;
					if(_plateau_en_cours_->peut_contenir_nv_env(_coords_sel.first,dims_,vois_)){
						QPair<int,int> coin_bas_droit_=QPair<int,int>(_coords_sel.first.first+dims_.first-1,_coords_sel.first.second+dims_.second-1);
						int nb_lg_=grille->nb_lignes();
						if(nb_lg_<=coin_bas_droit_.second){
							grille->ajouter_lignes(coin_bas_droit_.second-nb_lg_+1);
						}
						int nb_col_=grille->nb_colonnes();
						if(nb_col_<=coin_bas_droit_.first){
							grille->ajouter_colonnes(coin_bas_droit_.first-nb_col_+1);
						}
						_plateau_en_cours_->ajouter_environnement(_coords_sel.first,env_);
						panneau_editeur_env->maj_env(coordonnees_act);
						for(int i=_coords_sel.first.first;i<=coin_bas_droit_.first;i++){
							for(int j=_coords_sel.first.second;j<=coin_bas_droit_.second;j++){
								TuileGraphique *tuile_g_=grille->tuile(i,j);
								tuile_g_->maj_coords(QPair<int,int>(i-_coords_sel.first.first,j-_coords_sel.first.second));
								tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_.type_env()));
							}
						}
					}else{
					//TODO message
					}
				}else{
					EnvironnementLigue env_=dialogue_->nv_envir_ligue();
					QPair<int,int> dims_=env_.dimensions();
					QList<QPair<int,int> > vois_;
					if(_plateau_ligue_en_cours_->peut_contenir_nv_env(_coords_sel.first,dims_,vois_)){
						QPair<int,int> coin_bas_droit_=QPair<int,int>(_coords_sel.first.first+dims_.first-1,_coords_sel.first.second+dims_.second-1);
						int nb_lg_=grille->nb_lignes();
						if(nb_lg_<=coin_bas_droit_.second){
							grille->ajouter_lignes(coin_bas_droit_.second-nb_lg_+1);
						}
						int nb_col_=grille->nb_colonnes();
						if(nb_col_<=coin_bas_droit_.first){
							grille->ajouter_colonnes(coin_bas_droit_.first-nb_col_+1);
						}
						_plateau_ligue_en_cours_->ajouter_environnement(_coords_sel.first,env_);
						panneau_editeur_ligue->maj_env(coordonnees_act);
						for(int i=_coords_sel.first.first;i<=coin_bas_droit_.first;i++){
							for(int j=_coords_sel.first.second;j<=coin_bas_droit_.second;j++){
								TuileGraphique *tuile_g_=grille->tuile(i,j);
								tuile_g_->maj_coords(QPair<int,int>(i-_coords_sel.first.first,j-_coords_sel.first.second));
								tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_.type_env()));
							}
						}
					}else{
					//TODO message
					}
				}
			}
			delete dialogue_;
			dialogue_=NULL;
		}else{//SUPPRIMER
			QPair<int,int> dims_;
			if(_plateau_en_cours_!=NULL){
				dims_=_plateau_en_cours_->environnement(_coords_sel.first).dimensions();
				_plateau_en_cours_->supprimer_environnement(_coords_sel.first);
			}else{
				dims_=_plateau_ligue_en_cours_->environnement(_coords_sel.first).dimensions();
				_plateau_ligue_en_cours_->supprimer_environnement(_coords_sel.first);
			}
			QPair<int,int> id_=_coords_sel.first;
			QPair<int,int> coin_bas_droit_or_=QPair<int,int>(id_.first+dims_.first-1,id_.second+dims_.second-1);
			for(int i=id_.first;i<=coin_bas_droit_or_.first;i++){
				for(int j=id_.second;j<=coin_bas_droit_or_.second;j++){
					TuileGraphique *tuile_g_=grille->tuile(i,j);
					tuile_g_->reinit();
				}
			}
		}
	}else{
	//TODO deplacement
	//TODO agrandir si nécessaire
		QPair<int,int> id_or_=coordonnees_act.first;
		QPair<int,int> select_act_=QPair<int,int>(id_or_.first+coordonnees_act.second.first,id_or_.second+coordonnees_act.second.second);
		QPair<int,int> id_dest_=QPair<int,int>(id_or_.first+_coords_sel.second.first+_coords_sel.first.first-select_act_.first,id_or_.second+_coords_sel.second.second+_coords_sel.first.second-select_act_.second);
		if(_plateau_en_cours_!=NULL){
			Environnement env_=_plateau_en_cours_->environnement(id_or_);
			_plateau_en_cours_->supprimer_environnement(id_or_);
			QList<QPair<int,int> > vois_;
			QPair<int,int> dims_=env_.dimensions();
			if(_plateau_en_cours_->peut_contenir_nv_env(id_dest_,dims_,vois_)){
				QPair<int,int> coin_bas_droit_=QPair<int,int>(id_dest_.first+dims_.first-1,id_dest_.second+dims_.second-1);
				int nb_lg_=grille->nb_lignes();
				if(nb_lg_<=coin_bas_droit_.second){
					grille->ajouter_lignes(coin_bas_droit_.second-nb_lg_+1);
				}
				int nb_col_=grille->nb_colonnes();
				if(nb_col_<=coin_bas_droit_.first){
					grille->ajouter_colonnes(coin_bas_droit_.first-nb_col_+1);
				}
				_plateau_en_cours_->ajouter_environnement(id_dest_,env_);
				_plateau_en_cours_->deplacer_liens(id_or_,id_dest_);
				QPair<int,int> coin_bas_droit_or_=QPair<int,int>(id_or_.first+dims_.first-1,id_or_.second+dims_.second-1);
				for(int i=id_or_.first;i<=coin_bas_droit_or_.first;i++){
					for(int j=id_or_.second;j<=coin_bas_droit_or_.second;j++){
						TuileGraphique *tuile_g_=grille->tuile(i,j);
						tuile_g_->reinit();
					}
				}
				typedef QPair<QPair<int,int>,QPair<int,int> > OrigineLien;
				foreach(OrigineLien o,_plateau_en_cours_->liaisons_vers_autres_plateaux()){
					TuileGraphique *tuile_g_=grille->tuile(o.second.first+o.first.first,o.second.second+o.first.second);
					tuile_g_->maj_lien(QPair<QImage,bool>(Import::_liens_.valeur(_plateau_en_cours_->image_origine_liaison(o)),true));
				}
				for(int i=id_dest_.first;i<=coin_bas_droit_.first;i++){
					for(int j=id_dest_.second;j<=coin_bas_droit_.second;j++){
						TuileGraphique *tuile_g_=grille->tuile(i,j);
						tuile_g_->maj_coords(QPair<int,int>(i-id_dest_.first,j-id_dest_.second));
						Tuile *tuile_=env_.tuile(QPair<int,int>(i-id_dest_.first,j-id_dest_.second));
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
						if(env_.coords_autres_persos().contains(QPair<int,int>(i-id_dest_.first,j-id_dest_.second))){
							bool suppr_=false;
							Personnage *perso_=env_.personnage(QPair<int,int>(i-id_dest_.first,j-id_dest_.second),suppr_);
							tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*perso_->adr_nom_miniature()),*perso_->adr_orientation()));
						}else if(env_.coords_dresseurs().contains(QPair<int,int>(i-id_dest_.first,j-id_dest_.second))){
							bool suppr_=false;
							Dresseur1 *perso_=env_.dresseur(QPair<int,int>(i-id_dest_.first,j-id_dest_.second),suppr_);
							tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*perso_->adr_nom_miniature()),*perso_->adr_orientation()));
						}else if(env_.coords_champions().contains(QPair<int,int>(i-id_dest_.first,j-id_dest_.second))){
							bool suppr_=false;
							Champion *perso_=env_.champion(QPair<int,int>(i-id_dest_.first,j-id_dest_.second),suppr_);
							tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*perso_->adr_nom_miniature()),*perso_->adr_orientation()));
						}else if(env_.coords_objets().contains(QPair<int,int>(i-id_dest_.first,j-id_dest_.second))){
							bool suppr_=false;
							QString *objet_=env_.objet(QPair<int,int>(i-id_dest_.first,j-id_dest_.second),suppr_);
							tuile_g_->maj_obst(QPair<QImage,bool>(Import::_images_objets_.valeur(*objet_),true));
						}else if(env_.coords_pokemon_legendaire().contains(QPair<int,int>(i-id_dest_.first,j-id_dest_.second))){
							bool suppr_=false;
							Pokemon *pokemon_=env_.pokemon_legendaire(QPair<int,int>(i-id_dest_.first,j-id_dest_.second),suppr_);
							int num_pk_=Import::_pokedex_.valeur(*pokemon_->adr_nom())->num();
							tuile_g_->maj_obst(QPair<QImage,bool>(Import::_miniatures_.valeur(num_pk_),true));
						}else if(env_.coords_lieux_dons_pokemon().contains(QPair<int,int>(i-id_dest_.first,j-id_dest_.second))){
							tuile_g_->maj_obst(QPair<QImage,bool>(Import::_pk_trouve_,true));
						}
					}
				}
				//TODO affichage des coordonnées sélectionnées.
			}else{
				_plateau_en_cours_->ajouter_environnement(id_or_,env_);
			//TODO message
			}
		}else{
			EnvironnementLigue env_=_plateau_ligue_en_cours_->environnement(id_or_);//,suppr_)
			_plateau_ligue_en_cours_->supprimer_environnement(id_or_);
			QList<QPair<int,int> > vois_;
			QPair<int,int> dims_=env_.dimensions();
			if(_plateau_ligue_en_cours_->peut_contenir_nv_env(id_dest_,dims_,vois_)){
				QPair<int,int> coin_bas_droit_=QPair<int,int>(id_dest_.first+dims_.first-1,id_dest_.second+dims_.second-1);
				int nb_lg_=grille->nb_lignes();
				if(nb_lg_<=coin_bas_droit_.second){
					grille->ajouter_lignes(coin_bas_droit_.second-nb_lg_+1);
				}
				int nb_col_=grille->nb_colonnes();
				if(nb_col_<=coin_bas_droit_.first){
					grille->ajouter_colonnes(coin_bas_droit_.first-nb_col_+1);
				}
				_plateau_ligue_en_cours_->ajouter_environnement(id_dest_,env_);
				QPair<int,int> coin_bas_droit_or_=QPair<int,int>(id_or_.first+dims_.first-1,id_or_.second+dims_.second-1);
				for(int i=id_or_.first;i<=coin_bas_droit_or_.first;i++){
					for(int j=id_or_.second;j<=coin_bas_droit_or_.second;j++){
						TuileGraphique *tuile_g_=grille->tuile(i,j);
						tuile_g_->reinit();
					}
				}
				for(int i=id_dest_.first;i<=coin_bas_droit_.first;i++){
					for(int j=id_dest_.second;j<=coin_bas_droit_.second;j++){
						TuileGraphique *tuile_g_=grille->tuile(i,j);
						tuile_g_->maj_coords(QPair<int,int>(i-id_dest_.first,j-id_dest_.second));
						Tuile *tuile_=env_.tuile(QPair<int,int>(i-id_dest_.first,j-id_dest_.second));
						tuile_g_->maj_image(Import::_tuiles_importees_.valeur(*tuile_->adr_nom_image()));
					}
				}
				//TODO affichage des coordonnées sélectionnées.
			}else{
				_plateau_ligue_en_cours_->ajouter_environnement(id_or_,env_);
			//TODO message
			}
		}
	}
	grille->repaint();
	//TODO en fonction de choix_env
}

void Fenetre::maj_image_tuile(const QImage& _img){
	TuileGraphique *tuile_g_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
	tuile_g_->maj_image(_img);
	grille->repaint();
}

void Fenetre::inserer_plateau(){
	if(_ligue_en_cours_==NULL&&_lieu_en_cours_==NULL){
		QString erreur_;
		erreur_+=traduire("PAS_LIGUE_EDITION")+"\n";
		erreur_+=traduire("PAS_LIEU_EDITION");
		QMessageBox::critical(this,traduire("ERREUR"),erreur_);
		return;
	}
	if(_lieu_en_cours_!=NULL){
		PanneauEditerEnv::_environnement_en_cours_=NULL;
		PanneauEditerEnv::_tuile_en_cours_=NULL;
		QList<int> plateaux_=_lieu_en_cours_->plateaux_c();
		if(plateaux_.isEmpty()){
			_lieu_en_cours_->ajout_plateau(0,Plateau());
			_plateau_en_cours_=_lieu_en_cours_->plateau(0);
			ind_plateau=0;
		}else{
			Utilitaire::trier<int>(plateaux_,true);
			int ind_=plateaux_[0];
			if(ind_>0){
				_lieu_en_cours_->ajout_plateau(0,Plateau());
				_plateau_en_cours_=_lieu_en_cours_->plateau(0);
				ind_plateau=0;
			}else{
				for(int i=1;i<plateaux_.size();i++){
					if(plateaux_[i]-1!=plateaux_[i-1]){
						ind_=plateaux_[i-1]+1;
						break;
					}
				}
				if(plateaux_.last()==plateaux_.size()-1){
					ind_=plateaux_.size();
				}
				_lieu_en_cours_->ajout_plateau(ind_,Plateau());
				_plateau_en_cours_=_lieu_en_cours_->plateau(ind_);
				ind_plateau=ind_;
			}
		}
		grille->table_rase();
		//grille->repaint()
	}else{
		DialogueSelectPlateau *dial_=new DialogueSelectPlateau(langue,false,this,false,true);;
		dial_->exec();
		bool accepte_=dial_->result()==QDialog::Accepted;
		if(!accepte_){
			delete dial_;
			dial_=NULL;
			return;
		}
		grille->table_rase();
		ind_plateau=dial_->plateau_select();
		_ligue_en_cours_->inserer_plateau(ind_plateau,PlateauLigue());
		_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
		delete dial_;
		dial_=NULL;
	}
}

void Fenetre::selection_lieu(){
	if(donnees.lieux_c().isEmpty()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIEU_DONNEES"));
		return;
	}
	DialogueSelectLieu *dial_=new DialogueSelectLieu(langue,false,this);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		int choix_=dial_->lieu_select();
		if(choix_>=0){
			if(choix_!=ind_lieu||_ligue_en_cours_!=NULL){//TODO attention au chargement, il faut y passer si le chargement vient d'etre fait
				Lieu *lieu_=donnees.lieu(choix_);
				if(!lieu_->plateaux_c().isEmpty()){
					ind_lieu_tmp=ind_lieu;
					ind_lieu=choix_;
					_lieu_en_cours_=lieu_;
					DialogueSelectPlateau *dial_2_=new DialogueSelectPlateau(langue,false,this,true);
					dial_2_->exec();
					bool accepte_=dial_2_->result()==QDialog::Accepted;
					if(accepte_){
						int choix_=dial_2_->plateau_select();
						if(choix_>=0&&(choix_!=ind_plateau||ind_lieu_tmp!=ind_lieu||_ligue_en_cours_!=NULL)){
							ind_plateau=choix_;
							PanneauEditerEnv::_environnement_en_cours_=NULL;
							PanneauEditerEnv::_tuile_en_cours_=NULL;
							_plateau_en_cours_=_lieu_en_cours_->plateau(choix_);
							if(_ligue_en_cours_!=NULL){
								_plateau_ligue_en_cours_=NULL;
								_ligue_en_cours_=NULL;
								ascenseur_panneau->takeWidget();
								panneau_editeur_env->show();
								ascenseur_panneau->setWidget(panneau_editeur_env);
								grille->table_rase();
								//TODO
							}
							maj_plateau();
						}
					}
					delete dial_2_;
					dial_2_=NULL;
					if(_ligue_en_cours_!=NULL){
						_lieu_en_cours_=NULL;
					}
					ind_lieu_tmp=ind_lieu;
				}
			}else if(donnees.lieu(choix_)->plateaux_c().size()==1){
				Lieu *lieu_=donnees.lieu(choix_);
				if(lieu_->plateau(lieu_->plateaux_c()[0])->coins_gauche().isEmpty()){
					ind_lieu=choix_;
					_lieu_en_cours_=lieu_;
					ind_plateau=0;
					grille->table_rase();
					grille->repaint();
					if(_ligue_en_cours_!=NULL){
						_plateau_ligue_en_cours_=NULL;
						_ligue_en_cours_=NULL;
						ascenseur_panneau->takeWidget();
						panneau_editeur_env->show();
						ascenseur_panneau->setWidget(panneau_editeur_env);
						grille->table_rase();
						//TODO
					}
					PanneauEditerEnv::_environnement_en_cours_=NULL;
					PanneauEditerEnv::_tuile_en_cours_=NULL;
					_plateau_en_cours_=_lieu_en_cours_->plateau(ind_plateau);
				}
			}
		}
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::suppression_lieu(){
	if(donnees.lieux_c().isEmpty()||_lieu_en_cours_==NULL){
		QString err_;
		if(_lieu_en_cours_==NULL){
			err_+=traduire("PAS_LIEU_EDITION")+"\n";
		}
		if(donnees.lieux_c().isEmpty()){
			err_+=traduire("PAS_LIEU_DONNEES");
		}
		QMessageBox::critical(this,traduire("ERREUR"),err_);
		return;
	}
	DialogueSelectLieu *dial_=new DialogueSelectLieu(langue,false,this);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		int choix_=dial_->lieu_select();
		if(choix_>=0&&choix_!=ind_lieu){
			donnees.supprimer_lieu(choix_);
		}
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::maj_plateau(){
	grille->table_rase();
	Plateau *pl_=_plateau_en_cours_;
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

void Fenetre::select_plateau(){
	if(_lieu_en_cours_==NULL&&_ligue_en_cours_==NULL){
		QString erreur_;
		erreur_+=traduire("PAS_LIGUE_EDITION")+"\n";
		erreur_+=traduire("PAS_LIEU_EDITION");
		QMessageBox::critical(this,traduire("ERREUR"),erreur_);
		return;
	}
	if(_lieu_en_cours_!=NULL){
		//QMessageBox::critical(this,"Erreur","Pas de lieu en cours d'edition")
		DialogueSelectPlateau *dial_=new DialogueSelectPlateau(langue,false,this,true);
		dial_->exec();
		bool accepte_=dial_->result()==QDialog::Accepted;
		if(accepte_){
			int choix_=dial_->plateau_select();
			if(choix_>=0&&(choix_!=ind_plateau||ind_lieu_tmp!=ind_lieu)){
				ind_plateau=choix_;
				PanneauEditerEnv::_environnement_en_cours_=NULL;
				PanneauEditerEnv::_tuile_en_cours_=NULL;
				_plateau_en_cours_=_lieu_en_cours_->plateau(choix_);
				if(_ligue_en_cours_!=NULL){
					_plateau_ligue_en_cours_=NULL;
					_ligue_en_cours_=NULL;
					ascenseur_panneau->takeWidget();
					panneau_editeur_env->show();
					ascenseur_panneau->setWidget(panneau_editeur_env);
					grille->table_rase();
					//TODO
				}
				maj_plateau();
			}
		}
		delete dial_;
		dial_=NULL;
	}else{
		DialogueSelectPlateau *dial_=new DialogueSelectPlateau(langue,false,this,false);;
		dial_->exec();
		bool accepte_=dial_->result()==QDialog::Accepted;
		if(!accepte_){
			delete dial_;
			dial_=NULL;
			return;
		}
		int choix_=dial_->plateau_select();
		if(choix_>=0&&(choix_!=ind_plateau||ind_lieu_tmp!=ind_lieu)){
			grille->table_rase();
			ind_plateau=dial_->plateau_select();
			_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
			if(_lieu_en_cours_!=NULL){
				_plateau_en_cours_=NULL;
				_lieu_en_cours_=NULL;
				ascenseur_panneau->takeWidget();
				panneau_editeur_ligue->show();
				ascenseur_panneau->setWidget(panneau_editeur_ligue);
				grille->table_rase();
				//TODO
			}
			maj_plateau_ligue();
			panneau_editeur_ligue->maj_dresseur();
		}
		delete dial_;
		dial_=NULL;
	}
}

void Fenetre::suppression_plateau(){
	if(_lieu_en_cours_==NULL&&_ligue_en_cours_==NULL){
		QString erreur_;
		erreur_+=traduire("PAS_LIGUE_EDITION")+"\n";
		erreur_+=traduire("PAS_LIEU_EDITION");
		QMessageBox::critical(this,traduire("ERREUR"),erreur_);
		return;
	}
	if(_lieu_en_cours_!=NULL){
		DialogueSelectPlateau *dial_=new DialogueSelectPlateau(langue,true,this,true);
		dial_->exec();
		bool accepte_=dial_->result()==QDialog::Accepted;
		if(accepte_){
			int choix_=dial_->plateau_select();
			if(choix_>=0&&choix_!=ind_plateau){
				donnees.enlever_tous_liens_vers_plat(ind_lieu,choix_);
				_lieu_en_cours_->suppression_plateau(choix_);
			}
		}
		delete dial_;
		dial_=NULL;
	}else{
		DialogueSelectPlateau *dial_=new DialogueSelectPlateau(langue,false,this,false);;
		dial_->exec();
		bool accepte_=dial_->result()==QDialog::Accepted;
		if(accepte_){
			int choix_=dial_->plateau_select();
			if(choix_>=0&&choix_!=ind_plateau){
				_ligue_en_cours_->supprimer_plateau_reindexer(choix_);
				if(ind_plateau>choix_){
					ind_plateau--;
				}
			}
		}
		delete dial_;
		dial_=NULL;
	}
}

void Fenetre::ajouter_ligne_ht_plateau(){
	if(_plateau_en_cours_==NULL&&_plateau_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
		return;
	}
	if(_plateau_en_cours_!=NULL){
		_plateau_en_cours_->decaler_vers_bas(1);
	}else{
		_plateau_ligue_en_cours_->decaler_vers_bas(1);
	}
	grille->decaler_vers_bas(1);
	grille->repaint();
}

void Fenetre::ajouter_ligne_bas_plateau(){
	if(_plateau_en_cours_==NULL&&_plateau_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
		return;
	}
	grille->ajouter_lignes(1);
}

void Fenetre::ajouter_col_gauche_plateau(){
	if(_plateau_en_cours_==NULL&&_plateau_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
		return;
	}
	if(_plateau_en_cours_!=NULL){
		_plateau_en_cours_->decaler_vers_droite(1);
	}else{
		_plateau_ligue_en_cours_->decaler_vers_droite(1);
	} 
	grille->decaler_vers_droite(1);
	grille->repaint();
}

void Fenetre::ajouter_col_droite_plateau(){
	if(_plateau_en_cours_==NULL&&_plateau_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
		return;
	}
	grille->ajouter_colonnes(1);
}

void Fenetre::ajouter_lignes_ht_plateau(){
	if(_plateau_en_cours_==NULL&&_plateau_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
		return;
	}
	DialogueGrille *dialogue_=new DialogueGrille(langue,DialogueGrille::AJOUT_LGS_HAUT,this);
	dialogue_->exec();
	bool accepter_=dialogue_->result()==QDialog::Accepted;
	if(accepter_){
		int nb_lgs_=dialogue_->valeur();
		if(_plateau_en_cours_!=NULL){
			_plateau_en_cours_->decaler_vers_bas(nb_lgs_);
		}else{
			_plateau_ligue_en_cours_->decaler_vers_bas(nb_lgs_);
		}
		grille->decaler_vers_bas(nb_lgs_);
		grille->repaint();
	}
	delete dialogue_;
	dialogue_=NULL;
}

void Fenetre::ajouter_lignes_bas_plateau(){
	if(_plateau_en_cours_==NULL&&_plateau_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
		return;
	}
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

void Fenetre::ajouter_cols_gauche_plateau(){
	if(_plateau_en_cours_==NULL&&_plateau_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
		return;
	}
	DialogueGrille *dialogue_=new DialogueGrille(langue,DialogueGrille::AJOUT_COLS_GAUCHE,this);
	dialogue_->exec();
	bool accepter_=dialogue_->result()==QDialog::Accepted;
	if(accepter_){
		int nb_lgs_=dialogue_->valeur();
		if(_plateau_en_cours_!=NULL){
			_plateau_en_cours_->decaler_vers_droite(nb_lgs_);
		}else{
			_plateau_ligue_en_cours_->decaler_vers_droite(nb_lgs_);
		}
		grille->decaler_vers_droite(nb_lgs_);
		grille->repaint();
	}
	delete dialogue_;
	dialogue_=NULL;
}

void Fenetre::ajouter_cols_droite_plateau(){
	if(_plateau_en_cours_==NULL&&_plateau_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
		return;
	}
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

void Fenetre::nv_env(){
	choix_env=NOUVEAU;
	et_stat->setText(traduire("AJOUT_ENV"));
}

void Fenetre::deplacer_env(){
	choix_env=DEPLACER;
	et_stat->setText(traduire("DEPLACER_ENV"));
}

void Fenetre::selection_env(){
	choix_env=SELECTION;
	et_stat->setText(traduire("SELECT_ENV"));
}

void Fenetre::supprimer_env(){
	choix_env=SUPPRIMER;
	et_stat->setText(traduire("SUPPR_ENV"));
}

void Fenetre::modifier_hauteur_env(){
	if(_plateau_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_en_cours_->environnement(id_env_).dimensions();
		int hauteur_=dims_.second;
		DialogueHauteur *dialogue_=new DialogueHauteur(langue,hauteur_,this);
		dialogue_->exec();
		bool accepter_=dialogue_->result()==QDialog::Accepted;
		if(accepter_){
			int nv_hauteur_=dialogue_->hauteur_v();
			if(hauteur_<nv_hauteur_){
				dims_.second=nv_hauteur_-hauteur_;
				id_env_.second+=hauteur_;
				QList<QPair<int,int> > vois_;
				if(_plateau_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
					id_env_.second-=hauteur_;
					bool suppr_=false;
					Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
					int nb_lgs_aj_=dims_.second;
					for(int i=0;i<nb_lgs_aj_;i++){
						env_->inserer_ligne(hauteur_+i);
					}
					dims_=env_->dimensions();
					int nb_lg_grille_=grille->nb_lignes();
					if(id_env_.second+dims_.second>nb_lg_grille_){
						grille->ajouter_lignes(id_env_.second+dims_.second-nb_lg_grille_);
					}
					for(int i=hauteur_;i<nv_hauteur_;i++){
						for(int j=0;j<dims_.first;j++){
							TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
							tuile_g_->maj_coords(QPair<int,int>(j,i));
							tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
						}
					}
					grille->repaint();
				}else{
					QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"))				;
				}
			}else if(hauteur_>nv_hauteur_){
				bool suppr_=false;
				Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
				int nb_lgs_suppr_=hauteur_-nv_hauteur_;
				for(int i=0;i<nb_lgs_suppr_;i++){
					env_->supprimer_ligne(nv_hauteur_);
				}
				for(int i=nv_hauteur_;i<hauteur_;i++){
					for(int j=0;j<dims_.first;j++){
						TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
						tuile_g_->reinit();
					}
				}
				grille->repaint();
			}
		}
		delete dialogue_;
		dialogue_=NULL;
	}else if(_plateau_ligue_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_ligue_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_ligue_en_cours_->environnement(id_env_).dimensions();
		int hauteur_=dims_.second;
		DialogueHauteur *dialogue_=new DialogueHauteur(langue,hauteur_,this);
		dialogue_->exec();
		bool accepter_=dialogue_->result()==QDialog::Accepted;
		if(accepter_){
			int nv_hauteur_=dialogue_->hauteur_v();
			if(hauteur_<nv_hauteur_){
				dims_.second=nv_hauteur_-hauteur_;
				id_env_.second+=hauteur_;
				QList<QPair<int,int> > vois_;
				if(_plateau_ligue_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
					id_env_.second-=hauteur_;
					bool suppr_=false;
					EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
					int nb_lgs_aj_=dims_.second;
					for(int i=0;i<nb_lgs_aj_;i++){
						env_->inserer_ligne(hauteur_+i);
					}
					dims_=env_->dimensions();
					int nb_lg_grille_=grille->nb_lignes();
					if(id_env_.second+dims_.second>nb_lg_grille_){
						grille->ajouter_lignes(id_env_.second+dims_.second-nb_lg_grille_);
					}
					for(int i=hauteur_;i<nv_hauteur_;i++){
						for(int j=0;j<dims_.first;j++){
							TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
							tuile_g_->maj_coords(QPair<int,int>(j,i));
							tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
						}
					}
					grille->repaint();
				}else{
					QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"))				;
				}
			}else if(hauteur_>nv_hauteur_){
				bool suppr_=false;
				EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
				int nb_lgs_suppr_=hauteur_-nv_hauteur_;
				for(int i=0;i<nb_lgs_suppr_;i++){
					env_->supprimer_ligne(nv_hauteur_);
				}
				for(int i=nv_hauteur_;i<hauteur_;i++){
					for(int j=0;j<dims_.first;j++){
						TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
						tuile_g_->reinit();
					}
				}
				grille->repaint();
			}
		}
		delete dialogue_;
		dialogue_=NULL;
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
	}
}

void Fenetre::insert_ligne_env(){
	if(_plateau_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}	
		QPair<int,int> dims_=_plateau_en_cours_->environnement(id_env_).dimensions();
		int hauteur_=dims_.second;
		dims_.second=1;
		id_env_.second+=hauteur_;
		QList<QPair<int,int> > vois_;
		if(_plateau_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
			id_env_.second-=hauteur_;
			bool suppr_=false;
			Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
			env_->inserer_ligne(coordonnees_act.second.second);
			dims_=env_->dimensions();
			int nb_lg_grille_=grille->nb_colonnes();
			if(id_env_.second+dims_.second>nb_lg_grille_){
				grille->ajouter_lignes(id_env_.second+dims_.second-nb_lg_grille_);
			}
			for(int i=dims_.second-1;i>coordonnees_act.second.second;i--){
				for(int j=0;j<dims_.first;j++){
					TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
					TuileGraphique *tuile_g_2_=grille->tuile(j+id_env_.first,i+id_env_.second-1);
					QPair<int,int> coords_=tuile_g_2_->coords();
					tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first,coords_.second+1));
				}
			}
			for(int j=0;j<dims_.first;j++){
				TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,coordonnees_act.second.second+id_env_.second);;
				tuile_g_->maj_coords(QPair<int,int>(j,coordonnees_act.second.second));
				tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
				tuile_g_->init();;
			}
			//TODO mettre une colonne dépendant du type de l'environnement
			grille->repaint();
		}else{
			QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
		}
	}else if(_plateau_ligue_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_ligue_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_ligue_en_cours_->environnement(id_env_).dimensions();
		int hauteur_=dims_.second;
		dims_.second=1;
		id_env_.second+=hauteur_;
		QList<QPair<int,int> > vois_;
		if(_plateau_ligue_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
			id_env_.second-=hauteur_;
			bool suppr_=false;
			EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
			env_->inserer_ligne(coordonnees_act.second.second);
			dims_=env_->dimensions();
			int nb_lg_grille_=grille->nb_colonnes();
			if(id_env_.second+dims_.second>nb_lg_grille_){
				grille->ajouter_lignes(id_env_.second+dims_.second-nb_lg_grille_);
			}
			for(int i=dims_.second-1;i>coordonnees_act.second.second;i--){
				for(int j=0;j<dims_.first;j++){
					TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
					TuileGraphique *tuile_g_2_=grille->tuile(j+id_env_.first,i+id_env_.second-1);
					QPair<int,int> coords_=tuile_g_2_->coords();
					tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first,coords_.second+1));
				}
			}
			for(int j=0;j<dims_.first;j++){
				TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,coordonnees_act.second.second+id_env_.second);;
				tuile_g_->maj_coords(QPair<int,int>(j,coordonnees_act.second.second));
				tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
				tuile_g_->init();;
			}
			//TODO mettre une colonne dépendant du type de l'environnement
			grille->repaint();
		}else{
			QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
		}
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
	}
}

void Fenetre::insert_supprimer_lignes_env(){
	if(_plateau_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_en_cours_->environnement(id_env_).dimensions();
		int hauteur_=dims_.second;
		DialogueHauteur *dialogue_=new DialogueHauteur(langue,hauteur_,this);
		dialogue_->exec();
		bool accepter_=dialogue_->result()==QDialog::Accepted;
		if(accepter_){
			int nv_hauteur_=dialogue_->hauteur_v();
			if(hauteur_<nv_hauteur_){
				int diff_=nv_hauteur_-hauteur_;
				dims_.second=diff_;
				id_env_.second+=hauteur_;
				QList<QPair<int,int> > vois_;
				if(_plateau_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
					id_env_.second-=hauteur_;
					bool suppr_=false;
					Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
					int nb_lgs_aj_=dims_.second;
					for(int i=0;i<nb_lgs_aj_;i++){
						env_->inserer_ligne(coordonnees_act.second.second+i);
					}
					dims_=env_->dimensions();
					int nb_lg_grille_=grille->nb_lignes();
					if(id_env_.second+dims_.second>nb_lg_grille_){
						grille->ajouter_lignes(id_env_.second+dims_.second-nb_lg_grille_);
					}
					for(int i=dims_.second-1;i>coordonnees_act.second.second+diff_-1;i--){
						for(int j=0;j<dims_.first;j++){
							TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
							TuileGraphique *tuile_g_2_=grille->tuile(j+id_env_.first,i+id_env_.second-diff_);
							QPair<int,int> coords_=tuile_g_2_->coords();
							tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first,coords_.second+diff_));
						}
					}
					for(int i=coordonnees_act.second.second+diff_-1;i>=coordonnees_act.second.second;i--){
						for(int j=0;j<dims_.first;j++){
							TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);;
							tuile_g_->maj_coords(QPair<int,int>(j,i));
							tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
							tuile_g_->init();
						}
					}
					grille->repaint();
				}else{
					QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
				}
			}else if(hauteur_>nv_hauteur_){
				int diff_=hauteur_-nv_hauteur_;
				bool suppr_=false;
				Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
				int nb_lgs_suppr_=hauteur_-nv_hauteur_;
				for(int i=0;i<nb_lgs_suppr_;i++){
					env_->supprimer_ligne(coordonnees_act.second.second);
				}
				dims_=env_->dimensions();
				for(int i=coordonnees_act.second.second;i<dims_.second;i++){
					for(int j=0;j<dims_.first;j++){
						TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
						TuileGraphique *tuile_g_2_=grille->tuile(j+id_env_.first,i+id_env_.second+diff_);
						QPair<int,int> coords_=tuile_g_2_->coords();
						tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first,coords_.second-diff_));
					}
				}
				for(int i=dims_.second;i<dims_.second+diff_;i++){
					for(int j=0;j<dims_.first;j++){
						TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
						tuile_g_->reinit();
					}
				}
				grille->repaint();
			}
		}
		delete dialogue_;
		dialogue_=NULL;
	}else if(_plateau_ligue_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_ligue_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_ligue_en_cours_->environnement(id_env_).dimensions();
		int hauteur_=dims_.second;
		DialogueHauteur *dialogue_=new DialogueHauteur(langue,hauteur_,this);
		dialogue_->exec();
		bool accepter_=dialogue_->result()==QDialog::Accepted;
		if(accepter_){
			int nv_hauteur_=dialogue_->hauteur_v();
			if(hauteur_<nv_hauteur_){
				int diff_=nv_hauteur_-hauteur_;
				dims_.second=diff_;
				id_env_.second+=hauteur_;
				QList<QPair<int,int> > vois_;
				if(_plateau_ligue_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
					id_env_.second-=hauteur_;
					bool suppr_=false;
					EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
					int nb_lgs_aj_=dims_.second;
					for(int i=0;i<nb_lgs_aj_;i++){
						env_->inserer_ligne(coordonnees_act.second.second+i);
					}
					dims_=env_->dimensions();
					int nb_lg_grille_=grille->nb_lignes();
					if(id_env_.second+dims_.second>nb_lg_grille_){
						grille->ajouter_lignes(id_env_.second+dims_.second-nb_lg_grille_);
					}
					for(int i=dims_.second-1;i>coordonnees_act.second.second+diff_-1;i--){
						for(int j=0;j<dims_.first;j++){
							TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
							TuileGraphique *tuile_g_2_=grille->tuile(j+id_env_.first,i+id_env_.second-diff_);
							QPair<int,int> coords_=tuile_g_2_->coords();
							tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first,coords_.second+diff_));
						}
					}
					for(int i=coordonnees_act.second.second+diff_-1;i>=coordonnees_act.second.second;i--){
						for(int j=0;j<dims_.first;j++){
							TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);;
							tuile_g_->maj_coords(QPair<int,int>(j,i));
							tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
							tuile_g_->init();
						}
					}
					grille->repaint();
				}else{
					QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
				}
			}else if(hauteur_>nv_hauteur_){
				int diff_=hauteur_-nv_hauteur_;
				bool suppr_=false;
				EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
				int nb_lgs_suppr_=hauteur_-nv_hauteur_;
				for(int i=0;i<nb_lgs_suppr_;i++){
					env_->supprimer_ligne(coordonnees_act.second.second);
				}
				dims_=env_->dimensions();
				for(int i=coordonnees_act.second.second;i<dims_.second;i++){
					for(int j=0;j<dims_.first;j++){
						TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
						TuileGraphique *tuile_g_2_=grille->tuile(j+id_env_.first,i+id_env_.second+diff_);
						QPair<int,int> coords_=tuile_g_2_->coords();
						tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first,coords_.second-diff_));
					}
				}
				for(int i=dims_.second;i<dims_.second+diff_;i++){
					for(int j=0;j<dims_.first;j++){
						TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
						tuile_g_->reinit();
					}
				}
				grille->repaint();
			}
		}
		delete dialogue_;
		dialogue_=NULL;
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
	}
}

void Fenetre::supprimer_ligne_env(){
	if(_plateau_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_en_cours_->environnement(id_env_).dimensions();
		bool suppr_=false;
		Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
		env_->supprimer_ligne(coordonnees_act.second.second);
		for(int i=coordonnees_act.second.second;i<dims_.second-1;i++){
			for(int j=0;j<dims_.first;j++){
				TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
				TuileGraphique *tuile_g_2_=grille->tuile(j+id_env_.first,i+id_env_.second+1);
				QPair<int,int> coords_=tuile_g_2_->coords();
				tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first,coords_.second-1));
			}
		}
		for(int j=0;j<dims_.first;j++){
			TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,dims_.second+id_env_.second-1);
			tuile_g_->reinit();
		}
		grille->repaint();
	}else if(_plateau_ligue_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_ligue_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_ligue_en_cours_->environnement(id_env_).dimensions();
		bool suppr_=false;
		EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
		env_->supprimer_ligne(coordonnees_act.second.second);
		for(int i=coordonnees_act.second.second;i<dims_.second-1;i++){
			for(int j=0;j<dims_.first;j++){
				TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,i+id_env_.second);
				TuileGraphique *tuile_g_2_=grille->tuile(j+id_env_.first,i+id_env_.second+1);
				QPair<int,int> coords_=tuile_g_2_->coords();
				tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first,coords_.second-1));
			}
		}
		for(int j=0;j<dims_.first;j++){
			TuileGraphique *tuile_g_=grille->tuile(j+id_env_.first,dims_.second+id_env_.second-1);
			tuile_g_->reinit();
		}
		grille->repaint();
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
	}
}

void Fenetre::modifier_largeur_env(){
	if(_plateau_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_en_cours_->environnement(id_env_).dimensions();
		int largeur_=dims_.first;
		DialogueLargeur *dialogue_=new DialogueLargeur(langue,largeur_,this);
		dialogue_->exec();
		bool accepter_=dialogue_->result()==QDialog::Accepted;
		if(accepter_){
			int nv_largeur_=dialogue_->largeur_v();
			if(largeur_<nv_largeur_){
				dims_.first=nv_largeur_-largeur_;
				id_env_.first+=largeur_;
				QList<QPair<int,int> > vois_;
				if(_plateau_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
					id_env_.first-=largeur_;
					bool suppr_=false;
					Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
					int nb_cols_aj_=dims_.first;
					for(int i=0;i<nb_cols_aj_;i++){
						env_->inserer_colonne(largeur_+i);
					}
					dims_=env_->dimensions();
					int nb_col_grille_=grille->nb_colonnes();
					if(id_env_.first+dims_.first>nb_col_grille_){
						grille->ajouter_colonnes(id_env_.first+dims_.first-nb_col_grille_);
					}
					for(int i=largeur_;i<nv_largeur_;i++){
						for(int j=0;j<dims_.second;j++){
							TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
							tuile_g_->maj_coords(QPair<int,int>(i,j));
							tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
						}
					}
					grille->repaint();
				}else{
					QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
				}
			}else if(largeur_>nv_largeur_){
				bool suppr_=false;
				Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
				int nb_cols_suppr_=largeur_-nv_largeur_;
				for(int i=0;i<nb_cols_suppr_;i++){
					env_->supprimer_colonne(nv_largeur_);
				}
				for(int i=nv_largeur_;i<largeur_;i++){
					for(int j=0;j<dims_.second;j++){
						TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
						tuile_g_->reinit();
					}
				}
				grille->repaint();
			}
		}
		delete dialogue_;
		dialogue_=NULL;
	}else if(_plateau_ligue_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_ligue_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_ligue_en_cours_->environnement(id_env_).dimensions();
		int largeur_=dims_.first;
		DialogueLargeur *dialogue_=new DialogueLargeur(langue,largeur_,this);
		dialogue_->exec();
		bool accepter_=dialogue_->result()==QDialog::Accepted;
		if(accepter_){
			int nv_largeur_=dialogue_->largeur_v();
			if(largeur_<nv_largeur_){
				dims_.first=nv_largeur_-largeur_;
				id_env_.first+=largeur_;
				QList<QPair<int,int> > vois_;
				if(_plateau_ligue_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
					id_env_.first-=largeur_;
					bool suppr_=false;
					EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
					int nb_cols_aj_=dims_.first;
					for(int i=0;i<nb_cols_aj_;i++){
						env_->inserer_colonne(largeur_+i);
					}
					dims_=env_->dimensions();
					int nb_col_grille_=grille->nb_colonnes();
					if(id_env_.first+dims_.first>nb_col_grille_){
						grille->ajouter_colonnes(id_env_.first+dims_.first-nb_col_grille_);
					}
					for(int i=largeur_;i<nv_largeur_;i++){
						for(int j=0;j<dims_.second;j++){
							TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
							tuile_g_->maj_coords(QPair<int,int>(i,j));
							tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
						}
					}
					grille->repaint();
				}else{
					QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
				}
			}else if(largeur_>nv_largeur_){
				bool suppr_=false;
				EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
				int nb_cols_suppr_=largeur_-nv_largeur_;
				for(int i=0;i<nb_cols_suppr_;i++){
					env_->supprimer_colonne(nv_largeur_);
				}
				for(int i=nv_largeur_;i<largeur_;i++){
					for(int j=0;j<dims_.second;j++){
						TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
						tuile_g_->reinit();
					}
				}
				grille->repaint();
			}
		}
		delete dialogue_;
		dialogue_=NULL;
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
	}
}

void Fenetre::insert_colonne_env(){
	if(_plateau_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_en_cours_->environnement(id_env_).dimensions();
		int largeur_=dims_.first;
		dims_.first=1;
		id_env_.first+=largeur_;
		QList<QPair<int,int> > vois_;
		if(_plateau_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
			id_env_.first-=largeur_;
			bool suppr_=false;
			Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
			env_->inserer_colonne(coordonnees_act.second.first);
			dims_=env_->dimensions();
			int nb_col_grille_=grille->nb_colonnes();
			if(id_env_.first+dims_.first>nb_col_grille_){
				grille->ajouter_colonnes(id_env_.first+dims_.first-nb_col_grille_);
			}
			for(int i=dims_.first-1;i>coordonnees_act.second.first;i--){
				for(int j=0;j<dims_.second;j++){
					TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
					TuileGraphique *tuile_g_2_=grille->tuile(i+id_env_.first-1,j+id_env_.second);
					QPair<int,int> coords_=tuile_g_2_->coords();
					tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first+1,coords_.second));
				}
			}
			for(int j=0;j<dims_.second;j++){
				TuileGraphique *tuile_g_=grille->tuile(coordonnees_act.second.first+id_env_.first,j+id_env_.second);
				tuile_g_->maj_coords(QPair<int,int>(coordonnees_act.second.first,j));
				tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
				tuile_g_->init();
			}
			//TODO mettre une colonne dépendant du type de l'environnement
			grille->repaint();
		}else{
			QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
		}
	}else if(_plateau_ligue_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_ligue_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_ligue_en_cours_->environnement(id_env_).dimensions();
		int largeur_=dims_.first;
		dims_.first=1;
		id_env_.first+=largeur_;
		QList<QPair<int,int> > vois_;
		if(_plateau_ligue_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
			id_env_.first-=largeur_;
			bool suppr_=false;
			EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
			env_->inserer_colonne(coordonnees_act.second.first);
			dims_=env_->dimensions();
			int nb_col_grille_=grille->nb_colonnes();
			if(id_env_.first+dims_.first>nb_col_grille_){
				grille->ajouter_colonnes(id_env_.first+dims_.first-nb_col_grille_);
			}
			for(int i=dims_.first-1;i>coordonnees_act.second.first;i--){
				for(int j=0;j<dims_.second;j++){
					TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
					TuileGraphique *tuile_g_2_=grille->tuile(i+id_env_.first-1,j+id_env_.second);
					QPair<int,int> coords_=tuile_g_2_->coords();
					tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first+1,coords_.second));
				}
			}
			for(int j=0;j<dims_.second;j++){
				TuileGraphique *tuile_g_=grille->tuile(coordonnees_act.second.first+id_env_.first,j+id_env_.second);
				tuile_g_->maj_coords(QPair<int,int>(coordonnees_act.second.first,j));
				tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
				tuile_g_->init();
			}
			//TODO mettre une colonne dépendant du type de l'environnement
			grille->repaint();
		}else{
			QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
		}
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
	}
}

void Fenetre::insert_supprimer_colonnes_env(){
	if(_plateau_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_en_cours_->environnement(id_env_).dimensions();
		int largeur_=dims_.first;
		DialogueLargeur *dialogue_=new DialogueLargeur(langue,largeur_,this);
		dialogue_->exec();
		bool accepter_=dialogue_->result()==QDialog::Accepted;
		if(accepter_){
			int nv_largeur_=dialogue_->largeur_v();
			if(largeur_<nv_largeur_){
				int diff_=nv_largeur_-largeur_;
				dims_.first=diff_;
				id_env_.first+=largeur_;
				QList<QPair<int,int> > vois_;
				if(_plateau_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
					id_env_.first-=largeur_;
					bool suppr_=false;
					Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
					int nb_cols_aj_=dims_.first;
					for(int i=0;i<nb_cols_aj_;i++){
						env_->inserer_colonne(coordonnees_act.second.first+i);
					}
					dims_=env_->dimensions();
					int nb_col_grille_=grille->nb_colonnes();
					if(id_env_.first+dims_.first>nb_col_grille_){
						grille->ajouter_colonnes(id_env_.first+dims_.first-nb_col_grille_);
					}
					for(int i=dims_.first-1;i>coordonnees_act.second.first+diff_-1;i--){
						for(int j=0;j<dims_.second;j++){
							TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
							TuileGraphique *tuile_g_2_=grille->tuile(i+id_env_.first-diff_,j+id_env_.second);
							QPair<int,int> coords_=tuile_g_2_->coords();
							tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first+diff_,coords_.second));
						}
					}
					for(int i=coordonnees_act.second.first+diff_-1;i>=coordonnees_act.second.first;i--){
						for(int j=0;j<dims_.second;j++){
							TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
							tuile_g_->maj_coords(QPair<int,int>(i,j));
							tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
							tuile_g_->init();
						}
					}
					grille->repaint();
				}else{
					QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
				}
			}else if(largeur_>nv_largeur_){
				int diff_=largeur_-nv_largeur_;
				bool suppr_=false;
				Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
				int nb_cols_suppr_=largeur_-nv_largeur_;
				for(int i=0;i<nb_cols_suppr_;i++){
					env_->supprimer_colonne(coordonnees_act.second.first);
				}
				dims_=env_->dimensions();
				for(int i=coordonnees_act.second.first;i<dims_.first;i++){
					for(int j=0;j<dims_.second;j++){
						TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
						TuileGraphique *tuile_g_2_=grille->tuile(i+id_env_.first+diff_,j+id_env_.second);
						QPair<int,int> coords_=tuile_g_2_->coords();
						tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first-diff_,coords_.second));
					}
				}
				for(int i=dims_.first;i<dims_.first+diff_;i++){
					for(int j=0;j<dims_.second;j++){
						TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
						tuile_g_->reinit();
					}
				}
				grille->repaint();
			}
		}
		delete dialogue_;
		dialogue_=NULL;
	}else if(_plateau_ligue_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_ligue_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_ligue_en_cours_->environnement(id_env_).dimensions();
		int largeur_=dims_.first;
		DialogueLargeur *dialogue_=new DialogueLargeur(langue,largeur_,this);
		dialogue_->exec();
		bool accepter_=dialogue_->result()==QDialog::Accepted;
		if(accepter_){
			int nv_largeur_=dialogue_->largeur_v();
			if(largeur_<nv_largeur_){
				int diff_=nv_largeur_-largeur_;
				dims_.first=diff_;
				id_env_.first+=largeur_;
				QList<QPair<int,int> > vois_;
				if(_plateau_ligue_en_cours_->peut_contenir_nv_env(id_env_,dims_,vois_)){
					id_env_.first-=largeur_;
					bool suppr_=false;
					EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
					int nb_cols_aj_=dims_.first;
					for(int i=0;i<nb_cols_aj_;i++){
						env_->inserer_colonne(coordonnees_act.second.first+i);
					}
					dims_=env_->dimensions();
					int nb_col_grille_=grille->nb_colonnes();
					if(id_env_.first+dims_.first>nb_col_grille_){
						grille->ajouter_colonnes(id_env_.first+dims_.first-nb_col_grille_);
					}
					for(int i=dims_.first-1;i>coordonnees_act.second.first+diff_-1;i--){
						for(int j=0;j<dims_.second;j++){
							TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
							TuileGraphique *tuile_g_2_=grille->tuile(i+id_env_.first-diff_,j+id_env_.second);
							QPair<int,int> coords_=tuile_g_2_->coords();
							tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first+diff_,coords_.second));
						}
					}
					for(int i=coordonnees_act.second.first+diff_-1;i>=coordonnees_act.second.first;i--){
						for(int j=0;j<dims_.second;j++){
							TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
							tuile_g_->maj_coords(QPair<int,int>(i,j));
							tuile_g_->maj_image(Import::_images_env_def_.valeur(*env_->type_env()));
							tuile_g_->init();
						}
					}
					grille->repaint();
				}else{
					QMessageBox::critical(this,traduire("ERREUR"),traduire("ENVIRONNEMENT_PRES"));
				}
			}else if(largeur_>nv_largeur_){
				int diff_=largeur_-nv_largeur_;
				bool suppr_=false;
				EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
				int nb_cols_suppr_=largeur_-nv_largeur_;
				for(int i=0;i<nb_cols_suppr_;i++){
					env_->supprimer_colonne(coordonnees_act.second.first);
				}
				dims_=env_->dimensions();
				for(int i=coordonnees_act.second.first;i<dims_.first;i++){
					for(int j=0;j<dims_.second;j++){
						TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
						TuileGraphique *tuile_g_2_=grille->tuile(i+id_env_.first+diff_,j+id_env_.second);
						QPair<int,int> coords_=tuile_g_2_->coords();
						tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first-diff_,coords_.second));
					}
				}
				for(int i=dims_.first;i<dims_.first+diff_;i++){
					for(int j=0;j<dims_.second;j++){
						TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
						tuile_g_->reinit();
					}
				}
				grille->repaint();
			}
		}
		delete dialogue_;
		dialogue_=NULL;
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
	}
}

void Fenetre::supprimer_colonne_env(){
	if(_plateau_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_en_cours_->environnement(id_env_).dimensions();
		bool suppr_=false;
		Environnement *env_=_plateau_en_cours_->environnement(id_env_,suppr_);
		env_->supprimer_colonne(coordonnees_act.second.first);
		for(int i=coordonnees_act.second.first;i<dims_.first-1;i++){
			for(int j=0;j<dims_.second;j++){
				TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
				TuileGraphique *tuile_g_2_=grille->tuile(i+id_env_.first+1,j+id_env_.second);
				QPair<int,int> coords_=tuile_g_2_->coords();
				tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first-1,coords_.second));
			}
		}
		for(int j=0;j<dims_.second;j++){
			TuileGraphique *tuile_g_=grille->tuile(dims_.first+id_env_.first-1,j+id_env_.second);
			tuile_g_->reinit();
		}
		grille->repaint();
	}else if(_plateau_ligue_en_cours_!=NULL){
		QPair<int,int> id_env_=coordonnees_act.first;
		if(!_plateau_ligue_en_cours_->coins_gauche().contains(id_env_)){
			QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
			return;
		}
		QPair<int,int> dims_=_plateau_ligue_en_cours_->environnement(id_env_).dimensions();
		bool suppr_=false;
		EnvironnementLigue *env_=_plateau_ligue_en_cours_->environnement(id_env_,suppr_);
		env_->supprimer_colonne(coordonnees_act.second.first);
		for(int i=coordonnees_act.second.first;i<dims_.first-1;i++){
			for(int j=0;j<dims_.second;j++){
				TuileGraphique *tuile_g_=grille->tuile(i+id_env_.first,j+id_env_.second);
				TuileGraphique *tuile_g_2_=grille->tuile(i+id_env_.first+1,j+id_env_.second);
				QPair<int,int> coords_=tuile_g_2_->coords();
				tuile_g_->affecter(tuile_g_2_,QPair<int,int>(coords_.first-1,coords_.second));
			}
		}
		for(int j=0;j<dims_.second;j++){
			TuileGraphique *tuile_g_=grille->tuile(dims_.first+id_env_.first-1,j+id_env_.second);
			tuile_g_->reinit();
		}
		grille->repaint();
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_EDITION"));
	}
}

void Fenetre::nouvelle_ligue(){
	if(_lieu_en_cours_!=NULL){
		_plateau_en_cours_=NULL;
		_lieu_en_cours_=NULL;
		ascenseur_panneau->takeWidget();
		panneau_editeur_ligue->show();
		ascenseur_panneau->setWidget(panneau_editeur_ligue);
		grille->table_rase();
		//TODO
	}
	QList<int> ligues_=donnees.ligues_c();
	if(ligues_.isEmpty()){
		donnees.ajouter_ligue(0,Ligue());
		ind_lieu=0;
		if(grille->nb_lignes()==0){
			grille->init();
		}
		Ligue *ligue_=donnees.ligue(ind_lieu);
		_ligue_en_cours_=ligue_;
		ind_plateau=0;
		_ligue_en_cours_->inserer_plateau(ind_plateau,PlateauLigue());
		_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
	}else{
		Utilitaire::trier<int>(ligues_,true);
		int ind_=ligues_[0];
		if(ind_>0){
			donnees.ajouter_ligue(0,Ligue());
			ind_lieu=0;
		}else{
			for(int i=1;i<ligues_.size();i++){
				if(ligues_[i]-1!=ligues_[i-1]){
					ind_=ligues_[i-1]+1;
					break;
				}
			}
			if(ligues_.last()==ligues_.size()-1){
				ind_=ligues_.size();
			}
			donnees.ajouter_ligue(ind_,Ligue());
			ind_lieu=ind_;
		}
		Ligue *ligue_=donnees.ligue(ind_lieu);
		_ligue_en_cours_=ligue_;
		ind_plateau=0;
		_ligue_en_cours_->inserer_plateau(ind_plateau,PlateauLigue());
		_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
	}
}

void Fenetre::selection_ligue(){
	if(donnees.ligues_c().isEmpty()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIGUE_DONNEES"));
		return;
	}
	DialogueSelectLigue *dial_=new DialogueSelectLigue(langue,false,this);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		int choix_=dial_->ligue_select();
		if(choix_>=0){
			if(choix_!=ind_lieu||_lieu_en_cours_!=NULL){//TODO attention au chargement, il faut y passer si le chargement vient d'etre fait
				Ligue *ligue_=donnees.ligue(choix_);
				if(ligue_->nb_plateaux()>0){
					ind_lieu_tmp=ind_lieu;
					ind_lieu=choix_;
					_ligue_en_cours_=ligue_;
					//select_plateau_ligue()
					DialogueSelectPlateau *dial_2_=new DialogueSelectPlateau(langue,false,this,false);;
					dial_2_->exec();
					bool accepte_=dial_2_->result()==QDialog::Accepted;
					if(!accepte_){
						delete dial_2_;
						dial_2_=NULL;
						if(_lieu_en_cours_!=NULL){
							_ligue_en_cours_=NULL;
						}
						return;
					}
					int choix_=dial_2_->plateau_select();
					if(choix_>=0&&(choix_!=ind_plateau||ind_lieu_tmp!=ind_lieu||_lieu_en_cours_!=NULL)){
						grille->table_rase();
						ind_plateau=dial_2_->plateau_select();
						_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
						if(_lieu_en_cours_!=NULL){
							_plateau_en_cours_=NULL;
							_lieu_en_cours_=NULL;
							ascenseur_panneau->takeWidget();
							panneau_editeur_ligue->show();
							ascenseur_panneau->setWidget(panneau_editeur_ligue);
							grille->table_rase();
							//TODO
						}
						maj_plateau_ligue();
						panneau_editeur_ligue->maj_dresseur();
					}
					delete dial_2_;
					dial_2_=NULL;

					ind_lieu_tmp=ind_lieu;
				}else{
					QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_PLATEAU_LIGUE"));
				}
			}else if(donnees.ligue(choix_)->nb_plateaux()==1){
				if(donnees.ligue(choix_)->plateau(0)->coins_gauche().isEmpty()){
					Ligue *ligue_=donnees.ligue(choix_);
					ind_lieu=choix_;
					_ligue_en_cours_=ligue_;
					ind_plateau=0;
					grille->table_rase();
					grille->repaint();
					if(_lieu_en_cours_!=NULL){
						_plateau_en_cours_=NULL;
						_lieu_en_cours_=NULL;
						ascenseur_panneau->takeWidget();
						panneau_editeur_ligue->show();
						ascenseur_panneau->setWidget(panneau_editeur_ligue);
						grille->table_rase();
						//TODO
					}
					PanneauDresseurLigue::_environnement_ligue_en_cours_=NULL;
					PanneauDresseurLigue::_tuile_en_cours_=NULL;
					_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
				}
			}
		}
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::suppression_ligue(){
	if(donnees.ligues_c().isEmpty()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIGUE_DONNEES"));
		return;
	}
	DialogueSelectLigue *dial_=new DialogueSelectLigue(langue,false,this);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		int choix_=dial_->ligue_select();
		if(choix_>=0&&choix_!=ind_lieu){
			donnees.supprimer_ligue(choix_);
		}
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::nouveau_plateau_ligue(){
	if(_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIGUE_EDITION"));
		return;
	}
	DialogueSelectPlateau *dial_=new DialogueSelectPlateau(langue,false,this,false,true);;
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(!accepte_){
		delete dial_;
		dial_=NULL;
		return;
	}
	grille->table_rase();
	ind_plateau=dial_->plateau_select();
	_ligue_en_cours_->inserer_plateau(ind_plateau,PlateauLigue());
	_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
	delete dial_;
	dial_=NULL;
}

void Fenetre::maj_plateau_ligue(){
	PlateauLigue *pl_=_plateau_ligue_en_cours_;
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
	QPair<int,int> coords_=*pl_->adr_coords_dresseur();
	if(coords_.first<grille->nb_colonnes()&&coords_.second<grille->nb_lignes()){
		TuileGraphique *tuile_g_=grille->tuile(coords_.first,coords_.second);
		DresseurLigue *dr_=pl_->adr_dresseur_ligue();
		if(Import::_dresseurs_micros_.cles().contains(*dr_->adr_nom_miniature())){
			tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*dr_->adr_nom_miniature()),*dr_->adr_orientation()));
		}
	}
	grille->repaint();
}

void Fenetre::select_plateau_ligue(){
//TODO ne supprimer le lien entre plateaux que si autre chose que le dresseur de ligue est affecté
	if(_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIGUE_EDITION"));
		return;
	}
	DialogueSelectPlateau *dial_=new DialogueSelectPlateau(langue,false,this,false);;
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(!accepte_){
		delete dial_;
		dial_=NULL;
		return;
	}
	int choix_=dial_->plateau_select();
	if(choix_>=0&&(choix_!=ind_plateau||ind_lieu_tmp!=ind_lieu)){
		grille->table_rase();
		ind_plateau=dial_->plateau_select();
		_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
		if(_lieu_en_cours_!=NULL){
			_plateau_en_cours_=NULL;
			_lieu_en_cours_=NULL;
			ascenseur_panneau->takeWidget();
			panneau_editeur_ligue->show();
			ascenseur_panneau->setWidget(panneau_editeur_ligue);
			grille->table_rase();
			//TODO
		}
		maj_plateau_ligue();
		panneau_editeur_ligue->maj_dresseur();
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::suppression_plateau_ligue(){
	if(_ligue_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIGUE_EDITION"));
		return;
	}
	DialogueSelectPlateau *dial_=new DialogueSelectPlateau(langue,false,this,false);;
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		int choix_=dial_->plateau_select();
		if(choix_>=0&&choix_!=ind_plateau){
			_ligue_en_cours_->supprimer_plateau_reindexer(choix_);
		}
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::lier_plateaux(){
	if(donnees.lieux_c().isEmpty()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIEU_DONNEES"));
		return;
	}
	bool ligue_en_cours_=_ligue_en_cours_!=NULL;
	DialogueLiaisons *dial_=new DialogueLiaisons(langue,this,DialogueLiaisons::LIEN_PLATEAU);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		foreach(int l,donnees.lieux_c()){
			Lieu *lieu_=donnees.lieu(l);
			foreach(int p,lieu_->plateaux_c()){
				Plateau *plateau_=lieu_->plateau(p);
				plateau_->aff_noms_images_liens();
				plateau_->aff_liens_vers_autres_plateau();
			}
		}
		typedef QPair<QPair<int,int>,QPair<int,int> > OrigineLien;
		foreach(OrigineLien o,_plateau_en_cours_->liaisons_vers_autres_plateaux()){
			TuileGraphique *tuile_g_=grille->tuile(o.second.first+o.first.first,o.second.second+o.first.second);
			tuile_g_->maj_lien(QPair<QImage,bool>(Import::_liens_.valeur(_plateau_en_cours_->image_origine_liaison(o)),true));
		}
		grille->repaint();
	}
	delete dial_;
	dial_=NULL;
	if(ligue_en_cours_){
		_ligue_en_cours_=donnees.ligue(ind_lieu);
		_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
	}else{
		_lieu_en_cours_=donnees.lieu(ind_lieu);
		_plateau_en_cours_=_lieu_en_cours_->plateau(ind_plateau);
		typedef QPair<QPair<int,int>,QPair<int,int> > OrigineLien;
		foreach(OrigineLien o,_plateau_en_cours_->liaisons_vers_autres_plateaux()){
			TuileGraphique *tuile_g_=grille->tuile(o.second.first+o.first.first,o.second.second+o.first.second);
			tuile_g_->maj_lien(QPair<QImage,bool>(Import::_liens_.valeur(_plateau_en_cours_->image_origine_liaison(o)),true));
		}
		grille->repaint();
	}
}

void Fenetre::lier_plateaux_ligue(){
	if(donnees.lieux_c().isEmpty()||donnees.ligues_c().isEmpty()){
		QString err_;
		if(donnees.lieux_c().isEmpty()){
			err_+=traduire("PAS_LIEU_DONNEES")+"\n";
		}
		if(donnees.ligues_c().isEmpty()){
			err_+=traduire("PAS_LIGUE_DONNEES");
		}
		QMessageBox::critical(this,traduire("ERREUR"),err_);
		return;
	}
	bool ligue_en_cours_=_ligue_en_cours_!=NULL;
	DialogueLiaisons *dial_=new DialogueLiaisons(langue,this,DialogueLiaisons::LIEN_PLATEAU_LIGUE);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		HashMap<QPair<int,int>,QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > > liens_=dial_->maj_lien_vers_plateau_suivant();
		HashMap<int,Coordonnees> acces_=dial_->maj_acces();
		HashMap<int,Coordonnees> origine_=dial_->maj_origine();
		foreach(int l,donnees.ligues_c()){
			Ligue *ligue_=donnees.ligue(l);
			*ligue_->adr_acces()=acces_.valeur(l);
			*ligue_->adr_origine()=origine_.valeur(l);
			int nb_pl_l_=ligue_->nb_plateaux();
			for(int p=0;p<nb_pl_l_;p++){
				PlateauLigue *plateau_=ligue_->plateau(p);
				*plateau_->adr_orig_lien_vers_plateau_suivant()=liens_.valeur(QPair<int,int>(l,p)).first;
				*plateau_->adr_dest_lien_vers_plateau_suivant()=liens_.valeur(QPair<int,int>(l,p)).second;
			}
		}
	}
	delete dial_;
	dial_=NULL;
	if(ligue_en_cours_){
		_ligue_en_cours_=donnees.ligue(ind_lieu);
		_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
	}else{
		_lieu_en_cours_=donnees.lieu(ind_lieu);
		_plateau_en_cours_=_lieu_en_cours_->plateau(ind_plateau);
	}
}

void Fenetre::souder_lieux(){
	if(donnees.lieux_c().isEmpty()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIEU_DONNEES"));
		return;
	}
	bool ligue_en_cours_=_ligue_en_cours_!=NULL;
	DialogueLiaisons *dial_=new DialogueLiaisons(langue,this,DialogueLiaisons::LIEUX_A_SOUDER);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		foreach(int l,donnees.lieux_c()){
			Lieu *lieu_=donnees.lieu(l);
			lieu_->aff_liens_vers_autres_lieux();
		}
	}
	delete dial_;
	dial_=NULL;
	if(ligue_en_cours_){
		_ligue_en_cours_=donnees.ligue(ind_lieu);
		_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
	}else{
		_lieu_en_cours_=donnees.lieu(ind_lieu);
		_plateau_en_cours_=_lieu_en_cours_->plateau(ind_plateau);
	}
}


void Fenetre::charger_rapidement(){
	if(nom_fichier_flux==""){
		return;
	}
	anciennes_donnees=donnees;
	donnees.charger(nom_fichier_flux);
	QMessageBox::information(this,traduire("CHARGEMENT_FINI"),nom_fichier_flux);
}

void Fenetre::charger(){
	/**
	TODO demande de continuer
	if(anciennes_donnees!=donnees){
		//demande de continuer
	}
	*/
	DialogueFichiers *dialogue_=new DialogueFichiers(rep_travail,langue,DialogueFichiers::CHARGER,this);
	dialogue_->exec();
	QString fichier_=dialogue_->nom_fic();
	delete dialogue_;
	dialogue_=NULL;
	if(fichier_==""){
		return;
	}
	nom_fichier_flux=fichier_;
	QStringList chemin_=nom_fichier_flux.split(QDir::separator());
	rep_travail=QStringList(chemin_.mid(0,chemin_.size()-1)).join(QDir::separator());
	try{;
		charger_rapidement();
	}catch(...){
		donnees=anciennes_donnees;
		PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
		QMessageBox::critical(this,traduire("ECH_CHARGEMENT"),nom_fichier_flux);
		return;
	}
	if(grille->nb_lignes()==0){
		grille->init();
	}
	DialogueSelectLieuLigue *dial_=new DialogueSelectLieuLigue(langue,this);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		QPair<int,bool> retour_dial_=dial_->lieu_ligue_select();
		delete dial_;
		dial_=NULL;
		if(retour_dial_.second){
			//ligue
			int choix_=retour_dial_.first;
			if(choix_>=0){
				Ligue *ligue_=donnees.ligue(choix_);
				ind_lieu_tmp=ind_lieu;
				ind_lieu=choix_;
				if(ligue_->nb_plateaux()>0){
					_ligue_en_cours_=ligue_;
					DialogueSelectPlateau *dial_2_=new DialogueSelectPlateau(langue,false,this,false);
					dial_2_->exec();
					bool accepte_=dial_2_->result()==QDialog::Accepted;
					if(!accepte_){
						delete dial_2_;
						dial_2_=NULL;
						donnees=anciennes_donnees;
						PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
						_ligue_en_cours_=donnees.ligue(ind_lieu_tmp);
						_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
						return;
					}
					int choix_2_=dial_2_->plateau_select();
					if(choix_2_<0){
						delete dial_2_;
						dial_2_=NULL;
						donnees=anciennes_donnees;
						PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
						_ligue_en_cours_=donnees.ligue(ind_lieu_tmp);
						_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
						return;
					}
					ind_plateau=choix_2_;
					_ligue_en_cours_=donnees.ligue(choix_);
					PanneauDresseurLigue::_environnement_ligue_en_cours_=NULL;
					PanneauDresseurLigue::_tuile_en_cours_=NULL;
					_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(choix_2_);
					_lieu_en_cours_=NULL;
					_plateau_en_cours_=NULL;
					ascenseur_panneau->takeWidget();
					panneau_editeur_ligue->show();
					ascenseur_panneau->setWidget(panneau_editeur_ligue);
					maj_plateau_ligue();
					panneau_editeur_ligue->maj_dresseur();
					anciennes_donnees=donnees;
					delete dial_2_;
					dial_2_=NULL;
				}
			}else{
				donnees=anciennes_donnees;
				PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
				if(!donnees.ligues_c().isEmpty()){
					_ligue_en_cours_=donnees.ligue(ind_lieu);
					_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
				}
				return;
			}
		}else{
			//lieu
			int choix_=retour_dial_.first;
			if(choix_>=0){
				Lieu *lieu_=donnees.lieu(choix_);
				ind_lieu_tmp=ind_lieu;
				ind_lieu=choix_;
				if(!lieu_->plateaux_c().isEmpty()){
					_lieu_en_cours_=lieu_;
					DialogueSelectPlateau *dial_2_=new DialogueSelectPlateau(langue,false,this,true);
					dial_2_->exec();
					bool accepte_=dial_2_->result()==QDialog::Accepted;
					if(!accepte_){
						delete dial_2_;
						dial_2_=NULL;
						donnees=anciennes_donnees;
						PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
						_lieu_en_cours_=donnees.lieu(ind_lieu_tmp);
						_plateau_en_cours_=_lieu_en_cours_->plateau(ind_plateau);
						return;
					}
					int choix_2_=dial_2_->plateau_select();
					if(choix_2_<0){
						delete dial_2_;
						dial_2_=NULL;
						donnees=anciennes_donnees;
						PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
						_lieu_en_cours_=donnees.lieu(ind_lieu_tmp);
						_plateau_en_cours_=_lieu_en_cours_->plateau(ind_plateau);
						return;
					}
					ind_plateau=choix_2_;
					_lieu_en_cours_=donnees.lieu(choix_);
					PanneauEditerEnv::_environnement_en_cours_=NULL;
					PanneauEditerEnv::_tuile_en_cours_=NULL;
					_plateau_en_cours_=_lieu_en_cours_->plateau(choix_2_);
					_ligue_en_cours_=NULL;
					_plateau_ligue_en_cours_=NULL;
					ascenseur_panneau->takeWidget();
					panneau_editeur_env->show();
					ascenseur_panneau->setWidget(panneau_editeur_env);
					maj_plateau();
					anciennes_donnees=donnees;
					PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
					delete dial_2_;
					dial_2_=NULL;
				}
			}else{
				donnees=anciennes_donnees;
				PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
				if(!donnees.lieux_c().isEmpty()){
					_lieu_en_cours_=donnees.lieu(ind_lieu);
					_plateau_en_cours_=_lieu_en_cours_->plateau(ind_plateau);
				}
				return;
			}
		}
	}else{
		donnees=anciennes_donnees;
		PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
		if(!donnees.lieux_c().isEmpty()){
			_lieu_en_cours_=donnees.lieu(ind_lieu);
			_plateau_en_cours_=_lieu_en_cours_->plateau(ind_plateau);
		}
		delete dial_;
		dial_=NULL;
		return;
	}
	delete dial_;
	dial_=NULL;
	//TODO attention partie graphique
}

void Fenetre::sauvegarder_rapidement(){
	if(nom_fichier_flux==""){
		return;
	}
	donnees.sauvegarder(nom_fichier_flux);
	QMessageBox::information(this,traduire("SAUVEGARDE_FINIE"),nom_fichier_flux);
	anciennes_donnees=donnees;
}

void Fenetre::sauvegarder(){
	if(donnees.lieux_c().isEmpty()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIEU_DONNEES"));
		return;
	}
	DialogueFichiers *dialogue_=new DialogueFichiers(rep_travail,langue,DialogueFichiers::SAUVEGARDER,this);
	dialogue_->exec();
	QString fichier_=dialogue_->nom_fic();
	delete dialogue_;
	dialogue_=NULL;
	if(fichier_!=""){
		nom_fichier_flux=fichier_;
		QStringList chemin_=nom_fichier_flux.split(QDir::separator());
		rep_travail=QStringList(chemin_.mid(0,chemin_.size()-1)).join(QDir::separator());
		sauvegarder_rapidement();
	}
	//Appel de sauvegarder_rapidement
}

void Fenetre::exporter(){
	/**TODO test de validation*/
	/*if(nom_fichier_export==""){
		return
	}*/
#ifdef QT_NO_DEBUG
	if(!donnees.est_valide()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("DONNEES_INV"));
		return;
	}
#endif
	DialogueFichiers *dialogue_=new DialogueFichiers(rep_export,langue,DialogueFichiers::EXPORTER,this);
	dialogue_->exec();
	QString fichier_=dialogue_->nom_fic();
	delete dialogue_;
	dialogue_=NULL;
	if(fichier_!=""){
		//nom_fichier_export=fichier_
		QStringList chemin_=fichier_.split(QDir::separator());
		rep_export=QStringList(chemin_.mid(0,chemin_.size()-1)).join(QDir::separator());
		Utilitaire::ecrire_fichier(fichier_,donnees.exporter());
		QMessageBox::information(this,traduire("EXPORT_FINI"),fichier_);
	}
}

void Fenetre::valider(){
	if(!donnees.est_valide()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("DONNEES_INV"));
	}else{
		QMessageBox::information(this,traduire("SUCCES"),traduire("DONNEES_VAL"));
	}
}

void Fenetre::ajouter_pk_marche(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar();
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon(i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::DEPLACEMENT,pres_leg_);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		PanneauEditerEnv::_environnement_en_cours_->inserer_pk_appar(dial_->nv_pk(),nb_pk_appar_);
		panneau_editeur_env->maj_appar_per();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::inserer_pk_marche(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar();
	if(panneau_editeur_env->ligne_act_per()<=-1||panneau_editeur_env->ligne_act_per()>nb_pk_appar_){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_INSERT_INV"));
		return;
	}
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon(i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::DEPLACEMENT,pres_leg_);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		PanneauEditerEnv::_environnement_en_cours_->inserer_pk_appar(dial_->nv_pk(),panneau_editeur_env->ligne_act_per());
		panneau_editeur_env->maj_appar_per();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::editer_pk_marche(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar();
	if(panneau_editeur_env->ligne_act_per()<=-1||panneau_editeur_env->ligne_act_per()>nb_pk_appar_){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_EDIT_INV"));
		return;
	}
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon(i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::DEPLACEMENT,pres_leg_);
	dial_->maj_pk_edite(PanneauEditerEnv::_environnement_en_cours_->pokemon(panneau_editeur_env->ligne_act_per()));
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		*PanneauEditerEnv::_environnement_en_cours_->pokemon(panneau_editeur_env->ligne_act_per())=dial_->nv_pk();
		panneau_editeur_env->maj_appar_per();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::supprimer_pk_marche(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	if(panneau_editeur_env->ligne_act_per()>-1&&panneau_editeur_env->ligne_act_per()<PanneauEditerEnv::_environnement_en_cours_->periode_appar()){
		PanneauEditerEnv::_environnement_en_cours_->supprimer_pk_appar(panneau_editeur_env->ligne_act_per());
		panneau_editeur_env->maj_appar_per();
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_SUPPR_INV"));
	}
}

void Fenetre::ajouter_pk_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_canne_);
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_canne_,i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::CANNE,pres_leg_);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		PanneauEditerEnv::_environnement_en_cours_->inserer_pk_appar_peche(Environnement::_canne_,dial_->nv_pk(),nb_pk_appar_);
		panneau_editeur_env->maj_appar_canne();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::inserer_pk_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_canne_);
	if(panneau_editeur_env->ligne_act_canne()<=-1||panneau_editeur_env->ligne_act_canne()>nb_pk_appar_){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_INSERT_INV"));
		return;
	}
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_canne_,i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::CANNE,pres_leg_);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		PanneauEditerEnv::_environnement_en_cours_->inserer_pk_appar_peche(Environnement::_canne_,dial_->nv_pk(),panneau_editeur_env->ligne_act_canne());
		panneau_editeur_env->maj_appar_canne();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::editer_pk_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_canne_);
	if(panneau_editeur_env->ligne_act_canne()<=-1||panneau_editeur_env->ligne_act_canne()>nb_pk_appar_){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_EDIT_INV"));
		return;
	}
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_canne_,i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::CANNE,pres_leg_);
	dial_->maj_pk_edite(PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_canne_,panneau_editeur_env->ligne_act_canne()));
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_canne_,panneau_editeur_env->ligne_act_canne())=dial_->nv_pk();
		panneau_editeur_env->maj_appar_canne();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::supprimer_pk_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	if(panneau_editeur_env->ligne_act_canne()>-1&&panneau_editeur_env->ligne_act_canne()<PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_canne_)){
		PanneauEditerEnv::_environnement_en_cours_->supprimer_pk_appar_peche(Environnement::_canne_,panneau_editeur_env->ligne_act_canne());
		panneau_editeur_env->maj_appar_canne();
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_SUPPR_INV"));
	}
}

void Fenetre::ajouter_pk_super_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_super_canne_);
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_super_canne_,i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::SUPER_CANNE,pres_leg_);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		PanneauEditerEnv::_environnement_en_cours_->inserer_pk_appar_peche(Environnement::_super_canne_,dial_->nv_pk(),nb_pk_appar_);
		panneau_editeur_env->maj_appar_super_canne();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::inserer_pk_super_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_super_canne_);
	if(panneau_editeur_env->ligne_act_super_canne()<=-1||panneau_editeur_env->ligne_act_super_canne()>nb_pk_appar_){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_INSERT_INV"));
		return;
	}
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_super_canne_,i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::SUPER_CANNE,pres_leg_);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		PanneauEditerEnv::_environnement_en_cours_->inserer_pk_appar_peche(Environnement::_super_canne_,dial_->nv_pk(),panneau_editeur_env->ligne_act_super_canne());
		panneau_editeur_env->maj_appar_super_canne();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::editer_pk_super_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_super_canne_);
	if(panneau_editeur_env->ligne_act_super_canne()<=-1||panneau_editeur_env->ligne_act_super_canne()>nb_pk_appar_){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_EDIT_INV"));
		return;
	}
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_super_canne_,i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::SUPER_CANNE,pres_leg_);
	dial_->maj_pk_edite(PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_super_canne_,panneau_editeur_env->ligne_act_super_canne()));
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_super_canne_,panneau_editeur_env->ligne_act_super_canne())=dial_->nv_pk();
		panneau_editeur_env->maj_appar_super_canne();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::supprimer_pk_super_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	if(panneau_editeur_env->ligne_act_super_canne()>-1&&panneau_editeur_env->ligne_act_super_canne()<PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_super_canne_)){
		PanneauEditerEnv::_environnement_en_cours_->supprimer_pk_appar_peche(Environnement::_super_canne_,panneau_editeur_env->ligne_act_super_canne());
		panneau_editeur_env->maj_appar_super_canne();
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_SUPPR_INV"));
	}
}

void Fenetre::ajouter_pk_mega_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_mega_canne_);
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_mega_canne_,i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::SUPER_CANNE,pres_leg_);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		PanneauEditerEnv::_environnement_en_cours_->inserer_pk_appar_peche(Environnement::_mega_canne_,dial_->nv_pk(),nb_pk_appar_);
		panneau_editeur_env->maj_appar_mega_canne();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::inserer_pk_mega_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_mega_canne_);
	if(panneau_editeur_env->ligne_act_mega_canne()<=-1||panneau_editeur_env->ligne_act_mega_canne()>nb_pk_appar_){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_INSERT_INV"));
		return;
	}
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_mega_canne_,i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::SUPER_CANNE,pres_leg_);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		PanneauEditerEnv::_environnement_en_cours_->inserer_pk_appar_peche(Environnement::_mega_canne_,dial_->nv_pk(),panneau_editeur_env->ligne_act_mega_canne());
		panneau_editeur_env->maj_appar_mega_canne();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::editer_pk_mega_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	bool pres_leg_=false;
	int nb_pk_appar_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_mega_canne_);
	if(panneau_editeur_env->ligne_act_mega_canne()<=-1||panneau_editeur_env->ligne_act_mega_canne()>nb_pk_appar_){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_EDIT_INV"));
		return;
	}
	for(int i=0;i<nb_pk_appar_;i++){
		FichePokemon *fiche_pk_=Import::_pokedex_.valeur(*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_mega_canne_,i)->adr_nom());
		if(fiche_pk_->rep_genr()=="<LEG>"){
			pres_leg_=true;
			break;
		}
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_SAUVAGE,this,DialoguePkCombat::SUPER_CANNE,pres_leg_);
	dial_->maj_pk_edite(PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_mega_canne_,panneau_editeur_env->ligne_act_mega_canne()));
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		*PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_mega_canne_,panneau_editeur_env->ligne_act_mega_canne())=dial_->nv_pk();
		panneau_editeur_env->maj_appar_mega_canne();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::supprimer_pk_mega_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	if(panneau_editeur_env->ligne_act_mega_canne()>-1&&panneau_editeur_env->ligne_act_mega_canne()<PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_mega_canne_)){
		PanneauEditerEnv::_environnement_en_cours_->supprimer_pk_appar_peche(Environnement::_mega_canne_,panneau_editeur_env->ligne_act_mega_canne());
		panneau_editeur_env->maj_appar_mega_canne();
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_SUPPR_INV"));
	}
}

void Fenetre::maj_personnage(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	DialoguePersonnage *dial_=new DialoguePersonnage(langue,this);
	if(PanneauEditerEnv::_environnement_en_cours_->coords_autres_persos().contains(coordonnees_act.second)){
		int choix_=DialoguePersonnage::RIEN;
		bool suppr_=false;
		if(PanneauEditerEnv::_environnement_en_cours_->contient_centre_poke(coordonnees_act.second)){
			choix_=DialoguePersonnage::SOIN_PK;
		}else if(PanneauEditerEnv::_environnement_en_cours_->contient_pension(coordonnees_act.second)){
			choix_=DialoguePersonnage::PENSION;
		}else if(PanneauEditerEnv::_environnement_en_cours_->contient_move_tutor(coordonnees_act.second)){
			choix_=DialoguePersonnage::MOVE_TUTORS;
		}else if(PanneauEditerEnv::_environnement_en_cours_->contient_lieu_fossile(coordonnees_act.second)){
			choix_=DialoguePersonnage::LIEU_VIVRE;
		}else if(PanneauEditerEnv::_environnement_en_cours_->coords_achat_objets().contains(coordonnees_act.second)){
			choix_=DialoguePersonnage::ACHAT_OBJS;
			dial_->editer_achat_objets(PanneauEditerEnv::_environnement_en_cours_->achat_objets(coordonnees_act.second));
		}else if(PanneauEditerEnv::_environnement_en_cours_->coords_achat_ct().contains(coordonnees_act.second)){
			choix_=DialoguePersonnage::ACHAT_CTS;
			dial_->editer_achat_ct(PanneauEditerEnv::_environnement_en_cours_->achat_ct(coordonnees_act.second));
		}else if(PanneauEditerEnv::_environnement_en_cours_->coords_don_cs().contains(coordonnees_act.second)){
			choix_=DialoguePersonnage::DON_CS;
			dial_->editer_don_cs(PanneauEditerEnv::_environnement_en_cours_->don_cs(coordonnees_act.second));
		}else if(PanneauEditerEnv::_environnement_en_cours_->coords_lieux_dons_pokemon().contains(coordonnees_act.second)){
			choix_=DialoguePersonnage::DON_PK;
			dial_->editer_don_pk(*PanneauEditerEnv::_environnement_en_cours_->don_pokemon(coordonnees_act.second));
		}else if(PanneauEditerEnv::_environnement_en_cours_->coords_objets_donnes_ramasses().contains(coordonnees_act.second)){
			choix_=DialoguePersonnage::DON_OBJS;
			dial_->editer_don_obj(*PanneauEditerEnv::_environnement_en_cours_->objet_donne_ramasse(coordonnees_act.second));
		}
		dial_->maj_personnage(QPair<int,Personnage*>(choix_,PanneauEditerEnv::_environnement_en_cours_->personnage(coordonnees_act.second,suppr_)));
	}
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		QPair<int,Personnage> perso_=dial_->nv_personnage();
		PanneauEditerEnv::_environnement_en_cours_->modifier_personnage(coordonnees_act.second,perso_.second);
		if(perso_.first==DialoguePersonnage::SOIN_PK){
			PanneauEditerEnv::_environnement_en_cours_->ajouter_centre_poke(coordonnees_act.second);
		}else if(perso_.first==DialoguePersonnage::PENSION){
			PanneauEditerEnv::_environnement_en_cours_->ajouter_pension(coordonnees_act.second);
		}else if(perso_.first==DialoguePersonnage::MOVE_TUTORS){
			PanneauEditerEnv::_environnement_en_cours_->ajouter_move_tutor(coordonnees_act.second);
		}else if(perso_.first==DialoguePersonnage::LIEU_VIVRE){
			PanneauEditerEnv::_environnement_en_cours_->ajouter_lieu_faire_revivre_fossile(coordonnees_act.second);
		}else if(perso_.first==DialoguePersonnage::ACHAT_OBJS){
			PanneauEditerEnv::_environnement_en_cours_->ajouter_achat_objets(coordonnees_act.second,dial_->nv_achat_objets());
		}else if(perso_.first==DialoguePersonnage::ACHAT_CTS){
			PanneauEditerEnv::_environnement_en_cours_->ajouter_achat_ct(coordonnees_act.second,dial_->nv_achat_ct());
		}else if(perso_.first==DialoguePersonnage::DON_CS){
			PanneauEditerEnv::_environnement_en_cours_->ajouter_don_cs(coordonnees_act.second,dial_->nv_don_cs());
		}else if(perso_.first==DialoguePersonnage::DON_PK){
			PanneauEditerEnv::_environnement_en_cours_->ajouter_lieu_dons_pokemon(coordonnees_act.second,dial_->nv_don_pk());
		}else if(perso_.first==DialoguePersonnage::DON_OBJS){
			PanneauEditerEnv::_environnement_en_cours_->ajouter_objet_donne_ramasse(coordonnees_act.second,dial_->nv_don_obj());
		}
		Coordonnees c_;
		*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
		*c_.adr_environnement()=coordonnees_act.first;
		*c_.adr_tuile()=coordonnees_act.second	;
		donnees.supprimer_champions_battre(c_);
		TuileGraphique *tuile_g_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
		tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*perso_.second.adr_nom_miniature()),*perso_.second.adr_orientation()));
		tuile_g_->maj_obst(QPair<QImage,bool>(QImage(),false));
		grille->repaint();
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::maj_dresseur(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	DialogueDresseur *dial_=new DialogueDresseur(langue,false,this);
	if(PanneauEditerEnv::_environnement_en_cours_->coords_dresseurs().contains(coordonnees_act.second)){
		bool suppr_=false;
		dial_->maj_dresseur(PanneauEditerEnv::_environnement_en_cours_->dresseur(coordonnees_act.second,suppr_));
	}
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		PanneauEditerEnv::_environnement_en_cours_->modifier_dresseur(coordonnees_act.second,dial_->nv_dresseur());
		Coordonnees c_;
		*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
		*c_.adr_environnement()=coordonnees_act.first;
		*c_.adr_tuile()=coordonnees_act.second	;
		donnees.supprimer_champions_battre(c_);
		TuileGraphique *tuile_g_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
		tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*dial_->nv_dresseur().adr_nom_miniature()),*dial_->nv_dresseur().adr_orientation()));
		tuile_g_->maj_obst(QPair<QImage,bool>(QImage(),false));
		grille->repaint();
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::maj_champion(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	DialogueDresseur *dial_=new DialogueDresseur(langue,true,this);
	if(PanneauEditerEnv::_environnement_en_cours_->coords_champions().contains(coordonnees_act.second)){
		bool suppr_=false;
		dial_->maj_champion(PanneauEditerEnv::_environnement_en_cours_->champion(coordonnees_act.second,suppr_));
	}
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		Champion ch_=dial_->nv_champion();
		PanneauEditerEnv::_environnement_en_cours_->modifier_champion(coordonnees_act.second,ch_);
		Coordonnees c_;
		*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
		*c_.adr_environnement()=coordonnees_act.first;
		*c_.adr_tuile()=coordonnees_act.second;
		donnees.maj_champions_battre(c_,ch_);
		TuileGraphique *tuile_g_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
		tuile_g_->maj_perso(QPair<QImage,QPair<int,int> >(Import::_dresseurs_micros_.valeur(*ch_.adr_nom_miniature()),*ch_.adr_orientation()));
		tuile_g_->maj_obst(QPair<QImage,bool>(QImage(),false));
		grille->repaint();
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::editer_pk_leg(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	if(PanneauEditerEnv::_environnement_en_cours_->coords_pokemon_legendaire().contains(coordonnees_act.second)){
		bool suppr_=false;
		Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_legendaire(coordonnees_act.second,suppr_);
		DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_LEG_FIXE,this,DialoguePkCombat::RIEN);
		dial_->maj_pk_edite(pk_);
		dial_->exec();
		bool rejet_=dial_->rejete();
		if(!rejet_){
			Pokemon nv_pk_=dial_->nv_pk();
			PanneauEditerEnv::_environnement_en_cours_->modifier_pokemon_legendaire(coordonnees_act.second,nv_pk_);
			Coordonnees c_;
			*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
			*c_.adr_environnement()=coordonnees_act.first;
			*c_.adr_tuile()=coordonnees_act.second	;
			donnees.supprimer_champions_battre(c_);
			QPair<int,int> coords_abs_;
			coords_abs_.first=coordonnees_act.second.first+coordonnees_act.first.first;
			coords_abs_.second=coordonnees_act.second.second+coordonnees_act.first.second;
			TuileGraphique *tuile_=grille->tuile(coords_abs_.first,coords_abs_.second);
			int num_pk_=Import::_pokedex_.valeur(*nv_pk_.adr_nom())->num();
			tuile_->maj_obst(QPair<QImage,bool>(Import::_miniatures_.valeur(num_pk_),true));
			tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
			grille->repaint();
		}
		delete dial_;
		dial_=NULL;
	}else{
		DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_LEG_FIXE,this,DialoguePkCombat::RIEN);
		dial_->exec();
		bool rejet_=dial_->rejete();
		if(!rejet_){
			Pokemon nv_pk_=dial_->nv_pk();
			PanneauEditerEnv::_environnement_en_cours_->modifier_pokemon_legendaire(coordonnees_act.second,nv_pk_);
			Coordonnees c_;
			*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
			*c_.adr_environnement()=coordonnees_act.first;
			*c_.adr_tuile()=coordonnees_act.second	;
			donnees.supprimer_champions_battre(c_);
			QPair<int,int> coords_abs_;
			coords_abs_.first=coordonnees_act.second.first+coordonnees_act.first.first;
			coords_abs_.second=coordonnees_act.second.second+coordonnees_act.first.second;
			TuileGraphique *tuile_=grille->tuile(coords_abs_.first,coords_abs_.second);
			int num_pk_=Import::_pokedex_.valeur(*nv_pk_.adr_nom())->num();
			tuile_->maj_obst(QPair<QImage,bool>(Import::_miniatures_.valeur(num_pk_),true));
			tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
			grille->repaint();
		}
		delete dial_;
		dial_=NULL;
	}
}

void Fenetre::editer_pk_don(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	if(PanneauEditerEnv::_environnement_en_cours_->coords_lieux_dons_pokemon().contains(coordonnees_act.second)){
		Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->don_pokemon(coordonnees_act.second);
		DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_DONNE,this,DialoguePkCombat::RIEN);
		dial_->maj_pk_edite(pk_);
		dial_->exec();
		bool rejet_=dial_->rejete();
		if(!rejet_){
			Pokemon nv_pk_=dial_->nv_pk();
			PanneauEditerEnv::_environnement_en_cours_->ajouter_lieu_dons_pokemon(coordonnees_act.second,nv_pk_);
			Coordonnees c_;
			*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
			*c_.adr_environnement()=coordonnees_act.first;
			*c_.adr_tuile()=coordonnees_act.second	;
			donnees.supprimer_champions_battre(c_);
			QPair<int,int> coords_abs_;
			coords_abs_.first=coordonnees_act.second.first+coordonnees_act.first.first;
			coords_abs_.second=coordonnees_act.second.second+coordonnees_act.first.second;
			TuileGraphique *tuile_=grille->tuile(coords_abs_.first,coords_abs_.second);
			tuile_->maj_obst(QPair<QImage,bool>(Import::_pk_trouve_,true));
			tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
			grille->repaint();
			//
		}
		delete dial_;
		dial_=NULL;
	}else{
		DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_DONNE,this,DialoguePkCombat::RIEN);
		dial_->exec();
		bool rejet_=dial_->rejete();
		if(!rejet_){
			Pokemon nv_pk_=dial_->nv_pk();
			PanneauEditerEnv::_environnement_en_cours_->ajouter_lieu_dons_pokemon(coordonnees_act.second,nv_pk_);
			Coordonnees c_;
			*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
			*c_.adr_environnement()=coordonnees_act.first;
			*c_.adr_tuile()=coordonnees_act.second	;
			donnees.supprimer_champions_battre(c_);
			QPair<int,int> coords_abs_;
			coords_abs_.first=coordonnees_act.second.first+coordonnees_act.first.first;
			coords_abs_.second=coordonnees_act.second.second+coordonnees_act.first.second;
			TuileGraphique *tuile_=grille->tuile(coords_abs_.first,coords_abs_.second);
			tuile_->maj_obst(QPair<QImage,bool>(Import::_pk_trouve_,true));
			tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
			grille->repaint();
		}
		delete dial_;
		dial_=NULL;
	}
}

void Fenetre::editer_objet(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	DialogueObjet *dial_=new DialogueObjet(langue,this);
	if(PanneauEditerEnv::_environnement_en_cours_->coords_objets().contains(coordonnees_act.second)){
		bool suppr_=false;
		dial_->editer_objet(*PanneauEditerEnv::_environnement_en_cours_->objet(coordonnees_act.second,suppr_));
	}
	dial_->exec();
	QString nv_obj_=dial_->nv_obj();
	bool accepter_=dial_->result()==QDialog::Accepted;
	if(nv_obj_!=""&&accepter_){
		PanneauEditerEnv::_environnement_en_cours_->modifier_objet(coordonnees_act.second,nv_obj_);
		Coordonnees c_;
		*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
		*c_.adr_environnement()=coordonnees_act.first;
		*c_.adr_tuile()=coordonnees_act.second	;
		donnees.supprimer_champions_battre(c_);
		if(!PanneauEditerEnv::_environnement_en_cours_->coords_autres_persos().contains(coordonnees_act.second)){
			QPair<int,int> coords_abs_;
			coords_abs_.first=coordonnees_act.second.first+coordonnees_act.first.first;
			coords_abs_.second=coordonnees_act.second.second+coordonnees_act.first.second;
			TuileGraphique *tuile_=grille->tuile(coords_abs_.first,coords_abs_.second);
			tuile_->maj_obst(QPair<QImage,bool>(Import::_images_objets_.valeur(nv_obj_),true));
			grille->repaint();
		}
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::confirmer_echange_pk_boites(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	int rep_=QMessageBox::question(this,traduire("CONFIRM_ECH_PK"),traduire("CONTINUER_INT"),QMessageBox::Yes|QMessageBox::No);
	if(rep_==QMessageBox::Yes){
		PanneauEditerEnv::_environnement_en_cours_->ajouter_echange_poke_boites(coordonnees_act.second);
		Coordonnees c_;
		*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
		*c_.adr_environnement()=coordonnees_act.first;
		*c_.adr_tuile()=coordonnees_act.second	;
		donnees.supprimer_champions_battre(c_);
	}
}

void Fenetre::confirmer_obstacle_arbre(const QString& _nv_obst){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	if(Import::_arbres_.cles().size()==1){
		int rep_=QMessageBox::question(this,traduire("CONFIRM_MAJ_ARBRE"),traduire("CONTINUER_INT"),QMessageBox::Yes|QMessageBox::No);
		if(rep_==QMessageBox::Yes){
			QPair<QString,int> *nom_type_obst_=PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst();
			nom_type_obst_->first=Import::_arbres_.cles()[0];
			nom_type_obst_->second=Tuile::ARBRE;
			Coordonnees c_;
			*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
			*c_.adr_environnement()=coordonnees_act.first;
			*c_.adr_tuile()=coordonnees_act.second	;
			donnees.supprimer_champions_battre(c_);
			TuileGraphique *tuile_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
			tuile_->maj_obst(QPair<QImage,bool>(Import::_arbres_.valeur(nom_type_obst_->first),true));
			tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
			grille->repaint();
		}
	}else if(Import::_arbres_.cles().contains(_nv_obst)){
		QPair<QString,int> *nom_type_obst_=PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst();
		nom_type_obst_->first=_nv_obst;
		nom_type_obst_->second=Tuile::ARBRE;
		Coordonnees c_;
		*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
		*c_.adr_environnement()=coordonnees_act.first;
		*c_.adr_tuile()=coordonnees_act.second	;
		donnees.supprimer_champions_battre(c_);
		TuileGraphique *tuile_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
		tuile_->maj_obst(QPair<QImage,bool>(Import::_arbres_.valeur(nom_type_obst_->first),true));
		tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
		grille->repaint();
	}
}

void Fenetre::confirmer_obstacle_rochers_destructibles(const QString& _nv_obst){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	if(Import::_rochers_destructibles_.cles().size()==1){
		int rep_=QMessageBox::question(this,traduire("CONFIRM_MAJ_ROCHER_DESTR"),traduire("CONTINUER_INT"),QMessageBox::Yes|QMessageBox::No);
		if(rep_==QMessageBox::Yes){
			QPair<QString,int> *nom_type_obst_=PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst();
			nom_type_obst_->first=Import::_rochers_destructibles_.cles()[0];
			nom_type_obst_->second=Tuile::ROCHER_DESTRUCTIBLE;
			Coordonnees c_;
			*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
			*c_.adr_environnement()=coordonnees_act.first;
			*c_.adr_tuile()=coordonnees_act.second	;
			donnees.supprimer_champions_battre(c_);
			TuileGraphique *tuile_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
			tuile_->maj_obst(QPair<QImage,bool>(Import::_rochers_destructibles_.valeur(nom_type_obst_->first),true));
			tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
			grille->repaint();
		}
	}else if(Import::_rochers_destructibles_.cles().contains(_nv_obst)){
		QPair<QString,int> *nom_type_obst_=PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst();
		nom_type_obst_->first=_nv_obst;
		nom_type_obst_->second=Tuile::ROCHER_DESTRUCTIBLE;
		Coordonnees c_;
		*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
		*c_.adr_environnement()=coordonnees_act.first;
		*c_.adr_tuile()=coordonnees_act.second	;
		donnees.supprimer_champions_battre(c_);
		TuileGraphique *tuile_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
		tuile_->maj_obst(QPair<QImage,bool>(Import::_rochers_destructibles_.valeur(nom_type_obst_->first),true));
		tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
		grille->repaint();
	}
}

void Fenetre::confirmer_obstacle_rochers_amovibles(const QString& _nv_obst){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	if(Import::_rochers_amovibles_.cles().size()==1){
		int rep_=QMessageBox::question(this,traduire("CONFIRM_MAJ_ROCHER_AMOV"),traduire("CONTINUER_INT"),QMessageBox::Yes|QMessageBox::No);
		if(rep_==QMessageBox::Yes){
			QPair<QString,int> *nom_type_obst_=PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst();
			nom_type_obst_->first=Import::_rochers_amovibles_.cles()[0];
			nom_type_obst_->second=Tuile::ROCHER_AMOVIBLE;
			Coordonnees c_;
			*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
			*c_.adr_environnement()=coordonnees_act.first;
			*c_.adr_tuile()=coordonnees_act.second	;
			donnees.supprimer_champions_battre(c_);
			TuileGraphique *tuile_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
			tuile_->maj_obst(QPair<QImage,bool>(Import::_rochers_amovibles_.valeur(nom_type_obst_->first),true));
			tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
			grille->repaint();
		}
	}else if(Import::_rochers_amovibles_.cles().contains(_nv_obst)){
		QPair<QString,int> *nom_type_obst_=PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst();
		nom_type_obst_->first=_nv_obst;
		nom_type_obst_->second=Tuile::ROCHER_AMOVIBLE;
		Coordonnees c_;
		*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
		*c_.adr_environnement()=coordonnees_act.first;
		*c_.adr_tuile()=coordonnees_act.second	;
		donnees.supprimer_champions_battre(c_);
		TuileGraphique *tuile_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
		tuile_->maj_obst(QPair<QImage,bool>(Import::_rochers_amovibles_.valeur(nom_type_obst_->first),true));
		tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
		grille->repaint();
	}
}

void Fenetre::confirmer_obstacle_tourbillons(const QString& _nv_obst){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	if(Import::_tourbillons_.cles().size()==1){
		int rep_=QMessageBox::question(this,traduire("CONFIRM_MAJ_TOURBILLON"),traduire("CONTINUER_INT"),QMessageBox::Yes|QMessageBox::No);
		if(rep_==QMessageBox::Yes){
			QPair<QString,int> *nom_type_obst_=PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst();
			nom_type_obst_->first=Import::_tourbillons_.cles()[0];
			nom_type_obst_->second=Tuile::TOURBILLON;
			Coordonnees c_;
			*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
			*c_.adr_environnement()=coordonnees_act.first;
			*c_.adr_tuile()=coordonnees_act.second	;
			donnees.supprimer_champions_battre(c_);
			TuileGraphique *tuile_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
			tuile_->maj_obst(QPair<QImage,bool>(Import::_tourbillons_.valeur(nom_type_obst_->first),true));
			tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
			grille->repaint();
		}
	}else if(Import::_tourbillons_.cles().contains(_nv_obst)){
		QPair<QString,int> *nom_type_obst_=PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst();
		nom_type_obst_->first=_nv_obst;
		nom_type_obst_->second=Tuile::TOURBILLON;
		Coordonnees c_;
		*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
		*c_.adr_environnement()=coordonnees_act.first;
		*c_.adr_tuile()=coordonnees_act.second	;
		donnees.supprimer_champions_battre(c_);
		TuileGraphique *tuile_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
		tuile_->maj_obst(QPair<QImage,bool>(Import::_tourbillons_.valeur(nom_type_obst_->first),true));
		tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
		grille->repaint();
	}
}

void Fenetre::supprimer_elt_tuile(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_ENVIRONNEMENT_EDITION"));
		return;
	}
	PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst()->first="";
	PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst()->second=Tuile::RIEN;
	PanneauEditerEnv::_environnement_en_cours_->supprimer_elements(coordonnees_act.second);
	Coordonnees c_;
	*c_.adr_lieu_plateau()=QPair<int,int>(ind_lieu,ind_plateau);
	*c_.adr_environnement()=coordonnees_act.first;
	*c_.adr_tuile()=coordonnees_act.second	;
	donnees.supprimer_champions_battre(c_);
	TuileGraphique *tuile_=grille->tuile(coordonnees_act.first.first+coordonnees_act.second.first,coordonnees_act.first.second+coordonnees_act.second.second);
	tuile_->maj_obst(QPair<QImage,bool>(QImage(),false));
	tuile_->maj_perso(QPair<QImage,QPair<int,int> >(QImage(),QPair<int,int>(0,0)));
	grille->repaint();
}

void Fenetre::ajouter_pk(){
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_DRESSE,this,DialoguePkCombat::RIEN);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		QList<PokemonDresse> *equipe_=_plateau_ligue_en_cours_->adr_dresseur_ligue()->adr_equipe();
		(*equipe_)<<dial_->nv_pk_dresse();
		panneau_editeur_ligue->maj_equipe();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::inserer_pk(){
	QList<PokemonDresse> *equipe_=_plateau_ligue_en_cours_->adr_dresseur_ligue()->adr_equipe();
	if(panneau_editeur_ligue->ligne_courante()<0||panneau_editeur_ligue->ligne_courante()>equipe_->size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_INSERT_INV"));
		return;
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_DRESSE,this,DialoguePkCombat::RIEN);
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		QList<PokemonDresse> *equipe_=_plateau_ligue_en_cours_->adr_dresseur_ligue()->adr_equipe();
		equipe_->insert(panneau_editeur_ligue->ligne_courante(),dial_->nv_pk_dresse());
		panneau_editeur_ligue->maj_equipe();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::editer_pk(){
	QList<PokemonDresse> *equipe_=_plateau_ligue_en_cours_->adr_dresseur_ligue()->adr_equipe();
	if(panneau_editeur_ligue->ligne_courante()<0||panneau_editeur_ligue->ligne_courante()>=equipe_->size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_EDIT_INV"));
		return;
	}
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_DRESSE,this,DialoguePkCombat::RIEN);
	dial_->maj_pk_dresse_edite(&((*equipe_)[panneau_editeur_ligue->ligne_courante()]));
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		(*equipe_)[panneau_editeur_ligue->ligne_courante()]=dial_->nv_pk_dresse();
		panneau_editeur_ligue->maj_equipe();
		//TODO ajouter la ligne dans l'editeur d'environnement
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::supprimer_pk(){
	QList<PokemonDresse> *equipe_=Fenetre::_plateau_ligue_en_cours_->adr_dresseur_ligue()->adr_equipe();
	if(panneau_editeur_ligue->ligne_courante()<0||panneau_editeur_ligue->ligne_courante()>=equipe_->size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_SUPPR_INV"));
		return;
	}
	panneau_editeur_ligue->decrementer_ind_pk();
	equipe_->removeAt(panneau_editeur_ligue->ligne_courante());
	panneau_editeur_ligue->maj_equipe();
}

void Fenetre::editer_coords_depart(){
	if(donnees.lieux_c().isEmpty()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("PAS_LIEU_DONNEES"));
		return;
	}
	bool ligue_en_cours_=_ligue_en_cours_!=NULL;
	DialogueCoords *dial_=new DialogueCoords(langue,*donnees.adr_coords_depart(),&donnees,this,DialogueCoords::DEPART);
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_&&dial_->acceptable()){
		*donnees.adr_coords_depart()=dial_->coordonnees();
	}
	if(ligue_en_cours_){
		_ligue_en_cours_=donnees.ligue(ind_lieu);
		_plateau_ligue_en_cours_=_ligue_en_cours_->plateau(ind_plateau);
	}else{
		_lieu_en_cours_=donnees.lieu(ind_lieu);
		_plateau_en_cours_=_lieu_en_cours_->plateau(ind_plateau);
	}
	delete dial_;
	dial_=NULL;
}
void Fenetre::editer_pk_depart(){
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_DEPART,this,DialoguePkCombat::RIEN);
	if(*donnees.adr_pk_depart()->adr_nom()!=""){
		dial_->maj_pk_edite(donnees.adr_pk_depart());
	}
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		*donnees.adr_pk_depart()=dial_->nv_pk();
	}
	delete dial_;
	dial_=NULL;
}
void Fenetre::changer_nb_max_attaques(){
	bool ok=false;
	int nb_att_pre_=*donnees.adr_nb_attaques_max();
	int max_att_=(int)Import::constante_numerique("MAX_ATT");
	int min_att_=(int)Import::constante_numerique("MIN_ATT");
	int nb_att_=QInputDialog::getInteger(this,traduire("NB_ATT_MAX"),traduire("NOUVEAU_NB"),nb_att_pre_,min_att_,max_att_,1,&ok);
	if(ok){
		*donnees.adr_nb_attaques_max()=(uchar)nb_att_;
		PokemonDresse::_nb_attaques_max_=*donnees.adr_nb_attaques_max();
	}
}

void Fenetre::editer_map(){
	DialogueEditeurMap *dial_=new DialogueEditeurMap(langue,this,donnees.minimap());
	dial_->exec();
	bool rejete_=dial_->rejet();
	if(!rejete_){
		donnees.maj_minimap(dial_->carte_modif());
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::lier_map(){
	if(donnees.lieux_c().isEmpty()||donnees.minimap().total()==0){
		QString err_;
		if(donnees.lieux_c().isEmpty()){
			err_+=traduire("PAS_LIEU_DONNEES")+"\n";
		}
		if(donnees.minimap().total()==0){
			err_+=traduire("PAS_MINIMAP");
		}
		QMessageBox::critical(this,traduire("ERREUR"),err_);
		return;
	}
	DialogueLieuxVols *dial_=new DialogueLieuxVols(langue,this,&donnees,donnees.vols());
	dial_->exec();
	bool rejete_=dial_->rejet();
	if(!rejete_){
		donnees.maj_vols(dial_->vols());
	}
	delete dial_;
	dial_=NULL;
}


void Fenetre::ajouter_supprimer_condition_ligue(){
	if(donnees.lieux_c().isEmpty()||donnees.ligues_c().isEmpty()){
		QString err_;
		if(donnees.lieux_c().isEmpty()){
			err_+=traduire("PAS_LIEU_DONNEES")+"\n";
		}
		if(donnees.ligues_c().isEmpty()){
			err_+=traduire("PAS_LIGUE_DONNEES");
		}
		QMessageBox::critical(this,traduire("ERREUR"),err_);
		return;
	}
	DialogueAccesCarte *dial_=new DialogueAccesCarte(langue,this);
	dial_->conditions_acces_coords(*donnees.adr_acces_fct_ligues());
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		*donnees.adr_acces_fct_ligues()=dial_->conditions_acces_coords();
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::ajouter_supprimer_condition_champions(){
	if(donnees.val_champions_battre().total()==0||donnees.ligues_c().isEmpty()){
		QString err_;
		if(donnees.val_champions_battre().total()==0){
			err_+=traduire("PAS_CHAMPION")+"\n";
		}
		if(donnees.ligues_c().isEmpty()){
			err_+=traduire("PAS_LIGUE_DONNEES");
		}
		QMessageBox::critical(this,traduire("ERREUR"),err_);
		return;
	}
	DialogueAccesLigue *dial_=new DialogueAccesLigue(langue,this);
	dial_->conditions_acces_fct_champions(*donnees.adr_champions_battre_ligue());
	dial_->exec();
	bool accepte_=dial_->result()==QDialog::Accepted;
	if(accepte_){
		*donnees.adr_champions_battre_ligue()=dial_->conditions_acces_fct_champions();
	}
	delete dial_;
	dial_=NULL;
}

void Fenetre::voir_donnees(){
	DialogueBaseDonnees *dial_=new DialogueBaseDonnees(langue,this);
	dial_->exec();
	delete dial_;
	dial_=NULL;
}

void Fenetre::utilisation_logiciel(){
	DialogueAide *dial_=new DialogueAide(langue,this);
	dial_->exec();
	delete dial_;
	dial_=NULL;
}

void Fenetre::base_de_donnees(){
	if(!InitBDD::_fini_){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("ERREUR_BDD"));
		return;
	}
	DialogueSql *dial_=new DialogueSql(langue,this);
	dial_->exec();
	delete dial_;
	dial_=NULL;
}

void Fenetre::closeEvent(QCloseEvent* _ev){
	if(!InitBDD::_fini_){
		_ev->ignore();
		QMessageBox::critical(this,traduire("ERREUR"),traduire("ERREUR_BDD"));
		return;
	}
	if(donnees.egal(anciennes_donnees)){
		return;
	}
	int rep_=QMessageBox::question(this,traduire("TITRE_FERMETURE"),traduire("MESS_FERMETURE"),QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
	if(rep_==QMessageBox::Cancel){
		_ev->ignore();
		return;
	}
	if(rep_==QMessageBox::No){
		return;
	}
	sauvegarder();
	//TODO comparaison donnees
}

Fenetre::~Fenetre(){
	Import::destructeur();
	delete panneau_editeur_ligue;
	panneau_editeur_ligue=NULL;
	delete panneau_editeur_env;
	panneau_editeur_env=NULL;
	QSqlQuery requette_;
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_CT_PK",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_CS_PK",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_MT_PK",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_CAPAC_PK",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_TYPE_PK",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_NIV_ATT",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_CT_ATTAQUE",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_CS_ATTAQUE",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_TABLE_ATTAQUES",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_EVOLUTIONS_ATTAQUE",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_EVOLUTIONS_OBJEVO",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_EVOLUTIONS_PIERREEVO",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_EVOLUTIONS_BONHEUR",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_EVOLUTIONS_NIV",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_POKEDEX",langue+1));
	requette_.exec("drop table "+Import::constante_non_numerique("SQL_TABLE_TYPE",langue+1));
}



