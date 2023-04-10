#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H
#include "base_donnees/cartes/tuile.h"
#include "serialisable/base_donnees/hashmap.h"
#include "base_donnees/personnages/dresseur.h"
#include "base_donnees/personnages/personnage.h"
#include "base_donnees/pokemon/pokemonsauvage.h"
#include "math/montecarlo/montecarlo.h"

/***/
class Environnement{

	/***/
	int largeur;

	/**type peut valoir:
	1. roche
	2. herbe
	3. route
	4. étendue d'eau
	5. bâtiment
	6. neige
	7. cascade
	8. escalade
	9. <vide>
	10. muret
si type est vide alors l'environnement n'est jamais accessible.

si type est muret et si l'orientation n'est pas diagonale alors l'environnement n'est accessible que dans un sens.

si type est muret et si l'orientation est diagonale alors l'environnement n'est jamais accessible.*/
	QString type_environnement;

	/***/
	QList<Tuile*> tuiles;

	/***/
	HashMap<QPair<int,int>,Personnage*> personnages;

	/***/
	HashMap<QPair<int,int>,QString> objets;

	/***/
	//QList<QPair<int,int> > arbres;

	/***/
	//QList<QPair<int,int> > rochers_destructibles;

	/***/
	//QList<QPair<int,int> > rochers_deplacables;

	/***/
	//QList<QPair<int,int> > tourbillons;

	/**La probabilité qu'un pokémon apparaissent au bout d'un pas est de 1/nb_pas_moyen_pour_appar;
résultat d'une série numérique.*/
	uchar nb_pas_moyen_pour_appar;

	/***/
	QList<PokemonSauvage*> apparition_per_pok;

	/***/
	MonteCarlo<PokemonSauvage*> apparition_alea_pok;

	/***/
	QList<PokemonSauvage*> apparition_per_pok_sans_leg;

	/***/
	MonteCarlo<PokemonSauvage*> apparition_alea_pok_sans_leg;

	/***/
	HashMap<QString,QList<PokemonSauvage*> > apparition_per_pok_peche;

	/***/
	HashMap<QString,MonteCarlo<PokemonSauvage*> > apparition_alea_pok_peche;

	/***/
	HashMap<QString,QList<PokemonSauvage*> > apparition_per_pok_peche_sans_leg;

	/***/
	HashMap<QString,MonteCarlo<PokemonSauvage*> > apparition_alea_pok_peche_sans_leg;


	/***/
	QList<QPair<int,int> > centres_poke;

	/***/
	QList<QPair<int,int> > echanges_poke_boites;

	/***/
	QList<QPair<int,int> > pensions;

	/***/
	QList<QPair<int,int> > move_tutors;

	/***/
	QList<QPair<int,int> > lieu_faire_revivre_fossile;

	/***/
	//QList<Coordonnees>
	//QList<QPair<QPair<int,int>,QString> > objets_donnes_ramasses;
	HashMap<QPair<int,int>,QString> objets_donnes_ramasses;

	/**Lieux où on peut recevoir un pokémon.
Pour la QPair<QPair<QString,uchar>,QPair<QString,QString>>
premier: nom du pokémon
deuxième: niveau du pokémon
troisième: capacité du pokémon
quatrième: genre du pokémon*/
	//HashMap<QPair<int,int>,Pokemon> lieux_dons_pokemon;
	HashMap<QPair<int,int>,PokemonSauvage*> lieux_dons_pokemon;

	/***/
	HashMap<QPair<int,int>,QStringList> achats_objets;

	/***/
	HashMap<QPair<int,int>,QList<uchar> > achats_ct;

	/***/
	HashMap<QPair<int,int>,QList<uchar> > dons_cs;
	/***/
	HashMap<QPair<int,int>,PokemonSauvage*> pokemon_legendaires;

	/***/
	QList<QPair<QPair<int,int>,QPair<int,int> > > environnements_voisins;

	/**Muret: ne laisse passer le personnage principal que d'un côté.

orientation d'un muret

Si l'orientation est diagonale, alors le muret est symbolisé par un point.

Si l'environnement n'est pas un muret, alors vaut le couple (0,0)*/
	QPair<int,int> muret;

public:

	/**Constante arbitraire indiquant une canne*/
	const static QString _canne_;

	/**Constante arbitraire indiquant une canne*/
	const static QString _super_canne_;

	/**Constante arbitraire indiquant une canne*/
	const static QString _mega_canne_;

	/**Constante arbitraire indiquant un type d'environnement*/
	const static QString _roche_;

	/**Constante arbitraire indiquant un type d'environnement*/
	const static QString _herbe_;

	/**Constante arbitraire indiquant un type d'environnement*/
	const static QString _route_;

	/**Constante arbitraire indiquant un type d'environnement*/
	const static QString _eau_;

	/**Constante arbitraire indiquant un type d'environnement*/
	const static QString _batiment_;

	/**Constante arbitraire indiquant un type d'environnement*/
	const static QString _neige_;

	/**Constante arbitraire indiquant un type d'environnement*/
	const static QString _glace_;

	/**Constante arbitraire indiquant un type d'environnement*/
	const static QString _cascade_;

	Environnement(const QStringList&);

	QPair<int,int> dimensions()const;

	bool existe(const QPair<int,int>&)const;

	QPair<QPair<int,int>,QPair<int,int> > voisin(const QPair<int,int>&,const QPair<int,int>&)const;

	Personnage *perso(const QPair<int,int>&)const;

	bool accessible_par_pied()const;

	bool accessible_par_surf()const;

	bool est_vide(const QPair<int,int>&)const;

	QString type()const;

	QPair<int,int> muret_o()const;


	bool contient_centre_poke(const QPair<int,int>&)const;
	
	bool contient_echange_poke_boites(const QPair<int,int>&)const;

	bool contient_pension(const QPair<int,int>&)const;

	bool contient_move_tutor(const QPair<int,int>&)const;

	bool contient_lieu_fossile(const QPair<int,int>&)const;

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	//QPair<QPair<int,int>,Pokemon> *lieu_dons_pokemon(int);
	PokemonSauvage *don_pokemon(const QPair<int,int>&)const;

	/***/
	//int nb_lieux_dons_pokemon()const;
	QList<QPair<int,int> > coords_lieux_dons_pokemon()const;

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	//QPair<QPair<int,int>,QString> *objet_donne_ramasse(int);
	QString objet_donne_ramasse(const QPair<int,int>&)const;

	/***/
	//int nb_objets_donnes_ramasses()const;
	QList<QPair<int,int> > coords_objets_donnes_ramasses()const;

	/**@param _coords
	@return l'adresse du lieu d'indice _indice*/
	QStringList achat_objets(const QPair<int,int>&)const;

	/***/
	QList<QPair<int,int> > coords_achat_objets()const;

	/***/
	QList<QPair<int,int> > coords_achat_ct()const;

	/**@param _coords
	@return l'adresse du lieu d'indice _indice*/
	QList<uchar> achat_ct(const QPair<int,int>&)const;

	/***/
	QList<QPair<int,int> > coords_don_cs()const;

	/**@param _coords
	@return l'adresse du lieu d'indice _indice*/
	QList<uchar> don_cs(const QPair<int,int>&)const;

	/**Méthode appelée lors d'une tentative d'ajout d'un pokémon dans une liste d'apparition de pêche,
	la pêche prend en compte le type d'environnement du voisin lors du jeu
	@return vrai si et seulement si type_environnement est l'un des suivants: eau, cascade*/
	bool peut_etre_une_zone_de_peche()const;

	QList<QPair<int,int> > coords_autres_persos()const;

	QString objet(const QPair<int,int>&)const;

	
	QList<QPair<int,int> > coords_objets()const;
	
	PokemonSauvage *pokemon_legendaire(const QPair<int,int>&)const;

	
	QList<QPair<int,int> > coords_pokemon_legendaire()const;

	/**Il faut calculer l'indice de la tuile à récupérer en fonction des coordonnées de la tuile à récupérer et des dimensions de l'environnement.
@param _coords_tuile coordonnées de la tuile récupérer
@return L'adresse de la tuile à éditer.*/
	Tuile* tuile(const QPair<int,int>&)const;

	uchar nb_pas_pour_appar()const;

	QList<PokemonSauvage*> apparition_p_pok()const;

	MonteCarlo<PokemonSauvage*> apparition_a_pok()const;

	QList<PokemonSauvage*> apparition_p_sans_leg_pok()const;

	MonteCarlo<PokemonSauvage*> apparition_a_sans_leg_pok()const;

	QList<PokemonSauvage*> apparition_p_pok(const QString& _canne)const;

	MonteCarlo<PokemonSauvage*> apparition_a_pok(const QString& _canne)const;

	QList<PokemonSauvage*> apparition_p_sans_leg_pok(const QString& _canne)const;

	MonteCarlo<PokemonSauvage*> apparition_a_sans_leg_pok(const QString& _canne)const;

	virtual ~Environnement();
};
#endif


