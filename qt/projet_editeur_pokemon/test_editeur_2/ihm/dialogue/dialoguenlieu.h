#ifndef DIALOGUENLIEU_H
#define DIALOGUENLIEU_H
#include <QDialog>
#include <QList>
#include <QPair>
#include "serialisable/base_donnees/hashmap.h"
class Lieu;
class QLineEdit;
class QComboBox;
class QString;
/***/
class DialogueNLieu: public QDialog{

	//Q_OBJECT

	//QLineEdit *nom;

	int langue;

	QList<QLineEdit*> noms;

	QComboBox *type;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	//bool accepte;
	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

public:

	DialogueNLieu(int,QWidget*);

	//bool acceptation();

	Lieu nv_lieu()const;

	void maj_nom_type(const QPair<QString,QString>&);

	QPair<QString,QString> nom_type()const;

/*private slots:

	void accepter();*/
};

#endif


