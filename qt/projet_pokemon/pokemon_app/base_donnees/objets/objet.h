#ifndef OBJET_H
#define OBJET_H
#include <QObject>
#include <QStringList>
#include "serialisable/base_donnees/hashmap.h"

class Donnees;

/**Objet que peut transporter l'utilisateur:
	-potions
	-anti - statut
	-vitamines (augmentant les statistiques)
	-ball de capture
	-fossiles
	-objets de quete
	-pierre evolutive
	-objet a porter
	-restauration point pouvoir
	-baie
	-objet a attacher
	-objet affectant le bonheur
	-rappel
	-rappel max
	-ct
	-cs*/
class Objet: public QObject{
	Q_OBJECT

	/***/
	//QStringList effets;

	/***/
	bool attachable;

	/***/
	//bool achetable;

	/**prix de l'objet achete*/
	int prix_achat;

protected:

	/**Constructeur à utiliser*/
	Objet(QObject *parent=0);

	/**Met la valeur de l'attribut attachable à true*/
	void setAttachable();

	/**Met la valeur de l'attribut achetable à true*/
	//void setAchetable();

	/**@param _prix_achat*/
	void maj_prix_achat(int);

public:

	/**@return vrai si et seulement si l'objet est attachable sur un pokémon*/
	bool estAttachable()const;

	/**@return vrai si et seulement si l'objet est achetable dans une boutique*/
	bool estAchetable()const;

	/**@return la valeur de prix_achat*/
	int prix()const;

	/**@return effets*/
	//QStringList effets_objet()const;

	/**Donne la description d'un objet.*/
	virtual QString description(int,Donnees*)const=0;

	
	//virtual QList<QStringList> elements(const QString&)const=0;
};

#endif



