#ifndef DIALOGUEDRESSEUR_H
#define DIALOGUEDRESSEUR_H
#include <QDialog>
#include <QPair>
#include <QList>
#include "serialisable/pokemon/pokemondresse.h"
#include "serialisable/base_donnees/hashmap.h"
class Champion;
class Dresseur1;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QTableWidget;
class QTextEdit;
class QLabel;
/***/
class DialogueDresseur: public QDialog{

	Q_OBJECT

	bool rejeter;

	int indice_eq;

	int langue;

	QList<QPair<QList<PokemonDresse>,int> > equipes;

	//personnage
	QList<QLineEdit*> noms;//QString

	QComboBox *nom_miniature;//QString

	QSpinBox *orientation_h;
	QSpinBox *orientation_v;

	//dresseur:
	//equipes
	QTableWidget *table_equipes;
	//equipe selectionne
	QTableWidget *table_equipe;

	QComboBox *nom_image;//QString

	QTextEdit *message_fin_combat;//QString

	QTextEdit *message_debut_combat;//QString

	QSpinBox *multiplicite_combat;//uchar (1-4)

	//int recompense_base;

	//champion:
	//QLineEdit *badge;//QString
	QList<QLineEdit*> badges;

	QComboBox *ct;//uchar
	
	QLabel *attaque_ct;//nom de l'attaque ct

	QComboBox *cs;//uchar

	QLabel *attaque_cs;//nom de l'attaque cs

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

	void maj_equipe();

public:

	DialogueDresseur(int,bool,QWidget*);

	void maj_dresseur(Dresseur1*);

	void maj_champion(Champion*);

	Dresseur1 nv_dresseur()const;

	Champion nv_champion()const;

	bool rejete()const;

	virtual void closeEvent(QCloseEvent*);

private slots:

	void ajouter_equipe();

	void inserer_equipe();

	void supprimer_equipe();

	void editer_equipe();

	void acceptation();

	void maj_equipe(int);

	void maj_ct(const QString&);

	void maj_cs(const QString&);
};
#endif



