#ifndef DIALOGUEHAUTEUR_H
#define DIALOGUEHAUTEUR_H
#include <QDialog>
#include "serialisable/base_donnees/hashmap.h"
class QSpinBox;
/**classe gérant une boîte de dialogue jouant sur la largeur de l'environnement à changer les dimensions*/
class DialogueHauteur: public QDialog{

	Q_OBJECT

	int langue;

	QSpinBox *hauteur;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

public:

	DialogueHauteur(int,int,QWidget*);

	int hauteur_v()const;

signals:

	void dims(const QPair<int,int>&);

private slots:

	void fin_ecriture_dims();
};

#endif


