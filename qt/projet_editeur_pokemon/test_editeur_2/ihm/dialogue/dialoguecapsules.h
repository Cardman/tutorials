#ifndef DIALOGUECAPSULES_H
#define DIALOGUECAPSULES_H
#include <QDialog>
#include <QStringList>
#include "serialisable/base_donnees/hashmap.h"
class QComboBox;
class QTableWidget;
class QLabel;
/***/
class DialogueCapsules: public QDialog{
	Q_OBJECT

	int langue;

	QComboBox *nom_capsule;

	QLabel *capsule;

	QTableWidget *table_capsules;

	QList<uchar> capsules;

	bool ct;

	bool rejeter;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

public:

	DialogueCapsules(int,bool,QWidget*);

	void maj_liste(const QList<uchar>&);

	QList<uchar> nv_liste()const;

	bool rejete()const;

	virtual void closeEvent(QCloseEvent*);

private slots:

	void ajout_capsule();

	void suppression_capsule();

	void acceptation();

	void maj_capsule(const QString&);
};

#endif



