#ifndef TAUX_H
#define TAUX_H
#include "math/entier.h"

/**Fraction generalisee d'un nombre avec un numerateur et un denominateur.*/
class Taux{

	/**numerateur du nombre*/
	Entier numerateur;

	/**denominateur du nombre*/
	//Entier denominateur;
	EntierPositif denominateur;

	/**signe du nombre valant true si et seulement si le nombre est positif ou nul.*/
	//bool signe;

public:

	/***/
	Taux();

	/***/
	Taux(long long pnumerateur,bool psigne=true,long long pdenominateur=1);

	/***/
	Taux(long long pnumerateur,long long pdenominateur);//nombre positif

	/***/
	Taux(const Taux&);

	/***/
	Taux(const Entier& pnumerateur,bool psigne=true,const EntierPositif& pdenominateur=Entier(1));

	/***/
	Taux(const Entier& pnumerateur,const EntierPositif& pdenominateur);//nombre positif

	/***/
	static Taux parse_taux(const QString&);

	/***/
	void simplifier();

	/***/
	bool gsigne()const;

	/***/
	Entier gnumerateur()const;

	/***/
	EntierPositif gdenominateur()const;

	/***/
	Taux absolu()const;

	/***/
	Taux racine_abs(int)const;

	/***/
	Taux partie_decimale()const;

	/***/
	Entier partie_entiere()const;

	operator Entier();

	operator unsigned long long();

	/***/
	QString evaluer(int)const;

	/***/
	Taux& operator-=(const Taux&);

	/***/
	Taux& operator+=(const Taux&);

	/***/
	Taux& operator*=(const Taux&);

	/***/
	Taux& operator/=(const Taux&);

	/***/
	Taux operator^(const Entier&)const;

	/***/
	Taux inv()const;

	/***/
	Taux operator-()const;

	/***/
	bool estNul()const;

	/***/
	QString chaine()const;

	/***/
	Taux& operator=(const Taux&);

	/**@param chaine
	@param arguments
	@return une chane formatte*/
	//static QString formatter(const QString&,const QStringList&);

	/**Mthode de srialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Mthode de dsrialisation
	@param _in le flux d'entre*/
	virtual void deserialiser(Flux&);
};

	/***/
Taux operator-(const Taux&,const Taux&);

	/***/
Taux operator+(const Taux&,const Taux&);

	/***/
Taux operator*(const Taux&,const Taux&);

	/***/
Taux operator/(const Taux&,const Taux&);

	/***/
bool operator<(const Taux&,const Taux&);

	/***/
bool operator>(const Taux&,const Taux&);

	/***/
bool operator<=(const Taux&,const Taux&);

	/***/
bool operator>=(const Taux&,const Taux&);

	/***/
bool operator==(const Taux&,const Taux&);

	/***/
bool operator!=(const Taux&,const Taux&);

Flux & operator <<(Flux&,const Taux&);
Flux & operator >>(Flux&,Taux&);

#endif



