#ifndef BOUTON_H
#define BOUTON_H

#include <QLabel>

class QMouseEvent;

class Bouton : public QLabel{

	int sous_action;

	QString action;

	QColor couleur_texte;

	QColor couleur_fond;

	QColor couleur_rectangle;

	Q_OBJECT
public:
	Bouton();

	Bouton(const QString&);

	Bouton(const QString&,int);

	void maj_texte(const QString&);

	void maj_couleur_texte(const QColor&);

	void maj_couleur_fond(const QColor&);

	void maj_couleur_rectangle(const QColor&);

	virtual void mouseReleaseEvent(QMouseEvent *);

	virtual void paintEvent(QPaintEvent *);

signals:

	void clic();

	void clic(const QString&);

	void clic(const QString&,int);
};

#endif // BOUTON_H
