#ifndef MONTECARLO_H
#define MONTECARLO_H
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/math/taux.h"
#include "autre/utilitaire.h"
#include <cstdlib>

/**Classe modelisant une loi de probabilite avec des elements quelconques.*/
template<typename Element>
class MonteCarlo{

	/**loi de probabilite (pas forcement uniforme et les entiers representent les effectifs de tirage par rapport a la somme de tous ces entiers)*/
	HashMap<Element,Entier> loi;

	/***/
	const static int _nb_tirages_;

	/**tirage d'un nombre aleatoire compris entre 0 et 2^128 selon une loi uniforme.*/
	static Entier tirageNombre();
protected:

	/** accesseur à la hashmap par une classe fille.*/
	HashMap<Element,Entier> val_loi()const;

	/**@return le plus grand nombre aléatoire pouvant être tiré (n'appelle pas qrand).*/
	static Entier tirageNombreMax();
public:

	/**Constructeur de base permettant de construire une loi de probabilite.*/
	MonteCarlo();

	/**Tirage d'un nombre aleatoire et retourne l'element correspondant au nombre aleatoire en fonction de la loi.*/
	Element tirage()const;

	/**ajoute un evenement avec un effectif dans la loi de la probabilite.
@param evenement*/
	void ajouter_event(const QPair<Element,Entier>&);

	/**@param _indice indice de l'evenement à récupérer
	@return la somme des effectifs*/
	QPair<Element,Entier> event_proba(int)const;

	/**@return l'ensemble des événements possibles*/
	QList<Element> events()const;

	/**@param _event l'événement dont on veut récupérer la probabilité
	@return la probabilité (relative aux autres) associée à l'événement*/
	Entier proba_event(const Element&)const;

	/**@return la somme des effectifs*/
	Entier somme()const;

	/**simplifie les effectifs en les divisant par le pgcd de tous les effectifs*/
	void simplifier();

	/**La classe Element doit implementer la methode Element::chaine()*/
	QString chaine()const;

	/**La classe Element doit être de type primitif (int,long,char...)*/
	QString chaine_nb()const;

	/**La classe Element doit être de type bool*/
	QString chaine_ch()const;

	/***/
	bool operator==(const MonteCarlo<Element>&)const;

	void liberer_memoire();
};

template<typename Element>
Flux& operator<<(Flux&,const MonteCarlo<Element>&);

template<typename Element>
Flux& operator>>(Flux&,MonteCarlo<Element>&);


template<typename Element>
const int MonteCarlo<Element>::_nb_tirages_=4;

template<typename Element>
MonteCarlo<Element>::MonteCarlo(){
	;
}

template<typename Element>
HashMap<Element,Entier> MonteCarlo<Element>::val_loi()const{
	return loi;
}

template<typename Element>
Element MonteCarlo<Element>::tirage()const{
	QList<Element> cles_=loi.cles();
	if(cles_.size()==1){
		return cles_[0];
	}
	Entier somme_=Entier(0);
	Element elt_=cles_[0];
	foreach(Element c,cles_){
		somme_=somme_+loi.valeur(c);
	}
#ifdef QT_NO_DEBUG
	Entier alea_=tirageNombre()%somme_;
#else
	Entier alea_=tirageNombreMax()%somme_;
#endif
	somme_=Entier(0);
	foreach(Element c,cles_){
		somme_=somme_+loi.valeur(c);
		if(alea_<somme_){
			elt_=c;
			break;
		}
	}
	return elt_;
}

template<typename Element>
Entier MonteCarlo<Element>::tirageNombre(){
	int nb_tirages=_nb_tirages_;
	Entier alea=Entier(0);
	Entier nb_max_alea=Entier(((qulonglong)RAND_MAX)+1);
	for(int i=0;i<nb_tirages;i++){
		alea=alea*nb_max_alea;
		alea=alea+Entier(qrand());
	}
	return alea;
}

template<typename Element>
Entier MonteCarlo<Element>::tirageNombreMax(){
	int nb_tirages=_nb_tirages_;
	Entier alea=Entier(0);
	Entier nb_max_alea=Entier(((qulonglong)RAND_MAX)+1);
	for(int i=0;i<nb_tirages;i++){
		alea=alea*nb_max_alea;
		alea=alea+Entier(RAND_MAX);
	}
	return alea;
}

template<typename Element>
void MonteCarlo<Element>::ajouter_event(const QPair<Element,Entier>& evenement){
	loi.ajouter_cle_valeur(evenement.first,evenement.second);
}

template<typename Element>
QPair<Element,Entier> MonteCarlo<Element>::event_proba(int _indice)const{
	QList<Element> cles_=loi.cles();
	QPair<Element,Entier> retour_;
	retour_.first=cles_[_indice];
	retour_.second=loi.valeur(cles_[_indice]);
	return retour_;
}

template<typename Element>
QList<Element> MonteCarlo<Element>::events()const{
	return loi.cles();
}

template<typename Element>
Entier MonteCarlo<Element>::proba_event(const Element& _event)const{
	return loi.valeur(_event);
}

template<typename Element>
Entier MonteCarlo<Element>::somme()const{
	Entier somme_=Entier(0);
	QList<Element> cles_=loi.cles();
	foreach(Element e,cles_){
		somme_=somme_+loi.valeur(e);
	}
	return somme_;
}

template<typename Element>
void MonteCarlo<Element>::simplifier(){
	Entier pgcd_=Entier(0);
	QList<Element> cles_=loi.cles();
	foreach(Element e,cles_){
		pgcd_=pgcd_.pgcd(loi.valeur(e));
	}
	foreach(Element e,cles_){
		loi.valeur(e)/=pgcd_;
	}
}

template<typename Element>
QString MonteCarlo<Element>::chaine()const{
	QList<Element> evs_=events();
	Entier som_=somme();
	QString retour_;
	foreach(Element e,evs_){
		retour_+="("+e.chaine()+","+Taux(proba_event(e),som_).chaine()+");";
	}
	retour_.chop(1);
	return retour_;
}

template<typename Element>
QString MonteCarlo<Element>::chaine_nb()const{
	QList<Element> evs_=events();
	Entier som_=somme();
	QString retour_;
	foreach(Element e,evs_){
		retour_+="("+QString::number(e)+","+Taux(proba_event(e),som_).chaine()+");";
	}
	retour_.chop(1);
	return retour_;
}

template<typename Element>
QString MonteCarlo<Element>::chaine_ch()const{
	QList<Element> evs_=events();
	Entier som_=somme();
	QString retour_;
	foreach(Element e,evs_){
		retour_+="("+e+","+Taux(proba_event(e),som_).chaine()+");";
	}
	retour_.chop(1);
	return retour_;
}

template<typename Element>
bool MonteCarlo<Element>::operator==(const MonteCarlo<Element>& _autre)const{
	return loi==_autre.loi;
}

template<typename Element>
void MonteCarlo<Element>::liberer_memoire(){
	foreach(Element e,loi.cles()){
		delete e;
		e=NULL;
	}
}

template<typename Element>
Flux& operator<<(Flux& _out,const MonteCarlo<Element>&){
	return _out;
}

template<typename Element>
Flux& operator>>(Flux& _in,MonteCarlo<Element>&){
	return _in;
}
#endif



