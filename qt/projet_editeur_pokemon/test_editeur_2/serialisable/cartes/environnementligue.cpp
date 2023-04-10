#include "serialisable/cartes/environnementligue.h"
EnvironnementLigue::EnvironnementLigue(){
	largeur=0;//pour ne pas avoir d'intialisation aléatoire
}

EnvironnementLigue::EnvironnementLigue(int _largeur,int _hauteur,const QString& _type_environnement){
	largeur=_largeur;
	type_environnement=_type_environnement;
	int nb_tuiles_=_largeur*_hauteur;
	for(int i=0;i<nb_tuiles_;i++){
		tuiles<<Tuile();
		*tuiles.last().adr_nom_image()="ihm/"+_type_environnement;
	}
}

bool EnvironnementLigue::egal(const EnvironnementLigue& _autre)const{
	bool egal_;
	egal_=largeur==_autre.largeur;
	egal_&=type_environnement==_autre.type_environnement;
	egal_&=tuiles==_autre.tuiles;
	return egal_;
}

bool EnvironnementLigue::est_vide(const QPair<int,int>& _id)const{
	if(_id.first+largeur*_id.second>=tuiles.size()||_id.first+largeur*_id.second<0){
		return false;
	}
	Tuile t_=tuiles[_id.first+largeur*_id.second];
	if(t_.adr_nom_image_obst()->first!=""){
		return false;
	}
	return true;
}

Tuile* EnvironnementLigue::tuile(const QPair<int,int>& _coords_tuile){
	return &(tuiles[_coords_tuile.first+largeur*_coords_tuile.second]);
}

void EnvironnementLigue::inserer_ligne(int _indice){
	int indice_depart_=_indice*largeur;
	for(int i=0;i<largeur;i++){
		Tuile t_=Tuile();
		*t_.adr_nom_image()="ihm/"+type_environnement;
		tuiles.insert(indice_depart_,t_);//on pousse les nouvelles tuiles vers la droite sur une ligne
	}
}

void EnvironnementLigue::inserer_colonne(int _indice){
	int indice_depart_=_indice;
	int nb_tuiles_aj_=tuiles.size()/largeur;
	largeur++;
	for(int i=indice_depart_;i<nb_tuiles_aj_;i++){
		Tuile t_=Tuile();
		*t_.adr_nom_image()="ihm/"+type_environnement;
		tuiles.insert(i*largeur+indice_depart_,t_);//on coupe l'environnement en deux et on ajoute une colonne
	}
}

void EnvironnementLigue::supprimer_ligne(int _indice){
	int indice_depart_=_indice*largeur;
	for(int i=0;i<largeur;i++){
		tuiles.removeAt(indice_depart_);//on pousse les nouvelles tuiles vers la droite sur une ligne
	}
}

void EnvironnementLigue::supprimer_colonne(int _indice){
	int indice_depart_=_indice+tuiles.size()-largeur;
	for(int i=indice_depart_;i>-1;i-=largeur){
		tuiles.removeAt(i);
	}
	largeur--;
}

QString* EnvironnementLigue::type_env(){
	return &type_environnement;
}

QPair<int,int> EnvironnementLigue::dimensions()const{
	return QPair<int,int>(largeur,tuiles.size()/largeur);
}

QList<QPair<QPair<int,int>,QPair<int,int> > > EnvironnementLigue::bords(const QPair<int,int>& _id)const{
	QPair<int,int> dims_=dimensions();
	QList<QPair<QPair<int,int>,QPair<int,int> > > bords_;
	bords_<<QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(_id.first-1,_id.second),QPair<int,int>(1,dims_.second));
	bords_<<QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(_id.first,_id.second+dims_.second),QPair<int,int>(dims_.first,1));
	bords_<<QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(_id.first+dims_.first,_id.second),QPair<int,int>(1,dims_.second));
	bords_<<QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(_id.first,_id.second-1),QPair<int,int>(dims_.first,1));
	return bords_;
}

QPair<QPair<int,int>,QPair<int,int> > EnvironnementLigue::intersection(const QPair<int,int>& id,const QPair<int,int>& dims,const QPair<int,int>& id_v,const QPair<int,int>& dims_v){
	QPair<int,int> dr_=QPair<int,int>(id.first+dims.first-1,id.second+dims.second-1);
	QPair<int,int> dr_vois_=QPair<int,int>(id_v.first+dims_v.first-1,id_v.second+dims_v.second-1);
	QPair<int,int> g_int_;
	QPair<int,int> d_int_;
	int inval_=Tuile::_coords_invalide_;
	QPair<QPair<int,int>,QPair<int,int> > retour=QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(inval_,inval_),QPair<int,int>(inval_,inval_));
	if(id.first>id_v.first){
		g_int_.first=id.first;
	}else{
		g_int_.first=id_v.first;
	}
	if(id.second>id_v.second){
		g_int_.second=id.second;
	}else{
		g_int_.second=id_v.second;
	}
	if(dr_.first<dr_vois_.first){
		d_int_.first=dr_.first;
	}else{
		d_int_.first=dr_vois_.first;
	}
	if(dr_.second<dr_vois_.second){
		d_int_.second=dr_.second;
	}else{
		d_int_.second=dr_vois_.second;
	}
	if(d_int_.first<g_int_.first||d_int_.second<g_int_.second){
		return retour;
	}
	retour.first=QPair<int,int>(g_int_.first-id.first,g_int_.second-id.second);
	retour.second=QPair<int,int>(d_int_.first-id.first,d_int_.second-id.second);
	return retour;
}

QString EnvironnementLigue::exporter(int _nb_tab_env,const QPair<int,int>& _id)const{
	QString descr_;
	//_nb_tab_env=2
	for(int i=0;i<_nb_tab_env;i++){
		descr_+="\t";
	}
	descr_+="<EnvLigue coords=\""+QString::number(_id.first)+","+QString::number(_id.second)+"\">\n";
	int nb_tab_env_att_=_nb_tab_env+1;
	for(int i=0;i<nb_tab_env_att_;i++){
		descr_+="\t";
	}
	descr_+="<Largeur>"+QString::number(largeur)+"</Largeur>\n";
	for(int i=0;i<nb_tab_env_att_;i++){
		descr_+="\t";
	}
	descr_+="<Type>"+type_environnement+"</Type>\n";
	int nb_tuiles_=tuiles.size();
	for(int i=0;i<nb_tuiles_;i++){
		for(int j=0;j<nb_tab_env_att_;j++){
			descr_+="\t";
		}
		descr_+=tuiles[i].exporter();
	}
	return descr_;
}

bool operator==(const EnvironnementLigue& a,const EnvironnementLigue& b){
	return a.egal(b);
}

void EnvironnementLigue::serialiser(Flux& _out)const{
	_out<<largeur;
	_out<<type_environnement;
	_out<<tuiles;
}

void EnvironnementLigue::deserialiser(Flux& _in){
	_in>>largeur;
	_in>>type_environnement;
	_in>>tuiles;
}

Flux & operator <<(Flux& out,const EnvironnementLigue& _EnvironnementLigue){
	_EnvironnementLigue.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,EnvironnementLigue& _EnvironnementLigue){
	_EnvironnementLigue.deserialiser(in);
	return in;
}


