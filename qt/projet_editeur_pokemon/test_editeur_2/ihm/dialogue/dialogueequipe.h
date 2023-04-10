#ifndef DIALOGUEEQUIPE_H
#define DIALOGUEEQUIPE_H
#include <QDialog>
#include <QPair>
#include <QList>
#include "serialisable/pokemon/pokemondresse.h"
#include "serialisable/base_donnees/hashmap.h"
class QTableWidget;
class QLabel;
class QTextEdit;
class QLineEdit;
/***/
class DialogueEquipe: public QDialog{

	bool rejeter;

	QList<PokemonDresse> equipe;

	QTableWidget *table_equipe;

	QLabel *nom;

	QLabel *niveau;

	QLabel *genre;

	QLabel *capacite;

	QLabel *objet;

	QTextEdit *attaques;

	QLineEdit *champ_recompense;

	int recompense;

	int langue;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	static QString traduire(const QStringList&,const QString&,int);

	static QString traduire_revert(const QStringList&,const QString&,int);

	void maj_equipe();

	Q_OBJECT

public:

	DialogueEquipe(int,QWidget*);

	void maj_equipe_recompense(const QPair<QList<PokemonDresse>,int>&);

	QPair<QList<PokemonDresse>,int> equipe_recompense()const;

	bool rejete()const;

	virtual void closeEvent(QCloseEvent*);

private slots:

	void ajouter_pokemon();

	void inserer_pokemon();

	void supprimer_pokemon();

	void editer_pokemon();

	void acceptation();

	void maj_description(int);
};
#endif



