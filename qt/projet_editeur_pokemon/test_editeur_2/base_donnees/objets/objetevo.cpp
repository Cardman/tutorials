#include "base_donnees/objets/objetevo.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QRegExp>
const QStringList ObjetEvo::_descriptions_objets_evo_=ObjetEvo::init_descriptions_objets_evo();

QStringList ObjetEvo::init_descriptions_objets_evo(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_objet_evo_attacher");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_objet_evo_attacher.txt");
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

ObjetEvo::ObjetEvo(const QStringList& _pokemon_compatibles,int _prix_achat):Objet(){
	setAttachable();
	maj_prix_achat(_prix_achat);
	pokemon_compatibles=_pokemon_compatibles;
}

QStringList ObjetEvo::pks()const{
	return pokemon_compatibles;
}

QString ObjetEvo::description(int _langue)const{
	QString retour_;
	//QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(Ressources::_indice_francais_)+"}"
	foreach(QString p,pokemon_compatibles){
		QStringList args_;
		/*QStringList corresp_=Ressources::_noms_pk_.filter(QRegExp("^"+ch_exp_reg_+p+"\\t"))
		args_<<corresp_[0].split("\t")[_langue]*/
		args_<<Utilitaire::traduire(Import::_noms_pk_,p,_langue);
		retour_+=Utilitaire::formatter(_descriptions_objets_evo_[_langue],args_)+"\n";
	}
	retour_+="prix: "+QString::number(prix());
	return retour_;
}



