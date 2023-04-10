#include "base_donnees/attaques/effets/effetdegats.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QStringList>
EffetDegats::EffetDegats(const QString& _ligne){
	//EFFET_DEGAT[A,80,0]
	QStringList infos_=_ligne.split(",");
	maj_lanceur(infos_[0].contains("L"));
	if(infos_[1].endsWith("]")){
		infos_[1].chop(1);
	}
	puissance=infos_[1].toInt();
	if(infos_.size()>2){
		taux_cc=(char)infos_[2].left(infos_[2].size()-1).toInt();
	}else{
		taux_cc=0;
	}
	degats_fixe=false;
}

int EffetDegats::puis()const{
	return puissance;
}

char EffetDegats::tx_cc()const{
	return taux_cc;
}

bool EffetDegats::deg_fixe()const{
	return degats_fixe;
}

void EffetDegats::fixer_degats(){
	degats_fixe=true;
}

QString EffetDegats::description(int _langue,Donnees *_d)const{
	QString retour_=Effet::description(_langue,_d);
	QStringList args_;
	if(degats_fixe){
		args_<<QString::number(puissance);
		retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_DEGAT_FIXE").split("\t")[_langue],args_)+"\n";
	}else{
		args_<<QString::number(puissance);
		args_<<QString::number(taux_cc);
		retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_DEGAT").split("\t")[_langue],args_)+"\n";
	}
	return retour_;
}



