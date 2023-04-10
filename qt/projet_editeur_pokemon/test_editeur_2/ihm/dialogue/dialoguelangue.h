#ifndef DIALOGUELANGUE_H
#define DIALOGUELANGUE_H
#include <QDialog>

class QButtonGroup;
class DialogueLangue: public QDialog{

	Q_OBJECT

	QButtonGroup *choix;

	int choix_l;

	DialogueLangue();

	virtual ~DialogueLangue();

public:

	static int choix_b();

private slots:

	void choix_de_langue();
};

#endif


