#include "ihm/dialogue/dialogueselectlieu.h"
#include "ihm/fenetre.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QTableWidget>
#include <QSplitter>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStringList>

const HashMap<QString,QStringList> DialogueSelectLieu::_elements_ihm_=DialogueSelectLieu::init_elements_ihm();

HashMap<QString,QStringList> DialogueSelectLieu::init_elements_ihm(){
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

QString DialogueSelectLieu::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString DialogueSelectLieu::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueSelectLieu::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueSelectLieu::DialogueSelectLieu(int _langue,bool _a_suppr,QWidget* _parent):QDialog(_parent){
	langue=_langue;
	if(_a_suppr){
		setWindowTitle(traduire("TITRE_S"));
	}else{
		setWindowTitle(traduire("TITRE"));
	}
	cles_lieux=qobject_cast<Fenetre*>(_parent)->donnees_actuelles().lieux_c();
	HashMap<int,QPair<QString,QString> > texte_aff_=qobject_cast<Fenetre*>(_parent)->donnees_actuelles().nom_type_lieux();
	int nb_pl_=cles_lieux.size();
	QVBoxLayout *centre_=new QVBoxLayout();
	QStringList etiquettes_;
	etiquettes_<<traduire("ETIQUETTE_NOM");
	etiquettes_<<traduire("ETIQUETTE_TYPE");
	table=new QTableWidget(nb_pl_,etiquettes_.size());
	table->setHorizontalHeaderLabels(etiquettes_);
	for(int i=0;i<nb_pl_;i++){
		QTableWidgetItem *element_=new QTableWidgetItem();
		element_->setText(texte_aff_.valeur(i).first.split("\t")[langue]);
		table->setItem(i,0,element_);
		element_=new QTableWidgetItem();
		element_->setText(traduire(Import::_type_lieux_,texte_aff_.valeur(i).second,langue));
		table->setItem(i,1,element_);
	}
	centre_->addWidget(table);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	centre_->addWidget(valider_);
	setLayout(centre_);
}

int DialogueSelectLieu::lieu_select()const{
	if(table->currentRow()<0||table->currentRow()>=cles_lieux.size()){
		return -1;
	}
	return cles_lieux[table->currentRow()];
}


