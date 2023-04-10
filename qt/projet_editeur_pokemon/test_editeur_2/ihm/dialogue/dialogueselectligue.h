#ifndef DIALOGUESELECTLIGUE_H
#define DIALOGUESELECTLIGUE_H
#include <QDialog>
#include <QList>
#include "serialisable/base_donnees/hashmap.h"
class QTableWidget;
/***/
class DialogueSelectLigue: public QDialog{

	int langue;

	QTableWidget *table;
	QList<int> cles_ligues;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

public:

	DialogueSelectLigue(int,bool,QWidget*);

	int ligue_select()const;
};

#endif


