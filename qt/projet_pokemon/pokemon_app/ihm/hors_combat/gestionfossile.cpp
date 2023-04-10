#include "ihm/hors_combat/gestionfossile.h"
#include "ihm/boutons/boutonobjet.h"
#include "base_donnees/donnees.h"
#include "serialisable/utilisateur/inventaire.h"
#include <QScrollArea>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QGroupBox>

GestionFossile::GestionFossile(Donnees* _d){
	donnees=_d;
	QScrollArea *asc_=new QScrollArea();
	objets_particuliers=new QGroupBox();
	objets=new QVBoxLayout();
	objets->addWidget(new QLabel("Icone\tNom\tQuantite"));
	objets_particuliers->setLayout(objets);
	asc_->setWidget(objets_particuliers);
	addWidget(asc_);
	QLabel *conteneur_=new QLabel();
	QVBoxLayout *lay_=new QVBoxLayout();
	description=new QTextEdit();
	lay_->addWidget(description);
	conteneur_->setLayout(lay_);
	addWidget(conteneur_);
}

void GestionFossile::maj_fiche(const HashMap<QString,uchar>& _fossiles,Inventaire& _inv,int _langue,int _pk_equipe,int _max_pk_equipe){
	langue=_langue;
	fossiles=_fossiles;
	int nb_=objets->count();
	for(int i=1;i<nb_;i++){
		objets->itemAt(i)->widget()->deleteLater();
	}
	for(int i=1;i<nb_;i++){
		objets->removeItem(objets->itemAt(1));
	}
	objets->itemAt(0)->widget()->setFixedHeight(20);
	objets->itemAt(0)->widget()->setMinimumWidth(250);
	int h_=0;
	int l_=250;
	objets_particuliers->setTitle("Nombre de places restantes: "+QString::number(_max_pk_equipe-_pk_equipe));
	foreach(QString s,_fossiles.cles()){
		if(_fossiles.valeur(s)==0){
			continue;
		}
		fiche_description.ajouter_cle_valeur(s,donnees->val_objets().valeur(s)->description(langue,donnees));
		BoutonObjet *bouton_=new BoutonObjet(s,0,_inv,donnees);
		bouton_->maj_couleur_fond(QColor(255,255,255,255));
		bouton_->maj_couleur_texte(QColor(0,0,255,255));
		bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
		h_=bouton_->height();
		l_=Utilitaire::max_min<int>(l_,bouton_->minimumWidth()).first;
		connect(bouton_,SIGNAL(clic(QString)),this,SLOT(maj_objet(QString)));
		objets->addWidget(bouton_);
	}
	if(objets->count()>1){
		objets_particuliers->setFixedHeight(50+(objets->count()-1)*h_);
		objets_particuliers->setMinimumWidth(l_);
	}else{
		objets_particuliers->setFixedHeight(50);
		objets_particuliers->setMinimumWidth(l_);
	}
}

void GestionFossile::maj_objet(const QString& _objet){
	description->setPlainText(fiche_description.valeur(_objet));
	emit tentative_vivre_fossile(_objet);
}
