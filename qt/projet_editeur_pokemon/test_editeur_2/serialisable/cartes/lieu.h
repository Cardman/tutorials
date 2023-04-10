#ifndef LIEU_H
#define LIEU_H
#include "serialisable/cartes/plateau.h"
/***/
class Lieu{

	/***/
	QString nom;

	/***/
	QString type;

	/***/
	HashMap<int,Plateau> plateaux;

	/**Pour coller des lieux graphiquement*/
	HashMap<QPair<int,QPair<QPair<int,int>,QPair<int,int> > >,Coordonnees> liens_vers_autres_lieux;

	HashMap<QPair<int,QPair<QPair<int,int>,QPair<int,int> > >,Coordonnees> liens_vers_autres_lieux_tmp;

public:

	enum Orientation{GAUCHE,DROITE,HAUT,BAS};
	Lieu();

	bool egal(const Lieu&)const;

	bool est_valide()const;
	/**@return l'adresse de nom*/
	QString *adr_nom();

	/**@return l'adresse de type*/
	QString *adr_type();

	/**Mthode ajoutant un plateau
	@param _indice indice du nouveau plateau
	@param _plateau plateau  insrer*/
	void ajout_plateau(int,const Plateau&);

	/**Mthode supprimant un plateau
	@param _indice indice du plateau  supprimer*/
	void suppression_plateau(int);

	/***/
	QList<int> plateaux_c()const;

	/**Mthode rcuprant l'adresse d'un plateau
	@param _indice indice du plateau dont on veut rcuprer l'adresse*/
	Plateau *plateau(int);

	void aff_liens_vers_autres_lieux_tmp();

	void aff_liens_vers_autres_lieux();

	/**Mthode rcuprant l'adresse d'un lien vers un autre plateau
	@param _origine
	@param _n_inst un paramtre modifiable (de sortie seule) indiquant s'il faut librer la mmoire ou non
	@return l'adresse d'un lien vers un autre plateau*/
	Coordonnees *destination_autre_lieu(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _origine,bool& _n_inst);

	/**Mthode rcuprant un lien vers un autre plateau
	@param _origine
	@return l'adresse d'un lien vers un autre plateau*/
	Coordonnees destination_autre_lieu(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _origine);

	/**Mthode ajoutant un lien vers un autre plateau
	@param _origine
	@param _lien l'adresse d'un lien vers un autre plateau*/
	void ajouter_dest_autre_lieu(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _origine,const Coordonnees&);

	/***/
	void supprimer_dest_autre_lieu(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&);

	/***/
	QList<QPair<int,QPair<QPair<int,int>,QPair<int,int> > > > liaisons_vers_autres_lieux()const;

	/**Algo reliant deux plateaux du mme lieu  l'aide des coordonnes d'environnement et de tuiles
	@param _indice_l indice du lieu
	@param _indice indice du premier plateau  lier avec un autre plateau
	@param _indice_2 indice du deuxieme plateau  lier avec un autre plateau
	@param _coords coordonnes du premier plateau  lier avec un autre plateau
	@param _coords_2 coordonnes du deuxieme plateau  lier avec un autre plateau*/
	void relier_plateaux_m_lieu(int,int,int,const QPair<QPair<int,int>,QPair<int,int> >&,const QPair<QPair<int,int>,QPair<int,int> >&);

	/**Algo reliant deux plateaux du mme lieu  l'aide des coordonnes d'environnement et de tuiles
	@param _indice indice du premier plateau  lier avec un autre plateau
	@param _coords coordonnes du plateau  delier avec un autre plateau*/
	void delier_plateaux_m_lieu(int,const QPair<QPair<int,int>,QPair<int,int> >&);

	/**Algo reliant deux plateaux du mme lieu  l'aide des coordonnes d'environnement et de tuiles
	@param _indice_l indice du premier lieu contenant le premier plateau
	@param _indice_l_2 indice du deuxieme lieu contenant le deuxieme plateau
	@param _indice indice du premier plateau  lier avec un autre plateau
	@param _indice_2 indice du deuxieme plateau  lier avec un autre plateau
	@param _coords coordonnes du premier plateau  lier avec un autre plateau
	@param _coords_2 coordonnes du deuxieme plateau  lier avec un autre plateau*/
	void relier_plateaux_lieux_diff(int,int,int,int,const QPair<QPair<int,int>,QPair<int,int> >&,const QPair<QPair<int,int>,QPair<int,int> >&);

	/**Algo reliant deux plateaux du mme lieu  l'aide des coordonnes d'environnement et de tuiles
	@param _indice indice du premier plateau  lier avec un autre plateau
	@param _coords coordonnes du plateau  delier avec un autre plateau*/
	void delier_plateaux_lieux_diff(int,const QPair<QPair<int,int>,QPair<int,int> >&);

	/**
	@param _coords coordonnes du premier plateau  lier avec un autre plateau
	@param _autre_plateau plateau de l'autre lieu qui est li au plateau de ce lieu
	@param _coords_2 coordonnes du deuxieme plateau  lier avec un autre plateau
	*/
	QList<QPair<QPair<int,int>,QPair<int,int> > > futures_cles(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords,const Plateau& _autre_plateau,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >& _coords_2)const;

	/**Algo indiquant si deux lieux peuvent tre lis
	@param _coords coordonnes du premier plateau à lier avec un autre plateau
	@param _autre_plateau plateau de l'autre lieu qui est li au plateau de ce lieu
	@param _coords_2 coordonnes du deuxieme plateau à lier avec un autre plateau
	@param _futurs_cles les éventuelles futures clés paramètre modifiable
	@return vrai si et seulement si ce lieu peut tre li avec l'autre lieu*/
	bool peuvent_etre_lie_avec(const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&,const Plateau&,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&,QList<QPair<QPair<int,int>,QPair<int,int> > >&)const;

	/**Algo reliant deux plateaux du même lieu à l'aide des coordonnées d'environnement et de tuiles
	Les lieux doivent être collés
	Cette méthode est appelée après Lieu::peuvent_etre_lie_ avec
	@param _indice_l_2 indice du deuxieme lieu contenant le deuxieme plateau
	@param _coords coordonnes du premier plateau  lier avec un autre plateau
	@param _autre_plateau plateau de l'autre lieu qui est li au plateau de ce lieu
	@param _coords_2 coordonnes du deuxieme plateau  lier avec un autre plateau
	@param _futurs_cles les futures clés à donner pour la HashMap fournies par la méthode Lieu::peuvent_etre_lie_*/
	void relier_avec_autre_lieu(int,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&,const Plateau&,const QPair<int,QPair<QPair<int,int>,QPair<int,int> > >&,const QList<QPair<QPair<int,int>,QPair<int,int> > >&);

	/**Algo reliant deux plateaux du mme lieu  l'aide des coordonnes d'environnement et de tuiles
	@param _indice_l indice de l'autre lieu*/
	void delier_lieux(int);

	/**Exporte les informations sur le lieu
	@param _nb_tab_env le nombre de tabulations  utiliser pour l'indentation des lignes
	@return la liste des coordonnes des environnements voisins avec les coordonnes des tuiles adjacentes sous
	forme de chaine dans un XML.*/
	QString exporter(int)const;

	/**Mthode de srialisation
	@param _out le flux de sortie*/
	virtual void serialiser(Flux&)const;

	/**Mthode de dsrialisation
	@param _in le flux d'entre*/
	virtual void deserialiser(Flux&);
};

bool operator==(const Lieu&,const Lieu&);

Flux & operator <<(Flux&,const Lieu&);
Flux & operator >>(Flux&,Lieu&);

#endif



