#include "ihm/hors_combat/fiches/fichepkutequipe.h"
#include "ihm/combat/etiquettes/etiquetteattaque.h"
#include "serialisable/pokemon/pokemonutilisateur.h"
#include "base_donnees/donnees.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "ihm/hors_combat/gestionequipe.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QSplitter>
#include <QScrollArea>
#include <QTextEdit>

FichePkUtEquipe::FichePkUtEquipe(){
	QVBoxLayout *lay_=new QVBoxLayout();
	QHBoxLayout *lay_infos_gener_=new QHBoxLayout();
	QVBoxLayout *lay_partiel_=new QVBoxLayout();
	image_pk=new QLabel();
	image_pk->setPixmap(QPixmap::fromImage(QImage()));
	lay_partiel_->addWidget(image_pk);
	lay_infos_gener_->addLayout(lay_partiel_);
	lay_partiel_=new QVBoxLayout();
	pseudo=new QLabel();
	pseudo->setText("");
	lay_partiel_->addWidget(pseudo);
	capacite=new QLabel();
	capacite->setText("");
	lay_partiel_->addWidget(capacite);
	lay_infos_gener_->addLayout(lay_partiel_);
	lay_partiel_=new QVBoxLayout();
	bonheur=new QLabel();
	bonheur->setText("");
	lay_partiel_->addWidget(bonheur);
	pas_tete_equipe=new QLabel();
	pas_tete_equipe->setText("");
	lay_partiel_->addWidget(pas_tete_equipe);
	lay_infos_gener_->addLayout(lay_partiel_);
	lay_->addLayout(lay_infos_gener_);
	QGroupBox *groupe_=new QGroupBox("Statistiques");
	statistiques=new QGridLayout();
	statistiques->addWidget(new QLabel("Nom"),0,0);
	statistiques->addWidget(new QLabel("Ev"),0,1);
	statistiques->addWidget(new QLabel("Iv"),0,2);
	statistiques->addWidget(new QLabel("Valeur totale"),0,3);
	groupe_->setLayout(statistiques);
	lay_->addWidget(groupe_);
	groupe_=new QGroupBox("Attaques");
	attaques=new QVBoxLayout();
	attaques->addWidget(new QLabel("Nom PP/PP max"),0,0);
	groupe_->setLayout(attaques);
	lay_->addWidget(groupe_);
	description_attaque=new QTextEdit();
	lay_->addWidget(description_attaque);
	description_capacite=new QTextEdit();
	lay_->addWidget(description_capacite);
	description_objet=new QTextEdit();
	lay_->addWidget(description_objet);
	description_pokemon=new QTextEdit();
	lay_->addWidget(description_pokemon);
	setLayout(lay_);
}

void FichePkUtEquipe::maj_fiche(const PokemonUtilisateur& _pk,int _langue,uchar _gestion,Donnees* _d){
	gestion_en_cours=_gestion;
	FichePokemon *f_pk_=_d->val_pokedex().valeur(_pk.n_pk());
	int num_=f_pk_->num();
	image_pk->setPixmap(QPixmap::fromImage(_d->val_images_face_m().valeur(num_)));
	pseudo->setText(_pk.pseudo_pk());
	capacite->setText("Capacite :"+_pk.capacite_pk());
	pas_tete_equipe->setText("nombre de pas\nen tete\ndans l'equipe: "+QString::number(_pk.pas_tete_equipe()));
	bonheur->setText(QString::number(_pk.bonheur_pk()));
	if(noms_statistiques.isEmpty()){
		noms_statistiques=f_pk_->stat_ev().cles();
		int i_=0;
		foreach(QString s,noms_statistiques){
			statistiques->addWidget(new QLabel(s),i_+1,0);
			statistiques->addWidget(new QLabel(QString::number(_pk.ev_stat().valeur(s))),i_+1,1);
			statistiques->addWidget(new QLabel(QString::number(_pk.iv_stat().valeur(s))),i_+1,2);
			statistiques->addWidget(new QLabel(f_pk_->stat(_pk.niv_pk(),s,_pk.ev_stat().valeur(s),_pk.iv_stat().valeur(s)).evaluer(3)),i_+1,3);
			i_++;
		}
		//
	}else{
		int i_=0;
		foreach(QString s,noms_statistiques){
			QLabel *etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,1)->widget());
			etiquette_->setText(QString::number(_pk.ev_stat().valeur(s)));
			etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,2)->widget());
			etiquette_->setText(QString::number(_pk.iv_stat().valeur(s)));
			etiquette_=qobject_cast<QLabel*>(statistiques->itemAtPosition(i_+1,3)->widget());
			etiquette_->setText(f_pk_->stat(_pk.niv_pk(),s,_pk.ev_stat().valeur(s),_pk.iv_stat().valeur(s)).evaluer(3));
			i_++;
		}
	}
	foreach(QString a,liste_attaques.cles()){
		liste_attaques.valeur(a)->deleteLater();
		attaques->removeWidget(liste_attaques.valeur(a));
	}
	liste_attaques.tout_supprimer();
	descriptions_attaques.tout_supprimer();
	description_capacite->setPlainText(_d->val_capacites().valeur(_pk.capacite_pk())->description(_langue,_d));
	description_pokemon->setPlainText(_d->val_pokedex().valeur(_pk.n_pk())->description(_pk.n_pk(),_langue,_d));
	QString fiche_description_objet_;
	if(_pk.objet()!=""){
		fiche_description_objet_=_d->val_objets().valeur(_pk.objet())->description(_langue,_d);
	}
	description_objet->setPlainText(fiche_description_objet_);
	typedef QPair<QString,QPair<uchar,uchar> > AttaquePP;
	foreach(AttaquePP a,_pk.attaques_apprises()){
		EtiquetteAttaque *etiquette_=new EtiquetteAttaque(a.first,a.first+" "+QString::number(a.second.first)+"/"+QString::number(a.second.second));
		connect(etiquette_,SIGNAL(clic(QString)),this,SLOT(maj_description(QString)));
		attaques->addWidget(etiquette_);
		liste_attaques.ajouter_cle_valeur(a.first,etiquette_);
		descriptions_attaques.ajouter_cle_valeur(a.first,_d->val_attaques().valeur(a.first)->description(a.first,_langue,_d));
	}
}

void FichePkUtEquipe::maj_description(const QString& _attaque){
	if(gestion_en_cours!=GestionEquipe::MOVE_TUTORS&&gestion_en_cours!=GestionEquipe::APPRENDRE_CS&&gestion_en_cours!=GestionEquipe::APPRENDRE_CT){
		if(gestion_en_cours!=GestionEquipe::BOOST&&gestion_en_cours!=GestionEquipe::SOIN&&gestion_en_cours!=GestionEquipe::BAIE){
			foreach(QString a,liste_attaques.cles()){
				liste_attaques.valeur(a)->maj_choix(false);
			}
			liste_attaques.valeur(_attaque)->maj_choix(true);
			foreach(QString a,liste_attaques.cles()){
				liste_attaques.valeur(a)->repaint();
			}
			description_attaque->setPlainText(descriptions_attaques.valeur(_attaque));
		}else{
			emit choix_attaque(_attaque,liste_attaques.cles().indexOf(_attaque));
		}
	}else{
		emit choix_attaque(_attaque,liste_attaques.cles().indexOf(_attaque));
	}
}

