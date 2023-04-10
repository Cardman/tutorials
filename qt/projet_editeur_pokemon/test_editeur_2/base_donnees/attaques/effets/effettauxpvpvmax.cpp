#include "base_donnees/attaques/effets/effettauxpvpvmax.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>

EffetTauxPVPVMax::EffetTauxPVPVMax(const QString& _ligne):EffetTaux(_ligne){
	maj_lanceur(_ligne.contains("[L,"));
	climat=_ligne.split(",")[2].split("]")[0];
	if(climat=="SANS"){
		climat="";
	}
}

QString EffetTauxPVPVMax::cl()const{
	return climat;
}

QString EffetTauxPVPVMax::description(int _langue)const{
	QString retour_;
	QString cle_;
	QStringList args_;
	args_<<tx().chaine();
	if(qui()){
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,"LANCEUR_DESCR",_langue+1);
	}else{
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,"CIBLE_DESCR",_langue+1);
	}
	if(climat==""){
		cle_="EFFET_TAUX_PV_MAX_SANS";
	}else{
		cle_="EFFET_TAUX_PV_MAX";
		args_<<Utilitaire::traduire(Import::_noms_climats_,climat,_langue);
	}
	retour_+=Utilitaire::formatter(_descriptions_effets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	return retour_;
}



