#ifndef CREATURECOMBAT_H
#define CREATURECOMBAT_H
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/math/taux.h"
#include "serialisable/combat/combattant.h"
#include "math/montecarlo/montecarlonombre.h"
#include <QString>
#include <QStringList>
class PokemonUtilisateur;
class PokemonDresse;
class PokemonSauvage;
class Donnees;
class Baie;
class Soin;
class FichePokemon;
class Objet;
class FicheCapacite;
class Evolution;
struct TransfertRelais;
/***/
class CreatureCombat{

	/***/
	QString nom;

	/***/
	QString nom_act;

	/***/
	QString pseudo;

	/***/
	QString genre;

	/**ensemble des types actuels du pokemon.*/
	QStringList types;

	/**statistiques de base du combattant.*/
	HashMap<QString,Taux> statistiques_combat;

	HashMap<QString,QString> statistiques_valeurs;

	/***/
	HashMap<QString,uchar> ev_statistiques;

	/***/
	HashMap<QString,uchar> iv_statistiques;

	/***/
	Taux exp_gagnee_depuis_der_niveau;

	/***/
	uchar bonheur;

	/***/
	uchar ordre;

	/***/
	QString ball_capture;

	/**Capacité du pokémon au début du combat et qui remet à jour capacite_act à la valeur de capacite lors d'un switch.
Cette valeur ne peut être changée que par une évolution du pokémon.*/
	QString capacite;

	/***/
	QString capacite_act;

	/***/
	uchar niveau;

	/**est vrai <=> le pokémon n'a pas été switché de force.*/
	bool non_switch_force;

	/**est vrai <=> le pokémon a joué, c'est à dire a utilisé son attaque (réussie ou non), ou a switché (mis KO par Poursuite lancée avant ou non).*/
	bool a_joue;

	/***/
	QString nom_objet;

	/***/
	Taux masse;

	/***/
	QString statut;

	/***/
	Taux pv_restants;

	/***/
	QList<QPair<QString,QPair<uchar,uchar> > > attaques;

	/***/
	QList<QPair<QString,QPair<uchar,uchar> > > attaques_act;

	/***/
	HashMap<QString,qint8> boosts_statistiques;

	uchar boost_cc;

	/***/
	HashMap<Combattant,HashMap<QPair<QString,QString>,Taux> > table_types;

	/**attaque lancée avant l'attaque choisie.*/
	QString der_attaque_lance;

	/***/
	QString der_attaque_reussi;

	/**vrai si et seulement si l'attaque venant d'etre lancee est reussie.*/
	bool att_reussi;

	/***/
	uchar nb_tours_terrain;

	/***/
	uchar nb_tours_poison_grave;

	/**nombre de lancers des attaques*/
	HashMap<QString,int> nb_lancers_attaques;

	/***/
	QPair<uchar,bool> confusion;

	/***/
	Taux clone;

	/***/
	bool prepa_tour;

	/***/
	bool disparait;

	/***/
	bool nec_recharg;

	/***/
	uchar nb_tours_sommeil_non_repos;

	/**en fonction de action_choisie
	si action_choisie==SOIN alors
		attaque_choisie prend la valeur d'un objet de soin y compris les baies
	sinon si action_choisie==SWITCH alors
		attaque_choisie ne sert à rien
	sinon si action_choisie==ATTAQUE alors
		attaque_choisie prend la valeur de l'attaque choisie parmi les attaques actuelles du pokémon
	sinon
		attaque_choisie ne sert à rien
	fin
	*/
	QString attaque_choisie;

	/**SOIN,SWITCH,ATTAQUE*/
	QString action_choisie;

	/**
	ENCORE
	ENTRAVE
	clé: pair attaque du lanceur-cible
valeur: triplet attaque de la cible-nombre de tours-activité de l'attaque du lanceur.*/
	HashMap<QPair<QString,Combattant>,QPair<QString,QPair<bool,uchar> > > attaques_sur_combat_att;

	/**par defaut 1*/
	uchar coeff_roulade_ball_glace;

	/** VOL_MAGNETIK
	LEVIKINESIE subi
	REPOS
	EMBARGO subi
	ANTI_SOIN subi
	AIR_VEINARD
	PROVOC subi
	BAILLE subi
	BROUHAHA
	ROULADE
	BALL_GLACE
	MANIA
	COLERE
	DANSE_FLEUR
	*/
	HashMap<QString,QPair<uchar,bool> > nb_tours_effets_attaques;

	/***/
	QPair<uchar,QPair<Taux,bool> > patience;

	/**non subi*/
	HashMap<QPair<Combattant,QString>,QPair<bool,uchar> > attaques_piegeantes;

	/**non subi*/
	HashMap<Combattant,QStringList> attaques_possessif;

	/**
	AMOUR subi
	ANTI_FUITE
	CAUCHEMAR
	VERROUILLAGE
	LIRE_ESPRIT
	contient amoureux, anti_fuite, cauchemar, verrouillage, lire_esprit.*/
	HashMap<QString,HashMap<Combattant,bool> > relations_comb;

	/**premier 1:cumul des dégâts physiques
premier 2:cumul des dégâts spéciaux
second:dernière attaque ayant touché ce combattant*/
	QPair<QPair<Taux,Taux>,QString> derniere_attaque_subie;

	/***/
	uchar nb_succes_abris;

	/**gain d'expérience contre des adversaires pendant ce combat.*/
	Taux gain_exper;

	/**
	CLAIRVOYANCE subi
	OEIL_MIRACLE subi
	FLAIR subi
	LILLIPUT
	ANTI_AIR subi
	MAUDIT subi
	VAMPIGRAINE subi
	MORPHING
	RACINES
	COUP_D_MAIN
	MOI_D_ABORD
	RANCUNE
	PRLV_DESTIN
	ANNEAU_HYDRO
	TOURMENTE subi
	DETREMPAGE subi*/
	HashMap<QString,bool> attaques_actives;

	/**liste des pairs equipe, position de combat*/
	QList<QPair<uchar,uchar> > cibles_choisies;

	/**remplacant pour un switch demandé ou un KO subi.*/
	Combattant envoye;

	/***/
	bool peur;

	/**par vol magnetik,...*/
	HashMap<QString,bool> immu_attaques_types;

	/**lors de levitation,...*/
	HashMap<QString,Taux> coeff_att_types_subies;

	/**lors de tourniquet, ...*/
	HashMap<QString,Taux> coeff_att_types_subies_2;

	/*lors de chargeur,...**/
	HashMap<QString,Taux> coeff_att_types_lancees;

	/***/
	bool vient_de_perdre_objet;

	/***/
	QPair<QString,uchar> copie;

	/***/
	int nb_repet_att_succ;

	/**vrai <=> touché par une attaque feu et la capacité spéciale est torche.*/
	bool torche;

	/**premier: indicateur d'utilisation
deuxième: le lanceur de l'attaque possédait VOL avant l'utilisation*/
	QPair<bool,bool> atterrissage_lance;

	/**vrai <=> le combattant ne possédait que le type VOL avant l'utilisation de l'attaque atterrissage.*/
	bool pur_vol;

	/***/
	//bool astuce_force_apres_zone_etrange;

	/**objets utilisables en combat: soin et baie*/
	HashMap<QString,QList<QPair<uchar,Taux> > > objets;

	/***/
	bool utilise_baie;

	/***/
	QString der_objet_ut;

	void init_creature(Donnees*);

	void init_table_eff(const QList<Combattant>&,Donnees*);

	QString type_attaque_lanceur_2(const QPair<QPair<QString,uchar>,QPair<bool,bool> >&,const QString&,bool,Donnees*)const;

public:

	/**Ce constructeur ne sert qu'à sérialiser les données.*/
	CreatureCombat();

	/**Permet d'utiliser l'affectation
@param _copie copie du pokémon*/
	//CreatureCombat(const CreatureCombat&);

	/**Ce constructeur n'est appelé qu'au début d'un combat ou lors d'un ajout de combattant dans l'équipe par évolution (cas Munja)
@param _pokemon Pokémon à utiliser venant de l'utilisateur pour en créer un combattant.*/
	CreatureCombat(const PokemonUtilisateur&,Donnees *_d);

	/**Ce constructeur n'est appelé qu'au début d'un combat.
@param _pokemon pokémon du dresseur à en faire un combattant.*/
	CreatureCombat(PokemonDresse*,Donnees *_d);

	/**Ce constructeur n'est appelé qu'au début d'un combat.
@param _pokemon Pokemon sauvage à utiliser pour en faire un combattant.*/
	CreatureCombat(PokemonSauvage*,Donnees *_d);

	void transfer_relais(const TransfertRelais&);

	TransfertRelais relais()const;

	//void reinit_coeff_types_att(Donnees*);

	void maj_coeff_types_att_subie(Donnees*);

	void init_creature(const QList<Combattant>&,const HashMap<QString,QList<QPair<uchar,Taux> > >&,Donnees*);

	bool& non_switch_force_pk();

	bool& a_joue_pk();

	/**En cas d'évolution, il faut modifier le nom du pokémon.
@return l'adresse du nom du pokémon*/
	QString nom_pk()const;

	QString nom_pk_act()const;

	QString pseudo_pk()const;

	/**Le surnom est indéfiniment modifiable.
@return L'adresse du surnom du pokémon.
Par défaut le surnom vaut le nom du pokémon.*/
	QString& pseudo_pk();

	/**le genre ne peut être modifié que si morphing est utilisé.
@return le genre du pokemon*/
	QString genre_pk()const;

	/**Une attaque comme morphing, adaptation, change_type, ou une capacité comme météo,
peuvent changer l'ensemble des types du pokémon
@return l'adresse de la liste des chaînes de caractères représentant le type de pokémon.*/
	QStringList& types_pk();

	QStringList types_pk()const;

	QString& ball_capt();

	QString ball_capt()const;

	void morphing(const CreatureCombat&,Donnees*);

	Taux vitesse(bool,bool,bool,const QPair<QPair<QString,uchar>,QPair<bool,bool> >&,Donnees*)const;

	void echanger_statistiques(const QString&,const QString&);

	Taux clone_pk()const;

	Taux& clone_pk();

	Taux pv_max()const;

	Taux statistique_globale(const QString&,uchar,uchar)const;

	Taux statistique_mod_globale(const QString&,uchar,uchar)const;

	/**Il faut juste récupérer la valeur d'une statistique donnée.
@param _nom_stat nom de la statistique à donner pour récupérer la valeur de la statistique
@return La valeur de la statistique dont le nom est passé en paramètre.*/
	Taux statistique(const QString&)const;

	/**Il faut modifier la valeur d'une statistique donnée sans chercher à récupérer l'attribut statistiques_combat.
@param _nom_stat nom de la statistique indiquant la statistique à modifier.
@param _valeur_stat Valeur à assigner pour la statistique.*/
	void mod_statistique(const QString&,const Taux&);

	uchar ev_mod(const QString&)const;

	uchar ev(const QString&)const;

	uchar iv_mod(const QString&)const;

	uchar iv(const QString&)const;

	/**Sert à la fin d'un combat.
@return L'attribut ev_statistiques*/
	HashMap<QString,uchar> ev_statistiques_pk()const;

	/**Les evs de combat servent à augmenter les statistiques de combat et à modifier les evs hors combat.
@param _nom_stat Le nom de la statistique à donner pour ajouter la valeur aux evs dans la  hashmap ev_statistiques
@param _valeur_ev La valeur d'incrément des evs.
Un pokémon ne peut pas perdre d'evs, il ne peut gagner que des evs.*/
	void gain_ev_statistique(const QString&,uchar,uchar);

	/**
@return L'expérience gagnée depuis la dernière montée de niveau.*/
	Taux exp_gagnee()const;

	/**L'expérience gagnée depuis la dernière montée de niveau "exp_gagnee_depuis_der_niveau" ne peut être qu'augmentée.
@param _val_exp expérience à donner pour le pokémon, qui incrémente exp_gagnee_depuis_der_niveau.*/
	void gain_exp(const Taux&);

	/**réinitialise la valeur de exp_gagnee_depuis_der_niveau à 0*/
	void reinit_gain_exp();

	/**Le bonheur est modifié par une montée de niveau ou un soin par une boisson spéciale.
@return l'adresse du bonheur*/
	uchar bonheur_pk()const;

	void maj_bonheur_niveau(bool,const QPair<uchar,uchar>&,Donnees*);

	void mettre_jour_pv_restants2(Donnees*,const Taux& =Taux((long long int)0));

	/**La capture par Luxe Ball ne peut pas être modifiée par la suite.*/
	bool luxe_ball()const;

	/**la capacité du pokémon ne pourra être modifiée que si le pokémon évolue.
@return la capacité initiale avant le combat.*/
	QString capacite_pk_ini()const;

	/**La capacité actuelle du pokémon est modifié si une attaque comme échange est utilisée ou si une capacité comme calque s'active.
@return l'adresse de capacite_act*/
	QString& capacite_pk_act();

	QString capacite_pk_act()const;

	FicheCapacite *fiche_capacite(Donnees*)const;

	FichePokemon *fiche_pokemon(Donnees*)const;

	FichePokemon *fiche_pokemon_b(Donnees*)const;

	Objet *fiche_objet(Donnees*)const;

	/**
@return niveau du pokémon*/
	uchar niveau_pk()const;

	/**incrémente de 1, le niveau du pokémon*/
	void gain_niveau_pk();

	/**
@return l'expérience gagnée contre les adversaires actuels de ce combat "gain_exper".*/
	Taux gain_exp_combat()const;

	/**ajoute les points d'expérience contenus à la variable exp_gagnee_depuis_der_niveau et à la variable gain_exper
@param _exp_gagne expérience gagnée contre un adversaire.*/
	void gain_niveau_exp(const Taux&);

	/**réinitialise la valeur de gain_exper à 0*/
	void reinit_pts_exp();

	/**
@param _nom_att le nom de l'attaque dont on veut récupérer l'activité de l'attaque.
@return l'adresse de lilliput, de anti_air, de maudit, de tourmente, de vampigraine_subie, de morphing_actif, de astuce_force_actif, de precis_att_suiv, de racines_actif, de coup_d_main ou de detrempage en fonction du paramètre.*/
	bool& attaques_actives_ind(const QString&);

	bool attaques_actives_ind(const QString&)const;

	/**
@return l'adresse de ordre*/
	uchar& ordre_att();

	/**
@return l'adresse de nom_objet*/
	QString& objet();

	QString objet()const;

	bool peut_utiliser_objet(bool)const;

	HashMap<QString,QList<QPair<uchar,Taux> > >& objets_pk();

	HashMap<QString,QList<QPair<uchar,Taux> > > objets_pk()const;

	/**
@return l'adresse de masse*/
	Taux& masse_pk();

	Taux masse_pk()const;

	/**
@return l'adresse de statut*/
	QString& statut_pk();

	QString statut_pk()const;

	/**
@return l'adresse de pv_restants*/
	Taux& pv_restants_pk();

	Taux pv_restants_pk()const;

	void gain_bonheur(Soin*,Donnees*);

	void soin_pv(const Taux&,Taux&,Donnees*);

	Taux soin_tout_pv();

	void supprimer_pp(const QString&);

	void utiliser_pp(const QString&,uchar);

	uchar soin_pp(const QString&,uchar);

	QStringList soin_pp(uchar);

	uchar soin_pp(const QString&);

	HashMap<QString,uchar> soin_pp();

	/**@return l'éventuel porchain indice d'apprentissage d'attaque*/
	int attaque_apprise_niveau(int,Donnees*)const;

	QString type_attaque_lanceur(const QPair<QPair<QString,uchar>,QPair<bool,bool> >&,const QString&,bool,Donnees*)const;

	void apprendre_copie(const QString&);

	void reinit_copie();

	/**remplace definitivement gribouille si deja connue avant le combat*/
	void apprendre_attaque(const QString&,Donnees*);

	void apprendre_attaque(const QString&,int,Donnees*,QString&);

	QStringList noms_attaques_act()const;

	uchar nb_pp(const QString&)const;

	uchar nb_pp_max(const QString&)const;

	/**Cela permet de modifier les attaques lors d'apprentissage ou lors de l'utilisation de gribouille.
@return l'adresse de attaques*/
	QList<QPair<QString,QPair<uchar,uchar> > > attaques_pk()const;

	/**attaques_act est modifiée en cas de switch ou d'utilisation d'attaque comme copie ou comme morphing.
@return l'adresse de attaques_act*/
	QList<QPair<QString,QPair<uchar,uchar> > > attaques_act_pk()const;

	uchar& r_boost_cc();

	uchar r_boost_cc()const;

	QList<QString> statis_boost()const;

	/**
@param _nom_stat nom de la statistique à donner pour récupérer l'adresse de la valeur.
@return l'adresse de la valeur associée au nom de la statistique.*/
	qint8 boost(const QString&)const;

	void reinit_boost(const QString&,Donnees*);

	void var_boost(const QString&,qint8,Donnees*);

	void reinit_table_eff(Donnees*,int);

	void mise_a_jour_coeff_eff(const QString&,const HashMap<Combattant,QPair<uchar,uchar> >&,Donnees*,int);

	void ajouter_table_eff(const Combattant&,Donnees*);


	void reinit_coeff_types_att(Donnees *);

	HashMap<Combattant,HashMap<QPair<QString,QString>,Taux> > table()const;

	/**
@param _couple_types couple des types dont on veut récupérer l'efficacité du premier type sur le second.
@return l'adresse de la valeur associée au couple de types pour l'efficacité.*/
	Taux& table_eff(const Combattant&,const QPair<QString,QString>&);

	Taux table_eff(const Combattant&,const QPair<QString,QString>&)const;

	/**
@return l'adresse de der_attaque_lance*/
	QString& der_att_lancee();

	QString der_att_lancee()const;

	/**
@return l'adresse de der_attaque_reussi*/
	QString& der_att_reussie();

	QString der_att_reussie()const;

	/**
@return l'adresse de att_reussi*/
	bool& att_reussie();

	bool att_reussie()const;

	/**
@param _nom_attaque nom de l'attaque dont on veut modifier ou récupérer le nombre d'utilisations.
@return l'adresse de l'attribut nb_lancers_taillade ou de nb_stockages*/
	int& nb_lancer(const QString&);

	int nb_lancer(const QString&)const;

	/**incrémente de 1, le nombre de tours de combat*/
	void gain_nb_tours_terrain_pk();

	/**réinitialise le nombre de tours sur le terrain à 0*/
	void reinit_tours_terrain();

	/**
@return le nombre de tour passé sur le terrain depuis la dernière entrée sur le terrain.*/
	uchar nb_tours_terrain_pk()const;

	/**incrémente de 1 le nombre de tour sur le terrain du pokémon s'il est gravement empoisonné.*/
	void gain_nb_tours_poison_grave();

	/**réinitialise à 0 le nombre de tour sur le terrain où le pokémon subit un poison grave.*/
	void reinit_nb_tours_poison_grave();

	/**
@return le nombre de tours depuis la dernière entrée sur le terrain avec le poison grave.*/
	uchar nb_tours_poison_grave_pk()const;

	/**
@param _nom_attaque nom de l'attaque dont on veut récupérer l'adresse de la valeur avec le nombre de tours d'activité et l'activité en elle-même.
@return l'adresse de vol_magnetik, de levikinesie, de repos, de embargo_subi, de anti_soin, de air_veinard, de provoc, de baille, de brouhaha, de roulade ou de ball_glace*/
	QPair<uchar,bool>& attaques_actives_def(const QString&);

	QPair<uchar,bool> attaques_actives_def(const QString&)const;

	/**
@return l'adresse de confusion*/
	QPair<uchar,bool>& confusion_pk();

	QPair<uchar,bool> confusion_pk()const;

	/**
@return l'adresse de clone*/
	Taux& pv_clone();

	/**
@return l'adresse de prepa_tour*/
	bool& prepa_tour_pk();

	bool prepa_tour_pk()const;

	/**
@return l'adresse de disparait*/
	bool& disparition_pk();

	bool disparition_pk()const;

	/**
@return l'adresse de nec_recharg*/
	bool& nec_recharg_pk();

	bool nec_recharg_pk()const;

	/**
@return l'adresse de nb_tours_sommeil_non_repos*/
	uchar& sommeil_non_repos();

	uchar sommeil_non_repos()const;

	/**
@return l'adresse de attaque_choisie*/
	QString& att_choisie();

	QString att_choisie()const;

	/**
@return l'adresse de action_choisie*/
	QString& act_choisie();

	QString act_choisie()const;

	HashMap<QPair<QString,Combattant>,QPair<QString,QPair<bool,uchar> > > attaques_sur_cible()const;

	/**
@param _cible cible dont on veut récupérer l'activité de entrave, le nombre de tours et l'attaque entravée ou mise sous encore.
@return l'adresse de la valeur associée au paramètre _cible*/
	QPair<QString,QPair<bool,uchar> >& cible_atts(const QPair<QString,Combattant>&);

	QPair<QString,QPair<bool,uchar> > cible_atts(const QPair<QString,Combattant>&)const;

	/**
@return l'adresse de coeff_roulade_ball_glace*/
	uchar& coeff_roul_ballglace();

	uchar coeff_roul_ballglace()const;

	HashMap<QPair<Combattant,QString>,QPair<bool,uchar> > h_attaques_piegeantes()const;

	QList<QPair<Combattant,QString> > val_attaques_piegeantes()const;

	/**
@param _cible_attaque le couple cible,nom d'attaque dont on veut récupérer l'activité et le nombre de tours d'activité de l'attaque piégeante sur la cible
@return l'adresse de la valeur sur l'activité et le nombre de tours d'activité de l'attaque piégeante sur la cible*/
	QPair<bool,uchar>& att_pieg(const QPair<Combattant,QString>&);

	HashMap<Combattant,QStringList> possessif()const;
	/**
@param _cible La cible dont on veut récupérer les attaques qui lui sont interdites.
@return l'adresse de la valeur associée à la cible.*/
	QStringList& poss_pk(const Combattant&);

	HashMap<QString,HashMap<Combattant,bool> > relations()const;

	/**
@param _nom_attaque nom de l'attaque dont on veut récupérer la valeur.
@param _cible cible dont on veut connaître l'activité de l'attaque de la part du lanceur.
@return l'adresse de la valeur associée à _cible pour les hashmap amoureux, de anti_fuite, de cauchemar*/
	bool& att_active_cible(const QString&,const Combattant&);

	bool att_active_cible(const QString&,const Combattant&)const;

	/**
@return l'adresse de derniere_attaque_subie, qui contient le nom de l'attaque qu'a subi le combattant et la valeur des dégâts physiques et des dégâts spéciaux.*/
	QPair<QPair<Taux,Taux>,QString>& att_deg_subie();

	QPair<QPair<Taux,Taux>,QString> att_deg_subie()const;

	/**incrémente de 1 la valeur nb_succes_abris.*/
	void gain_nb_succes_abris();

	/**réinitialise à 0 nb_succes_abris*/
	void reinit_nb_succes_abris();

	/**
@return la valeur de nb_succes_abris*/
	uchar succes_abris()const;

	/**incrémente de 1, la valeur nb_utilisation_attaques*/
	void gain_nb_utilisation_attaques();

	/**Réinitialise à 0 la valeur nb_utilisation_attaques*/
	void reinit_nb_utilisation_attaques();

	/**
@return la valeur de nb_utilisation_attaques*/
	uchar util_attaques_succ()const;

	/**
@return l'adresse de cibles_choisies*/
	QList<QPair<uchar,uchar> >& cibles();

	QList<QPair<uchar,uchar> > cibles()const;

	/**
@return l'adresse de envoye*/
	Combattant& remplacant();

	Combattant remplacant()const;

	/**
@return l'adresse de peur*/
	bool& peur_pk();

	//void maj_coeff_att_types_subies(const QString&);

	void reinit_immu_attaques_type();

	bool immu_att_type(const QString&)const;

	bool& immu_att_type(const QString&);

	/**met à jour l'attribut coeff_att_types_subies.
@param _nom_type le nom du type dont on veut modifier le coefficient d'attaques subies.
@param _coeff nouvelle valeur du coefficient d'attaque subie*/
	//void maj_coeff_att_types_subies(const QString&,const Taux&);

	/**
@param _nom_type nom du type dont on veut récupérer le coefficient d'attaque subie.
@return le coefficient d'attaque subie associé à _nom_type.*/
	Taux coeff_att_type(const QString&)const;

	Taux& coeff_att_type(const QString&);

	Taux& r_coeff_att_types_lancees(const QString&);

	Taux r_coeff_att_types_lancees(const QString&)const;

	void maj_coeff_att_types_subies_2(const QString&);

	/**met à jour l'attribut coeff_att_types_subies.
@param _nom_type le nom du type dont on veut modifier le coefficient d'attaques subies.
@param _coeff nouvelle valeur du coefficient d'attaque subie*/
	void maj_coeff_att_types_subies_2(const QString&,const Taux&);

	/**
@param _nom_type nom du type dont on veut récupérer le coefficient d'attaque subie.
@return le coefficient d'attaque subie associé à _nom_type.*/
	Taux coeff_att_type_2(const QString&)const;

	/**
@return l'adresse de vient_de_perdre_objet*/
	bool& perte_objet();

	/**
@return l'adresse de copie*/
	QPair<QString,uchar>& att_copie();

	QPair<QString,uchar> att_copie()const;

	/**
@return l'adresse de torche*/
	bool& torche_pk();

	bool torche_pk()const;

	/**
@return l'adresse de atterrissage_lance*/
	QPair<bool,bool>& atterrissage();

	QPair<bool,bool> atterrissage()const;

	/**
@return l'adresse de pur_vol*/
	bool& pur_vol_atterr();

	/**
@return l'adresse de astuce_force_apres_zone_etrange*/
	//bool* ast_force_ap_z_etr();

	/**
@return l'adresse de patience*/
	QPair<uchar,QPair<Taux,bool> >& patience_pk();

	QPair<uchar,QPair<Taux,bool> > patience_pk()const;

	void evoluer(FichePokemon*,int,Donnees*);

	int existence_evolution_niveau(FichePokemon*,const QStringList&,int,const Taux&,Donnees*)const;

	/**Fait évoluer un pokémon en cours de combat si possible.
Incrémente _indice_evo de 1, dans tous les cas.
@param _indice_evo provient de ElementsCombat
@param _commentaire commentaire sur l'évolution.*/
	bool peut_evoluer(Evolution*,const QStringList&,const Taux&,Donnees*)const;

	void activer_baie(Baie*,Donnees*,Taux&);

	void activer_capacite(bool,Donnees*,const HashMap<Combattant,QPair<uchar,uchar> >&,bool,int,QPair<QPair<QString,uchar>,QPair<bool,bool> >&,Taux&);

	void desactiver_capacite(bool,const HashMap<Combattant,QPair<uchar,uchar> >&,int,Donnees*,QPair<QPair<QString,uchar>,QPair<bool,bool> >&);

	void annuler_patience();

	QStringList attaques_avec_pp()const;

	bool existence_attaques_lanceur_un_pp_max()const;

	Taux calcul_picots(int)const;

	Taux calcul_pieges_roche(Donnees*)const;
	/**
@return l'adresse de utilise_baie*/
	bool& utilisation_baie();

	bool bloque()const;

	/**met à jour les attributs pseudo, exp_gagnee_depuis_der_niveau,
bonheur, capture_luxe_ball, nom_objet, masse, statut, pv_restants, gain_exper
@param _pokemon pokémon d'utilisateur à utiliser lors du chargement d'une partie.*/
	//void affecterPkUt(const PokemonUtilisateur&);

	/**met à jour les attributs pseudo,
nom_objet, masse, statut, pv_restants
@param _pokemon pokémon dressé à utiliser pour le chargement.*/
	//void affecterPkDr(const PokemonDresse&);

	/**met à jour les attributs pseudo,
nom_objet, masse, statut, pv_restants
@param _pokemon le pokémon sauvage à utiliser pour le chargement*/
	//void affecterPkSa(const PokemonSauvage&);

	Taux calcul_degats_confusion(const QPair<QPair<QString,uchar>,QPair<bool,bool> >&,bool,uchar,Donnees*)const;

	bool tirage_confusion_nb_tour(Donnees*)const;

	QStringList types_conversion_2(const QString&,Donnees*)const;

	QString tirage_conversion_2(const QString&,Donnees*)const;

	static bool tirage_effet_continuer(const MonteCarloNombre&,const Taux&);

	//TODO static
	bool tirage_auto_inflige(Donnees*)const;

	QStringList types_adaptation(Donnees*)const;

	static QString calcul_pics_toxik(uchar);

	Taux calcul_avale()const;

	Taux calcul_degommage(Donnees*)const;

	static bool tirage_amoureux(Donnees*);

	static bool tirage_degel(Donnees*);

	static bool tirage_precision(const Taux&);

	static bool tirage_paralysie(Donnees*);

	static Taux tirage_excuse();

	static bool tirage_echange_vit_egales(Donnees*);

	static bool tirage_vive_griffe(Donnees*);

	static bool tirage_effet_fin_tour(const QString&,uint,Donnees*);

	static QString tirage_attaque(const QStringList&);

	QString tirage_attaques_blabladodo(const QStringList&)const;

	QString tirage_adaptation(const QStringList&)const;

	bool tirage_reveil(Donnees*)const;

	bool existe_boost_acupression(Donnees*)const;

	QString tirage_acupression(Donnees*)const;

	//nb_coups()
	MonteCarloNombre loi_repet_coups(const QString&,Donnees*)const;

	MonteCarloNombre loi_cc(const Taux&,Donnees*)const;

	static QString tirage_type(Donnees*);

	static MonteCarloNombre loi_puissance_cachee();

	MonteCarloNombre loi_puissance_cachee(Donnees*)const;

	static MonteCarloNombre loi_ampleur();

	MonteCarloNombre loi_ampleur(Donnees*)const;

	static MonteCarloNombre loi_random(uchar);

	/***/
	static Taux coeff_boost(qint8);

	/***/
	static Taux coeff_pre(qint8);

	/***/
	static Taux coeff_esq(qint8);

	QString& val_der_objet_ut();

	QString val_der_objet_ut()const;

	/**Permet d'utiliser l'affectation
@param _autre*/
	//CreatureCombat operator=(const CreatureCombat&);

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const CreatureCombat&);
Flux & operator >>(Flux&,CreatureCombat&);

#endif


