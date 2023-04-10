#ifndef PANNEAUEDITEURENV_H
#define PANNEAUEDITEURENV_H
#include <QWidget>
#include "serialisable/base_donnees/hashmap.h"
class Environnement;
class Tuile;
class QButtonGroup;
class Fenetre;
class QSpinBox;
class QTableWidget;
class Fenetre;
class QComboBox;
class QPushButton;
class PanneauEditerEnv: public QWidget{

	Q_OBJECT

	int langue;

	Fenetre *fenetre;

	QButtonGroup *groupe_type_tuile;

	QComboBox *type_env;

	QSpinBox *muret_h;

	QSpinBox *muret_v;

	QSpinBox *appar_per;

	QTableWidget *table_appar_marche;

	QTableWidget *table_appar_peche_canne;

	QTableWidget *table_appar_peche_super_canne;

	QTableWidget *table_appar_peche_mega_canne;

	QPushButton *editer_perso;

	QPushButton *editer_dresseur_ligue;

	QPushButton *editer_dresseur;
	
	QPushButton *editer_champion;

	QComboBox *choix_imgs_arbres;
	
	QComboBox *choix_imgs_rochers_destructibles;

	QComboBox *choix_imgs_rochers_amovibles;

	QComboBox *choix_imgs_tourbillons;

	QComboBox *choix_imgs_tuiles;

	QPushButton *editer_pk_leg;

	QPushButton *editer_don_pk;

	QPushButton *editer_objet;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

	enum RolesTuile{AUTRE_PERSO,DRESSEUR_LIGUE,DRESSEUR,CHAMPION,ARBRE,ROCHER_AMOV,ROCHER_DESTR,TOURBILLON,ECHANGE,PK_LEG,DON_PK,OBJET,RIEN};

	RolesTuile selection;
public:

	static Environnement *_environnement_en_cours_;

	static Tuile *_tuile_en_cours_;

	PanneauEditerEnv(int,Fenetre*,Environnement *_environnement_en_cours=NULL);

	void activer();

	void ajouter_arbre_image(const QString&);

	void ajouter_rocher_destructible_image(const QString&);

	void ajouter_rocher_amovible_image(const QString&);

	void ajouter_tourbillon_image(const QString&);

	void ajouter_tuile_image(const QString&);

	void maj_env();

	void maj_env(const QPair<QPair<int,int>,QPair<int,int> >&);

	int ligne_act_per()const;

	void maj_appar_per();

	int ligne_act_canne()const;

	void maj_appar_canne();

	int ligne_act_super_canne()const;

	void maj_appar_super_canne();

	int ligne_act_mega_canne()const;

	void maj_appar_mega_canne();

	virtual ~PanneauEditerEnv();

signals:

	void image_tuile_changee(const QImage&);

private slots:

	void activer_bouton(int);

	void maj_image_tuile(const QString&);

	void maj_nb_pas();

	void maj_muret();

	void maj_type_env();

};

#endif


