#include "base_donnees/objets/fossile.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QRegExp>
const QStringList Fossile::_descriptions_fossiles_=Fossile::init_descriptions_fossiles();

QStringList Fossile::init_descriptions_fossiles(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_fossile");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_fossile.txt");
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

Fossile::Fossile(const QString& _nom_pokemon,uchar _niveau,int _prix_achat):Objet(){
	nom_pokemon=_nom_pokemon;
	niveau=_niveau;
	maj_prix_achat(_prix_achat);
}

QString Fossile::nom_pk()const{
	return nom_pokemon;
}

uchar Fossile::niv()const{
	return niveau;
}

QString Fossile::description(int _langue)const{
	QString retour_;
	//QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(Ressources::_indice_francais_)+"}"
	QStringList args_;
	/*QStringList corresp_=Ressources::_noms_pk_.filter(QRegExp("^"+ch_exp_reg_+nom_pokemon+"\\t"))
	args_<<corresp_[0].split("\t")[_langue]*/
	args_<<Utilitaire::traduire(Import::_noms_pk_,nom_pokemon,_langue);
	args_<<QString::number(niveau);
	retour_+=Utilitaire::formatter(_descriptions_fossiles_[_langue],args_)+"\n";
	retour_+="prix: "+QString::number(prix());
	return retour_;
}



