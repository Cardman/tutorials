#include "base_donnees/objets/baie.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QRegExp>
const HashMap<QString,QString> Baie::_descriptions_baies_=Baie::init_descriptions_baies();

HashMap<QString,QString> Baie::init_descriptions_baies(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/descriptions_baies");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/descriptions_baies.txt");
#endif
	QStringList lignes_=contenu_.split("\n");
	HashMap<QString,QString> descriptions_baies_;
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		QString cle_=infos_.takeFirst();
		descriptions_baies_.ajouter_cle_valeur(cle_,infos_.join("\t"));
	}
	return descriptions_baies_;
}

Baie::Baie(const QStringList& _effets,const QPair<QString,uchar>& _type_puiss_dn,int _prix_achat):Objet(){
	type_puiss_dn=_type_puiss_dn;
	setAttachable();
	maj_prix_achat(_prix_achat);
	sans_echec=_effets.contains("SANS_ECHEC");
	QStringList effets_=_effets.filter(QRegExp("^GAIN_PV\\[>"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_(",[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		gain_pv_super_eff=Taux::parse_taux(exp_taux_.capturedTexts()[0].mid(1));
	}
	effets_=_effets.filter(QRegExp("^LOI_PROBA"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		loi_proba_premier=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_DEGATS_ADV"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_(",[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			QString type_=e.split(QRegExp("[\\[\\],]+"))[2];
			e.indexOf(exp_taux_);
			mult_degats_adv.ajouter_cle_valeur(type_,Taux::parse_taux(exp_taux_.capturedTexts()[0].mid(1)));
		}
	}
	effets_=_effets.filter(QRegExp("^TAUX_DEGATS_RECUL_ADV"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			QString type_=e.split(QRegExp("[\\[\\],]+"))[1];
			e.indexOf(exp_taux_);
			taux_degats_recul_adv.ajouter_cle_valeur(type_,Taux::parse_taux(exp_taux_.capturedTexts()[0]));
		}
	}
	effets_=_effets.filter(QRegExp("^SOIN_TAUX_PV_PVMAX"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		int ind_=effets_[0].indexOf(exp_taux_);
		QString taux_ch_=exp_taux_.capturedTexts()[0];
		soin_taux_pv_pvmax.first=Taux::parse_taux(taux_ch_);
		effets_[0].indexOf(exp_taux_,taux_ch_.size()+ind_+1);
		soin_taux_pv_pvmax.second=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^SOIN_PV"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		int ind_=effets_[0].indexOf(exp_taux_);
		QString taux_ch_=exp_taux_.capturedTexts()[0];
		soin_pv.first=Taux::parse_taux(taux_ch_);
		effets_[0].indexOf(exp_taux_,taux_ch_.size()+ind_+1);
		soin_pv.second=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^SOIN_(PSEUDO_)?STATUT"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			soin_statut<<e.split(QRegExp("[\\[\\],]+"))[1];
		}
	}
	/**HashMap<QString,QPair<Taux,qint8> > mult_statistique_si;
	QPair<QString,QString> soin_pp;*/
	effets_=_effets.filter(QRegExp("^SOIN_PP"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		int ind_=effets_[0].indexOf(exp_taux_);
		QString taux_ch_=exp_taux_.capturedTexts()[0];
		soin_pp.first=taux_ch_;
		effets_[0].indexOf(exp_taux_,taux_ch_.size()+ind_+1);
		soin_pp.second=exp_taux_.capturedTexts()[0];
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		QRegExp exp_cran_("[0-9]+C");
		foreach(QString e,effets_){
			QString type_=e.split(QRegExp("[\\[\\],]+"))[2];
			e.indexOf(exp_taux_);
			e.indexOf(exp_cran_);
			QPair<Taux,qint8> pair_;
			pair_.first=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
			QString cran_ch_=exp_cran_.capturedTexts()[0];
			cran_ch_.chop(1);
			pair_.second=(qint8)cran_ch_.toInt();
			mult_statistique_si.ajouter_cle_valeur(type_,pair_);
		}
	}
}

	/**Donne la description d'un objet.*/
QString Baie::description(int _langue,Donnees* _d)const{
	QString retour_;
	QString cle_;
	if(sans_echec){
		cle_="SANS_ECHEC";
		retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(gain_pv_super_eff!=Taux(0)){
		cle_="GAIN_PV[>";
		QStringList args_;
		args_<<gain_pv_super_eff.chaine();
		retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(loi_proba_premier!=Taux(0)){
		cle_="LOI_PROBA_PREMIER";
		QStringList args_;
		args_<<loi_proba_premier.chaine();
		retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	QList<QString> cles_ch_=mult_degats_adv.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_DEGATS_ADV";
		foreach(QString l,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_types(),l,_langue);
			args_<<mult_degats_adv.valeur(l).chaine();
			retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=taux_degats_recul_adv.cles();
	if(!cles_ch_.isEmpty()){
		cle_="TAUX_DEGATS_RECUL_ADV";
		foreach(QString l,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_categories(),l,_langue);
			args_<<taux_degats_recul_adv.valeur(l).chaine();
			retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(soin_taux_pv_pvmax.first!=Taux(0)){
		cle_="SOIN_TAUX_PV_PVMAX";
		QStringList args_;
		args_<<soin_taux_pv_pvmax.first.chaine();
		args_<<soin_taux_pv_pvmax.second.chaine();
		retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(soin_pv.first!=Taux(0)){
		cle_="SOIN_PV";
		QStringList args_;
		args_<<soin_pv.first.chaine();
		args_<<soin_pv.second.chaine();
		retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!soin_statut.isEmpty()){
		cle_="SOIN_STATUT";
		foreach(QString l,soin_statut){
			QStringList args_;
			if(Utilitaire::traduisible(_d->val_noms_statuts(),l)){
				args_<<Utilitaire::traduire(_d->val_noms_statuts(),l,_langue);
			}else{
				args_<<Utilitaire::traduire(_d->val_noms_pseudo_statuts(),l,_langue);
			}
			retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(soin_pp.first!=""){
		cle_="SOIN_PP";
		QStringList args_;
		args_<<soin_pp.first;
		retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	cles_ch_=mult_statistique_si.cles();
	if(!cles_ch_.isEmpty()){//HashMap<QString,QPair<Taux,qint8> >
		cle_="MULT_STATISTIQUE_SI";
		foreach(QString l,cles_ch_){
			QStringList args_;
			QPair<Taux,qint8> val_=mult_statistique_si.valeur(l);
			args_<<val_.first.chaine();
			args_<<Utilitaire::traduire(_d->val_noms_statistiques(),l,_langue);
			args_<<QString::number(val_.second);
			retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cle_="PUISSANCE_TYPE";
	QStringList args_;
	args_<<type_puiss_dn.first;
	args_<<QString::number(type_puiss_dn.second);
	retour_+=Utilitaire::formatter(_descriptions_baies_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	//TODO traduire "prix" en "price" dans un fichier
	retour_+="prix: "+QString::number(prix());
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}

QPair<QString,uchar> Baie::type_puis_dn()const{
	return type_puiss_dn;
}

Taux Baie::gain_pv_sup_ef()const{
	return gain_pv_super_eff;
}

Taux Baie::loi_pr()const{
	return loi_proba_premier;
}

HashMap<QString,Taux> Baie::mult_deg_ad()const{
	return mult_degats_adv;
}

HashMap<QString,QPair<Taux,qint8> > Baie::mult_stat()const{
	return mult_statistique_si;
}

bool Baie::reu()const{
	return sans_echec;
}

QPair<QString,QString> Baie::s_pp()const{
	return soin_pp;
}

QPair<Taux,Taux> Baie::s_pv()const{
	return soin_pv;
}

QStringList Baie::s_statut()const{
	return soin_statut;
}

QPair<Taux,Taux> Baie::s_tx_pv()const{
	return soin_taux_pv_pvmax;
}

HashMap<QString,Taux> Baie::tx_deg_recul_ad()const{
	return taux_degats_recul_adv;
}



