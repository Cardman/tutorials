#ifndef DIALOGUEOBJET_H
#define DIALOGUEOBJET_H
#include <QDialog>
#include "serialisable/base_donnees/hashmap.h"
class QComboBox;
class QLabel;
/***/
class DialogueObjet: public QDialog{

	Q_OBJECT

	int langue;

	QComboBox *objet;

	QLabel *type;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

public:

	DialogueObjet(int,QWidget*);

	void editer_objet(const QString&);

	QString nv_obj()const;

private slots:

	void descr_obj();
};

#endif


