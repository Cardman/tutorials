#include "base_donnees/evolution/evolutionpierreevolutive.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>
EvolutionPierreEvolutive::EvolutionPierreEvolutive(const QString& _pierre){
	pierre=_pierre;
}

QString EvolutionPierreEvolutive::nom_pierre()const{
	return pierre;
}

QString EvolutionPierreEvolutive::description(const QString& _base,const QString& _evo,int _langue)const{
	QStringList args_;
	args_<<Utilitaire::traduire(Import::_noms_pierres_evo_,pierre,_langue);
	return Evolution::description(_base,_evo,_langue)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_PIERRE").split("\t")[_langue],args_)+"\n";
}



