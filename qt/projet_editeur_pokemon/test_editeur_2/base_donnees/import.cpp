#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/attaques/ficheattaque.h"
#include "base_donnees/capacites/fichecapacite.h"
//#include "base_donnees/objets/objet.h"
#include "base_donnees/objets/baie.h"
#include "base_donnees/objets/ball.h"
#include "base_donnees/objets/boost.h"
#include "base_donnees/objets/fossile.h"
#include "base_donnees/objets/objetattachablecombat.h"
#include "base_donnees/objets/objetevo.h"
#include "base_donnees/objets/pierreevo.h"
#include "base_donnees/objets/plaque.h"
#include "base_donnees/objets/module.h"
#include "base_donnees/objets/repousse.h"
#include "base_donnees/objets/revente.h"
#include "base_donnees/objets/soin.h"
#include "base_donnees/objets/soinpp.h"
#include "base_donnees/objets/soinpv.h"
#include "base_donnees/objets/soinpvstatut.h"
#include "base_donnees/objets/soinstatut.h"
#include "base_donnees/evolution/evolutionobjet.h"
#include "base_donnees/evolution/evolutionpierreevolutivegenre.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QDir>

const int Import::_log_base_=Entier::log_base();

const HashMap<QString,QStringList> Import::_noms_menus_=Import::init_noms_menus();

#ifdef QT_NO_DEBUG
const QImage Import::_tuile_invalide_=QImage(":/ihm/tuile_invalide");
#else
const QImage Import::_tuile_invalide_=QImage("fichiers_ressources/ihm/tuile_invalide.png");
#endif

#ifdef QT_NO_DEBUG
const QImage Import::_map_invalide_=QImage(":/map/map_invalide");
#else
const QImage Import::_map_invalide_=QImage("fichiers_ressources/ihm/map/map_invalide.png");
#endif

#ifdef QT_NO_DEBUG
const QImage Import::_pk_trouve_=QImage(":/ihm/objet_trouve");
#else
const QImage Import::_pk_trouve_=QImage("fichiers_ressources/ihm/objet_trouve.png");
#endif

const QStringList Import::_dossiers_tuiles_=Import::init_dossiers_tuiles();

const QStringList Import::_dossiers_dresseurs_macro_=Import::init_dossiers_dresseurs_macro();

const QStringList Import::_dossiers_dresseurs_micro_=Import::init_dossiers_dresseurs_micro();

const HashMap<QString,QImage> Import::_liens_=Import::init_liens();

const HashMap<QString,QImage> Import::_elements_map_=Import::init_elements_map();

const HashMap<QString,QImage> Import::_tuiles_importees_=Import::init_tuiles_importees();

const HashMap<QString,QImage> Import::_dresseurs_macros_=Import::init_dresseurs_macros();

const HashMap<QString,QImage> Import::_dresseurs_micros_=Import::init_dresseurs_micros();
////enum TypeObstacle{ARBRE,ROCHER_DEST,ROCHER_AMOV,TOURBILLON};

const HashMap<QString,QImage> Import::_arbres_=Import::init_obstacles(Import::ARBRE);

const HashMap<QString,QImage> Import::_rochers_destructibles_=Import::init_obstacles(Import::ROCHER_DEST);

const HashMap<QString,QImage> Import::_rochers_amovibles_=Import::init_obstacles(Import::ROCHER_AMOV);

const HashMap<QString,QImage> Import::_tourbillons_=Import::init_obstacles(Import::TOURBILLON);

const HashMap<QString,QStringList> Import::_noms_descriptions_attaques_=Import::init_descriptions_complements();

	/**noms des types des pokémons*/
#ifdef QT_NO_DEBUG
const QStringList Import::_constantes_=Utilitaire::lire_fichier(":/fichiers_ressources/constantes").split("\n");
#else
const QStringList Import::_constantes_=Utilitaire::lire_fichier("fichiers_ressources/constantes.txt").split("\n");
#endif

#ifdef QT_NO_DEBUG
const QStringList Import::_noms_genres_=Utilitaire::lire_fichier(":/fichiers_ressources/noms_genres").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_genres_=Utilitaire::lire_fichier("fichiers_ressources/noms_genres.txt").split("\n",QString::SkipEmptyParts);
#endif

#ifdef QT_NO_DEBUG
const QStringList Import::_constantes_non_num_=Utilitaire::lire_fichier(":/fichiers_ressources/constantes_non_num").split("\n");
#else
const QStringList Import::_constantes_non_num_=Utilitaire::lire_fichier("fichiers_ressources/constantes_non_num.txt").split("\n");
#endif

const int Import::_adv_=1;

const int Import::_ut_=0;

const HashMap<QPair<QString,QString>,Taux> Import::_attaques_touchant_pseudo_invuln_=Import::init_attaques_touchant_pseudo_invuln();

const HashMap<QString,Taux> Import::_attaques_lilliput_=Import::init_attaques_lilliput();

const HashMap<QString,Taux> Import::_puissance_degommage_=Import::init_puissance_degommage();
//
/**noms des types des pokémons*/
#ifdef QT_NO_DEBUG
//const QStringList _noms_pk_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_noms_pk").split("\n");//trad_n_pk
const QStringList Import::_noms_pk_=Utilitaire::lire_fichier(":/fichiers_ressources/trad_n_pk").split("\n",QString::SkipEmptyParts);//trad_n_pk
#else
const QStringList Import::_noms_pk_=Utilitaire::lire_fichier("fichiers_ressources/trad_n_pk.txt").split("\n",QString::SkipEmptyParts);
#endif

//type_environnement_2
#ifdef QT_NO_DEBUG
//const QStringList _noms_pk_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_noms_pk").split("\n");//trad_n_pk
const QStringList Import::_noms_envir_=Utilitaire::lire_fichier(":/fichiers_ressources/type_environnement").split("\n",QString::SkipEmptyParts);//trad_n_pk
#else
const QStringList Import::_noms_envir_=Utilitaire::lire_fichier("fichiers_ressources/type_environnement.txt").split("\n",QString::SkipEmptyParts);
#endif

const HashMap<QString,QImage> Import::_images_env_def_=Import::init_images_env_def();

/**noms des types des pokémons*/
#ifdef QT_NO_DEBUG
const QStringList Import::_noms_types_=Utilitaire::lire_fichier(":/fichiers_ressources/types").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_types_=Utilitaire::lire_fichier("fichiers_ressources/types.txt").split("\n",QString::SkipEmptyParts);
#endif

const QStringList Import::_noms_types_fr_=Import::init_types();

/**noms des statistiques*/
#ifdef QT_NO_DEBUG
const QStringList Import::_noms_statistiques_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_statistiques").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_statistiques_=Utilitaire::lire_fichier("fichiers_ressources/traduction_statistiques.txt").split("\n",QString::SkipEmptyParts);
#endif

/**noms des statistiques*/
#ifdef QT_NO_DEBUG
const QStringList Import::_types_courbes_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_types_courbes").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_types_courbes_=Utilitaire::lire_fichier("fichiers_ressources/traduction_types_courbes.txt").split("\n",QString::SkipEmptyParts);
#endif

/**noms des statistiques*/
#ifdef QT_NO_DEBUG
const QStringList Import::_groupes_oeufs_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_groupes_oeuf").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_groupes_oeufs_=Utilitaire::lire_fichier("fichiers_ressources/traduction_groupes_oeuf.txt").split("\n",QString::SkipEmptyParts);
#endif

/**noms des climats*/
#ifdef QT_NO_DEBUG
const QStringList Import::_noms_climats_=Utilitaire::lire_fichier(":/fichiers_ressources/climats").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_climats_=Utilitaire::lire_fichier("fichiers_ressources/climats.txt").split("\n",QString::SkipEmptyParts);
#endif

/**noms des statuts*/
#ifdef QT_NO_DEBUG
const QStringList Import::_noms_statuts_=Utilitaire::lire_fichier(":/fichiers_ressources/statuts").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_statuts_=Utilitaire::lire_fichier("fichiers_ressources/statuts.txt").split("\n",QString::SkipEmptyParts);
#endif

/**noms des capacites*/
#ifdef QT_NO_DEBUG
const QStringList Import::_noms_capacites_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_capacites_pk").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_capacites_=Utilitaire::lire_fichier("fichiers_ressources/traduction_capacites_pk.txt").split("\n",QString::SkipEmptyParts);
#endif

/**noms des attaques*/
#ifdef QT_NO_DEBUG
const QStringList Import::_noms_attaques_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_attaques_pk").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_attaques_=Utilitaire::lire_fichier("fichiers_ressources/traduction_attaques_pk.txt").split("\n",QString::SkipEmptyParts);
#endif

/**langues*/
#ifdef QT_NO_DEBUG
const QStringList Import::_noms_pseudo_statuts_=Utilitaire::lire_fichier(":/fichiers_ressources/pseudo_statuts").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_pseudo_statuts_=Utilitaire::lire_fichier("fichiers_ressources/pseudo_statuts.txt").split("\n",QString::SkipEmptyParts);
#endif

/**langues*/
#ifdef QT_NO_DEBUG
const QStringList Import::_noms_categories_=Utilitaire::lire_fichier(":/fichiers_ressources/categories").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_categories_=Utilitaire::lire_fichier("fichiers_ressources/categories.txt").split("\n",QString::SkipEmptyParts);
#endif

/**langues*/
#ifdef QT_NO_DEBUG
const QStringList Import::_noms_pierres_evo_=Utilitaire::lire_fichier(":/fichiers_ressources/traductions_pierres_evo").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_pierres_evo_=Utilitaire::lire_fichier("fichiers_ressources/traductions_pierres_evo.txt").split("\n",QString::SkipEmptyParts);
#endif

/**langues*/
#ifdef QT_NO_DEBUG
const QStringList Import::_noms_objets_evo_=Utilitaire::lire_fichier(":/fichiers_ressources/traductions_objets_evo").split("\n",QString::SkipEmptyParts);
#else
const QStringList Import::_noms_objets_evo_=Utilitaire::lire_fichier("fichiers_ressources/traductions_objets_evo.txt").split("\n",QString::SkipEmptyParts);
#endif

const QStringList Import::_noms_objets_=Import::init_noms_objets();

/**langues: francais et anglais*/
const HashMap<QString,QStringList> Import::_langues_=Import::init_langues();

const QStringList Import::_type_lieux_=Import::init_type_lieux();

/**langues*/
#ifdef QT_NO_DEBUG
const int Import::_indice_francais_=Import::_langues_.cles().indexOf("FRANCAIS");
#else
const int Import::_indice_francais_=Import::_langues_.cles().indexOf("FRANCAIS");
#endif

const HashMap<QString,FichePokemon*> Import::_pokedex_=Import::init_pokedex();

const QStringList Import::_bases_evos_=Import::init_bases_evos();

const HashMap<int,QImage> Import::_miniatures_=Import::init_miniatures();

const Taux Import::_rapport_max_masse_=Import::init_rapport_masse_max();

const HashMap<QString,FicheAttaque*> Import::_attaques_=Import::init_attaques();

const HashMap<QString,FicheCapacite*> Import::_capacites_=Import::init_capacites();

const HashMap<QString,int> Import::_prix_objets_evo_=Import::init_prix_pierres_objets_evo();

const HashMap<QString,Objet*> Import::_objets_=Import::init_objets();

const HashMap<QString,QImage> Import::_images_objets_=Import::init_images_objets();

const HashMap<QPair<QString,QString>,Taux> Import::_table_types_base_=Import::init_table_types_base();

const HashMap<uchar,QString> Import::_ct_=Import::init_ct();

const HashMap<uchar,QString> Import::_cs_=Import::init_cs();

QString Import::constante(const QString& cle){
	return Utilitaire::constante(Import::_constantes_,cle);
}

Taux Import::constante_numerique(const QString& cle){
	return Taux::parse_taux(constante(cle));
}

QString Import::constante_non_numerique(const QString& cle,int langue){
	return Utilitaire::traduire_bis(Import::_constantes_non_num_,cle,langue);
}


QStringList Import::init_noms_objets(){
	QStringList noms_objets_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/fichiers_ressources");
	QStringList noms_fichiers_=dossier_.entryList(QDir::Files).filter(QRegExp("^traductions_"));
#else
	QDir dossier_("fichiers_ressources");
	QStringList noms_fichiers_=dossier_.entryList(QDir::Files).filter(QRegExp("^traductions_"));
#endif
	foreach(QString f,noms_fichiers_){
		noms_objets_<<Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
	}
	return noms_objets_;
}

HashMap<QString,QStringList> Import::init_langues(){
	HashMap<QString,QStringList> langues_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/langues").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/langues.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		langues_.ajouter_cle_valeur(l.split("\t")[0],QStringList(l.split("\t")));
	}
	return langues_;
}

QStringList Import::init_type_lieux(){
	QStringList type_lieux_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/type_lieux").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/type_lieux.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		type_lieux_<<l;
	}
	return type_lieux_;
}

HashMap<QString,QStringList> Import::init_noms_menus(){
	HashMap<QString,QStringList> descr_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/ihm/noms_menus").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/ihm/noms_menus.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		if(l.startsWith("\t")){
			descr_.ajouter_cle_valeur("\t"+l.split("\t")[1],QStringList(l.split("\t").mid(2)));
		}else{
			descr_.ajouter_cle_valeur(l.split("\t")[0],QStringList(l.split("\t").mid(1)));
		}
	}
	return descr_;
}

QStringList Import::init_dossiers_tuiles(){
#ifdef QT_NO_DEBUG
	//lecture d'un fichier de ressources
	QStringList dossiers_=Utilitaire::lire_fichier(":/fichiers_ressources/dossiers_tuiles").split("\n",QString::SkipEmptyParts);
#else
	//parcours par iteration de rang dans l'arborescence
	QStringList dossiers_=Utilitaire::lire_fichier("fichiers_ressources/dossiers_tuiles_d.txt").split("\n",QString::SkipEmptyParts);
#endif
	return dossiers_;
}

QStringList Import::init_dossiers_dresseurs_macro(){
#ifdef QT_NO_DEBUG
	//lecture d'un fichier de ressources
	QStringList dossiers_=Utilitaire::lire_fichier(":/fichiers_ressources/dossiers_images_macro_d").split("\n",QString::SkipEmptyParts);
#else
	//parcours par iteration de rang dans l'arborescence
	QStringList dossiers_=Utilitaire::lire_fichier("fichiers_ressources/dossiers_images_macro_d_d.txt").split("\n",QString::SkipEmptyParts);
#endif
	return dossiers_;
}

QStringList Import::init_dossiers_dresseurs_micro(){
#ifdef QT_NO_DEBUG
	//lecture d'un fichier de ressources
	QStringList dossiers_=Utilitaire::lire_fichier(":/fichiers_ressources/dossiers_images_micro_d").split("\n",QString::SkipEmptyParts);
#else
	//parcours par iteration de rang dans l'arborescence
	QStringList dossiers_=Utilitaire::lire_fichier("fichiers_ressources/dossiers_images_micro_d_d.txt").split("\n",QString::SkipEmptyParts);
#endif
	return dossiers_;
}

HashMap<QString,QImage> Import::init_elements_map(){
	HashMap<QString,QImage> elements_map_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/map");
	QStringList noms_images_=dossier_.entryList(QDir::Files);
	noms_images_.removeOne("map_invalide");
#else
	QDir dossier_("fichiers_ressources/ihm/map");
	QStringList noms_images_=dossier_.entryList(QDir::Files);
	noms_images_.removeOne("map_invalide.png");
#endif
	foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
		elements_map_.ajouter_cle_valeur("map/"+f,QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			elements_map_.ajouter_cle_valeur("map/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
		}
#endif
	}
	return elements_map_;
}

HashMap<QString,QImage> Import::init_liens(){
	HashMap<QString,QImage> liens_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/liens");
	QStringList noms_images_=dossier_.entryList(QDir::Files);
	noms_images_.removeOne("VIDE");
#else
	QDir dossier_("fichiers_ressources/ihm/liens");
	QStringList noms_images_=dossier_.entryList(QDir::Files);
	noms_images_.removeOne("VIDE.png");
#endif
	foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
		liens_.ajouter_cle_valeur("liens/"+f,QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			liens_.ajouter_cle_valeur("liens/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
		}
#endif
	}
#ifdef QT_NO_DEBUG
	liens_.ajouter_cle_valeur("",QImage(dossier_.path()+"/VIDE"));
#else
	liens_.ajouter_cle_valeur("",QImage(dossier_.path()+"/VIDE.png"));
#endif
	return liens_;
}

HashMap<QString,QImage> Import::init_tuiles_importees(){
	HashMap<QString,QImage> tuiles_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/ihm");
	QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("^[A-Z]+$"));
	noms_images_.removeOne("VIDE");
#else
	QDir dossier_("fichiers_ressources/ihm");
	QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("^[A-Z]+\\.png$"));
	noms_images_.removeOne("VIDE.png");
#endif
	foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
		tuiles_.ajouter_cle_valeur("ihm/"+f,QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			tuiles_.ajouter_cle_valeur("ihm/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
		}
#endif
	}
	foreach(QString d,_dossiers_tuiles_){
#ifdef QT_NO_DEBUG
		QDir dossier_(":/"+d);
		QStringList noms_images_=dossier_.entryList(QDir::Files);
#else
		QDir dossier_(d);
		QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("\\.png$"));
#endif
		foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
			tuiles_.ajouter_cle_valeur(d+"/"+f,QImage(dossier_.path()+"/"+f));
#else
			if(f!="."&&f!=".."){
				tuiles_.ajouter_cle_valeur(d.split("/").last()+"/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
			}
#endif
		}
	}
	return tuiles_;
}

HashMap<QString,QImage> Import::init_dresseurs_micros(){
	HashMap<QString,QImage> tuiles_;
	foreach(QString d,_dossiers_dresseurs_micro_){
#ifdef QT_NO_DEBUG
		QDir dossier_(":/"+d);
		QStringList noms_images_=dossier_.entryList(QDir::Files);
#else
		QDir dossier_(d);
		QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("\\.png$"));
#endif
		foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
			tuiles_.ajouter_cle_valeur(d+"/"+f,QImage(dossier_.path()+"/"+f));
#else
			if(f!="."&&f!=".."){
				tuiles_.ajouter_cle_valeur(d.split("/").last()+"/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
			}
#endif
		}
	}
	return tuiles_;
}

HashMap<QString,QImage> Import::init_dresseurs_macros(){
	HashMap<QString,QImage> tuiles_;
	foreach(QString d,_dossiers_dresseurs_macro_){
#ifdef QT_NO_DEBUG
		QDir dossier_(":/"+d);
		QStringList noms_images_=dossier_.entryList(QDir::Files);
#else
		QDir dossier_(d);
		QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("\\.png$"));
#endif
		foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
			tuiles_.ajouter_cle_valeur(d+"/"+f,QImage(dossier_.path()+"/"+f));
#else
			if(f!="."&&f!=".."){
				tuiles_.ajouter_cle_valeur(d.split("/").last()+"/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
			}
#endif
		}
	}
	return tuiles_;
}

HashMap<QString,QImage> Import::init_obstacles(TypeObstacle obstacle){
	HashMap<QString,QImage> tuiles_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/obstacles_interaction");
	if(obstacle==ARBRE){
		tuiles_.ajouter_cle_valeur("arbre_coupe",QImage(dossier_.path()+"/arbre_coupe"));
	}else if(obstacle==ROCHER_DEST){
		tuiles_.ajouter_cle_valeur("rocher_destr",QImage(dossier_.path()+"/rocher_destr"));
	}else if(obstacle==ROCHER_AMOV){
		tuiles_.ajouter_cle_valeur("rocher_amov",QImage(dossier_.path()+"/rocher_amov"));
	}else if(obstacle==TOURBILLON){
		tuiles_.ajouter_cle_valeur("tourbillon",QImage(dossier_.path()+"/tourbillon"));
	}
#else
	QDir dossier_("fichiers_ressources/ihm/obstacles_interaction");
	if(obstacle==ARBRE){
		tuiles_.ajouter_cle_valeur("arbre_coupe",QImage(dossier_.path()+"/arbre_coupe.png"));
	}else if(obstacle==ROCHER_DEST){
		tuiles_.ajouter_cle_valeur("rocher_destr",QImage(dossier_.path()+"/rocher_destr.png"));
	}else if(obstacle==ROCHER_AMOV){
		tuiles_.ajouter_cle_valeur("rocher_amov",QImage(dossier_.path()+"/rocher_amov.png"));
	}else if(obstacle==TOURBILLON){
		tuiles_.ajouter_cle_valeur("tourbillon",QImage(dossier_.path()+"/tourbillon.png"));
	}
#endif
	return tuiles_;
}

HashMap<QString,QStringList> Import::init_descriptions_complements(){
	HashMap<QString,QStringList> descr_;
#ifdef QT_NO_DEBUG
	QStringList noms_descriptions_attaques_=QDir(":/description_complement_attaques").entryList(QDir::Files);
#else
	QStringList noms_descriptions_attaques_=QDir("fichiers_ressources/description_complement_attaques").entryList(QDir::Files);
#endif
	foreach(QString f,noms_descriptions_attaques_){
#ifdef QT_NO_DEBUG
		QString contenu_=Utilitaire::lire_fichier(":/description_complement_attaques/"+f);
		QStringList lignes_=contenu_.split("\n",QString::SkipEmptyParts);
		QStringList descriptions_objets_;
		int nb_langues_=1;//Import::_langues_.total();
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
		descr_.ajouter_cle_valeur(f,descriptions_objets_);
#else
		if(f!="."&&f!=".."){
			QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_complement_attaques/"+f);
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
			descr_.ajouter_cle_valeur(f.split(".")[0],descriptions_objets_);
		}
#endif
	}
	return descr_;
}

HashMap<QString,QImage> Import::init_images_env_def(){
	HashMap<QString,QImage> images_env_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/ihm");
	QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("^[A-Z]+$"));
	noms_images_.removeOne("VIDE");
#else
	QDir dossier_("fichiers_ressources/ihm");
	QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("^[A-Z]+\\.png$"));
	noms_images_.removeOne("VIDE.png");
#endif
	foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
		images_env_.ajouter_cle_valeur(f,QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			images_env_.ajouter_cle_valeur(f.split(".")[0],QImage(dossier_.path()+"/"+f));
		}
#endif
	}
#ifdef QT_NO_DEBUG
	images_env_.ajouter_cle_valeur("",QImage(dossier_.path()+"/VIDE"));
#else
	images_env_.ajouter_cle_valeur("",QImage(dossier_.path()+"/VIDE.png"));
#endif
	return images_env_;
}

HashMap<QString,FichePokemon*> Import::init_pokedex(){
	HashMap<QString,FichePokemon*> pokedex_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/pokedex");
#else
	QDir dossier_("fichiers_ressources/pokedex");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		pokedex_.ajouter_cle_valeur(f,new FichePokemon(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")));
#else
		if(f!="."&&f!=".."){
			pokedex_.ajouter_cle_valeur(f.split(".")[0],new FichePokemon(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")));
		}
#endif
	}
	return pokedex_;
}

QStringList Import::init_bases_evos(){
	QStringList bases_evos_;
	foreach(QString f,_pokedex_.cles()){
		bases_evos_<<_pokedex_.valeur(f)->b_ev();
	}
	bases_evos_.removeDuplicates();
	bases_evos_.sort();
	return bases_evos_;
}

HashMap<int,QImage> Import::init_miniatures(){
	HashMap<int,QImage> miniatures_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/miniat");
#else
	QDir dossier_("fichiers_ressources/ihm/miniat");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		miniatures_.ajouter_cle_valeur(f.toInt(),QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			miniatures_.ajouter_cle_valeur(f.split(".")[0].toInt(),QImage(dossier_.path()+"/"+f));
		}
#endif
	}
	return miniatures_;
}



QStringList Import::init_types(){
	QStringList types_;
	foreach(QString t,Import::_noms_types_){
		types_<<t.split("\t")[Import::_indice_francais_];
	}
	return types_;
}

Taux Import::init_rapport_masse_max(){
	Taux t_som_=Taux(0);
	Taux t_max_=Taux(0);
	foreach(QString f,_pokedex_.cles()){
		FichePokemon *f_pk_=_pokedex_.valeur(f);
		Taux m_pk_=f_pk_->m_pk();
		t_som_=t_som_+m_pk_;
		if(t_max_<m_pk_){
			t_max_=m_pk_;
		}
	}
	return t_max_*Taux(_pokedex_.cles().size())/t_som_;
}

HashMap<QString,FicheAttaque*> Import::init_attaques(){
	HashMap<QString,FicheAttaque*> attaques_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/fiches_attaques");
#else
	QDir dossier_("fichiers_ressources/fiches_attaques");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		attaques_.ajouter_cle_valeur(f,new FicheAttaque(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")));
#else
		if(f!="."&&f!=".."){
			attaques_.ajouter_cle_valeur(f.split(".")[0],new FicheAttaque(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")));
		}
#endif
	}
	return attaques_;
}

	/**coeff_attaques_touch_pseudoinvuln*/
HashMap<QPair<QString,QString>,Taux> Import::init_attaques_touchant_pseudo_invuln(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/coeff_attaques_touch_pseudoinvuln").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/coeff_attaques_touch_pseudoinvuln.txt").split("\n",QString::SkipEmptyParts);
#endif
	HashMap<QPair<QString,QString>,Taux> attaques_touchant_pseudo_invuln;
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		QStringList infos_att_=infos_[0].split(",");
		attaques_touchant_pseudo_invuln.ajouter_cle_valeur(QPair<QString,QString>(infos_att_[0],infos_att_[1]),Taux::parse_taux(infos_[1]));
	}
	return attaques_touchant_pseudo_invuln;
}

HashMap<QString,Taux> Import::init_attaques_lilliput(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/attaques_lilliput").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/attaques_lilliput.txt").split("\n",QString::SkipEmptyParts);
#endif
	HashMap<QString,Taux> attaques_lilliput;
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		attaques_lilliput.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
	}
	return attaques_lilliput	;
}

HashMap<QString,Taux> Import::init_puissance_degommage(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/puissance_degommage").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/puissance_degommage.txt").split("\n",QString::SkipEmptyParts);
#endif
	HashMap<QString,Taux> puissance_degommage;
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		puissance_degommage.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
	}
	return puissance_degommage	;
}

HashMap<QString,FicheCapacite*> Import::init_capacites(){
	HashMap<QString,FicheCapacite*> capacites_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/fiches_capacites");
#else
	QDir dossier_("fichiers_ressources/fiches_capacites");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		capacites_.ajouter_cle_valeur(f,new FicheCapacite(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")));
#else
		if(f!="."&&f!=".."){
			capacites_.ajouter_cle_valeur(f.split(".")[0],new FicheCapacite(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")));
		}
#endif
	}
	return capacites_;
}

HashMap<QString,int> Import::init_prix_pierres_objets_evo(){
	HashMap<QString,int> prix_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fiches_objets/prix_pierres").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/fiches_objets/prix_pierres.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		QStringList infos_l_=l.split("\t");
		prix_.ajouter_cle_valeur(infos_l_[0],infos_l_[1].toInt());
	}
	return prix_;
}

HashMap<QString,Objet*> Import::init_objets(){
	//TODO ajouter les prix d'achat
	HashMap<QString,Objet*> objets_;
#ifdef QT_NO_DEBUG
	QDir dossier_(":/baies");
#else
	QDir dossier_("fichiers_ressources/fiches_objets/baies");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
		QString don_nat_=infos_.takeLast();
		int prix_=infos_.takeLast().toInt();
		QStringList infos_don_nat_=don_nat_.split(QRegExp("(\\W)+"));
		QString type_don_nat_=infos_don_nat_[1];
		QString puis_don_nat_=infos_don_nat_[2];
		objets_.ajouter_cle_valeur(f,new Baie(infos_,QPair<QString,uchar>(type_don_nat_,(uchar)puis_don_nat_.toUInt()),prix_));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			QString don_nat_=infos_.takeLast();
			int prix_=infos_.takeLast().toInt();
			QStringList infos_don_nat_=don_nat_.split(QRegExp("(\\W)+"));
			QString type_don_nat_=infos_don_nat_[1];
			QString puis_don_nat_=infos_don_nat_[2];
			objets_.ajouter_cle_valeur(f.split(".")[0],new Baie(infos_,QPair<QString,uchar>(type_don_nat_,(uchar)puis_don_nat_.toUInt()),prix_));
		}
#endif
	}
#ifdef QT_NO_DEBUG
	dossier_=QDir(":/balls");
#else
	dossier_=QDir("fichiers_ressources/fiches_objets/balls");
#endif
	fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
		if(infos_[0]!="--"){
			int prix_=infos_.takeAt(0).toInt();
			objets_.ajouter_cle_valeur(f,new Ball(infos_,prix_));
		}else{
			infos_.removeAt(0);
			objets_.ajouter_cle_valeur(f,new Ball(infos_));
		}
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
			if(infos_[0]!="--"){
				int prix_=infos_.takeAt(0).toInt();
				objets_.ajouter_cle_valeur(f.split(".")[0],new Ball(infos_,prix_));
			}else{
				infos_.removeAt(0);
				objets_.ajouter_cle_valeur(f.split(".")[0],new Ball(infos_));
			}
		}
#endif
	}
#ifdef QT_NO_DEBUG
	dossier_=QDir(":/fossiles");
#else
	dossier_=QDir("fichiers_ressources/fiches_objets/fossiles");
#endif
	fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
		int prix_=infos_.takeLast().toInt();
		uchar niveau_=(uchar)infos_.takeLast().toUInt();
		QString nom_pk_=infos_.takeLast();
		objets_.ajouter_cle_valeur(f,new Fossile(nom_pk_,niveau_,prix_));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			int prix_=infos_.takeLast().toInt();
			uchar niveau_=(uchar)infos_.takeLast().toUInt();
			QString nom_pk_=infos_.takeLast();
			objets_.ajouter_cle_valeur(f.split(".")[0],new Fossile(nom_pk_,niveau_,prix_));
		}
#endif
	}
#ifdef QT_NO_DEBUG
	dossier_=QDir(":/objet_attacher_2");
#else
	dossier_=QDir("fichiers_ressources/fiches_objets/objet_attacher_2");
#endif
	fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
		int prix_=infos_.takeLast().toInt();
		objets_.ajouter_cle_valeur(f,new ObjetAttachableCombat(infos_,prix_));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			int prix_=infos_.takeLast().toInt();
			objets_.ajouter_cle_valeur(f.split(".")[0],new ObjetAttachableCombat(infos_,prix_));
		}
#endif
	}
	QList<QString> noms_pk_=_pokedex_.cles();
	HashMap<QString,QStringList> hash_objets_pk_;
	bool suppr_=false;
	foreach(QString n,noms_pk_){
		FichePokemon *fiche_poke_=_pokedex_.valeur(n);
		QStringList evolutions_=fiche_poke_->pokemons_evolues();
		foreach(QString e,evolutions_){
			EvolutionObjet *evo_obj_=qobject_cast<EvolutionObjet*>(fiche_poke_->facon_evoluer(e));
			if(evo_obj_){
				//Si l'évolution se fait par le port d'un objet permettant l'évolution en montant de niveau
				QList<QString> noms_objets_=hash_objets_pk_.cles();
				QString nom_objet_=evo_obj_->nom_objet();
				if(noms_objets_.contains(nom_objet_)){
					QStringList *ls_pk_=hash_objets_pk_.valeur(nom_objet_,suppr_);
					if(!ls_pk_->contains(n)){
						ls_pk_->append(n);
					}
				}else{
					hash_objets_pk_.ajouter_cle_valeur(nom_objet_,QStringList(n));
				}
			}
		}
	}
	QList<QString> noms_objets_=hash_objets_pk_.cles();
	foreach(QString n,noms_objets_){
		int prix_=_prix_objets_evo_.valeur(n);
		objets_.ajouter_cle_valeur(n,new ObjetEvo(hash_objets_pk_.valeur(n),prix_));
	}
	HashMap<QString,QStringList> hash_pierres_pk_;
	foreach(QString n,noms_pk_){
		FichePokemon *fiche_poke_=_pokedex_.valeur(n);
		QStringList evolutions_=fiche_poke_->pokemons_evolues();
		foreach(QString e,evolutions_){
			EvolutionPierreEvolutive *evo_obj_=qobject_cast<EvolutionPierreEvolutive*>(fiche_poke_->facon_evoluer(e));
			if(evo_obj_){
				//Si l'évolution se fait par le port d'un objet permettant l'évolution en montant de niveau
				QList<QString> noms_objets_=hash_pierres_pk_.cles();
				QString nom_objet_=evo_obj_->nom_pierre();
				if(noms_objets_.contains(nom_objet_)){
					QStringList *ls_pk_=hash_pierres_pk_.valeur(nom_objet_,suppr_);
					if(!ls_pk_->contains(n)){
						ls_pk_->append(n);
					}
				}else{
					hash_pierres_pk_.ajouter_cle_valeur(nom_objet_,QStringList(n));
				}
			}
		}
	}
	noms_objets_=hash_pierres_pk_.cles();
	foreach(QString n,noms_objets_){
		int prix_=_prix_objets_evo_.valeur(n);
		objets_.ajouter_cle_valeur(n,new PierreEvo(hash_pierres_pk_.valeur(n),prix_));
	}
	//noms_pk_objets_.removeDuplicates()
	/*
	TODO utiliser les pokédex pour la compatibilité pour les pierres évo et les objets à attacher
	dossier_=QDir(":/objet_attacher_evo")
	fiches_=dossier_.entryList()
	foreach(QString f,fiches_){
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")
		objets_.ajouter_cle_valeur(f,new ObjetEvo(infos_))
	}*/
#ifdef QT_NO_DEBUG
	dossier_=QDir(":/objet_boost_statistiques");
#else
	dossier_=QDir("fichiers_ressources/fiches_objets/objet_boost_statistiques");
#endif
	fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
		int prix_=infos_.takeLast().toInt();
		QString effet_p_=infos_.takeAt(0);
		objets_.ajouter_cle_valeur(f,new Boost(infos_,effet_p_,prix_));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			int prix_=infos_.takeLast().toInt();
			QString effet_p_=infos_.takeAt(0);
			objets_.ajouter_cle_valeur(f.split(".")[0],new Boost(infos_,effet_p_,prix_));
		}
#endif
	}
#ifdef QT_NO_DEBUG
	dossier_=QDir(":/objets_reventes");
#else
	dossier_=QDir("fichiers_ressources/fiches_objets/objets_reventes");
#endif
	fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
		QRegExp exp_prix_("[0-9]+");
		infos_[0].indexOf(exp_prix_);
		objets_.ajouter_cle_valeur(f,new Revente(exp_prix_.capturedTexts()[0].toInt()));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
			QRegExp exp_prix_("[0-9]+");
			infos_[0].indexOf(exp_prix_);
			objets_.ajouter_cle_valeur(f.split(".")[0],new Revente(exp_prix_.capturedTexts()[0].toInt()));
		}
#endif
	}
#ifdef QT_NO_DEBUG
	dossier_=QDir(":/repousse");
#else
	dossier_=QDir("fichiers_ressources/fiches_objets/repousse");
#endif
	fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
		QRegExp exp_pas_("[0-9]+");
		infos_[0].indexOf(exp_pas_);
		QRegExp exp_prix_("[0-9]+");
		infos_[1].indexOf(exp_prix_);
		objets_.ajouter_cle_valeur(f,new Repousse(exp_pas_.capturedTexts()[0].toUInt(),exp_prix_.capturedTexts()[0].toInt()));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
			QRegExp exp_pas_("[0-9]+");
			infos_[0].indexOf(exp_pas_);
			QRegExp exp_prix_("[0-9]+");
			infos_[1].indexOf(exp_prix_);
			objets_.ajouter_cle_valeur(f.split(".")[0],new Repousse(exp_pas_.capturedTexts()[0].toUInt(),exp_prix_.capturedTexts()[0].toInt()));
		}
#endif
	}
#ifdef QT_NO_DEBUG
	dossier_=QDir(":/modules");
#else
	dossier_=QDir("fichiers_ressources/fiches_objets/modules");
#endif
	fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
		QRegExp exp_prix_("[0-9]+");
		infos_[1].indexOf(exp_prix_);
		objets_.ajouter_cle_valeur(f,new Module(infos_[0],exp_prix_.capturedTexts()[0].toInt()));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
			QRegExp exp_prix_("[0-9]+");
			infos_[1].indexOf(exp_prix_);
			objets_.ajouter_cle_valeur(f.split(".")[0],new Module(infos_[0],exp_prix_.capturedTexts()[0].toInt()));
		}
#endif
	}
#ifdef QT_NO_DEBUG
	dossier_=QDir(":/objets_soins");
#else
	dossier_=QDir("fichiers_ressources/fiches_objets/objets_soins");
#endif
	fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
		int prix_=infos_.takeLast().toInt();
		if(!infos_.filter(QRegExp("^SOIN_PV\\[")).isEmpty()){
			if(!infos_.filter(QRegExp("^SOIN_(STATUT\\[|KO)")).isEmpty()){
				//SOIN_STATUT
				QStringList statuts_=infos_.filter(QRegExp("^SOIN_STATUT\\["));
				QStringList statuts_2_;
				foreach(QString s,statuts_){
					statuts_2_<<s.split(QRegExp("(\\W)+"))[1];
				}
				QStringList pvs_=infos_.filter(QRegExp("^SOIN_PV\\["));
				QRegExp exp_taux_("MAX(/[0-9]+)?");
				pvs_[0].indexOf(exp_taux_);
				Taux tx_=Taux::parse_taux(exp_taux_.capturedTexts()[0].replace("MAX","1"));
				objets_.ajouter_cle_valeur(f,new SoinPVStatut(infos_,statuts_2_,tx_,prix_));
			}else{
				QStringList pvs_=infos_.filter(QRegExp("^SOIN_PV\\["));
				if(!pvs_[0].contains("MAX")){
					QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
					pvs_[0].indexOf(exp_taux_);
					Taux tx_=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
					objets_.ajouter_cle_valeur(f,new SoinPV(infos_,tx_,prix_));
				}else{
					objets_.ajouter_cle_valeur(f,new SoinPV(infos_,Taux(0),prix_));
				}
			}
		}else{
			if(!infos_.filter(QRegExp("^SOIN_STATUT\\[")).isEmpty()){
				//SOIN_STATUT
				QStringList statuts_=infos_.filter(QRegExp("^SOIN_STATUT\\["));
				QStringList statuts_2_;
				foreach(QString s,statuts_){
					statuts_2_<<s.split(QRegExp("(\\W)+"))[1];
				}
				objets_.ajouter_cle_valeur(f,new SoinStatut(infos_,statuts_2_,prix_));
			}else if(!infos_.filter(QRegExp("^SOIN_PP\\[")).isEmpty()){
				QStringList infos_pp_=infos_.filter(QRegExp("^SOIN_PP\\["))[0].split(QRegExp("(\\W)+"));
				objets_.ajouter_cle_valeur(f,new SoinPP(infos_,QPair<QString,QString>(infos_pp_[1],infos_pp_[2]),prix_));
			}else{//if(!infos_.filter(QRegExp("^SOIN_EQUIPE")).isEmpty())
				objets_.ajouter_cle_valeur(f,new Soin(infos_,prix_));
			}
		}
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			int prix_=infos_.takeLast().toInt();
			if(!infos_.filter(QRegExp("^SOIN_PV\\[")).isEmpty()){
				if(!infos_.filter(QRegExp("^SOIN_((STATUT)|(KO))\\[")).isEmpty()){
					//SOIN_STATUT
					QStringList statuts_=infos_.filter(QRegExp("^SOIN_STATUT\\["));
					QStringList statuts_2_;
					foreach(QString s,statuts_){
						statuts_2_<<s.split(QRegExp("(\\W)+"))[1];
					}
					QStringList pvs_=infos_.filter(QRegExp("^SOIN_PV\\["));
					QRegExp exp_taux_("MAX(/[0-9]+)?");
					pvs_[0].indexOf(exp_taux_);
					Taux tx_=Taux::parse_taux(exp_taux_.capturedTexts()[0].replace("MAX","1"));
					objets_.ajouter_cle_valeur(f.split(".")[0],new SoinPVStatut(infos_,statuts_2_,tx_,prix_));
				}else{
					QStringList pvs_=infos_.filter(QRegExp("^SOIN_PV\\["));
					if(!pvs_[0].contains("MAX")){
						QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
						pvs_[0].indexOf(exp_taux_);
						Taux tx_=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
						objets_.ajouter_cle_valeur(f.split(".")[0],new SoinPV(infos_,tx_,prix_));
					}else{
						objets_.ajouter_cle_valeur(f.split(".")[0],new SoinPV(infos_,Taux(0),prix_));
					}
				}
			}else{
				if(!infos_.filter(QRegExp("^SOIN_STATUT\\[")).isEmpty()){
					//SOIN_STATUT
					QStringList statuts_=infos_.filter(QRegExp("^SOIN_STATUT\\["));
					QStringList statuts_2_;
					foreach(QString s,statuts_){
						statuts_2_<<s.split(QRegExp("(\\W)+"))[1];
					}
					objets_.ajouter_cle_valeur(f.split(".")[0],new SoinStatut(infos_,statuts_2_,prix_));
				}else if(!infos_.filter(QRegExp("^SOIN_PP\\[")).isEmpty()){
					QStringList infos_pp_=infos_.filter(QRegExp("^SOIN_PP\\["))[0].split(QRegExp("(\\W)+"));
					objets_.ajouter_cle_valeur(f.split(".")[0],new SoinPP(infos_,QPair<QString,QString>(infos_pp_[1],infos_pp_[2]),prix_));
				}else{//if(!infos_.filter(QRegExp("^SOIN_EQUIPE")).isEmpty())
					objets_.ajouter_cle_valeur(f.split(".")[0],new Soin(infos_,prix_));
				}
			}
		}
#endif
		//objets_.ajouter_cle_valeur(f,new Soin(infos_,prix_))
	}
#ifdef QT_NO_DEBUG
	dossier_=QDir(":/plaques");
#else
	dossier_=QDir("fichiers_ressources/fiches_objets/plaques");
#endif
	fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
		int prix_=infos_.takeLast().toInt();
		QString type_pk_=infos_.takeAt(0);
		QRegExp exp_coeff_("[0-9]+(/[0-9]+)?");
		infos_[0].indexOf(exp_coeff_);
		Taux coeff_=Taux::parse_taux(exp_coeff_.capturedTexts()[0]);
		QString type_plaque_=infos_[0].split(QRegExp("(\\W)+"))[2];
		objets_.ajouter_cle_valeur(f,new Plaque(type_plaque_,type_pk_,coeff_,prix_));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			int prix_=infos_.takeLast().toInt();
			QString type_pk_=infos_.takeAt(0);
			QRegExp exp_coeff_("[0-9]+(/[0-9]+)?");
			infos_[0].indexOf(exp_coeff_);
			Taux coeff_=Taux::parse_taux(exp_coeff_.capturedTexts()[0]);
			QString type_plaque_=infos_[0].split(QRegExp("(\\W)+"))[2];
			objets_.ajouter_cle_valeur(f.split(".")[0],new Plaque(type_plaque_,type_pk_,coeff_,prix_));
		}
#endif
	}
	return objets_;
}

HashMap<QString,QImage> Import::init_images_objets(){
	HashMap<QString,QImage> images_objets_;
	QStringList dossiers_;
	dossiers_<<"baies_i";
	dossiers_<<"balls_i";
	dossiers_<<"fossiles_i";
	dossiers_<<"objet_attacher_2_i";
	dossiers_<<"objet_attacher_evo_i";
	dossiers_<<"objet_boost_statistiques_i";
	dossiers_<<"objets_reventes_i";
	dossiers_<<"objets_soins_i";
	dossiers_<<"pierres_evo_i";
	dossiers_<<"plaques_i";
	dossiers_<<"repousse_i";
	dossiers_<<"modules_i";
	foreach(QString d,dossiers_){
#ifdef QT_NO_DEBUG
		QDir dossier_=QDir(":/"+d);
#else
		QDir dossier_=QDir("fichiers_ressources/img_obj/"+d);
#endif
		foreach(QString f,dossier_.entryList(QDir::Files)){
#ifdef QT_NO_DEBUG
			images_objets_.ajouter_cle_valeur(f,QImage(dossier_.path()+"/"+f));
#else
			if(f!="."&&f!=".."){
				images_objets_.ajouter_cle_valeur(f.split(".")[0],QImage(dossier_.path()+"/"+f));
			}
#endif		
		}
	}
	return images_objets_;
}

HashMap<QPair<QString,QString>,Taux> Import::init_table_types_base(){
	HashMap<QPair<QString,QString>,Taux> table_types_base_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/table_types").split("\n");
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/table_types.txt").split("\n");
#endif
	int i_=0;//indice du type defensif
	int j_=0;//indice du type offensif
	foreach(QString l,lignes_){//l est la ligne des coefficients d'efficacité sur le type défensif
		QStringList colonnes_=l.split("\t");
		j_=0;
		foreach(QString c,colonnes_){
			table_types_base_.ajouter_cle_valeur(QPair<QString,QString>(_noms_types_fr_[j_],_noms_types_fr_[i_]),Taux::parse_taux(c));
			j_++;
		}
		i_++;
	}
	return table_types_base_;
}

HashMap<uchar,QString> Import::init_ct(){
	HashMap<uchar,QString> ct_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fiches_objets/ct_cs_nb").split("\n").filter(QRegExp("^CT"));
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/fiches_objets/ct_cs_nb.txt").split("\n").filter(QRegExp("^CT"));
#endif
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		ct_.ajouter_cle_valeur((uchar)infos_[0].mid(2).toUInt(),infos_[1]);
	}
	return ct_;
}

HashMap<uchar,QString> Import::init_cs(){
	HashMap<uchar,QString> cs_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fiches_objets/ct_cs_nb").split("\n").filter(QRegExp("^CS"));
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/fiches_objets/ct_cs_nb.txt").split("\n").filter(QRegExp("^CS"));
#endif
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		cs_.ajouter_cle_valeur((uchar)infos_[0].mid(2).toUInt(),infos_[1]);
	}
	return cs_;
}

void Import::destructeur(){
	QList<QString> cles_=_pokedex_.cles();
	foreach(QString c,cles_){
		FichePokemon *fiche_pk=_pokedex_.valeur(c);
		delete fiche_pk;
		fiche_pk=NULL;
		//_pokedex_.supprimer_cle_valeur(c)
	}
	cles_=_attaques_.cles();
	foreach(QString c,cles_){
		FicheAttaque *fiche_att=_attaques_.valeur(c);
		delete fiche_att;
		fiche_att=NULL;
		//_attaques_.supprimer_cle_valeur(c)
	}
	cles_=_capacites_.cles();
	foreach(QString c,cles_){
		FicheCapacite *fiche_cap=_capacites_.valeur(c);
		delete fiche_cap;
		fiche_cap=NULL;
		//_capacites_.supprimer_cle_valeur(c)
	}
	cles_=_objets_.cles();
	foreach(QString c,cles_){
		Objet *fiche_cap=_objets_.valeur(c);
		delete fiche_cap;
		fiche_cap=NULL;
		//_objets_.supprimer_cle_valeur(c)
	}
}



