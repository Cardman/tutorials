#include "ihm/hors_combat/fiches/ficheoeuf.h"
#include "ihm/combat/etiquettes/barre.h"
#include "serialisable/pokemon/oeufpokemon.h"
#include "serialisable/math/taux.h"
#include "base_donnees/donnees.h"
#include <QVBoxLayout>

FicheOeuf::FicheOeuf(){
	QVBoxLayout *lay_=new QVBoxLayout();
	lay_->setSpacing(0);
	nom_futur_pokemon=new QLabel();
	lay_->addWidget(nom_futur_pokemon);
	//nom_parent_ayant_pondu_oeuf=new QLabel();
	//lay_->addWidget(nom_parent_ayant_pondu_oeuf);
	taux_pas_restants=new Barre(QColor(255,0,0,255));
	lay_->addWidget(taux_pas_restants);
	pas_restants=new QLabel();
	lay_->addWidget(pas_restants);
	setLayout(lay_);
	setFixedHeight(100);
	setFixedWidth(120);
}

void FicheOeuf::maj_fiche(const OeufPokemon& _oeuf,Donnees* _d){
	nom_futur_pokemon->setText("Futur pokemon:\n"+_oeuf.nom_pk());
	//nom_parent_ayant_pondu_oeuf->setText("Pokemon ayant pondu l'oeuf:"+_oeuf.);
	FichePokemon *f_pk_=_d->val_pokedex().valeur(_oeuf.nom_pk());
	int nb_pas_=_oeuf.nb_pas();
	Entier pas_=f_pk_->pas_ecl();
	Entier pas_restants_=pas_-Entier(nb_pas_);
	Taux tx_(pas_restants_,pas_);
	taux_pas_restants->maj_pourcent(tx_);
	taux_pas_restants->repaint();
	pas_restants->setText(pas_restants_.chaine()+"/"+pas_.chaine());
}
