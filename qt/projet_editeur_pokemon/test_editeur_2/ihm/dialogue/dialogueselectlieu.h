#ifndef DIALOGUESELECTLIEU_H
#define DIALOGUESELECTLIEU_H
#include <QDialog>
#include <QList>
#include "serialisable/base_donnees/hashmap.h"
class QTableWidget;
/***/
class DialogueSelectLieu: public QDialog{

	int langue;

	QTableWidget *table;
	QList<int> cles_lieux;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

public:

	DialogueSelectLieu(int,bool,QWidget*);

	int lieu_select()const;
};

#endif


