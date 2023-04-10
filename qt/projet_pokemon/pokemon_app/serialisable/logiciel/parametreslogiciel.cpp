#include "serialisable/logiciel/parametreslogiciel.h"

void ParametresLogiciel::serialiser(Flux& _out)const{
	_out<<langue;
	_out<<der_sauvegarde;
	_out<<lancer_der_sauvegarde;
	_out<<clic_sur_bouton;
}

void ParametresLogiciel::deserialiser(Flux& _in){
	_in>>langue;
	_in>>der_sauvegarde;
	_in>>lancer_der_sauvegarde;
	_in>>clic_sur_bouton;
}

Flux & operator <<(Flux& out,const ParametresLogiciel& _ParametresLogiciel){
	_ParametresLogiciel.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,ParametresLogiciel& _ParametresLogiciel){
	_ParametresLogiciel.deserialiser(in);
	return in;
}


