#ifndef DIALOGUESELECTLIEULIGUE_H
#define DIALOGUESELECTLIEULIGUE_H
#include <QDialog>
#include <QList>
#include <QPair>
#include "serialisable/base_donnees/hashmap.h"
class QTableWidget;
class QCheckBox;
/***/
class DialogueSelectLieuLigue: public QDialog{

	int langue;

	QTableWidget *table_lieux;
	QTableWidget *table_ligues;
	QList<int> cles_lieux;
	QList<int> cles_ligues;
	QCheckBox *choix;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

public:

	DialogueSelectLieuLigue(int,QWidget*);

	QPair<int,bool> lieu_ligue_select()const;
};

#endif


