#include "serialisable/coordonnees/coordonnees.h"
#include <QStringList>

Coordonnees::Coordonnees(){
	lieu_plateau=QPair<int,int>(-1,-1);
	environnement=QPair<int,int>(-1,-1);
	tuile=QPair<int,int>(-1,-1);
}

Coordonnees::Coordonnees(const QString& _ligne){
	QStringList gp_couples_=_ligne.split(";");
	QStringList couple_=gp_couples_[0].split(",");
	lieu_plateau.first=couple_[0].toInt();
	lieu_plateau.second=couple_[1].toInt();
	couple_=gp_couples_[1].split(",");
	environnement.first=couple_[0].toInt();
	environnement.second=couple_[1].toInt();
	couple_=gp_couples_[2].split(",");
	tuile.first=couple_[0].toInt();
	tuile.second=couple_[1].toInt();
}

int Coordonnees::lieu()const{
	return lieu_plateau.first;
}

int& Coordonnees::lieu(){
	return lieu_plateau.first;
}

int Coordonnees::plateau()const{
	return lieu_plateau.second;
}

int& Coordonnees::plateau(){
	return lieu_plateau.second;
}

QPair<int,int> Coordonnees::val_lieu_plateau()const{
	return lieu_plateau;
}

/*int *Coordonnees::adr_lieu(){
	return &lieu_plateau.first;
}

int *Coordonnees::adr_plateau(){
	return &lieu_plateau.second;
}

QPair<int,int> *Coordonnees::adr_lieu_plateau(){
	return &lieu_plateau;
}*/

QPair<int,int> Coordonnees::coords_environnement()const{
	return environnement;
}

QPair<int,int>& Coordonnees::coords_environnement(){
	return environnement;
}

/*QPair<int,int> *Coordonnees::adr_environnement(){
	return &environnement;
}*/

QPair<int,int> Coordonnees::coords_tuile()const{
	return tuile;
}

QPair<int,int>& Coordonnees::coords_tuile(){
	return tuile;
}

/*QPair<int,int> *Coordonnees::adr_tuile(){
	return &tuile;
}*/

QPair<QPair<int,int>,QPair<int,int> > Coordonnees::coords_par_rap_plateau()const{
	return QPair<QPair<int,int>,QPair<int,int> >(tuile,environnement);
}

QPair<int,QPair<QPair<int,int>,QPair<int,int> > > Coordonnees::coords_par_rap_lieu()const{
	return QPair<int,QPair<QPair<int,int>,QPair<int,int> > >(plateau(),coords_par_rap_plateau());
}

bool Coordonnees::operator==(const Coordonnees& _autre)const{
	return lieu_plateau==_autre.lieu_plateau&&environnement==_autre.environnement&&tuile==_autre.tuile;
}

bool Coordonnees::operator!=(const Coordonnees& _autre)const{
	return !operator==(_autre);
}


QString Coordonnees::formater()const{
	QString format_=QString::number(lieu_plateau.first)+","+QString::number(lieu_plateau.second)+";";
	format_+=QString::number(environnement.first)+","+QString::number(environnement.second)+";";
	format_+=QString::number(tuile.first)+","+QString::number(tuile.second);
	return format_;
}

void Coordonnees::serialiser(Flux& _out)const{
	_out<<lieu_plateau;
	_out<<environnement;
	_out<<tuile;
}

void Coordonnees::deserialiser(Flux& _in){
	_in>>lieu_plateau;
	_in>>environnement;
	_in>>tuile;
}

Flux & operator <<(Flux& out,const Coordonnees& _Coordonnees){
	_Coordonnees.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Coordonnees& _Coordonnees){
	_Coordonnees.deserialiser(in);
	return in;
}


