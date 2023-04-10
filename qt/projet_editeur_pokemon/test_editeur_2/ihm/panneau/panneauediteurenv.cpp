#include "ihm/panneau/panneauediteurenv.h"
#include "ihm/fenetre.h"
#include "ihm/dialogue/dialoguepkcombat.h"
#include "serialisable/cartes/environnement.h"
#include "serialisable/pokemon/pokemondresse.h"
#include "base_donnees/import.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "autre/utilitaire.h"
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QSpinBox>
#include <QGroupBox>
#include <QTableWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QPixmap>
#include <QLabel>

Environnement *PanneauEditerEnv::_environnement_en_cours_=NULL;

Tuile *PanneauEditerEnv::_tuile_en_cours_=NULL;

const HashMap<QString,QStringList> PanneauEditerEnv::_elements_ihm_=PanneauEditerEnv::init_elements_ihm();

HashMap<QString,QStringList> PanneauEditerEnv::init_elements_ihm(){
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

QString PanneauEditerEnv::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString PanneauEditerEnv::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString PanneauEditerEnv::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

PanneauEditerEnv::PanneauEditerEnv(int _langue,Fenetre *_fenetre,Environnement *_environnement_en_cours){
	_environnement_en_cours_=_environnement_en_cours;
	PanneauEditerEnv::_tuile_en_cours_=NULL;
	fenetre=_fenetre;
	langue=_langue;
	//setEnable(environnement_en_cours!=NULL)
	QVBoxLayout *centre_=new QVBoxLayout();
	QHBoxLayout *type_env_lay_=new QHBoxLayout();
	type_env_lay_->addWidget(new QLabel(traduire("TYPE_ENV")));
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
	type_env_lay_->addWidget(type_env);
	centre_->addLayout(type_env_lay_);
	QHBoxLayout *muret_lay_=new QHBoxLayout();
	QGroupBox *groupe_muret_=new QGroupBox(traduire("MURET"));
	muret_lay_->addWidget(new QLabel(traduire("MURET_XY")));
	muret_h=new QSpinBox();
	muret_h->setRange(-1,1);
	muret_h->setValue(0);
	connect(muret_h,SIGNAL(valueChanged(int)),this,SLOT(maj_muret()));
	muret_lay_->addWidget(muret_h);
	muret_v=new QSpinBox();
	muret_v->setRange(-1,1);
	muret_v->setValue(0);
	connect(muret_v,SIGNAL(valueChanged(int)),this,SLOT(maj_muret()));
	muret_lay_->addWidget(muret_v);
	groupe_muret_->setLayout(muret_lay_);
	centre_->addWidget(groupe_muret_);
	QHBoxLayout *appar_per_lay_=new QHBoxLayout();
	QGroupBox *groupe_appar_=new QGroupBox(traduire("APPAR_PER"));
	appar_per=new QSpinBox();
	int max_per_=(int)Import::constante_numerique("MAX_PERIODE_APPARITION");
	int min_per_=(int)Import::constante_numerique("MIN_PERIODE_APPARITION");
	int def_per_=(int)Import::constante_numerique("DEF_PERIODE_APPARITION");
	appar_per->setRange(min_per_,max_per_);
	appar_per->setValue(def_per_);
	appar_per_lay_->addWidget(new QLabel(traduire("NB_PAS_MOYEN")));
	connect(appar_per,SIGNAL(valueChanged(int)),this,SLOT(maj_nb_pas()));
	appar_per_lay_->addWidget(appar_per);
	groupe_appar_->setLayout(appar_per_lay_);
	centre_->addWidget(groupe_appar_);
	QStringList liste_elts_;
	//liste_elts_<<"icone"
	liste_elts_<<traduire("ETIQUETTE_NOM");
	liste_elts_<<traduire("ETIQUETTE_NIVEAU");
	liste_elts_<<traduire("ETIQUETTE_CAPACITE");
	liste_elts_<<traduire("ETIQUETTE_OBJET");
	liste_elts_<<traduire("ETIQUETTE_GENRE");
	centre_->addWidget(new QLabel(traduire("AFFICHE_APPAR_PER")));
	table_appar_marche=new QTableWidget(1,liste_elts_.size());
	table_appar_marche->setHorizontalHeaderLabels(liste_elts_);
	for(int i=0;i<liste_elts_.size();i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText("");
		table_appar_marche->setItem(0,i,element_);
	}
	centre_->addWidget(table_appar_marche);
	QGridLayout *groupes_boutons_appar_;
	QPushButton *bouton_;
	groupes_boutons_appar_=new QGridLayout();
	bouton_=new QPushButton(traduire("AJOUTER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(ajouter_pk_marche()));
	groupes_boutons_appar_->addWidget(bouton_,0,0);
	bouton_=new QPushButton(traduire("EDITER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(editer_pk_marche()));
	groupes_boutons_appar_->addWidget(bouton_,0,1);
	bouton_=new QPushButton(traduire("SUPPRIMER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(supprimer_pk_marche()));
	groupes_boutons_appar_->addWidget(bouton_,0,2);
	bouton_=new QPushButton(traduire("INSERER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(inserer_pk_marche()));
	groupes_boutons_appar_->addWidget(bouton_,1,0);
	centre_->addLayout(groupes_boutons_appar_);
	centre_->addWidget(new QLabel(traduire("AFFICHE_APPAR_CANNE")));
	table_appar_peche_canne=new QTableWidget(1,liste_elts_.size());
	table_appar_peche_canne->setHorizontalHeaderLabels(liste_elts_);
	for(int i=0;i<liste_elts_.size();i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText("");
		table_appar_peche_canne->setItem(0,i,element_);
	}
	centre_->addWidget(table_appar_peche_canne);
	groupes_boutons_appar_=new QGridLayout();
	bouton_=new QPushButton(traduire("AJOUTER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(ajouter_pk_canne()));
	groupes_boutons_appar_->addWidget(bouton_,0,0);
	bouton_=new QPushButton(traduire("EDITER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(editer_pk_canne()));
	groupes_boutons_appar_->addWidget(bouton_,0,1);
	bouton_=new QPushButton(traduire("SUPPRIMER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(supprimer_pk_canne()));
	groupes_boutons_appar_->addWidget(bouton_,0,2);
	bouton_=new QPushButton(traduire("INSERER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(inserer_pk_canne()));
	groupes_boutons_appar_->addWidget(bouton_,1,0);
	centre_->addLayout(groupes_boutons_appar_);
	centre_->addWidget(new QLabel(traduire("AFFICHE_APPAR_SUPER_CANNE")));
	table_appar_peche_super_canne=new QTableWidget(1,liste_elts_.size());
	table_appar_peche_super_canne->setHorizontalHeaderLabels(liste_elts_);
	for(int i=0;i<liste_elts_.size();i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText("");
		table_appar_peche_super_canne->setItem(0,i,element_);
	}
	centre_->addWidget(table_appar_peche_super_canne);
	groupes_boutons_appar_=new QGridLayout();
	bouton_=new QPushButton(traduire("AJOUTER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(ajouter_pk_super_canne()));
	groupes_boutons_appar_->addWidget(bouton_,0,0);
	bouton_=new QPushButton(traduire("EDITER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(editer_pk_super_canne()));
	groupes_boutons_appar_->addWidget(bouton_,0,1);
	bouton_=new QPushButton(traduire("SUPPRIMER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(supprimer_pk_super_canne()));
	groupes_boutons_appar_->addWidget(bouton_,0,2);
	bouton_=new QPushButton(traduire("INSERER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(inserer_pk_super_canne()));
	groupes_boutons_appar_->addWidget(bouton_,1,0);
	centre_->addLayout(groupes_boutons_appar_);
	centre_->addWidget(new QLabel(traduire("AFFICHE_APPAR_MEGA_CANNE")));
	table_appar_peche_mega_canne=new QTableWidget(1,liste_elts_.size());
	table_appar_peche_mega_canne->setHorizontalHeaderLabels(liste_elts_);
	for(int i=0;i<liste_elts_.size();i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText("");
		table_appar_peche_mega_canne->setItem(0,i,element_);
	}
	centre_->addWidget(table_appar_peche_mega_canne);
	groupes_boutons_appar_=new QGridLayout();
	bouton_=new QPushButton(traduire("AJOUTER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(ajouter_pk_mega_canne()));
	groupes_boutons_appar_->addWidget(bouton_,0,0);
	bouton_=new QPushButton(traduire("EDITER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(editer_pk_mega_canne()));
	groupes_boutons_appar_->addWidget(bouton_,0,1);
	bouton_=new QPushButton(traduire("SUPPRIMER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(supprimer_pk_mega_canne()));
	groupes_boutons_appar_->addWidget(bouton_,0,2);
	bouton_=new QPushButton(traduire("INSERER_PK"));
	connect(bouton_,SIGNAL(clicked()),_fenetre,SLOT(inserer_pk_mega_canne()));
	groupes_boutons_appar_->addWidget(bouton_,1,0);
	centre_->addLayout(groupes_boutons_appar_);
	groupe_type_tuile=new QButtonGroup();
	QGroupBox *valider_tuile_=new QGroupBox(traduire("INFOS_TUILES"));
	QFormLayout *form_=new QFormLayout();
	QRadioButton *radio_;
	radio_=new QRadioButton(traduire("PERSONNAGE"));//TODO slot et boite de dialogue
	groupe_type_tuile->addButton(radio_,AUTRE_PERSO);
	editer_perso=new QPushButton(traduire("EDITER_P"));
	connect(editer_perso,SIGNAL(clicked()),_fenetre,SLOT(maj_personnage()));
	form_->addRow(radio_,editer_perso);
	/*radio_=new QRadioButton("Dresseur ligue")
	//TODO slot et boite de dialogue
	groupe_type_tuile->addButton(radio_,DRESSEUR_LIGUE)
	editer_dresseur_ligue=new QPushButton("Editer")
	form_->addRow(radio_,editer_dresseur_ligue)*/
	radio_=new QRadioButton(traduire("DRESSEUR"));//TODO slot et boite de dialogue
	groupe_type_tuile->addButton(radio_,DRESSEUR);
	editer_dresseur=new QPushButton(traduire("EDITER_D"));
	connect(editer_dresseur,SIGNAL(clicked()),_fenetre,SLOT(maj_dresseur()));
	form_->addRow(radio_,editer_dresseur);
	radio_=new QRadioButton(traduire("CHAMPION"));//TODO slot et boite de dialogue
	groupe_type_tuile->addButton(radio_,CHAMPION);
	editer_champion=new QPushButton(traduire("EDITER_C"));
	connect(editer_champion,SIGNAL(clicked()),_fenetre,SLOT(maj_champion()));
	form_->addRow(radio_,editer_champion);
	radio_=new QRadioButton(traduire("ARBRE"));
	groupe_type_tuile->addButton(radio_,ARBRE);
	choix_imgs_arbres=new QComboBox();
	foreach(QString s,Import::_arbres_.cles()){
		choix_imgs_arbres->addItem(QPixmap::fromImage(Import::_arbres_.valeur(s)),s);
	}
	if(choix_imgs_arbres->count()==1){
		connect(radio_,SIGNAL(clicked()),_fenetre,SLOT(confirmer_obstacle_arbre()));
	}else{
		choix_imgs_arbres->setEditable(true);
		connect(choix_imgs_arbres,SIGNAL(editTextChanged(QString)),_fenetre,SLOT(confirmer_obstacle_arbre(QString)));
	}
	form_->addRow(radio_,choix_imgs_arbres);
	radio_=new QRadioButton(traduire("ROCHER_DESTR"));
	groupe_type_tuile->addButton(radio_,ROCHER_DESTR);
	choix_imgs_rochers_destructibles=new QComboBox();
	foreach(QString s,Import::_rochers_destructibles_.cles()){
		choix_imgs_rochers_destructibles->addItem(QPixmap::fromImage(Import::_rochers_destructibles_.valeur(s)),s);
	}
	if(choix_imgs_rochers_destructibles->count()==1){
		connect(radio_,SIGNAL(clicked()),_fenetre,SLOT(confirmer_obstacle_rochers_destructibles()));
	}else{
		choix_imgs_rochers_destructibles->setEditable(true);
		connect(choix_imgs_rochers_destructibles,SIGNAL(editTextChanged(QString)),_fenetre,SLOT(confirmer_obstacle_rochers_destructibles(QString)));
	}
	form_->addRow(radio_,choix_imgs_rochers_destructibles);
	radio_=new QRadioButton(traduire("ROCHER_AMOV"));
	groupe_type_tuile->addButton(radio_,ROCHER_AMOV);
	choix_imgs_rochers_amovibles=new QComboBox();
	foreach(QString s,Import::_rochers_amovibles_.cles()){
		choix_imgs_rochers_amovibles->addItem(QPixmap::fromImage(Import::_rochers_amovibles_.valeur(s)),s);
	}
	if(choix_imgs_rochers_amovibles->count()==1){
		connect(radio_,SIGNAL(clicked()),_fenetre,SLOT(confirmer_obstacle_rochers_amovibles()));
	}else{
		choix_imgs_rochers_amovibles->setEditable(true);
		connect(choix_imgs_rochers_amovibles,SIGNAL(editTextChanged(QString)),_fenetre,SLOT(confirmer_obstacle_rochers_amovibles(QString)));
	}
	form_->addRow(radio_,choix_imgs_rochers_amovibles);
	radio_=new QRadioButton(traduire("TOURBILLON"));
	groupe_type_tuile->addButton(radio_,TOURBILLON);
	choix_imgs_tourbillons=new QComboBox();
	foreach(QString s,Import::_tourbillons_.cles()){
		choix_imgs_tourbillons->addItem(QPixmap::fromImage(Import::_tourbillons_.valeur(s)),s);
	}
	if(choix_imgs_tourbillons->count()==1){
		connect(radio_,SIGNAL(clicked()),_fenetre,SLOT(confirmer_obstacle_tourbillons()));
	}else{
		choix_imgs_tourbillons->setEditable(true);
		connect(choix_imgs_tourbillons,SIGNAL(editTextChanged(QString)),_fenetre,SLOT(confirmer_obstacle_tourbillons(QString)));
	}
	form_->addRow(radio_,choix_imgs_tourbillons);
	radio_=new QRadioButton(traduire("BOITE_ECH"));
	connect(radio_,SIGNAL(clicked()),_fenetre,SLOT(confirmer_echange_pk_boites()));
	groupe_type_tuile->addButton(radio_,ECHANGE);
	form_->addRow(radio_,new QLabel(""));
	radio_=new QRadioButton(traduire("PK_LEG"));
	groupe_type_tuile->addButton(radio_,PK_LEG);
	editer_pk_leg=new QPushButton(traduire("EDITER_PK_LEG"));
	connect(editer_pk_leg,SIGNAL(clicked()),_fenetre,SLOT(editer_pk_leg()));
	form_->addRow(radio_,editer_pk_leg);
	radio_=new QRadioButton(traduire("DON_PK"));
	groupe_type_tuile->addButton(radio_,DON_PK);
	editer_don_pk=new QPushButton(traduire("EDITER_DON_PK"));
	connect(editer_don_pk,SIGNAL(clicked()),_fenetre,SLOT(editer_pk_don()));
	form_->addRow(radio_,editer_don_pk);
	radio_=new QRadioButton(traduire("OBJET"));//TODO slot et boite de dialogue
	groupe_type_tuile->addButton(radio_,OBJET);
	editer_objet=new QPushButton(traduire("EDITER_OBJET"));
	connect(editer_objet,SIGNAL(clicked()),_fenetre,SLOT(editer_objet()));
	form_->addRow(radio_,editer_objet);
	radio_=new QRadioButton(traduire("RIEN"));
	connect(radio_,SIGNAL(clicked()),_fenetre,SLOT(supprimer_elt_tuile()));
	groupe_type_tuile->addButton(radio_,RIEN);
	radio_->setChecked(true);
	selection=RIEN;
	form_->addRow(radio_,new QLabel(""));
	editer_perso->setEnabled(false);
	//editer_dresseur_ligue->setEnabled(false)
	editer_dresseur->setEnabled(false);
	editer_champion->setEnabled(false);
	choix_imgs_arbres->setEnabled(false);
	choix_imgs_rochers_destructibles->setEnabled(false);
	choix_imgs_rochers_amovibles->setEnabled(false);
	choix_imgs_tourbillons->setEnabled(false);
	editer_pk_leg->setEnabled(false);
	editer_don_pk->setEnabled(false);
	editer_objet->setEnabled(false);
	connect(groupe_type_tuile,SIGNAL(buttonReleased(int)),this,SLOT(activer_bouton(int)));
	choix_imgs_tuiles=new QComboBox();
	foreach(QString s,Import::_tuiles_importees_.cles()){
		choix_imgs_tuiles->addItem(QPixmap::fromImage(Import::_tuiles_importees_.valeur(s)),s);
	}
	choix_imgs_tuiles->setEditable(true);
	connect(choix_imgs_tuiles,SIGNAL(editTextChanged(QString)),this,SLOT(maj_image_tuile(QString)));
	//const QImage&
	form_->addRow(traduire("IMAGE_FOND_TUILE"),choix_imgs_tuiles);
	valider_tuile_->setLayout(form_);
	centre_->addWidget(valider_tuile_);
	setLayout(centre_);
}

void PanneauEditerEnv::activer(){
	setEnabled(true);
}

void PanneauEditerEnv::ajouter_arbre_image(const QString& _nom){
	choix_imgs_arbres->addItem(QPixmap::fromImage(Import::_arbres_.valeur(_nom)),_nom);
}

void PanneauEditerEnv::ajouter_rocher_destructible_image(const QString& _nom){
	choix_imgs_rochers_destructibles->addItem(QPixmap::fromImage(Import::_rochers_destructibles_.valeur(_nom)),_nom);
}

void PanneauEditerEnv::ajouter_rocher_amovible_image(const QString& _nom){
	choix_imgs_rochers_amovibles->addItem(QPixmap::fromImage(Import::_rochers_amovibles_.valeur(_nom)),_nom);
}

void PanneauEditerEnv::ajouter_tourbillon_image(const QString& _nom){
	choix_imgs_tourbillons->addItem(QPixmap::fromImage(Import::_tourbillons_.valeur(_nom)),_nom);
}

void PanneauEditerEnv::ajouter_tuile_image(const QString& _nom){
	//choix_imgs_tuiles->addItem(QPixmap::fromImage(Fenetre::_tuiles_importees_.valeur(_nom)),_nom)
	choix_imgs_tuiles->addItem(QPixmap::fromImage(Import::_tuiles_importees_.valeur(_nom)),_nom);
}

void PanneauEditerEnv::maj_env(){
	int nb_l_=table_appar_marche->rowCount();
	for(int i=0;i<nb_l_;i++){
		table_appar_marche->item(i,0)->setIcon(QPixmap::fromImage(QImage()));
		table_appar_marche->item(i,0)->setText("");
		table_appar_marche->item(i,1)->setText("");
		table_appar_marche->item(i,2)->setText("");
		table_appar_marche->item(i,3)->setText("");
		table_appar_marche->item(i,4)->setText("");
	}

}

void PanneauEditerEnv::maj_env(const QPair<QPair<int,int>,QPair<int,int> >& _coords){
	if(Fenetre::_plateau_en_cours_!=NULL){
		bool suppr_=false;
		_environnement_en_cours_=Fenetre::_plateau_en_cours_->environnement(_coords.first,suppr_);
		PanneauEditerEnv::_tuile_en_cours_=_environnement_en_cours_->tuile(_coords.second);
		//TODO maj totale du panneau en fonction de l'environnement
		int indice_=choix_imgs_tuiles->findText(*PanneauEditerEnv::_tuile_en_cours_->adr_nom_image());
		if(indice_>-1){
			choix_imgs_tuiles->setCurrentIndex(indice_);
		}
		if(*_environnement_en_cours_->type_env()==""){
			type_env->setCurrentIndex(type_env->findText(""));
		}else{
			type_env->setCurrentIndex(type_env->findText(traduire(Import::_noms_envir_,*_environnement_en_cours_->type_env(),langue)));
		}
		//type_env->setCurrentIndex(type_env->findText(*_environnement_en_cours_->type_env()))
		muret_h->setValue(_environnement_en_cours_->adr_muret()->first);
		muret_v->setValue(_environnement_en_cours_->adr_muret()->second);
		appar_per->setValue(*_environnement_en_cours_->adr_nb_pas_moyen_pour_appar());
		int nb_l_;
		int per_appar_;
		int nb_col_;
		nb_l_=table_appar_marche->rowCount();
		nb_col_=table_appar_marche->columnCount();
		per_appar_=_environnement_en_cours_->periode_appar();
		if(nb_l_<per_appar_){
			table_appar_marche->setRowCount(per_appar_);
			for(int i=nb_l_;i<per_appar_;i++){
				for(int j=0;j<nb_col_;j++){
					QTableWidgetItem *element_=new QTableWidgetItem();
					element_->setText("");
					table_appar_marche->setItem(i,j,element_);
				}
			}
		}
		for(int i=0;i<per_appar_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon(i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_marche->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_marche->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_marche->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_marche->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_marche->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_marche->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
		nb_l_=table_appar_peche_canne->rowCount();
		nb_col_=table_appar_peche_canne->columnCount();
		per_appar_=_environnement_en_cours_->periode_appar(Environnement::_canne_);
		if(nb_l_<per_appar_){
			table_appar_peche_canne->setRowCount(per_appar_);
			for(int i=nb_l_;i<per_appar_;i++){
				for(int j=0;j<nb_col_;j++){
					QTableWidgetItem *element_=new QTableWidgetItem();
					element_->setText("");
					table_appar_peche_canne->setItem(i,j,element_);
				}
			}
		}
		for(int i=0;i<per_appar_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_canne_,i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_peche_canne->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_peche_canne->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_peche_canne->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_peche_canne->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_peche_canne->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_peche_canne->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
		nb_l_=table_appar_peche_super_canne->rowCount();
		nb_col_=table_appar_peche_super_canne->columnCount();
		per_appar_=_environnement_en_cours_->periode_appar(Environnement::_super_canne_);
		if(nb_l_<per_appar_){
			table_appar_peche_super_canne->setRowCount(per_appar_);
			for(int i=nb_l_;i<per_appar_;i++){
				for(int j=0;j<nb_col_;j++){
					QTableWidgetItem *element_=new QTableWidgetItem();
					element_->setText("");
					table_appar_peche_super_canne->setItem(i,j,element_);
				}
			}
		}
		for(int i=0;i<per_appar_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_super_canne_,i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_peche_super_canne->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_peche_super_canne->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_peche_super_canne->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_peche_super_canne->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_peche_super_canne->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_peche_super_canne->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
		nb_l_=table_appar_peche_mega_canne->rowCount();
		nb_col_=table_appar_peche_mega_canne->columnCount();
		per_appar_=_environnement_en_cours_->periode_appar(Environnement::_mega_canne_);
		if(nb_l_<per_appar_){
			table_appar_peche_mega_canne->setRowCount(per_appar_);
			for(int i=nb_l_;i<per_appar_;i++){
				for(int j=0;j<nb_col_;j++){
					QTableWidgetItem *element_=new QTableWidgetItem();
					element_->setText("");
					table_appar_peche_mega_canne->setItem(i,j,element_);
				}
			}
		}
		for(int i=0;i<per_appar_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_mega_canne_,i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_peche_mega_canne->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_peche_mega_canne->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_peche_mega_canne->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_peche_mega_canne->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_peche_mega_canne->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_peche_mega_canne->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
		int choix_=PanneauEditerEnv::RIEN;
		groupe_type_tuile->button(choix_)->setChecked(false);
		if(_environnement_en_cours_->coords_autres_persos().contains(_coords.second)){
			choix_=PanneauEditerEnv::AUTRE_PERSO;
		}else if(_environnement_en_cours_->coords_dresseurs().contains(_coords.second)){
			choix_=PanneauEditerEnv::DRESSEUR;
		}else if(_environnement_en_cours_->coords_champions().contains(_coords.second)){
			choix_=PanneauEditerEnv::CHAMPION;
		/*}else if(_environnement_en_cours_->coords_champions().contains(_coords.second)){
			choix_=PanneauEditerEnv::CHAMPION*/
		}else if(Import::_arbres_.cles().contains(PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst()->first)){
			choix_=PanneauEditerEnv::ARBRE;
		}else if(Import::_rochers_destructibles_.cles().contains(PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst()->first)){
			choix_=PanneauEditerEnv::ROCHER_DESTR;
		}else if(Import::_rochers_amovibles_.cles().contains(PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst()->first)){
			choix_=PanneauEditerEnv::ROCHER_AMOV;
		}else if(Import::_tourbillons_.cles().contains(PanneauEditerEnv::_tuile_en_cours_->adr_nom_image_obst()->first)){
			choix_=PanneauEditerEnv::TOURBILLON;
		}else if(_environnement_en_cours_->contient_echange_poke_boites(_coords.second)){
			choix_=PanneauEditerEnv::ECHANGE;
		}else if(_environnement_en_cours_->coords_pokemon_legendaire().contains(_coords.second)){
			choix_=PanneauEditerEnv::PK_LEG;
		}else if(_environnement_en_cours_->coords_lieux_dons_pokemon().contains(_coords.second)){
			choix_=PanneauEditerEnv::DON_PK;
		}else if(_environnement_en_cours_->coords_objets_donnes_ramasses().contains(_coords.second)){
			choix_=PanneauEditerEnv::OBJET;
		}
		groupe_type_tuile->button(choix_)->setChecked(true);
		activer_bouton(choix_);
	}
}

int PanneauEditerEnv::ligne_act_per()const{
	return table_appar_marche->currentRow();
}

void PanneauEditerEnv::maj_appar_per(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		return;
	}
	int nb_act_l_=table_appar_marche->rowCount();
	int nb_appar_per_=PanneauEditerEnv::_environnement_en_cours_->periode_appar();
	if(nb_act_l_==nb_appar_per_){
		for(int i=0;i<nb_act_l_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon(i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_marche->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_marche->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_marche->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_marche->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_marche->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_marche->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
	}else if(nb_act_l_<nb_appar_per_){
		for(int i=0;i<nb_act_l_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon(i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_marche->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_marche->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_marche->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_marche->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_marche->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_marche->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
		table_appar_marche->setRowCount(nb_act_l_+1);
		QTableWidgetItem *element_;
		element_=new QTableWidgetItem();
		Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon(nb_act_l_);
		QString n_pk_=*pk_->adr_nom();
		int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
		element_->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
		element_->setText(traduire(Import::_noms_pk_,n_pk_,langue));
		table_appar_marche->setItem(nb_act_l_,0,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*pk_->adr_niveau()));
		table_appar_marche->setItem(nb_act_l_,1,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
		table_appar_marche->setItem(nb_act_l_,2,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
		table_appar_marche->setItem(nb_act_l_,3,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		table_appar_marche->setItem(nb_act_l_,4,element_);
	}else{
		int nb_act_c_=table_appar_marche->columnCount();
		for(int i=0;i<nb_act_l_-1;i++){
			table_appar_marche->item(i,0)->setIcon(table_appar_marche->item(i+1,0)->icon());
			for(int j=0;j<nb_act_c_;j++){
				table_appar_marche->item(i,j)->setText(table_appar_marche->item(i+1,j)->text());
			}
		}
		table_appar_marche->item(nb_act_l_-1,0)->setIcon(QIcon());
		for(int j=0;j<nb_act_c_;j++){
			table_appar_marche->item(nb_act_l_-1,j)->setText("");
		}
	}
}

int PanneauEditerEnv::ligne_act_canne()const{
	return table_appar_peche_canne->currentRow();
}

void PanneauEditerEnv::maj_appar_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		return;
	}
	int nb_act_l_=table_appar_peche_canne->rowCount();
	int nb_appar_per_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_canne_);
	if(nb_act_l_==nb_appar_per_){
		for(int i=0;i<nb_act_l_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_canne_,i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_peche_canne->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_peche_canne->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_peche_canne->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_peche_canne->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_peche_canne->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_peche_canne->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
	}else if(nb_act_l_<nb_appar_per_){
		for(int i=0;i<nb_act_l_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_canne_,i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_peche_canne->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_peche_canne->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_peche_canne->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_peche_canne->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_peche_canne->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_peche_canne->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
		table_appar_peche_canne->setRowCount(nb_act_l_+1);
		QTableWidgetItem *element_;
		element_=new QTableWidgetItem();
		Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_canne_,nb_act_l_);
		QString n_pk_=*pk_->adr_nom();
		int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
		element_->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
		element_->setText(traduire(Import::_noms_pk_,n_pk_,langue));
		table_appar_peche_canne->setItem(nb_act_l_,0,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*pk_->adr_niveau()));
		table_appar_peche_canne->setItem(nb_act_l_,1,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
		table_appar_peche_canne->setItem(nb_act_l_,2,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
		table_appar_peche_canne->setItem(nb_act_l_,3,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		table_appar_peche_canne->setItem(nb_act_l_,4,element_);
	}else{
		int nb_act_c_=table_appar_peche_canne->columnCount();
		for(int i=0;i<nb_act_l_-1;i++){
			table_appar_peche_canne->item(i,0)->setIcon(table_appar_peche_canne->item(i+1,0)->icon());
			for(int j=0;j<nb_act_c_;j++){
				table_appar_peche_canne->item(i,j)->setText(table_appar_peche_canne->item(i+1,j)->text());
			}
		}
		table_appar_peche_canne->item(nb_act_l_-1,0)->setIcon(QIcon());
		for(int j=0;j<nb_act_c_;j++){
			table_appar_peche_canne->item(nb_act_l_-1,j)->setText("");
		}
	}
}

int PanneauEditerEnv::ligne_act_super_canne()const{
	return table_appar_peche_super_canne->currentRow();
}

void PanneauEditerEnv::maj_appar_super_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		return;
	}
	int nb_act_l_=table_appar_peche_super_canne->rowCount();
	int nb_appar_per_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_super_canne_);
	if(nb_act_l_==nb_appar_per_){
		for(int i=0;i<nb_act_l_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_super_canne_,i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_peche_super_canne->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_peche_super_canne->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_peche_super_canne->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_peche_super_canne->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_peche_super_canne->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_peche_super_canne->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
	}else if(nb_act_l_<nb_appar_per_){
		for(int i=0;i<nb_act_l_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_super_canne_,i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_peche_super_canne->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_peche_super_canne->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_peche_super_canne->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_peche_super_canne->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_peche_super_canne->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_peche_super_canne->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
		table_appar_peche_super_canne->setRowCount(nb_act_l_+1);
		QTableWidgetItem *element_;
		element_=new QTableWidgetItem();
		Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_super_canne_,nb_act_l_);
		QString n_pk_=*pk_->adr_nom();
		int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
		element_->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
		element_->setText(traduire(Import::_noms_pk_,n_pk_,langue));
		table_appar_peche_super_canne->setItem(nb_act_l_,0,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*pk_->adr_niveau()));
		table_appar_peche_super_canne->setItem(nb_act_l_,1,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
		table_appar_peche_super_canne->setItem(nb_act_l_,2,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
		table_appar_peche_super_canne->setItem(nb_act_l_,3,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		table_appar_peche_super_canne->setItem(nb_act_l_,4,element_);
	}else{
		int nb_act_c_=table_appar_peche_super_canne->columnCount();
		for(int i=0;i<nb_act_l_-1;i++){
			table_appar_peche_super_canne->item(i,0)->setIcon(table_appar_peche_super_canne->item(i+1,0)->icon());
			for(int j=0;j<nb_act_c_;j++){
				table_appar_peche_super_canne->item(i,j)->setText(table_appar_peche_super_canne->item(i+1,j)->text());
			}
		}
		table_appar_peche_super_canne->item(nb_act_l_-1,0)->setIcon(QIcon());
		for(int j=0;j<nb_act_c_;j++){
			table_appar_peche_super_canne->item(nb_act_l_-1,j)->setText("");
		}
	}
}

int PanneauEditerEnv::ligne_act_mega_canne()const{
	return table_appar_peche_mega_canne->currentRow();
}

void PanneauEditerEnv::maj_appar_mega_canne(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		return;
	}
	int nb_act_l_=table_appar_peche_mega_canne->rowCount();
	int nb_appar_per_=PanneauEditerEnv::_environnement_en_cours_->periode_appar(Environnement::_mega_canne_);
	if(nb_act_l_==nb_appar_per_){
		for(int i=0;i<nb_act_l_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_mega_canne_,i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_peche_mega_canne->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_peche_mega_canne->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_peche_mega_canne->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_peche_mega_canne->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_peche_mega_canne->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_peche_mega_canne->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
	}else if(nb_act_l_<nb_appar_per_){
		for(int i=0;i<nb_act_l_;i++){
			Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_mega_canne_,i);
			QString n_pk_=*pk_->adr_nom();
			int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
			table_appar_peche_mega_canne->item(i,0)->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
			table_appar_peche_mega_canne->item(i,0)->setText(traduire(Import::_noms_pk_,n_pk_,langue));
			table_appar_peche_mega_canne->item(i,1)->setText(QString::number(*pk_->adr_niveau()));
			table_appar_peche_mega_canne->item(i,2)->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
			table_appar_peche_mega_canne->item(i,3)->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
			table_appar_peche_mega_canne->item(i,4)->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		}
		table_appar_peche_mega_canne->setRowCount(nb_act_l_+1);
		QTableWidgetItem *element_;
		element_=new QTableWidgetItem();
		Pokemon *pk_=PanneauEditerEnv::_environnement_en_cours_->pokemon_peche(Environnement::_mega_canne_,nb_act_l_);
		QString n_pk_=*pk_->adr_nom();
		int num_pk_=Import::_pokedex_.valeur(n_pk_)->num();
		element_->setIcon(QPixmap::fromImage(Import::_miniatures_.valeur(num_pk_)));
		element_->setText(traduire(Import::_noms_pk_,n_pk_,langue));
		table_appar_peche_mega_canne->setItem(nb_act_l_,0,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*pk_->adr_niveau()));
		table_appar_peche_mega_canne->setItem(nb_act_l_,1,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_capacites_,*pk_->adr_capacite(),langue));
		table_appar_peche_mega_canne->setItem(nb_act_l_,2,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_objets_,*pk_->adr_nom_objet(),langue));
		table_appar_peche_mega_canne->setItem(nb_act_l_,3,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_noms_genres_,*pk_->adr_genre(),langue));
		table_appar_peche_mega_canne->setItem(nb_act_l_,4,element_);
	}else{
		int nb_act_c_=table_appar_peche_mega_canne->columnCount();
		for(int i=0;i<nb_act_l_-1;i++){
			table_appar_peche_mega_canne->item(i,0)->setIcon(table_appar_peche_mega_canne->item(i+1,0)->icon());
			for(int j=0;j<nb_act_c_;j++){
				table_appar_peche_mega_canne->item(i,j)->setText(table_appar_peche_mega_canne->item(i+1,j)->text());
			}
		}
		table_appar_peche_mega_canne->item(nb_act_l_-1,0)->setIcon(QIcon());
		for(int j=0;j<nb_act_c_;j++){
			table_appar_peche_mega_canne->item(nb_act_l_-1,j)->setText("");
		}
	}
}

void PanneauEditerEnv::activer_bouton(int _indice){
	editer_perso->setEnabled(false);
	editer_dresseur->setEnabled(false);
	editer_champion->setEnabled(false);
	choix_imgs_arbres->setEnabled(false);
	choix_imgs_rochers_destructibles->setEnabled(false);
	choix_imgs_rochers_amovibles->setEnabled(false);
	choix_imgs_tourbillons->setEnabled(false);
	editer_pk_leg->setEnabled(false);
	editer_don_pk->setEnabled(false);
	editer_objet->setEnabled(false);
	if(_indice==AUTRE_PERSO){
		editer_perso->setEnabled(true);
	}else if(_indice==DRESSEUR_LIGUE){
		editer_dresseur_ligue->setEnabled(true);
	}else if(_indice==DRESSEUR){
		editer_dresseur->setEnabled(true);
	}else if(_indice==CHAMPION){
		editer_champion->setEnabled(true);
	}else if(_indice==ARBRE){
		choix_imgs_arbres->setEnabled(true);
	}else if(_indice==ROCHER_DESTR){
		choix_imgs_rochers_destructibles->setEnabled(true);
	}else if(_indice==ROCHER_AMOV){
		choix_imgs_rochers_amovibles->setEnabled(true);
	}else if(_indice==TOURBILLON){
		choix_imgs_tourbillons->setEnabled(true);
	}else if(_indice==PK_LEG){
		editer_pk_leg->setEnabled(true);
	}else if(_indice==DON_PK){
		editer_don_pk->setEnabled(true);
	}else if(_indice==OBJET){
		editer_objet->setEnabled(true);
	}
	selection=(PanneauEditerEnv::RolesTuile)_indice;
}

void PanneauEditerEnv::maj_image_tuile(const QString& _tuile){
	int _indice=choix_imgs_tuiles->findText(_tuile);
	if(_indice>-1&&PanneauEditerEnv::_tuile_en_cours_!=NULL){
		*PanneauEditerEnv::_tuile_en_cours_->adr_nom_image()=choix_imgs_tuiles->currentText();
		emit image_tuile_changee(Import::_tuiles_importees_.valeur(*PanneauEditerEnv::_tuile_en_cours_->adr_nom_image()));
	}
}

void PanneauEditerEnv::maj_nb_pas(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		return;
	}
	*_environnement_en_cours_->adr_nb_pas_moyen_pour_appar()=appar_per->value();
}

void PanneauEditerEnv::maj_type_env(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		return;
	}
	if(type_env->findText(type_env->currentText())<0){
		return;
	}
	if(type_env->currentText()==""){
		*_environnement_en_cours_->type_env()="";
		return;
	}
	*_environnement_en_cours_->type_env()=Utilitaire::rever_traduire(Import::_noms_envir_,type_env->currentText(),langue);
}

void PanneauEditerEnv::maj_muret(){
	if(PanneauEditerEnv::_environnement_en_cours_==NULL){
		return;
	}
	*_environnement_en_cours_->adr_muret()=QPair<int,int>(muret_h->value(),muret_v->value());
}

PanneauEditerEnv::~PanneauEditerEnv(){
	delete groupe_type_tuile;
	groupe_type_tuile=NULL;
}


