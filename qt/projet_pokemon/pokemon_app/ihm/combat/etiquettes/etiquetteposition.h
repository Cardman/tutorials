#ifndef ETIQUETTEPOSITION_H
#define ETIQUETTEPOSITION_H

#include <QLabel>

class EtiquettePosition : public QLabel{

	/**Position de combat*/
	QPair<int,int> position;

	/***/
	bool choisi;

	Q_OBJECT
public:
	EtiquettePosition(int,int,int,int);

	void maj_choix(bool);

	void mouseReleaseEvent(QMouseEvent *);

	void paintEvent(QPaintEvent *);

signals:

	void clic(const QPair<int,int>&);
public slots:

};

#endif // ETIQUETTEPOSITION_H
