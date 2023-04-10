#include "base_donnees/personnages/dresseur.h"
#include <QStringList>

Dresseur::Dresseur(const QStringList& _lignes):Personnage(sous_attributs(_lignes,"<O>")){
	nom_image=_lignes[3].split(">")[1].split("<")[0];
	message_fin_combat=_lignes[4].split(">")[1].split("<")[0].replace("\\n","\n");
	message_debut_combat=_lignes[5].split(">")[1].split("<")[0].replace("\\n","\n");
	multiplicite_combat=(uchar)_lignes[6].split(">")[1].split("<")[0].toUInt();
}

uchar Dresseur::mult_comb()const{
	return multiplicite_combat;
}


