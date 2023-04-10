#include "base_donnees/objets/pierreevo.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QRegExp>
const QStringList PierreEvo::_descriptions_pierres_evo_=PierreEvo::init_descriptions_pierres_evo();

QStringList PierreEvo::init_descriptions_pierres_evo(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_pierre_evo");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_pierre_evo.txt");
#endif
	return contenu_.split("\n",QString::SkipEmptyParts);
}

PierreEvo::PierreEvo(const QStringList& _pokemon_compatibles,int _prix_achat):Objet(){
	pokemon_compatibles=_pokemon_compatibles;
	maj_prix_achat(_prix_achat);
}

QStringList PierreEvo::pks()const{
	return pokemon_compatibles;
}

QString PierreEvo::description(int _langue,Donnees* _d)const{
	QString retour_;
	QString descriptions_pierres_evo_;
	foreach(QString l,_descriptions_pierres_evo_){
		QStringList infos_=l.split("\t");
		descriptions_pierres_evo_+=infos_[_langue]+"\n";
	}
	descriptions_pierres_evo_.chop(1);
	foreach(QString p,pokemon_compatibles){
		QStringList args_;
		args_<<Utilitaire::traduire(_d->val_noms_pk(),p,_langue);
		retour_+=Utilitaire::formatter(descriptions_pierres_evo_,args_)+"\n";
	}
	retour_+="prix: "+QString::number(prix());
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}



