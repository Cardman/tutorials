#include "base_donnees/attaques/effets/effettauxpvrestants.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QStringList>
EffetTauxPVRestants::EffetTauxPVRestants(const QString& _ligne):EffetTaux(_ligne){
	maj_lanceur(_ligne.contains("[L,"));
}

QString EffetTauxPVRestants::description(int _langue,Donnees *_d)const{
	QString retour_=Effet::description(_langue,_d);
	QString cle_;
	QStringList args_;
	args_<<tx().chaine();
	if(qui()){
		args_<<Utilitaire::traduire(_d->val_constantes_non_num(),"LANCEUR_DESCR",_langue+1);
	}else{
		args_<<Utilitaire::traduire(_d->val_constantes_non_num(),"CIBLE_DESCR",_langue+1);
	}
	cle_="EFFET_TAUX_PV_RESTANTS";
	retour_+=Utilitaire::formatter(_descriptions_effets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	return retour_;
}



