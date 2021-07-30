#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QList>
#include <QPair>
class QModelIndex;
class Thread;
class QProgressDialog;
class QCloseEvent;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
	const static QString auPlus;
	const static QString caractere;
	const static QString chaineCaracteres;
	const static QString echappeMeta;
	const static QString espaces;
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    Thread *th;
    QProgressDialog *avancement;
    QMap<QString,QList<QPair<int,QString> > > lignes;
    QMap<QString,long long> tailles;
    QString etape;
    QString element;
    QString etiquetteDossier;
    QString prefixeCommun;
    static void ecrireFichier(const QString& _nom,const QString& lignes_);
    void gererLignesFichiers(bool);
    QString correspondancesSeules(const QString&)const;
private slots:
    void on_actionAPartirDesLignesDesFichiers_triggered();
    void on_actionAPartirDesNomsDeFichiersTrouves_triggered();
    void on_actionAPartirDuSysteme_triggered();
    void on_actionNomsDeFichiersEtLignes_triggered();
    void on_actionChargerParametres_triggered();
    void on_actionSauvegarderParametres_triggered();
    void on_parcourir_clicked();
    void on_boutonAjouterExtension_clicked();
    void on_boutonSupprimerExtension_clicked();
    void on_fichiersResultants_clicked(const QModelIndex&);
    void majAvancementTraitement(int);
    void majChangementEtape(const QString&,int);
    void majEtapeTraitement(const QString&);
    void traitementFini();
    void annuler();
    void on_afficheExpReg_clicked(bool checked);
    //void on_afficheExpReg_stateChanged(int arg1);
    void on_actionNomsDeFichiersSeuls_triggered();
    void on_actionRemplacer_triggered();
};

#endif // MAINWINDOW_H
