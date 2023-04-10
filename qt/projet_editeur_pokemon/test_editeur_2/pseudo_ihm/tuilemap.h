#ifndef TUILEMAP_H
#define TUILEMAP_H
//#include <QLabel>
#include <QImage>
#include <QPair>
#include "base_donnees/import.h"

/***/
class TuileMap{

	/**image représentant la tuile réelle.*/
	QImage image;

public:

	/***/
	TuileMap(const QImage& _img=Import::_map_invalide_);

	/***/
	void maj_image(const QImage&);

	/***/
	QImage imag()const;

	/***/
	void affecter(TuileMap*);

	/***/
	//void init();

	/***/
	void reinit();

};

#endif



