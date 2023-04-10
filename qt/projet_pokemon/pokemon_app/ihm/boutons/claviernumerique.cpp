#include "ihm/boutons/claviernumerique.h"
#include "ihm/boutons/bouton.h"
#include "ihm/boutons/touche.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include "serialisable/math/taux.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

ClavierNumerique::ClavierNumerique(bool _entier,Donnees *_d){
	entier=_entier;
	texte="0";
	valeur=Entier(0);
	exp_taux=QRegExp(_d->constante("EXP_REG_TAUX_REL"));
	exp_entier=QRegExp(_d->constante("EXP_REG_ENTIER"));
	QVBoxLayout *lay_=new QVBoxLayout();
	lay_->setSpacing(0);
	champ=new Bouton();
	champ->maj_texte(texte);
	champ->maj_couleur_fond(QColor(255,255,255,255));
	champ->maj_couleur_texte(QColor(0,0,255,255));
	champ->maj_couleur_rectangle(QColor(0,0,255,255));
	lay_->addWidget(champ);
	int largeur_totale_=0;
	int hauteur_totale_=0;
	int hauteur_lay_=0;
	int h_=0;
	int largeur_=0;
	int hauteur_=0;
	QLabel *touches_=new QLabel();
	QVBoxLayout *lay_touches_=new QVBoxLayout();
	lay_touches_->setSpacing(0);
	QLabel *touches_h_=new QLabel();
	QHBoxLayout *lay_touches_h_=new QHBoxLayout();
	QList<QChar> chiffres_;
	for(int i=0;i<256;i++){
		if(QChar(i).isDigit()||QChar(i)=='-'||((QChar(i)=='.'||QChar(i)=='/')&&!entier)){
			chiffres_<<QChar(i);
		}
	}
	largeur_=Entier(chiffres_.size()).racine_abs(2).modulo_absolu_base();
	largeur_totale_=Utilitaire::max_min<int>(largeur_totale_,largeur_).first;
	hauteur_=chiffres_.size()/largeur_;
	if(largeur_*hauteur_<chiffres_.size()){
		hauteur_++;
	}
	hauteur_lay_=Utilitaire::max_min<int>(hauteur_lay_,hauteur_).first;
	hauteur_totale_+=hauteur_;
	QGridLayout *lay_chiffres_=new QGridLayout();
	lay_chiffres_->setSpacing(0);
	for(int i=0;i<hauteur_;i++){
		for(int j=0;j<largeur_;j++){
			int ind_=largeur_*i+j;
			if(ind_<chiffres_.size()){
				Touche *touche_=new Touche(chiffres_[ind_]);
				touche_->maj_couleur_fond(QColor(255,255,255,255));
				touche_->maj_couleur_texte(QColor(0,0,255,255));
				touche_->maj_couleur_rectangle(QColor(0,0,255,255));
				h_=touche_->height();
				connect(touche_,SIGNAL(clic(QString)),this,SLOT(maj_champ(QString)));
				lay_chiffres_->addWidget(touche_,i,j);
			}
		}
	}
	lay_touches_h_->addLayout(lay_chiffres_);
	lay_touches_h_->addStretch();
	touches_h_->setLayout(lay_touches_h_);
	touches_h_->setMinimumHeight(hauteur_lay_*h_);
	lay_touches_->addWidget(touches_h_);
	touches_->setLayout(lay_touches_);
	lay_->addWidget(touches_);
	if(entier){
		QHBoxLayout *dirs_2_=new QHBoxLayout();
		Bouton *bouton_=new Bouton();
		bouton_->maj_texte("<-");
		bouton_->maj_couleur_fond(QColor(255,255,255,255));
		bouton_->maj_couleur_texte(QColor(0,0,255,255));
		bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
		connect(bouton_,SIGNAL(clic()),this,SLOT(decrementer()));
		dirs_2_->addWidget(bouton_);
		bouton_=new Bouton();
		bouton_->maj_texte("->");
		bouton_->maj_couleur_fond(QColor(255,255,255,255));
		bouton_->maj_couleur_texte(QColor(0,0,255,255));
		bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
		connect(bouton_,SIGNAL(clic()),this,SLOT(incrementer()));
		dirs_2_->addWidget(bouton_);
		lay_->addLayout(dirs_2_);
	}
	QHBoxLayout *dirs_=new QHBoxLayout();
	Bouton *bouton_=new Bouton();
	bouton_->maj_texte("valider");
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	connect(bouton_,SIGNAL(clic()),this,SLOT(maj_valider()));
	dirs_->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("Effacer");
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	connect(bouton_,SIGNAL(clic()),this,SLOT(vider_champ()));
	dirs_->addWidget(bouton_);
	/*if(entier){
		bouton_=new Bouton();
		bouton_->maj_texte("<-");
		bouton_->maj_couleur_fond(QColor(255,255,255,255));
		bouton_->maj_couleur_texte(QColor(0,0,255,255));
		bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
		connect(bouton_,SIGNAL(clic()),this,SLOT(decrementer()));
		dirs_->addWidget(bouton_);
		bouton_=new Bouton();
		bouton_->maj_texte("->");
		bouton_->maj_couleur_fond(QColor(255,255,255,255));
		bouton_->maj_couleur_texte(QColor(0,0,255,255));
		bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
		connect(bouton_,SIGNAL(clic()),this,SLOT(incrementer()));
		dirs_->addWidget(bouton_);
	}*/
	lay_->addLayout(dirs_);
	setLayout(lay_);
	setMinimumSize(200,210);
}

void ClavierNumerique::incrementer(){
	++valeur;
	texte=valeur.chaine();
	champ->maj_texte(texte);
	champ->repaint();
}

void ClavierNumerique::decrementer(){
	--valeur;
	texte=valeur.chaine();
	champ->maj_texte(texte);
	champ->repaint();
}

void ClavierNumerique::maj_valider(){
	if(entier){
		if(exp_entier.exactMatch(texte)||texte=="0"){
			emit valider(valeur);
		}else{
			return;
		}
	}else if(exp_entier.exactMatch(texte)||texte=="0"){
		emit valider(Entier(texte));
	}else if(exp_taux.exactMatch(texte)||texte=="0"){
		emit valider(Taux(texte));
	}
}

void ClavierNumerique::vider_champ(){
	texte="0";
	if(entier){
		valeur=Entier(0);
	}
	champ->maj_texte(texte);
	champ->repaint();
}

QString ClavierNumerique::texte_ecrit()const{
	return texte;
}

void ClavierNumerique::maj_texte(const QString& _texte){
	texte=_texte;
	if(entier&&(exp_entier.exactMatch(texte)||texte=="0")){
		valeur=Entier(texte);
	}
	champ->maj_texte(texte);
	champ->repaint();
}

void ClavierNumerique::maj_champ(const QString& _carac){
	if(texte=="0"&&_carac[0]>='0'&&_carac[0]<='9'){
		texte=texte;
		valeur*=10;
		valeur+=_carac.toInt();
	}else if(entier&&exp_entier.exactMatch(texte+_carac)){
		texte+=_carac;
		valeur*=10;
		valeur+=_carac.toInt();
	}
	champ->maj_texte(texte);
	champ->repaint();
}



