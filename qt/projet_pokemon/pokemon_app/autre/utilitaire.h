#ifndef UTILITAIRE_H
#define UTILITAIRE_H
#include <QPair>
#include <QList>
class QString;
class QStringList;

/**Permet de ne pas avoir de collision dans les noms de méthodes avec les méthodes ou attributs d'une classe*/
namespace Utilitaire{

	/**@param nom nom du fichier à lire
	@return une longue chaîne sur le fichier*/
	QString lire_fichier(const QString&);

	/**@param nom nom du fichier à écrire
	@param contenu contenu à écrire*/
	void ecrire_fichier(const QString&,const QString&);

	/**@param chaine
	@param arguments
	@return une chaîne formattée*/
	QString formatter(const QString&,const QStringList&);

	/**T doit implémenter l'opérateur <
	@param elt1
	@param elt2
	@return dans cette ordre le maximum puis le minimum*/
	template<typename T>
	QPair<T,T> max_min(const T&,const T&);

	/**T doit implémenter l'opérateur <
	@param liste
	@param croissant
	trie une liste*/
	template<typename T>
	void trier(QList<T>&,bool croissant=true);

	template<typename T>
	bool contient(const QList<T>&,const QList<T>&);

	template<typename T>
	QList<T> intersection(const QList<T>&,const QList<T>&);

	/***/
	template<typename T>
	QPair<T,T> max_min(const QList<T>&,const T& def=T());

	/**@param dico_const
	@param const_chercher
	@return la constante voulue*/
	QString constante(const QStringList&,const QString&);

	/**@param dico_trad un ensemble de chaines de caractères
	@param chaine_orig chaine de la langue par défaut à traduire
	@param langue_dest langue de destination
	@return la chaine traduite*/
	QString traduire(const QStringList&,const QString&,int);

	/**@param dico_trad un ensemble de chaines de caractères
	@param chaine_orig chaine de la langue par défaut à traduire
	@param langue_dest langue de destination
	@return la chaine traduite*/
	QString traduire_bis(const QStringList&,const QString&,int);

	/**@param dico_trad un ensemble de chaines de caractères
	@param chaine_orig chaine de la langue par défaut à traduire
	@param langue_dest langue de destination
	@return la chaine traduite*/
	QString rever_traduire(const QStringList&,const QString&,int);

	/**@param dico_trad un ensemble de chaines de caractères
	@param chaine_orig chaine de la langue par défaut à traduire
	@param langue_dest langue de destination
	@return la chaine traduite*/
	QString rever_traduire_bis(const QStringList&,const QString&,int);

	/**@param dico_trad un ensemble de chaines de caractères
	@param chaine_orig chaine de la langue par défaut à traduire
	@return vrai si et seulement si la chaine chaine_orig est traduisible dans une langue*/
	bool traduisible(const QStringList&,const QString&);

	/**@param dico_trad un ensemble de chaines de caractères
	@param chaine_orig chaine de la langue par défaut à traduire
	@param langue_orig langue d'origine pour savoir si le mot existe dans cette langue
	@return vrai si et seulement si la chaine chaine_orig est traduisible dans une langue*/
	bool rever_traduisible(const QStringList&,const QString&,int);
}

namespace Utilitaire{
	/**@param elt1
	@param elt2
	@return dans cette ordre le maximum puis le minimum*/
	template<typename T>
	QPair<T,T> max_min(const T& elt1,const T& elt2){
		if(elt1<elt2){
			return QPair<T,T>(elt2,elt1);
		}
		return QPair<T,T>(elt1,elt2);
	}

	template<typename T>
	void trier(QList<T>& liste,bool croissant){
		int nb_=liste.size();
		for(int i=0;i<nb_;i++){
			for(int j=i+1;j<nb_;j++){
				if((liste[i]<liste[j])!=croissant){
					liste.swap(i,j);
				}
			}
		}
	}

	template<typename T>
	QPair<T,T> max_min(const QList<T>& liste,const T& def){
		QPair<T,T> max_min_=QPair<T,T>(def,def);
		foreach(T e,liste){
			if(e<max_min_.second){
				max_min_.second=e;
			}
			if(!(e<max_min_.first)){
				max_min_.first=e;
			}
		}
		return max_min_;
	}

	template<typename T>
	bool contient(const QList<T>& liste_1,const QList<T>& liste_2){
		foreach(T t,liste_2){
			if(!liste_1.contains(t)){
				return false;
			}
		}
		return true;
	}

	template<typename T>
	QList<T> intersection(const QList<T>& liste_1,const QList<T>& liste_2){
		QList<T> inter_;
		foreach(T t,liste_1){
			if(liste_2.contains(t)){
				inter_<<t;
			}
		}
		return inter_;
	}
}
#endif



