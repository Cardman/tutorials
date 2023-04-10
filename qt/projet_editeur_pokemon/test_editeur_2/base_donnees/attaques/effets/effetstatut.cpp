#include "base_donnees/attaques/effets/effetstatut.h"
#include "math/taux.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QStringList>
EffetStatut::EffetStatut(const QString& _ligne){
	pseudo_statut=_ligne.contains("PSEUDO_STATUT");
	maj_lanceur(_ligne.contains("[L,"));
	//QString infos_=_ligne.mid(_ligne.indexOf("["))
	Taux proba_gl_=Taux::parse_taux(_ligne.split(",")[1]);
	Entier effectif_actif_;
	QStringList statuts_=_ligne.split(",[")[1].split("]]")[0].split(";");
	MonteCarlo<QString> loi_proba_statuts_;
	Entier ppcm_=Entier(1);
	foreach(QString s,statuts_){
		ppcm_=ppcm_.ppcm(Taux::parse_taux(s.split(",")[1]).gdenominateur());
	}
	foreach(QString s,statuts_){
		Taux proba_statut_=Taux::parse_taux(s.split(",")[1]);
		loi_proba_statuts_.ajouter_event(QPair<QString,Entier>(s.split(",")[0],(proba_statut_*Taux(ppcm_)).partie_entiere()));
	}
	if(proba_gl_==Taux(1)){
		effectif_actif_=Entier(1);
		loi_proba_statuts.ajouter_event(QPair<MonteCarlo<QString>,Entier>(loi_proba_statuts_,effectif_actif_));
	}else{//TODO a voir pendant codage du jeu
		MonteCarlo<QString> loi_proba_ok_;
		loi_proba_ok_.ajouter_event(QPair<QString,Entier>("OK",1));
		effectif_actif_=proba_gl_.gnumerateur();
		Entier effectif_inactif_=Entier(proba_gl_.gdenominateur())-effectif_actif_;
		loi_proba_statuts.ajouter_event(QPair<MonteCarlo<QString>,Entier>(loi_proba_statuts_,effectif_actif_));
		loi_proba_statuts.ajouter_event(QPair<MonteCarlo<QString>,Entier>(loi_proba_ok_,effectif_inactif_));
	}
}

MonteCarlo<MonteCarlo<QString> > EffetStatut::loi_st()const{
	return loi_proba_statuts;
}

bool EffetStatut::ps_stat()const{
	return pseudo_statut;
}

QStringList EffetStatut::statuts_possibles_non_ok()const{
	MonteCarlo<QString> loi_proba_statuts_=loi_proba_statuts.event_proba(0).first;
	QList<QString> statuts_=loi_proba_statuts_.events();
	QStringList statuts_non_ok_=QStringList(statuts_);
	return statuts_non_ok_;
}

QString EffetStatut::description(int _langue)const{
	QString retour_;
	QPair<MonteCarlo<QString>,Entier> loi_proba_statuts_=loi_proba_statuts.event_proba(0);
	QStringList statuts_pos_;
	//QStringList loi_
	MonteCarlo<QString> loi_;
	foreach(QString s,loi_proba_statuts_.first.events()){
		if(Utilitaire::traduisible(Import::_noms_statuts_,s)){
			statuts_pos_<<Utilitaire::traduire(Import::_noms_statuts_,s,_langue);
		}else{
			statuts_pos_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,s,_langue);
		}
		loi_.ajouter_event(QPair<QString,Entier>(statuts_pos_.last(),loi_proba_statuts_.first.proba_event(s)));
		//loi_<<"("+statuts_pos_.last()+": "+loi_proba_statuts_.proba_event(s).chaine()+")"
	}
	statuts_pos_.sort();
	//loi_.sort()
	QStringList args_;
	args_<<statuts_pos_.join(",");
	if(loi_proba_statuts.events().size()>1){
		args_<<Taux(loi_proba_statuts_.second,loi_proba_statuts_.second+loi_proba_statuts.event_proba(1).second).chaine();
	}else{
		args_<<Taux(1).chaine();
	}
	//args_<<Taux(loi_proba_statuts_.second,loi_proba_statuts_.second+loi_proba_statuts.event_proba(1).second).chaine()
	if(qui()){
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,"LANCEUR_DESCR",_langue+1);
	}else{
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,"CIBLE_DESCR",_langue+1);
	}
	args_<<loi_.chaine_ch();
	retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_STATUT").split("\t")[_langue],args_)+"\n";
	return retour_;
}



