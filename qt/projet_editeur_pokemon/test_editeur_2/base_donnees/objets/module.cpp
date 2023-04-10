#include "base_donnees/objets/module.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QRegExp>
const QStringList Module::_descriptions_modules_=Module::init_descriptions_modules();

QStringList Module::init_descriptions_modules(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_modules");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_modules.txt");
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

Module::Module(const QString& _type,int _prix_vente):Objet(){
	maj_prix_achat(_prix_vente);
	type_techno_buster=_type;
}

QString Module::description(int _langue)const{
	QString retour_;
	QStringList args_;
	args_<<Utilitaire::traduire(Import::_noms_types_,type_techno_buster,_langue);
	retour_+=Utilitaire::formatter(_descriptions_modules_[_langue],args_)+"\n";
	retour_+="prix: "+QString::number(prix());
	return retour_;
}



