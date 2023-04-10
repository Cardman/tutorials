#ifndef BALL_H
#define BALL_H
#include "base_donnees/objets/objet.h"
#include "math/taux.h"

/***/
class Ball: public Objet{

	Q_OBJECT

	/***/
	Taux taux_fixe;

	/***/
	HashMap<QPair<Taux,Taux>,Taux> taux_niveaux;

	/***/
	HashMap<bool,Taux> taux_peche;

	/***/
	QPair<QStringList,Taux> taux_pierre_evo;

	/***/
	HashMap<bool,Taux> taux_genre;

	/***/
	HashMap<QPair<Taux,Taux>,Taux> taux_masse;

	/***/
	HashMap<QPair<Taux,Taux>,Taux> taux_vitesse;

	/***/
	HashMap<bool,Taux> taux_deja_capture;

	/***/
	HashMap<QPair<uchar,uchar>,Taux> taux_temps;

	/***/
	HashMap<QPair<uchar,uchar>,Taux> taux_niveau_adv;

	/***/
	QPair<QStringList,Taux> taux_types;

	/***/
	HashMap<QString,Taux> taux_lieu;

	/***/
	const static HashMap<QString,QString> _descriptions_balls_;

	/***/
	static HashMap<QString,QString> init_descriptions_balls();

public:

	/**Constructeur à utiliser
	@param _effets effets de l'objet
	@param _prix_achat le prix d'achat à affecter si la ball est achetable*/
	Ball(const QStringList&,int _prix_achat=0);

	/**Donne la description d'un objet.*/
	virtual QString description(int)const;

	/**@return la valeur de taux_fixe*/
	Taux tx_fix()const;

	/**@return la valeur de taux_niveaux*/
	HashMap<QPair<Taux,Taux>,Taux> tx_niv()const;

	/**@return la valeur de taux_peche*/
	HashMap<bool,Taux> tx_pec()const;

	/**@return la valeur de taux_pierre_evo*/
	QPair<QStringList,Taux> tx_pier_evo()const;

	/**@return la valeur de taux_genre*/
	HashMap<bool,Taux> tx_gen()const;

	/**@return la valeur de taux_masse*/
	HashMap<QPair<Taux,Taux>,Taux> tx_m()const;

	/**@return la valeur de taux_vitesse*/
	HashMap<QPair<Taux,Taux>,Taux> tx_v()const;

	/**@return la valeur de taux_deja_capture*/
	HashMap<bool,Taux> tx_capt()const;

	/**@return la valeur de taux_temps*/
	HashMap<QPair<uchar,uchar>,Taux> tx_tps()const;

	/**@return la valeur de taux_niveau_adv*/
	HashMap<QPair<uchar,uchar>,Taux> niv_adv()const;

	/**@return la valeur de taux_types*/
	QPair<QStringList,Taux> tx_types()const;

	/**@return la valeur de taux_lieu*/
	HashMap<QString,Taux> tx_lieu()const;

	//virtual QList<QStringList> elements(const QString&)const;
};
#endif



