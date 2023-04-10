#ifndef DIALOGUEFICHIERS_H
#define DIALOGUEFICHIERS_H
#include <QDialog>
#include <QCloseEvent>
#include <QString>
#include "serialisable/base_donnees/hashmap.h"
class QModelIndex;
class ListeFichiers;
class ListeDossiers;
class QLineEdit;
class DialogueFichiers: public QDialog{

	Q_OBJECT

	QString nom_fichier;

	bool clique_image;

	ListeFichiers *ls_fichiers;

	ListeDossiers *ls_dossiers;

	QLineEdit *champ_fichier;

	int action;

	int type;

	int langue;

	static HashMap<QString,QStringList> init_elements_ihm();

	QString traduire(const QString&)const;

	const static HashMap<QString,QStringList> _elements_ihm_;

protected:
	void closeEvent(QCloseEvent*);
public:

	enum Actions{CHARGER,SAUVEGARDER,EXPORTER};

	DialogueFichiers(const QString&,int,Actions,QWidget *_parent=NULL);

	QString nom_fic()const;

signals:

private slots:

	void sauvegarde();

	void choix_fichier(const QModelIndex& indice);

};

#endif


