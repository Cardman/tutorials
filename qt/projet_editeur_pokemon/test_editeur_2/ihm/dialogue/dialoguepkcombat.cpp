#include "ihm/dialogue/dialoguepkcombat.h"
#include "ihm/panneau/panneauediteurenv.h"
#include "serialisable/pokemon/pokemondresse.h"
#include "base_donnees/import.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/attaques/ficheattaque.h"
#include "autre/utilitaire.h"
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QTableWidget>
#include <QMessageBox>
#include <QCloseEvent>

const HashMap<QString,QStringList> DialoguePkCombat::_elements_ihm_=DialoguePkCombat::init_elements_ihm();

HashMap<QString,QStringList> DialoguePkCombat::init_elements_ihm(){
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

QString DialoguePkCombat::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString DialoguePkCombat::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialoguePkCombat::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialoguePkCombat::DialoguePkCombat(int _langue,DialoguePkCombat::TypeDialogue _type,QWidget *_parent,DialoguePkCombat::TypeRencontre _type_r,bool _leg_deja_pres):QDialog(_parent){
	//PK_DRESSE,PK_SAUVAGE,PK_DONNE,PK_LEG_FIXE,PK_DEPART
	rejeter=true;
	langue=_langue;
	type_dialogue=_type;
	type_rencontre=_type_r;
	//pk_edite=NULL
	//pk_dresse_edite=NULL
	if(_type==DialoguePkCombat::PK_DRESSE){
		setWindowTitle(traduire("TITRE_DR"));
	}else if(_type==DialoguePkCombat::PK_SAUVAGE){
		setWindowTitle(traduire("TITRE_SAUV"));
	}else if(_type==DialoguePkCombat::PK_DONNE){
		setWindowTitle(traduire("TITRE_DONNE"));
	}else if(_type==DialoguePkCombat::PK_LEG_FIXE){
		setWindowTitle(traduire("TITRE_LEG_FIXE"));
	}else if(_type==DialoguePkCombat::PK_DEPART){
		setWindowTitle(traduire("TITRE_DEPART"));
	}
	nom_pk=new QComboBox();//TODO traduire de la langue vers le francais pour le retour
	if(_type==DialoguePkCombat::PK_SAUVAGE){
		foreach(QString l,Import::_noms_pk_){
			QString n_pk_=l.split("\t")[langue];
			FichePokemon *fiche_pk_=Import::_pokedex_.valeur(l.split("\t")[Import::_indice_francais_]);
			if(fiche_pk_->rep_genr()!="<LEG>"||!_leg_deja_pres){
				nom_pk->addItem(n_pk_);
			}
		}
	}else{
		foreach(QString l,Import::_noms_pk_){
			nom_pk->addItem(l.split("\t")[langue]);
		}
	}
	nom_pk->setEditable(true);
	connect(nom_pk,SIGNAL(editTextChanged(QString)),this,SLOT(maj_fct_nom_pk()));
	QFormLayout *form_=new QFormLayout();
	form_->addRow(traduire("NOM_PK"),nom_pk);
	QString n_pk_=nom_pk->currentText();
	n_pk_=traduire_revert(Import::_noms_pk_,n_pk_,langue);;
	FichePokemon *fiche_pk_=Import::_pokedex_.valeur(n_pk_);
	if(_type!=DialoguePkCombat::PK_LEG_FIXE&&_type!=DialoguePkCombat::PK_DEPART){
		genre_pk=new QComboBox();
		QString rep_genre_=fiche_pk_->rep_genr();
		if(rep_genre_=="<LEG>"||rep_genre_=="ASSEXUE"){
			//genre_pk->addItem("ASSEXUE")
			genre_pk->addItem(traduire(Import::_noms_genres_,"ASSEXUE",langue));
		}else if(rep_genre_=="MIXTE"){
			//genre_pk->addItem("FEMELLE")
			//genre_pk->addItem("MALE")
			foreach(QString g,Import::_noms_genres_){
				if(g.indexOf(QRegExp("^([^\\t]+\\t){"+QString::number(Import::_indice_francais_)+"}ASSEXUE"))<0){
					genre_pk->addItem(g.split("\t")[langue]);
				}
			}
		}else{
			//genre_pk->addItem(rep_genre_)
			genre_pk->addItem(traduire(Import::_noms_genres_,rep_genre_,langue));
		}
		form_->addRow(traduire("GENRE"),genre_pk);
	}else{
		genre_pk=NULL;
	}
	niveau_pk=new QSpinBox();
	int min_niv_=(int)Import::constante_numerique("NIVEAU_PK_MIN");
	int max_niv_=(int)Import::constante_numerique("NIVEAU_PK_MAX");
	int def_niv_=(int)Import::constante_numerique("NIVEAU_PK_DEF");
	niveau_pk->setRange(min_niv_,max_niv_);
	niveau_pk->setValue(def_niv_);
	connect(niveau_pk,SIGNAL(valueChanged(int)),this,SLOT(maj_fct_niveau_pk()));
	form_->addRow(traduire("NIVEAU"),niveau_pk);
	capacite_pk=new QComboBox();
	foreach(QString l,fiche_pk_->capac()){
		capacite_pk->addItem(traduire(Import::_noms_capacites_,l,langue));
		//capacite_pk->addItem(l)
	}
	capacite_pk->setEditable(true);
	form_->addRow(traduire("CAPACITE"),capacite_pk);
	objet_pk=new QComboBox();
	foreach(QString l,Import::_objets_.cles()){
		objet_pk->addItem(traduire(Import::_noms_objets_,l,langue));
		//objet_pk->addItem(l)
	}
	objet_pk->addItem("");
	objet_pk->setEditable(true);
	form_->addRow(traduire("OBJET"),objet_pk);
	if(_type==DialoguePkCombat::PK_DRESSE){//
		QVBoxLayout *boutons_categ_attaq_lay_=new QVBoxLayout();
		boutons_categ_attaques=new QButtonGroup();
		QRadioButton *radio_;
		radio_=new QRadioButton(traduire(Import::_noms_categories_,"PHYSIQUE",langue));
		boutons_categ_attaq_lay_->addWidget(radio_);
		boutons_categ_attaques->addButton(radio_,PHYSIQUE);
		radio_=new QRadioButton(traduire(Import::_noms_categories_,"SPECIALE",langue));
		boutons_categ_attaq_lay_->addWidget(radio_);
		boutons_categ_attaques->addButton(radio_,SPECIALE);
		radio_=new QRadioButton(traduire(Import::_noms_categories_,"AUTRE",langue));
		boutons_categ_attaq_lay_->addWidget(radio_);
		boutons_categ_attaques->addButton(radio_,AUTRE);
		connect(boutons_categ_attaques,SIGNAL(buttonReleased(int)),this,SLOT(maj_fct_categ_attaques_pk(int)));
		form_->addRow(traduire("CATEGORIE"),boutons_categ_attaq_lay_);
		nom_attaque_pk=new QComboBox();
		nom_attaque_pk->setEditable(true);
		form_->addRow(traduire("NOM_ATTAQUE"),nom_attaque_pk);
	}else{
		boutons_categ_attaques=NULL;
		nom_attaque_pk=NULL;
	}
	QStringList attributs_att_;
	attributs_att_<<traduire("ETIQUETTE_NOM");
	attributs_att_<<traduire("ETIQUETTE_CATEGORIE");
	attributs_att_<<traduire("ETIQUETTE_DIRECTE");
	attributs_att_<<traduire("ETIQUETTE_TYPE");
	attributs_att_<<traduire("ETIQUETTE_PP");
	attributs_att_<<traduire("ETIQUETTE_PRECISION");
	attributs_att_<<traduire("ETIQUETTE_PRIORITE");
	attributs_att_<<traduire("ETIQUETTE_PUISSANCE");
	if(_type==DialoguePkCombat::PK_DRESSE){
		table_attaques=new QTableWidget((int)Import::constante_numerique("MAX_ATT"),attributs_att_.size());
		table_attaques->setHorizontalHeaderLabels(attributs_att_);
		int nb_l_=table_attaques->rowCount();
		int nb_c_=table_attaques->columnCount();
		for(int i=0;i<nb_l_;i++){
			for(int j=0;j<nb_c_;j++){
				QTableWidgetItem *element_=new QTableWidgetItem();
				element_->setText("");
				table_attaques->setItem(i,j,element_);
			}
		}
		form_->addRow(traduire("ATTAQUES"),table_attaques);
		QPushButton *bouton_;
		bouton_=new QPushButton(traduire("AJOUTER_ATTAQUE"));
		connect(bouton_,SIGNAL(clicked()),this,SLOT(ajout_attaque()));
		QPushButton *bouton_2_;
		bouton_2_=new QPushButton(traduire("SUPPRIMER_ATTAQUE"));
		connect(bouton_2_,SIGNAL(clicked()),this,SLOT(suppression_attaque()));
		form_->addRow(bouton_,bouton_2_);
	}else{
		table_attaques=new QTableWidget((int)Import::constante_numerique("MAX_ATT"),attributs_att_.size());
		table_attaques->setHorizontalHeaderLabels(attributs_att_);
		int nb_attaq_=Utilitaire::max_min<int>((int)Import::constante_numerique("MAX_ATT"),fiche_pk_->atts().size()).second;
		QList<QPair<uchar,QString> > attaques_pok_=fiche_pk_->atts();
		for(int i=0;i<nb_attaq_;i++){
			QString nom_attaq_=attaques_pok_[i].second;
			FicheAttaque *fiche_attaq_=Import::_attaques_.valeur(nom_attaq_);
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText(nom_attaq_);
			table_attaques->setItem(i,0,element_);
			element_=new QTableWidgetItem();
			element_->setText(fiche_attaq_->cat());
			table_attaques->setItem(i,1,element_);
			element_=new QTableWidgetItem();
			if(fiche_attaq_->cat()=="AUTRE"){
				element_->setText("x");
			}else if(fiche_attaq_->dir()){
				element_->setText(traduire("OUI"));
			}else{
				element_->setText(traduire("NON"));
			}
			table_attaques->setItem(i,2,element_);
			element_=new QTableWidgetItem();
			element_->setText(fiche_attaq_->tp());
			table_attaques->setItem(i,3,element_);
			element_=new QTableWidgetItem();
			element_->setText(QString::number(fiche_attaq_->pps()));
			table_attaques->setItem(i,4,element_);
			element_=new QTableWidgetItem();
			element_->setText(QString::number(fiche_attaq_->prec()));
			table_attaques->setItem(i,5,element_);
			element_=new QTableWidgetItem();
			element_->setText(QString::number(fiche_attaq_->prio()));
			table_attaques->setItem(i,6,element_);
			element_=new QTableWidgetItem();
			element_->setText(QString::number(fiche_attaq_->puis()));
			table_attaques->setItem(i,7,element_);
		}
		form_->addRow(traduire("ATTAQUES"),table_attaques);
	}
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(acceptation()));
	form_->addRow("",valider_);
	setLayout(form_);
}

Pokemon DialoguePkCombat::nv_pk()const{
	Pokemon pk_;
	//*pk_.adr_nom()=nom_pk->currentText()
	*pk_.adr_nom()=traduire_revert(Import::_noms_pk_,nom_pk->currentText(),langue);
	*pk_.adr_niveau()=(uchar)niveau_pk->value();
	if(genre_pk!=NULL){
		//*pk_.adr_genre()=genre_pk->currentText()
		*pk_.adr_genre()=traduire_revert(Import::_noms_genres_,genre_pk->currentText(),langue);
	}else{
		*pk_.adr_genre()="ASSEXUE";
	}
	//*pk_.adr_capacite()=capacite_pk->currentText()
	*pk_.adr_capacite()=traduire_revert(Import::_noms_capacites_,capacite_pk->currentText(),langue);
	//*pk_.adr_nom_objet()=objet_pk->currentText()
	*pk_.adr_nom_objet()=traduire_revert(Import::_noms_objets_,objet_pk->currentText(),langue);
	return pk_;
}

PokemonDresse DialoguePkCombat::nv_pk_dresse()const{
	return PokemonDresse(nv_pk(),attaques);
}

void DialoguePkCombat::maj_pk_edite(Pokemon* _pk_ed){
	if(type_dialogue==DialoguePkCombat::PK_DRESSE){
		setWindowTitle(traduire("TITRE_DR_2"));
	}else if(type_dialogue==DialoguePkCombat::PK_SAUVAGE){
		setWindowTitle(traduire("TITRE_SAUV_2"));
	}else if(type_dialogue==DialoguePkCombat::PK_DONNE){
		setWindowTitle(traduire("TITRE_DONNE_2"));
	}else if(type_dialogue==DialoguePkCombat::PK_LEG_FIXE){
		setWindowTitle(traduire("TITRE_LEG_FIXE_2"));
	}else if(type_dialogue==DialoguePkCombat::PK_DEPART){
		setWindowTitle(traduire("TITRE_DEPART_2"));
	}
	//pk_edite=_pk_ed
	QString n_pk_=*_pk_ed->adr_nom();
	FichePokemon *fiche_pk_=Import::_pokedex_.valeur(n_pk_);
	if(type_dialogue==DialoguePkCombat::PK_SAUVAGE&&fiche_pk_->rep_genr()=="<LEG>"){
		foreach(QString l,Import::_noms_pk_){
			QString n_pk_2_=l.split("\t")[langue];
			FichePokemon *fiche_pk_2_=Import::_pokedex_.valeur(n_pk_2_);
			if(fiche_pk_2_->rep_genr()=="<LEG>"){
				nom_pk->addItem(n_pk_2_);
			}
		}
	}
	//nom_pk->setEditText(n_pk_)
	nom_pk->setEditText(traduire(Import::_noms_pk_,n_pk_,langue));
	QString rep_genre_=fiche_pk_->rep_genr();
	if(genre_pk!=NULL){
		genre_pk->clear();
		if(rep_genre_=="<LEG>"||rep_genre_=="ASSEXUE"){
			//genre_pk->addItem("ASSEXUE")
			genre_pk->addItem(traduire(Import::_noms_genres_,"ASSEXUE",langue));
		}else if(rep_genre_=="MIXTE"){
			foreach(QString g,Import::_noms_genres_){
				if(g.indexOf(QRegExp("^([^\\t]+\\t){"+QString::number(Import::_indice_francais_)+"}ASSEXUE"))<0){
					genre_pk->addItem(g.split("\t")[langue]);
				}
			}
			//genre_pk->addItem("FEMELLE")
			//genre_pk->addItem("MALE")
		}else{
			//genre_pk->addItem(rep_genre_)
			genre_pk->addItem(traduire(Import::_noms_genres_,rep_genre_,langue));
		}
		genre_pk->setEditText(traduire(Import::_noms_genres_,*_pk_ed->adr_genre(),langue));
		//genre_pk->setEditText(*_pk_ed->adr_genre())
	}
	capacite_pk->clear();
	foreach(QString l,fiche_pk_->capac()){
		capacite_pk->addItem(traduire(Import::_noms_capacites_,l,langue));
		//capacite_pk->addItem(l)
	}
	capacite_pk->setEditText(traduire(Import::_noms_capacites_,*_pk_ed->adr_capacite(),langue));
	//capacite_pk->setEditText(*_pk_ed->adr_capacite())
	objet_pk->setEditText(traduire(Import::_noms_objets_,*_pk_ed->adr_nom_objet(),langue));
	//objet_pk->setEditText(*_pk_ed->adr_nom_objet())
	niveau_pk->setValue(*_pk_ed->adr_niveau());
	if(nom_attaque_pk==NULL){
		QStringList attaques_;
		int nb_attaq_=Utilitaire::max_min<int>((int)Import::constante_numerique("MAX_ATT"),fiche_pk_->atts().size()).second;
		int indice_pre_attaq_=fiche_pk_->atts().size()-1;
		QList<QPair<uchar,QString> > attaques_pok_=fiche_pk_->atts();
		while(indice_pre_attaq_>-1&&attaques_pok_[indice_pre_attaq_].first>niveau_pk->value()){
			indice_pre_attaq_--;
		}
		for(int i=indice_pre_attaq_;i>-1;i--){
			if(attaques_.size()==nb_attaq_){
				break;
			}
			attaques_<<attaques_pok_[i].second;
		}
		attaques_.removeDuplicates();
		nb_attaq_=attaques_.size();
		for(int i=0;i<nb_attaq_;i++){
			QString nom_attaq_=attaques_[i];
			FicheAttaque *fiche_attaq_=Import::_attaques_.valeur(nom_attaq_);
			QTableWidgetItem *element_=table_attaques->item(i,0);
			element_->setText(traduire(Import::_noms_attaques_,nom_attaq_,langue));
			//element_->setText(nom_attaq_)
			element_=table_attaques->item(i,1);
			element_->setText(traduire(Import::_noms_categories_,fiche_attaq_->cat(),langue));
			//element_->setText(fiche_attaq_->cat())
			element_=table_attaques->item(i,2);
			if(fiche_attaq_->cat()=="AUTRE"){
				element_->setText("x");
			}else if(fiche_attaq_->dir()){
				element_->setText(traduire("OUI"));
			}else{
				element_->setText(traduire("NON"));
			}
			element_=table_attaques->item(i,3);
			element_->setText(traduire(Import::_noms_types_,fiche_attaq_->tp(),langue));
			//element_->setText(fiche_attaq_->tp())
			element_=table_attaques->item(i,4);
			element_->setText(QString::number(fiche_attaq_->pps()));
			element_=table_attaques->item(i,5);
			element_->setText(QString::number(fiche_attaq_->prec()));
			element_=table_attaques->item(i,6);
			element_->setText(QString::number(fiche_attaq_->prio()));
			element_=table_attaques->item(i,7);
			element_->setText(QString::number(fiche_attaq_->puis()));
		}
		int nb_l_=table_attaques->rowCount();
		int nb_c_=table_attaques->columnCount();
		for(int i=nb_attaq_;i<nb_l_;i++){
			for(int j=0;j<nb_c_;j++){
				QTableWidgetItem *element_=table_attaques->item(i,j);
				element_->setText("");
			}
		}
	}
}

void DialoguePkCombat::maj_pk_dresse_edite(PokemonDresse* _pk_ed){
	maj_pk_edite(_pk_ed);
	//pk_dresse_edite=_pk_ed
	attaques=*_pk_ed->adr_attaques();
	int nb_attaq_=attaques.size();
	for(int i=0;i<nb_attaq_;i++){
		QString nom_attaq_=attaques[i];
		FicheAttaque *fiche_attaq_=Import::_attaques_.valeur(nom_attaq_);
		QTableWidgetItem *element_=table_attaques->item(i,0);
		element_->setText(traduire(Import::_noms_attaques_,nom_attaq_,langue));
		//element_->setText(nom_attaq_)
		element_=table_attaques->item(i,1);
		element_->setText(traduire(Import::_noms_categories_,fiche_attaq_->cat(),langue));
		//element_->setText(fiche_attaq_->cat())
		element_=table_attaques->item(i,2);
		if(fiche_attaq_->cat()=="AUTRE"){
			element_->setText("x");
		}else if(fiche_attaq_->dir()){
			element_->setText(traduire("OUI"));
		}else{
			element_->setText(traduire("NON"));
		}
		element_=table_attaques->item(i,3);
		element_->setText(traduire(Import::_noms_types_,fiche_attaq_->tp(),langue));
		//element_->setText(fiche_attaq_->tp())
		element_=table_attaques->item(i,4);
		element_->setText(QString::number(fiche_attaq_->pps()));
		element_=table_attaques->item(i,5);
		element_->setText(QString::number(fiche_attaq_->prec()));
		element_=table_attaques->item(i,6);
		element_->setText(QString::number(fiche_attaq_->prio()));
		element_=table_attaques->item(i,7);
		element_->setText(QString::number(fiche_attaq_->puis()));
	}

}

void DialoguePkCombat::maj_fct_nom_pk(){
	QString n_pk_=nom_pk->currentText();
	if(nom_pk->findText(n_pk_)<0){
		return;
	}
	/*if(!Import::_pokedex_.cles().contains(n_pk_)){
		return
	}*/
	n_pk_=traduire_revert(Import::_noms_pk_,n_pk_,langue);
	FichePokemon *fiche_pk_=Import::_pokedex_.valeur(n_pk_);
	QString rep_genre_=fiche_pk_->rep_genr();
	if(genre_pk!=NULL){
		genre_pk->clear();
		if(rep_genre_=="<LEG>"||rep_genre_=="ASSEXUE"){
			genre_pk->addItem(traduire(Import::_noms_genres_,"ASSEXUE",langue));
			//genre_pk->addItem("ASSEXUE")
		}else if(rep_genre_=="MIXTE"){
			foreach(QString g,Import::_noms_genres_){
				//g.indexOf(QRegExp("^([^\\t]+\\t){"+QString::number(Import::_indice_francais_)+"}ASSEXUE"))<0
				//
				if(g.indexOf(QRegExp("^([^\\t]+\\t){"+QString::number(Import::_indice_francais_)+"}ASSEXUE"))<0){
					genre_pk->addItem(g.split("\t")[langue]);
				}
			}
			//genre_pk->addItem("FEMELLE")
			//genre_pk->addItem("MALE")
		}else{
			genre_pk->addItem(traduire(Import::_noms_genres_,rep_genre_,langue));
			//genre_pk->addItem(rep_genre_)
		}
	}
	capacite_pk->clear();
	foreach(QString l,fiche_pk_->capac()){
		capacite_pk->addItem(traduire(Import::_noms_capacites_,l,langue));
		//capacite_pk->addItem(l)
	}
	if(nom_attaque_pk!=NULL){
		int indice_=boutons_categ_attaques->checkedId();
		QStringList attaques_;
		attaques_<<fiche_pk_->mt();
		foreach(uchar a,fiche_pk_->ct()){
			attaques_<<Import::_ct_.valeur(a);
		}
		foreach(uchar a,fiche_pk_->cs()){
			attaques_<<Import::_cs_.valeur(a);
		}
		int nb_attaq_=fiche_pk_->atts().size();
		QList<QPair<uchar,QString> > attaques_pok_=fiche_pk_->atts();
		for(int i=0;i<nb_attaq_;i++){
			if(attaques_pok_[i].first<=niveau_pk->value()){
				attaques_<<attaques_pok_[i].second;
			}
		}
		attaques_.removeDuplicates();
		QStringList attaques_def_;
		foreach(QString a,attaques_){
			if(indice_==PHYSIQUE){
				if(Import::_attaques_.valeur(a)->cat()=="PHYSIQUE"){
					attaques_def_<<a;
				}
			}else if(indice_==SPECIALE){
				if(Import::_attaques_.valeur(a)->cat()=="SPECIALE"){
					attaques_def_<<a;
				}
			}else if(indice_==AUTRE){
				if(Import::_attaques_.valeur(a)->cat()=="AUTRE"){
					attaques_def_<<a;
				}
			}
		}
		nom_attaque_pk->clear();
		foreach(QString a,attaques_def_){
			nom_attaque_pk->addItem(traduire(Import::_noms_attaques_,a,langue));
			//nom_attaque_pk->addItem(a)
		}
		int nb_l_=table_attaques->rowCount();
		int nb_c_=table_attaques->columnCount();
		for(int i=0;i<nb_l_;i++){
			for(int j=0;j<nb_c_;j++){
				QTableWidgetItem *element_=table_attaques->item(i,j);
				element_->setText("");
			}
		}
		attaques.clear();
	}else{
		QStringList attaques_;
		int nb_attaq_=Utilitaire::max_min<int>((int)Import::constante_numerique("MAX_ATT"),fiche_pk_->atts().size()).second;
		int indice_pre_attaq_=fiche_pk_->atts().size()-1;
		QList<QPair<uchar,QString> > attaques_pok_=fiche_pk_->atts();
		while(indice_pre_attaq_>-1&&attaques_pok_[indice_pre_attaq_].first>niveau_pk->value()){
			indice_pre_attaq_--;
		}
		for(int i=indice_pre_attaq_;i>-1;i--){
			if(attaques_.size()==nb_attaq_){
				break;
			}
			attaques_<<attaques_pok_[i].second;
		}
		attaques_.removeDuplicates();
		nb_attaq_=attaques_.size();
		for(int i=0;i<nb_attaq_;i++){
			QString nom_attaq_=attaques_[i];
			FicheAttaque *fiche_attaq_=Import::_attaques_.valeur(nom_attaq_);
			QTableWidgetItem *element_=table_attaques->item(i,0);
			element_->setText(traduire(Import::_noms_attaques_,nom_attaq_,langue));
			//element_->setText(nom_attaq_)
			element_=table_attaques->item(i,1);
			element_->setText(traduire(Import::_noms_categories_,fiche_attaq_->cat(),langue));
			//element_->setText(fiche_attaq_->cat())
			element_=table_attaques->item(i,2);
			if(fiche_attaq_->cat()=="AUTRE"){
				element_->setText("x");
			}else if(fiche_attaq_->dir()){
				element_->setText(traduire("OUI"));
			}else{
				element_->setText(traduire("NON"));
			}
			element_=table_attaques->item(i,3);
			element_->setText(traduire(Import::_noms_types_,fiche_attaq_->tp(),langue));
			//element_->setText(fiche_attaq_->tp())
			element_=table_attaques->item(i,4);
			element_->setText(QString::number(fiche_attaq_->pps()));
			element_=table_attaques->item(i,5);
			element_->setText(QString::number(fiche_attaq_->prec()));
			element_=table_attaques->item(i,6);
			element_->setText(QString::number(fiche_attaq_->prio()));
			element_=table_attaques->item(i,7);
			element_->setText(QString::number(fiche_attaq_->puis()));
		}
		int nb_l_=table_attaques->rowCount();
		int nb_c_=table_attaques->columnCount();
		for(int i=nb_attaq_;i<nb_l_;i++){
			for(int j=0;j<nb_c_;j++){
				QTableWidgetItem *element_=table_attaques->item(i,j);
				element_->setText("");
			}
		}
	}
}

void DialoguePkCombat::maj_fct_niveau_pk(){
	QString n_pk_=nom_pk->currentText();
	if(nom_pk->findText(n_pk_)<0){
		return;
	}
	/*if(!Import::_pokedex_.cles().contains(n_pk_)){
		return
	}*/
	n_pk_=traduire_revert(Import::_noms_pk_,n_pk_,langue);
	FichePokemon *fiche_pk_=Import::_pokedex_.valeur(n_pk_);
	if(nom_attaque_pk!=NULL){
		int indice_=boutons_categ_attaques->checkedId();
		QStringList attaques_;
		attaques_<<fiche_pk_->mt();
		foreach(uchar a,fiche_pk_->ct()){
			attaques_<<Import::_ct_.valeur(a);
		}
		foreach(uchar a,fiche_pk_->cs()){
			attaques_<<Import::_cs_.valeur(a);
		}
		int nb_attaq_=fiche_pk_->atts().size();
		QList<QPair<uchar,QString> > attaques_pok_=fiche_pk_->atts();
		for(int i=0;i<nb_attaq_;i++){
			if(attaques_pok_[i].first<=niveau_pk->value()){
				attaques_<<attaques_pok_[i].second;
			}
		}
		attaques_.removeDuplicates();
		QStringList attaques_def_;
		foreach(QString a,attaques_){
			if(indice_==PHYSIQUE){
				if(Import::_attaques_.valeur(a)->cat()=="PHYSIQUE"){
					attaques_def_<<a;
				}
			}else if(indice_==SPECIALE){
				if(Import::_attaques_.valeur(a)->cat()=="SPECIALE"){
					attaques_def_<<a;
				}
			}else if(indice_==AUTRE){
				if(Import::_attaques_.valeur(a)->cat()=="AUTRE"){
					attaques_def_<<a;
				}
			}
		}
		nom_attaque_pk->clear();
		foreach(QString a,attaques_def_){
			nom_attaque_pk->addItem(traduire(Import::_noms_attaques_,a,langue));
			//nom_attaque_pk->addItem(a)
		}
	}else{
		QStringList attaques_;
		int nb_attaq_=Utilitaire::max_min<int>((int)Import::constante_numerique("MAX_ATT"),fiche_pk_->atts().size()).second;
		int indice_pre_attaq_=fiche_pk_->atts().size()-1;
		QList<QPair<uchar,QString> > attaques_pok_=fiche_pk_->atts();
		while(indice_pre_attaq_>-1&&attaques_pok_[indice_pre_attaq_].first>niveau_pk->value()){
			indice_pre_attaq_--;
		}
		for(int i=indice_pre_attaq_;i>-1;i--){
			if(attaques_.size()==nb_attaq_){
				break;
			}
			attaques_<<attaques_pok_[i].second;
		}
		attaques_.removeDuplicates();
		nb_attaq_=attaques_.size();
		for(int i=0;i<nb_attaq_;i++){
			QString nom_attaq_=attaques_[i];
			FicheAttaque *fiche_attaq_=Import::_attaques_.valeur(nom_attaq_);
			QTableWidgetItem *element_=table_attaques->item(i,0);
			element_->setText(traduire(Import::_noms_attaques_,nom_attaq_,langue));
			//element_->setText(nom_attaq_)
			element_=table_attaques->item(i,1);
			element_->setText(traduire(Import::_noms_categories_,fiche_attaq_->cat(),langue));
			//element_->setText(fiche_attaq_->cat())
			element_=table_attaques->item(i,2);
			if(fiche_attaq_->cat()=="AUTRE"){
				element_->setText("x");
			}else if(fiche_attaq_->dir()){
				element_->setText(traduire("OUI"));
			}else{
				element_->setText(traduire("NON"));
			}
			element_=table_attaques->item(i,3);
			element_->setText(traduire(Import::_noms_types_,fiche_attaq_->tp(),langue));
			//element_->setText(fiche_attaq_->tp())
			element_=table_attaques->item(i,4);
			element_->setText(QString::number(fiche_attaq_->pps()));
			element_=table_attaques->item(i,5);
			element_->setText(QString::number(fiche_attaq_->prec()));
			element_=table_attaques->item(i,6);
			element_->setText(QString::number(fiche_attaq_->prio()));
			element_=table_attaques->item(i,7);
			element_->setText(QString::number(fiche_attaq_->puis()));
		}
		int nb_l_=table_attaques->rowCount();
		int nb_c_=table_attaques->columnCount();
		for(int i=nb_attaq_;i<nb_l_;i++){
			for(int j=0;j<nb_c_;j++){
				QTableWidgetItem *element_=table_attaques->item(i,j);
				element_->setText("");
			}
		}
	}
}

void DialoguePkCombat::maj_fct_categ_attaques_pk(int _indice){
	QString n_pk_=nom_pk->currentText();
	if(nom_pk->findText(n_pk_)<0){
		return;
	}
	/*if(!Import::_pokedex_.cles().contains(n_pk_)){
		return
	}*/
	n_pk_=traduire_revert(Import::_noms_pk_,n_pk_,langue);
	FichePokemon *fiche_pk_=Import::_pokedex_.valeur(n_pk_);
	QStringList attaques_;
	attaques_<<fiche_pk_->mt();
	foreach(uchar a,fiche_pk_->ct()){
		attaques_<<Import::_ct_.valeur(a);
	}
	foreach(uchar a,fiche_pk_->cs()){
		attaques_<<Import::_cs_.valeur(a);
	}
	int nb_attaq_=fiche_pk_->atts().size();
	QList<QPair<uchar,QString> > attaques_pok_=fiche_pk_->atts();
	for(int i=0;i<nb_attaq_;i++){
		if(attaques_pok_[i].first<=niveau_pk->value()){
			attaques_<<attaques_pok_[i].second;
		}
	}
	attaques_.removeDuplicates();
	QStringList attaques_def_;
	foreach(QString a,attaques_){
		if(_indice==PHYSIQUE){
			if(Import::_attaques_.valeur(a)->cat()=="PHYSIQUE"){
				attaques_def_<<a;
			}
		}else if(_indice==SPECIALE){
			if(Import::_attaques_.valeur(a)->cat()=="SPECIALE"){
				attaques_def_<<a;
			}
		}else if(_indice==AUTRE){
			if(Import::_attaques_.valeur(a)->cat()=="AUTRE"){
				attaques_def_<<a;
			}
		}
	}
	nom_attaque_pk->clear();
	foreach(QString a,attaques_def_){
		nom_attaque_pk->addItem(traduire(Import::_noms_attaques_,a,langue));
		//nom_attaque_pk->addItem(a)
	}
}

void DialoguePkCombat::ajout_attaque(){
	//
	//traduire_revert
	QString attaque_=nom_attaque_pk->currentText();
	//if(!Import::_attaques_.cles().contains(attaque_)){//||nom_attaque_pk.findText(attaque_)<0
	QStringList args_;
	if(nom_attaque_pk->findText(attaque_)<0){
		args_<<attaque_;
		QMessageBox::critical(this,traduire("ERREUR"),Utilitaire::formatter(traduire("ATTAQUE_INVAL"),args_));
		return;
	}
	QString attaque_fr_=traduire_revert(Import::_noms_attaques_,attaque_,langue);
	if(attaques.contains(attaque_fr_)||attaques.size()>=(int)Import::constante_numerique("MAX_ATT")){
		QString erreur_;
		if(attaques.contains(attaque_fr_)){
			args_<<attaque_fr_;
			erreur_+=Utilitaire::formatter(traduire("ATTAQUE_DEJA_PRESENTE"),args_)+"\n";
		}
		if(attaques.size()>=(int)Import::constante_numerique("MAX_ATT")){
			erreur_+=traduire("NB_MAX_ATTAQUES")+"\n";
		}
		QMessageBox::critical(this,traduire("ERREUR"),erreur_);
		return;
	}
	//attaque_=traduire_revert(Import::_noms_attaques_,attaque_,langue)
	FicheAttaque *fiche_attaq_=Import::_attaques_.valeur(attaque_fr_);
	QTableWidgetItem *element_=table_attaques->item(attaques.size(),0);
	element_->setText(attaque_);
	//element_->setText(attaque_)
	element_=table_attaques->item(attaques.size(),1);
	element_->setText(traduire(Import::_noms_categories_,fiche_attaq_->cat(),langue));
	//element_->setText(fiche_attaq_->cat())
	element_=table_attaques->item(attaques.size(),2);
	if(fiche_attaq_->cat()=="AUTRE"){
		element_->setText("x");
	}else if(fiche_attaq_->dir()){
		element_->setText(traduire("OUI"));
	}else{
		element_->setText(traduire("NON"));
	}
	element_=table_attaques->item(attaques.size(),3);
	element_->setText(traduire(Import::_noms_types_,fiche_attaq_->tp(),langue));
	//element_->setText(fiche_attaq_->tp())
	element_=table_attaques->item(attaques.size(),4);
	element_->setText(QString::number(fiche_attaq_->pps()));
	element_=table_attaques->item(attaques.size(),5);
	element_->setText(QString::number(fiche_attaq_->prec()));
	element_=table_attaques->item(attaques.size(),6);
	element_->setText(QString::number(fiche_attaq_->prio()));
	element_=table_attaques->item(attaques.size(),7);
	element_->setText(QString::number(fiche_attaq_->puis()));
	attaques<<attaque_fr_;
	QMessageBox::information(this,traduire("SUCCES"),traduire("AJOUT_ATT_FINI"));
}

void DialoguePkCombat::suppression_attaque(){
	int indice_=table_attaques->currentRow();
	if(indice_>=attaques.size()||indice_<0){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("INDICE_SUPPR_ATT"));
		return;
	}
	int nb_attaq_=attaques.size()-1;
	int nb_c_=table_attaques->columnCount();
	for(int i=indice_;i<nb_attaq_;i++){
		for(int j=0;j<nb_c_;j++){
			QTableWidgetItem *element_=table_attaques->item(i,j);
			element_->setText(table_attaques->item(i+1,j)->text());
		}
	}
	int nb_l_=table_attaques->rowCount();
	for(int i=nb_attaq_;i<nb_l_;i++){
		for(int j=0;j<nb_c_;j++){
			QTableWidgetItem *element_=table_attaques->item(i,j);
			element_->setText("");
		}
	}
	attaques.removeAt(indice_);
	QMessageBox::information(this,traduire("SUCCES"),traduire("SUPPR_ATT_FINIE"));
}

void DialoguePkCombat::acceptation(){
	rejeter=false;
	close();
}

bool DialoguePkCombat::rejete()const{
	return rejeter;
}

void DialoguePkCombat::closeEvent(QCloseEvent* _ev){
	if(rejeter){
		return;
	}
	QString erreur_;
	QString n_pk_=nom_pk->currentText();
	QStringList args_;
	if(nom_pk->findText(n_pk_)<0){
		args_<<n_pk_;
		erreur_+=Utilitaire::formatter(traduire("NOM_PK_INVAL"),args_)+"\n";
	}
	args_.clear();
	QString capacite_pk_=capacite_pk->currentText();
	if(capacite_pk->findText(capacite_pk_)<0){
		args_<<capacite_pk_;
		erreur_+=Utilitaire::formatter(traduire("CAPACITE_PK_INVAL"),args_)+"\n";
	}
	args_.clear();
	if(genre_pk!=NULL&&genre_pk->findText(genre_pk->currentText())<0){
		args_<<genre_pk->currentText();
		erreur_+=Utilitaire::formatter(traduire("GENRE_PK_INVAL"),args_)+"\n";
	}
	args_.clear();
	QString objet_pk_=objet_pk->currentText();
	if(objet_pk->findText(objet_pk_)<0&&objet_pk_!=""){
		args_<<objet_pk_;
		erreur_+=Utilitaire::formatter(traduire("OBJET_PK_INVAL"),args_)+"\n";
	}
	if(nom_attaque_pk!=NULL&&attaques.isEmpty()){
		erreur_+=traduire("ABS_ATTAQUES")+"\n";
	}
	if(erreur_!=""){
		_ev->ignore();
		rejeter=true;
		QMessageBox::critical(this,traduire("ERREUR"),erreur_);
	}
}

DialoguePkCombat::~DialoguePkCombat(){
	delete boutons_categ_attaques;
	boutons_categ_attaques=NULL;
}

