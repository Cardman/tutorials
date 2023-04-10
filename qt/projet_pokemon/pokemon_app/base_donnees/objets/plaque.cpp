#include "base_donnees/objets/plaque.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QRegExp>
const QStringList Plaque::_descriptions_plaques_=Plaque::init_descriptions_plaques();

QStringList Plaque::init_descriptions_plaques(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_plaques");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_plaques.txt");
#endif
	return contenu_.split("\n",QString::SkipEmptyParts);
}

Plaque::Plaque(const QString& _type_plaque,const QString& _type_pk,const Taux& _coeff,int _prix):Objet(){
	setAttachable();
	type_plaque=_type_plaque;
	type_pk=_type_pk;
	coeff=_coeff;
	maj_prix_achat(_prix);
}

QString Plaque::tp_pl()const{
	return type_plaque;
}

QString Plaque::tp_pk()const{
	return type_pk;
}

Taux Plaque::co()const{
	return coeff;
}

QString Plaque::description(int _langue,Donnees* _d)const{
	QString retour_;
	QStringList args_;
	args_<<Utilitaire::traduire(_d->val_noms_types(),type_plaque,_langue);
	args_<<coeff.chaine();
	args_<<Utilitaire::traduire(_d->val_noms_types(),type_pk,_langue);
	QString descriptions_plaques_;
	foreach(QString l,_descriptions_plaques_){
		QStringList infos_=l.split("\t");
		descriptions_plaques_+=infos_[_langue]+"\n";
	}
	descriptions_plaques_.chop(1);
	retour_+=Utilitaire::formatter(descriptions_plaques_,args_)+"\n";
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}



