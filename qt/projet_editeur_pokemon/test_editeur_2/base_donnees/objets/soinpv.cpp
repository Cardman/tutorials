#include "base_donnees/objets/soinpv.h"
#include "autre/utilitaire.h"
#include <QString>
#include <QRegExp>
SoinPV::SoinPV(const QStringList& _effets,const Taux& _pv_max_rest,int _prix_achat):Soin(_effets,_prix_achat){
	pv_max_rest=_pv_max_rest;
}

Taux SoinPV::pv_m_res()const{
	return pv_max_rest;
}

QString SoinPV::description(int _langue)const{
	//QStringList effets_=effets_objet()
	QString retour_;
	//QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(Ressources::_indice_francais_)+"}"
	//if(effets_.contains("BONHEUR")){
	if(bonh().first!=0){
		QStringList args_;
		args_<<QString::number(bonh().first);
		args_<<QString::number(bonh().second);
		QString cle_="BONHEUR";
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(pv_max_rest==Taux(0)){
		retour_+=Utilitaire::formatter(_descriptions_soins_.valeur("SOIN_PV[*").split("\t")[_langue],QStringList())+"\n";
	}else{
		QStringList args_;
		args_<<pv_max_rest.chaine();
		retour_+=Utilitaire::formatter(_descriptions_soins_.valeur("SOIN_PV").split("\t")[_langue],args_)+"\n";
	}
	retour_+="prix: "+QString::number(prix());
	return retour_;
}



