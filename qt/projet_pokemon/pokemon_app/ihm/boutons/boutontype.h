#ifndef BOUTONTYPE_H
#define BOUTONTYPE_H

#include <QLabel>

class BoutonType : public QLabel{

	uchar type_action;

	QColor couleur_texte;

	QColor couleur_fond;

	QColor couleur_rectangle;

	Q_OBJECT

public:

	BoutonType(const QString&,uchar);

	void maj_texte(const QString&);

	void maj_couleur_texte(const QColor&);

	void maj_couleur_fond(const QColor&);

	void maj_couleur_rectangle(const QColor&);

	virtual void mouseReleaseEvent(QMouseEvent *);

	virtual void paintEvent(QPaintEvent *);

signals:

	void clic(uchar);
};

#endif // BOUTONTYPE_H
