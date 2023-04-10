#ifndef FOSSILE_H
#define FOSSILE_H
#include "base_donnees/objets/objet.h"
#include <QString>

/***/
class Fossile: public Objet{

	Q_OBJECT

	/**nom du pokemon a faire revivre par ce fossile.*/
	QString nom_pokemon;

	/**niveau du pokemon lorsqu'il revit venant de son fossile.*/
	uchar niveau;

	
	const static QStringList _descriptions_fossiles_;

	
	static QStringList init_descriptions_fossiles();

public:

	/**@param _nom_pokemon
	@param _niveau
	@param _prix_achat*/
	Fossile(const QString&,uchar,int);

	/**@return la valeur de nom_pokemon*/
	QString nom_pk()const;

	/**@return la valeur de niveau*/
	uchar niv()const;

	/**@param _langue langue du programme
	Donne la description d'un objet.*/
	virtual QString description(int)const;

	/**@param _effet l'effet dont on veut rcuprer les lments (_effet est une chane de dpart) on recherche en boucle
	si le retour est vide alors l'effet n'est pas prsent*/
	//virtual QList<QStringList> elements(const QString&)const;
};
#endif



