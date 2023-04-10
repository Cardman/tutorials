#ifndef ETIQUETTEEQUIPE_H
#define ETIQUETTEEQUIPE_H

#include <QLabel>
class QMouseEvent;
class EtiquetteEquipe : public QLabel{

	/**Numero d'equipe*/
	uchar equipe;

	/**Vrai <=> selectionne*/
	bool choisi;

	Q_OBJECT
public:
	EtiquetteEquipe(uchar);

	void redim();

	void maj_choix(bool);

	void mouseReleaseEvent(QMouseEvent *);

	void paintEvent(QPaintEvent *);
signals:

	void clic(uchar);
public slots:

};

#endif // ETIQUETTEEQUIPE_H
