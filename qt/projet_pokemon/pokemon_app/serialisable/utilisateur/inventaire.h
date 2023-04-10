#ifndef INVENTAIRE_H
#define INVENTAIRE_H
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/math/taux.h"
#include <QString>

class Donnees;

/***/
class Inventaire{

	/***/
	HashMap<QString,QList<QPair<uchar,Taux> > > objets_soins;

	/***/
	HashMap<QString,uchar> balls;

	/***/
	HashMap<QString,uchar> objets_attacher_evolution;

	/***/
	HashMap<QString,uchar> objets_attacher;

	/***/
	HashMap<QString,uchar> pierres_evo;

	/***/
	HashMap<QString,uchar> fossiles;

	/***/
	HashMap<QString,uchar> baies;

	/***/
	HashMap<QString,QList<QPair<uchar,uchar> > > boost_statistiques;

	/***/
	HashMap<QString,uchar> objets_reventes;

	/***/
	HashMap<QString,uchar> plaques;

	/***/
	HashMap<QString,uchar> repousse;

	/***/
	HashMap<uchar,uchar> ct;

	/***/
	HashMap<uchar,bool> cs;

	/***/
	//HashMap<QString,bool> objets_quetes;
public:

	/**Constructeur par défaut permettant la sérialisation de l'objet*/
	Inventaire();

	Inventaire(Donnees*);

	/**
@return l'adresse de objets_soins*/
	HashMap<QString,QList<QPair<uchar,Taux> > >& objets_soins_ut();

	/**
@return l'adresse de balls*/
	HashMap<QString,uchar>& balls_ut();

	/**
@return l'adresse de objets_attacher_evolution*/
	HashMap<QString,uchar>& objets_attacher_evolution_ut();

	/**
@return l'adresse de objets_attacher*/
	HashMap<QString,uchar>& objets_attacher_ut();

	/**
@return l'adresse de pierres_evo*/
	HashMap<QString,uchar>& pierres_evo_ut();

	/**
@return l'adresse de baies*/
	HashMap<QString,uchar>& baies_ut();

	/**
@return l'adresse de boost_statistiques*/
	HashMap<QString,QList<QPair<uchar,uchar> > >& boost_statistiques_ut();

	/**
@return l'adresse de objets_reventes*/
	HashMap<QString,uchar>& objets_reventes_ut();

	/**
@return l'adresse de plaques*/
	HashMap<QString,uchar>& plaques_ut();

	/**@return repousse*/
	HashMap<QString,uchar>& repousse_ut();

	/**
@return l'adresse de fossiles*/
	HashMap<QString,uchar>& fossiles_ut();

	/**
@return l'adresse de ct*/
	HashMap<uchar,uchar>& ct_ut();

	/**
@return l'adresse de cs*/
	HashMap<uchar,bool>& cs_ut();

	uchar quantite(const QString&)const;

	uchar quantite(const QString&,int)const;

	void consommer(const QString&,int=-1);

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

Flux & operator <<(Flux&,const Inventaire&);
Flux & operator >>(Flux&,Inventaire&);

#endif


