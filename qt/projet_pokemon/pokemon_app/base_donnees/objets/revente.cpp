#include "base_donnees/objets/revente.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QRegExp>
const QStringList Revente::_descriptions_renventes_=Revente::init_descriptions_renventes();

QStringList Revente::init_descriptions_renventes(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_objet_reventes");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_objet_reventes.txt");
#endif
	return contenu_.split("\n",QString::SkipEmptyParts);
}

Revente::Revente(int _prix_vente):Objet(){
	maj_prix_achat(_prix_vente);
}

QString Revente::description(int _langue,Donnees *)const{
	QString retour_;
	QStringList args_;
	args_<<QString::number(prix());
	QString descriptions_renventes_;
	foreach(QString l,_descriptions_renventes_){
		QStringList infos_=l.split("\t");
		descriptions_renventes_+=infos_[_langue]+"\n";
	}
	descriptions_renventes_.chop(1);
	retour_+=Utilitaire::formatter(descriptions_renventes_,args_)+"\n";
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}



