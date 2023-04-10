#ifndef TOUCHE_H
#define TOUCHE_H

#include <QLabel>

class Touche : public QLabel{

	QColor couleur_texte;

	QColor couleur_fond;

	QColor couleur_rectangle;

	Q_OBJECT
public:
	Touche(const QChar&);

	void maj_couleur_texte(const QColor&);

	void maj_couleur_fond(const QColor&);

	void maj_couleur_rectangle(const QColor&);

	void mouseReleaseEvent(QMouseEvent *);

	virtual void paintEvent(QPaintEvent *);

signals:

	void clic(const QString&);
public slots:

};

#endif // TOUCHE_H
