#ifndef ACTION_H
#define ACTION_H
#include <QAction>
#include <QStringList>

class Action:public QAction{

	/**Noms dans les différentes langues*/
	QStringList noms;

public:

	/***/
	Action(const QString&,int);

	/***/
	void maj_langue(int);
};

#endif


