#ifndef BOUTONCHOIX_H
#define BOUTONCHOIX_H

#include <QLabel>

/**Case a cocher*/
class BoutonChoix : public QLabel{

	bool choisi;

	QColor couleur_texte;

	QColor couleur_fond;

	QColor couleur_choix;

	QColor couleur_rectangle;

	Q_OBJECT

public:

	BoutonChoix();

	void maj_choix(bool);

	void maj_texte(const QString&);

	void maj_couleur_texte(const QColor&);

	void maj_couleur_choix(const QColor&);

	void maj_couleur_fond(const QColor&);

	void maj_couleur_rectangle(const QColor&);

	virtual void mouseReleaseEvent(QMouseEvent *);

	virtual void paintEvent(QPaintEvent *);

signals:

	void clic(bool);
};

#endif // BOUTONCHOIX_H
