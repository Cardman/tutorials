#include "ihm/hors_combat/fiches/fichepkutboite.h"
#include "ihm/combat/etiquettes/barre.h"
#include "ihm/combat/etiquettes/etiquetteattaque.h"
#include "serialisable/pokemon/pokemonutilisateur.h"
#include "base_donnees/donnees.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QSplitter>
#include <QScrollArea>
#include <QTextEdit>

FichePkUtBoite::FichePkUtBoite(){
	QVBoxLayout *lay_=new QVBoxLayout();
	QHBoxLayout *lay_infos_gener_=new QHBoxLayout();
	QVBoxLayout *lay_partiel_=new QVBoxLayout();
	image_pk=new QLabel();
	image_pk->setPixmap(QPixmap::fromImage(QImage()));
	lay_partiel_->addWidget(image_pk);
	ico_ball=new QLabel();
	lay_partiel_->addWidget(ico_ball);
	objet_pk=new QLabel();
	lay_partiel_->addWidget(objet_pk);
	lay_infos_gener_->addLayout(lay_partiel_);
	lay_partiel_=new QVBoxLayout();
	pseudo=new QLabel();
	pseudo->setText("");
	lay_partiel_->addWidget(pseudo);
	nom_pk=new QLabel();
	lay_partiel_->addWidget(nom_pk);
	pas_tete_equipe=new QLabel();
	pas_tete_equipe->setText("");
	lay_partiel_->addWidget(pas_tete_equipe);
	capacite=new QLabel();
	capacite->setText("");
	lay_partiel_->addWidget(capacite);
	lay_infos_gener_->addLayout(lay_partiel_);
	lay_partiel_=new QVBoxLayout();
	genre_pk=new QLabel();
	lay_partiel_->addWidget(genre_pk);
	niveau_pk=new QLabel();
	lay_partiel_->addWidget(niveau_pk);
	bonheur=new QLabel();
	bonheur->setText("");
	lay_partiel_->addWidget(bonheur);
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
	pts_pk=new QLabel();
	lay_->addWidget(pts_pk);
	barre_pts=new Barre(QColor(0,0,255,255));
	lay_->addWidget(barre_pts);
	groupe_=new QGroupBox("Attaques ayant des effets sur plusieurs tours");
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

void FichePkUtBoite::maj_fiche(const PokemonUtilisateur& _pk,int _langue,Donnees* _d){
	FichePokemon *f_pk_=_d->val_pokedex().valeur(_pk.n_pk());
	int num_=f_pk_->num();
	if(_pk.ball_capt()==""){
		ico_ball->setPixmap(QPixmap::fromImage(_d->val_images_objets().valeur("POKE_BALL")));
	}else{
		ico_ball->setPixmap(QPixmap::fromImage(_d->val_images_objets().valeur(_pk.ball_capt())));
	}
	image_pk->setPixmap(QPixmap::fromImage(_d->val_images_face_m().valeur(num_)));
	objet_pk->setText("Objet: "+_pk.objet());
	pseudo->setText(_pk.pseudo_pk());
	nom_pk->setText(_pk.n_pk());
	genre_pk->setText(QString(_pk.genre_pk()[0]));
	capacite->setText("Capacite :"+_pk.capacite_pk());
	pas_tete_equipe->setText("nombre de pas\nen tete\ndans l'equipe: "+QString::number(_pk.pas_tete_equipe()));
	bonheur->setText(QString::number(_pk.bonheur_pk()));
	niveau_pk->setText("N "+QString::number(_pk.niv_pk()));
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
	f_pk_=_d->val_pokedex().valeur(_pk.n_pk());
	uchar niv_=_pk.niv_pk();
	Taux nb_pts_total_dem_=f_pk_->diff_pts_niveaux(niv_+1);
	Taux nb_pts_restants_=nb_pts_total_dem_-_pk.exp_gagne();
	barre_pts->maj_pourcent(nb_pts_restants_/nb_pts_total_dem_);
	pts_pk->setText(nb_pts_restants_.evaluer(3)+"/"+nb_pts_total_dem_.evaluer(3));
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

void FichePkUtBoite::maj_description(const QString& _attaque){
	foreach(QString a,liste_attaques.cles()){
		liste_attaques.valeur(a)->maj_choix(false);
	}
	liste_attaques.valeur(_attaque)->maj_choix(true);
	foreach(QString a,liste_attaques.cles()){
		liste_attaques.valeur(a)->repaint();
	}
	description_attaque->setPlainText(descriptions_attaques.valeur(_attaque));
}
