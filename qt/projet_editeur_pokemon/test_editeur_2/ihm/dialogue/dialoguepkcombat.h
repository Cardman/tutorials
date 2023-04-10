#ifndef DIALOGUEPKCOMBAT_H
#define DIALOGUEPKCOMBAT_H
#include <QDialog>
#include <QStringList>
#include "serialisable/base_donnees/hashmap.h"
class QComboBox;
class QSpinBox;
class Pokemon;
class PokemonDresse;
class QTableWidget;
class QButtonGroup;
/***/
class DialoguePkCombat: public QDialog{

	Q_OBJECT

	int langue;

	QComboBox *nom_pk;

	QComboBox *genre_pk;

	QSpinBox *niveau_pk;

	QComboBox *capacite_pk;

	QComboBox *objet_pk;

	QButtonGroup *boutons_categ_attaques;

	QComboBox *nom_attaque_pk;

	QTableWidget *table_attaques;

	QStringList attaques;

	//Pokemon *pk_edite;

	//PokemonDresse *pk_dresse_edite;

	bool rejeter;

	int type_dialogue;

	int type_rencontre;

	enum CategorieAttaque{PHYSIQUE,SPECIALE,AUTRE};

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

	//static QString traduire(const QString&,int);

public:

	enum TypeDialogue{PK_DRESSE,PK_SAUVAGE,PK_DONNE,PK_LEG_FIXE,PK_DEPART};

	enum TypeRencontre{DEPLACEMENT,CANNE,SUPER_CANNE,MEGA_CANNE,RIEN};

	DialoguePkCombat(int,DialoguePkCombat::TypeDialogue,QWidget*,DialoguePkCombat::TypeRencontre,bool=false);

	void maj_pk_edite(Pokemon*);

	void maj_pk_dresse_edite(PokemonDresse*);

	Pokemon nv_pk()const;

	PokemonDresse nv_pk_dresse()const;

	bool rejete()const;

	virtual void closeEvent(QCloseEvent*);

	virtual ~DialoguePkCombat();

private slots:

	void maj_fct_nom_pk();

	void maj_fct_niveau_pk();

	void maj_fct_categ_attaques_pk(int);

	void ajout_attaque();

	void suppression_attaque();

	void acceptation();

};

#endif


