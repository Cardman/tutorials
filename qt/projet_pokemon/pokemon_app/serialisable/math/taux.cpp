#include "serialisable/math/taux.h"
#include <QStringList>
#include <QString>
Taux::Taux(){
	numerateur=Entier(0);
	denominateur=Entier(1);
}

Taux::Taux(const QString& _chaine){
	QString taux_pris_=_chaine;
	if(taux_pris_.startsWith(".")){
		taux_pris_="0"+taux_pris_;
	}
	if(taux_pris_.startsWith("-.")){
		taux_pris_.insert(1,"0");
	}
	if(taux_pris_.contains(".")){
		int puis_dix_=taux_pris_.length()-1-taux_pris_.indexOf(QChar('.'));
		numerateur=Entier(taux_pris_.replace(".",""));
		denominateur=Entier(EntierPositif::_base_numer_)^Entier(puis_dix_);
	}else if(taux_pris_.contains("/")){
		QStringList num_den=taux_pris_.split("/");
		numerateur=Entier(num_den[0]);
		denominateur=Entier(num_den[1]);
	}else{
		numerateur=Entier(_chaine);
		denominateur=Entier(1);
	}
}

Taux::Taux(long long _numerateur,bool _signe,long long _denominateur){
	numerateur=Entier(_numerateur);
	if(_signe){
		numerateur=numerateur.absolu();
	}else{
		numerateur=-numerateur.absolu();
	}
	denominateur=EntierPositif(Entier(_denominateur));
	simplifier();
}

Taux::Taux(long long _numerateur,long long _denominateur){
	if(_denominateur<0){
		_numerateur=-_numerateur;
	}
	numerateur=Entier(_numerateur);
	denominateur=EntierPositif(Entier(_denominateur));
	simplifier();
}

Taux::Taux(const Entier& _numerateur,bool _signe,const EntierPositif& _denominateur):numerateur(_numerateur),denominateur(_denominateur){
	if(_signe){
		numerateur=numerateur.absolu();
	}else{
		numerateur=-numerateur.absolu();
	}
	simplifier();
}

Taux::Taux(const Entier& _numerateur,const EntierPositif& _denominateur):numerateur(_numerateur),denominateur(_denominateur){
	simplifier();
}

/*Taux::Taux(const Taux& _copie){
	numerateur=_copie.numerateur
	denominateur=_copie.denominateur
}*/

Taux Taux::parse_taux(const QString& _chaine){
	QString taux_pris_=_chaine;
	Taux taux_;
	if(taux_pris_.startsWith(".")){
		taux_pris_="0"+taux_pris_;
	}
	if(taux_pris_.startsWith("-.")){
		taux_pris_.insert(1,"0");
	}
	if(taux_pris_.contains(".")){
		int indice_pt_=taux_pris_.indexOf(QChar('.'));
		int puis_dix_=taux_pris_.length()-1-indice_pt_;
		Entier denom_=Entier(EntierPositif::_base_numer_)^Entier(puis_dix_);
		QString ch_num_=taux_pris_.replace(".","");
		Entier numer_=Entier::parse_entier(ch_num_);
		taux_=Taux(numer_,!taux_pris_.contains("-"),denom_);
	}else if(taux_pris_.contains("/")){
		QStringList num_den=taux_pris_.split("/");
		QString ch_den_=num_den[1];
		Entier denom_=Entier::parse_entier(ch_den_);
		Entier numer_=Entier::parse_entier(num_den[0]);
		taux_=Taux(numer_,taux_pris_.startsWith("-")==ch_den_.startsWith("-"),denom_);
	}else{
		Entier numer_=Entier::parse_entier(_chaine);
		taux_=Taux(numer_,!_chaine.startsWith("-"),Entier(1));
	}
	return taux_;
}

Taux Taux::absolu()const{
	return Taux(numerateur,true,denominateur);
}

Taux Taux::racine_abs(int _expo)const{
	return Taux((numerateur*(Entier(denominateur)^Entier(_expo-1))).racine_abs(Entier(_expo)),true,denominateur);
}

void Taux::simplifier(){
	Entier pgcd_c_=numerateur.pgcd(denominateur);
	numerateur=numerateur/pgcd_c_;
	denominateur=denominateur/pgcd_c_;
}

bool Taux::gsigne()const{
	return numerateur.non_negatif();
}

Entier Taux::gnumerateur()const{
	return numerateur;
}

EntierPositif Taux::gdenominateur()const{
	return denominateur;
}

Taux Taux::operator^(const Entier& _expo)const{
	Taux puis_=(*this);
	puis_.numerateur^=_expo.absolu();
	puis_.denominateur=puis_.denominateur^_expo.absolu();
	if(!_expo.non_negatif()){
		puis_=puis_.inv();
	}
	return puis_;
}

Taux& Taux::operator-=(const Taux& _autre){
	(*this)+=-_autre;
	return (*this);
}

Taux& Taux::operator+=(const Taux& _autre){
	Entier ppcm_den_=Entier(denominateur).ppcm(_autre.denominateur);
	numerateur*=ppcm_den_;
	numerateur/=denominateur;
	numerateur+=_autre.numerateur*ppcm_den_/_autre.denominateur;
	denominateur=ppcm_den_;
	return (*this);
}

Taux& Taux::operator*=(const Taux& _autre){
	numerateur*=_autre.numerateur;
	denominateur=denominateur*_autre.denominateur;
	simplifier();
	return (*this);
}

Taux& Taux::operator/=(const Taux& _autre){
	(*this)*=_autre.inv();
	return (*this);
}


Taux operator-(const Taux& _celui_ci,const Taux& _autre){
	return _celui_ci+-_autre;
}

Taux operator+(const Taux& _celui_ci,const Taux& _autre){
	Taux somme_=_celui_ci;
	somme_+=_autre;
	return somme_;
}

Taux operator*(const Taux& _celui_ci,const Taux& _autre){
	Taux produit_=_celui_ci;
	produit_*=_autre;
	return produit_;
}

Taux operator/(const Taux& _celui_ci,const Taux& _autre){
	return _celui_ci*_autre.inv();
}

Taux Taux::inv()const{
	return Taux(denominateur,numerateur.non_negatif(),numerateur);
}

Taux Taux::operator-()const{
	if(estNul()){
		return Taux(numerateur,true,denominateur);
	}
	return Taux(numerateur,!numerateur.non_negatif(),denominateur);
}

QString Taux::evaluer(int _nombre_decimales)const{
	if(!numerateur.non_negatif()){
		return "-"+absolu().evaluer(_nombre_decimales);
	}
	if(estNul()){
		return "0";
	}
	Taux taux_1_=Taux(1);
	Taux copie2_=(*this);
	Entier ent_10_=Entier(EntierPositif::_base_numer_);
	Taux taux_10_=Taux(ent_10_,true);
	int puissance_=0;
	if(copie2_<taux_1_){//S ecrit x.xxxxxE-xx où x est un chiffre
		while(copie2_<taux_1_){
			copie2_=copie2_*taux_10_;
			puissance_--;
		}
	}else{
		while(copie2_>=taux_10_){
			copie2_=copie2_/taux_10_;
			puissance_++;
		}
	}
	Taux copie_=copie2_*Taux(ent_10_^Entier(_nombre_decimales-1),true);
	QString retour_=copie_.partie_entiere().chaine();
	retour_.insert(1,QChar('.'));
	return retour_+"E"+QString::number(puissance_);
}

QString Taux::chaine()const{
	QString retour_="";
	retour_+=numerateur.chaine();
	if(Entier(denominateur)!=Entier(1)){
		retour_+="/"+Entier(denominateur).chaine();
	}
	return retour_;
}

bool operator<(const Taux& _celui_ci,const Taux& _autre){
	if(_celui_ci.gnumerateur().estNul()&&_autre.gnumerateur().estNul()){
		return false;
	}
	if(!_celui_ci.gnumerateur().non_negatif()&&_autre.gnumerateur().non_negatif()){
		return true;
	}
	if(_celui_ci.gnumerateur().non_negatif()&&!_autre.gnumerateur().non_negatif()){
		return false;
	}
	return _celui_ci.gnumerateur()*_autre.gdenominateur()<_celui_ci.gdenominateur()*_autre.gnumerateur();
}

bool operator>(const Taux& _celui_ci,const Taux& _autre){
	if(_celui_ci.gnumerateur().estNul()&&_autre.gnumerateur().estNul()){
		return false;
	}
	if(_celui_ci.gnumerateur().non_negatif()&&!_autre.gnumerateur().non_negatif()){
		return true;
	}
	if(!_celui_ci.gnumerateur().non_negatif()&&_autre.gnumerateur().non_negatif()){
		return false;
	}
	return _celui_ci.gnumerateur()*_autre.gdenominateur()>_celui_ci.gdenominateur()*_autre.gnumerateur();
}

bool operator<=(const Taux& _celui_ci,const Taux& _autre){
	return !(_celui_ci>_autre);
}

bool operator>=(const Taux& _celui_ci,const Taux& _autre){
	return !(_celui_ci<_autre);
}


bool Taux::estNul()const{
	return numerateur.estNul();
}

bool operator==(const Taux& _celui_ci,const Taux& _autre){
	if(_celui_ci.gnumerateur().estNul()&&_autre.gnumerateur().estNul()){
		return true;
	}
	return _celui_ci.gnumerateur()==_autre.gnumerateur()&&_celui_ci.gdenominateur()==_autre.gdenominateur();
}

bool operator!=(const Taux& _celui_ci,const Taux& _autre){
	return !(_celui_ci==_autre);
}

Taux Taux::partie_decimale()const{
	return (*this)-partie_entiere();
}

Entier Taux::partie_entiere()const{
	return numerateur/denominateur;
	/*if(numerateur.non_negatif()){
		return numerateur/denominateur;
	}
	if((numerateur%denominateur).estNul()){
		return numerateur/denominateur;
	}
	return -(numerateur/denominateur+Entier(1));*/
}

Taux::operator Entier(){
	return partie_entiere();
}

Taux::operator long long(){
	if(numerateur.non_negatif()){
		return partie_entiere().modulo_absolu_base();
	}
	return -partie_entiere().modulo_absolu_base();
}

/*Taux& Taux::operator=(const Taux& _autre){
	numerateur=_autre.numerateur
	denominateur=_autre.denominateur
	return (*this)
}*/

void Taux::serialiser(Flux& _out)const{
	_out<<numerateur;
	_out<<denominateur;
}

void Taux::deserialiser(Flux& _in){
	_in>>numerateur;
	_in>>denominateur;
}

Flux & operator <<(Flux& out,const Taux& _Taux){
	_Taux.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Taux& _Taux){
	_Taux.deserialiser(in);
	return in;
}


