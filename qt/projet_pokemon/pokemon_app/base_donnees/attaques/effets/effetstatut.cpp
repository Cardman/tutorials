#include "base_donnees/attaques/effets/effetstatut.h"
#include "base_donnees/donnees.h"
#include "serialisable/math/taux.h"
#include "autre/utilitaire.h"
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

MonteCarlo<QString> EffetStatut::tirage_statut(uchar _coeff,bool _mult_2,bool _primaire)const{
	MonteCarlo<QString> loi_;
	Taux proba_((long long int)0);
	foreach(MonteCarlo<QString> m,loi_proba_statuts.events()){
		if(m.events()!=QStringList("OK")){
			loi_=m;
			proba_=loi_proba_statuts.proba_event(m);
		}
	}
	Taux coeff_((long long int)1);
	if(!_primaire){
		if(_coeff){
			coeff_*=Taux((long long int)_coeff);
		}
		if(_mult_2){
			coeff_*=Taux((long long int)2);
		}
	}
	Taux produit_=proba_*coeff_;
	if(produit_>=Taux((long long int)1)){
		return loi_;
	}
	MonteCarlo<MonteCarlo<QString> > loi_2_;
	EntierPositif den_=produit_.gdenominateur();
	Entier num_=produit_.gnumerateur();
	loi_2_.ajouter_event(QPair<MonteCarlo<QString>,Entier>(loi_,num_));
	MonteCarlo<QString> loi_3_;
	loi_3_.ajouter_event(QPair<QString,Entier>("OK",Entier(1)));
	loi_2_.ajouter_event(QPair<MonteCarlo<QString>,Entier>(loi_3_,den_-num_));
	return loi_2_.tirage();
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

QString EffetStatut::description(int _langue,Donnees *_d)const{
	QString retour_=Effet::description(_langue,_d);
	QPair<MonteCarlo<QString>,Entier> loi_proba_statuts_=loi_proba_statuts.event_proba(0);
	QStringList statuts_pos_;
	//QStringList loi_
	MonteCarlo<QString> loi_;
	foreach(QString s,loi_proba_statuts_.first.events()){
		if(Utilitaire::traduisible(_d->val_noms_statuts(),s)){
			statuts_pos_<<Utilitaire::traduire(_d->val_noms_statuts(),s,_langue);
		}else{
			statuts_pos_<<Utilitaire::traduire(_d->val_noms_pseudo_statuts(),s,_langue);
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
		args_<<Utilitaire::traduire(_d->val_constantes_non_num(),"LANCEUR_DESCR",_langue+1);
	}else{
		args_<<Utilitaire::traduire(_d->val_constantes_non_num(),"CIBLE_DESCR",_langue+1);
	}
	args_<<loi_.chaine_ch();
	retour_+=Utilitaire::formatter(_descriptions_effets_.valeur("EFFET_STATUT").split("\t")[_langue],args_)+"\n";
	return retour_;
}



