#ifndef RESSOURCES_H
#define RESSOURCES_H
#include "autre/utilitaire.h"
/**Ressources stockées dans l'exécutable pour la traduction*/
namespace Ressources{

	/**noms des types des pokémons*/
#ifdef QT_NO_DEBUG
	const QStringList _constantes_=Utilitaire::lire_fichier(":/fichiers_ressources/constantes").split("\n");
#else
	const QStringList _constantes_=Utilitaire::lire_fichier("fichiers_ressources/constantes.txt").split("\n");
#endif

	/**noms des types des pokémons*/
#ifdef QT_NO_DEBUG
	//const QStringList _noms_pk_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_noms_pk").split("\n");//trad_n_pk
	const QStringList _noms_pk_=Utilitaire::lire_fichier(":/fichiers_ressources/trad_n_pk").split("\n");//
#else
	const QStringList _noms_pk_=Utilitaire::lire_fichier("fichiers_ressources/trad_n_pk.txt").split("\n");
#endif

	/**noms des types des pokémons*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_types_=Utilitaire::lire_fichier(":/fichiers_ressources/types").split("\n");
#else
	const QStringList _noms_types_=Utilitaire::lire_fichier("fichiers_ressources/types.txt").split("\n");
#endif

	/**noms des statistiques*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_statistiques_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_statistiques").split("\n");
#else
	const QStringList _noms_statistiques_=Utilitaire::lire_fichier("fichiers_ressources/traduction_statistiques.txt").split("\n");
#endif

	/**noms des climats*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_climats_=Utilitaire::lire_fichier(":/fichiers_ressources/climats").split("\n");
#else
	const QStringList _noms_climats_=Utilitaire::lire_fichier("fichiers_ressources/climats.txt").split("\n");
#endif

	/**noms des statuts*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_statuts_=Utilitaire::lire_fichier(":/fichiers_ressources/statuts").split("\n");
#else
	const QStringList _noms_statuts_=Utilitaire::lire_fichier("fichiers_ressources/statuts.txt").split("\n");
#endif

	/**noms des capacites*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_capacites_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_capacites_pk").split("\n");
#else
	const QStringList _noms_capacites_=Utilitaire::lire_fichier("fichiers_ressources/traduction_capacites_pk.txt").split("\n");
#endif

	/**noms des attaques*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_attaques_=Utilitaire::lire_fichier(":/fichiers_ressources/traduction_attaques_pk").split("\n");
#else
	const QStringList _noms_attaques_=Utilitaire::lire_fichier("fichiers_ressources/traduction_attaques_pk.txt").split("\n");
#endif

	/**langues*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_pseudo_statuts_=Utilitaire::lire_fichier(":/fichiers_ressources/pseudo_statuts").split("\n");;
#else
	const QStringList _noms_pseudo_statuts_=Utilitaire::lire_fichier("fichiers_ressources/pseudo_statuts.txt").split("\n");;
#endif

	/**langues*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_categories_=Utilitaire::lire_fichier(":/fichiers_ressources/categories").split("\n");;
#else
	const QStringList _noms_categories_=Utilitaire::lire_fichier("fichiers_ressources/categories.txt").split("\n");;
#endif

	/**langues*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_types_lieux_=Utilitaire::lire_fichier(":/fichiers_ressources/type_environnement_2").split("\n");;
#else
	const QStringList _noms_types_lieux_=Utilitaire::lire_fichier("fichiers_ressources/type_environnement_2.txt").split("\n");;
#endif

	/**langues*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_pierres_evo_=Utilitaire::lire_fichier(":/fichiers_ressources/traductions_pierres_evo").split("\n");;
#else
	const QStringList _noms_pierres_evo_=Utilitaire::lire_fichier("fichiers_ressources/traductions_pierres_evo.txt").split("\n");;
#endif

	/**langues: francais et anglais*/
#ifdef QT_NO_DEBUG
	const QStringList _noms_langues_=Utilitaire::lire_fichier(":/fichiers_ressources/langues").split(";");
#else
	const QStringList _noms_langues_=Utilitaire::lire_fichier("fichiers_ressources/langues.txt").split(";");
#endif

	/**langues*/
#ifdef QT_NO_DEBUG
	const int _indice_francais_=_noms_langues_.indexOf("FRANCAIS");
#else
	const int _indice_francais_=_noms_langues_.indexOf("FRANCAIS");
#endif
}
#endif



