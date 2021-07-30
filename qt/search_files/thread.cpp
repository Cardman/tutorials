#include "thread.h"
#include "mainwindow.h"

#include <QDate>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

const QString Thread::separateurFichiers=QDir::separator();

Thread::Thread(const QMap<QString,QList<QPair<int,QString> > >& _lignes,
		   const QString& _nomDossier,
		   const QStringList& _nomsFichiers,
		   const QStringList& _extensions,
		   const QStringList& _extensionsBase,
		   const int& _rangRecursivite,
		   const QString& _dateTot,
		   const QString& _dateTard,
		   const int& _intervalleTemps,
		   const QString& _minOctets,
		   const QString& _maxOctets,
		   const QString& _contenuNomFichiers,
		   const QString& _expRegNomFichiers,
		   const bool& _casseNomFichiers,
		   const bool& _motsEntiersNomFichiers,
		   const QString& _contenuLignes,
		   const QString& _expRegLignes,
		   const bool& _casseLignes,
		   const bool& _motsEntiersLignes,QObject *parent) :
	MesThread(parent),lignes(_lignes),nomDossier(_nomDossier),nomsFichiers(_nomsFichiers),
	extensions(_extensions),extensionsBase(_extensionsBase),
	rangRecursivite(_rangRecursivite),
	dateTot(_dateTot),dateTard(_dateTard),
	intervalleTemps(_intervalleTemps),
	minOctets(_minOctets),maxOctets(_maxOctets),
	contenuNomFichiers(_contenuNomFichiers),expRegNomFichiers(_expRegNomFichiers),
	casseNomFichiers(_casseNomFichiers),motsEntiersNomFichiers(_motsEntiersNomFichiers),
	contenuLignes(_contenuLignes),expRegLignes(_expRegLignes),
	casseLignes(_casseLignes),motsEntiersLignes(_motsEntiersLignes)
{
}

QMap<QString,QList<QPair<int,QString> > > Thread::valLignes()const{
	return lignes;
}

QStringList Thread::valNomsFichiers()const{
	return nomsFichiers;
}

QString Thread::valPrefixeCommun()const{
	return prefixeCommun;
}
void Thread::majPrefixeCommun(const QString& _prefixeCommun){
	prefixeCommun=_prefixeCommun;
}

QMap<QString,long long> Thread::valTailles()const{
	return tailles;
}

void Thread::majTailles(const QMap<QString,long long>& _tailles){
	tailles=_tailles;
}

QString Thread::lireFichier(const QString& _nom){
	QFile fichier(_nom);
	QString chaine_;
	if(fichier.open(QIODevice::ReadOnly|QIODevice::Text)){
	QTextStream flux(&fichier);
	chaine_=flux.readAll();
	fichier.close();
	}
	return chaine_;
}

QString Thread::prefixe(const QStringList& _nomsFichiers){
	QString prefixe_;
	int taille_=0;
	int nbFichiers_=_nomsFichiers.size();
	//int min_=0;
	int max_=0;
	for(int i=0;i<nbFichiers_;i++){
		/*if(min_==0){
			min_=_nomsFichiers[i].size();
		}else if(_nomsFichiers[i].size()<min_){
			min_=_nomsFichiers[i].size();
		}*/
		if(_nomsFichiers[i].size()>max_){
			max_=_nomsFichiers[i].size();
		}
	}
	for(int i=0;i<max_;i++){
		bool sortirBoucles=false;
		for(int i2=1;i2<nbFichiers_;i2++){
			if(_nomsFichiers[i2].size()<=i){
				sortirBoucles=true;
				break;
			}
			if(_nomsFichiers[i2-1].size()<=i){
				sortirBoucles=true;
				break;
			}
			if(_nomsFichiers[i2][i]!=_nomsFichiers[i2-1][i]){
				sortirBoucles=true;
				break;
			}
		}
		if(sortirBoucles){
			taille_=i;
			break;
		}
	}
	for(int i=0;i<nbFichiers_;i++){
		prefixe_=_nomsFichiers[i].left(taille_);
		break;
	}
	prefixe_.remove(QRegExp("[^"+QRegExp::escape(separateurFichiers)+"]+$"));
	return prefixe_;
}

void Thread::run(){
	//arreter=false;
	//finiAuBout=false;
	tailles.clear();
	if(nomDossier!=""){
		prefixeCommun=nomDossier+separateurFichiers;
		lignes.clear();
		nomsFichiers.clear();
		int rang_=rangRecursivite;
		QStringList dossiers_fin_;
		/*if(rang_!=1){
			//QStringList fichiers_bis;
			dossiers_fin_=QDir(nomDossier).entryList(QDir::AllDirs|QDir::NoDotAndDotDot);
			//QStringList dossiers_avec_seul_fichiers;
			for(int i=0;i<dossiers_fin_.size();i++){
				dossiers_fin_[i]=nomDossier+separateurFichiers+dossiers_fin_[i];
			}
		}*/
		dossiers_fin_<<nomDossier;
		bool modif_=true;
		//bool affiche_=true;
		//QString ch_;
		int i_=0;
		QStringList dossiers_;
		QStringList dossiers_def_;
		QDir::Filters filtreSurDossier_=QDir::AllDirs|QDir::NoDotAndDotDot;
		QDir::Filters filtreSurFichier_=QDir::Files|QDir::NoDotAndDotDot;
		while(modif_){
			if(rang_==i_&&rang_>0){
				break;
			}
			modif_=false;
			dossiers_.clear();
			dossiers_def_<<dossiers_fin_;
			foreach(QString e,dossiers_fin_){
				/*if(e=="."||e==".."){
					continue;
				}*/
				if(estArrete()){
					return;
				}
				emit etapeTraitement(nomDossier+"\n"+e.mid(nomDossier.size()));
				foreach(QString e2,QDir(e).entryList(filtreSurDossier_)){
					dossiers_<<QString(e+separateurFichiers+e2);
				}
			}
			if(!dossiers_.isEmpty()){
				dossiers_fin_=dossiers_;
				modif_=true;
			}
			i_++;
		}
		dossiers_def_.removeDuplicates();
		emit changementEtape("Liste des fichiers",dossiers_def_.size());
		QString extensions_=extensionsBase.join("|");
		if(extensions.join("|")==""){
			int i_=0;
			foreach(QString e,dossiers_def_){
				foreach(QString e2,QDir(e).entryList(filtreSurFichier_).filter(QRegExp("\\.("+extensions_+")$"))){
					nomsFichiers<<e+separateurFichiers+e2;
				}
				emit avancementTraitement(i_);
				emit etapeTraitement(e);
				if(estArrete()){
					return;
				}
				i_++;
			}
		}else{
			int i_=0;
			foreach(QString e,dossiers_def_){
				foreach(QString e2,QDir(e).entryList(filtreSurFichier_).filter(QRegExp("\\.("+extensions.join("|")+")$"))){
					nomsFichiers<<e+separateurFichiers+e2;
				}
				emit avancementTraitement(i_);
				emit etapeTraitement(e);
				if(estArrete()){
					return;
				}
			}
		}
		emit changementEtape("Filtre des fichiers",nomsFichiers.size());
		filtrerFichiers();
		if(estArrete()){
			return;
		}
		emit changementEtape("Filtre des lignes",1000000);
		filtrerLignes();
		finirAuBout();
		//emit finir();
		return;
	}
	if(!nomsFichiers.isEmpty()){
		prefixeCommun=prefixe(nomsFichiers);
		lignes.clear();
		emit changementEtape("Filtre des fichiers",nomsFichiers.size());
		filtrerFichiers();
		if(estArrete()){
			return;
		}
		emit changementEtape("Filtre des lignes",1000000);
		filtrerLignes();
		finirAuBout();
		//emit finir();
		return;
	}
	/*prefixeCommun=prefixe(lignes.keys());
	long long tailleTotale_=0LL;
	foreach(QString e,lignes.keys()){
		long long taille_=QFileInfo(e).size();
		tailleTotale_+=taille_;
		e.remove(QRegExp("^"+QRegExp::escape(prefixeCommun)));
		tailles.insert(e,taille_);
	}
	foreach(QString e,tailles.keys()){
		tailles.insert(e,(tailles.value(e)*1000000)/tailleTotale_);
	}*/
	emit changementEtape("Filtre des lignes",1000000);
	filtrerLignesSansLireFichier();
	finirAuBout();
	//emit finir();
}

const QPair<QStringList,QStringList> Thread::motsEtSeparateursMots(const QString& _chaine){
	//QRegExp expRegMots_=QRegExp("([^\\*\\\\;\\.]|\\\\\\*|\\\\;|\\\\\\.|\\\\\\\\)+");
	QString listeMetas=MainWindow::echappeMeta+MainWindow::auPlus;
	listeMetas+=MainWindow::caractere+MainWindow::chaineCaracteres;
	QRegExp expRegMots_=QRegExp("([^"+QRegExp::escape(listeMetas)+"]|"+QRegExp::escape(MainWindow::echappeMeta)+".)+");
	QPair<QStringList,QStringList> motsEtSeparateursMots_;
	motsEtSeparateursMots_.second=_chaine.split(expRegMots_);
	int indice_=0;
	forever{
		indice_=expRegMots_.indexIn(_chaine,indice_);
		if(indice_<0){
			break;
		}
		indice_+=expRegMots_.matchedLength();
		motsEtSeparateursMots_.first<<expRegMots_.capturedTexts()[0];
	}
	int nbMots_=motsEtSeparateursMots_.first.size();
	for(int i=0;i<nbMots_;i++){
		QString& chaineAEchapper_=motsEtSeparateursMots_.first[i];
		chaineAEchapper_.replace(MainWindow::echappeMeta+MainWindow::auPlus,MainWindow::auPlus);
		chaineAEchapper_.replace(MainWindow::echappeMeta+MainWindow::caractere,MainWindow::caractere);
		chaineAEchapper_.replace(MainWindow::echappeMeta+MainWindow::chaineCaracteres,MainWindow::chaineCaracteres);
		chaineAEchapper_.replace(MainWindow::echappeMeta+MainWindow::echappeMeta,MainWindow::echappeMeta);
	}
	return motsEtSeparateursMots_;
}

bool Thread::chaineAPrendre(const QString& _chaine,const QString& _filtre,Qt::CaseSensitivity _casse){
	if(_filtre==""){
		return true;
	}
	const QPair<QStringList,QStringList> motsEtSeparateursMots_=motsEtSeparateursMots(_filtre);
	const QStringList& mots_=motsEtSeparateursMots_.first;
	const QStringList& separateurs_=motsEtSeparateursMots_.second;
	int i_=0;
	int indiceR_=0;
	int indiceRDecalePt_=0;
	int indiceSuivant_=0;
	foreach(QString e,mots_){
		int nbPts_=separateurs_[i_].count(MainWindow::caractere);
		indiceRDecalePt_=indiceR_+nbPts_;
		indiceSuivant_=_chaine.indexOf(e,indiceRDecalePt_,_casse);
		if(separateurs_[i_].contains(MainWindow::chaineCaracteres)){
			if(indiceSuivant_<0){
				return false;
			}
		}else{
			if(indiceRDecalePt_>indiceSuivant_||indiceRDecalePt_<indiceSuivant_-separateurs_[i_].count(MainWindow::auPlus)){
				return false;
			}
		}
		indiceR_=indiceSuivant_+e.size();
		i_++;
	}
	indiceR_+=separateurs_.last().count(MainWindow::caractere);
	if(indiceR_==_chaine.size()){
		return true;
	}
	if(indiceR_<_chaine.size()){
		if(separateurs_.last().contains(MainWindow::chaineCaracteres)){
			return true;
		}
		if(_chaine.size()<=indiceR_+separateurs_.last().count(MainWindow::auPlus)){
			return true;
		}
	}
	return false;
}

void Thread::filtrerFichiers(){
	if(contenuNomFichiers!=""){
		bool sensibleCasse_=casseNomFichiers;
		Qt::CaseSensitivity casse_;
		if(sensibleCasse_){
			casse_=Qt::CaseSensitive;
		}else{
			casse_=Qt::CaseInsensitive;
		}
		foreach(QString e,nomsFichiers){
			const QString& nomFichier_=e.split(separateurFichiers).last().section(".",0,e.count(".")-1);
			if(!chaineAPrendre(nomFichier_,contenuNomFichiers,casse_)){
				nomsFichiers.removeAll(e);
			}
			if(estArrete()){
				return;
			}
		}
	}
	QRegExp expRegFichier_=QRegExp(expRegNomFichiers);
	if(expRegNomFichiers!=""&&expRegFichier_.isValid()){
		bool sensibleCasse_=casseNomFichiers;
		Qt::CaseSensitivity casse_;
		if(sensibleCasse_){
			casse_=Qt::CaseSensitive;
		}else{
			casse_=Qt::CaseInsensitive;
		}
		bool entier_=motsEntiersNomFichiers;
		if(entier_){
			QRegExp expRegFichierMot_=QRegExp("\\b"+expRegNomFichiers+"\\b");
			expRegFichierMot_.setCaseSensitivity(casse_);
			foreach(QString e,nomsFichiers){
				if(e.indexOf(expRegFichierMot_)<0){
					nomsFichiers.removeAll(e);
				}
				if(estArrete()){
					return;
				}
			}
		}else{
            expRegFichier_.setCaseSensitivity(casse_);
			foreach(QString e,nomsFichiers){
				if(e.indexOf(expRegFichier_)<0){
					nomsFichiers.removeAll(e);
				}
				if(estArrete()){
					return;
				}
			}
		}
	}
	if(dateTot!=""){
		QDate dateAuPlusTot_=QDate::fromString(dateTot,"dd/MM/yyyy");
		if(dateAuPlusTot_.isValid()){
			foreach(QString e,nomsFichiers){
				QFileInfo infosFichier_=QFileInfo(e);
				if(infosFichier_.lastModified().date()<dateAuPlusTot_){
					nomsFichiers.removeAll(e);
				}
				if(estArrete()){
					return;
				}
			}
		}
	}
	if(dateTard!=""){
		QDate dateAuPlusTard_=QDate::fromString(dateTard,"dd/MM/yyyy");
		if(dateAuPlusTard_.isValid()){
			foreach(QString e,nomsFichiers){
				QFileInfo infosFichier_=QFileInfo(e);
				if(infosFichier_.lastModified().date()>dateAuPlusTard_){
					nomsFichiers.removeAll(e);
				}
				if(estArrete()){
					return;
				}
			}
		}
	}
	if(intervalleTemps>=0){
		QDate dateCouranteMoinsIntervalle_=QDate::currentDate();
		dateCouranteMoinsIntervalle_.addDays(-intervalleTemps);
		foreach(QString e,nomsFichiers){
			QFileInfo infosFichier_=QFileInfo(e);
			if(infosFichier_.lastModified().date()<dateCouranteMoinsIntervalle_){
				nomsFichiers.removeAll(e);
			}
			if(estArrete()){
				return;
			}
		}
	}
	if(minOctets!=""&&QRegExp("[1-9][0-9]*").exactMatch(minOctets)){
		long long minTaille_=minOctets.toLongLong();
		foreach(QString e,nomsFichiers){
			QFileInfo infosFichier_=QFileInfo(e);
			if(infosFichier_.size()<minTaille_){
				nomsFichiers.removeAll(e);
			}
			if(estArrete()){
				return;
			}
		}
	}
	if(maxOctets!=""&&QRegExp("[1-9][0-9]*").exactMatch(maxOctets)){
		long long maxTaille_=maxOctets.toLongLong();
		foreach(QString e,nomsFichiers){
			QFileInfo infosFichier_=QFileInfo(e);
			if(infosFichier_.size()>maxTaille_){
				nomsFichiers.removeAll(e);
			}
			if(estArrete()){
				return;
			}
		}
	}
	long long tailleTotale_=0LL;
	foreach(QString e,nomsFichiers){
		long long taille_=QFileInfo(e).size();
		tailleTotale_+=taille_;
		e.remove(QRegExp("^"+QRegExp::escape(prefixeCommun)));
		tailles.insert(e,taille_);
	}
	foreach(QString e,tailles.keys()){
		tailles.insert(e,(tailles.value(e)*1000000)/tailleTotale_);
	}
}

void Thread::filtrerLignes(){
	QString contenuLigne_=contenuLignes;
	bool sensibleCasse_=casseLignes;
	Qt::CaseSensitivity casse_;
	if(sensibleCasse_){
		casse_=Qt::CaseSensitive;
	}else{
		casse_=Qt::CaseInsensitive;
	}
	int avancement_=0;
	foreach(QString e,nomsFichiers){
		QString fichier_=lireFichier(e);
		int noLigne_=0;
		QList<QPair<int,QString> > lignesFichier_;
		foreach(QString e2,fichier_.split("\n")){
			noLigne_++;
			if(chaineAPrendre(e2,contenuLigne_,casse_)){
				lignesFichier_<<QPair<int,QString>(noLigne_,e2);
			}
			if(estArrete()){
				return;
			}
		}
		e.remove(QRegExp("^"+QRegExp::escape(prefixeCommun)));
		if(!lignesFichier_.isEmpty()){
			lignes.insert(e,lignesFichier_);
		}else{
			nomsFichiers.removeAll(prefixeCommun+e);
		}
		avancement_+=tailles.value(e);
		emit avancementTraitement(avancement_);
		emit etapeTraitement(e);
	}
	QString regLignes_=expRegLignes;
	QRegExp expRegLigne_=QRegExp(regLignes_);
	expRegLigne_.setCaseSensitivity(casse_);
	typedef QPair<int,QString> NumeroLigne;
	if(regLignes_!=""&&expRegLigne_.isValid()){
		emit changementEtape("Liste des lignes par exp reg",1000000);
		avancement_=0;
		bool entier_=motsEntiersLignes;
		if(entier_){
			QRegExp expRegLigneMot_=QRegExp("\\b"+regLignes_+"\\b");
			expRegLigneMot_.setCaseSensitivity(casse_);
			foreach(QString c,lignes.keys()){
				QList<QPair<int,QString> > lignesFichierFiltrees_;
				foreach(NumeroLigne e,lignes.value(c)){
					if(e.second.indexOf(expRegLigneMot_)>=0){
						lignesFichierFiltrees_<<e;
					}
				}
				if(!lignesFichierFiltrees_.isEmpty()){
					lignes.insert(c,lignesFichierFiltrees_);
				}else{
					lignes.remove(c);
					nomsFichiers.removeOne(prefixeCommun+c);
				}
				if(estArrete()){
					return;
				}
				avancement_+=tailles.value(c);
				emit avancementTraitement(avancement_);
				emit etapeTraitement(c);
			}
		}else{
            foreach(QString c,lignes.keys()){
				QList<QPair<int,QString> > lignesFichierFiltrees_;
				foreach(NumeroLigne e,lignes.value(c)){
					if(e.second.indexOf(expRegLigne_)>=0){
						lignesFichierFiltrees_<<e;
					}
				}
				if(!lignesFichierFiltrees_.isEmpty()){
					lignes.insert(c,lignesFichierFiltrees_);
				}else{
					lignes.remove(c);
					nomsFichiers.removeOne(prefixeCommun+c);
				}
				if(estArrete()){
					return;
				}
				avancement_+=tailles.value(c);
				emit avancementTraitement(avancement_);
				emit etapeTraitement(c);
			}
		}
	}

}


void Thread::filtrerLignesSansLireFichier(){
	QString contenuLigne_=contenuLignes;
	bool sensibleCasse_=casseLignes;
	Qt::CaseSensitivity casse_;
	if(sensibleCasse_){
		casse_=Qt::CaseSensitive;
	}else{
		casse_=Qt::CaseInsensitive;
	}
	int avancement_=0;
	typedef QPair<int,QString> NumLigne;
	foreach(QString e,lignes.keys()){
		QList<QPair<int,QString> > lignesFichier_;
		foreach(NumLigne e2,lignes.value(e)){
			if(chaineAPrendre(e2.second,contenuLigne_,casse_)){
				lignesFichier_<<e2;
			}
			if(estArrete()){
				return;
			}
		}
		if(!lignesFichier_.isEmpty()){
			lignes.insert(e,lignesFichier_);
		}else{
			lignes.remove(e);
		}
		avancement_+=tailles.value(e);
		emit avancementTraitement(avancement_);
		emit etapeTraitement(e);
	}
	QString regLignes_=expRegLignes;
	QRegExp expRegLigne_=QRegExp(regLignes_);
	expRegLigne_.setCaseSensitivity(casse_);
	typedef QPair<int,QString> NumeroLigne;
	if(regLignes_!=""&&expRegLigne_.isValid()){
		emit changementEtape("Liste des lignes par exp reg",1000000);
		avancement_=0;
		bool entier_=motsEntiersLignes;
		if(entier_){
			QRegExp expRegLigneMot_=QRegExp("\\b"+regLignes_+"\\b");
			expRegLigneMot_.setCaseSensitivity(casse_);
			foreach(QString c,lignes.keys()){
				QList<QPair<int,QString> > lignesFichierFiltrees_;
				foreach(NumeroLigne e,lignes.value(c)){
					if(e.second.indexOf(expRegLigneMot_)>=0){
						lignesFichierFiltrees_<<e;
					}
				}
				if(!lignesFichierFiltrees_.isEmpty()){
					lignes.insert(c,lignesFichierFiltrees_);
				}else{
					lignes.remove(c);
				}
				if(estArrete()){
					return;
				}
				avancement_+=tailles.value(c);
				emit avancementTraitement(avancement_);
				emit etapeTraitement(c);
			}
		}else{
			foreach(QString c,lignes.keys()){
				QList<QPair<int,QString> > lignesFichierFiltrees_;
				foreach(NumeroLigne e,lignes.value(c)){
					if(e.second.indexOf(expRegLigne_)>=0){
						lignesFichierFiltrees_<<e;
					}
				}
				if(!lignesFichierFiltrees_.isEmpty()){
					lignes.insert(c,lignesFichierFiltrees_);
				}else{
					lignes.remove(c);
				}
				if(estArrete()){
					return;
				}
				avancement_+=tailles.value(c);
				emit avancementTraitement(avancement_);
				emit etapeTraitement(c);
			}
		}
	}
}

