#include "base_donnees/objets/module.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QRegExp>
const QStringList Module::_descriptions_modules_=Module::init_descriptions_modules();

QStringList Module::init_descriptions_modules(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_modules");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_modules.txt");
#endif
	return contenu_.split("\n",QString::SkipEmptyParts);
}

Module::Module(const QString& _type,int _prix_vente):Objet(){
	maj_prix_achat(_prix_vente);
	type_techno_buster=_type;
}

QString Module::type()const{
	return type_techno_buster;
}

QString Module::description(int _langue,Donnees *_d)const{
	QString retour_;
	QStringList args_;
	args_<<Utilitaire::traduire(_d->val_noms_types(),type_techno_buster,_langue);
	QString descriptions_modules_;
	foreach(QString l,_descriptions_modules_){
		QStringList infos_=l.split("\t");
		descriptions_modules_+=infos_[_langue]+"\n";
	}
	descriptions_modules_.chop(1);
	retour_+=Utilitaire::formatter(descriptions_modules_,args_)+"\n";
	retour_+="prix: "+QString::number(prix());
	return retour_;
}



