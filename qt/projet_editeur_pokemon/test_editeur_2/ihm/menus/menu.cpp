#include "ihm/menus/menu.h"
#include "base_donnees/import.h"
Menu::Menu(const QString& _nom,int _langue):QMenu(_nom){
	noms=Import::_noms_menus_.valeur(_nom);
	maj_langue(_langue);
}

void Menu::maj_langue(int _langue){
	setTitle(noms[_langue]);
}


