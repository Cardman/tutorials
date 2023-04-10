#include "base_donnees/evolution/evolutionbonheur.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>
EvolutionBonheur::EvolutionBonheur():Evolution(){

}

QString EvolutionBonheur::description(const QString& _base,const QString& _evo,int _langue)const{
	QStringList args_;
	args_<<Import::_constantes_.filter(QRegExp("^EVO_BONHEUR\\t"))[0].split("\t")[1];
	return Evolution::description(_base,_evo,_langue)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_BON").split("\t")[_langue],args_)+"\n";
}



