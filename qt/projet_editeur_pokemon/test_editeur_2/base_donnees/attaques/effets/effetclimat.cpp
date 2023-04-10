#include "base_donnees/attaques/effets/effetclimat.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>
EffetClimat::EffetClimat(const QString& _ligne){
	nom_climat=_ligne.split("[")[1].split("]")[0];
}

QString EffetClimat::cl()const{
	return nom_climat;
}

QString EffetClimat::description(int _langue)const{
	QString retour_;
	QStringList args_;
	args_<<Utilitaire::traduire(Import::_noms_climats_,nom_climat,_langue);
	retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_CLIMAT").split("\t")[_langue],args_)+"\n";
	return retour_;
}



