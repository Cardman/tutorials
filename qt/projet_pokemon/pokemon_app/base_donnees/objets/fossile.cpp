#include "base_donnees/objets/fossile.h"
#include "base_donnees/donnees.h"
#include "autre/utilitaire.h"
#include <QRegExp>
const QStringList Fossile::_descriptions_fossiles_=Fossile::init_descriptions_fossiles();

QStringList Fossile::init_descriptions_fossiles(){
#ifdef QT_NO_DEBUG
	QString contenu_=Utilitaire::lire_fichier(":/fichiers_ressources/description_fossile");
#else
	QString contenu_=Utilitaire::lire_fichier("fichiers_ressources/description_fossile.txt");
#endif
	return contenu_.split("\n",QString::SkipEmptyParts);
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

QString Fossile::description(int _langue,Donnees* _d)const{
	QString retour_;
	QStringList args_;
	args_<<Utilitaire::traduire(_d->val_noms_pk(),nom_pokemon,_langue);
	args_<<QString::number(niveau);
	QString descriptions_fossiles_;
	foreach(QString l,_descriptions_fossiles_){
		QStringList infos_=l.split("\t");
		descriptions_fossiles_+=infos_[_langue]+"\n";
	}
	descriptions_fossiles_.chop(1);
	retour_+=Utilitaire::formatter(descriptions_fossiles_,args_)+"\n";
	retour_+="prix: "+QString::number(prix());
#ifdef QT_NO_DEBUG
	return retour_;
#else
	QString jedi=retour_;
	return jedi;
#endif
}



