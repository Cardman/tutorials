#ifndef DIALOGUESQL_H
#define DIALOGUESQL_H

#include <QDialog>

class QTextEdit;
class QSqlQueryModel;
class DialogueSql : public QDialog
{
Q_OBJECT
	QTextEdit *edit;
	QTextEdit *erreur;
	QSqlQueryModel *plainModel;
public:
    explicit DialogueSql(int,QWidget *parent = 0);

signals:

public slots:
    void resultat();
};

#endif // DIALOGUESQL_H

