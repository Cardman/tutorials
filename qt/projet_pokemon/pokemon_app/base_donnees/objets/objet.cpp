#include "base_donnees/objets/objet.h"


Objet::Objet(QObject *_parent):QObject(_parent){
	attachable=false;
	//achetable=false
	//effets=_effets
}

	/*QStringList Objet::effets_objet()const{
		return effets
	}*/

void Objet::setAttachable(){
	attachable=true;
}

bool Objet::estAttachable()const{
	return attachable;
}

	/*void Objet::setAchetable(){
		achetable=true
	}*/

bool Objet::estAchetable()const{
	return prix_achat>0;
}

int Objet::prix()const{
	return prix_achat;
}

void Objet::maj_prix_achat(int _prix_achat){
	prix_achat=_prix_achat;
}



