#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H
#include "serialisable/cartes/tuile.h"
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/personnages/champion.h"
#include "serialisable/personnages/dresseur1.h"
#include "serialisable/pokemon/pokemon.h"

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
	7. glace
	8. cascade
	9. escalade
	10. <vide>
	//11. muret
si type est vide alors l'environnement n'est jamais accessible.

si type est muret et si l'orientation n'est pas diagonale alors l'environnement n'est accessible que dans un sens.

si type est muret et si l'orientation est diagonale alors l'environnement n'est jamais accessible.*/
	QString type_environnement;

	/***/
	QList<Tuile> tuiles;

	/***/
	HashMap<QPair<int,int>,Champion> champions;

	/***/
	HashMap<QPair<int,int>,Dresseur1> dresseurs1;

	/***/
	HashMap<QPair<int,int>,Personnage> autres_persos;

	/***/
	HashMap<QPair<int,int>,QString> objets;

	/**TODO a supprimer des que le changement d'attribut pour la classe Tuile est fait*/
	//QList<QPair<int,int> > arbres;

	/**TODO a supprimer des que le changement d'attribut pour la classe Tuile est fait*/
	//QList<QPair<int,int> > rochers_destructibles;

	/**TODO a supprimer des que le changement d'attribut pour la classe Tuile est fait*/
	//QList<QPair<int,int> > rochers_deplacables;

	/**TODO a supprimer des que le changement d'attribut pour la classe Tuile est fait*/
	//QList<QPair<int,int> > tourbillons;

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
	HashMap<QPair<int,int>,Pokemon> lieux_dons_pokemon;
	//QList<QPair<QPair<int,int>,Pokemon> > lieux_dons_pokemon;

	/***/
	HashMap<QPair<int,int>,QStringList> achats_objets;

	/***/
	HashMap<QPair<int,int>,QList<uchar> > achats_ct;

	/***/
	HashMap<QPair<int,int>,QList<uchar> > dons_cs;

	/***/
	QList<Pokemon> apparition_per_pok;

	/**La probabilité qu'un pokémon apparaissent au bout d'un pas est de 1/nb_pas_moyen_pour_appar;
résultat d'une série numérique.*/
	uchar nb_pas_moyen_pour_appar;

	/***/
	HashMap<QString,QList<Pokemon> > apparition_per_pok_peche;

	/***/
	HashMap<QPair<int,int>,Pokemon> pokemon_legendaires;

	/**Muret: ne laisse passer le personnage principal que d'un côté.

orientation d'un muret

Si l'orientation est diagonale, alors le muret est symbolisé par un point.

Si l'environnement n'est pas un muret, alors vaut le couple (0,0)

Si l'environnement est un muret franchissable que dans un sens alors la norme au carré de ce couple vaut 1.

Sinon (si l'environnement est un muret non franchissable) la norme au carré de ce couple vaut 2.*/
	QPair<int,int> muret;

	/**Cette méthode décale les clés et les positions d'obstacle d'un point d'ordonnée
	@param _indice indice de la ligne par insertion
	@param _sens si positif ajout, si negatif suppression*/
	void decaler_ligne_elements(int,int);

	/**Cette méthode décale les clés et les positions d'obstacle d'un point d'abscisse
	@param _indice indice de la ligne par insertion
	@param _sens si positif ajout, si negatif suppression*/
	void decaler_colonne_elements(int,int);

	/**Exporte les obstacles
	@param nb_tab_env_att le nombre de tabulation utilisées pour l'indentation
	@param nom_balise le nom de la balise à utiliser
	@param obstacles les coordonnées des obstacles de même nature
	@return une chaîne formatée en XML donnant des informations sur les obstacles*/
	static QString exporter_obstacles(int,const QString&,const QList<QPair<int,int> >&);

	/**Exporte une loi de probabilité à l'aide d'une période de même proba d'apparation dans le temps
	Si nb_pas_moyen_pour_appar vaut 0 alors il n'y a pas d'événement supplémentaire
	@param nb_tab_env_att le nombre de tabulation utilisées pour l'indentation
	@param periode le nombre de tabulation utilisées pour l'indentation
	@param nb_pas_moyen_pour_appar le nombre de tabulation utilisées pour l'indentation
	@param attribut_balise l'attribut de la balise à assigner
	@return une chaîne formatée en XML donnant des informations sur la loi de probabilité*/
	static QString deduire_aleatoire(int,const QList<Pokemon>&,int,const QString& attribut_balise="");

	template<typename Type>
	static void decaler_hashmap(HashMap<QPair<int,int>,Type>&,const QPair<int,int>&);

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

	/**constructeur permettant de sérialiser les données.*/
	Environnement();

	/**constructeur permettant d'intialiser une instance de la classe avec les
	informations apportées par l'utilisateur (largeur,type_environnement) et une information indirectement stockée
	dans l'instance qui est la hauteur.
	Le nombre d'éléments de l'attribut tuiles est de _largeur * _hauteur
	@param _largeur pour assigner la valeur de largeur et calculer le nombre d'éléments de tuiles
	@param _hauteur pour calculer le nombre d'éléments de tuiles
	@param _type_environnement pour assigner la valeur de type_environnement*/
	Environnement(int,int,const QString&);

	bool egal(const Environnement&)const;

	bool existe(const QPair<int,int>&)const;

	bool est_vide(const QPair<int,int>&)const;

	/**@param _coords_suppression coordonnées par rapport à l'environnement où il faut supprimer les éléments*/
	void supprimer_elements(const QPair<int,int>&,bool y_compris_perso=true);

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	QPair<int,int> *centre_poke(int);

	
	int nb_centres_poke()const;

	/**@param _centre_poke le nouveau lieu*/
	void ajouter_centre_poke(const QPair<int,int>&);

	bool contient_centre_poke(const QPair<int,int>&);

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	QPair<int,int> *echange_poke_boites(int);

	
	int nb_echanges_poke_boites()const;

	/**@param _echange_poke_boites le nouveau lieu*/
	void ajouter_echange_poke_boites(const QPair<int,int>&);

	bool contient_echange_poke_boites(const QPair<int,int>&);

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	QPair<int,int> *pension(int);

	/***/
	int nb_pensions()const;

	/**@param _pension le nouveau lieu*/
	void ajouter_pension(const QPair<int,int>&);

	bool contient_pension(const QPair<int,int>&);

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	QPair<int,int> *move_tutor(int);

	/***/
	int nb_move_tutors()const;

	/**@param _move_tutor le nouveau lieu*/
	void ajouter_move_tutor(const QPair<int,int>&);

	bool contient_move_tutor(const QPair<int,int>&);

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	QPair<int,int> *adr_lieu_faire_revivre_fossile(int);

	/***/
	int nb_lieu_faire_revivre_fossile()const;

	/**@param _lieu_faire_revivre_fossile le nouveau lieu*/
	void ajouter_lieu_faire_revivre_fossile(const QPair<int,int>&);

	bool contient_lieu_fossile(const QPair<int,int>&);

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	//QPair<QPair<int,int>,Pokemon> *lieu_dons_pokemon(int);
	Pokemon *don_pokemon(const QPair<int,int>&);

	/***/
	//int nb_lieux_dons_pokemon()const;
	QList<QPair<int,int> > coords_lieux_dons_pokemon()const;

	/**@param _lieu_dons_pokemon le nouveau lieu*/
	//void ajouter_lieu_dons_pokemon(const QPair<QPair<int,int>,Pokemon>&);
	void ajouter_lieu_dons_pokemon(const QPair<int,int>&,const Pokemon&);

	/**@param _indice l'indice du lieu
	@return l'adresse du lieu d'indice _indice*/
	//QPair<QPair<int,int>,QString> *objet_donne_ramasse(int);
	QString *objet_donne_ramasse(const QPair<int,int>&);

	/***/
	//int nb_objets_donnes_ramasses()const;
	QList<QPair<int,int> > coords_objets_donnes_ramasses()const;

	/**@param _objet_donne_ramasse le nouveau lieu*/
	//void ajouter_objet_donne_ramasse(const QPair<QPair<int,int>,QString>&);
	void ajouter_objet_donne_ramasse(const QPair<int,int>&,const QString&);

	/**@param _coords
	@param _n_instance
	@return l'adresse du lieu d'indice _indice*/
	QStringList *achat_objets(const QPair<int,int>&,bool&);

	/**@param _coords
	@return l'adresse du lieu d'indice _indice*/
	QStringList achat_objets(const QPair<int,int>&)const;

	/***/
	QList<QPair<int,int> > coords_achat_objets()const;

	/***/
	void ajouter_achat_objets(const QPair<int,int>&,const QStringList&);

	/***/
	void ajouter_achat_ct(const QPair<int,int>&,const QList<uchar>&);

	/***/
	QList<QPair<int,int> > coords_achat_ct()const;

	/**@param _coords
	@param _n_instance
	@return l'adresse du lieu d'indice _indice*/
	QList<uchar> *achat_ct(const QPair<int,int>&,bool&);

	/**@param _coords
	@return l'adresse du lieu d'indice _indice*/
	QList<uchar> achat_ct(const QPair<int,int>&)const;

	/***/
	void ajouter_don_cs(const QPair<int,int>&,const QList<uchar>&);

	/***/
	QList<QPair<int,int> > coords_don_cs()const;

	/**@param _coords
	@param _n_instance
	@return l'adresse du lieu d'indice _indice*/
	QList<uchar> *don_cs(const QPair<int,int>&,bool&);

	/**@param _coords
	@return l'adresse du lieu d'indice _indice*/
	QList<uchar> don_cs(const QPair<int,int>&)const;

	/**Méthode appelée lors d'une tentative d'ajout d'un pokémon dans une liste d'apparition de pêche,
	la pêche prend en compte le type d'environnement du voisin lors du jeu
	@return vrai si et seulement si type_environnement est l'un des suivants: eau, cascade*/
	bool peut_etre_une_zone_de_peche()const;

	/**Méthode appelée lors d'une tentative de changement de type d'environnement,
	la pêche prend en compte le type d'environnement du voisin lors du jeu
	@param _n_type_env le nouveau type d'environnement pouvant ou non mettre à jour le type d'environnement actuel
	@return vrai si et seulement si type_environnement est l'un des suivants: eau, cascade*/
	bool peut_etre_une_zone_de_peche(const QString&)const;

	/**Permet d'ajouter, de modifier un personnage tout en supprimant éventuellement un élement de l'environnement.
@param _coords_ajout Coordonnées du personnage (par à rapport à l'environnement où il se trouve) où il faut ajouter ou modifier les caractéristiques.
@param _champion personnage à affecter dans une des hashmap des personnage en fonction du type d'instanciation du personnage.*/
	void modifier_champion(const QPair<int,int>&,const Champion&);

	
	Champion *champion(const QPair<int,int>&,bool&);

	
	QList<QPair<int,int> > coords_champions()const;

	/**Permet d'ajouter, de modifier un personnage tout en supprimant éventuellement un élement de l'environnement.
@param _coords_ajout Coordonnées du personnage (par à rapport à l'environnement où il se trouve) où il faut ajouter ou modifier les caractéristiques.
@param _dresseur personnage à affecter dans une des hashmap des personnage en fonction du type d'instanciation du personnage.*/
	void modifier_dresseur(const QPair<int,int>&,const Dresseur1&);

	
	Dresseur1 *dresseur(const QPair<int,int>&,bool&);

	
	QList<QPair<int,int> > coords_dresseurs()const;

	/**Permet d'ajouter, de modifier un personnage tout en supprimant éventuellement un élement de l'environnement.
@param _coords_ajout Coordonnées du personnage (par à rapport à l'environnement où il se trouve) où il faut ajouter ou modifier les caractéristiques.
@param _personnage personnage à affecter dans une des hashmap des personnage en fonction du type d'instanciation du personnage.*/
	void modifier_personnage(const QPair<int,int>&,const Personnage&);

	
	Personnage *personnage(const QPair<int,int>&,bool&);

	
	QList<QPair<int,int> > coords_autres_persos()const;

	/**Ajoute, modifie ou supprimer des obstacles.
@param _coords_ajout coordonnées du nouvel obstacle.
@param _nature_obstacle nature de l'obstacle à ajouter ou à modifier.*/
	/*void modifier_obstacle(const QPair<int,int>&,const QString&);

	
	QPair<int,int> *obstacle(int,const QString&);

	
	int nb_obstacle(const QString&)const;*/

	/**Ajoute l'objet aux coordonnées indiquées.
@param _coords_ajout coordonnées d'ajout d'un objet.
@param _nom_objet nom de l'objet à affecter aux coordonnées.*/
	void modifier_objet(const QPair<int,int>&,const QString&);

	
	QString *objet(const QPair<int,int>&,bool&);

	
	QList<QPair<int,int> > coords_objets()const;

	/**Cette méthode ajoute un pokémon sauvage.
@param _coords Les coordonnées du pokémon à ajouter.
@param _pokemon le pokémon légendaire à ajouter*/
	void modifier_pokemon_legendaire(const QPair<int,int>&,const Pokemon&);

	
	Pokemon *pokemon_legendaire(const QPair<int,int>&,bool&);

	
	QList<QPair<int,int> > coords_pokemon_legendaire()const;

	/**Il faut calculer l'indice de la tuile à récupérer en fonction des coordonnées de la tuile à récupérer et des dimensions de l'environnement.
@param _coords_tuile coordonnées de la tuile récupérer
@return L'adresse de la tuile à éditer.*/
	Tuile* tuile(const QPair<int,int>&);

	/**Cette méthode ajoute une ligne de tuiles standard à l'environnement à l'indice _indice.
Le nombre de tuiles ajoutées vaut la largeur de l'environnement.
La méthode ne modifie pas la largeur.
La méthode modifie certains attributs pour incrémenter l'ordonnée de 1.

Dépend de la largeur.
@param _indice indice de la ligne par insertion*/
	void inserer_ligne(int);

	/**Cette méthode ajoute une ligne de tuiles standard à l'environnement à l'indice _indice.
Le nombre de tuiles ajoutées vaut le nombre total de tuiles sur la largeur de l'environnement.
La méthode incrémente la largeur de 1.
La méthode modifie certains attributs pour incrémenter l'abscisse de 1.

Dépend de la largeur.
@param _indice indice de la colonne à ajouter.*/
	void inserer_colonne(int);

	/**supprime tous les éléments sur la ligne et change les coordonnées (en ordonnée) de certains éléments.
@param _indice indice de la ligne à supprimer*/
	void supprimer_ligne(int);

	/**supprime tous les éléments sur la colonne et change les coordonnées (en abscisse) de certains éléments.

Décrémente de 1, la largeur.
@param _indice indice de la colonne à supprimer*/
	void supprimer_colonne(int);

	/**
@return L'adresse de type_environnement.*/
	QString* type_env();

	
	int periode_appar()const;

	/**Cette méthode insère un pokémon dans l'apparition possible pour l'environnement.
@param _pokemon pokémon sauvage pouvant apparaître dans l'environnement
@param _indice indice d'insertion du pokémon*/
	void inserer_pk_appar(const Pokemon&,int);

	/**Supprime l'apparition du pokémon sauvage.
@param _indice indice de suppression du pokémon sauvage.*/
	void supprimer_pk_appar(int);

	/**@param _indice indice du pokemon dont on veut récupérer l'adresse
	@return l'adresse du pokemon à l'indice _indice*/
	Pokemon *pokemon(int);

	/**
@return l'adresse de nb_pas_moyen_pour_appar.*/
	uchar* adr_nb_pas_moyen_pour_appar();

	
	int periode_appar(const QString&)const;

	/**
@param _canne canne pouvant être utilisée.
@param _pokemon pokémon pouvant être pêché
@param _indice indice d'insertion du pokémon.*/
	void inserer_pk_appar_peche(const QString&,const Pokemon&,int);

	/**
@param _canne canne à utiliser.
@param _indice indice de suppression du pokémon pouvant être péché.*/
	void supprimer_pk_appar_peche(const QString&,int);

	/**@param _canne canne à utiliser
	@param _indice indice du pokemon dont on veut récupérer l'adresse
	@return l'adresse du pokemon à l'indice _indice*/
	Pokemon *pokemon_peche(const QString&,int);

	/**
@return l'adresse de muret.*/
	QPair<int,int>* adr_muret();

	/**Cette méthode donne les dimensions de l'environnement (la hauteur est le quotient entier du nombre de tuiles sur
	la largeur, puisque le nombre de tuiles est un multiple de la largeur.)
	@return les dimensions largeur,hauteur de l'environnement*/
	QPair<int,int> dimensions()const;

	/**Cette méthode donne les dimensions et la position des 4 bords uniligne ou unicolonne de l'environnement (la hauteur est le quotient entier du nombre de tuiles sur
	la largeur, puisque le nombre de tuiles est un multiple de la largeur.)
	@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
	@return la position de les dimensions des 4 bords (extérieurs) de l'environnement*/
	QList<QPair<QPair<int,int>,QPair<int,int> > > bords(const QPair<int,int>&)const;

	/**Cette méthode calcule l'intersection entre 2 environnements
	@param id les coordonnées de l'environnement par rapport au plateau qui le contient
	@param dims les dimensions de l'environnement
	@param id_v les coordonnées de l'environnement voisin par rapport au plateau qui le contient
	@param dims_v les dimensions de l'environnement voisin
	@return les positions des coins extremes de l'intersection par rapport à l'environnement si elle existe, des données invalides sinon*/
	static QPair<QPair<int,int>,QPair<int,int> > intersection(const QPair<int,int>&,const QPair<int,int>&,const QPair<int,int>&,const QPair<int,int>&);

	/**Cette méthode vérifie si l'environnement est valide ou non
	Si l'environnement est un muret alors tous les ensembles doivent être vides et le type de l'environnement doit être la chaîne vide
	Sinon tout est permis.
	@return vrai en cas de validité, faux sinon*/
	bool est_valide()const;

	QList<Pokemon> pokemon_obtensible()const;

	/**Cette méthode exporte sous forme de chaîne de caractères les caractéristiques
de l'environnement situé à la ligue pokémon
appelle la fonction Tuile::exporter()const
Cette méthode ne ferme pas la balise EnvLigue
@param _nb_tab_env le nombre de tabulation à donner pour indenter les lignes.
@param _id les coordonnées de l'environnement par rapport au plateau qui le contient
@return la chaîne de caractères décrivant l'environnement en format XML*/
	QString exporter(int,const QPair<int,int>&)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

template<typename Type>
void Environnement::decaler_hashmap(HashMap<QPair<int,int>,Type>& hash_map,const QPair<int,int>& sens){
	typedef QPair<int,int> Origine;
	QList<Origine> liens_=hash_map.cles();
	HashMap<Origine,Origine> depl_liens_;
	foreach(Origine c,liens_){
		depl_liens_.ajouter_cle_valeur(c,Origine(c.first+sens.first,c.second+sens.second));
	}
	while(!liens_.isEmpty()){
		foreach(Origine c,liens_){
			Origine dest_=depl_liens_.valeur(c);
			if(!liens_.contains(dest_)){
				Type env_depl_=hash_map.valeur(c);
				hash_map.supprimer_cle_valeur(c);
				hash_map.ajouter_cle_valeur(dest_,env_depl_);
				depl_liens_.supprimer_cle_valeur(c);
			}
		}
		liens_=depl_liens_.cles();
	}
}

bool operator==(const Environnement&,const Environnement&);

Flux & operator <<(Flux&,const Environnement&);
Flux & operator >>(Flux&,Environnement&);

#endif



