#include "base_donnees/objets/repousse.h"
#include "autre/utilitaire.h"
#include "base_donnees/donnees.h"
#include <QRegExp>
const QStringList Repousse::_descriptions_repousses_=Repousse::init_descriptions_repousses();

QStringList Repousse::init_descriptions_repousses(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_repousses");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_repousses.txt");
#endif
	return contenu_.split("\n",QString::SkipEmptyParts);
}

Repousse::Repousse(uint _nb_pas,int _prix_vente):Objet(){
	maj_prix_achat(_prix_vente);
	nb_pas=_nb_pas;
}

uint Repousse::pas()const{
	return nb_pas;
}

QString Repousse::description(int _langue,Donnees*)const{
	QString retour_;
	QStringList args_;
	args_<<QString::number(nb_pas);
	QString descriptions_repousses_;
	foreach(QString l,_descriptions_repousses_){
		QStringList infos_=l.split("\t");
		descriptions_repousses_+=infos_[_langue]+"\n";
	}
	descriptions_repousses_.chop(1);
	retour_+=Utilitaire::formatter(descriptions_repousses_,args_)+"\n";
	retour_+="prix: "+QString::number(prix());
	return retour_;
}



