#ifndef DIALOGUEPERSONNAGE_H
#define DIALOGUEPERSONNAGE_H
#include <QStringList>
#include <QDialog>
#include "serialisable/pokemon/pokemon.h"
#include "serialisable/base_donnees/hashmap.h"
class QLineEdit;
class QButtonGroup;
class QComboBox;
class QSpinBox;
class QPushButton;
class Personnage;
/***/
class DialoguePersonnage:public QDialog{

	Q_OBJECT

	bool rejeter;

	int langue;

	QButtonGroup *choix;

	QList<QLineEdit*> noms;//QString

	QComboBox *nom_miniature;//QString

	QSpinBox *orientation_h;
	QSpinBox *orientation_v;

	QStringList achat_objets;
	QPushButton *b_editer_achat_objets;

	QList<uchar> achat_ct;
	QPushButton *b_editer_achat_ct;

	QList<uchar> don_cs;
	QPushButton *b_editer_don_cs;
	
	//soin_pk
	
	QString don_obj;
	QPushButton *b_editer_don_obj;
	
	
	//lieu_faire_vivre
	
	//pension_pk
	
	//move_tutors
	
	Pokemon don_pk;
	QPushButton *b_editer_don_pk;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

public:

	enum Roles{ACHAT_OBJS,ACHAT_CTS,DON_CS,SOIN_PK,DON_OBJS,LIEU_VIVRE,PENSION,MOVE_TUTORS,DON_PK,RIEN};

	DialoguePersonnage(int,QWidget*);

	QPair<int,Personnage> nv_personnage()const;

	void maj_personnage(QPair<int,Personnage*>);

	void editer_achat_objets(const QStringList&);
	void editer_achat_ct(const QList<uchar>&);
	void editer_don_cs(const QList<uchar>&);
	void editer_don_obj(const QString&);
	void editer_don_pk(const Pokemon&);

	QStringList nv_achat_objets()const;
	QList<uchar> nv_achat_ct()const;
	QList<uchar> nv_don_cs()const;
	QString nv_don_obj()const;
	Pokemon nv_don_pk()const;

	virtual ~DialoguePersonnage();

	bool rejete()const;

	virtual void closeEvent(QCloseEvent*);

private slots:

	void activer_bouton(int);

	void maj_achat_objets();

	void maj_achat_capsules();

	void maj_don_capsules();

	void maj_don_objets();

	void maj_don_pokemon();

	void acceptation();
};


#endif


