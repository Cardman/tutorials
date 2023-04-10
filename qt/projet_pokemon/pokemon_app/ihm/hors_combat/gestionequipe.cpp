#include "ihm/hors_combat/gestionequipe.h"
#include "ihm/hors_combat/etiquettes/etiquetteoeuf.h"
#include "ihm/hors_combat/etiquettes/etiquettepkut.h"
#include "ihm/hors_combat/fiches/ficheoeuf.h"
#include "ihm/hors_combat/fiches/fichepkutequipe.h"
#include "ihm/boutons/bouton.h"
#include "base_donnees/donnees.h"
#include "base_donnees/objets/boost.h"
#include "base_donnees/objets/soinpp.h"
#include "serialisable/utilisateur/utilisateur.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QScrollArea>

GestionEquipe::GestionEquipe(){
	pokemon_vu=-1;
	pokemons_echanges=QPair<int,int>(-1,-1);
	gestion_en_cours=GestionEquipe::RIEN;
	echange_obj=false;
	echange_pos=false;
	QScrollArea *asc_id_=new QScrollArea();
	asc_id_->setWidgetResizable(true);
	QGroupBox *groupe_=new QGroupBox();
	lay_identite=new QVBoxLayout();
	groupe_->setLayout(lay_identite);
	asc_id_->setWidget(groupe_);
	addWidget(asc_id_);
	QSplitter *infos_actions_=new QSplitter(Qt::Vertical);
	asc_fiche_pk_ut=new QScrollArea();
	asc_fiche_pk_ut->setWidgetResizable(true);
	fiche_pk_ut=new FichePkUtEquipe();
	connect(fiche_pk_ut,SIGNAL(choix_attaque(QString,int)),this,SLOT(apprendre_move_tutors(QString,int)));
	asc_fiche_pk_ut->setWidget(fiche_pk_ut);
	infos_actions_->addWidget(asc_fiche_pk_ut);
	asc_fiche_pk_ut->hide();
	asc_fiche_oeuf=new QScrollArea();
	asc_fiche_oeuf->setWidgetResizable(true);
	fiche_oeuf=new FicheOeuf();
	asc_fiche_oeuf->setWidget(fiche_oeuf);
	infos_actions_->addWidget(asc_fiche_oeuf);
	asc_fiche_oeuf->hide();
	QScrollArea *asc_=new QScrollArea();
	asc_->setWidgetResizable(true);
	groupe_=new QGroupBox("Actions");
	lay_actions=new QVBoxLayout();
	groupe_->setLayout(lay_actions);
	asc_->setWidget(groupe_);
	infos_actions_->addWidget(asc_);
	addWidget(infos_actions_);
	asc_mt=new QScrollArea();
	asc_mt->setWidgetResizable(true);
	groupe_=new QGroupBox("Move tutors");
	lay_mt=new QVBoxLayout();
	groupe_->setLayout(lay_mt);
	asc_mt->setWidget(groupe_);
	addWidget(asc_mt);
}

uchar GestionEquipe::gestion()const{
	return gestion_en_cours;
}

int GestionEquipe::pokemon_fiche(){
	return pokemon_vu;
}

bool GestionEquipe::echange_en_cours(){
	return echange_obj||echange_pos;
}

void GestionEquipe::maj_fiche(const Utilisateur& _ut,int _langue,uchar _type,Donnees* _d,const QString& _attaque){
	donnees=_d;
	attaque_apprise="";
	gestion_en_cours=_type;
	Bouton *etiquette_=NULL;
	int nb_=lay_actions->count();
	for(int i=0;i<nb_;i++){
		lay_actions->itemAt(i)->widget()->deleteLater();
	}
	for(int i=0;i<nb_;i++){
		lay_actions->removeItem(lay_actions->itemAt(0));
	}
	nb_=lay_mt->count();
	for(int i=0;i<nb_;i++){
		lay_mt->itemAt(i)->widget()->deleteLater();
	}
	for(int i=0;i<nb_;i++){
		lay_mt->removeItem(lay_mt->itemAt(0));
	}
	equipe=_ut.equipe_ut();
	oeufs_equipe=_ut.oeufs();
	if(gestion_en_cours==GestionEquipe::ORDRE){
		asc_mt->hide();
		etiquette_=new Bouton();
		connect(etiquette_,SIGNAL(clic()),this,SLOT(echange_position()));
		etiquette_->maj_texte("Echanger positions");
		etiquette_->maj_couleur_fond(QColor(255,255,255,255));
		etiquette_->maj_couleur_rectangle(QColor(0,0,255,255));
		etiquette_->maj_couleur_texte(QColor(0,0,255,255));
		lay_actions->addWidget(etiquette_);
		etiquette_=new Bouton();
		connect(etiquette_,SIGNAL(clic()),this,SLOT(echange_objets()));
		etiquette_->maj_texte("Echanger objets");
		etiquette_->maj_couleur_fond(QColor(255,255,255,255));
		etiquette_->maj_couleur_rectangle(QColor(0,0,255,255));
		etiquette_->maj_couleur_texte(QColor(0,0,255,255));
		lay_actions->addWidget(etiquette_);
		etiquette_=new Bouton();
		connect(etiquette_,SIGNAL(clic()),this,SLOT(rangement_objet()));
		etiquette_->maj_texte("Ranger objet");
		//TODO ajouter la connection au slot
		etiquette_->maj_couleur_fond(QColor(255,255,255,255));
		etiquette_->maj_couleur_rectangle(QColor(0,0,255,255));
		etiquette_->maj_couleur_texte(QColor(0,0,255,255));
		lay_actions->addWidget(etiquette_);
		etiquette_=new Bouton();
		etiquette_->maj_texte("Annuler");
		connect(etiquette_,SIGNAL(clic()),this,SLOT(annuler()));
		etiquette_->maj_couleur_fond(QColor(255,255,255,255));
		etiquette_->maj_couleur_rectangle(QColor(0,0,255,255));
		etiquette_->maj_couleur_texte(QColor(0,0,255,255));
		lay_actions->addWidget(etiquette_);
		etiquette_=new Bouton();
		etiquette_->maj_texte("Finir");
		connect(etiquette_,SIGNAL(clic()),this,SLOT(finir_gestion()));
		etiquette_->maj_couleur_fond(QColor(255,255,255,255));
		etiquette_->maj_couleur_rectangle(QColor(0,0,255,255));
		etiquette_->maj_couleur_texte(QColor(0,0,255,255));
		lay_actions->addWidget(etiquette_);
		bool existe_vol_=false;
		for(int i=0;i<equipe.size();i++){
			typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
			foreach(AttaquePP a,equipe[i].second.attaques_apprises()){
				if(a.first=="VOL"){
					existe_vol_=true;
					break;
				}
			}
		}
		if(existe_vol_){
			etiquette_=new Bouton();
			etiquette_->maj_texte("Voler");
			connect(etiquette_,SIGNAL(clic()),this,SLOT(voler()));
			etiquette_->maj_couleur_fond(QColor(255,255,255,255));
			etiquette_->maj_couleur_rectangle(QColor(0,0,255,255));
			etiquette_->maj_couleur_texte(QColor(0,0,255,255));
			lay_actions->addWidget(etiquette_);
		}
	}else if(gestion_en_cours==GestionEquipe::PENSION){
		asc_mt->hide();
		etiquette_=new Bouton();
		etiquette_->maj_texte("Annuler");
		connect(etiquette_,SIGNAL(clic()),this,SLOT(annuler()));
		etiquette_->maj_couleur_fond(QColor(255,255,255,255));
		etiquette_->maj_couleur_rectangle(QColor(0,0,255,255));
		etiquette_->maj_couleur_texte(QColor(0,0,255,255));
		lay_actions->addWidget(etiquette_);
		etiquette_=new Bouton();
		etiquette_->maj_texte("Finir");
		connect(etiquette_,SIGNAL(clic()),this,SLOT(finir_gestion()));
		etiquette_->maj_couleur_fond(QColor(255,255,255,255));
		etiquette_->maj_couleur_rectangle(QColor(0,0,255,255));
		etiquette_->maj_couleur_texte(QColor(0,0,255,255));
		lay_actions->addWidget(etiquette_);
	}else if(gestion_en_cours==GestionEquipe::MOVE_TUTORS){
		asc_mt->show();
		etiquette_=new Bouton();
		etiquette_->maj_texte("Annuler");
		connect(etiquette_,SIGNAL(clic()),this,SLOT(annuler()));
		etiquette_->maj_couleur_fond(QColor(255,255,255,255));
		etiquette_->maj_couleur_rectangle(QColor(0,0,255,255));
		etiquette_->maj_couleur_texte(QColor(0,0,255,255));
		lay_actions->addWidget(etiquette_);
		etiquette_=new Bouton();
		etiquette_->maj_texte("Finir");
		connect(etiquette_,SIGNAL(clic()),this,SLOT(finir_gestion()));
		etiquette_->maj_couleur_fond(QColor(255,255,255,255));
		etiquette_->maj_couleur_rectangle(QColor(0,0,255,255));
		etiquette_->maj_couleur_texte(QColor(0,0,255,255));
		lay_actions->addWidget(etiquette_);
	}else{
		asc_mt->hide();
	}
	if(etiquette_){
		lay_actions->parentWidget()->setMinimumSize(etiquette_->width(),etiquette_->height()*lay_actions->count());
	}
	echange_pos=false;
	echange_obj=false;
	pokemon_vu=-1;
	pokemons_echanges=QPair<int,int>(-1,-1);
	langue=_langue;
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->deleteLater();
		lay_identite->removeWidget(etiquettes_pk_ut.valeur(p));
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->deleteLater();
		lay_identite->removeWidget(etiquettes_oeuf.valeur(p));
	}
	etiquettes_pk_ut.tout_supprimer();
	etiquettes_oeuf.tout_supprimer();
	pos_indice.tout_supprimer();
	for(int i=equipe.size()-1;i>-1;i--){
		pos_indice.ajouter_cle_valeur(equipe[i].first,i);
	}
	for(int i=oeufs_equipe.size()-1;i>-1;i--){
		pos_indice.ajouter_cle_valeur(oeufs_equipe[i].first,i);
	}
	nb_=equipe.size()+oeufs_equipe.size();
	for(int i=0;i<nb_;i++){
		bool trouve_=false;
		for(int j=0;j<equipe.size();j++){
			if(equipe[j].first==i){
				bool appr_=false;
				if(_type==GestionEquipe::APPRENDRE_CT){
					attaque_apprise=_attaque;
					appr_=true;
				}else if(_type==GestionEquipe::APPRENDRE_CS){
					attaque_apprise=_attaque;
					appr_=true;
				}else if(_type==GestionEquipe::PIERRE_EVO){
					attaque_apprise=_attaque;
					appr_=true;
				}else if(_type==GestionEquipe::BOOST){
					attaque_apprise=_attaque;
					appr_=true;
				}else if(_type==GestionEquipe::SOIN){
					attaque_apprise=_attaque;
				}else if(_type==GestionEquipe::BAIE){
					attaque_apprise=_attaque;
				}
				QString cas_;
				if(appr_){
					if(_type==GestionEquipe::PIERRE_EVO){
						QString nom_=equipe[j].second.n_pk();
						if(equipe[j].second.peut_evoluer(attaque_apprise,donnees)!=nom_){
							cas_+=_attaque+" compatible";
						}else{
							cas_+=_attaque+" incompatible";
						}
					}else if(_type==GestionEquipe::BOOST){
						Boost *boost_=qobject_cast<Boost*>(_d->val_objets().valeur(_attaque));
						if(boost_->g_ev().first!=""){
							cas_+="ev "+boost_->g_ev().first+": "+QString::number(equipe[j].second.ev_stat().valeur(boost_->g_ev().first));
						}
					}else if(equipe[j].second.attaque_deja_connue(_attaque)){
						cas_+=_attaque+"\ndeja connue";
					}else{
						bool apte_=false;
						foreach(uchar c,donnees->val_pokedex().valeur(equipe[j].second.n_pk())->ct()){
							if(donnees->val_ct().valeur(c)==_attaque){
								apte_=true;
								break;
							}
						}
						if(!apte_){
							foreach(uchar c,donnees->val_pokedex().valeur(equipe[j].second.n_pk())->cs()){
								if(donnees->val_cs().valeur(c)==_attaque){
									apte_=true;
									break;
								}
							}
						}
						if(apte_){
							cas_+="Apte pour\n"+_attaque;
						}else{
							cas_+="Inapte pour\n"+_attaque;
						}
					}
				}
				EtiquettePkUt *etiquette_=new EtiquettePkUt(i,equipe[j].second,_d,cas_);
				connect(etiquette_,SIGNAL(clic(uchar)),this,SLOT(voir_fiche_pk_ut(uchar)));
				lay_identite->addWidget(etiquette_);
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
				lay_identite->addWidget(etiquette_);
				etiquettes_oeuf.ajouter_cle_valeur(i,etiquette_);
			}
		}
	}
}

void GestionEquipe::maj_type(uchar _type){
	gestion_en_cours=_type;
}

void GestionEquipe::annuler(){
	echange_pos=false;
	echange_obj=false;
	pokemons_echanges=QPair<int,int>(-1,-1);
	pokemon_vu=-1;
	attaque_apprise="";
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->maj_choix(false);
		etiquettes_pk_ut.valeur(p)->repaint();
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->maj_choix(false);
		etiquettes_oeuf.valeur(p)->repaint();
	}
}

void GestionEquipe::gestion_finie(){
	echange_pos=false;
	echange_obj=false;
	pokemons_echanges=QPair<int,int>(-1,-1);
	gestion_en_cours=GestionEquipe::RIEN;
	pokemon_vu=-1;
	attaque_apprise="";
}

void GestionEquipe::finir_gestion(){
	gestion_finie();
	emit fin_gestion();
}

void GestionEquipe::echange_position(){
	echange_pos=true;
	echange_obj=false;
}

void GestionEquipe::echange_objets(){
	echange_pos=false;
	echange_obj=true;
}

void GestionEquipe::rangement_objet(){
	if(pokemon_vu!=-1){
		uchar pos_=pos_indice.cles(pokemon_vu)[0];
		pokemon_vu=-1;
		foreach(uchar p,etiquettes_pk_ut.cles()){
			etiquettes_pk_ut.valeur(p)->maj_choix(false);
			etiquettes_pk_ut.valeur(p)->repaint();
		}
		emit rangement_objet(pos_);
	}
}

void GestionEquipe::voir_fiche_pk_ut(uchar _pos){
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->maj_choix(false);
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->maj_choix(false);
	}
	pokemon_vu=pos_indice.valeur(_pos);
	etiquettes_pk_ut.valeur(_pos)->maj_choix(true);
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->repaint();
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->repaint();
	}
	asc_fiche_pk_ut->show();
	fiche_pk_ut->setMinimumSize(500,1500);
	asc_fiche_oeuf->hide();
	fiche_pk_ut->maj_fiche(equipe[pokemon_vu].second,langue,gestion_en_cours,donnees);
	if(gestion_en_cours==GestionEquipe::BAIE){
		emit soin_baie(pos_indice.cles(pokemon_vu)[0]);
	}else if(gestion_en_cours==GestionEquipe::SOIN){
		SoinPP *soin_=qobject_cast<SoinPP*>(donnees->val_objets().valeur(attaque_apprise));
		if(!soin_||soin_->effs_se().second=="MAX"){
			emit soin(pos_indice.cles(pokemon_vu)[0]);
		}
	}else if(gestion_en_cours==GestionEquipe::APPRENDRE_CT){
		int nb_attaques_=equipe[pokemon_vu].second.attaques_apprises().size();
		if(nb_attaques_<donnees->nb_att_max()){
			emit move_tutors(attaque_apprise,pos_indice.cles(pokemon_vu)[0],nb_attaques_);
		}
	}else if(gestion_en_cours==GestionEquipe::APPRENDRE_CS){
		int nb_attaques_=equipe[pokemon_vu].second.attaques_apprises().size();
		if(nb_attaques_<donnees->nb_att_max()){
			emit move_tutors(attaque_apprise,pos_indice.cles(pokemon_vu)[0],nb_attaques_);
		}
	}else if(gestion_en_cours==GestionEquipe::ATTACHER_OBJET){
		emit attacher(pos_indice.cles(pokemon_vu)[0]);
	}else if(gestion_en_cours==GestionEquipe::PIERRE_EVO){
		if(attaque_apprise==""){
			return;
		}
		QString pierre_=attaque_apprise;
		attaque_apprise="";
		emit evoluer(pierre_,pos_indice.cles(pokemon_vu)[0]);
	}else if(gestion_en_cours==GestionEquipe::BOOST){
		Boost *boost_=qobject_cast<Boost*>(donnees->val_objets().valeur(attaque_apprise));
		if(boost_->g_pp().estNul()){
			emit boost(pos_indice.cles(pokemon_vu)[0]);
		}
	}else if(gestion_en_cours==GestionEquipe::MOVE_TUTORS){
		int nb_=lay_mt->count();
		for(int i=0;i<nb_;i++){
			lay_mt->itemAt(i)->widget()->deleteLater();
		}
		for(int i=0;i<nb_;i++){
			lay_mt->removeItem(lay_mt->itemAt(0));
		}
		QStringList liste_=equipe[pokemon_vu].second.move_tutors(donnees);
		if(liste_.isEmpty()){
			return;
		}
		int l_=0;
		int h_=0;
		foreach(QString a,liste_){
			Bouton *bouton_=new Bouton(a);
			l_=bouton_->width();
			h_=bouton_->height();
			connect(bouton_,SIGNAL(clic(QString)),this,SLOT(move_tutors(QString)));
			bouton_->maj_couleur_fond(QColor(255,255,255,255));
			bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
			bouton_->maj_couleur_texte(QColor(0,0,255,255));
			lay_mt->addWidget(bouton_);
		}
		lay_mt->parentWidget()->setMinimumSize(l_,liste_.size()*h_);
	}else if(gestion_en_cours==GestionEquipe::PENSION){
		if(pokemons_echanges.first==-1){
			pokemons_echanges.first=_pos;
		}else{
			pokemons_echanges.second=_pos;
			emit pension(pokemons_echanges);
		}
	}else if(echange_pos){
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
	}
	//
}

void GestionEquipe::voir_fiche_oeuf(uchar _pos){
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->maj_choix(false);
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->maj_choix(false);
	}
	pokemon_vu=-1;
	etiquettes_oeuf.valeur(_pos)->maj_choix(true);
	foreach(uchar p,etiquettes_pk_ut.cles()){
		etiquettes_pk_ut.valeur(p)->repaint();
	}
	foreach(uchar p,etiquettes_oeuf.cles()){
		etiquettes_oeuf.valeur(p)->repaint();
	}
	asc_fiche_pk_ut->hide();
	asc_fiche_oeuf->show();
	fiche_oeuf->maj_fiche(oeufs_equipe[pos_indice.valeur(_pos)].second,donnees);
	if(echange_pos){
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
	}
	//
}

void GestionEquipe::apprendre_move_tutors(const QString& _attaque,int _indice){
	if(attaque_apprise!=""){
		if(gestion_en_cours==GestionEquipe::BOOST||gestion_en_cours==GestionEquipe::SOIN||gestion_en_cours==GestionEquipe::BAIE){
			attaque_apprise=_attaque;
		}
		emit appris_move_tutors(attaque_apprise,pos_indice.cles(pokemon_vu)[0],_indice);
	}else{
		emit appris_move_tutors(_attaque,pos_indice.cles(pokemon_vu)[0],-1);
	}
}

void GestionEquipe::move_tutors(const QString& _attaque){
	int nb_attaques_=equipe[pokemon_vu].second.attaques_apprises().size();
	if(nb_attaques_==donnees->nb_att_max()){
		attaque_apprise=_attaque;
		emit move_tutors(_attaque,pos_indice.cles(pokemon_vu)[0],-1);
	}else{
		emit move_tutors(_attaque,pos_indice.cles(pokemon_vu)[0],nb_attaques_);
	}
}

void GestionEquipe::voler(){
	emit vol();
}
