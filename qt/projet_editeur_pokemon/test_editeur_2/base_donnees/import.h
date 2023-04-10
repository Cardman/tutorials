#ifndef IMPORT_H
#define IMPORT_H
//#include "serialisable/cartes/donnees.h"
//#include "serialisable/cartes/lieu.h"
//#include "base_donnees/objets/objet.h"
#include <QImage>
#include "math/taux.h"
#include "serialisable/base_donnees/hashmap.h"

class FichePokemon;
class FicheAttaque;
class FicheCapacite;
class Objet;
/***/
class Import{

	enum TypeObstacle{ARBRE,ROCHER_DEST,ROCHER_AMOV,TOURBILLON};

	static QStringList init_type_lieux();

	static HashMap<QString,QStringList> init_langues();

	/***/
	static HashMap<QString,QStringList> init_noms_menus();

	/***/
	static QStringList init_dossiers_tuiles();

	/***/
	static QStringList init_dossiers_dresseurs_macro();

	/***/
	static QStringList init_dossiers_dresseurs_micro();

	/***/
	static HashMap<QString,QImage> init_liens();

	/***/
	static HashMap<QString,QImage> init_elements_map();

	/***/
	static HashMap<QString,QImage> init_tuiles_importees();

	/***/
	static HashMap<QString,QImage> init_dresseurs_macros();

	/***/
	static HashMap<QString,QImage> init_dresseurs_micros();

	/**enum TypeObstacle{ARBRE,ROCHER_DEST,ROCHER_AMOV,TOURBILLON};*/
	static HashMap<QString,QImage> init_obstacles(TypeObstacle);

	/***/
	static HashMap<QString,FichePokemon*> init_pokedex();

	/***/
	static QStringList init_bases_evos();
	
	static HashMap<QPair<QString,QString>,Taux> init_attaques_touchant_pseudo_invuln();

	/***/
	static HashMap<int,QImage> init_miniatures();

	
	static HashMap<QString,Taux> init_attaques_lilliput();

	
	static HashMap<QString,Taux> init_puissance_degommage();

	
	static QStringList init_types();

	/***/
	static HashMap<QString,QImage> init_images_env_def();

	
	static HashMap<QString,QStringList> init_descriptions_complements();

	
	static Taux init_rapport_masse_max();

	static QStringList init_noms_genres();

	/***/
	static QStringList init_noms_objets();

	/***/
	static HashMap<QString,QImage> init_images_objets();

	/***/
	static HashMap<QString,FicheAttaque*> init_attaques();

	/***/
	static HashMap<QString,FicheCapacite*> init_capacites();

	/***/
	static HashMap<QPair<QString,QString>,Taux> init_table_types_base();

	/***/
	static HashMap<QString,Objet*> init_objets();

	/***/
	static HashMap<QString,int> init_prix_pierres_objets_evo();

	/***/
	static HashMap<uchar,QString> init_ct();

	/***/
	static HashMap<uchar,QString> init_cs();

	/***/
	const static HashMap<QString,int> _prix_objets_evo_;

	/**Ne pas instancier un objet de cette classe*/
	Import();
public:

	static QString constante(const QString&);

	static Taux constante_numerique(const QString&);

	static QString constante_non_numerique(const QString&,int);

	/***/
	const static int _log_base_;

	/***/
	const static HashMap<QString,QStringList> _noms_menus_;

	/***/
	const static QImage _tuile_invalide_;

	const static QImage _map_invalide_;

	const static QImage _pk_trouve_;

	const static QStringList _dossiers_tuiles_;

	const static QStringList _dossiers_dresseurs_macro_;

	const static QStringList _dossiers_dresseurs_micro_;

	const static HashMap<QString,QImage> _liens_;

	const static HashMap<QString,QImage> _elements_map_;

	/***/
	const static HashMap<QString,QImage> _tuiles_importees_;

	const static HashMap<QString,QImage> _dresseurs_macros_;

	const static HashMap<QString,QImage> _dresseurs_micros_;

	const static HashMap<QString,QImage> _arbres_;

	const static HashMap<QString,QImage> _rochers_destructibles_;

	const static HashMap<QString,QImage> _rochers_amovibles_;

	const static HashMap<QString,QImage> _tourbillons_;

	/***/
	const static HashMap<QString,QStringList> _noms_descriptions_attaques_;

	/***/
	const static HashMap<int,QImage> _miniatures_;

	/**noms des types des pokémons*/
	const static QStringList _constantes_;

	const static QStringList _noms_genres_;

	/**noms des types des pokémons*/
	const static QStringList _constantes_non_num_;

	/***/
	const static int _adv_;

	/***/
	const static int _ut_;

	/**coeff_attaques_touch_pseudoinvuln*/
	const static HashMap<QPair<QString,QString>,Taux> _attaques_touchant_pseudo_invuln_;

	/**coeff_attaques_touch_pseudoinvuln*/
	const static HashMap<QString,Taux> _attaques_lilliput_;

	/**coeff_attaques_touch_pseudoinvuln*/
	const static HashMap<QString,Taux> _puissance_degommage_;

	/**noms des types des pokémons*/
	const static QStringList _noms_pk_;

	const static QStringList _bases_evos_;

	/**noms des environnements*/
	const static QStringList _noms_envir_;

	/***/
	const static HashMap<QString,QImage> _images_env_def_;

	/**noms des types des pokémons*/
	const static QStringList _noms_types_;

	/**noms des types des pokémons*/
	const static QStringList _noms_types_fr_;

	/**noms des statistiques*/
	const static QStringList _noms_statistiques_;

	/**noms des types de courbes*/
	const static QStringList _types_courbes_;

	/**noms des groupes d'oeufs*/
	const static QStringList _groupes_oeufs_;

	/**noms des climats*/
	const static QStringList _noms_climats_;

	/**noms des statuts*/
	const static QStringList _noms_statuts_;

	/**noms des capacites*/
	const static QStringList _noms_capacites_;

	/**noms des attaques*/
	const static QStringList _noms_attaques_;

	/**langues*/
	const static QStringList _noms_pseudo_statuts_;

	/**langues*/
	const static QStringList _noms_categories_;

	/**langues*/
	const static QStringList _noms_pierres_evo_;

	/**langues*/
	const static QStringList _noms_objets_evo_;

	/**noms des objets*/
	const static QStringList _noms_objets_;

	const static HashMap<QString,QImage> _images_objets_;

	/**langues: francais et anglais*/
	/**uniquement utilisé pour le constructeur de la classe Ball*/
	const static Taux _rapport_max_masse_;

	const static HashMap<QString,QStringList> _langues_;

	const static QStringList _type_lieux_;

	/**langues*/
	const static int _indice_francais_;

	/***/
	const static HashMap<QString,FichePokemon*> _pokedex_;

	/***/
	const static HashMap<QString,FicheAttaque*> _attaques_;

	/***/
	const static HashMap<QString,FicheCapacite*> _capacites_;

	/***/
	const static HashMap<QString,Objet*> _objets_;

	/***/
	const static HashMap<QPair<QString,QString>,Taux> _table_types_base_;

	/***/
	const static HashMap<uchar,QString> _ct_;

	/***/
	const static HashMap<uchar,QString> _cs_;

	/***/
	static void destructeur();
	//HashMap<QString,QStringList> objets_quetes;
};

#endif




