#include "base_donnees/objets/boost.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QRegExp>
const uchar Boost::_max_ev_=255;//(uchar)Import::_constantes_.filter(QRegExp("^MAX_EV\\b"))[0].split("\t")[1].toUInt();
const HashMap<QString,QString> Boost::_descriptions_boosts_=Boost::init_descriptions_boosts();

HashMap<QString,QString> Boost::init_descriptions_boosts(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/descriptions_boost_statistiques");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/descriptions_boost_statistiques.txt");
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

Boost::Boost(const QStringList& _effets,const QString& _effet,int _prix_achat):Objet(){
	//effet=_effet
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
	if(_effet.startsWith("GAIN_PP")){
		QRegExp exp_taux_("(-)?([0-9])+(/([0-9])+)?");
		_effet.indexOf(exp_taux_);
		gain_pp=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	if(_effet.startsWith("GAIN_EV")){
		gain_ev.first=_effet.split(QRegExp("(\\W)+"))[1];
		QRegExp exp_taux_("(-)?([0-9])+(/([0-9])+)?");
		_effet.indexOf(exp_taux_);
		gain_ev.second=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
}

Taux Boost::g_pp()const{
	return gain_pp;
}

QPair<uchar,uchar> Boost::bonh()const{
	return bonheur;
}

QPair<QString,Taux> Boost::g_ev()const{
	return gain_ev;
}

QString Boost::description(int _langue)const{
	//QStringList effets_=effets_objet()
	QString retour_;
	//QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(Ressources::_indice_francais_)+"}"
	if(gain_ev.first!=""){
		QStringList args_;
		/*QStringList corresp_=Ressources::_noms_statistiques_.filter(QRegExp("^"+ch_exp_reg_+effet.split(QRegExp("(\\W)+"))[1]+"\\t"))
		args_<<corresp_[0].split("\t")[_langue]*/
		args_<<Utilitaire::traduire(Import::_noms_statistiques_,gain_ev.first,_langue);
		args_<<QString::number(_max_ev_);
		args_<<gain_ev.second.chaine();
		QString cle_="GAIN_EV";
		retour_+=Utilitaire::formatter(_descriptions_boosts_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(gain_pp!=Taux(0)){
		QStringList args_;
		args_<<gain_pp.chaine();
		QString cle_="GAIN_PP";
		retour_+=Utilitaire::formatter(_descriptions_boosts_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(bonheur.first!=0){
		QStringList args_;
		args_<<QString::number(bonheur.first);
		args_<<QString::number(bonheur.second);
		QString cle_="BONHEUR";
		retour_+=Utilitaire::formatter(_descriptions_boosts_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	retour_+="prix: "+QString::number(prix());
	return retour_;
}




