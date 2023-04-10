#ifndef DIALOGUEAIDE_H
#define DIALOGUEAIDE_H
#include <QDialog>

class DialogueAide: public QDialog{

	static QStringList init_titre();

	const static QStringList _titre_;

	const static QStringList _aide_;

	static QStringList init_aide();

public:

	DialogueAide(int,QWidget*);
};

#endif


