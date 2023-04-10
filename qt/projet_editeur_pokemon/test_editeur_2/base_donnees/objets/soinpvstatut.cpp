#include "base_donnees/objets/soinpvstatut.h"
#include <QString>
#include "autre/utilitaire.h"
#include <QRegExp>
SoinPVStatut::SoinPVStatut(const QStringList& _effets,const QStringList& _statuts,const Taux& _taux_soin,int _prix_achat):SoinStatut(_effets,_statuts,_prix_achat){
	taux_soin=_taux_soin;
}

Taux SoinPVStatut::tx_soin()const{
	return taux_soin;
}

QString SoinPVStatut::description(int _langue)const{
	//QStringList effets_=effets_objet()
	QString retour_=SoinStatut::description(_langue);
	retour_=retour_.left(retour_.lastIndexOf("\n"));
	if(taux_soin<Taux(1)){
		QStringList args_;
		args_<<taux_soin.chaine();
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur("SOIN_PV[*/").split("\t")[_langue],args_)+"\n";
	}else{
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur("SOIN_PV[*").split("\t")[_langue],QStringList())+"\n";
	}
	retour_+="prix: "+QString::number(prix());
	return retour_;
}



