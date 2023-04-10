#ifndef DIALOGUEACCESLIGUE_H
#define DIALOGUEACCESLIGUE_H
#include "serialisable/donnees.h"
#include <QDialog>
#include <QList>
class QTableWidget;
class GrilleDialogue;
class QLabel;
/***/
class DialogueAccesLigue: public QDialog{

	Q_OBJECT

	int langue;

	QTableWidget *table_champions;

	QTableWidget *table_ligues;
	QList<int> cles_ligues;

	QTableWidget *table_champions_ajoutes;

	//QLabel *coords_et;
	HashMap<int,QList<Coordonnees> > acces_fct_champions;
	QList<Coordonnees> champions_select;
	int ind_ligue;

	Donnees *donnees;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	void maj_champions();

public:

	DialogueAccesLigue(int,QWidget*);

	void conditions_acces_fct_champions(const HashMap<int,QList<Coordonnees> >&);

	HashMap<int,QList<Coordonnees> > conditions_acces_fct_champions()const;

private slots:

	void maj_table(int);

	void ajouter_condition_champion();

	void supprimer_condition_champion();

	void ajouter_condition_acces_ligue();

	void supprimer_condition_acces_ligue();
};

#endif

