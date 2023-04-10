#include "base_donnees/attaques/effets/effettauxdegats.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>
EffetTauxDegats::EffetTauxDegats(const QString& _ligne):EffetTaux(_ligne){
	maj_lanceur(_ligne.contains("[L,"));
}

QString EffetTauxDegats::description(int _langue)const{
	QString retour_;
	QStringList args_;
	if(qui()){
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,"LANCEUR_MAJ_DESCR",_langue+1);
	}else{
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,"CIBLE_MAJ_DESCR",_langue+1);
	}
	args_<<tx().chaine();
	retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_TAUX_DEGATS").split("\t")[_langue],args_)+"\n";
	return retour_;
}



