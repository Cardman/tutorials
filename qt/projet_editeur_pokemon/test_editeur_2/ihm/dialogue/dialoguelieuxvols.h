#ifndef DIALOGUELIEUXVOLS
#define DIALOGUELIEUXVOLS
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/coordonnees/coordonnees.h"
#include <QDialog>
class GrilleMap;
class Donnees;
class QLabel;
class QCloseEvent;
/***/
class DialogueLieuxVols: public QDialog{

	Q_OBJECT

	HashMap<QPair<int,int>,Coordonnees> lieux_vols;

	int langue;

	bool rejete;

	GrilleMap *grille;

	/**Dans la grande map*/
	QLabel *coord_donnees;

	/**Dans la grande map*/
	Coordonnees coord_act;

	Donnees *donnees;

	QPair<int,int> coords;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

public:

	DialogueLieuxVols(int,QWidget*,Donnees*,const HashMap<QPair<int,int>,Coordonnees>&);

	HashMap<QPair<int,int>,Coordonnees> vols()const;

	bool rejet()const;

	virtual void closeEvent(QCloseEvent*);

private slots:

	/***/
	void maj_coords(const QPair<int,int>&);

	void supprimer_lien();

	void maj_lien();

	void acceptation();

};

#endif


