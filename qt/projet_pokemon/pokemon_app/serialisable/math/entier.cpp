#include "serialisable/math/entier.h"
#include <QList>
#include <QString>

Entier::Entier(){
	;
}

Entier::Entier(const QString& _chaine):EntierPositif(chaine_valeur_absolue(_chaine)){
	signe=!_chaine.startsWith("-");
}

Entier::Entier(qlonglong _entier_l):EntierPositif(_entier_l){
	signe=_entier_l>=0;
}

/*Entier::Entier(const Entier& _copie):EntierPositif(_copie){
	signe=_copie.signe
}*/

Entier::Entier(const QList<qulonglong>& _gr_chiffre,bool _signe):EntierPositif(_gr_chiffre){
	signe=_signe;
}

Entier::Entier(const EntierPositif& _pseudo_copie,bool _signe):EntierPositif(_pseudo_copie){
	signe=_signe;
}

QString Entier::chaine_valeur_absolue(const QString& _chaine){
	if(_chaine.startsWith("-")){
		return _chaine.mid(1);
	}
	return _chaine;
}

Entier::operator long long(){
	if(signe){
		return modulo_absolu_base();
	}
	return -((long long)modulo_absolu_base());
}

Entier Entier::parmi(const Entier& _nombre_total_elements)const{
	Entier cardinal_(1L);
	int nombre_;
	Entier pgcd_;
	QList<Entier> numerateur_;
	QList<Entier> denominateur_;
	Entier diff_total_partiel_=_nombre_total_elements-(*this);
	if(Entier(0)>diff_total_partiel_){
		return Entier(0);
	}
	unsigned long long abs_base_=modulo_absolu_base();
	unsigned long long diff_abs_base_=diff_total_partiel_.modulo_absolu_base();
	nombre_=(abs_base_>diff_abs_base_)?diff_abs_base_:abs_base_;
	for(int i=0;i<nombre_;i++){
		Entier temp_=Entier(i);
		numerateur_<<_nombre_total_elements-temp_;
		denominateur_<<Entier(nombre_)-temp_;
	}
	for(int i=0;i<nombre_-1;i++){
		for(int j=0;denominateur_[i]!=Entier(1);j++){
			pgcd_=numerateur_[j].pgcd(denominateur_[i]);
			numerateur_[j]=numerateur_[j]/pgcd_;
			denominateur_[i]=denominateur_[i]/pgcd_;
		}
	}
	for(int i=0;i<nombre_;i++){
		cardinal_=cardinal_*numerateur_[i];
	}
	return cardinal_;
}

Entier Entier::fact()const{//Attention a_ 40!
	Entier res_(1);
	Entier init_(0);
	Entier incr_(1);
	forever{
		if(init_==(*this)){
			break;
		}
		init_=init_+incr_;
		res_=res_*init_;
	}
	return res_;
}

Entier Entier::ppcm(const Entier& _b)const{
	Entier a_=(*this);
	if(a_==_b){
		return a_;
	}
	return a_/a_.pgcd(_b)*_b;
}

Entier Entier::pgcd(const Entier& _b)const{
	Entier reste_=(*this)%_b;
	Entier a_t_=(*this);
	Entier b_t_=_b;
	while(!reste_.estNul()){
		a_t_=b_t_;
		b_t_=reste_;
		reste_=a_t_%b_t_;
	}
	return b_t_;
}

Entier Entier::racine_abs(const Entier& _ordre)const{
	Entier absolu_ent_=absolu();
	if(_ordre.estNul()){
		return absolu_ent_;
	}
	Entier nb_1_(1);
	Entier nb_2_(2);
	if(absolu_ent_<nb_2_){
		return absolu_ent_;
	}
	Entier M_=absolu_ent_;//(absolu_ent_+nb_1_)/nb_2_
	Entier m_(0);
	Entier moy_(0);
	Entier ent_ordre_(_ordre);
	Entier expo_(0);
	while(m_+nb_1_<M_){
		moy_=(M_+m_)/nb_2_;
		expo_=moy_^ent_ordre_;
		if(expo_==absolu_ent_){
			return moy_;
		}
		if(expo_<absolu_ent_){
			m_=moy_;
		}else{
			M_=moy_;
		}
	}
	return m_;
}

Entier& Entier::operator^=(const Entier& _expo){
	Entier copie_(*this);
	operator=(Entier(1));
	for(Entier e(0);e<_expo;++e){
		(*this)*=copie_;
	}
	return (*this);
}

unsigned long long Entier::modulo_absolu_base()const{
	return EntierPositif::modulo_absolu_base();
}

Entier& Entier::operator/=(const Entier& _autre){
	operator=(division_euclidienne_generalise(_autre).first);
	return (*this);
}

Entier& Entier::operator%=(const Entier& _autre){
	operator=(division_euclidienne_generalise(_autre).second);
	return (*this);
}

Entier& Entier::operator*=(const Entier& _autre){
	EntierPositif::operator*=(_autre);
	signe=signe==_autre.signe;
	return (*this);
}

Entier& Entier::operator-=(const Entier& _autre){
	(*this)+=(-_autre);
	return (*this);
}

Entier Entier::operator-()const{
	Entier resultat_=(*this);
	if(estNul()){
		resultat_.signe=true;
		return resultat_;
	}
	resultat_.signe=!signe;
	return resultat_;
}

Entier& Entier::operator++(){
	(*this)+=Entier(1);
	return (*this);
}

Entier& Entier::operator--(){
	(*this)-=Entier(1);
	return (*this);
}

Entier& Entier::operator+=(const Entier& _autre){
	if((*this)==(-_autre)){
		Entier::operator=(Entier(0));
		return (*this);
	}
	if(signe==_autre.signe){
		EntierPositif::operator+=(_autre);
		return (*this);
	}
	if(plus_petit_que(_autre)){
		Entier::operator=(EntierPositif::soustraire(_autre,*this));
		signe=_autre.signe;
		return (*this);
	}
	EntierPositif::operator-=(_autre);
	return (*this);
}

QPair<Entier,Entier> Entier::division_euclidienne_generalise(const Entier& _autre)const{
	QPair<Entier,Entier> quotient_reste_;
	Entier absolu_=absolu();
	Entier autre_absolu_=_autre.absolu();
	QPair<QList<unsigned long long>,QList<unsigned long long> > quotient_reste_positif_;
	quotient_reste_positif_=absolu_.division_euclidienne(autre_absolu_);
	quotient_reste_.first=Entier(quotient_reste_positif_.first,true);
	quotient_reste_.second=Entier(quotient_reste_positif_.second,true);
	if(signe){
		quotient_reste_.first.signe=_autre.signe;
		return quotient_reste_;
	}
	if(_autre.signe){
		if(quotient_reste_.second>Entier(0)){
			quotient_reste_.first=-Entier(1)-quotient_reste_.first;
			quotient_reste_.second=_autre-quotient_reste_.second;
		}else{
			quotient_reste_.first=-quotient_reste_.first;
		}
		return quotient_reste_;
	}
	if(quotient_reste_.second>Entier(0))
	{
		quotient_reste_.first=quotient_reste_.first+Entier(1);
		quotient_reste_.second=-_autre-quotient_reste_.second;
	}
	return quotient_reste_;
}

Entier Entier::absolu()const{
	Entier resultat_=(*this);
	resultat_.signe=true;
	return resultat_;
}



Entier operator+(const Entier& _celui_ci,const Entier& _autre){
	Entier somme_=_celui_ci;
	somme_+=_autre;
	return somme_;
}

Entier operator*(const Entier& _celui_ci,const Entier& _autre){
	Entier produit_=_celui_ci;
	produit_*=_autre;
	return produit_;
}

Entier operator/(const Entier& _celui_ci,const Entier& _autre){
	Entier quotient_=_celui_ci;
	quotient_/=_autre;
	return quotient_;
}

Entier operator%(const Entier& _celui_ci,const Entier& _autre){
	Entier reste_=_celui_ci;
	reste_%=_autre;
	return reste_;
}

Entier operator-(const Entier& _celui_ci,const Entier& _autre){
	Entier diff_=_celui_ci;
	diff_-=_autre;
	return diff_;
}

Entier operator^(const Entier& _celui_ci,const Entier& _autre){
	Entier puis_=_celui_ci;
	puis_^=_autre;
	return puis_;
}

bool Entier::estNul()const{
	return EntierPositif::estNul();
}

bool Entier::non_negatif()const{
	return signe;
}
/*Entier& Entier::operator=(const Entier& _autre){
	EntierPositif::operator =(_autre)
	signe=_autre.signe
	return (*this)
}*/
bool operator>(const Entier& _celui_ci,const Entier& _autre){
	if(_celui_ci.non_negatif()!=_autre.non_negatif()){
		return _celui_ci.non_negatif();
	}
	if(_celui_ci.non_negatif()){
		return _celui_ci.plus_grand_que(_autre);
	}
	if(_celui_ci==_autre){
		return false;
	}
	return !_celui_ci.plus_grand_que(_autre);
}



bool operator!=(const Entier& _celui_ci,const Entier& _autre){
	return !(_celui_ci==_autre);
}

bool operator==(const Entier& _celui_ci,const Entier& _autre){
	return _celui_ci.non_negatif()==_autre.non_negatif()&&_celui_ci.egal_a(_autre);
}

bool operator<=(const Entier& _celui_ci,const Entier& _autre){
	return !(_celui_ci>_autre);
}

bool operator>=(const Entier& _celui_ci,const Entier& _autre){
	return !(_celui_ci<_autre);
}

bool operator<(const Entier& _celui_ci,const Entier& _autre){
	if(_celui_ci.non_negatif()!=_autre.non_negatif()){
		return _autre.non_negatif();
	}
	if(_celui_ci.non_negatif()){//
		return _celui_ci.plus_petit_que(_autre);
	}
	if(_celui_ci==_autre){
		return false;
	}
	return !_celui_ci.plus_petit_que(_autre);
}

QString Entier::chaine()const{
	QString chaine_=EntierPositif::chaine();
	if(!signe){
		chaine_="-"+chaine_;
	}
	return chaine_;
}

Entier Entier::parse_entier(const QString& _chaine){
	int puissance10_=Entier::_log_base_;
	QString nb_lu_=_chaine;
	QList<unsigned long long> ents_;
	bool pres_signe_=nb_lu_.contains("-");
	if(pres_signe_){
		nb_lu_=nb_lu_.mid(1);
	}
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
		ents_.prepend(nb_lu2_.toLongLong());
	}
	return Entier(ents_,!pres_signe_);
}

void Entier::serialiser(Flux& _out)const{
	EntierPositif::serialiser(_out);
	_out<<signe;
}

void Entier::deserialiser(Flux& _in){
	EntierPositif::deserialiser(_in);
	_in>>signe;
}

Flux & operator <<(Flux& out,const Entier& _Entier){
	_Entier.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Entier& _Entier){
	_Entier.deserialiser(in);
	return in;
}


