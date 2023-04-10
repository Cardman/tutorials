#ifndef FICHEATTAQUE_H
#define FICHEATTAQUE_H
#include "math/montecarlo/montecarlonombre.h"
#include <QString>
#include <QStringList>
class Effet;
class Donnees;
/***/
class FicheAttaque{

	/***/
	uchar pp;

	/***/
	QString type;

	/***/
	QString categorie;

	/**vrai <=> l'attaque est directe.
Contrairement à ce qu'on peut penser, une attaque directe n'est pas équivalent à une attaque physique.*/
	bool direct;

	/***/
	char priorite;

	/***/
	uchar precision;

	/***/
	QList<Effet*> effets;

	/***/
	bool fuite_adverse;

	/***/
	bool preparation_tour;

	/***/
	bool disparition_tour;

	/***/
	QStringList touche_attaq_pokemon_disparu;

	/***/
	MonteCarloNombre loi_proba_repetition_tour;

	/***/
	MonteCarloNombre loi_proba_repetition_coups;

	/***/
	bool blocage_lanceur;

	/***/
	QPair<int,int> min_max_mult_puissance;

	/***/
	bool ne_peut_mettre_ko;

	/***/
	bool effet_echec;

	/***/
	bool effet_non_degats;

	/***/
	bool nec_sexe_oppos;

	/***/
	bool nec_cible_sommeil;

	/***/
	bool nec_lanceur_sommeil;

	/***/
	bool description_suppl;

	/**peut etre une cible, toutes les cibles adverses ou tous les autres combattants.
Sert surtour pour le combat multiple.*/
	QString qui;

	/**le premier booléen est vrai si et seulement l'attaque du lanceur (physique ou spéciale) est utilisée
	le deuxième booléen est vrai si et seulement la catégorie de l'attaque correspond à la statitistique à utiliser
	Ne sert que pour des attaques offensives*/
	QPair<bool,bool> stat_att;

	/**le premier booléen est vrai si et seulement la défense de la cible (physique ou spéciale) est utilisée
	le deuxième booléen est vrai si et seulement la catégorie de l'attaque correspond à la statitistique à utiliser
	Ne sert que pour des attaques offensives*/
	QPair<bool,bool> stat_def;

	/***/
	static QStringList init_descriptions_attaques_gener();

	/***/
	static QStringList _descriptions_attaques_gener_;

	/***/
	static HashMap<QString,QString> init_descriptions_attaques_particul();

	/***/
	static HashMap<QString,QString> _descriptions_attaques_particul_;

public:

	/**@param _lignes*/
	FicheAttaque(const QStringList&);

	/**@return la valeur de pp*/
	uchar pps()const;

	/**@return la valeur de type*/
	QString tp()const;

	/**@return la valeur de categorie*/
	QString cat()const;

	/**@return la valeur de direct*/
	bool dir()const;

	/**@return la valeur de priorite*/
	char prio()const;

	/**@return la valeur de precision*/
	uchar prec()const;

	/**@return la valeur de effets*/
	QList<Effet*> effs()const;

	/***/
	int puis()const;

	/**@return la valeur de fuite_adverse*/
	bool fuit()const;

	/**@return la valeur de preparation_tour*/
	bool prepa()const;

	/**@return la valeur de disparition_tour*/
	bool dispa()const;

	/**@return la valeur de touche_attaq_pokemon_disparu*/
	QStringList touch_pk_disp()const;

	/**@return la valeur de loi_proba_repetition_tour*/
	MonteCarloNombre loi_rep_tour()const;

	/**@return la valeur de loi_proba_repetition_coups*/
	MonteCarloNombre loi_rep_coup()const;

	/**@return la valeur de blocage_lanceur*/
	bool bloc_lan()const;

	/**@return la valeur de min_max_mult_puissance*/
	QPair<int,int> mult_puis()const;

	/**@return la valeur de ne_peut_mettre_ko*/
	bool pas_ko()const;

	/**@return la valeur de effet_echec*/
	bool eff_ech()const;

	/**@return la valeur de effet_non_degats*/
	bool eff_n_deg()const;

	/**@return la valeur de nec_sexe_oppos*/
	bool sex_opp()const;

	/**@return la valeur de nec_cible_sommeil*/
	bool cible_som()const;

	/**@return la valeur de nec_lanceur_sommeil*/
	bool lanc_som()const;

	/**@return la valeur de description_suppl*/
	bool descr_suppl()const;

	/**@return la valeur de qui*/
	QString qi()const;

	/**@return la valeur de stat_att*/
	QPair<bool,bool> st_atts()const;

	/**@return la valeur de stat_def*/
	QPair<bool,bool> st_def()const;

	bool ohko()const;

	/**Donne la description d'un objet.
	appelle les méthodes des effets de l'attaque
	@param _langue langue de destination*/
	QString description_part(const QString&,int,Donnees*)const;

	/**Donne la description d'un objet.
	appelle description_part
	@param _langue langue de destination*/
	QString description(const QString&,int,Donnees*)const;

	/***/
	~FicheAttaque();
};

#endif



