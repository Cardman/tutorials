#include "base_donnees/attaques/effets/effettauxpvrestants.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>
EffetTauxPVRestants::EffetTauxPVRestants(const QString& _ligne):EffetTaux(_ligne){
	maj_lanceur(_ligne.contains("[L,"));
}

QString EffetTauxPVRestants::description(int _langue)const{
	QString retour_;
	QString cle_;
	QStringList args_;
	args_<<tx().chaine();
	if(qui()){
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,"LANCEUR_DESCR",_langue+1);
	}else{
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,"CIBLE_DESCR",_langue+1);
	}
	cle_="EFFET_TAUX_PV_RESTANTS";
	retour_+=Utilitaire::formatter(_descriptions_effets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	return retour_;
}


