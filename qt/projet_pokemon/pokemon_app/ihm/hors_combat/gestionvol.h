#ifndef GESTIONVOL_H
#define GESTIONVOL_H

#include <QLabel>
class Coordonnees;
class Donnees;
class GestionVol : public QLabel{

	Donnees *donnees;

	QPair<int,int> dims;

	Q_OBJECT
public:
	GestionVol(Donnees*);

	void mouseReleaseEvent(QMouseEvent *);

signals:

	void clic(const Coordonnees&);
};

#endif // GESTIONVOL_H
