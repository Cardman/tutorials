#include "ihm/hors_combat/fiches/fichepartie.h"
#include "serialisable/partie/partie.h"
#include "base_donnees/donnees.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>

FichePartie::FichePartie(Donnees *_d){
	foreach(QString p,_d->val_pokedex().cles()){
		pokemon_attrapes.ajouter_cle_valeur(p,false);
	}
	QPair<QPair<PokemonUtilisateur,PokemonUtilisateur>,int> triplet_(QPair<PokemonUtilisateur,PokemonUtilisateur>(PokemonUtilisateur(),PokemonUtilisateur()),0);
	typedef QPair<int,int> Coin;
	Coordonnees c_;
	foreach(int l,_d->val_lieux().cles()){
		Lieu *l_=_d->val_lieux().valeur(l);
		c_.lieu()=l;
		foreach(int p,l_->plateaux_c()){
			Plateau *p_=l_->plateau(p);
			c_.plateau()=p;
			foreach(Coin e,p_->coords_env()){
				Environnement *e_=p_->environnement(e);
				c_.coords_environnement()=e;
				QPair<int,int> dims_=e_->dimensions();
				for(int i=0;i<dims_.first;i++){
					for(int j=0;j<dims_.second;j++){
						if(e_->contient_pension(QPair<int,int>(i,j))){
							c_.coords_tuile()=QPair<int,int>(i,j);
							pokemon_pension.ajouter_cle_valeur(c_,triplet_);
						}
					}
				}
			}
		}
	}
	stade_ligue=0;
	repousse_actif=false;
	pas_restants_repousse=0;
	argent=Entier(0);
	indice_pas=0;
	indice_periode=0;
	indice_periode_peche.ajouter_cle_valeur(Environnement::_canne_,0);
	indice_periode_peche.ajouter_cle_valeur(Environnement::_super_canne_,0);
	indice_periode_peche.ajouter_cle_valeur(Environnement::_mega_canne_,0);
	ligue=false;
	QHBoxLayout *lay_partiel_=new QHBoxLayout();
	et_pseudo=new QLabel();
	lay_partiel_->addWidget(et_pseudo);
	et_argent=new QLabel();
	lay_partiel_->addWidget(et_argent);
	QVBoxLayout *lay_=new QVBoxLayout();
	lay_->addLayout(lay_partiel_);
	et_repousse=new QLabel();
	lay_->addWidget(et_repousse);
	QScrollArea *asc_=new QScrollArea();
	groupe_pokemon=new QGroupBox();
	pokemons=new QVBoxLayout();
	groupe_pokemon->setLayout(pokemons);
	asc_->setWidget(groupe_pokemon);
	lay_->addWidget(asc_);
	et_ligue=new QLabel();
	lay_->addWidget(et_ligue);
	asc_=new QScrollArea();
	groupe_pokemon_pens=new QGroupBox();
	pokemons_pens=new QVBoxLayout();
	groupe_pokemon_pens->setLayout(pokemons_pens);
	asc_->setWidget(groupe_pokemon_pens);
	lay_->addWidget(asc_);
	setLayout(lay_);
}

void FichePartie::maj_fiche(const Partie& _partie,Donnees* _d){
	Utilisateur ut_=_partie.utilis();
	et_pseudo->setText(ut_.nom());
	et_pseudo->setFixedHeight(20);
	et_pseudo->setMinimumWidth(200);
	et_argent->setText("argent: "+ut_.val_argent().chaine());
	et_argent->setFixedHeight(20);
	et_argent->setMinimumWidth(200);
	if(ut_.repous_act()){
		if(ut_.pas_repousse()>0){
			et_repousse->setText("pas restants: "+ut_.pas_repousse());
		}else{
			et_repousse->setText("repousse actif");
		}
	}else{
		et_repousse->setText("repousse inactif");
	}
	et_repousse->setFixedHeight(20);
	foreach(QString p,pokemon_attrapes.cles()){
		pokemon_attrapes.valeur(p)=ut_.present_pk(p);
	}
	groupe_pokemon->setTitle("Pokemons attrapes");
	int nb_=pokemons->count();
	for(int i=0;i<nb_;i++){
		pokemons->itemAt(i)->widget()->deleteLater();
	}
	for(int i=0;i<nb_;i++){
		pokemons->removeItem(pokemons->itemAt(0));
	}
	QHBoxLayout *lay_=new QHBoxLayout();
	QLabel *ico_=new QLabel("ico");
	lay_->addWidget(ico_);
	QLabel *nom_=new QLabel("Nom");
	lay_->addWidget(nom_);
	QLabel *attrape_=new QLabel("Attrape");
	lay_->addWidget(attrape_);
	pokemons->addLayout(lay_);
	int nb_pk_=pokemon_attrapes.total()+1;
	foreach(QString p,pokemon_attrapes.cles()){
		lay_=new QHBoxLayout();
		ico_=new QLabel();
		ico_->setPixmap(QPixmap::fromImage(_d->val_miniatures().valeur(_d->val_pokedex().valeur(p)->num())));
		lay_->addWidget(ico_);
		nom_=new QLabel(p);
		lay_->addWidget(nom_);
		attrape_=new QLabel();
		if(pokemon_attrapes.valeur(p)){
			attrape_->setText("OUI");
		}else{
			attrape_->setText("NON");
		}
		lay_->addWidget(attrape_);
		pokemons->addLayout(lay_);
	}
	groupe_pokemon->setFixedHeight(nb_pk_*32+20);
	groupe_pokemon->setMinimumWidth(250);
	QString texte_;
	if(_partie.present_ligue()){
		texte_+="Present a la ligue\t";
		texte_+="nombre de dresseurs battus: "+QString::number(_partie.nb_dresseur_ligue_battus());
	}else{
		texte_+="Absent de la ligue";
	}
	et_ligue->setText(texte_);
	et_ligue->setFixedHeight(20);
	et_ligue->setMinimumWidth(400);
	groupe_pokemon_pens->setTitle("Pokemons en pension");
	nb_=pokemons_pens->count();
	for(int i=0;i<nb_;i++){
		pokemons_pens->itemAt(i)->widget()->deleteLater();
	}
	for(int i=0;i<nb_;i++){
		pokemons_pens->removeItem(pokemons_pens->itemAt(0));
	}
	lay_=new QHBoxLayout();
	nom_=new QLabel("Nom du 1er parent");
	lay_->addWidget(nom_);
	nom_=new QLabel("Nom du 2e parent");
	lay_->addWidget(nom_);
	QLabel *genre_=new QLabel("Genre du 1er parent");
	lay_->addWidget(genre_);
	genre_=new QLabel("Genre du 2e parent");
	lay_->addWidget(genre_);
	QLabel *pas_=new QLabel("Pas restants");
	lay_->addWidget(pas_);
	/*pas_=new QLabel("Pas totaux");
	lay_->addWidget(pas_);
	pas_=new QLabel("Taux de pas restants");
	lay_->addWidget(pas_);*/
	pokemons_pens->addLayout(lay_);
	nb_pk_=1;
	foreach(Coordonnees c,pokemon_pension.cles()){
		if(_partie.pension_disponible(c)){
			continue;
		}
		nb_pk_++;
		QPair<QPair<PokemonUtilisateur,PokemonUtilisateur>,int> valeur_=pokemon_pension.valeur(c);
		lay_=new QHBoxLayout();
		nom_=new QLabel(valeur_.first.first.n_pk());
		lay_->addWidget(nom_);
		nom_=new QLabel(valeur_.first.second.n_pk());
		lay_->addWidget(nom_);
		genre_=new QLabel(QString(valeur_.first.first.genre_pk()[0]));
		lay_->addWidget(genre_);
		genre_=new QLabel(QString(valeur_.first.second.genre_pk()[0]));
		lay_->addWidget(genre_);
		int nb_pas_=_partie.nombre_pas_restants(c,_d);
		pas_=new QLabel(QString::number(nb_pas_));
		lay_->addWidget(pas_);
		pokemons_pens->addLayout(lay_);
		/*pas_=new QLabel("Pas totaux");
		lay_->addWidget(pas_);
		pas_=new QLabel("Taux de pas restants");
		lay_->addWidget(pas_);
		pokemons_pens->addLayout(lay_);*/
	}
	groupe_pokemon_pens->setFixedHeight(nb_pk_*30+20);
	groupe_pokemon_pens->setMinimumWidth(700);
}
