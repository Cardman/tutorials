#include "base_donnees/attaques/effets/effetmultpuissattaque.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QStringList>
EffetMultPuissAttaque::EffetMultPuissAttaque(const QString& _ligne){
	type=_ligne.split("[")[1].split(",")[0];
	coeff=Taux::parse_taux(_ligne.split("]")[0].split(",")[1]);
	non_subi=_ligne.contains("_2[");
	maj_lanceur(_ligne.contains("[L,"));
}

QString EffetMultPuissAttaque::tp()const{
	return type;
}

Taux EffetMultPuissAttaque::co()const{
	return coeff;
}

bool EffetMultPuissAttaque::n_subi()const{
	return non_subi;
}

QString EffetMultPuissAttaque::description(int _langue,Donnees *_d)const{
	QString retour_=Effet::description(_langue,_d);
	QStringList args_;
	if(non_subi){
		args_<<Utilitaire::traduire(_d->val_noms_types(),type,_langue);
		args_<<coeff.chaine();
		retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_MULT_PUISS_ATT_2").split("\t")[_langue],args_)+"\n";
	}else{
		args_<<Utilitaire::traduire(_d->val_noms_types(),type,_langue);
		args_<<coeff.chaine();
		retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_MULT_PUISS_ATT").split("\t")[_langue],args_)+"\n";
	}
	return retour_;
}



