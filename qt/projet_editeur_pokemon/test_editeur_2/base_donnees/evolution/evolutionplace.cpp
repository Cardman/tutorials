#include "base_donnees/evolution/evolutionplace.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>
EvolutionPlace::EvolutionPlace(const QString& _nom):Evolution(){
	nom_pokemon=_nom;
	nom_pokemon=nom_pokemon.toUpper();
}

QString EvolutionPlace::nom()const{
	return nom_pokemon;
}

QString EvolutionPlace::description(const QString& _base,const QString& _evo,int _langue)const{
	QStringList args_;
	args_<<Utilitaire::traduire(Import::_noms_pk_,nom_pokemon,_langue);
	return Evolution::description(_base,_evo,_langue)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_PLACE").split("\t")[_langue],args_)+"\n";
	//return "avoir au moins un "+nom_pokemon+" dans l'équipe"
}



