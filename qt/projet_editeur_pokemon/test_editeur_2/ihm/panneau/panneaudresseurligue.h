#ifndef PANNEAUDRESSEURLIGUE_H
#define PANNEAUDRESSEURLIGUE_H
#include <QLabel>
#include <QPair>
#include <QList>
#include "serialisable/pokemon/pokemondresse.h"
#include "serialisable/base_donnees/hashmap.h"
//class DresseurLigue;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QTableWidget;
class QTextEdit;
class Fenetre;
class EnvironnementLigue;
class Tuile;
/***/
class PanneauDresseurLigue: public QLabel{

	Q_OBJECT

	QList<QLineEdit*> noms_ligues;//QString

	int indice_eq;

	int langue;

	QList<PokemonDresse> equipe;
	int recompense;

	QComboBox *type_env;

	//personnage
	QList<QLineEdit*> noms;//QString

	QComboBox *nom_miniature;//QString

	QSpinBox *orientation_h;
	QSpinBox *orientation_v;

	QSpinBox *coord_h;
	QSpinBox *coord_v;

	//dresseur:
	//equipes
	QTableWidget *table_equipes;
	//equipe selectionne

	QLabel *nom_pk;

	QLabel *niveau;

	QLabel *genre;

	QLabel *capacite;

	QLabel *objet;

	QTextEdit *attaques;

	QLineEdit *champ_recompense;


	QComboBox *nom_image;//QString

	QTextEdit *message_fin_combat;//QString

	QTextEdit *message_debut_combat;//QString

	QSpinBox *multiplicite_combat;//uchar (1-4)

	QComboBox *choix_imgs_tuiles;
	//int recompense_base;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

public:

	static EnvironnementLigue *_environnement_ligue_en_cours_;

	static Tuile *_tuile_en_cours_;

	PanneauDresseurLigue(int,Fenetre*);

	void maj_dresseur();

	//DresseurLigue nv_dresseur()const;

	int ligne_courante()const;

	void maj_equipe();

	void maj_env(const QPair<QPair<int,int>,QPair<int,int> >&);

	void decrementer_ind_pk();

signals:

	void image_tuile_changee(const QImage&);

private slots:

	void maj_type_env();

	void maj_equipe(int);

	//void supprimer_pk();

	void maj_dresseur_revert();

	void maj_image_tuile(const QString&);
};
#endif



