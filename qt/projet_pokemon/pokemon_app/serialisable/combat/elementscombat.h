#ifndef ELEMENTSCOMBAT_H
#define ELEMENTSCOMBAT_H
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/combat/combattant.h"
#include "serialisable/combat/creaturecombat.h"
#include "serialisable/coordonnees/coordonnees.h"
#include "serialisable/difficulte/difficulte.h"
#include "serialisable/math/taux.h"
class Utilisateur;
class Dresseur;
class PokemonSauvage;
class Donnees;
class Baie;
class FichePokemon;
class Objet;
class FicheCapacite;
class Evolution;
class FicheAttaque;
class EffetStatistique;
class Partie;
class Coordonnees;
class Ball;
/***/
class ElementsCombat{

	/***/
	QString type_combat;

	QString type_environnement;

	/***/
	HashMap<Combattant,CreatureCombat> creatures_act;

	/**permet de récupérer le pokémon dans l'équipe à partir d'un pokémon de front.

Cet attribut est utilisé pendant le combat.

La position de front change pendant un combat (lors d'un switch, d'un KO), alors que la place dans l'équipe ne change pas pendant un combat.

La position de front vaut -1, si le pokemon n'est pas au front, une valeur supérieure ou égale à 0, indiquant la place par rapport à la gauche. (Ex: 0 si tout à gauche)*/
	HashMap<Combattant,QPair<uchar,uchar> > positions_places;

	HashMap<Combattant,QPair<uchar,uchar> > positions_places_bis;

	/**nom, nombre de tour, actif,, eternel*/
	QPair<QPair<QString,uchar>,QPair<bool,bool> > climat;

	/***/
	qint8 indice_pk;

	/***/
	qint8 indice_attaque;

	/***/
	qint8 indice_evolution;

	int indice_capture;

	/***/
	QString base_evolution;

	/**pour pouvoir mettre en place correctement l'ihm de combat au chargement d'une partie.*/
	uchar situation;

	bool a_evolue;

	/**cle: adversaire
valeur: pokemons de l'utilisateur l'ayant combattu.
les uchar sont des positions dans l'équipe.*/
	HashMap<uchar,QList<uchar> > combattants_contre_adv;

	/**Gains d'experience contre une liste d'adversaires mis ko pendant le meme tour*/
	HashMap<uchar,Taux> gain_exp_tmp;

	/***/
	QList<Combattant> numeros_front;

	/**objets attachables*/
	HashMap<QString,Entier> objets_utilisateur_perdus;

	/***/
	QString derniere_attaque_lancee;

	/**
	PROTECTION
	MUR_LUMIERE
	VENT_ARRIERE
	RUNE_PROTECT
	BRUME
	AIR_VEINARD
	ANTI_SOIN
	AIRE_EAU_FEU
	AIRE_EAU_HERBE
	AIRE_FEU_HERBE
	PICOTS
	PICS_TOXIKS
	PIEGE_DE_ROC

	clé: equipe et nom d'attaque
valeur: activité de l'attaque et nombre de tours effectués pour l'attaque.
comprend les combinaisons aires d'eau, feu, herbe.*/
	HashMap<uchar,HashMap<QString,QPair<uchar,bool> > > nb_tour_attaque_equipe;

	/***/
	QString derniere_attaque_reussie;

	/**coordonnées du dresseur (dans le cas d'un combat contre un dresseur) plus le nombre de rematch contre lui.*/
	QPair<Coordonnees,int> coords_adversaire;

	/***/
	//uchar appats_lances;

	/***/
	//uchar nb_safari_ball_possedes;

	/**Actions que choisit l'utilisateur pour tous les pokémons qu'ils possèdent. Chaque pokémon possède au plus une action. Dir qu'un pokémon n'a pas d'action, c'est dire que la chaîne de caractère (valeur) est vide.*/
	HashMap<uchar,QString> actions_choisies_ut;

	/***/
	QString commentaire_recent;

	/***/
	QStringList commentaires_combat;

	/**cle: position de lancer d'attaque
valeur: nombre de tours, activité depuis le dernier tour, activité depuis l'avant dernier tour.*/
	HashMap<QPair<uchar,uchar>,QPair<uchar,QPair<bool,bool> > > voeu;

	/***/
	HashMap<QPair<uchar,uchar>,QPair<uchar,bool> > soin_total;

	/**cle: nom de l'attaques, position de lancer d'attaque
valeur: dégâts, nombre de tours et position de la cible qui va recevoir l'attaque*/
	HashMap<QPair<QString,QPair<uchar,uchar> >,QPair<QPair<Taux,uchar>,QPair<uchar,uchar> > > prescience_carnar;

	/**maximum: 255*/
	uchar nb_tours_terrain;

	/***/
	HashMap<uchar,QPair<bool,bool> > vengeance_actif;

	/**nombre d'utilisations de chant_canon ou de echo dans le tour, par equipe.*/
	HashMap<QPair<QString,uchar>,uchar> nb_utilisation_attaques;

	/**contient les effets globaux du combat:
	gravite
	requiem
	distorsion
	zone_magique
	zone_etrange*/
	HashMap<QString,QPair<uchar,bool> > effets_globaux;

	/**multiplicité du combat
	1 pour simple
	2 pour double
...*/
	uchar multiplicite;

	/**nom de la ball utilisé et résultat de capture.*/
	QPair<QString,bool> capture;

	/***/
	HashMap<uchar,uchar> lanceur_par_ici;

	/***/
	HashMap<Combattant,Combattant> lanceur_saisie;

	int fuite;

	Taux var_argent;

	uchar ut;

	uchar adv;

	int arriere;

	Difficulte diff;

	Coordonnees coords_leg;
	//Inventaire inventaire;

	/**juste avant l'évolution d'un pokémon.*/
	CreatureCombat prochaine_evolution;
	
	void init_combat(Donnees*,const Utilisateur&);


public:

	enum STATISTIQUES{MINI,MAXI,ALEA,VAR,MOY};

	enum TypeInterface{CAPTURE_KO,REDESSIN_SCENE,VILLE_DEPART,DEBUT_LIGUE,SURNOM,APPRENDRE_ATT,EVOLUTION,NORMAL,SWITCH_PROPOSE,PAS_SWITCH,RIEN};

	/**constructeur permettant la sérialisation*/
	ElementsCombat();

	/**constructeur utilisé pour un combat avec un dresseur.
@param _utilisateur l'utilisateur pour le combat
@param _dresseur dresseur pour le combat*/
	ElementsCombat(const Utilisateur&,const Difficulte&,Dresseur*,Donnees*,int=-1);

	/**constructeur utilisé pour un combat contre un pokémon sauvage.
@param _utilisateur utilisateur pour le combat
@param _pokemon pokémon sauvage qui va combattre.*/
	ElementsCombat(const Utilisateur&,const Difficulte&,PokemonSauvage*,Donnees*);

	Coordonnees& maj_coords_leg();

	void init_type_env(const Coordonnees&,const Coordonnees&,bool,Donnees*);

	QString type_env()const;

	Taux argent()const;

	uchar adversaire(uchar)const;

	void reinit_constantes(const Partie&,Donnees*);

	/**constructeur par copie
@param _copie copie pour l'affectation*/
	//ElementsCombat(const ElementsCombat&);

	/**Retourne l'adresse de creatures_act
@return adresse de creatures_act pour pouvoir modifier à l'extérieur de la classe.*/
	HashMap<Combattant,CreatureCombat> creatures_combats()const;

	CreatureCombat& creature_combat(const Combattant&);

	void ajouter_combattant();

	/**On cherche les combattants qui ont pour position _position. L'ensemble retourné peut être vide s'il n'y a aucun combattant à cette position. Cet ensemble peut contenir plusieurs combattant s'il ne sont pas au front.
Cette méthode est utilisée pour récupérer la cible lors d'une attaque.
@param _position position dont on veut récupérer les combattants qui y sont placés.
@return L'ensemble des combattants ayant pour position _position.*/
	QList<Combattant> combattants_a_position(const QPair<uchar,uchar>&)const;

	/**
@param _pokemon pokémon dont on veut récupérer la position de front au combat.
@return l'adresse de la valeur associé à _pokemon dans la hashmap positions_places*/
	QPair<uchar,uchar> position(const Combattant&)const;

	/**attribut utilisé: actions_choisies_ut

@return l'adresse de l'attribut
actions_choisies_ut*/
	HashMap<uchar,QString>& actions_choisies();

	HashMap<uchar,QString> actions_choisies()const;

	int nb_fuite()const;

	/**
@return la valeur de type_combat*/
	QString type_cbt()const;

	void fin_cbt();

	/**
@return l'adresse de climat.*/
	QPair<QPair<QString,uchar>,QPair<bool,bool> > climat_gl()const;

	/**
@return l'adresse de indice_pk*/
	qint8& indice_pos_pk();

	/**
@return l'adresse de indice_attaque*/
	qint8& indice_pos_attaque();

	/**
@return l'adresse de indice_evolution*/
	qint8& indice_pos_evolution();

	int& indice_pos_boite();

	/**
@return l'adresse de base_evolution*/
	QString base_evo()const;

	/**
@return l'adresse de situation*/
	uchar& situation_cbt();

	HashMap<uchar,QList<uchar> > combattants_ut()const;

	/**
@param _adversaire position avant le combat du pokémon adverse.
@return l'adresse de la valeur associée à _adversaire dans la hashmap combattants_contre_adv*/
	QList<uchar> combattants_ut(uchar)const;

	/**met à jour la hashmap combattants_contre_adv, pour changement de valeur
@param _adversaire pokémon adverse dont on veut modifier la liste des combattants contre lui.
@param _liste_combattants liste des combattants à assigner avec la valeur _adversaire*/
	void maj_liste_cbts(uchar,const QList<uchar>&);

	/**
@return l'adresse de numeros_front*/
	QList<Combattant> fronts()const;

	/**
@return l'adresse de objets_utilisateur_perdus*/
	HashMap<QString,Entier> objets_ut_perdus()const;

	void stocker_dans_inventaire_perdu(const QString&);

	/**
@return l'adresse de derniere_attaque_lancee*/
	QString der_att_lancee()const;

	/**
@return l'adresse de derniere_attaque_reussie*/
	QString der_att_reussie()const;

	HashMap<uchar,HashMap<QString,QPair<uchar,bool> > > attaques_equipes()const;

	/**
@param _equipe equipe dont on veut récupérer les effets sur plusieurs tours.
@param _nom_attaque nom de l'attaque, dont on veut récupérer l'activité et le nombre de tours écoulé.
@return l'adresse de la valeur associée aux paramètres dans la hashmap nb_tour_attaque_equipe*/
	QPair<uchar,bool> attaque_equipe(uchar,const QString&)const;

	QPair<uchar,bool>& attaque_equipe(uchar,const QString&);

	HashMap<QString,QPair<uchar,bool> > attaques_globales()const;

	QPair<uchar,bool> effet_global(const QString& _effet)const;

	/**si la première clé _equipe est contenue dans la hashmap nb_tour_attaque_equipe, alors on récupère la valeur qui est contenue, sinon on crée une hashmap de type HashMap<QString,QPair<uchar,bool> >. Dans tous les cas il faut mettre à jour la hashmap nb_tour_attaque_equipe.
@param _equipe Equipe dont on veut modifier l'ensemble des attaques actives.
@param _nom_attaque l'attaque dont on veut modifier les effets.
@param _activite l'activité à modifier pour l'équipe.*/
	//void maj_attaque_equipe(uchar,const QString&,const QPair<uchar,bool>&);

	/**utilisé pour le chargement et pour la fin de combat
@return la valeur de coords_adversaire*/
	QPair<Coordonnees,int> adversaire()const;

	/**
@return l'adresse de voeu*/
	HashMap<QPair<uchar,uchar>,QPair<uchar,QPair<bool,bool> > > voeu_gl()const;

	/**
@return l'adresse de soin_total*/
	HashMap<QPair<uchar,uchar>,QPair<uchar,bool> > soin_total_gl()const;

	/**
@return l'adresse de prescience_carnar*/
	HashMap<QPair<QString,QPair<uchar,uchar> >,QPair<QPair<Taux,uchar>,QPair<uchar,uchar> > > attaques_prepa_tours()const;

	/**incrémente de 1, la valeur de nb_tours_terrain*/
	void gain_nb_tours_terrain();

	/**
@return la valeur de nb_tours_terrain*/
	uchar nb_tours_terrain_gl()const;

	/**
@return l'adresse de vengeance_actif*/
	HashMap<uchar,QPair<bool,bool> > vengeance()const;

	/**
@return l'adresse de nb_utilisation_attaques*/
	HashMap<QPair<QString,uchar>,uchar> nb_util_attaq()const;

	/**
@return l'adresse de commentaire*/
	QString& maj_commentaire_tour();

	/**
@return la valeur de multiplicite*/
	uchar mult_cbt()const;

	/**
@return la valeur de capture*/
	QPair<QString,bool> capture_pk_sa()const;

	/**@return vrai <=> il existe un pokemon au front avec une capacite annulant les effets du climat*/
	bool existence_anti_climat_actif(Donnees *_d)const;

	bool existence_adversaire_non_ko(const QList<Combattant>&,const Combattant&)const;

	bool existence_cible_non_ko(const Combattant&,FicheAttaque*)const;

	bool existence_cible_dort(const Combattant&,Donnees*)const;

	bool existence_combattant_ut_non_ko_contre_1_adv()const;

	bool existence_ut_non_ko()const;

	bool existence_ut_non_ko_contre_1_adv()const;

	bool existence_entrave(const Combattant&,const QString&)const;

	QPair<bool,bool> existence_eq_ko()const;

	bool existence_attaque_meme_eq(const Combattant&,const QString&)const;

	bool existence_partenaire_non_ko(const Combattant&)const;

	bool existence_pk_arriere_non_ko(const Combattant&)const;

	bool existence_partenaire_front(const Combattant&)const;

	QPair<QString,uchar> existence_pk_eq_lumargile_non_embargo(uchar,Donnees*)const;

	bool existence_pk_eq_climat_non_embargo(Donnees*)const;

	bool existe_pk_ut_rempl()const;

	Combattant tirage_envoi(uchar)const;

	Combattant tirage_front_adv(uchar)const;

	static bool tirage_capture(const Taux&,uchar);

	static bool tirage_fuite(const Taux&);

	bool existe_pk_avec_statut_non_ko(uchar)const;

	bool cible_de_a_la_queue(const Combattant&,Donnees*)const;

	QList<Combattant> ordre_non_joue(Donnees *_d,bool)const;

	Combattant chercher_cible_apres_vous(const Combattant&,Donnees*)const;

	QStringList calcul_attaques_equipe(const Combattant&)const;

	bool perdre_dresseur()const;

	bool gagner_dresseur()const;

	bool match_nul()const;

	QList<Combattant> cibles_possible_lanceur_bis(const Combattant& _lanceur,const QStringList& _attaques,Donnees *_d)const;

	QList<Combattant> cibles_possible_lanceur(const Combattant& _lanceur,const QStringList& _attaques,Donnees *_d)const;

	QList<Combattant> cibles_possible_lanceur(const Combattant&,FicheAttaque*)const;

	QList<Combattant> cibles_lanceur(const Combattant&,Donnees*)const;

	QList<Combattant> cibles_lanceur(const Combattant&,FicheAttaque*)const;

	QList<Combattant> combattants_adjacents(const Combattant&,bool,bool)const;


	QList<Combattant> trier_ordre_non_joue(bool,Donnees*)const;

	void calcul_experience_ev(const QList<Combattant>&,const Combattant&,Donnees*,uchar,uchar);

	int nb_pk_ut_multiexp_niv(Donnees*,uchar)const;

	Taux calcul_coeff_fuite(Donnees*)const;

	bool protege_contre_amour(const CreatureCombat&,const CreatureCombat&,const QString&,FicheCapacite*,FicheCapacite*)const;

	bool ne_peut_pas_dormir(const CreatureCombat&,Donnees*)const;

	QString valeur_climat()const;

	//QStringList ens_statuts_recev_par(const CreatureCombat&,uchar,bool,EffetStatut*,Donnees*)const;

	bool traiter_reussite_seul_effet_statut(const CreatureCombat&,FicheCapacite*,const CreatureCombat&,const QString&,FicheCapacite*,uchar,const QString&,const QString&,bool,const QStringList&,bool,Donnees*)const;

	bool traiter_reussite_seul_effet_statut(const CreatureCombat&,FicheCapacite*,uchar,const QString&,bool,Donnees*,bool=false,bool=false)const;

	QList<Combattant> choix_ia_envoi_remplacement()const;

	QStringList traiter_reussite_effet_statistiques(const CreatureCombat&,FicheCapacite*,uchar,FicheCapacite*,const QString&,FicheAttaque*,Donnees*)const;

	bool traiter_reussite_effet_statistique(const CreatureCombat&,FicheCapacite*,uchar,FicheCapacite*,const QString&,const QString&,qint8,bool,Donnees*)const;

	void intimidation(FicheCapacite*,uchar,Donnees*);

	void reinit(const Combattant&,CreatureCombat&,Donnees*);

	void mise_a_ko(const Combattant&,CreatureCombat&,Donnees*);

	void retrait(const Combattant&,CreatureCombat&,Donnees*);

	void traiter_effet_statut(const Combattant&,CreatureCombat&,uchar,CreatureCombat&,uchar,const MonteCarlo<QString>&,const QString&,bool,Donnees*);

	void traiter_effet_statist(CreatureCombat&,CreatureCombat&,uchar,EffetStatistique*,bool,Donnees*);

	void ss_methode_envoi(const Combattant&,CreatureCombat&,bool,Donnees*);

	void envoi(const Combattant&,CreatureCombat&,bool,Donnees*,const Combattant& =Combattant(),bool=false);

	QPair<bool,bool> condition_reussite(const Combattant&,const CreatureCombat&,const Combattant&,const CreatureCombat&,const QString&,const QString&,Donnees*)const;

	Taux calcul_precision(const Combattant&,const CreatureCombat&,const QString&,FicheAttaque*,const Combattant&,const CreatureCombat&,uchar,bool&,bool&,Donnees*)const;

	Taux calcul_puissance(const QString&,FicheAttaque*,const Combattant&,const CreatureCombat&,const Combattant&,const CreatureCombat&,uchar,Donnees*)const;

	static QPair<Taux,Taux> esperance_carree_variance_prod(const QPair<Taux,Taux>&,const QPair<Taux,Taux>&);

	Taux calcul_degats(const QString&,FicheAttaque*,const QString&,const Combattant&,const CreatureCombat&,const Combattant&,const CreatureCombat&,const Taux&,uchar,bool&,bool&,bool&,Donnees*)const;

	Taux calcul_degats(const MonteCarloNombre&,const QString&,FicheAttaque*,const QString&,const Combattant&,const CreatureCombat&,const Combattant&,const CreatureCombat&,const Taux&,uchar,HashMap<Combattant,bool>&,HashMap<Combattant,bool>&,Donnees*,const Taux& =Taux(0))const;

	bool existe_anti_fuite(const Combattant&,const CreatureCombat&,Donnees*)const;

	HashMap<Combattant,HashMap<QString,QStringList> > actions_possibles(uchar,Donnees*)const;

	QPair<QString,HashMap<Combattant,QPair<QPair<QString,QString>,Combattant> > > jouable_utilisateur(Donnees*)const;

	HashMap<Combattant,QPair<QString,QPair<Combattant,Combattant> > > choix_ia_attaque(Donnees*)const;

	void tour_lanceur(const Combattant&,CreatureCombat&,Donnees*);

	void traiter_apres_degats(const QString& _att_lanc,const Combattant& _cb,CreatureCombat& _cible,const Combattant& _lc,CreatureCombat& _lanceur,const Taux& _degats,const Taux& _degats_2,Taux& _degats_clone,Taux& _pv_soignes,Taux& _degats_recul,const QString& _type_att,Donnees *_d);

	void effets_fin_tour(Donnees*);

	Taux calcul_coeff_capture(Ball*,bool,bool,const CreatureCombat&,Donnees*)const;

	bool cas_switch_force(const Combattant&,CreatureCombat&,const Combattant&,CreatureCombat&,Donnees*);

	uchar tour_combat(Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d);

	bool lancer(const Combattant&,CreatureCombat&,Donnees*);

	uchar traiter_apres_tour(Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d);

	uchar tentative_capture(const QString& _nom_ball,Ball *_ball,Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d);

	uchar apprentissage_attaque_plus_evo(const Utilisateur&,Donnees *_d);

	uchar traiter_apprentissage_attaque(uchar _type,const QString& _action,int _indice,Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d);

	//uchar traiter_apres_tour(Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d);

	uchar tentative_fuite(Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d);

	uchar traiter_remplacement(Utilisateur& _utilisateur,QList<uchar>& _ligues,uchar& _stade_ligue,HashMap<QPair<Coordonnees,int>,bool>& _dresseurs_battus,Donnees *_d);

	uchar fin_combat(Utilisateur&,QList<uchar>&,uchar&,HashMap<QPair<Coordonnees,int>,bool>&,Donnees*);

	uchar capturer(const QString&,Utilisateur&,Donnees*);

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const ElementsCombat&);
Flux & operator >>(Flux&,ElementsCombat&);

#endif


