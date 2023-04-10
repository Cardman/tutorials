#include "base_donnees/attaques/effets/effetantiimmu.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QStringList>
EffetAntiImmu::EffetAntiImmu(const QString& _ligne){
	QStringList infos_=_ligne.split(",[[");
	maj_lanceur(infos_[0].contains("L"));
	infos_[1].chop(3);
	foreach(QString s,infos_[1].split("],[")){
		QStringList types_=s.split(",");
		types<<QPair<QString,QString>(types_[0],types_[1]);
	}
}

QList<QPair<QString,QString> > EffetAntiImmu::tp()const{
	return types;
}

QString EffetAntiImmu::description(int _langue,Donnees* _d)const{
	//EFFET_ANTI_IMMU
	QString retour_=Effet::description(_langue,_d);
	typedef QPair<QString,QString> Types;
	foreach(Types t,types){
		QStringList args_;
		args_<<Utilitaire::traduire(_d->val_noms_types(),t.second,_langue);
		args_<<Utilitaire::traduire(_d->val_noms_types(),t.first,_langue);
		retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_ANTI_IMMU").split("\t")[_langue],args_)+"\n";
	}
	return retour_;
}



