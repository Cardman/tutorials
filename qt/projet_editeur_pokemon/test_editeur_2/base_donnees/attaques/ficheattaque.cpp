#include "base_donnees/attaques/ficheattaque.h"
#include "base_donnees/attaques/effets/effetantiimmu.h"
#include "base_donnees/attaques/effets/effetmultpuissattaque.h"
#include "base_donnees/attaques/effets/effettauxdegats.h"
#include "base_donnees/attaques/effets/effetclimat.h"
//#include "base_donnees/attaques/effets/effetspecifique.h"
#include "base_donnees/attaques/effets/effetdegats.h"
#include "base_donnees/attaques/effets/effetstatistique.h"
#include "base_donnees/attaques/effets/effettauxpvpvmax.h"
#include "base_donnees/attaques/effets/effetstatut.h"
#include "base_donnees/attaques/effets/effettauxpvrestants.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"

const QStringList FicheAttaque::_descriptions_attaques_gener_=FicheAttaque::init_descriptions_attaques_gener();

const HashMap<QString,QString> FicheAttaque::_descriptions_attaques_particul_=FicheAttaque::init_descriptions_attaques_particul();

QStringList FicheAttaque::init_descriptions_attaques_gener(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/descriptions_attaques");
	QStringList lignes_=contenu_.split("\n",QString::SkipEmptyParts);
	QStringList descriptions_objets_;
	int nb_langues_=1;//Import::_langues_.total()
	for(int i=0;i<nb_langues_;i++){
		descriptions_objets_<<"";
	}
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		for(int i=0;i<nb_langues_;i++){
			descriptions_objets_[i]+=infos_[i]+"\n";
		}
	}
	for(int i=0;i<nb_langues_;i++){
		descriptions_objets_[i].chop(1);
	}
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/descriptions_attaques.txt");
	QStringList lignes_=contenu_.split("\n",QString::SkipEmptyParts);
	QStringList descriptions_objets_;
	int nb_langues_=1;
	for(int i=0;i<nb_langues_;i++){
		descriptions_objets_<<"";
	}
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		for(int i=0;i<nb_langues_;i++){
			descriptions_objets_[i]+=infos_[i]+"\n";
		}
	}
	for(int i=0;i<nb_langues_;i++){
		descriptions_objets_[i].chop(1);
	}
#endif
	return descriptions_objets_;
}

HashMap<QString,QString> FicheAttaque::init_descriptions_attaques_particul(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/descriptions_attaques_var");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/descriptions_attaques_var.txt");
#endif
	QStringList lignes_=contenu_.split("\n");
	HashMap<QString,QString> _descriptions_capacites_;
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		QString cle_=infos_.takeFirst();
		_descriptions_capacites_.ajouter_cle_valeur(cle_,infos_.join("\t"));
	}
	return _descriptions_capacites_;

}

FicheAttaque::FicheAttaque(const QStringList& _lignes){
	pp=(uchar)_lignes[0].split(":")[1].toUInt();
	type=_lignes[1].split(":")[1];
	categorie=_lignes[2].split(":")[1];
	direct=categorie!="AUTRE"&&_lignes[2].split(":")[2]!="I";
	priorite=(char)_lignes[3].split(":")[1].toInt();
	precision=(uchar)_lignes[4].split(":")[1].toUInt();
	int i_=5;
	description_suppl=false;
	while(_lignes[i_].startsWith("EFFET")){
		if(_lignes[i_].startsWith("EFFET_ANTI_IMMU")){
			effets<<new EffetAntiImmu(_lignes[i_]);
		}else if(_lignes[i_].startsWith("EFFET_DEGAT[")||_lignes[i_].startsWith("EFFET_DEGAT_FIXE")){
			effets<<new EffetDegats(_lignes[i_]);
			if(_lignes[i_].startsWith("EFFET_DEGAT_FIXE")){
				EffetDegats *effet_d_=qobject_cast<EffetDegats*>(effets.last());
				effet_d_->fixer_degats();
			}
		}else if(_lignes[i_].startsWith("EFFET_CLIMAT")){
			effets<<new EffetClimat(_lignes[i_]);
		}else if(_lignes[i_].startsWith("EFFET_MULT_PUISS_ATT")){
			effets<<new EffetMultPuissAttaque(_lignes[i_]);
		}else if(_lignes[i_].startsWith("EFFET_STATISTIQUE[")){
			effets<<new EffetStatistique(_lignes[i_]);
		}else if(_lignes[i_].startsWith("EFFET_STATUT[")){
			effets<<new EffetStatut(_lignes[i_]);
		}else if(_lignes[i_].startsWith("EFFET_TAUX_DEGATS[")){
			effets<<new EffetTauxDegats(_lignes[i_]);
		}else if(_lignes[i_].startsWith("EFFET_TAUX_PV_MAX[")){
			effets<<new EffetTauxPVPVMax(_lignes[i_]);
		}else if(_lignes[i_].startsWith("EFFET_TAUX_PV_RESTANTS[")){
			effets<<new EffetTauxPVRestants(_lignes[i_]);
		}else{
			description_suppl=true;
		}
		i_++;
	}
	fuite_adverse=_lignes[i_].split(":")[1].contains("VRAI");
	preparation_tour=_lignes[i_+1].split(":")[1].contains("VRAI");
	disparition_tour=_lignes[i_+2].split(":")[1].contains("VRAI");
	touche_attaq_pokemon_disparu=_lignes[i_+3].split(":")[1].split(",");
	Entier ppcm_=Entier(1);
	foreach(QString s,_lignes[i_+4].split(":[(")[1].split(")]")[0].split(");(")){
		ppcm_=ppcm_.ppcm(Taux::parse_taux(s.split(",")[1]).gdenominateur());
	}
	foreach(QString s,_lignes[i_+4].split(":[(")[1].split(")]")[0].split(");(")){
		loi_proba_repetition_tour.ajouter_event(QPair<Taux,Entier>(Taux::parse_taux(s.split(",")[0]),(Taux::parse_taux(s.split(",")[1])*Taux(ppcm_)).partie_entiere()));
	}
	ppcm_=Entier(1);
	foreach(QString s,_lignes[i_+5].split(":[(")[1].split(")]")[0].split(");(")){
		ppcm_=ppcm_.ppcm(Taux::parse_taux(s.split(",")[1]).gdenominateur());
	}
	foreach(QString s,_lignes[i_+5].split(":[(")[1].split(")]")[0].split(");(")){
		loi_proba_repetition_coups.ajouter_event(QPair<Taux,Entier>(Taux::parse_taux(s.split(",")[0]),(Taux::parse_taux(s.split(",")[1])*Taux(ppcm_)).partie_entiere()));
	}
	blocage_lanceur=_lignes[i_+6].split(":")[1].contains("VRAI");
	QStringList min_max_puiss_=_lignes[i_+7].split(QRegExp("[^0-9]+"),QString::SkipEmptyParts);
	min_max_mult_puissance.first=min_max_puiss_[0].toInt();
	min_max_mult_puissance.second=min_max_puiss_[1].toInt();
	ne_peut_mettre_ko=_lignes[i_+8].split(":")[1].contains("VRAI");
	effet_echec=_lignes[i_+10].split(":")[1].contains("VRAI");
	effet_non_degats=_lignes[i_+11].split(":")[1].contains("VRAI");
	nec_sexe_oppos=_lignes[i_+12].split(":")[1].contains("VRAI");
	nec_lanceur_sommeil=_lignes[i_+13].split(":")[1].contains("VRAI");
	nec_cible_sommeil=_lignes[i_+14].split(":")[1].contains("VRAI");
	qui=_lignes[i_+15];
	stat_att.first=_lignes[i_+17].contains("LANCEUR");
	stat_att.second=(categorie=="PHYSIQUE")==(_lignes[i_+17].endsWith("ATTAQUE"));
	stat_def.first=_lignes[i_+18].contains("CIBLE");
	stat_def.second=(categorie=="PHYSIQUE")==(_lignes[i_+18].endsWith("DEFENSE"));
	touche_attaq_pokemon_disparu.removeAll("");
}

uchar FicheAttaque::pps()const{
	return pp;
}

QString FicheAttaque::tp()const{
	return type;
}

QString FicheAttaque::cat()const{
	return categorie;
}

bool FicheAttaque::dir()const{
	return direct;
}

char FicheAttaque::prio()const{
	return priorite;
}

uchar FicheAttaque::prec()const{
	return precision;
}

QList<Effet*> FicheAttaque::effs()const{
	return effets;
}

int FicheAttaque::puis()const{
	if(effets.isEmpty()){
		return 0;
	}
	EffetDegats *effet_=qobject_cast<EffetDegats*>(effets[0]);
	if(effet_==NULL){
		return 0;
	}
	return effet_->puis();
}

bool FicheAttaque::fuit()const{
	return fuite_adverse;
}

bool FicheAttaque::prepa()const{
	return preparation_tour;
}

bool FicheAttaque::dispa()const{
	return disparition_tour;
}

QStringList FicheAttaque::touch_pk_disp()const{
	return touche_attaq_pokemon_disparu;
}

MonteCarloNombre FicheAttaque::loi_rep_tour()const{
	return loi_proba_repetition_tour;
}

MonteCarloNombre FicheAttaque::loi_rep_coup()const{
	return loi_proba_repetition_coups;
}

bool FicheAttaque::bloc_lan()const{
	return blocage_lanceur;
}

QPair<int,int> FicheAttaque::mult_puis()const{
	return min_max_mult_puissance;
}

bool FicheAttaque::pas_ko()const{
	return ne_peut_mettre_ko;
}

bool FicheAttaque::eff_ech()const{
	return effet_echec;
}

bool FicheAttaque::eff_n_deg()const{
	return effet_non_degats;
}

bool FicheAttaque::sex_opp()const{
	return nec_sexe_oppos;
}

bool FicheAttaque::cible_som()const{
	return nec_cible_sommeil;
}

bool FicheAttaque::lanc_som()const{
	return nec_lanceur_sommeil;
}

bool FicheAttaque::descr_suppl()const{
	return description_suppl;
}

QString FicheAttaque::qi()const{
	return qui;
}

QPair<bool,bool> FicheAttaque::st_atts()const{
	return stat_att;
}

QPair<bool,bool> FicheAttaque::st_def()const{
	return stat_def;
}

QString FicheAttaque::description_part(const QString& _nom_attaque,int _langue)const{
	QString retour_;
	foreach(Effet *e,effets){
		retour_+=e->description(_langue)+"\n";
	}
	if(description_suppl){
		QList<QString> cles_=Import::_noms_descriptions_attaques_.cles();
		if(cles_.contains(_nom_attaque)){
			retour_+=Import::_noms_descriptions_attaques_.valeur(_nom_attaque)[_langue]+"\n";
		}
	}
	return retour_;
}

QString FicheAttaque::description(const QString& _nom_attaque,int _langue)const{
	QStringList args_;
	args_<<QString::number(pp);
	args_<<Utilitaire::traduire(Import::_noms_types_,type,_langue);
	args_<<Utilitaire::traduire(Import::_noms_categories_,categorie,_langue);
	args_<<QString::number(priorite);
	QString retour_=Utilitaire::formatter(_descriptions_attaques_gener_[_langue],args_)+"\n";
	args_.clear();
	if(direct){
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("DIRECT").split("\t")[_langue],args_)+"\n";
	}else{
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("INDIRECT").split("\t")[_langue],args_)+"\n";
	}
	if(precision!=101){
		args_<<QString::number(precision);
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("PRECISION_N").split("\t")[_langue],args_)+"\n";
		args_.clear();
	}else{
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("PRECISION_SURE").split("\t")[_langue],args_)+"\n";
	}
	if(fuite_adverse){
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("FUITE_ADV").split("\t")[_langue],args_)+"\n";
	}else{
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("NON_FUITE_ADV").split("\t")[_langue],args_)+"\n";
	}
	if(preparation_tour){
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("PREPA_TOUR").split("\t")[_langue],args_)+"\n";
	}else{
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("NON_PREPA_TOUR").split("\t")[_langue],args_)+"\n";
	}
	if(disparition_tour){
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("DISPARITION_TOUR").split("\t")[_langue],args_)+"\n";
	}else{
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("NON_DISPARITION_TOUR").split("\t")[_langue],args_)+"\n";
	}
	QStringList attaq_;
	foreach(QString s,touche_attaq_pokemon_disparu){
		attaq_<<Utilitaire::traduire(Import::_noms_attaques_,s,_langue);
	}
	attaq_.sort();
	if(!attaq_.isEmpty()){
		args_<<attaq_.join(",");
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("ATTAQ_TOUCH_PK_DISP").split("\t")[_langue],args_)+"\n";
		args_.clear();
	}else{
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("NON_ATTAQ_TOUCH_PK_DISP").split("\t")[_langue],args_)+"\n";
	}
	QString qui_=qui;
	qui_.replace(" ","_");
	retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur(qui_).split("\t")[_langue],args_)+"\n";
	args_<<loi_proba_repetition_tour.chaine();
	retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("LOI_PROBA_REPET_TOUR").split("\t")[_langue],args_)+"\n";
	args_.clear();
	args_<<loi_proba_repetition_coups.chaine();
	retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("LOI_PROBA_REPET_COUPS").split("\t")[_langue],args_)+"\n";
	args_.clear();
	if(blocage_lanceur){
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("BLOQ").split("\t")[_langue],args_)+"\n";
	}else{
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("NON_BLOQ").split("\t")[_langue],args_)+"\n";
	}
	args_<<QString::number(min_max_mult_puissance.first);
	args_<<QString::number(min_max_mult_puissance.second);
	retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("MIN_MAX_PUIS").split("\t")[_langue],args_)+"\n";
	args_.clear();
	if(ne_peut_mettre_ko){
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("KO_IMPOSS").split("\t")[_langue],args_)+"\n";
	}else{
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("KO_POSS").split("\t")[_langue],args_)+"\n";
	}
	if(nec_cible_sommeil){
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("CIBLE_SOM").split("\t")[_langue],args_)+"\n";
	}else{
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("NON_CIBLE_SOM").split("\t")[_langue],args_)+"\n";
	}
	if(nec_lanceur_sommeil){
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("LANCEUR_SOM").split("\t")[_langue],args_)+"\n";
	}else{
		retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("NON_LANCEUR_SOM").split("\t")[_langue],args_)+"\n";
	}
	if(stat_att.first){
		if(categorie=="PHYSIQUE"){
			retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("STAT_ATT_01").split("\t")[_langue],args_)+"\n";
		}else if(categorie!="AUTRE"){
			retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("STAT_ATT_11").split("\t")[_langue],args_)+"\n";
		}
	}else{
		if(categorie=="PHYSIQUE"){
			retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("STAT_ATT_00").split("\t")[_langue],args_)+"\n";
		}else if(categorie!="AUTRE"){
			retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("STAT_ATT_10").split("\t")[_langue],args_)+"\n";
		}
	}
	if(stat_def.first){
		if(categorie=="PHYSIQUE"){
			retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("STAT_DEF_00").split("\t")[_langue],args_)+"\n";
		}else if(categorie!="AUTRE"){
			retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("STAT_DEF_10").split("\t")[_langue],args_)+"\n";
		}
	}else{
		if(categorie=="PHYSIQUE"){
			retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("STAT_DEF_01").split("\t")[_langue],args_)+"\n";
		}else if(categorie!="AUTRE"){
			retour_+=Utilitaire::formatter(_descriptions_attaques_particul_.valeur("STAT_DEF_11").split("\t")[_langue],args_)+"\n";
		}
	}
	retour_+="\n\n";
	retour_+=description_part(_nom_attaque,_langue)+"\n";
	return retour_;
}

FicheAttaque::~FicheAttaque(){
	int i_=0;
	while(i_<effets.size()){
		Effet *e=effets[i_];
		delete e;
		e=NULL;
		effets.removeAt(i_);
	}
}



