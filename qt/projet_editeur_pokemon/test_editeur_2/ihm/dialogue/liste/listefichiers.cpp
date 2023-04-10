#include "ihm/dialogue/liste/listefichiers.h"
#include <QFileSystemModel>

ListeFichiers::ListeFichiers(const QString& _ch,QWidget *_parent):QTreeView(_parent){
	modele_fichier=new QFileSystemModel();
	modele_fichier->setFilter(QDir::Files);
	setModel(modele_fichier);
	setRootIndex(modele_fichier->setRootPath(_ch));
	setCurrentIndex(modele_fichier->index(_ch));
	setSortingEnabled(true);
}

void ListeFichiers::mouseReleaseEvent(QMouseEvent *_event){
	emit fichier_selectionne(currentIndex());
}

void ListeFichiers::maj_liste(const QString& _dossier_parent){
	setRootIndex(modele_fichier->setRootPath(_dossier_parent));
	setCurrentIndex(modele_fichier->index(_dossier_parent));
}


