#include <QThread>
class Donnees;
class InitDonnees: public QThread{

	Q_OBJECT

	Donnees *donnees;

signals:

	void avancement(int);

public:

	InitDonnees();

	Donnees *res()const;

	void run();
};


