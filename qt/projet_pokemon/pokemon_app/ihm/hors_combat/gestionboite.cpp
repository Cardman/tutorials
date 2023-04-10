#include "ihm/hors_combat/gestionboite.h"
#include "ihm/hors_combat/etiquettes/etiquetteoeuf.h"
#include "ihm/hors_combat/etiquettes/etiquettepkut.h"
#include "ihm/hors_combat/etiquettes/miniature.h"
#include "ihm/hors_combat/fiches/ficheoeuf.h"
#include "ihm/hors_combat/fiches/fichepkutequipe.h"
#include "ihm/hors_combat/fiches/fichepkutboite.h"
#include "ihm/hors_combat/gestionequipe.h"
#include "ihm/boutons/bouton.h"
#include "ihm/boutons/claviernumerique.h"
#include "base_donnees/donnees.h"
#include "serialisable/utilisateur/utilisateur.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QScrollArea>

GestionBoite::GestionBoite(Donnees* _d){
	existe_select_1=false;
	existe_select_2=false;
	donnees=_d;
	echange_pos=false;
	echange_obj=false;
	gestion_en_cours=false;
	QSplitter *equipe_=new QSplitter(Qt::Vertical);
	QScrollArea *asc_=new QScrollArea();
	asc_->setWidgetResizable(true);
	QGroupBox *groupe_=new QGroupBox("Equipe");
	equipe=new QVBoxLayout();
	groupe_->setLayout(equipe);
	asc_->setWidget(groupe_);
	equipe_->addWidget(asc_);
	pk_equipe=-1;
	asc_fiche_pk_eq=new QScrollArea();
	fiche_pk_eq=new FichePkUtEquipe();
	asc_fiche_pk_eq->setWidget(fiche_pk_eq);
	equipe_->addWidget(asc_fiche_pk_eq);
	asc_fiche_oeuf_eq=new QScrollArea();
	fiche_oeuf_eq=new FicheOeuf();
	asc_fiche_oeuf_eq->setWidget(fiche_oeuf_eq);
	equipe_->addWidget(asc_fiche_oeuf_eq);
	asc_=new QScrollArea();
	groupe_=new QGroupBox("Actions");
	QVBoxLayout *lay_boutons_=new QVBoxLayout();
	Bouton *bouton_=new Bouton("Echanger Pokemons ou oeuf");
	connect(bouton_,SIGNAL(clic(QString)),this,SLOT(echange_pokemon()));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	lay_boutons_->addWidget(bouton_);
	bouton_=new Bouton("Echanger objets");
	connect(bouton_,SIGNAL(clic(QString)),this,SLOT(echange_objets()));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	lay_boutons_->addWidget(bouton_);
	bouton_=new Bouton("Deposer pokemon");
	connect(bouton_,SIGNAL(clic(QString)),this,SLOT(depos()));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	lay_boutons_->addWidget(bouton_);
	bouton_=new Bouton("Retirer pokemon");
	connect(bouton_,SIGNAL(clic(QString)),this,SLOT(retrait()));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	lay_boutons_->addWidget(bouton_);
	bouton_=new Bouton("Relacer pokemon");
	connect(bouton_,SIGNAL(clic(QString)),this,SLOT(relacher()));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	lay_boutons_->addWidget(bouton_);
	bouton_=new Bouton("Ranger objets");
	connect(bouton_,SIGNAL(clic(QString)),this,SLOT(ranger_objets()));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	lay_boutons_->addWidget(bouton_);
	bouton_=new Bouton("Finir");
	connect(bouton_,SIGNAL(clic(QString)),this,SLOT(finir_gestion()));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	lay_boutons_->addWidget(bouton_);
	groupe_->setLayout(lay_boutons_);
	asc_->setWidget(groupe_);
	equipe_->addWidget(asc_);
	addWidget(equipe_);
	QSplitter *groupe_boite_1_=new QSplitter(Qt::Vertical);
	position_1.first=0;
	position_1.second=0;
	indice_boite_1=0;
	asc_=new QScrollArea();
	nom_boite_1=new QGroupBox();
	boite_1=new QGridLayout();
	boite_1->setSpacing(0);
	int nb_places_=_d->constante_numerique("MAX_PK_PAR_BOITE");
	int largeur_=Entier(nb_places_).racine_abs(2);
	int hauteur_=nb_places_/largeur_;
	if(hauteur_*largeur_<nb_places_){
		hauteur_++;
	}
	for(int i=0;i<hauteur_;i++){
		for(int j=0;j<largeur_;j++){
			Miniature *mini_=new Miniature(QPair<uchar,uchar>(i,j),_d);
			connect(mini_,SIGNAL(clic(QPair<uchar,uchar>,bool,bool)),this,SLOT(voir_fiche_boite_1(QPair<uchar,uchar>,bool,bool)));
			etiquettes_b_1.ajouter_cle_valeur(QPair<uchar,uchar>(i,j),mini_);
			boite_1->addWidget(mini_,i,j);
		}
	}
	nom_boite_1->setLayout(boite_1);
	asc_->setWidget(nom_boite_1);
	groupe_boite_1_->addWidget(asc_);
	asc_fiche_pk_boite_1=new QScrollArea();
	fiche_pk_boite_1=new FichePkUtBoite();
	asc_fiche_pk_boite_1->setWidget(fiche_pk_boite_1);
	groupe_boite_1_->addWidget(asc_fiche_pk_boite_1);
	asc_fiche_oeuf_boite_1=new QScrollArea();
	fiche_oeuf_boite_1=new FicheOeuf();
	asc_fiche_oeuf_boite_1->setWidget(fiche_oeuf_boite_1);
	groupe_boite_1_->addWidget(asc_fiche_oeuf_boite_1);
	asc_=new QScrollArea();
	clavier_1=new ClavierNumerique(true,_d);
	connect(clavier_1,SIGNAL(valider(Entier)),this,SLOT(maj_indice_boite_1(Entier)));
	asc_->setWidget(clavier_1);
	groupe_boite_1_->addWidget(asc_);
	addWidget(groupe_boite_1_);
	QSplitter *groupe_boite_2_=new QSplitter(Qt::Vertical);
	position_2.first=0;
	position_2.second=0;
	indice_boite_2=0;
	asc_=new QScrollArea();
	nom_boite_2=new QGroupBox();
	boite_2=new QGridLayout();
	boite_2->setSpacing(0);
	for(int i=0;i<hauteur_;i++){
		for(int j=0;j<largeur_;j++){
			Miniature *mini_=new Miniature(QPair<uchar,uchar>(i,j),_d);
			connect(mini_,SIGNAL(clic(QPair<uchar,uchar>,bool,bool)),this,SLOT(voir_fiche_boite_2(QPair<uchar,uchar>,bool,bool)));
			etiquettes_b_2.ajouter_cle_valeur(QPair<uchar,uchar>(i,j),mini_);
			boite_2->addWidget(mini_,i,j);
		}
	}
	nom_boite_2->setLayout(boite_2);
	asc_->setWidget(nom_boite_2);
	groupe_boite_2_->addWidget(asc_);
	asc_fiche_pk_boite_2=new QScrollArea();
	fiche_pk_boite_2=new FichePkUtBoite();
	asc_fiche_pk_boite_2->setWidget(fiche_pk_boite_2);
	groupe_boite_2_->addWidget(asc_fiche_pk_boite_2);
	asc_fiche_oeuf_boite_2=new QScrollArea();
	fiche_oeuf_boite_2=new FicheOeuf();
	asc_fiche_oeuf_boite_2->setWidget(fiche_oeuf_boite_2);
	groupe_boite_2_->addWidget(asc_fiche_oeuf_boite_2);
	asc_=new QScrollArea();
	clavier_2=new ClavierNumerique(true,_d);
	connect(clavier_2,SIGNAL(valider(Entier)),this,SLOT(maj_indice_boite_2(Entier)));
	asc_->setWidget(clavier_2);
	groupe_boite_2_->addWidget(asc_);
	addWidget(groupe_boite_2_);
	asc_fiche_oeuf_boite_1->hide();
	asc_fiche_oeuf_boite_2->hide();
	asc_fiche_pk_boite_1->hide();
	asc_fiche_pk_boite_2->hide();
	asc_fiche_oeuf_eq->hide();
	asc_fiche_pk_eq->hide();
}

void GestionBoite::maj_fiche(const Utilisateur& _ut,int _langue,Donnees* _d){
	langue=_langue;
	existe_select_1=false;
	existe_select_2=false;
	boites.clear();
	boites_oeufs.clear();
	int nb_b_=_d->constante_numerique("NB_BOITES");
	for(int i=0;i<nb_b_;i++){
		boites<<_ut.boite(i);
	}
	for(int i=0;i<nb_b_;i++){
		boites_oeufs<<_ut.boite_oeuf(i);
	}
	equipe_ut=_ut.equipe_ut();
	oeufs_equipe=_ut.oeufs();
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->deleteLater();
		equipe->removeWidget(etiquettes_pk_ut.valeur(p));
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->deleteLater();
		equipe->removeWidget(etiquettes_oeuf.valeur(p));
	}
	etiquettes_pk_ut.tout_supprimer();
	etiquettes_oeuf.tout_supprimer();
	pos_indice.tout_supprimer();
	for(int i=equipe_ut.size()-1;i>-1;i--){
		pos_indice.ajouter_cle_valeur(equipe_ut[i].first,i);
	}
	for(int i=oeufs_equipe.size()-1;i>-1;i--){
		pos_indice.ajouter_cle_valeur(oeufs_equipe[i].first,i);
	}
	int nb_=equipe_ut.size()+oeufs_equipe.size();
	for(int i=0;i<nb_;i++){
		bool trouve_=false;
		for(int j=0;j<equipe_ut.size();j++){
			if(equipe_ut[j].first==i){
				EtiquettePkUt *etiquette_=new EtiquettePkUt(i,equipe_ut[j].second,_d);
				connect(etiquette_,SIGNAL(clic(uchar)),this,SLOT(voir_fiche_pk_ut(uchar)));
				equipe->addWidget(etiquette_);
				etiquettes_pk_ut.ajouter_cle_valeur(i,etiquette_);
				trouve_=true;
				break;
			}
		}
		if(trouve_){
			continue;
		}
		for(int j=0;j<oeufs_equipe.size();j++){
			if(oeufs_equipe[j].first==i){
				EtiquetteOeuf *etiquette_=new EtiquetteOeuf(i,oeufs_equipe[j].second,_d);
				connect(etiquette_,SIGNAL(clic(uchar)),this,SLOT(voir_fiche_oeuf(uchar)));
				equipe->addWidget(etiquette_);
				etiquettes_oeuf.ajouter_cle_valeur(i,etiquette_);
			}
		}
	}
	equipe->parentWidget()->setMinimumSize(220,nb_*170+20);
	maj_boite_1(indice_boite_1);
	maj_boite_2(indice_boite_2);
}

void GestionBoite::maj_boite_1(uchar _indice){
	nom_boite_1->setTitle("Boite "+QString::number(_indice));
	int nb_pk_ut_=boites[_indice].size();
	int nb_oeufs_=boites_oeufs[_indice].size();
	int nb_=donnees->constante_numerique("MAX_PK_PAR_BOITE");
	int largeur_=boite_1->columnCount();
	int l_=0;
	int h_=0;
	for(int i=0;i<nb_;i++){
		bool trouve_=false;
		for(int j=0;j<nb_pk_ut_;j++){
			if(boites[_indice][j].first==i){
				QPair<Entier,Entier> quot_rest_=Entier(i).division_euclidienne_generalise(largeur_);
				//Premier indice: ligue
				//Deuxime indice: colonne
				FichePokemon *f_pk_=donnees->val_pokedex().valeur(boites[_indice][j].second.n_pk());
				Miniature *mini_=etiquettes_b_1.valeur(QPair<uchar,uchar>(quot_rest_.first,quot_rest_.second));
				mini_->maj_miniature(f_pk_->num(),donnees);
				mini_->repaint();
				l_=mini_->width();
				h_=mini_->height();
				trouve_=true;
				break;
			}
		}
		if(trouve_){
			continue;
		}
		for(int j=0;j<nb_oeufs_;j++){
			if(boites_oeufs[_indice][j].first==i){
				QPair<Entier,Entier> quot_rest_=Entier(i).division_euclidienne_generalise(largeur_);
				//Premier indice: ligue
				//Deuxime indice: colonne
				Miniature *mini_=etiquettes_b_1.valeur(QPair<uchar,uchar>(quot_rest_.first,quot_rest_.second));
				mini_->maj_miniature(0,donnees);
				mini_->repaint();
				l_=mini_->width();
				h_=mini_->height();
				trouve_=true;
				break;
			}
		}
		if(!trouve_){
			QPair<Entier,Entier> quot_rest_=Entier(i).division_euclidienne_generalise(largeur_);
			Miniature *mini_=etiquettes_b_1.valeur(QPair<uchar,uchar>(quot_rest_.first,quot_rest_.second));
			mini_->maj_miniature(-1,donnees);
			mini_->repaint();
			l_=mini_->width();
			h_=mini_->height();
		}
	}
	nom_boite_1->setFixedWidth(largeur_*l_);
	nom_boite_1->setMinimumHeight(h_*boite_1->rowCount()+20);
}

void GestionBoite::maj_boite_2(uchar _indice){
	nom_boite_2->setTitle("Boite "+QString::number(_indice));
	int nb_pk_ut_=boites[_indice].size();
	int nb_oeufs_=boites_oeufs[_indice].size();
	int nb_=donnees->constante_numerique("MAX_PK_PAR_BOITE");
	int largeur_=boite_2->columnCount();
	int l_=0;
	int h_=0;
	for(int i=0;i<nb_;i++){
		bool trouve_=false;
		for(int j=0;j<nb_pk_ut_;j++){
			if(boites[_indice][j].first==i){
				QPair<Entier,Entier> quot_rest_=Entier(i).division_euclidienne_generalise(largeur_);
				//Premier indice: ligue
				//Deuxime indice: colonne
				FichePokemon *f_pk_=donnees->val_pokedex().valeur(boites[_indice][j].second.n_pk());
				Miniature *mini_=etiquettes_b_2.valeur(QPair<uchar,uchar>(quot_rest_.first,quot_rest_.second));
				mini_->maj_miniature(f_pk_->num(),donnees);
				mini_->repaint();
				l_=mini_->width();
				h_=mini_->height();
				trouve_=true;
				break;
			}
		}
		if(trouve_){
			continue;
		}
		for(int j=0;j<nb_oeufs_;j++){
			if(boites_oeufs[_indice][j].first==i){
				QPair<Entier,Entier> quot_rest_=Entier(i).division_euclidienne_generalise(largeur_);
				//Premier indice: ligue
				//Deuxime indice: colonne
				Miniature *mini_=etiquettes_b_2.valeur(QPair<uchar,uchar>(quot_rest_.first,quot_rest_.second));
				mini_->maj_miniature(0,donnees);
				mini_->repaint();
				l_=mini_->width();
				h_=mini_->height();
				trouve_=true;
				break;
			}
		}
		if(!trouve_){
			QPair<Entier,Entier> quot_rest_=Entier(i).division_euclidienne_generalise(largeur_);
			Miniature *mini_=etiquettes_b_2.valeur(QPair<uchar,uchar>(quot_rest_.first,quot_rest_.second));
			mini_->maj_miniature(-1,donnees);
			mini_->repaint();
			l_=mini_->width();
			h_=mini_->height();
		}
	}
	nom_boite_2->setFixedWidth(largeur_*l_);
	nom_boite_2->setMinimumHeight(h_*boite_2->rowCount()+20);
}


bool GestionBoite::gestion()const{
	return gestion_en_cours;
}

void GestionBoite::finir_gestion(){
	if(equipe_ut.isEmpty()){
		return;
	}
	gestion_en_cours=false;
	emit gestion_finie();
}

void GestionBoite::voir_fiche_pk_ut(uchar _pos){
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->maj_choix(false);
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->maj_choix(false);
	}
	if(pk_equipe==-1||pk_equipe!=_pos){
		//Selection
		pk_equipe=_pos;
		etiquettes_pk_ut.valeur(_pos)->maj_choix(true);
		asc_fiche_pk_eq->show();
		fiche_pk_eq->setMinimumSize(500,1500);
		fiche_pk_eq->maj_fiche(equipe_ut[pos_indice.valeur(_pos)].second,langue,GestionEquipe::ORDRE,donnees);
	}else{
		//Desselection
		pk_equipe=-1;
		asc_fiche_pk_eq->hide();
	}
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->repaint();
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->repaint();
	}
	asc_fiche_oeuf_eq->hide();
	//fiche_pk_ut->maj_fiche(equipe[pos_indice.valeur(_pos)].second,langue,gestion_en_cours,donnees);
	/*if(echange_pos){
		if(pokemons_echanges.first==-1){
			pokemons_echanges.first=_pos;
		}else{
			pokemons_echanges.second=_pos;
			emit echange_place(pokemons_echanges);
		}
	}else if(echange_obj){
		if(pokemons_echanges.first==-1){
			pokemons_echanges.first=_pos;
		}else{
			pokemons_echanges.second=_pos;
			emit echange_objets(pokemons_echanges);
		}
	}*/
	//
}

void GestionBoite::voir_fiche_oeuf(uchar _pos){
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->maj_choix(false);
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->maj_choix(false);
	}
	//pokemon_vu=-1;

	if(pk_equipe==-1||pk_equipe!=_pos){
		//Selection
		pk_equipe=_pos;
		etiquettes_oeuf.valeur(_pos)->maj_choix(true);
		asc_fiche_oeuf_eq->show();
		fiche_oeuf_eq->maj_fiche(oeufs_equipe[pos_indice.valeur(_pos)].second,donnees);
	}else{
		//Desselection
		pk_equipe=-1;
		asc_fiche_oeuf_eq->hide();
	}
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->repaint();
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->repaint();
	}
	asc_fiche_pk_eq->hide();
	/*asc_fiche_pk_ut->hide();
	asc_fiche_oeuf->show();
	fiche_oeuf->setMinimumSize(500,500);
	fiche_oeuf->maj_fiche(oeufs_equipe[pos_indice.valeur(_pos)].second,donnees);*/
	/*if(echange_pos){
		if(pokemons_echanges.first==-1){
			pokemons_echanges.first=_pos;
		}else{
			pokemons_echanges.second=_pos;
			emit echange_place(pokemons_echanges);
		}
	}else if(echange_obj){
		if(pokemons_echanges.first==-1){
			pokemons_echanges.first=_pos;
		}else{
			pokemons_echanges.second=_pos;
			emit echange_objets(pokemons_echanges);
		}
	}*/
	//
}

void GestionBoite::maj_indice_boite_1(const Entier& _indice){
	if(_indice<Entier(0)){
		return;
	}
	if(_indice>=Entier(donnees->constante_numerique("NB_BOITES").gnumerateur())){
		return;
	}
	indice_boite_1=_indice.modulo_absolu_base();
	maj_boite_1(indice_boite_1);
}

void GestionBoite::maj_indice_boite_2(const Entier& _indice){
	if(_indice<Entier(0)){
		return;
	}
	if(_indice>=Entier(donnees->constante_numerique("NB_BOITES").gnumerateur())){
		return;
	}
	indice_boite_2=_indice.modulo_absolu_base();
	maj_boite_2(indice_boite_2);
}

void GestionBoite::voir_fiche_boite_1(const QPair<uchar,uchar>& _pos,bool _oeuf,bool _vide){
	typedef QPair<uchar,uchar> Position;
	foreach(Position p,etiquettes_b_1.cles()){
		etiquettes_b_1.valeur(p)->maj_choix(false);
	}
	etiquettes_b_1.valeur(_pos)->maj_choix(true);
	if(_vide){
		if(existe_select_1&&position_1==_pos){
			existe_select_1=false;
			etiquettes_b_1.valeur(_pos)->maj_choix(false);
		}else{
			position_1=_pos;
			existe_select_1=true;
			fiche_pk_boite_1->hide();
			fiche_oeuf_boite_1->hide();
			foreach(Position p,etiquettes_b_1.cles()){
				etiquettes_b_1.valeur(p)->repaint();
			}
		}
		return;
	}
	uchar indice_=_pos.first*boite_1->columnCount()+_pos.second;
	if(_oeuf){
		if(existe_select_1&&_pos==position_1){
			existe_select_1=false;
			etiquettes_b_1.valeur(_pos)->maj_choix(false);
			asc_fiche_pk_boite_1->hide();
		}else{
			position_1=_pos;
			existe_select_1=true;
			asc_fiche_oeuf_boite_1->show();
			asc_fiche_pk_boite_1->hide();
			for(int i=0;i<boites_oeufs[indice_boite_1].size();i++){
				if(boites_oeufs[indice_boite_1][i].first==indice_){
					indice_=i;
					break;
				}
			}
			fiche_oeuf_boite_1->maj_fiche(boites_oeufs[indice_boite_1][indice_].second,donnees);
		}
	}else{
		if(existe_select_1&&_pos==position_1){
			existe_select_1=false;
			etiquettes_b_1.valeur(_pos)->maj_choix(false);
			asc_fiche_pk_boite_1->hide();
		}else{
			position_1=_pos;
			existe_select_1=true;
			asc_fiche_pk_boite_1->show();
			asc_fiche_oeuf_boite_1->hide();
			fiche_pk_boite_1->setMinimumSize(500,1500);
			for(int i=0;i<boites[indice_boite_1].size();i++){
				if(boites[indice_boite_1][i].first==indice_){
					indice_=i;
					break;
				}
			}
			fiche_pk_boite_1->maj_fiche(boites[indice_boite_1][indice_].second,langue,donnees);
		}
	}
	foreach(Position p,etiquettes_b_1.cles()){
		etiquettes_b_1.valeur(p)->repaint();
	}
}

void GestionBoite::voir_fiche_boite_2(const QPair<uchar,uchar>& _pos,bool _oeuf,bool _vide){
	typedef QPair<uchar,uchar> Position;
	foreach(Position p,etiquettes_b_2.cles()){
		etiquettes_b_2.valeur(p)->maj_choix(false);
	}
	etiquettes_b_2.valeur(_pos)->maj_choix(true);
	if(_vide){
		if(existe_select_2&&position_2==_pos){
			existe_select_2=false;
			etiquettes_b_2.valeur(_pos)->maj_choix(false);
		}else{
			position_2=_pos;
			existe_select_2=true;
			fiche_pk_boite_2->hide();
			fiche_oeuf_boite_2->hide();
			foreach(Position p,etiquettes_b_2.cles()){
				etiquettes_b_2.valeur(p)->repaint();
			}
		}
		return;
	}
	uchar indice_=_pos.first*boite_2->columnCount()+_pos.second;
	if(_oeuf){
		if(existe_select_2&&_pos==position_2){
			existe_select_2=false;
			etiquettes_b_2.valeur(_pos)->maj_choix(false);
			asc_fiche_oeuf_boite_2->hide();
		}else{
			position_2=_pos;
			existe_select_2=true;
			asc_fiche_oeuf_boite_2->show();
			asc_fiche_pk_boite_2->hide();
			for(int i=0;i<boites_oeufs[indice_boite_2].size();i++){
				if(boites_oeufs[indice_boite_2][i].first==indice_){
					indice_=i;
					break;
				}
			}
			fiche_oeuf_boite_2->maj_fiche(boites_oeufs[indice_boite_2][indice_].second,donnees);
		}
	}else{
		if(existe_select_2&&_pos==position_2){
			existe_select_2=false;
			etiquettes_b_2.valeur(_pos)->maj_choix(false);
			asc_fiche_pk_boite_2->hide();
		}else{
			position_2=_pos;
			existe_select_2=true;
			asc_fiche_pk_boite_2->show();
			asc_fiche_oeuf_boite_2->hide();
			fiche_pk_boite_2->setMinimumSize(500,1500);
			for(int i=0;i<boites[indice_boite_2].size();i++){
				if(boites[indice_boite_2][i].first==indice_){
					indice_=i;
					break;
				}
			}
			fiche_pk_boite_2->maj_fiche(boites[indice_boite_2][indice_].second,langue,donnees);
		}
	}
	foreach(Position p,etiquettes_b_2.cles()){
		etiquettes_b_2.valeur(p)->repaint();
	}
}

void GestionBoite::echange_pokemon(){
	if(pk_equipe!=-1){
		if(existe_select_1&&(fiche_oeuf_boite_1->isVisible()||fiche_pk_boite_1->isVisible())){
			if(!existe_select_2||!(fiche_oeuf_boite_2->isVisible()||fiche_pk_boite_2->isVisible())){
				emit echange_pokemon(QPair<int,int>(-1,pk_equipe),QPair<int,int>(indice_boite_1,position_1.first*boite_1->columnCount()+position_1.second));
			}
		}else if(existe_select_2&&(fiche_oeuf_boite_2->isVisible()||fiche_pk_boite_2->isVisible())){
			emit echange_pokemon(QPair<int,int>(-1,pk_equipe),QPair<int,int>(indice_boite_2,position_2.first*boite_2->columnCount()+position_2.second));
		}
	}else{
		if(existe_select_1&&(fiche_oeuf_boite_1->isVisible()||fiche_pk_boite_1->isVisible())){
			if(existe_select_2&&(fiche_oeuf_boite_2->isVisible()||fiche_pk_boite_2->isVisible())){
				emit echange_pokemon(QPair<int,int>(indice_boite_1,position_1.first*boite_1->columnCount()+position_1.second),QPair<int,int>(indice_boite_2,position_2.first*boite_2->columnCount()+position_2.second));
			}
		}
	}
}

void GestionBoite::echange_objets(){
	if(pk_equipe!=-1){
		if(existe_select_1&&fiche_pk_boite_1->isVisible()){
			if(!existe_select_2||!fiche_pk_boite_2->isVisible()){
				emit echange_objets(QPair<int,int>(-1,pk_equipe),QPair<int,int>(indice_boite_1,position_1.first*boite_1->columnCount()+position_1.second));
			}
		}else if(existe_select_2&&fiche_pk_boite_2->isVisible()){
			emit echange_objets(QPair<int,int>(-1,pk_equipe),QPair<int,int>(indice_boite_2,position_2.first*boite_2->columnCount()+position_2.second));
		}
	}else{
		if(existe_select_1&&fiche_pk_boite_1->isVisible()){
			if(existe_select_2&&fiche_pk_boite_2->isVisible()){
				emit echange_objets(QPair<int,int>(indice_boite_1,position_1.first*boite_1->columnCount()+position_1.second),QPair<int,int>(indice_boite_2,position_2.first*boite_2->columnCount()+position_2.second));
			}
		}
	}
}

void GestionBoite::ranger_objets(){
	if(pk_equipe!=-1){
		if(!existe_select_1||!fiche_pk_boite_1->isVisible()){
			if(!existe_select_2||!fiche_pk_boite_2->isVisible()){
				emit ranger_objets(QPair<int,int>(-1,pk_equipe));
			}
		}
	}else if(existe_select_1&&fiche_pk_boite_1->isVisible()){
		if(!existe_select_2||!fiche_pk_boite_2->isVisible()){
			emit ranger_objets(QPair<int,int>(indice_boite_1,position_1.first*boite_1->columnCount()+position_1.second));
		}
	}else if(existe_select_2&&fiche_pk_boite_2->isVisible()){
		emit ranger_objets(QPair<int,int>(indice_boite_2,position_2.first*boite_2->columnCount()+position_2.second));
	}
}

void GestionBoite::depos(){
	if(pk_equipe!=-1&&existe_select_1){
		emit depos(pk_equipe,QPair<uchar,uchar>(indice_boite_1,position_1.first*boite_1->columnCount()+position_1.second));
	}
}

void GestionBoite::retrait(){
	if(existe_select_1){
		emit retrait(QPair<uchar,uchar>(indice_boite_1,position_1.first*boite_1->columnCount()+position_1.second));
	}
}

void GestionBoite::relacher(){
	if(existe_select_1){
		emit relacher(QPair<uchar,uchar>(indice_boite_1,position_1.first*boite_1->columnCount()+position_1.second));
	}
}
