#include "base_donnees/objets/objetattachablecombat.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QRegExp>
const HashMap<QString,QString> ObjetAttachableCombat::_descriptions_objets_=ObjetAttachableCombat::init_descriptions_objetsatt();
HashMap<QString,QString> ObjetAttachableCombat::init_descriptions_objetsatt(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/descriptions_objets_non_baie");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/descriptions_objets_non_baie.txt");
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

ObjetAttachableCombat::ObjetAttachableCombat(const QStringList& _effets,int _prix_achat):Objet(){
	setAttachable();
	maj_prix_achat(_prix_achat);
	annule_immu_type=_effets.contains("ANNULE_IMMU_TYPE");
	anti_evo=_effets.contains("ANTI_EVO");
	attaque_dernier=_effets.contains("ATTAQUE_DERNIER");
	calcul_experience=_effets.contains("CALCUL_EXPERIENCE");
	fuite_reussie=_effets.contains("FUITE_REUSSIE");
	immu_amour=_effets.contains("IMMU_AMOUR");
	immu_baisse_statistique=_effets.contains("IMMU_BAISSE_STATISTIQUE");
	nb_tours_pieges=_effets.contains("NB_TOURS_PIEGES");
	prepa_vite=_effets.contains("PREPA_VITE");
	repousse_sauvages=_effets.contains("REPOUSSE_SAUVAGES");
	switch_reussi=_effets.contains("SWITCH_REUSSI");
	synchro_amour=_effets.contains("SYNCHRO_AMOUR");
	usage_unique=_effets.contains("USAGE_UNIQUE");
	detruit_si_contact=_effets.contains("DETRUIT_SI_CONTACT");
	switch_possible_si_touche=_effets.contains("SWITCH_POSSIBLE_SI_TOUCHE");
	switch_force_adv_si_touche=_effets.contains("SWITCH_FORCE_ADV_SI_TOUCHE");
	transfert_obj_si_contact=_effets.contains("TRANSFERT_OBJ_SI_CONTACT");
	QStringList effets_=_effets.filter(QRegExp("^ANTI_KO\\["));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		anti_ko=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^ANTI_KO_SI"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		anti_ko_si_tous_pv=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_MASSE"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_masse=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^DEGATS_REC"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		degats_recul=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^DRAINE"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		draine_taux_degats=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^GAIN_PV_TOUS"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		gain_pv_tous=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_DEGATS_ATT_PIEG"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_degats_att_piegeante=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_GAIN_BONHEUR"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_gain_bonheur=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_GAIN_ARGENT"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_gain_argent=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_GAIN_EV"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_gain_ev=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_GAIN_EXP"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_gain_experience=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_ATTAQUE\\[[^><]"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_puissance_attaque=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_ATTAQUE\\[>"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_,effets_[0].indexOf(","));
		mult_puissance_attaque_sup_eff=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_ATTAQUE_CONSECUTIVE"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_puissance_attaque_consecutive=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^MULT_PV_DRAINES"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		mult_pv_draines=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	effets_=_effets.filter(QRegExp("^DEGATS_RECUL_ADV"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		deg_recul=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
	}
	//deg_recul
	effets_=_effets.filter(QRegExp("^NB_TOURS_CLIMAT"));
	if(!effets_.isEmpty()){
		nb_tours_climat=effets_[0].split(QRegExp("[\\[\\],]+"),QString::SkipEmptyParts).mid(1);
	}
	effets_=_effets.filter(QRegExp("^NB_TOURS_PROTECTION"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		nb_tours_protection=exp_taux_.capturedTexts()[0].toInt();
	}else{
		nb_tours_protection=0;
	}
	effets_=_effets.filter(QRegExp("^REPRODUCTION"));
	if(!effets_.isEmpty()){
		reproduction=QStringList(effets_[0].split(QRegExp("[\\[\\],]+")).mid(1));
		reproduction.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^SENSIBLE_TYPE"));
	if(!effets_.isEmpty()){
		sensible_type=QStringList(effets_[0].split(QRegExp("[\\[\\],]+")).mid(1));
		sensible_type.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^IMMU_TYPE"));
	if(!effets_.isEmpty()){
		immu_type=QStringList(effets_[0].split(QRegExp("[\\[\\],]+")).mid(1));
		immu_type.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^SANS_EFFET_CAPACITE"));
	if(!effets_.isEmpty()){
		sans_effet_capacite=QStringList(effets_[0].split(QRegExp("[\\[\\],]+")).mid(1));
		sans_effet_capacite.removeAll("");
	}
	effets_=_effets.filter(QRegExp("^STATUT_FIN_TOUR_LANCEUR"));
	if(!effets_.isEmpty()){
		statut_fin_tour_lanceur=effets_[0].split(QRegExp("[\\[\\],]+"))[1];
	}
	effets_=_effets.filter(QRegExp("^GAIN_EV_COMBAT"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("[\\[\\],]+")).mid(1));
			gain_ev_combat.ajouter_cle_valeur(infos_[0],(uchar)infos_[1].toUInt());
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_ATTAQUE_CATEGORIE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("[\\[\\],]+")).mid(1));
			mult_puissance_attaque_categorie.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_ATTAQUE_TYPE"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("[\\[\\],]+")).mid(1));
			mult_puissance_attaque_type.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_SI_DERNIER"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("[\\[\\],]+")).mid(1));
			mult_statistique_si_dernier.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_PRE_EVO"));
	if(!effets_.isEmpty()){
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("[\\[\\],]+")).mid(1));
			mult_statistique_pre_evo.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_PUISSANCE_ATTAQUE_POKEMON\\[TYPES"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			QRegExp exp_types_("TYPES\\[[A-Z_]+(,[A-Z_]+)*");
			int ind_=e.indexOf(exp_types_);
			e.indexOf(exp_taux_);
			QString type_ch_=exp_types_.capturedTexts()[0];
			QRegExp exp_nom_("[A-Z_]+");
			e.indexOf(exp_nom_,type_ch_.size()+ind_+1);
			QString nom_pk_=exp_nom_.capturedTexts()[0];
			foreach(QString t,type_ch_.split(QRegExp("[\\[\\],]+"),QString::SkipEmptyParts).mid(1)){
				mult_puissance_attaque_pokemon_types.ajouter_cle_valeur(QPair<QString,QString>(nom_pk_,t),Taux::parse_taux(exp_taux_.capturedTexts()[0]));
			}
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_POKEMON"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			if(!e.endsWith("C]")){
				QRegExp exp_types_("\\[POKEMON\\[[A-Z_]+(,[A-Z_]+)*");
				int ind_=e.indexOf(exp_types_);
				e.indexOf(exp_taux_);
				QString type_ch_=exp_types_.capturedTexts()[0];
				QRegExp exp_nom_("[A-Z_]+");
				e.indexOf(exp_nom_,type_ch_.size()+ind_+1);
				QString nom_pk_=exp_nom_.capturedTexts()[0];
				foreach(QString t,type_ch_.split(QRegExp("[\\[\\],]+"),QString::SkipEmptyParts).mid(1)){
					mult_statistique_pokemon_coeff.ajouter_cle_valeur(QPair<QString,QString>(nom_pk_,t),Taux::parse_taux(exp_taux_.capturedTexts()[0]));
				}
			}else{
				QRegExp exp_types_("\\[POKEMON\\[[A-Z]+(,[A-Z]+)*");
				int ind_=e.indexOf(exp_types_);
				e.indexOf(exp_taux_);
				QString type_ch_=exp_types_.capturedTexts()[0];
				QRegExp exp_nom_("[A-Z_]+");
				e.indexOf(exp_nom_,type_ch_.size()+ind_+1);
				QString nom_pk_=exp_nom_.capturedTexts()[0];
				foreach(QString t,type_ch_.split(QRegExp("[\\[\\],]+"),QString::SkipEmptyParts).mid(1)){
					mult_statistique_pokemon_cran.ajouter_cle_valeur(QPair<QString,QString>(nom_pk_,t),(qint8)exp_taux_.capturedTexts()[0].toInt());
				}
			}
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE_ADV"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("[\\[\\],]+")).mid(1));
			e.indexOf(exp_taux_);
			mult_statistique_adv.ajouter_cle_valeur(infos_[0],QPair<Taux,bool>(Taux::parse_taux(exp_taux_.capturedTexts()[0]),!e.endsWith("C]")));
		}
	}
	effets_=_effets.filter(QRegExp("^MULT_STATISTIQUE\\["));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		foreach(QString e,effets_){
			QStringList infos_=QStringList(e.split(QRegExp("[\\[\\],]+")).mid(1));
			e.indexOf(exp_taux_);
			mult_statistique.ajouter_cle_valeur(infos_[0],QPair<Taux,bool>(Taux::parse_taux(exp_taux_.capturedTexts()[0]),!e.endsWith("C]")));
		}
	}
	effets_=_effets.filter(QRegExp("^LOI_PROBA_PREMIER"));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
		effets_[0].indexOf(exp_taux_);
		Taux taux_=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
		Entier eff_inac_=Entier(taux_.gdenominateur())-Entier(taux_.gnumerateur());
		loi_proba_premier.ajouter_event(QPair<bool,Entier>(true,taux_.gnumerateur()));
		loi_proba_premier.ajouter_event(QPair<bool,Entier>(false,eff_inac_));
	}
	effets_=_effets.filter(QRegExp("^GAIN_PV\\["));
	if(!effets_.isEmpty()){
		QRegExp exp_taux_("(-)?[0-9]+(/[0-9]+)?");
		int ind_=effets_[0].indexOf(exp_taux_);
		QString ch_taux_=exp_taux_.capturedTexts()[0];
		QString type_=effets_[0].split(QRegExp("[^A-Z_]+"))[1];
		gain_pv_sel.ajouter_cle_valeur(type_,Taux::parse_taux(ch_taux_));
		effets_[0].indexOf(exp_taux_,ind_+ch_taux_.size()+1);
		ch_taux_=exp_taux_.capturedTexts()[0];
		gain_pv_sel.ajouter_cle_valeur("",Taux::parse_taux(ch_taux_));
	}
}

QString ObjetAttachableCombat::description(int _langue,Donnees *_d)const{
	QString retour_;
	QString cle_;
	if(annule_immu_type){
		cle_="ANNULE_IMMU_TYPE";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(anti_evo){
		cle_="ANTI_EVO";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(attaque_dernier){
		cle_="ATTAQUE_DERNIER";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(calcul_experience){//TODO changer attribut en Taux
		cle_="CALCUL_EXPERIENCE";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(fuite_reussie){
		cle_="FUITE_REUSSIE";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_amour){
		cle_="IMMU_AMOUR";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(immu_baisse_statistique){
		cle_="IMMU_BAISSE_STATISTIQUE";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(nb_tours_pieges){
		cle_="NB_TOURS_PIEGES";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(prepa_vite){
		cle_="PREPA_VITE";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(repousse_sauvages){
		cle_="REPOUSSE_SAUVAGES";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(switch_reussi){
		cle_="SWITCH_REUSSI";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(synchro_amour){
		cle_="SYNCHRO_AMOUR";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(usage_unique){
		cle_="USAGE_UNIQUE";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(detruit_si_contact){
		cle_="DETRUIT_SI_CONTACT";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(switch_possible_si_touche){
		cle_="SWITCH_POSSIBLE_SI_TOUCHE";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(switch_force_adv_si_touche){
		cle_="SWITCH_FORCE_ADV_SI_TOUCHE";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(transfert_obj_si_contact){
		cle_="TRANSFERT_OBJ_SI_CONTACT";
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],QStringList())+"\n";
	}
	if(anti_ko!=Taux(0)){
		cle_="ANTI_KO";
		QStringList args_;
		args_<<anti_ko.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(anti_ko_si_tous_pv!=Taux(0)){
		cle_="ANTI_KO_SI_TOUS_PV";
		QStringList args_;
		args_<<anti_ko_si_tous_pv.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_masse!=Taux(0)){
		cle_="MULT_MASSE";
		QStringList args_;
		args_<<mult_masse.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(degats_recul!=Taux(0)){
		cle_="DEGATS_RECUL";
		QStringList args_;
		args_<<degats_recul.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(draine_taux_degats!=Taux(0)){
		cle_="DRAINE_TAUX_DEGATS";
		QStringList args_;
		args_<<draine_taux_degats.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(gain_pv_tous!=Taux(0)){
		cle_="GAIN_PV_TOUS";
		QStringList args_;
		args_<<gain_pv_tous.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_degats_att_piegeante!=Taux(0)){
		cle_="MULT_DEGATS_ATT_PIEGEANTE";
		QStringList args_;
		args_<<mult_degats_att_piegeante.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_gain_argent!=Taux(0)){
		cle_="MULT_GAIN_ARGENT";
		QStringList args_;
		args_<<mult_gain_argent.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_gain_bonheur!=Taux(0)){
		cle_="MULT_GAIN_BONHEUR";
		QStringList args_;
		args_<<mult_gain_bonheur.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_gain_ev!=Taux(0)){
		cle_="MULT_GAIN_EV";
		QStringList args_;
		args_<<mult_gain_ev.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_gain_experience!=Taux(0)){
		cle_="MULT_GAIN_EXPERIENCE";
		QStringList args_;
		args_<<mult_gain_experience.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_puissance_attaque!=Taux(0)){
		cle_="MULT_PUISSANCE_ATTAQUE";
		QStringList args_;
		args_<<mult_puissance_attaque.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_puissance_attaque_sup_eff!=Taux(0)){
		cle_="MULT_PUISSANCE_ATTAQUE[>";
		QStringList args_;
		args_<<mult_puissance_attaque_sup_eff.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_puissance_attaque_consecutive!=Taux(0)){
		cle_="MULT_PUISSANCE_ATTAQUE_CONSECUTIVE";
		QStringList args_;
		args_<<mult_puissance_attaque_consecutive.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(mult_pv_draines!=Taux(0)){
		cle_="MULT_PV_DRAINES";
		QStringList args_;
		args_<<mult_pv_draines.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(deg_recul!=Taux(0)){
		cle_="DEGATS_RECUL_ADV";
		QStringList args_;
		args_<<deg_recul.chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!nb_tours_climat.isEmpty()){
		cle_="NB_TOURS_CLIMAT";
		foreach(QString c,nb_tours_climat){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_climats(),c,_langue);
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	if(nb_tours_protection!=0){
		cle_="NB_TOURS_PROTECTION";
		QStringList args_;
		args_<<QString::number(nb_tours_protection);
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!reproduction.isEmpty()){
		cle_="REPRODUCTION";
		QStringList args_;
		foreach(QString p,reproduction){
			args_<<Utilitaire::traduire(_d->val_noms_pk(),p,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!sensible_type.isEmpty()){
		cle_="SENSIBLE_TYPE";
		QStringList args_;
		foreach(QString t,sensible_type){
			args_<<Utilitaire::traduire(_d->val_noms_types(),t,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!immu_type.isEmpty()){
		cle_="IMMU_TYPE";
		QStringList args_;
		foreach(QString t,immu_type){
			args_<<Utilitaire::traduire(_d->val_noms_types(),t,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	if(!sans_effet_capacite.isEmpty()){
		cle_="SANS_EFFET_CAPACITE";
		QStringList args_;
		foreach(QString t,sans_effet_capacite){
			args_<<Utilitaire::traduire(_d->val_noms_capacites(),t,_langue);
		}
		args_.sort();
		args_=QStringList(args_.join(","));
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	//
	if(statut_fin_tour_lanceur!=""){
		cle_="STATUT_FIN_TOUR_LANCEUR";
		QStringList args_;
		if(Utilitaire::traduisible(_d->val_noms_statuts(),statut_fin_tour_lanceur)){
			args_<<Utilitaire::traduire(_d->val_noms_statuts(),statut_fin_tour_lanceur,_langue);
		}else{
			args_<<Utilitaire::traduire(_d->val_noms_pseudo_statuts(),statut_fin_tour_lanceur,_langue);
		}
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	QList<QString> cles_ch_=mult_puissance_attaque_categorie.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_PUISSANCE_ATTAQUE_CATEGORIE";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_categories(),e,_langue);
			args_<<mult_puissance_attaque_categorie.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_puissance_attaque_type.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_PUISSANCE_ATTAQUE_TYPE";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_types(),e,_langue);
			args_<<mult_puissance_attaque_type.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique_si_dernier.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_STATISTIQUE_SI_DERNIER";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_statistiques(),e,_langue);
			args_<<mult_statistique_si_dernier.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique_pre_evo.cles();
	if(!cles_ch_.isEmpty()){
		cle_="MULT_STATISTIQUE_PRE_EVO";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_statistiques(),e,_langue);
			args_<<mult_statistique_pre_evo.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=gain_ev_combat.cles();
	if(!cles_ch_.isEmpty()){
		cle_="GAIN_EV_COMBAT";
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_statistiques(),e,_langue);
			args_<<QString::number(gain_ev_combat.valeur(e));
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=gain_pv_sel.cles();
	if(!cles_ch_.isEmpty()){
		cle_="GAIN_PV";
		QStringList args_;
		QString type_=QStringList(cles_ch_).filter(QRegExp(".+"))[0];
		args_<<Utilitaire::traduire(_d->val_noms_types(),type_,_langue);
		args_<<gain_pv_sel.valeur(type_).chaine();
		args_<<gain_pv_sel.valeur("").chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	cles_ch_=mult_statistique.cles();
	if(!cles_ch_.isEmpty()){	
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_statistiques(),e,_langue);
			QPair<Taux,bool> val_=mult_statistique.valeur(e);
			if(val_.second){
				cle_="MULT_STATISTIQUE";
			}else{
				cle_="MULT_STATISTIQUE[C";
			}
			args_<<val_.first.chaine();
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_ch_=mult_statistique_adv.cles();
	if(!cles_ch_.isEmpty()){	
		foreach(QString e,cles_ch_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_statistiques(),e,_langue);
			QPair<Taux,bool> val_=mult_statistique_adv.valeur(e);
			if(val_.second){
				cle_="MULT_STATISTIQUE_ADV";
			}else{
				cle_="MULT_STATISTIQUE_ADV[C";
			}
			args_<<val_.first.chaine();
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	QList<QPair<QString,QString> > cles_cpl_=mult_puissance_attaque_pokemon_types.cles();
	typedef QPair<QString,QString> CleChCh;
	if(!cles_cpl_.isEmpty()){
		cle_="MULT_PUISSANCE_ATTAQUE_POKEMON[TYPES";
		foreach(CleChCh e,cles_cpl_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_types(),e.second,_langue);
			args_<<Utilitaire::traduire(_d->val_noms_pk(),e.first,_langue);
			args_<<mult_puissance_attaque_pokemon_types.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_cpl_=mult_statistique_pokemon_coeff.cles();
	if(!cles_cpl_.isEmpty()){
		cle_="MULT_STATISTIQUE_POKEMON";
		foreach(CleChCh e,cles_cpl_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_statistiques(),e.first,_langue);
			args_<<Utilitaire::traduire(_d->val_noms_pk(),e.second,_langue);
			args_<<mult_statistique_pokemon_coeff.valeur(e).chaine();
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	cles_cpl_=mult_statistique_pokemon_cran.cles();
	if(!cles_cpl_.isEmpty()){
		cle_="MULT_STATISTIQUE_POKEMON[C";
		foreach(CleChCh e,cles_cpl_){
			QStringList args_;
			args_<<Utilitaire::traduire(_d->val_noms_statistiques(),e.first,_langue);
			args_<<Utilitaire::traduire(_d->val_noms_pk(),e.second,_langue);
			args_<<QString::number(mult_statistique_pokemon_cran.valeur(e));
			retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
		}
	}
	QList<bool> events_=loi_proba_premier.events();
	if(!events_.isEmpty()){
		cle_="LOI_PROBA_PREMIER";
		Entier eff_act_=loi_proba_premier.proba_event(true);
		Entier eff_inact_=loi_proba_premier.proba_event(false);
		QStringList args_;
		args_<<Taux(eff_act_,eff_act_+eff_inact_).chaine();
		retour_+=Utilitaire::formatter(_descriptions_objets_.valeur(cle_).split("\t")[_langue],args_)+"\n";
	}
	//TODO traduire "prix" en "price" dans un fichier
	retour_+="prix: "+QString::number(prix());
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}

Taux ObjetAttachableCombat::a_ko()const{
	return anti_ko;
}

Taux ObjetAttachableCombat::a_ko_pv()const{
	return anti_ko_si_tous_pv;
}

Taux ObjetAttachableCombat::deg_rec()const{
	return degats_recul;
}

Taux ObjetAttachableCombat::dr_tx_deg()const{
	return draine_taux_degats;
}

HashMap<QString,uchar> ObjetAttachableCombat::gain_ev_cbt()const{
	return gain_ev_combat;
}

Taux ObjetAttachableCombat::gain_pv_t()const{
	return gain_pv_tous;
}

HashMap<QString,Taux> ObjetAttachableCombat::gain_pv_s()const{
	return gain_pv_sel;
}

MonteCarlo<bool> ObjetAttachableCombat::loi_prem()const{
	return loi_proba_premier;
}

Taux ObjetAttachableCombat::mult_deg_pieg()const{
	return mult_degats_att_piegeante;
}

Taux ObjetAttachableCombat::mult_gain_arg()const{
	return mult_gain_argent;
}

Taux ObjetAttachableCombat::mult_gain_bonh()const{
	return mult_gain_bonheur;
}

Taux ObjetAttachableCombat::mult_gn_ev()const{
	return mult_gain_ev;
}

Taux ObjetAttachableCombat::mult_gain_exp()const{
	return mult_gain_experience;
}

Taux ObjetAttachableCombat::mult_puiss_att()const{
	return mult_puissance_attaque;
}

Taux ObjetAttachableCombat::mult_puiss_att_sup_eff()const{
	return mult_puissance_attaque_sup_eff;
}

HashMap<QString,Taux> ObjetAttachableCombat::mult_puiss_att_categ()const{
	return mult_puissance_attaque_categorie;
}

Taux ObjetAttachableCombat::mult_puiss_att_consec()const{
	return mult_puissance_attaque_consecutive;
}

HashMap<QPair<QString,QString>,Taux> ObjetAttachableCombat::mult_puiss_att_pk_types()const{
	return mult_puissance_attaque_pokemon_types;
}

HashMap<QString,Taux> ObjetAttachableCombat::mult_puiss_att_type()const{
	return mult_puissance_attaque_type;
}

Taux ObjetAttachableCombat::mult_pv_drai()const{
	return mult_pv_draines;
}

Taux ObjetAttachableCombat::recul()const{
	return deg_recul;
}

HashMap<QString,QPair<Taux,bool> > ObjetAttachableCombat::mult_stat_adv()const{
	return mult_statistique_adv;
}

HashMap<QString,QPair<Taux,bool> > ObjetAttachableCombat::mult_stat()const{
	return mult_statistique;
}

HashMap<QPair<QString,QString>,Taux> ObjetAttachableCombat::mult_stat_pk_co()const{
	return mult_statistique_pokemon_coeff;
}

HashMap<QPair<QString,QString>,qint8> ObjetAttachableCombat::mult_stat_pk_cr()const{
	return mult_statistique_pokemon_cran;
}

HashMap<QString,Taux> ObjetAttachableCombat::mult_stat_der()const{
	return mult_statistique_si_dernier;
}

QStringList ObjetAttachableCombat::nb_trs_cl()const{
	return nb_tours_climat;
}

int ObjetAttachableCombat::nb_trs_prot()const{
	return nb_tours_protection;
}

QStringList ObjetAttachableCombat::reprod()const{
	return reproduction;
}

QStringList ObjetAttachableCombat::sens_type()const{
	return sensible_type;
}

QString ObjetAttachableCombat::statut_tr_lanc()const{
	return statut_fin_tour_lanceur;
}

bool ObjetAttachableCombat::annule_immu_t()const{
	return annule_immu_type;
}

bool ObjetAttachableCombat::anti_ev()const{
	return anti_evo;
}

bool ObjetAttachableCombat::att_der()const{
	return attaque_dernier;
}

bool ObjetAttachableCombat::calc_exp()const{
	return calcul_experience;
}

bool ObjetAttachableCombat::fuite_re()const{
	return fuite_reussie;
}

bool ObjetAttachableCombat::immu_am()const{
	return immu_amour;
}

bool ObjetAttachableCombat::immu_bais_stat()const{
	return immu_baisse_statistique;
}

bool ObjetAttachableCombat::nb_trs_pieg()const{
	return nb_tours_pieges;
}

bool ObjetAttachableCombat::prepa_v()const{
	return prepa_vite;
}

bool ObjetAttachableCombat::rep_sauv()const{
	return repousse_sauvages;
}

bool ObjetAttachableCombat::switch_re()const{
	return switch_reussi;
}

bool ObjetAttachableCombat::sync_am()const{
	return synchro_amour;
}

bool ObjetAttachableCombat::us_uniq()const{
	return usage_unique;
}

bool ObjetAttachableCombat::exp_ev()const{
	//CALCUL_EXPERIENCE,MULT_GAIN_EXPERIENCE,GAIN_EV_COMBAT,MULT_GAIN_EV
	return calcul_experience||!mult_gain_experience.estNul()||gain_ev_combat.total()>0||!mult_gain_ev.estNul();
}

/*ObjetAttachableCombat::ObjetAttachableCombat(const QStringList& _effets,const QStringList& _infos,int _prix_achat):Objet(_effets){
	setAttachable()
	infos=_infos
	maj_prix_achat(_prix_achat)
}*/



