#ifndef MONTECARLONOMBRE_H
#define MONTECARLONOMBRE_H
#include "math/montecarlo/montecarlo.h"
class Taux;

/**Classe modelisant un tirage de nombres entiers aleatoires*/
class MonteCarloNombre: public MonteCarlo<Taux>{
public:

	/**Constructeur permettant d'avoir une loi vide.*/
	MonteCarloNombre();

	/**Retourne l'esperance d'une loi de probabilite.*/
	Taux esperance()const;

	/**Retourne l'esperance d'une loi de probabilite en tenant compte du biais du reste.*/
	Taux esperance_reelle()const;

	/**Retourne la variance d'une loi de probabilite.*/
	Taux variance()const;

	/**Retourne la variance d'une loi de probabilite en tenant compte du biais du reste.*/
	Taux variance_reelle()const;

	/***/
	QPair<Taux,Taux> esperance_variance()const;

	/***/
	QPair<Taux,Taux> esperance_variance_reelles()const;

	/**Retourne le minimum de la loi de probabilite (soit le plus petit Xi)*/
	Taux minimum()const;

	/**Retourne le maximum de la loi de probabilite (soit le plus grand Xi)*/
	Taux maximum()const;

	/**Calcul une variance et une espérance d'un produit de variables aléatoires indépendantes.
@param _variance_var_alea Variance d'une variable aléatoire
//@param _esperance_car_var_alea Carré de l'espérance d'une variable aléatoire
@param _esperance_var_alea espérance d'une variable aléatoire
@return Le couple variance, carré de l'espérance d'un produit de variables aléatoires indépendantes.*/
	QPair<Taux,Taux> variance_esperance_indep(const Taux&,const Taux&)const;

	/**Calcul une variance et une espérance d'un produit de variables aléatoires indépendantes.
@param _variance_var_alea Variance d'une variable aléatoire
//@param _esperance_car_var_alea Carré de l'espérance d'une variable aléatoire
@param _esperance_var_alea espérance d'une variable aléatoire
@return Le couple variance, carré de l'espérance d'un produit de variables aléatoires indépendantes.*/
	QPair<Taux,Taux> variance_esperance_indep_reelles(const Taux&,const Taux&)const;

	MonteCarlo<bool> loi_sachant_sup(const Taux&)const;

	/***/
	virtual QString chaine()const;
};
#endif



