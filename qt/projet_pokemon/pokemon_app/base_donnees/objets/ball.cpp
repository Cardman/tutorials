#include "base_donnees/objets/ball.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QRegExp>
const HashMap<QString,QString> Ball::_descriptions_balls_=Ball::init_descriptions_balls();

HashMap<QString,QString> Ball::init_descriptions_balls(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/descriptions_ball");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/descriptions_ball.txt");
#endif
	QStringList lignes_=contenu_.split("\n");
	HashMap<QString,QString> descriptions_balls_;
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		QString cle_=infos_.takeFirst();
		descriptions_balls_.ajouter_cle_valeur(cle_,infos_.join("\t"));
	}
	return descriptions_balls_;
}

Ball::Ball(const QStringList& _effets,Donnees* _d,int _prix_achat):Objet(){
	maj_prix_achat(_prix_achat);
	QStringList effets_=_effets.filter(QRegExp("^TAUX_FIXE"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		taux_fixe=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^TAUX_DEJA_CAPTURE"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		taux_deja_capture.ajouter_cle_valeur(true,Taux::parse_taux(exp_taux_.capturedTexts()[0]));
		QString taux_base_=_d->val_constantes().filter(QRegExp("^TAUX_BASE\t"))[0].split("\t")[1];
		taux_deja_capture.ajouter_cle_valeur(false,Taux::parse_taux(taux_base_));
	}
	effets_=_effets.filter(QRegExp("^TAUX_GENRE"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		taux_genre.ajouter_cle_valeur(true,Taux::parse_taux(exp_taux_.capturedTexts()[0]));
		QString taux_base_=_d->val_constantes().filter(QRegExp("^TAUX_BASE\t"))[0].split("\t")[1];
		taux_genre.ajouter_cle_valeur(false,Taux::parse_taux(taux_base_));
	}
	effets_=_effets.filter(QRegExp("^TAUX_PECHE"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		taux_peche.ajouter_cle_valeur(true,Taux::parse_taux(exp_taux_.capturedTexts()[0]));
		QString taux_base_=_d->val_constantes().filter(QRegExp("^TAUX_BASE\t"))[0].split("\t")[1];
		taux_peche.ajouter_cle_valeur(false,Taux::parse_taux(taux_base_));
	}
	effets_=_effets.filter(QRegExp("^TAUX_VITESSE"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			int ind_=e.indexOf(exp_taux_);
			QString b_inf_ch_=exp_taux_.capturedTexts()[0];
			Taux b_inf_=Taux::parse_taux(b_inf_ch_);
			ind_=e.indexOf(exp_taux_,ind_+b_inf_ch_.size()+1);
			QString b_sup_ch_=exp_taux_.capturedTexts()[0];
			Taux b_sup_=Taux::parse_taux(b_sup_ch_);
			e.indexOf(exp_taux_,ind_+b_sup_ch_.size()+1);
			taux_vitesse.ajouter_cle_valeur(QPair<Taux,Taux>(b_inf_,b_sup_),Taux::parse_taux(exp_taux_.capturedTexts()[0]));
		}
	}
	effets_=_effets.filter(QRegExp("^TAUX_TEMPS"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			int ind_=e.indexOf(exp_taux_);
			QString b_inf_ch_=exp_taux_.capturedTexts()[0];
			uchar b_inf_=(uchar)b_inf_ch_.toUInt();
			ind_=e.indexOf(exp_taux_,ind_+b_inf_ch_.size()+1);
			QString b_sup_ch_=exp_taux_.capturedTexts()[0];
			uchar b_sup_=(uchar)b_sup_ch_.toUInt();
			e.indexOf(exp_taux_,ind_+b_sup_ch_.size()+1);
			taux_temps.ajouter_cle_valeur(QPair<uchar,uchar>(b_inf_,b_sup_),Taux::parse_taux(exp_taux_.capturedTexts()[0]));
		}
	}
	effets_=_effets.filter(QRegExp("^TAUX_NIVEAU_ADV"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			int ind_=e.indexOf(exp_taux_);
			QString b_inf_ch_=exp_taux_.capturedTexts()[0];
			uchar b_inf_=(uchar)b_inf_ch_.toUInt();
			ind_=e.indexOf(exp_taux_,ind_+b_inf_ch_.size()+1);
			QString b_sup_ch_=exp_taux_.capturedTexts()[0];
			uchar b_sup_=(uchar)b_sup_ch_.toUInt();
			e.indexOf(exp_taux_,ind_+b_sup_ch_.size()+1);
			taux_niveau_adv.ajouter_cle_valeur(QPair<uchar,uchar>(b_inf_,b_sup_),Taux::parse_taux(exp_taux_.capturedTexts()[0]));
		}
	}
	effets_=_effets.filter(QRegExp("^TAUX_NIVEAUX"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			int ind_=e.indexOf(exp_taux_);
			QString b_inf_ch_=exp_taux_.capturedTexts()[0];
			Taux b_inf_=Taux::parse_taux(b_inf_ch_);
			ind_=e.indexOf(exp_taux_,ind_+b_inf_ch_.size()+1);
			QString b_sup_ch_=exp_taux_.capturedTexts()[0];
			Taux b_sup_=Taux::parse_taux(b_sup_ch_);
			e.indexOf(exp_taux_,ind_+b_sup_ch_.size()+1);
			taux_niveaux.ajouter_cle_valeur(QPair<Taux,Taux>(b_inf_,b_sup_),Taux::parse_taux(exp_taux_.capturedTexts()[0]));
		}
	}
	effets_=_effets.filter(QRegExp("^TAUX_MASSE"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			if(!e.contains("INFINI")){
				int ind_=e.indexOf(exp_taux_);
				QString b_inf_ch_=exp_taux_.capturedTexts()[0];
				Taux b_inf_=Taux::parse_taux(b_inf_ch_);
				ind_=e.indexOf(exp_taux_,ind_+b_inf_ch_.size()+1);
				QString b_sup_ch_=exp_taux_.capturedTexts()[0];
				Taux b_sup_=Taux::parse_taux(b_sup_ch_);
				e.indexOf(exp_taux_,ind_+b_sup_ch_.size()+1);
				taux_masse.ajouter_cle_valeur(QPair<Taux,Taux>(b_inf_,b_sup_),Taux::parse_taux(exp_taux_.capturedTexts()[0]));
			}else{
				int ind_=e.indexOf(exp_taux_);
				QString b_inf_ch_=exp_taux_.capturedTexts()[0];
				Taux b_inf_=Taux::parse_taux(b_inf_ch_);
				ind_=e.indexOf(exp_taux_,ind_+b_inf_ch_.size()+1);
				Taux b_sup_=_d->val_rapport_max_masse();
				taux_masse.ajouter_cle_valeur(QPair<Taux,Taux>(b_inf_,b_sup_),Taux::parse_taux(exp_taux_.capturedTexts()[0]));
			}
		}
	}
	effets_=_effets.filter(QRegExp("^TAUX_LIEU"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			QString lieu_=e.split(QRegExp("[\\[\\],]+"))[1];
			e.indexOf(exp_taux_);
			taux_lieu.ajouter_cle_valeur(lieu_,Taux::parse_taux(exp_taux_.capturedTexts()[0]));
		}
		foreach(QString c,_d->val_noms_envir()){
			QList<QString> cles_=taux_lieu.cles();
			QString lieu_=c.split("\t")[_d->val_indice_francais()];
			if(!cles_.contains(lieu_)){
				QString taux_base_=_d->val_constantes().filter(QRegExp("^TAUX_BASE\t"))[0].split("\t")[1];
				taux_lieu.ajouter_cle_valeur(lieu_,Taux::parse_taux(taux_base_));
			}
		}
	}
	effets_=_effets.filter(QRegExp("^TAUX_TYPES"));
	if(!effets_.isEmpty()){
		taux_types.first=effets_[0].split(QRegExp("[\\[\\],]+"),QString::SkipEmptyParts).mid(1);
		taux_types.first.removeLast();
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		taux_types.second=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^TAUX_PIERRE_EVO"));
	if(!effets_.isEmpty()){
		taux_pierre_evo.first=effets_[0].split(QRegExp("[\\[\\],]+"),QString::SkipEmptyParts).mid(1);
		taux_pierre_evo.first.removeLast();
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		taux_pierre_evo.second=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
}

QString Ball::description(int _langue,Donnees* _d)const{
	QString retour_;
	QString cle_;
	if(taux_fixe!=Taux(0)){
		QStringList args_;
		args_<<taux_fixe.chaine();
		cle_="TAUX_FIXE";
		retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	QList<bool> cles_b_=taux_deja_capture.cles();
	if(!cles_b_.isEmpty()){
		cle_="TAUX_DEJA_CAPTURE";
		QStringList args_;
		args_<<taux_deja_capture.valeur(true).chaine();
		retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		args_.clear();
		cle_="TAUX_DEFAUT";
		args_<<taux_deja_capture.valeur(false).chaine();
		retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	cles_b_=taux_genre.cles();
	if(!cles_b_.isEmpty()){
		cle_="TAUX_GENRE";
		QStringList args_;
		args_<<taux_genre.valeur(true).chaine();
		retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		args_.clear();
		cle_="TAUX_DEFAUT";
		args_<<taux_genre.valeur(false).chaine();
		retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	cles_b_=taux_peche.cles();
	if(!cles_b_.isEmpty()){
		cle_="TAUX_PECHE";
		QStringList args_;
		args_<<taux_peche.valeur(true).chaine();
		retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		args_.clear();
		cle_="TAUX_DEFAUT";
		args_<<taux_peche.valeur(false).chaine();
		retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	typedef QPair<uchar,uchar> BornesPetitEntier;
	QList<BornesPetitEntier> cles_bornes_=taux_temps.cles();
	if(!cles_bornes_.isEmpty()){
		cle_="TAUX_TEMPS";
		foreach(BornesPetitEntier b,cles_bornes_){
			QStringList args_;
			args_<<taux_temps.valeur(b).chaine();
			args_<<QString::number(b.first);
			args_<<QString::number(b.second);
			retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_bornes_=taux_niveau_adv.cles();
	if(!cles_bornes_.isEmpty()){
		cle_="TAUX_NIVEAU_ADV";
		foreach(BornesPetitEntier b,cles_bornes_){
			QStringList args_;
			args_<<taux_niveau_adv.valeur(b).chaine();
			args_<<QString::number(b.first);
			args_<<QString::number(b.second);
			retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	typedef QPair<Taux,Taux> BornesTaux;
	QList<BornesTaux> cles_bornes_2_=taux_masse.cles();
	if(!cles_bornes_2_.isEmpty()){
		cle_="TAUX_MASSE";
		foreach(BornesTaux b,cles_bornes_2_){
			QStringList args_;
			args_<<taux_masse.valeur(b).chaine();
			args_<<b.first.chaine();
			args_<<b.second.chaine();
			retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_bornes_2_=taux_vitesse.cles();
	if(!cles_bornes_2_.isEmpty()){
		cle_="TAUX_VITESSE";
		foreach(BornesTaux b,cles_bornes_2_){
			QStringList args_;
			args_<<taux_vitesse.valeur(b).chaine();
			args_<<b.first.chaine();
			args_<<b.second.chaine();
			retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_bornes_2_=taux_niveaux.cles();
	if(!cles_bornes_2_.isEmpty()){
		cle_="TAUX_NIVEAUX";
		foreach(BornesTaux b,cles_bornes_2_){
			QStringList args_;
			args_<<taux_niveaux.valeur(b).chaine();
			args_<<b.first.chaine();
			args_<<b.second.chaine();
			retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	QList<QString> cles_ch_=taux_lieu.cles();
	if(!cles_ch_.isEmpty()){
		cle_="TAUX_LIEU";
		foreach(QString l,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_envir(),l,_langue);
			args_<<taux_lieu.valeur(l).chaine();
			retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(!taux_pierre_evo.first.isEmpty()){
		cle_="TAUX_PIERRE_EVO";
		QStringList ls_pierre_evo_;
		foreach(QString p,cles_ch_){
			ls_pierre_evo_<<Utilitaire::traduire(_d->val_noms_pierres_evo(),p,_langue);
		}
		ls_pierre_evo_.sort();
		foreach(QString p,ls_pierre_evo_){
			QStringList args_;
			args_<<p;
			args_<<taux_pierre_evo.second.chaine();
			retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(!taux_types.first.isEmpty()){
		cle_="TAUX_TYPES";
		QStringList ls_pierre_evo_;
		foreach(QString p,cles_ch_){
			ls_pierre_evo_<<Utilitaire::traduire(_d->val_noms_types(),p,_langue);
		}
		ls_pierre_evo_.sort();
		foreach(QString p,ls_pierre_evo_){
			QStringList args_;
			args_<<p;
			args_<<taux_types.second.chaine();
			retour_+=Utilitaire::formatter(_descriptions_balls_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	//taux_lieu
	//TODO traduire "prix" en "price" dans un fichier
	retour_+="prix: "+QString::number(prix());
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}

Taux Ball::tx_fix()const{
	return taux_fixe;
}

HashMap<QPair<Taux,Taux>,Taux> Ball::tx_niv()const{
	return taux_niveaux;
}

HashMap<bool,Taux> Ball::tx_pec()const{
	return taux_peche;
}

QPair<QStringList,Taux> Ball::tx_pier_evo()const{
	return taux_pierre_evo;
}

HashMap<bool,Taux> Ball::tx_gen()const{
	return taux_genre;
}

HashMap<QPair<Taux,Taux>,Taux> Ball::tx_m()const{
	return taux_masse;
}

HashMap<QPair<Taux,Taux>,Taux> Ball::tx_v()const{
	return taux_vitesse;
}

HashMap<bool,Taux> Ball::tx_capt()const{
	return taux_deja_capture;
}

HashMap<QPair<uchar,uchar>,Taux> Ball::tx_tps()const{
	return taux_temps;
}

HashMap<QPair<uchar,uchar>,Taux> Ball::niv_adv()const{
	return taux_niveau_adv;
}

QPair<QStringList,Taux> Ball::tx_types()const{
	return taux_types;
}

HashMap<QString,Taux> Ball::tx_lieu()const{
	return taux_lieu;
}



