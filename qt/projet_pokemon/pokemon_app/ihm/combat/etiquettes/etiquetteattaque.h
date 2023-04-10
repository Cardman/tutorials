#ifndef ETIQUETTEATTAQUE_H
#define ETIQUETTEATTAQUE_H

#include <QLabel>

class QMouseEvent;
class EtiquetteAttaque : public QLabel
{
	QString action;

	/**Vrai <=> selectionne*/
	bool choisi;

	/**Vrai <=> actif*/
	bool actif;

	Q_OBJECT
public:
	EtiquetteAttaque(const QString&,const QString&);

	void maj_choix(bool);

	void maj_actif(bool);

	void mouseReleaseEvent(QMouseEvent *);

	void paintEvent(QPaintEvent *);
signals:

	void clic(const QString&);
public slots:

};

#endif // ETIQUETTEATTAQUE_H
