//#include "autre/utilitaire.h"
#include "base_donnees/import.h"
#include "base_donnees/initbdd.h"
#include "autre/utilitaire.h"
#include <QRegExp>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
namespace Utilitaire{

	void initialialiser_bdd(int _langue){
		QThread *tache_=new QThread();
		InitBDD *th_=new InitBDD(_langue);
		QObject::connect(tache_,SIGNAL(finished()),tache_,SLOT(deleteLater()));
		QObject::connect(tache_,SIGNAL(started()),th_,SLOT(initialialiser()));
		QObject::connect(tache_,SIGNAL(finished()),th_,SLOT(deleteLater()));
		th_->moveToThread(tache_);
		tache_->start();
	}

	QString lire_fichier(const QString& nom){
		QFile fichier_(nom);
		fichier_.open(QIODevice::ReadOnly|QIODevice::Text);
		QTextStream flux_(&fichier_);
		flux_.setCodec("UTF-8");
		QString chaine_lue_=flux_.readAll();
		fichier_.close();
		return chaine_lue_;
	}

	void ecrire_fichier(const QString& nom,const QString& contenu){
		QFile fichier_(nom);
		fichier_.open(QIODevice::WriteOnly|QIODevice::Text);
		QTextStream flux_(&fichier_);
		flux_.setCodec("UTF-8");
		flux_<<contenu;
		fichier_.close();
	}

	QString formatter(const QString& chaine,const QStringList& arguments){
		QString chaine_=chaine;
		int indice_=-1;
		QRegExp exp_saut_l_2_("^\\\\n");
		chaine_.replace(exp_saut_l_2_,"\n");
		QRegExp exp_saut_l_("[^\\\\]\\\\n");
		forever{
			int ind2_=chaine_.indexOf(exp_saut_l_,indice_+1);
			if(ind2_<0){
				break;
			}
			QString saut_l_=exp_saut_l_.capturedTexts()[0];
			QString nouv_ch_=saut_l_[0]+"\n";
			chaine_.replace(ind2_,saut_l_.size(),nouv_ch_);
			indice_=ind2_;
		}
		QRegExp exp_tab_2_("^\\\\t");
		chaine_.replace(exp_tab_2_,"\t");
		QRegExp exp_tab_("[^\\\\]\\\\t");
		indice_=-1;
		forever{
			int ind2_=chaine_.indexOf(exp_tab_,indice_+1);
			if(ind2_<0){
				break;
			}
			QString saut_l_=exp_tab_.capturedTexts()[0];
			QString nouv_ch_=saut_l_[0]+"\t";
			chaine_.replace(ind2_,saut_l_.size(),nouv_ch_);
			indice_=ind2_;
		}
		chaine_.replace("\\\\","\\");
		int i_=1;
		foreach(QString s,arguments){
			QRegExp var_deb_("^\\$"+QString::number(i_)+"\\b");
			chaine_.replace(var_deb_,s);
			QRegExp var_en_cours_("[^\\$]\\$"+QString::number(i_)+"\\b");
			indice_=-1;
			forever{
				int ind2_=chaine_.indexOf(var_en_cours_,indice_+1);
				if(ind2_<0){
					break;
				}
				QString saut_l_=var_en_cours_.capturedTexts()[0];
				QString nouv_ch_=saut_l_[0]+s;
				chaine_.replace(ind2_,saut_l_.size(),nouv_ch_);
				indice_=ind2_;
			}
			i_++;
		}
		int nb_args_=arguments.size();
		i_=1;
		while(i_<=nb_args_){
			QRegExp var_en_cours_("\\$\\$"+QString::number(i_)+"\\b");
			indice_=-1;
			forever{
				int ind2_=chaine_.indexOf(var_en_cours_,indice_+1);
				if(ind2_<0){
					break;
				}
				QString saut_l_=var_en_cours_.capturedTexts()[0];
				QString nouv_ch_="$"+QString::number(i_);
				chaine_.replace(ind2_,saut_l_.size(),nouv_ch_);
				indice_=ind2_;
			}
			i_++;
		}
		return chaine_;
	}

	QString constante(const QStringList& dico_const,const QString& const_chercher){
		return dico_const.filter(QRegExp("^"+const_chercher+"\\t"))[0].split("\t")[1];
	}

	QString traduire(const QStringList& dico_trad,const QString& chaine_orig,int langue_dest){
		QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(Import::_indice_francais_)+"}";
		QStringList corresp_=dico_trad.filter(QRegExp("^"+ch_exp_reg_+chaine_orig+"\\t"));
		return corresp_[0].split("\t")[langue_dest];
	}

	QString traduire_bis(const QStringList& dico_trad,const QString& chaine_orig,int langue_dest){
		//QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(Import::_indice_francais_+1)+"}"
		//QStringList corresp_=dico_trad.filter(QRegExp("^"+ch_exp_reg_+chaine_orig+"\\t"))
		QStringList corresp_=dico_trad.filter(QRegExp("^"+chaine_orig+"\\t"));
		return corresp_[0].split("\t")[langue_dest];
	}

	QString rever_traduire(const QStringList& dico_trad,const QString& chaine_orig,int langue_orig){
		QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(langue_orig)+"}";
		QStringList corresp_=dico_trad.filter(QRegExp("^"+ch_exp_reg_+chaine_orig+"\\b"));
		return corresp_[0].split("\t")[Import::_indice_francais_];
	}

	QString rever_traduire_bis(const QStringList& dico_trad,const QString& chaine_orig,int langue_dest){
		//QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(Import::_indice_francais_+1)+"}"
		//QStringList corresp_=dico_trad.filter(QRegExp("^"+ch_exp_reg_+chaine_orig+"\\t"))
		QStringList corresp_=dico_trad.filter(QRegExp("^"+chaine_orig+"\\t"));
		return corresp_[0].split("\t")[langue_dest];
	}
	bool traduisible(const QStringList& dico_trad,const QString& chaine_orig){
		QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(Import::_indice_francais_)+"}";
		return !dico_trad.filter(QRegExp("^"+ch_exp_reg_+chaine_orig+"\\t")).isEmpty();
	}
	bool rever_traduisible(const QStringList& dico_trad,const QString& chaine_orig,int langue_orig){
		QString ch_exp_reg_="([^\\t]+\\t){"+QString::number(langue_orig)+"}";
		return !dico_trad.filter(QRegExp("^"+ch_exp_reg_+chaine_orig+"\\b")).isEmpty();
	}
}



