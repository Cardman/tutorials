#ifndef DONNEES_H
#define DONNEES_H
#include "base_donnees/cartes/ligue.h"
#include "base_donnees/cartes/lieu.h"
#include "serialisable/coordonnees/coordonnees.h"
#include "serialisable/base_donnees/hashmap.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/attaques/ficheattaque.h"
#include "base_donnees/capacites/fichecapacite.h"
#include "base_donnees/objets/objet.h"
#include "serialisable/math/taux.h"
#include <QImage>

class Partie;
/**Contient les elements qui ne changent pas du tout au cours du jeu (excepte les acces a certains de la carte)*/
class Donnees{

	/***/
	HashMap<QString,QImage> debut_heros;

	/***/
	HashMap<QString,QImage> miniatures_heros;

	/***/
	HashMap<QString,QImage> face_heros;

	/***/
	HashMap<QString,QImage> dos_heros;

	/***/
	HashMap<QString,QString> equivalents_genre;

	/**Nombre maximal d'attaques (entre 2 et 8 compris).*/
	uchar nb_attaques_max;

	/***/
	HashMap<int,Ligue*> ligues;

	/***/
	HashMap<int,Lieu*> lieux;

	/***/
	//QList<Coordonnees> centres_poke;

	/***/
	//QList<Coordonnees> echanges_poke_boites;

	/***/
	//QList<Coordonnees> pensions;

	/***/
	//QList<Coordonnees> move_tutors;

	/***/
	//QList<Coordonnees> lieu_faire_revivre_fossile;

	/***/
	//HashMap<Coordonnees,QStringList> objets_donnes_ramasses;

	/**Lieux où on peut recevoir un pokémon.
Pour la QPair<QPair<QString,uchar>,QPair<QString,QString>>
premier: nom du pokémon
deuxième: niveau du pokémon
troisième: capacité du pokémon
quatrième: genre du pokémon*/
	//QList<QPair<Coordonnees,QPair<QPair<QString,uchar>,QPair<QString,QString> > > > lieux_dons_pokemon;
	//HashMap<Coordonnees,PokemonSauvage*> lieux_dons_pokemon;

	/***/
	//HashMap<Coordonnees,QStringList> achats_objets;
	HashMap<Coordonnees,QList<int> > acces_fct_ligues;

	HashMap<int,QList<Coordonnees> > champions_battre_ligue;

	/**Pour que pendant le jeu, l'utilisateur puisse voler à certains endroit en regardant une carte globale*/
	HashMap<QPair<int,int>,Coordonnees> lieux_vols;

	/***/
	HashMap<QPair<int,int>,QString> images_minimap;

	/***/
	Coordonnees coords_depart;

	/***/
	PokemonSauvage *pk_depart;

	/***/
	HashMap<QString,FichePokemon*> pokedex;

	/***/
	HashMap<QString,FicheAttaque*> attaques;

	/***/
	HashMap<QString,FicheCapacite*> capacites;

	/***/
	HashMap<QString,Objet*> objets;

	/***/
	HashMap<QPair<QString,QString>,Taux> table_types_base;

	QImage pk_trouve;

	QStringList dossiers_tuiles;

	QStringList dossiers_dresseurs_macro;

	QStringList dossiers_dresseurs_micro;

	HashMap<QString,QImage> liens;

	HashMap<QString,QImage> elements_map;

	/***/
	HashMap<QString,QImage> tuiles_importees;

	HashMap<QString,QImage> dresseurs_macros;

	HashMap<QString,QImage> dresseurs_micros;

	HashMap<QString,QImage> arbres;

	HashMap<QString,QImage> rochers_destructibles;

	HashMap<QString,QImage> rochers_amovibles;

	HashMap<QString,QImage> tourbillons;

	HashMap<QString,QStringList> noms_descriptions_attaques;

	/***/
	HashMap<int,QImage> miniatures;

	/***/
	HashMap<int,QImage> images_dos_f;

	/***/
	HashMap<int,QImage> images_dos_m;

	/***/
	HashMap<int,QImage> images_face_f;

	/***/
	HashMap<int,QImage> images_face_m;

	/**noms des types des pokémons*/
	QStringList constantes;

	QStringList noms_genres;

	/**noms des types des pokémons*/
	QStringList constantes_non_num;

	/***/
	int adv;

	/***/
	int ut;

	/**coeff_attaques_touch_pseudoinvuln*/
	HashMap<QPair<QString,QString>,Taux> attaques_touchant_pseudo_invuln;

	/**coeff_attaques_touch_pseudoinvuln*/
	HashMap<QString,Taux> attaques_lilliput;

	/**coeff_attaques_touch_pseudoinvuln*/
	HashMap<QString,Taux> puissance_degommage;

	/**noms des types des pokémons*/
	QStringList noms_pk;

	QStringList bases_evos;

	/**noms des environnements*/
	QStringList noms_envir;

	/***/
	HashMap<QString,QImage> images_env_def;

	/**noms des types des pokémons*/
	QStringList noms_types;

	/**noms des types des pokémons*/
	QStringList noms_types_fr;

	/**noms des statistiques*/
	QStringList noms_statistiques;

	/**noms des types de courbes*/
	QStringList types_courbes;

	/**noms des groupes d'oeufs*/
	QStringList groupes_oeufs;

	/**noms des climats*/
	QStringList noms_climats;

	/**noms des statuts*/
	QStringList noms_statuts;

	/**noms des capacites*/
	QStringList noms_capacites;

	/**noms des attaques*/
	QStringList noms_attaques;

	/**langues*/
	QStringList noms_pseudo_statuts;

	/**langues*/
	QStringList noms_categories;

	/**langues*/
	QStringList noms_pierres_evo;

	/**langues*/
	QStringList noms_objets_evo;

	/**noms des objets*/
	QStringList noms_objets;

	HashMap<QString,QImage> images_objets;

	/**langues: francais et anglais*/
	/**uniquement utilisé pour le constructeur de la classe Ball*/
	Taux rapport_max_masse;

	Taux masse_moy;

	HashMap<QString,QStringList> langues;

	QStringList type_lieux;

	HashMap<QString,QPair<QPair<uint,uint>,MonteCarlo<bool> > > lois_fin_tour;

	HashMap<QString,QString> types_ball_meteo;

	/**langues*/
	int indice_francais;

	HashMap<uchar,QString> ct;

	HashMap<QString,int> prix_objets_evo;

	/***/
	HashMap<uchar,QString> cs;

	QStringList attaques_piegeantes;
	QStringList abri_attaques;//attaques
	QStringList assistance_attaques;//attaques
	QStringList attaques_1_pp_plus_tours;//attaques
	QStringList attaques_actives_definies;//attaques
	QStringList attaques_actives_indefinies;//attaques
	QStringList attaques_anti_soin;//attaques
	QStringList attaques_cc;//attaques
	QStringList auto_degel;//attaques
	QStringList blabla_dodo_attaques;//attaques
	HashMap<QString,QString> camouflage;//type_env,type_att
	HashMap<QString,QString> effets_ec_degommage;//attaques
	QStringList clonage_bloc;//attaques
	QStringList clonage_non_bloc;//attaques
	QStringList copie_attaques;//attaques
	QStringList encore_attaques;//attaques
	QStringList gravite;//attaques
	QStringList metronome;//attaques
	QStringList mimique_attaques;//attaques
	QStringList mimique_attaques2;//attaques
	QStringList non_affecte_abri;//attaques
	QStringList non_affecte_poudre_claire;//attaques
	QStringList relations_combattants;//attaques
	QStringList saisie_attaques;//attaques
	QStringList switch_force;//attaques
	HashMap<QString,QStringList> types_immu;
	HashMap<QString,QString> force_nature;
	QStringList reflet_magik;
	/***/
	//HashMap<QString,QStringList> objets_quetes;
public:

	enum TypeObstacle{ARBRE,ROCHER_DEST,ROCHER_AMOV,TOURBILLON};

	void init_heros();

	void init_equivalents_genre();

	void init_type_lieux();

	void init_langues();

	/***/
	void init_dossiers_tuiles();

	/***/
	void init_dossiers_dresseurs_macro();

	/***/
	void init_dossiers_dresseurs_micro();

	/***/
	void init_liens();

	/***/
	void init_elements_map();

	/***/
	void init_tuiles_importees();

	/***/
	void init_dresseurs_macros();

	/***/
	void init_dresseurs_micros();

	/**enum TypeObstacle{ARBRE,ROCHER_DEST,ROCHER_AMOV,TOURBILLON};*/
	void init_obstacles(TypeObstacle);

	/***/
	void init_pokedex();

	/***/
	void init_bases_evos();

	void init_attaques_touchant_pseudo_invuln();

	/***/
	void init_miniatures();

	/***/
	void init_images_dos_f();

	/***/
	void init_images_dos_m();

	/***/
	void init_images_face_f();

	/***/
	void init_images_face_m();


	void init_attaques_lilliput();


	void init_puissance_degommage();


	void init_types();

	/***/
	void init_images_env_def();


	void init_descriptions_complements();


	void init_rapport_masse_max();

	void init_masse_moy();

	void init_noms_genres();

	/***/
	void init_noms_objets();

	/***/
	void init_images_objets();

	/***/
	void init_attaques();

	/***/
	void init_capacites();

	/***/
	void init_table_types_base();

	/***/
	void init_objets();

	/***/
	void init_prix_pierres_objets_evo();

	/***/
	void init_ct();

	void init_types_ball_meteo();

	void init_lois_fin_tour();

	void init_abri_attaques();

	void init_assistance_attaques();

	void init_attaques_1_pp_plus_tours();

	void init_attaques_actives_definies();

	void init_attaques_actives_indefinies();

	void init_attaques_anti_soin();

	void init_attaques_cc();

	void init_auto_degel();

	void init_blabla_dodo_attaques();

	void init_camouflage();

	void init_effets_ec_degommage();

	void init_clonage_bloc();

	void init_clonage_non_bloc();

	void init_copie_attaques();

	void init_encore_attaques();

	void init_gravite();

	void init_metronome();

	void init_mimique_attaques();

	void init_mimique_attaques2();

	void init_non_affecte_abri();

	void init_non_affecte_poudre_claire();

	void init_relations_combattants();

	void init_saisie_attaques();

	void init_switch_force();

	void init_force_nature();

	void init_types_immu();

	void init_reflet_magik();

	/***/
	void init_cs();

	void init_attaques_piegeantes();

	void init_donnees_carto();

	QString constante(const QString&);

	Taux constante_numerique(const QString&);

	QString constante_non_numerique(const QString&,int);

	Donnees();

	void deplacer_camera(HashMap<QPair<int,int>,Coordonnees>&,const QPair<int,int>&,bool);

	HashMap<QPair<int,int>,Coordonnees> intersection_avec_ecran(const Coordonnees&,bool);

	/**Cette méthode calcule l'intersection entre 2 environnements
	@param id les coordonnées de l'environnement par rapport au plateau qui le contient
	@param dims les dimensions de l'environnement
	@param id_v les coordonnées de l'environnement voisin par rapport au plateau qui le contient
	@param dims_v les dimensions de l'environnement voisin
	@return les positions des coins extremes de l'intersection par rapport à l'environnement si elle existe, des données invalides sinon*/
	static QPair<QPair<int,int>,QPair<int,int> > intersection(const QPair<int,int>&,const QPair<int,int>&,const QPair<int,int>&,const QPair<int,int>&);

	Coordonnees tuile_voisine(const Coordonnees&,const QPair<int,int>&,bool)const;

	void deplacement(const Partie&,const QPair<int,int>&,bool&,Coordonnees&,QPair<Coordonnees,Coordonnees>&,QPair<int,int>&,Coordonnees&,QPair<int,int>&)const;

	bool existe_cs(const Partie& _partie,const QString& _cs)const;

	void destruction_obstacle(const Partie&,const Coordonnees&,const QString&,const QPair<int,int>&,const QPair<int,int>&,Coordonnees&,Coordonnees&,QPair<int,int>&)const;

	HashMap<QString,QString> val_equivalents_genre()const;

	HashMap<QString,QImage> val_debut_heros()const;

	HashMap<QString,QImage> val_miniatures_heros()const;

	HashMap<QString,QImage> val_face_heros()const;

	HashMap<QString,QImage> val_dos_heros()const;

	PokemonSauvage *val_pk_depart()const;

	Coordonnees val_coords_depart()const;

	uchar nb_att_max()const;

	HashMap<int,Ligue*> val_ligues()const;

	HashMap<int,Lieu*> val_lieux()const;

	HashMap<QPair<int,int>,Coordonnees> val_lieux_vols()const;

	HashMap<QPair<int,int>,QString> val_images_minimap()const;

	QStringList genres_non_assexues()const;

	HashMap<QString,FichePokemon*> val_pokedex()const;
	HashMap<QString,FicheAttaque*> val_attaques()const;
	HashMap<QString,FicheCapacite*> val_capacites()const;
	HashMap<QString,Objet*> val_objets()const;
	HashMap<QPair<QString,QString>,Taux> val_table_types_base()const;
	QImage val_pk_trouve()const;
	QStringList val_dossiers_tuiles()const;
	QStringList val_dossiers_dresseurs_macro()const;
	QStringList val_dossiers_dresseurs_micro()const;
	HashMap<QString,QImage> val_liens()const;
	HashMap<QString,QImage> val_elements_map()const;
	HashMap<QString,QImage> val_tuiles_importees()const;
	HashMap<QString,QImage> val_dresseurs_macros()const;
	HashMap<QString,QImage> val_dresseurs_micros()const;
	HashMap<QString,QImage> val_arbres()const;
	HashMap<QString,QImage> val_rochers_destructibles()const;
	HashMap<QString,QImage> val_rochers_amovibles()const;
	HashMap<QString,QImage> val_tourbillons()const;
	HashMap<QString,QStringList> val_noms_descriptions_attaques()const;
	HashMap<int,QImage> val_miniatures()const;
	HashMap<int,QImage> val_images_dos_f()const;
	HashMap<int,QImage> val_images_dos_m()const;
	HashMap<int,QImage> val_images_face_f()const;
	HashMap<int,QImage> val_images_face_m()const;
	QStringList val_constantes()const;
	QStringList val_noms_genres()const;
	QStringList val_constantes_non_num()const;
	int val_adv()const;
	int val_ut()const;
	HashMap<QPair<QString,QString>,Taux> val_attaques_touchant_pseudo_invuln()const;
	HashMap<QString,Taux> val_attaques_lilliput()const;
	HashMap<QString,Taux> val_puissance_degommage()const;
	QStringList val_noms_pk()const;
	QStringList val_bases_evos()const;
	QStringList val_noms_envir()const;
	HashMap<QString,QImage> val_images_env_def()const;
	QStringList val_noms_types()const;
	QStringList val_noms_types_fr()const;
	QStringList val_noms_statistiques()const;
	QStringList val_types_courbes()const;
	QStringList val_groupes_oeufs()const;
	QStringList val_noms_climats()const;
	QStringList val_noms_statuts()const;
	QStringList val_noms_capacites()const;
	QStringList val_noms_attaques()const;
	QStringList val_noms_pseudo_statuts()const;
	QStringList val_noms_categories()const;
	QStringList val_noms_pierres_evo()const;
	QStringList val_noms_objets_evo()const;
	QStringList val_noms_objets()const;
	HashMap<QString,QImage> val_images_objets()const;
	Taux val_rapport_max_masse()const;
	Taux val_masse_moy()const;
	HashMap<QString,QStringList> val_langues()const;
	QStringList val_type_lieux()const;
	HashMap<QString,QString> val_types_ball_meteo()const;
	HashMap<QString,QPair<QPair<uint,uint>,MonteCarlo<bool> > > val_lois_fin_tour()const;
	int val_indice_francais()const;
	HashMap<uchar,QString> val_ct()const;
	HashMap<QString,int> val_prix_objets_evo()const;
	HashMap<uchar,QString> val_cs()const;

	QStringList val_abri_attaques()const;

	QStringList val_assistance_attaques()const;

	QStringList val_attaques_1_pp_plus_tours()const;

	QStringList val_attaques_actives_definies()const;

	QStringList val_attaques_actives_indefinies()const;

	QStringList val_attaques_anti_soin()const;

	QStringList val_attaques_cc()const;

	QStringList val_auto_degel()const;

	QStringList val_blabla_dodo_attaques()const;

	HashMap<QString,QString> val_camouflage()const;

	HashMap<QString,QString> val_effets_ec_degommage()const;

	QStringList val_clonage_bloc()const;

	QStringList val_clonage_non_bloc()const;

	QStringList val_copie_attaques()const;

	QStringList val_encore_attaques()const;

	QStringList val_gravite()const;

	QStringList val_metronome()const;

	QStringList val_mimique_attaques()const;

	QStringList val_mimique_attaques2()const;

	QStringList val_non_affecte_abri()const;

	QStringList val_non_affecte_poudre_claire()const;

	QStringList val_relations_combattants()const;

	QStringList val_saisie_attaques()const;

	QStringList val_switch_force()const;

	HashMap<QString,QString>  val_force_nature()const;

	HashMap<QString,QStringList> val_types_immu()const;

	QStringList val_reflet_magik()const;

	QStringList val_attaques_piegeantes()const;

	virtual ~Donnees();

};
#endif


