#include "base_donnees/initbdd.h"
#include "base_donnees/import.h"
#include "base_donnees/attaques/ficheattaque.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/evolution/evolution.h"
//#include "base_donnees/evolution/evolutionbonheur.h"
#include "base_donnees/evolution/evolutionniveau.h"
#include "base_donnees/evolution/evolutionbonheur.h"
#include "base_donnees/evolution/evolutionpierreevolutive.h"
#include "base_donnees/evolution/evolutionpierreevolutivegenre.h"
#include "base_donnees/evolution/evolutionobjet.h"
#include "base_donnees/evolution/evolutionattaque.h"
#include "autre/utilitaire.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

bool InitBDD::_fini_=false;

InitBDD::InitBDD(int _langue):QThread(0){
	langue=_langue;
	avancement=0;
}

void InitBDD::run(){
	initialialiser();
}

void InitBDD::initialialiser(){
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//QODBC
	db.setDatabaseName(":memory:");
	if (!db.open()) {;
		_fini_=true;
	    return;
	}
	QSqlQuery query_;
	QString requette_;
	QString nom_table_=Import::constante_non_numerique("SQL_TABLE_TYPE",langue+1);
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_TABLE_TYPE_TYPE1",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_TABLE_TYPE_TYPE2",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_TABLE_TYPE_EFF",langue+1)+" float, ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_TABLE_TYPE_TYPE1",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_TABLE_TYPE_TYPE2",langue+1)+"))";
	query_.exec(requette_);
	typedef QPair<QString,QString> Cle;
	foreach(Cle c,Import::_table_types_base_.cles()){
		QString type_1_=Utilitaire::traduire(Import::_noms_types_,c.first,langue);
		QString type_2_=Utilitaire::traduire(Import::_noms_types_,c.second,langue);
		query_.exec("insert into "+nom_table_+" values('"+type_1_+"','"+type_2_+"',"+Import::_table_types_base_.valeur(c).evaluer(1)+")");
		avancement++;
		emit nv_avanc(avancement);
	}
	nom_table_=Import::constante_non_numerique("SQL_POKEDEX",langue+1);
	QString table_pk_=nom_table_;
	requette_="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_NUMERO",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_MASSE",langue+1)+" float, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_TAILLE",langue+1)+" float, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_REP_GENRE",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_EXP_BASE",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_PV",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_PV_EV",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_ATTAQUE",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_ATTAQUE_EV",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_DEFENSE",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_DEFENSE_EV",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_ATTAQUE_SPECIALE",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_ATTAQUE_SPECIALE_EV",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_DEFENSE_SPECIALE",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_DEFENSE_SPECIALE_EV",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_VITESSE",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_VITESSE_EV",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_TX_CAPT",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_PAS_ECL",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_PKBASE",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_PKBASE",langue+1)+")";
	requette_+=" references "+nom_table_+"(";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"))";
	//TODO ici
	query_.exec(requette_);
	foreach(QString n,Import::_bases_evos_){
		FichePokemon *f_pk_=Import::_pokedex_.valeur(n);
		QString pk_=Utilitaire::traduire(Import::_noms_pk_,n,langue);
		requette_.clear();
		requette_+="insert into "+nom_table_+" values('"+pk_+"',"+QString::number(f_pk_->num())+","+f_pk_->t_pk().evaluer(1)+","+f_pk_->m_pk().evaluer(1)+",'";
		//QString genre_=Utilitaire::traduire(Import::_noms_genres_,f_pk_->rep_genr(),langue);
		QString genre_=Utilitaire::traduire(Import::_noms_pk_,pk_,langue);
		requette_+=genre_+"',"+QString::number(f_pk_->pt_base())+",";
		foreach(QString s,f_pk_->stat_ev().cles()){
			requette_+=QString::number(f_pk_->stat_ev().valeur(s).first)+","+QString::number(f_pk_->stat_ev().valeur(s).second)+",";
		}
		requette_+=QString::number(f_pk_->tx_capt())+","+f_pk_->pas_ecl().chaine()+",'"+pk_+"')";
		query_.exec(requette_);
		avancement++;
		emit nv_avanc(avancement);
	}
	foreach(QString n,Import::_pokedex_.cles()){
		if(Import::_bases_evos_.contains(n)){
			continue;
		}
		FichePokemon *f_pk_=Import::_pokedex_.valeur(n);
		QString pk_=Utilitaire::traduire(Import::_noms_pk_,n,langue);
		requette_.clear();
		requette_+="insert into "+nom_table_+" values('"+pk_+"',"+QString::number(f_pk_->num())+","+f_pk_->t_pk().evaluer(1)+","+f_pk_->m_pk().evaluer(1)+",'";
		QString genre_=Utilitaire::traduire(Import::_noms_pk_,n,langue);
		requette_+=genre_+"',"+QString::number(f_pk_->pt_base())+",";
		foreach(QString s,f_pk_->stat_ev().cles()){
			requette_+=QString::number(f_pk_->stat_ev().valeur(s).first)+","+QString::number(f_pk_->stat_ev().valeur(s).second)+",";
		}
		pk_=Utilitaire::traduire(Import::_noms_pk_,f_pk_->b_ev(),langue);
		requette_+=QString::number(f_pk_->tx_capt())+","+f_pk_->pas_ecl().chaine()+",'"+pk_+"')";
		query_.exec(requette_);
		avancement++;
		emit nv_avanc(avancement);
	}
	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_EVOLUTIONS_NIV",langue+1);
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_NIV_NOMBASE",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_NIV_NOMEVO",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_NIV_NIVEAU",langue+1)+" int, ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_NIV_NOMBASE",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_NIV_NOMEVO",langue+1)+"),";
	requette_+=" foreign key("+Import::constante_non_numerique("SQL_EVOLUTIONS_NIV_NOMBASE",langue+1)+")";
	requette_+=" references "+table_pk_+"("+Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"),";
	requette_+=" foreign key("+Import::constante_non_numerique("SQL_EVOLUTIONS_NIV_NOMEVO",langue+1)+")";
	requette_+=" references "+table_pk_+"("+Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"))";
	query_.exec(requette_);
	foreach(QString n,Import::_pokedex_.cles()){
		FichePokemon *f_pk_=Import::_pokedex_.valeur(n);
		QString n_pk_=Utilitaire::traduire(Import::_noms_pk_,n,langue);
		requette_.clear();
		HashMap<QString,Evolution*> evos_=f_pk_->evos();
		foreach(QString e,evos_.cles()){
			EvolutionNiveau *niv_=qobject_cast<EvolutionNiveau*>(evos_.valeur(e));
			if(niv_){
				requette_.clear();
				QString e_pk_=Utilitaire::traduire(Import::_noms_pk_,e,langue);
				requette_+="insert into "+nom_table_+" values('"+n_pk_+"','"+e_pk_+"',"+QString::number(niv_->niv())+")";
				query_.exec(requette_);
				avancement++;
				emit nv_avanc(avancement);
			}
		}
	}
	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_EVOLUTIONS_BONHEUR",langue+1);
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_BONHEUR_NOMBASE",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_BONHEUR_NOMEVO",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_BONHEUR_NOMBASE",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_BONHEUR_NOMEVO",langue+1)+"),";
	requette_+=" foreign key("+Import::constante_non_numerique("SQL_EVOLUTIONS_BONHEUR_NOMBASE",langue+1)+")";
	requette_+=" references "+table_pk_+"("+Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"),";
	requette_+=" foreign key("+Import::constante_non_numerique("SQL_EVOLUTIONS_BONHEUR_NOMEVO",langue+1)+")";
	requette_+=" references "+table_pk_+"("+Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"))";
	query_.exec(requette_);
	foreach(QString n,Import::_pokedex_.cles()){
		FichePokemon *f_pk_=Import::_pokedex_.valeur(n);
		QString n_pk_=Utilitaire::traduire(Import::_noms_pk_,n,langue);
		requette_.clear();
		HashMap<QString,Evolution*> evos_=f_pk_->evos();
		foreach(QString e,evos_.cles()){
			EvolutionBonheur *niv_=qobject_cast<EvolutionBonheur*>(evos_.valeur(e));
			if(niv_){
				requette_.clear();
				QString e_pk_=Utilitaire::traduire(Import::_noms_pk_,e,langue);
				requette_+="insert into "+nom_table_+" values('"+n_pk_+"','"+e_pk_+"')";
				query_.exec(requette_);
				avancement++;
				emit nv_avanc(avancement);
			}
		}
	}
	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_EVOLUTIONS_PIERREEVO",langue+1);
	//requette_="create table evolutions_pierreevo (nombase varchar(15), nomevo varchar(15), pierre varchar(15),"
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_PIERREEVO_NOMBASE",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_PIERREEVO_NOMEVO",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_PIERREEVO_PIERRE",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_PIERREEVO_NOMBASE",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_PIERREEVO_NOMEVO",langue+1)+"),";
	requette_+=" foreign key("+Import::constante_non_numerique("SQL_EVOLUTIONS_PIERREEVO_NOMBASE",langue+1)+")";
	requette_+=" references "+table_pk_+"("+Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"),";
	requette_+=" foreign key("+Import::constante_non_numerique("SQL_EVOLUTIONS_PIERREEVO_NOMEVO",langue+1)+")";
	requette_+=" references "+table_pk_+"("+Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"))";
	//requette_+=" primary key(nombase,nomevo),foreign key (nombase) references pokedex(nom),foreign key (nomevo) references pokedex(nom))"
	query_.exec(requette_);
	foreach(QString n,Import::_pokedex_.cles()){
		FichePokemon *f_pk_=Import::_pokedex_.valeur(n);
		QString n_pk_=Utilitaire::traduire(Import::_noms_pk_,n,langue);
		requette_.clear();
		HashMap<QString,Evolution*> evos_=f_pk_->evos();
		foreach(QString e,evos_.cles()){
			EvolutionPierreEvolutive *niv_=qobject_cast<EvolutionPierreEvolutive*>(evos_.valeur(e));
			if(niv_){
				QString e_pk_=Utilitaire::traduire(Import::_noms_pk_,e,langue);
				requette_.clear();
				QString pierre_=niv_->nom_pierre();
				requette_+="insert into "+nom_table_+" values('"+n_pk_+"','"+e_pk_+"','"+Utilitaire::traduire(Import::_noms_objets_,pierre_,langue)+"')";
				query_.exec(requette_);
				avancement++;
				emit nv_avanc(avancement);
			}
		}
	}
	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_EVOLUTIONS_OBJEVO",langue+1);
	//requette_="create table evolutions_pierreevo (nombase varchar(15), nomevo varchar(15), pierre varchar(15),"
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_OBJEVO_NOMBASE",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_OBJEVO_NOMEVO",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_OBJEVO_OBJET",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_OBJEVO_NOMBASE",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_OBJEVO_NOMEVO",langue+1)+"),";
	requette_+=" foreign key("+Import::constante_non_numerique("SQL_EVOLUTIONS_OBJEVO_NOMBASE",langue+1)+")";
	requette_+=" references "+table_pk_+"("+Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"),";
	requette_+=" foreign key("+Import::constante_non_numerique("SQL_EVOLUTIONS_OBJEVO_NOMEVO",langue+1)+")";
	requette_+=" references "+table_pk_+"("+Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"))";
	;
	//requette_="create table evolutions_objevo (nombase varchar(15), nomevo varchar(15), objet varchar(15),"
	//requette_+=" primary key(nombase,nomevo),foreign key (nombase) references pokedex(nom),foreign key (nomevo) references pokedex(nom))"
	query_.exec(requette_);
	foreach(QString n,Import::_pokedex_.cles()){
		FichePokemon *f_pk_=Import::_pokedex_.valeur(n);
		QString n_pk_=Utilitaire::traduire(Import::_noms_pk_,n,langue);
		requette_.clear();
		HashMap<QString,Evolution*> evos_=f_pk_->evos();
		foreach(QString e,evos_.cles()){
			EvolutionObjet *niv_=qobject_cast<EvolutionObjet*>(evos_.valeur(e));
			if(niv_){
				QString e_pk_=Utilitaire::traduire(Import::_noms_pk_,e,langue);
				requette_.clear();
				QString objet_=niv_->nom_objet();
				requette_+="insert into "+nom_table_+" values('"+n_pk_+"','"+e_pk_+"','"+Utilitaire::traduire(Import::_noms_objets_,objet_,langue)+"')";
				query_.exec(requette_);
				avancement++;
				emit nv_avanc(avancement);
			}
		}
	}
	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_EVOLUTIONS_ATTAQUE",langue+1);
	//requette_="create table evolutions_pierreevo (nombase varchar(15), nomevo varchar(15), pierre varchar(15),"
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_ATTAQUE_NOMBASE",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_ATTAQUE_NOMEVO",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_ATTAQUE_NOMATT",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_ATTAQUE_NOMBASE",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_EVOLUTIONS_ATTAQUE_NOMEVO",langue+1)+"),";
	requette_+=" foreign key("+Import::constante_non_numerique("SQL_EVOLUTIONS_ATTAQUE_NOMBASE",langue+1)+")";
	requette_+=" references "+table_pk_+"("+Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"),";
	requette_+=" foreign key("+Import::constante_non_numerique("SQL_EVOLUTIONS_ATTAQUE_NOMEVO",langue+1)+")";
	requette_+=" references "+table_pk_+"("+Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"))";

	//requette_="create table evolutions_attaque (nombase varchar(15), nomevo varchar(15), nomatt varchar(15),"
	//requette_+=" primary key(nombase,nomevo),foreign key (nombase) references pokedex(nom),foreign key (nomevo) references pokedex(nom))"
	query_.exec(requette_);
	foreach(QString n,Import::_pokedex_.cles()){
		FichePokemon *f_pk_=Import::_pokedex_.valeur(n);
		QString n_pk_=Utilitaire::traduire(Import::_noms_pk_,n,langue);
		requette_.clear();
		HashMap<QString,Evolution*> evos_=f_pk_->evos();
		foreach(QString e,evos_.cles()){
			EvolutionAttaque *niv_=qobject_cast<EvolutionAttaque*>(evos_.valeur(e));
			if(niv_){
				QString e_pk_=Utilitaire::traduire(Import::_noms_pk_,e,langue);
				requette_.clear();
				QString attaque_=niv_->attaque();
				requette_+="insert into "+nom_table_+" values('"+n_pk_+"','"+e_pk_+"','"+Utilitaire::traduire(Import::_noms_attaques_,attaque_,langue)+"')";
				query_.exec(requette_);
				avancement++;
				emit nv_avanc(avancement);
			}
		}
	}
	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_TABLE_ATTAQUES",langue+1);
	QString table_att_=nom_table_;
	//requette_="create table evolutions_pierreevo (nombase varchar(15), nomevo varchar(15), pierre varchar(15),"
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_NOM",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_TYPE_ATT",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_PRIO",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_PUISSANCE",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_PUISSANCE_FIXE",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_CATEGORIE",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_DIRECTE",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_PRECISION",langue+1)+" int, ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_NOM",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_TYPE_ATT",langue+1)+")";
	requette_+=" references "+Import::constante_non_numerique("SQL_TABLE_TYPE",langue+1)+"(";
	requette_+=Import::constante_non_numerique("SQL_TABLE_TYPE_TYPE1",langue+1)+"))";
	//requette_="create table attaques (nom varchar(15), type_att varchar(15), prio int, puissance int,"
	//requette_+="effet_neg_lanceur varchar(3), effet_neg_cible varchar(3), effet_pos_lanceur varchar(3), effet_pos_cible varchar(3),"
	//requette_+="puissance_fixe varchar(4), categorie varchar(10), directe varchar(4), precision int,"
	//requette_+=" primary key(nom),foreign key (type_att) references table_type(type1))"
	query_.exec(requette_);
	foreach(QString n,Import::_attaques_.cles()){
		FicheAttaque *f_att_=Import::_attaques_.valeur(n);
		QString n_att_=Utilitaire::traduire(Import::_noms_attaques_,n,langue);
		QString n_type_=Utilitaire::traduire(Import::_noms_types_,f_att_->tp(),langue);
		requette_.clear();
		requette_+="insert into "+nom_table_+" values('"+n_att_+"','"+n_type_+"',"+QString::number(f_att_->prio())+","+QString::number(f_att_->puis())+",'";
		QString categ_=f_att_->cat();
		if(categ_=="AUTRE"||f_att_->puis()>0){
			requette_+=Import::constante_non_numerique("SQL_OUI",langue+1);
		}else{
			requette_+=Import::constante_non_numerique("SQL_NON",langue+1);
		}
		requette_+="','";
		requette_+=Utilitaire::traduire(Import::_noms_categories_,categ_,langue)+"','";
		if(categ_=="AUTRE"){
			requette_+=Import::constante_non_numerique("SQL_XX",langue+1);
		}else if(f_att_->dir()){
			requette_+=Import::constante_non_numerique("SQL_OUI",langue+1);
		}else{
			requette_+=Import::constante_non_numerique("SQL_NON",langue+1);
		}
		requette_+="',";
		requette_+=QString::number(f_att_->prec())+")";
		query_.exec(requette_);
		avancement++;
		emit nv_avanc(avancement);
	}
	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_CS_ATTAQUE",langue+1);
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_CS_ATTAQUE_CS",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_CS_ATTAQUE_ATTAQUE",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_CS_ATTAQUE_CS",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_CS_ATTAQUE_ATTAQUE",langue+1)+")";
	requette_+=" references "+table_att_+"(";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_NOM",langue+1)+"))";
	//nom_table_
	query_.exec(requette_);
	foreach(uchar c,Import::_cs_.cles()){
		requette_.clear();
		QString n_att_=Utilitaire::traduire(Import::_noms_attaques_,Import::_cs_.valeur(c),langue);
		requette_+="insert into "+nom_table_+" values("+QString::number(c)+",'"+n_att_+"')";
		query_.exec(requette_);
		avancement++;
		emit nv_avanc(avancement);
	}
	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_CT_ATTAQUE",langue+1);
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_CT_ATTAQUE_CT",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_CT_ATTAQUE_ATTAQUE",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_CT_ATTAQUE_CT",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_CT_ATTAQUE_ATTAQUE",langue+1)+")";
	requette_+=" references "+table_att_+"(";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_NOM",langue+1)+"))";
	//nom_table_
	query_.exec(requette_);
	foreach(uchar c,Import::_ct_.cles()){
		requette_.clear();
		QString n_att_=Utilitaire::traduire(Import::_noms_attaques_,Import::_ct_.valeur(c),langue);
		requette_+="insert into "+nom_table_+" values("+QString::number(c)+",'"+n_att_+"')";
		query_.exec(requette_);
		avancement++;
		emit nv_avanc(avancement);
	}

	/*QString requette_2_="create table niv_att (nom varchar(15), niv int, attaque varchar(15), primary key(nom,niv,attaque), "
	requette_2_+="foreign key (nom) references pokedex(nom),foreign key (attaque) references attaques(nom))"
	query_.exec(requette_2_)

	requette_2_="create table type_pk (nom varchar(15), type varchar(15), primary key(nom,type), "
	requette_2_+="foreign key (nom) references pokedex(nom))"
	query_.exec(requette_2_)
	requette_2_="create table capac_pk (nom varchar(15), capacite varchar(15), primary key(nom,capacite), "
	requette_2_+="foreign key (nom) references pokedex(nom))"
	query_.exec(requette_2_)
	requette_2_="create table mt_pk (nom varchar(15), mt varchar(15), primary key(nom,mt), "
	requette_2_+="foreign key (nom) references pokedex(nom))"
	query_.exec(requette_2_)*/

	nom_table_=Import::constante_non_numerique("SQL_NIV_ATT",langue+1);
	QString table_niv_att_=nom_table_;
	requette_="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_NIV_ATT_NOM",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_NIV_ATT_NIV",langue+1)+" int, ";
	requette_+=Import::constante_non_numerique("SQL_NIV_ATT_ATTAQUE",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_NIV_ATT_NOM",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_NIV_ATT_NIV",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_NIV_ATT_ATTAQUE",langue+1)+")";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_NIV_ATT_ATTAQUE",langue+1)+")";
	requette_+=" references "+table_pk_+"(";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_NOM",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_NIV_ATT_NOM",langue+1)+")";
	requette_+=" references "+table_att_+"(";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"))";
	//nom_table_
	query_.exec(requette_);
	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_TYPE_PK",langue+1);
	QString table_type_pk_=nom_table_;
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_TYPE_PK_NOM",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_TYPE_PK_TYPE",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_TYPE_PK_NOM",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_TYPE_PK_TYPE",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_TYPE_PK_NOM",langue+1)+")";
	requette_+=" references "+table_pk_+"(";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"))";
	query_.exec(requette_);

	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_CAPAC_PK",langue+1);
	QString table_capac_=nom_table_;
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_CAPAC_PK_NOM",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_CAPAC_PK_CAPACITE",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_CAPAC_PK_NOM",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_CAPAC_PK_CAPACITE",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_CAPAC_PK_NOM",langue+1)+")";
	requette_+=" references "+table_pk_+"(";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"))";
	query_.exec(requette_);

	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_MT_PK",langue+1);
	QString table_mt_=nom_table_;
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_MT_PK_NOM",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_MT_PK_MT",langue+1)+" varchar(15), ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_MT_PK_NOM",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_MT_PK_MT",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_MT_PK_NOM",langue+1)+")";
	requette_+=" references "+table_pk_+"(";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_MT_PK_MT",langue+1)+")";
	requette_+=" references "+table_att_+"(";
	requette_+=Import::constante_non_numerique("SQL_TABLE_ATTAQUES_NOM",langue+1)+"))";
	query_.exec(requette_);


	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_CS_PK",langue+1);
	QString table_cs_pk_=nom_table_;
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_CS_PK_NOM",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_CS_PK_CS",langue+1)+" int, ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_CS_PK_NOM",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_CS_PK_CS",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_CS_PK_NOM",langue+1)+")";
	requette_+=" references "+table_pk_+"(";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_CS_PK_CS",langue+1)+")";
	requette_+=" references "+Import::constante_non_numerique("SQL_CS_ATTAQUE",langue+1)+"(";
	requette_+=Import::constante_non_numerique("SQL_CS_ATTAQUE_CS",langue+1)+"))";
	query_.exec(requette_);
	requette_.clear();
	nom_table_=Import::constante_non_numerique("SQL_CT_PK",langue+1);
	QString table_ct_pk_=nom_table_;
	requette_+="create table "+nom_table_+" (";
	requette_+=Import::constante_non_numerique("SQL_CT_PK_NOM",langue+1)+" varchar(15), ";
	requette_+=Import::constante_non_numerique("SQL_CT_PK_CT",langue+1)+" int, ";
	requette_+=" primary key(";
	requette_+=Import::constante_non_numerique("SQL_CT_PK_NOM",langue+1)+",";
	requette_+=Import::constante_non_numerique("SQL_CT_PK_CT",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_CT_PK_NOM",langue+1)+")";
	requette_+=" references "+table_pk_+"(";
	requette_+=Import::constante_non_numerique("SQL_POKEDEX_NOM",langue+1)+"),";
	requette_+=" foreign key(";
	requette_+=Import::constante_non_numerique("SQL_CT_PK_CT",langue+1)+")";
	requette_+=" references "+Import::constante_non_numerique("SQL_CT_ATTAQUE",langue+1)+"(";
	requette_+=Import::constante_non_numerique("SQL_CT_ATTAQUE_CT",langue+1)+"))";
	query_.exec(requette_);

	/*requette_2_="create table ct_pk (nom varchar(15), ct int, primary key(nom,ct), "
	requette_2_+="foreign key (nom) references pokedex(nom),foreign key (ct) references ct_attaque(ct))"
	query_.exec(requette_2_)
	requette_2_="create table cs_pk (nom varchar(15), cs int, primary key(nom,cs), "
	requette_2_+="foreign key (nom) references pokedex(nom),foreign key (cs) references cs_attaque(cs))"
	query_.exec(requette_2_)*/
	//int nb_=ls_.size()
	foreach(QString pok,Import::_pokedex_.cles()){
		FichePokemon *f_pk_=Import::_pokedex_.valeur(pok);
		QString n_pk_=Utilitaire::traduire(Import::_noms_pk_,pok,langue);
		QString n_att_;
		QString n_capac_;
		QString n_type_;
		QSqlQuery req_;
		typedef QPair<uchar,QString> NivAtt;
		foreach(NivAtt n,f_pk_->atts()){
			requette_.clear();
			requette_+="insert into "+table_niv_att_+" values('";
			requette_+=n_pk_+"',"+QString::number(n.first)+",'";
			n_att_=Utilitaire::traduire(Import::_noms_attaques_,n.second,langue);
			requette_+=n_att_+"')";
			req_.exec(requette_);
			avancement++;
			emit nv_avanc(avancement);
		}
		foreach(QString n,f_pk_->typs()){
			requette_.clear();
			requette_+="insert into "+table_type_pk_+" values('";
			n_type_=Utilitaire::traduire(Import::_noms_types_,n,langue);
			requette_+=n_pk_+"','"+n_type_+"')";
			req_.exec(requette_);
			avancement++;
			emit nv_avanc(avancement);
		}
		foreach(QString n,f_pk_->capac()){
			requette_.clear();
			requette_+="insert into "+table_capac_+" values('";
			n_capac_=Utilitaire::traduire(Import::_noms_capacites_,n,langue);
			requette_+=n_pk_+"','"+n_capac_+"')";
			req_.exec(requette_);
			avancement++;
			emit nv_avanc(avancement);
		}
		foreach(uchar c,f_pk_->ct()){
			requette_.clear();
			requette_+="insert into "+table_ct_pk_+" values('";
			requette_+=n_pk_+"','"+QString::number(c)+"')";
			req_.exec(requette_);
			avancement++;
			emit nv_avanc(avancement);
		}
		foreach(uchar c,f_pk_->cs()){
			requette_.clear();
			requette_+="insert into "+table_cs_pk_+" values('";
			requette_+=n_pk_+"','"+QString::number(c)+"')";
			req_.exec(requette_);
			avancement++;
			emit nv_avanc(avancement);
		}
		foreach(QString n,f_pk_->mt()){
			requette_.clear();
			requette_+="insert into "+table_mt_+" values('";
			n_att_=Utilitaire::traduire(Import::_noms_attaques_,n,langue);
			requette_+=n_pk_+"','"+n_att_+"')";
			req_.exec(requette_);
			avancement++;
			emit nv_avanc(avancement);
		}
	}
	_fini_=true;
}

