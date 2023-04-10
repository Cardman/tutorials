#ifndef ETIQUETTEPKUT_H
#define ETIQUETTEPKUT_H

#include <QLabel>
class CreatureCombat;
class Taux;
class Donnees;
class Barre;
class PokemonUtilisateur;

class EtiquettePkUt : public QLabel{

	/**Position du pokemon dans l'equipe*/
	uchar position;

	/**Miniature du pokemon en place*/
	QLabel *ico_pk;

	/**Icone de la pokeball ayant servi a capturer le pokemon*/
	QLabel *ico_ball;

	/**Nom actuel du pokemon eventuellement transeforme par morphing*/
	QLabel *nom_pk;

	/**Genre du pokemon*/
	QLabel *genre_pk;

	/**Niveau du pokemon*/
	QLabel *niveau_pk;

	/**Barre de vie*/
	Barre *barre_vie;

	/**PV restants du pokemon / PV max du pokemon*/
	QLabel *pv_pk;

	/**Statut du pokemon*/
	QLabel *statut_pk;

	/**Barre de points d'experience*/
	Barre *barre_pts;

	/**Points d'experience restants pour le niveau suivant / Total de points d'experience restants pour le niveau suivant*/
	QLabel *pts_pk;

	/**Objet porte par le pokemon*/
	QLabel *objet_pk;

	bool choisi;

	Q_OBJECT

public:
	EtiquettePkUt(uchar,const PokemonUtilisateur&,Donnees*,const QString& ="");

	void maj_choix(bool);

	void mouseReleaseEvent(QMouseEvent *);

	void paintEvent(QPaintEvent *);

signals:

	void clic(uchar);
};

#endif // ETIQUETTEPKUT_H
