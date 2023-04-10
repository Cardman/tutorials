#ifndef INITBDD_H
#define INITBDD_H

#include <QThread>

class InitBDD: public QThread{

	Q_OBJECT

	int langue;

	qulonglong avancement;

signals:

	void nv_avanc(int);

public:

	static bool _fini_;

	InitBDD(int);

	void run();

public slots:

	void initialialiser();
};


#endif


