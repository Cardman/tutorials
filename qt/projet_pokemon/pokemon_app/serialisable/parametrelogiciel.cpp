#include "serialisable/parametrelogiciel.h"
#include "base_donnees/donnees.h"
#include <QApplication>
#include <QDir>

ParametreLogiciel::ParametreLogiciel(Donnees *_d){
	if(_d){
		init(_d);
	}
}

void ParametreLogiciel::init(Donnees* _d){
	langue=_d->val_indice_francais();
	lancer_der_sauvegarde=false;
}

int ParametreLogiciel::val_langue()const{
	return langue;
}

QString ParametreLogiciel::val_der_sauvegarde()const{
	return der_sauvegarde;
}

bool ParametreLogiciel::val_lancer_der_sauvegarde()const{
	return lancer_der_sauvegarde;
}

int& ParametreLogiciel::val_langue(){
	return langue;
}

QString& ParametreLogiciel::val_der_sauvegarde(){
	return der_sauvegarde;
}

bool& ParametreLogiciel::val_lancer_der_sauvegarde(){
	return lancer_der_sauvegarde;
}

void ParametreLogiciel::sauvegarder(Donnees* _d)const{
	Flux f_;
	serialiser(f_);
	f_.ecrire(QApplication::applicationDirPath()+QDir::separator()+_d->constante_non_numerique("PARAM",_d->val_indice_francais()+1));
}

void ParametreLogiciel::charger(Donnees* _d){
	Flux f_;
	f_.lire(QApplication::applicationDirPath()+QDir::separator()+_d->constante_non_numerique("PARAM",_d->val_indice_francais()+1));
	deserialiser(f_);
}

void ParametreLogiciel::serialiser(Flux& _out)const{
	_out<<langue;
	_out<<lancer_der_sauvegarde;
	_out<<der_sauvegarde;
}

void ParametreLogiciel::deserialiser(Flux& _in){
	_in>>langue;
	_in>>lancer_der_sauvegarde;
	_in>>der_sauvegarde;
}

