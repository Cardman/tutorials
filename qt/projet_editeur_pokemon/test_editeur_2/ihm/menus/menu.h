#ifndef MENU_H
#define MENU_H
#include <QMenu>
#include <QStringList>

class Menu:public QMenu{

	/**Noms dans les différentes langues*/
	QStringList noms;

public:

	/***/
	Menu(const QString&,int);

	/***/
	void maj_langue(int);
};

#endif


