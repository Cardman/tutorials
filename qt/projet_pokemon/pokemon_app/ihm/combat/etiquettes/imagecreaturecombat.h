#ifndef IMAGECREATURECOMBAT_H
#define IMAGECREATURECOMBAT_H

#include <QLabel>
#include "serialisable/combat/combattant.h"

class CreatureCombat;
class Donnees;
class QMouseEvent;
class ImageCreatureCombat : public QLabel{

	/**Image du pokemon en place*/
	QLabel *img_pk;

	/**Icone de l'eventuel objet porte par le pokemon*/
	QLabel *ico_objet;

	/***/
	Combattant cbt;

	Q_OBJECT
public:
	ImageCreatureCombat(const Combattant&,const CreatureCombat&,Donnees*);

	void maj_img_pk(const QImage&);

	void maj_ico_objet(const QImage&);

	void maj_cbt(const Combattant&);

	void mouseReleaseEvent(QMouseEvent*);
signals:
	void clic(const Combattant&);
public slots:
};

#endif // IMAGECREATURECOMBAT_H
