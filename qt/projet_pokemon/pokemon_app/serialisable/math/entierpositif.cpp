#include "serialisable/math/entierpositif.h"
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <climits>
const int EntierPositif::_base_numer_=10;
const qulonglong EntierPositif::_base_=EntierPositif::base();
const int EntierPositif::_log_base_=EntierPositif::log_base();

qulonglong EntierPositif::base(){
	qulonglong max_=ULONG_LONG_MAX;
	qulonglong copie_b=1;
	qulonglong div_=_base_numer_*_base_numer_;
	qulonglong copie_b2=1;
	while(max_>0){
		max_/=div_;
		copie_b=copie_b2;
		copie_b2*=_base_numer_;
	}
	return copie_b;
}

int EntierPositif::log_base(){
	int puissance10=0;
	qulonglong copie_b=1;
	while(copie_b<_base_){
		copie_b*=_base_numer_;
		puissance10++;
	}
	return puissance10;
}

EntierPositif::EntierPositif(const QString& _chaine){
	int puissance10_=EntierPositif::_log_base_;
	QString nb_lu_=_chaine;
	forever{
		if(nb_lu_.size()==1){
			break;
		}
		if(nb_lu_[0]!=QChar('0')){
			break;
		}
		nb_lu_=nb_lu_.mid(1);
	}
	for(int i=nb_lu_.length()-1;i>-1;i-=puissance10_){
		QString nb_lu2_;
		if(nb_lu_.length()>=puissance10_){
			nb_lu2_=nb_lu_.right(puissance10_);
			if(nb_lu_.length()>puissance10_){
				//nb_lu_.resize(nb_lu_.length()-puissance10_)
				nb_lu_.chop(puissance10_);
			}
		}else{
			nb_lu2_=nb_lu_;
		}
		gr_chiffres.prepend(nb_lu2_.toLongLong());
	}
}

EntierPositif::EntierPositif(){

}

EntierPositif::EntierPositif(long long _nombre){
	long long nombre_;
	if(_nombre<0){
		nombre_=-_nombre;
	}else{
		nombre_=_nombre;
	}
	unsigned long long quotient_;
	unsigned long long reste_;
	quotient_=nombre_/_base_;
	reste_=nombre_-quotient_*_base_;
	gr_chiffres<<reste_;
	while(quotient_>_base_){
		nombre_=quotient_;
		quotient_=nombre_/_base_;
		reste_=nombre_-quotient_*_base_;
		gr_chiffres.prepend(reste_);
	}
	if(quotient_!=0){
		gr_chiffres.prepend(quotient_);
	}
}

EntierPositif::EntierPositif(const QList<unsigned long long>& _composants){
	gr_chiffres=_composants;
}

unsigned long long EntierPositif::modulo_absolu_base()const{
	return gr_chiffres.last();
}

EntierPositif& EntierPositif::operator*=(const EntierPositif& _autre){
	EntierPositif resultat_(0);
	EntierPositif tmp_;
	int longueur1_=gr_chiffres.size();
	int longueur2_=_autre.gr_chiffres.size();
	int expo_=0;
	if(longueur1_<longueur2_){
		for(int i=longueur1_-1;i>-1;i--){
			tmp_=_autre.multiplier(gr_chiffres[i]);
			for(int j=0;j<expo_;j++){
				tmp_.gr_chiffres<<0;
			}
			expo_++;
			resultat_+=tmp_;
		}
	}else{
		for(int i=longueur2_-1;i>-1;i--){
			tmp_=multiplier(_autre.gr_chiffres[i]);
			for(int j=0;j<expo_;j++){
				tmp_.gr_chiffres<<0;
			}
			expo_++;
			resultat_+=tmp_;
		}
	}
	gr_chiffres=resultat_.gr_chiffres;
	return (*this);
}

EntierPositif& EntierPositif::operator+=(const EntierPositif& _autre){
	long long retenue_=0;
	unsigned long long somme_;
	long long reste_;
	int longueur1_=gr_chiffres.size();
	int longueur2_=_autre.gr_chiffres.size();
	int i_=longueur1_-1;
	int j_=longueur2_-1;
	while(i_>-1&&j_>-1){
		somme_=gr_chiffres[i_]+_autre.gr_chiffres[j_]+retenue_;
		if(somme_<_base_){
			gr_chiffres[i_]=somme_;
			retenue_=0;
		}else{
			reste_=somme_-_base_;
			gr_chiffres[i_]=reste_;
			retenue_=1;
		}
		i_--;
		j_--;
	}
	if(longueur1_>longueur2_){
		while(i_>-1){
			somme_=gr_chiffres[i_]+retenue_;
			if(somme_<_base_){
				gr_chiffres[i_]=somme_;
				retenue_=0;
			}else{
				reste_=somme_-_base_;;
				gr_chiffres[i_]=reste_;
				retenue_=1;
			}
			i_--;
		}
	}else if(longueur1_<longueur2_){
		while(j_>-1){
			somme_=_autre.gr_chiffres[j_]+retenue_;
			if(somme_<_base_){
				gr_chiffres.prepend(somme_);
				retenue_=0;
			}else{
				reste_=somme_-_base_;
				gr_chiffres.prepend(reste_);
				retenue_=1;
			}
			j_--;
		}
	}
	if(retenue_==1){
		gr_chiffres.prepend(retenue_);
	}
	return (*this);
}

EntierPositif& EntierPositif::operator-=(const EntierPositif& _autre){
	unsigned long long retenue_=0;
	int longueur1_=gr_chiffres.size();
	int longueur2_=_autre.gr_chiffres.size();
	long long diff_;
	int k_=longueur1_-1;
	int l_=longueur2_-1;
	while(k_>-1&&l_>-1){
		if(gr_chiffres[k_]>=_autre.gr_chiffres[l_]+retenue_){
			diff_=gr_chiffres[k_]-_autre.gr_chiffres[l_]-retenue_;
			retenue_=0;
		}else{
			diff_=gr_chiffres[k_]+_base_-_autre.gr_chiffres[l_]-retenue_;
			retenue_=1;
		}
		gr_chiffres[k_]=diff_;
		k_--;
		l_--;
	}
	if(longueur1_>longueur2_){
		while(k_>-1){
			if(gr_chiffres[k_]>=retenue_){
				diff_=gr_chiffres[k_]-retenue_;
				retenue_=0;
			}else{
				diff_=gr_chiffres[k_]+_base_-retenue_;
				retenue_=1;
			}
			gr_chiffres[k_]=diff_;
			k_--;
		}
	}
	k_=0;
	while(k_<gr_chiffres.size()-1&&gr_chiffres[k_]==0){
		gr_chiffres.removeAt(k_);
	}
	return (*this);
}

EntierPositif EntierPositif::soustraire(const EntierPositif& celui_ci,const EntierPositif& autre){
	EntierPositif res_=celui_ci;
	res_-=autre;
	return res_;
}

QPair<QList<unsigned long long> ,QList<unsigned long long> > EntierPositif::division_euclidienne(const EntierPositif& _autre)const{
	QPair<QList<unsigned long long> ,QList<unsigned long long> > quotient_reste_;
	if(plus_petit_que(_autre)){
		//quotient_reste_.first=EntierPositif(0)
		quotient_reste_.first<<0;
		//quotient_reste_.second.gr_chiffres=gr_chiffres
		//quotient_reste_.second.signe=signe
		//quotient_reste_.second=(*this)
		quotient_reste_.second=gr_chiffres;
		return quotient_reste_;
	}
	int taille1_=gr_chiffres.size();
	int taille2_=_autre.gr_chiffres.size();
	int nb_nombres_;
	unsigned long long chiffre_min_=0;
	unsigned long long chiffre_max_;
	EntierPositif reste_;
	EntierPositif quotient_;
	int ch_i_;
	if(gr_chiffres[0]>=_autre.gr_chiffres[0]){
		chiffre_max_=gr_chiffres[0]/_autre.gr_chiffres[0];
		/*chiffre_max_>=1 car gr_chiffres[0]>=_autre.gr_chiffres[0] et le quotient entier entre un dividende plus grand que le diviseur est >= 1
		*/
		nb_nombres_=taille1_-taille2_+1;
		for(int i=0;i<taille2_;i++){
			reste_.gr_chiffres<<gr_chiffres[i];
		}
		ch_i_=taille2_;
	}else{
		chiffre_max_=(gr_chiffres[0]*_base_+gr_chiffres[1])/_autre.gr_chiffres[0];
		/*_base_>=_autre.gr_chiffres[0], car _base_ est la _base_ de numérotation.
		gr_chiffres[0]>=1, car (*this)>=_autre et _autre>0 => (*this)>0 => gr_chiffres[0]>=1
		donc gr_chiffres[0]*_base_>=_autre.gr_chiffres[0]
		donc gr_chiffres[0]*_base_+gr_chiffres[1]>=_autre.gr_chiffres[0]
		donc chiffre_max_>=1*/
		nb_nombres_=taille1_-taille2_;
		for(int i=0;i<taille2_+1;i++){
			reste_.gr_chiffres<<gr_chiffres[i];
		}
		ch_i_=taille2_+1;
	}
	//chiffre_max_>=1
	quotient_.gr_chiffres<<reste_.division_temporaire(_autre,chiffre_min_,chiffre_max_);
	reste_-=_autre.multiplier(quotient_.gr_chiffres.last());
	for(int i=1;i<nb_nombres_;i++){
		while(!reste_.gr_chiffres.isEmpty()&&reste_.gr_chiffres[0]==0){
			reste_.gr_chiffres.removeAt(0);
		}
		reste_.gr_chiffres<<gr_chiffres[ch_i_];
		if(reste_.plus_petit_que(_autre)){
			quotient_.gr_chiffres<<0;
		}else{
			if(reste_.gr_chiffres[0]>=_autre.gr_chiffres[0]){
				chiffre_max_=reste_.gr_chiffres[0]/_autre.gr_chiffres[0];
				/*chiffre_max_>=1 car reste_.gr_chiffres[0]>=_autre.gr_chiffres[0] et le quotient entier entre un dividende plus grand que le diviseur est >= 1*/
			}else{
				chiffre_max_=(reste_.gr_chiffres[0]*_base_+reste_.gr_chiffres[1])/_autre.gr_chiffres[0];
				/*_base_>=_autre.gr_chiffres[0], car _base_ est la _base_ de numérotation.
				reste_.gr_chiffres[0]>=1, car reste_>=_autre et _autre>0 => reste_>0 => gr_chiffres[0]>=1
				donc gr_chiffres[0]*_base_>=_autre.gr_chiffres[0]
				donc gr_chiffres[0]*_base_+gr_chiffres[1]>=_autre.gr_chiffres[0]
				donc chiffre_max_>=1*/
			}
			//chiffre_max_>=1
			quotient_.gr_chiffres<<reste_.division_temporaire(_autre,chiffre_min_,chiffre_max_);
			reste_-=_autre.multiplier(quotient_.gr_chiffres.last());
		}
		ch_i_++;
	}
	quotient_reste_.first=quotient_.gr_chiffres;
	while(reste_.gr_chiffres.size()>1&&reste_.gr_chiffres[0]==0){
		reste_.gr_chiffres.removeAt(0);
	}
	quotient_reste_.second=reste_.gr_chiffres;
	return quotient_reste_;
}

unsigned long long EntierPositif::division_temporaire(const EntierPositif& _diviseur,unsigned long long _min,unsigned long long _max)const{
	/*_max>=1, car pendant les appels de cette fonction passe le dernier argument avec une valeur >= 1
	_min==0, car pendant les appels de cette fonction passe le premier argument avec une valeur == 0*/
	unsigned long long quotient_=(_min+_max)/2;
	if(_min==quotient_){
		//quotient_==1, car _min=0 et _min=quotient_ => quotient_=0 => _min+_max <= 1 => _max <= 1 => _max = 1
		//De même _max = 1 => _min+_max/2 (division entière) = 0 => quotient_=0 => quotient_=_min
		return 1;
	}
	//_max>=2
	EntierPositif prod_=_diviseur.multiplier(_max);
	if(!prod_.plus_grand_que(*this)){
		return _max;
	}
	/*_diviseur*_max=prod_>(*this)*/
	/*On a toujours _min*_diviseur<=(*this), car _min==0*/
	while(_min<_max-1){
		quotient_=(_min+_max)/2;
		prod_=_diviseur.multiplier(quotient_);
		if(prod_.plus_grand_que(*this)){
			_max=quotient_;
		}else{
			_min=quotient_;
		}
	}
	/*_max-1<=_min<_max, donc _max-1==_min et c'est le min qui doit etre retourne, car _min*_diviseur<=(*this) et _diviseur*_max>(*this)*/
	return _min;
}

bool EntierPositif::plus_petit_que(const EntierPositif& _autre)const{
	if(gr_chiffres.size()>_autre.gr_chiffres.size()){
		return false;
	}
	if(gr_chiffres.size()<_autre.gr_chiffres.size()){
		return true;
	}
	for(int i=0;i<gr_chiffres.size();i++){
		long long entier1_=gr_chiffres[i];
		long long entier2_=_autre.gr_chiffres[i];
		if(entier1_<entier2_){
			return true;
		}
		if(entier1_>entier2_){
			return false;
		}
	}
	return false;
}

bool EntierPositif::plus_grand_que(const EntierPositif& _autre)const{
	if(gr_chiffres.size()>_autre.gr_chiffres.size()){
		return true;
	}
	if(gr_chiffres.size()<_autre.gr_chiffres.size()){
		return false;
	}
	for(int i=0;i<gr_chiffres.size();i++){
		long long entier1_=gr_chiffres[i];
		long long entier2_=_autre.gr_chiffres[i];
		if(entier1_<entier2_){
			return false;
		}
		if(entier1_>entier2_){
			return true;
		}
	}
	return false;
}


bool EntierPositif::egal_a(const EntierPositif& _autre)const{
	return gr_chiffres==_autre.gr_chiffres;
}

bool EntierPositif::estNul()const{
	return gr_chiffres[0]==0;
}

EntierPositif EntierPositif::multiplier(long long _autre)const{
	EntierPositif resultat_;
	if(_autre==0L||(gr_chiffres.size()==1&&gr_chiffres[0]==0)){
		resultat_.gr_chiffres<<0;
		return resultat_;
	}
	long long quotient_;
	long long retenue_=0;
	long long reste_;
	for(int i=gr_chiffres.size()-1;i>-1;i--){
		quotient_=gr_chiffres[i]*_autre+retenue_;
		retenue_=quotient_/_base_;
		reste_=quotient_-_base_*retenue_;
		resultat_.gr_chiffres.prepend(reste_);
	}
	if(retenue_>0){
		resultat_.gr_chiffres.prepend(retenue_);
	}
	return resultat_;
}

QString EntierPositif::chaine()const{
	QString retour_;
	int indice_=0;
	int puissance10_=log_base();
	//puissance10 vaut log10(_base_)
	foreach(unsigned long long c,gr_chiffres){
		if(indice_>0){
			if(c==0){
				for(int i=0;i<puissance10_;i++){
					retour_+="0";
				}
			}else{
				int puissance_=0;
				unsigned long long copie_=c;
				while(copie_>0){
					copie_/=_base_numer_;
					puissance_++;
				}
				int nb_zeros_=puissance10_-puissance_;
				for(int i=0;i<nb_zeros_;i++){
					retour_+="0";
				}
				retour_+=QString::number(c);
			}
		}else{
			retour_+=QString::number(c);
		}
		indice_++;
	}
	return retour_;

}

void EntierPositif::serialiser(Flux& _out)const{
	_out<<gr_chiffres;
}

void EntierPositif::deserialiser(Flux& _in){
	_in>>gr_chiffres;
}

Flux & operator <<(Flux& out,const EntierPositif& _EntierPositif){
	_EntierPositif.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,EntierPositif& _EntierPositif){
	_EntierPositif.deserialiser(in);
	return in;
}



