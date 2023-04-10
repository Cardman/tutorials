#ifndef DIALOGUENENVIR_H
#define DIALOGUENENVIR_H
#include <QDialog>
#include "serialisable/base_donnees/hashmap.h"
class Environnement;
class EnvironnementLigue;
class QComboBox;
class QSpinBox;
/***/
class DialogueNEnvir: public QDialog{

	Q_OBJECT

	int langue;

	QComboBox *type;

	QSpinBox *largeur;

	QSpinBox *hauteur;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

public:

	DialogueNEnvir(int,QWidget*);

	Environnement nv_envir()const;

	EnvironnementLigue nv_envir_ligue()const;

signals:

	void dims(const QPair<int,int>&);

private slots:

	void fin_ecriture_dims();
};

#endif


