#ifndef PARTIE_H
#define PARTIE_H
#include "serialisable/utilisateur/utilisateur.h"
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/coordonnees/coordonnees.h"
#include "serialisable/pokemon/pokemonutilisateur.h"
#include "serialisable/combat/elementscombat.h"
#include "serialisable/difficulte/difficulte.h"
#include "serialisable/math/entier.h"

/**Contient les donnes essentielles pour mettre en place l'ihm*/
class Partie{

	/**contient les elements modifies par l'utilisateur*/
	Utilisateur utilisateur;

	/**nom du rival du heros*/
	//QString nom_rival;

	/**premier: numero du stade de la ligue
0 pour la premiere ligue non battue
1 pour la deuxieme ligue non battue
2 pour la troisieme ligue non battue
3 pour la troisieme ligue battue

deuxieme: accessibilite au numero de ligue
0 pour la premiere ligue inaccessible
1pour la premiere ligue accessible
2 pour la deuxieme ligue accessible
3 pour la troisieme ligue accessible*/
	//QPair<uchar,uchar> numero_ligue;
	QList<uchar> ligues_deja_battues;

	/**nombre de dresseurs de la ligue battus (remis a zero une fois la ligue battue)*/
	uchar stade_ligue;

	/***/
	HashMap<QPair<Coordonnees,int>,bool> dresseurs_battus;

	/***/
	HashMap<Coordonnees,bool> objets_ramasses;

	/***/
	HashMap<Coordonnees,bool> arbres_coupes;

	/***/
	HashMap<Coordonnees,bool> rochers_detruits;

	/***/
	HashMap<Coordonnees,Coordonnees> position_actuelle_rochers_deplacables;

	/***/
	HashMap<Coordonnees,bool> tourbillons_siphones;

	/***/
	HashMap<Coordonnees,bool> pokemon_pris;

	/***/
	bool ligue;

	/***/
	Coordonnees coordonnees_utilisateur;

	/**(0,1);(1,0);(0,-1);(-1,0)*/
	QPair<int,int> orientation_utilisateur;

	/***/
	Coordonnees dernier_ctre_poke_vis;

	/***/
	HashMap<Coordonnees,QPair<QPair<PokemonUtilisateur,PokemonUtilisateur>,int> > pokemon_pension;

	/***/
	ElementsCombat elements_combat;

	/***/
	Difficulte difficultes;

	/**nombre total de captures mis à jour lors d'une sauvegarde d'une partie.*/
	Entier total_captures;

	/**noms des boîtes donnés par l'utilisateur.*/
	QStringList noms_boites;

	/**maximum de pokémons que l'utilisateur et les adversaires peuvent utiliser pendant un combat.*/
	//uchar max_pk_equipe;

	HashMap<QString,uint> indice_periode_peche;

	uint indice_periode;

	uint indice_pas;

	QString commentaire;

	HashMap<int,bool> lieux_visites;

public:

	enum INTERFACE{RIEN,VOL,DIFF,JOUEUR,DRESSEUR,COMBAT_PK_SAUV,PK_LEG,PECHE,DON_OBJET,DON_PK,OBJ_RAMAS,PK_RAMAS,PERSONNAGE,ECH_BOITE,SOIN_PK,MOVE_TUTORS,ACHATS,ACHATS_CT,DON_CS,PENSION,FOSSILE};

	Partie();

	Partie(Donnees*);

	QString& commentaire_r();

	void incrementer_per_peche(const QString&);

	void reinit_per_peche(const QString&);

	uint periode_peche(const QString&)const;

	bool present_ligue()const;

	bool& present_ligue();

	bool lieu_visite(int)const;

	Coordonnees coords_util()const;

	Coordonnees& coords_util();

	bool contient_champions(const QList<Coordonnees>&)const;

	uchar nb_dresseur_ligue_battus()const;

	uchar& nb_dresseur_ligue_battus();

	QList<uchar> ligues_battues()const;

	QList<uchar>& ligues_battues();

	QList<Coordonnees> arbres_non_coupes()const;

	QList<Coordonnees> tourbillon_non_siphones()const;

	QList<Coordonnees> rochers_non_detruits()const;

	QList<Coordonnees> rocher_a_position(const Coordonnees&)const;

	void prendre_pokemon(const Coordonnees&);

	bool element_absent(const Coordonnees&)const;

	QPair<int,int> orientation()const;

	Difficulte diff()const;

	Difficulte& diff();

	Utilisateur utilis()const;

	Utilisateur& utilis();

	bool existe_pokemon_avec_capsule(const QString& _capsule)const;

	bool pension_disponible(const Coordonnees&)const;

	QString compatibles_pensions(uchar,uchar,Donnees*)const;

	void deposer_pokemons_pension(uchar,uchar,const Coordonnees&);

	bool recuperer_pokemons_pension(const Coordonnees&);

	void augmenter_pas_vers_ponte();

	int nombre_pas_restants(const Coordonnees&,Donnees*)const;

	bool possibilite_de_recuperer_oeuf(const Coordonnees&,Donnees*)const;

	OeufPokemon oeuf_produit(const Coordonnees&,Donnees*)const;

	void prendre_oeuf_produit(const Coordonnees&);

	HashMap<QPair<Coordonnees,int>,bool>& r_dresseurs_battus();

	uchar deplacement(const QPair<int,int>&,QPair<int,int>&,QPair<int,int>&,Donnees*);

	ElementsCombat& combat();

	bool partie_finie(Donnees*)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const Partie&);
Flux & operator >>(Flux&,Partie&);

#endif


