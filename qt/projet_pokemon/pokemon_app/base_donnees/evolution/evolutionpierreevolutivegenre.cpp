#include "base_donnees/evolution/evolutionpierreevolutivegenre.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
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

QString EvolutionPierreEvolutiveGenre::description(const QString& _base,const QString& _evo,int _langue,Donnees* _d)const{
	QStringList args_;
	args_<<Utilitaire::traduire(_d->val_noms_pierres_evo(),nom_pierre(),_langue);
	args_<<Utilitaire::traduire(_d->val_constantes_non_num(),genre,_langue);
	return Evolution::description(_base,_evo,_langue,_d)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_PIERRE_GEN").split("\t")[_langue],args_)+"\n";
}


