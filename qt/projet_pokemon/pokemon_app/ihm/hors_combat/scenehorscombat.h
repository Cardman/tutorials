#ifndef SCENEHORSCOMBAT_H
#define SCENEHORSCOMBAT_H
#include "base_donnees/donnees.h"
#include <QLabel>

class QPaintEvent;
class Partie;
class SceneHorsCombat : public QLabel
{

	Q_OBJECT

	HashMap<QPair<int,int>,Coordonnees> tuiles;
	//HashMap<QPair<int,int>,Tuile*> tuiles_g;
	HashMap<QPair<int,int>,QImage> tuiles_g;

	/*HashMap<QPair<int,int>,QImage> perso_g;

	HashMap<QPair<int,int>,bool> persos;*/

	HashMap<QPair<int,int>,QImage> premier_plan_g;

	HashMap<QPair<int,int>,bool> premier_plan;

	QPair<int,int> coords_heros;

	QPair<int,int> orientation_heros;

	QImage heros;

	void replacer(const Partie&,bool,Donnees*);

public:

	SceneHorsCombat(Donnees*);

	void maj_orientation(const QPair<int,int>&);

	void maj_tuiles(const Partie&,const Coordonnees&,bool,Donnees*);

	void maj_camera(const Partie&,const QPair<int,int>&,bool,Donnees*);

	void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // SCENEHORSCOMBAT_H
