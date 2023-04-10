#include "ihm/combat/fiches/ficheelements.h"
#include "ihm/combat/etiquettes/etiquettecombattant.h"
#include "ihm/combat/etiquettes/etiquetteattaque.h"
#include "ihm/combat/etiquettes/etiquetteequipe.h"
#include "ihm/combat/etiquettes/etiquetteposition.h"
#include "serialisable/combat/combattant.h"
#include "serialisable/combat/creaturecombat.h"
#include "serialisable/combat/elementscombat.h"
#include "base_donnees/donnees.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

FicheElements::FicheElements(Donnees* _d){
	QVBoxLayout *lay_=new QVBoxLayout();
	QHBoxLayout *ligne_;
	//QHBoxLayout *lay_infos_gener_=new QHBoxLayout();
	ligne_=new QHBoxLayout();
	multiplicite=new QLabel();
	ligne_->addWidget(multiplicite);
	ligne_->addStretch();
	lay_->addLayout(ligne_);
	fuite=new QLabel();
	lay_->addWidget(fuite);
	argent=new QLabel();
	lay_->addWidget(argent);
	QGroupBox *groupe_=new QGroupBox("Informations sur le climat");
	QVBoxLayout *lay_climat_=new QVBoxLayout();
	nom_climat=new QLabel();
	lay_climat_->addWidget(nom_climat);
	nombre_tours_climat=new QLabel();
	lay_climat_->addWidget(nombre_tours_climat);
	nombre_tours_min_climat=new QLabel();
	lay_climat_->addWidget(nombre_tours_min_climat);
	nombre_tours_max_climat=new QLabel();
	lay_climat_->addWidget(nombre_tours_max_climat);
	climat_actif=new QLabel();
	lay_climat_->addWidget(climat_actif);
	groupe_->setLayout(lay_climat_);
	lay_->addWidget(groupe_);
	ligne_=new QHBoxLayout();
	groupe_=new QGroupBox("Attaques globales");
	effets_globaux=new QGridLayout();
	effets_globaux->addWidget(new QLabel("Nom"),0,0);
	effets_globaux->addWidget(new QLabel("Nombre de tours"),0,1);
	effets_globaux->addWidget(new QLabel("Nombre minimal de tours"),0,2);
	effets_globaux->addWidget(new QLabel("Nombre maximal de tours"),0,3);
	groupe_->setLayout(effets_globaux);
	ligne_->addWidget(groupe_);
	ligne_->addStretch();
	lay_->addLayout(ligne_);
	QVBoxLayout *lay_equipe_=new QVBoxLayout();
	ligne_=new QHBoxLayout();
	QVBoxLayout *tableau_equipe_=new QVBoxLayout();
	tableau_equipe_->addWidget(new QLabel("Equipe"));
	bouton_ut=new EtiquetteEquipe(_d->val_ut());
	bouton_ut->setText("JOUEUR");
	bouton_ut->redim();
	connect(bouton_ut,SIGNAL(clic(uchar)),this,SLOT(maj_fiche(uchar)));
	tableau_equipe_->addWidget(bouton_ut);
	bouton_adv=new EtiquetteEquipe(_d->val_adv());
	bouton_adv->setText("ADVERSAIRE");
	bouton_adv->redim();
	connect(bouton_adv,SIGNAL(clic(uchar)),this,SLOT(maj_fiche(uchar)));
	tableau_equipe_->addWidget(bouton_adv);
	ligne_->addLayout(tableau_equipe_);
	ligne_->addStretch();
	lay_equipe_->addLayout(ligne_);
	ligne_=new QHBoxLayout();
	groupe_=new QGroupBox("Attaques de l'equipe selectionnee");
	effets_attaques_equipes=new QGridLayout();
	effets_attaques_equipes->addWidget(new QLabel("Nom"),0,0);
	effets_attaques_equipes->addWidget(new QLabel("Nombre de tours"),0,1);
	effets_attaques_equipes->addWidget(new QLabel("Nombre minimal de tours"),0,2);
	effets_attaques_equipes->addWidget(new QLabel("Nombre maximal de tours"),0,3);
	groupe_->setLayout(effets_attaques_equipes);
	ligne_->addWidget(groupe_);
	ligne_->addStretch();
	lay_equipe_->addLayout(ligne_);
	vengeance_effet=new QLabel();
	lay_equipe_->addWidget(vengeance_effet);
	ligne_=new QHBoxLayout();
	groupe_=new QGroupBox("Nombre de lancers des attaques de l'equipe selectionnee");
	nb_lancers_attaques_equipes=new QGridLayout();
	nb_lancers_attaques_equipes->addWidget(new QLabel("Nom"),0,0);
	nb_lancers_attaques_equipes->addWidget(new QLabel("Nombre d'utilisations"),0,1);
	groupe_->setLayout(nb_lancers_attaques_equipes);
	ligne_->addWidget(groupe_);
	ligne_->addStretch();
	lay_equipe_->addLayout(ligne_);
	//ligne_=new QHBoxLayout();
	lay_->addLayout(lay_equipe_);
	ligne_=new QHBoxLayout();
	groupe_=new QGroupBox("Positions de front des equipes");
	positions=new QVBoxLayout();
	groupe_->setLayout(positions);
	ligne_->addWidget(groupe_);
	QVBoxLayout *lay_positions_=new QVBoxLayout();
	groupe_=new QGroupBox("Effets de l'attaque VOEU");
	voeu_attaque=new QGridLayout();
	voeu_attaque->addWidget(new QLabel("Nombre de tours"),0,0);
	voeu_attaque->addWidget(new QLabel("Deja actif"),0,1);
	voeu_attaque->addWidget(new QLabel("Nombre maximal de tours"),0,2);
	groupe_->setLayout(voeu_attaque);
	lay_positions_->addWidget(groupe_);
	groupe_=new QGroupBox("Effets des attaques PRESCIENCE et CARNAREKET");
	presc_carnar_attaque=new QGridLayout();
	presc_carnar_attaque->addWidget(new QLabel("Nom"),0,0);
	presc_carnar_attaque->addWidget(new QLabel("Nombre\nde tours"),0,1);
	presc_carnar_attaque->addWidget(new QLabel("Nombre maximal\nde tours"),0,2);
	presc_carnar_attaque->addWidget(new QLabel("Degats\nminimaux"),0,3);
	presc_carnar_attaque->addWidget(new QLabel("Degats\nmaximaux"),0,4);
	presc_carnar_attaque->addWidget(new QLabel("Combattant\nactuellement touche"),0,5);
	presc_carnar_attaque->addWidget(new QLabel("Ko"),0,6);
	groupe_->setLayout(presc_carnar_attaque);
	lay_positions_->addWidget(groupe_);
	ligne_->addLayout(lay_positions_);
	ligne_->addStretch();
	lay_->addLayout(ligne_);
	ligne_=new QHBoxLayout();
	groupe_=new QGroupBox("Pokemons adverses");
	boutons_adv=new QVBoxLayout();
	groupe_->setLayout(boutons_adv);
	ligne_->addWidget(groupe_);
	groupe_=new QGroupBox("Vos pokemons");
	boutons_ut=new QVBoxLayout();
	groupe_->setLayout(boutons_ut);
	ligne_->addWidget(groupe_);
	ligne_->addStretch();
	lay_->addLayout(ligne_);
	//ligne_->addStretch();
	//lay_equipe_->addStretch();
	//lay_->addLayout(ligne_);
	//maj_fiche(_d->val_ut());
	//nb_lancers_attaques_equipes
	setLayout(lay_);
	equipe_ut=_d->val_ut();
	arriere=_d->constante_numerique("ARRIERE");
}

void FicheElements::maj_fiche(const ElementsCombat& _elt,const Difficulte& _diff,Donnees* _d){
	difficulte=_diff;
	multiplicite->setText(QString::number(_elt.mult_cbt()));
	if(_elt.type_cbt()=="SAUVAGE"){
		fuite->setText("Nombre de tentative de fuite: "+QString::number(_elt.nb_fuite()));//TODO methode pour la fuite
	}
	argent->setText("Variation d'argent: "+_elt.argent().evaluer(3));
	QPair<QPair<QString,uchar>,QPair<bool,bool> > climat_=_elt.climat_gl();
	nom_climat->setText("nom du climat en cours: "+climat_.first.first);
	if(!climat_.second.second){
		nombre_tours_climat->setText("nombre de tours ecoules pour le climat en cours: "+QString::number(climat_.first.second));
	}else{
		nombre_tours_climat->setText("nombre de tours ecoules pour le climat en cours: INDEFINI");
	}
	if(!climat_.second.first){
		climat_actif->setText("Climat actif");
	}else{
		climat_actif->setText("Climat inactif");
	}
	int i_=0;
	if(attaques_globales.isEmpty()){
		attaques_globales=_elt.attaques_globales().cles();
		attaques_globales.sort();
		int i_=0;
		int nb_col_=effets_globaux->columnCount();
		foreach(QString a,attaques_globales){
			effets_globaux->addWidget(new QLabel(a),i_+1,0);
			for(int i=1;i<nb_col_;i++){
				effets_globaux->addWidget(new QLabel(""),i_+1,i);
			}
			i_++;
		}
	}
	i_=0;
	foreach(QString a,_elt.attaques_globales().cles()){
		QPair<uchar,bool> valeur_=_elt.effet_global(a);
		QLabel *etiquette_=qobject_cast<QLabel*>(effets_globaux->itemAtPosition(i_+1,1)->widget());
		if(valeur_.second){
			etiquette_->setText(QString::number(valeur_.first+1));
		}else{
			etiquette_->setText(QString::number(valeur_.first));
		}
		i_++;
	}
	//TODO
	nb_tour_attaque_equipe=_elt.attaques_equipes();
	nb_utilisation_attaques=_elt.nb_util_attaq();
	vengeance_actif=_elt.vengeance();
	maj_fiche(_d->val_ut());
	voeu_gl=_elt.voeu_gl();
	attaques_prepa_tours=_elt.attaques_prepa_tours();
	typedef QPair<int,int> Position;
	foreach(Position p,liste_positions.cles()){
		liste_positions.valeur(p)->deleteLater();
		positions->removeWidget(liste_positions.valeur(p));
	}
	liste_positions.tout_supprimer();
	for(int i=0;i<_elt.mult_cbt();i++){
		EtiquettePosition *etiquette_=new EtiquettePosition(_d->val_ut(),i,arriere,equipe_ut);
		connect(etiquette_,SIGNAL(clic(QPair<int,int>)),this,SLOT(maj_fiche(QPair<int,int>)));
		positions->addWidget(etiquette_);
		liste_positions.ajouter_cle_valeur(QPair<int,int>(_d->val_ut(),i),etiquette_);
		etiquette_=new EtiquettePosition(_d->val_adv(),i,arriere,equipe_ut);
		connect(etiquette_,SIGNAL(clic(QPair<int,int>)),this,SLOT(maj_fiche(QPair<int,int>)));
		positions->addWidget(etiquette_);
		liste_positions.ajouter_cle_valeur(QPair<int,int>(_d->val_adv(),i),etiquette_);
	}
	maj_fiche(QPair<int,int>(equipe_ut,0));
	combattants_adverses=_elt.combattants_ut();
	HashMap<Combattant,CreatureCombat> cr_=_elt.creatures_combats();
	Combattant cbt_non_ko_;
	foreach(Combattant c,cr_.cles()){
		if(c.equipe()==_d->val_ut()){
			continue;
		}
		if(cr_.valeur(c).statut_pk()!="KO"){
			cbt_non_ko_=c;
			break;
		}
	}
	/*int nb_cbt_=boutons_adv->count();
	for(int i=0;i<nb_cbt_;i++){
		boutons_adv->removeItem(boutons_adv->itemAt(0));
	}*/
	foreach(Combattant c,liste_combattants.cles()){
		liste_combattants.valeur(c)->deleteLater();
		boutons_adv->removeWidget(liste_combattants.valeur(c));
	}
	liste_combattants.tout_supprimer();
	positions_places.tout_supprimer();
	noms_combattants.tout_supprimer();
	pv_restants.tout_supprimer();
	foreach(Combattant c,cr_.cles()){
		positions_places.ajouter_cle_valeur(c,_elt.position(c));
		CreatureCombat& cr_c_=cr_.valeur(c);
		noms_combattants.ajouter_cle_valeur(c,cr_c_.nom_pk_act());
		pv_restants.ajouter_cle_valeur(c,cr_c_.pv_restants_pk());
		if(c.equipe()==_d->val_ut()){
			continue;
		}
		EtiquetteCombattant *etiquette_=new EtiquetteCombattant(c,cr_c_,_elt.position(c).second,_d);
		connect(etiquette_,SIGNAL(clic(Combattant)),this,SLOT(maj_fiche(Combattant)));
		boutons_adv->addWidget(etiquette_);
		liste_combattants.ajouter_cle_valeur(c,etiquette_);
	}
	if(cbt_non_ko_!=Combattant()){
		maj_fiche(cbt_non_ko_);
	}
	//
}

void FicheElements::maj_fiche(uchar _equipe){
	bouton_adv->maj_choix(false);
	bouton_ut->maj_choix(false);
	if(equipe_ut==_equipe){
		bouton_ut->maj_choix(true);
	}else{
		bouton_adv->maj_choix(true);
	}
	bouton_ut->repaint();
	bouton_adv->repaint();
	HashMap<QString,QPair<uchar,bool> > att_eq_=nb_tour_attaque_equipe.valeur(_equipe);
	if(attaques_equipes.isEmpty()){
		attaques_equipes=att_eq_.cles();
		attaques_equipes.sort();
		int i_=0;
		int nb_col_=effets_attaques_equipes->columnCount();
		foreach(QString a,attaques_equipes){
			effets_attaques_equipes->addWidget(new QLabel(a),i_+1,0);
			for(int i=1;i<nb_col_;i++){
				effets_attaques_equipes->addWidget(new QLabel(""),i_+1,i);
			}
			i_++;
		}
	}
	foreach(QString a,att_eq_.cles()){
		int i_=attaques_equipes.indexOf(a);
		QPair<uchar,bool> valeur_=att_eq_.valeur(a);
		QLabel *etiquette_=qobject_cast<QLabel*>(effets_attaques_equipes->itemAtPosition(i_+1,1)->widget());
		if(a!="PICOTS"&&a!="PICS_TOXIKS"&&a!="PIEGE_DE_ROC"){
			if(valeur_.second){
				etiquette_->setText(QString::number(valeur_.first+1));
			}else{
				etiquette_->setText(QString::number(valeur_.first));
			}
		}else{
			etiquette_->setText(QString::number(valeur_.first));
		}
	}
	QPair<bool,bool> veng_=vengeance_actif.valeur(_equipe);
	QString texte_;
	if(veng_.second){
		texte_+="Ko a l'avant dernier tour: VRAI\n";
	}else{
		texte_+="Ko a l'avant dernier tour: FAUX\n";
	}
	if(veng_.first){
		texte_+="Ko au dernier tour: VRAI";
	}else{
		texte_+="Ko au dernier tour: FAUX";
	}
	vengeance_effet->setText(texte_);
	typedef QPair<QString,uchar> AttaqueUtilisation;
	if(lancers_attaques_equipes.isEmpty()){
		foreach(AttaqueUtilisation a,nb_utilisation_attaques.cles()){
			if(a.second==_equipe){
				lancers_attaques_equipes<<a.first;
			}
		}
		lancers_attaques_equipes.sort();
		int i_=0;
		int nb_col_=nb_lancers_attaques_equipes->columnCount();
		foreach(QString a,lancers_attaques_equipes){
			nb_lancers_attaques_equipes->addWidget(new QLabel(a),i_+1,0);
			for(int i=1;i<nb_col_;i++){
				nb_lancers_attaques_equipes->addWidget(new QLabel(""),i_+1,i);
			}
			i_++;
		}
	}
	foreach(AttaqueUtilisation a,nb_utilisation_attaques.cles()){
		if(a.second==_equipe){
			int i_=lancers_attaques_equipes.indexOf(a.first);
			QLabel *etiquette_=qobject_cast<QLabel*>(nb_lancers_attaques_equipes->itemAtPosition(i_+1,1)->widget());
			etiquette_->setText(QString::number(nb_utilisation_attaques.valeur(a)));
		}
	}
	//
}

void FicheElements::maj_fiche(const Combattant& _cbt){
	foreach(Combattant c,liste_combattants.cles()){
		liste_combattants.valeur(c)->maj_choix(false);
	}
	liste_combattants.valeur(_cbt)->maj_choix(true);
	foreach(Combattant c,liste_combattants.cles()){
		liste_combattants.valeur(c)->repaint();
	}
	QList<uchar> cbts_ut_=combattants_adverses.valeur(_cbt.position());
	int nb_cbt_=boutons_ut->count();
	for(int i=0;i<nb_cbt_;i++){
		boutons_ut->itemAt(i)->widget()->deleteLater();
	}
	for(int i=0;i<nb_cbt_;i++){
		boutons_ut->removeItem(boutons_ut->itemAt(0));
	}
	foreach(uchar c,cbts_ut_){
		Combattant cbt_(equipe_ut,c);
		EtiquetteCombattant *etiquette_=new EtiquetteCombattant(cbt_,noms_combattants.valeur(cbt_),positions_places.valeur(cbt_).second,arriere);
		boutons_ut->addWidget(etiquette_);
		//const QString& _nom_act,int _position,int _arriere
	}
	//
}

void FicheElements::maj_fiche(const QPair<int,int>& _pos){
	typedef QPair<int,int> Position;
	foreach(Position c,liste_positions.cles()){
		liste_positions.valeur(c)->maj_choix(false);
	}
	liste_positions.valeur(_pos)->maj_choix(true);
	foreach(Position c,liste_positions.cles()){
		liste_positions.valeur(c)->repaint();
	}
	QPair<uchar,uchar> cle_(_pos.first,_pos.second);
	QPair<uchar,QPair<bool,bool> >& voeu_=voeu_gl.valeur(cle_);
	int nb_=voeu_attaque->count();
	for(int i=0;i<nb_;i++){
		voeu_attaque->itemAt(i)->widget()->deleteLater();;
	}
	for(int i=0;i<nb_;i++){
		voeu_attaque->removeItem(voeu_attaque->itemAt(0));
	}
	voeu_attaque->addWidget(new QLabel("Nombre de tours"),0,0);
	voeu_attaque->addWidget(new QLabel("Deja actif"),0,1);
	voeu_attaque->addWidget(new QLabel("Nombre maximal de tours"),0,2);
	if(voeu_.second.second){
		voeu_attaque->addWidget(new QLabel("OUI"),1,1);
	}else{
		voeu_attaque->addWidget(new QLabel("NON"),1,1);
	}
	if(voeu_.second.first){
		voeu_attaque->addWidget(new QLabel(QString::number(voeu_.first+1)),1,0);
	}else{
		voeu_attaque->addWidget(new QLabel(QString::number(voeu_.first)),1,0);
	}
	nb_=presc_carnar_attaque->count();
	for(int i=0;i<nb_;i++){
		presc_carnar_attaque->itemAt(i)->widget()->deleteLater();;
	}
	for(int i=0;i<nb_;i++){
		presc_carnar_attaque->removeItem(presc_carnar_attaque->itemAt(0));
	}
	presc_carnar_attaque->addWidget(new QLabel("Nom"),0,0);
	presc_carnar_attaque->addWidget(new QLabel("Nombre\nde tours"),0,1);
	presc_carnar_attaque->addWidget(new QLabel("Nombre maximal\nde tours"),0,2);
	presc_carnar_attaque->addWidget(new QLabel("Degats\nminimaux"),0,3);
	presc_carnar_attaque->addWidget(new QLabel("Degats\nmaximaux"),0,4);
	presc_carnar_attaque->addWidget(new QLabel("Combattant\nactuellement touche"),0,5);
	presc_carnar_attaque->addWidget(new QLabel("Ko"),0,6);
	typedef QPair<QString,QPair<uchar,uchar> > AttaquePosition;
	int i_=0;
	foreach(AttaquePosition a,attaques_prepa_tours.cles()){
		if(a.second.first==_pos.first&&a.second.second==_pos.second){
			QPair<QPair<Taux,uchar>,QPair<uchar,uchar> >& valeur_=attaques_prepa_tours.valeur(a);
			presc_carnar_attaque->addWidget(new QLabel(a.first),i_+1,0);
			presc_carnar_attaque->addWidget(new QLabel(QString::number(valeur_.first.second)),i_+1,1);
			Taux degats_=valeur_.first.first;
			Taux degats_min_(0);
			if(_pos.first==equipe_ut){
				degats_min_=degats_*CreatureCombat::loi_random(difficulte.r_choix_lois().first).minimum();
			}else{
				degats_min_=degats_*CreatureCombat::loi_random(difficulte.r_choix_lois().second).minimum();
			}
			presc_carnar_attaque->addWidget(new QLabel(degats_min_.evaluer(3)),i_+1,3);
			Taux degats_max_(0);
			if(_pos.first==equipe_ut){
				degats_max_=degats_*CreatureCombat::loi_random(difficulte.r_choix_lois().first).maximum();
			}else{
				degats_max_=degats_*CreatureCombat::loi_random(difficulte.r_choix_lois().second).maximum();
			}
			presc_carnar_attaque->addWidget(new QLabel(degats_max_.evaluer(3)),i_+1,4);
			QList<Combattant> cbts_t_=positions_places.cles(valeur_.second);
			if(cbts_t_.isEmpty()){
				presc_carnar_attaque->addWidget(new QLabel("AUCUN"),i_+1,5);
				presc_carnar_attaque->addWidget(new QLabel("NON"),i_+1,6);
			}else{
				Taux& pv_rest_=pv_restants.valeur(cbts_t_[0]);
				presc_carnar_attaque->addWidget(new EtiquetteCombattant(cbts_t_[0],noms_combattants.valeur(cbts_t_[0]),positions_places.valeur(cbts_t_[0]).second,arriere),i_+1,5);
				if(pv_rest_<=degats_min_){
					presc_carnar_attaque->addWidget(new QLabel("OUI"),i_+1,6);
				}else if(pv_rest_>degats_max_){
					presc_carnar_attaque->addWidget(new QLabel("NON"),i_+1,6);
				}else{
					presc_carnar_attaque->addWidget(new QLabel("PROBABLE"),i_+1,6);
				}
			}
			//
			i_++;
		}
	}
}
