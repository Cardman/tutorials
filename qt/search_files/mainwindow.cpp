#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProgressDialog>
#include <QStringListModel>
#include <QDate>
#include <QTextStream>
#include <QMessageBox>
//#include <iostream>
#include <QDomDocument>
#include <QApplication>
#include <QCloseEvent>
#include "thread.h"
#include "dialog.h"

const QString MainWindow::auPlus=";";
const QString MainWindow::caractere=".";
const QString MainWindow::chaineCaracteres="*";
const QString MainWindow::echappeMeta="\\";
const QString MainWindow::espaces="\t\t";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),th(NULL),avancement(NULL)
{
    ui->setupUi(this);
    QStringList extensions_;
    QFile fichier_(":/ressources/extensions");
    if(fichier_.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream flux(&fichier_);
        extensions_=flux.readAll().split("\n",QString::SkipEmptyParts);
        fichier_.close();
    }
    extensions_.removeDuplicates();
    extensions_.sort();
    /*extensions_<<"txt";
    extensions_<<"cpp";
    extensions_<<"h";
    extensions_<<"java";
    extensions_<<"xml";
    extensions_<<"qrc";
    extensions_<<"ui";*/
    //QStringListModel *modele_=new QStringListModel(extensions_);
    QStringListModel *modele_=new QStringListModel();
    //modele_->insertColumn(0);
    modele_->setStringList(extensions_);
    ui->extensionsBase->setModel(modele_);
    extensions_.clear();
    modele_=new QStringListModel(extensions_);
    ui->extensionsPrisesEnCompte->setModel(modele_);
    extensions_.clear();
   // extensions_<<"sure";
   //extensions_<<"pc";
     modele_=new QStringListModel(extensions_);
     ui->fichiersResultants->setModel(modele_);
     QString cheminCourant_=QDir::currentPath();
     cheminCourant_.replace('/',QDir::separator());
     ui->champDossier->setText(cheminCourant_);
     etiquetteDossier=ui->etiquetteDossier->text();
     ui->scrollArea->setWidget(ui->splitter_2);
     setCentralWidget(ui->scrollArea);
//ui->centralWidget=ui->scrollArea;
}



MainWindow::~MainWindow()
{
    delete ui;
    ui=NULL;
    delete avancement;
    avancement=NULL;
    delete th;
    th=NULL;
}

void MainWindow::closeEvent(QCloseEvent*){
	if(th!=NULL){
		th->arreterTache();
		th->wait();
		avancement->close();
	}
}

void MainWindow::on_boutonAjouterExtension_clicked(){
	QString choix_=ui->extensionsBase->currentIndex().data().toString();
	 QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->extensionsPrisesEnCompte->model());
	 modele_->insertRow(modele_->rowCount(),ui->extensionsPrisesEnCompte->rootIndex());
	 QStringList extensions_=modele_->stringList();
	 if(!extensions_.contains(choix_)){
		 extensions_<<choix_;
	 }
	 if(!extensions_.contains(ui->champExtension->text())){
		  extensions_<<ui->champExtension->text();
	 }
	 extensions_.removeAll("");
	 extensions_.sort();
	 modele_->setStringList(extensions_);
	//ui->lineEdit_6->text();
	//ui->listView_2->model()->insertRow(ui->listView_2->model()->rowCount(),QModelIndex());
	//ui->listView_2->model()->set(ui->listView_2->model()->rowCount())
}

void MainWindow::on_boutonSupprimerExtension_clicked(){
	QString choix_=ui->extensionsPrisesEnCompte->currentIndex().data().toString();
	if(choix_!=""){
		 QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->extensionsPrisesEnCompte->model());
		QStringList extensions_=modele_->stringList();
		extensions_.removeAll(choix_);
		 modele_->setStringList(extensions_);
	}
}

void MainWindow::on_fichiersResultants_clicked(const QModelIndex& _indice){
	gererLignesFichiers(ui->afficheExpReg->isChecked());
	/*QString nom_=_indice.data().toString();
	if(!lignes.contains(nom_.split(MainWindow::espaces)[0])){
		return;
	}
	typedef QPair<int,QString> NumeroLigne;
	QList<NumeroLigne> lignes_=lignes.value(nom_.split(MainWindow::espaces)[0]);
	QString texte_;
	foreach(NumeroLigne e,lignes_){
		texte_+=QString::number(e.first)+"\t"+e.second+"\n";
	}
	ui->lignesFichier->setPlainText(texte_);*/
}

void MainWindow::ecrireFichier(const QString& _nom,const QString& lignes_){
	QFile fichier(_nom);
	if(fichier.open(QIODevice::WriteOnly|QIODevice::Text)){
	    QTextStream flux(&fichier);
	   flux<<lignes_;
	    fichier.close();
	}
}

void MainWindow::majAvancementTraitement(int _avancement){
	if(avancement==NULL){
		return;
	}
	avancement->setValue(_avancement);
}

void MainWindow::majChangementEtape(const QString& _nouvelleEtape,int _maximum){
	if(avancement==NULL){
		return;
	}
	etape=_nouvelleEtape;
	avancement->setMaximum(_maximum);
	avancement->setValue(0);
	avancement->setLabelText(etape+"\n"+element);
}

void MainWindow::majEtapeTraitement(const QString& _element){
	if(avancement==NULL){
		return;
	}
	element=_element;
	avancement->setLabelText(etape+"\n"+element);
}

void MainWindow::traitementFini(){
	if(th!=NULL){
		if(th->aFiniAuBout()){
			lignes=th->valLignes();
			QStringList fichiers_=th->valNomsFichiers();
			tailles=th->valTailles();
			delete th;
			th=NULL;
			avancement->close();
			delete avancement;
			avancement=NULL;
			//ui->etiquetteDossier->setText(etiquetteDossier+" "+ui->champDossier->text());
			prefixeCommun=Thread::prefixe(fichiers_);
			ui->etiquetteDossier->setText(etiquetteDossier+" "+Thread::prefixe(fichiers_)+" avec pour nombre de fichiers: "+QString::number(lignes.size()));
			//Thread::prefixe(fichiers_)
			QString fichierCourant_ = ui->fichiersResultants->currentIndex().data().toString();
			QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->fichiersResultants->model());
			QStringList fichiersVus_;
			foreach(QString e,lignes.keys()){
				fichiersVus_<<(e+MainWindow::espaces+QString::number(lignes.value(e).size()));
			}
			modele_->setStringList(fichiersVus_);
			if(!fichiers_.isEmpty()){
				ui->fichiers->setPlainText(fichiers_.join("\n"));
			}
			if(!lignes.contains(fichierCourant_.split(" ")[0])){
				ui->lignesFichier->setPlainText("");
			}
			//ui->lignesFichier->setPlainText(Thread::prefixe(fichiers_));
		}else{
			annuler();
		}
	}

}

void MainWindow::annuler(){
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

void MainWindow::on_parcourir_clicked(){
	QString dossier_ = QFileDialog::getExistingDirectory(this);
	if(dossier_!=""){
		ui->champDossier->setText(dossier_);
	}/*else{
		QMessageBox::critical(this,"Erreur",QObject::tr(QRegExp("*a").errorString().toStdString().c_str()));
	}*/
}

void MainWindow::on_actionSauvegarderParametres_triggered(){
	QString nomFichier_ = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Parametres (*.xml)");
	if(nomFichier_==""){
		return;
	}
	QDomDocument dom("parametres_recherche_fichiers");
	//if(dom.setContent(&fichier))

	QDomElement elt=dom.createElement("params");
	QDomElement elt2=dom.createElement("contenuLigne");
	QDomText elt3=dom.createTextNode(ui->contenuLignes->text());
	elt2.appendChild(elt3);
	elt.appendChild(elt2);
	elt2=dom.createElement("regLigne");
	if(ui->motsEntierLignes->isChecked()){
		elt2.setAttribute("mots","V");
	}
	elt3=dom.createTextNode(ui->regLignes->text());
	elt2.appendChild(elt3);
	elt.appendChild(elt2);
	elt2=dom.createElement("casseLignes");
	if(ui->casseLignes->isChecked()){
		elt2.setAttribute("c","V");
	}
	elt.appendChild(elt2);

	elt2=dom.createElement("contenuFichiers");
	elt3=dom.createTextNode(ui->contenuNomFichier->text());
	elt2.appendChild(elt3);
	elt.appendChild(elt2);
	elt2=dom.createElement("regFichier");
	if(ui->motsEntierFichiers->isChecked()){
		elt2.setAttribute("mots","V");
	}
	elt3=dom.createTextNode(ui->regFichiers->text());
	elt2.appendChild(elt3);
	elt.appendChild(elt2);
	elt2=dom.createElement("casseFichiers");
	if(ui->casseNomsFichiers->isChecked()){
		elt2.setAttribute("c","V");
	}
	elt.appendChild(elt2);
	elt2=dom.createElement("extensions");
	QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->extensionsPrisesEnCompte->model());
	elt3=dom.createTextNode(modele_->stringList().join(";"));
	elt2.appendChild(elt3);

	elt2=dom.createElement("dateInf");
	elt3=dom.createTextNode(ui->dateAuPlusTot->text());
	elt2.appendChild(elt3);
	elt.appendChild(elt2);
	elt2=dom.createElement("dateSup");
	elt3=dom.createTextNode(ui->dateAuPlusTard->text());
	elt2.appendChild(elt3);
	elt.appendChild(elt2);
	elt2=dom.createElement("intervalleTemps");
	elt2.setAttribute("i",ui->intervalleTemps->value());
	elt.appendChild(elt2);
	elt2=dom.createElement("minOctet");
	elt2.setAttribute("v",ui->minOctets->text());
	elt.appendChild(elt2);
	elt2=dom.createElement("maxOctet");
	elt2.setAttribute("v",ui->maxOctets->text());
	elt.appendChild(elt2);

	elt2=dom.createElement("dossier");
	elt3=dom.createTextNode(ui->champDossier->text());
	elt2.appendChild(elt3);
	elt.appendChild(elt2);
	elt2=dom.createElement("rang");
	elt2.setAttribute("r",ui->rangRecursivite->value());
	elt.appendChild(elt2);

	dom.appendChild(elt);
	QFile fichier(nomFichier_);
	if(fichier.open(QIODevice::WriteOnly|QIODevice::Text)){
		QTextStream flux(&fichier);
		flux<<dom.toString(0);
		fichier.close();
	}
}


void MainWindow::on_actionChargerParametres_triggered(){
	QString fichier_ = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Parametres (*.xml)");
	if(fichier_==""){
		return;
	}
	QFile fichier2(fichier_);
	if(!fichier2.open(QIODevice::ReadOnly|QIODevice::Text)){
		return;
	}
	QDomDocument dom2("parametres_recherche_fichiers");
	if(!dom2.setContent(&fichier2)){
		return;
	}
	fichier2.close();
	QDomElement docElem = dom2.documentElement();
	int nbEnfs_=docElem.childNodes().size();
	//QDomElement elt_=docElem.childNodes().at(0).toElement();
	  QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->extensionsPrisesEnCompte->model());
	 for(int i=0;i<nbEnfs_;i++){
		 QDomElement eltLoc_=docElem.childNodes().at(i).toElement();
		 int  nbEnfs2_=eltLoc_.childNodes().size();
		 if(eltLoc_.tagName()=="contenuLigne"){
			 for(int i2=0;i2<nbEnfs2_;i2++){
				  ui->contenuLignes->setText(eltLoc_.childNodes().at(i2).toText().data());
				  break;
			 }
		 }
		 if(eltLoc_.tagName()=="regLigne"){
			 ui->motsEntierLignes->setChecked(eltLoc_.attribute("mots","")=="V");
			 for(int i2=0;i2<nbEnfs2_;i2++){
				  ui->regLignes->setText(eltLoc_.childNodes().at(i2).toText().data());
				  break;
			 }
		 }
		  if(eltLoc_.tagName()=="casseLignes"){
			   ui->casseLignes->setChecked(eltLoc_.attribute("c","")=="V");
		  }
		  if(eltLoc_.tagName()=="contenuFichiers"){
			  for(int i2=0;i2<nbEnfs2_;i2++){
				   ui->contenuNomFichier->setText(eltLoc_.childNodes().at(i2).toText().data());
				   break;
			  }
		  }
		  if(eltLoc_.tagName()=="regFichier"){
			  ui->motsEntierFichiers->setChecked(eltLoc_.attribute("mots","")=="V");
			  for(int i2=0;i2<nbEnfs2_;i2++){
				   ui->regFichiers->setText(eltLoc_.childNodes().at(i2).toText().data());
				   break;
			  }
		  }
		   if(eltLoc_.tagName()=="casseFichiers"){
			    ui->casseNomsFichiers->setChecked(eltLoc_.attribute("c","")=="V");
		   }
		   if(eltLoc_.tagName()=="extensions"){
			   modele_=qobject_cast<QStringListModel*>(ui->extensionsPrisesEnCompte->model());
			   QStringList ext_;
			   for(int i2=0;i2<nbEnfs2_;i2++){
				   ext_=eltLoc_.childNodes().at(i2).toText().data().split(";");
				   break;
			   }
			   modele_->setStringList(ext_);
		   }
		   if(eltLoc_.tagName()=="dateInf"){
			   for(int i2=0;i2<nbEnfs2_;i2++){
				    ui->dateAuPlusTot->setText(eltLoc_.childNodes().at(i2).toText().data());
				    break;
			   }
		   }
		   if(eltLoc_.tagName()=="dateSup"){
			   for(int i2=0;i2<nbEnfs2_;i2++){
				    ui->dateAuPlusTard->setText(eltLoc_.childNodes().at(i2).toText().data());
				    break;
			   }
		   }
		   if(eltLoc_.tagName()=="intervalleTemps"){
			   ui->intervalleTemps->setValue(eltLoc_.attribute("i","-1").toInt());
		   }
		   if(eltLoc_.tagName()=="minOctet"){
			   ui->minOctets->setText(eltLoc_.attribute("v",""));
		   }
		   if(eltLoc_.tagName()=="maxOctet"){
			   ui->maxOctets->setText(eltLoc_.attribute("v",""));
		   }
		   if(eltLoc_.tagName()=="dossier"){
			   for(int i2=0;i2<nbEnfs2_;i2++){
				    ui->champDossier->setText(eltLoc_.childNodes().at(i2).toText().data());
				    break;
			   }
		   }
		   if(eltLoc_.tagName()=="rang"){
			   ui->rangRecursivite->setValue(eltLoc_.attribute("r","0").toInt());
		   }
	 }
}

void MainWindow::on_actionNomsDeFichiersEtLignes_triggered(){
    if(th!=NULL){
        return;
    }
	QString fichier_ = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Texte (*.txt)");
	if(fichier_==""){
		return;
	}
	QString texteFichier_;
	typedef QPair<int,QString> NumeroLigne;
	foreach(QString c,lignes.keys()){
		texteFichier_+=c+"\n";
		foreach(NumeroLigne e,lignes.value(c)){
			texteFichier_+="\t"+QString::number(e.first)+"\t"+e.second+"\n";
		}
		texteFichier_+="\n";
	}
	ecrireFichier(fichier_,texteFichier_);
}

void MainWindow::on_actionAPartirDuSysteme_triggered(){
	if(th!=NULL){
		return;
		//th->arreterTache();
	}
	QString chemin_=ui->champDossier->text();
	if(chemin_==""){
		QMessageBox::critical(this,"Nom de dossier obligatoire","le dossier de recherche doit etre renseigne!");
		return;
	}
	QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->extensionsBase->model());
       QStringList extensions_=modele_->stringList();
       modele_=qobject_cast<QStringListModel*>(ui->extensionsPrisesEnCompte->model());
       QStringList extensionsPrisesEnCompte_=modele_->stringList();
	th=new Thread(lignes,
		      ui->champDossier->text(),
		      QStringList(),
		      extensionsPrisesEnCompte_,
		      extensions_,
		      ui->rangRecursivite->value(),
		      ui->dateAuPlusTot->text(),
		      ui->dateAuPlusTard->text(),
		      ui->intervalleTemps->value(),
		      ui->minOctets->text(),
		      ui->maxOctets->text(),
		      ui->contenuNomFichier->text(),
		      ui->regFichiers->text(),
		      ui->casseNomsFichiers->isChecked(),
		      ui->motsEntierFichiers->isChecked(),
		      ui->contenuLignes->text(),
		      ui->regLignes->text(),
		      ui->casseLignes->isChecked(),
		      ui->motsEntierLignes->isChecked());
	connect(th,SIGNAL(avancementTraitement(int)),this,SLOT(majAvancementTraitement(int)));
	connect(th,SIGNAL(changementEtape(QString,int)),this,SLOT(majChangementEtape(QString,int)));
	connect(th,SIGNAL(etapeTraitement(QString)),this,SLOT(majEtapeTraitement(QString)));
	connect(th,SIGNAL(finished()),this,SLOT(traitementFini()));
	avancement=new QProgressDialog("Recherche des dossiers","Annuler",0,0);
	//avancement->moveToThread(th);
	connect(avancement,SIGNAL(canceled()),this,SLOT(annuler()));
	avancement->show();
	th->start();
}

void MainWindow::on_actionAPartirDesNomsDeFichiersTrouves_triggered(){
	if(th!=NULL){
		return;
		//th->arreterTache();
	}
	QStringList fichiers_=ui->fichiers->toPlainText().split("\n");
	if(fichiers_.isEmpty()||fichiers_[0]==""){
		return;
	}
	QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->extensionsBase->model());
       QStringList extensions_=modele_->stringList();
       modele_=qobject_cast<QStringListModel*>(ui->extensionsPrisesEnCompte->model());
       QStringList extensionsPrisesEnCompte_=modele_->stringList();
	th=new Thread(lignes,
		      "",
		      fichiers_,
		      extensionsPrisesEnCompte_,
		      extensions_,
		      ui->rangRecursivite->value(),
		      ui->dateAuPlusTot->text(),
		      ui->dateAuPlusTard->text(),
		      ui->intervalleTemps->value(),
		      ui->minOctets->text(),
		      ui->maxOctets->text(),
		      ui->contenuNomFichier->text(),
		      ui->regFichiers->text(),
		      ui->casseNomsFichiers->isChecked(),
		      ui->motsEntierFichiers->isChecked(),
		      ui->contenuLignes->text(),
		      ui->regLignes->text(),
		      ui->casseLignes->isChecked(),
		      ui->motsEntierLignes->isChecked());
	th->majPrefixeCommun(prefixeCommun);
	connect(th,SIGNAL(avancementTraitement(int)),this,SLOT(majAvancementTraitement(int)));
	connect(th,SIGNAL(changementEtape(QString,int)),this,SLOT(majChangementEtape(QString,int)));
	connect(th,SIGNAL(etapeTraitement(QString)),this,SLOT(majEtapeTraitement(QString)));
	connect(th,SIGNAL(finished()),this,SLOT(traitementFini()));
	avancement=new QProgressDialog("Recherche des dossiers","Annuler",0,0);
	connect(avancement,SIGNAL(canceled()),this,SLOT(annuler()));
	avancement->show();
	th->start();
}

void MainWindow::on_actionAPartirDesLignesDesFichiers_triggered(){
	if(th!=NULL){
		return;
		//th->arreterTache();
	}
	QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->extensionsBase->model());
       QStringList extensions_=modele_->stringList();
       modele_=qobject_cast<QStringListModel*>(ui->extensionsPrisesEnCompte->model());
       QStringList extensionsPrisesEnCompte_=modele_->stringList();
	th=new Thread(lignes,
			"",
		      QStringList(),
		      extensionsPrisesEnCompte_,
		      extensions_,
		      ui->rangRecursivite->value(),
		      ui->dateAuPlusTot->text(),
		      ui->dateAuPlusTard->text(),
		      ui->intervalleTemps->value(),
		      ui->minOctets->text(),
		      ui->maxOctets->text(),
		      ui->contenuNomFichier->text(),
		      ui->regFichiers->text(),
		      ui->casseNomsFichiers->isChecked(),
		      ui->motsEntierFichiers->isChecked(),
		      ui->contenuLignes->text(),
		      ui->regLignes->text(),
		      ui->casseLignes->isChecked(),
		      ui->motsEntierLignes->isChecked());
	th->majTailles(tailles);
	connect(th,SIGNAL(avancementTraitement(int)),this,SLOT(majAvancementTraitement(int)));
	connect(th,SIGNAL(changementEtape(QString,int)),this,SLOT(majChangementEtape(QString,int)));
	connect(th,SIGNAL(etapeTraitement(QString)),this,SLOT(majEtapeTraitement(QString)));
	connect(th,SIGNAL(finished()),this,SLOT(traitementFini()));
	avancement=new QProgressDialog("Recherche des dossiers","Annuler",0,0);
	connect(avancement,SIGNAL(canceled()),this,SLOT(annuler()));
	avancement->show();
	th->start();
}

void MainWindow::gererLignesFichiers(bool _checked){
    if(!_checked){
        QString nom_=ui->fichiersResultants->currentIndex().data().toString();
        if(!lignes.contains(nom_.split(MainWindow::espaces)[0])){
            return;
        }
        typedef QPair<int,QString> NumeroLigne;
        QList<NumeroLigne> lignes_=lignes.value(nom_.split(MainWindow::espaces)[0]);
        QString texte_;
        foreach(NumeroLigne e,lignes_){
            texte_+=QString::number(e.first)+"\t"+e.second+"\n";
        }
        ui->lignesFichier->setPlainText(texte_);
        return;
    }
    if(ui->regLignes->text()==""){
        return;
    }
//    if(_checked){
        //afficheExpReg
        QString nom_=ui->fichiersResultants->currentIndex().data().toString();
        if(!lignes.contains(nom_.split(MainWindow::espaces)[0])){
            return;
        }
       /* typedef QPair<int,QString> NumeroLigne;
        //
        QList<NumeroLigne> lignes_=lignes.value(nom_.split(MainWindow::espaces)[0]);
        QString texte_;
        QRegExp expLigne_;
        if(ui->casseLignes->isChecked()){
            expLigne_=QRegExp(ui->regLignes->text(),Qt::CaseSensitive);
        }else{
            expLigne_=QRegExp(ui->regLignes->text(),Qt::CaseInsensitive);
        }
        if(ui->motsEntierLignes->isChecked()){
            expLigne_=QRegExp("\\b"+expLigne_.pattern()+"\\b");
        }
        bool videMatch_=expLigne_.exactMatch("");
        if(videMatch_){
            foreach(NumeroLigne e,lignes_){
//                if(e.second==""){
//                    texte_+=QString::number(e.first)+"\t\t1\n";
//                    continue;
//                }
                texte_+=QString::number(e.first)+"\t\t"+QString::number(e.second.size()+1)+"\n";
            }
        }else{
            foreach(NumeroLigne e,lignes_){
                if(e.second==""){
                    continue;
                }
                int ind_=0;
                QMap<QString,int> emplacements_;
                forever{
                    int ind2_=e.second.indexOf(expLigne_,ind_);
                    if(ind2_<0){
                        break;
                    }
                    QString capture_=expLigne_.capturedTexts()[0];
                    if(!emplacements_.contains(capture_)){
                        emplacements_.insert(capture_,1);
                    }else{
                        emplacements_.insert(capture_,emplacements_.value(capture_)+1);
                    }
                    ind_=ind2_+capture_.size();
                }
                foreach(QString c,emplacements_.keys()){
                    texte_+=QString::number(e.first)+"\t"+c+"\t"+QString::number(emplacements_.value(c))+"\n";
                }
                //e.second.indexOf(expLigne_);
                
                //if(ui->regLignes->text())
            }
        }*/
        ui->lignesFichier->setPlainText(correspondancesSeules(nom_.split(MainWindow::espaces)[0]));
//    }else{
        
//    }
}

void MainWindow::on_afficheExpReg_clicked(bool _checked){
    if(th!=NULL){
        return;
    }

    /*if(_checked){
        QMessageBox::information(this,"clic","");
    }else{
        QMessageBox::information(this,"pas clic","");
    }*/
    gererLignesFichiers(_checked);
}

/*void MainWindow::on_afficheExpReg_stateChanged(int _arg1){
    //if(_arg1==QCheckBox::)
    QMessageBox::information(this,"clic",QString::number(_arg1));
}*/

QString MainWindow::correspondancesSeules(const QString& _nomFichierRes)const{
    typedef QPair<int,QString> NumeroLigne;
    QList<NumeroLigne> lignes_=lignes.value(_nomFichierRes);
    QString texte_;
    QRegExp expLigne_;
    if(ui->casseLignes->isChecked()){
        expLigne_=QRegExp(ui->regLignes->text(),Qt::CaseSensitive);
    }else{
        expLigne_=QRegExp(ui->regLignes->text(),Qt::CaseInsensitive);
    }
    if(ui->motsEntierLignes->isChecked()){
        expLigne_=QRegExp("\\b"+expLigne_.pattern()+"\\b");
    }
    bool videMatch_=expLigne_.exactMatch("");
    if(videMatch_){
        foreach(NumeroLigne e,lignes_){
            texte_+=QString::number(e.first)+"\t\t"+QString::number(e.second.size()+1)+"\n";
        }
    }else{
        foreach(NumeroLigne e,lignes_){
            if(e.second==""){
                continue;
            }
            int ind_=0;
            QMap<QString,int> emplacements_;
            forever{
                int ind2_=e.second.indexOf(expLigne_,ind_);
                if(ind2_<0){
                    break;
                }
                QString capture_=expLigne_.capturedTexts()[0];
                if(!emplacements_.contains(capture_)){
                    emplacements_.insert(capture_,1);
                }else{
                    emplacements_.insert(capture_,emplacements_.value(capture_)+1);
                }
                ind_=ind2_+capture_.size();
            }
            foreach(QString c,emplacements_.keys()){
                texte_+=QString::number(e.first)+"\t"+c+"\t"+QString::number(emplacements_.value(c))+"\n";
            }
        }
    }
    return texte_;
}

void MainWindow::on_actionNomsDeFichiersSeuls_triggered(){
    if(th!=NULL){
        return;
    }
    QString fichier_ = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Texte (*.txt)");
	if(fichier_==""){
		return;
	}
	QString texteFichier_;
    /*QRegExp expLigne_;
    if(ui->casseLignes->isChecked()){
        expLigne_=QRegExp(ui->regLignes->text(),Qt::CaseSensitive);
    }else{
        expLigne_=QRegExp(ui->regLignes->text(),Qt::CaseInsensitive);
    }
    if(ui->motsEntierLignes->isChecked()){
        expLigne_=QRegExp("\\b"+expLigne_.pattern()+"\\b");
    }*/
	foreach(QString c,lignes.keys()){
        texteFichier_+=c+"\n";
        texteFichier_+=correspondancesSeules(c);
        /*typedef QPair<int,QString> NumeroLigne;
        QList<NumeroLigne> lignes_=lignes.value(c);
        foreach(NumeroLigne e,lignes_){
            int ind_=0;
            QMap<QString,int> emplacements_;
            forever{
                int ind2_=e.second.indexOf(expLigne_,ind_);
                if(ind2_<0){
                    break;
                }
                QString capture_=expLigne_.capturedTexts()[0];
                if(!emplacements_.contains(capture_)){
                    emplacements_.insert(capture_,1);
                }else{
                    emplacements_.insert(capture_,emplacements_.value(capture_)+1);
                }
                ind_=ind2_+capture_.size();
            }
            foreach(QString c2,emplacements_.keys()){
                 texteFichier_+=QString::number(e.first)+"\t"+c2+"\t"+QString::number(emplacements_.value(c2))+"\n";
            }
        }
        texteFichier_+="\n";*/
    }
	ecrireFichier(fichier_,texteFichier_);
}

void MainWindow::on_actionRemplacer_triggered(){
    if(th!=NULL){
        return;
    }
    QStringListModel *modele_=qobject_cast<QStringListModel*>(ui->extensionsBase->model());
    QStringList extensions_=modele_->stringList();
    modele_=qobject_cast<QStringListModel*>(ui->extensionsPrisesEnCompte->model());
    extensions_<<modele_->stringList();
    extensions_.removeDuplicates();
    Dialog *dial_=new Dialog(this,
                             ui->fichiers->toPlainText().split("\n",QString::SkipEmptyParts),
                             extensions_,
                             ui->contenuNomFichier->text(),
                             ui->regFichiers->text(),
                             ui->casseNomsFichiers->isChecked(),
                             ui->motsEntierFichiers->isChecked(),
                             ui->contenuLignes->text(),
                             ui->regLignes->text(),
                             ui->casseLignes->isChecked(),
                             ui->motsEntierLignes->isChecked());
    dial_->exec();
    delete dial_;
    dial_=NULL;
}
