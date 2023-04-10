#include "ihm/combat/fiches/ficheactions.h"
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
#include <QGroupBox>
#include <QScrollArea>
#include <iostream>

FicheActions::FicheActions(){
	mettre_a_jour_cr=true;
	attaque_selectionnee="";
	QVBoxLayout *centre_=new QVBoxLayout();
	QHBoxLayout *lay_=new QHBoxLayout();
	actions_possibles=new QVBoxLayout();
	attaquer=new EtiquetteAttaque("ATTAQUE","ATTAQUE");
	connect(attaquer,SIGNAL(clic(QString)),this,SLOT(maj_fiche_fct_action(QString)));
	actions_possibles->addWidget(attaquer);
	liste_actions.ajouter_cle_valeur("ATTAQUE",attaquer);
	switcher=new EtiquetteAttaque("SWITCH","SWITCH");
	connect(switcher,SIGNAL(clic(QString)),this,SLOT(maj_fiche_fct_action(QString)));
	actions_possibles->addWidget(switcher);
	liste_actions.ajouter_cle_valeur("SWITCH",switcher);
	soin=new EtiquetteAttaque("SOIN","SOIN");
	connect(soin,SIGNAL(clic(QString)),this,SLOT(maj_fiche_fct_action(QString)));
	actions_possibles->addWidget(soin);
	liste_actions.ajouter_cle_valeur("SOIN",soin);
	ne_rien_faire=new EtiquetteAttaque("","RIEN");
	connect(ne_rien_faire,SIGNAL(clic(QString)),this,SLOT(maj_fiche_fct_action(QString)));
	actions_possibles->addWidget(ne_rien_faire);
	liste_actions.ajouter_cle_valeur("",ne_rien_faire);
	lay_->addLayout(actions_possibles);
	QVBoxLayout *lay_attaques_objets_=new QVBoxLayout();
	QGroupBox *groupe_=new QGroupBox("Attaques de base du pokemon selectionne");
	attaques_possibles=new QVBoxLayout();
	groupe_->setLayout(attaques_possibles);
	lay_attaques_objets_->addWidget(groupe_);
	groupe_=new QGroupBox("Attaques actuelles du pokemon selectionne");
	attaques_act_possibles=new QVBoxLayout();
	groupe_->setLayout(attaques_act_possibles);
	lay_attaques_objets_->addWidget(groupe_);
	conteneur_objets=new QScrollArea();
	conteneur_objets->setWidgetResizable(true);
	groupe_=new QGroupBox("Objets");
	objets_possibles=new QVBoxLayout();
	groupe_->setLayout(objets_possibles);
	conteneur_objets->setWidget(groupe_);
	lay_attaques_objets_->addWidget(conteneur_objets);
	lay_->addLayout(lay_attaques_objets_);
	QVBoxLayout *lay_combattants_=new QVBoxLayout();
	groupe_=new QGroupBox("Cibles");
	cibles_possibles=new QVBoxLayout();
	groupe_->setLayout(cibles_possibles);
	lay_combattants_->addWidget(groupe_);
	groupe_=new QGroupBox("Remplacants");
	remplacants_possibles=new QVBoxLayout();
	groupe_->setLayout(remplacants_possibles);
	lay_combattants_->addWidget(groupe_);
	lay_->addLayout(lay_combattants_);
	centre_->addLayout(lay_);
	setLayout(centre_);
}

void FicheActions::maj_fiche(const Combattant& _cbt,ElementsCombat& _elt,bool _apprende_attaque,bool _remplacer_fin_tour,Donnees* _d){
	/*if(mettre_a_jour_cr){
		autres_creatures=_elt.creatures_combats();
		mettre_a_jour_cr=false;
	}*/
	apprende_attaque=_apprende_attaque;
	if(apprende_attaque){
		attaquer->maj_actif(false);
		switcher->maj_actif(false);
		soin->maj_actif(false);
		ne_rien_faire->maj_actif(false);
	}else{
		attaquer->maj_actif(true);
		switcher->maj_actif(true);
		soin->maj_actif(true);
		ne_rien_faire->maj_actif(true);
	}
	remplacer_fin_tour=_remplacer_fin_tour;
	if(remplacer_fin_tour){
		attaquer->maj_actif(false);
		soin->maj_actif(false);
	}else{
		attaquer->maj_actif(true);
		soin->maj_actif(true);
	}
	combattant=_cbt;
	creature=_elt.creatures_combats().valeur(_cbt);
	QString attaque_;
	if(_apprende_attaque){
		FichePokemon *f_pk_=creature.fiche_pokemon_b(_d);
		attaque_=f_pk_->atts()[_elt.indice_pos_attaque()].second;
	}
	/*ordre_de_jeu=_elt.trier_ordre_non_joue(false,_d);
	ordre_de_jeu<<_elt.trier_ordre_non_joue(true,_d);*/
	foreach(QString a,liste_attaques.cles()){
		liste_attaques.valeur(a)->deleteLater();
		attaques_possibles->removeWidget(liste_attaques.valeur(a));
	}
	int nb_=attaques_possibles->count();
	/*for(int i=0;i<nb_;i++){
		attaques_possibles->removeItem(attaques_possibles->itemAt(0));
	}*/
	liste_attaques.tout_supprimer();
	typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
	QList<QPair<QString,QPair<uchar,uchar> > > attaques_=creature.attaques_pk();
	int i_att_=0;
	foreach(AttaquePP a,attaques_){
		EtiquetteAttaque *etiquette_=new EtiquetteAttaque(a.first+";"+QString::number(i_att_),a.first+" "+QString::number(a.second.first)+"/"+QString::number(a.second.second));
		etiquette_->maj_actif(apprende_attaque);
		connect(etiquette_,SIGNAL(clic(QString)),this,SLOT(maj_attaque_a_apprendre(QString)));
		attaques_possibles->addWidget(etiquette_);
		liste_attaques.ajouter_cle_valeur(a.first,etiquette_);
		i_att_++;
	}
	EtiquetteAttaque *etiquette_annuler_=new EtiquetteAttaque("","Ne pas apprendre "+attaque_);
	etiquette_annuler_->maj_actif(apprende_attaque);
	connect(etiquette_annuler_,SIGNAL(clic(QString)),this,SLOT(maj_attaque_a_apprendre(QString)));
	attaques_possibles->addWidget(etiquette_annuler_);
	attaques_possibles->parentWidget()->repaint();
	liste_attaques.ajouter_cle_valeur("",etiquette_annuler_);
	//std::cout<<"lay= "<<QString::number(attaques_act_possibles->count()).toStdString()<<"\n";
	//nb_=attaques_act_possibles->count();
	foreach(QString a,liste_act_attaques.cles()){
		liste_act_attaques.valeur(a)->deleteLater();
		attaques_act_possibles->removeWidget(liste_act_attaques.valeur(a));
	}
	liste_act_attaques.tout_supprimer();
	/*for(int i=0;i<nb_;i++){
		attaques_act_possibles->removeItem(attaques_act_possibles->itemAt(0));
	}*/
	//std::cout<<"lay= "<<QString::number(attaques_act_possibles->count()).toStdString()<<"\n";
	liste_act_attaques.tout_supprimer();
	foreach(QString a,creature.noms_attaques_act()){
		uchar pp_=creature.nb_pp(a);
		uchar pp_max_=creature.nb_pp_max(a);
		EtiquetteAttaque *etiquette_=new EtiquetteAttaque(a,a+" "+QString::number(pp_)+"/"+QString::number(pp_max_));
		etiquette_->maj_actif(creature.act_choisie()=="ATTAQUE");
		connect(etiquette_,SIGNAL(clic(QString)),this,SLOT(maj_attaque_a_lancer(QString)));
		attaques_act_possibles->addWidget(etiquette_);
		liste_act_attaques.ajouter_cle_valeur(a,etiquette_);
	}
	//attaques_act_possibles->parentWidget()->repaint();
	//noms_attaques_act()
	//nb_pp nb_pp_max
	nb_=objets_possibles->count();
	for(int i=0;i<nb_;i++){
		objets_possibles->itemAt(i)->widget()->deleteLater();;
	}
	for(int i=0;i<nb_;i++){
		objets_possibles->removeItem(objets_possibles->itemAt(0));
	}
	liste_objets.tout_supprimer();
	objets=creature.objets_pk();
	int nb_obj_=0;
	int h_=0;
	int l_=0;
	foreach(QString o,objets.cles()){
		uchar somme_=0;
		typedef QPair<uchar,Taux> Quantite;
		foreach(Quantite q,objets.valeur(o)){
			somme_+=q.first;
		}
		EtiquetteAttaque *etiquette_=new EtiquetteAttaque(o,o+" x"+QString::number(somme_));
		etiquette_->maj_actif(creature.act_choisie()=="SOIN"&&somme_>0);
		connect(etiquette_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
		h_=etiquette_->minimumHeight()+2;
		l_=Utilitaire::max_min<int>(etiquette_->minimumWidth(),l_).first;
		objets_possibles->addWidget(etiquette_);
		liste_objets.ajouter_cle_valeur(o,etiquette_);
		nb_obj_++;
	}
	objets_possibles->parentWidget()->setFixedHeight(nb_obj_*h_);
	objets_possibles->parentWidget()->setFixedWidth(l_);
	conteneur_objets->setFixedSize(200,200);
	foreach(Combattant c,liste_cibles.cles()){
		liste_cibles.valeur(c)->deleteLater();
		cibles_possibles->removeWidget(liste_cibles.valeur(c));
	}
	liste_cibles.tout_supprimer();
	foreach(Combattant c,liste_remplacants.cles()){
		liste_remplacants.valeur(c)->deleteLater();
		remplacants_possibles->removeWidget(liste_remplacants.valeur(c));
	}
	liste_remplacants.tout_supprimer();
	/*nb_=cibles_possibles->count();
	for(int i=0;i<nb_;i++){
		cibles_possibles->removeItem(cibles_possibles->itemAt(0));
	}
	nb_=remplacants_possibles->count();
	for(int i=0;i<nb_;i++){
		remplacants_possibles->removeItem(remplacants_possibles->itemAt(0));
	}*/
	foreach(Combattant c,_elt.creatures_combats().cles()){
		EtiquetteCombattant *etiquette_=new EtiquetteCombattant(c,_elt.creatures_combats().valeur(c),_elt.position(c).second,_d);
		etiquette_->maj_actif(false);
		connect(etiquette_,SIGNAL(clic(Combattant)),this,SLOT(maj_cible(Combattant)));
		cibles_possibles->addWidget(etiquette_);
		liste_cibles.ajouter_cle_valeur(c,etiquette_);
		if(c.equipe()==combattant.equipe()&&c.equipe()==_d->val_ut()){
			etiquette_=new EtiquetteCombattant(c,_elt.creatures_combats().valeur(c),_elt.position(c).second,_d);
			etiquette_->maj_actif(remplacer_fin_tour||creature.act_choisie()=="SWITCH");
			connect(etiquette_,SIGNAL(clic(Combattant)),this,SLOT(maj_remplacant(Combattant)));
			remplacants_possibles->addWidget(etiquette_);
			liste_remplacants.ajouter_cle_valeur(c,etiquette_);
		}
	}
}

void FicheActions::maj_fiche_fct_action(const QString& _action){
	foreach(QString a,liste_actions.cles()){
		liste_actions.valeur(a)->maj_choix(false);
	}
	liste_actions.valeur(_action)->maj_choix(true);
	foreach(QString a,liste_actions.cles()){
		liste_actions.valeur(a)->repaint();
	}
	if(_action=="ATTAQUE"){
		foreach(QString a,liste_act_attaques.cles()){
			liste_act_attaques.valeur(a)->maj_actif(true);
			liste_act_attaques.valeur(a)->repaint();
		}
		QStringList att_switch_;
		att_switch_<<"RELAIS";
		att_switch_<<"CHANGE_ECLAIR";
		att_switch_<<"DEMI_TOUR";
		att_switch_<<"VOEU_SOIN";
		att_switch_<<"DANSE_LUNE";
		if(att_switch_.contains(attaque_selectionnee)){
			foreach(Combattant c,liste_remplacants.cles()){
				liste_remplacants.valeur(c)->maj_actif(true);
				liste_remplacants.valeur(c)->repaint();
			}
		}else{
			foreach(Combattant c,liste_remplacants.cles()){
				liste_remplacants.valeur(c)->maj_actif(false);
				liste_remplacants.valeur(c)->repaint();
			}
		}
		foreach(QString o,liste_objets.cles()){
			liste_objets.valeur(o)->maj_actif(false);
			liste_objets.valeur(o)->repaint();
		}
		//
	}else if(_action=="SWITCH"){
		foreach(QString a,liste_act_attaques.cles()){
			liste_act_attaques.valeur(a)->maj_actif(false);
			liste_act_attaques.valeur(a)->repaint();
		}
		foreach(Combattant c,liste_remplacants.cles()){
			liste_remplacants.valeur(c)->maj_actif(true);
			liste_remplacants.valeur(c)->repaint();
		}
		foreach(Combattant c,liste_cibles.cles()){
			liste_cibles.valeur(c)->maj_actif(false);
			liste_cibles.valeur(c)->repaint();
		}
		foreach(QString o,liste_objets.cles()){
			liste_objets.valeur(o)->maj_actif(false);
			liste_objets.valeur(o)->repaint();
		}
		//
	}else if(_action=="SOIN"){
		foreach(QString a,liste_act_attaques.cles()){
			liste_act_attaques.valeur(a)->maj_actif(true);
			liste_act_attaques.valeur(a)->repaint();
		}
		foreach(QString o,liste_objets.cles()){
			liste_objets.valeur(o)->maj_actif(true);
			liste_objets.valeur(o)->repaint();
		}
		foreach(Combattant c,liste_cibles.cles()){
			liste_cibles.valeur(c)->maj_actif(false);
			liste_cibles.valeur(c)->repaint();
		}
		foreach(Combattant c,liste_remplacants.cles()){
			liste_remplacants.valeur(c)->maj_actif(false);
			liste_remplacants.valeur(c)->repaint();
		}
		//
	}else{
		foreach(QString a,liste_act_attaques.cles()){
			liste_act_attaques.valeur(a)->maj_actif(false);
			liste_act_attaques.valeur(a)->repaint();
		}
		foreach(QString o,liste_objets.cles()){
			liste_objets.valeur(o)->maj_actif(false);
			liste_objets.valeur(o)->repaint();
		}
		foreach(Combattant c,liste_cibles.cles()){
			liste_cibles.valeur(c)->maj_actif(false);
			liste_cibles.valeur(c)->repaint();
		}
		foreach(Combattant c,liste_remplacants.cles()){
			liste_remplacants.valeur(c)->maj_actif(false);
			liste_remplacants.valeur(c)->repaint();
		}
		//
	}
	emit clic_action(combattant,_action);
	//
}

void FicheActions::fin_combat_ou_ajout_cr(){
	mettre_a_jour_cr=true;
}

void FicheActions::maj_objet(const QString& _objet){
	objet_selectionnee=_objet;
	emit clic_objet(combattant,_objet);
}

void FicheActions::maj_attaque_a_lancer(const QString& _attaque){
	foreach(QString a,liste_act_attaques.cles()){
		liste_act_attaques.valeur(a)->maj_choix(false);
	}
	liste_act_attaques.valeur(_attaque)->maj_choix(true);
	foreach(QString a,liste_act_attaques.cles()){
		liste_act_attaques.valeur(a)->repaint();
	}
	attaque_selectionnee=_attaque;
	foreach(Combattant c,liste_cibles.cles()){
		liste_cibles.valeur(c)->maj_actif(true);
		liste_cibles.valeur(c)->repaint();
	}
	QStringList att_switch_;
	att_switch_<<"RELAIS";
	att_switch_<<"CHANGE_ECLAIR";
	att_switch_<<"DEMI_TOUR";
	att_switch_<<"VOEU_SOIN";
	att_switch_<<"DANSE_LUNE";
	if(att_switch_.contains(attaque_selectionnee)){
		foreach(Combattant c,liste_remplacants.cles()){
			liste_remplacants.valeur(c)->maj_actif(true);
			liste_remplacants.valeur(c)->repaint();
		}
	}else{
		foreach(Combattant c,liste_remplacants.cles()){
			liste_remplacants.valeur(c)->maj_actif(false);
			liste_remplacants.valeur(c)->repaint();
		}
	}
}

void FicheActions::maj_attaque_a_apprendre(const QString& _attaque){
	int indice_=-1;
	if(_attaque.contains(";")){
		indice_=_attaque.split(";")[1].toInt();
	}
	emit clic_attaque(indice_);
}

void FicheActions::maj_ordre_jeu(const QList<Combattant>& _ordre_jeu){
	ordre_de_jeu=_ordre_jeu;
}

void FicheActions::maj_cible(const Combattant& _cible){
	if(attaque_selectionnee!=""){
		foreach(Combattant c,liste_cibles.cles()){
			liste_cibles.valeur(c)->maj_choix(false);
		}
		liste_cibles.valeur(_cible)->maj_choix(true);
		foreach(Combattant c,liste_cibles.cles()){
			liste_cibles.valeur(c)->repaint();
		}
		emit clic_attaque(combattant,_cible,attaque_selectionnee);
	}
}

void FicheActions::maj_remplacant(const Combattant& _remplacant){
	foreach(Combattant c,liste_remplacants.cles()){
		liste_remplacants.valeur(c)->maj_choix(false);
	}
	liste_remplacants.valeur(_remplacant)->maj_choix(true);
	foreach(Combattant c,liste_remplacants.cles()){
		liste_remplacants.valeur(c)->repaint();
	}
	emit changer_remplacant(combattant,_remplacant);
}

