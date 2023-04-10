#ifndef CLAVIER_H
#define CLAVIER_H

#include <QLabel>
class Bouton;
class Clavier : public QLabel{

	int indice;

	QString texte;

	Bouton *champ;

	Bouton *position;

	Q_OBJECT
public:
	Clavier();

	QString texte_ecrit()const;

	void vider_champ();

signals:

	void valider(const QString&);
public slots:
private slots:

	void maj_valider();

	/**Insertion*/
	void maj_champ(const QString&);

	void gauche();

	void droite();

	void supprimer_droite();

	void supprimer_gauche();
};

#endif // CLAVIER_H
