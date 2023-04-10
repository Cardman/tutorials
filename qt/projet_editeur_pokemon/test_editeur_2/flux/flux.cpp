#include "flux/flux.h"
#include <QFile>
#include <cstdlib>
#include <limits.h>
#include <QImage>

Flux::Flux(){
	lect_ecr="";
	position=0;
	taille=0;
}

/*void Flux::ecrire(QTextStream& _out)const{
	_out<<lect_ecr
}

void Flux::lire(QTextStream& _in){
	lect_ecr=_in.readAll()
}*/

void Flux::ecrire(const QString& _out)const{
	QFile fic_(_out);
	if(fic_.open(QIODevice::WriteOnly|QIODevice::Text)){
		QTextStream out_(&fic_);
		out_<<lect_ecr;
		fic_.close();
	}
}

void Flux::lire(const QString& _in){
	QFile fic_(_in);
	if(fic_.open(QIODevice::ReadOnly|QIODevice::Text)){
		QTextStream in_(&fic_);
		lect_ecr=in_.readAll();
		taille=lect_ecr.size();
		fic_.close();
	}
}

Flux& operator<<(Flux& _out,const qint8& _qint8){
	if(_qint8>=0){
		if(_qint8<16){
			_out.lect_ecr+="0";
		}
		_out.lect_ecr+=QString::number(_qint8,16);
	}else{
		_out.lect_ecr+=QString::number(_qint8+UCHAR_MAX+1,16);
	}
	//_out.taille+=2;
	return _out;
}

Flux& operator>>(Flux& _in,qint8& _qint8){
	if(_in.position>=_in.taille){
		throw "fin";
	}
	int elt_=_in.lect_ecr.mid(_in.position,2).toInt(NULL,16);
	if(elt_>=CHAR_MAX){
		elt_-=UCHAR_MAX+1;
	}
	_qint8=(qint8)elt_;
	_in.position+=2;
	return _in;
}

Flux& operator<<(Flux& _out,const quint8& _quint8){
	if(_quint8<16){
		_out.lect_ecr+="0";
	}
	_out.lect_ecr+=QString::number(_quint8,16);
	return _out;
}

Flux& operator>>(Flux& _in,quint8& _quint8){
	if(_in.position>=_in.taille){
		throw "fin";
	}
	int elt_=_in.lect_ecr.mid(_in.position,2).toInt(NULL,16);
	_quint8=(qint8)elt_;
	_in.position+=2;
	return _in;
}

Flux& operator<<(Flux& _out,const qint16& _qint16){
	//qint16 copie_=_qint16
	quint16 copie_=_qint16;
	/*if(copie_<0){
		copie_+=USHRT_MAX
	}*/
	quint8 ecr_=copie_>>8;
	_out<<ecr_;
	ecr_=copie_%(UCHAR_MAX+1);
	_out<<ecr_;
	return _out;
}

Flux& operator>>(Flux& _in,qint16& _qint16){
	quint8 lect_;
	_in>>lect_;
	_qint16=lect_*(UCHAR_MAX+1);
	_in>>lect_;
	_qint16+=lect_;
	/*if(_qint16>=SHRT_MAX){
		_qint16-=USHRT_MAX
	}*/
	return _in;
}

Flux& operator<<(Flux& _out,const quint16& _quint16){
	quint16 copie_=_quint16;
	quint8 ecr_=copie_>>8;
	_out<<ecr_;
	ecr_=copie_%(UCHAR_MAX+1);
	_out<<ecr_;
	return _out;
}

Flux& operator>>(Flux& _in,quint16& _quint16){
	quint8 lect_;
	_in>>lect_;
	_quint16=lect_*(UCHAR_MAX+1);
	_in>>lect_;
	_quint16+=lect_;
	return _in;
}

Flux& operator<<(Flux& _out,const qint32& _qint32){
	quint32 copie_=_qint32;
	/*if(copie_<0){
		copie_+=UINT_MAX
	}*/
	quint16 ecr_=copie_>>16;
	_out<<ecr_;
	ecr_=copie_%(USHRT_MAX+1);
	_out<<ecr_;
	return _out;
}

Flux& operator>>(Flux& _in,qint32& _qint32){
	quint16 lect_;
	_in>>lect_;
	_qint32=lect_*(USHRT_MAX+1);
	_in>>lect_;
	_qint32+=lect_;
	/*if(_qint32>=INT_MAX){
		_qint32-=UINT_MAX
	}*/
	return _in;
}

Flux& operator<<(Flux& _out,const quint32& _quint32){
	quint32 copie_=_quint32;
	quint16 ecr_=copie_>>16;
	_out<<ecr_;
	ecr_=copie_%(USHRT_MAX+1);
	_out<<ecr_;
	return _out;
}

Flux& operator>>(Flux& _in,quint32& _quint32){
	quint16 lect_;
	_in>>lect_;
	_quint32=lect_*(USHRT_MAX+1);
	_in>>lect_;
	_quint32+=lect_;
	return _in;
}

Flux& operator<<(Flux& _out,const qint64& _qint64){
	quint64 copie_=_qint64;
	/*if(copie_<0){
		copie_+=ULONG_LONG_MAX
	}*/
	quint32 ecr_=copie_>>32;
	_out<<ecr_;
	ecr_=copie_%((quint64)UINT_MAX+1);
	_out<<ecr_;
	return _out;
}

Flux& operator>>(Flux& _in,qint64& _qint64){
	quint32 lect_;
	_in>>lect_;
	_qint64=lect_*((quint64)UINT_MAX+1);
	_in>>lect_;
	_qint64+=lect_;
	/*if(_qint64>=LONG_LONG_MAX){
		_qint64-=ULONG_LONG_MAX
	}*/
	return _in;
}

Flux& operator<<(Flux& _out,const quint64& _quint64){
	quint64 copie_=_quint64;
	quint32 ecr_=copie_>>32;
	_out<<ecr_;
	ecr_=copie_%((quint64)UINT_MAX+1);
	_out<<ecr_;
	return _out;
}

Flux& operator>>(Flux& _in,quint64& _quint64){
	quint32 lect_;
	_in>>lect_;
	_quint64=lect_*((quint64)UINT_MAX+1);
	_in>>lect_;
	_quint64+=lect_;
	return _in;
}

Flux& operator<<(Flux& _out,const QString& _qstring){
	quint32 taille_=_qstring.size();
	/**
	if(taille_==0){
		_out.lect_ecr+="X"
		return _out
	}
	*/
	_out<<taille_;
	for(quint32 i=0;i<taille_;i++){
		/*quint8 car_=_qstring[i].unicode()
		_out<<car_*/
		_out<<(quint8)_qstring[i].unicode();
	}
	return _out;
}

Flux& operator>>(Flux& _in,QString& _qstring){
	/**
	if(_in.position>=_in.taille){
		throw "fin"
	}
	if(_in.lect_ecr[_in.position]==QChar('X')){
		_qstring.clear()
		_in.position++
		return _in
	}
	*/
	quint32 taille_=0;
	_in>>taille_;
	int t_=(int)taille_;
	_qstring.clear();
	for(int i=0;i<t_;i++){
		quint8 car_=0;
		_in>>car_;
		_qstring+=QChar(car_);
	}
	return _in;
}


Flux& operator<<(Flux& _out,const QImage&){
	return _out;
}

Flux& operator>>(Flux& _in,QImage&){
	return _in;
}

Flux& operator<<(Flux& _out,const bool& _bool){
	if(_bool){
		_out<<(qint8)1;
	}else{
		_out<<(qint8)0;
	}
	return _out;
}

Flux& operator>>(Flux& _in,bool& _bool){
	qint8 qint8_;
	_in>>qint8_;
	_bool=qint8_==1;
	return _in;
}
