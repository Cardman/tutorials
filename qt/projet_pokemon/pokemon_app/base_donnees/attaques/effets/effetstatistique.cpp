#include "base_donnees/attaques/effets/effetstatistique.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QStringList>
EffetStatistique::EffetStatistique(const QString& _ligne){
	//EFFET_STATISTIQUE[L,[ATTAQUE,DEFENSE,ATTAQUE_SPECIALE,DEFENSE_SPECIALE,VITESSE],1/10,1]
	//EFFET_STATISTIQUE[L,ATTAQUE,1/10,1]
	//EFFET_STATISTIQUE[L,[[ATTAQUE,1],[DEFENSE,1],[ATTAQUE_SPECIALE,1],[DEFENSE_SPECIALE,1],[VITESSE,1]],1/10]
	if(_ligne.count("[")==1){
		QString tmp_=_ligne.mid(_ligne.indexOf("["));
		QStringList infos_=tmp_.split(",");
		maj_lanceur(infos_[0].contains("L"));
		proba_actif=Taux::parse_taux(infos_[2]);
		infos_[3]=infos_[3].left(infos_[3].size()-1);
		statis_var_crans.ajouter_cle_valeur(infos_[1],(qint8)infos_[3].toInt());
	}else if(_ligne.count("[")==2){
		QString tmp_=_ligne.mid(_ligne.indexOf("["));
		QStringList statis_=tmp_.split(",[")[1].split("],")[0].split(",");
		QStringList infos_=tmp_.split(",");
		maj_lanceur(infos_[0].contains("L"));
		int ind_proba_=infos_.size()-2;
		proba_actif=Taux::parse_taux(infos_[ind_proba_]);
		int ind_cran_=ind_proba_+1;
		infos_[ind_cran_]=infos_[ind_cran_].left(infos_[ind_cran_].size()-1);
		qint8 val_cran_=(qint8)infos_[ind_cran_].toInt();
		foreach(QString s,statis_){
			statis_var_crans.ajouter_cle_valeur(s,val_cran_);
		}
	}else{
		QString tmp_=_ligne.mid(_ligne.indexOf("["));
		QStringList statis_=tmp_.split(",[[")[1].split("]],")[0].split(",");
		for(int i=0;i<statis_.size();i++){
			statis_[i].remove(QRegExp("["));
			statis_[i].remove(QRegExp("]"));
		}
		QStringList infos_=tmp_.split(",");
		maj_lanceur(infos_[0].contains("L"));
		int ind_proba_=infos_.size()-1;
		proba_actif=Taux::parse_taux(infos_[ind_proba_]);
		foreach(QString s,statis_){
			QStringList infos_statis_=s.split(",");
			qint8 val_cran_=(qint8)infos_statis_[1].toInt();
			statis_var_crans.ajouter_cle_valeur(infos_statis_[0],val_cran_);
		}
	}
}

HashMap<QString,qint8> EffetStatistique::stat_cr()const{
	return statis_var_crans;
}

Taux EffetStatistique::pr_ac()const{
	return proba_actif;
}

QString EffetStatistique::description(int _langue,Donnees *_d)const{
	QString retour_=Effet::description(_langue,_d);
	typedef QPair<QString,char> StatVar;
	foreach(QString s,statis_var_crans.cles()){
		QStringList args_;
		if(qui()){
			args_<<Utilitaire::traduire(_d->val_constantes_non_num(),"DU_LANCEUR",_langue+1);
		}else{
			args_<<Utilitaire::traduire(_d->val_constantes_non_num(),"DE_LA_CIBLE",_langue+1);
		}
		args_<<Utilitaire::traduire(_d->val_noms_statistiques(),s.replace(" ","_"),_langue);
		args_<<proba_actif.chaine();
		args_<<QString::number(statis_var_crans.valeur(s));
		retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_STATISTIQUE").split("\t")[_langue],args_)+"\n";
	}
	return retour_;
}



