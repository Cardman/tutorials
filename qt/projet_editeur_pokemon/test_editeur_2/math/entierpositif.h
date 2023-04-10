#ifndef ENTIERPOSITIF_H
#define ENTIERPOSITIF_H
//#include <QVariant>
//#include <QSettings>
#include "flux/flux.h"
#include <QList>
#include <QPair>
class QString;

/**Classe modelisant un entier positif avec des groupes de chiffres, c'est une valeur absolue.*/
class EntierPositif{

	/**Un entier est represente par un groupe de chiffres tous inferieurs a la base (10^9).*/
	QList<unsigned long long> gr_chiffres;
protected:

	/**@param _nombre*/
	EntierPositif(long long);

	/**@param _composants*/
	EntierPositif(const QList<unsigned long long>&);

	/***/
	virtual unsigned long long modulo_absolu_base()const;

	/**@param _autre*/
	virtual EntierPositif& operator*=(const EntierPositif&);
	//virtual EntierPositif operator*(const EntierPositif&)const;

	/**@param _autre*/
	virtual EntierPositif& operator+=(const EntierPositif&);

	//virtual EntierPositif operator-(const EntierPositif&)const;

	/**@param _autre*/
	//virtual bool operator<(const EntierPositif&)const;//comparaison des VALEURS ABSOLUES

	//comparaison des VALEURS ABSOLUES

	
	virtual bool estNul()const;

	/**@param _autre*/
	EntierPositif multiplier(long long)const;

	/**on multiplie un nombre par 10^_exposant par copie
	@param _exposant*/
	//EntierPositif operator<<(int)const;//multiplier par base

	/***/
	unsigned long long division_temporaire(const EntierPositif&,unsigned long long,unsigned long long)const;

	/***/
	QPair<QList<unsigned long long>,QList<unsigned long long> > division_euclidienne(const EntierPositif&)const;

	/**@param _autre*/
	//virtual bool operator>(const EntierPositif&)const;//Appele seulement dans la classe fille

	/**@param _autre*/
	//virtual EntierPositif operator+(const EntierPositif&)const;//Appele seulement dans la classe fille

public:

	/**base des entiers*/
	const static qulonglong _base_;

	/**La base décimale*/
	const static int _base_numer_;

	/***/
	static int log_base();

	/**Appelé seulement dans l'opérateur < libre entre deux "Entiers"*/
	bool plus_petit_que(const EntierPositif&)const;
	/**Appelé seulement dans l'opérateur > libre entre deux "Entiers"*/
	bool plus_grand_que(const EntierPositif&)const;
	/**Appelé seulement dans l'opérateur == libre entre deux "Entiers"*/
	bool egal_a(const EntierPositif&)const;

	/**@param _autre, l'opération n'est réalisable que si (*this)>=_autre, accessible uniq dans Entier::operator+=*/
	virtual EntierPositif& operator-=(const EntierPositif&);

	//Appele seulement dans la methode QString Entier::chaine_div()const;
	/***/
	EntierPositif();//Appele seulement dans la classe fille et mere

	/**@param _copie*/
	EntierPositif(const EntierPositif&);//Appele seulement dans la classe fille

	/***/
	virtual QString chaine()const;

	/**@param _autre*/
	virtual EntierPositif& operator=(const EntierPositif&);//Appele seulement dans la classe Taux (explicite)

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const EntierPositif&);
Flux & operator >>(Flux&,EntierPositif&);
#endif



