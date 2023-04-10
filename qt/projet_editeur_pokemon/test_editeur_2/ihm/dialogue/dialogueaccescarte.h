#ifndef DIALOGUEACCESCARTE_H
#define DIALOGUEACCESCARTE_H
#include "serialisable/donnees.h"
#include <QDialog>
#include <QList>
class QTableWidget;
class GrilleDialogue;
class QLabel;
/***/
class DialogueAccesCarte: public QDialog{

	Q_OBJECT

	int langue;

	QTableWidget *table_lieux;
	QList<int> cles_lieux;

	QTableWidget *table_ligues;
	QList<int> cles_ligues;

	QTableWidget *table_ligues_ajoutees;

	QTableWidget *table_plateaux;
	QList<int> cles_plateaux;

	GrilleDialogue *grille;

	//QLabel *coords_et;
	Coordonnees coords;
	HashMap<Coordonnees,QList<int> > acces_fct_ligues;
	QList<int> ligues_select;

	Donnees *donnees;

	bool acceptable_coords;
	bool acceptable_coords_dest;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

	static void maj_grille_lien(GrilleDialogue*,Donnees*,const Coordonnees&);

	void maj_ligues();

public:

	DialogueAccesCarte(int,QWidget*);

	void conditions_acces_coords(const HashMap<Coordonnees,QList<int> >&);

	HashMap<Coordonnees,QList<int> > conditions_acces_coords()const;

private slots:

	void maj_table(int);

	void maj_grille(int);

	void maj_coords(const QPair<QPair<int,int>,QPair<int,int> >&);

	void ajouter_condition_ligue();

	void supprimer_condition_ligue();

	void ajouter_condition_acces_coords();

	void supprimer_condition_acces_coords();
};

#endif

