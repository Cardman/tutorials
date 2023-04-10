#ifndef DIALOGUECOORDS_H
#define DIALOGUECOORDS_H
#include "serialisable/donnees.h"
#include <QDialog>
#include <QList>
class QTableWidget;
class GrilleDialogue;
class QLabel;
/***/
class DialogueCoords: public QDialog{

	Q_OBJECT

	int langue;

	QTableWidget *table_lieux;
	QList<int> cles_lieux;

	QTableWidget *table_plateaux;
	QList<int> cles_plateaux;
	GrilleDialogue *grille;
	QLabel *coords_et;
	Coordonnees coords;
	Donnees *donnees;
	bool acceptable_coords;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

public:

	enum TypeCoordonnees{DEPART,LIEU_VOL,LIAISON};
	DialogueCoords(int,const Coordonnees&,Donnees*,QWidget*,int);

	Coordonnees coordonnees()const;

	bool acceptable()const;

private slots:

	void maj_table(int);

	void maj_grille(int);

	void maj_coords(const QPair<QPair<int,int>,QPair<int,int> >&);
};

#endif

