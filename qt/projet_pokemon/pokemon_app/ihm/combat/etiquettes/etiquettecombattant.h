#ifndef ETIQUETTECOMBATTANT_H
#define ETIQUETTECOMBATTANT_H

#include "serialisable/combat/combattant.h"
#include <QLabel>
class CreatureCombat;
class Donnees;
class QMouseEvent;

class EtiquetteCombattant : public QLabel{

	/**Pour le clic*/
	Combattant combattant;

	/**Vrai <=> selectionne*/
	bool choisi;

	/**Vrai <=> actif*/
	bool actif;

	Q_OBJECT
public:
	EtiquetteCombattant(const Combattant&,const CreatureCombat&,int,Donnees*);

	EtiquetteCombattant(const Combattant&,const QString&,int,int);

	void maj_choix(bool);

	void maj_actif(bool);

	void mouseReleaseEvent(QMouseEvent *_ev);

	void paintEvent(QPaintEvent *);
signals:

	void clic(const Combattant&);
public slots:

};

#endif // ETIQUETTECOMBATTANT_H
