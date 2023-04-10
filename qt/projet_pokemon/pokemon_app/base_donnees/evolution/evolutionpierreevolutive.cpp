#include "base_donnees/evolution/evolutionpierreevolutive.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QStringList>
EvolutionPierreEvolutive::EvolutionPierreEvolutive(const QString& _pierre){
	pierre=_pierre;
}

QString EvolutionPierreEvolutive::nom_pierre()const{
	return pierre;
}

QString EvolutionPierreEvolutive::description(const QString& _base,const QString& _evo,int _langue,Donnees* _d)const{
	QStringList args_;
	args_<<Utilitaire::traduire(_d->val_noms_pierres_evo(),pierre,_langue);
	return Evolution::description(_base,_evo,_langue,_d)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_PIERRE").split("\t")[_langue],args_)+"\n";
}



