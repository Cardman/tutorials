#include "base_donnees/evolution/evolutionconditionstat.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QStringList>

EvolutionConditionStat::EvolutionConditionStat(uchar _niveau,const QString& _stat):EvolutionNiveau(_niveau){
	statistique=_stat;
}

QString EvolutionConditionStat::stat()const{
	return statistique;
}

QString EvolutionConditionStat::description(const QString& _base,const QString& _evo,int _langue,Donnees* _d)const{
	QStringList args_;
	QString retour_;
	args_<<QString::number(niv());
	if(statistique==""){
		args_<<Utilitaire::traduire(_d->val_noms_statistiques(),"ATTAQUE",_langue);
		args_<<Utilitaire::traduire(_d->val_noms_statistiques(),"DEFENSE",_langue);
		retour_+=Evolution::description(_base,_evo,_langue,_d)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_COND_STAT_EG").split("\t")[_langue],args_)+"\n";
	}else{
		QString statistique_;
		if(statistique=="ATTAQUE"){
			statistique_="DEFENSE";
		}else{//statistique vaut DEFENSE
			statistique_="ATTAQUE";
		}
		args_<<Utilitaire::traduire(_d->val_noms_statistiques(),statistique,_langue);
		args_<<Utilitaire::traduire(_d->val_noms_statistiques(),statistique_,_langue);
		retour_+=Evolution::description(_base,_evo,_langue,_d)+Utilitaire::formatter(_descriptions_evos_.valeur("EVO_COND_STAT_SUP").split("\t")[_langue],args_)+"\n";
	}
	return retour_;//EvolutionNiveau::description()+"\n avec la statistique "+statistique
}


