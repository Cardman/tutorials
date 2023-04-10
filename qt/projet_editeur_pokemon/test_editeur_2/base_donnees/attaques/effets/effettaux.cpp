#include "base_donnees/attaques/effets/effettaux.h"
#include <QStringList>
EffetTaux::EffetTaux(const QString& _ligne){
	taux=Taux::parse_taux(_ligne.split(",")[1].split("]")[0]);
}

Taux EffetTaux::tx()const{
	return taux;
}



