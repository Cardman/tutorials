#include "ihm/fenetre.h"
#include "ihm/boutons/bouton.h"
#include "ihm/boutons/clavier.h"
#include "ihm/boutons/choixheros.h"
#include "ihm/hors_combat/interactions.h"
#include "ihm/hors_combat/fiches/fichepartie.h"
#include "base_donnees/donnees.h"
#include "base_donnees/cartes/lieu.h"
#include "base_donnees/personnages/champion.h"
#include "base_donnees/personnages/dresseurligue.h"
#include "base_donnees/cartes/plateau.h"
#include "base_donnees/cartes/ligue.h"
#include "base_donnees/cartes/plateauligue.h"
#include "base_donnees/objets/ball.h"
#include "base_donnees/objets/baie.h"
#include "base_donnees/objets/soinpvstatut.h"
#include "base_donnees/objets/soinpv.h"
#include "base_donnees/objets/soinpp.h"
#include "base_donnees/initdonnees.h"
#include "serialisable/partie/partie.h"
#include "ihm/combat/scenecombat.h"
#include "ihm/hors_combat/scenehorscombat.h"
#include "ihm/combat/etiquettes/imagecreaturecombat.h"
#include "ihm/combat/etiquettes/etiquettecreatcombat.h"
#include "ihm/combat/fiches/ficheelements.h"
#include "ihm/combat/fiches/fichecreature.h"
#include "ihm/combat/fiches/ficheactions.h"
#include "ihm/hors_combat/gestionequipe.h"
#include "ihm/hors_combat/gestionboite.h"
#include "ihm/hors_combat/gestionfossile.h"
#include "ihm/hors_combat/gestioninventaire.h"
#include "ihm/hors_combat/gestionachatvente.h"
#include "ihm/hors_combat/gestionoption.h"
#include "ihm/hors_combat/gestionvol.h"
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QProgressBar>
#include <QScrollArea>
#include <QSplitter>
#include <iostream>

Fenetre::Fenetre(){
	donnees=NULL;
	initialisateur=NULL;
	bouton=NULL;
	centre=NULL;
	patience=NULL;
	lieu=NULL;
	ligue=NULL;
	plateau=NULL;
	plateau_ligue=NULL;
	scene_hc=NULL;
	interactions=NULL;
	avancement=NULL;
	menu=NULL;
	scene_c=NULL;
	asc_cl=NULL;
	clavier=NULL;
	choix_heros=NULL;
	gestion_i=NULL;
	gestion=NULL;
	gestion_b=NULL;
	gestion_a=NULL;
	gestion_f=NULL;
	asc_fiche_partie=NULL;
	fiche_partie=NULL;
	asc_gestion_o=NULL;
	gestion_o=NULL;
	asc_gestion_v=NULL;
	gestion_v=NULL;
	debut_jeu=true;
	en_deplacement=false;
	langue=0;
}

void Fenetre::init(){
	patience=new QLabel("Veuillez patienter");
	centre=new QSplitter();
	centre->addWidget(patience);
	setCentralWidget(centre);
	initialisateur=new InitDonnees();
	avancement=new QProgressBar(0);
	avancement->setWindowTitle("Chargement des donnees en cours");
	avancement->setRange(0,100);
	avancement->setValue(0);
	avancement->show();
	connect(initialisateur,SIGNAL(avancement(int)),avancement,SLOT(setValue(int)));
	connect(initialisateur,SIGNAL(finished()),this,SLOT(finir_initialisation()));
	initialisateur->start();
}

void Fenetre::finir_initialisation(){
	donnees=initialisateur->res();
	//langue=donnees->val_indice_francais();//TODO etre plus generique
	try{
		parametre.charger(donnees);
	}catch(...){
		parametre.init(donnees);
		parametre.sauvegarder(donnees);
	}
	langue=parametre.val_langue();//TODO etre plus generique
	//par=Partie(donnees);
	patience->hide();
	QSplitter *scene_=new QSplitter(Qt::Vertical);
	scene_hc=new SceneHorsCombat(donnees);
	scene_hc->hide();
	scene_->addWidget(scene_hc);
	interactions=new Interactions(donnees);
	connect(interactions,SIGNAL(clic(uchar,uchar,QString)),this,SLOT(interaction(uchar,uchar,QString)));
	interactions->hide();
	scene_->addWidget(interactions);
	centre->addWidget(scene_);
	scene_c=new SceneCombat(donnees);
	connect(scene_c,SIGNAL(clic_ball(QString)),this,SLOT(tentative_capture(QString)));
	connect(scene_c,SIGNAL(clic_action(Combattant,QString)),this,SLOT(maj_action(Combattant,QString)));
	connect(scene_c,SIGNAL(change_fiche_creature(Combattant)),this,SLOT(maj_fiche(Combattant)));
	connect(scene_c,SIGNAL(clic_fuite()),this,SLOT(tentative_fuite()));
	connect(scene_c,SIGNAL(clic_attaque(int)),this,SLOT(apprendre_attaque(int)));
	connect(scene_c,SIGNAL(clic_attaque(Combattant,Combattant,QString)),this,SLOT(maj_attaque_combat(Combattant,Combattant,QString)));
	connect(scene_c,SIGNAL(evoluer()),this,SLOT(traiter_evo()));
	connect(scene_c,SIGNAL(clic_remplacant(Combattant,Combattant)),this,SLOT(maj_remplacant(Combattant,Combattant)));
	connect(scene_c,SIGNAL(ne_pas_evoluer()),this,SLOT(traiter_non_evo()));//clic_remplacant
	connect(scene_c,SIGNAL(valider()),this,SLOT(tour_combat()));
	//scene_c->maj_fiche(cbt_,par.combat(),par.utilis().inv(),par.diff(),false,false,donnees);
	centre->addWidget(scene_c);
	scene_c->hide();
	choix_heros=new QLabel();
	QHBoxLayout *lay_heros_=new QHBoxLayout();
	int l_=0;
	foreach(QString s,donnees->val_debut_heros().cles()){
		ChoixHeros *choix_=new ChoixHeros(s,donnees);
		connect(choix_,SIGNAL(clic(QString)),this,SLOT(maj_sexe_heros(QString)));
		lay_heros_->addWidget(choix_);
		choix_h.ajouter_cle_valeur(s,choix_);
		l_+=choix_->width()+1;
	}
	choix_heros->setLayout(lay_heros_);
	choix_heros->setFixedWidth(l_);
	centre->addWidget(choix_heros);
	choix_heros->hide();
	//conteneur_principal->addWidget(scene_hc);
	menu=new QLabel();
	QVBoxLayout *layout_menu_=new QVBoxLayout();
	Bouton *bouton_=new Bouton();
	int largeur_=0;
	bouton_->maj_texte("NOUVEAU JEU");
	connect(bouton_,SIGNAL(clic()),this,SLOT(nouveau_jeu()));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	largeur_=Utilitaire::max_min<int>(largeur_,bouton_->minimumWidth()).first;
	layout_menu_->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("BASE_DE_DONNEES");
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	largeur_=Utilitaire::max_min<int>(largeur_,bouton_->minimumWidth()).first;
	layout_menu_->addWidget(bouton_);
	bouton_=new Bouton();
	connect(bouton_,SIGNAL(clic()),this,SLOT(gerer_inventaire()));
	bouton_->maj_texte("INVENTAIRE");
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	largeur_=Utilitaire::max_min<int>(largeur_,bouton_->minimumWidth()).first;
	layout_menu_->addWidget(bouton_);
	bouton_=new Bouton();
	connect(bouton_,SIGNAL(clic()),this,SLOT(gerer_equipe()));
	bouton_->maj_texte("EQUIPE");
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	largeur_=Utilitaire::max_min<int>(largeur_,bouton_->minimumWidth()).first;
	layout_menu_->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("SAUVEGARDER");
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	largeur_=Utilitaire::max_min<int>(largeur_,bouton_->minimumWidth()).first;
	layout_menu_->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("CHARGER");
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	largeur_=Utilitaire::max_min<int>(largeur_,bouton_->minimumWidth()).first;
	layout_menu_->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("OPTIONS");
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	largeur_=Utilitaire::max_min<int>(largeur_,bouton_->minimumWidth()).first;
	connect(bouton_,SIGNAL(clic()),this,SLOT(options()));
	layout_menu_->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("JOUEUR");
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,0,255));
	largeur_=Utilitaire::max_min<int>(largeur_,bouton_->minimumWidth()).first;
	connect(bouton_,SIGNAL(clic()),this,SLOT(joueur()));
	layout_menu_->addWidget(bouton_);
	menu->setLayout(layout_menu_);
	menu->setMinimumSize(largeur_,8*bouton_->height());
	centre->addWidget(menu);
	gestion_i=new GestionInventaire(donnees);
	connect(gestion_i,SIGNAL(gestion_finie()),this,SLOT(finir_gerer_inventaire()));
	connect(gestion_i,SIGNAL(attacher_obj()),this,SLOT(attacher()));
	connect(gestion_i,SIGNAL(utiliser(uchar)),this,SLOT(utiliser(uchar)));
	connect(gestion_i,SIGNAL(apprendre(uchar)),this,SLOT(apprendre(uchar)));
	centre->addWidget(gestion_i);
	gestion_i->hide();
	gestion_f=new GestionFossile(donnees);
	connect(gestion_f,SIGNAL(tentative_vivre_fossile(QString)),this,SLOT(vivre_fossile(QString)));
	centre->addWidget(gestion_f);
	gestion_f->hide();
	gestion=new GestionEquipe();
	connect(gestion,SIGNAL(evoluer(QString,uchar)),this,SLOT(evoluer(QString,uchar)));
	connect(gestion,SIGNAL(attacher(uchar)),this,SLOT(attacher(uchar)));
	connect(gestion,SIGNAL(boost(uchar)),this,SLOT(boost(uchar)));
	connect(gestion,SIGNAL(soin(uchar)),this,SLOT(soin(uchar)));
	connect(gestion,SIGNAL(vol()),this,SLOT(voler()));
	connect(gestion,SIGNAL(rangement_objet(uchar)),this,SLOT(retrait_objet(uchar)));
	connect(gestion,SIGNAL(echange_objets(QPair<int,int>)),this,SLOT(maj_objet(QPair<int,int>)));
	connect(gestion,SIGNAL(echange_place(QPair<int,int>)),this,SLOT(maj_position(QPair<int,int>)));
	connect(gestion,SIGNAL(pension(QPair<int,int>)),this,SLOT(maj_pension(QPair<int,int>)));
	connect(gestion,SIGNAL(fin_gestion()),this,SLOT(finir_gestion_equipe()));
	connect(gestion,SIGNAL(move_tutors(QString,uchar,int)),this,SLOT(tentative_apprendre_move_tutor(QString,uchar,int)));
	connect(gestion,SIGNAL(appris_move_tutors(QString,uchar,int)),this,SLOT(apprendre_move_tutor(QString,uchar,int)));
	centre->addWidget(gestion);
	gestion->hide();
	gestion_b=new GestionBoite(donnees);
	connect(gestion_b,SIGNAL(echange_pokemon(QPair<int,int>,QPair<int,int>)),this,SLOT(echanger_pokemons_boite(QPair<int,int>,QPair<int,int>)));
	connect(gestion_b,SIGNAL(ranger_objets(QPair<int,int>)),this,SLOT(ranger_objets_boite(QPair<int,int>)));
	connect(gestion_b,SIGNAL(echange_objets(QPair<int,int>,QPair<int,int>)),this,SLOT(echanger_objets_boite(QPair<int,int>,QPair<int,int>)));
	connect(gestion_b,SIGNAL(depos(uchar,QPair<uchar,uchar>)),this,SLOT(deposer_pokemon(uchar,QPair<uchar,uchar>)));
	connect(gestion_b,SIGNAL(retrait(QPair<uchar,uchar>)),this,SLOT(retrait_pokemon(QPair<uchar,uchar>)));
	connect(gestion_b,SIGNAL(relacher(QPair<uchar,uchar>)),this,SLOT(relacher_pokemon(QPair<uchar,uchar>)));
	connect(gestion_b,SIGNAL(gestion_finie()),this,SLOT(finir_gestion_boite()));
	centre->addWidget(gestion_b);
	gestion_b->hide();
	gestion_a=new GestionAchatVente(langue,donnees);
	connect(gestion_a,SIGNAL(erreur_achat()),this,SLOT(erreur_achat()));
	connect(gestion_a,SIGNAL(achat()),this,SLOT(achat()));
	connect(gestion_a,SIGNAL(vente()),this,SLOT(vente()));
	connect(gestion_a,SIGNAL(erreur_vente()),this,SLOT(erreur_vente()));
	connect(gestion_a,SIGNAL(fin_gestion()),this,SLOT(finir_gestion_achat_vente()));
	centre->addWidget(gestion_a);
	asc_gestion_o=new QScrollArea();
	asc_gestion_o->hide();
	gestion_o=new GestionOption(donnees);
	connect(gestion_o,SIGNAL(maj_diff(Difficulte)),this,SLOT(maj_diff(Difficulte)));
	asc_gestion_o->setWidget(gestion_o);
	asc_gestion_o->setWidgetResizable(true);
	centre->addWidget(asc_gestion_o);
	asc_gestion_v=new QScrollArea();
	asc_gestion_v->hide();
	gestion_v=new GestionVol(donnees);
	connect(gestion_v,SIGNAL(clic(Coordonnees)),this,SLOT(maj_coords_vol(Coordonnees)));
	asc_gestion_v->setWidget(gestion_v);
	centre->addWidget(asc_gestion_v);
	asc_fiche_partie=new QScrollArea();
	fiche_partie=new FichePartie(donnees);
	asc_fiche_partie->setWidget(fiche_partie);
	centre->addWidget(asc_fiche_partie);
	asc_fiche_partie->hide();
	asc_fiche_partie->setWidgetResizable(true);
	gestion_a->hide();
	asc_cl=new QScrollArea();
	asc_cl->setWidgetResizable(true);
	clavier=new Clavier();
	connect(clavier,SIGNAL(valider(QString)),this,SLOT(maj_texte_clavier(QString)));
	asc_cl->setWidget(clavier);
	centre->addWidget(asc_cl);
	asc_cl->hide();
	delete initialisateur;
	initialisateur=NULL;
	avancement->hide();
	avancement->close();
	delete avancement;
	avancement=NULL;
	//QMessageBox::information(this,"succes","chargement fini");
}

void Fenetre::maj_texte_clavier(const QString& _texte){
	ElementsCombat& elt_=par.combat();
	if(elt_.type_cbt()!=""){
		//Surnom en fin de combat
		int ind_=elt_.indice_pos_boite();
		int nb_boites_=donnees->constante_numerique("NB_BOITES");
		if(_texte!=""){
			if(ind_>=0&&ind_<nb_boites_){
				par.utilis().boite(ind_).last().second.pseudo_pk()=_texte;
			}else{
				par.utilis().equipe_ut().last().second.pseudo_pk()=_texte;
			}
			//
		}
		CreatureCombat& cr_adv_=elt_.creature_combat(Combattant(donnees->val_adv(),0));
		bool nouveau_=false;
		if(ind_>=0&&ind_<nb_boites_){
			par.utilis().boite(ind_).last().second.ball_capt()=cr_adv_.ball_capt();
			nouveau_=true;
		}else{
			par.utilis().equipe_ut().last().second.ball_capt()=cr_adv_.ball_capt();
			nouveau_=true;
		}
		if(nouveau_&&cr_adv_.ball_capt()=="COPAIN_BALL"){
			if(ind_>=0&&ind_<nb_boites_){
				par.utilis().boite(ind_).last().second.affecter_bonheur_pk(donnees->constante_numerique("COPAIN_BALL_BONHEUR"));
			}else{
				par.utilis().equipe_ut().last().second.affecter_bonheur_pk(donnees->constante_numerique("COPAIN_BALL_BONHEUR"));
			}
		}
		elt_.fin_cbt();//TODO clavier virtuel
		clavier->vider_champ();
		asc_cl->hide();
		scene_c->raz_scene_combat();
		scene_c->hide();
		menu->show();
		if(elt_.maj_coords_leg()!=Coordonnees()){
			par.prendre_pokemon(elt_.maj_coords_leg());
			scene_hc->maj_tuiles(par,par.coords_util(),par.present_ligue(),donnees);
			scene_hc->repaint();
			interactions->raz_interaction();
		}
		interactions->show();
		scene_hc->show();
	}else if(debut_jeu){
		if(_texte!=""&&sexe_heros!=""){
			par.utilis()=Utilisateur(_texte,sexe_heros,donnees);
			par.utilis().inv().balls_ut().valeur("SUPER_BALL")+=2;
			par.utilis().inv().ct_ut().valeur(10)++;
			par.utilis().inv().pierres_evo_ut().valeur("PIERRE_FOUDRE")++;
			par.utilis().equipe_ut()[0].second.tmp_exp_gagne_der_niv(donnees);
			//par.utilis().inv().cs_ut().valeur(2)=true;
			//par.utilis().oeufs()<<QPair<uchar,OeufPokemon>(1,OeufPokemon("PIKACHU",donnees));
			//par.utilis().activer_repousse("REPOUSSE_MAX",donnees);
			debut_jeu=false;
			scene_hc->maj_tuiles(par,donnees->val_coords_depart(),par.present_ligue(),donnees);
			scene_hc->maj_orientation(par.orientation());
			scene_hc->repaint();
			scene_hc->show();
			interactions->show();
			menu->show();
			choix_heros->hide();
			clavier->vider_champ();
			asc_cl->hide();
		}
	}else if(gestion->gestion()==GestionEquipe::ORDRE&&gestion->pokemon_fiche()!=-1&&!gestion->echange_en_cours()){
		if(_texte!=""){
			par.utilis().equipe_ut()[gestion->pokemon_fiche()].second.pseudo_pk()=_texte;
		}else{
			PokemonUtilisateur& _pk=par.utilis().equipe_ut()[gestion->pokemon_fiche()].second;
			_pk.pseudo_pk()=_pk.n_pk();
		}
		clavier->vider_champ();
	}
	//boites, achat / vente
}

void Fenetre::maj_sexe_heros(const QString& _sexe){
	foreach(QString s,choix_h.cles()){
		choix_h.valeur(s)->maj_choix(false);
	}
	choix_h.valeur(_sexe)->maj_choix(true);
	foreach(QString s,choix_h.cles()){
		choix_h.valeur(s)->repaint();
	}
	sexe_heros=_sexe;
}

void Fenetre::nouveau_jeu(){
	par=Partie(donnees);
	choix_heros->show();
	asc_cl->show();
	menu->hide();
	scene_hc->hide();
	interactions->hide();
	//
}

void Fenetre::maj_attaque_combat_sauvage(const QString&){
	//
}

void Fenetre::maj_action(const Combattant& _cbt,const QString& _action){
	ElementsCombat& elt_=par.combat();
	CreatureCombat& cr_c_=elt_.creature_combat(_cbt);
	if(_cbt.equipe()==donnees->val_ut()){
		cr_c_.act_choisie()=_action;
		if(_action==""){
			cr_c_.remplacant()=Combattant();
		}
	}
	scene_c->maj_fiche(_cbt,elt_,elt_.situation_cbt()==ElementsCombat::APPRENDRE_ATT,elt_.situation_cbt()==ElementsCombat::SWITCH_PROPOSE,donnees);
	//fiche_creature_combat->maj_fiche(_cbt,cr_c_,par.combat(),donnees);
}

void Fenetre::maj_fiche(const Combattant& _combattant){
	scene_c->maj_fiche(_combattant,par.combat(),false,false,donnees);
}

void Fenetre::maj_attaque_combat(const Combattant& _lanceur,const Combattant& _cible,const QString& _attaque){
	scene_c->maj_attaque_combat(_lanceur,_cible,par.combat(),_attaque,donnees);
	//const HashMap<uchar,Taux>&,const Taux&,const QString&
	//
	//
}

void Fenetre::maj_remplacant(const Combattant& _sortant,const Combattant& _remplacant){
	if(_sortant.equipe()==donnees->val_ut()){
		CreatureCombat& cr_c_=par.combat().creature_combat(_sortant);
		cr_c_.remplacant()=_remplacant;
		cr_c_.att_choisie()="SWITCH";
	}
}

void Fenetre::tentative_fuite(){
	ElementsCombat& elt_=par.combat();
	uchar res_=elt_.tentative_fuite(par.utilis(),par.ligues_battues(),par.nb_dresseur_ligue_battus(),par.r_dresseurs_battus(),donnees);
	scene_c->maj_commentaire(elt_.maj_commentaire_tour());
	redessiner_ihm(res_);
}

void Fenetre::tentative_capture(const QString& _ball){
	ElementsCombat& elt_=par.combat();
	if(_ball==""){
		elt_.fin_cbt();
		scene_c->raz_scene_combat();
		scene_c->hide();
		menu->show();
		scene_hc->show();
		interactions->show();
		return;
	}
	Ball *ball_=qobject_cast<Ball*>(donnees->val_objets().valeur(_ball));
	uchar res_=elt_.tentative_capture(_ball,ball_,par.utilis(),par.ligues_battues(),par.nb_dresseur_ligue_battus(),par.r_dresseurs_battus(),donnees);
	scene_c->maj_commentaire(elt_.maj_commentaire_tour());
	redessiner_ihm(res_);
}

void Fenetre::tour_combat(){
	ElementsCombat& elt_=par.combat();
	if(elt_.situation_cbt()==ElementsCombat::SWITCH_PROPOSE){
		QString err_;
		QList<uchar> rempl_;
		foreach(Combattant f,elt_.fronts()){
			if(f.equipe()==donnees->val_ut()){
				CreatureCombat& cr_c_=elt_.creature_combat(f);
				if(cr_c_.act_choisie()=="SWITCH"){
					if(cr_c_.remplacant()==Combattant()){
						err_+="Il manque un remplacant pour "+cr_c_.nom_pk_act()+"!\n";
					}else{
						rempl_<<cr_c_.remplacant().position();
					}
				}
			}
		}
		foreach(Combattant c,elt_.creatures_combats().cles()){
			if(c.equipe()==donnees->val_ut()&&!elt_.fronts().contains(c)){
				CreatureCombat& cr_c_=elt_.creature_combat(c);
				if(cr_c_.act_choisie()=="SWITCH"){
					err_+=cr_c_.nom_pk_act()+" n'est pas au combat!\n";
				}
			}
		}
		Utilitaire::trier<uchar>(rempl_);
		for(int i=rempl_.size()-1;i>0;i--){
			if(rempl_[i]==rempl_[i-1]){
				err_+="Meme remplacant pour deux pokemons differents\n";
			}
		}
		if(err_==""){
			uchar res_=elt_.traiter_remplacement(par.utilis(),par.ligues_battues(),par.nb_dresseur_ligue_battus(),par.r_dresseurs_battus(),donnees);
			Combattant cbt_;
			foreach(Combattant c,elt_.fronts()){
				if(c.equipe()==donnees->val_ut()){
					cbt_=c;
					break;
				}
			}
			//scene_c->maj_fiche(cbt_,par.combat(),par.utilis().inv(),par.diff(),false,false,donnees);
			//scene_c->afficher_evolutions(false);
			scene_c->maj_commentaire(elt_.maj_commentaire_tour());
			redessiner_ihm(res_);
		}else{
			scene_c->maj_erreur(err_);
		}
		return;
	}
	QPair<QString,HashMap<Combattant,QPair<QPair<QString,QString>,Combattant> > > res_=elt_.jouable_utilisateur(donnees);
	if(res_.first==""){
		uchar res_2_=elt_.tour_combat(par.utilis(),par.ligues_battues(),par.nb_dresseur_ligue_battus(),par.r_dresseurs_battus(),donnees);
		scene_c->maj_commentaire(elt_.maj_commentaire_tour());
		redessiner_ihm(res_2_);
		//Jeu
	}else{
		scene_c->maj_erreur(res_.first);
	}
}

void Fenetre::apprendre_attaque(int _indice){
	ElementsCombat& elt_=par.combat();
	FichePokemon *f_pk_=donnees->val_pokedex().valeur(elt_.creature_combat(Combattant(donnees->val_ut(),elt_.indice_pos_pk())).nom_pk());
	QString attaque_;
	if(_indice>=0){
		attaque_=f_pk_->atts()[elt_.indice_pos_attaque()].second;
	}
	uchar res_=elt_.traiter_apprentissage_attaque(ElementsCombat::APPRENDRE_ATT,attaque_,_indice,par.utilis(),par.ligues_battues(),par.nb_dresseur_ligue_battus(),par.r_dresseurs_battus(),donnees);
	redessiner_ihm(res_);
}

void Fenetre::traiter_evo(){
	ElementsCombat& elt_=par.combat();
	uchar res_=elt_.traiter_apprentissage_attaque(ElementsCombat::EVOLUTION,"OUI",0,par.utilis(),par.ligues_battues(),par.nb_dresseur_ligue_battus(),par.r_dresseurs_battus(),donnees);
	redessiner_ihm(res_);
}

void Fenetre::traiter_non_evo(){
	ElementsCombat& elt_=par.combat();
	uchar res_=elt_.traiter_apprentissage_attaque(ElementsCombat::EVOLUTION,"",0,par.utilis(),par.ligues_battues(),par.nb_dresseur_ligue_battus(),par.r_dresseurs_battus(),donnees);
	redessiner_ihm(res_);
}

void Fenetre::maj_position(const QPair<int,int>& _pos){
	par.utilis().echanger_place(_pos.first,_pos.second);
	gestion->maj_fiche(par.utilis(),langue,GestionEquipe::ORDRE,donnees);
}

void Fenetre::retrait_objet(uchar _pos){
	QString obj_;
	par.utilis().retirer_objet(_pos,true,obj_,donnees);
	if(obj_!=""){
		QString commentaire_="L'objet "+obj_+" est range dans l'inventaire";
		interactions->maj_commentaire(commentaire_);
	}
}

void Fenetre::maj_objet(const QPair<int,int>& _pos){
	par.utilis().echanger_objet_equipe(_pos.first,_pos.second,donnees);
	gestion->maj_fiche(par.utilis(),langue,GestionEquipe::ORDRE,donnees);
}

void Fenetre::tentative_apprendre_move_tutor(const QString& _attaque,uchar _pos,int _indice){
	if(_indice<0){
		interactions->maj_commentaire("Vous allez ecraser une attaque par "+_attaque+"\n");
	}else{
		QString att_;
		bool appr_=false;
		if(gestion->gestion()!=GestionEquipe::APPRENDRE_CT){
			par.utilis().apprendre_attaque(_pos,_indice,_attaque,att_,donnees);
			appr_=true;
		}else{
			if(par.utilis().inv().ct_ut().valeur(donnees->val_ct().cles(_attaque)[0])>0){
				par.utilis().apprendre_attaque(_pos,_indice,_attaque,att_,donnees);
				appr_=true;
				par.utilis().inv().ct_ut().valeur(donnees->val_ct().cles(_attaque)[0])--;
			}
		}
		if(appr_){
			interactions->maj_commentaire("L'attaque "+_attaque+" est apprise!\n");
		}
		if(gestion->gestion()!=GestionEquipe::MOVE_TUTORS){
			gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
		}
	}
}

void Fenetre::apprendre_move_tutor(const QString& _attaque,uchar _pos,int _indice){
	if(_indice>-1){
		QString att_;
		if(gestion->gestion()==GestionEquipe::BAIE){
			QPair<QString,int> obj_=gestion_i->obj_select();
			uchar pp_=par.utilis().soin_baie_pp(_pos,_attaque,obj_.first,donnees);
			if(pp_>0){
				interactions->maj_commentaire("L'attaque "+_attaque+" est soignee de "+QString::number(pp_)+"\n");
			}
			gestion_i->maj_fiche(par.utilis().inv(),langue,GestionInventaire::BAIE);
		}else if(gestion->gestion()==GestionEquipe::SOIN){
			QPair<QString,int> obj_=gestion_i->obj_select();
			par.utilis().soin_pp_pk(_pos,obj_.first,donnees,_attaque);
			gestion_i->maj_fiche(par.utilis().inv(),langue,GestionInventaire::SOIN);
		}else if(gestion->gestion()==GestionEquipe::BOOST){
			QPair<QString,int> obj_=gestion_i->obj_select();
			par.utilis().gain_pp_max(_pos,_attaque,obj_.first,donnees);
			gestion_i->maj_fiche(par.utilis().inv(),langue,GestionInventaire::BOOST);
		}else if(gestion->gestion()!=GestionEquipe::APPRENDRE_CT){
			par.utilis().apprendre_attaque(_pos,_indice,_attaque,att_,donnees);
			if(gestion->gestion()==GestionEquipe::APPRENDRE_CS){
				gestion_i->maj_fiche(par.utilis().inv(),langue,GestionInventaire::CS);
			}
		}else{
			if(par.utilis().inv().ct_ut().valeur(donnees->val_ct().cles(_attaque)[0])>0){
				par.utilis().apprendre_attaque(_pos,_indice,_attaque,att_,donnees);
				par.utilis().inv().ct_ut().valeur(donnees->val_ct().cles(_attaque)[0])--;
				gestion_i->maj_fiche(par.utilis().inv(),langue,GestionInventaire::CT);
			}
		}
		if(att_!=""){
			interactions->maj_commentaire("Vous avez ecrase l'attaque "+att_+" par "+_attaque+"\n");
		}
		if(gestion->gestion()!=GestionEquipe::MOVE_TUTORS){
			gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
		}
	}else{
		interactions->maj_commentaire("Vous avez n'avez pas selectionne d'attaque pour ecraser l'attaque "+_attaque+"\n");
	}
}


void Fenetre::maj_pension(const QPair<int,int>& _pos){
	Utilisateur& ut_=par.utilis();
	if(ut_.equipe_ut().size()>=3){
		QString err_=par.compatibles_pensions(_pos.first,_pos.second,donnees);
		if(err_==""){
			Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
			par.deposer_pokemons_pension(_pos.first,_pos.second,voisin_);
			finir_gestion_equipe();
			//gestion->maj_fiche(par.utilis(),langue,GestionEquipe::PENSION,donnees);

		}else{
			interactions->maj_commentaire(err_);
		}
		//QString Partie::compatibles_pensions(uchar pos_1_,uchar pos_2_,Donnees *_d)const
	}else{
		interactions->maj_commentaire("Manque de pokemon dans l'equipe il en faut au moins 3");
	}
	//
}

void Fenetre::gerer_equipe(){
	if(debut_jeu){
		return;
	}
	gestion->maj_fiche(par.utilis(),langue,GestionEquipe::ORDRE,donnees);
	gestion->show();
	asc_cl->show();
}

void Fenetre::voler(){
	if(!donnees->existe_cs(par,"VOL")){
		interactions->maj_commentaire("Il vous manque le badge");
		return;
	}
	QStringList actions_;
	actions_<<"Voler";
	actions_<<"Annuler vol";
	actions_<<"Retour a la gestion d'equipe";
	actions_<<"Fin de gestion";
	interactions->maj_interaction(Partie::VOL,actions_);
	gestion->hide();
	asc_gestion_v->show();
	asc_cl->hide();
}

void Fenetre::gerer_inventaire(){
	if(debut_jeu){
		return;
	}
	gestion_i->maj_fiche(par.utilis().inv(),langue);
	gestion_i->show();
	gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
	gestion->show();
}

void Fenetre::attacher(){
	gestion->maj_fiche(par.utilis(),langue,GestionEquipe::ATTACHER_OBJET,donnees);
}

void Fenetre::attacher(uchar _pos){
	QPair<QString,int> obj_=gestion_i->obj_select();
	if(par.utilis().inv().quantite(obj_.first)>0){
		par.utilis().inv().consommer(obj_.first,obj_.second);
		QString obj_ret_;
		par.utilis().retirer_objet(_pos,true,obj_ret_,donnees);
		par.utilis().attacher_objet(_pos,obj_.first);
		gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
	}
}

void Fenetre::utiliser(uchar _type){
	if(_type==GestionInventaire::REPOUSSE){
		if(par.utilis().inv().repousse_ut().valeur(gestion_i->obj_select().first)>0&&!par.utilis().repous_act()){
			par.utilis().inv().repousse_ut().valeur(gestion_i->obj_select().first)--;
			par.utilis().activer_repousse(gestion_i->obj_select().first,donnees);
			interactions->maj_commentaire("Utilisation de "+gestion_i->obj_select().first);
		}
	}else if(_type==GestionInventaire::PIERRE_EVO){
		gestion->maj_fiche(par.utilis(),langue,GestionEquipe::PIERRE_EVO,donnees,gestion_i->obj_select().first);
	}else if(_type==GestionInventaire::BOOST){
		gestion->maj_fiche(par.utilis(),langue,GestionEquipe::BOOST,donnees,gestion_i->obj_select().first);
	}else if(_type==GestionInventaire::SOIN){
		Soin *soin_=qobject_cast<Soin*>(donnees->val_objets().valeur(gestion_i->obj_select().first));
		if(soin_->soin_eq()){
			if(par.utilis().inv().objets_soins_ut().valeur(gestion_i->obj_select().first)[gestion_i->obj_select().second].first>0){
				par.utilis().inv().objets_soins_ut().valeur(gestion_i->obj_select().first)[gestion_i->obj_select().second].first--;
				par.utilis().soin_equipe_ct_pk(donnees);
			}
		}else{
			gestion->maj_fiche(par.utilis(),langue,GestionEquipe::SOIN,donnees,gestion_i->obj_select().first);
		}
	}else if(_type==GestionInventaire::BAIE){
		Baie *baie_=qobject_cast<Baie*>(donnees->val_objets().valeur(gestion_i->obj_select().first));
		bool gerer_=false;
		if(!baie_->s_pv().first.estNul()){
			gerer_=true;
		}else if(!baie_->s_tx_pv().first.estNul()){
			gerer_=true;
		}else if(baie_->s_pp().first!=""){
			gerer_=true;
		}else if(!baie_->gain_pv_sup_ef().estNul()){
			gerer_=true;
		}else{
			foreach(QString s,baie_->s_statut()){
				if(Utilitaire::traduisible(donnees->val_noms_statuts(),s)){
					gerer_=true;
					break;
				}
			}
		}
		if(gerer_){
			gestion->maj_fiche(par.utilis(),langue,GestionEquipe::BAIE,donnees);
		}
		//
	}
	//...
}

void Fenetre::boost(uchar _pos){
	QPair<QString,int> obj_=gestion_i->obj_select();
	if(par.utilis().inv().quantite(obj_.first)>0){
		par.utilis().boost_statistique(_pos,obj_.first,donnees);
	}
}

void Fenetre::soin(uchar _pos){
	QPair<QString,int> obj_=gestion_i->obj_select();
	if(par.utilis().inv().objets_soins_ut().valeur(obj_.first)[obj_.second].first>0){
		SoinStatut *soin_statut_=qobject_cast<SoinStatut*>(donnees->val_objets().valeur(obj_.first));
		if(soin_statut_){
			par.utilis().soin_statut(_pos,obj_.first,donnees);
		}else{
			SoinPV *soin_pv_=qobject_cast<SoinPV*>(donnees->val_objets().valeur(obj_.first));
			if(soin_pv_){
				par.utilis().soin_pv_pk(_pos,obj_.first,obj_.second,donnees);
			}else{
				par.utilis().soin_pp_pk(_pos,obj_.first,donnees,"");
			}
		}
		gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
	}
}

void Fenetre::soin_baie(uchar _pos){
	QPair<QString,int> obj_=gestion_i->obj_select();
	if(par.utilis().inv().quantite(gestion_i->obj_select().first)>0){
		Baie *baie_=qobject_cast<Baie*>(donnees->val_objets().valeur(obj_.first));
		if(baie_->s_pp().first==""){
			Taux pv_=par.utilis().soin_baie(_pos,obj_.first,donnees);
			if(!pv_.estNul()){
				interactions->maj_commentaire(pv_.evaluer(3)+" pv soignes");
			}
			gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
		}
	}
}

void Fenetre::apprendre(uchar _type){
	if(_type==GestionInventaire::CT){
		gestion->maj_fiche(par.utilis(),langue,GestionEquipe::APPRENDRE_CT,donnees,gestion_i->obj_select().first);
	}else{
		gestion->maj_fiche(par.utilis(),langue,GestionEquipe::APPRENDRE_CS,donnees,gestion_i->obj_select().first);
	}
	//
}

void Fenetre::achat(){
	Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
	Environnement *env_=donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement());
	if(gestion_a->type_gestion()==GestionAchatVente::ACHAT_OBJET){
		foreach(QString o,gestion_a->val_quantites_achat().cles()){
			par.utilis().achat_objet(o,gestion_a->val_quantites_achat().valeur(o),donnees);
		}
		gestion_a->maj_fiche(gestion_a->type_gestion(),par.utilis(),env_->achat_objets(voisin_.coords_tuile()));
	}else{
		foreach(uchar c,gestion_a->val_quantites_ct().cles()){
			par.utilis().achat_ct(c,gestion_a->val_quantites_ct().valeur(c));
		}
		gestion_a->maj_fiche_c(gestion_a->type_gestion(),par.utilis(),env_->achat_ct(voisin_.coords_tuile()));
	}
}

void Fenetre::vente(){
	if(gestion_a->type_gestion()==GestionAchatVente::VENTE_OBJET){
		typedef QPair<QString,int> ObjetIndice;
		foreach(ObjetIndice o,gestion_a->val_quantites_vente().cles()){
			par.utilis().vente_objet(o.first,o.second,gestion_a->val_quantites_vente().valeur(o),donnees);
		}
		gestion_a->maj_fiche(gestion_a->type_gestion(),par.utilis());
	}else{
		foreach(uchar c,gestion_a->val_quantites_ct().cles()){
			par.utilis().vente_ct(c,gestion_a->val_quantites_ct().valeur(c));
		}
		gestion_a->maj_fiche_c(gestion_a->type_gestion(),par.utilis());
	}
}

void Fenetre::erreur_achat(){
	interactions->maj_commentaire("Pas assez d'argent");
}

void Fenetre::erreur_vente(){
	interactions->maj_commentaire("Pas assez d'objets");
}

void Fenetre::finir_gestion_achat_vente(){
	gestion_a->hide();
}


void Fenetre::finir_gestion_equipe(){
	gestion->gestion_finie();
	gestion->hide();
	asc_cl->hide();
}

void Fenetre::evoluer(const QString& _pierre,uchar _pos){
	if(par.utilis().inv().pierres_evo_ut().valeur(_pierre)>0){
		par.utilis().inv().pierres_evo_ut().valeur(_pierre)--;
		QString com_;
		par.utilis().evoluer_pk_pierre(_pos,_pierre,com_,donnees);
		gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
		gestion_i->maj_fiche(par.utilis().inv(),langue,GestionInventaire::PIERRE_EVO);
		interactions->maj_commentaire(com_);
	}
}

void Fenetre::finir_gerer_inventaire(){
	gestion_i->hide();
	gestion->gestion_finie();
	gestion->hide();
}

void Fenetre::vivre_fossile(const QString& _fossile){
	Utilisateur& ut_=par.utilis();
	QString comm_;
	ut_.faire_vivre_fossile(_fossile,par.diff().r_nb_max_pk_par_equipe(),donnees,comm_);
	interactions->maj_commentaire(comm_);
	int nb_=par.utilis().equipe_ut().size()+par.utilis().oeufs().size();
	gestion_f->maj_fiche(par.utilis().inv().fossiles_ut(),par.utilis().inv(),langue,nb_,par.diff().r_nb_max_pk_par_equipe());
}

void Fenetre::interaction(uchar _action,uchar _sous_action,const QString& _nom){
	if(_action==Partie::PK_LEG){
		Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
		PokemonSauvage *pk_leg_=donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement())->pokemon_legendaire(voisin_.coords_tuile());
		par.combat()=ElementsCombat(par.utilis(),par.diff(),pk_leg_,donnees);
		par.combat().maj_coords_leg()=voisin_;
		Combattant cbt_=par.combat().combattants_a_position(QPair<uchar,uchar>(donnees->val_ut(),0))[0];
		scene_c->maj_fiche(cbt_,par.combat(),par.utilis().inv(),par.diff(),false,false,donnees);
		scene_c->afficher_evolutions(false);
		scene_c->afficher_attaques_objets(true);
		scene_c->afficher_actions_sauvage(true);
		scene_c->show();
		scene_hc->hide();
		interactions->hide();
		menu->hide();
	}else if(_action==Partie::VOL){
		if(_sous_action==0){
			//voler
			if(coords_vol==Coordonnees()||!par.lieu_visite(coords_vol.lieu())){
				return;
			}
			gestion->gestion_finie();
			asc_cl->hide();
			gestion->hide();
			asc_gestion_v->hide();
			par.coords_util()=coords_vol;
			scene_hc->maj_tuiles(par,coords_vol,par.present_ligue(),donnees);
			scene_hc->repaint();
			interactions->raz_interaction();
			maj_coords_vol(Coordonnees());
		}else if(_sous_action==1){
			//annuler vol
			maj_coords_vol(Coordonnees());
		}else if(_sous_action==2){
			//retour gestion equipe
			gestion->show();
			asc_cl->show();
			asc_gestion_v->hide();
			interactions->raz_interaction();
			maj_coords_vol(Coordonnees());
		}else{
			//fin de gestion
			gestion->gestion_finie();
			gestion->hide();
			asc_cl->hide();
			asc_gestion_v->hide();
			interactions->raz_interaction();
			maj_coords_vol(Coordonnees());
		}
	}else if(_action==Partie::DIFF){
		asc_gestion_o->hide();
		interactions->raz_interaction();
	}else if(_action==Partie::JOUEUR){
		asc_fiche_partie->hide();
		interactions->raz_interaction();
	}else if(_action==Partie::PENSION){
		Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
		Utilisateur& ut_=par.utilis();
		QString commentaire_;
		if(_sous_action==1){
			QList<QPair<uchar,OeufPokemon> >& oeufs_=ut_.oeufs();
			int total_=ut_.equipe_ut().size()+oeufs_.size();
			if(total_<par.diff().r_nb_max_pk_par_equipe()){
				OeufPokemon oeuf_=par.oeuf_produit(voisin_,donnees);
				oeufs_<<QPair<uchar,OeufPokemon>(total_,oeuf_);
				par.prendre_oeuf_produit(voisin_);
				commentaire_+="Vous avez recuperer un oeuf contenant "+oeuf_.nom_pk()+"\n";
				interactions->raz_interaction();
			}else{
				commentaire_+="Pas asssez de place dans l'equipe\npour recuperer l'oeuf\n";
			}
			interactions->maj_commentaire(commentaire_);
		}else if(par.possibilite_de_recuperer_oeuf(voisin_,donnees)){
			QList<QPair<uchar,OeufPokemon> >& oeufs_=ut_.oeufs();
			int total_=ut_.equipe_ut().size()+oeufs_.size();
			if(total_+2<par.diff().r_nb_max_pk_par_equipe()){
				OeufPokemon oeuf_=par.oeuf_produit(voisin_,donnees);
				par.recuperer_pokemons_pension(voisin_);
				total_+=2;
				oeufs_<<QPair<uchar,OeufPokemon>(total_,oeuf_);
				par.prendre_oeuf_produit(voisin_);
				commentaire_+="Vous avez recuperer un oeuf contenant "+oeuf_.nom_pk()+"\net les deux pokemons l'ayant produite\n";
				interactions->raz_interaction();
			}else{
				commentaire_+="Pas asssez de place dans l'equipe\npour recuperer l'oeuf\n";
			}
		}else if(!par.recuperer_pokemons_pension(voisin_)){
			commentaire_+="Pas asssez de place dans l'equipe\npour recuperer les pokemons a la pensions\n";
		}else{
			commentaire_+="Vous avez recupere les pokemons de la pensions\n";
			interactions->raz_interaction();
		}
		interactions->maj_commentaire(commentaire_);
	}else if(_action==Partie::DON_PK){
		Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
		PokemonSauvage *pk_=donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement())->don_pokemon(voisin_.coords_tuile());
		QString commentaire_;
		bool suppr_=true;
		if(!par.utilis().recevoir_pokemon(pk_,par.diff().r_nb_max_pk_par_equipe(),donnees,commentaire_)){
			suppr_=false;
		}
		if(suppr_){
			par.prendre_pokemon(voisin_);
			scene_hc->maj_tuiles(par,par.coords_util(),par.present_ligue(),donnees);
			scene_hc->repaint();
			interactions->raz_interaction();
		}
		interactions->maj_commentaire(commentaire_);
	}else if(_action==Partie::OBJ_RAMAS||_action==Partie::DON_OBJET){
		Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
		//TODO gerer la suppression d'objet
		QString obj_;
		if(_action==Partie::OBJ_RAMAS){
			obj_=donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement())->objet_donne_ramasse(voisin_.coords_tuile());
		}else{
			obj_=donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement())->objet(voisin_.coords_tuile());
		}
		par.utilis().ramasser_objet(obj_,donnees);
		scene_hc->maj_tuiles(par,par.coords_util(),par.present_ligue(),donnees);
		scene_hc->repaint();
		interactions->raz_interaction();
	}else if(_action==Partie::PECHE){
		Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
		Environnement *env_=donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement());
		QList<PokemonSauvage*> liste_peche_=env_->apparition_p_pok(_nom);
		bool existe_leg_=false;
		foreach(PokemonSauvage *p,liste_peche_){
			if(par.utilis().present_pk(p->n_pk())){
				FichePokemon *f_pk_=donnees->val_pokedex().valeur(p->n_pk());
				if(f_pk_->rep_genr()=="<LEG>"){
					existe_leg_=true;
					break;
				}
			}
		}
		if(existe_leg_){
			liste_peche_=env_->apparition_p_pok(_nom);
		}
		if(liste_peche_.isEmpty()){
			return;
		}
		PokemonSauvage *pk_=NULL;
		if(!par.diff().r_appar_alea()){
			int per_=par.periode_peche(_nom);
			if(per_>=liste_peche_.size()){
				pk_=liste_peche_[0];
				par.reinit_per_peche(_nom);
				per_=0;
			}else{
				pk_=liste_peche_[per_];
			}
			if(per_+1<liste_peche_.size()){
				par.incrementer_per_peche(_nom);
			}else{
				par.reinit_per_peche(_nom);
			}
		}else{
			if(existe_leg_){
				pk_=env_->apparition_a_sans_leg_pok(_nom).tirage();
			}else{
				pk_=env_->apparition_a_pok(_nom).tirage();
			}
		}
		par.combat()=ElementsCombat(par.utilis(),par.diff(),pk_,donnees);
		Combattant cbt_=par.combat().combattants_a_position(QPair<uchar,uchar>(donnees->val_ut(),0))[0];
		scene_c->maj_fiche(cbt_,par.combat(),par.utilis().inv(),par.diff(),false,false,donnees);
		scene_c->afficher_evolutions(false);
		scene_c->afficher_attaques_objets(true);
		scene_c->show();
		scene_hc->hide();
		interactions->hide();
		menu->hide();
	}else if(_action==Partie::DRESSEUR){
		if(par.present_ligue()){
			Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
			DresseurLigue *dr_=plateau_ligue->val_dresseur_ligue();
			//TODO pres du dresseur
			par.combat()=ElementsCombat(par.utilis(),par.diff(),dr_,donnees);
			par.combat().init_type_env(par.coords_util(),voisin_,par.present_ligue(),donnees);
		}else{
			bool battu_=true;
			int nb_=0;
			typedef QPair<Coordonnees,int> DresseurNb;
			Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
			foreach(DresseurNb d,par.r_dresseurs_battus().cles()){
				if(d.first==voisin_){
					if(!par.r_dresseurs_battus().valeur(DresseurNb(d.first,nb_))){
						battu_=false;
						break;
					}
					nb_++;
				}
			}
			Environnement *env_=donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement());
			Dresseur1 *dr_=qobject_cast<Dresseur1*>(env_->perso(voisin_.coords_tuile()));
			par.combat()=ElementsCombat(par.utilis(),par.diff(),dr_,donnees,nb_);
			par.combat().init_type_env(par.coords_util(),voisin_,par.present_ligue(),donnees);
		}
		ElementsCombat& elt_=par.combat();
		HashMap<Combattant,QPair<QString,QPair<Combattant,Combattant> > > choix_=elt_.choix_ia_attaque(donnees);
		foreach(Combattant c,choix_.cles()){
			CreatureCombat& cr_c_=elt_.creature_combat(c);
			QPair<QString,QPair<Combattant,Combattant> > valeur_=choix_.valeur(c);
			cr_c_.att_choisie()=valeur_.first;
			cr_c_.cibles().clear();
			if(valeur_.second.first!=Combattant()){
				cr_c_.act_choisie()="ATTAQUE";
				cr_c_.cibles()<<elt_.position(valeur_.second.first);
			}
			cr_c_.remplacant()=valeur_.second.second;
		}
		Combattant cbt_=par.combat().combattants_a_position(QPair<uchar,uchar>(donnees->val_ut(),0))[0];
		scene_c->maj_fiche(cbt_,par.combat(),par.utilis().inv(),par.diff(),false,false,donnees);
		scene_c->afficher_evolutions(false);
		scene_c->afficher_attaques_objets(true);
		scene_c->afficher_actions_sauvage(false);
		scene_c->show();
		scene_hc->hide();
		interactions->hide();
		menu->hide();
	}else if(_action==Partie::ACHATS){
		Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
		Environnement *env_=donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement());
		if(_sous_action==0){
			gestion_a->maj_fiche(GestionAchatVente::ACHAT_OBJET,par.utilis(),env_->achat_objets(voisin_.coords_tuile()));
		}else{
			gestion_a->maj_fiche(GestionAchatVente::VENTE_OBJET,par.utilis());
		}
		gestion_a->show();
		interactions->raz_interaction();
	}else if(_action==Partie::ACHATS_CT){
		Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),par.orientation(),par.present_ligue());
		Environnement *env_=donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement());
		if(_sous_action==0){
			gestion_a->maj_fiche_c(GestionAchatVente::ACHAT_CT,par.utilis(),env_->achat_ct(voisin_.coords_tuile()));
		}else{
			gestion_a->maj_fiche_c(GestionAchatVente::VENTE_CT,par.utilis());
		}
		gestion_a->show();
		interactions->raz_interaction();
	}else if(_action==Partie::FOSSILE){
		gestion_f->hide();
		interactions->raz_interaction();
	}
}

void Fenetre::echanger_pokemons_boite(const QPair<int,int>& _pos_1,const QPair<int,int>& _pos_2){
	Utilisateur& ut_=par.utilis();
	QPair<uchar,uchar> pos_1_(_pos_1.first,_pos_1.second);
	QPair<uchar,uchar> pos_2_(_pos_2.first,_pos_2.second);
	if(_pos_1.first<0){
		//equipe et boite
		ut_.echanger_pokemons(_pos_1.second,pos_2_,donnees);
	}else{
		ut_.echanger_pokemons(pos_1_,pos_2_);
	}
	gestion_b->maj_fiche(ut_,langue,donnees);
}

void Fenetre::echanger_objets_boite(const QPair<int,int>& _pos_1,const QPair<int,int>& _pos_2){
	Utilisateur& ut_=par.utilis();
	QPair<uchar,uchar> pos_1_(_pos_1.first,_pos_1.second);
	QPair<uchar,uchar> pos_2_(_pos_2.first,_pos_2.second);
	if(_pos_1.first<0){
		//equipe et boite
		ut_.echanger_objets(_pos_1.second,pos_2_);
	}else{
		ut_.echanger_objets(pos_1_,pos_2_);
	}
	gestion_b->maj_fiche(ut_,langue,donnees);
}

void Fenetre::ranger_objets_boite(const QPair<int,int>& _pos_1){
	Utilisateur& ut_=par.utilis();
	QPair<uchar,uchar> pos_1_(_pos_1.first,_pos_1.second);
	QString obj_;
	if(_pos_1.first<0){
		//equipe et boite
		ut_.retirer_objet(_pos_1.second,true,obj_,donnees);
		if(obj_!=""){
			QString commentaire_="L'objet "+obj_+" est range dans l'inventaire";
			interactions->maj_commentaire(commentaire_);
		}
	}else{
		ut_.retirer_objet(pos_1_,true,obj_,donnees);
		if(obj_!=""){
			QString commentaire_="L'objet "+obj_+" est range dans l'inventaire";
			interactions->maj_commentaire(commentaire_);
		}
	}
	gestion_b->maj_fiche(ut_,langue,donnees);
}

void Fenetre::deposer_pokemon(uchar _pos,const QPair<uchar,uchar>& _indice_boite){
	Utilisateur& ut_=par.utilis();
	ut_.placer_dans_boite(_pos,_indice_boite,donnees);
	gestion_b->maj_fiche(ut_,langue,donnees);
}

void Fenetre::retrait_pokemon(const QPair<uchar,uchar>& _indice_boite){
	Utilisateur& ut_=par.utilis();
	ut_.retirer_de_boite(_indice_boite,par.diff().r_nb_max_pk_par_equipe());
	gestion_b->maj_fiche(ut_,langue,donnees);
}

void Fenetre::relacher_pokemon(const QPair<uchar,uchar>& _indice_boite){
	Utilisateur& ut_=par.utilis();
	ut_.relacher_pokemon(_indice_boite,donnees);
	gestion_b->maj_fiche(ut_,langue,donnees);
}

void Fenetre::finir_gestion_boite(){
	gestion_b->hide();
}

void Fenetre::joueur(){
	if(debut_jeu){
		return;
	}
	en_deplacement=true;
	interactions->maj_interaction(Partie::JOUEUR,QStringList("Finir"));
	fiche_partie->maj_fiche(par,donnees);
	asc_fiche_partie->show();
	en_deplacement=false;
}

void Fenetre::options(){
	if(debut_jeu){
		return;
	}
	en_deplacement=true;
	interactions->maj_interaction(Partie::DIFF,QStringList("Finir"));
	Utilisateur& ut_=par.utilis();
	gestion_o->maj_fiche(par.diff(),ut_.equipe_ut().size()+ut_.oeufs().size());
	asc_gestion_o->show();
	en_deplacement=false;
}

void Fenetre::maj_diff(const Difficulte& _diff){
	par.diff()=_diff;
}

void Fenetre::maj_coords_vol(const Coordonnees& _coords_vol){
	coords_vol=_coords_vol;
	if(coords_vol==Coordonnees()){
		interactions->maj_commentaire("");
	}else{
		interactions->maj_commentaire("Voler vers "+donnees->val_lieux().valeur(coords_vol.lieu())->val_nom());
	}
}

void Fenetre::redessiner_ihm(uchar _res){
	ElementsCombat& elt_=par.combat();
	elt_.situation_cbt()=_res;
	if(_res==ElementsCombat::REDESSIN_SCENE){
		elt_.fin_cbt();
		scene_c->raz_scene_combat();
		scene_c->hide();
		menu->show();
		scene_hc->show();
		interactions->show();
		//
	}else if(_res==ElementsCombat::VILLE_DEPART){
		par.nb_dresseur_ligue_battus()=0;
		par.coords_util()=donnees->val_coords_depart();
		par.utilis().soin_equipe_ct_pk(donnees);
		elt_.fin_cbt();
		scene_c->hide();
		menu->show();
		scene_hc->maj_tuiles(par,par.coords_util(),par.present_ligue(),donnees);
		scene_hc->repaint();
		scene_hc->show();
		interactions->show();
	}else if(_res==ElementsCombat::DEBUT_LIGUE){
		par.nb_dresseur_ligue_battus()=0;
		par.coords_util()=ligue->origine_c();
		par.present_ligue()=false;
		par.utilis().soin_equipe_ct_pk(donnees);
		elt_.fin_cbt();
		scene_c->hide();
		menu->show();
		scene_hc->maj_tuiles(par,par.coords_util(),par.present_ligue(),donnees);
		scene_hc->repaint();
		scene_hc->show();
	}else if(_res==ElementsCombat::CAPTURE_KO){
		Combattant cbt_(donnees->val_ut(),0);
		scene_c->maj_fiche(cbt_,elt_,par.utilis().inv(),par.diff(),false,false,donnees);
		scene_c->afficher_attaques_objets(false);
		scene_c->afficher_evolutions(false);
	}else if(_res==ElementsCombat::SURNOM){
		asc_cl->show();
	}else if(_res==ElementsCombat::APPRENDRE_ATT){
		//elt_.traiter_apprentissage_attaque(res_2_,)
		Combattant cbt_(donnees->val_ut(),elt_.indice_pos_pk());
		scene_c->maj_fiche(cbt_,par.combat(),par.utilis().inv(),par.diff(),true,false,donnees);
		scene_c->afficher_attaques_objets(true);
		scene_c->afficher_evolutions(false);
		scene_c->ajout_commentaire("Apprendre attaque?");
		scene_c->afficher_actions_sauvage(false);
	}else if(_res==ElementsCombat::EVOLUTION){
		scene_c->afficher_attaques_objets(false);
		scene_c->afficher_evolutions(true);
	}else if(_res==ElementsCombat::PAS_SWITCH){
		QString envoi_;
		QList<Combattant> cbts_=elt_.choix_ia_envoi_remplacement();
		foreach(Combattant e,elt_.choix_ia_envoi_remplacement()){
			CreatureCombat& cr_c_=elt_.creature_combat(e);
			foreach(Combattant f,elt_.fronts()){
				if(f.equipe()==donnees->val_adv()){
					CreatureCombat& cr_f_=elt_.creature_combat(f);
					if(cr_f_.statut_pk()=="KO"){
						cr_f_.remplacant()=e;
						envoi_+=cr_c_.nom_pk_act()+" va etre envoye a la place de "+cr_f_.nom_pk_act()+"\n";
					}
				}
			}
		}
		if(!cbts_.isEmpty()){
			Combattant cbt_;
			foreach(Combattant c,elt_.fronts()){
				if(c.equipe()==donnees->val_ut()){
					cbt_=c;
					break;
				}
			}
			scene_c->maj_fiche(cbt_,par.combat(),par.utilis().inv(),par.diff(),false,true,donnees);
			scene_c->afficher_evolutions(false);
			scene_c->ajout_commentaire(envoi_);
			elt_.situation_cbt()=ElementsCombat::SWITCH_PROPOSE;
		}
	}else if(_res==ElementsCombat::SWITCH_PROPOSE){
		Combattant cbt_;
		foreach(Combattant c,elt_.fronts()){
			if(c.equipe()==donnees->val_ut()){
				cbt_=c;
				break;
			}
		}
		scene_c->maj_fiche(cbt_,par.combat(),par.utilis().inv(),par.diff(),false,true,donnees);
		scene_c->afficher_evolutions(false);
		QString envoi_;
		foreach(Combattant e,elt_.choix_ia_envoi_remplacement()){
			CreatureCombat& cr_c_=elt_.creature_combat(e);
			foreach(Combattant f,elt_.fronts()){
				if(f.equipe()==donnees->val_adv()){
					CreatureCombat& cr_f_=elt_.creature_combat(f);
					if(cr_f_.statut_pk()=="KO"){
						cr_f_.remplacant()=e;
						envoi_+=cr_c_.nom_pk_act()+" va etre envoye a la place de "+cr_f_.nom_pk_act()+"\n";
					}
				}
			}
		}
		envoi_+="Voulez vous changer de pokemons?\n";
		scene_c->ajout_commentaire(envoi_);
	}else if(_res==ElementsCombat::NORMAL){
		//uchar res_=elt_.traiter_remplacement(par.utilis(),par.ligues_battues(),par.nb_dresseur_ligue_battus(),par.r_dresseurs_battus(),donnees);
		if(elt_.type_cbt()!="SAUVAGE"){
			HashMap<Combattant,QPair<QString,QPair<Combattant,Combattant> > > choix_=elt_.choix_ia_attaque(donnees);
			foreach(Combattant c,choix_.cles()){
				CreatureCombat& cr_c_=elt_.creature_combat(c);
				QPair<QString,QPair<Combattant,Combattant> > valeur_=choix_.valeur(c);
				cr_c_.att_choisie()=valeur_.first;
				cr_c_.cibles().clear();
				if(valeur_.second.first!=Combattant()){
					cr_c_.act_choisie()="ATTAQUE";
					cr_c_.cibles()<<elt_.position(valeur_.second.first);
				}
				cr_c_.remplacant()=valeur_.second.second;
			}
		}
		Combattant cbt_=par.combat().combattants_a_position(QPair<uchar,uchar>(donnees->val_ut(),0))[0];
		scene_c->maj_fiche(cbt_,par.combat(),par.utilis().inv(),par.diff(),false,false,donnees);
		scene_c->afficher_evolutions(false);
	}
}

void Fenetre::keyPressEvent(QKeyEvent *_ev){

}

void Fenetre::deplacement(QKeyEvent *_ev){
	if(en_deplacement){
		return;
	}
	en_deplacement=true;
	if(initialisateur&&initialisateur->isRunning()){
		en_deplacement=false;
		return;
	}
	if(par.combat().type_cbt()!=""||!asc_cl||asc_cl->isVisible()||!gestion||gestion->gestion()!=GestionEquipe::RIEN||gestion_b->isVisible()){
		en_deplacement=false;
		return;
	}
	if(gestion_i->isVisible()||gestion_a->isVisible()||gestion_f->isVisible()||asc_fiche_partie->isVisible()||asc_gestion_o->isVisible()){
		en_deplacement=false;
		return;
	}
	if(asc_gestion_v->isVisible()){
		en_deplacement=false;
		return;
	}
	if(debut_jeu){
		en_deplacement=false;
		return;
	}
	//patience->show();
	QPair<int,int> dir_(0,0);
	if(_ev->key()==Qt::Key_Up){
		dir_.second=-1;
	}else if(_ev->key()==Qt::Key_Down){
		dir_.second=1;
	}else if(_ev->key()==Qt::Key_Left){
		dir_.first=-1;
	}else if(_ev->key()==Qt::Key_Right){
		dir_.first=1;
	}else{
		en_deplacement=false;
		return;
	}
	QPair<int,int> coords_muret_(0,0);
	QPair<int,int> deplacement_(0,0);
	QPair<int,int> orientation_=par.orientation();
	Coordonnees coords_ut_=par.coords_util();
	bool ligue_=par.present_ligue();
	uchar res_=par.deplacement(dir_,coords_muret_,deplacement_,donnees);
	//std::cout<<QString::number(res_).toStdString()<<"\n";
	if(par.partie_finie(donnees)&&par.coords_util()==donnees->val_coords_depart()){
		scene_c->hide();
		scene_hc->hide();
		interactions->hide();
		menu->hide();
#ifdef PERSO
		QLabel *etiq_=new QLabel();
		etiq_->setPixmap(QImage(":/ihm/anthea_and_concordia"));
		centre->addWidget(etiq_);
#endif
		QMessageBox::information(this,"Felicitations!","Vous avez fini pokemon evolution.");
		close();
		return;
	}else if(ligue_!=par.present_ligue()){
		par.nb_dresseur_ligue_battus()=0;
		scene_hc->maj_tuiles(par,par.coords_util(),par.present_ligue(),donnees);
		scene_hc->repaint();
	}else if(coords_ut_.val_lieu_plateau()!=par.coords_util().val_lieu_plateau()){
		scene_hc->maj_tuiles(par,par.coords_util(),par.present_ligue(),donnees);
		scene_hc->repaint();
	}else if(deplacement_.first!=0||deplacement_.second!=0){
		scene_hc->maj_camera(par,dir_,par.present_ligue(),donnees);
		scene_hc->repaint();
	}else if(orientation_!=par.orientation()){
		scene_hc->maj_orientation(par.orientation());
		scene_hc->repaint();
	}
	if(par.present_ligue()){
		ligue=donnees->val_ligues().valeur(par.coords_util().lieu());
		lieu=NULL;
		plateau_ligue=ligue->plateau(par.coords_util().plateau());
		plateau=NULL;
	}else{
		ligue=NULL;
		lieu=donnees->val_lieux().valeur(par.coords_util().lieu());
		plateau_ligue=NULL;
		plateau=lieu->plateau(par.coords_util().plateau());
	}
	//Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),dir_,par.present_ligue());
	//lieu=donnees->val_lipar.coords_util().lieu();
	QString com_;
	if(res_==Partie::COMBAT_PK_SAUV){
		Combattant cbt_=par.combat().combattants_a_position(QPair<uchar,uchar>(donnees->val_ut(),0))[0];
		scene_c->maj_fiche(cbt_,par.combat(),par.utilis().inv(),par.diff(),false,false,donnees);
		scene_c->afficher_evolutions(false);
		scene_c->afficher_attaques_objets(true);
		scene_c->afficher_actions_sauvage(true);
		scene_c->show();
		scene_hc->hide();
		interactions->hide();
		menu->hide();
	}else if(res_==Partie::SOIN_PK){
		com_="Votre equipe est\nsoignee!\n";
		par.utilis().soin_equipe_ct_pk(donnees);
	}else if(res_==Partie::DON_CS){
		Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),dir_,par.present_ligue());
		foreach(uchar c,donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement())->don_cs(voisin_.coords_tuile())){
			par.utilis().inv().cs_ut().valeur(c)=true;
		}
	}else if(res_==Partie::PK_LEG){
		interactions->maj_interaction(res_,QStringList("Pokemon legendaire"));
	}else if(res_==Partie::OBJ_RAMAS||res_==Partie::DON_OBJET){
		interactions->maj_interaction(res_,QStringList("Prendre l'objet"));
	}else if(res_==Partie::DON_PK){
		interactions->maj_interaction(res_,QStringList("Pokemon a prendre"));
		//coords_leg
	}else if(res_==Partie::RIEN){
		interactions->raz_interaction();
		interactions->maj_commentaire("");//PECHE
	}else if(res_==Partie::PENSION){
		Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),dir_,par.present_ligue());
		if(!par.pension_disponible(voisin_)){
			QStringList actions_;
			actions_<<"Recuperer pokemons";
			if(par.possibilite_de_recuperer_oeuf(voisin_,donnees)){
				actions_<<"Recuperer oeuf";
			}else{
				par.commentaire_r()+=QString::number(par.nombre_pas_restants(voisin_,donnees))+" pas restants avant d'avoir l'oeuf";
			}
			interactions->maj_interaction(res_,actions_);
		}else{
			gestion->show();
			gestion->maj_fiche(par.utilis(),langue,GestionEquipe::PENSION,donnees);
		}
	}else if(res_==Partie::MOVE_TUTORS){
		gestion->show();
		gestion->maj_fiche(par.utilis(),langue,GestionEquipe::MOVE_TUTORS,donnees);
	}else if(res_==Partie::ECH_BOITE){
		gestion_b->show();
		gestion_b->maj_fiche(par.utilis(),langue,donnees);
	}else if(res_==Partie::ACHATS){
		QStringList actions_;
		actions_<<"Acheter";
		actions_<<"Vendre";
		interactions->maj_interaction(res_,actions_);
	}else if(res_==Partie::ACHATS_CT){
		QStringList actions_;
		actions_<<"Acheter";
		actions_<<"Vendre";
		interactions->maj_interaction(res_,actions_);
	}else if(res_==Partie::FOSSILE){
		gestion_f->show();
		int nb_=par.utilis().equipe_ut().size()+par.utilis().oeufs().size();
		gestion_f->maj_fiche(par.utilis().inv().fossiles_ut(),par.utilis().inv(),langue,nb_,par.diff().r_nb_max_pk_par_equipe());
		interactions->maj_interaction(res_,QStringList("Finir"));
	}else if(res_==Partie::DRESSEUR){
		interactions->maj_interaction(res_,QStringList("Dresseur a battre"));
	}else if(res_==Partie::PECHE){
		QStringList cannes_;
		cannes_<<Environnement::_canne_;
		cannes_<<Environnement::_super_canne_;
		cannes_<<Environnement::_mega_canne_;
		interactions->maj_interaction(res_,cannes_);
		//Coordonnees voisin_=donnees->tuile_voisine(par.coords_util(),dir_,par.present_ligue());
		//Environnement *env_=donnees->val_lieux().valeur(voisin_.lieu())->plateau(voisin_.plateau())->environnement(voisin_.coords_environnement());
		//env_->apparition_p_pok("");
	}//gestion_a
	if(interactions->isVisible()){
		interactions->maj_commentaire(com_+par.commentaire_r());
	}
	par.commentaire_r()="";
	en_deplacement=false;
}

void Fenetre::keyReleaseEvent(QKeyEvent *_ev){
	deplacement(_ev);
}

void Fenetre::closeEvent(QCloseEvent *_ev){
	if(initialisateur&&initialisateur->isRunning()){
		_ev->ignore();
		return;
	}
}

Fenetre::~Fenetre(){
	delete donnees;
	donnees=NULL;
	delete scene_hc;
	scene_hc=NULL;
	delete scene_c;
	scene_c=NULL;
	delete menu;
	menu=NULL;
	delete patience;
	patience=NULL;
}
