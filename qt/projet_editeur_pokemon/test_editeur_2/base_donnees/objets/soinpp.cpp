#include "base_donnees/objets/soinpp.h"
#include "autre/utilitaire.h"
#include <QRegExp>
SoinPP::SoinPP(const QStringList& _effets,const QPair<QString,QString>& _effets_sec,int _prix_achat):Soin(_effets,_prix_achat){
	effets_sec=_effets_sec;
}

QPair<QString,QString> SoinPP::effs_se()const{
	return effets_sec;
}

QString SoinPP::description(int _langue)const{
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
		//QRegExp exp_taux_("(-)?([0-9])+(/([0-9])+)?")
		//int ind_=e.indexOf(exp_taux_)
		QStringList args_;
		//args_<<exp_taux_.capturedTexts()[0]
		args_<<effets_sec.first;
		//e.indexOf(exp_taux_,ind_+args_.last().size())
		args_<<effets_sec.second;
		//args_<<exp_taux_.capturedTexts()[0]
		QString cle_="SOIN_PP";
		retour_+=Utilitaire::formatter(Soin::_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	/*foreach(QString e,effets_){
		if(e.startsWith("BONHEUR")){
			QRegExp exp_taux_("(-)?([0-9])+(/([0-9])+)?")
			int ind_=e.indexOf(exp_taux_)
			QStringList args_
			args_<<exp_taux_.capturedTexts()[0]
			e.indexOf(exp_taux_,ind_+args_.last().size())
			args_<<exp_taux_.capturedTexts()[0]
			QString cle_="BONHEUR"
			retour_+=Utilitaire::formatter(_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)
		}else if(e.startsWith("SOIN_PP[MAX,MAX")){
			QString cle_="SOIN_PP[*,*"
			retour_+=Utilitaire::formatter(_descriptions_soins_.valeur(cle_).split("\t")[_langue],QStringList())
		}else if(e.startsWith("SOIN_PP[MAX")){
			QRegExp exp_taux_("(-)?([0-9])+(/([0-9])+)?")
			e.indexOf(exp_taux_)
			QStringList args_
			args_<<exp_taux_.capturedTexts()[0]
			QString cle_="SOIN_PP[*"
			retour_+=Utilitaire::formatter(_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)
		}else if(e.startsWith("SOIN_PP")&&e.contains("MAX")){
			QRegExp exp_taux_("(-)?([0-9])+(/([0-9])+)?")
			e.indexOf(exp_taux_)
			QStringList args_
			args_<<exp_taux_.capturedTexts()[0]
			QString cle_="SOIN_PP[,*"
			retour_+=Utilitaire::formatter(_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)
		}else if(e.startsWith("SOIN_PP")){
			QRegExp exp_taux_("(-)?([0-9])+(/([0-9])+)?")
			int ind_=e.indexOf(exp_taux_)
			QStringList args_
			args_<<exp_taux_.capturedTexts()[0]
			e.indexOf(exp_taux_,ind_+args_.last().size())
			args_<<exp_taux_.capturedTexts()[0]
			QString cle_="SOIN_PP"
			retour_+=Utilitaire::formatter(_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)
		}
		retour_+="\n"
	}*/
	//TODO traduire "prix" en "price" dans un fichier
	retour_+="prix: "+QString::number(prix());
	return retour_;
}



