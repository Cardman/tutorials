#include "base_donnees/attaques/effets/effettauxdegats.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QStringList>
EffetTauxDegats::EffetTauxDegats(const QString& _ligne):EffetTaux(_ligne){
	maj_lanceur(_ligne.contains("[L,"));
}

QString EffetTauxDegats::description(int _langue,Donnees *_d)const{
	QString retour_=Effet::description(_langue,_d);
	QStringList args_;
	if(qui()){
		args_<<Utilitaire::traduire(_d->val_constantes_non_num(),"LANCEUR_MAJ_DESCR",_langue+1);
	}else{
		args_<<Utilitaire::traduire(_d->val_constantes_non_num(),"CIBLE_MAJ_DESCR",_langue+1);
	}
	args_<<tx().chaine();
	retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_TAUX_DEGATS").split("\t")[_langue],args_)+"\n";
	return retour_;
}



