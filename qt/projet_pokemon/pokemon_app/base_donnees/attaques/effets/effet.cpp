#include "base_donnees/attaques/effets/effet.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QStringList>
const HashMap<QString,QString> Effet::_descriptions_effets_=Effet::init_descriptions_effets();

HashMap<QString,QString> Effet::init_descriptions_effets(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/descriptions_attaques_effets");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/descriptions_attaques_effets.txt");
#endif
	QStringList lignes_=contenu_.split("\n");
	HashMap<QString,QString> descriptions_effets_;
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		QString cle_=infos_.takeFirst();
		descriptions_effets_.ajouter_cle_valeur(cle_,infos_.join("\t"));
	}
	return descriptions_effets_;
}

Effet::Effet(bool _lanceur,QObject *parent):QObject(parent){
	lanceur=_lanceur;
}

void Effet::maj_lanceur(bool _lanceur){
	lanceur=_lanceur;
}

bool Effet::qui()const{
	return lanceur;
}

QString Effet::description(int _langue,Donnees*)const{
	if(lanceur){
		return Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_L").split("\t")[_langue],QStringList())+"\n";
	}
	return Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_A").split("\t")[_langue],QStringList())+"\n";
}


