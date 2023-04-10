#ifndef GESTIONBOITE_H
#define GESTIONBOITE_H

#include <QSplitter>
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/pokemon/oeufpokemon.h"
#include "serialisable/pokemon/pokemonutilisateur.h"


class QVBoxLayout;
class ClavierNumerique;
class FichePkUtEquipe;
class FichePkUtBoite;
class FicheOeuf;
class Miniature;
class QGridLayout;
class Utilisateur;
class Donnees;
class QScrollArea;
class EtiquetteOeuf;
class EtiquettePkUt;
class QGroupBox;
class GestionBoite : public QSplitter{

	QVBoxLayout *equipe;

	QScrollArea *asc_fiche_pk_eq;

	FichePkUtEquipe *fiche_pk_eq;

	QScrollArea *asc_fiche_oeuf_eq;

	FicheOeuf *fiche_oeuf_eq;

	bool existe_select_1;

	QPair<uchar,uchar> position_1;

	uchar indice_boite_1;

	QGroupBox *nom_boite_1;

	QGridLayout *boite_1;

	QScrollArea *asc_fiche_pk_boite_1;

	FichePkUtBoite *fiche_pk_boite_1;

	QScrollArea *asc_fiche_oeuf_boite_1;

	FicheOeuf *fiche_oeuf_boite_1;

	ClavierNumerique *clavier_1;

	bool existe_select_2;

	QPair<uchar,uchar> position_2;

	uchar indice_boite_2;

	QGroupBox *nom_boite_2;

	QGridLayout *boite_2;

	QScrollArea *asc_fiche_pk_boite_2;

	FichePkUtBoite *fiche_pk_boite_2;

	QScrollArea *asc_fiche_oeuf_boite_2;

	FicheOeuf *fiche_oeuf_boite_2;

	ClavierNumerique *clavier_2;

	int pk_equipe;

	int langue;

	bool echange_pos;

	bool echange_obj;

	HashMap<uchar,uchar> pos_indice;

	HashMap<uchar,EtiquetteOeuf*> etiquettes_oeuf;

	HashMap<uchar,EtiquettePkUt*> etiquettes_pk_ut;

	HashMap<QPair<uchar,uchar>,Miniature*> etiquettes_b_1;

	HashMap<QPair<uchar,uchar>,Miniature*> etiquettes_b_2;

	/**Ensemble des pokemon dans les oeufs presents dans l'equipe. (maximum 6)*/
	QList<QPair<uchar,OeufPokemon> > oeufs_equipe;

	/**equipe de l'utilisateur autre que les oeufs (maximum 6)*/
	QList<QPair<uchar,PokemonUtilisateur> > equipe_ut;

	/**Ensemble des boites d'oeufs de pokemon (maximum 256 boites de 256 pokemon)*/
	QList<QList<QPair<uchar,OeufPokemon> > > boites_oeufs;

	/**Ensemble des boites contenant les pokemon (maximum 256 boites de 256 pokemon)*/
	QList<QList<QPair<uchar,PokemonUtilisateur> > > boites;

	bool gestion_en_cours;

	Donnees *donnees;

	Q_OBJECT

	void maj_boite_1(uchar);

	void maj_boite_2(uchar);

public:

	GestionBoite(Donnees*);

	void maj_fiche(const Utilisateur&,int,Donnees*);

	bool gestion()const;

signals:

	void gestion_finie();

	void echange_pokemon(const QPair<int,int>&,const QPair<int,int>&);

	void echange_objets(const QPair<int,int>&,const QPair<int,int>&);

	void ranger_objets(const QPair<int,int>&);

	void depos(uchar,const QPair<uchar,uchar>&);

	void retrait(const QPair<uchar,uchar>&);

	void relacher(const QPair<uchar,uchar>&);

private slots:

	void finir_gestion();

	void maj_indice_boite_1(const Entier&);

	void maj_indice_boite_2(const Entier&);

	void voir_fiche_pk_ut(uchar);

	void voir_fiche_oeuf(uchar);

	void voir_fiche_boite_1(const QPair<uchar,uchar>&,bool,bool);

	void voir_fiche_boite_2(const QPair<uchar,uchar>&,bool,bool);

	void echange_pokemon();

	void echange_objets();

	void ranger_objets();

	void depos();

	void retrait();

	void relacher();
};

#endif // GESTIONBOITE_H
