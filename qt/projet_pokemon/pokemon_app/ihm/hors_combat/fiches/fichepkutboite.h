#ifndef FICHEPKUTBOITE_H
#define FICHEPKUTBOITE_H

#include "serialisable/base_donnees/hashmap.h"
#include <QLabel>
#include <QVBoxLayout>

class EtiquetteAttaque;
class PokemonUtilisateur;
class Donnees;
class QTextEdit;
class Barre;
class FichePkUtBoite : public QLabel{

	/**Image macroscopique associée à la forme actuelle pokémon sur le combat*/
	QLabel *image_pk;

	/**Icone de la pokeball ayant servi a capturer le pokemon*/
	QLabel *ico_ball;

	/**Pseudo du pokemon*/
	QLabel *pseudo;

	/**Nom actuel du pokemon eventuellement transeforme par morphing*/
	QLabel *nom_pk;

	/**Genre du pokemon*/
	QLabel *genre_pk;

	/**Niveau du pokemon*/
	QLabel *niveau_pk;

	/**Capacité de base avant un combat*/
	QLabel *capacite;

	/**Pseudo du pokemon*/
	QLabel *pas_tete_equipe;

	/**Bonheur du pokemon*/
	QLabel *bonheur;

	/**Noms des statistiques*/
	QStringList noms_statistiques;

	/**Statistiques du pokemon (sauf PV)*/
	QGridLayout *statistiques;

	/**Attaques apprises*/
	QVBoxLayout *attaques;

	HashMap<QString,EtiquetteAttaque*> liste_attaques;

	HashMap<QString,QString> descriptions_attaques;

	QTextEdit *description_attaque;

	QTextEdit *description_capacite;

	QTextEdit *description_objet;

	QTextEdit *description_pokemon;

	/**Position du pokemon dans l'equipe*/
	uchar position;

	/**Barre de points d'experience*/
	Barre *barre_pts;

	/**Points d'experience restants pour le niveau suivant / Total de points d'experience restants pour le niveau suivant*/
	QLabel *pts_pk;

	/**Objet porte par le pokemon*/
	QLabel *objet_pk;

	bool choisi;

	Q_OBJECT

public:

	FichePkUtBoite();

	void maj_fiche(const PokemonUtilisateur&,int,Donnees*);

private slots:

	void maj_description(const QString&);

};

#endif // FICHEPKUTBOITE_H
