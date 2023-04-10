#include "base_donnees/personnages/personnage.h"
#include <QStringList>

Personnage::Personnage(const QStringList& _lignes,QObject *_parent):QObject(_parent){
	nom=_lignes[0].split(">")[1].split("<")[0];
	nom_miniature=_lignes[1].split(">")[1].split("<")[0];
	QStringList orient_=_lignes[2].split(">")[1].split("<")[0].split(",");
	orientation.first=orient_[0].toInt();
	orientation.second=orient_[1].toInt();
}

QStringList Personnage::sous_attributs(const QStringList& attributs,const QString& fin){
	int i_=0;
	int nb_attr_=attributs.size();
	while(i_<nb_attr_){
		if(attributs[i_].contains(fin)){
			break;
		}
		i_++;
	}
	return attributs.mid(0,i_+1);
}

QString Personnage::nom_p()const{
	return nom;
}

QString Personnage::miniature()const{
	return nom_miniature;
}

QPair<int,int> Personnage::orient()const{
	return orientation;
}

