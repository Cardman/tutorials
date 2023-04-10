#include "base_donnees/objets/soinpp.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QRegExp>
SoinPP::SoinPP(const QStringList& _effets,const QPair<QString,QString>& _effets_sec,int _prix_achat):Soin(_effets,_prix_achat){
	effets_sec=_effets_sec;
}

QPair<QString,QString> SoinPP::effs_se()const{
	return effets_sec;
}

QString SoinPP::description(int _langue,Donnees *)const{
	//QStringList effets_=effets_objet()
	QString retour_;
	//QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(Ressources::_indice_francais_)+"}"
	if(bonh().first!=0){
		QStringList args_;
		args_<<QString::number(bonh().first);
		args_<<QString::number(bonh().second);
		QString cle_="BONHEUR";
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(effets_sec==QPair<QString,QString>("MAX","MAX")){
		QString cle_="SOIN_PP[*,*";
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}else if(effets_sec.first=="MAX"){
		QStringList args_;
		args_<<effets_sec.second;
		QString cle_="SOIN_PP[*";
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}else if(effets_sec.second=="MAX"){
		QStringList args_;
		args_<<effets_sec.first;
		QString cle_="SOIN_PP[,*";
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}else{//Que des nombres
		QStringList args_;
		args_<<effets_sec.first;
		args_<<effets_sec.second;
		QString cle_="SOIN_PP";
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	//TODO traduire "prix" en "price" dans un fichier
	retour_+="prix: "+QString::number(prix());
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}



