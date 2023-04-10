#include "base_donnees/objets/soin.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QRegExp>
const HashMap<QString,QString> Soin::_descriptions_soins_=Soin::init_descriptions_soins();

HashMap<QString,QString> Soin::init_descriptions_soins(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/descriptions_objets_soins");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/descriptions_objets_soins.txt");
#endif
	QStringList lignes_=contenu_.split("\n");
	HashMap<QString,QString> descriptions_objets_;
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		QString cle_=infos_.takeFirst();
		descriptions_objets_.ajouter_cle_valeur(cle_,infos_.join("\t"));
	}
	return descriptions_objets_;
}

Soin::Soin(const QStringList& _effets,int _prix_achat):Objet(){
	maj_prix_achat(_prix_achat);
	QStringList effets_=_effets.filter(QRegExp("^BONHEUR"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("(-)?([0-9])+(/([0-9])+)?");
		int ind_=effets_[0].indexOf(exp_taux_);
		QString min_=exp_taux_.capturedTexts()[0];
		bonheur.first=(uchar)min_.toUInt();
		effets_[0].indexOf(exp_taux_,ind_+min_.size()+1);
		bonheur.second=(uchar)exp_taux_.capturedTexts()[0].toUInt();
	}
	soin_equipe=_effets.contains("SOIN_EQUIPE");
}

bool Soin::soin_eq()const{
	return soin_equipe;
}

QPair<uchar,uchar> Soin::bonh()const{
	return bonheur;
}

QString Soin::description(int _langue,Donnees*)const{
	QString retour_;
	if(bonheur.first!=0){
		QStringList args_;
		args_<<QString::number(bonheur.first);
		args_<<QString::number(bonheur.second);
		QString cle_="BONHEUR";
		retour_+=Utilitaire::formatter(_descriptions_soins_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(soin_equipe){
		retour_+=Utilitaire::formatter(_descriptions_soins_.valeur("SOIN_EQUIPE").split("\t")[_langue],QStringList())+"\n";
	}
	retour_+="prix: "+QString::number(prix());
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}


