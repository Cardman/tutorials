#ifndef HASHMAP_H
#define HASHMAP_H
#include "flux/flux.h"
#include <QList>
#include <QPair>

/**Classe se comportant comme une HashMap ordinaire avec pour pseudo indice une cle et pour chaque cle, une valeur est associée.
L'utilisation de cette classe nécessité l'implémentation de l'opérateur == pour le type Cle.
Pour récupérer l'ensemble des clés ayant une même valeur, il faut en plus l'implémentation de l'opérateur == pour le type Valeur*/
template<typename Cle,typename Valeur>
class HashMap{

	/**Ensemble des duos cle-valeur*/
	QList<QPair<Cle,Valeur> > cles_valeurs;
public:

	/**Constructeur de base permettant d'initialiser une hashmap.*/
	HashMap();

	/**Test d'existence d'une clé par une boucle sur la liste des couples clés valeur en comparant la clé dans la liste avec la clé passée en paramètre.

l'indice de la clé est retourné dans le cas d'existence de celle-ci.

-1 est retournée sinon.
@param _cle Clé à chercher dans la hashmap
@return l'indice de la clé est retourné dans le cas d'existence de celle-ci.
-1, sinon.*/
	int contient(const Cle&)const;

	/**supprime le couple clé valeur de la hashmap si la clé existe.
@param _cle clé à connaître pour supprimer la valeur.*/
	void supprimer_cle_valeur(const Cle&);

	/**
	@param _a_cle
	@param _n_cle
	*/
	void changer_cle(const Cle&,const Cle&);

	void modifier_cle_valeur(const Cle&,const Valeur&);

	void ajouter_fin_cle_valeur(const Cle&,const Valeur&);

	/**Retourne la valeur associée à la clé si elle existe, une nouvelle valeur sinon
@param _cle Clé dont on veut récupérer la valeur.
@return La valeur associée à la clé. (C'est la valeur qui est associée à la clé)*/
	Valeur valeur(const Cle&)const;

	/**Retourne la valeur associée à la clé si elle existe, une nouvelle valeur sinon
@param _cle Clé dont on veut récupérer la valeur.
@return La valeur associée à la clé. (C'est la valeur qui est associée à la clé)*/
	Valeur& valeur(const Cle&);

	/**Retourne l'adresse de la valeur associée à la clé si elle existe, une nouvelle allocation mémoire sinon
	A libérer ave précaution, à la seule condition que _n_instance passe à vrai.
@param _cle Clé dont on veut récupérer la valeur.
@param _n_instance une référence indiquant une allocation mémoire ou non, elle est modifiable
@return L'adresse de la valeur associée à la clé. (C'est la valeur qui est associée à la clé)*/
	Valeur* valeur(const Cle&,bool&);

	/**Cherche toutes les clés de la HashMap.
@return L'ensemble des clés de la HashMap.*/
	QList<Cle> cles()const;

	/**Cherche les clés de la HashMap telles que ces clés aient pour valeur _valeur. L'utilisation de cette méthode contrairement aux autres nécessite une implémentation de l'opérateur == pour le type Valeur.
@param _valeur La valeur dont on veut récupérer les clés qui la possèdent.
@return L'ensemble des clés (éventuellement vide si la valeur n'existe pas) de la HashMap asociées à _valeur.*/
	QList<Cle> cles(const Valeur&)const;

	/**Si la cle est contenue dans la hash map, alors cette methode ajoute le duo cle-valeur a la fin de l'ensemble cles_valeurs.
Sinon elle met a jour la valeur se situant a l'indexe de la cle associee
@param cle
@param valeur*/
	void ajouter_cle_valeur(const Cle&,const Valeur&);

	/**Retourne le couple clé adresse de la valeur à l'indice passé en paramètre.

Attention, il ne faut pas que l'indice soit supérieur ou égal au nombre de clés dans la hashmap. L'indice ne doit pas être strictement négatif.
@param _indice indice de la clé dans la hashmap
@return le couple clé adresse de la valeur à l'indice passé en paramètre*/
	//QPair<Cle,Valeur*> cle_valeur(int);

	/**Retourne le nombre total de duo Cle-Valeur*/
	int total()const;

	void tout_supprimer();

	/**
@return la liste des adresses des couples clés - valeur associée à la clé.*/
	//QList<QPair<Cle,Valeur>* > cles_adr_valeurs();

	/**Si cette cle est contenue dans l'ensemble cles_valeurs, cette methode recupere la valeur associe a la cle.
Sinon, cette methode leve une exception indiquant quelle cle n'existe pas.
@param cle*/
	//Valeur operator()(const Cle&)const;

	/**@param _autre l'autre hashmap à comparer avec celle-ci
	@return vrai si et seulement les deux hashmap sont égales c'est-à-dire si les couples de clés-valeurs sont égaux*/
	bool operator==(const HashMap<Cle,Valeur>&)const;

	/**Méthode de sérialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Méthode de désérialisation
	@param _in le flux d'entrée*/
	virtual void deserialiser(Flux&);
};

//TODO indiquer les types pouvant être sérialisés. ajouter des typedef
/*typedef HashMap<int,Coordonnees> LieuxVol;
typedef HashMap<QPair<int,int>,Champion> Champions;
typedef HashMap<QPair<int,int>,Dresseur1> Dresseurs;
typedef HashMap<QPair<int,int>,Environnement> Environnements;
typedef HashMap<QPair<int,int>,EnvironnementLigue> EnvironnementsLigue;
typedef HashMap<QPair<int,int>,Personnage> Personnages;
typedef HashMap<QPair<int,int>,Pokemon> Pokemons;
typedef HashMap<QString,QList<Pokemon> > Peches;
typedef HashMap<QPair<int,int>,QStringList> Achats;
typedef HashMap<QPair<int,int>,QString> Objets;
typedef HashMap<QPair<int,QPair<QPair<int,int>,QPair<int,int> > >,QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > > LiensLieux;
typedef HashMap<QPair<QPair<int,int>,QPair<int,int> >,QPair<QPair<QPair<int,int>,QPair<int,int> >,QPair<int,int> > > LiensPlateaux;
*/
template<typename Cle,typename Valeur>
Flux & operator <<(Flux&,const HashMap<Cle,Valeur>&);

template<typename Cle,typename Valeur>
Flux & operator >>(Flux&,HashMap<Cle,Valeur>&);

template<typename Cle,typename Valeur>
HashMap<Cle,Valeur>::HashMap(){
	;
}

template<typename Cle,typename Valeur>
int HashMap<Cle,Valeur>::contient(const Cle& _cle)const{
	int indice_=-1;
	int nb_elts_=cles_valeurs.size();
	for(int i=0;i<nb_elts_;i++){
		if(cles_valeurs[i].first==_cle){
			indice_=i;
			break;
		}
	}
	return indice_;
}

template<typename Cle,typename Valeur>
void HashMap<Cle,Valeur>::supprimer_cle_valeur(const Cle& _cle){
	int contient_=contient(_cle);
	if(contient_>-1){
		cles_valeurs.removeAt(contient_);
	}
}

template<typename Cle,typename Valeur>
Valeur HashMap<Cle,Valeur>::valeur(const Cle& _cle)const{
	int contient_=contient(_cle);
	/*if(contient_<0){
		return Valeur()
	}*/
	return cles_valeurs[contient_].second;
}

template<typename Cle,typename Valeur>
Valeur& HashMap<Cle,Valeur>::valeur(const Cle& _cle){
	return cles_valeurs[contient(_cle)].second;
}

template<typename Cle,typename Valeur>
Valeur* HashMap<Cle,Valeur>::valeur(const Cle& _cle,bool& _n_instance){
	int contient_=contient(_cle);
	/*if(contient_<0){
		_n_instance=true
		return new Valeur
	}*/
	_n_instance=false;
	return &(cles_valeurs[contient_].second);
}

template<typename Cle,typename Valeur>
QList<Cle> HashMap<Cle,Valeur>::cles()const{
	QList<Cle> cles_;
	int nb_elts_=cles_valeurs.size();
	for(int i=0;i<nb_elts_;i++){
		cles_<<cles_valeurs[i].first;
	}
	return cles_;
}

template<typename Cle,typename Valeur>
QList<Cle> HashMap<Cle,Valeur>::cles(const Valeur& _valeur)const{
	QList<Cle> cles_;
	int nb_elts_=cles_valeurs.size();
	for(int i=0;i<nb_elts_;i++){
		if(cles_valeurs[i].second==_valeur){
			cles_<<cles_valeurs[i].first;
		}
	}
	return cles_;
}

template<typename Cle,typename Valeur>
void HashMap<Cle,Valeur>::ajouter_cle_valeur(const Cle& _cle,const Valeur& _valeur){
	int contient_=contient(_cle);
	if(contient_<0){
		cles_valeurs<<QPair<Cle,Valeur>(_cle,_valeur);
	}else{
		cles_valeurs[contient_].second=_valeur;
	}
}

	/*template<typename Cle,typename Valeur>
	QPair<Cle,Valeur*> HashMap<Cle,Valeur>::cle_valeur(int _indice){
	
	}*/

template<typename Cle,typename Valeur>
int HashMap<Cle,Valeur>::total()const{
	return cles_valeurs.size();
}

template<typename Cle,typename Valeur>
void HashMap<Cle,Valeur>::tout_supprimer(){
	cles_valeurs.clear();
}

template<typename Cle,typename Valeur>
void HashMap<Cle,Valeur>::changer_cle(const Cle& _a_cle,const Cle& _n_cle){
	int nb_=cles_valeurs.size();
	int indice_=-1;
	int indice_2_=-1;
	for(int i=0;i<nb_;i++){
		if(cles_valeurs[i].first==_a_cle){
			indice_=i;
		}
		if(cles_valeurs[i].first==_n_cle){
			indice_2_=i;
		}
	}
	if(indice_>-1&&indice_2_<0){
		cles_valeurs[indice_].first=_n_cle;
	}
}

template<typename Cle,typename Valeur>
void HashMap<Cle,Valeur>::modifier_cle_valeur(const Cle& _n_cle,const Valeur& _valeur){
	cles_valeurs[_n_cle].second=_valeur;
}

template<typename Cle,typename Valeur>
void HashMap<Cle,Valeur>::ajouter_fin_cle_valeur(const Cle& _n_cle,const Valeur& _valeur){
	cles_valeurs<<QPair<Cle,Valeur>(_n_cle,_valeur);
}


	/*template<typename Cle,typename Valeur>
	QList<QPair<Cle,Valeur>* > HashMap<Cle,Valeur>::cles_adr_valeurs(){
		QList<QPair<Cle,Valeur>* > adresses_couples_
		typedef QPair<Cle,Valeur> Couple_cle_valeur
		foreach(Couple_cle_valeur c,cles_valeurs){
			adresses_couples_<<&c
		}
		return adresses_couples_
	}*/

	/*template<typename Cle,typename Valeur>
	Valeur HashMap<Cle,Valeur>::operator()(const Cle& cle)const{
	
	}*/

template<typename Cle,typename Valeur>
bool HashMap<Cle,Valeur>::operator==(const HashMap<Cle,Valeur>& _autre)const{
	bool egal_=total()==_autre.total();
	if(!egal_){
		return false;
	}
	QList<Cle> cles_=cles();
	QList<Cle> cles_autre_=_autre.cles();
	foreach(Cle c,cles_){
		if(!cles_autre_.contains(c)){
			return false;
		}
	}
	QList<Valeur> valeurs_;
	QList<Valeur> valeurs_autre_;
	foreach(Cle c,cles_){
		valeurs_<<valeur(c);
	}
	foreach(Cle c,cles_autre_){
		valeurs_autre_<<_autre.valeur(c);
	}
	foreach(Valeur v,valeurs_){
		if(!valeurs_autre_.contains(v)){
			return false;
		}
	}
	return true;
}

template<typename Cle,typename Valeur>
void HashMap<Cle,Valeur>::serialiser(Flux& _out)const{
	_out<<cles_valeurs;
}

template<typename Cle,typename Valeur>
void HashMap<Cle,Valeur>::deserialiser(Flux& _in){
	_in>>cles_valeurs;
}

template<typename Cle,typename Valeur>
Flux & operator <<(Flux& out,const HashMap<Cle,Valeur>& _HashMap){
	_HashMap.serialiser(out);
	return out;
}

template<typename Cle,typename Valeur>
Flux & operator >>(Flux& in,HashMap<Cle,Valeur>& _HashMap){
	_HashMap.deserialiser(in);
	return in;
}

#endif



