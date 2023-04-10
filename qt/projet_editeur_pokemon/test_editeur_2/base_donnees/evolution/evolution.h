#ifndef EVOLUTION_H
#define EVOLUTION_H
#include <QObject>
#include "serialisable/base_donnees/hashmap.h"
class QString;

/**Classe permettant de dire comment evolue un pokemon
(niveau, pierre evolutive, objet a porter, lieu pour faire evoluer, bonheur, condition_stat,
genre et niveau, pierre evolutive et genre, attaque a apprendre, pokemon a avoir dans equipe)*/
class Evolution: public QObject{
	Q_OBJECT

	/***/
	static HashMap<QString,QString> init_descriptions_evos();

protected:

	/***/
	const static HashMap<QString,QString> _descriptions_evos_;

	/***/
	Evolution(QObject *parent=0);

public:

	/***/
	virtual QString description(const QString&,const QString&,int)const;
};

#endif



