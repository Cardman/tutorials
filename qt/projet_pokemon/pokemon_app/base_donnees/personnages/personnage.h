#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <QObject>
#include <QString>
#include <QPair>

/***/
class Personnage: public QObject{

	Q_OBJECT

	/**Nom du personnage*/
	QString nom;

	/**nom de la miniature du personnage a utiliser*/
	QString nom_miniature;

	/**orientation du personnage*/
	QPair<int,int> orientation;

protected:

	static QStringList sous_attributs(const QStringList&,const QString&);

public:

	Personnage(const QStringList&,QObject *parent=0);

	QString nom_p()const;

	QString miniature()const;

	QPair<int,int> orient()const;
};
#endif


