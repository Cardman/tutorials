#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QApplication>
#include <QTextCodec>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include "ihm/fenetre.h"
#include "base_donnees/donnees.h"
#include "serialisable/parametrelogiciel.h"

#include <QMetaEnum>
#include <iostream>


/**Ce jeu est jouable pour l'instant en solo, il incarne un nouveau pokémon, deux nouvelles attaques et une catégorie de dresseur avec deux genres différents.*/
int main(int argc,char** argv){
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	/*methode(Utilitaire::lire_fichier("envir.xml").split("\n"));
	if(true){
		return 0;
	}*/
	QApplication app(argc,argv);
	ParametreLogiciel param;
	Fenetre fen;
	fen.init();
	fen.show();
	/*Curseur curseur_;
	curseur_.show();*/
	/*QLabel etiquette_;
	QVBoxLayout *lay_=new QVBoxLayout();
	QSlider *slider_=new QSlider(Qt::Horizontal);
	slider_->setRange(0,100);
	slider_->setValue(10);
	lay_->addWidget(slider_);
	QLabel *etiquette_i_=new QLabel();
	lay_->addWidget(etiquette_i_);
	QObject::connect(slider_,SIGNAL(valueChanged(int)),etiquette_i_,SLOT(setNum(int)));
	etiquette_.setLayout(lay_);
	etiquette_.show();
	lay_=NULL;
	slider_=NULL;
	etiquette_i_=NULL;*/
	//QMetaEnum acier=Difficulte::GainPtExp;
	/*QMetaObject mo =  Difficulte::staticMetaObject;
	//QMetaEnum acier = mo.enumerator(mo.indexOfEnumerator("GainPtExp"));
	QMetaEnum acier = mo.enumerator(0);//mo.indexOfEnumerator("GainPtExp"));
	std::cout<<acier.name()<<"\n";
	std::cout<<QString::number(acier.keyCount()).toStdString()<<"\n";
	std::cout<<QString::number(QFontMetrics(QFont()).width("a\t")).toStdString()<<"\n";
	std::cout<<QString::number(QFontMetrics(QFont()).width("\t")).toStdString()<<"\n";
	std::cout<<QString::number(QFontMetrics(QFont()).width("francois\t")).toStdString()<<"\n";
	std::cout<<QString::number(QFontMetrics(QFont()).width("francisi\t")).toStdString()<<"\n";
	std::cout<<QString::number(QFontMetrics(QFont()).width("abcdefghi\t")).toStdString()<<"\n";
	std::cout<<QString::number(QFontMetrics(QFont()).width("iiiiiiiii\t")).toStdString()<<"\n";
	std::cout<<QString::number(QFontMetrics(QFont()).width("iiiiiiiii")).toStdString()<<"\n";
	std::cout<<QString::number(QFontMetrics(QFont()).width("abcdefghijklmn\t")).toStdString()<<"\n";*/
	/**
class Toto : public QObject {
   Q_OBJECT // obligatoire pour Q_ENUMS
   Q_ENUMS(MonEnum)
public:
   enum MonEnum {
      Enum1 = 18,
      Enum2 = 52
   };
};
...
QMetaObject mo =  Toto::staticMetaObject;
QMetaEnum Toto_MonEnum = mo.enumerator(mo.indexOfEnumerator("MonEnum"));
qDebug() << Toto_MonEnum.keyToValue("Enum2");  // renvoie 52
qDebug() << Toto_MonEnum.valueToKey(18); // renvoie "Enum1"

*/
	//acier.
	/*std::cout<<"imprimable: \n";
	for(int i=0;i<256;i++){
		if(QChar(i).isPunct()){
			std::cout<<QString(QChar(i)).toStdString()<<"\n";
		}
	}
	std::cout<<"imprimable: \n";
	for(int i=0;i<256;i++){
		if(QChar(i).isLetter()){
			std::cout<<QString(QChar(i)).toStdString()<<"\n";
		}
	}
	std::cout<<"imprimable: \n";
	for(int i=0;i<256;i++){
		if(QChar(i).isDigit()){
			std::cout<<QString(QChar(i)).toStdString()<<"\n";
		}
	}*/
	return app.exec();
}
