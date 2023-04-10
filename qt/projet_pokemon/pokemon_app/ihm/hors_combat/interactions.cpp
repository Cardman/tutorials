#include "ihm/hors_combat/interactions.h"
#include "ihm/boutons/bouton.h"
#include "base_donnees/donnees.h"
#include "serialisable/partie/partie.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

Interactions::Interactions(Donnees* _d){
	int largeur_ecran_=(int)(_d->constante_numerique("ESPACE_GAUCHE_ECRAN")+Taux(1)+_d->constante_numerique("ESPACE_DROITE_ECRAN"));
	setFixedWidth(largeur_ecran_*32);
	setMinimumHeight(100);
	QHBoxLayout *lay_=new QHBoxLayout();
	commentaire=new QLabel();
	lay_->addWidget(commentaire);
	lay_boutons=new QVBoxLayout();
	lay_->addLayout(lay_boutons);
	setLayout(lay_);
}

void Interactions::maj_interaction(uchar _action,const QStringList& _noms){
	foreach(uchar i,boutons.cles()){
		boutons.valeur(i)->deleteLater();
		lay_boutons->removeWidget(boutons.valeur(i));
	}
	boutons.tout_supprimer();
	act_boutons.tout_supprimer();
	if(_action==Partie::PK_LEG||_action==Partie::DON_PK||_action==Partie::DIFF||_action==Partie::OBJ_RAMAS||_action==Partie::DON_OBJET||_action==Partie::DRESSEUR||_action==Partie::FOSSILE||_action==Partie::JOUEUR){
		Bouton *bouton_=new Bouton(_noms[0]);
		bouton_->maj_couleur_fond(QColor(255,255,255,255));
		bouton_->maj_couleur_texte(QColor(0,0,255,255));
		bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
		connect(bouton_,SIGNAL(clic(QString)),this,SLOT(cliquer(QString)));
		lay_boutons->addWidget(bouton_);
		boutons.ajouter_cle_valeur(_action,bouton_);
		act_boutons.ajouter_cle_valeur(_action,_noms[0]);
	}else if(_action==Partie::PECHE||_action==Partie::PENSION||_action==Partie::ACHATS||_action==Partie::ACHATS_CT||_action==Partie::VOL){
		int i_=0;
		foreach(QString c,_noms){
			Bouton *bouton_=new Bouton(c);
			bouton_->maj_couleur_fond(QColor(255,255,255,255));
			bouton_->maj_couleur_texte(QColor(0,0,255,255));
			bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
			connect(bouton_,SIGNAL(clic(QString)),this,SLOT(cliquer(QString)));
			lay_boutons->addWidget(bouton_);
			boutons.ajouter_cle_valeur(i_+_action,bouton_);
			act_boutons.ajouter_cle_valeur(i_+_action,c);
			i_++;
		}
	}
}

void Interactions::raz_interaction(){
	foreach(uchar i,boutons.cles()){
		boutons.valeur(i)->deleteLater();
		lay_boutons->removeWidget(boutons.valeur(i));
	}
	boutons.tout_supprimer();
	act_boutons.tout_supprimer();
}

void Interactions::maj_commentaire(const QString& _commentaire){
	commentaire->setText(_commentaire);
}

void Interactions::cliquer(const QString& _texte){
	if(act_boutons.total()==0){
		return;
	}
	uchar sous_action_=act_boutons.cles(_texte)[0]-act_boutons.cles()[0];
	if(act_boutons.cles().size()>1){
		emit clic(act_boutons.cles()[0],sous_action_,_texte);
	}else{
		emit clic(act_boutons.cles(_texte)[0],sous_action_,_texte);
	}
}
