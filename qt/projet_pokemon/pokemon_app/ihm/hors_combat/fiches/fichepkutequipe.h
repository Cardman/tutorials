#ifndef FICHEPKUTEQUIPE_H
#define FICHEPKUTEQUIPE_H

#include "serialisable/base_donnees/hashmap.h"
#include <QLabel>
#include <QVBoxLayout>

class EtiquetteAttaque;
class PokemonUtilisateur;
class Donnees;
class QTextEdit;

class FichePkUtEquipe : public QLabel{

	/**Image macroscopique associée à la forme actuelle pokémon sur le combat*/
	QLabel *image_pk;

	/**Pseudo du pokemon*/
	QLabel *pseudo;

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

	uchar gestion_en_cours;

	Q_OBJECT
public:

	FichePkUtEquipe();

	void maj_fiche(const PokemonUtilisateur&,int,uchar,Donnees*);
	//
signals:

	void choix_attaque(const QString&,int);
private slots:

	void maj_description(const QString&);
};

#endif // FICHEPKUTEQUIPE_H
