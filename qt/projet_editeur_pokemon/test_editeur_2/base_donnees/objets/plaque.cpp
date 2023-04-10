#include "base_donnees/objets/plaque.h"
#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include <QRegExp>
const QStringList Plaque::_descriptions_plaques_=Plaque::init_descriptions_plaques();

QStringList Plaque::init_descriptions_plaques(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_plaques");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_plaques.txt");
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

Plaque::Plaque(const QString& _type_plaque,const QString& _type_pk,const Taux& _coeff,int _prix):Objet(){
	setAttachable();
	type_plaque=_type_plaque;
	type_pk=_type_pk;
	coeff=_coeff;
	maj_prix_achat(_prix);
}

QString Plaque::tp_pl()const{
	return type_plaque;
}

QString Plaque::tp_pk()const{
	return type_pk;
}

Taux Plaque::co()const{
	return coeff;
}

QString Plaque::description(int _langue)const{
	QString retour_;
	//QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(Ressources::_indice_francais_)+"}"
	QStringList args_;
	/*QStringList corresp_=Ressources::_noms_types_.filter(QRegExp("^"+ch_exp_reg_+type_plaque+"\\t"))
	args_<<corresp_[0].split("\t")[_langue]*/
	args_<<Utilitaire::traduire(Import::_noms_types_,type_plaque,_langue);
	args_<<coeff.chaine();
	/*corresp_=Ressources::_noms_types_.filter(QRegExp("^"+ch_exp_reg_+type_pk+"\\t"))
	args_<<corresp_[0].split("\t")[_langue]*/
	args_<<Utilitaire::traduire(Import::_noms_types_,type_pk,_langue);
	retour_+=Utilitaire::formatter(_descriptions_plaques_[_langue],args_)+"\n";
	return retour_;
}



