#include "serialisable/donnees.h"
#include "base_donnees/import.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include "base_donnees/objets/objet.h"
#include "autre/utilitaire.h"
#include "math/taux.h"
#include <QFile>
//uchar Donnees::_nb_attaques_max_=(uchar)Taux::parse_taux(Utilitaire::constante(Import::_constantes_,"DEF_MAX_ATT"));

Donnees::Donnees(){
	//TODO init coords_depart et pk_depart
	nb_attaques_max=PokemonDresse::_nb_attaques_max_;
	//(uchar)Taux::parse_taux(Utilitaire::constante(Import::_constantes_,"DEF_MAX_ATT"))
	//Donnees::_nb_attaques_max_=nb_attaques_max
	//ligue_tmp=-1//
}

bool Donnees::egal(const Donnees& _autre)const{
	bool egal_=true;
	egal_&=nb_attaques_max==_autre.nb_attaques_max;
	egal_&=lieux==_autre.lieux;
	egal_&=ligues==_autre.ligues;
	egal_&=acces_fct_ligues==_autre.acces_fct_ligues;
	egal_&=champions_battre_ligue==_autre.champions_battre_ligue;
	egal_&=lieux_vols==_autre.lieux_vols;
	egal_&=images_minimap==_autre.images_minimap;
	egal_&=coords_depart==_autre.coords_depart;
	egal_&=pk_depart==_autre.pk_depart;
	return egal_;
}

bool Donnees::est_valide()const{
	typedef QPair<QPair<int,int>,QPair<int,int> > Liaison;
	typedef QPair<int,int> Origine;
	if(lieux.total()==0||ligues.total()==0){
		return false;
	}
	bool lieu_faire_vivre_fossile_=false;
	bool pension_=false;
	bool move_tutors_=false;
	bool echanges_poke_boites_=false;
	QStringList obj_ach_;
	QList<uchar> ct_ach_;
	QList<uchar> cs_don_;
	QList<QPair<QString,QString> > pk_appar_;
	foreach(int l,lieux.cles()){
		Lieu lieu_=lieux.valeur(l);
		if(!lieu_.est_valide()){
			return false;
		}
		foreach(int p,lieu_.plateaux_c()){
			Plateau *pl_=lieu_.plateau(p);
			foreach(Origine o,pl_->coins_gauche()){
				Environnement env_=pl_->environnement(o);
				foreach(Origine a,env_.coords_achat_objets()){
					obj_ach_<<env_.achat_objets(a);
				}
				foreach(Origine a,env_.coords_achat_ct()){
					ct_ach_<<env_.achat_ct(a);
				}
				foreach(Origine a,env_.coords_don_cs()){
					cs_don_<<env_.don_cs(a);
				}
				//QList<Pokemon> appar_=env_.pokemon_obtensible()
				foreach(Pokemon p,env_.pokemon_obtensible()){
					if(!pk_appar_.contains(QPair<QString,QString>(*p.adr_nom(),*p.adr_genre()))){
						pk_appar_<<QPair<QString,QString>(*p.adr_nom(),*p.adr_genre());
					}
				}
				//_bases_evos_ QList<Pokemon> pokemon_obtensible()
				//coords_don_cs()
				//coords_achat_objets()
				if(env_.nb_echanges_poke_boites()>0){
					echanges_poke_boites_=true;
				}
				//echanges_poke_boites_
				if(env_.nb_lieu_faire_revivre_fossile()>0){
					lieu_faire_vivre_fossile_=true;
				}
				if(env_.nb_pensions()>0){
					pension_=true;
				}
				if(env_.nb_move_tutors()>0){
					move_tutors_=true;
				}
				//nb_move_tutors(
			}
			QList<Liaison> lais_=pl_->liaisons_vers_autres_plateaux();
			foreach(Liaison l,lais_){
				if(!pl_->coins_gauche().contains(l.first)){
					return false;
				}
				Environnement env_2_=pl_->environnement(l.first);
				if(*env_2_.type_env()==""||!env_2_.est_vide(l.second)){
					return false;
				}
				Coordonnees coords_=pl_->destination_autre_plateau(l);
				if(!lieux.cles().contains(coords_.lieu())){
					return false;
				}
				Lieu lieu_2_=lieux.valeur(coords_.lieu());
				if(!lieu_2_.plateaux_c().contains(coords_.plateau())){
					return false;
				}
				Plateau *pl_2_=lieu_2_.plateau(coords_.plateau());
				if(!pl_2_->coins_gauche().contains(coords_.coords_environnement())){
					return false;
				}
				Environnement env_=pl_2_->environnement(coords_.coords_environnement());
				if(*env_.type_env()==""||!env_.est_vide(coords_.coords_tuile())){
					return false;
				}
			//
			}
		}
	}
	/**
		QList<uchar> ct_ach_
	QList<uchar> cs_don_
	*/
	Utilitaire::trier<uchar>(ct_ach_);
	Utilitaire::trier<uchar>(cs_don_);
	int i_=0;
	while(i_<ct_ach_.size()){
		while(i_<ct_ach_.size()-1&&ct_ach_[i_]==ct_ach_[i_+1]){
			ct_ach_.removeAt(i_+1);
		}
		i_++;
	}
	i_=0;
	while(i_<cs_don_.size()){
		while(i_<cs_don_.size()-1&&cs_don_[i_]==cs_don_[i_+1]){
			cs_don_.removeAt(i_+1);
		}
		i_++;
	}
	if(Import::_ct_.cles().size()!=ct_ach_.size()){
		return false;
	}
	if(Import::_cs_.cles().size()!=cs_don_.size()){
		return false;
	}
	Utilitaire::trier<QPair<QString,QString> >(pk_appar_);
	QList<QPair<QString,QString> > pk_appar_base_;
	typedef QPair<QString,QString> NomGenre;
	foreach(NomGenre n,pk_appar_){
		QString base_ev_=Import::_pokedex_.valeur(n.first)->b_ev();
		if(!pk_appar_base_.contains(NomGenre(base_ev_,n.second))){
			pk_appar_base_<<NomGenre(base_ev_,n.second);
		}
	}
	Utilitaire::trier<QPair<QString,QString> >(pk_appar_base_);
	foreach(QString n,Import::_bases_evos_){
		FichePokemon *f_pk_=Import::_pokedex_.valeur(n);
		if(f_pk_->rep_genr()=="MIXTE"){
			int nb_=0;
			foreach(NomGenre n2,pk_appar_base_){
				if(n2.first==n){
					nb_++;
				}
			}
			if(nb_!=2){
				return false;
			}
		}else{
			int nb_=0;
			foreach(NomGenre n2,pk_appar_base_){
				if(n2.first==n){
					nb_++;
				}
			}
			if(nb_!=1){
				return false;
			}
		}//ASSEXUE
	}
	obj_ach_.removeDuplicates();
	obj_ach_.sort();
	foreach(QString o,Import::_objets_.cles()){
		if(Import::_objets_.valeur(o)->estAchetable()){
			if(!obj_ach_.contains(o)){
				return false;
			}
		}
	}
	foreach(int l,ligues.cles()){
		Ligue ligue_=ligues.valeur(l);
		if(!ligue_.est_valide()){
			return false;
		}
		Coordonnees *coords_=ligue_.adr_origine();
		if(!lieux.cles().contains(coords_->lieu())){
			return false;
		}
		Lieu lieu_2_=lieux.valeur(coords_->lieu());
		if(!lieu_2_.plateaux_c().contains(coords_->plateau())){
			return false;
		}
		Plateau *pl_2_=lieu_2_.plateau(coords_->plateau());
		if(!pl_2_->coins_gauche().contains(coords_->coords_environnement())){
			return false;
		}
		Environnement env_=pl_2_->environnement(coords_->coords_environnement());
		if(*env_.type_env()==""||!env_.est_vide(coords_->coords_tuile())){
			return false;
		}
	}
	Lieu lieu_2_=lieux.valeur(coords_depart.lieu());
	if(!lieu_2_.plateaux_c().contains(coords_depart.plateau())){
		return false;
	}
	Plateau *pl_2_=lieu_2_.plateau(coords_depart.plateau());
	if(!pl_2_->coins_gauche().contains(coords_depart.coords_environnement())){
		return false;
	}
	Environnement env_=pl_2_->environnement(coords_depart.coords_environnement());
	if(*env_.type_env()==""||!env_.est_vide(coords_depart.coords_tuile())){
		return false;
	}
	typedef QPair<int,int> Position;
	foreach(Position p,lieux_vols.cles()){
		Coordonnees coords_=lieux_vols.valeur(p);
		lieu_2_=lieux.valeur(coords_.lieu());
		if(!lieu_2_.plateaux_c().contains(coords_.plateau())){
			return false;
		}
		pl_2_=lieu_2_.plateau(coords_.plateau());
		if(!pl_2_->coins_gauche().contains(coords_.coords_environnement())){
			return false;
		}
		env_=pl_2_->environnement(coords_.coords_environnement());
		if(*env_.type_env()==""||!env_.est_vide(coords_.coords_tuile())){
			return false;
		}
		/*if(!lieu_2_.plateau(coords_.plateau())->environnement(coords_.coords_environnement()).est_vide(coords_.coords_tuile())){
			return false
		}*/
	}
	Pokemon pk_=pk_depart;
	if(*pk_.adr_nom()==""){
		return false;
	}
	//TODO il faut attraper les 650 pk de toutes les manieres et pk_depart et il existe au moins un champion d'arene
	/**
	bool lieu_faire_vivre_fossile_=false
	bool pension_=false
	bool move_tutors_=false
	bool echanges_poke_boites_=false
	*/
	foreach(Coordonnees c,acces_fct_ligues.cles()){
		lieu_2_=lieux.valeur(c.lieu());
		if(!lieu_2_.plateaux_c().contains(c.plateau())){
			return false;
		}
		pl_2_=lieu_2_.plateau(c.plateau());
		if(!pl_2_->coins_gauche().contains(c.coords_environnement())){
			return false;
		}
		env_=pl_2_->environnement(c.coords_environnement());
		if(!env_.existe(c.coords_tuile())){
			return false;
		}
		foreach(int l,acces_fct_ligues.valeur(c)){
			if(!ligues_c().contains(l)){
				return false;
			}
		}
	}
	foreach(int l,champions_battre_ligue.cles()){
		if(!ligues_c().contains(l)){
			return false;
		}
		foreach(Coordonnees c,champions_battre_ligue.valeur(l)){
			lieu_2_=lieux.valeur(c.lieu());
			if(!lieu_2_.plateaux_c().contains(c.plateau())){
				return false;
			}
			pl_2_=lieu_2_.plateau(c.plateau());
			if(!pl_2_->coins_gauche().contains(c.coords_environnement())){
				return false;
			}
			env_=pl_2_->environnement(c.coords_environnement());
			if(!env_.coords_champions().contains(c.coords_tuile())){
				return false;
			}
		}
	}
	foreach(int l,champions_battre_ligue.cles()){
		foreach(int l2,champions_battre_ligue.cles()){
			if(!Utilitaire::contient<Coordonnees>(champions_battre_ligue.valeur(l),champions_battre_ligue.valeur(l2))){
				if(!Utilitaire::contient<Coordonnees>(champions_battre_ligue.valeur(l2),champions_battre_ligue.valeur(l))){
					return false;
				}
			}
		}
	}
	return lieu_faire_vivre_fossile_&&pension_&&move_tutors_&&echanges_poke_boites_;
}
	/*int *Donnees::adr_ligue_tmp(){
		return &ligue_tmp
	}*/

HashMap<Coordonnees,QList<int> > *Donnees::adr_acces_fct_ligues(){
	return &acces_fct_ligues;
}

HashMap<int,QList<Coordonnees> > *Donnees::adr_champions_battre_ligue(){
	return &champions_battre_ligue;
}

HashMap<Coordonnees,Champion> Donnees::val_champions_battre()const{
	return champions_battre;
}

void Donnees::maj_champions_battre(const Coordonnees& _coords,const Champion& _champion){
	champions_battre.ajouter_cle_valeur(_coords,_champion);
}

void Donnees::supprimer_champions_battre(const Coordonnees& _coords){
	champions_battre.supprimer_cle_valeur(_coords);
}

Coordonnees *Donnees::adr_coords_depart(){
	return &coords_depart;
}

Pokemon *Donnees::adr_pk_depart(){
	return &pk_depart;
}

bool Donnees::peuvent_etre_lies_lieux(int _lieu_1,int _plateau_1,int _lieu_2,int _plateau_2,Lieu::Orientation _or)const{
	//liaisons_vers_autres_lieux()
	//destination_autre_lieu(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _origine)
	Lieu lieu_1_=lieux.valeur(_lieu_1);
	Lieu lieu_2_=lieux.valeur(_lieu_2);
	Plateau *plateau_1_=lieu_1_.plateau(_plateau_1);
	Plateau *plateau_2_=lieu_2_.plateau(_plateau_2);
	QPair<QPair<int,int>,QPair<int,int> > bords_1_=plateau_1_->bords();
	QPair<QPair<int,int>,QPair<int,int> > bords_2_=plateau_2_->bords();
	typedef QPair<int,QPair<QPair<int,int>,QPair<int,int> > > Origine;
	QList<Origine> origines_1_=lieu_1_.liaisons_vers_autres_lieux();
	QList<Origine> origines_2_=lieu_2_.liaisons_vers_autres_lieux();
	QList<Origine> origines_1_pl_;
	foreach(Origine o,origines_1_){
		if(o.first==_plateau_1){
			origines_1_pl_<<o;
		}
	}
	QList<Origine> origines_2_pl_;
	foreach(Origine o,origines_2_){
		if(o.first==_plateau_2){
			origines_2_pl_<<o;
		}
	}
	if(_or==Lieu::GAUCHE){
		foreach(Origine o,origines_1_pl_){
			if(o.second.first.first+o.second.second.first==bords_1_.first.first){
				return false;
			}
		}
		foreach(Origine o,origines_2_pl_){
			if(o.second.first.first+o.second.second.first==bords_2_.second.first){
				return false;
			}
		}
	}else if(_or==Lieu::DROITE){
		foreach(Origine o,origines_1_pl_){
			if(o.second.first.first+o.second.second.first==bords_1_.second.first){
				return false;
			}
		}
		foreach(Origine o,origines_2_pl_){
			if(o.second.first.first+o.second.second.first==bords_2_.first.first){
				return false;
			}
		}
	}else if(_or==Lieu::HAUT){
		foreach(Origine o,origines_1_pl_){
			if(o.second.first.second+o.second.second.second==bords_1_.first.second){
				return false;
			}
		}
		foreach(Origine o,origines_2_pl_){
			if(o.second.first.second+o.second.second.second==bords_2_.second.second){
				return false;
			}
		}
	}else{
		foreach(Origine o,origines_1_pl_){
			if(o.second.first.second+o.second.second.second==bords_1_.second.second){
				return false;
			}
		}
		foreach(Origine o,origines_2_pl_){
			if(o.second.first.second+o.second.second.second==bords_2_.first.second){
				return false;
			}
		}
	}
	return true;
}

void Donnees::enlever_tous_liens_vers_plat(int _lieu,int _plateau){
	Lieu *lieu_=lieu(_lieu);
	Plateau *plateau_=lieu_->plateau(_plateau);
	typedef QPair<QPair<int,int>,QPair<int,int> > Origine;
	typedef QPair<int,QPair<QPair<int,int>,QPair<int,int> > > OrigineLien;
	QList<Origine> liens_pls_=plateau_->liaisons_vers_autres_plateaux();
	QList<Coordonnees> arrivees_;
	foreach(Origine o,liens_pls_){
		arrivees_<<plateau_->destination_autre_plateau(o);
	}
	foreach(int i,lieux.cles()){
		if(i!=_lieu){
			Lieu *lieu_2_=lieu(i);
			QList<OrigineLien> origines_=lieu_2_->liaisons_vers_autres_lieux();
			foreach(OrigineLien o,origines_){
				//destination_autre_lieu
				Coordonnees c_=lieu_2_->destination_autre_lieu(o);
				if(*c_.adr_lieu_plateau()==QPair<int,int>(_lieu,_plateau)){
					lieu_2_->supprimer_dest_autre_lieu(o);
				}
			}
			foreach(int j,lieu_2_->plateaux_c()){
				Plateau *plateau_2_=lieu_2_->plateau(j);
				foreach(Origine o,plateau_2_->liaisons_vers_autres_plateaux()){
					Coordonnees c_=plateau_2_->destination_autre_plateau(o);
					if(*c_.adr_lieu_plateau()==QPair<int,int>(_lieu,_plateau)){
						plateau_2_->supprimer_dest_autre_plateau(o);
					}
				}
			}
		}
	}
	foreach(int i,lieu_->plateaux_c()){
		if(i!=_plateau){
			Plateau *plateau_2_=lieu_->plateau(i);
			foreach(Origine o,plateau_2_->liaisons_vers_autres_plateaux()){
				Coordonnees c_=plateau_2_->destination_autre_plateau(o);
				if(*c_.adr_lieu_plateau()==QPair<int,int>(_lieu,_plateau)){
					plateau_2_->supprimer_dest_autre_plateau(o);
				}
			}
		}
	}
	foreach(Origine o,plateau_->liaisons_vers_autres_plateaux()){
		plateau_->supprimer_dest_autre_plateau(o);
	}
	QList<OrigineLien> origines_=lieu_->liaisons_vers_autres_lieux();
	foreach(OrigineLien o,origines_){
		if(o.first==_plateau){
			lieu_->supprimer_dest_autre_lieu(o);
		}
	}
	/*foreach(Coordonnees c,arrivees_){
		if(c.lieu()!=_lieu){
			Lieu *lieu_2_=lieu(c.lieu())
			Plateau *plateau_2_=lieu_2_->plateau(c.plateau())
			foreach(Origine o,plateau_2_->liaisons_vers_autres_plateaux()){
				Coordonnees c_=plateau_2_->destination_autre_plateau(o)
				if(*c_.adr_lieu_plateau()==QPair<int,int>(_lieu,_plateau)){
					plateau_2_->supprimer_dest_autre_plateau(o)
				}
			}
		}else if(c.plateau()!=_plateau){
			Plateau *plateau_2_=lieu_->plateau(c.plateau())
			foreach(Origine o,plateau_2_->liaisons_vers_autres_plateaux()){
				Coordonnees c_=plateau_2_->destination_autre_plateau(o)
				if(*c_.adr_lieu_plateau()==QPair<int,int>(_lieu,_plateau)){
					plateau_2_->supprimer_dest_autre_plateau(o)
				}
			}
		}else{
			
		}
	}*/
}

uchar *Donnees::adr_nb_attaques_max(){
	return &nb_attaques_max;
}

Lieu *Donnees::lieu(int _indice){
	bool suppr_=false;
	return lieux.valeur(_indice,suppr_);
}

void Donnees::ajouter_lieu(int _indice,const Lieu& _lieu){
	lieux.ajouter_cle_valeur(_indice,_lieu);
	Lieu *lieu_=lieu(_indice);
	nom_types_lieux.ajouter_cle_valeur(_indice,QPair<QString,QString>(*lieu_->adr_nom(),*lieu_->adr_type()));
}

QList<int> Donnees::lieux_c()const{
	return lieux.cles();
}

HashMap<int,QPair<QString,QString> > Donnees::nom_type_lieux()const{
	return nom_types_lieux;
}

void Donnees::maj_nom_type_lieu(int _lieu,const QPair<QString,QString>& _nom_type){
	nom_types_lieux.ajouter_cle_valeur(_lieu,_nom_type);
}

void Donnees::delier_plateaux_lieux_diff(int _lieu_orig,int _plateau_orig,const QPair<QPair<int,int>,QPair<int,int> >& _deb_lien){
	Lieu *lieu_or_=lieu(_lieu_orig);
	Plateau *plateau_or_=lieu_or_->plateau(_plateau_orig);
	plateau_or_->supprimer_dest_autre_plateau(_deb_lien);
}

void Donnees::delier_plateaux_lieux_diff_double(int _lieu_orig,int _plateau_orig,const QPair<QPair<int,int>,QPair<int,int> >& _deb_lien){
	Lieu *lieu_or_=lieu(_lieu_orig);
	Plateau *plateau_or_=lieu_or_->plateau(_plateau_orig);
	Coordonnees dest_autre_l_=plateau_or_->destination_autre_plateau(_deb_lien);
	//destination_autre_plateau
	Lieu *lieu_dest_=lieu(dest_autre_l_.lieu());
	Plateau *plateau_dest_=lieu_dest_->plateau(dest_autre_l_.plateau());
	if(plateau_dest_->liaisons_vers_autres_plateaux().contains(dest_autre_l_.coords_par_rap_plateau())){
		plateau_dest_->supprimer_dest_autre_plateau(dest_autre_l_.coords_par_rap_plateau());
	}
	plateau_or_->supprimer_dest_autre_plateau(_deb_lien);//destination_autre_plateau
}

void Donnees::supprimer_lieu(int _indice){
	QList<int> cles_=lieux.cles();
	foreach(int i,cles_){
		delier_lieux(i,_indice);
	}
	bool suppr_=false;
	typedef QPair<QPair<int,int>,QPair<int,int> > Origine;
	foreach(int i,cles_){
		Lieu *lieu_=lieu(i);
		QList<int> cles_pl_=lieu_->plateaux_c();
		if(i!=_indice){
			foreach(int j,cles_pl_){
				foreach(Origine o,lieu_->plateau(j)->liaisons_vers_autres_plateaux()){
					if(lieu_->plateau(j)->destination_autre_plateau(o,suppr_)->lieu()==_indice){
						lieu_->plateau(j)->supprimer_dest_autre_plateau(o);
					}
				}
			}
		}else{
			foreach(int j,cles_pl_){
				foreach(Origine o,lieu_->plateau(j)->liaisons_vers_autres_plateaux()){
					lieu_->plateau(j)->supprimer_dest_autre_plateau(o);
				}
			}
		}
	}
	typedef QPair<int,int> OrigineVol;
	foreach(OrigineVol c,lieux_vols.cles()){
		if(lieux_vols.valeur(c,suppr_)->lieu()==_indice){
			lieux_vols.supprimer_cle_valeur(c);
		}
	}
	lieux.supprimer_cle_valeur(_indice);
	nom_types_lieux.supprimer_cle_valeur(_indice);
}

Ligue *Donnees::ligue(int _indice){
	bool suppr_=false;
	return ligues.valeur(_indice,suppr_);
}

void Donnees::ajouter_ligue(int _indice,const Ligue& _ligue){
	ligues.ajouter_cle_valeur(_indice,_ligue);
}

void Donnees::supprimer_ligue(int _indice){
	ligues.supprimer_cle_valeur(_indice);
}

QList<int> Donnees::ligues_c()const{
	return ligues.cles();
}

HashMap<QPair<int,int>,Coordonnees> Donnees::vols()const{
	return lieux_vols;
}

void Donnees::maj_vols(const HashMap<QPair<int,int>,Coordonnees>& _lieux_vols){
	lieux_vols=_lieux_vols;
}

HashMap<QPair<int,int>,QString> Donnees::minimap()const{
	return images_minimap;
}

void Donnees::maj_minimap(const HashMap<QPair<int,int>,QString>& _images_minimap){
	images_minimap=_images_minimap;
}

QString *Donnees::image_minimap(const QPair<int,int>& _id_lieu,bool& _n_instance){
	return images_minimap.valeur(_id_lieu,_n_instance);
}

QString Donnees::image_minimap(const QPair<int,int>& _id_lieu)const{
	return images_minimap.valeur(_id_lieu);
}

void Donnees::ajouter_image_minimap(const QPair<int,int>& _id_lieu,const QString& _nom_fic){
	images_minimap.ajouter_cle_valeur(_id_lieu,_nom_fic);
}


void Donnees::supprimer_image_minimap(const QPair<int,int>& _id_lieu){
	images_minimap.supprimer_cle_valeur(_id_lieu);
}

	;
QList<QPair<int,int> > Donnees::origines_images_minimap()const{
	return images_minimap.cles();
}

Coordonnees *Donnees::lieu_vols(const QPair<int,int>& _id_lieu,bool& _n_instance){
	return lieux_vols.valeur(_id_lieu,_n_instance);
}

Coordonnees Donnees::lieu_vols(const QPair<int,int>& _id_lieu)const{
	return lieux_vols.valeur(_id_lieu);
}

void Donnees::ajouter_lieu_vols(const QPair<int,int>& _id_lieu,const Coordonnees& _coords_arrivee){
	lieux_vols.ajouter_cle_valeur(_id_lieu,_coords_arrivee);
}

void Donnees::supprimer_lieu_vols(const QPair<int,int>& _id_lieu){
	lieux_vols.supprimer_cle_valeur(_id_lieu);
}

QList<QPair<int,int> > Donnees::origines_vols()const{
	return lieux_vols.cles();
}

void Donnees::relier_lieux(int _indice_l,int _indice_l_2,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords_2){
	Lieu *lieu_1_=lieu(_indice_l);
	Lieu *lieu_2_=lieu(_indice_l_2);
	Plateau pl_1_=*lieu_1_->plateau(_coords.first);
	Plateau pl_2_=*lieu_2_->plateau(_coords_2.first);
	QList<QPair<QPair<int,int>,QPair<int,int> > > futurs_cles_;
	QList<QPair<QPair<int,int>,QPair<int,int> > > futurs_cles_2_;
	if(lieu_1_->peuvent_etre_lie_avec(_coords,pl_2_,_coords_2,futurs_cles_)&&lieu_2_->peuvent_etre_lie_avec(_coords_2,pl_1_,_coords,futurs_cles_2_)){
		relier_lieux(_indice_l,_indice_l_2,_coords,_coords_2,futurs_cles_,futurs_cles_2_);
	}
}

void Donnees::relier_lieux(int _indice_l,int _indice_l_2,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords_2,const QList<QPair<QPair<int,int>,QPair<int,int> > >& _futurs_cles,const QList<QPair<QPair<int,int>,QPair<int,int> > >& _futurs_cles_2){
	Lieu *lieu_1_=lieu(_indice_l);
	Lieu *lieu_2_=lieu(_indice_l_2);
	Plateau pl_1_=*lieu_1_->plateau(_coords.first);
	Plateau pl_2_=*lieu_2_->plateau(_coords_2.first);
	lieu_1_->relier_avec_autre_lieu(_indice_l_2,_coords,pl_2_,_coords_2,_futurs_cles);
	lieu_2_->relier_avec_autre_lieu(_indice_l,_coords_2,pl_1_,_coords,_futurs_cles_2);
}

void Donnees::delier_lieux(int _indice,int _indice_2){
	Lieu *lieu_1_=lieu(_indice);
	Lieu *lieu_2_=lieu(_indice_2);
	lieu_1_->delier_lieux(_indice_2);
	lieu_2_->delier_lieux(_indice);
}

void Donnees::desouder_lieux_plateau(int _indice_l,int _indice_l_2,int _indice_p,int _indice_p_2){
	Lieu *lieu_1_=lieu(_indice_l);
	Lieu *lieu_2_=lieu(_indice_l_2);
	typedef QPair<int,QPair<QPair<int,int>,QPair<int,int> > > OrigineLienLieu;
	QList<OrigineLienLieu> liens_=lieu_1_->liaisons_vers_autres_lieux();
	QList<OrigineLienLieu> liens_bis_;
	foreach(OrigineLienLieu o,liens_){
		if(o.first==_indice_p){
			liens_bis_<<o;
		}
	}
	foreach(OrigineLienLieu o,liens_bis_){
		Coordonnees coords_=lieu_1_->destination_autre_lieu(o);
		if(coords_.lieu()==_indice_l_2&&coords_.plateau()==_indice_p_2){
			lieu_1_->supprimer_dest_autre_lieu(o);
		}
	}
	liens_bis_.clear();
	liens_=lieu_2_->liaisons_vers_autres_lieux();
	foreach(OrigineLienLieu o,liens_){
		if(o.first==_indice_p_2){
			liens_bis_<<o;
		}
	}
	foreach(OrigineLienLieu o,liens_bis_){
		Coordonnees coords_=lieu_2_->destination_autre_lieu(o);
		if(coords_.lieu()==_indice_l&&coords_.plateau()==_indice_p){
			lieu_2_->supprimer_dest_autre_lieu(o);
		}
	}
}

QString Donnees::exporter()const{
	int nb_tab_=0;
	QString descr_="<NbAt>"+QString::number(nb_attaques_max)+"</NbAt>\n";
	QList<int> cles_l_=lieux.cles();
	int nb_tab_attr_=nb_tab_;
	foreach(int i,cles_l_){
		descr_+=QString::number(i)+":\n";
		descr_+=lieux.valeur(i).exporter(nb_tab_attr_);
	}
	cles_l_=ligues.cles();
	foreach(int i,cles_l_){
		descr_+=QString::number(i)+":\n";
		descr_+=ligues.valeur(i).exporter(nb_tab_attr_);
	}
	descr_+=coords_depart.formater()+"\n";
	descr_+=pk_depart.exporter(nb_tab_attr_);
	typedef QPair<int,int> Origine;
	foreach(Origine cle_,lieux_vols.cles()){
		for(int i=0;i<nb_tab_attr_;i++){
			descr_+="\t";
		}
		descr_+="LV:"+QString::number(cle_.first)+","+QString::number(cle_.second)+":";
		descr_+=lieux_vols.valeur(cle_).formater()+"\n";
	}
	foreach(Origine cle_,images_minimap.cles()){
		for(int i=0;i<nb_tab_attr_;i++){
			descr_+="\t";
		}
		descr_+="IMG:"+QString::number(cle_.first)+","+QString::number(cle_.second)+":";
		descr_+=images_minimap.valeur(cle_)+"\n";
	}
	foreach(Coordonnees c,acces_fct_ligues.cles()){
		QList<int> ligues_=acces_fct_ligues.valeur(c);
		if(!ligues_.isEmpty()){
			for(int i=0;i<nb_tab_attr_;i++){
				descr_+="\t";
			}
			descr_+="ACC:"+c.formater()+":"+QString::number(ligues_[0]);
			int nb_l_=ligues_.size();
			for(int i=1;i<nb_l_;i++){
				descr_+=","+QString::number(ligues_[i]);
			}
			/*foreach(int l,acces_fct_ligues.valeur(c)){
				descr_+=QString::number(l)+","
			}
			descr_.chop(1)*/
			descr_+="\n";
		}
	}
	foreach(int l,champions_battre_ligue.cles()){
		QList<Coordonnees> coords_=champions_battre_ligue.valeur(l);
		if(!coords_.isEmpty()){
			for(int i=0;i<nb_tab_attr_;i++){
				descr_+="\t";
			}
			descr_+="CHAMP:"+QString::number(l)+":"+coords_[0].formater();
			int nb_l_=coords_.size();
			for(int i=1;i<nb_l_;i++){
				descr_+="_"+coords_[i].formater();
			}
			descr_+="\n";
		}
	}
	return descr_;
}

void Donnees::sauvegarder(const QString& _nom_fichier)const{
	Flux flux_;
	flux_<<(*this);
	flux_.ecrire(_nom_fichier);
}

void Donnees::charger(const QString& _nom_fichier){
	Flux flux_;
	flux_.lire(_nom_fichier);
	flux_>>(*this);
	nom_types_lieux=HashMap<int,QPair<QString,QString> >();
	champions_battre=HashMap<Coordonnees,Champion>();
	typedef QPair<int,int> Position;
	bool suppr_=false;
	foreach(int c,lieux.cles()){
		Lieu *lieu_=lieu(c);
		nom_types_lieux.ajouter_cle_valeur(c,QPair<QString,QString>(*lieu_->adr_nom(),*lieu_->adr_type()));
		foreach(int p,lieu_->plateaux_c()){
			Plateau *pl_=lieu_->plateau(p);
			foreach(Position p2,pl_->coins_gauche()){
				Environnement *env_=pl_->environnement(p2,suppr_);
				foreach(Position p3,env_->coords_champions()){
					Coordonnees c_;
					*c_.adr_lieu_plateau()=Position(c,p);
					*c_.adr_environnement()=p2;
					*c_.adr_tuile()=p3;
					champions_battre.ajouter_cle_valeur(c_,*env_->champion(p3,suppr_));
				}
			}
		}
	}
}

/*Donnees Donnees::charger_statique(const QString& nom_fichier){
	Donnees donnees_=Donnees()
	donnees_.charger(nom_fichier)
	return donnees_
}*/

void Donnees::serialiser(Flux& _out)const{
	_out<<nb_attaques_max;
	_out<<pk_depart;
	_out<<lieux;
	_out<<ligues;
	_out<<lieux_vols;
	_out<<images_minimap;
	_out<<coords_depart;
	_out<<acces_fct_ligues;
	_out<<champions_battre_ligue;
	//_out<<plateau_tmp
}

void Donnees::deserialiser(Flux& _in){
	_in>>nb_attaques_max;
	_in>>pk_depart;
	_in>>lieux;
	_in>>ligues;
	_in>>lieux_vols;
	_in>>images_minimap;
	_in>>coords_depart;
	_in>>acces_fct_ligues;
	_in>>champions_battre_ligue;
	//_in>>plateau_tmp
}

Flux & operator <<(Flux& out,const Donnees& _Donnees){
	_Donnees.serialiser(out);
	return out;
}

Flux & operator >>(Flux& in,Donnees& _Donnees){
	_Donnees.deserialiser(in);
	return in;
}



