#include "base_donnees/objets/soinpvstatut.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QString>
#include <QRegExp>
SoinPVStatut::SoinPVStatut(const QStringList& _effets,const QStringList& _statuts,const Taux& _taux_soin,int _prix_achat):SoinStatut(_effets,_statuts,_prix_achat){
	taux_soin=_taux_soin;
}

Taux SoinPVStatut::tx_soin()const{
	return taux_soin;
}

QString SoinPVStatut::description(int _langue,Donnees* _d)const{
	//QStringList effets_=effets_objet()
	QString retour_=SoinStatut::description(_langue,_d);
	retour_=retour_.left(retour_.lastIndexOf("\n"));
	if(taux_soin<Taux(1)){
		QStringList args_;
		args_<<taux_soin.chaine();
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur("SOIN_PV[*/").split("\t")[_langue],args_)+"\n";
	}else{
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur("SOIN_PV[*").split("\t")[_langue],QStringList())+"\n";
	}
	retour_+="prix: "+QString::number(prix());
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}



