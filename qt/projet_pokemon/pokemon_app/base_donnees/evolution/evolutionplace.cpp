#include "base_donnees/evolution/evolutionplace.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QStringList>
EvolutionPlace::EvolutionPlace(const QString& _nom):Evolution(){
	nom_pokemon=_nom;
	nom_pokemon=nom_pokemon.toUpper();
}

QString EvolutionPlace::nom()const{
	return nom_pokemon;
}

QString EvolutionPlace::description(const QString& _base,const QString& _evo,int _langue,Donnees* _d)const{
	QStringList args_;
	args_<<Utilitaire::traduire(_d->val_noms_pk(),nom_pokemon,_langue);
	return Evolution::description(_base,_evo,_langue,_d)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_PLACE").split("\t")[_langue],args_)+"\n";
	//return "avoir au moins un "+nom_pokemon+" dans l'équipe"
}



