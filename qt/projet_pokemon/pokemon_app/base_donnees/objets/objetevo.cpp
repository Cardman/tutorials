#include "base_donnees/objets/objetevo.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QRegExp>
const QStringList ObjetEvo::_descriptions_objets_evo_=ObjetEvo::init_descriptions_objets_evo();

QStringList ObjetEvo::init_descriptions_objets_evo(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_objet_evo_attacher");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_objet_evo_attacher.txt");
#endif
	return contenu_.split("\n",QString::SkipEmptyParts);
}

ObjetEvo::ObjetEvo(const QStringList& _pokemon_compatibles,int _prix_achat):Objet(){
	setAttachable();
	maj_prix_achat(_prix_achat);
	pokemon_compatibles=_pokemon_compatibles;
}

QStringList ObjetEvo::pks()const{
	return pokemon_compatibles;
}

QString ObjetEvo::description(int _langue,Donnees* _d)const{
	QString retour_;
	QString descriptions_objets_evo_;
	foreach(QString l,_descriptions_objets_evo_){
		QStringList infos_=l.split("\t");
		descriptions_objets_evo_+=infos_[_langue]+"\n";
	}
	descriptions_objets_evo_.chop(1);
	foreach(QString p,pokemon_compatibles){
		QStringList args_;
		args_<<Utilitaire::traduire(_d->val_noms_pk(),p,_langue);
		retour_+=Utilitaire::formatter(descriptions_objets_evo_,args_)+"\n";
	}
	retour_+="prix: "+QString::number(prix());
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}



