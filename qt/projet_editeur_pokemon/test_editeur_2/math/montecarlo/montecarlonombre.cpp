#include "math/montecarlo/montecarlonombre.h"
#include "math/taux.h"
#include <QPair>

MonteCarloNombre::MonteCarloNombre(){
	;
}

Taux MonteCarloNombre::esperance()const{
	Taux somme_num_=Taux(0);
	Taux somme_den_=Taux(0);
	HashMap<Taux,Entier> loi_=val_loi();
	QList<Taux> evenements_=loi_.cles();
	foreach(Taux c,evenements_){
		Entier effectif_=loi_.valeur(c);
		somme_num_=somme_num_+c*Taux(effectif_);
		somme_den_=somme_den_+Taux(effectif_);
	}
	return somme_num_/somme_den_;
}

Taux MonteCarloNombre::esperance_reelle()const{
	Taux somme_num_=Taux(0);
	Entier somme_den_=Entier(0);
	HashMap<Taux,Entier> loi_=val_loi();
	QList<Taux> evenements_=loi_.cles();
	foreach(Taux c,evenements_){
		somme_den_=somme_den_+loi_.valeur(c);
	}
	Entier plus_gd_nb_alea_=tirageNombreMax()+Entier(1);
	QPair<Entier,Entier> quotient_reste_=plus_gd_nb_alea_.division_euclidienne_generalise(somme_den_);
	Entier somme_den_2_=Entier(0);
	int max_indice_=-1;
	int nb_evenements_=evenements_.size();
	for(int i=0;i<nb_evenements_;i++){
		somme_den_2_=somme_den_2_+loi_.valeur(evenements_[i]);
		if(quotient_reste_.second<somme_den_2_){
			max_indice_=i;
			break;
		}
	}
	if(quotient_reste_.second>Entier(0)){
		HashMap<Taux,Entier> loi_2_=loi_;
		bool suppr_=false;
		for(int i=0;i<nb_evenements_;i++){
			Entier *effectif_=loi_2_.valeur(evenements_[i],suppr_);
			Entier tmp_=*effectif_;
			*effectif_=*effectif_*quotient_reste_.first;
			if(i<max_indice_){
				*effectif_=*effectif_+tmp_;
			}else if(i==max_indice_){
				somme_den_2_=Entier(0);
				for(int j=0;j<max_indice_;j++){
					somme_den_2_=somme_den_2_+loi_.valeur(evenements_[j]);
				}
				*effectif_=*effectif_+quotient_reste_.second-somme_den_2_;
			}
		}
		loi_=loi_2_;
	}
	foreach(Taux c,evenements_){
		Entier effectif_=loi_.valeur(c);
		somme_num_=somme_num_+c*Taux(effectif_);
	}
	if(quotient_reste_.second>Entier(0)){
		return somme_num_/Taux(plus_gd_nb_alea_);
	}
	return somme_num_/Taux(somme_den_);
}

Taux MonteCarloNombre::variance_reelle()const{
	Taux somme_num_car=Taux(0);
	Taux somme_num_=Taux(0);
	Entier somme_den_=Entier(0);
	HashMap<Taux,Entier> loi_=val_loi();
	QList<Taux> evenements_=loi_.cles();
	foreach(Taux c,evenements_){
		somme_den_=somme_den_+loi_.valeur(c);
	}
	Entier plus_gd_nb_alea_=tirageNombreMax()+Entier(1);
	QPair<Entier,Entier> quotient_reste_=plus_gd_nb_alea_.division_euclidienne_generalise(somme_den_);
	Entier somme_den_2_=Entier(0);
	int max_indice_=-1;
	int nb_evenements_=evenements_.size();
	for(int i=0;i<nb_evenements_;i++){
		somme_den_2_=somme_den_2_+loi_.valeur(evenements_[i]);
		if(quotient_reste_.second<somme_den_2_){
			max_indice_=i;
			break;
		}
	}
	if(quotient_reste_.second>Entier(0)){
		HashMap<Taux,Entier> loi_2_=loi_;
		bool suppr_=false;
		for(int i=0;i<nb_evenements_;i++){
			Entier *effectif_=loi_2_.valeur(evenements_[i],suppr_);
			Entier tmp_=*effectif_;
			*effectif_=*effectif_*quotient_reste_.first;
			if(i<max_indice_){
				*effectif_=*effectif_+tmp_;
			}else if(i==max_indice_){
				somme_den_2_=Entier(0);
				for(int j=0;j<max_indice_;j++){
					somme_den_2_=somme_den_2_+loi_.valeur(evenements_[j]);
				}
				*effectif_=*effectif_+quotient_reste_.second-somme_den_2_;
			}
		}
		loi_=loi_2_;
	}
	foreach(Taux c,evenements_){
		Entier effectif_=loi_.valeur(c);
		Taux effectif_taux_=Taux(effectif_);
		Taux prod_tmp=c*effectif_taux_;
		somme_num_=somme_num_+prod_tmp;
		somme_num_car=somme_num_car+c*prod_tmp;
	}
	Taux somme_den_taux_;
	if(quotient_reste_.second>Entier(0)){
		somme_den_taux_=Taux(plus_gd_nb_alea_);
	}else{
		somme_den_taux_=Taux(somme_den_);
	}
	Taux esp_=somme_num_/somme_den_taux_;
	return somme_num_car/somme_den_taux_-esp_*esp_;//E[X^2]-E[X]^2
}

Taux MonteCarloNombre::variance()const{
	Taux somme_num_car=Taux(0);
	Taux somme_num_=Taux(0);
	Taux somme_den_=Taux(0);
	HashMap<Taux,Entier> loi_=val_loi();
	QList<Taux> evenements_=loi_.cles();
	foreach(Taux c,evenements_){
		Entier effectif_=loi_.valeur(c);
		Taux effectif_taux_=Taux(effectif_);
		Taux prod_tmp=c*effectif_taux_;
		somme_num_=somme_num_+prod_tmp;
		somme_num_car=somme_num_car+c*prod_tmp;
		somme_den_=somme_den_+effectif_taux_;
	}
	Taux esp_=somme_num_/somme_den_;
	return somme_num_car/somme_den_-esp_*esp_;//E[X^2]-E[X]^2
}

QPair<Taux,Taux> MonteCarloNombre::esperance_variance()const{
	Taux somme_num_car=Taux(0);
	Taux somme_num_=Taux(0);
	Taux somme_den_=Taux(0);
	HashMap<Taux,Entier> loi_=val_loi();
	QList<Taux> evenements_=loi_.cles();
	foreach(Taux c,evenements_){
		Entier effectif_=loi_.valeur(c);
		Taux effectif_taux_=Taux(effectif_);
		Taux prod_tmp=c*effectif_taux_;
		somme_num_=somme_num_+prod_tmp;
		somme_num_car=somme_num_car+c*prod_tmp;
		somme_den_=somme_den_+effectif_taux_;
	}
	QPair<Taux,Taux> esp_var_;
	esp_var_.first=somme_num_/somme_den_;
	esp_var_.second=somme_num_car/somme_den_-esp_var_.first*esp_var_.first;
	return esp_var_;//E[X^2]-E[X]^2
}

QPair<Taux,Taux> MonteCarloNombre::esperance_variance_reelles()const{
	Entier somme_den_=Entier(0);
	HashMap<Taux,Entier> loi_=val_loi();
	QList<Taux> evenements_=loi_.cles();
	foreach(Taux c,evenements_){
		somme_den_=somme_den_+loi_.valeur(c);
	}
	Entier plus_gd_nb_alea_=tirageNombreMax()+Entier(1);
	QPair<Entier,Entier> quotient_reste_=plus_gd_nb_alea_.division_euclidienne_generalise(somme_den_);
	Entier somme_den_2_=Entier(0);
	int max_indice_=-1;
	int nb_evenements_=evenements_.size();
	for(int i=0;i<nb_evenements_;i++){
		somme_den_2_=somme_den_2_+loi_.valeur(evenements_[i]);
		if(quotient_reste_.second<somme_den_2_){
			max_indice_=i;
			break;
		}
	}
	if(quotient_reste_.second>Entier(0)){
		HashMap<Taux,Entier> loi_2_=loi_;
		bool suppr_=false;
		for(int i=0;i<nb_evenements_;i++){
			Entier *effectif_=loi_2_.valeur(evenements_[i],suppr_);
			Entier tmp_=*effectif_;
			*effectif_=*effectif_*quotient_reste_.first;
			if(i<max_indice_){
				*effectif_=*effectif_+tmp_;
			}else if(i==max_indice_){
				somme_den_2_=Entier(0);
				for(int j=0;j<max_indice_;j++){
					somme_den_2_=somme_den_2_+loi_.valeur(evenements_[j]);
				}
				*effectif_=*effectif_+quotient_reste_.second-somme_den_2_;
			}
		}
		loi_=loi_2_;
	}
	Taux somme_num_=Taux(0);
	Taux somme_num_car=Taux(0);
	foreach(Taux c,evenements_){
		Entier effectif_=loi_.valeur(c);
		Taux effectif_taux_=Taux(effectif_);
		Taux prod_tmp=c*effectif_taux_;
		somme_num_=somme_num_+prod_tmp;
		somme_num_car=somme_num_car+c*prod_tmp;
	}
	Taux somme_den_taux_;
	if(quotient_reste_.second>Entier(0)){
		somme_den_taux_=Taux(plus_gd_nb_alea_);
	}else{
		somme_den_taux_=Taux(somme_den_);
	}
	Taux esp_=somme_num_/somme_den_taux_;
	QPair<Taux,Taux> esp_var_;
	esp_var_.first=esp_;
	esp_var_.second=somme_num_car/somme_den_taux_-esp_*esp_;
	return esp_var_;
}

Taux MonteCarloNombre::minimum()const{
	Taux min_=Taux(0);
	HashMap<Taux,Entier> loi_=val_loi();
	QList<Taux> evenements_=loi_.cles();
	if(evenements_.isEmpty()){
		return min_;
	}
	//Il faut bien initialiser le minimum, car 0 n'est pas forcément inférieur ou égal au minimum
	min_=evenements_[0];
	foreach(Taux c,evenements_){
		if(c<min_){
			min_=c;
		}
	}
	return min_;
}

Taux MonteCarloNombre::maximum()const{
	Taux max_=Taux(0);
	HashMap<Taux,Entier> loi_=val_loi();
	QList<Taux> evenements_=loi_.cles();
	if(evenements_.isEmpty()){
		return max_;
	}
	//Il faut bien initialiser le maximum, car 0 n'est pas forcément supérieur ou égal au maximum
	max_=evenements_[0];
	foreach(Taux c,evenements_){
		if(max_<c){
			max_=c;
		}
	}
	return max_;
}

QPair<Taux,Taux> MonteCarloNombre::variance_esperance_indep(const Taux& _var_var_alea,const Taux& _esp_var_alea)const{
	QPair<Taux,Taux> var_esp_car_=QPair<Taux,Taux>(Taux(0),Taux(0));
	//esperance_variance()
	QPair<Taux,Taux> var_esp_=esperance_variance();
	Taux var_tmp_=var_esp_.second;
	Taux esp_tmp_=var_esp_.first;
	var_esp_car_.first=var_tmp_*_var_var_alea+var_tmp_*_esp_var_alea*_esp_var_alea+esp_tmp_*esp_tmp_*_var_var_alea;
	var_esp_car_.second=esp_tmp_*_esp_var_alea;
	return var_esp_car_;
}

QPair<Taux,Taux> MonteCarloNombre::variance_esperance_indep_reelles(const Taux& _var_var_alea,const Taux& _esp_var_alea)const{
	QPair<Taux,Taux> var_esp_car_=esperance_variance_reelles();
	Taux var_tmp_=var_esp_car_.second;
	Taux esp_tmp_=var_esp_car_.first;
	var_esp_car_.first=var_tmp_*_var_var_alea+var_tmp_*_esp_var_alea*_esp_var_alea+esp_tmp_*esp_tmp_*_var_var_alea;
	var_esp_car_.second=esp_tmp_*_esp_var_alea;
	return var_esp_car_;
}

QString MonteCarloNombre::chaine()const{
	QList<Taux> evs_=events();
	Entier som_=somme();
	QString retour_;
	foreach(Taux e,evs_){
		retour_+="("+e.chaine()+","+Taux(proba_event(e),som_).chaine()+");";
	}
	retour_.chop(1);
	return retour_;
}



