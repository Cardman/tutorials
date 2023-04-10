#include "ihm/menus/action.h"
#include "base_donnees/import.h"
Action::Action(const QString& _nom,int _langue):QAction(_nom,NULL){
	noms=Import::_noms_menus_.valeur(_nom);
	maj_langue(_langue);
}

void Action::maj_langue(int _langue){
	setText(noms[_langue]);
}


