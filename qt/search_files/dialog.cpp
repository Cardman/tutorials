#include "dialog.h"
#include "ui_dialog.h"
#include "thread.h"
#include "threadmodif.h"
#include <QProgressDialog>
#include <QStringListModel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Dialog::Dialog(QWidget *_parent,const QStringList& _nomsFichiers,const QStringList& _extensions,
               const QString & _contenuFichier,
               const QString & _regFichier,
               bool _casseFichiers,
               bool _motsEntiersFichier,
               const QString & _contenuLignes,
               const QString & _regLignes,
               bool _caseLignes,
               bool _motsEntiersLignes):
    QDialog(_parent),
    ui(new Ui::Dialog),
    th(NULL),
    avancement(NULL),
    nomsFichiers(_nomsFichiers),
    extensions(_extensions)
{
    ui->setupUi(this);
    ui->fichiersTrouves->setModel(new QStringListModel());
    ui->fichiersAModifier->setModel(new QStringListModel());
	ui->contenuFichier->setText(_contenuFichier);
	ui->regFichier->setText(_regFichier);
	ui->casseFichiers->setChecked(_casseFichiers);
	ui->motsEntiersFichier->setChecked(_motsEntiersFichier);
	ui->contenuLignes->setText(_contenuLignes);
	ui->regLignes->setText(_regLignes);
	ui->caseLignes->setChecked(_caseLignes);
	ui->motsEntiersLignes->setChecked(_motsEntiersLignes);
    prefixeCommun=Thread::prefixe(nomsFichiers);
	ui->cheminCommun->setText(ui->cheminCommun->text()+" "+prefixeCommun);
	QVBoxLayout *lay_=new QVBoxLayout();
    lay_->addWidget(ui->scrollArea);
    setLayout(lay_);
//setLayout(ui->verticalLayout_4);
}

Dialog::~Dialog(){
    delete ui;
    ui=NULL;
    delete avancement;
    avancement=NULL;
    delete th;
    th=NULL;
}

void Dialog::closeEvent(QCloseEvent *){
    if(th!=NULL){
		th->arreterTache();
		th->wait();
		avancement->close();
	}
}


QString Dialog::lireFichier(const QString& _nom){
	QFile fichier(_nom);
	QString chaine_;
	if(fichier.open(QIODevice::ReadOnly|QIODevice::Text)){
	QTextStream flux(&fichier);
	chaine_=flux.readAll();
	fichier.close();
	}
	return chaine_;
}

void Dialog::ecrireFichier(const QString& _nom,const QString& lignes_){
	QFile fichier(_nom);
	if(fichier.open(QIODevice::WriteOnly|QIODevice::Text)){
	    QTextStream flux(&fichier);
	   flux<<lignes_;
	    fichier.close();
	}
}

void Dialog::on_chercher_clicked(){
    //chercher fichiers => thread
    if(th!=NULL){
		return;
		//th->arreterTache();
	}
    th=new Thread(lignes,
		      "",
		      nomsFichiers,
		      QStringList(),
		      extensions,
		      0,
		      "",
		      "",
		      -1,
		      "",
		      "",
		      ui->contenuFichier->text(),
		      ui->regFichier->text(),
		      ui->casseFichiers->isChecked(),
		      ui->motsEntiersFichier->isChecked(),
		      ui->contenuLignes->text(),
		      ui->regLignes->text(),
		      ui->caseLignes->isChecked(),
		      ui->motsEntiersLignes->isChecked());
    Thread *th_=qobject_cast<Thread*>(th);
	th_->majPrefixeCommun(Thread::prefixe(nomsFichiers));
	connect(th,SIGNAL(avancementTraitement(int)),this,SLOT(majAvancementTraitement(int)));
	connect(th,SIGNAL(changementEtape(QString,int)),this,SLOT(majChangementEtape(QString,int)));
	connect(th,SIGNAL(etapeTraitement(QString)),this,SLOT(majEtapeTraitement(QString)));
	connect(th,SIGNAL(finished()),this,SLOT(traitementFini()));
	avancement=new QProgressDialog("Recherche des fichiers","Annuler",0,0,this);
	avancement->setModal(true);
	connect(avancement,SIGNAL(canceled()),this,SLOT(annuler()));
	avancement->show();
	th->start();
}

void Dialog::majAvancementTraitement(int _avancement){
	if(avancement==NULL){
		return;
	}
	avancement->setValue(_avancement);
}

void Dialog::majChangementEtape(const QString& _nouvelleEtape,int _maximum){
	if(avancement==NULL){
		return;
	}
	etape=_nouvelleEtape;
	avancement->setMaximum(_maximum);
	avancement->setValue(0);
	avancement->setLabelText(etape+"\n"+element);
}

void Dialog::majEtapeTraitement(const QString& _element){
	if(avancement==NULL){
		return;
	}
	element=_element;
	avancement->setLabelText(etape+"\n"+element);
}

void Dialog::traitementFini(){
	if(th!=NULL){
		if(th->aFiniAuBout()){
			Thread *th_=qobject_cast<Thread*>(th);
			if(th_!=NULL){
				lignes=th_->valLignes();
				//prefixeCommun=th_->valPrefixeCommun();
				delete th;
				th=NULL;
				avancement->close();
				delete avancement;
				avancement=NULL;
				QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->fichiersTrouves->model());
				modele_->setStringList(lignes.keys());
			}else{
				delete th;
				th=NULL;
				avancement->close();
				close();
			}
		}else{
			annuler();
		}
	}

}

void Dialog::annuler(){
	if(th!=NULL){
		th->arreterTache();
		th->wait();
		delete th;
		th=NULL;
		if(avancement!=NULL){
			avancement->close();
			delete avancement;
			avancement=NULL;
		}
	}
}


void Dialog::on_ajouter_clicked(){
    //Ajouter fichiers dans la liste
    QString choix_=ui->fichiersTrouves->currentIndex().data().toString();
	 QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->fichiersAModifier->model());
	 modele_->insertRow(modele_->rowCount(),ui->fichiersAModifier->rootIndex());
	 QStringList extensions_=modele_->stringList();
	 if(!extensions_.contains(choix_)){
		 extensions_<<choix_;
	 }
	 //Mise a jour
	 lignesAModifier.insert(choix_,lignes.value(choix_));
	 extensions_.removeAll("");
	 extensions_.sort();
	 modele_->setStringList(extensions_);
}

void Dialog::on_retirer_clicked(){
    //Retirer fichiers de la liste
    QString choix_=ui->fichiersAModifier->currentIndex().data().toString();
	if(choix_!=""){
		 QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->fichiersAModifier->model());
		QStringList extensions_=modele_->stringList();
		extensions_.removeAll(choix_);
		lignesAModifier.remove(choix_);
		 modele_->setStringList(extensions_);
	}
}

void Dialog::on_fichiersAModifier_clicked(const QModelIndex &){
    if(ui->regLignes->text()==""){
        return;
    }
    typedef QPair<int,QString> NumeroLigne;
    QList<NumeroLigne> lignesAModifier_=lignesAModifier.value(ui->fichiersAModifier->currentIndex().data().toString());
    QString texte_;
    foreach(NumeroLigne e,lignesAModifier_){
        texte_+=QString::number(e.first)+"\t"+e.second+"\n";
    }
    ui->avantModif->setPlainText(texte_);
    texte_.clear();
    QRegExp expLigne_;
    if(ui->caseLignes->isChecked()){
        expLigne_=QRegExp(ui->regLignes->text(),Qt::CaseSensitive);
    }else{
        expLigne_=QRegExp(ui->regLignes->text(),Qt::CaseInsensitive);
    }
    if(ui->motsEntiersLignes->isChecked()){
        expLigne_=QRegExp("\\b"+expLigne_.pattern()+"\\b");
    }
    foreach(NumeroLigne e,lignesAModifier_){
        texte_+=QString::number(e.first)+"\t"+e.second.replace(QRegExp(expLigne_),ui->chaineRemplacement->text())+"\n";
    }
    ui->apresModif->setPlainText(texte_);
    //QString choix_=ui->fichiersAModifier->currentIndex().data().toString();
    //lire fichier puis afficher les lignes a modifier
    //puis les lignes modifiees
    //Afficher les lignes avant et apres modification des fichiers
}

void Dialog::on_remplacement_clicked(){
	if(th!=NULL){
		return;
		//th->arreterTache();
	}
	if(ui->regLignes->text()==""){
        return;
    }
	int reponse_=QMessageBox::question(this,
                                       "Voulez vous faire un \"backup\" des fichiers a modifier",
                                       "Faire un \"backup\" permet de garder les anciens fichiers tels quels.",
                                       QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    if(reponse_==QMessageBox::Cancel){
        return;
    }
    bool backup_=false;
    if(reponse_==QMessageBox::Yes){
        backup_=true;
    }
    QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->fichiersAModifier->model());
	QStringList nomsFichiersAmodifier_=modele_->stringList();
    th=new ThreadModif(prefixeCommun,
            nomsFichiersAmodifier_,
            lignesAModifier,
            ui->regLignes->text(),
            ui->caseLignes->isChecked(),
            ui->motsEntiersLignes->isChecked(),
            ui->chaineRemplacement->text(),
            backup_);
    connect(th,SIGNAL(avancementTraitement(int)),this,SLOT(majAvancementTraitement(int)));
	connect(th,SIGNAL(changementEtape(QString,int)),this,SLOT(majChangementEtape(QString,int)));
	connect(th,SIGNAL(etapeTraitement(QString)),this,SLOT(majEtapeTraitement(QString)));
	connect(th,SIGNAL(finished()),this,SLOT(traitementFini()));
	avancement=new QProgressDialog("Recherche des dossiers","Annuler",0,0,this);
	avancement->setModal(true);
	connect(avancement,SIGNAL(canceled()),this,SLOT(annuler()));
	avancement->show();
	th->start();
//    QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->fichiersAModifier->model());
//	QStringList nomsFichiersAmodifier_=modele_->stringList();
//	typedef QPair<int,QString> NumeroLigne;
//	QRegExp expLigne_;
//    if(ui->caseLignes->isChecked()){
//        expLigne_=QRegExp(ui->regLignes->text(),Qt::CaseSensitive);
//    }else{
//        expLigne_=QRegExp(ui->regLignes->text(),Qt::CaseInsensitive);
//    }
//    if(ui->motsEntiersLignes->isChecked()){
//        expLigne_=QRegExp("\\b"+expLigne_.pattern()+"\\b");
//    }
//    QString chaineRemplacement_=ui->chaineRemplacement->text();
//	foreach(QString e,nomsFichiersAmodifier_){
//        if(!QFile(prefixeCommun+e).exists()){
//            //QMessageBox::critical(this,"existe...",prefixeCommun+e);
//            continue;
//        }
//        /*if(!QFile(prefixeCommun+e).isReadable()){
//            QMessageBox::critical(this,"lire...",prefixeCommun+e);
//            continue;
//        }
//        if(!QFile(prefixeCommun+e).isWritable()){
//            QMessageBox::critical(this,"ecrire..",prefixeCommun+e);
//            continue;
//        }*/
//        if(!lignesAModifier.contains(e)){
//            //QMessageBox::critical(this,"pas contient",prefixeCommun+e);
//            continue;
//        }
//        if(lignesAModifier.value(e).isEmpty()){
//            //QMessageBox::critical(this,"vide",prefixeCommun+e);
//            continue;
//        }
//        //lire
//        QStringList lignes_=lireFichier(prefixeCommun+e).split("\n");
//        int nbLignes_=lignes_.size();
//        if(lignesAModifier.value(e).last().first>nbLignes_){
//            //QMessageBox::critical(this,"sup",prefixeCommun+e);
//            continue;
//        }
//        for(int i=0;i<nbLignes_;i++){
//            foreach(NumeroLigne e2,lignesAModifier.value(e)){
//                if(e2.first-1==i){
//                    lignes_[i].replace(expLigne_,chaineRemplacement_);
//                }
//            }
//        }
//        ecrireFichier(prefixeCommun+e,lignes_.join("\n"));
//        //lignes indices
//        //modifier les fichiers
//	}
//	close();
}
