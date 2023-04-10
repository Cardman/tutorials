#include "ihm/boutons/clavier.h"
#include "ihm/boutons/bouton.h"
#include "ihm/boutons/touche.h"
#include "serialisable/math/entier.h"
#include "autre/utilitaire.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

Clavier::Clavier(){
	QVBoxLayout *lay_=new QVBoxLayout();
	indice=0;
	champ=new Bouton();
	champ->maj_texte(texte);
	champ->maj_couleur_fond(QColor(255,255,255,255));
	champ->maj_couleur_texte(QColor(0,0,255,255));
	champ->maj_couleur_rectangle(QColor(0,0,255,255));
	lay_->addWidget(champ);
	position=new Bouton();
	position->maj_texte(QString::number(indice));
	position->maj_couleur_fond(QColor(255,255,255,255));
	position->maj_couleur_texte(QColor(0,0,255,255));
	position->maj_couleur_rectangle(QColor(0,0,255,255));
	lay_->addWidget(position);
	QList<QChar> lettres_maj_;
	for(int i=0;i<256;i++){
		if(QChar(i).isLetter()&&QChar(i).isUpper()){
			lettres_maj_<<QChar(i);
		}
	}
	int largeur_totale_=0;
	int hauteur_totale_=0;
	int hauteur_lay_=0;
	int h_=0;
	int largeur_=Entier(lettres_maj_.size()).racine_abs(2).modulo_absolu_base();
	largeur_totale_=Utilitaire::max_min<int>(largeur_totale_,largeur_).first;
	int hauteur_=lettres_maj_.size()/largeur_;
	if(largeur_*hauteur_<lettres_maj_.size()){
		hauteur_++;
	}
	hauteur_lay_=Utilitaire::max_min<int>(hauteur_lay_,hauteur_).first;
	hauteur_totale_+=hauteur_;
	QLabel *touches_=new QLabel();
	QVBoxLayout *lay_touches_=new QVBoxLayout();
	QLabel *touches_h_=new QLabel();
	QHBoxLayout *lay_touches_h_=new QHBoxLayout();
	QGridLayout *lay_lettres_maj_=new QGridLayout();
	lay_lettres_maj_->setSpacing(0);
	for(int i=0;i<hauteur_;i++){
		for(int j=0;j<largeur_;j++){
			int ind_=largeur_*i+j;
			if(ind_<lettres_maj_.size()){
				Touche *touche_=new Touche(lettres_maj_[ind_]);
				touche_->maj_couleur_fond(QColor(255,255,255,255));
				touche_->maj_couleur_texte(QColor(0,0,255,255));
				touche_->maj_couleur_rectangle(QColor(0,0,255,255));
				h_=touche_->height();
				connect(touche_,SIGNAL(clic(QString)),this,SLOT(maj_champ(QString)));
				lay_lettres_maj_->addWidget(touche_,i,j);
			}
		}
	}
	lay_touches_h_->addLayout(lay_lettres_maj_);
	QList<QChar> lettres_min_;
	for(int i=0;i<256;i++){
		if(QChar(i).isLetter()&&QChar(i).isLower()){
			lettres_min_<<QChar(i);
		}
	}
	largeur_=Entier(lettres_min_.size()).racine_abs(2).modulo_absolu_base();
	largeur_totale_=Utilitaire::max_min<int>(largeur_totale_,largeur_).first;
	hauteur_=lettres_min_.size()/largeur_;
	if(largeur_*hauteur_<lettres_min_.size()){
		hauteur_++;
	}
	hauteur_lay_=Utilitaire::max_min<int>(hauteur_lay_,hauteur_).first;
	hauteur_totale_+=hauteur_;
	QGridLayout *lay_lettres_min_=new QGridLayout();
	lay_lettres_min_->setSpacing(0);
	for(int i=0;i<hauteur_;i++){
		for(int j=0;j<largeur_;j++){
			int ind_=largeur_*i+j;
			if(ind_<lettres_min_.size()){
				Touche *touche_=new Touche(lettres_min_[ind_]);
				touche_->maj_couleur_fond(QColor(255,255,255,255));
				touche_->maj_couleur_texte(QColor(0,0,255,255));
				touche_->maj_couleur_rectangle(QColor(0,0,255,255));
				h_=touche_->height();
				connect(touche_,SIGNAL(clic(QString)),this,SLOT(maj_champ(QString)));
				lay_lettres_min_->addWidget(touche_,i,j);
			}
		}
	}
	lay_touches_h_->addLayout(lay_lettres_min_);
	QList<QChar> chiffres_;
	for(int i=0;i<256;i++){
		if(QChar(i).isDigit()){
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
	QList<QChar> espaces_;
	for(int i=0;i<256;i++){
		if(QChar(i).isPunct()||i==' '){
			espaces_<<QChar(i);
		}
	}
	largeur_=Entier(espaces_.size()).racine_abs(2).modulo_absolu_base();
	largeur_totale_=Utilitaire::max_min<int>(largeur_totale_,largeur_).first;
	hauteur_=espaces_.size()/largeur_;
	if(largeur_*hauteur_<espaces_.size()){
		hauteur_++;
	}
	hauteur_lay_=Utilitaire::max_min<int>(hauteur_lay_,hauteur_).first;
	hauteur_totale_+=hauteur_;
	QGridLayout *lay_espaces_=new QGridLayout();
	lay_espaces_->setSpacing(0);
	for(int i=0;i<hauteur_;i++){
		for(int j=0;j<largeur_;j++){
			int ind_=largeur_*i+j;
			if(ind_<espaces_.size()){
				Touche *touche_=new Touche(espaces_[ind_]);
				touche_->maj_couleur_fond(QColor(255,255,255,255));
				touche_->maj_couleur_texte(QColor(0,0,255,255));
				touche_->maj_couleur_rectangle(QColor(0,0,255,255));
				h_=touche_->height();
				connect(touche_,SIGNAL(clic(QString)),this,SLOT(maj_champ(QString)));
				lay_espaces_->addWidget(touche_,i,j);
			}
		}
	}
	lay_touches_h_->addLayout(lay_espaces_);
	lay_touches_h_->addStretch();
	touches_h_->setLayout(lay_touches_h_);
	lay_touches_->addWidget(touches_h_);
	touches_->setLayout(lay_touches_);
	touches_h_->setFixedHeight(hauteur_lay_*h_);
	lay_->addWidget(touches_);
	QVBoxLayout *dirs_=new QVBoxLayout();
	QHBoxLayout *lay_dirs_=new QHBoxLayout();
	Bouton *bouton_=new Bouton();
	bouton_->maj_texte("gauche");
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	connect(bouton_,SIGNAL(clic()),this,SLOT(gauche()));
	lay_dirs_->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("droite");
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	connect(bouton_,SIGNAL(clic()),this,SLOT(droite()));
	lay_dirs_->addWidget(bouton_);
	dirs_->addLayout(lay_dirs_);
	lay_dirs_=new QHBoxLayout();
	bouton_=new Bouton();
	bouton_->maj_texte("supprimer a gauche");
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	connect(bouton_,SIGNAL(clic()),this,SLOT(supprimer_gauche()));
	lay_dirs_->addWidget(bouton_);
	bouton_=new Bouton();
	bouton_->maj_texte("supprimer a droite");
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	connect(bouton_,SIGNAL(clic()),this,SLOT(supprimer_droite()));
	lay_dirs_->addWidget(bouton_);
	dirs_->addLayout(lay_dirs_);
	bouton_=new Bouton();
	bouton_->maj_texte("valider");
	bouton_->maj_couleur_fond(QColor(255,255,255,255));
	bouton_->maj_couleur_texte(QColor(0,0,255,255));
	bouton_->maj_couleur_rectangle(QColor(0,0,255,255));
	connect(bouton_,SIGNAL(clic()),this,SLOT(maj_valider()));
	dirs_->addWidget(bouton_);
	lay_->addLayout(dirs_);
	setLayout(lay_);
	setFixedSize(520,500);
}

void Clavier::maj_valider(){
	emit valider(texte);
}

void Clavier::vider_champ(){
	indice=0;
	position->maj_texte(QString::number(indice));
	position->repaint();
	texte="";
	champ->maj_texte(texte);
	champ->repaint();
}

QString Clavier::texte_ecrit()const{
	return texte;
}

void Clavier::gauche(){
	if(indice>0){
		indice--;
		position->maj_texte(QString::number(indice));
		position->repaint();
	}
}

void Clavier::droite(){
	if(indice<texte.size()){
		indice++;
		position->maj_texte(QString::number(indice));
		position->repaint();
	}
}

void Clavier::supprimer_droite(){
	if(indice<texte.size()){
		texte.remove(indice,1);
		champ->maj_texte(texte);
		champ->repaint();
	}
}

void Clavier::maj_champ(const QString& _carac){
	texte.insert(indice,_carac);
	indice++;
	position->maj_texte(QString::number(indice));
	position->repaint();
	champ->maj_texte(texte);
	champ->repaint();
}

void Clavier::supprimer_gauche(){
	if(indice>0){
		texte.remove(indice-1,1);
		champ->maj_texte(texte);
		champ->repaint();
		indice--;
		position->maj_texte(QString::number(indice));
		position->repaint();
	}
}
