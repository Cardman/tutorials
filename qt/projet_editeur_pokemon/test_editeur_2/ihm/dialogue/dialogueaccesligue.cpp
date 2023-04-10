#include "ihm/dialogue/dialogueaccesligue.h"
#include "ihm/fenetre.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QTableWidget>
#include <QSplitter>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QComboBox>

const HashMap<QString,QStringList> DialogueAccesLigue::_elements_ihm_=DialogueAccesLigue::init_elements_ihm();

HashMap<QString,QStringList> DialogueAccesLigue::init_elements_ihm(){
	HashMap<QString,QStringList> elements_ihm_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/ihm_texte/"+QString(__FILE__).split(QRegExp("\\\\|/")).last().split(".")[0]).split("\n");
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/ihm_texte/"+QString(__FILE__).split("/").last().split(".")[0]+".txt").split("\n");
#endif
	foreach(QString l,lignes_){
		QStringList infos_l_=l.split("\t");
		elements_ihm_.ajouter_cle_valeur(infos_l_[0],QStringList(infos_l_.mid(1)));
	}
	return elements_ihm_;
}

QString DialogueAccesLigue::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

DialogueAccesLigue::DialogueAccesLigue(int _langue,QWidget* _parent):QDialog(_parent){
	langue=_langue;
	donnees=qobject_cast<Fenetre*>(_parent)->adr_donnees();
	setWindowTitle(traduire("TITRE"));
	QSplitter *split_c_=new QSplitter();
	QSplitter *split_=new QSplitter(Qt::Vertical);
	ind_ligue=0;
	HashMap<Coordonnees,Champion> texte_aff_=donnees->val_champions_battre();
	QList<Coordonnees> cles_ch_=texte_aff_.cles();
	int nb_pl_=texte_aff_.total();
	QStringList etiquettes_;
	etiquettes_<<traduire("ETIQUETTE_COORDONNEES");
	etiquettes_<<traduire("ETIQUETTE_NOM");
	etiquettes_<<traduire("ETIQUETTE_BADGE");
	etiquettes_<<traduire("ETIQUETTE_CT");
	etiquettes_<<traduire("ETIQUETTE_ATTAQUE_CT");
	etiquettes_<<traduire("ETIQUETTE_CS");
	etiquettes_<<traduire("ETIQUETTE_ATTAQUE_CS");
	etiquettes_<<traduire("ETIQUETTE_NIV_MIN_PRE_EQ");
	etiquettes_<<traduire("ETIQUETTE_NIV_MAX_PRE_EQ");
	etiquettes_<<traduire("ETIQUETTE_RECOMP_BASE");
	etiquettes_<<traduire("ETIQUETTE_RECOMP_TOTALE");
	etiquettes_<<traduire("ETIQUETTE_MULT_CBT");
	table_champions=new QTableWidget(nb_pl_,etiquettes_.size());
	table_champions->setHorizontalHeaderLabels(etiquettes_);
	for(int i=0;i<nb_pl_;i++){
		Coordonnees coords_=cles_ch_[i];
		Champion ch_=texte_aff_.valeur(coords_);
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText(coords_.formater());
		table_champions->setItem(i,0,element_);
		element_=new QTableWidgetItem();
		element_->setIcon(QPixmap::fromImage(Import::_dresseurs_micros_.valeur(*ch_.adr_nom_miniature())));
		element_->setText(ch_.adr_nom()->split("\t")[langue]);
		table_champions->setItem(i,1,element_);
		element_=new QTableWidgetItem();
		element_->setText(ch_.adr_badge()->split("\t")[langue]);
		table_champions->setItem(i,2,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*ch_.adr_ct()));
		table_champions->setItem(i,3,element_);
		element_=new QTableWidgetItem();
		if(*ch_.adr_ct()!=(uchar)Import::constante_numerique("CT_INVALIDE")){
			element_->setText(Import::_ct_.valeur(*ch_.adr_ct()));
		}else{
			element_->setText("");
		}
		table_champions->setItem(i,4,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*ch_.adr_cs()));
		table_champions->setItem(i,5,element_);
		element_=new QTableWidgetItem();
		if(*ch_.adr_cs()!=(uchar)Import::constante_numerique("CS_INVALIDE")){
			element_->setText(Import::_cs_.valeur(*ch_.adr_cs()));
		}else{
			element_->setText("");
		}
		table_champions->setItem(i,6,element_);
		QList<QPair<QList<PokemonDresse>,int> > equipes_=*ch_.adr_equipes();
		QList<PokemonDresse> equipe_=equipes_[0].first;
		int min_=*equipe_[0].adr_niveau();
		int max_=*equipe_[0].adr_niveau();
		int somme_=0;
		foreach(PokemonDresse p,equipe_){
			if(*p.adr_niveau()<min_){
				min_=*p.adr_niveau();
			}
			if(*p.adr_niveau()>max_){
				max_=*p.adr_niveau();
			}
			somme_+=*p.adr_niveau();
		}
		element_=new QTableWidgetItem();
		element_->setText(QString::number(min_));
		table_champions->setItem(i,7,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(max_));
		table_champions->setItem(i,8,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(equipes_[0].second));
		table_champions->setItem(i,9,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(equipes_[0].second*somme_));
		table_champions->setItem(i,10,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*ch_.adr_multiplicite_combat()));
		table_champions->setItem(i,11,element_);
		//adr_equipes()
	}
	//
	split_->addWidget(table_champions);
	QPushButton *ajout_champion_=new QPushButton(traduire("AJOUTER_COND_CH"));
	connect(ajout_champion_,SIGNAL(clicked()),this,SLOT(ajouter_condition_champion()));
	split_->addWidget(ajout_champion_);
	QPushButton *supprimer_champion_=new QPushButton(traduire("SUPPR_COND_CH"));
	connect(supprimer_champion_,SIGNAL(clicked()),this,SLOT(supprimer_condition_champion()));
	split_->addWidget(supprimer_champion_);
	table_champions_ajoutes=new QTableWidget(nb_pl_,etiquettes_.size());
	table_champions_ajoutes->setHorizontalHeaderLabels(etiquettes_);
	int nb_et_=etiquettes_.size();
	for(int i=0;i<nb_pl_;i++){
		for(int j=0;j<nb_et_;j++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText("");
			table_champions_ajoutes->setItem(i,j,element_);
		}
	}
	split_->addWidget(table_champions_ajoutes);
	split_c_->addWidget(split_);
	//Droite
	split_=new QSplitter(Qt::Vertical);
	cles_ligues=donnees->ligues_c();
	nb_pl_=cles_ligues.size();
	table_ligues=new QTableWidget(nb_pl_,1);
	for(int i=0;i<nb_pl_;i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText(QString::number(i));
		table_ligues->setItem(i,0,element_);
	}
	connect(table_ligues,SIGNAL(cellClicked(int,int)),this,SLOT(maj_table(int)));
	split_->addWidget(table_ligues);
	QPushButton *maj_condition_=new QPushButton(traduire("AJOUTER_COND_ACCES_LIGUE"));
	connect(maj_condition_,SIGNAL(clicked()),this,SLOT(ajouter_condition_acces_ligue()));
	split_->addWidget(maj_condition_);
	QPushButton *suppr_condition_=new QPushButton(traduire("SUPPR_COND_ACCES_LIGUE"));
	connect(suppr_condition_,SIGNAL(clicked()),this,SLOT(supprimer_condition_acces_ligue()));
	split_->addWidget(suppr_condition_);
	split_c_->addWidget(split_);
	QVBoxLayout *centre_=new QVBoxLayout();
	centre_->addWidget(split_c_);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	centre_->addWidget(valider_);
	setLayout(centre_);
}

void DialogueAccesLigue::conditions_acces_fct_champions(const HashMap<int,QList<Coordonnees> >& _acces_fct_champions){
	acces_fct_champions=_acces_fct_champions;
}

HashMap<int,QList<Coordonnees> > DialogueAccesLigue::conditions_acces_fct_champions()const{
	return acces_fct_champions;
}

void DialogueAccesLigue::maj_champions(){
	int nb_lignes_=table_champions_ajoutes->rowCount();
	int nb_colonnes_=table_champions_ajoutes->columnCount();
	int nb_champions_=champions_select.size();
	HashMap<Coordonnees,Champion> texte_aff_=donnees->val_champions_battre();
	QList<Coordonnees> cles_ch_=texte_aff_.cles();
	for(int i=0;i<nb_champions_;i++){
		Coordonnees coords_=cles_ch_[i];
		Champion ch_=texte_aff_.valeur(coords_);
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText(coords_.formater());
		table_champions_ajoutes->setItem(i,0,element_);
		element_=new QTableWidgetItem();
		element_->setIcon(QPixmap::fromImage(Import::_dresseurs_micros_.valeur(*ch_.adr_nom_miniature())));
		element_->setText(ch_.adr_nom()->split("\t")[langue]);
		table_champions_ajoutes->setItem(i,1,element_);
		element_=new QTableWidgetItem();
		element_->setText(ch_.adr_badge()->split("\t")[langue]);
		table_champions_ajoutes->setItem(i,2,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*ch_.adr_ct()));
		table_champions_ajoutes->setItem(i,3,element_);
		element_=new QTableWidgetItem();
		if(*ch_.adr_ct()!=(uchar)Import::constante_numerique("CT_INVALIDE")){
			element_->setText(Import::_ct_.valeur(*ch_.adr_ct()));
		}else{
			element_->setText("");
		}
		table_champions_ajoutes->setItem(i,4,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*ch_.adr_cs()));
		table_champions_ajoutes->setItem(i,5,element_);
		element_=new QTableWidgetItem();
		if(*ch_.adr_cs()!=(uchar)Import::constante_numerique("CS_INVALIDE")){
			element_->setText(Import::_cs_.valeur(*ch_.adr_cs()));
		}else{
			element_->setText("");
		}
		table_champions_ajoutes->setItem(i,6,element_);
		QList<QPair<QList<PokemonDresse>,int> > equipes_=*ch_.adr_equipes();
		QList<PokemonDresse> equipe_=equipes_[0].first;
		int min_=*equipe_[0].adr_niveau();
		int max_=*equipe_[0].adr_niveau();
		int somme_=0;
		foreach(PokemonDresse p,equipe_){
			if(*p.adr_niveau()<min_){
				min_=*p.adr_niveau();
			}
			if(*p.adr_niveau()>max_){
				max_=*p.adr_niveau();
			}
			somme_+=*p.adr_niveau();
		}
		element_=new QTableWidgetItem();
		element_->setText(QString::number(min_));
		table_champions_ajoutes->setItem(i,7,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(max_));
		table_champions_ajoutes->setItem(i,8,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(equipes_[0].second));
		table_champions_ajoutes->setItem(i,9,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(equipes_[0].second*somme_));
		table_champions_ajoutes->setItem(i,10,element_);
		element_=new QTableWidgetItem();
		element_->setText(QString::number(*ch_.adr_multiplicite_combat()));
		table_champions_ajoutes->setItem(i,11,element_);
		/*for(int j=0;j<nb_colonnes_;j++){
			table_champions_ajoutes->item(i,j)->setText(table_champions->item(i,j)->text())
			table_champions_ajoutes->item(i,j)->setIcon(table_champions->item(i,j)->icon())
		}*/
	}
	for(int i=nb_champions_;i<nb_lignes_;i++){
		for(int j=0;j<nb_colonnes_;j++){
			table_champions_ajoutes->item(i,j)->setText("");
			table_champions_ajoutes->item(i,j)->setIcon(QIcon());
		}
	}
	//int nb_ligues_=table_ligues
}

void DialogueAccesLigue::maj_table(int _lieu){
	ind_ligue=cles_ligues[_lieu];
	if(acces_fct_champions.cles().contains(ind_ligue)){
		champions_select=acces_fct_champions.valeur(ind_ligue);
		maj_champions();
	}
}


void DialogueAccesLigue::ajouter_condition_champion(){
	if(table_champions->currentRow()<0||table_champions->currentRow()>=table_champions->rowCount()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("CHAMPION_NON_SELECT"));
		return;
	}
	HashMap<Coordonnees,Champion> texte_aff_=donnees->val_champions_battre();
	QList<Coordonnees> cles_ch_=texte_aff_.cles();
	if(champions_select.contains(cles_ch_[table_champions->currentRow()])){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("CONDITION_DEJA_PRESENTE"));
		return;
	}
	champions_select<<cles_ch_[table_champions->currentRow()];
	maj_champions();
	QMessageBox::information(this,traduire("SUCCES"),traduire("CONDITION_CH_AJ"));
	//if(cles_ligues.cont
}

void DialogueAccesLigue::supprimer_condition_champion(){
	if(table_champions_ajoutes->currentRow()<0||table_champions_ajoutes->currentRow()>=champions_select.size()){
		QMessageBox::critical(this,traduire("ERREUR"),traduire("CHAMPION_NON_SELECT"));
		return;
	}
	champions_select.removeAt(table_champions_ajoutes->currentRow());
	maj_champions();
	QMessageBox::information(this,traduire("SUCCES"),traduire("CONDITION_CH_SUPPR"));
}

void DialogueAccesLigue::ajouter_condition_acces_ligue(){
	//acces_fct_ligues.ajouter_cle_valeur(coords,table_ligues->currentRow())
	acces_fct_champions.ajouter_cle_valeur(ind_ligue,champions_select);
	QMessageBox::information(this,traduire("SUCCES"),traduire("CONDITION_ACCES_LIGUE_AJ"));
}

void DialogueAccesLigue::supprimer_condition_acces_ligue(){
	if(acces_fct_champions.cles().contains(ind_ligue)){
		acces_fct_champions.supprimer_cle_valeur(ind_ligue);
		//ligues_select.clear()
		QMessageBox::information(this,traduire("SUCCES"),traduire("CONDITION_ACCES_LIGUE_SUPPR"));
	}else{
		QMessageBox::critical(this,traduire("ERREUR"),traduire("COORDS_NON_SELECT"));
	}
}



