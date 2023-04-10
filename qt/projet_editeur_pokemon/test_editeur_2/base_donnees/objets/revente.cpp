#include "base_donnees/objets/revente.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QRegExp>
const QStringList Revente::_descriptions_renventes_=Revente::init_descriptions_renventes();

QStringList Revente::init_descriptions_renventes(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_objet_reventes");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_objet_reventes.txt");
#endif
	QStringList lignes_=contenu_.split("\n",QString::SkipEmptyParts);
	QStringList descriptions_objets_;
	int nb_langues_=1;//Import::_langues_.total();
	for(int i=0;i<nb_langues_;i++){
		descriptions_objets_<<"";
	}
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		for(int i=0;i<nb_langues_;i++){
			descriptions_objets_[i]+=infos_[i]+"\n";
		}
	}
	for(int i=0;i<nb_langues_;i++){
		descriptions_objets_[i].chop(1);
	}
	return descriptions_objets_;
}

Revente::Revente(int _prix_vente):Objet(){
	maj_prix_achat(_prix_vente);
}

QString Revente::description(int _langue)const{
	QString retour_;
	QStringList args_;
	args_<<QString::number(prix());
	retour_+=Utilitaire::formatter(_descriptions_renventes_[_langue],args_)+"\n";
	return retour_;
}



