#ifndef DIALOGUEACHATS_H
#define DIALOGUEACHATS_H
#include <QDialog>
#include <QStringList>
#include "serialisable/base_donnees/hashmap.h"
class QComboBox;
class QTableWidget;
/***/
class DialogueAchats: public QDialog{
	Q_OBJECT

	int langue;

	QComboBox *nom_objet;

	QTableWidget *table_objets;

	QStringList objets;

	bool rejeter;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

public:

	DialogueAchats(int,QWidget*);

	void maj_liste(const QStringList&);

	QStringList nv_liste()const;

	bool rejete()const;

	virtual void closeEvent(QCloseEvent*);

private slots:

	void ajout_objet();

	void suppression_objet();

	void acceptation();
};

#endif


