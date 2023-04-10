#ifndef LISTEFICHIERS_H
#define LISTEFICHIERS_H

#include <QTreeWidget>
class QModelIndex;
class QFileSystemModel;
/***/
class ListeFichiers : public QTreeView
{

	/***/
	QFileSystemModel *modele_fichier;

	Q_OBJECT
protected:
	void mouseReleaseEvent(QMouseEvent*);
public:
	ListeFichiers(const QString&,QWidget *_parent=NULL);

signals:
	void fichier_selectionne(QModelIndex);

public slots:

	void maj_liste(const QString&);
};

#endif // LISTEFICHIERS_H



