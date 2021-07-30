#include "mesthread.h"

MesThread::MesThread(QObject *parent) :
    QThread(parent),arreter(false),finiAuBout(false)
{
}

void MesThread::finirAuBout(){
	finiAuBout=true;
}

bool MesThread::aFiniAuBout()const{
	return finiAuBout;
}

bool MesThread::estArrete()const{
	return arreter;
}

void MesThread::arreterTache(){
	arreter=true;
}
