#include "base_donnees/cartes/environnement.h"
#include "base_donnees/personnages/personnage.h"
#include "base_donnees/personnages/champion.h"
const QString Environnement::_canne_="CANNE";
const QString Environnement::_super_canne_="SUPER_CANNE";
const QString Environnement::_mega_canne_="MEGA_CANNE";
const QString Environnement::_roche_="ROCHE";
const QString Environnement::_herbe_="HERBE";
const QString Environnement::_route_="ROUTE";
const QString Environnement::_eau_="EAU";
const QString Environnement::_batiment_="BATIMENT";
const QString Environnement::_neige_="NEIGE";
const QString Environnement::_glace_="GLACE";
const QString Environnement::_cascade_="CASCADE";


Environnement::Environnement(const QStringList& _lignes){
	nb_pas_moyen_pour_appar=0;
	largeur=_lignes[0].split(">")[1].split("<")[0].toInt();
	type_environnement=_lignes[1].split(">")[1].split("<")[0];
	int ind_=2;
	while(_lignes[ind_].contains("<Tuile>")){
		tuiles<<new Tuile(_lignes[ind_]);
		ind_++;
	}
	while(_lignes[ind_].contains("<Champ coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		ind_++;
		int ind_deb_=ind_;
		while(!_lignes[ind_].contains("</Champ>")){
			ind_++;
		}
		personnages.ajouter_cle_valeur(x_y_,new Champion(_lignes.mid(ind_deb_,ind_-ind_deb_)));
		ind_++;
	}
	while(_lignes[ind_].contains("<Dres coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		ind_++;
		int ind_deb_=ind_;
		while(!_lignes[ind_].contains("</Dres>")){
			ind_++;
		}
		personnages.ajouter_cle_valeur(x_y_,new Dresseur1(_lignes.mid(ind_deb_,ind_-ind_deb_)));
		ind_++;
	}
	while(_lignes[ind_].contains("<Pers coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		ind_++;
		int ind_deb_=ind_;
		while(!_lignes[ind_].contains("</Pers>")){
			ind_++;
		}
		personnages.ajouter_cle_valeur(x_y_,new Personnage(_lignes.mid(ind_deb_,ind_-ind_deb_)));
		ind_++;
	}
	while(_lignes[ind_].contains("<Obj coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		objets.ajouter_cle_valeur(x_y_,_lignes[ind_].split(">")[1].split("<")[0]);
		ind_++;
	}
	while(_lignes[ind_].contains("<DonObj coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		objets_donnes_ramasses.ajouter_cle_valeur(x_y_,_lignes[ind_].split(">")[1].split("<")[0]);
		ind_++;
	}
	while(_lignes[ind_].contains("<DonPk coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		ind_++;
		int ind_deb_=ind_+1;
		while(!_lignes[ind_].contains("</DonPk>")){
			ind_++;
		}
		lieux_dons_pokemon.ajouter_cle_valeur(x_y_,new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_-1)));
		ind_++;
	}
	while(_lignes[ind_].contains("<AchObj coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		achats_objets.ajouter_cle_valeur(x_y_,_lignes[ind_].split(">")[1].split("<")[0].split(";"));
		ind_++;
	}
	while(_lignes[ind_].contains("<AchCt coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		QStringList cts_=_lignes[ind_].split(">")[1].split("<")[0].split(",");
		QList<uchar> cts_2_;
		foreach(QString t,cts_){
			cts_2_<<(uchar)t.toUInt();
		}
		achats_ct.ajouter_cle_valeur(x_y_,cts_2_);
		ind_++;
	}
	while(_lignes[ind_].contains("<DonCs coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		QStringList cts_=_lignes[ind_].split(">")[1].split("<")[0].split(",");
		QList<uchar> cts_2_;
		foreach(QString t,cts_){
			cts_2_<<(uchar)t.toUInt();
		}
		dons_cs.ajouter_cle_valeur(x_y_,cts_2_);
		ind_++;
	}
	if(!_lignes[ind_].contains("<CtrePk></CtrePk>")){
		QStringList coords_=_lignes[ind_].split(">")[1].split("<")[0].split(";");
		foreach(QString c,coords_){
			QStringList c_=c.split(",");
			centres_poke<<QPair<int,int>(c_[0].toInt(),c_[1].toInt());
		}
	}
	ind_++;
	if(!_lignes[ind_].contains("<EchPk></EchPk>")){
		QStringList coords_=_lignes[ind_].split(">")[1].split("<")[0].split(";");
		foreach(QString c,coords_){
			QStringList c_=c.split(",");
			echanges_poke_boites<<QPair<int,int>(c_[0].toInt(),c_[1].toInt());
		}
	}
	ind_++;
	if(!_lignes[ind_].contains("<Pens></Pens>")){
		QStringList coords_=_lignes[ind_].split(">")[1].split("<")[0].split(";");
		foreach(QString c,coords_){
			QStringList c_=c.split(",");
			pensions<<QPair<int,int>(c_[0].toInt(),c_[1].toInt());
		}
	}
	ind_++;
	if(!_lignes[ind_].contains("<MT></MT>")){
		QStringList coords_=_lignes[ind_].split(">")[1].split("<")[0].split(";");
		foreach(QString c,coords_){
			QStringList c_=c.split(",");
			move_tutors<<QPair<int,int>(c_[0].toInt(),c_[1].toInt());
		}
	}
	ind_++;
	if(!_lignes[ind_].contains("<LFoss></LFoss>")){
		QStringList coords_=_lignes[ind_].split(">")[1].split("<")[0].split(";");
		foreach(QString c,coords_){
			QStringList c_=c.split(",");
			lieu_faire_revivre_fossile<<QPair<int,int>(c_[0].toInt(),c_[1].toInt());
		}
	}
	ind_++;
	QStringList coords_m_=_lignes[ind_].split(">")[1].split("<")[0].split(",");
	muret.first=coords_m_[0].toInt();
	muret.second=coords_m_[1].toInt();
	ind_+=2;
	while(!_lignes[ind_].contains("</ApparPer>")){
		//apparition_per_pok
		int ind_deb_=ind_+1;
		while(!_lignes[ind_].contains("</Pok>")){
			ind_++;
		}
		apparition_per_pok<<new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_));
		ind_++;
	}
	if(!apparition_per_pok.isEmpty()){//nb_pas_moyen_pour_appar
		int proba_=apparition_per_pok.size();
		ind_+=2;
		while(!_lignes[ind_].contains("</ApparAlea>")){
			int ind_deb_=ind_+1;
			while(!_lignes[ind_].contains("</Pok>")){
				ind_++;
			}
			proba_=_lignes[ind_+1].split(">")[1].split("<")[0].toInt();
			apparition_alea_pok.ajouter_event(QPair<PokemonSauvage*,Entier>(new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)),Entier(proba_)));
			ind_+=2;
		}
		nb_pas_moyen_pour_appar=proba_/apparition_per_pok.size()+1;
		ind_+=2;
		while(!_lignes[ind_].contains("</ApparPerSansLeg>")){
			//apparition_per_pok
			int ind_deb_=ind_+1;
			while(!_lignes[ind_].contains("</Pok>")){
				ind_++;
			}
			apparition_per_pok_sans_leg<<new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_));
			ind_++;
		}
		if(!apparition_per_pok_sans_leg.isEmpty()){//nb_pas_moyen_pour_appar
			int proba_=apparition_per_pok_sans_leg.size();
			ind_+=2;
			while(!_lignes[ind_].contains("</ApparAlea>")){
				int ind_deb_=ind_+1;
				while(!_lignes[ind_].contains("</Pok>")){
					ind_++;
				}
				proba_=_lignes[ind_+1].split(">")[1].split("<")[0].toInt();
				apparition_alea_pok_sans_leg.ajouter_event(QPair<PokemonSauvage*,Entier>(new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)),Entier(proba_)));
				ind_+=2;
			}
		}
	}
	while(!_lignes[ind_].contains("<Peche>")){
		ind_++;
	}
	while(!_lignes[ind_+1].contains("</Peche>")){
		ind_++;
		QString canne_=_lignes[ind_].split("\"")[1];
		QList<PokemonSauvage*> apparition_peche_;
		MonteCarlo<PokemonSauvage*> apparition_peche_alea_;
		ind_++;
		while(!_lignes[ind_].contains("</ApparPer>")){
			while(!_lignes[ind_].contains("<Pok>")){
				ind_++;
			}
			int ind_deb_=ind_+1;
			while(!_lignes[ind_].contains("</Pok>")){
				ind_++;
			}
			apparition_peche_<<new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_));
			ind_++;
		}
		apparition_per_pok_peche.ajouter_cle_valeur(canne_,apparition_peche_);
		if(!apparition_peche_.isEmpty()){//nb_pas_moyen_pour_appar
			while(!_lignes[ind_].contains("<ApparAlea canne")){
				ind_++;
			}
			int proba_=apparition_peche_.size();
			ind_++;
			while(!_lignes[ind_].contains("</ApparAlea>")){
				int ind_deb_=ind_+1;
				while(!_lignes[ind_].contains("</Pok>")){
					ind_++;
				}
				proba_=_lignes[ind_+1].split(">")[1].split("<")[0].toInt();
				apparition_peche_alea_.ajouter_event(QPair<PokemonSauvage*,Entier>(new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)),Entier(proba_)));
				ind_+=2;
			}
			apparition_alea_pok_peche.ajouter_cle_valeur(canne_,apparition_peche_alea_);
			MonteCarlo<PokemonSauvage*> apparition_peche_alea_2_;
			apparition_peche_.clear();
			while(!_lignes[ind_].contains("<ApparPerSansLeg canne")){
				ind_++;
			}
			canne_=_lignes[ind_].split("\"")[1];
			ind_++;
			while(!_lignes[ind_].contains("</ApparPerSansLeg>")){
				while(!_lignes[ind_].contains("<Pok>")){
					ind_++;
				}
				int ind_deb_=ind_+1;
				while(!_lignes[ind_].contains("</Pok>")){
					ind_++;
				}
				apparition_peche_<<new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_));
				ind_++;
			}
			apparition_per_pok_peche_sans_leg.ajouter_cle_valeur(canne_,apparition_peche_);
			if(!apparition_peche_.isEmpty()){//nb_pas_moyen_pour_appar
				while(!_lignes[ind_].contains("<ApparAlea canne")){
					ind_++;
				}
				int proba_=apparition_peche_.size();
				ind_++;
				while(!_lignes[ind_].contains("</ApparAlea>")){
					int ind_deb_=ind_+1;
					while(!_lignes[ind_].contains("</Pok>")){
						ind_++;
					}
					proba_=_lignes[ind_+1].split(">")[1].split("<")[0].toInt();
					apparition_peche_alea_2_.ajouter_event(QPair<PokemonSauvage*,Entier>(new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)),Entier(proba_)));
					ind_+=2;
				}
			}
			apparition_alea_pok_peche_sans_leg.ajouter_cle_valeur(canne_,apparition_peche_alea_2_);
		}
		apparition_peche_.clear();
		if(_lignes[ind_+1].contains("</Peche>")){
			ind_+=2;
			break;
		}
	}
	if(apparition_per_pok_peche.total()==0){
		ind_+=2;
	}
	//CANNE
	/*QString canne_;
	QList<PokemonSauvage*> apparition_peche_;
	MonteCarlo<PokemonSauvage*> apparition_peche_alea_;
	while(!_lignes[ind_].contains("<ApparPer canne")){
		ind_++;
	}
	canne_=_lignes[ind_].split("\"")[1];
	ind_++;
	while(!_lignes[ind_].contains("</ApparPer>")){
		while(!_lignes[ind_].contains("<Pok>")){
			ind_++;
		}
		int ind_deb_=ind_+1;
		while(!_lignes[ind_].contains("</Pok>")){
			ind_++;
		}
		apparition_peche_<<new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_));
		ind_++;
	}
	apparition_per_pok_peche.ajouter_cle_valeur(canne_,apparition_peche_);
	if(!apparition_peche_.isEmpty()){//nb_pas_moyen_pour_appar
		while(!_lignes[ind_].contains("<ApparAlea canne")){
			ind_++;
		}
		int proba_=apparition_peche_.size();
		ind_++;
		while(!_lignes[ind_].contains("</ApparAlea>")){
			int ind_deb_=ind_+1;
			while(!_lignes[ind_].contains("</Pok>")){
				ind_++;
			}
			proba_=_lignes[ind_+1].split(">")[1].split("<")[0].toInt();
			apparition_peche_alea_.ajouter_event(QPair<PokemonSauvage*,Entier>(new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)),Entier(proba_)));
			ind_+=2;
		}
		apparition_alea_pok_peche.ajouter_cle_valeur(canne_,apparition_peche_alea_);
		MonteCarlo<PokemonSauvage*> apparition_peche_alea_2_;
		apparition_peche_.clear();
		while(!_lignes[ind_].contains("<ApparPerSansLeg canne")){
			ind_++;
		}
		canne_=_lignes[ind_].split("\"")[1];
		ind_++;
		while(!_lignes[ind_].contains("</ApparPerSansLeg>")){
			while(!_lignes[ind_].contains("<Pok>")){
				ind_++;
			}
			int ind_deb_=ind_+1;
			while(!_lignes[ind_].contains("</Pok>")){
				ind_++;
			}
			apparition_peche_<<new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_));
			ind_++;
		}
		apparition_per_pok_peche_sans_leg.ajouter_cle_valeur(canne_,apparition_peche_);
		if(!apparition_peche_.isEmpty()){//nb_pas_moyen_pour_appar
			while(!_lignes[ind_].contains("<ApparAlea canne")){
				ind_++;
			}
			int proba_=apparition_peche_.size();
			ind_++;
			while(!_lignes[ind_].contains("</ApparAlea>")){
				int ind_deb_=ind_+1;
				while(!_lignes[ind_].contains("</Pok>")){
					ind_++;
				}
				proba_=_lignes[ind_+1].split(">")[1].split("<")[0].toInt();
				apparition_peche_alea_2_.ajouter_event(QPair<PokemonSauvage*,Entier>(new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)),Entier(proba_)));
				ind_+=2;
			}
		}
		apparition_alea_pok_peche_sans_leg.ajouter_cle_valeur(canne_,apparition_peche_alea_2_);
	}
	apparition_peche_.clear();
	//SUPER_CANNE
	MonteCarlo<PokemonSauvage*> apparition_peche_alea_3_;
	while(!_lignes[ind_].contains("<ApparPer canne")){
		ind_++;
	}
	canne_=_lignes[ind_].split("\"")[1];
	ind_++;
	while(!_lignes[ind_].contains("</ApparPer>")){
		while(!_lignes[ind_].contains("<Pok>")){
			ind_++;
		}
		int ind_deb_=ind_+1;
		while(!_lignes[ind_].contains("</Pok>")){
			ind_++;
		}
		apparition_peche_<<new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_));
		ind_++;
	}
	apparition_per_pok_peche.ajouter_cle_valeur(canne_,apparition_peche_);
	if(!apparition_peche_.isEmpty()){//nb_pas_moyen_pour_appar
		while(!_lignes[ind_].contains("<ApparAlea canne")){
			ind_++;
		}
		int proba_=apparition_peche_.size();
		ind_++;
		while(!_lignes[ind_].contains("</ApparAlea>")){
			int ind_deb_=ind_+1;
			while(!_lignes[ind_].contains("</Pok>")){
				ind_++;
			}
			proba_=_lignes[ind_+1].split(">")[1].split("<")[0].toInt();
			apparition_peche_alea_3_.ajouter_event(QPair<PokemonSauvage*,Entier>(new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)),Entier(proba_)));
			ind_+=2;
		}
		apparition_alea_pok_peche.ajouter_cle_valeur(canne_,apparition_peche_alea_3_);
		MonteCarlo<PokemonSauvage*> apparition_peche_alea_4_;
		apparition_peche_.clear();
		while(!_lignes[ind_].contains("<ApparPerSansLeg canne")){
			ind_++;
		}
		canne_=_lignes[ind_].split("\"")[1];
		ind_++;
		while(!_lignes[ind_].contains("</ApparPerSansLeg>")){
			while(!_lignes[ind_].contains("<Pok>")){
				ind_++;
			}
			int ind_deb_=ind_+1;
			while(!_lignes[ind_].contains("</Pok>")){
				ind_++;
			}
			apparition_peche_<<new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_));
			ind_++;
		}
		apparition_per_pok_peche_sans_leg.ajouter_cle_valeur(canne_,apparition_peche_);
		if(!apparition_peche_.isEmpty()){//nb_pas_moyen_pour_appar
			while(!_lignes[ind_].contains("<ApparAlea canne")){
				ind_++;
			}
			int proba_=apparition_peche_.size();
			ind_++;
			while(!_lignes[ind_].contains("</ApparAlea>")){
				int ind_deb_=ind_+1;
				while(!_lignes[ind_].contains("</Pok>")){
					ind_++;
				}
				proba_=_lignes[ind_+1].split(">")[1].split("<")[0].toInt();
				apparition_peche_alea_4_.ajouter_event(QPair<PokemonSauvage*,Entier>(new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)),Entier(proba_)));
				ind_+=2;
			}
		}
		apparition_alea_pok_peche_sans_leg.ajouter_cle_valeur(canne_,apparition_peche_alea_4_);
		apparition_peche_.clear();
	}
	//MEGA_CANNE
	MonteCarlo<PokemonSauvage*> apparition_peche_alea_5_;
	while(!_lignes[ind_].contains("<ApparPer canne")){
		ind_++;
	}
	canne_=_lignes[ind_].split("\"")[1];
	ind_++;
	while(!_lignes[ind_].contains("</ApparPer>")){
		while(!_lignes[ind_].contains("<Pok>")){
			ind_++;
		}
		int ind_deb_=ind_+1;
		while(!_lignes[ind_].contains("</Pok>")){
			ind_++;
		}
		apparition_peche_<<new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_));
		ind_++;
	}
	apparition_per_pok_peche.ajouter_cle_valeur(canne_,apparition_peche_);
	if(!apparition_peche_.isEmpty()){//nb_pas_moyen_pour_appar
		while(!_lignes[ind_].contains("<ApparAlea canne")){
			ind_++;
		}
		int proba_=apparition_peche_.size();
		ind_++;
		while(!_lignes[ind_].contains("</ApparAlea>")){
			int ind_deb_=ind_+1;
			while(!_lignes[ind_].contains("</Pok>")){
				ind_++;
			}
			proba_=_lignes[ind_+1].split(">")[1].split("<")[0].toInt();
			apparition_peche_alea_5_.ajouter_event(QPair<PokemonSauvage*,Entier>(new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)),Entier(proba_)));
			ind_+=2;
		}
		apparition_alea_pok_peche.ajouter_cle_valeur(canne_,apparition_peche_alea_5_);
		MonteCarlo<PokemonSauvage*> apparition_peche_alea_6_;
		apparition_peche_.clear();
		while(!_lignes[ind_].contains("<ApparPerSansLeg canne")){
			ind_++;
		}
		canne_=_lignes[ind_].split("\"")[1];
		ind_++;
		while(!_lignes[ind_].contains("</ApparPerSansLeg>")){
			while(!_lignes[ind_].contains("<Pok>")){
				ind_++;
			}
			int ind_deb_=ind_+1;
			while(!_lignes[ind_].contains("</Pok>")){
				ind_++;
			}
			apparition_peche_<<new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_));
			ind_++;
		}
		apparition_per_pok_peche_sans_leg.ajouter_cle_valeur(canne_,apparition_peche_);
		if(!apparition_peche_.isEmpty()){//nb_pas_moyen_pour_appar
			while(!_lignes[ind_].contains("<ApparAlea canne")){
				ind_++;
			}
			int proba_=apparition_peche_.size();
			ind_++;
			while(!_lignes[ind_].contains("</ApparAlea>")){
				int ind_deb_=ind_+1;
				while(!_lignes[ind_].contains("</Pok>")){
					ind_++;
				}
				proba_=_lignes[ind_+1].split(">")[1].split("<")[0].toInt();
				apparition_peche_alea_6_.ajouter_event(QPair<PokemonSauvage*,Entier>(new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)),Entier(proba_)));
				ind_+=2;
			}
		}
		apparition_alea_pok_peche_sans_leg.ajouter_cle_valeur(canne_,apparition_peche_alea_6_);
	}
	ind_+=2;*/
	while(_lignes[ind_].contains("<Pok coords")){
		QStringList coords_=_lignes[ind_].split("\"")[1].split(",");
		QPair<int,int> x_y_;
		x_y_.first=coords_[0].toInt();
		x_y_.second=coords_[1].toInt();
		int ind_deb_=ind_+1;
		while(!_lignes[ind_].contains("</Pok>")){
			ind_++;
		}
		pokemon_legendaires.ajouter_cle_valeur(x_y_,new PokemonSauvage(_lignes.mid(ind_deb_,ind_-ind_deb_)));
		ind_++;
	}
	//int nb_vois_=_lignes.size()
	QPair<int,int> dims_=dimensions();
	int per_=2*(dims_.first+dims_.second);
	//dimensions()
	//while(ind_<nb_vois_){//environnements_voisins.size()<2*(dims_.first+dims_.second)
	while(environnements_voisins.size()<per_){
		if(_lignes[ind_].contains("<V/>")){
			environnements_voisins<<QPair<QPair<int,int>,QPair<int,int> >(QPair<int,int>(-1,-1),QPair<int,int>(-1,-1));
		}else{
			QStringList coords_=_lignes[ind_].split(">")[1].split("<")[0].split(";");
			QStringList coords_1_=coords_[0].split(",");
			QStringList coords_2_=coords_[1].split(",");
			QPair<QPair<int,int>,QPair<int,int> > vois_;
			vois_.first.first=coords_1_[0].toInt();
			vois_.first.second=coords_1_[1].toInt();
			vois_.second.first=coords_2_[0].toInt();
			vois_.second.second=coords_2_[1].toInt();
			environnements_voisins<<vois_;
		}
		ind_++;
	}
	//<ApparPerSansLeg>
	//DonCs
}

QPair<int,int> Environnement::dimensions()const{
	return QPair<int,int>(largeur,tuiles.size()/largeur);
}

bool Environnement::existe(const QPair<int,int>& _id)const{
	QPair<int,int> dims_=dimensions();
	if(_id.first<0||_id.first>=dims_.first){
		return false;
	}
	if(_id.second<0||_id.second>=dims_.second){
		return false;
	}
	return true;
}

QPair<QPair<int,int>,QPair<int,int> > Environnement::voisin(const QPair<int,int>& _coords_tuile,const QPair<int,int>& _direction)const{
	int cte_=(_direction.second-_direction.first-1)/2;
	int ax_=_direction.second;
	int ay_=-_direction.first;
	int h_=_direction.second*(_direction.second+1)/2-2*cte_;
	int l_=_direction.second*(_direction.second-1)/2-cte_;
	QPair<int,int> dims_=dimensions();
	int indice_=l_*dims_.first+h_*dims_.second+_coords_tuile.first*ax_+_coords_tuile.second*ay_+cte_;
	return environnements_voisins[indice_];
}

Personnage *Environnement::perso(const QPair<int,int>& _coords)const{
	if(personnages.cles().contains(_coords)){
		return personnages.valeur(_coords);
	}
	return NULL;
}

bool Environnement::accessible_par_pied()const{
	bool acces_=type_environnement=="NEIGE"||type_environnement=="BATIMENT"||type_environnement=="DESERT";
	return acces_||type_environnement=="ROCHE"||type_environnement=="ROUTE"||type_environnement=="HERBE";
}

bool Environnement::accessible_par_surf()const{
	return accessible_par_pied()||type_environnement=="EAU";
}

bool Environnement::est_vide(const QPair<int,int>& _id)const{
	if(!existe(_id)){
		return false;
	}
	Tuile *t_=tuiles[_id.first+largeur*_id.second];
	if(t_->val_nom_image_obst().first!=""){
		return false;
	}
	if(personnages.cles().contains(_id)){
		return false;
	}
	if(objets.cles().contains(_id)){
		return false;
	}
	if(pokemon_legendaires.cles().contains(_id)){
		return false;
	}
	if(centres_poke.contains(_id)){
		return false;
	}
	if(echanges_poke_boites.contains(_id)){
		return false;
	}
	if(pensions.contains(_id)){
		return false;
	}
	if(move_tutors.contains(_id)){
		return false;
	}
	if(lieu_faire_revivre_fossile.contains(_id)){
		return false;
	}
	if(objets_donnes_ramasses.cles().contains(_id)){
		return false;
	}
	if(lieux_dons_pokemon.cles().contains(_id)){
		return false;
	}
	if(achats_objets.cles().contains(_id)){
		return false;
	}
	if(achats_ct.cles().contains(_id)){
		return false;
	}
	if(dons_cs.cles().contains(_id)){
		return false;
	}
	return true;
}

QString Environnement::type()const{
	return type_environnement;
}

QPair<int,int> Environnement::muret_o()const{
	return muret;
}


bool Environnement::contient_centre_poke(const QPair<int,int>& _id)const{
	return centres_poke.contains(_id);
}

bool Environnement::contient_echange_poke_boites(const QPair<int,int>& _id)const{
	return echanges_poke_boites.contains(_id);
}

bool Environnement::contient_pension(const QPair<int,int>& _id)const{
	return pensions.contains(_id);
}

bool Environnement::contient_move_tutor(const QPair<int,int>& _id)const{
	return move_tutors.contains(_id);
}

bool Environnement::contient_lieu_fossile(const QPair<int,int>& _id)const{
	return lieu_faire_revivre_fossile.contains(_id);
}

PokemonSauvage *Environnement::don_pokemon(const QPair<int,int>& _id)const{
	return lieux_dons_pokemon.valeur(_id);
}

QList<QPair<int,int> > Environnement::coords_lieux_dons_pokemon()const{
	return lieux_dons_pokemon.cles();
}

QString Environnement::objet_donne_ramasse(const QPair<int,int>& _id)const{
	return objets_donnes_ramasses.valeur(_id);
}

QList<QPair<int,int> > Environnement::coords_objets_donnes_ramasses()const{
	return objets_donnes_ramasses.cles();
}

QStringList Environnement::achat_objets(const QPair<int,int>& _id)const{
	return achats_objets.valeur(_id);
}

QList<QPair<int,int> > Environnement::coords_achat_objets()const{
	return achats_objets.cles();
}

QList<QPair<int,int> > Environnement::coords_achat_ct()const{
	return achats_ct.cles();
}

QList<uchar> Environnement::achat_ct(const QPair<int,int>& _id)const{
	return achats_ct.valeur(_id);
}

QList<QPair<int,int> > Environnement::coords_don_cs()const{
	return dons_cs.cles();
}

QList<uchar> Environnement::don_cs(const QPair<int,int>& _id)const{
	return dons_cs.valeur(_id);
}

bool Environnement::peut_etre_une_zone_de_peche()const{
	return type_environnement==_eau_||type_environnement==_cascade_;
}

QList<QPair<int,int> > Environnement::coords_autres_persos()const{
	return personnages.cles();
}

QString Environnement::objet(const QPair<int,int>& _id)const{
	return objets.valeur(_id);
}

QList<QPair<int,int> > Environnement::coords_objets()const{
	return objets.cles();
}

PokemonSauvage *Environnement::pokemon_legendaire(const QPair<int,int>& _id)const{
	return pokemon_legendaires.valeur(_id);
}

QList<QPair<int,int> > Environnement::coords_pokemon_legendaire()const{
	return pokemon_legendaires.cles();
}

Tuile* Environnement::tuile(const QPair<int,int>& _coords_tuile)const{
	return tuiles[_coords_tuile.first+largeur*_coords_tuile.second];
}

uchar Environnement::nb_pas_pour_appar()const{
	return nb_pas_moyen_pour_appar;
}

QList<PokemonSauvage*> Environnement::apparition_p_pok()const{
	return apparition_per_pok;
}

MonteCarlo<PokemonSauvage*> Environnement::apparition_a_pok()const{
	return apparition_alea_pok;
}

QList<PokemonSauvage*> Environnement::apparition_p_sans_leg_pok()const{
	return apparition_per_pok_sans_leg;
}

MonteCarlo<PokemonSauvage*> Environnement::apparition_a_sans_leg_pok()const{
	return apparition_alea_pok;
}

QList<PokemonSauvage*> Environnement::apparition_p_pok(const QString& _canne)const{
	return apparition_per_pok_peche.valeur(_canne);
}

MonteCarlo<PokemonSauvage*> Environnement::apparition_a_pok(const QString& _canne)const{
	return apparition_alea_pok_peche.valeur(_canne);
}

QList<PokemonSauvage*> Environnement::apparition_p_sans_leg_pok(const QString& _canne)const{
	return apparition_per_pok_peche_sans_leg.valeur(_canne);
}

MonteCarlo<PokemonSauvage*> Environnement::apparition_a_sans_leg_pok(const QString& _canne)const{
	return apparition_alea_pok_peche_sans_leg.valeur(_canne);
}


Environnement::~Environnement(){
	foreach(Tuile *t,tuiles){
		delete t;
		t=NULL;
	}
	typedef QPair<int,int> Origine;
	foreach(Origine o,personnages.cles()){
		Personnage *perso_=personnages.valeur(o);
		delete perso_;
		perso_=NULL;
	}
	foreach(Origine o,lieux_dons_pokemon.cles()){
		PokemonSauvage *pk_=lieux_dons_pokemon.valeur(o);
		delete pk_;
		pk_=NULL;
	}
	foreach(Origine o,pokemon_legendaires.cles()){
		PokemonSauvage *pk_=pokemon_legendaires.valeur(o);
		delete pk_;
		pk_=NULL;
	}
	foreach(PokemonSauvage *p,apparition_per_pok){
		delete p;
		p=NULL;
	}
	foreach(PokemonSauvage *p,apparition_per_pok_sans_leg){
		delete p;
		p=NULL;
	}
	foreach(QString c,apparition_per_pok_peche.cles()){
		foreach(PokemonSauvage *p,apparition_per_pok_peche.valeur(c)){
			delete p;;
			p=NULL;;
		}
	}
	foreach(QString c,apparition_per_pok_peche_sans_leg.cles()){
		foreach(PokemonSauvage *p,apparition_per_pok_peche_sans_leg.valeur(c)){
			delete p;;
			p=NULL;;
		}
	}
	apparition_alea_pok.liberer_memoire();;
	apparition_alea_pok_sans_leg.liberer_memoire();;
	foreach(QString c,apparition_alea_pok_peche.cles()){
		apparition_alea_pok_peche.valeur(c).liberer_memoire();;
	}
	foreach(QString c,apparition_alea_pok_peche_sans_leg.cles()){
		apparition_alea_pok_peche_sans_leg.valeur(c).liberer_memoire();;
	}

}


