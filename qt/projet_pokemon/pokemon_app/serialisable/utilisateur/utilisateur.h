#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include "serialisable/pokemon/oeufpokemon.h"
#include "serialisable/pokemon/pokemonutilisateur.h"
#include "serialisable/utilisateur/inventaire.h"
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/math/entier.h"

class ElementsCombat;
/***/
class Utilisateur{

	/**nom du héros*/
	QString pseudo;

	/**sexe du héros*/
	QString sexe_heros;

	/**Ensemble des pokemon dans les oeufs presents dans l'equipe. (maximum 6)*/
	QList<QPair<uchar,OeufPokemon> > oeufs_equipe;

	/**equipe de l'utilisateur autre que les oeufs (maximum 6)*/
	QList<QPair<uchar,PokemonUtilisateur> > equipe;

	/**Ensemble des boites d'oeufs de pokemon (maximum 256 boites de 256 pokemon)*/
	QList<QList<QPair<uchar,OeufPokemon> > > boites_oeufs;

	/**Ensemble des boites contenant les pokemon (maximum 256 boites de 256 pokemon)*/
	QList<QList<QPair<uchar,PokemonUtilisateur> > > boites;

	/**Inventaire des objets de l'utilisateur.*/
	Inventaire inventaire;

	/**Ensemble des pokemon attrapes.*/
	HashMap<QString,bool> pokemon_attrapes;

	/***/
	Entier argent;

	/***/
	bool repousse_actif;

	/***/
	int pas_restants_repousse;

	/**Nombre de pas effectués depuis le dernier accouplement.*/
	//int pas_effectues_accoupl_pk;
public:

	Utilisateur();

	Utilisateur(const QString&,const QString&,Donnees*);

	void deplacement(int,Donnees*,QString&);

	/**
@return la valeur de pseudo*/
	QString nom()const;

	QStringList nom_pk_equipe()const;

	/**
@return la valeur de sexe*/
	QString sexe()const;

	/**Cette méthode incrémente le nombre de pas pour l'éclosion et pour chaque éclosion d'oeuf supprime l'élément dans oeufs_equipe et crée un élément dans equipe. Dans la pair QPair<uchar,OeufPokemon>, on garde l'entier pour la position dans l'equipe.
@param _nouveaux_nes paramètre modifiable qui va contenir d'éventuels nouveaux-nés*/
	void eclosion_oeuf(QStringList&,Donnees *_d);

	void echanger_objets(uchar,const QPair<uchar,uchar>&);

	void echanger_objets(const QPair<uchar,uchar>&,const QPair<uchar,uchar>&);

	void echanger_pokemons(const QPair<uchar,uchar>&,const QPair<uchar,uchar>&);

	void echanger_pokemons(uchar,const QPair<uchar,uchar>&,Donnees*);

	/**si l'equipe est de taille supérieure ou égale à 2 et que c'est un pokémon de l'équipe ou si l'equipe est de taille égale à 1 et que c'est un oeuf, alors cette méthode déplace l'élément chez l'utilisateur vers une boîte donnée pourvu qu'elle ait encore au moins une place.
@param _position_equipe l'indice de position du pokémon ou de l'oeuf à stocker dans les boites.
@param _indice_boite numéro de la boîte où le pokémon à stocker doit être placé.*/
	void placer_dans_boite(uchar,const QPair<uchar,uchar>&,Donnees*);

	/**si l'équipe possède une place, alors cette méthode déplace l'élément vers equipe ou oeufs_equipe.
@param _boite_place position exacte du pokémon à retirer.*/
	void retirer_de_boite(const QPair<uchar,uchar>&,uchar);

	void relacher_pokemon(const QPair<uchar,uchar>&,Donnees*);

	/**soigne totalement l'équipe de l'utilisateur à un centre pokémon. (PP,statuts,PV)*/
	void soin_equipe_ct_pk(Donnees*);

	Taux soin_baie(uchar,const QString&,Donnees*);

	uchar soin_baie_pp(uchar,const QString&,const QString&,Donnees*);

	/**soigne un pokémon de l'équipe, en utilisant une partie de la potion (si elle n'est pas max). Cette méthode ne fait rien si les pv sont pleins.
@param _indice_pk indice du pokémon qui doit être soigné par des objets de soins (potions)
@param _nom_objet nom de l'objet qui soigne les pv du pokémon*/
	void soin_pv_pk(uchar,const QString&,uchar,Donnees*);

	/**si _nom_attaque est vide alors toutes les attaques du pokémon sont soignées avec des restes de pp, sinon seule l'attaque concernée est soignée.
@param _indice_pk indice du pokémon à soigner les pp de l'attaque passée en paramètre ou de toutes les attaques.
@param _nom_objet nom de l'objet soignant les pp du pokémon
@param _nom_attaque nom de l'attaque si une seule attaque est soignée, sinon toutes les attaques sont soignées.*/
	void soin_pp_pk(uchar,const QString&,Donnees*,const QString& _nom_attaque="");

	void gain_pp_max(uchar,const QString& _attaque,const QString&,Donnees *_d);

	/**Cette méthode soigne un pokémon de l'équipe de l'utilisateur, elle ne fait rien si le pokémon ne peut être soigné (statut OK, incompatibilité avec le statut.)
@param _indice_equipe indice du pokémonn à soigner le statut.
@param _nom_objet nom de l'objet à utiliser pour guérir le statut du pokémon.*/
	void soin_statut(uchar,const QString&,Donnees*);

	/**Cette méthode booste la statitistique d'un pokémon en donnant une partie des ev à ce pokémon.
@param _indice indice du pokémon, dont on veut augmenter les ev d'une statistique.
@param _nom_objet nom de l'objet à utiliser pour augmenter les ev du pokémon.*/
	void boost_statistique(uchar,const QString&,Donnees*);

	/**Cette méthode ne fait rien s'il n'y a plus de place dans l'équipe et s'il n'y a plus de place dans les boîtes.
Dans le cas, où cette méthode fait quelque chose, un nouveau pokémon est ajouté dans l'équipe ou dans une boîte.
@param _nom_fossile nom du fossile qui doit revivre.*/
	void faire_vivre_fossile(const QString&,uchar _max_eq,Donnees *_d,QString& _com);

	void echanger_objet_equipe(uchar,uchar,Donnees*);

	void retirer_objet(QPair<uchar,uchar>,bool,QString&,Donnees *_d);

	void retirer_objet(uchar,bool,QString&,Donnees *_d);

	void attacher_objet(uchar,const QString&);

	QStringList move_tutors(uchar,Donnees*)const;

	bool peut_apprendre_ct(uchar,uchar,Donnees*)const;

	bool peut_apprendre_cs(uchar,uchar,Donnees*)const;

	/**Avant l'appel de cette méthode, il faut interroger l'utilisateur, dans le cas où il faut supprimer une attaque pour en apprendre une autre, pour avoir la confirmation.
_indice_attaque est l'indice de l'attaque à supprimer si cet indice existe, sinon l'attaque à apprendre se placera à la fin.
l'attaque pouvant être apprises fait partie des ct, cs, move tutors
	Cette methode suppose que l'indice du pokemon existe
@param _indice indice du pokémon devant apprendre l'attaque.
@param _indice_attaque indice de l'attaque à supprimer si cet indice existe.
@param _nom_attaque nom de l'attaque devant être apprise par le pokémon*/
	void apprendre_attaque(uchar,uchar,const QString&,QString&,Donnees*);

	/**Cette méthode ne fait rien s'il n'y a plus de places dans l'équipe et s'il n'y a plus de places dans les boîtes.
@param _pokemon_donne caracteristiques du pokemon donné*/
	bool recevoir_pokemon(PokemonSauvage*,uchar,Donnees*,QString&);

	/**Place un objet dans l'inventaire sauf s'il y en a 255.
utilise QObjet::inherits
Cette méthode est appelé avant de modifier les objets ramassés de la classe Partie.
@param _nom_objet nom de l'objet à ramasser et à placer dans l'inventaire.*/
	void ramasser_objet(const QString&,Donnees*);

	/**A la différence de ramasser_objet, cette méthode diminue la quantité d'argent.
@param _nom_objet nom de l'objet à acheter*/
	void achat_objet(const QString&,uchar,Donnees*);

	/**Cette méthode permet de vendre des objets (achetables) pour gagner des l'argent.
@param _nom_objet nom de l'objet à vendre
@param _indice indice de la liste d'objets consommés de même nom.*/
	void vente_objet(const QString&,uchar,uchar,Donnees*);

	void achat_ct(uchar,uchar);

	void vente_ct(uchar,uchar);

	void obtention_cs(uchar);

	void activer_repousse(const QString&,Donnees*);

	int pas_repousse()const;

	bool repous_act()const;

	/**Cette méthode met à jour à true, la valeur associé à _nom dans la hashmap pokemon_attrapes.
@param _nom nom du pokémon venant d'être obtenu.
@return l'ancienne valeur associée à _nom*/
	bool attrape_pk(const QString&);

	bool present_pk(const QString&)const;

	/**réinitialise le nombre de pas à 0, lorsque les pokémons en pension sont séparés.*/
	//void reinit_pas_reproduction();

	/**incrémente de 1, la valeur de pas_effectues_accoupl_pk.*/
	//void gain_pas_reproduction();

	/**
@return la valeur de pas_effectues_accoupl_pk.*/
	//int pas_reproduction()const;

	/**Cette méthode ne fait rien s'il y a incompatibilité entre la pierre et le pokémon.
@param _indice indice du pokémon à faire évoluer.
@param _nom_pierre nom de la pierre à utiliser pour l'évolution du pokémon.*/
	void evoluer_pk_pierre(uchar,const QString&,QString&,Donnees*);

	Entier val_argent()const;
	/**incrémente le gain d'argent après un combat
@param _gain Argent à ajouter pour l'utilisateur.*/
	void gain_argent_combat(const Entier&);

	/**Cette méthode met à jour l'équipe de l'utilisateur et les boîtes de l'utilisateur, par la méthode capture_pk_sa de ElementsCombat.

Cette restaure les objets perdus l'utilisateur pendant le combat.
@param _combat combat qui vient de se dérouler*/
	void affecterFinCombat(const ElementsCombat&,Donnees*);

	/**Cette méthode ajoute un pokémon au bout de l'équipe de l'utilisateur.
@param _pokemon_sauvage pokémon à intégrer directement dans l'équipe*/
	//void attraper_pk_sauvage(const QPair<uchar,PokemonUtilisateur>&);

	/**Cette méthode stocke un pokémon sauvage venant d'être capturé dans la première boîte possible.
@param _pokemon_sauvage pokémon sauvage à stocker dans les boîtes.
@return 256, si le pokémon a été ajouté dans l'équipe
	1023, si le pokémon n'a pas pu être ajouté dans l'équipe ou dans une boîte
	le premier indice de boîte, sinon
*/
	uint attraper_pk_sauvage(const CreatureCombat&,Donnees*,uchar);

	/**
@return la valeur de equipe.*/
	QList<QPair<uchar,PokemonUtilisateur> > equipe_ut()const;

	QList<QPair<uchar,PokemonUtilisateur> >& equipe_ut();

	void echanger_place(uchar,uchar);

	/**
@return la valeur de oeufs_equipe*/
	QList<QPair<uchar,OeufPokemon> > oeufs()const;

	QList<QPair<uchar,OeufPokemon> >& oeufs();

	/**
@param _indice_boite l'indice de la boîte de pokémons non oeufs à récupérer.
@return la liste de QList<QList<QPair<uchar,PokemonUtilisateur> > > à récupérer.*/
	QList<QPair<uchar,PokemonUtilisateur> >& boite(uchar);

	/**
@param _indice_boite_oeuf l'indice de la boîte d'oeufs à récupérer.
@return la liste de QList<QList<QPair<uchar,OeufPokemon> > > à récupérer*/
	QList<QPair<uchar,OeufPokemon> >& boite_oeuf(uchar);

	/**
@param _indice_boite l'indice de la boîte de pokémons non oeufs à récupérer.
@return la liste de QList<QList<QPair<uchar,PokemonUtilisateur> > > à récupérer.*/
	QList<QPair<uchar,PokemonUtilisateur> > boite(uchar)const;

	/**
@param _indice_boite_oeuf l'indice de la boîte d'oeufs à récupérer.
@return la liste de QList<QList<QPair<uchar,OeufPokemon> > > à récupérer*/
	QList<QPair<uchar,OeufPokemon> > boite_oeuf(uchar)const;

	/**
@return la valeur de inventaire*/
	Inventaire inv()const;

	Inventaire& inv();

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const Utilisateur&);
Flux & operator >>(Flux&,Utilisateur&);

#endif


