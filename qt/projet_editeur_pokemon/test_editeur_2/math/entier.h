#ifndef ENTIER_H
#define ENTIER_H
#include "math/entierpositif.h"

/**Entier avec un signe represente par un booleen vrai si et seulement si le nombre est positif ou nul.*/
class Entier: public EntierPositif{

	/**signe valant true si et seulement si le nombre entier est positif ou nul.*/
	bool signe;

public:

	/**logarithme de la base de comptage en base 10*/
	const static int _log_base_;

	/**Initialise un entier a zero*/
	Entier();

	/**constructeur prenant en parametre un entier du type long long int, pour fabriquer un entier generalise.
@param _entier_l*/
	Entier(qlonglong);

	/**Constructeur par copie d'un entier
@param _copie*/
	Entier(const Entier&);

	/**Constructeur utilisant les groupes de chiffres.
@param _grp_chiffres
@param _signe*/
	Entier(const QList<qulonglong>&,bool);

	/**/
	Entier(const EntierPositif&,bool _signe=true);

	/**Ajoute les chiffres (pas plus de 9) a la copie du nombre.
@param _chiffres_fin*/
	//Entier ajouter_chiffres(qulonglong)const;

	/***/
	Entier racine_abs(const Entier&)const;

	/***/
	Entier operator^(const Entier&)const;

	/***/
	Entier parmi(const Entier&)const;

	/***/
	Entier fact()const;

	/***/
	Entier ppcm(const Entier&)const;

	/***/
	Entier pgcd(const Entier&)const;

	/***/
	virtual Entier& operator+=(const Entier&);

	/***/
	virtual Entier& operator*=(const Entier&);

	/***/
	Entier& operator/=(const Entier&);

	/***/
	Entier& operator%=(const Entier&);

	/***/
	virtual Entier& operator-=(const Entier&);

	/***/
	Entier operator-()const;

	/***/
	QPair<Entier,Entier> division_euclidienne_generalise(const Entier&)const;

	/***/
	virtual Entier& operator=(const Entier&);

	/***/
	Entier absolu()const;

	/***/
	//EntierPositif absolu_2()const;

	/***/
	virtual bool estNul()const;

	/***/
	bool non_negatif()const;

	/***/
	virtual unsigned long long modulo_absolu_base()const;

	/***/
	virtual QString chaine()const;

	/***/
	static Entier parse_entier(const QString&);

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Entier operator+(const Entier&,const Entier&);

/***/
Entier operator*(const Entier&,const Entier&);

/***/
Entier operator/(const Entier&,const Entier&);

/***/
Entier operator%(const Entier&,const Entier&);

/***/
Entier operator-(const Entier&,const Entier&);

	/***/
bool operator<(const Entier&,const Entier&);

	/***/
bool operator>(const Entier&,const Entier&);

	/***/
bool operator<=(const Entier&,const Entier&);

	/***/
bool operator>=(const Entier&,const Entier&);

	/***/
bool operator!=(const Entier&,const Entier&);

	/***/
bool operator==(const Entier&,const Entier&);


Flux & operator <<(Flux&,const Entier&);
Flux & operator >>(Flux&,Entier&);
#endif



