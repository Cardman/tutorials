#include "base_donnees/attaques/effets/effettauxpvpvmax.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
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

QString EffetTauxPVPVMax::description(int _langue,Donnees *_d)const{
	QString retour_=Effet::description(_langue,_d);
	QString cle_;
	QStringList args_;
	args_<<tx().chaine();
	if(qui()){
		args_<<Utilitaire::traduire(_d->val_constantes_non_num(),"LANCEUR_DESCR",_langue+1);
	}else{
		args_<<Utilitaire::traduire(_d->val_constantes_non_num(),"CIBLE_DESCR",_langue+1);
	}
	if(climat==""){
		cle_="EFFET_TAUX_PV_MAX_SANS";
	}else{
		cle_="EFFET_TAUX_PV_MAX";
		args_<<Utilitaire::traduire(_d->val_noms_climats(),climat,_langue);
	}
	retour_+=Utilitaire::formatter(_descriptions_effets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	return retour_;
}



