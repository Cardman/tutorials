#ifndef MESTHREAD_H
#define MESTHREAD_H

#include <QThread>

class MesThread : public QThread
{
    Q_OBJECT
	bool arreter;
	bool finiAuBout;
protected:
	bool estArrete()const;
	void finirAuBout();
public:
    explicit MesThread(QObject *parent = 0);
	void arreterTache();
	bool aFiniAuBout()const;
signals:
	void avancementTraitement(int);
	void changementEtape(const QString&,int);
	void etapeTraitement(const QString&);
public slots:
    
};

#endif // MESTHREAD_H
