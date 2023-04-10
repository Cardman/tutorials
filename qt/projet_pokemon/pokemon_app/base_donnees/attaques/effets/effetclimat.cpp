#include "base_donnees/attaques/effets/effetclimat.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QStringList>
EffetClimat::EffetClimat(const QString& _ligne){
	nom_climat=_ligne.split("[")[1].split("]")[0];
}

QString EffetClimat::cl()const{
	return nom_climat;
}

QString EffetClimat::description(int _langue,Donnees *_d)const{
	QString retour_=Effet::description(_langue,_d);
	QStringList args_;
	args_<<Utilitaire::traduire(_d->val_noms_climats(),nom_climat,_langue);
	retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_CLIMAT").split("\t")[_langue],args_)+"\n";
	return retour_;
}



