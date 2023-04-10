#ifndef DIALOGUEEDITEURMAP
#define DIALOGUEEDITEURMAP
#include "serialisable/base_donnees/hashmap.h"
#include <QDialog>
class GrilleMap;
class QComboBox;
class QCloseEvent;
/***/
class DialogueEditeurMap: public QDialog{

	Q_OBJECT

	GrilleMap *grille;

	QPair<int,int> coords;

	int langue;

	bool rejete;

	QComboBox *elements_map;

	HashMap<QPair<int,int>,QString> images_minimap;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

	bool carte_valide()const;

public:

	DialogueEditeurMap(int,QWidget*,const HashMap<QPair<int,int>,QString>&);

	bool rejet()const;

	HashMap<QPair<int,int>,QString> carte_modif()const;

	virtual void closeEvent(QCloseEvent*);

private slots:

	/***/
	void ajouter_ligne_ht_plateau();

	/***/
	void ajouter_ligne_bas_plateau();

	/***/
	void ajouter_col_gauche_plateau();

	/***/
	void ajouter_col_droite_plateau();

	/***/
	void ajouter_lignes_ht_plateau();

	/***/
	void ajouter_lignes_bas_plateau();

	/***/
	void ajouter_cols_gauche_plateau();

	/***/
	void ajouter_cols_droite_plateau();

	/***/
	void supprimer_ligne_map();

	/***/
	void supprimer_colonne_map();

	/***/
	void supprimer_tuile_map();

	/***/
	void maj_tuile_courante();

	/***/
	void maj_coords(const QPair<int,int>&);

	void acceptation();
};

#endif


