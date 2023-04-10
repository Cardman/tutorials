#include "base_donnees/evolution/evolutionattaque.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QStringList>
EvolutionAttaque::EvolutionAttaque(const QString&_nom_attaque):Evolution(){
	nom_attaque=_nom_attaque;
	nom_attaque=nom_attaque.toUpper();
}

QString EvolutionAttaque::attaque()const{
	return nom_attaque;
}

QString EvolutionAttaque::description(const QString& _base,const QString& _evo,int _langue,Donnees* _d)const{
	QStringList args_;
	args_<<Utilitaire::traduire(_d->val_noms_attaques(),nom_attaque,_langue);
	return Evolution::description(_base,_evo,_langue,_d)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_ATT").split("\t")[_langue],args_)+"\n";
}



