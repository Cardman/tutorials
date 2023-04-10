#ifndef MINIATURE_H
#define MINIATURE_H

#include <QLabel>

class Donnees;
class Miniature : public QLabel{

	QPair<uchar,uchar> position;

	bool oeuf;

	/**Ni oeuf, ni pokemon n'est présent sur cette case
	mais on peut placer un pokemon ou un oeuf lorsque c'est vide*/
	bool vide;

	/**Ni oeuf, ni pokemon n'est présent sur cette case
	et il est impossible de placer un pokemon ou un oeuf sur cette case*/
	bool valide;

	bool choisi;

	Q_OBJECT
public:

	Miniature(const QPair<uchar,uchar>&,Donnees*);

	void maj_choix(bool);

	void maj_miniature(int,Donnees*);

	void mouseReleaseEvent(QMouseEvent *);

	void paintEvent(QPaintEvent *);

signals:

	void clic(const QPair<uchar,uchar>&,bool,bool);
};

#endif // MINIATURE_H
