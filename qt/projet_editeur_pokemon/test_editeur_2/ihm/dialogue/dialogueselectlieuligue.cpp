#include "ihm/dialogue/dialogueselectlieuligue.h"
#include "ihm/fenetre.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QTableWidget>
#include <QSplitter>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <QCheckBox>

const HashMap<QString,QStringList> DialogueSelectLieuLigue::_elements_ihm_=DialogueSelectLieuLigue::init_elements_ihm();

HashMap<QString,QStringList> DialogueSelectLieuLigue::init_elements_ihm(){
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

QString DialogueSelectLieuLigue::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

QString DialogueSelectLieuLigue::traduire(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::traduire(_dico,_nom,_langue);
}

QString DialogueSelectLieuLigue::traduire_revert(const QStringList& _dico,const QString& _nom,int _langue){
	return Utilitaire::rever_traduire(_dico,_nom,_langue);
}

DialogueSelectLieuLigue::DialogueSelectLieuLigue(int _langue,QWidget* _parent):QDialog(_parent){
	langue=_langue;
	setWindowTitle(traduire("TITRE"));
	cles_lieux=qobject_cast<Fenetre*>(_parent)->donnees_actuelles().lieux_c();
	cles_ligues=qobject_cast<Fenetre*>(_parent)->donnees_actuelles().ligues_c();
	HashMap<int,QPair<QString,QString> > texte_aff_=qobject_cast<Fenetre*>(_parent)->donnees_actuelles().nom_type_lieux();
	int nb_pl_=cles_lieux.size();
	QVBoxLayout *centre_=new QVBoxLayout();
	if(nb_pl_>0){
		QStringList etiquettes_;
		etiquettes_<<traduire("ETIQUETTE_NOM");
		etiquettes_<<traduire("ETIQUETTE_TYPE");
		table_lieux=new QTableWidget(nb_pl_,etiquettes_.size());
		table_lieux->setHorizontalHeaderLabels(etiquettes_);
		for(int i=0;i<nb_pl_;i++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText(texte_aff_.valeur(i).first.split("\t")[langue]);
			table_lieux->setItem(i,0,element_);
			element_=new QTableWidgetItem();
			element_->setText(traduire(Import::_type_lieux_,texte_aff_.valeur(i).second,langue));
			table_lieux->setItem(i,1,element_);
		}
		centre_->addWidget(table_lieux);
	}else{
		table_lieux=NULL;
	}
	nb_pl_=cles_ligues.size();
	if(nb_pl_>0){
		table_ligues=new QTableWidget(nb_pl_,1);
		for(int i=0;i<nb_pl_;i++){
			QTableWidgetItem *element_=new QTableWidgetItem();
			element_->setText(QString::number(i));
			table_ligues->setItem(i,0,element_);
		}
		centre_->addWidget(table_ligues);
	}else{
		table_ligues=NULL;
	}
	if(cles_ligues.size()>0&&cles_lieux.size()>0){
		choix=new QCheckBox(traduire("LIGUE_SELECT"));;
		centre_->addWidget(choix);
	}else{
		choix=NULL;
	}
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(accept()));
	centre_->addWidget(valider_);
	setLayout(centre_);
}

QPair<int,bool> DialogueSelectLieuLigue::lieu_ligue_select()const{
	QPair<int,bool> retour_=QPair<int,bool>(-1,false);
	if(choix!=NULL){
		if(choix->isChecked()){
			if(table_ligues->currentRow()<0||table_ligues->currentRow()>=cles_ligues.size()){
				return retour_;
			}
			retour_.first=cles_ligues[table_ligues->currentRow()];
			retour_.second=true;
			return retour_;
		}
		if(table_lieux->currentRow()<0||table_lieux->currentRow()>=cles_lieux.size()){
			return retour_;
		}
		retour_.first=cles_lieux[table_lieux->currentRow()];
		retour_.second=false;
		return retour_;
	}
	if(!cles_lieux.isEmpty()){
		if(table_lieux->currentRow()<0||table_lieux->currentRow()>=cles_lieux.size()){
			return retour_;
		}
		retour_.first=cles_lieux[table_lieux->currentRow()];
		retour_.second=false;
		return retour_;
	}
	if(table_ligues->currentRow()<0||table_ligues->currentRow()>=cles_ligues.size()){
		return retour_;
	}
	retour_.first=cles_ligues[table_ligues->currentRow()];
	retour_.second=true;
	return retour_;
}


