#include "base_donnees/objets/soinstatut.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QRegExp>
SoinStatut::SoinStatut(const QStringList& _effets,const QStringList& _statuts,int _prix_achat):Soin(_effets,_prix_achat){
	statuts=_statuts;
	soin_ko=_effets.contains("SOIN_KO");
}

QStringList SoinStatut::stats()const{
	return statuts;
}

bool SoinStatut::s_ko()const{
	return soin_ko;
}

QString SoinStatut::description(int _langue,Donnees*)const{
	QString retour_;
	if(bonh().first!=0){
		QStringList args_;
		args_<<QString::number(bonh().first);
		args_<<QString::number(bonh().second);
		QString cle_="BONHEUR";
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(soin_ko){
		QStringList args_;
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur("SOIN_KO").split("\t")[_langue],args_)+"\n";
	}
	if(!statuts.isEmpty()){
		foreach(QString s,statuts){
			QStringList args_;
			args_<<s;
			retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur("SOIN_STATUT").split("\t")[_langue],args_)+"\n";
		}
	}
	retour_+="prix: "+QString::number(prix());
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}



