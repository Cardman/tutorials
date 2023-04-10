#ifndef ETIQUETTECREATCOMBAT_H
#define ETIQUETTECREATCOMBAT_H

#include <QLabel>
#include "serialisable/combat/combattant.h"
class CreatureCombat;
class Taux;
class Donnees;
class Barre;
class EtiquetteCreatCombat : public QLabel{

	/**Combattant*/
	Combattant combattant;

	/**Miniature du pokemon en place*/
	QLabel *ico_pk;

	/**Icone de la pokeball ayant servi a capturer le pokemon*/
	QLabel *ico_ball;

	/**Nom actuel du pokemon eventuellement transeforme par morphing*/
	QLabel *nom_pk;

	/**Genre du pokemon*/
	QLabel *genre_pk;

	/**Niveau du pokemon*/
	QLabel *niveau_pk;

	/**Barre de vie*/
	Barre *barre_vie;

	/**PV restants du pokemon / PV max du pokemon*/
	QLabel *pv_pk;

	/**Statut du pokemon*/
	QLabel *statut_pk;

	/**Barre de points d'experience*/
	Barre *barre_pts;

	/**Points d'experience restants pour le niveau suivant / Total de points d'experience restants pour le niveau suivant*/
	QLabel *pts_pk;

	bool choisi;

	bool valide;

	Q_OBJECT
public:
	EtiquetteCreatCombat(const Combattant&,const CreatureCombat&,Donnees*);

	EtiquetteCreatCombat();

	void maj_choix(bool);

	void mouseReleaseEvent(QMouseEvent *);

	void maj_ico_pk(const QImage&);

	void maj_ico_ball(const QImage&);

	void maj_nom_pk(const QString&);

	void maj_genre_pk(const QString&);

	void maj_niveau_pk(uchar);

	void maj_pv_pk(const Taux&,const Taux&);

	void maj_pts_pk(const Taux&,const Taux&);

	void paintEvent(QPaintEvent *);
signals:

	void clic(const Combattant&);
public slots:

};

#endif // ETIQUETTECREATCOMBAT_H
