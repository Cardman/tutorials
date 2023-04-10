#ifndef LISTEDOSSIERS_H
#define LISTEDOSSIERS_H

#include <QTreeWidget>
class QModelIndex;
class QFileSystemModel;
/***/
class ListeDossiers : public QTreeView
{

	/***/
	QFileSystemModel *modele_dossier;

	Q_OBJECT
protected:
	void mouseReleaseEvent(QMouseEvent*);
public:
	ListeDossiers(const QString&,const QString&,QWidget *_parent=NULL);

signals:
	void dossier_selectionne(const QString&);

};

#endif // LISTEFICHIERS_H



