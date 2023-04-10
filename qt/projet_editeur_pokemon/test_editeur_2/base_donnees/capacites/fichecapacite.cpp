#include "base_donnees/capacites/fichecapacite.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QRegExp>
const HashMap<QString,QString> FicheCapacite::_descriptions_capacites_=FicheCapacite::init_descriptions_capacites();
HashMap<QString,QString> FicheCapacite::init_descriptions_capacites(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/descriptions_capacites");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/descriptions_capacites.txt");
#endif
	QStringList lignes_=contenu_.split("\n");
	HashMap<QString,QString> descriptions_capacites_;
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		QString cle_=infos_.takeFirst();
		descriptions_capacites_.ajouter_cle_valeur(cle_,infos_.join("\t"));
	}
	return descriptions_capacites_;
}

FicheCapacite::FicheCapacite(const QStringList& _effets){
	anti_climat=_effets.contains("ANTI_CLIMAT");
	anti_fuite=_effets.contains("ANTI_FUITE");
	QStringList effets_=_effets.filter(QRegExp("^MULT_DEGATS\\[<"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		QString taux_=exp_taux_.capturedTexts()[0];
		coeff_att_peu_eff=Taux::parse_taux(taux_);
	}
	effets_=_effets.filter(QRegExp("ANTI_FUITE_SI_(NE_)?POSSEDE_TYPE"));
	anti_fuite_type.first=false;
	if(!effets_.isEmpty()){
		anti_fuite_type.first=effets_[0].contains("ANTI_FUITE_SI_POSSEDE_TYPE");
		anti_fuite_type.second=QStringList(effets_[0].split(QRegExp("(\\W)+"),QString::SkipEmptyParts).mid(1));
	}else{
		anti_fuite_type.second=QStringList();
	}
	effets_=_effets.filter(QRegExp("^ANTI_IMMU_ATTAQUE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList types_=QStringList(e.split(QRegExp("(\\W)+"),QString::SkipEmptyParts).mid(1));
			anti_immu_attaque<<QPair<QString,QString>(types_[0],types_[1]);
		}
	}
	effets_=_effets.filter(QRegExp("^BAISSE_STATISTIQUE_ADVERSAIRE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+"),QString::SkipEmptyParts).mid(1));
			infos_[1].chop(1);
			baisse_statistique_adversaire.ajouter_cle_valeur(infos_[0],(qint8)infos_[1].toInt());
		}
	}
	bloque_conso_baies_adv=_effets.contains("BLOQUE_CONSO_BAIES_ADV");
	effets_=_effets.filter(QRegExp("^CHANGEMENT_TYPE_SI_CLIMAT"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("(\\W)+"),QString::SkipEmptyParts).mid(1));
			changement_type_si_climat.ajouter_cle_valeur(infos_[0],infos_[1]);
		}
	}
	changement_type_si_degats=_effets.contains("CHANGEMENT_TYPE_SI_DEGATS");
	effets_=_effets.filter(QRegExp("^CLIMAT"));
	if(!effets_.isEmpty()){
		climat=effets_[0].split(QRegExp("(\\W)+"))[1];
	}
	copie_capacite=_effets.contains("COPIE_CAPACITE");
	effets_=_effets.filter(QRegExp("^DEGATS_RECUL_ADV\\["));
	if(!effets_.isEmpty()){//TODO editer fiche
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		QString taux_=exp_taux_.capturedTexts()[0];
		degats_recul_adv=Taux::parse_taux(taux_);
	}else{
		degats_recul_adv=Taux(0);
	}
	effets_=_effets.filter(QRegExp("^DEGATS_RECUL_ADV_SI_KO"));
	if(!effets_.isEmpty()){//TODO editer fiche
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		QString taux_=exp_taux_.capturedTexts()[0];
		degats_recul_adv_si_ko=Taux::parse_taux(taux_);
	}else{
		degats_recul_adv_si_ko=Taux(0);
	}
	effets_=_effets.filter(QRegExp("^DEGATS_STATUT"));
	if(!effets_.isEmpty()){
		degats_statut.first=effets_[0].split(QRegExp("(\\W)+"))[1];
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		QString taux_=exp_taux_.capturedTexts()[0];
		degats_statut.second=Taux::parse_taux(taux_);
	}else{
		degats_statut.second=Taux(0);
	}
	bool suppr_=false;//TODO a supprimer
	effets_=_effets.filter(QRegExp("^DIMINUE_PAS_ECLOSION"));
	if(!effets_.isEmpty()){
		diminue_pas_eclosion=effets_[0].split(QRegExp("(\\W)+"))[1].toInt();
	}else{
		diminue_pas_eclosion=0;
	}
	effets_=_effets.filter(QRegExp("^DIVISE_TOUR_SOMMEIL"));
	if(!effets_.isEmpty()){
		divise_tour_sommeil=effets_[0].split(QRegExp("(\\W)+"))[1].toInt();
	}else{
		divise_tour_sommeil=0;
	}
	effets_=_effets.filter(QRegExp("^GAIN_PV_SI_CLIMAT"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			gain_pv_si_climat.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^GAIN_PV_TYPE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			gain_pv_type.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^IGN_CAPACITE"));
	if(!effets_.isEmpty()){
		ign_capacite=QStringList(effets_[0].split(QRegExp("([\\[\\],])+")).mid(1));
		ign_capacite.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^IGNORE_ATTAQUE"));
	if(!effets_.isEmpty()){
		ignore_attaque=QStringList(effets_[0].split(QRegExp("([\\[\\],])+")).mid(1));
		ignore_attaque.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^IGNORE_BOOST_STATISTIQUE_ADV"));
	if(!effets_.isEmpty()){
		ignore_boost_statistique_adv=QStringList(effets_[0].split(QRegExp("([\\[\\],])+")).mid(1));
		ignore_boost_statistique_adv.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^IMMU_ANTI_FUITE"));
	if(!effets_.isEmpty()){
		immu_anti_fuite=QStringList(effets_[0].split(QRegExp("([\\[\\],])+")).mid(1));
		immu_anti_fuite.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^IMMU_ATTAQUE\\["));
	if(!effets_.isEmpty()){
		immu_attaque=QStringList(effets_[0].split(QRegExp("([\\[\\],])+")).mid(1));
		immu_attaque.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^IMMU_ATTAQUE_TYPE"));
	if(!effets_.isEmpty()){
		immu_attaque_type=QStringList(effets_[0].split(QRegExp("([\\[\\],])+")).mid(1));
		immu_attaque_type.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^IMMU_BAISSE_STATISTIQUE\\["));
	if(!effets_.isEmpty()){
		immu_baisse_statistique=QStringList(effets_[0].split(QRegExp("([\\[\\],])+")).mid(1));
		immu_baisse_statistique.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^IMMU_BAISSE_STATISTIQUE_SI_STATUT"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			immu_baisse_statistique_si_statut<<QPair<QString,QString>(infos_[0],infos_[1]);
		}
	}
	effets_=_effets.filter(QRegExp("^IMMU_CLIMAT"));
	if(!effets_.isEmpty()){
		immu_climat=QStringList(effets_[0].split(QRegExp("([\\[\\],])+")).mid(1));
		immu_climat.removeAll("");
	}
	immu_cc=_effets.contains("IMMU_CC");
	immu_degats_attaques_piegeantes=_effets.contains("IMMU_DEGATS_ATTAQUES_PIEGEANTES");
	immu_degats_cauchemar=_effets.contains("IMMU_DEGATS_CAUCHEMAR");
	immu_degats_malediction_2=_effets.contains("IMMU_DEGATS_MALEDICTION_2");
	immu_degats_part=_effets.contains("IMMU_DEGATS_PART");
	immu_degats_recul=_effets.contains("IMMU_DEGATS_RECUL");
	immu_degats_vampigraine=_effets.contains("IMMU_DEGATS_VAMPIGRAINE");
	effets_=_effets.filter(QRegExp("^IMMU_CAPACITE"));
	if(!effets_.isEmpty()){
		immu_capacite=QStringList(effets_[0].split(QRegExp("([\\[\\],])+")).mid(1));
		immu_capacite.removeAll("");
	}
	immu_degats_recul=_effets.contains("IMMU_DEGATS_RECUL");
	immu_paralysie_totale=_effets.contains("IMMU_PARALYSIE_TOTALE");
	immu_picots=_effets.contains("IMMU_PICOTS");
	immu_piege_de_roc=_effets.contains("IMMU_PIEGE_DE_ROC");
	immu_recharger_tour=_effets.contains("IMMU_RECHARGER_TOUR");
	lenteur_vitesse=_effets.contains("LENTEUR_VITESSE");
	nombre_coups=_effets.contains("NOMBRE_COUPS");
	passe_abri=_effets.contains("PASSE_ABRI");
	plaque=_effets.contains("PLAQUE");
	soin_statut_si_switch=_effets.contains("SOIN_STATUT_SI_SWITCH");
	touche_pseudo_invulnerable=_effets.contains("TOUCHE_PSEUDO_INVULNERABLE");
	momie=_effets.contains("MOMIE");
	effets_=_effets.filter(QRegExp("^MULT_DEGATS_CC"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_degats_cc=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_DEGATS_PART"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_degats_part=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_PROBA_CC"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_proba_cc=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_TOUTES_ATTAQUES"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_puissance_toutes_attaques=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_STAB"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_stab=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_VARIATION_CRAN"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_variation_cran=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^SOIN_TAUX_PVMAX_SI_SWITCH"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		soin_taux_pvmax_si_switch=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^UTILISE_BAIE_SOIN_PV"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		utilise_baie_soin_pv=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_DEGATS_ADV"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			mult_degats_adv.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_DEGATS_STATUT"));
	if(!effets_.isEmpty()){//Si effets_ n'est pas vide, alors les coeffs ne valent pas 1, il faudra tester l'appartenance d'un statut à la HashMap
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			mult_degats_statut.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}//Sinon les coeffs de degats de statut sont à 1.
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_ATTAQUE_CATEGORIE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			mult_puissance_attaque_categorie.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_ATTAQUE_TYPE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			mult_puissance_attaque_type.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_PART"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			mult_statistique_part.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_DERNIER"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			mult_statistique_si_dernier.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_PERD_OBJET"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			mult_statistique_si_perd_objet.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_DEGATS_RECU\\[(>|<)"));
	if(!effets_.isEmpty()){//TODO changer fiche
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			mult_degats_recu.ajouter_cle_valeur(e.contains(">"),Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_ATTAQUE_SI_EGALITE_GENRE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			mult_puissance_attaque_si_egalite_genre.ajouter_cle_valeur(infos_[0].contains("EGAL"),Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_PROBA_EFFET_SEC"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			mult_proba_effet_sec.ajouter_cle_valeur(e.contains("LANCEUR"),Taux::parse_taux(infos_[0]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_ADV_KO"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			infos_[1].chop(1);
			mult_statistique_si_adv_ko.ajouter_cle_valeur(infos_[0],(qint8)infos_[1].toInt());
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_BAISSE_STATISTIQUE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			infos_[1].chop(1);
			mult_statistique_si_baisse_statistique.ajouter_cle_valeur(infos_[0],(qint8)infos_[1].toInt());
		}
	}
	effets_=_effets.filter(QRegExp("^IMMU_STATUT"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			if(e.contains("SI_CLIMAT")){
				QList<QString> cles_=immu_statut.cles();
				if(cles_.contains(infos_[0])){
					QStringList *liste_=immu_statut.valeur(infos_[0],suppr_);
					liste_->append(infos_[1]);
				}else{
					QStringList liste_;
					liste_<<infos_[1];
					immu_statut.ajouter_cle_valeur(infos_[0],liste_);
				}
			}else if(e.contains("SI_NON_CLIMAT")){
				QList<QString> cles_=immu_statut.cles();
				if(cles_.contains("")){
					QStringList *liste_=immu_statut.valeur("",suppr_);
					liste_->append(infos_[0]);
				}else{
					QStringList liste_;
					liste_<<infos_[0];
					immu_statut.ajouter_cle_valeur("",liste_);
				}
			}else{
				infos_.removeAll("");
				foreach(QString s,infos_){
					QList<QString> cles_=immu_statut.cles();
					foreach(QString c,cles_){
						QStringList *liste_=immu_statut.valeur(c,suppr_);
						if(!liste_->contains(s)){
							liste_->append(s);
						}
					}
					foreach(QString c,Import::_noms_climats_){
						QString cl_=c.split("\t")[Import::_indice_francais_];
						if(!cles_.contains(cl_)){
							QStringList liste_;
							liste_<<s;
							immu_statut.ajouter_cle_valeur(cl_,liste_);
						}
					}
					if(!cles_.contains("")){
						QStringList liste_;
						liste_<<s;
						immu_statut.ajouter_cle_valeur("",liste_);
					}
				}
			}
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_ATTAQUE\\[\\["));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QRegExp exp_ens_("\\[(\\w)+(,(\\w)+)*");
			e.indexOf(exp_ens_);
			QRegExp exp_taux_("[0-9]+(/[0-9])?");
			e.indexOf(exp_taux_);
			foreach(QString a,exp_ens_.capturedTexts()[0].mid(1).split(",")){
				mult_puissance_attaques.ajouter_cle_valeur(a,Taux::parse_taux(exp_taux_.capturedTexts()[0]));
			}
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_SI\\[<="));
	if(!effets_.isEmpty()){
		QRegExp exp_ens_("<=[0-9]+");
		effets_[0].indexOf(exp_ens_);
		mult_puissance_si_inf_eg.first=exp_ens_.capturedTexts()[0].mid(2).toInt();
		QRegExp exp_taux_("[0-9]+(/[0-9])?");
		effets_[0].indexOf(exp_taux_,effets_[0].indexOf(","));
		mult_puissance_si_inf_eg.second=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_TYPE_SI_CLIMAT"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			QList<QPair<QString,QString> > cles_=mult_puissance_type_si_climat.cles();
			QPair<QString,QString> pair_=QPair<QString,QString>(infos_[0],infos_[1]);
			if(cles_.contains(pair_)){
				Taux *taux_=mult_puissance_type_si_climat.valeur(pair_,suppr_);
				QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
				e.indexOf(exp_taux_);
				*taux_=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
			}else{
				QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
				e.indexOf(exp_taux_);
				mult_puissance_type_si_climat.ajouter_cle_valeur(pair_,Taux::parse_taux(exp_taux_.capturedTexts()[0]));
			}
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_TYPE\\["));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			QString pair_=infos_[0];
			QPair<Taux,Taux> taux_;
			QRegExp exp_taux_("[0-9]+(/[0-9])?");
			int ind_=e.indexOf(exp_taux_);
			QString chaine_=exp_taux_.capturedTexts()[0];
			taux_.first=Taux::parse_taux(chaine_);
			e.indexOf(exp_taux_,ind_+chaine_.size());
			taux_.second=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
			mult_puissance_type_inf_eg.ajouter_cle_valeur(pair_,taux_);
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE\\["));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			QString pair_=infos_[0];
			QPair<Taux,bool> valeur_;
			valeur_.second=!infos_[1].contains("C");
			infos_[1].remove("C");
			valeur_.first=Taux::parse_taux(infos_[1]);
			mult_statistique.ajouter_cle_valeur(pair_,valeur_);
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_CATEGORIE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			QPair<QString,QString> pair_=QPair<QString,QString>(infos_[0],infos_[1]);
			Taux valeur_=Taux::parse_taux(infos_[2]);
			mult_statistique_si_categorie.ajouter_cle_valeur(pair_,valeur_);
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_CLIMAT"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			QPair<QString,QString> pair_=QPair<QString,QString>(infos_[0],infos_[1]);
			Taux valeur_=Taux::parse_taux(infos_[2]);
			mult_statistique_si_climat.ajouter_cle_valeur(pair_,valeur_);
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_STATISTIQUE_ADV"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			QString pair_=infos_[0];
			QPair<QString,qint8> valeur_;
			valeur_.first=infos_[3];
			infos_[4].chop(1);
			valeur_.second=(qint8)infos_[4].toInt();
			mult_statistique_si_statistique_adv.first.ajouter_cle_valeur(pair_,valeur_);
			mult_statistique_si_statistique_adv.second=QPair<QString,QString>(infos_[1],infos_[2]);
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_STATUT"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			QString statistique_=infos_[0];
			QString statut_=infos_[1];
			if(e.contains(QRegExp("[0-9]+C"))){
				infos_[2].chop(1);
				qint8 cran_=(qint8)infos_[2].toInt();
				mult_statistique_si_statut_cran<<QPair<QString,QPair<QString,qint8> >(statistique_,QPair<QString,qint8>(statut_,cran_));
			}else{
				mult_statistique_si_statut_coeff<<QPair<QString,QPair<QString,Taux> >(statistique_,QPair<QString,Taux>(statut_,Taux::parse_taux(infos_[2])));
			}
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_TOUCHE_CATEGORIE"));
	if(!effets_.isEmpty()){//TODO changer attribut
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			QList<QString> cles_=mult_statistique_si_touche_categorie.cles();
			if(!cles_.contains(infos_[0])){
				QList<QPair<QString,qint8> > valeur_;
				valeur_<<QPair<QString,qint8>("",0);
				valeur_.last().first=infos_[1];
				infos_[2].chop(1);
				valeur_.last().second=(qint8)infos_[2].toInt();
				mult_statistique_si_touche_categorie.ajouter_cle_valeur(infos_[0],valeur_);
			}else{
				QList<QPair<QString,qint8> > *valeur_=mult_statistique_si_touche_categorie.valeur(infos_[0],suppr_);
				(*valeur_)<<QPair<QString,qint8>("",0);
				valeur_->last().first=infos_[1];
				infos_[2].chop(1);
				valeur_->last().second=(qint8)infos_[2].toInt();
			}
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_TOUCHE_TYPE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			QPair<QString,qint8> valeur_;
			valeur_.first=infos_[1];
			infos_[2].chop(1);
			valeur_.second=(qint8)infos_[2].toInt();
			mult_statistique_si_touche_type.ajouter_cle_valeur(infos_[0],valeur_);
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_TAUX_DEGATS_ADV"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_(",(-)?[0-9]+");
		effets_[0].indexOf(exp_taux_);
		mult_taux_degats_adv_absorb=(char)exp_taux_.capturedTexts()[0].mid(1).toInt();
	}else{
		mult_taux_degats_adv_absorb=0;
	}
	effets_=_effets.filter(QRegExp("^NB_PP_UTILISE"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+");
		effets_[0].indexOf(exp_taux_);
		nb_pp_utilise=exp_taux_.capturedTexts()[0].toInt();
	}else{
		nb_pp_utilise=0;
	}
	effets_=_effets.filter(QRegExp("^SOMME_PRIO"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			somme_prio.ajouter_cle_valeur(infos_[0],(uchar)infos_[1].toUInt());
		}
	}
	effets_=_effets.filter(QRegExp("^STATISTIQUES_MAXIMALES_SI_CC"));
	if(!effets_.isEmpty()){
		statistiques_maximales_si_cc=QStringList(effets_[0].split(QRegExp("([\\[\\],])+")).mid(1));
		statistiques_maximales_si_cc.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^STATUT_OK\\["));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		QString taux_=exp_taux_.capturedTexts()[0];
		statut_ok=Taux::parse_taux(taux_);
	}
	effets_=_effets.filter(QRegExp("^STATUT_OK_PART"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		QString taux_=exp_taux_.capturedTexts()[0];
		statut_ok_part=Taux::parse_taux(taux_);
	}
	effets_=_effets.filter(QRegExp("^STATUT\\["));
	if(!effets_.isEmpty()){
		QRegExp exp_loi_("\\[\\[(\\w)+,[0-9]+(/[0-9]+)?(;(\\w)+,[0-9]+(/[0-9]+)?)*");
		int ind_=effets_[0].indexOf(exp_loi_);
		QString loi_=exp_loi_.capturedTexts()[0].mid(2);
		QStringList statuts_pr_=loi_.split(";");
		MonteCarlo<QString> loi_proba_statuts_;
		MonteCarlo<QString> loi_proba_statuts_2_;
		Entier ppcm_=Entier(1);
		foreach(QString s,statuts_pr_){
			ppcm_=ppcm_.ppcm(Taux::parse_taux(s.split(",")[1]).gdenominateur());
		}
		Taux taux_ppcm_=Taux(ppcm_);
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_,ind_+loi_.size()+3);
		Taux proba_gl_=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
		MonteCarlo<QString> loi_proba_ok_;
		loi_proba_ok_.ajouter_event(QPair<QString,Entier>("OK",Entier(1)));
		Entier effectif_actif_=proba_gl_.gnumerateur();
		Entier effectif_inactif_=Entier(proba_gl_.gdenominateur())-effectif_actif_;
		Entier somme_effs_act_=Entier(0);
		foreach(QString s,statuts_pr_){
			Taux proba_statut_=Taux::parse_taux(s.split(",")[1]);
			Entier eff_p_act_=(proba_statut_*taux_ppcm_).partie_entiere();
			somme_effs_act_=somme_effs_act_+eff_p_act_;
			loi_proba_statuts_.ajouter_event(QPair<QString,Entier>(s.split(",")[0],eff_p_act_));
			statut_simple.ajouter_event(QPair<QString,Entier>(s.split(",")[0],effectif_actif_*eff_p_act_));
		}
		statut_simple.ajouter_event(QPair<QString,Entier>("OK",effectif_inactif_*somme_effs_act_));
		statut_simple.simplifier();
		statut.ajouter_event(QPair<MonteCarlo<QString>,Entier>(loi_proba_statuts_,effectif_actif_));
		statut.ajouter_event(QPair<MonteCarlo<QString>,Entier>(loi_proba_ok_,effectif_inactif_));
	}
	effets_=_effets.filter(QRegExp("^TRANSFERT_STATUT"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("([\\[\\],])+")).mid(1));
			transfert_statut.ajouter_cle_valeur(infos_[0],infos_[1]);
		}
	}
	effets_=_effets.filter(QRegExp("^TYPE_ATTAQUES"));
	if(!effets_.isEmpty()){
		type_attaques=effets_[0].split(QRegExp("([\\[\\],])+"))[1];
	}
}

QString FicheCapacite::description(int _langue)const{
	QString retour_;
	QString cle_;
	if(anti_climat){
		cle_="ANTI_CLIMAT";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(anti_fuite){
		cle_="ANTI_FUITE";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(bloque_conso_baies_adv){
		cle_="BLOQUE_CONSO_BAIES_ADV";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(changement_type_si_degats){
		cle_="CHANGEMENT_TYPE_SI_DEGATS";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(copie_capacite){
		cle_="COPIE_CAPACITE";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_cc){
		cle_="IMMU_CC";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_degats_attaques_piegeantes){
		cle_="IMMU_DEGATS_ATTAQUES_PIEGEANTES";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_degats_cauchemar){
		cle_="IMMU_DEGATS_CAUCHEMAR";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_degats_malediction_2){
		cle_="IMMU_DEGATS_MALEDICTION_2";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_degats_part){
		cle_="IMMU_DEGATS_PART";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_degats_recul){
		cle_="IMMU_DEGATS_RECUL";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_degats_vampigraine){
		cle_="IMMU_DEGATS_VAMPIGRAINE";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_paralysie_totale){
		cle_="IMMU_PARALYSIE_TOTALE";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_picots){
		cle_="IMMU_PICOTS";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_piege_de_roc){
		cle_="IMMU_PIEGE_DE_ROC";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_recharger_tour){
		cle_="IMMU_RECHARGER_TOUR";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(lenteur_vitesse){
		cle_="LENTEUR_VITESSE";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(momie){
		cle_="MOMIE";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(nombre_coups){
		cle_="NOMBRE_COUPS";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(passe_abri){
		cle_="PASSE_ABRI";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(plaque){
		cle_="PLAQUE";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(soin_statut_si_switch){
		cle_="SOIN_STATUT_SI_SWITCH";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(touche_pseudo_invulnerable){
		cle_="TOUCHE_PSEUDO_INVULNERABLE";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(mult_taux_degats_adv_absorb!=0){
		cle_="MULT_TAUX_DEGATS_ADV";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(degats_recul_adv!=Taux(0)){
		cle_="DEGATS_RECUL_ADV";
		QStringList args_;
		args_<<degats_recul_adv.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(degats_recul_adv_si_ko!=Taux(0)){
		cle_="DEGATS_RECUL_ADV_SI_KO";
		QStringList args_;
		args_<<degats_recul_adv_si_ko.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_degats_cc!=Taux(0)){
		cle_="MULT_DEGATS_CC";
		QStringList args_;
		args_<<mult_degats_cc.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_degats_part!=Taux(0)){
		cle_="MULT_DEGATS_PART";
		QStringList args_;
		args_<<mult_degats_part.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_proba_cc!=Taux(0)){
		cle_="MULT_PROBA_CC";
		QStringList args_;
		args_<<mult_proba_cc.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_puissance_toutes_attaques!=Taux(0)){
		cle_="MULT_PUISSANCE_TOUTES_ATTAQUES";
		QStringList args_;
		args_<<mult_puissance_toutes_attaques.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_stab!=Taux(0)){
		cle_="MULT_STAB";
		QStringList args_;
		args_<<mult_stab.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(coeff_att_peu_eff!=Taux(0)){
		cle_="MULT_DEGATS[<";
		QStringList args_;
		args_<<coeff_att_peu_eff.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_variation_cran!=Taux(0)){
		cle_="MULT_VARIATION_CRAN";
		QStringList args_;
		args_<<mult_variation_cran.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(soin_taux_pvmax_si_switch!=Taux(0)){
		cle_="SOIN_TAUX_PVMAX_SI_SWITCH";
		QStringList args_;
		args_<<soin_taux_pvmax_si_switch.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(utilise_baie_soin_pv!=Taux(0)){
		cle_="UTILISE_BAIE_SOIN_PV";
		QStringList args_;
		args_<<utilise_baie_soin_pv.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!ign_capacite.isEmpty()){
		cle_="IGN_CAPACITE";
		QStringList args_;
		foreach(QString c,ign_capacite){
			args_<<Utilitaire::traduire(Import::_noms_capacites_,c,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!ignore_attaque.isEmpty()){
		cle_="IGNORE_ATTAQUE";
		QStringList args_;
		foreach(QString c,ignore_attaque){
			args_<<Utilitaire::traduire(Import::_noms_attaques_,c,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!ignore_boost_statistique_adv.isEmpty()){
		cle_="IGNORE_BOOST_STATISTIQUE_ADV";
		QStringList args_;
		foreach(QString c,ignore_boost_statistique_adv){
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,c,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!immu_anti_fuite.isEmpty()){
		cle_="IMMU_ANTI_FUITE";
		QStringList args_;
		foreach(QString c,immu_anti_fuite){
			args_<<Utilitaire::traduire(Import::_noms_capacites_,c,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!immu_attaque.isEmpty()){
		cle_="IMMU_ATTAQUE";
		QStringList args_;
		foreach(QString c,immu_attaque){
			args_<<Utilitaire::traduire(Import::_noms_attaques_,c,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!immu_attaque_type.isEmpty()){
		cle_="IMMU_ATTAQUE_TYPE";
		QStringList args_;
		foreach(QString c,immu_attaque_type){
			args_<<Utilitaire::traduire(Import::_noms_types_,c,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!immu_baisse_statistique.isEmpty()){
		cle_="IMMU_BAISSE_STATISTIQUE";
		QStringList args_;
		foreach(QString c,immu_baisse_statistique){
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,c,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!immu_capacite.isEmpty()){
		cle_="IMMU_CAPACITE";
		QStringList args_;
		foreach(QString c,immu_capacite){
			args_<<Utilitaire::traduire(Import::_noms_capacites_,c,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!immu_climat.isEmpty()){
		cle_="IMMU_CLIMAT";
		QStringList args_;
		foreach(QString c,immu_climat){
			args_<<Utilitaire::traduire(Import::_noms_climats_,c,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!statistiques_maximales_si_cc.isEmpty()){
		cle_="STATISTIQUES_MAXIMALES_SI_CC";
		QStringList args_;
		foreach(QString c,statistiques_maximales_si_cc){
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,c,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	QList<bool> cles_=mult_proba_effet_sec.cles();;
	if(!cles_.isEmpty()){
		foreach(bool e,cles_){
			QStringList args_;
			if(e){
				cle_="MULT_PROBA_EFFET_SEC_LANCEUR";
			}else{
				cle_="MULT_PROBA_EFFET_SEC";
			}
			args_<<mult_proba_effet_sec.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_=mult_degats_recu.cles();;
	if(!cles_.isEmpty()){
		foreach(bool e,cles_){
			QStringList args_;
			if(e){
				cle_="MULT_DEGATS_RECU[>";
			}else{
				cle_="MULT_DEGATS_RECU[<";
			}
			args_<<mult_degats_recu.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_=mult_puissance_attaque_si_egalite_genre.cles();;
	if(!cles_.isEmpty()){
		foreach(bool e,cles_){
			QStringList args_;
			if(e){
				cle_="MULT_PUISSANCE_ATTAQUE_SI_EGALITE_GENRE[EGAL";
			}else{
				cle_="MULT_PUISSANCE_ATTAQUE_SI_EGALITE_GENRE[OPPOSE";
			}
			args_<<mult_puissance_attaque_si_egalite_genre.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(climat!=""){
		cle_="CLIMAT";
		QStringList args_;
		args_<<Utilitaire::traduire(Import::_noms_climats_,climat,_langue);
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(type_attaques!=""){
		cle_="TYPE_ATTAQUES";
		QStringList args_;
		args_<<Utilitaire::traduire(Import::_noms_types_,type_attaques,_langue);
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(diminue_pas_eclosion>0){
		cle_="DIMINUE_PAS_ECLOSION";
		QStringList args_;
		args_<<QString::number(diminue_pas_eclosion);
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(divise_tour_sommeil>0){
		cle_="DIVISE_TOUR_SOMMEIL";
		QStringList args_;
		args_<<QString::number(divise_tour_sommeil);
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(nb_pp_utilise>0){
		cle_="NB_PP_UTILISE";
		QStringList args_;
		args_<<QString::number(nb_pp_utilise);
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	QList<QString> cles_ch_=gain_pv_si_climat.cles();
	if(!cles_ch_.isEmpty()){
		cle_="GAIN_PV_SI_CLIMAT";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_climats_,e,_langue);
			args_<<gain_pv_si_climat.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_degats_adv.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_DEGATS_ADV";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_types_,e,_langue);
			args_<<mult_degats_adv.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_degats_statut.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_DEGATS_STATUT";
		foreach(QString e,cles_ch_){
			QStringList args_;
			if(Utilitaire::traduisible(Import::_noms_statuts_,e)){
				args_<<Utilitaire::traduire(Import::_noms_statuts_,e,_langue);
			}else{
				args_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,e,_langue);
			}
			args_<<mult_degats_statut.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_puissance_attaque_categorie.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_PUISSANCE_ATTAQUE_CATEGORIE";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_categories_,e,_langue);
			args_<<mult_puissance_attaque_categorie.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_puissance_attaques.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_PUISSANCE_ATTAQUE";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_attaques_,e,_langue);
			args_<<mult_puissance_attaques.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_puissance_attaque_type.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_PUISSANCE_ATTAQUE_TYPE";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_types_,e,_langue);
			args_<<mult_puissance_attaque_type.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique_part.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_STATISTIQUE_PART";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e,_langue);
			args_<<mult_statistique_part.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique_si_dernier.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_STATISTIQUE_SI_DERNIER";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e,_langue);
			args_<<mult_statistique_si_dernier.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=gain_pv_type.cles();
	if(!cles_ch_.isEmpty()){
		cle_="GAIN_PV_TYPE";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_types_,e,_langue);
			args_<<gain_pv_type.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique_si_perd_objet.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_STATISTIQUE_SI_PERD_OBJET";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e,_langue);
			args_<<mult_statistique_si_perd_objet.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=immu_statut.cles();
	if(!cles_ch_.isEmpty()){
		foreach(QString e,cles_ch_){
			if(e==""){
				cle_="IMMU_STATUT_SI_NON_CLIMAT";
				foreach(QString v,immu_statut.valeur(e)){
					QStringList args_;
					if(Utilitaire::traduisible(Import::_noms_statuts_,v)){
						args_<<Utilitaire::traduire(Import::_noms_statuts_,v,_langue);
					}else{
						args_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,v,_langue);
					}
					retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
				}
			}else{
				cle_="IMMU_STATUT_SI_CLIMAT";
				foreach(QString v,immu_statut.valeur(e)){
					QStringList args_;
					args_<<Utilitaire::traduire(Import::_noms_climats_,e,_langue);
					if(Utilitaire::traduisible(Import::_noms_statuts_,v)){
						args_<<Utilitaire::traduire(Import::_noms_statuts_,v,_langue);
					}else{
						args_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,v,_langue);
					}
					retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
				}
			}
		}
	}
	if(!anti_immu_attaque.isEmpty()){
		typedef QPair<QString,QString> TypeType;
		foreach(TypeType e,anti_immu_attaque){
			QStringList args_;
			cle_="ANTI_IMMU_ATTAQUE";
			args_<<Utilitaire::traduire(Import::_noms_types_,e.first,_langue);
			args_<<Utilitaire::traduire(Import::_noms_types_,e.second,_langue);
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=changement_type_si_climat.cles();
	if(!cles_ch_.isEmpty()){
		foreach(QString e,cles_ch_){
			QStringList args_;
			cle_="CHANGEMENT_TYPE_SI_CLIMAT";
			args_<<Utilitaire::traduire(Import::_noms_climats_,e,_langue);
			args_<<Utilitaire::traduire(Import::_noms_types_,changement_type_si_climat.valeur(e),_langue);
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=transfert_statut.cles();
	if(!cles_ch_.isEmpty()){
		foreach(QString e,cles_ch_){
			QStringList args_;
			cle_="TRANSFERT_STATUT";
			if(Utilitaire::traduisible(Import::_noms_statuts_,e)){
				args_<<Utilitaire::traduire(Import::_noms_statuts_,e,_langue);
			}else{
				args_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,e,_langue);
			}
			QString statut_recu_=transfert_statut.valeur(e);
			if(Utilitaire::traduisible(Import::_noms_statuts_,statut_recu_)){
				args_<<Utilitaire::traduire(Import::_noms_statuts_,statut_recu_,_langue);
			}else{
				args_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,statut_recu_,_langue);
			}
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=baisse_statistique_adversaire.cles();
	if(!cles_ch_.isEmpty()){
		foreach(QString e,cles_ch_){
			QStringList args_;
			cle_="BAISSE_STATISTIQUE_ADVERSAIRE";
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e,_langue);
			args_<<QString::number(baisse_statistique_adversaire.valeur(e));
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique_si_adv_ko.cles();
	if(!cles_ch_.isEmpty()){
		foreach(QString e,cles_ch_){
			QStringList args_;
			cle_="MULT_STATISTIQUE_SI_ADV_KO";
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e,_langue);
			args_<<QString::number(mult_statistique_si_adv_ko.valeur(e));
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique_si_baisse_statistique.cles();
	if(!cles_ch_.isEmpty()){
		foreach(QString e,cles_ch_){
			QStringList args_;
			cle_="MULT_STATISTIQUE_SI_BAISSE_STATISTIQUE";
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e,_langue);
			args_<<QString::number(mult_statistique_si_baisse_statistique.valeur(e));
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique_si_touche_categorie.cles();
	if(!cles_ch_.isEmpty()){
		typedef QPair<QString,qint8> ValPart;
		foreach(QString e,cles_ch_){
			foreach(ValPart v,mult_statistique_si_touche_categorie.valeur(e)){
				QStringList args_;
				cle_="MULT_STATISTIQUE_SI_TOUCHE_CATEGORIE";
				args_<<Utilitaire::traduire(Import::_noms_categories_,e,_langue);
				args_<<Utilitaire::traduire(Import::_noms_statistiques_,v.first,_langue);
				args_<<QString::number(v.second);
				retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
			}
		}
	}
	cles_ch_=mult_statistique_si_touche_type.cles();
	if(!cles_ch_.isEmpty()){
		foreach(QString e,cles_ch_){
			QStringList args_;
			cle_="MULT_STATISTIQUE_SI_TOUCHE_TYPE";
			args_<<Utilitaire::traduire(Import::_noms_types_,e,_langue);
			QPair<QString,qint8> valeur_=mult_statistique_si_touche_type.valeur(e);
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,valeur_.first,_langue);
			args_<<QString::number(valeur_.second);
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	QList<QPair<QString,QString> > cles_cpl_=mult_puissance_type_si_climat.cles();
	typedef QPair<QString,QString> CleChCh;
	if(!cles_cpl_.isEmpty()){
		cle_="MULT_PUISSANCE_TYPE_SI_CLIMAT";
		foreach(CleChCh e,cles_cpl_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_climats_,e.first,_langue);
			args_<<Utilitaire::traduire(Import::_noms_types_,e.second,_langue);
			args_<<mult_puissance_type_si_climat.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_cpl_=mult_statistique_si_categorie.cles();
	if(!cles_cpl_.isEmpty()){
		cle_="MULT_STATISTIQUE_SI_CATEGORIE";
		foreach(CleChCh e,cles_cpl_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e.first,_langue);
			args_<<Utilitaire::traduire(Import::_noms_categories_,e.second,_langue);
			args_<<mult_statistique_si_categorie.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_cpl_=mult_statistique_si_climat.cles();
	if(!cles_cpl_.isEmpty()){
		cle_="MULT_STATISTIQUE_SI_CLIMAT";
		foreach(CleChCh e,cles_cpl_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e.first,_langue);
			args_<<Utilitaire::traduire(Import::_noms_climats_,e.second,_langue);
			args_<<mult_statistique_si_climat.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique.cles();
	if(!cles_ch_.isEmpty()){
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e,_langue);
			QPair<Taux,bool> valeur_=mult_statistique.valeur(e);
			args_<<valeur_.first.chaine();
			if(valeur_.second){
				cle_="MULT_STATISTIQUE";
			}else{
				cle_="MULT_STATISTIQUE[C";
			}
			args_<<QString::number(valeur_.second);
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_puissance_type_inf_eg.cles();
	if(!cles_ch_.isEmpty()){
		foreach(QString e,cles_ch_){
			QStringList args_;
			cle_="MULT_PUISSANCE_TYPE_INF_EG";
			args_<<Utilitaire::traduire(Import::_noms_types_,e,_langue);
			QPair<Taux,Taux> valeur_=mult_puissance_type_inf_eg.valeur(e);
			args_<<valeur_.first.chaine();
			args_<<valeur_.second.chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique_si_statistique_adv.first.cles();
	if(!cles_ch_.isEmpty()){
		foreach(QString e,cles_ch_){
			QStringList args_;
			cle_="MULT_STATISTIQUE_SI_STATISTIQUE_ADV["+e;
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,mult_statistique_si_statistique_adv.second.second,_langue);
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,mult_statistique_si_statistique_adv.second.first,_langue);
			QPair<QString,qint8> valeur_=mult_statistique_si_statistique_adv.first.valeur(e);
			args_<<QString::number(valeur_.second);
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,valeur_.first,_langue);
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=somme_prio.cles();
	if(!cles_ch_.isEmpty()){
		cle_="SOMME_PRIO";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_categories_,e,_langue);
			args_<<QString::number(somme_prio.valeur(e));
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(!mult_statistique_si_statut_cran.isEmpty()){
		typedef QPair<QString,QPair<QString,qint8> > StatistiqueStatut;
		foreach(StatistiqueStatut e,mult_statistique_si_statut_cran){
			QStringList args_;
			if(Utilitaire::traduisible(Import::_noms_statuts_,e.second.first)){
				args_<<Utilitaire::traduire(Import::_noms_statuts_,e.second.first,_langue);
			}else{
				args_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,e.second.first,_langue);
			}
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e.first,_langue);
			cle_="MULT_STATISTIQUE_SI_STATUT_CRAN";
			args_<<QString::number(e.second.second);
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(!mult_statistique_si_statut_coeff.isEmpty()){
		typedef QPair<QString,QPair<QString,Taux> > StatistiqueStatut;
		foreach(StatistiqueStatut e,mult_statistique_si_statut_coeff){
			QStringList args_;
			if(Utilitaire::traduisible(Import::_noms_statuts_,e.second.first)){
				args_<<Utilitaire::traduire(Import::_noms_statuts_,e.second.first,_langue);
			}else{
				args_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,e.second.first,_langue);
			}
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e.first,_langue);
			cle_="MULT_STATISTIQUE_SI_STATUT_COEFF";
			args_<<e.second.second.chaine();
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(!immu_baisse_statistique_si_statut.isEmpty()){
		typedef QPair<QString,QString> StatistiqueStatut;
		foreach(StatistiqueStatut e,immu_baisse_statistique_si_statut){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_statistiques_,e.first,_langue);
			cle_="IMMU_BAISSE_STATISTIQUE_SI_STATUT";
			if(Utilitaire::traduisible(Import::_noms_statuts_,e.second)){
				args_<<Utilitaire::traduire(Import::_noms_statuts_,e.second,_langue);
			}else{
				args_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,e.second,_langue);
			}
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(!anti_fuite_type.second.isEmpty()){
		if(anti_fuite_type.first){
			cle_="ANTI_FUITE_SI_POSSEDE_TYPE";
		}else{
			cle_="ANTI_FUITE_SI_NE_POSSEDE_TYPE";
		}
		foreach(QString t,anti_fuite_type.second){
			QStringList args_;
			args_<<Utilitaire::traduire(Import::_noms_types_,t,_langue);
			retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(degats_statut.first!=""){
		cle_="DEGATS_STATUT";
		QStringList args_;
		if(Utilitaire::traduisible(Import::_noms_statuts_,degats_statut.first)){
			args_<<Utilitaire::traduire(Import::_noms_statuts_,degats_statut.first,_langue);
		}else{
			args_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,degats_statut.first,_langue);
		}
		args_<<degats_statut.second.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(statut_ok!=Taux(0)){
		cle_="STATUT_OK";
		QStringList args_;
		args_<<statut_ok.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(statut_ok_part!=Taux(0)){
		cle_="STATUT_OK_PART";
		QStringList args_;
		args_<<statut_ok_part.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_puissance_si_inf_eg.second!=Taux(0)){
		cle_="MULT_PUISSANCE_SI[<=";
		QStringList args_;
		args_<<QString::number(mult_puissance_si_inf_eg.first);
		args_<<mult_puissance_si_inf_eg.second.chaine();
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	cles_ch_=statut_simple.events();
	if(!cles_ch_.isEmpty()){
		MonteCarlo<QString> loi_;
		QList<MonteCarlo<QString> > lois_=statut.events();
		Entier eff_act_=Entier(0);
		Entier eff_inact_=Entier(1);
		typedef MonteCarlo<QString> MonteCarloString;
		foreach(MonteCarloString l,lois_){
			if(l.events().contains("OK")){
				eff_inact_=statut.proba_event(l);
			}else{
				loi_=l;
				eff_act_=statut.proba_event(l);
			}
		}
		cles_ch_=loi_.events();
		QStringList evts_;
		Entier som_=loi_.somme();
		foreach(QString e,cles_ch_){
			if(Utilitaire::traduisible(Import::_noms_statuts_,e)){
				evts_<<Utilitaire::traduire(Import::_noms_statuts_,e,_langue)+","+Taux(loi_.proba_event(e),som_).chaine();
			}else{
				evts_<<Utilitaire::traduire(Import::_noms_pseudo_statuts_,e,_langue)+","+Taux(loi_.proba_event(e),som_).chaine();
			}
		}
		QStringList args_;
		args_<<Taux(eff_act_,eff_act_+eff_inact_).chaine();
		args_<<evts_.join(";");
		QString cle_="STATUT";
		retour_+=Utilitaire::formatter(_descriptions_capacites_.valeur(cle_).split("\t")[_langue],args_);
	}
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}

bool FicheCapacite::ant_clim()const{
	return anti_climat;
}

bool FicheCapacite::ant_fuite()const{
	return anti_fuite;
}

QPair<bool,QStringList> FicheCapacite::type_anti_fuite()const{
	return anti_fuite_type;
}

QList<QPair<QString,QString> > FicheCapacite::anti_immu_att()const{
	return anti_immu_attaque;
}

HashMap<QString,qint8> FicheCapacite::baisse_stat_adv()const{
	return baisse_statistique_adversaire;
}

bool FicheCapacite::anti_conso_baies_adv()const{
	return bloque_conso_baies_adv;
}

HashMap<QString,QString> FicheCapacite::chgt_type_clim()const{
	return changement_type_si_climat;
}

bool FicheCapacite::chgt_type_deg()const{
	return changement_type_si_degats;
}

QString FicheCapacite::clim()const{
	return climat;
}

bool FicheCapacite::capac()const{
	return copie_capacite;
}

Taux FicheCapacite::deg_recul_adv()const{
	return degats_recul_adv;
}

Taux FicheCapacite::deg_recul_adv_ko()const{
	return degats_recul_adv_si_ko;
}

QPair<QString,Taux> FicheCapacite::deg_statu()const{
	return degats_statut;
}

int FicheCapacite::dim_pas_ecl()const{
	return diminue_pas_eclosion;
}

int FicheCapacite::div_tr_som()const{
	return divise_tour_sommeil;
}

HashMap<QString,Taux> FicheCapacite::gain_pv_clim()const{
	return gain_pv_si_climat;
}

HashMap<QString,Taux> FicheCapacite::gain_pv_t()const{
	return gain_pv_type;
}

QStringList FicheCapacite::capac_ign()const{
	return ign_capacite;
}

QStringList FicheCapacite::att_ign()const{
	return ignore_attaque;
}

QStringList FicheCapacite::boost_adv_ign()const{
	return ignore_boost_statistique_adv;
}

QStringList FicheCapacite::immu_anti_fuit()const{
	return immu_anti_fuite;
}

QStringList FicheCapacite::immu_att()const{
	return immu_attaque;
}

QStringList FicheCapacite::immu_att_t()const{
	return immu_attaque_type;
}

QStringList FicheCapacite::immu_bais_statis()const{
	return immu_baisse_statistique;
}

QList<QPair<QString,QString> > FicheCapacite::immu_bais_statis_stat()const{
	return immu_baisse_statistique_si_statut;
}

bool FicheCapacite::immu_c()const{
	return immu_cc;
}

QStringList FicheCapacite::immu_cl()const{
	return immu_climat;
}

bool FicheCapacite::immu_deg_att_pieg()const{
	return immu_degats_attaques_piegeantes;
}

bool FicheCapacite::immu_deg_cauch()const{
	return immu_degats_cauchemar;
}

bool FicheCapacite::immu_deg_maled()const{
	return immu_degats_malediction_2;
}

bool FicheCapacite::immu_deg_part()const{
	return immu_degats_part;
}

bool FicheCapacite::immu_deg_recul()const{
	return immu_degats_recul;
}

bool FicheCapacite::immu_deg_vampig()const{
	return immu_degats_vampigraine;
}

QStringList FicheCapacite::immu_cap()const{
	return immu_capacite;
}

bool FicheCapacite::immu_para_tot()const{
	return immu_paralysie_totale;
}

bool FicheCapacite::immu_pic()const{
	return immu_picots;
}

bool FicheCapacite::immu_pieg()const{
	return immu_piege_de_roc;
}

bool FicheCapacite::immu_recharg()const{
	return immu_recharger_tour;
}

HashMap<QString,QStringList> FicheCapacite::immu_stat()const{
	return immu_statut;
}

bool FicheCapacite::lent()const{
	return lenteur_vitesse;
}

HashMap<QString,Taux> FicheCapacite::mult_deg_adv()const{
	return mult_degats_adv;
}

Taux FicheCapacite::mult_deg_c()const{
	return mult_degats_cc;
}

Taux FicheCapacite::mult_deg_part()const{
	return mult_degats_part;
}

HashMap<bool,Taux> FicheCapacite::mult_deg_rec()const{
	return mult_degats_recu;
}

HashMap<QString,Taux> FicheCapacite::mult_deg_statut()const{
	return mult_degats_statut;
}

Taux FicheCapacite::mult_pr_cc()const{
	return mult_proba_cc;
}

HashMap<bool,Taux> FicheCapacite::mult_pr_eff_sec()const{
	return mult_proba_effet_sec;
}

HashMap<QString,Taux> FicheCapacite::mult_puis_att_categ()const{
	return mult_puissance_attaque_categorie;
}

HashMap<QString,Taux> FicheCapacite::mult_puis_att()const{
	return mult_puissance_attaques;
}

Taux FicheCapacite::mult_puis_t_att()const{
	return mult_puissance_toutes_attaques;
}

HashMap<QString,Taux> FicheCapacite::mult_puis_att_t()const{
	return mult_puissance_attaque_type;
}

HashMap<bool,Taux> FicheCapacite::mult_puis_att_eg_genre()const{
	return mult_puissance_attaque_si_egalite_genre;
}

QPair<int,Taux> FicheCapacite::mult_puis_inf_eg()const{
	return mult_puissance_si_inf_eg;
}

HashMap<QPair<QString,QString>,Taux> FicheCapacite::mult_puis_typ_cl()const{
	return mult_puissance_type_si_climat;
}

HashMap<QString,QPair<Taux,Taux> >  FicheCapacite::mult_puis_typ_inf_eg()const{
	return mult_puissance_type_inf_eg;
}

Taux FicheCapacite::mult_st()const{
	return mult_stab;
}

HashMap<QString,QPair<Taux,bool> > FicheCapacite::mult_statis()const{
	return mult_statistique;
}

HashMap<QString,Taux> FicheCapacite::mult_statis_part()const{
	return mult_statistique_part;
}

HashMap<QString,qint8> FicheCapacite::mult_statis_adv_ko()const{
	return mult_statistique_si_adv_ko;
}

HashMap<QString,qint8> FicheCapacite::mult_statis_bais_stat()const{
	return mult_statistique_si_baisse_statistique;
}

HashMap<QPair<QString,QString>,Taux> FicheCapacite::mult_statis_categ()const{
	return mult_statistique_si_categorie;
}

HashMap<QPair<QString,QString>,Taux> FicheCapacite::mult_statis_clim()const{
	return mult_statistique_si_climat;
}

HashMap<QString,Taux> FicheCapacite::mult_statis_der()const{
	return mult_statistique_si_dernier;
}

HashMap<QString,Taux> FicheCapacite::mult_statis_perd_obj()const{
	return mult_statistique_si_perd_objet;
}

QPair<HashMap<QString,QPair<QString,qint8> >,QPair<QString,QString> > FicheCapacite::mult_statis_statis_adv()const{
	return mult_statistique_si_statistique_adv;
}

QList<QPair<QString,QPair<QString,Taux> > > FicheCapacite::mult_statis_statut_coef()const{
	return mult_statistique_si_statut_coeff;
}

QList<QPair<QString,QPair<QString,qint8> > > FicheCapacite::mult_statis_statut_cran()const{
	return mult_statistique_si_statut_cran;
}

HashMap<QString,QList<QPair<QString,qint8> > > FicheCapacite::mult_statis_to_categ()const{
	return mult_statistique_si_touche_categorie;
}

HashMap<QString,QPair<QString,qint8> > FicheCapacite::mult_statis_to_t()const{
	return mult_statistique_si_touche_type;
}

char FicheCapacite::mult_tx_deg_adv_abs()const{
	return mult_taux_degats_adv_absorb;
}

Taux FicheCapacite::mult_var_cran()const{
	return mult_variation_cran;
}

int FicheCapacite::nb_pp_ut()const{
	return nb_pp_utilise;
}

bool FicheCapacite::nb_coups()const{
	return nombre_coups;
}

bool FicheCapacite::abri()const{
	return passe_abri;
}

bool FicheCapacite::plaq()const{
	return plaque;
}

bool FicheCapacite::soin_statut_sw()const{
	return soin_statut_si_switch;
}

Taux FicheCapacite::soin_tx_pvmax_sw()const{
	return soin_taux_pvmax_si_switch;
}

HashMap<QString,uchar> FicheCapacite::som_pr()const{
	return somme_prio;
}

QStringList FicheCapacite::statis_max_cc()const{
	return statistiques_maximales_si_cc;
}

Taux FicheCapacite::statut_o()const{
	return statut_ok;
}

Taux FicheCapacite::statut_o_p()const{
	return statut_ok_part;
}

MonteCarlo<MonteCarlo<QString> > FicheCapacite::statut_l()const{
	return statut;
}

MonteCarlo<QString> FicheCapacite::statut_sim()const{
	return statut_simple;
}

bool FicheCapacite::to_pseud_invul()const{
	return touche_pseudo_invulnerable;
}

HashMap<QString,QString> FicheCapacite::transf_statut()const{
	return transfert_statut;
}

QString FicheCapacite::t_att()const{
	return type_attaques;
}

Taux FicheCapacite::ut_baie_soin_pv()const{
	return utilise_baie_soin_pv;
}

bool FicheCapacite::mom()const{
	return momie;
}

Taux FicheCapacite::co_att_pef()const{
	return coeff_att_peu_eff;
}




