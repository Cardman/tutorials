#ifndef POKEMONUTILISATEUR_H
#define POKEMONUTILISATEUR_H
#include "base_donnees/pokemon/pokemon.h"
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/math/taux.h"
#include "serialisable/math/entier.h"
class CreatureCombat;
class Fossile;
class OeufPokemon;
class PokemonSauvage;
class Donnees;
class SoinPV;
class SoinPVStatut;
class FichePokemon;

/**Pokemon d'utilisateur en combat ou utilise en aventure. Les ev sont modifiables par le gain d'experience en  combat.*/
class PokemonUtilisateur{

	/***/
	QString nom;

	/***/
	uchar niveau;

	/***/
	QString genre;

	/**non modifiable une fois affecte a l'objet.*/
	QString capacite;

	/**si la chaine de caractere est vide alors le pokemon ne porte pas d'objet, sinon cette chaine vaut le nom de l'objet. */
	QString nom_objet;

	/***/
	Taux pv_restants;

	/***/
	QString statut;

	/***/
	HashMap<QString,uchar> iv_statistiques;

	/**pseudo du pokemon par defaut le nom du pokemon*/
	QString pseudo;

	/***/
	QList<QPair<QString,QPair<uchar,uchar> > > attaques;

	/***/
	HashMap<QString,uchar> ev_statistiques;

	/**Points d'experience gagnes depuis la derniere montee de niveau*/
	Taux exp_gagne_der_niv;

	/**bonheur du pokemon (0 a 255)*/
	uchar bonheur;

	/**nom de la ball ayant capturé le pokémon. Si ce nom est vide, alors le pokémon vient d'une éclosion ou d'un don.*/
	QString ball_capture;

	/**Nombre de pas effectué en tête d'équipe.*/
	uchar nombre_pas_tete_equipe;

	/**numéro de capture du pokémon utilisé pour l'historique.*/
	Entier numero_capture;

	/**élément mis à jour lors de la création d'un pokémon d'utilisateur, lors du chargement d'une partie sauvegardée et mettant à jour un champ de la partie.*/
	//static Entier total_captures;

	void init_attaques(Donnees*);

	void init_alea_capacite_genre(Donnees*);

	void obtention();

public:

	/**Utilisé pour une QPair*/
	PokemonUtilisateur();

	/**Il faut construire un pokémon reçu par le don d'un personnage en fonction du nom, du niveau, de la capacité et du genre.
@param _pokemon_donne pokémon donné à ajouter dans l'équipe.*/
	//PokemonUtilisateur(const QPair<QPair<QString,uchar>,QPair<QString,QString> >&);
	PokemonUtilisateur(PokemonSauvage*,Donnees*,const QString& ="");

	/**Construit un pokémon à partie d'un pokémon sauvage.
@param _pokemon_sauvage Pokémon sauvage à ajouter dans l'équipe ou la boîte.*/
	PokemonUtilisateur(const CreatureCombat&,Donnees*);

	/**Construit un pokémon à partir des données d'un fossile.
@param _fossile Fossile à fair revivre*/
	PokemonUtilisateur(Fossile*,Donnees*);

	/**Modelise l'eclosion d'un oeuf de pokemon. Un tirage aléatoire est éventuellement fait pour la capacité spéciale et pour le genre.
@param _oeuf*/
	PokemonUtilisateur(const OeufPokemon&,Donnees*);

	void deplacement(int,Donnees*);

	QStringList move_tutors(Donnees*);

	bool attaque_deja_connue(const QString&)const;

	QList<QPair<QString,QPair<uchar,uchar> > > attaques_apprises()const;

	QString apprendre_attaque(const QString&,uchar,Donnees*);

	QString n_pk()const;

	uchar niv_pk()const;

	QString genre_pk()const;

	QString capacite_pk()const;

	QString& objet();

	QString objet()const;

	QString& pseudo_pk();

	QString pseudo_pk()const;

	QString ball_capt()const;

	QString& ball_capt();

	uchar bonheur_pk()const;

	void affecter_bonheur_pk(uchar);

	uchar pas_tete_equipe()const;

	/**Fait evoluer un pokemon
@param _indice indice de l'évolution*/
	void evoluer(const QString&,Donnees*);

	Taux pv_rest()const;

	Taux pv_max(Donnees*)const;

	/**Soigne totalement le pokemon (points de vie, statut, points de pouvoir)*/
	void soin_total(Donnees*);

	QString statut_pk()const;

	void soin_statut();

	void soin_pv(FichePokemon*);

	Taux soin_pv(SoinPVStatut*,Donnees*);

	Taux soin_pv(SoinPV*,Donnees*);

	Taux soin_pv(const Taux&,const QPair<uchar,uchar>&,Donnees*);

	void soin_pv_baie(const Taux&,Donnees*,Taux&);

	void soin_pp_baie(uchar,const QString&,uchar&);

	uchar soin_pp(const QString&,uchar);

	uchar soin_pp(const QString&);

	QStringList soin_pp(uchar);

	HashMap<QString,uchar> soin_pp();

	bool gain_pp_max(const QString&,uchar,uchar);

	//TODO soin_pp

	Taux exp_gagne()const;

	void tmp_exp_gagne_der_niv(Donnees*);
	/**
@param _pierre_evo Pierre évolutive à indiquer pour dire si l'évolution est possible ou non avec.
@return le nom du pokémon si la pierre évolutive n'est pas compatible avec le pokémon.
le nom de l'évolution du pokémon sinon.*/
	QString peut_evoluer(const QString&,Donnees*)const;

	/**met à jour les attributs ev_statistiques, exp_gagne_der_niv, capture_luxe_ball, niveau, capacite, nom_objet, pv_restants, statut
@param _pokemon pokémon d'utilisateur à utiliser pour la sauvegarde de parties.*/
	//void affecterCreatureCombat(const CreatureCombat&);

	/**met à jour les attributs attaques, ev_statistiques, exp_gagne_der_niv, capture_luxe_ball, niveau, capacite, nom_objet, pv_restants, statut, nom, pseudo
@param _pokemon pokemon de combat à utiliser pour la fin d'un combat.*/
	void finCombat(const CreatureCombat&);

	HashMap<QString,uchar> iv_stat()const;

	HashMap<QString,uchar> ev_stat()const;

	uchar gain_ev(const QString&,uchar,const QPair<uchar,uchar>&,uchar,Donnees*);

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const PokemonUtilisateur&);
Flux & operator >>(Flux&,PokemonUtilisateur&);

#endif


