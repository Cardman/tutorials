#include "base_donnees/evolution/evolutionniveaugenre.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>
EvolutionNiveauGenre::EvolutionNiveauGenre(uchar _niveau,const QString& _genre):EvolutionNiveau(_niveau){
	genre=_genre;
	if(genre.endsWith(" ")){
		genre.chop(1);
	}
}

QString EvolutionNiveauGenre::gr()const{
	return genre;
}

QString EvolutionNiveauGenre::description(const QString& _base,const QString& _evo,int _langue)const{
	QStringList args_;
	args_<<QString::number(niv());
	args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,genre,_langue+1);
	return Evolution::description(_base,_evo,_langue)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_NIV_GEN").split("\t")[_langue],args_)+"\n";
	//return EvolutionNiveau::description()+"\n"+EvolutionGenre::description()
}


