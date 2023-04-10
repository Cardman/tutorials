#ifndef DIALOGUESELECTPLATEAU_H
#define DIALOGUESELECTPLATEAU_H
#include <QDialog>
#include <QList>
#include "serialisable/base_donnees/hashmap.h"
class GrilleVisuelle;
class QTableWidget;
/***/
class DialogueSelectPlateau: public QDialog{

	Q_OBJECT

	int langue;

	bool lieu_select;

	bool aj_suppl;

	GrilleVisuelle *grille;
	QTableWidget *table;
	QList<int> cles_plateaux;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

public:

	DialogueSelectPlateau(int,bool,QWidget*,bool,bool _aj_suppl=false);

	int plateau_select()const;

private slots:

	void maj_grille(int);
};

#endif


