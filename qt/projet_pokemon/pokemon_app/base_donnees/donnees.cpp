#include "base_donnees/donnees.h"
#include "base_donnees/personnages/champion.h"
#include "autre/utilitaire.h"
#include "serialisable/partie/partie.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/attaques/ficheattaque.h"
#include "base_donnees/capacites/fichecapacite.h"
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
#include <QDir>
#include <iostream>

QString Donnees::constante(const QString& cle){
	return Utilitaire::constante(constantes,cle);
}

Taux Donnees::constante_numerique(const QString& cle){
	return Taux(constante(cle));
}

QString Donnees::constante_non_numerique(const QString& cle,int langue){
	return Utilitaire::traduire(constantes_non_num,cle,langue);
}

void Donnees::init_heros(){
#ifdef QT_NO_DEBUG
	QStringList fic_m_=QDir(":/heros").entryList().entryList().filter("_M");
	QStringList fic_d_=QDir(":/heros").entryList().entryList().filter("_D");
	QStringList fic_f_=QDir(":/heros").entryList().entryList().filter("_F");
	foreach(QString c,equivalents_genre.cles()){
		debut_heros.ajouter_cle_valeur(c,QImage(":/heros/"+c));
	}
	foreach(QString c,fic_m_){
		miniatures_heros.ajouter_cle_valeur(c.split("_")[0],QImage(":/heros/"+c));
	}
	foreach(QString c,fic_f_){
		face_heros.ajouter_cle_valeur(c.split("_")[0],QImage(":/heros/"+c));
	}
	foreach(QString c,fic_d_){
		dos_heros.ajouter_cle_valeur(c.split("_")[0],QImage(":/heros/"+c));
	}
#else
	QStringList fic_m_=QDir("fichiers_ressources/ihm/heros").entryList().filter("_M");
	QStringList fic_d_=QDir("fichiers_ressources/ihm/heros").entryList().filter("_D");
	QStringList fic_f_=QDir("fichiers_ressources/ihm/heros").entryList().filter("_F");
	foreach(QString c,equivalents_genre.cles()){
		debut_heros.ajouter_cle_valeur(c,QImage("fichiers_ressources/ihm/heros/"+c+".png"));
	}
	foreach(QString c,fic_m_){
		miniatures_heros.ajouter_cle_valeur(c.split("_")[0],QImage("fichiers_ressources/ihm/heros/"+c));
	}
	foreach(QString c,fic_f_){
		face_heros.ajouter_cle_valeur(c.split("_")[0],QImage("fichiers_ressources/ihm/heros/"+c));
	}
	foreach(QString c,fic_d_){
		dos_heros.ajouter_cle_valeur(c.split("_")[0],QImage("fichiers_ressources/ihm/heros/"+c));
	}
#endif
	//miniatures_heros
	//face_heros
	//dos_heros
}

void Donnees::init_equivalents_genre(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/equivalents_genre").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/equivalents_genre.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		equivalents_genre.ajouter_cle_valeur(infos_[0],infos_[1]);
	}
}

void Donnees::init_noms_objets(){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/fichiers_ressources");
	QStringList noms_fichiers_=dossier_.entryList(QDir::Files).filter(QRegExp("^traductions_"));
#else
	QDir dossier_("fichiers_ressources");
	QStringList noms_fichiers_=dossier_.entryList(QDir::Files).filter(QRegExp("^traductions_"));
#endif
	foreach(QString f,noms_fichiers_){
		noms_objets<<Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
	}
}

void Donnees::init_langues(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/langues").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/langues.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		langues.ajouter_cle_valeur(l.split("\t")[0],QStringList(l.split("\t")));
	}
}

void Donnees::init_type_lieux(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/type_lieux").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/type_lieux.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		type_lieux<<l;
	}
}

void Donnees::init_dossiers_tuiles(){
#ifdef QT_NO_DEBUG
	//lecture d'un fichier de ressources
	dossiers_tuiles=Utilitaire::lire_fichier(":/fichiers_ressources/dossiers_tuiles").split("\n",QString::SkipEmptyParts);
#else
	//parcours par iteration de rang dans l'arborescence
	dossiers_tuiles=Utilitaire::lire_fichier("fichiers_ressources/dossiers_tuiles_d.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_dossiers_dresseurs_macro(){
#ifdef QT_NO_DEBUG
	//lecture d'un fichier de ressources
	dossiers_dresseurs_macro=Utilitaire::lire_fichier(":/fichiers_ressources/dossiers_images_macro_d").split("\n",QString::SkipEmptyParts);
#else
	//parcours par iteration de rang dans l'arborescence
	dossiers_dresseurs_macro=Utilitaire::lire_fichier("fichiers_ressources/dossiers_images_macro_d_d.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_dossiers_dresseurs_micro(){
#ifdef QT_NO_DEBUG
	//lecture d'un fichier de ressources
	dossiers_dresseurs_micro=Utilitaire::lire_fichier(":/fichiers_ressources/dossiers_images_micro_d").split("\n",QString::SkipEmptyParts);
#else
	//parcours par iteration de rang dans l'arborescence
	dossiers_dresseurs_micro=Utilitaire::lire_fichier("fichiers_ressources/dossiers_images_micro_d_d.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_elements_map(){
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
		elements_map.ajouter_cle_valeur("map/"+f,QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			elements_map.ajouter_cle_valeur("map/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
		}
#endif
	}
}

void Donnees::init_liens(){
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
		liens.ajouter_cle_valeur("liens/"+f,QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			liens.ajouter_cle_valeur("liens/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
		}
#endif
	}
#ifdef QT_NO_DEBUG
	liens.ajouter_cle_valeur("",QImage(dossier_.path()+"/VIDE"));
#else
	liens.ajouter_cle_valeur("",QImage(dossier_.path()+"/VIDE.png"));
#endif
}

void Donnees::init_tuiles_importees(){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/ihm");
	QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("^[A-Z]+$"));
	//noms_images_.removeOne("VIDE");
#else
	QDir dossier_("fichiers_ressources/ihm");
	QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("^[A-Z]+\\.png$"));
	//noms_images_.removeOne("VIDE.png");
#endif
	foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
		tuiles_importees.ajouter_cle_valeur("ihm/"+f,QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			tuiles_importees.ajouter_cle_valeur("ihm/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
		}
#endif
	}
	foreach(QString d,dossiers_tuiles){
#ifdef QT_NO_DEBUG
		QDir dossier_(":/"+d);
		QStringList noms_images_=dossier_.entryList(QDir::Files);
#else
		QDir dossier_(d);
		QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("\\.png$"));
#endif
		foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
			tuiles_importees.ajouter_cle_valeur(d+"/"+f,QImage(dossier_.path()+"/"+f));
#else
			if(f!="."&&f!=".."){
				tuiles_importees.ajouter_cle_valeur(d.split("/").last()+"/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
			}
#endif
		}
	}
}

void Donnees::init_dresseurs_micros(){
	foreach(QString d,dossiers_dresseurs_micro){
#ifdef QT_NO_DEBUG
		QDir dossier_(":/"+d);
		QStringList noms_images_=dossier_.entryList(QDir::Files);
#else
		QDir dossier_(d);
		QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("\\.png$"));
#endif
		foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
			dresseurs_micros.ajouter_cle_valeur(d+"/"+f,QImage(dossier_.path()+"/"+f));
#else
			if(f!="."&&f!=".."){
				dresseurs_micros.ajouter_cle_valeur(d.split("/").last()+"/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
			}
#endif
		}
	}
}

void Donnees::init_dresseurs_macros(){
	foreach(QString d,dossiers_dresseurs_macro){
#ifdef QT_NO_DEBUG
		QDir dossier_(":/"+d);
		QStringList noms_images_=dossier_.entryList(QDir::Files);
#else
		QDir dossier_(d);
		QStringList noms_images_=dossier_.entryList(QDir::Files).filter(QRegExp("\\.png$"));
#endif
		foreach(QString f,noms_images_){
#ifdef QT_NO_DEBUG
			dresseurs_macros.ajouter_cle_valeur(d+"/"+f,QImage(dossier_.path()+"/"+f));
#else
			if(f!="."&&f!=".."){
				dresseurs_macros.ajouter_cle_valeur(d.split("/").last()+"/"+f.split(".")[0],QImage(dossier_.path()+"/"+f));
			}
#endif
		}
	}
}

void Donnees::init_obstacles(TypeObstacle obstacle){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/obstacles_interaction");
	if(obstacle==ARBRE){
		arbres.ajouter_cle_valeur("arbre_coupe",QImage(dossier_.path()+"/arbre_coupe"));
	}else if(obstacle==ROCHER_DEST){
		rochers_destructibles.ajouter_cle_valeur("rocher_destr",QImage(dossier_.path()+"/rocher_destr"));
	}else if(obstacle==ROCHER_AMOV){
		rochers_amovibles.ajouter_cle_valeur("rocher_amov",QImage(dossier_.path()+"/rocher_amov"));
	}else if(obstacle==TOURBILLON){
		tourbillons.ajouter_cle_valeur("tourbillon",QImage(dossier_.path()+"/tourbillon"));
	}
#else
	QDir dossier_("fichiers_ressources/ihm/obstacles_interaction");
	if(obstacle==ARBRE){
		arbres.ajouter_cle_valeur("arbre_coupe",QImage(dossier_.path()+"/arbre_coupe.png"));
	}else if(obstacle==ROCHER_DEST){
		rochers_destructibles.ajouter_cle_valeur("rocher_destr",QImage(dossier_.path()+"/rocher_destr.png"));
	}else if(obstacle==ROCHER_AMOV){
		rochers_amovibles.ajouter_cle_valeur("rocher_amov",QImage(dossier_.path()+"/rocher_amov.png"));
	}else if(obstacle==TOURBILLON){
		tourbillons.ajouter_cle_valeur("tourbillon",QImage(dossier_.path()+"/tourbillon.png"));
	}
#endif
}

void Donnees::init_descriptions_complements(){
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
		int nb_langues_=langues.total();
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
		noms_descriptions_attaques.ajouter_cle_valeur(f,descriptions_objets_);
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
			noms_descriptions_attaques.ajouter_cle_valeur(f.split(".")[0],descriptions_objets_);
		}
#endif
	}
}

void Donnees::init_images_env_def(){
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
		images_env_def.ajouter_cle_valeur(f,QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			images_env_def.ajouter_cle_valeur(f.split(".")[0],QImage(dossier_.path()+"/"+f));
		}
#endif
	}
#ifdef QT_NO_DEBUG
	images_env_def.ajouter_cle_valeur("",QImage(dossier_.path()+"/VIDE"));
#else
	images_env_def.ajouter_cle_valeur("",QImage(dossier_.path()+"/VIDE.png"));
#endif
}

void Donnees::init_pokedex(){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/pokedex");
#else
	QDir dossier_("fichiers_ressources/pokedex");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		pokedex.ajouter_cle_valeur(f,new FichePokemon(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")));
#else
		if(f!="."&&f!=".."){
			QString nom_=f.split(".")[0];
			pokedex.ajouter_cle_valeur(nom_,new FichePokemon(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")));
		}
#endif
	}
}

void Donnees::init_bases_evos(){
	foreach(QString f,pokedex.cles()){
		bases_evos<<pokedex.valeur(f)->b_ev();
	}
	bases_evos.removeDuplicates();
	bases_evos.sort();
}

void Donnees::init_miniatures(){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/miniat");
#else
	QDir dossier_("fichiers_ressources/ihm/miniat");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		miniatures.ajouter_cle_valeur(f.toInt(),QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			miniatures.ajouter_cle_valeur(f.split(".")[0].toInt(),QImage(dossier_.path()+"/"+f));
		}
#endif
	}
}

void Donnees::init_images_dos_f(){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/back_f");
#else
	QDir dossier_("fichiers_ressources/ihm/back_f");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		images_dos_f.ajouter_cle_valeur(f.toInt(),QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			images_dos_f.ajouter_cle_valeur(f.split(".")[0].toInt(),QImage(dossier_.path()+"/"+f));
		}
#endif
	}
}

void Donnees::init_images_dos_m(){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/back_m");
#else
	QDir dossier_("fichiers_ressources/ihm/back_m");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		images_dos_m.ajouter_cle_valeur(f.toInt(),QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			images_dos_m.ajouter_cle_valeur(f.split(".")[0].toInt(),QImage(dossier_.path()+"/"+f));
		}
#endif
	}
}

void Donnees::init_images_face_f(){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/front_f");
#else
	QDir dossier_("fichiers_ressources/ihm/front_f");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		images_face_f.ajouter_cle_valeur(f.toInt(),QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			images_face_f.ajouter_cle_valeur(f.split(".")[0].toInt(),QImage(dossier_.path()+"/"+f));
		}
#endif
	}
}

void Donnees::init_images_face_m(){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/front_m");
#else
	QDir dossier_("fichiers_ressources/ihm/front_m");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		images_face_m.ajouter_cle_valeur(f.toInt(),QImage(dossier_.path()+"/"+f));
#else
		if(f!="."&&f!=".."){
			images_face_m.ajouter_cle_valeur(f.split(".")[0].toInt(),QImage(dossier_.path()+"/"+f));
		}
#endif
	}
}



void Donnees::init_types(){
	foreach(QString t,noms_types){
		noms_types_fr<<t.split("\t")[indice_francais];
	}
}

void Donnees::init_rapport_masse_max(){
	Taux t_som_(0);
	Taux t_max_(0);
	foreach(QString f,pokedex.cles()){
		FichePokemon *f_pk_=pokedex.valeur(f);
		Taux m_pk_=f_pk_->m_pk();
		t_som_=t_som_+m_pk_;
		if(t_max_<m_pk_){
			t_max_=m_pk_;
		}
	}
	rapport_max_masse=t_max_*Taux(pokedex.cles().size())/t_som_;
}


void Donnees::init_masse_moy(){
	Taux t_som_=Taux(0);
	foreach(QString f,pokedex.cles()){
		FichePokemon *f_pk_=pokedex.valeur(f);
		Taux m_pk_=f_pk_->m_pk();
		t_som_=t_som_+m_pk_;
	}
	masse_moy=t_som_/Taux(pokedex.cles().size());
}

void Donnees::init_attaques(){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/fiches_attaques");
#else
	QDir dossier_("fichiers_ressources/fiches_attaques");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		attaques.ajouter_cle_valeur(f,new FicheAttaque(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")));
#else
		if(f!="."&&f!=".."){
			QString nom_=f.split(".")[0];
			attaques.ajouter_cle_valeur(nom_,new FicheAttaque(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n")));
		}
#endif
	}
}

	/**coeff_attaques_touch_pseudoinvuln*/
void Donnees::init_attaques_touchant_pseudo_invuln(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/coeff_attaques_touch_pseudoinvuln").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/coeff_attaques_touch_pseudoinvuln.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		QStringList infos_att_=infos_[0].split(",");
		attaques_touchant_pseudo_invuln.ajouter_cle_valeur(QPair<QString,QString>(infos_att_[0],infos_att_[1]),Taux::parse_taux(infos_[1]));
	}
}

void Donnees::init_attaques_lilliput(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/attaques_lilliput").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/attaques_lilliput.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		attaques_lilliput.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
	}
}

void Donnees::init_puissance_degommage(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/puissance_degommage").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/puissance_degommage.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		puissance_degommage.ajouter_cle_valeur(infos_[0],Taux::parse_taux(infos_[1]));
	}
}

void Donnees::init_capacites(){
#ifdef QT_NO_DEBUG
	QDir dossier_(":/fiches_capacites");
#else
	QDir dossier_("fichiers_ressources/fiches_capacites");
#endif
	QStringList fiches_=dossier_.entryList();
	foreach(QString f,fiches_){
#ifdef QT_NO_DEBUG
		capacites.ajouter_cle_valeur(f,new FicheCapacite(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n"),this));
#else
		if(f!="."&&f!=".."){
			capacites.ajouter_cle_valeur(f.split(".")[0],new FicheCapacite(Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n"),this));
		}
#endif
	}
}

void Donnees::init_prix_pierres_objets_evo(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fiches_objets/prix_pierres").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/fiches_objets/prix_pierres.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		QStringList infos_l_=l.split("\t");
		prix_objets_evo.ajouter_cle_valeur(infos_l_[0],infos_l_[1].toInt());
	}
}

void Donnees::init_objets(){
	//TODO ajouter les prix d'achat
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
		objets.ajouter_cle_valeur(f,new Baie(infos_,QPair<QString,uchar>(type_don_nat_,(uchar)puis_don_nat_.toUInt()),prix_));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			QString don_nat_=infos_.takeLast();
			int prix_=infos_.takeLast().toInt();
			QStringList infos_don_nat_=don_nat_.split(QRegExp("(\\W)+"));
			QString type_don_nat_=infos_don_nat_[1];
			QString puis_don_nat_=infos_don_nat_[2];
			objets.ajouter_cle_valeur(f.split(".")[0],new Baie(infos_,QPair<QString,uchar>(type_don_nat_,(uchar)puis_don_nat_.toUInt()),prix_));
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
			objets.ajouter_cle_valeur(f,new Ball(infos_,this,prix_));
		}else{
			infos_.removeAt(0);
			objets.ajouter_cle_valeur(f,new Ball(infos_,this));
		}
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
			if(infos_[0]!="--"){
				int prix_=infos_.takeAt(0).toInt();
				objets.ajouter_cle_valeur(f.split(".")[0],new Ball(infos_,this,prix_));
			}else{
				infos_.removeAt(0);
				objets.ajouter_cle_valeur(f.split(".")[0],new Ball(infos_,this));
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
		objets.ajouter_cle_valeur(f,new Fossile(nom_pk_,niveau_,prix_));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			int prix_=infos_.takeLast().toInt();
			uchar niveau_=(uchar)infos_.takeLast().toUInt();
			QString nom_pk_=infos_.takeLast();
			objets.ajouter_cle_valeur(f.split(".")[0],new Fossile(nom_pk_,niveau_,prix_));
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
		objets.ajouter_cle_valeur(f,new ObjetAttachableCombat(infos_,prix_));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			int prix_=infos_.takeLast().toInt();
			objets.ajouter_cle_valeur(f.split(".")[0],new ObjetAttachableCombat(infos_,prix_));
		}
#endif
	}
	QList<QString> noms_pk_=pokedex.cles();
	HashMap<QString,QStringList> hash_objets_pk_;
	foreach(QString n,noms_pk_){
		FichePokemon *fiche_poke_=pokedex.valeur(n);
		QStringList evolutions_=fiche_poke_->pokemons_evolues();
		foreach(QString e,evolutions_){
			EvolutionObjet *evo_obj_=qobject_cast<EvolutionObjet*>(fiche_poke_->facon_evoluer(e));
			if(evo_obj_){
				//Si l'volution se fait par le port d'un objet permettant l'volution en montant de niveau
				QList<QString> noms_objets_=hash_objets_pk_.cles();
				QString nom_objet_=evo_obj_->nom_objet();
				if(noms_objets_.contains(nom_objet_)){
					QStringList& ls_pk_=hash_objets_pk_.valeur(nom_objet_);
					if(!ls_pk_.contains(n)){
						ls_pk_.append(n);
					}
				}else{
					hash_objets_pk_.ajouter_cle_valeur(nom_objet_,QStringList(n));
				}
			}
		}
	}
	QList<QString> noms_objets_=hash_objets_pk_.cles();
	foreach(QString n,noms_objets_){
		int prix_=prix_objets_evo.valeur(n);
		objets.ajouter_cle_valeur(n,new ObjetEvo(hash_objets_pk_.valeur(n),prix_));
	}
	HashMap<QString,QStringList> hash_pierres_pk_;
	foreach(QString n,noms_pk_){
		FichePokemon *fiche_poke_=pokedex.valeur(n);
		QStringList evolutions_=fiche_poke_->pokemons_evolues();
		foreach(QString e,evolutions_){
			EvolutionPierreEvolutive *evo_obj_=qobject_cast<EvolutionPierreEvolutive*>(fiche_poke_->facon_evoluer(e));
			if(evo_obj_){
				//Si l'volution se fait par le port d'un objet permettant l'volution en montant de niveau
				QList<QString> noms_objets_=hash_pierres_pk_.cles();
				QString nom_objet_=evo_obj_->nom_pierre();
				if(noms_objets_.contains(nom_objet_)){
					QStringList& ls_pk_=hash_pierres_pk_.valeur(nom_objet_);
					if(!ls_pk_.contains(n)){
						ls_pk_.append(n);
					}
				}else{
					hash_pierres_pk_.ajouter_cle_valeur(nom_objet_,QStringList(n));
				}
			}
		}
	}
	noms_objets_=hash_pierres_pk_.cles();
	foreach(QString n,noms_objets_){
		int prix_=prix_objets_evo.valeur(n);
		objets.ajouter_cle_valeur(n,new PierreEvo(hash_pierres_pk_.valeur(n),prix_));
	}
	//noms_pk_objets_.removeDuplicates()
	/*
	TODO utiliser les pokdex pour la compatibilit pour les pierres vo et les objets  attacher
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
		objets.ajouter_cle_valeur(f,new Boost(infos_,effet_p_,prix_));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			int prix_=infos_.takeLast().toInt();
			QString effet_p_=infos_.takeAt(0);
			objets.ajouter_cle_valeur(f.split(".")[0],new Boost(infos_,effet_p_,prix_));
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
		objets.ajouter_cle_valeur(f,new Module(infos_[0],exp_prix_.capturedTexts()[0].toInt()));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
			QRegExp exp_prix_("[0-9]+");
			infos_[1].indexOf(exp_prix_);
			objets.ajouter_cle_valeur(f.split(".")[0],new Module(infos_[0],exp_prix_.capturedTexts()[0].toInt()));
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
		objets.ajouter_cle_valeur(f,new Repousse(exp_pas_.capturedTexts()[0].toUInt(),exp_prix_.capturedTexts()[0].toInt()));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
			QRegExp exp_pas_("[0-9]+");
			infos_[0].indexOf(exp_pas_);
			QRegExp exp_prix_("[0-9]+");
			infos_[1].indexOf(exp_prix_);
			objets.ajouter_cle_valeur(f.split(".")[0],new Repousse(exp_pas_.capturedTexts()[0].toUInt(),exp_prix_.capturedTexts()[0].toInt()));
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
		objets.ajouter_cle_valeur(f,new Revente(exp_prix_.capturedTexts()[0].toInt()));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n");
			QRegExp exp_prix_("[0-9]+");
			infos_[0].indexOf(exp_prix_);
			objets.ajouter_cle_valeur(f.split(".")[0],new Revente(exp_prix_.capturedTexts()[0].toInt()));
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
				objets.ajouter_cle_valeur(f,new SoinPVStatut(infos_,statuts_2_,tx_,prix_));
			}else{
				QStringList pvs_=infos_.filter(QRegExp("^SOIN_PV\\["));
				if(!pvs_[0].contains("MAX")){
					QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
					pvs_[0].indexOf(exp_taux_);
					Taux tx_=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
					objets.ajouter_cle_valeur(f,new SoinPV(infos_,tx_,prix_));
				}else{
					objets.ajouter_cle_valeur(f,new SoinPV(infos_,Taux(0),prix_));
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
				objets.ajouter_cle_valeur(f,new SoinStatut(infos_,statuts_2_,prix_));
			}else if(!infos_.filter(QRegExp("^SOIN_PP\\[")).isEmpty()){
				QStringList infos_pp_=infos_.filter(QRegExp("^SOIN_PP\\["))[0].split(QRegExp("(\\W)+"));
				objets.ajouter_cle_valeur(f,new SoinPP(infos_,QPair<QString,QString>(infos_pp_[1],infos_pp_[2]),prix_));
			}else{//if(!infos_.filter(QRegExp("^SOIN_EQUIPE")).isEmpty())
				objets.ajouter_cle_valeur(f,new Soin(infos_,prix_));
			}
		}
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			int prix_=infos_.takeLast().toInt();
			if(!infos_.filter(QRegExp("^SOIN_PV\\[")).isEmpty()){
				if(!infos_.filter(QRegExp("^SOIN_((STATUT\\[)|(KO))")).isEmpty()){
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
					objets.ajouter_cle_valeur(f.split(".")[0],new SoinPVStatut(infos_,statuts_2_,tx_,prix_));
				}else{
					QStringList pvs_=infos_.filter(QRegExp("^SOIN_PV\\["));
					if(!pvs_[0].contains("MAX")){
						QRegExp exp_taux_("[0-9]+(/[0-9]+)?");
						pvs_[0].indexOf(exp_taux_);
						Taux tx_=Taux::parse_taux(exp_taux_.capturedTexts()[0]);
						objets.ajouter_cle_valeur(f.split(".")[0],new SoinPV(infos_,tx_,prix_));
					}else{
						objets.ajouter_cle_valeur(f.split(".")[0],new SoinPV(infos_,Taux(0),prix_));
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
					objets.ajouter_cle_valeur(f.split(".")[0],new SoinStatut(infos_,statuts_2_,prix_));
				}else if(!infos_.filter(QRegExp("^SOIN_PP\\[")).isEmpty()){
					QStringList infos_pp_=infos_.filter(QRegExp("^SOIN_PP\\["))[0].split(QRegExp("(\\W)+"));
					objets.ajouter_cle_valeur(f.split(".")[0],new SoinPP(infos_,QPair<QString,QString>(infos_pp_[1],infos_pp_[2]),prix_));
				}else{//if(!infos_.filter(QRegExp("^SOIN_EQUIPE")).isEmpty())
					objets.ajouter_cle_valeur(f.split(".")[0],new Soin(infos_,prix_));
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
		objets.ajouter_cle_valeur(f,new Plaque(type_plaque_,type_pk_,coeff_,prix_));
#else
		if(f!="."&&f!=".."){
			QStringList infos_=Utilitaire::lire_fichier(dossier_.path()+"/"+f).split("\n",QString::SkipEmptyParts);
			int prix_=infos_.takeLast().toInt();
			QString type_pk_=infos_.takeAt(0);
			QRegExp exp_coeff_("[0-9]+(/[0-9]+)?");
			infos_[0].indexOf(exp_coeff_);
			Taux coeff_=Taux::parse_taux(exp_coeff_.capturedTexts()[0]);
			QString type_plaque_=infos_[0].split(QRegExp("(\\W)+"))[2];
			objets.ajouter_cle_valeur(f.split(".")[0],new Plaque(type_plaque_,type_pk_,coeff_,prix_));
		}
#endif
	}
}

void Donnees::init_images_objets(){
	QStringList dossiers_;
	dossiers_<<"baies_i";
	dossiers_<<"balls_i";
	dossiers_<<"fossiles_i";
	dossiers_<<"objet_attacher_2_i";
	dossiers_<<"objet_attacher_evo_i";
	dossiers_<<"objet_boost_statistiques_i";
	dossiers_<<"objets_reventes_i";
	dossiers_<<"repousse_i";
	dossiers_<<"modules_i";
	dossiers_<<"objets_soins_i";
	dossiers_<<"pierres_evo_i";
	dossiers_<<"plaques_i";
	foreach(QString d,dossiers_){
#ifdef QT_NO_DEBUG
		QDir dossier_=QDir(":/"+d);
#else
		QDir dossier_=QDir("fichiers_ressources/img_obj/"+d);
#endif
		foreach(QString f,dossier_.entryList(QDir::Files)){
#ifdef QT_NO_DEBUG
			images_objets.ajouter_cle_valeur(f,QImage(dossier_.path()+"/"+f));
#else
			if(f!="."&&f!=".."){
				images_objets.ajouter_cle_valeur(f.split(".")[0],QImage(dossier_.path()+"/"+f));
			}
#endif		
		}
	}
}

void Donnees::init_table_types_base(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/table_types").split("\n");
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/table_types.txt").split("\n");
#endif
	int i_=0;//indice du type defensif
	int j_=0;//indice du type offensif
	foreach(QString l,lignes_){//l est la ligne des coefficients d'efficacit sur le type dfensif
		QStringList colonnes_=l.split("\t");
		j_=0;
		foreach(QString c,colonnes_){
			table_types_base.ajouter_cle_valeur(QPair<QString,QString>(noms_types_fr[j_],noms_types_fr[i_]),Taux::parse_taux(c));
			j_++;
		}
		i_++;
	}
}

void Donnees::init_ct(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fiches_objets/ct_cs_nb").split("\n").filter(QRegExp("^CT"));
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/fiches_objets/ct_cs_nb.txt").split("\n").filter(QRegExp("^CT"));
#endif
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		ct.ajouter_cle_valeur((uchar)infos_[0].mid(2).toUInt(),infos_[1]);
	}
}

void Donnees::init_cs(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fiches_objets/ct_cs_nb").split("\n").filter(QRegExp("^CS"));
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/fiches_objets/ct_cs_nb.txt").split("\n").filter(QRegExp("^CS"));
#endif
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		cs.ajouter_cle_valeur((uchar)infos_[0].mid(2).toUInt(),infos_[1]);
	}
}

void Donnees::init_types_ball_meteo(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/ball_meteo").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/ball_meteo.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		types_ball_meteo.ajouter_cle_valeur(infos_[0],infos_[1]);
	}
}

void Donnees::init_lois_fin_tour(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/lois_effets_fin_tour").split("\n",QString::SkipEmptyParts);
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/lois_effets_fin_tour.txt").split("\n",QString::SkipEmptyParts);
#endif
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		uint min_=infos_[1].toUInt();
		uint max_=infos_[3].toUInt();
		Taux proba_actif_=Taux::parse_taux(infos_[2]);
		Entier eff_actif_=proba_actif_.gnumerateur();
		Entier eff_inactif_=proba_actif_.gdenominateur()-eff_actif_;
		MonteCarlo<bool> loi_;
		loi_.ajouter_event(QPair<bool,Entier>(true,eff_actif_));
		loi_.ajouter_event(QPair<bool,Entier>(false,eff_inactif_));
		lois_fin_tour.ajouter_cle_valeur(infos_[0],QPair<QPair<uint,uint>,MonteCarlo<bool> >(QPair<uint,uint>(min_,max_),loi_));
	}
}

void Donnees::init_abri_attaques(){
#ifdef QT_NO_DEBUG
	abri_attaques=Utilitaire::lire_fichier(":/fichiers_ressources/abri_attaques").split("\n",QString::SkipEmptyParts);
#else
	abri_attaques=Utilitaire::lire_fichier("fichiers_ressources/abri_attaques.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_assistance_attaques(){
#ifdef QT_NO_DEBUG
	assistance_attaques=Utilitaire::lire_fichier(":/fichiers_ressources/assistance_attaques").split("\n",QString::SkipEmptyParts);
#else
	assistance_attaques=Utilitaire::lire_fichier("fichiers_ressources/assistance_attaques.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_attaques_1_pp_plus_tours(){
#ifdef QT_NO_DEBUG
	attaques_1_pp_plus_tours=Utilitaire::lire_fichier(":/fichiers_ressources/attaques_1_pp_plus_tours").split("\n",QString::SkipEmptyParts);
#else
	attaques_1_pp_plus_tours=Utilitaire::lire_fichier("fichiers_ressources/attaques_1_pp_plus_tours.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_attaques_actives_definies(){
#ifdef QT_NO_DEBUG
	attaques_actives_definies=Utilitaire::lire_fichier(":/fichiers_ressources/attaques_actives_definies").split("\n",QString::SkipEmptyParts);
#else
	attaques_actives_definies=Utilitaire::lire_fichier("fichiers_ressources/attaques_actives_definies.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_attaques_actives_indefinies(){
#ifdef QT_NO_DEBUG
	attaques_actives_indefinies=Utilitaire::lire_fichier(":/fichiers_ressources/attaques_actives_indefinies").split("\n",QString::SkipEmptyParts);
#else
	attaques_actives_indefinies=Utilitaire::lire_fichier("fichiers_ressources/attaques_actives_indefinies.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_attaques_anti_soin(){
#ifdef QT_NO_DEBUG
	attaques_anti_soin=Utilitaire::lire_fichier(":/fichiers_ressources/attaques_anti_soin").split("\n",QString::SkipEmptyParts);
#else
	attaques_anti_soin=Utilitaire::lire_fichier("fichiers_ressources/attaques_anti_soin.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_attaques_cc(){
#ifdef QT_NO_DEBUG
	attaques_cc=Utilitaire::lire_fichier(":/fichiers_ressources/attaques_cc").split("\n",QString::SkipEmptyParts);
#else
	attaques_cc=Utilitaire::lire_fichier("fichiers_ressources/attaques_cc.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_auto_degel(){
#ifdef QT_NO_DEBUG
	auto_degel=Utilitaire::lire_fichier(":/fichiers_ressources/auto_degel").split("\n",QString::SkipEmptyParts);
#else
	auto_degel=Utilitaire::lire_fichier("fichiers_ressources/auto_degel.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_blabla_dodo_attaques(){
#ifdef QT_NO_DEBUG
	blabla_dodo_attaques=Utilitaire::lire_fichier(":/fichiers_ressources/blabla_dodo_attaques").split("\n",QString::SkipEmptyParts);
#else
	blabla_dodo_attaques=Utilitaire::lire_fichier("fichiers_ressources/blabla_dodo_attaques.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_camouflage(){
#ifdef QT_NO_DEBUG
	foreach(QString e,Utilitaire::lire_fichier(":/fichiers_ressources/camouflage").split("\n",QString::SkipEmptyParts)){
#else
	foreach(QString e,Utilitaire::lire_fichier("fichiers_ressources/camouflage.txt").split("\n",QString::SkipEmptyParts)){
#endif
		QStringList infos_=e.split("\t");
		camouflage.ajouter_cle_valeur(infos_[0],infos_[1]);
	}
}

void Donnees::init_effets_ec_degommage(){
#ifdef QT_NO_DEBUG
	foreach(QString e,Utilitaire::lire_fichier(":/fichiers_ressources/effets_ec_degommage").split("\n",QString::SkipEmptyParts)){
#else
	foreach(QString e,Utilitaire::lire_fichier("fichiers_ressources/effets_ec_degommage.txt").split("\n",QString::SkipEmptyParts)){
#endif
		QStringList infos_=e.split("\t");
		effets_ec_degommage.ajouter_cle_valeur(infos_[0],infos_[1]);
	}
}

void Donnees::init_clonage_bloc(){
#ifdef QT_NO_DEBUG
	clonage_bloc=Utilitaire::lire_fichier(":/fichiers_ressources/clonage_bloc").split("\n",QString::SkipEmptyParts);
#else
	clonage_bloc=Utilitaire::lire_fichier("fichiers_ressources/clonage_bloc.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_clonage_non_bloc(){
#ifdef QT_NO_DEBUG
	clonage_non_bloc=Utilitaire::lire_fichier(":/fichiers_ressources/clonage_non_bloc").split("\n",QString::SkipEmptyParts);
#else
	clonage_non_bloc=Utilitaire::lire_fichier("fichiers_ressources/clonage_non_bloc.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_copie_attaques(){
#ifdef QT_NO_DEBUG
	copie_attaques=Utilitaire::lire_fichier(":/fichiers_ressources/copie_attaques").split("\n",QString::SkipEmptyParts);
#else
	copie_attaques=Utilitaire::lire_fichier("fichiers_ressources/copie_attaques.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_encore_attaques(){
#ifdef QT_NO_DEBUG
	encore_attaques=Utilitaire::lire_fichier(":/fichiers_ressources/encore_attaques").split("\n",QString::SkipEmptyParts);
#else
	encore_attaques=Utilitaire::lire_fichier("fichiers_ressources/encore_attaques.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_gravite(){
#ifdef QT_NO_DEBUG
	gravite=Utilitaire::lire_fichier(":/fichiers_ressources/gravite").split("\n",QString::SkipEmptyParts);
#else
	gravite=Utilitaire::lire_fichier("fichiers_ressources/gravite.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_metronome(){
#ifdef QT_NO_DEBUG
	metronome=Utilitaire::lire_fichier(":/fichiers_ressources/metronome").split("\n",QString::SkipEmptyParts);
#else
	metronome=Utilitaire::lire_fichier("fichiers_ressources/metronome.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_mimique_attaques(){
#ifdef QT_NO_DEBUG
	mimique_attaques=Utilitaire::lire_fichier(":/fichiers_ressources/mimique_attaques").split("\n",QString::SkipEmptyParts);
#else
	mimique_attaques=Utilitaire::lire_fichier("fichiers_ressources/mimique_attaques.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_mimique_attaques2(){
#ifdef QT_NO_DEBUG
	mimique_attaques2=Utilitaire::lire_fichier(":/fichiers_ressources/mimique_attaques2").split("\n",QString::SkipEmptyParts);
#else
	mimique_attaques2=Utilitaire::lire_fichier("fichiers_ressources/mimique_attaques2.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_non_affecte_abri(){
#ifdef QT_NO_DEBUG
	non_affecte_abri=Utilitaire::lire_fichier(":/fichiers_ressources/non_affecte_abri").split("\n",QString::SkipEmptyParts);
#else
	non_affecte_abri=Utilitaire::lire_fichier("fichiers_ressources/non_affecte_abri.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_non_affecte_poudre_claire(){
#ifdef QT_NO_DEBUG
	non_affecte_poudre_claire=Utilitaire::lire_fichier(":/fichiers_ressources/non_affecte_poudre_claire").split("\n",QString::SkipEmptyParts);
#else
	non_affecte_poudre_claire=Utilitaire::lire_fichier("fichiers_ressources/non_affecte_poudre_claire.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_relations_combattants(){
#ifdef QT_NO_DEBUG
	relations_combattants=Utilitaire::lire_fichier(":/fichiers_ressources/relations_combattants").split("\n",QString::SkipEmptyParts);
#else
	relations_combattants=Utilitaire::lire_fichier("fichiers_ressources/relations_combattants.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_saisie_attaques(){
#ifdef QT_NO_DEBUG
	saisie_attaques=Utilitaire::lire_fichier(":/fichiers_ressources/saisie_attaques").split("\n",QString::SkipEmptyParts);
#else
	saisie_attaques=Utilitaire::lire_fichier("fichiers_ressources/saisie_attaques.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_switch_force(){
#ifdef QT_NO_DEBUG
	switch_force=Utilitaire::lire_fichier(":/fichiers_ressources/switch_force").split("\n",QString::SkipEmptyParts);
#else
	switch_force=Utilitaire::lire_fichier("fichiers_ressources/switch_force.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_force_nature(){
#ifdef QT_NO_DEBUG
	foreach(QString e,Utilitaire::lire_fichier(":/fichiers_ressources/force_nature").split("\n",QString::SkipEmptyParts)){
#else
	foreach(QString e,Utilitaire::lire_fichier("fichiers_ressources/force_nature.txt").split("\n",QString::SkipEmptyParts)){
#endif
		QStringList infos_=e.split("\t");
		force_nature.ajouter_cle_valeur(infos_[0],infos_[1]);
	}
}

void Donnees::init_types_immu(){
#ifdef QT_NO_DEBUG
	foreach(QString e,Utilitaire::lire_fichier(":/fichiers_ressources/types_immu").split("\n",QString::SkipEmptyParts)){
#else
	foreach(QString e,Utilitaire::lire_fichier("fichiers_ressources/types_immu.txt").split("\n",QString::SkipEmptyParts)){
#endif
		QStringList infos_=e.split("\t");
		types_immu.ajouter_cle_valeur(infos_[0],infos_[1].split(";"));
	}
}

void Donnees::init_reflet_magik(){
#ifdef QT_NO_DEBUG
	reflet_magik=Utilitaire::lire_fichier(":/fichiers_ressources/reflet_magik").split("\n",QString::SkipEmptyParts);
#else
	reflet_magik=Utilitaire::lire_fichier("fichiers_ressources/reflet_magik.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_attaques_piegeantes(){
#ifdef QT_NO_DEBUG
	attaques_piegeantes=Utilitaire::lire_fichier(":/fichiers_ressources/attaques_piegeantes").split("\n",QString::SkipEmptyParts);
#else
	attaques_piegeantes=Utilitaire::lire_fichier("fichiers_ressources/attaques_piegeantes.txt").split("\n",QString::SkipEmptyParts);
#endif
}

void Donnees::init_donnees_carto(){
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/fichiers_ressources/donnees_map").split("\n");
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/donnees_map.xml").split("\n");
#endif
	int ind_=0;
	nb_attaques_max=(uchar)lignes_[ind_].split(">")[1].split("<")[0].toUInt();
	ind_++;
	while(lignes_[ind_].endsWith(":")&&lignes_[ind_+1].contains("<Lieu>")){
		//int cle_=lignes_[ind_].left(lignes_[ind_].size()-1)
		QString ligne_=lignes_[ind_];
		ligne_.chop(1);
		while(ligne_[0]<'0'||ligne_[0]>'9'){
			ligne_.remove(0,1);
		}
		int cle_=ligne_.toInt();
		ind_++;
		int ind_deb_=ind_;
		while(!lignes_[ind_].contains("</Lieu>")){
			ind_++;
		}
		lieux.ajouter_cle_valeur(cle_,new Lieu(lignes_.mid(ind_deb_,ind_-ind_deb_)));
		ind_++;
	}
	while(lignes_[ind_].endsWith(":")){
		//int cle_=lignes_[ind_].left(lignes_[ind_].size()-1)
		QString ligne_=lignes_[ind_];
		ligne_.chop(1);
		while(ligne_[0]<'0'||ligne_[0]>'9'){
			ligne_.remove(0,1);
		}
		int cle_=ligne_.toInt();
		ind_++;
		int ind_deb_=ind_;
		while(!lignes_[ind_].contains("</Lig>")){
			ind_++;
		}
		ligues.ajouter_cle_valeur(cle_,new Ligue(lignes_.mid(ind_deb_,ind_-ind_deb_)));
		ind_++;
	}
	coords_depart=Coordonnees(lignes_[ind_]);
	ind_++;
	int ind_deb_=ind_+1;
	while(!lignes_[ind_].contains("</Pok>")){
		ind_++;
	}
	pk_depart=new PokemonSauvage(lignes_.mid(ind_deb_,ind_-ind_deb_));
	ind_++;
	while(lignes_[ind_].contains("LV:")){
		QStringList coords_=lignes_[ind_].split(":");
		QPair<int,int> cle_;
		QStringList coords_2_=coords_[1].split(",");
		cle_.first=coords_2_[0].toInt();
		cle_.second=coords_2_[1].toInt();
		lieux_vols.ajouter_cle_valeur(cle_,Coordonnees(coords_[2]));
		ind_++;
		if(ind_>=lignes_.size()){
			return;
		}
	}
	while(lignes_[ind_].contains("IMG:")){
		QStringList coords_=lignes_[ind_].split(":");
		QPair<int,int> cle_;
		QStringList coords_2_=coords_[1].split(",");
		cle_.first=coords_2_[0].toInt();
		cle_.second=coords_2_[1].toInt();
		images_minimap.ajouter_cle_valeur(cle_,coords_[2]);
		ind_++;
		if(ind_>=lignes_.size()){
			return;
		}
	}
	while(lignes_[ind_].contains("ACC:")){
		QStringList coords_=lignes_[ind_].split(":");
		QList<int> vals_;
		if(!lignes_[ind_].endsWith(":")){
			foreach(QString l,coords_[2].split(",")){
				vals_<<l.toInt();
			}
		}
		acces_fct_ligues.ajouter_cle_valeur(Coordonnees(coords_[1]),vals_);
		//acces_fct_ligues
		ind_++;
		if(ind_>=lignes_.size()){
			return;
		}
	}
	while(lignes_[ind_].contains("CHAMP:")){
		QStringList coords_=lignes_[ind_].split(":");
		QList<Coordonnees> vals_;
		if(!lignes_[ind_].endsWith(":")){
			foreach(QString l,coords_[2].split("_")){
				vals_<<Coordonnees(l);
			}
		}
		champions_battre_ligue.ajouter_cle_valeur(coords_[1].toInt(),vals_);
		//acces_fct_ligues
		ind_++;
		if(ind_>=lignes_.size()){
			return;
		}
	}
}

Donnees::Donnees(){
#ifdef QT_NO_DEBUG
	pk_trouve=QImage(":/ihm/objet_trouve");
#else
	pk_trouve=QImage("fichiers_ressources/ihm/objet_trouve.png");
#endif
	init_langues();
#ifdef QT_NO_DEBUG
	indice_francais=langues.cles().indexOf("FRANCAIS");
#else
	indice_francais=langues.cles().indexOf("FRANCAIS");
#endif
#ifdef QT_NO_DEBUG
	constantes=Utilitaire::lire_fichier(":/fichiers_ressources/constantes").split("\n");
#else
	constantes=Utilitaire::lire_fichier("fichiers_ressources/constantes.txt").split("\n");
#endif
#ifdef QT_NO_DEBUG
	noms_genres=Utilitaire::lire_fichier(":/fichiers_ressources/noms_genres").split("\n",QString::SkipEmptyParts);
#else
	noms_genres=Utilitaire::lire_fichier("fichiers_ressources/noms_genres.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	constantes_non_num=Utilitaire::lire_fichier(":/fichiers_ressources/constantes_non_num").split("\n");
#else
	constantes_non_num=Utilitaire::lire_fichier("fichiers_ressources/constantes_non_num.txt").split("\n");
#endif
	adv=1;
	ut=0;
#ifdef QT_NO_DEBUG
	noms_pk=Utilitaire::lire_fichier(":/fichiers_ressources/trad_n_pk").split("\n",QString::SkipEmptyParts);//trad_n_pk
#else
	noms_pk=Utilitaire::lire_fichier("fichiers_ressources/trad_n_pk.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_envir=Utilitaire::lire_fichier(":/fichiers_ressources/type_environnement").split("\n",QString::SkipEmptyParts);//trad_n_pk
#else
	noms_envir=Utilitaire::lire_fichier("fichiers_ressources/type_environnement.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_types=Utilitaire::lire_fichier(":/fichiers_ressources/types").split("\n",QString::SkipEmptyParts);
#else
	noms_types=Utilitaire::lire_fichier("fichiers_ressources/types.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_statistiques=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_statistiques").split("\n",QString::SkipEmptyParts);
#else
	noms_statistiques=Utilitaire::lire_fichier("fichiers_ressources/traduction_statistiques.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	types_courbes=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_types_courbes").split("\n",QString::SkipEmptyParts);
#else
	types_courbes=Utilitaire::lire_fichier("fichiers_ressources/traduction_types_courbes.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	groupes_oeufs=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_groupes_oeuf").split("\n",QString::SkipEmptyParts);
#else
	groupes_oeufs=Utilitaire::lire_fichier("fichiers_ressources/traduction_groupes_oeuf.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_climats=Utilitaire::lire_fichier(":/fichiers_ressources/climats").split("\n",QString::SkipEmptyParts);
#else
	noms_climats=Utilitaire::lire_fichier("fichiers_ressources/climats.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_statuts=Utilitaire::lire_fichier(":/fichiers_ressources/statuts").split("\n",QString::SkipEmptyParts);
#else
	noms_statuts=Utilitaire::lire_fichier("fichiers_ressources/statuts.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_capacites=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_capacites_pk").split("\n",QString::SkipEmptyParts);
#else
	noms_capacites=Utilitaire::lire_fichier("fichiers_ressources/traduction_capacites_pk.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_attaques=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_attaques_pk").split("\n",QString::SkipEmptyParts);
#else
	noms_attaques=Utilitaire::lire_fichier("fichiers_ressources/traduction_attaques_pk.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_pseudo_statuts=Utilitaire::lire_fichier(":/fichiers_ressources/pseudo_statuts").split("\n",QString::SkipEmptyParts);
#else
	noms_pseudo_statuts=Utilitaire::lire_fichier("fichiers_ressources/pseudo_statuts.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_categories=Utilitaire::lire_fichier(":/fichiers_ressources/categories").split("\n",QString::SkipEmptyParts);
#else
	noms_categories=Utilitaire::lire_fichier("fichiers_ressources/categories.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_pierres_evo=Utilitaire::lire_fichier(":/fichiers_ressources/traductions_pierres_evo").split("\n",QString::SkipEmptyParts);
#else
	noms_pierres_evo=Utilitaire::lire_fichier("fichiers_ressources/traductions_pierres_evo.txt").split("\n",QString::SkipEmptyParts);
#endif
#ifdef QT_NO_DEBUG
	noms_objets_evo=Utilitaire::lire_fichier(":/fichiers_ressources/traductions_objets_evo").split("\n",QString::SkipEmptyParts);
#else
	noms_objets_evo=Utilitaire::lire_fichier("fichiers_ressources/traductions_objets_evo.txt").split("\n",QString::SkipEmptyParts);
#endif
	//lieux_vols
//Lig
}

HashMap<QPair<int,int>,Coordonnees> Donnees::val_lieux_vols()const{
	return lieux_vols;
}

HashMap<QPair<int,int>,QString> Donnees::val_images_minimap()const{
	return images_minimap;
}

QStringList Donnees::genres_non_assexues()const{
	QStringList genres_;
	foreach(QString g,noms_genres){
		if(!g.startsWith("ASSEXUE")){
			genres_<<g.split("\t")[indice_francais];
		}
	}
	return genres_;
}

void Donnees::deplacer_camera(HashMap<QPair<int,int>,Coordonnees>& _tuiles,const QPair<int,int>& _direction,bool _ligue){
	//typedef QPair<int,int> CoinGauche;
	//QList<CoinGauche> cles_abs_;
	//QList<CoinGauche> cles_=_tuiles.cles();
	int largeur_ecran_=(int)(constante_numerique("ESPACE_GAUCHE_ECRAN")+Taux(1)+constante_numerique("ESPACE_DROITE_ECRAN"));
	int hauteur_ecran_=(int)(constante_numerique("ESPACE_HAUT_ECRAN")+Taux(1)+constante_numerique("ESPACE_BAS_ECRAN"));
	/*foreach(CoinGauche c,cles_){
		CoinGauche cle_;
		cle_.first=c.first+_direction.first;
		cle_.second=c.second+_direction.second;
		if(cle_.first<0||cle_.second<0||cle_.first>=largeur_ecran_||cle_.second>=hauteur_ecran_){
			cles_abs_<<c;
		}
	}*/
	HashMap<QPair<int,int>,Coordonnees> bord_ecran_;
	if(_direction.first==0){
		if(_direction.second==1){//vers le bas
			for(int i=0;i<largeur_ecran_;i++){
				for(int j=0;j<hauteur_ecran_-1;j++){
					_tuiles.valeur(QPair<int,int>(i,j))=_tuiles.valeur(QPair<int,int>(i,j+1));
				}
				Coordonnees& coords_=_tuiles.valeur(QPair<int,int>(i,hauteur_ecran_-1));
				//if(coords_.coords_tuile().first!=-1&&coords_.coords_tuile().second!=-1){
				if(coords_!=Coordonnees()){
					bord_ecran_.ajouter_cle_valeur(QPair<int,int>(i,hauteur_ecran_-1),tuile_voisine(coords_,_direction,_ligue));
				}else{
					bord_ecran_.ajouter_cle_valeur(QPair<int,int>(i,hauteur_ecran_-1),coords_);
				}
			}
		}else{//vers le haut
			for(int i=0;i<largeur_ecran_;i++){
				for(int j=hauteur_ecran_-1;j>0;j--){
					_tuiles.valeur(QPair<int,int>(i,j))=_tuiles.valeur(QPair<int,int>(i,j-1));
				}
				Coordonnees& coords_=_tuiles.valeur(QPair<int,int>(i,0));
				//if(coords_.coords_tuile().first!=-1&&coords_.coords_tuile().second!=-1){
				if(coords_!=Coordonnees()){
					bord_ecran_.ajouter_cle_valeur(QPair<int,int>(i,0),tuile_voisine(coords_,_direction,_ligue));
				}else{
					bord_ecran_.ajouter_cle_valeur(QPair<int,int>(i,0),coords_);
				}
			}
		}
	}else if(_direction.first==1){//vers la droite
		for(int j=0;j<hauteur_ecran_;j++){
			for(int i=0;i<largeur_ecran_-1;i++){
				_tuiles.valeur(QPair<int,int>(i,j))=_tuiles.valeur(QPair<int,int>(i+1,j));
			}
			Coordonnees& coords_=_tuiles.valeur(QPair<int,int>(largeur_ecran_-1,j));
			//if(coords_.coords_tuile().first!=-1&&coords_.coords_tuile().second!=-1){
			if(coords_!=Coordonnees()){
				bord_ecran_.ajouter_cle_valeur(QPair<int,int>(largeur_ecran_-1,j),tuile_voisine(coords_,_direction,_ligue));
			}else{
				bord_ecran_.ajouter_cle_valeur(QPair<int,int>(largeur_ecran_-1,j),coords_);
			}
		}
	}else{//vers la gauche
		for(int j=0;j<hauteur_ecran_;j++){
			for(int i=largeur_ecran_-1;i>0;i--){
				_tuiles.valeur(QPair<int,int>(i,j))=_tuiles.valeur(QPair<int,int>(i-1,j));
			}
			Coordonnees& coords_=_tuiles.valeur(QPair<int,int>(0,j));
			//if(coords_.coords_tuile().first!=-1&&coords_.coords_tuile().second!=-1){
			if(coords_!=Coordonnees()){
				bord_ecran_.ajouter_cle_valeur(QPair<int,int>(0,j),tuile_voisine(coords_,_direction,_ligue));
			}else{
				bord_ecran_.ajouter_cle_valeur(QPair<int,int>(0,j),coords_);
			}
		}
	}

	typedef QPair<int,int> Direction;
	typedef QPair<int,int> Position;
	QList<Direction> dirs_;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i!=0||j!=0){
				if(i*_direction.first+j*_direction.second==0){
					dirs_<<Direction(i,j);
				}
			}
		}
	}
	QList<Position> cles_=bord_ecran_.cles();
	bool ajout_=false;
	do{
		ajout_=false;
		foreach(Position p,cles_){
			Coordonnees& coords_=bord_ecran_.valeur(p);
			if(coords_==Coordonnees()){
				continue;
			}
			foreach(Direction d,dirs_){
				Position cle_(d.first+p.first,d.second+p.second);
				if(!cles_.contains(cle_)){
					continue;
				}
				Coordonnees& coords_2_=bord_ecran_.valeur(cle_);
				if(coords_2_==Coordonnees()){
					coords_2_=tuile_voisine(coords_,d,_ligue);
					if(coords_2_!=Coordonnees()){
						ajout_=true;
					}
				}
			}
		}
	}while(ajout_);
	foreach(Position p,cles_){
		_tuiles.valeur(p)=bord_ecran_.valeur(p);
	}
}

HashMap<QPair<int,int>,Coordonnees> Donnees::intersection_avec_ecran(const Coordonnees& _coords,bool _ligue){
	HashMap<QPair<int,int>,Coordonnees> liste_;
	int largeur_ecran_=(int)(constante_numerique("ESPACE_GAUCHE_ECRAN")+Taux(1)+constante_numerique("ESPACE_DROITE_ECRAN"));
	int hauteur_ecran_=(int)(constante_numerique("ESPACE_HAUT_ECRAN")+Taux(1)+constante_numerique("ESPACE_BAS_ECRAN"));
	int x_ecran_2_=constante_numerique("ESPACE_GAUCHE_ECRAN");
	int y_ecran_2_=constante_numerique("ESPACE_HAUT_ECRAN");
	for(int i=0;i<largeur_ecran_;i++){
		for(int j=0;j<hauteur_ecran_;j++){
			liste_.ajouter_cle_valeur(QPair<int,int>(i,j),Coordonnees());
		}
	}
	typedef QPair<int,int> Direction;
	typedef QPair<int,int> Position;
	liste_.valeur(Position(x_ecran_2_,y_ecran_2_))=_coords;
	QList<Direction> dirs_;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if((i!=0)!=(j!=0)){
				dirs_<<Direction(i,j);
			}
		}
	}
	QList<Position> cles_=liste_.cles();
	bool ajout_=false;
	do{
		ajout_=false;
		foreach(Position p,cles_){
			Coordonnees& coords_=liste_.valeur(p);
			if(coords_==Coordonnees()){
				continue;
			}
			foreach(Direction d,dirs_){
				Position cle_(d.first+p.first,d.second+p.second);
				if(!cles_.contains(cle_)){
					continue;
				}
				Coordonnees& coords_2_=liste_.valeur(cle_);
				if(coords_2_==Coordonnees()){
					coords_2_=tuile_voisine(coords_,d,_ligue);
					if(coords_2_!=Coordonnees()){
						ajout_=true;
					}
				}
			}
		}
	}while(ajout_);
	return liste_;
}

QPair<QPair<int,int>,QPair<int,int> > Donnees::intersection(const QPair<int,int>& id,const QPair<int,int>& dims,const QPair<int,int>& id_v,const QPair<int,int>& dims_v){
	QPair<int,int> dr_=QPair<int,int>(id.first+dims.first-1,id.second+dims.second-1);
	QPair<int,int> dr_vois_=QPair<int,int>(id_v.first+dims_v.first-1,id_v.second+dims_v.second-1);
	QPair<int,int> g_int_;
	QPair<int,int> d_int_;
	int inval_=Tuile::_coords_invalide_;
	QPair<QPair<int,int>,QPair<int,int> > retour=QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(inval_,inval_),QPair<int,int>(inval_,inval_));
	if(id.first>id_v.first){
		g_int_.first=id.first;
	}else{
		g_int_.first=id_v.first;
	}
	if(id.second>id_v.second){
		g_int_.second=id.second;
	}else{
		g_int_.second=id_v.second;
	}
	if(dr_.first<dr_vois_.first){
		d_int_.first=dr_.first;
	}else{
		d_int_.first=dr_vois_.first;
	}
	if(dr_.second<dr_vois_.second){
		d_int_.second=dr_.second;
	}else{
		d_int_.second=dr_vois_.second;
	}
	if(d_int_.first<g_int_.first||d_int_.second<g_int_.second){
		return retour;
	}
	retour.first=QPair<int,int>(g_int_.first-id.first,g_int_.second-id.second);
	retour.second=QPair<int,int>(d_int_.first-id.first,d_int_.second-id.second);
	return retour;
}


Coordonnees Donnees::tuile_voisine(const Coordonnees& _coords,const QPair<int,int>& _direction,bool _ligue)const{
	Coordonnees coords_;
	if(!_ligue){
		Lieu *lieu_=lieux.valeur(_coords.lieu());
		Plateau *plateau_=lieu_->plateau(_coords.plateau());
		Environnement *envir_=plateau_->environnement(_coords.coords_environnement());
		QPair<int,int> vois_=_coords.coords_tuile();
		vois_.first+=_direction.first;
		vois_.second+=_direction.second;
		if(envir_->existe(vois_)){
			coords_.lieu()=_coords.lieu();
			coords_.plateau()=_coords.plateau();
			coords_.coords_environnement()=_coords.coords_environnement();
			coords_.coords_tuile()=vois_;
		}else{
			QPair<QPair<int,int>,QPair<int,int> > env_vois_=envir_->voisin(vois_,_direction);
			if(env_vois_.first.first!=-1){
				coords_.lieu()=_coords.lieu();
				coords_.plateau()=_coords.plateau();
				coords_.coords_environnement()=env_vois_.first;
				coords_.coords_tuile()=env_vois_.second;
			}else if(lieu_->contient_lien(_coords.coords_par_rap_lieu())){
				coords_=lieu_->lien_vers(_coords.coords_par_rap_lieu());
			}
		}
		/*if(!lieux.cles().contains(coords_.lieu())){
			coords_=Coordonnees();
		}else{
			lieu_=lieux.valeur(coords_.lieu());
			if(!lieu_->plateaux_c().contains(coords_.plateau())){
				coords_=Coordonnees();
			}else{
				plateau_=lieu_->plateau(coords_.plateau());
				if(!plateau_->coords_env().contains(coords_.coords_environnement())){
					coords_=Coordonnees();
				}else{
					envir_=plateau_->environnement(coords_.coords_environnement());
					if(!envir_->existe(coords_.coords_tuile())){
						coords_=Coordonnees();
					}
				}
			}
		}*/
	}else{
		Ligue *lieu_=ligues.valeur(_coords.lieu());
		PlateauLigue *plateau_=lieu_->plateau(_coords.plateau());
		EnvironnementLigue *envir_=plateau_->environnement(_coords.coords_environnement());
		QPair<int,int> vois_=_coords.coords_tuile();
		vois_.first+=_direction.first;
		vois_.second+=_direction.second;
		if(envir_->existe(vois_)){
			coords_.lieu()=_coords.lieu();
			coords_.plateau()=_coords.plateau();
			coords_.coords_environnement()=_coords.coords_environnement();
			coords_.coords_tuile()=vois_;
		}else{
			QPair<QPair<int,int>,QPair<int,int> > env_vois_=envir_->voisin(vois_,_direction);
			if(env_vois_.first.first!=-1){
				coords_.lieu()=_coords.lieu();
				coords_.plateau()=_coords.plateau();
				coords_.coords_environnement()=env_vois_.first;
				coords_.coords_tuile()=env_vois_.second;
			}
		}
	}
	return coords_;
}

void Donnees::deplacement(const Partie& _partie,const QPair<int,int>& _direction,bool& _ligue,Coordonnees& _coords_ut,QPair<Coordonnees,Coordonnees>& _coords_rocher,QPair<int,int>& _coords_muret,Coordonnees& _obstacle_detruit,QPair<int,int>& _deplacement)const{
	Coordonnees voisin_=tuile_voisine(_coords_ut,_direction,_ligue);
	if(voisin_==Coordonnees()){
		return;
	}
	if(_ligue){
		//TODO
		QPair<int,int> coords_pl_;
		coords_pl_.first=voisin_.coords_environnement().first+voisin_.coords_tuile().first;
		coords_pl_.second=voisin_.coords_environnement().second+voisin_.coords_tuile().second;
		Ligue *ligue_=ligues.valeur(voisin_.lieu());
		PlateauLigue *plateau_=ligue_->plateau(voisin_.plateau());
		if(plateau_->val_coords_dresseur()==coords_pl_){
			return;
		}
		if(voisin_.coords_par_rap_plateau()==plateau_->orig_lien_vers_plateau_suivant()){
			if(_partie.nb_dresseur_ligue_battus()>voisin_.plateau()){
				QPair<QPair<int,int>,QPair<int,int> > dest_=plateau_->dest_lien_vers_plateau_suivant();
				if(dest_.first.first<0){
					_ligue=false;
					_coords_ut=coords_depart;
					return;
				}
				_coords_ut.coords_environnement()=dest_.second;
				_coords_ut.coords_tuile()=dest_.first;
				_coords_ut.plateau()++;
				return;
			}
		}
		_deplacement=_direction;
		_coords_ut=voisin_;
	}else{
		QPair<int,int> pas_suppl_=QPair<int,int>(0,0);
		if(acces_fct_ligues.cles().contains(voisin_)){
			QList<int> ligues_b_;
			foreach(uchar l,_partie.ligues_battues()){
				ligues_b_<<l;
			}
			if(!Utilitaire::contient<int>(ligues_b_,acces_fct_ligues.valeur(voisin_))){
				//TODO message vous devez battre la ligue
				std::cout<<"Ligue non battue\n";
				/*_coords_ut=voisin_;
				_deplacement=pas_suppl_;
				_deplacement.first+=_direction.first;
				_deplacement.second+=_direction.second;*/
				return;
			}
		}
		Lieu *lieu_=lieux.valeur(voisin_.lieu());
		Plateau *plateau_=lieu_->plateau(voisin_.plateau());
		Environnement *envir_=plateau_->environnement(voisin_.coords_environnement());
		QPair<int,int> muret_=envir_->muret_o();
		if(muret_.first!=0||muret_.second!=0){
			if(muret_!=_direction){
				return;
			}
			pas_suppl_=_direction;
			_coords_muret=pas_suppl_;
			voisin_=tuile_voisine(voisin_,_direction,_ligue);
			lieu_=lieux.valeur(voisin_.lieu());
			plateau_=lieu_->plateau(voisin_.plateau());
			envir_=plateau_->environnement(voisin_.coords_environnement());
		}
		if(envir_->type()==""){
			return;
		}
		if(plateau_->contient_lien(voisin_.coords_par_rap_plateau())){
			_coords_ut=plateau_->destination_autre_plateau(voisin_.coords_par_rap_plateau());
			_deplacement=pas_suppl_;
			_deplacement.first+=_direction.first;
			_deplacement.second+=_direction.second;
			return;
		}
		QList<QPair<int,int> > nb_ch_cles_ligues_;
		foreach(int l,ligues.cles()){
			Ligue *ligue_=ligues.valeur(l);
			if(ligue_->origine_c()==voisin_){
				nb_ch_cles_ligues_<<QPair<int,int>(champions_battre_ligue.valeur(l).size(),l);
			}
		}
		Utilitaire::trier<QPair<int,int> >(nb_ch_cles_ligues_,false);
		QList<int> cles_ligues_;
		int nb_l_=nb_ch_cles_ligues_.size();
		for(int i=0;i<nb_l_;i++){
			cles_ligues_<<nb_ch_cles_ligues_[i].second;
		}
		foreach(int l,cles_ligues_){
			Ligue *ligue_=ligues.valeur(l);
			if(_partie.contient_champions(champions_battre_ligue.valeur(l))){
				_ligue=true;
				_coords_ut=ligue_->acces_c();
				return;
			}else{
				std::cout<<"Champion non battu\n";
				_coords_ut=voisin_;
				_deplacement=pas_suppl_;
				_deplacement.first+=_direction.first;
				_deplacement.second+=_direction.second;
				//TODO message vous devez battre le champion....
				return;
			}
		}
		QPair<int,int> depl_glace_=QPair<int,int>(0,0);
		while(envir_->type()=="GLACE"){
			voisin_=tuile_voisine(voisin_,_direction,_ligue);
			if(voisin_==Coordonnees()){
				break;
			}
			envir_=plateau_->environnement(voisin_.coords_environnement());
			depl_glace_.first+=_direction.first;
			depl_glace_.second+=_direction.second;
		}
		if(depl_glace_!=QPair<int,int>(0,0)){
			pas_suppl_.first+=depl_glace_.first;
			pas_suppl_.second+=depl_glace_.second;
			if(!envir_->accessible_par_pied()){
				QPair<int,int> direction_;
				direction_.first=-_direction.first;
				direction_.second=-_direction.second;
				pas_suppl_.first--;
				pas_suppl_.second--;
				voisin_=tuile_voisine(voisin_,direction_,_ligue);
			}
			_deplacement=pas_suppl_;
			_deplacement.first+=_direction.first;
			_deplacement.second+=_direction.second;
			_coords_ut=voisin_;
			return;
		}
		Lieu *lieu_cour_=lieux.valeur(_coords_ut.lieu());
		Plateau *plateau_cour_=lieu_cour_->plateau(_coords_ut.plateau());
		Environnement *envir_cour_=plateau_cour_->environnement(_coords_ut.coords_environnement());
		if(envir_cour_->type()=="EAU"){
			if(envir_->type()=="CASCADE"){
			//champions_battre_ligue
				bool existe_cs_=existe_cs(_partie,"CASCADE");
				if(!existe_cs_){
					//TODO message vous devez battre
					return;
				}
				//TODO test d'existence d'un champion battu donnant l'autorisation d'utiliser CASCADE if(_partie.
				int nb_tuiles_;
				if(_direction.first==0){
					nb_tuiles_=envir_->dimensions().second;
				}else{
					nb_tuiles_=envir_->dimensions().first;
				}
				_deplacement=pas_suppl_;
				for(int i=0;i<nb_tuiles_;i++){
					voisin_=tuile_voisine(voisin_,_direction,_ligue);
					_deplacement.first+=_direction.first;
					_deplacement.second+=_direction.second;
				}
				_coords_ut=voisin_;
				_deplacement.first+=_direction.first;
				_deplacement.second+=_direction.second;
				return;
			}
			if(envir_->accessible_par_surf()){
				if(_partie.arbres_non_coupes().contains(voisin_)){
					destruction_obstacle(_partie,voisin_,"COUPE",pas_suppl_,_direction,_obstacle_detruit,_coords_ut,_deplacement);
					return;
				}
				if(_partie.tourbillon_non_siphones().contains(voisin_)){
					destruction_obstacle(_partie,voisin_,"SIPHON",pas_suppl_,_direction,_obstacle_detruit,_coords_ut,_deplacement);
					return;
				}
				if(_partie.rochers_non_detruits().contains(voisin_)){
					destruction_obstacle(_partie,voisin_,"ECLATE_ROC",pas_suppl_,_direction,_obstacle_detruit,_coords_ut,_deplacement);
					return;
				}
				QList<Coordonnees> roc_depl_=_partie.rocher_a_position(voisin_);
				if(!roc_depl_.isEmpty()){
					bool existe_cs_=existe_cs(_partie,"FORCE");
					if(!existe_cs_){
						//TODO message vous devez battre
						return;
					}
					Coordonnees voisin_2_=tuile_voisine(voisin_,_direction,_ligue);
					if(voisin_2_==Coordonnees()){
						return;
					}
					Lieu *lieu_v_=lieux.valeur(voisin_2_.lieu());
					Plateau *plateau_v_=lieu_v_->plateau(voisin_2_.plateau());
					Environnement *envir_v_=plateau_v_->environnement(voisin_2_.coords_environnement());
					if(!envir_v_->est_vide(voisin_2_.coords_tuile())){
						return;
					}
					_coords_rocher.first=roc_depl_[0];
					_coords_rocher.second=voisin_2_;
					_coords_ut=voisin_;
					_deplacement=pas_suppl_;
					_deplacement.first+=_direction.first;
					_deplacement.second+=_direction.second;
					//est_vide(
				}
				if(!envir_->est_vide(voisin_.coords_tuile())&&!_partie.element_absent(voisin_)){
					return;
				}
				_coords_ut=voisin_;
				_deplacement=pas_suppl_;
				_deplacement.first+=_direction.first;
				_deplacement.second+=_direction.second;
				//
			}
			return;
		}else{
			if(envir_->type()=="ESCALADE"){
			//champions_battre_ligue
				bool existe_cs_=existe_cs(_partie,"ESCALADE");
				if(!existe_cs_){
					//TODO message vous devez battre
					return;
				}
				//TODO test d'existence d'un champion battu donnant l'autorisation d'utiliser ESCALADE if(_partie.
				int nb_tuiles_;
				if(_direction.first==0){
					nb_tuiles_=envir_->dimensions().second;
				}else{
					nb_tuiles_=envir_->dimensions().first;
				}
				_deplacement=pas_suppl_;
				for(int i=0;i<nb_tuiles_;i++){
					voisin_=tuile_voisine(voisin_,_direction,_ligue);
					_deplacement.first+=_direction.first;
					_deplacement.second+=_direction.second;
				}
				_deplacement.first+=_direction.first;
				_deplacement.second+=_direction.second;
				_coords_ut=voisin_;
				return;
			}
			if(envir_->accessible_par_surf()){
				if(_partie.arbres_non_coupes().contains(voisin_)){
					destruction_obstacle(_partie,voisin_,"COUPE",pas_suppl_,_direction,_obstacle_detruit,_coords_ut,_deplacement);
					return;
				}
				if(_partie.tourbillon_non_siphones().contains(voisin_)){
					destruction_obstacle(_partie,voisin_,"SIPHON",pas_suppl_,_direction,_obstacle_detruit,_coords_ut,_deplacement);
					return;
				}
				if(_partie.rochers_non_detruits().contains(voisin_)){
					destruction_obstacle(_partie,voisin_,"ECLATE_ROC",pas_suppl_,_direction,_obstacle_detruit,_coords_ut,_deplacement);
					return;
				}
				QList<Coordonnees> roc_depl_=_partie.rocher_a_position(voisin_);
				if(!roc_depl_.isEmpty()){
					bool existe_cs_=existe_cs(_partie,"FORCE");
					if(!existe_cs_){
						//TODO message vous devez battre
						return;
					}
					Coordonnees voisin_2_=tuile_voisine(voisin_,_direction,_ligue);
					if(voisin_2_==Coordonnees()){
						return;
					}
					Lieu *lieu_v_=lieux.valeur(voisin_2_.lieu());
					Plateau *plateau_v_=lieu_v_->plateau(voisin_2_.plateau());
					Environnement *envir_v_=plateau_v_->environnement(voisin_2_.coords_environnement());
					if(!envir_v_->est_vide(voisin_2_.coords_tuile())){
						return;
					}
					_coords_rocher.first=roc_depl_[0];
					_coords_rocher.second=voisin_2_;
					_coords_ut=voisin_;
					_deplacement=pas_suppl_;
					_deplacement.first+=_direction.first;
					_deplacement.second+=_direction.second;
					//est_vide(
				}
				if(!envir_->est_vide(voisin_.coords_tuile())&&!_partie.element_absent(voisin_)){
					return;
				}
				_deplacement=pas_suppl_;
				_deplacement.first+=_direction.first;
				_deplacement.second+=_direction.second;
				_coords_ut=voisin_;
				//
			}
			return;
		}
		//if(voisin_==ligues.valeur(_partie.ligue_act())
		//champions_battre_ligue
	}
	//Coordonnees pas_suppl_
}

void Donnees::destruction_obstacle(const Partie& _partie,const Coordonnees& _voisin,const QString& _capsule,const QPair<int,int>& _pas_suppl,const QPair<int,int>& _direction,Coordonnees& _obstacle_detruit,Coordonnees& _coords_ut,QPair<int,int>& _deplacement)const{
	bool existe_cs_=existe_cs(_partie,_capsule);
	if(!existe_cs_){
		//TODO message vous devez battre
		return;
	}
	bool existe_coupe_=_partie.existe_pokemon_avec_capsule(_capsule);
	if(existe_coupe_){
		_obstacle_detruit=_voisin;
		_coords_ut=_voisin;
		_deplacement=_pas_suppl;
		_deplacement.first+=_direction.first;
		_deplacement.second+=_direction.second;
	}
}

bool Donnees::existe_cs(const Partie& _partie,const QString& _cs)const{
	foreach(int l,champions_battre_ligue.cles()){
		foreach(Coordonnees c,champions_battre_ligue.valeur(l)){
			Lieu *lieu_ch_=lieux.valeur(c.lieu());
			Plateau *plateau_ch_=lieu_ch_->plateau(c.plateau());
			Environnement *envir_ch_=plateau_ch_->environnement(c.coords_environnement());
			Champion *champ_=qobject_cast<Champion*>(envir_ch_->perso(c.coords_tuile()));
			if(champ_->val_cs()!=0&&cs.valeur(champ_->val_cs())==_cs){
				QList<Coordonnees> sing_ch_;
				sing_ch_<<c;
				if(!_partie.contient_champions(sing_ch_)){
					return false;
				}
			}
		}
	}
	return true;
}

HashMap<QString,QString> Donnees::val_equivalents_genre()const{
	return equivalents_genre;
}

HashMap<QString,QImage> Donnees::val_debut_heros()const{
	return debut_heros;
}

HashMap<QString,QImage> Donnees::val_miniatures_heros()const{
	return miniatures_heros;
}

HashMap<QString,QImage> Donnees::val_face_heros()const{
	return face_heros;
}

HashMap<QString,QImage> Donnees::val_dos_heros()const{
	return dos_heros;
}


Coordonnees Donnees::val_coords_depart()const{
	return coords_depart;
}

uchar Donnees::nb_att_max()const{
	return nb_attaques_max;
}

HashMap<int,Ligue*> Donnees::val_ligues()const{
	return ligues;
}

HashMap<int,Lieu*> Donnees::val_lieux()const{
	return lieux;
}

PokemonSauvage *Donnees::val_pk_depart()const{
	return pk_depart;
}

HashMap<QString,FichePokemon*> Donnees::val_pokedex()const{
	return pokedex;
}

HashMap<QString,FicheAttaque*> Donnees::val_attaques()const{
	return attaques;
}

HashMap<QString,FicheCapacite*> Donnees::val_capacites()const{
	return capacites;
}

HashMap<QString,Objet*> Donnees::val_objets()const{
	return objets;
}

HashMap<QPair<QString,QString>,Taux> Donnees::val_table_types_base()const{
	return table_types_base;
}

QImage Donnees::val_pk_trouve()const{
	return pk_trouve;
}

QStringList Donnees::val_dossiers_tuiles()const{
	return dossiers_tuiles;
}

QStringList Donnees::val_dossiers_dresseurs_macro()const{
	return dossiers_dresseurs_macro;
}

QStringList Donnees::val_dossiers_dresseurs_micro()const{
	return dossiers_dresseurs_micro;
}

HashMap<QString,QImage> Donnees::val_liens()const{
	return liens;
}

HashMap<QString,QImage> Donnees::val_elements_map()const{
	return elements_map;
}

HashMap<QString,QImage> Donnees::val_tuiles_importees()const{
	return tuiles_importees;
}

HashMap<QString,QImage> Donnees::val_dresseurs_macros()const{
	return dresseurs_macros;
}

HashMap<QString,QImage> Donnees::val_dresseurs_micros()const{
	return dresseurs_micros;
}

HashMap<QString,QImage> Donnees::val_arbres()const{
	return arbres;
}

HashMap<QString,QImage> Donnees::val_rochers_destructibles()const{
	return rochers_destructibles;
}

HashMap<QString,QImage> Donnees::val_rochers_amovibles()const{
	return rochers_amovibles;
}

HashMap<QString,QImage> Donnees::val_tourbillons()const{
	return tourbillons;
}

HashMap<QString,QStringList> Donnees::val_noms_descriptions_attaques()const{
	return noms_descriptions_attaques;
}

HashMap<int,QImage> Donnees::val_miniatures()const{
	return miniatures;
}

HashMap<int,QImage> Donnees::val_images_dos_f()const{
	return images_dos_f;
}

HashMap<int,QImage> Donnees::val_images_dos_m()const{
	return images_dos_m;
}

HashMap<int,QImage> Donnees::val_images_face_f()const{
	return images_face_f;
}

HashMap<int,QImage> Donnees::val_images_face_m()const{
	return images_face_m;
}

QStringList Donnees::val_constantes()const{
	return constantes;
}

QStringList Donnees::val_noms_genres()const{
	return noms_genres;
}

QStringList Donnees::val_constantes_non_num()const{
	return constantes_non_num;
}

int Donnees::val_adv()const{
	return adv;
}

int Donnees::val_ut()const{
	return ut;
}

HashMap<QPair<QString,QString>,Taux> Donnees::val_attaques_touchant_pseudo_invuln()const{
	return attaques_touchant_pseudo_invuln;
}

HashMap<QString,Taux> Donnees::val_attaques_lilliput()const{
	return attaques_lilliput;
}

HashMap<QString,Taux> Donnees::val_puissance_degommage()const{
	return puissance_degommage;
}

QStringList Donnees::val_noms_pk()const{
	return noms_pk;
}

QStringList Donnees::val_bases_evos()const{
	return bases_evos;
}

QStringList Donnees::val_noms_envir()const{
	return noms_envir;
}

HashMap<QString,QImage> Donnees::val_images_env_def()const{
	return images_env_def;
}

QStringList Donnees::val_noms_types()const{
	return noms_types;
}

QStringList Donnees::val_noms_types_fr()const{
	return noms_types_fr;
}

QStringList Donnees::val_noms_statistiques()const{
	return noms_statistiques;
}

QStringList Donnees::val_types_courbes()const{
	return types_courbes;
}

QStringList Donnees::val_groupes_oeufs()const{
	return groupes_oeufs;
}

QStringList Donnees::val_noms_climats()const{
	return noms_climats;
}

QStringList Donnees::val_noms_statuts()const{
	return noms_statuts;
}

QStringList Donnees::val_noms_capacites()const{
	return noms_capacites;
}

QStringList Donnees::val_noms_attaques()const{
	return noms_attaques;
}

QStringList Donnees::val_noms_pseudo_statuts()const{
	return noms_pseudo_statuts;
}

QStringList Donnees::val_noms_categories()const{
	return noms_categories;
}

QStringList Donnees::val_noms_pierres_evo()const{
	return noms_pierres_evo;
}

QStringList Donnees::val_noms_objets_evo()const{
	return noms_objets_evo;
}

QStringList Donnees::val_noms_objets()const{
	return noms_objets;
}

HashMap<QString,QImage> Donnees::val_images_objets()const{
	return images_objets;
}

Taux Donnees::val_rapport_max_masse()const{
	return rapport_max_masse;
}

Taux Donnees::val_masse_moy()const{
	return masse_moy;
}

HashMap<QString,QStringList> Donnees::val_langues()const{
	return langues;
}

QStringList Donnees::val_type_lieux()const{
	return type_lieux;
}

HashMap<QString,QString> Donnees::val_types_ball_meteo()const{
	return types_ball_meteo;
}

HashMap<QString,QPair<QPair<uint,uint>,MonteCarlo<bool> > > Donnees::val_lois_fin_tour()const{
	return lois_fin_tour;
}

int Donnees::val_indice_francais()const{
	return indice_francais;
}

HashMap<uchar,QString> Donnees::val_ct()const{
	return ct;
}

HashMap<QString,int> Donnees::val_prix_objets_evo()const{
	return prix_objets_evo;
}

HashMap<uchar,QString> Donnees::val_cs()const{
	return cs;
}

QStringList Donnees::val_abri_attaques()const{
	return abri_attaques;
}

QStringList Donnees::val_assistance_attaques()const{
	return assistance_attaques;
}

QStringList Donnees::val_attaques_1_pp_plus_tours()const{
	return attaques_1_pp_plus_tours;
}

QStringList Donnees::val_attaques_actives_definies()const{
	return attaques_actives_definies;
}

QStringList Donnees::val_attaques_actives_indefinies()const{
	return attaques_actives_indefinies;
}

QStringList Donnees::val_attaques_anti_soin()const{
	return attaques_anti_soin;
}

QStringList Donnees::val_attaques_cc()const{
	return attaques_cc;
}

QStringList Donnees::val_auto_degel()const{
	return auto_degel;
}

QStringList Donnees::val_blabla_dodo_attaques()const{
	return blabla_dodo_attaques;
}

HashMap<QString,QString> Donnees::val_camouflage()const{
	return camouflage;
}

HashMap<QString,QString> Donnees::val_effets_ec_degommage()const{
	return effets_ec_degommage;
}

QStringList Donnees::val_clonage_bloc()const{
	return clonage_bloc;
}

QStringList Donnees::val_clonage_non_bloc()const{
	return clonage_non_bloc;
}

QStringList Donnees::val_copie_attaques()const{
	return copie_attaques;
}

QStringList Donnees::val_encore_attaques()const{
	return encore_attaques;
}

QStringList Donnees::val_gravite()const{
	return gravite;
}

QStringList Donnees::val_metronome()const{
	return metronome;
}

QStringList Donnees::val_mimique_attaques()const{
	return mimique_attaques;
}

QStringList Donnees::val_mimique_attaques2()const{
	return mimique_attaques2;
}

QStringList Donnees::val_non_affecte_abri()const{
	return non_affecte_abri;
}

QStringList Donnees::val_non_affecte_poudre_claire()const{
	return non_affecte_poudre_claire;
}

QStringList Donnees::val_relations_combattants()const{
	return relations_combattants;
}

QStringList Donnees::val_saisie_attaques()const{
	return saisie_attaques;
}

QStringList Donnees::val_switch_force()const{
	return switch_force;
}

HashMap<QString,QString> Donnees::val_force_nature()const{
	return force_nature;
}

HashMap<QString,QStringList> Donnees::val_types_immu()const{
	return types_immu;
}

QStringList Donnees::val_reflet_magik()const{
	return reflet_magik;
}

QStringList Donnees::val_attaques_piegeantes()const{
	return attaques_piegeantes;
}

Donnees::~Donnees(){
	foreach(int l,lieux.cles()){
		Lieu *l_=lieux.valeur(l);
		delete l_;
		l_=NULL;
	}
	foreach(int l,ligues.cles()){
		Ligue *l_=ligues.valeur(l);
		delete l_;
		l_=NULL;
	}
	delete pk_depart;
	pk_depart=NULL;
	foreach(QString c,pokedex.cles()){
		FichePokemon *fiche_pk=pokedex.valeur(c);
		delete fiche_pk;
		fiche_pk=NULL;
	}
	foreach(QString c,attaques.cles()){
		FicheAttaque *fiche_att=attaques.valeur(c);
		delete fiche_att;
		fiche_att=NULL;
	}
	foreach(QString c,capacites.cles()){
		FicheCapacite *fiche_cap=capacites.valeur(c);
		delete fiche_cap;
		fiche_cap=NULL;
	}
	foreach(QString c,objets.cles()){
		Objet *fiche_cap=objets.valeur(c);
		delete fiche_cap;
		fiche_cap=NULL;
	}
}


