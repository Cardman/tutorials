#ifndef DIALOGUEBASEDONNEES_H
#define DIALOGUEBASEDONNEES_H
#include <QDialog>
#include "serialisable/base_donnees/hashmap.h"

class QTextEdit;
class QComboBox;
class DialogueBaseDonnees: public QDialog{

	Q_OBJECT

	int langue;

	QComboBox *combo_pk;

	QTextEdit *descr_pk;

	QComboBox *combo_capac;

	QTextEdit *descr_capac;

	QComboBox *combo_obj;

	QTextEdit *descr_obj;

	QComboBox *combo_att;

	QTextEdit *descr_att;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

public:

	DialogueBaseDonnees(int,QWidget*);

private slots:

	void maj_descr_pk();

	void maj_descr_capac();

	void maj_descr_obj();

	void maj_descr_att();
};

#endif


