#include "base_donnees/evolution/evolutionobjet.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QStringList>
EvolutionObjet::EvolutionObjet(const QString& _objet):Evolution(){
	objet=_objet;
}

QString EvolutionObjet::nom_objet()const{
	return objet;
}

QString EvolutionObjet::description(const QString& _base,const QString& _evo,int _langue,Donnees* _d)const{
	QStringList args_;
	args_<<Utilitaire::traduire(_d->val_noms_objets_evo(),objet,_langue);
	return Evolution::description(_base,_evo,_langue,_d)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_OBJ").split("\t")[_langue],args_)+"\n";
}



