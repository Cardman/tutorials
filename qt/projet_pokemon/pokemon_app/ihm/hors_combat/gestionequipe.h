#ifndef GESTIONEQUIPE_H
#define GESTIONEQUIPE_H

#include <QSplitter>
#include "serialisable/base_donnees/hashmap.h"
#include "serialisable/pokemon/oeufpokemon.h"
#include "serialisable/pokemon/pokemonutilisateur.h"

class Utilisateur;
class Donnees;
class QVBoxLayout;
class QScrollArea;
class EtiquetteOeuf;
class EtiquettePkUt;
class FichePkUtEquipe;
class FicheOeuf;
class GestionEquipe : public QSplitter{

	int langue;

	bool echange_pos;

	bool echange_obj;

	uchar gestion_en_cours;

	int pokemon_vu;

	QPair<int,int> pokemons_echanges;

	QVBoxLayout *lay_identite;

	HashMap<uchar,uchar> pos_indice;

	HashMap<uchar,EtiquetteOeuf*> etiquettes_oeuf;

	HashMap<uchar,EtiquettePkUt*> etiquettes_pk_ut;

	/**Ensemble des pokemon dans les oeufs presents dans l'equipe. (maximum 6)*/
	QList<QPair<uchar,OeufPokemon> > oeufs_equipe;

	/**equipe de l'utilisateur autre que les oeufs (maximum 6)*/
	QList<QPair<uchar,PokemonUtilisateur> > equipe;

	QScrollArea *asc_fiche_pk_ut;

	FichePkUtEquipe *fiche_pk_ut;

	QScrollArea *asc_fiche_oeuf;

	FicheOeuf *fiche_oeuf;

	QVBoxLayout *lay_actions;

	QScrollArea *asc_mt;

	QString attaque_apprise;

	QVBoxLayout *lay_mt;

	Donnees *donnees;

	Q_OBJECT
public:

	enum TypeGestion{ORDRE,BAIE,SOIN,APPRENDRE_CT,APPRENDRE_CS,ATTACHER_OBJET,PIERRE_EVO,BOOST,PENSION,MOVE_TUTORS,RIEN};
	GestionEquipe();

	uchar gestion()const;

	void maj_fiche(const Utilisateur&,int,uchar,Donnees*,const QString& ="");

	void maj_type(uchar);

	int pokemon_fiche();

	bool echange_en_cours();

	void gestion_finie();

signals:

	void vol();

	void fin_gestion();

	void echange_place(const QPair<int,int>&);

	void echange_objets(const QPair<int,int>&);

	void rangement_objet(uchar);

	void pension(const QPair<int,int>&);

	void appris_move_tutors(const QString&,uchar,int);

	void move_tutors(const QString&,uchar,int);

	void evoluer(const QString&,uchar);

	void attacher(uchar);

	void boost(uchar);

	void soin(uchar);

	void soin_baie(uchar);

private slots:

	void annuler();

	void finir_gestion();

	void echange_position();

	//void echanger_pokemons();

	void echange_objets();

	void rangement_objet();

	void voir_fiche_pk_ut(uchar);

	void voir_fiche_oeuf(uchar);

	void apprendre_move_tutors(const QString&,int);

	void move_tutors(const QString&);

	void voler();
};

#endif // GESTIONEQUIPE_H
