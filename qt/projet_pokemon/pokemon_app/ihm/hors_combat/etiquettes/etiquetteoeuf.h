#ifndef ETIQUETTEOEUF_H
#define ETIQUETTEOEUF_H

#include <QLabel>
class OeufPokemon;
class Donnees;
class EtiquetteOeuf : public QLabel{

	QImage image_oeuf;

	bool choisi;

	uchar position;

	Q_OBJECT
public:
	EtiquetteOeuf(uchar,const OeufPokemon&,Donnees*);

	void maj_choix(bool);

	void mouseReleaseEvent(QMouseEvent *);

	void paintEvent(QPaintEvent *);

signals:

	void clic(uchar);
};

#endif // ETIQUETTEOEUF_H
