#ifndef FLUX_H
#define FLUX_H
#include <QString>
#include <QTextStream>
#include <QPair>
#include <QList>
class QImage;

class Flux{

	QString lect_ecr;

	int position;

	int taille;

public:

	Flux();

	/*void ecrire(QTextStream&)const;

	void lire(QTextStream&);*/

	void ecrire(const QString&)const;

	void lire(const QString&);

	friend Flux& operator<<(Flux&,const qint8&);
	friend Flux& operator>>(Flux&,qint8&);
	friend Flux& operator<<(Flux&,const quint8&);
	friend Flux& operator>>(Flux&,quint8&);
	friend Flux& operator<<(Flux&,const QString&);
	friend Flux& operator>>(Flux&,QString&);
};

Flux& operator<<(Flux&,const qint8&);
Flux& operator>>(Flux&,qint8&);
Flux& operator<<(Flux&,const quint8&);
Flux& operator>>(Flux&,quint8&);
Flux& operator<<(Flux&,const qint16&);
Flux& operator>>(Flux&,qint16&);
Flux& operator<<(Flux&,const quint16&);
Flux& operator>>(Flux&,quint16&);
Flux& operator<<(Flux&,const qint32&);
Flux& operator>>(Flux&,qint32&);
Flux& operator<<(Flux&,const quint32&);
Flux& operator>>(Flux&,quint32&);
Flux& operator<<(Flux&,const qint64&);
Flux& operator>>(Flux&,qint64&);
Flux& operator<<(Flux&,const quint64&);
Flux& operator>>(Flux&,quint64&);
Flux& operator<<(Flux&,const QString&);
Flux& operator>>(Flux&,QString&);
Flux& operator<<(Flux&,const QImage&);
Flux& operator>>(Flux&,QImage&);
Flux& operator<<(Flux&,const bool&);
Flux& operator>>(Flux&,bool&);
template<typename T,typename S>
Flux& operator<<(Flux&,const QPair<T,S>&);
template<typename T,typename S>
Flux& operator>>(Flux&,QPair<T,S>&);
template<typename T>
Flux& operator<<(Flux&,const QList<T>&);
template<typename T>
Flux& operator>>(Flux&,QList<T>&);
template<typename T>
Flux& operator>>(Flux&,T*);
template<typename T>
Flux& operator<<(Flux&,T*);

template<typename T,typename S>
Flux& operator<<(Flux& _out,const QPair<T,S>& _paire){
	_out<<_paire.first;
	_out<<_paire.second;
	return _out;
}

template<typename T,typename S>
Flux& operator>>(Flux& _in,QPair<T,S>& _paire){
	_in>>_paire.first;
	_in>>_paire.second;
	return _in;
}

template<typename T>
Flux& operator<<(Flux& _out,const QList<T>& _liste){
	quint32 taille_=_liste.size();
	_out<<taille_;
	foreach(T t,_liste){
		_out<<t;
	}
	return _out;
}

template<typename T>
Flux& operator>>(Flux& _in,QList<T>& _liste){
	quint32 taille_;
	_in>>taille_;
	int t_=(int)taille_;
	_liste.clear();
	for(int i=0;i<t_;i++){
		T t_lu_=T();
		_in>>t_lu_;
		_liste<<t_lu_;
	}
	return _in;
}

template<typename T>
Flux& operator>>(Flux& _in,T*){
	return _in;
}
template<typename T>
Flux& operator<<(Flux& _in,T*){
	return _in;
}
#endif


