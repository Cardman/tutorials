#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QFile>
#include "ihm/fenetre.h"
#include "autre/utilitaire.h"
#include "ihm/dialogue/dialoguelangue.h"

/**Ce programme permet d'éditer toutes les cartes du jeu pokémon EVOLUTION.

Ce logiciel est très pratique car il évite d'écrire des fichiers XML pour des ressources.*/
int main(int argc,char** argv){
	QApplication app(argc,argv);
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	int langue_=Import::_indice_francais_;
	QString fichier_langue_="langue_log.txt";
	if(QFile(fichier_langue_).exists()){
		int langue_tmp_=Utilitaire::lire_fichier(fichier_langue_).toInt();
		if(langue_tmp_>=Import::_langues_.total()){
			langue_=DialogueLangue::choix_b();
		}else{
			langue_=langue_tmp_;
		}
	}else{
		langue_=DialogueLangue::choix_b();
	}
	Utilitaire::ecrire_fichier(fichier_langue_,QString::number(langue_));
	QTranslator translator;
	if(langue_==Import::_indice_francais_){
#ifdef QT_NO_DEBUG
		translator.load(":/fichiers_ressources/qt_fr");
#else
		translator.load("qt_fr","fichiers_ressources");
#endif
		app.installTranslator(&translator);
	}
	//Utilitaire::initialialiser_bdd(langue_);
	Fenetre fen_(langue_);
	fen_.show();
	fen_.init_bdd();
	return app.exec();
}

