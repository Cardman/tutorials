#include "ihm/dialogue/liste/listedossiers.h"
#include <QFileSystemModel>

ListeDossiers::ListeDossiers(const QString& _ch,const QString& _racine,QWidget *_parent):QTreeView(_parent){
	modele_dossier=new QFileSystemModel();
	modele_dossier->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);;
	setModel(modele_dossier);
	setRootIndex(modele_dossier->setRootPath(_racine));
	setCurrentIndex(modele_dossier->index(_ch));
	setSortingEnabled(true);
}

void ListeDossiers::mouseReleaseEvent(QMouseEvent *_event){
	emit dossier_selectionne(modele_dossier->fileInfo(currentIndex()).absoluteFilePath());
}



