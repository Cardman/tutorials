#include "serialisable/combat/combattant.h"

Combattant::Combattant(){
	coordonnees_equipe_totale.first=255;
	coordonnees_equipe_totale.second=255;
}

Combattant::Combattant(uchar _equipe,uchar _position){
	coordonnees_equipe_totale.first=_equipe;
	coordonnees_equipe_totale.second=_position;
}

uchar Combattant::equipe()const{
	return coordonnees_equipe_totale.first;
}

uchar Combattant::position()const{
	return coordonnees_equipe_totale.second;
}

bool operator==(const Combattant& _celui_ci,const Combattant& _autre){
	return _celui_ci.equipe()==_autre.equipe()&&_celui_ci.position()==_autre.position();
}

bool operator!=(const Combattant& _celui_ci,const Combattant& _autre){
	return !(_celui_ci==_autre);
}

void Combattant::serialiser(Flux& _out)const{
	_out<<coordonnees_equipe_totale;
}

void Combattant::deserialiser(Flux& _in){
	_in>>coordonnees_equipe_totale;
}

Flux & operator <<(Flux& out,const Combattant& _Combattant){
	_Combattant.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Combattant& _Combattant){
	_Combattant.deserialiser(in);
	return in;
}


