#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMap>

class MesThread;
class QProgressDialog;
class QModelIndex;

namespace Ui {
    class Dialog;
}

class Dialog:public QDialog
{
Q_OBJECT
    Ui::Dialog *ui;
    MesThread *th;
    QProgressDialog *avancement;
    QStringList nomsFichiers;
    QStringList extensions;
    QString etape;
    QString element;
    QString prefixeCommun;
    QMap<QString,QList<QPair<int,QString> > > lignes;
    QMap<QString,QList<QPair<int,QString> > > lignesAModifier;
	static QString lireFichier(const QString&);
    static void ecrireFichier(const QString& _nom,const QString& lignes_);
    void closeEvent(QCloseEvent *);
public:
    Dialog(QWidget *,
           const QStringList&,
           const QStringList&,
           const QString&,
           const QString&,
           bool,
           bool,
           const QString&,
           const QString&,
           bool,
           bool);
    ~Dialog();
private slots:
    void on_chercher_clicked();
    void on_ajouter_clicked();
    void on_retirer_clicked();
    void on_fichiersAModifier_clicked(const QModelIndex &index);
    void majAvancementTraitement(int);
    void majChangementEtape(const QString&,int);
    void majEtapeTraitement(const QString&);
    void traitementFini();
    void annuler();
    void on_remplacement_clicked();
};

#endif // DIALOG_H
