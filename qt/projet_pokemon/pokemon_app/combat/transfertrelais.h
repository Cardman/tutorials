#ifndef TRANSFERTRELAIS_H
#define TRANSFERTRELAIS_H
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/math/taux.h"
#include "serialisable/combat/combattant.h"
#include <QString>

/***/
struct TransfertRelais{

	HashMap<QString,QString> statistiques_valeurs;

	/***/
	QString capacite_act;

	/***/
	HashMap<QString,qint8> boosts_statistiques;

	uchar boost_cc;

	/***/
	HashMap<Combattant,HashMap<QPair<QString,QString>,Taux> > table_types;

	/**nombre de lancers des attaques*/
	HashMap<QString,int> nb_lancers_attaques;

	/***/
	QPair<uchar,bool> confusion;

	/***/
	Taux clone;

	/**
	ENCORE
	ENTRAVE
	clé: pair attaque du lanceur-cible
valeur: triplet attaque de la cible-nombre de tours-activité de l'attaque du lanceur.*/
	HashMap<QPair<QString,Combattant>,QPair<QString,QPair<bool,uchar> > > attaques_sur_combat_att;

	/**par defaut 1*/
	uchar coeff_roulade_ball_glace;

	/**VOL_MAGNETIK
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
	ASTUCE_FORCE
	COUP_D_MAIN
	MOI_D_ABORD
	RANCUNE
	PRLV_DESTIN
	ANNEAU_HYDRO
	TOURMENTE subi
	DETREMPAGE subi*/
	HashMap<QString,bool> attaques_actives;

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
	QString der_objet_ut;
};
#endif

