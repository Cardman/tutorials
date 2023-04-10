#include "base_donnees/evolution/evolutionpierreevolutivegenre.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>
EvolutionPierreEvolutiveGenre::EvolutionPierreEvolutiveGenre(const QString& _genre,const QString& _pierre):EvolutionPierreEvolutive(_pierre){
	genre=_genre;
	if(genre.endsWith(" ")){
		genre.chop(1);
	}
}

QString EvolutionPierreEvolutiveGenre::gr()const{
	return genre;
}

QString EvolutionPierreEvolutiveGenre::description(const QString& _base,const QString& _evo,int _langue)const{
	QStringList args_;
	args_<<Utilitaire::traduire(Import::_noms_pierres_evo_,nom_pierre(),_langue);
	args_<<Utilitaire::traduire(Import::_constantes_non_num_,genre,_langue);
	return Evolution::description(_base,_evo,_langue)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_PIERRE_GEN").split("\t")[_langue],args_)+"\n";
	//return EvolutionGenre::description()+"\n"+EvolutionPierreEvolutive::description()
}


