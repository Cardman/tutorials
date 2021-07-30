#include "threadmodif.h"
#include <QFile>
#include <QDir>
#include <QTextStream>

ThreadModif::ThreadModif(const QString& _prefixeCommun,
                         const QStringList& _nomsFichiers,
                         const QMap<QString,QList<QPair<int,QString> > >& _lignesAModifier,
                         const QString& _regLignes,
                         bool _casseLignes,
                         bool _motsEntiersLignes,
                         const QString& _chaineRemplacement,bool _backup,QObject *parent):MesThread(parent),
    prefixeCommun(_prefixeCommun),
    nomsFichiers(_nomsFichiers),
    lignesAModifier(_lignesAModifier),
    regLignes(_regLignes),
    casseLignes(_casseLignes),
    motsEntiersLignes(_motsEntiersLignes),
    chaineRemplacement(_chaineRemplacement),
    backup(_backup){
}

QString ThreadModif::lireFichier(const QString& _nom){
	QFile fichier(_nom);
	QString chaine_;
	if(fichier.open(QIODevice::ReadOnly|QIODevice::Text)){
	QTextStream flux(&fichier);
	chaine_=flux.readAll();
	fichier.close();
	}
	return chaine_;
}

void ThreadModif::ecrireFichier(const QString& _nom,const QString& lignes_){
	QFile fichier(_nom);
	if(fichier.open(QIODevice::WriteOnly|QIODevice::Text)){
	    QTextStream flux(&fichier);
	   flux<<lignes_;
	    fichier.close();
	}
}

void ThreadModif::run(){
    QString dossierLecture_=prefixeCommun;
    if(backup){
        int iDossier_=0;
        while(QDir(prefixeCommun+"tmp"+QString::number(iDossier_)).exists()){
            iDossier_++;
        }
        QDir(prefixeCommun).mkdir("tmp"+QString::number(iDossier_));
        prefixeCommun+="tmp"+QString::number(iDossier_)+QDir::separator();
        QStringList dossierACreer_;
        foreach(QString e,nomsFichiers){
            if(!e.contains(QDir::separator())){
                continue;
            }
            dossierACreer_<<e.left(e.lastIndexOf(QDir::separator())+1);
        }
        dossierACreer_.removeDuplicates();
        foreach(QString e,dossierACreer_){
            QDir(prefixeCommun).mkpath(e);
        }
    }
	typedef QPair<int,QString> NumeroLigne;
	QRegExp expLigne_;
    if(casseLignes){
        expLigne_=QRegExp(regLignes,Qt::CaseSensitive);
    }else{
        expLigne_=QRegExp(regLignes,Qt::CaseInsensitive);
    }
    if(motsEntiersLignes){
        expLigne_=QRegExp("\\b"+expLigne_.pattern()+"\\b");
    }
    emit changementEtape("Remplacement",nomsFichiers.size());
    int i_=-1;
	foreach(QString e,nomsFichiers){
        i_++;
        emit avancementTraitement(i_);
        emit etapeTraitement(e);
        if(estArrete()){
            return;
        }
        if(!QFile(dossierLecture_+e).exists()){
            continue;
        }
        if(!lignesAModifier.contains(e)){
            continue;
        }
        if(lignesAModifier.value(e).isEmpty()){
            continue;
        }
        //lire
        QStringList lignes_=lireFichier(dossierLecture_+e).split("\n");
        if(estArrete()){
            return;
        }
        int nbLignes_=lignes_.size();
        //lignes indices
        if(lignesAModifier.value(e).last().first>nbLignes_){
            continue;
        }
        //lignes indices
        for(int i=0;i<nbLignes_;i++){
            foreach(NumeroLigne e2,lignesAModifier.value(e)){
                if(e2.first-1==i){
                    lignes_[i].replace(expLigne_,chaineRemplacement);
                }
            }
        }
        if(estArrete()){
            return;
        }
        //modifier les fichiers
        ecrireFichier(prefixeCommun+e,lignes_.join("\n"));
	}
	finirAuBout();
}
