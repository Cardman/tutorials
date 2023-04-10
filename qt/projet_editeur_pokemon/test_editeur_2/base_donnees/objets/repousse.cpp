#include "base_donnees/objets/repousse.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QRegExp>
const QStringList Repousse::_descriptions_repousses_=Repousse::init_descriptions_repousses();

QStringList Repousse::init_descriptions_repousses(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_repousses");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_repousses.txt");
#endif
	QStringList lignes_=contenu_.split("\n",QString::SkipEmptyParts);
	QStringList descriptions_objets_;
	int nb_langues_=1;//Import::_langues_.total();
	for(int i=0;i<nb_langues_;i++){
		descriptions_objets_<<"";
	}
	foreach(QString l,lignes_){
		QStringList infos_=l.split("\t");
		for(int i=0;i<nb_langues_;i++){
			descriptions_objets_[i]+=infos_[i]+"\n";
		}
	}
	for(int i=0;i<nb_langues_;i++){
		descriptions_objets_[i].chop(1);
	}
	return descriptions_objets_;
}

Repousse::Repousse(uint _nb_pas,int _prix_vente):Objet(){
	maj_prix_achat(_prix_vente);
	nb_pas=_nb_pas;
}

QString Repousse::description(int _langue)const{
	QString retour_;
	QStringList args_;
	args_<<QString::number(nb_pas);
	retour_+=Utilitaire::formatter(_descriptions_repousses_[_langue],args_)+"\n";
	retour_+="prix: "+QString::number(prix());
	return retour_;
}



