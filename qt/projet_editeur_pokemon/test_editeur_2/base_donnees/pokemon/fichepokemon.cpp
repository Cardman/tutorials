#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/evolution/evolutionattaque.h"
#include "base_donnees/evolution/evolutionbonheur.h"
#include "base_donnees/evolution/evolutionconditionstat.h"
#include "base_donnees/evolution/evolutionpierreevolutivegenre.h"
#include "base_donnees/evolution/evolutionniveaugenre.h"
#include "base_donnees/evolution/evolutionobjet.h"
#include "base_donnees/evolution/evolutionplace.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"

const QStringList FichePokemon::_description_fiche_=FichePokemon::init_descriptions_fiches();

QStringList FichePokemon::init_descriptions_fiches(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_fiche_pokemon");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_fiche_pokemon.txt");
#endif
	QStringList lignes_=contenu_.split("\n",QString::SkipEmptyParts);
	QStringList descriptions_fiches_;
	int nb_langues_=1;//Import::_langues_.total();
	for(int i=0;i<nb_langues_;i++){
		descriptions_fiches_<<"";
	}
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		for(int i=0;i<nb_langues_;i++){
			descriptions_fiches_[i]+=infos_[i]+"\n";
		}
	}
	for(int i=0;i<nb_langues_;i++){
		descriptions_fiches_[i].chop(1);
	}
	return descriptions_fiches_;
}

FichePokemon::FichePokemon(const QStringList& _lignes){
	taille=Taux::parse_taux(_lignes.filter(QRegExp("([0-9])+\\.[0-9]\\sm"))[0].split(" ")[0]);
	masse=Taux::parse_taux(_lignes.filter(QRegExp("([0-9])+\\.[0-9]\\skg"))[0].split(" ")[0]);
	types=_lignes.filter(QRegExp("\\[[A-Z]+(,\\s[A-Z]+)*\\]"))[0].split(QRegExp("(\\W)+"),QString::SkipEmptyParts);
	QStringList leg_=_lignes.filter("<LEG>");
	if(leg_.isEmpty()){
		repartition_genre=_lignes.filter(QRegExp("^[A-Z]+$"))[0];
	}else{
		repartition_genre="<LEG>";
	}
	QStringList evos_chaines=_lignes.filter(QRegExp("^(\\w)+\\s;")).filter(QRegExp("^[A-Z]"));
	foreach(QString e,evos_chaines){
		QStringList infos_=e.split(" ; ");
		QStringList elts_;
		if(e.contains("Apprendre")){
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionAttaque(infos_[1].split(" ")[1].toUpper()));
		}else if(e.contains("Bonheur")){
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionBonheur());
		}else if(e.contains("Defense est superieure")){
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionConditionStat((uchar)infos_[1].split(",")[0].split("Niveau ")[1].toUInt(),"DEFENSE"));
		}else if(e.contains("Attaque est superieure")){
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionConditionStat((uchar)infos_[1].split(",")[0].split("Niveau ")[1].toUInt(),"ATTAQUE"));
		}else if(e.contains("Defense est egale a")){
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionConditionStat((uchar)infos_[1].split(",")[0].split("Niveau ")[1].toUInt(),""));
		}else if(e.contains("Niveau")&&e.contains(" , ")){
			elts_=infos_[1].split("Niveau ")[1].split(" , ");
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionNiveauGenre((uchar)elts_[0].toUInt(),elts_[1]));
		}else if(e.contains("Niveau")){
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionNiveau((uchar)infos_[1].split("Niveau ")[1].toUInt()));
		}else if(e.contains("en tenant")){
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionObjet(infos_[1].split("en tenant ")[1].replace(" ","_").toUpper()));
		}else if(e.contains("Pierre")&&e.contains(" , ")){
			elts_=infos_[1].split(" , ");
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionPierreEvolutiveGenre(elts_[1].toUpper(),elts_[0].replace(" ","_").toUpper()));
		}else if(e.contains("Pierre")){
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionPierreEvolutive(infos_[1].replace(" ","_").toUpper()));
		}else if(e.contains("Avoir")){
			evolutions.ajouter_cle_valeur(infos_[0],new EvolutionPlace(infos_[1].split("Avoir ")[1].split(" ")[0]));
		}
	}
	capacites=_lignes.filter(QRegExp("\\[[A-Z_]+\\s:(,\\s[A-Z_]+\\s:)*"))[0].split(QRegExp("(\\W)+"),QString::SkipEmptyParts);
	QStringList stats_;//TODO procéder par élimination de précision, esquive, coup critique
	stats_<<"PV"<<"ATTAQUE"<<"DEFENSE"<<"ATTAQUE_SPECIALE"<<"DEFENSE_SPECIALE"<<"VITESSE";
	QStringList val_ev_=_lignes.filter(QRegExp("^[0-9]+\\s;\\s[0-9]+$"));
	int indice_=0;
	foreach(QString s,stats_){
		QStringList elts_=val_ev_[indice_].split(" ; ");
		statistiques_ev.ajouter_cle_valeur(s,QPair<uchar,uchar>((uchar)elts_[0].toUInt(),(uchar)elts_[1].toUInt()));
		indice_++;
	}
	QStringList attaques_chaines_=_lignes.filter(QRegExp("\\s(\\w)+\\s;"));
	foreach(QString a,attaques_chaines_){
		QStringList elts_=a.split(" ; ");
		elts_[0]=elts_[0].mid(1);
		attaques<<QPair<uchar,QString>((uchar)elts_[1].toUInt(),elts_[0]);
	}
	foreach(QString m,_lignes.filter(QRegExp("^MT\\s"))){
		move_tutors<<m.split(" ")[1];
	}
	foreach(QString c,_lignes.filter(QRegExp("^CS\\s"))){
		capsules_secretes<<((uchar)c.split(" ")[1].toUInt());
	}
	foreach(QString c,_lignes.filter(QRegExp("^CT\\s"))){
		capsules_techniques<<((uchar)c.split(" ")[1].toUInt());
	}
	if(leg_.isEmpty()){
		base_evo=_lignes.filter(QRegExp("^[A-Z_0-9]{2,}$"))[1];
	}else{
		base_evo=_lignes.filter(QRegExp("^[A-Z_0-9]{2,}$"))[0];
	}
	courbe=_lignes.filter(QRegExp("^[A-Z]$"))[0];
	numero=_lignes.filter(QRegExp("^[0-9]+$"))[0].toInt();
	pts_exp_adv_base=_lignes.filter(QRegExp("^[0-9]+$"))[1].toUInt();
	taux_capture=(uchar)_lignes.filter(QRegExp("^[0-9]+$"))[2].toUInt();
	foreach(QString g,_lignes.filter(QRegExp("^G\\s"))){
		g_oeufs<<g.split(" ")[1];
	}
	pas_eclosion=Entier::parse_entier(_lignes.filter(QRegExp("^E\\s"))[0].mid(2));
	//Defense est egale a
}

QString FichePokemon::n_pk()const{
	return nom;
}

int FichePokemon::num()const{
	return numero;
}

Taux FichePokemon::m_pk()const{
	return masse;
}

QStringList FichePokemon::typs()const{
	return types;
}

HashMap<QString,QPair<uchar,uchar> > FichePokemon::stat_ev()const{
	return statistiques_ev;
}

QList<QPair<uchar,QString> > FichePokemon::atts()const{
	return attaques;
}

QString FichePokemon::rep_genr()const{
	return repartition_genre;
}

QStringList FichePokemon::capac()const{
	return capacites;
}

QStringList FichePokemon::mt()const{
	return move_tutors;
}

QList<uchar> FichePokemon::cs()const{
	return capsules_secretes;
}

QList<uchar> FichePokemon::ct()const{
	return capsules_techniques;
}

QString FichePokemon::b_ev()const{
	return base_evo;
}

HashMap<QString,Evolution*> FichePokemon::evos()const{
	return evolutions;
}

uchar FichePokemon::tx_capt()const{
	return taux_capture;
}

Taux FichePokemon::t_pk()const{
	return taille;
}

QString FichePokemon::cb()const{
	return courbe;
}

uint FichePokemon::pt_base()const{
	return pts_exp_adv_base;
}

QStringList FichePokemon::gps_o()const{
	return g_oeufs;
}

Entier FichePokemon::pas_ecl()const{
	return pas_eclosion;
}

QString FichePokemon::description(const QString& _nom_pk,int _langue){
	QStringList args_;
	args_<<Utilitaire::traduire(Import::_noms_pk_,_nom_pk,_langue);
	args_<<QString::number(numero);
	args_<<masse.chaine();
	QStringList types_pk_;
	foreach(QString t,types){
		types_pk_<<Utilitaire::traduire(Import::_noms_types_,t,_langue);
	}
	types_pk_.sort();
	args_<<types_pk_.join(", ");
	QString arg_stat_;
	foreach(QString s,statistiques_ev.cles()){
		QPair<uchar,uchar> val_=statistiques_ev.valeur(s);
		arg_stat_+=Utilitaire::traduire(Import::_noms_statistiques_,s,_langue)+"\t"+QString::number(val_.first)+"\t"+QString::number(val_.second)+"\n";
	}
	args_<<arg_stat_;
	QString arg_att_n_;
	typedef QPair<uchar,QString> AttNiv;
	foreach(AttNiv a,attaques){
		arg_att_n_+="\t"+QString::number(a.first)+"\t"+Utilitaire::traduire(Import::_noms_attaques_,a.second,_langue)+"\n";
	}
	args_<<arg_att_n_;
	if(repartition_genre=="<LEG>"){
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,"LEG",_langue+1);
	}else if(repartition_genre=="ASSEXUE"||repartition_genre=="MIXTE"){
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,repartition_genre,_langue+1);
	}else{
		args_<<Utilitaire::traduire_bis(Import::_constantes_non_num_,repartition_genre+"_100",_langue+1);
	}
	QString arg_att_ct_;
	foreach(uchar t,capsules_techniques){
		arg_att_ct_+=QString::number(t)+"\t"+Utilitaire::traduire(Import::_noms_attaques_,Import::_ct_.valeur(t),_langue)+"\n";
	}
	args_<<arg_att_ct_;
	QString arg_att_cs_;
	foreach(uchar s,capsules_secretes){
		arg_att_cs_+=QString::number(s)+"\t"+Utilitaire::traduire(Import::_noms_attaques_,Import::_cs_.valeur(s),_langue)+"\n";
	}
	args_<<arg_att_cs_;
	QStringList capac_pk_;
	foreach(QString c,capacites){
		capac_pk_<<Utilitaire::traduire(Import::_noms_capacites_,c,_langue);
	}
	capac_pk_.sort();
	args_<<capac_pk_.join(", ");
	QStringList mt_pk_;
	foreach(QString a,move_tutors){
		mt_pk_<<Utilitaire::traduire(Import::_noms_attaques_,a,_langue);
	}
	mt_pk_.sort();
	args_<<mt_pk_.join("\n");
	args_<<Utilitaire::traduire(Import::_noms_pk_,base_evo,_langue);
	args_<<QString::number(taux_capture);
	args_<<taille.chaine();
	args_<<Utilitaire::traduire(Import::_types_courbes_,courbe,_langue+1);
	args_<<QString::number(pts_exp_adv_base);
	QStringList gp_oeuf_;
	foreach(QString g,g_oeufs){
		gp_oeuf_<<Utilitaire::traduire(Import::_groupes_oeufs_,g,_langue+1);
	}
	gp_oeuf_.sort();
	args_<<gp_oeuf_.join(", ");
	args_<<pas_eclosion.chaine();
	args_<<masse.evaluer(2);
	args_<<taille.evaluer(2);
	QString retour_=Utilitaire::formatter(_description_fiche_[_langue],args_)+"\n";
	foreach(QString e,evolutions.cles()){
		retour_+=evolutions.valeur(e)->description(_nom_pk,e,_langue);
	}
	return retour_;
}

QStringList FichePokemon::pokemons_evolues()const{
	return evolutions.cles();
}

Evolution* FichePokemon::facon_evoluer(const QString& _nom_evo)const{
	return evolutions.valeur(_nom_evo);
}

FichePokemon::~FichePokemon(){
	QList<QString> cles_=evolutions.cles();
	foreach(QString c,cles_){
		Evolution* evo_=evolutions.valeur(c);
		delete evo_;
		evo_=NULL;
		evolutions.supprimer_cle_valeur(c);
	}
}


