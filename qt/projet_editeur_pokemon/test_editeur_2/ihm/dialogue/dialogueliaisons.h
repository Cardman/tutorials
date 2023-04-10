#ifndef DIALOGUELIASONS_H
#define DIALOGUELIASONS_H
#include "serialisable/donnees.h"
#include <QDialog>
#include <QList>
class QTableWidget;
class GrilleDialogue;
class QLabel;
/***/
class DialogueLiaisons: public QDialog{

	Q_OBJECT

	int langue;

	QTableWidget *table_lieux;
	QList<int> cles_lieux;

	QTableWidget *table_lieux_dest;
	QList<int> cles_lieux_dest;

	QTableWidget *table_plateaux;
	QList<int> cles_plateaux;

	QTableWidget *table_plateaux_dest;
	QList<int> cles_plateaux_dest;

	GrilleDialogue *grille;
	GrilleDialogue *grille_dest;
	//QLabel *coords_et;
	Coordonnees coords;
	Coordonnees coords_dest;
	Donnees *donnees;
	bool acceptable_coords;
	bool acceptable_coords_dest;
	int type;

	HashMap<QPair<int,int>,QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > > lien_vers_plateau_suivant;
	HashMap<int,Coordonnees> acces;
	HashMap<int,Coordonnees> origine;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

	static void maj_grille_lien(GrilleDialogue*,Donnees*,const Coordonnees&);

public:

	enum TypesLiaisons{LIEN_PLATEAU,LIEN_PLATEAU_LIGUE,LIEUX_A_SOUDER};
	DialogueLiaisons(int,QWidget*,DialogueLiaisons::TypesLiaisons);

	HashMap<QPair<int,int>,QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<int,int>,QPair<int,int> > > > maj_lien_vers_plateau_suivant()const;
	HashMap<int,Coordonnees> maj_acces()const;
	HashMap<int,Coordonnees> maj_origine()const;

private slots:

	void maj_table(int);

	void maj_table_dest(int);

	void maj_grille(int);

	void maj_grille_dest(int);

	void maj_coords(const QPair<QPair<int,int>,QPair<int,int> >&);

	void maj_coords_dest(const QPair<QPair<int,int>,QPair<int,int> >&);

	void souder_lieux();

	void desouder_lieux();

	void lier_plateaux();

	void delier_plateaux();

	void lier_plateaux_ligues();

	void delier_plateaux_ligues();

	void maj_coords_acces();

	void maj_coords_origine();

	void suppr_coords_acces();

	void suppr_coords_origine();
};

#endif

