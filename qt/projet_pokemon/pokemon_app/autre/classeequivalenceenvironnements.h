#ifndef CLASSEEQUIVALENCEENVIRONNEMENTS_H
#define CLASSEEQUIVALENCEENVIRONNEMENTS_H
#include "serialisable/cartes/environnement.h"

/**Dire qu'un lieu est valide, c'est dire que tous
les environnements forment une même classe
d'équivalence ou
il n'existe pas de classe d'équivalence dont un des
représentant est pointé par un des environnement d'une autre classe d'équivalence
(au sens de "est lié à") .
Dire qu'un environnement est lié à un autre c'est dire
que cet environnement est accessible par un autre.*/
class ClasseEquivalenceEnvironnements{

	/**environnements accessibles les uns des autres.*/
	QList<Environnement> elements;
public:

	/**Cette méthode ajoute un environnement s'il existe un environnement de la classe d'équivalence permettant d accéder à l'environnement passé en paramètre et s'il existe un environnement de la classe d'équivalence accessible depuis l'environnement passé en paramètre.
@param environnement Environnement q'il faut ajouter ou non.
@return vrai si et seulement si l'environnement passé en paramètre a été ajouté.*/
	bool ajouter_environnement(const Environnement&);
};
#endif



