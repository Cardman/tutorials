#include "base_donnees/evolution/evolutionniveau.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QStringList>
EvolutionNiveau::EvolutionNiveau(uchar _niveau):Evolution(){
	niveau=_niveau;
}

uchar EvolutionNiveau::niv()const{
	return niveau;
}

QString EvolutionNiveau::description(const QString& _base,const QString& _evo,int _langue,Donnees* _d)const{
	QStringList args_;
	args_<<QString::number(niveau);
	return Evolution::description(_base,_evo,_langue,_d)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_NIV").split("\t")[_langue],args_)+"\n";
}



