#include "dialoguesql.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QTextEdit>
#include <QStringList>
#include <QTableView>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QVBoxLayout>

DialogueSql::DialogueSql(int _langue,QWidget *parent) : QDialog(parent){
	QStringList cst_sql_;
	foreach(QString c,Import::_constantes_non_num_){
		if(c.startsWith("SQL_")){
			cst_sql_<<c.split("\t")[_langue+1];
		}
	}
	QVBoxLayout *lay_=new QVBoxLayout();
	QTextEdit *infos_=new QTextEdit();
	infos_->setPlainText(cst_sql_.join("\n"));
	infos_->setReadOnly(true);
	lay_->addWidget(infos_);
	edit=new QTextEdit();
	lay_->addWidget(edit);
	QPushButton *b=new QPushButton("exec");
	connect(b,SIGNAL(clicked()),this,SLOT(resultat()));
	lay_->addWidget(b);
	QTableView *view = new QTableView;
	plainModel=new QSqlQueryModel();
	view->setModel(plainModel);
	lay_->addWidget(view);
	erreur=new QTextEdit();
	erreur->setReadOnly(true);
	lay_->addWidget(erreur);
	setLayout(lay_);

}

void DialogueSql::resultat(){
	plainModel->setQuery(edit->toPlainText());
	//erreur->setPlainText("")
	erreur->setPlainText(plainModel->query().lastError().text());
}

