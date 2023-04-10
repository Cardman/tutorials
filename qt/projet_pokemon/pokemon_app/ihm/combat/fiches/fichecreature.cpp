#include "ihm/combat/fiches/fichecreature.h"
#include "ihm/combat/etiquettes/etiquettecombattant.h"
#include "ihm/combat/etiquettes/etiquetteattaque.h"
#include "serialisable/combat/combattant.h"
#include "serialisable/combat/creaturecombat.h"
#include "serialisable/combat/elementscombat.h"
#include "base_donnees/donnees.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QSplitter>
#include <QScrollArea>
#include <iostream>

FicheCreature::FicheCreature(Donnees *_d){
	QVBoxLayout *lay_=new QVBoxLayout();
	QHBoxLayout *lay_infos_gener_=new QHBoxLayout();
	QVBoxLayout *lay_partiel_=new QVBoxLayout();
	image_pk=new QLabel();
	image_pk->setPixmap(QPixmap::fromImage(QImage()));
	lay_partiel_->addWidget(image_pk);
	types_pk=new QLabel();
	types_pk->setText("");
	lay_partiel_->addWidget(types_pk);
	lay_infos_gener_->addLayout(lay_partiel_);
	lay_partiel_=new QVBoxLayout();
	pseudo=new QLabel();
	pseudo->setText("");
	lay_partiel_->addWidget(pseudo);
	capacite_act=new QLabel();
	capacite_act->setText("");
	lay_partiel_->addWidget(capacite_act);
	capacite=new QLabel();
	capacite->setText("");
	lay_partiel_->addWidget(capacite);
	lay_infos_gener_->addLayout(lay_partiel_);
	lay_partiel_=new QVBoxLayout();
	bonheur=new QLabel();
	bonheur->setText("");
	lay_partiel_->addWidget(bonheur);
	prepa_tour=new QLabel();
	prepa_tour->setText("");
	lay_partiel_->addWidget(prepa_tour);
	nec_recharg=new QLabel();
	nec_recharg->setText("");
	lay_partiel_->addWidget(nec_recharg);
	lay_infos_gener_->addLayout(lay_partiel_);
	lay_->addLayout(lay_infos_gener_);
	QGroupBox *groupe_=new QGroupBox("Statistiques");
	statistiques=new QGridLayout();
	statistiques->addWidget(new QLabel("Nom"),0,0);
	statistiques->addWidget(new QLabel("Ev"),0,1);
	statistiques->addWidget(new QLabel("Iv"),0,2);
	statistiques->addWidget(new QLabel("Boost"),0,3);
	statistiques->addWidget(new QLabel("Valeur sans prendre compte le boost"),0,4);
	groupe_->setLayout(statistiques);
	lay_->addWidget(groupe_);
	vitesse=new QLabel();
	lay_->addWidget(vitesse);
	clone_pk=new QLabel();
	lay_->addWidget(clone_pk);
	groupe_=new QGroupBox("Attaques ayant des effets sur plusieurs tours");
	attaques=new QGridLayout();
	attaques->addWidget(new QLabel("Nom"),0,0);
	attaques->addWidget(new QLabel("Nombre de tours"),0,1);
	attaques->addWidget(new QLabel("Nombre de tours minimal"),0,2);
	attaques->addWidget(new QLabel("Nombre de tours maximal"),0,3);
	attaques->addWidget(new QLabel("Effet subi par le pokemon"),0,4);
	groupe_->setLayout(attaques);
	lay_->addWidget(groupe_);
	copie=new QLabel();
	lay_->addWidget(copie);
	confusion=new QLabel();
	lay_->addWidget(confusion);
	patience=new QLabel();
	lay_->addWidget(patience);
	coefficient_roul_ball_glace=new QLabel();
	lay_->addWidget(coefficient_roul_ball_glace);
	succes_abris=new QLabel();
	lay_->addWidget(succes_abris);
	groupe_=new QGroupBox("Attaques dont les effets varient en fonction du nombre d'utilisations");
	attaques_lancees=new QGridLayout();
	attaques_lancees->addWidget(new QLabel("Nom"),0,0);
	attaques_lancees->addWidget(new QLabel("Nombre de lancers"),0,1);
	groupe_->setLayout(attaques_lancees);
	lay_->addWidget(groupe_);
	groupe_=new QGroupBox("Types des attaques lancees ou subies et immunisations au type d'attaque");
	coeff_types=new QGridLayout();
	coeff_types->addWidget(new QLabel("Type"),0,0);
	coeff_types->addWidget(new QLabel("Coefficient\ndes degats subis\nassocie a la capacite"),0,1);//LEVITATION et SOL => 0
	coeff_types->addWidget(new QLabel("Coefficient\ndes degats subis\nassocie a une attaque lancee"),0,2);//TOURNIQUET et FEU => 1/2
	coeff_types->addWidget(new QLabel("Coefficient\ndes degats\nd'une attaque lancee\nde ce type"),0,3);
	coeff_types->addWidget(new QLabel("Immunise au type d'attaque"),0,4);
	groupe_->setLayout(coeff_types);
	lay_->addWidget(groupe_);
	sommeil_non_repos=new QLabel();
	lay_->addWidget(sommeil_non_repos);
	poison_grave=new QLabel();
	lay_->addWidget(poison_grave);
	QHBoxLayout *lay_combattants_=new QHBoxLayout();
	combattants=new QVBoxLayout();
	QLabel *titre_=new QLabel("Pokemon");
	titre_->setFixedHeight(titre_->font().pointSize());
	combattants->addWidget(titre_);
	lay_combattants_->addLayout(combattants);
	QSplitter *lay_relation_combattant_=new QSplitter(Qt::Vertical);
	QScrollArea *ascenseur_=new QScrollArea();
	groupe_=new QGroupBox("Attaques ou effets mettant en jeu une relation entre deux pokemons pendant plusieurs tours");
	attaques_rel_combattants=new QGridLayout();
	attaques_rel_combattants->addWidget(new QLabel("Nom"),0,0);
	attaques_rel_combattants->addWidget(new QLabel("Nombre de\ntours"),0,1);
	attaques_rel_combattants->addWidget(new QLabel("Nombre de\ntours minimal"),0,2);
	attaques_rel_combattants->addWidget(new QLabel("Nombre de\ntours maximal"),0,3);
	attaques_rel_combattants->addWidget(new QLabel("Nom de l'attaque\ndu pokemon selectionne"),0,4);
	attaques_rel_combattants->addWidget(new QLabel("Effet subi par le pokemon\nassocie a cette fiche"),0,5);
	groupe_->setLayout(attaques_rel_combattants);
	groupe_->setMinimumSize(800,800);
	ascenseur_->setWidget(groupe_);
	lay_relation_combattant_->addWidget(ascenseur_);
	ascenseur_=new QScrollArea();
	groupe_=new QGroupBox("Table d'efficacite des types offensifs (horizontaux) sur les types defensifs (verticaux)");
	groupe_->setMinimumSize(800,800);
	table_types=new QGridLayout();
	noms_types<<_d->val_noms_types_fr();
	noms_types.sort();
	int max_long_=0;
	foreach(QString t,noms_types){
		max_long_=Utilitaire::max_min<int>(max_long_,t.size()).first;
	}
	int i_=0;
	int nb_col_=coeff_types->columnCount();
	QLabel *etiq_=new QLabel("");
	etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
	table_types->addWidget(etiq_,0,0);
	foreach(QString a,noms_types){
		etiq_=new QLabel(a);
		etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
		coeff_types->addWidget(etiq_,i_+1,0);
		for(int i=1;i<nb_col_;i++){
			etiq_=new QLabel("");
			//etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
			coeff_types->addWidget(etiq_,i_+1,i);
		}
		etiq_=new QLabel(a);
		etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
		table_types->addWidget(etiq_,i_+1,0);
		etiq_=new QLabel(a);
		etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
		table_types->addWidget(etiq_,0,i_+1);
		i_++;
	}
	int nb_t_=noms_types.size();
	for(int i=1;i<=nb_t_;i++){
		for(int j=1;j<=nb_t_;j++){
			etiq_=new QLabel("");
			etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
			table_types->addWidget(etiq_,i,j);
		}
	}
	groupe_->setLayout(table_types);
	ascenseur_->setWidget(groupe_);
	lay_relation_combattant_->addWidget(ascenseur_);
	attaques_possedees=new QLabel("Attaques interdites");
	attaques_possedees->setMinimumSize(200,50);
	lay_relation_combattant_->addWidget(attaques_possedees);
	//table_types
	lay_combattants_->addWidget(lay_relation_combattant_);
	lay_->addLayout(lay_combattants_);
	QHBoxLayout *lay_cibles_=new QHBoxLayout();
	groupe_cibles=new QGroupBox("Cible et attaque choisie si le combat est contre un pokemon sauvage");
	cibles=new QGridLayout();
	groupe_cibles->setLayout(cibles);
	lay_cibles_->addWidget(groupe_cibles);
	QVBoxLayout *choix_=new QVBoxLayout();
	action_choisie=new QLabel();
	choix_->addWidget(action_choisie);
	attaque_choisie=new QLabel();
	choix_->addWidget(attaque_choisie);
	envoye=new QLabel();
	choix_->addWidget(envoye);
	lay_cibles_->addLayout(choix_);
	choix_=new QVBoxLayout();
	der_att_lancee=new QLabel();
	choix_->addWidget(der_att_lancee);
	der_att_reussie=new QLabel();
	choix_->addWidget(der_att_reussie);
	der_objet_utilise=new QLabel();
	choix_->addWidget(der_objet_utilise);
	lay_cibles_->addLayout(choix_);
	lay_->addLayout(lay_cibles_);
	setLayout(lay_);
	//attaques_lancees
}

void FicheCreature::maj_fiche(const Combattant& _cbt,const CreatureCombat& _cr_c,const ElementsCombat& _elt,Donnees* _d){
	int num_=_cr_c.fiche_pokemon(_d)->num();
	image_pk->setPixmap(QPixmap::fromImage(_d->val_images_face_m().valeur(num_)));
	types_pk->setText("types:\n"+_cr_c.types_pk().join("\n"));
	pseudo->setText(_cr_c.pseudo_pk());
	capacite_act->setText("Capacite actuelle:"+_cr_c.capacite_pk_act());
	if(_cr_c.capacite_pk_act()!=_cr_c.capacite_pk_ini()){
		capacite->setText("Capacite de base:"+_cr_c.capacite_pk_ini());
	}else{
		capacite->setText("");
	}
	bonheur->setText(QString::number(_cr_c.bonheur_pk()));
	if(_cr_c.prepa_tour_pk()){
		prepa_tour->setText("En cours de preparation d'attaque: OUI");
	}else{
		prepa_tour->setText("En cours de preparation d'attaque: NON");
	}
	if(_cr_c.nec_recharg_pk()){
		nec_recharg->setText("Necessite un tour de rechargement: OUI");
	}else{
		nec_recharg->setText("Necessite un tour de rechargement: NON");
	}
	if(noms_statistiques.isEmpty()){
		noms_statistiques<<"ATTAQUE";
		noms_statistiques<<"DEFENSE";
		noms_statistiques<<"ATTAQUE_SPECIALE";
		noms_statistiques<<"DEFENSE_SPECIALE";
		noms_statistiques<<"VITESSE";
		noms_statistiques<<"PV";
		noms_statistiques<<"PRECISION";
		noms_statistiques<<"ESQUIVE";
		noms_statistiques<<"COUP_CRITIQUE";
		int i_=0;
		foreach(QString s,noms_statistiques){
			statistiques->addWidget(new QLabel(s),i_+1,0);
			if(s=="PV"){
				statistiques->addWidget(new QLabel(QString::number(_cr_c.ev_mod(s))),i_+1,1);
				statistiques->addWidget(new QLabel(QString::number(_cr_c.iv_mod(s))),i_+1,2);
				statistiques->addWidget(new QLabel(QString::number(_cr_c.pv_max())),i_+1,4);
			}else if(s=="PRECISION"||s=="ESQUIVE"){
				statistiques->addWidget(new QLabel(QString::number(_cr_c.boost(s))),i_+1,3);
			}else if(s=="COUP_CRITIQUE"){
				statistiques->addWidget(new QLabel(QString::number(_cr_c.r_boost_cc())),i_+1,3);
			}else{
				statistiques->addWidget(new QLabel(QString::number(_cr_c.ev_mod(s))),i_+1,1);
				statistiques->addWidget(new QLabel(QString::number(_cr_c.iv_mod(s))),i_+1,2);
				statistiques->addWidget(new QLabel(QString::number(_cr_c.boost(s))),i_+1,3);
				statistiques->addWidget(new QLabel(_cr_c.statistique_mod_globale(s,_cr_c.ev_mod(s),_cr_c.iv_mod(s)).evaluer(3)),i_+1,4);
			}
			i_++;
		}
		//
	}else{
		int i_=0;
		foreach(QString s,noms_statistiques){
			QLabel *etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,0)->widget());
			etiquette_->setText(s);
			if(s=="PV"){
				etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,1)->widget());
				etiquette_->setText(QString::number(_cr_c.ev_mod(s)));
				etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,2)->widget());
				etiquette_->setText(QString::number(_cr_c.iv_mod(s)));
				etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,4)->widget());
				etiquette_->setText(QString::number(_cr_c.pv_max()));
			}else if(s=="PRECISION"||s=="ESQUIVE"){
				etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,3)->widget());
				etiquette_->setText(QString::number(_cr_c.boost(s)));
			}else if(s=="COUP_CRITIQUE"){
				etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,3)->widget());
				etiquette_->setText(QString::number(_cr_c.r_boost_cc()));
			}else{
				etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,1)->widget());
				etiquette_->setText(QString::number(_cr_c.ev_mod(s)));
				etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,2)->widget());
				etiquette_->setText(QString::number(_cr_c.iv_mod(s)));
				etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,3)->widget());
				etiquette_->setText(QString::number(_cr_c.boost(s)));
				etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,4)->widget());
				etiquette_->setText(_cr_c.statistique_mod_globale(s,_cr_c.ev_mod(s),_cr_c.iv_mod(s)).evaluer(3));
			}
			i_++;
		}
	}
	bool vent_arriere_=_elt.attaque_equipe(_cbt.equipe(),"VENT_ARRIERE").second;
	bool aire_eau_herbre_=_elt.attaque_equipe(_elt.adversaire(_cbt.equipe()),"AIRE_EAU_HERBE").second;
	bool zone_magique_=_elt.effet_global("ZONE_MAGIQUE").second;
	vitesse->setText("Vitesse globale: "+_cr_c.vitesse(aire_eau_herbre_,zone_magique_,vent_arriere_,_elt.climat_gl(),_d).evaluer(3));
	clone_pk->setText("Pv du clone: "+_cr_c.clone_pk().evaluer(3));
	if(noms_attaques.isEmpty()){
		noms_attaques<<_d->val_attaques_actives_definies();
		noms_attaques<<_d->val_attaques_actives_indefinies();
		noms_attaques.sort();
		int i_=0;
		int nb_col_=attaques->columnCount();
		foreach(QString a,noms_attaques){
			attaques->addWidget(new QLabel(a),i_+1,0);
			for(int i=1;i<nb_col_;i++){
				attaques->addWidget(new QLabel(""),i_+1,i);
			}
			i_++;
		}
	}
	//int i_=0;
	foreach(QString a,noms_attaques){
		int i_=noms_attaques.indexOf(a);
		QLabel *etiquette_=qobject_cast<QLabel*>(attaques->itemAtPosition(i_+1,1)->widget());
		if(_d->val_attaques_actives_definies().contains(a)){
			QPair<uchar,bool> val_=_cr_c.attaques_actives_def(a);
			if(val_.second){
				etiquette_->setText(QString::number(val_.first+1));
			}else{
				etiquette_->setText(QString::number(val_.first));
			}
		}else if(_cr_c.attaques_actives_ind(a)){
			etiquette_->setText("ACTIF");
		}else{
			etiquette_->setText("INACTIF");
		}
	}
	QPair<QString,uchar> att_copie_=_cr_c.att_copie();
	if(att_copie_.first!=""){
		copie->setText("Attaque copiee: "+att_copie_.first+", nombre de pp restants: "+QString::number(att_copie_.second));
	}else{
		copie->setText("Attaque copiee: , nombre de pp restants: 0");
	}
	QPair<uchar,bool> confusion_=_cr_c.confusion_pk();
	if(confusion_.second){
		confusion->setText("Nombre de tours de confusion: "+QString::number(confusion_.first+1));
	}else{
		confusion->setText("Nombre de tours de confusion: "+QString::number(confusion_.first));
	}
	QPair<uchar,QPair<Taux,bool> > patience_=_cr_c.patience_pk();
	if(patience_.second.second){
		patience->setText("Nombre de tours de patience: "+QString::number(confusion_.first+1)+", degats encaisses: "+patience_.second.first.evaluer(3));
	}else{
		patience->setText("Nombre de tours de patience: "+QString::number(confusion_.first)+", degats encaisses: 0");
	}
	coefficient_roul_ball_glace->setText("Coefficient de puissance pour roulade ou ball glace: "+QString::number(_cr_c.coeff_roul_ballglace()));
	succes_abris->setText("Nombre total de succes des attaques d'\"abris\": "+QString::number(_cr_c.succes_abris()));
	if(noms_attaques_lancees.isEmpty()){
		noms_attaques_lancees<<"STOCKAGE";
		noms_attaques_lancees<<"TAILLADE";
		int i_=0;
		int nb_col_=attaques_lancees->columnCount();
		foreach(QString a,noms_attaques_lancees){
			attaques_lancees->addWidget(new QLabel(a),i_+1,0);
			for(int i=1;i<nb_col_;i++){
				attaques_lancees->addWidget(new QLabel(""),i_+1,i);
			}
			i_++;
		}
	}
	int i_=0;
	foreach(QString a,noms_attaques_lancees){
		QLabel *etiquette_=qobject_cast<QLabel*>(attaques_lancees->itemAtPosition(i_+1,1)->widget());
		etiquette_->setText(QString::number(_cr_c.nb_lancer(a)));
		i_++;
	}
	i_=0;
	/*if(noms_types.isEmpty()){
		noms_types<<_d->val_noms_types_fr();
		noms_types.sort();
		int max_long_=0;
		foreach(QString t,noms_types){
			max_long_=Utilitaire::max_min<int>(max_long_,t.size()).first;
		}
		int i_=0;
		int nb_col_=coeff_types->columnCount();
		QLabel *etiq_=new QLabel("");
		etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
		table_types->addWidget(etiq_,0,0);
		foreach(QString a,noms_types){
			etiq_=new QLabel(a);
			etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
			coeff_types->addWidget(etiq_,i_+1,0);
			for(int i=1;i<nb_col_;i++){
				etiq_=new QLabel("");
				//etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
				coeff_types->addWidget(etiq_,i_+1,i);
			}
			etiq_=new QLabel(a);
			etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
			table_types->addWidget(etiq_,i_+1,0);
			etiq_=new QLabel(a);
			etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
			table_types->addWidget(etiq_,0,i_+1);
			i_++;
		}
		int nb_t_=noms_types.size();
		for(int i=1;i<=nb_t_;i++){
			for(int j=1;j<=nb_t_;j++){
				etiq_=new QLabel("");
				etiq_->setMinimumSize(max_long_*etiq_->font().pointSize(),etiq_->font().pointSize());
				table_types->addWidget(etiq_,i,j);
			}
		}
		std::cout<<etiq_->minimumHeight()<<";"<<etiq_->minimumWidth()<<"\n";
	}*/
	foreach(QString t,noms_types){
		QLabel *etiquette_=qobject_cast<QLabel*>(coeff_types->itemAtPosition(i_+1,1)->widget());
		etiquette_->setText(_cr_c.coeff_att_type(t).chaine());
		etiquette_=qobject_cast<QLabel*>(coeff_types->itemAtPosition(i_+1,2)->widget());
		etiquette_->setText(_cr_c.coeff_att_type_2(t).chaine());
		etiquette_=qobject_cast<QLabel*>(coeff_types->itemAtPosition(i_+1,3)->widget());
		etiquette_->setText(_cr_c.r_coeff_att_types_lancees(t).chaine());
		etiquette_=qobject_cast<QLabel*>(coeff_types->itemAtPosition(i_+1,4)->widget());
		bool immu_=_cr_c.immu_att_type(t);
		if(immu_){
			etiquette_->setText("OUI");
		}else{
			etiquette_->setText("NON");
		}
		i_++;
	}
	sommeil_non_repos->setText("Nombre de tours de sommeil autre que de repos: "+QString::number(_cr_c.sommeil_non_repos()));
	poison_grave->setText("Nombre de tours de poison grave: "+QString::number(_cr_c.nb_tours_poison_grave_pk()));
	Combattant cbt_;
	HashMap<Combattant,CreatureCombat> cr_cbt_=_elt.creatures_combats();
	int nb_cbts_=combattants->count()-1;
	for(int i=1;i<=nb_cbts_;i++){
		combattants->itemAt(i)->widget()->deleteLater();;
	}
	for(int i=0;i<nb_cbts_;i++){
		combattants->removeItem(combattants->itemAt(1));
	}
	liste_combattants.tout_supprimer();
	foreach(Combattant c,cr_cbt_.cles()){
		cbt_=c;
		EtiquetteCombattant *etiquette_=new EtiquetteCombattant(c,cr_cbt_.valeur(c),_elt.position(c).second,_d);
		connect(etiquette_,SIGNAL(clic(Combattant)),this,SLOT(maj_fiche(Combattant)));
		combattants->addWidget(etiquette_);
		liste_combattants.ajouter_cle_valeur(c,etiquette_);
	}
	attaques_possessif=_cr_c.possessif();
	attaques_sur_combat_att=_cr_c.attaques_sur_cible();
	attaques_piegeantes=_cr_c.h_attaques_piegeantes();
	relations_comb=_cr_c.relations();
	h_table_types=_cr_c.table();
	maj_fiche(cbt_);
	if(_cbt.equipe()==(int)_d->val_adv()){
		nb_cbts_=cibles->count();
		for(int i=0;i<nb_cbts_;i++){
			cibles->itemAt(i)->widget()->deleteLater();;
		}
		for(int i=0;i<nb_cbts_;i++){
			cibles->removeItem(combattants->itemAt(0));
		}
		if(_elt.type_cbt()!="SAUVAGE"){
			foreach(Combattant c,_elt.cibles_lanceur(_cbt,_d)){
				EtiquetteCombattant *etiquette_=new EtiquetteCombattant(c,cr_cbt_.valeur(c),_elt.position(c).second,_d);
				cibles->addWidget(etiquette_);
				//
			}
			action_choisie->setText("Action choisie: "+_cr_c.act_choisie());
			attaque_choisie->setText("Attaque choisie: "+_cr_c.att_choisie());
			if(_cr_c.remplacant()!=Combattant()){
				envoye->setText("Envoye: "+cr_cbt_.valeur(_cr_c.remplacant()).nom_pk_act());
			}
		}else{
			liste_attaques.tout_supprimer();
			typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
			QList<AttaquePP> attaques_=_cr_c.attaques_act_pk();
			foreach(AttaquePP a,attaques_){
				EtiquetteAttaque *etiquette_=new EtiquetteAttaque(a.first,a.first+" "+QString::number(a.second.first)+"/"+QString::number(a.second.second));
				connect(etiquette_,SIGNAL(clic(QString)),this,SLOT(attaque_cliquee(QString)));
				cibles->addWidget(etiquette_);
				liste_attaques.ajouter_cle_valeur(a.first,etiquette_);
			}
			//
		}
	}else{
		action_choisie->setText("Action choisie: "+_cr_c.act_choisie());
		attaque_choisie->setText("Attaque choisie: "+_cr_c.att_choisie());
		if(_cr_c.remplacant()!=Combattant()){
			envoye->setText("Envoye: "+cr_cbt_.valeur(_cr_c.remplacant()).nom_pk_act());
		}
	}
	der_att_lancee->setText("Derniere attaque lancee: "+_cr_c.der_att_lancee());
	der_att_reussie->setText("Derniere attaque reussie: "+_cr_c.der_att_reussie());
	der_objet_utilise->setText("Derniere attaque reussie: "+_cr_c.val_der_objet_ut());
	//copie
}

void FicheCreature::maj_fiche(const Combattant& _cbt){
	foreach(Combattant c,liste_combattants.cles()){
		liste_combattants.valeur(c)->maj_choix(false);
	}
	liste_combattants.valeur(_cbt)->maj_choix(true);
	foreach(Combattant c,liste_combattants.cles()){
		liste_combattants.valeur(c)->repaint();
	}
	//
	typedef QPair<QString,Combattant> ChaineCbt;
	typedef QPair<Combattant,QString> CbtChaine;
	if(noms_attaques_rel_combattants.isEmpty()){
		foreach(ChaineCbt c,attaques_sur_combat_att.cles()){
			if(c.second==_cbt){
				noms_attaques_rel_combattants<<c.first;
			}
		}
		foreach(CbtChaine c,attaques_piegeantes.cles()){
			if(c.first==_cbt){
				noms_attaques_rel_combattants<<c.second;
			}
		}
		foreach(QString a,relations_comb.cles()){
			noms_attaques_rel_combattants<<a;
		}
		noms_attaques_rel_combattants.sort();
		int nb_col_=attaques_rel_combattants->columnCount();
		int i_=0;
		foreach(QString a,noms_attaques_rel_combattants){
			attaques_rel_combattants->addWidget(new QLabel(a),i_+1,0);
			for(int i=1;i<nb_col_;i++){
				attaques_rel_combattants->addWidget(new QLabel(""),i_+1,i);
			}
			i_++;
		}
	}
	foreach(ChaineCbt c,attaques_sur_combat_att.cles()){
		if(c.second==_cbt){
			int i_=noms_attaques_rel_combattants.indexOf(c.first);
			QPair<QString,QPair<bool,uchar> > valeur_=attaques_sur_combat_att.valeur(c);
			QLabel *etiquette_=qobject_cast<QLabel*>(attaques_rel_combattants->itemAtPosition(i_+1,1)->widget());
			if(valeur_.second.first){
				etiquette_->setText(QString::number(valeur_.second.second+1));
			}else{
				etiquette_->setText(QString::number(valeur_.second.second));
			}
			etiquette_=qobject_cast<QLabel*>(attaques_rel_combattants->itemAtPosition(i_+1,4)->widget());
			etiquette_->setText(valeur_.first);
			etiquette_=qobject_cast<QLabel*>(attaques_rel_combattants->itemAtPosition(i_+1,0)->widget());
			etiquette_->setText(c.first);
		}
	}
	foreach(CbtChaine c,attaques_piegeantes.cles()){
		if(c.first==_cbt){
			int i_=noms_attaques_rel_combattants.indexOf(c.second);
			QPair<bool,uchar> valeur_=attaques_piegeantes.valeur(c);
			QLabel *etiquette_=qobject_cast<QLabel*>(attaques_rel_combattants->itemAtPosition(i_+1,1)->widget());
			if(valeur_.first){
				etiquette_->setText(QString::number(valeur_.second+1));
			}else{
				etiquette_->setText(QString::number(valeur_.second));
			}
			etiquette_=qobject_cast<QLabel*>(attaques_rel_combattants->itemAtPosition(i_+1,0)->widget());
			etiquette_->setText(c.second);
		}
	}
	foreach(QString a,relations_comb.cles()){
		HashMap<Combattant,bool> val_=relations_comb.valeur(a);
		foreach(Combattant c,val_.cles()){
			if(c==_cbt){
				int i_=noms_attaques_rel_combattants.indexOf(a);
				QLabel *etiquette_=qobject_cast<QLabel*>(attaques_rel_combattants->itemAtPosition(i_+1,1)->widget());
				if(val_.valeur(c)){
					etiquette_->setText("ACTIF");
				}else{
					etiquette_->setText("INACTIF");
				}
				etiquette_=qobject_cast<QLabel*>(attaques_rel_combattants->itemAtPosition(i_+1,0)->widget());
				etiquette_->setText(a);
			}
		}
	}
	if(h_table_types.cles().contains(_cbt)){//TODO etre plus generique
		HashMap<QPair<QString,QString>,Taux> valeur_=h_table_types.valeur(_cbt);
		typedef QPair<QString,QString> Types;
		foreach(Types t,valeur_.cles()){
			int i_=noms_types.indexOf(t.first);
			int j_=noms_types.indexOf(t.second);
			QLabel *etiquette_=qobject_cast<QLabel*>(table_types->itemAtPosition(j_+1,i_+1)->widget());
			etiquette_->setText(valeur_.valeur(t).chaine());
		}
		attaques_possedees->setText("attaques interdites:\n"+attaques_possessif.valeur(_cbt).join("\n"));
	}
}

void FicheCreature::attaque_cliquee(const QString& _attaque){
	foreach(QString a,liste_attaques.cles()){
		liste_attaques.valeur(a)->maj_choix(false);
	}
	liste_attaques.valeur(_attaque)->maj_choix(true);
	foreach(QString a,liste_attaques.cles()){
		liste_attaques.valeur(a)->repaint();
	}
	emit clic_attaque(_attaque);
}

FicheCreature::~FicheCreature(){
	//
}
