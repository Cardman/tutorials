#ifndef DIALOGUELARGEUR_H
#define DIALOGUELARGEUR_H
#include <QDialog>
#include "serialisable/base_donnees/hashmap.h"
class QSpinBox;
/**classe gérant une boîte de dialogue jouant sur la largeur de l'environnement à changer les dimensions*/
class DialogueLargeur: public QDialog{

	Q_OBJECT

	int langue;

	QSpinBox *largeur;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

public:

	DialogueLargeur(int,int,QWidget*);

	int largeur_v()const;

signals:

	void dims(const QPair<int,int>&);

private slots:

	void fin_ecriture_dims();
};

#endif


