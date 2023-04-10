#ifndef DIALOGUEGRILLE_H
#define DIALOGUEGRILLE_H
#include <QDialog>
#include "serialisable/base_donnees/hashmap.h"
class QSpinBox;
/***/
class DialogueGrille: public QDialog{

	int langue;

	QSpinBox *colonnes_lignes;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

public:

	enum Fonction{AJOUT_LGS_HAUT,AJOUT_COLS_GAUCHE,AJOUT_LGS_BAS,AJOUT_COLS_DROITE};

	DialogueGrille(int,Fonction,QWidget*);

	int valeur()const;
};

#endif


