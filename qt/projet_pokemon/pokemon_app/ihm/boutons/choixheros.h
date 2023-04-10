#ifndef CHOIXHEROS_H
#define CHOIXHEROS_H

#include <QLabel>
class Donnees;
class ChoixHeros : public QLabel{

	QString sexe;

	bool choix;

	Q_OBJECT
public:
	ChoixHeros(const QString&,Donnees*);

	void maj_choix(bool);

	void mouseReleaseEvent(QMouseEvent *);

	void paintEvent(QPaintEvent *);
signals:

	void clic(const QString&);
public slots:

};

#endif // CHOIXHEROS_H
