#include "serialisable/utilisateur/utilisateur.h"
#include <QStringList>
#include "serialisable/combat/elementscombat.h"
#include "base_donnees/donnees.h"
#include "base_donnees/pokemon/pokemonsauvage.h"
#include "base_donnees/objets/soinpvstatut.h"
#include "base_donnees/objets/soinpv.h"
#include "base_donnees/objets/soinpp.h"
#include "base_donnees/objets/boost.h"
#include "base_donnees/objets/fossile.h"
#include "base_donnees/objets/objetevo.h"
#include "base_donnees/objets/pierreevo.h"
#include "base_donnees/objets/objetattachablecombat.h"
#include "base_donnees/objets/revente.h"
#include "base_donnees/objets/module.h"
#include "base_donnees/objets/plaque.h"
#include "base_donnees/objets/repousse.h"
#include "base_donnees/objets/ball.h"
#include "base_donnees/objets/baie.h"

Utilisateur::Utilisateur(){

}

Utilisateur::Utilisateur(const QString& _pseudo,const QString& _sexe_heros,Donnees* _d){
	pseudo=_pseudo;
	sexe_heros=_sexe_heros;
	PokemonSauvage *pk_depart_=_d->val_pk_depart();
	FichePokemon *f_pk_=_d->val_pokedex().valeur(pk_depart_->n_pk());
	if(f_pk_->rep_genr()=="MIXTE"){
		equipe<<QPair<uchar,PokemonUtilisateur>(0,PokemonUtilisateur(pk_depart_,_d,_d->val_equivalents_genre().valeur(_sexe_heros)));
	}else if(f_pk_->rep_genr()=="<LEG>"){
		equipe<<QPair<uchar,PokemonUtilisateur>(0,PokemonUtilisateur(pk_depart_,_d));
	}else{
		equipe<<QPair<uchar,PokemonUtilisateur>(0,PokemonUtilisateur(pk_depart_,_d,f_pk_->rep_genr()));
	}
	foreach(QString p,_d->val_pokedex().cles()){
		pokemon_attrapes.ajouter_cle_valeur(p,false);
	}
	pokemon_attrapes.ajouter_cle_valeur(pk_depart_->n_pk(),true);
	int nb_max_pk_=_d->constante_numerique("MAX_PK_PAR_BOITE");
	for(int i=0;i<nb_max_pk_;i++){
		boites_oeufs<<QList<QPair<uchar,OeufPokemon> >();
		boites<<QList<QPair<uchar,PokemonUtilisateur> >();
	}
	argent=_d->constante_numerique("ARGENT");
	inventaire=Inventaire(_d);
	repousse_actif=false;
	pas_restants_repousse=0;
}

void Utilisateur::deplacement(int _nb_pas,Donnees *_d,QString& _commentaire){
	equipe[0].second.deplacement(_nb_pas,_d);
	int nb_eq_=equipe.size();
	int coeff_=1;
	for(int i=0;i<nb_eq_;i++){
		FicheCapacite *f_capac_=_d->val_capacites().valeur(equipe[i].second.capacite_pk());
		if(f_capac_->dim_pas_ecl()>0){
			coeff_+=f_capac_->dim_pas_ecl();
		}
	}
	nb_eq_=oeufs_equipe.size();
	for(int i=0;i<nb_eq_;i++){
		oeufs_equipe[i].second.vers_eclosion(coeff_);
	}
	QStringList nouveaux_nes_;
	eclosion_oeuf(nouveaux_nes_,_d);
	if(!nouveaux_nes_.isEmpty()){
		_commentaire+=nouveaux_nes_.join(", ")+" viennent de naitre\n";
	}
	if(pas_restants_repousse>0){
		pas_restants_repousse--;
	}else{
		repousse_actif=false;
		_commentaire+="Les pokemons ne sont plus repousses\n";
	}
	//dim_pas_ecl()
}

QString Utilisateur::nom()const{
	return pseudo;
}

QStringList Utilisateur::nom_pk_equipe()const{
	QStringList noms_;
	for(int i=equipe.size()-1;i>-1;i--){
		noms_<<equipe[i].second.n_pk();
	}
	return noms_;
}

QString Utilisateur::sexe()const{
	return sexe_heros;
}

void Utilisateur::eclosion_oeuf(QStringList& _nouveaux_nes,Donnees *_d){
	int nb_eq_=oeufs_equipe.size();
	QList<int> eclosions_;
	for(int i=nb_eq_-1;i>-1;i--){
		int place_=oeufs_equipe[i].first;
		OeufPokemon oeuf_=oeufs_equipe[i].second;
		int nb_pas_=oeuf_.nb_pas();
		QString nom_=oeuf_.nom_pk();
		FichePokemon *f_pk_=_d->val_pokedex().valeur(nom_);
		Entier pas_=f_pk_->pas_ecl();
		if(Entier(nb_pas_)>=pas_){
			eclosions_<<i;
			_nouveaux_nes<<nom_;
			if(place_<equipe[0].first){
				equipe.insert(0,QPair<uchar,PokemonUtilisateur>(place_,PokemonUtilisateur(oeuf_,_d)));
			}else if(place_>equipe.last().first){
				equipe<<QPair<uchar,PokemonUtilisateur>(place_,PokemonUtilisateur(oeuf_,_d));
			}else{
				int j_=1;
				forever{
					if(equipe[j_-1].first<place_&&place_<equipe[j_].first){
						equipe.insert(j_,QPair<uchar,PokemonUtilisateur>(place_,PokemonUtilisateur(oeuf_,_d)));
						break;
					}
					j_++;
				}
			}
		}
	}
	foreach(int i,eclosions_){
		oeufs_equipe.removeAt(i);
	}
}

void Utilisateur::echanger_objets(uchar _position_equipe,const QPair<uchar,uchar>& _boite_place){
	int indice_=-1;
	int indice_b_=-1;
	int nb_=equipe.size();
	for(int j=0;j<nb_;j++){
		if(equipe[j].first==_position_equipe){
			indice_=j;
			break;
		}
	}
	int nb_boite_=boites[_boite_place.first].size();
	for(int j=0;j<nb_boite_;j++){
		if(boites[_boite_place.first][j].first==_boite_place.second){
			indice_b_=j;
			break;
		}
	}
	if(indice_<0||indice_b_<0){
		return;
	}
	QString objet_1_=equipe[indice_].second.objet();
	QString objet_2_=boites[_boite_place.first][indice_b_].second.objet();
	equipe[indice_].second.objet()=objet_2_;
	boites[_boite_place.first][indice_b_].second.objet()=objet_1_;
}

void Utilisateur::echanger_objets(const QPair<uchar,uchar>& _boite_place_1,const QPair<uchar,uchar>& _boite_place_2){
	int indice_=-1;
	int indice_b_=-1;
	int nb_=boites[_boite_place_1.first].size();
	for(int j=0;j<nb_;j++){
		if(boites[_boite_place_1.first][j].first==_boite_place_1.second){
			indice_=j;
			break;
		}
	}
	int nb_boite_=boites[_boite_place_2.first].size();
	for(int j=0;j<nb_boite_;j++){
		if(boites[_boite_place_2.first][j].first==_boite_place_2.second){
			indice_b_=j;
			break;
		}
	}
	if(indice_<0||indice_b_<0){
		return;
	}
	QString objet_1_=boites[_boite_place_1.first][indice_].second.objet();
	QString objet_2_=boites[_boite_place_2.first][indice_b_].second.objet();
	boites[_boite_place_1.first][indice_].second.objet()=objet_2_;
	boites[_boite_place_2.first][indice_b_].second.objet()=objet_1_;
}

void Utilisateur::echanger_pokemons(const QPair<uchar,uchar>& _boite_place_1,const QPair<uchar,uchar>& _boite_place_2){
	int indice_=-1;
	int indice_b_=-1;
	bool oeuf_=false;
	bool oeuf_b_=false;
	int nb_=boites[_boite_place_2.first].size();
	for(int j=0;j<nb_;j++){
		if(boites[_boite_place_2.first][j].first==_boite_place_2.second){
			indice_=j;
			break;
		}
	}
	nb_=boites_oeufs[_boite_place_2.first].size();
	for(int j=0;j<nb_;j++){
		if(boites_oeufs[_boite_place_2.first][j].first==_boite_place_2.second){
			indice_=j;
			oeuf_=true;
			break;
		}
	}
	int nb_boite_=boites[_boite_place_1.first].size();
	for(int j=0;j<nb_boite_;j++){
		if(boites[_boite_place_1.first][j].first==_boite_place_1.second){
			indice_b_=j;
			break;
		}
	}
	nb_boite_=boites_oeufs[_boite_place_1.first].size();
	for(int j=0;j<nb_boite_;j++){
		if(boites_oeufs[_boite_place_1.first][j].first==_boite_place_1.second){
			indice_b_=j;
			oeuf_b_=true;
			break;
		}
	}
	if(indice_b_<0||indice_<0){
		return;
	}
	if(_boite_place_2.first==_boite_place_1.first){
		if(oeuf_&&oeuf_b_){
			OeufPokemon oeuf_1_=boites_oeufs[_boite_place_2.first][indice_].second;
			OeufPokemon oeuf_2_=boites_oeufs[_boite_place_2.first][indice_b_].second;
			boites_oeufs[_boite_place_2.first][indice_].second=oeuf_2_;
			boites_oeufs[_boite_place_2.first][indice_b_].second=oeuf_1_;
		}else if(!oeuf_&&!oeuf_b_){
			PokemonUtilisateur pk_1_=boites[_boite_place_2.first][indice_].second;
			PokemonUtilisateur pk_2_=boites[_boite_place_2.first][indice_b_].second;
			boites[_boite_place_2.first][indice_].second=pk_2_;
			boites[_boite_place_2.first][indice_b_].second=pk_1_;
		}else if(!oeuf_){
			boites_oeufs[_boite_place_2.first][indice_b_].first=_boite_place_2.second;
			boites[_boite_place_2.first][indice_].first=_boite_place_1.second;
		}else{
			boites_oeufs[_boite_place_2.first][indice_].first=_boite_place_1.second;
			boites[_boite_place_2.first][indice_b_].first=_boite_place_2.second;
		}
		return;
	}
	if(oeuf_){
		boites_oeufs[_boite_place_2.first]<<QPair<uchar,OeufPokemon>(_boite_place_2.second,boites_oeufs[_boite_place_1.first].takeAt(indice_).second);
	}else{
		boites[_boite_place_2.first]<<QPair<uchar,PokemonUtilisateur>(_boite_place_2.second,boites[_boite_place_1.first].takeAt(indice_).second);
	}
	if(oeuf_b_){
		boites_oeufs[_boite_place_1.first]<<QPair<uchar,OeufPokemon>(_boite_place_1.second,boites_oeufs[_boite_place_2.first].takeAt(indice_b_).second);
	}else{
		boites[_boite_place_1.first]<<QPair<uchar,PokemonUtilisateur>(_boite_place_1.second,boites[_boite_place_2.first].takeAt(indice_b_).second);
	}
}

void Utilisateur::echanger_pokemons(uchar _position_equipe,const QPair<uchar,uchar>& _boite_place,Donnees *_d){
	int indice_=-1;
	int indice_b_=-1;
	bool oeuf_=false;
	bool oeuf_b_=false;
	int nb_=equipe.size();
	for(int j=0;j<nb_;j++){
		if(equipe[j].first==_position_equipe){
			indice_=j;
			break;
		}
	}
	nb_=oeufs_equipe.size();
	for(int j=0;j<nb_;j++){
		if(oeufs_equipe[j].first==_position_equipe){
			indice_=j;
			oeuf_=true;
			break;
		}
	}
	int nb_boite_=boites[_boite_place.first].size();
	for(int j=0;j<nb_boite_;j++){
		if(boites[_boite_place.first][j].first==_boite_place.second){
			indice_b_=j;
			break;
		}
	}
	nb_boite_=boites_oeufs[_boite_place.first].size();
	for(int j=0;j<nb_boite_;j++){
		if(boites_oeufs[_boite_place.first][j].first==_boite_place.second){
			indice_b_=j;
			oeuf_b_=true;
			break;
		}
	}
	if(indice_<0||indice_b_<0){
		return;
	}
	if(oeuf_){
		boites_oeufs[_boite_place.first]<<QPair<uchar,OeufPokemon>(_boite_place.second,oeufs_equipe.takeAt(indice_).second);
	}else{
		boites[_boite_place.first]<<QPair<uchar,PokemonUtilisateur>(_boite_place.second,equipe.takeAt(indice_).second);
		boites[_boite_place.first].last().second.soin_total(_d);
	}
	if(oeuf_b_){
		oeufs_equipe<<QPair<uchar,OeufPokemon>(_position_equipe,boites_oeufs[_boite_place.first].takeAt(indice_b_).second);
	}else{
		equipe<<QPair<uchar,PokemonUtilisateur>(_position_equipe,boites[_boite_place.first].takeAt(indice_b_).second);
	}
	int nb_pk_eq_=equipe.size();
	int nb_oeufs_=oeufs_equipe.size();
	for(int i=0;i<nb_pk_eq_;i++){
		for(int j=i+1;j<nb_pk_eq_;j++){
			if(equipe[i].first>equipe[j].first){
				equipe.swap(i,j);
			}
		}
	}
	for(int i=0;i<nb_oeufs_;i++){
		for(int j=i+1;j<nb_oeufs_;j++){
			if(oeufs_equipe[i].first>oeufs_equipe[j].first){
				oeufs_equipe.swap(i,j);
			}
		}
	}
}

void Utilisateur::placer_dans_boite(uchar _position_equipe,const QPair<uchar,uchar>& _boite_place,Donnees *_d){
	int indice_boite_=_boite_place.first;
	int pos_=boites_oeufs[indice_boite_].size()+boites[indice_boite_].size();
	if(pos_==(int)_d->constante_numerique("MAX_PK_PAR_BOITE")){
		return;
	}
	QList<uchar> _indices;
	int nb_=boites_oeufs[indice_boite_].size();
	for(int i=0;i<nb_;i++){
		_indices<<boites_oeufs[indice_boite_][i].first;
	}
	nb_=boites[indice_boite_].size();
	for(int i=0;i<nb_;i++){
		_indices<<boites[indice_boite_][i].first;
	}
	if(_indices.contains(_boite_place.second)){
		return;
	}
	int indice_=-1;
	bool oeuf_=false;
	nb_=equipe.size();
	for(int j=0;j<nb_;j++){
		if(equipe[j].first==_position_equipe){
			indice_=j;
			break;
		}
	}
	nb_=oeufs_equipe.size();
	for(int j=0;j<nb_;j++){
		if(oeufs_equipe[j].first==_position_equipe){
			indice_=j;
			oeuf_=true;
			break;
		}
	}
	if(indice_<0){
		return;
	}
	/*if(equipe.size()<2&&!oeuf_){
		return
	}*/
	if(!oeuf_){
		QPair<uchar,PokemonUtilisateur> pk_=equipe.takeAt(indice_);
		boites[indice_boite_]<<QPair<uchar,PokemonUtilisateur>(_boite_place.second,pk_.second);
		boites[indice_boite_].last().second.soin_total(_d);
		nb_=equipe.size();
		for(int i=indice_;i<nb_;i++){
			equipe[i].first--;
		}
		nb_=oeufs_equipe.size();
		for(int i=0;i<nb_;i++){
			if(oeufs_equipe[i].first>pk_.first){
				oeufs_equipe[i].first--;
			}
		}
	}else{
		QPair<uchar,OeufPokemon> oeuf_=oeufs_equipe.takeAt(indice_);
		boites_oeufs[indice_boite_]<<QPair<uchar,OeufPokemon>(_boite_place.second,oeuf_.second);
		nb_=oeufs_equipe.size();
		for(int i=indice_;i<nb_;i++){
			oeufs_equipe[i].first--;
		}
		nb_=equipe.size();
		for(int i=0;i<nb_;i++){
			if(equipe[i].first>oeuf_.first){
				equipe[i].first--;
			}
		}
	}
}

void Utilisateur::retirer_de_boite(const QPair<uchar,uchar>& _boite_place,uchar _max_eq){
	uchar pos_=oeufs_equipe.size()+equipe.size();
	if(pos_>=_max_eq){
		return;
	}
	int indice_=-1;
	bool oeuf_=false;
	int nb_boite_=boites[_boite_place.first].size();
	for(int j=0;j<nb_boite_;j++){
		if(boites[_boite_place.first][j].first==_boite_place.second){
			indice_=j;
			break;
		}
	}
	nb_boite_=boites_oeufs[_boite_place.first].size();
	for(int j=0;j<nb_boite_;j++){
		if(boites_oeufs[_boite_place.first][j].first==_boite_place.second){
			indice_=j;
			oeuf_=true;
			break;
		}
	}
	if(indice_<0){
		return;
	}
	if(!oeuf_){
		equipe<<QPair<uchar,PokemonUtilisateur>(pos_,boites[_boite_place.first].takeAt(indice_).second);
	}else{
		oeufs_equipe<<QPair<uchar,OeufPokemon>(pos_,boites_oeufs[_boite_place.first].takeAt(indice_).second);
	}
}

void Utilisateur::relacher_pokemon(const QPair<uchar,uchar>& _boite_place,Donnees* _d){
	int indice_=-1;
	bool oeuf_=false;
	int nb_boite_=boites[_boite_place.first].size();
	for(int j=0;j<nb_boite_;j++){
		if(boites[_boite_place.first][j].first==_boite_place.second){
			indice_=j;
			break;
		}
	}
	nb_boite_=boites_oeufs[_boite_place.first].size();
	for(int j=0;j<nb_boite_;j++){
		if(boites_oeufs[_boite_place.first][j].first==_boite_place.second){
			indice_=j;
			oeuf_=true;
			break;
		}
	}
	if(indice_>-1){
		if(!oeuf_){
			FichePokemon *f_pk_=_d->val_pokedex().valeur(boites[_boite_place.first][indice_].second.n_pk());
			if(f_pk_->rep_genr()=="<LEG>"){
				return;
			}
			QString obj_=boites[_boite_place.first][indice_].second.objet();
			if(obj_!=""){
				ramasser_objet(obj_,_d);
			}
			boites[_boite_place.first].removeAt(indice_);
		}else{
			boites_oeufs[_boite_place.first].removeAt(indice_);
		}
	}
}

void Utilisateur::soin_equipe_ct_pk(Donnees *_d){
	int nb_pk_=equipe.size();
	for(int i=0;i<nb_pk_;i++){
		equipe[i].second.soin_total(_d);
	}
}

Taux Utilisateur::soin_baie(uchar _indice_pk,const QString& _nom_objet,Donnees* _d){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice_pk){
			ind_=i;
			break;
		}
	}
	PokemonUtilisateur& pk_soigne_=equipe[ind_].second;
	Baie *baie_=qobject_cast<Baie*>(_d->val_objets().valeur(_nom_objet));
	Taux pv_rest_(0);
	if(!baie_->s_pv().first.estNul()){
		pk_soigne_.soin_pv_baie(baie_->s_pv().first,_d,pv_rest_);
		if(!pv_rest_.estNul()){
			inventaire.consommer(_nom_objet);
			//gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
		}
	}else if(!baie_->s_tx_pv().first.estNul()){
		pk_soigne_.soin_pv_baie(baie_->s_tx_pv().first*pk_soigne_.pv_max(_d),_d,pv_rest_);
		if(!pv_rest_.estNul()){
			inventaire.consommer(_nom_objet);
			//gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
		}
	}else if(baie_->s_pp().first==""){
		if(!baie_->gain_pv_sup_ef().estNul()){
			pk_soigne_.soin_pv_baie(baie_->gain_pv_sup_ef()*pk_soigne_.pv_max(_d),_d,pv_rest_);
			if(!pv_rest_.estNul()){
				inventaire.consommer(_nom_objet);
				//gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
			}
		}else{
			QString statut_=pk_soigne_.statut_pk();
			foreach(QString s,baie_->s_statut()){
				if(s==statut_){
					pk_soigne_.soin_statut();
					inventaire.consommer(_nom_objet);
					//gestion->maj_fiche(par.utilis(),langue,GestionEquipe::RIEN,donnees);
					break;
				}
			}
		}
	}
	return pv_rest_;
}

uchar Utilisateur::soin_baie_pp(uchar _indice_pk,const QString& _nom_attaque,const QString& _nom_objet,Donnees* _d){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice_pk){
			ind_=i;
			break;
		}
	}
	PokemonUtilisateur& pk_soigne_=equipe[ind_].second;
	Baie *baie_=qobject_cast<Baie*>(_d->val_objets().valeur(_nom_objet));
	uchar pp_rest_=0;
	pk_soigne_.soin_pp_baie(baie_->s_pp().first.toInt(),_nom_attaque,pp_rest_);
	if(pp_rest_>0){
		inventaire.consommer(_nom_objet);
	}
	return pp_rest_;
}

void Utilisateur::soin_pv_pk(uchar _indice_pk,const QString& _nom_objet,uchar _indice_quant,Donnees* _d){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice_pk){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return;
	}
	PokemonUtilisateur& pk_soigne_=equipe[ind_].second;
	SoinPV *soin_pv_=qobject_cast<SoinPV*>(_d->val_objets().valeur(_nom_objet));
	QList<QPair<uchar,Taux> >& liste_=inventaire.objets_soins_ut().valeur(_nom_objet);
	Taux contenu_=liste_[_indice_quant].second;
	Taux pv_soignes_=pk_soigne_.soin_pv(contenu_,soin_pv_->bonh(),_d);
	if(!pv_soignes_.estNul()){
		Taux reste_=contenu_-pv_soignes_;
		if(!reste_.estNul()){
			int ind_=-1;
			for(int i=liste_.size()-1;i>-1;i--){
				if(liste_[i].second==reste_){
					ind_=i;
					break;
				}
			}
			if(ind_<0){
				liste_<<QPair<uchar,Taux>(1,reste_);
			}else{
				liste_[ind_].first++;
			}
		}
		liste_[_indice_quant].first--;
		if(liste_[_indice_quant].first==0){
			liste_.removeAt(_indice_quant);
		}
	}
}

void Utilisateur::soin_pp_pk(uchar _indice_pk,const QString& _nom_objet,Donnees *_d,const QString& _nom_attaque){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice_pk){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return;
	}
	PokemonUtilisateur& pk_soigne_=equipe[ind_].second;
	SoinPP *soin_pp_=qobject_cast<SoinPP*>(_d->val_objets().valeur(_nom_objet));
	QPair<QString,QString> effet_=soin_pp_->effs_se();
	bool utilise_=false;
	if(effet_.first=="MAX"&&effet_.second=="MAX"){
		HashMap<QString,uchar> attaques_soignes_=pk_soigne_.soin_pp();
		foreach(QString s,attaques_soignes_.cles()){
			utilise_|=attaques_soignes_.valeur(s)>0;
		}
	}else if(effet_.first=="MAX"){
		uchar pp_soignes_=pk_soigne_.soin_pp(_nom_attaque);
		utilise_=pp_soignes_>0;
	}else if(effet_.second=="MAX"){
		QStringList attaques_=pk_soigne_.soin_pp(effet_.first.toUInt());
		utilise_=!attaques_.isEmpty();
	}else{
		uchar pp_soignes_=pk_soigne_.soin_pp(_nom_attaque,effet_.first.toUInt());
		utilise_=pp_soignes_>0;
	}
	if(utilise_){
		inventaire.objets_soins_ut().valeur(_nom_objet)[0].first--;
	}
}

void Utilisateur::gain_pp_max(uchar _indice,const QString& _attaque,const QString& _nom_objet,Donnees *_d){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return;
	}
	Boost *boost_=qobject_cast<Boost*>(_d->val_objets().valeur(_nom_objet));
	uchar pp_=_d->val_attaques().valeur(_attaque)->pps();
	if(equipe[ind_].second.gain_pp_max(_attaque,boost_->g_pp(),2*pp_)){
		inventaire.boost_statistiques_ut().valeur(_nom_objet)[0].first--;
	}
}

void Utilisateur::soin_statut(uchar _indice_equipe,const QString& _nom_objet,Donnees* _d){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice_equipe){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return;
	}
	SoinStatut *soin_=qobject_cast<SoinStatut*>(_d->val_objets().valeur(_nom_objet));
	QString statut_=equipe[ind_].second.statut_pk();
	if(qobject_cast<SoinPVStatut*>(soin_)){
		SoinPVStatut *soin_pv_=qobject_cast<SoinPVStatut*>(soin_);
		if(soin_->s_ko()&&statut_=="KO"){
			equipe[ind_].second.soin_statut();
		}else if(soin_->stats().contains(statut_)){
			equipe[ind_].second.soin_statut();
		}
		Taux pv_=equipe[ind_].second.soin_pv(soin_pv_,_d);
		if(!pv_.estNul()||statut_!="OK"){
			inventaire.objets_soins_ut().valeur(_nom_objet)[0].first--;
		}
	}else if(soin_->stats().contains(statut_)){
		equipe[ind_].second.soin_statut();
		if(statut_!="OK"){
			inventaire.objets_soins_ut().valeur(_nom_objet)[0].first--;
		}
	}
}

void Utilisateur::boost_statistique(uchar _indice,const QString& _nom_objet,Donnees *_d){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return;
	}
	Boost *boost_=qobject_cast<Boost*>(_d->val_objets().valeur(_nom_objet));
	QPair<QString,Taux> stat_ev_=boost_->g_ev();
	uchar gain_ev_=equipe[ind_].second.gain_ev(stat_ev_.first,stat_ev_.second,boost_->bonh(),_d->constante_numerique("MAX_EV"),_d);
	if(gain_ev_>0){
		QList<QPair<uchar,uchar> >& liste_=inventaire.boost_statistiques_ut().valeur(_nom_objet);
		liste_[0].first--;
	}
}

void Utilisateur::faire_vivre_fossile(const QString& _nom_fossile,uchar _max_eq,Donnees *_d,QString& _com){
	uchar pos_=oeufs_equipe.size()+equipe.size();
	Fossile *fossile_=qobject_cast<Fossile*>(_d->val_objets().valeur(_nom_fossile));
	if(pos_<_max_eq){
		equipe<<QPair<uchar,PokemonUtilisateur>(pos_,PokemonUtilisateur(fossile_,_d));
		bool deja_pris_=attrape_pk(equipe.last().second.n_pk());
		inventaire.fossiles_ut().valeur(_nom_fossile)--;
		_com="ajout dans l'equipe\n";
		if(!deja_pris_){
			_com+="capture du nouveau pokemon "+equipe.last().second.n_pk();
		}
		return;
	}
	int indice_=-1;
	int nb_boites_=_d->constante_numerique("NB_BOITES");
	int nb_pk_max_=_d->constante_numerique("MAX_PK_PAR_BOITE");
	for(int i=0;i<nb_boites_;i++){
		if(boites[i].size()+boites_oeufs[i].size()<nb_pk_max_){
			indice_=i;
			break;
		}
	}
	if(indice_>-1){
		int place_=boites[indice_].size()+boites_oeufs[indice_].size();
		boites[indice_]<<QPair<uchar,PokemonUtilisateur>(place_,PokemonUtilisateur(fossile_,_d));
		bool deja_pris_=attrape_pk(boites[indice_].last().second.n_pk());
		inventaire.fossiles_ut().valeur(_nom_fossile)--;
		_com="ajout dans la boite "+QString::number(indice_)+"\n";
		if(!deja_pris_){
			_com+="capture du nouveau pokemon "+equipe.last().second.n_pk();
		}
	}else{
		_com="plus de places...";
	}
}

void Utilisateur::echanger_objet_equipe(uchar _indice,uchar _indice_2,Donnees* _d){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return;
	}
	ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice_2){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return;
	}
	QString objet_1_;
	QString objet_2_;
	retirer_objet(_indice,false,objet_1_,_d);
	retirer_objet(_indice_2,false,objet_2_,_d);
	attacher_objet(_indice,objet_2_);
	attacher_objet(_indice_2,objet_1_);
}

void Utilisateur::retirer_objet(QPair<uchar,uchar> _indice,bool _ranger,QString& _objet,Donnees *_d){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(boites[_indice.first][i].first==_indice.second){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return;
	}
	QString obj_=boites[_indice.first][ind_].second.objet();
	_objet=obj_;
	if(obj_==""){
		return;
	}
	if(_ranger){
		ramasser_objet(obj_,_d);
	}
	boites[_indice.first][ind_].second.objet()="";
}

void Utilisateur::retirer_objet(uchar _indice,bool _ranger,QString& _objet,Donnees *_d){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return;
	}
	QString obj_=equipe[ind_].second.objet();
	_objet=obj_;
	if(obj_==""){
		return;
	}
	if(_ranger){
		ramasser_objet(obj_,_d);
	}
	equipe[ind_].second.objet()="";
}

void Utilisateur::attacher_objet(uchar _indice,const QString& _nom_objet){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return;
	}
	QString obj_=equipe[ind_].second.objet();
	if(obj_!=""){
		return;
	}
	equipe[ind_].second.objet()=_nom_objet;
}

QStringList Utilisateur::move_tutors(uchar _indice,Donnees* _d)const{
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return QStringList();
	}
	QString nom_=equipe[ind_].second.n_pk();
	return _d->val_pokedex().valeur(nom_)->mt();
}

bool Utilisateur::peut_apprendre_ct(uchar _indice,uchar _ct,Donnees* _d)const{
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return false;
	}
	QString nom_=equipe[ind_].second.n_pk();
	return _d->val_pokedex().valeur(nom_)->ct().contains(_ct);
}

bool Utilisateur::peut_apprendre_cs(uchar _indice,uchar _cs,Donnees* _d)const{
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		return false;
	}
	QString nom_=equipe[ind_].second.n_pk();
	return _d->val_pokedex().valeur(nom_)->cs().contains(_cs);
}

void Utilisateur::apprendre_attaque(uchar _indice,uchar _indice_attaque,const QString& _nom_attaque,QString& _att_oubliee,Donnees* _d){
	int ind_=-1;
	for(int i=equipe.size()-1;i>-1;i--){
		if(equipe[i].first==_indice){
			ind_=i;
			break;
		}
	}
	_att_oubliee=equipe[ind_].second.apprendre_attaque(_nom_attaque,_indice_attaque,_d);
}

bool Utilisateur::recevoir_pokemon(PokemonSauvage* _pokemon_donne,uchar _max_eq,Donnees *_d,QString& _com){
	uchar pos_=oeufs_equipe.size()+equipe.size();
	if(pos_<_max_eq){
		equipe<<QPair<uchar,PokemonUtilisateur>(pos_,PokemonUtilisateur(_pokemon_donne,_d));
		_com="ajout dans l'equipe\n";
		return true;
	}
	int indice_=-1;
	int nb_boites_=_d->constante_numerique("NB_BOITES");
	int nb_pk_max_=_d->constante_numerique("MAX_PK_PAR_BOITE");
	for(int i=0;i<nb_boites_;i++){
		if(boites[i].size()+boites_oeufs[i].size()<nb_pk_max_){
			indice_=i;
			break;
		}
	}
	if(indice_>-1){
		int place_=boites[indice_].size()+boites_oeufs[indice_].size();
		boites[indice_]<<QPair<uchar,PokemonUtilisateur>(place_,PokemonUtilisateur(_pokemon_donne,_d));
		_com="ajout dans la boite "+QString::number(indice_)+"\n";
		return true;
	}else{
		_com="plus de places...\n";
		return false;
	}
}

void Utilisateur::ramasser_objet(const QString& _nom_objet,Donnees* _d){
	Objet *obj_=_d->val_objets().valeur(_nom_objet);
	if(qobject_cast<Ball*>(obj_)){
		inventaire.balls_ut().valeur(_nom_objet)++;
	}else if(qobject_cast<ObjetEvo*>(obj_)){
		inventaire.objets_attacher_evolution_ut().valeur(_nom_objet)++;
	}else if(qobject_cast<PierreEvo*>(obj_)){
		inventaire.pierres_evo_ut().valeur(_nom_objet)++;
	}else if(qobject_cast<Baie*>(obj_)){
		inventaire.baies_ut().valeur(_nom_objet)++;
	}else if(qobject_cast<ObjetAttachableCombat*>(obj_)){
		inventaire.objets_attacher_ut().valeur(_nom_objet)++;
	}else if(qobject_cast<Revente*>(obj_)){
		inventaire.objets_reventes_ut().valeur(_nom_objet)++;
	}else if(qobject_cast<Plaque*>(obj_)||qobject_cast<Module*>(obj_)){
		inventaire.plaques_ut().valeur(_nom_objet)++;
	}else if(qobject_cast<Repousse*>(obj_)){
		inventaire.repousse_ut().valeur(_nom_objet)++;
	}else if(qobject_cast<Fossile*>(obj_)){
		inventaire.fossiles_ut().valeur(_nom_objet)++;
	}else if(qobject_cast<Soin*>(obj_)){//objets_attacher_ut()
		if(qobject_cast<SoinPV*>(obj_)){
			SoinPV *soin_=qobject_cast<SoinPV*>(obj_);
			Taux tx_=soin_->pv_m_res();
			if(tx_.estNul()){
				inventaire.objets_soins_ut().valeur(_nom_objet)[0].first++;
			}else{
				QList<QPair<uchar,Taux> >& liste_=inventaire.objets_soins_ut().valeur(_nom_objet);
				int ind_=-1;
				int nb_=liste_.size();
				for(int i=0;i<nb_;i++){
					if(liste_[i].second==tx_){
						ind_=i;
						break;
					}
				}
				if(ind_<0){
					liste_<<QPair<uchar,Taux>(1,tx_);
				}else{
					liste_[ind_].first++;
				}
			}
		}else if(qobject_cast<SoinStatut*>(obj_)){
			inventaire.objets_soins_ut().valeur(_nom_objet)[0].first++;
			//SoinPVStatut *soin_=qobject_cast<SoinPVStatut*>(obj_)
			//if(soin_->
			//
		}else{//SoinPP
			inventaire.objets_soins_ut().valeur(_nom_objet)[0].first++;
		}
	}else if(qobject_cast<Boost*>(obj_)){
		//Boost *boost_=qobject_cast<Boost*>(obj_);
		//Taux tx_=boost_->g_ev().second
		QList<QPair<uchar,uchar> >& liste_=inventaire.boost_statistiques_ut().valeur(_nom_objet);
		liste_[0].first++;
		/*if(!tx_.estNul()){
			int ind_=-1
			int nb_=liste_.size()
			for(int i=0;i<nb_;i++){
				if(liste_[i].second==(int)tx_){
					ind_=i
					break
				}
			}
			if(ind_<0){
				liste_<<QPair<uchar,uchar>(1,tx_)
			}else{
				liste_[ind_].first++
			}
		}else{
			liste_[0].first++
		}*/
	}
}

void Utilisateur::achat_objet(const QString& _nom_objet,uchar _quantite,Donnees* _d){
	Entier prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
	for(int i=0;i<_quantite;i++){
		ramasser_objet(_nom_objet,_d);
	}
	argent-=prix_;
}

void Utilisateur::vente_objet(const QString& _nom_objet,uchar _indice,uchar _quantite,Donnees* _d){
	Objet *obj_=_d->val_objets().valeur(_nom_objet);
	Entier prix_;
	if(qobject_cast<Ball*>(obj_)){
		prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
		inventaire.balls_ut().valeur(_nom_objet)-=_quantite;
	}else if(qobject_cast<ObjetEvo*>(obj_)){
		prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
		inventaire.objets_attacher_evolution_ut().valeur(_nom_objet)-=_quantite;
	}else if(qobject_cast<PierreEvo*>(obj_)){
		prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
		inventaire.pierres_evo_ut().valeur(_nom_objet)-=_quantite;
	}else if(qobject_cast<Baie*>(obj_)){
		prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
		inventaire.baies_ut().valeur(_nom_objet)-=_quantite;
	}else if(qobject_cast<ObjetAttachableCombat*>(obj_)){
		prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
		inventaire.objets_attacher_ut().valeur(_nom_objet)-=_quantite;
	}else if(qobject_cast<Revente*>(obj_)){
		prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
		inventaire.objets_reventes_ut().valeur(_nom_objet)-=_quantite;
	}else if(qobject_cast<Plaque*>(obj_)||qobject_cast<Module*>(obj_)){
		prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
		inventaire.plaques_ut().valeur(_nom_objet)-=_quantite;
	}else if(qobject_cast<Repousse*>(obj_)){
		prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
		inventaire.repousse_ut().valeur(_nom_objet)-=_quantite;
	}else if(qobject_cast<Fossile*>(obj_)){
		prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
		inventaire.fossiles_ut().valeur(_nom_objet)-=_quantite;
	}else if(qobject_cast<Soin*>(obj_)){//objets_attacher_ut()
		if(qobject_cast<SoinPV*>(obj_)){
			SoinPV *soin_=qobject_cast<SoinPV*>(obj_);
			Taux tx_=soin_->pv_m_res();
			if(tx_.estNul()){
				prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
				inventaire.objets_soins_ut().valeur(_nom_objet)[0].first-=_quantite;
			}else{
				QList<QPair<uchar,Taux> >& liste_=inventaire.objets_soins_ut().valeur(_nom_objet);
				prix_=(Taux(_d->val_objets().valeur(_nom_objet)->prix()*_quantite)*Taux((long long)liste_[_indice].second,(long long)tx_)).partie_entiere();
				if(liste_[_indice].first==_quantite){
					liste_.removeAt(_indice);
				}else{
					liste_[_indice].first-=_quantite;
				}
			}
		}else if(qobject_cast<SoinStatut*>(obj_)){
			prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
			inventaire.objets_soins_ut().valeur(_nom_objet)[0].first-=_quantite;
			//SoinPVStatut *soin_=qobject_cast<SoinPVStatut*>(obj_)
			//if(soin_->
			//
		}else{//SoinPP
			prix_=_d->val_objets().valeur(_nom_objet)->prix()*_quantite;
			inventaire.objets_soins_ut().valeur(_nom_objet)[0].first-=_quantite;
			//
		}
	}else if(qobject_cast<Boost*>(obj_)){
		Boost *boost_=qobject_cast<Boost*>(obj_);
		Taux tx_=boost_->g_ev().second;
		QList<QPair<uchar,Taux> >& liste_=inventaire.objets_soins_ut().valeur(_nom_objet);
		if(!tx_.estNul()){
			prix_=(Taux(_d->val_objets().valeur(_nom_objet)->prix()*_quantite)*Taux((long long)liste_[_indice].second,(long long)tx_)).partie_entiere();
			if(liste_[_indice].first==_quantite){
				liste_.removeAt(_indice);
			}else{
				liste_[_indice].first-=_quantite;
			}
		}else{
			prix_=Taux(_d->val_objets().valeur(_nom_objet)->prix()*_quantite);
			liste_[0].first-=_quantite;
		}
	}
	argent+=prix_;
}

void Utilisateur::achat_ct(uchar _ct,uchar _quantite){
	inventaire.ct_ut().valeur(_ct)+=_quantite;
	argent-=1000*_quantite;
}

void Utilisateur::vente_ct(uchar _ct,uchar _quantite){
	inventaire.ct_ut().valeur(_ct)-=_quantite;
	argent+=1000*_quantite;
}

void Utilisateur::obtention_cs(uchar _cs){
	inventaire.cs_ut().valeur(_cs)=true;
}

bool Utilisateur::present_pk(const QString& _nom)const{
	return pokemon_attrapes.valeur(_nom);
}

void Utilisateur::activer_repousse(const QString& _nom_objet,Donnees* _d){
	if(pas_restants_repousse>0||repousse_actif){
		return;
	}
	Repousse *repousse_=qobject_cast<Repousse*>(_d->val_objets().valeur(_nom_objet));
	pas_restants_repousse=repousse_->pas();
	repousse_actif=true;
}

int Utilisateur::pas_repousse()const{
	return pas_restants_repousse;
}

bool Utilisateur::repous_act()const{
	return repousse_actif;
}

bool Utilisateur::attrape_pk(const QString& _nom){
	bool deja_pris_=pokemon_attrapes.valeur(_nom);
	pokemon_attrapes.valeur(_nom)=true;
	return deja_pris_;
}

/*void Utilisateur::reinit_pas_reproduction(){
	
}

void Utilisateur::gain_pas_reproduction(){
	
}

int Utilisateur::pas_reproduction()const{
	
}*/

void Utilisateur::evoluer_pk_pierre(uchar _indice,const QString& _nom_pierre,QString& _com,Donnees* _d){
	int ind_=-1;
	int nb_=equipe.size();
	for(int i=0;i<nb_;i++){
		if(equipe[i].first==_indice){
			ind_=i;
			break;
		}
	}
	if(ind_<0){
		_com="ceci est un oeuf";
		return;
	}
	QString res_=equipe[ind_].second.peut_evoluer(_nom_pierre,_d);
	if(res_==equipe[ind_].second.n_pk()){
		//Si le pokemon ne peut pas evoluer
		_com="incompatibilite";
		return;
	}
	QString nom_=equipe[ind_].second.n_pk();
	equipe[ind_].second.evoluer(res_,_d);
	bool deja_pris_=attrape_pk(res_);
	_com+="Evolution de "+nom_+" en "+equipe[ind_].second.n_pk()+"\n";
	if(!deja_pris_){
		_com+="nouveau pokemon ajoute";
	}
}

Entier Utilisateur::val_argent()const{
	return argent;
}

void Utilisateur::gain_argent_combat(const Entier& _gain){
	argent+=_gain;
}

void Utilisateur::affecterFinCombat(const ElementsCombat& _combat,Donnees *_d){
	gain_argent_combat(_combat.argent());
	HashMap<Combattant,CreatureCombat> creatures_=_combat.creatures_combats();
	foreach(Combattant c,creatures_.cles()){
		if(c.equipe()!=(int)_d->val_ut()){
			continue;
		}
		int indice_=-1;
		for(int i=equipe.size()-1;i>-1;i--){
			if(equipe[i].first==c.position()){
				indice_=i;
				break;
			}
		}
		if(indice_<0){
			uchar pos_=oeufs_equipe.size()+equipe.size();
			equipe<<QPair<uchar,PokemonUtilisateur>(pos_,PokemonUtilisateur(creatures_.valeur(c),_d));
		}else{
			equipe[indice_].second.finCombat(creatures_.valeur(c));
		}
	}
}

/*void Utilisateur::attraper_pk_sauvage(const QPair<uchar,PokemonUtilisateur>& _pokemon_sauvage){
	
}*/

uint Utilisateur::attraper_pk_sauvage(const CreatureCombat& _pokemon_sauvage,Donnees *_d,uchar _max_eq){
	uchar pos_=oeufs_equipe.size()+equipe.size();
	if(pos_>=_max_eq){
		int indice_boite_=-1;
		int nb_boites_=_d->constante_numerique("NB_BOITES");
		int nb_pk_max_=_d->constante_numerique("MAX_PK_PAR_BOITE");
		for(int i=0;i<nb_boites_;i++){
			if(boites[i].size()+boites_oeufs[i].size()<nb_pk_max_){
				indice_boite_=i;
				break;
			}
		}
		if(indice_boite_<0){
			return 1023;
		}
		int taille_=boites[indice_boite_].size()+boites_oeufs[indice_boite_].size();
		boites[indice_boite_]<<QPair<uchar,PokemonUtilisateur>(taille_,PokemonUtilisateur(_pokemon_sauvage,_d));
		boites[indice_boite_].last().second.soin_total(_d);
		return indice_boite_;
	}
	equipe<<QPair<uchar,PokemonUtilisateur>(pos_,PokemonUtilisateur(_pokemon_sauvage,_d));
	return _d->constante_numerique("NB_BOITES");
}

QList<QPair<uchar,PokemonUtilisateur> > Utilisateur::equipe_ut()const{
	return equipe;
}

QList<QPair<uchar,PokemonUtilisateur> >& Utilisateur::equipe_ut(){
	return equipe;
}

void Utilisateur::echanger_place(uchar _place_1,uchar _place_2){
	if(_place_1==_place_2){
		return;
	}
	int indice_1_=-1;
	bool groupe_1_=false;
	int indice_2_=-1;
	bool groupe_2_=false;
	int nb_pk_eq_=equipe.size();
	int nb_oeufs_=oeufs_equipe.size();
	for(int i=0;i<nb_pk_eq_;i++){
		if(equipe[i].first==_place_1){
			indice_1_=i;
			break;
		}
	}
	for(int i=0;i<nb_oeufs_;i++){
		if(oeufs_equipe[i].first==_place_1){
			indice_1_=i;
			groupe_1_=true;
			break;
		}
	}
	for(int i=0;i<nb_pk_eq_;i++){
		if(equipe[i].first==_place_2){
			indice_2_=i;
			break;
		}
	}
	for(int i=0;i<nb_oeufs_;i++){
		if(oeufs_equipe[i].first==_place_2){
			indice_2_=i;
			groupe_2_=true;
			break;
		}
	}
	if(groupe_1_==groupe_2_){
		if(groupe_1_){
			OeufPokemon oeuf_=oeufs_equipe[indice_2_].second;
			oeufs_equipe[indice_2_].second=oeufs_equipe[indice_1_].second;
			oeufs_equipe[indice_1_].second=oeuf_;
		}else{
			PokemonUtilisateur pk_=equipe[indice_2_].second;
			equipe[indice_2_].second=equipe[indice_1_].second;
			equipe[indice_1_].second=pk_;
		}
	}else{
		if(groupe_1_){
			equipe[indice_2_].first=_place_1;
			oeufs_equipe[indice_1_].first=_place_2;
		}else{
			equipe[indice_1_].first=_place_2;
			oeufs_equipe[indice_2_].first=_place_1;
		}
		for(int i=0;i<nb_pk_eq_;i++){
			for(int j=i+1;j<nb_pk_eq_;j++){
				if(equipe[i].first>equipe[j].first){
					equipe.swap(i,j);
				}
			}
		}
		for(int i=0;i<nb_oeufs_;i++){
			for(int j=i+1;j<nb_oeufs_;j++){
				if(oeufs_equipe[i].first>oeufs_equipe[j].first){
					oeufs_equipe.swap(i,j);
				}
			}
		}
	}
}

QList<QPair<uchar,OeufPokemon> > Utilisateur::oeufs()const{
	return oeufs_equipe;
}

QList<QPair<uchar,OeufPokemon> >& Utilisateur::oeufs(){
	return oeufs_equipe;
}

QList<QPair<uchar,PokemonUtilisateur> >& Utilisateur::boite(uchar _indice_boite){
	return boites[_indice_boite];
}

QList<QPair<uchar,OeufPokemon> >& Utilisateur::boite_oeuf(uchar _indice_boite_oeuf){
	return boites_oeufs[_indice_boite_oeuf];
}

QList<QPair<uchar,PokemonUtilisateur> > Utilisateur::boite(uchar _indice_boite)const{
	return boites[_indice_boite];
}

QList<QPair<uchar,OeufPokemon> > Utilisateur::boite_oeuf(uchar _indice_boite_oeuf)const{
	return boites_oeufs[_indice_boite_oeuf];
}

Inventaire Utilisateur::inv()const{
	return inventaire;
}

Inventaire& Utilisateur::inv(){
	return inventaire;
}

void Utilisateur::serialiser(Flux& _out)const{
	_out<<pseudo;
	_out<<sexe_heros;
	_out<<oeufs_equipe;
	_out<<equipe;
	_out<<boites_oeufs;
	_out<<boites;
	_out<<inventaire;
	_out<<pokemon_attrapes;
	_out<<argent;
	_out<<repousse_actif;
	_out<<pas_restants_repousse;
	//_out<<pas_effectues_accoupl_pk
}

void Utilisateur::deserialiser(Flux& _in){
	_in>>pseudo;
	_in>>sexe_heros;
	_in>>oeufs_equipe;
	_in>>equipe;
	_in>>boites_oeufs;
	_in>>boites;
	_in>>inventaire;
	_in>>pokemon_attrapes;
	_in>>argent;
	_in>>repousse_actif;
	_in>>pas_restants_repousse;
	//_in>>pas_effectues_accoupl_pk
}


Flux & operator <<(Flux& out,const Utilisateur& _Utilisateur){
	_Utilisateur.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Utilisateur& _Utilisateur){
	_Utilisateur.deserialiser(in);
	return in;
}


