#include "serialisable/utilisateur/inventaire.h"
#include "base_donnees/objets/baie.h"
#include "base_donnees/objets/ball.h"
#include "base_donnees/objets/boost.h"
#include "base_donnees/objets/fossile.h"
#include "base_donnees/objets/objetattachablecombat.h"
#include "base_donnees/objets/objetevo.h"
#include "base_donnees/objets/pierreevo.h"
#include "base_donnees/objets/plaque.h"
#include "base_donnees/objets/module.h"
#include "base_donnees/objets/repousse.h"
#include "base_donnees/objets/revente.h"
#include "base_donnees/objets/soin.h"
#include "base_donnees/donnees.h"

Inventaire::Inventaire(){
}

Inventaire::Inventaire(Donnees* _d){
	foreach(QString o,_d->val_objets().cles()){
		Objet *obj_=_d->val_objets().valeur(o);
		if(qobject_cast<Ball*>(obj_)){
			balls.ajouter_cle_valeur(o,0);
		}
		if(qobject_cast<Soin*>(obj_)){
			objets_soins.ajouter_cle_valeur(o,QList<QPair<uchar,Taux> >());
			objets_soins.valeur(o)<<QPair<uchar,Taux>(0,Taux(0));
		}
		if(qobject_cast<Boost*>(obj_)){
			boost_statistiques.ajouter_cle_valeur(o,QList<QPair<uchar,uchar> >());
			boost_statistiques.valeur(o)<<QPair<uchar,uchar>(0,0);
		}
		if(qobject_cast<ObjetEvo*>(obj_)){
			objets_attacher_evolution.ajouter_cle_valeur(o,0);
		}
		if(qobject_cast<ObjetAttachableCombat*>(obj_)){
			objets_attacher.ajouter_cle_valeur(o,0);
		}
		if(qobject_cast<PierreEvo*>(obj_)){
			pierres_evo.ajouter_cle_valeur(o,0);
		}
		if(qobject_cast<Baie*>(obj_)){
			baies.ajouter_cle_valeur(o,0);
		}
		if(qobject_cast<Revente*>(obj_)){
			objets_reventes.ajouter_cle_valeur(o,0);
		}
		if(qobject_cast<Plaque*>(obj_)||qobject_cast<Module*>(obj_)){
			plaques.ajouter_cle_valeur(o,0);
		}
		if(qobject_cast<Repousse*>(obj_)){
			repousse.ajouter_cle_valeur(o,0);
		}
		if(qobject_cast<Fossile*>(obj_)){
			fossiles.ajouter_cle_valeur(o,0);
		}
	}
	foreach(uchar c,_d->val_ct().cles()){
		ct.ajouter_cle_valeur(c,0);
	}
	foreach(uchar c,_d->val_cs().cles()){
		cs.ajouter_cle_valeur(c,false);
	}
}


HashMap<QString,QList<QPair<uchar,Taux> > >& Inventaire::objets_soins_ut(){
	return objets_soins;
}

HashMap<QString,uchar>& Inventaire::balls_ut(){
	return balls;
}

HashMap<QString,uchar>& Inventaire::objets_attacher_evolution_ut(){
	return objets_attacher_evolution;
}

HashMap<QString,uchar>& Inventaire::objets_attacher_ut(){
	return objets_attacher;
}

HashMap<QString,uchar>& Inventaire::pierres_evo_ut(){
	return pierres_evo;
}

HashMap<QString,uchar>& Inventaire::baies_ut(){
	return baies;
}

HashMap<QString,QList<QPair<uchar,uchar> > >& Inventaire::boost_statistiques_ut(){
	return boost_statistiques;
}

HashMap<QString,uchar>& Inventaire::objets_reventes_ut(){
	return objets_reventes;
}

HashMap<QString,uchar>& Inventaire::plaques_ut(){
	return plaques;
}

HashMap<QString,uchar>& Inventaire::repousse_ut(){
	return repousse;
}

HashMap<QString,uchar>& Inventaire::fossiles_ut(){
	return fossiles;
}

HashMap<uchar,uchar>& Inventaire::ct_ut(){
	return ct;
}

HashMap<uchar,bool>& Inventaire::cs_ut(){
	return cs;
}

uchar Inventaire::quantite(const QString& _objet)const{
	if(objets_soins.cles().contains(_objet)){
		uchar somme_=0;
		typedef QPair<uchar,Taux> EffectifQuantite;
		foreach(EffectifQuantite e,objets_soins.valeur(_objet)){
			somme_+=e.first;
		}
		return somme_;
	}
	if(boost_statistiques.cles().contains(_objet)){
		uchar somme_=0;
		typedef QPair<uchar,uchar> EffectifQuantite;
		foreach(EffectifQuantite e,boost_statistiques.valeur(_objet)){
			somme_+=e.first;
		}
		return somme_;
	}
	if(balls.cles().contains(_objet)){
		return balls.valeur(_objet);
	}
	if(objets_attacher_evolution.cles().contains(_objet)){
		return objets_attacher_evolution.valeur(_objet);
	}
	if(objets_attacher.cles().contains(_objet)){
		return objets_attacher.valeur(_objet);
	}
	if(pierres_evo.cles().contains(_objet)){
		return pierres_evo.valeur(_objet);
	}
	if(baies.cles().contains(_objet)){
		return baies.valeur(_objet);
	}
	if(objets_reventes.cles().contains(_objet)){
		return objets_reventes.valeur(_objet);
	}
	if(plaques.cles().contains(_objet)){
		return plaques.valeur(_objet);
	}
	if(repousse.cles().contains(_objet)){
		return repousse.valeur(_objet);
	}
	if(fossiles.cles().contains(_objet)){
		return fossiles.valeur(_objet);
	}
	return 0;
}

uchar Inventaire::quantite(const QString& _objet,int _indice)const{
	if(objets_soins.cles().contains(_objet)){
		return objets_soins.valeur(_objet)[_indice].first;
	}
	if(boost_statistiques.cles().contains(_objet)){
		return boost_statistiques.valeur(_objet)[_indice].first;
	}
	return quantite(_objet);
}


void Inventaire::consommer(const QString& _obj,int _indice){
	if(objets_soins.cles().contains(_obj)){
		objets_soins.valeur(_obj)[_indice].first--;
	}
	if(boost_statistiques.cles().contains(_obj)){
		boost_statistiques.valeur(_obj)[_indice].first--;
	}
	if(balls.cles().contains(_obj)){
		balls.valeur(_obj)--;
	}
	if(objets_attacher_evolution.cles().contains(_obj)){
		objets_attacher_evolution.valeur(_obj)--;
	}
	if(objets_attacher.cles().contains(_obj)){
		objets_attacher.valeur(_obj)--;
	}
	if(pierres_evo.cles().contains(_obj)){
		pierres_evo.valeur(_obj)--;
	}
	if(baies.cles().contains(_obj)){
		baies.valeur(_obj)--;
	}
	if(objets_reventes.cles().contains(_obj)){
		objets_reventes.valeur(_obj)--;
	}
	if(plaques.cles().contains(_obj)){
		plaques.valeur(_obj)--;
	}
	if(repousse.cles().contains(_obj)){
		repousse.valeur(_obj)--;
	}
	if(fossiles.cles().contains(_obj)){
		fossiles.valeur(_obj)--;
	}
}

void Inventaire::serialiser(Flux& _out)const{
	_out<<objets_soins;
	_out<<balls;
	_out<<objets_attacher_evolution;
	_out<<objets_attacher;
	_out<<pierres_evo;
	_out<<fossiles;
	_out<<baies;
	_out<<boost_statistiques;
	_out<<objets_reventes;
	_out<<plaques;
	_out<<ct;
	_out<<cs;
	//_out<<objets_quetes
}

void Inventaire::deserialiser(Flux& _in){
	_in>>objets_soins;
	_in>>balls;
	_in>>objets_attacher_evolution;
	_in>>objets_attacher;
	_in>>pierres_evo;
	_in>>fossiles;
	_in>>baies;
	_in>>boost_statistiques;
	_in>>objets_reventes;
	_in>>plaques;
	_in>>ct;
	_in>>cs;
	//_in>>objets_quetes
}

Flux & operator <<(Flux& out,const Inventaire& _Inventaire){
	_Inventaire.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Inventaire& _Inventaire){
	_Inventaire.deserialiser(in);
	return in;
}


