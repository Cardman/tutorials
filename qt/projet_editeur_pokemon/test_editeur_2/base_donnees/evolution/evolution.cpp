#include "base_donnees/evolution/evolution.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>

const HashMap<QString,QString> Evolution::_descriptions_evos_=Evolution::init_descriptions_evos();

HashMap<QString,QString> Evolution::init_descriptions_evos(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/descriptions_evolutions");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/descriptions_evolutions.txt");
#endif
	QStringList lignes_=contenu_.split("\n",QString::SkipEmptyParts);
	HashMap<QString,QString> descriptions_evos_;
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		QString cle_=infos_.takeFirst();
		descriptions_evos_.ajouter_cle_valeur(cle_,infos_.join("\t"));
	}
	return descriptions_evos_;
}

Evolution::Evolution(QObject *parent):QObject(parent){

}

QString Evolution::description(const QString& _base,const QString& _evo,int _langue)const{
	QString base_=Utilitaire::traduire(Import::_noms_pk_,_base,_langue);
	QString evo_=Utilitaire::traduire(Import::_noms_pk_,_evo,_langue);
	QStringList args_;
	args_<<base_;
	args_<<evo_;
	return Utilitaire::formatter(_descriptions_evos_.valeur("EVO").split("\t")[_langue],args_);
}



