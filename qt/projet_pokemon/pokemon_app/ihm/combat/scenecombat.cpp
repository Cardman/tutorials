#include "ihm/combat/scenecombat.h"
#include "ihm/combat/etiquettes/imagecreaturecombat.h"
#include "ihm/combat/etiquettes/etiquettecreatcombat.h"
#include "ihm/combat/fiches/ficheelements.h"
#include "ihm/combat/fiches/fichecreature.h"
#include "ihm/combat/fiches/ficheactions.h"
#include "ihm/boutons/bouton.h"
#include "serialisable/combat/combattant.h"
#include "serialisable/combat/creaturecombat.h"
#include "serialisable/combat/elementscombat.h"
#include "serialisable/utilisateur/utilisateur.h"
#include "base_donnees/donnees.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/objets/ball.h"
#include <QScrollArea>
#include <QGroupBox>
#include <QGridLayout>
#include <QTextEdit>

SceneCombat::SceneCombat(Donnees* _d){
	QSplitter *combat_scene_=new QSplitter(Qt::Vertical);
	type_combat=new QLabel();
	combat_scene_->addWidget(type_combat);
	type_environnement=new QLabel();
	combat_scene_->addWidget(type_environnement);
	QLabel *etiq_=new QLabel();
	coeur_combat=new QGridLayout();
	etiq_->setLayout(coeur_combat);
	combat_scene_->addWidget(etiq_);
	commentaire_tour=new QTextEdit();
	combat_scene_->addWidget(commentaire_tour);
	QSplitter *actions_=new QSplitter();
	asc_actions_combat_sauvage=new QScrollArea();
	groupe_actions_combat_sauvage=new QGroupBox("Actions de capture ou de fuite");
	actions_combat_sauvage=new QVBoxLayout();
	groupe_actions_combat_sauvage->setLayout(actions_combat_sauvage);
	asc_actions_combat_sauvage->setWidget(groupe_actions_combat_sauvage);
	actions_->addWidget(asc_actions_combat_sauvage);
	QScrollArea *asc_=new QScrollArea();
	groupe_pokemon_utilisateur=new QGroupBox("Vos pokemons");
	pokemon_utilisateur=new QVBoxLayout();
	groupe_pokemon_utilisateur->setLayout(pokemon_utilisateur);
	asc_->setWidget(groupe_pokemon_utilisateur);
	actions_->addWidget(asc_);
	asc_=new QScrollArea();
	groupe_pokemon_adverse=new QGroupBox("Pokemons adverses");
	pokemon_adverse=new QVBoxLayout();
	groupe_pokemon_adverse->setLayout(pokemon_adverse);
	asc_->setWidget(groupe_pokemon_adverse);
	actions_->addWidget(asc_);
	asc_=new QScrollArea();
	QGroupBox *groupe_flux_=new QGroupBox();
	actions_flux=new QVBoxLayout();
	Bouton *bouton_=new Bouton();
	bouton_->maj_texte("CHARGER");
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	actions_flux->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("SAUVEGARDER");
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	actions_flux->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("VALIDER");
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	connect(bouton_,SIGNAL(clic()),this,SLOT(valider_actions()));
	actions_flux->addWidget(bouton_);
	groupe_flux_->setLayout(actions_flux);
	asc_->setWidget(groupe_flux_);
	actions_->addWidget(asc_);
	combat_scene_->addWidget(actions_);
	addWidget(combat_scene_);
	QSplitter *combat_infos_=new QSplitter(Qt::Vertical);
	conteneur_elements_combat=new QScrollArea();
	fiche_elements_combat=new FicheElements(_d);
	fiche_elements_combat->setMinimumSize(1000,1300);
	conteneur_elements_combat->setWidget(fiche_elements_combat);
	combat_infos_->addWidget(conteneur_elements_combat);
	conteneur_creature_combat=new QScrollArea();
	fiche_creature_combat=new FicheCreature(_d);
	//TODO connect(fiche_creature_combat,SIGNAL(clic_attaque(Combattant,Combattant,QString)),this,SLOT(maj_attaque_combat(Combattant,Combattant,QString)));
	fiche_creature_combat->setMinimumSize(1000,2500);
	conteneur_creature_combat->setWidget(fiche_creature_combat);
	combat_infos_->addWidget(conteneur_creature_combat);
	conteneur_actions_combat=new QScrollArea();
	actions_combat=new FicheActions();
	connect(actions_combat,SIGNAL(clic_attaque(int)),this,SLOT(maj_attaque(int)));
	connect(actions_combat,SIGNAL(clic_attaque(Combattant,Combattant,QString)),this,SLOT(maj_attaque_combat(Combattant,Combattant,QString)));
	connect(actions_combat,SIGNAL(clic_action(Combattant,QString)),this,SLOT(maj_action(Combattant,QString)));
	connect(actions_combat,SIGNAL(changer_remplacant(Combattant,Combattant)),this,SLOT(maj_remplacant(Combattant,Combattant)));
	//connect(actions_combat,SIGNAL(clic_attaque(Combattant,QString)),this,SLOT(maj_attaque(Combattant,QString)));
	actions_combat->setMinimumSize(1000,500);
	conteneur_actions_combat->setWidget(actions_combat);
	combat_infos_->addWidget(conteneur_actions_combat);
	conteneur_evo=new QScrollArea();
	evolution=new QGroupBox("Voulez-vous faire evoluer le pokemon?");
	QVBoxLayout *lay_=new QVBoxLayout();
	EtiquetteAttaque *etiquette_=new EtiquetteAttaque("OUI","OUI");
	connect(etiquette_,SIGNAL(clic(QString)),this,SLOT(faire_evoluer()));
	lay_->addWidget(etiquette_);
	etiquette_=new EtiquetteAttaque("NON","NON");
	connect(etiquette_,SIGNAL(clic(QString)),this,SLOT(ne_pas_faire_evoluer()));
	lay_->addWidget(etiquette_);
	evolution->setLayout(lay_);
	conteneur_evo->setWidget(evolution);
	combat_infos_->addWidget(conteneur_evo);
	addWidget(combat_infos_);
	QSplitter *splitter_err_res_=new QSplitter(Qt::Vertical);
	asc_erreur=new QScrollArea();
	erreur_utilisateur=new QTextEdit();
	asc_erreur->setWidget(erreur_utilisateur);
	splitter_err_res_->addWidget(asc_erreur);
	resultats=new QGroupBox("resultats");
	QVBoxLayout *lay_res_=new QVBoxLayout();
	resultats_bis=new QLabel();
	lay_res_->addWidget(resultats_bis);
	resultats->setLayout(lay_res_);
	splitter_err_res_->addWidget(resultats);
	addWidget(splitter_err_res_);
}

void SceneCombat::maj_erreur(const QString& _erreur){
	erreur_utilisateur->setPlainText(_erreur);
}

void SceneCombat::maj_commentaire(const QString& _com){
	commentaire_tour->setPlainText(_com);
}

void SceneCombat::ajout_commentaire(const QString& _com){
	commentaire_tour->setPlainText(commentaire_tour->toPlainText()+"\n"+_com);
}

void SceneCombat::maj_fiche(const Combattant& _combattant,ElementsCombat& _elt,Inventaire& _inventaire,const Difficulte& _diff,bool _apprende_attaque,bool _remplacer_fin_tour,Donnees* _d){
	CreatureCombat& cr_c_=_elt.creature_combat(_combattant);
	fiche_elements_combat->maj_fiche(_elt,_diff,_d);
	fiche_creature_combat->maj_fiche(_combattant,cr_c_,_elt,_d);
	actions_combat->maj_fiche(_combattant,_elt,_apprende_attaque,_remplacer_fin_tour,_d);
	foreach(Combattant c,creat_ut.cles()){
		creat_ut.valeur(c)->deleteLater();
		pokemon_utilisateur->removeWidget(creat_ut.valeur(c));
	}
	foreach(Combattant c,creat_adv.cles()){
		creat_adv.valeur(c)->deleteLater();
		pokemon_adverse->removeWidget(creat_adv.valeur(c));
	}
	int nb_=pokemon_utilisateur->count();
	/*for(int i=0;i<nb_;i++){
		pokemon_utilisateur->removeItem(pokemon_utilisateur->itemAt(0));
	}
	creat_ut.tout_supprimer();
	nb_=pokemon_adverse->count();
	for(int i=0;i<nb_;i++){
		pokemon_adverse->removeItem(pokemon_adverse->itemAt(0));
	}*/
	creat_ut.tout_supprimer();
	creat_adv.tout_supprimer();
	int nb_ut_=0;
	int h_=0;
	int l_=0;
	int nb_adv_=0;
	foreach(Combattant c,_elt.creatures_combats().cles()){
		EtiquetteCreatCombat *et_=new EtiquetteCreatCombat(c,_elt.creature_combat(c),_d);
		h_=et_->minimumHeight();
		l_=et_->minimumWidth();
		connect(et_,SIGNAL(clic(Combattant)),this,SLOT(maj_fiche(Combattant)));
		if(c.equipe()==_d->val_ut()){
			pokemon_utilisateur->addWidget(et_);
			creat_ut.ajouter_cle_valeur(c,et_);
			nb_ut_++;
		}else{
			pokemon_adverse->addWidget(et_);
			creat_adv.ajouter_cle_valeur(c,et_);
			nb_adv_++;
		}
	}
	groupe_pokemon_utilisateur->setMinimumSize(l_+100,(h_+50)*nb_ut_);
	groupe_pokemon_adverse->setMinimumSize(l_+100,(h_+50)*nb_adv_);
	if(_elt.type_cbt()=="SAUVAGE"){
		asc_actions_combat_sauvage->show();
		groupe_actions_combat_sauvage->setMinimumSize(500,400);
		nb_=actions_combat_sauvage->count();
		for(int i=0;i<nb_;i++){
			actions_combat_sauvage->itemAt(i)->widget()->deleteLater();;
		}
		for(int i=0;i<nb_;i++){
			actions_combat_sauvage->removeItem(actions_combat_sauvage->itemAt(0));
		}
		Combattant cbt_(_d->val_adv(),0);
		CreatureCombat& cr_a_=_elt.creature_combat(cbt_);
		foreach(QString b,_inventaire.balls_ut().cles()){
			Ball *ball_=qobject_cast<Ball*>(_d->val_objets().valeur(b));
			uchar eff_=_inventaire.balls_ut().valeur(b);
			//TODO etre plus generique
			EtiquetteAttaque *et_=new EtiquetteAttaque(b,b+" x"+QString::number(eff_)+" proba:"+_elt.calcul_coeff_capture(ball_,true,_elt.type_env()=="EAU",cr_a_,_d).evaluer(3));
			if(!eff_){
				et_->maj_actif(false);
			}
			connect(et_,SIGNAL(clic(QString)),this,SLOT(maj_ball(QString)));
			actions_combat_sauvage->addWidget(et_);
		}
		EtiquetteAttaque *et_=new EtiquetteAttaque("","Ne pas capturer");
		et_->maj_actif(_diff.r_autorise_ko_capture()&&_elt.creature_combat(Combattant(_d->val_adv(),0)).statut_pk()=="KO");
		connect(et_,SIGNAL(clic(QString)),this,SLOT(ne_pas_capturer()));
		actions_combat_sauvage->addWidget(et_);
		QString taux_;
		if(!_diff.r_autorise_ko_capture()||_elt.creature_combat(Combattant(_d->val_adv(),0)).statut_pk()!="KO"){
			taux_=(_elt.calcul_coeff_fuite(_d)/Taux(256)).evaluer(3);
		}
		et_=new EtiquetteAttaque("","Fuite proba:"+taux_);
		connect(et_,SIGNAL(clic(QString)),this,SLOT(tentative_fuite()));
		actions_combat_sauvage->addWidget(et_);
	}
	nb_=coeur_combat->count();
	for(int i=0;i<nb_;i++){
		coeur_combat->itemAt(i)->widget()->deleteLater();;
	}
	for(int i=0;i<nb_;i++){
		coeur_combat->removeItem(coeur_combat->itemAt(0));
	}
	fronts.tout_supprimer();
	//fronts
	//coeur_combat->parentWidget()->repaint();
	int multi_=_elt.mult_cbt();
	switch(multi_){
	case 1:{
		coeur_combat->parentWidget()->setMinimumSize(400,400);
		QList<Combattant> cbts_=_elt.combattants_a_position(QPair<uchar,uchar>(_d->val_adv(),0));
		if(!cbts_.isEmpty()){
			Combattant cbt_=cbts_[0];
			CreatureCombat& cr_a_2_=_elt.creature_combat(cbt_);
			EtiquetteCreatCombat *et_cr_=new EtiquetteCreatCombat(cbt_,cr_a_2_,_d);
			fronts.ajouter_cle_valeur(cbt_,et_cr_);
			coeur_combat->addWidget(et_cr_,0,0);
			coeur_combat->addWidget(new ImageCreatureCombat(cbt_,cr_a_2_,_d),0,1);
		}else{
			coeur_combat->addWidget(new EtiquetteCreatCombat(),0,0);
			coeur_combat->addWidget(new EtiquetteCreatCombat(),0,1);
		}
		cbts_=_elt.combattants_a_position(QPair<uchar,uchar>(_d->val_ut(),0));
		if(!cbts_.isEmpty()){
			Combattant cbt_=cbts_[0];
			CreatureCombat& cr_u_=_elt.creature_combat(cbt_);
			EtiquetteCreatCombat *et_cr_=new EtiquetteCreatCombat(cbt_,cr_u_,_d);
			coeur_combat->addWidget(et_cr_,1,1);
			fronts.ajouter_cle_valeur(cbt_,et_cr_);
			coeur_combat->addWidget(new ImageCreatureCombat(cbt_,cr_u_,_d),1,0);
		}else{
			coeur_combat->addWidget(new EtiquetteCreatCombat(),1,1);
			coeur_combat->addWidget(new EtiquetteCreatCombat(),1,0);
		}
		break;
	}
	case 2:{
		coeur_combat->parentWidget()->setMinimumSize(800,400);
		QList<Combattant> cbts_=_elt.combattants_a_position(QPair<uchar,uchar>(_d->val_adv(),0));
		if(!cbts_.isEmpty()){
			Combattant cbt_=cbts_[0];
			CreatureCombat& cr_a_2_=_elt.creature_combat(cbt_);
			EtiquetteCreatCombat *et_cr_=new EtiquetteCreatCombat(cbt_,cr_a_2_,_d);
			fronts.ajouter_cle_valeur(cbt_,et_cr_);
			coeur_combat->addWidget(et_cr_,0,0);
			coeur_combat->addWidget(new ImageCreatureCombat(cbt_,cr_a_2_,_d),0,2);
		}else{
			coeur_combat->addWidget(new EtiquetteCreatCombat(),0,0);
			coeur_combat->addWidget(new EtiquetteCreatCombat(),0,2);
		}
		cbts_=_elt.combattants_a_position(QPair<uchar,uchar>(_d->val_adv(),1));
		if(!cbts_.isEmpty()){
			Combattant cbt_=cbts_[0];
			CreatureCombat& cr_a_2_=_elt.creature_combat(cbt_);
			EtiquetteCreatCombat *et_cr_=new EtiquetteCreatCombat(cbt_,cr_a_2_,_d);
			fronts.ajouter_cle_valeur(cbt_,et_cr_);
			coeur_combat->addWidget(et_cr_,0,1);
			coeur_combat->addWidget(new ImageCreatureCombat(cbt_,cr_a_2_,_d),0,3);
		}else{
			coeur_combat->addWidget(new EtiquetteCreatCombat(),0,1);
			coeur_combat->addWidget(new EtiquetteCreatCombat(),0,3);
		}
		cbts_=_elt.combattants_a_position(QPair<uchar,uchar>(_d->val_ut(),0));
		if(!cbts_.isEmpty()){
			Combattant cbt_=cbts_[0];
			CreatureCombat& cr_u_=_elt.creature_combat(cbt_);
			EtiquetteCreatCombat *et_cr_=new EtiquetteCreatCombat(cbt_,cr_u_,_d);
			coeur_combat->addWidget(et_cr_,1,2);
			fronts.ajouter_cle_valeur(cbt_,et_cr_);
			coeur_combat->addWidget(new ImageCreatureCombat(cbt_,cr_u_,_d),1,0);
		}else{
			coeur_combat->addWidget(new EtiquetteCreatCombat(),1,2);
			coeur_combat->addWidget(new EtiquetteCreatCombat(),1,0);
		}
		cbts_=_elt.combattants_a_position(QPair<uchar,uchar>(_d->val_ut(),1));
		if(!cbts_.isEmpty()){
			Combattant cbt_=cbts_[0];
			CreatureCombat& cr_u_=_elt.creature_combat(cbt_);
			EtiquetteCreatCombat *et_cr_=new EtiquetteCreatCombat(cbt_,cr_u_,_d);
			coeur_combat->addWidget(et_cr_,1,3);
			fronts.ajouter_cle_valeur(cbt_,et_cr_);
			coeur_combat->addWidget(new ImageCreatureCombat(cbt_,cr_u_,_d),1,1);
		}else{
			coeur_combat->addWidget(new EtiquetteCreatCombat(),1,3);
			coeur_combat->addWidget(new EtiquetteCreatCombat(),1,1);
		}
		break;
	}
	case 3:break;
	default:break;
	}
}

void SceneCombat::maj_attaque_combat(const Combattant& _lanceur,const Combattant& _cible,ElementsCombat& _elt,const QString& _attaque,Donnees *_d){
	//const HashMap<uchar,Taux>&,const Taux&,const QString&
	CreatureCombat& cr_l_=_elt.creature_combat(_lanceur);
	CreatureCombat& cr_c_=_elt.creature_combat(_cible);
	if(_lanceur.equipe()==_d->val_ut()){
		cr_l_.att_choisie()=_attaque;
		cr_l_.cibles().clear();
		cr_l_.cibles()<<_elt.position(_cible);
	}
	QList<Combattant> cbts_=_elt.trier_ordre_non_joue(false,_d);
	cbts_<<_elt.trier_ordre_non_joue(true,_d);
	actions_combat->maj_ordre_jeu(cbts_);
	int ind_1_=cbts_.indexOf(_lanceur);
	int ind_2_=cbts_.indexOf(_cible);
	Taux ordre_(0);
	if(ind_2_<0){
		if(ind_1_>0){
			ordre_=-Taux(ind_1_);
		}
	}else if(ind_1_<0){
		ordre_=Taux(ind_2_);
	}else if(ind_2_>ind_1_){
		ordre_=Taux(ind_2_-ind_1_);
	}else{
		ordre_=-Taux(ind_1_-ind_2_);
	}
	FicheAttaque *f_att_=_d->val_attaques().valeur(_attaque);
	HashMap<uchar,Taux> degats_;
	QString texte_;
	QString ko_;
	if(f_att_->cat()!="AUTRE"&&_attaque!="EXCUSE"){
		MonteCarloNombre loi_repet_coups_=cr_l_.loi_repet_coups(_attaque,_d);
		HashMap<Combattant,bool> utilise_baie_;
		HashMap<Combattant,bool> cc_;
		foreach(Combattant c,_elt.creatures_combats().cles()){
			utilise_baie_.ajouter_cle_valeur(c,false);
			cc_.ajouter_cle_valeur(c,false);
		}
		QString type_att_=cr_l_.type_attaque_lanceur(_elt.climat_gl(),_attaque,_elt.effet_global("ZONE_MAGIQUE").second,_d);
		bool reussi_=_elt.condition_reussite(_lanceur,cr_l_,_cible,cr_c_,_attaque,type_att_,_d).first;
		if(reussi_){
			//const QString& _nom_att_l,FicheAttaque *_att_lanc,const Combattant& _cb,const CreatureCombat& _cible,uchar _statistique,bool& _ut_prec_att_suivante,bool& _lanceur_baie,Donnees *_d
			bool ut_prec_att_suivante_=false;
			bool ut_baie_=false;
			Taux prec_min_=_elt.calcul_precision(_lanceur,cr_l_,_attaque,f_att_,_cible,cr_c_,ElementsCombat::MINI,ut_prec_att_suivante_,ut_baie_,_d);
			Taux deg_=_elt.calcul_degats(loi_repet_coups_,_attaque,f_att_,type_att_,_lanceur,cr_l_,_cible,cr_c_,Taux(0),ElementsCombat::MINI,utilise_baie_,cc_,_d);
			degats_.ajouter_cle_valeur(ElementsCombat::MINI,deg_*prec_min_);
			Taux deg_min_=deg_;
			deg_=_elt.calcul_degats(loi_repet_coups_,_attaque,f_att_,type_att_,_lanceur,cr_l_,_cible,cr_c_,Taux(0),ElementsCombat::MAXI,utilise_baie_,cc_,_d);
			Taux prec_max_=_elt.calcul_precision(_lanceur,cr_l_,_attaque,f_att_,_cible,cr_c_,ElementsCombat::MAXI,ut_prec_att_suivante_,ut_baie_,_d);
			degats_.ajouter_cle_valeur(ElementsCombat::MAXI,deg_*prec_max_);
			Taux deg_max_=deg_;
			deg_=_elt.calcul_degats(loi_repet_coups_,_attaque,f_att_,type_att_,_lanceur,cr_l_,_cible,cr_c_,Taux(0),ElementsCombat::MOY,utilise_baie_,cc_,_d);
			Taux deg_moy_=deg_;
			Taux prec_moy_=_elt.calcul_precision(_lanceur,cr_l_,_attaque,f_att_,_cible,cr_c_,ElementsCombat::MOY,ut_prec_att_suivante_,ut_baie_,_d);
			degats_.ajouter_cle_valeur(ElementsCombat::MOY,deg_*prec_moy_);
			Taux prec_var_=_elt.calcul_precision(_lanceur,cr_l_,_attaque,f_att_,_cible,cr_c_,ElementsCombat::VAR,ut_prec_att_suivante_,ut_baie_,_d);
			deg_=_elt.calcul_degats(loi_repet_coups_,_attaque,f_att_,type_att_,_lanceur,cr_l_,_cible,cr_c_,Taux(0),ElementsCombat::VAR,utilise_baie_,cc_,_d);
			degats_.ajouter_cle_valeur(ElementsCombat::VAR,ElementsCombat::esperance_carree_variance_prod(QPair<Taux,Taux>(deg_moy_*deg_moy_,deg_),QPair<Taux,Taux>(prec_moy_*prec_moy_,prec_var_)).second);
			//min_degats->setText(_statistiques.valeur(ElementsCombat::MINI).evaluer(3));
			/*max_degats->setText(_statistiques.valeur(ElementsCombat::MAXI).evaluer(3));
			moy_degats->setText(_statistiques.valeur(ElementsCombat::MOY).evaluer(3));
			var_degats->setText(_statistiques.valeur(ElementsCombat::VAR).evaluer(3));*/
			if(deg_min_>=cr_c_.pv_restants_pk()){
				ko_="VRAI";
			}else if(deg_max_<cr_c_.pv_restants_pk()){
				ko_="FAUX";
			}else{
				ko_="PROBABLE";
			}
		}else{
			ko_="FAUX";
		}
	}else{
		ko_="PROBABLE";
	}
	texte_+="attaque: "+_attaque+"\n";
	if(degats_.total()>0){
		texte_+="min: "+degats_.valeur(ElementsCombat::MINI).evaluer(3)+"\n";
		texte_+="max: "+degats_.valeur(ElementsCombat::MAXI).evaluer(3)+"\n";
		texte_+="moy: "+degats_.valeur(ElementsCombat::MOY).evaluer(3)+"\n";
		texte_+="var: "+degats_.valeur(ElementsCombat::VAR).evaluer(3)+"\n";
	}else{
		texte_+="min: 0\n";
		texte_+="max: 0\n";
		texte_+="moy: 0\n";
		texte_+="var: 0\n";
	}
	texte_+="ordre: "+ordre_.chaine()+"\n";
	texte_+="ko: "+ko_;
	resultats_bis->setText(texte_);
}

void SceneCombat::raz_scene_combat(){
	int nb_=coeur_combat->count();
	for(int i=0;i<nb_;i++){
		coeur_combat->itemAt(i)->widget()->deleteLater();
	}
	for(int i=0;i<nb_;i++){
		coeur_combat->removeItem(coeur_combat->itemAt(0));
	}
	coeur_combat->parentWidget()->repaint();
	actions_combat->fin_combat_ou_ajout_cr();
}

void SceneCombat::maj_ball(const QString& _ball){
	emit clic_ball(_ball);
}

void SceneCombat::afficher_attaques_objets(bool _affiche){
	if(_affiche){
		conteneur_actions_combat->show();
	}else{
		conteneur_actions_combat->hide();
	}
}

void SceneCombat::afficher_actions_sauvage(bool _affiche){
	if(_affiche){
		asc_actions_combat_sauvage->show();
	}else{
		asc_actions_combat_sauvage->hide();
	}
}

void SceneCombat::valider_actions(){
	emit valider();
}

void SceneCombat::afficher_evolutions(bool _affiche){
	if(_affiche){
		conteneur_evo->show();
	}else{
		conteneur_evo->hide();
	}
}

void SceneCombat::maj_attaque_combat_sauvage(const QString& _attaque){
	emit clic_attaque_combat_sauvage(_attaque);
}

void SceneCombat::maj_action(const Combattant& _combattant,const QString& _action){
	emit clic_action(_combattant,_action);
}

void SceneCombat::maj_attaque_combat(const Combattant& _lanceur,const Combattant& _cible,const QString& _attaque){
	emit clic_attaque(_lanceur,_cible,_attaque);
}

void SceneCombat::maj_attaque(int _indice){
	emit clic_attaque(_indice);
}

/*void SceneCombat::maj_attaque(const Combattant& _lanceur,const QString& _attaque){
	emit clic_attaque_apprendre(_lanceur,_attaque);
}*/

void SceneCombat::maj_remplacant(const Combattant& _sortant,const Combattant& _entrant){
	emit clic_remplacant(_sortant,_entrant);
}

void SceneCombat::maj_fiche(const Combattant& _cbt){
	foreach(Combattant c,creat_ut.cles()){
		creat_ut.valeur(c)->maj_choix(false);
	}
	foreach(Combattant c,creat_adv.cles()){
		creat_adv.valeur(c)->maj_choix(false);
	}
	if(creat_ut.cles().contains(_cbt)){
		creat_ut.valeur(_cbt)->maj_choix(true);
	}else{
		creat_adv.valeur(_cbt)->maj_choix(true);
	}
	foreach(Combattant c,creat_ut.cles()){
		creat_ut.valeur(c)->repaint();
	}
	foreach(Combattant c,creat_adv.cles()){
		creat_adv.valeur(c)->repaint();
	}
	emit change_fiche_creature(_cbt);
}

void SceneCombat::maj_fiche(const Combattant& _cbt,ElementsCombat& _elt,bool _apprende_attaque,bool _remplacer_fin_tour,Donnees* _d){
	CreatureCombat& cr_c_=_elt.creature_combat(_cbt);
	fiche_creature_combat->maj_fiche(_cbt,cr_c_,_elt,_d);
	fiche_creature_combat->repaint();
	actions_combat->maj_fiche(_cbt,_elt,_apprende_attaque,_remplacer_fin_tour,_d);
	actions_combat->repaint();
}

void SceneCombat::ne_pas_capturer(){
	emit clic_ball("");
}

void SceneCombat::faire_evoluer(){
	emit evoluer();
}

void SceneCombat::ne_pas_faire_evoluer(){
	emit ne_pas_evoluer();
}

void SceneCombat::tentative_fuite(){
	emit clic_fuite();
}
