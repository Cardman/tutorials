#include "ihm/dialogue/dialoguepersonnage.h"
#include "ihm/dialogue/dialogueachats.h"
#include "ihm/dialogue/dialoguecapsules.h"
#include "ihm/dialogue/dialogueobjet.h"
#include "ihm/dialogue/dialoguepkcombat.h"
#include "serialisable/personnages/personnage.h"
#include "base_donnees/import.h"
#include "autre/utilitaire.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QCloseEvent>
#include <QMessageBox>
#include <QButtonGroup>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>

const HashMap<QString,QStringList> DialoguePersonnage::_elements_ihm_=DialoguePersonnage::init_elements_ihm();

HashMap<QString,QStringList> DialoguePersonnage::init_elements_ihm(){
	HashMap<QString,QStringList> elements_ihm_;
#ifdef QT_NO_DEBUG
	QStringList lignes_=Utilitaire::lire_fichier(":/ihm_texte/"+QString(__FILE__).split(QRegExp("\\\\|/")).last().split(".")[0]).split("\n");
#else
	QStringList lignes_=Utilitaire::lire_fichier("fichiers_ressources/ihm_texte/"+QString(__FILE__).split("/").last().split(".")[0]+".txt").split("\n");
#endif
	foreach(QString l,lignes_){
		QStringList infos_l_=l.split("\t");
		elements_ihm_.ajouter_cle_valeur(infos_l_[0],QStringList(infos_l_.mid(1)));
	}
	return elements_ihm_;
}

QString DialoguePersonnage::traduire(const QString& _chaine)const{
	return _elements_ihm_.valeur(_chaine)[langue];
}

DialoguePersonnage::DialoguePersonnage(int _langue,QWidget* _parent):QDialog(_parent){
	langue=_langue;
	rejeter=true;
	setWindowTitle(traduire("TITRE"));
	choix=new QButtonGroup();
	connect(choix,SIGNAL(buttonReleased(int)),this,SLOT(activer_bouton(int)));
	QFormLayout *centre_=new QFormLayout();
		foreach(QString l,Import::_langues_.cles()){
		QLineEdit *nom_=new QLineEdit();
		QStringList args_;
		args_<<Import::_langues_.valeur(l)[langue];
		centre_->addRow(Utilitaire::formatter(traduire("NOM"),args_),nom_);
		noms<<nom_;
	}
	nom_miniature=new QComboBox();
	foreach(QString s,Import::_dresseurs_micros_.cles()){
		nom_miniature->addItem(QPixmap::fromImage(Import::_dresseurs_micros_.valeur(s)),s);
	}
	nom_miniature->setEditable(true);
	centre_->addRow(traduire("NOM_MINIATURE"),nom_miniature);
	orientation_h=new QSpinBox();
	orientation_h->setRange(-1,1);
	orientation_h->setValue(0);
	centre_->addRow(traduire("ORIENTATION_H"),orientation_h);
	orientation_v=new QSpinBox();
	orientation_v->setRange(-1,1);
	orientation_v->setValue(1);
	centre_->addRow(traduire("ORIENTATION_V"),orientation_v);
	QRadioButton *radio_;
	b_editer_achat_objets=new QPushButton(traduire("EDITER"));
	connect(b_editer_achat_objets,SIGNAL(clicked()),this,SLOT(maj_achat_objets()));
	radio_=new QRadioButton(traduire("ACHAT_OBJ"));//DialogueAchats TODO
	centre_->addRow(radio_,b_editer_achat_objets);
	choix->addButton(radio_,DialoguePersonnage::ACHAT_OBJS);
	b_editer_achat_ct=new QPushButton(traduire("EDITER"));
	connect(b_editer_achat_ct,SIGNAL(clicked()),this,SLOT(maj_achat_capsules()));
	radio_=new QRadioButton(traduire("ACHAT_CT"));//DialogueCapsules TODO
	centre_->addRow(radio_,b_editer_achat_ct);
	choix->addButton(radio_,DialoguePersonnage::ACHAT_CTS);
	b_editer_don_cs=new QPushButton(traduire("EDITER"));
	connect(b_editer_don_cs,SIGNAL(clicked()),this,SLOT(maj_don_capsules()));
	radio_=new QRadioButton(traduire("DON_CS"));
	centre_->addRow(radio_,b_editer_don_cs);
	choix->addButton(radio_,DialoguePersonnage::DON_CS);
	radio_=new QRadioButton(traduire("SOIN_PK"));
	centre_->addRow(radio_,new QLabel(""));
	choix->addButton(radio_,DialoguePersonnage::SOIN_PK);
	radio_=new QRadioButton(traduire("LIEU_VIVRE_FOSSILE"));
	centre_->addRow(radio_,new QLabel(""));
	choix->addButton(radio_,DialoguePersonnage::LIEU_VIVRE);
	radio_=new QRadioButton(traduire("LIEU_PENSION"));
	centre_->addRow(radio_,new QLabel(""));
	choix->addButton(radio_,DialoguePersonnage::PENSION);
	radio_=new QRadioButton(traduire("MOVE_TUTOR"));
	centre_->addRow(radio_,new QLabel(""));
	choix->addButton(radio_,DialoguePersonnage::MOVE_TUTORS);
	b_editer_don_obj=new QPushButton(traduire("EDITER"));
	connect(b_editer_don_obj,SIGNAL(clicked()),this,SLOT(maj_don_objets()));
	radio_=new QRadioButton(traduire("DON_OBJET"));
	centre_->addRow(radio_,b_editer_don_obj);
	choix->addButton(radio_,DialoguePersonnage::DON_OBJS);//DialogueObjet
	b_editer_don_pk=new QPushButton(traduire("EDITER"));
	connect(b_editer_don_pk,SIGNAL(clicked()),this,SLOT(maj_don_pokemon()));
	radio_=new QRadioButton(traduire("DON_PK"));
	centre_->addRow(radio_,b_editer_don_pk);
	choix->addButton(radio_,DialoguePersonnage::DON_PK);//DialoguePkCombat
	radio_=new QRadioButton(traduire("RIEN"));
	centre_->addRow(radio_,new QLabel(""));
	choix->addButton(radio_,DialoguePersonnage::RIEN);
	radio_->setChecked(true);
	b_editer_achat_objets->setEnabled(false);
	b_editer_achat_ct->setEnabled(false);
	b_editer_don_cs->setEnabled(false);
	b_editer_don_obj->setEnabled(false);
	b_editer_don_pk->setEnabled(false);
	QPushButton *valider_=new QPushButton(traduire("VALIDER"));
	connect(valider_,SIGNAL(clicked()),this,SLOT(acceptation()));
	centre_->addRow("",valider_);
	setLayout(centre_);
}

void DialoguePersonnage::maj_personnage(QPair<int,Personnage*> _personnage){
	setWindowTitle(traduire("TITRE_2"));
	int nb_champs_=noms.size();
	QStringList ls_=_personnage.second->adr_nom()->split("\t");
	for(int i=0;i<nb_champs_;i++){
		noms[i]->setText(ls_[i]);
	}
	nom_miniature->setEditText(*_personnage.second->adr_nom_miniature());
	orientation_h->setValue(_personnage.second->adr_orientation()->first);
	orientation_v->setValue(_personnage.second->adr_orientation()->second);
	activer_bouton(_personnage.first);
	choix->button(_personnage.first)->setChecked(true);
}

QPair<int,Personnage> DialoguePersonnage::nv_personnage()const{
	QPair<int,Personnage> perso_(choix->checkedId(),Personnage());
	QString noms_=noms[0]->text();
	int nb_champs_=noms.size();
	for(int i=1;i<nb_champs_;i++){
		noms_+="\t"+noms[i]->text();
	}
	*perso_.second.adr_nom()=noms_;
	*perso_.second.adr_nom_miniature()=nom_miniature->currentText();
	*perso_.second.adr_orientation()=QPair<int,int>(orientation_h->value(),orientation_v->value());
	return perso_;
}

void DialoguePersonnage::editer_achat_objets(const QStringList& _achat_obj){
	achat_objets=_achat_obj;
}
void DialoguePersonnage::editer_achat_ct(const QList<uchar>& _achat_ct){
	achat_ct=_achat_ct;
}
void DialoguePersonnage::editer_don_cs(const QList<uchar>& _don_cs){
	don_cs=_don_cs;
}
void DialoguePersonnage::editer_don_obj(const QString& _don_obj){
	don_obj=_don_obj;
}
void DialoguePersonnage::editer_don_pk(const Pokemon& _don_pk){
	don_pk=_don_pk;
}

QStringList DialoguePersonnage::nv_achat_objets()const{
	return achat_objets;
}
QList<uchar> DialoguePersonnage::nv_achat_ct()const{
	return achat_ct;
}
QList<uchar> DialoguePersonnage::nv_don_cs()const{
	return don_cs;
}
QString DialoguePersonnage::nv_don_obj()const{
	return don_obj;
}
Pokemon DialoguePersonnage::nv_don_pk()const{
	return don_pk;
}

void DialoguePersonnage::activer_bouton(int _indice){
	b_editer_achat_objets->setEnabled(false);
	b_editer_achat_ct->setEnabled(false);
	b_editer_don_cs->setEnabled(false);
	b_editer_don_obj->setEnabled(false);
	b_editer_don_pk->setEnabled(false);
	if(_indice==DialoguePersonnage::ACHAT_OBJS){
		b_editer_achat_objets->setEnabled(true);
	}else if(_indice==DialoguePersonnage::ACHAT_CTS){
		b_editer_achat_ct->setEnabled(true);
	}else if(_indice==DialoguePersonnage::DON_CS){
		b_editer_don_cs->setEnabled(true);
	}else if(_indice==DialoguePersonnage::DON_OBJS){
		b_editer_don_obj->setEnabled(true);
	}else if(_indice==DialoguePersonnage::DON_PK){
		b_editer_don_pk->setEnabled(true);
	}else{
		achat_objets.clear();
		achat_ct.clear();
		don_cs.clear();
		don_obj="";
		don_pk=Pokemon();
	}
}

void DialoguePersonnage::maj_achat_objets(){
	DialogueAchats *dial_=new DialogueAchats(langue,this);
	if(!achat_objets.isEmpty()){
		dial_->maj_liste(achat_objets);
	}
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		achat_objets=dial_->nv_liste();
		achat_ct.clear();
		don_cs.clear();
		don_obj="";
		don_pk=Pokemon();
	}
	delete dial_;
	dial_=NULL;
}

void DialoguePersonnage::maj_achat_capsules(){
	DialogueCapsules *dial_=new DialogueCapsules(langue,true,this);
	if(!achat_ct.isEmpty()){
		dial_->maj_liste(achat_ct);
	}
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		achat_objets.clear();
		achat_ct=dial_->nv_liste();
		don_cs.clear();
		don_obj="";
		don_pk=Pokemon();
	}
	delete dial_;
	dial_=NULL;
}

void DialoguePersonnage::maj_don_capsules(){
	DialogueCapsules *dial_=new DialogueCapsules(langue,false,this);
	if(!don_cs.isEmpty()){
		dial_->maj_liste(don_cs);
	}
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		achat_objets.clear();
		achat_ct.clear();
		don_cs=dial_->nv_liste();
		don_obj="";
		don_pk=Pokemon();
	}
	delete dial_;
	dial_=NULL;
}

void DialoguePersonnage::maj_don_objets(){
	DialogueObjet *dial_=new DialogueObjet(langue,this);
	if(don_obj!=""){
		dial_->editer_objet(don_obj);
	}
	dial_->exec();
	QString nv_obj_=dial_->nv_obj();
	bool accepter_=dial_->result()==QDialog::Accepted;
	if(nv_obj_!=""&&accepter_){
		don_obj=nv_obj_;
	}
	delete dial_;
	dial_=NULL;
}

void DialoguePersonnage::maj_don_pokemon(){
	DialoguePkCombat *dial_=new DialoguePkCombat(langue,DialoguePkCombat::PK_DONNE,this,DialoguePkCombat::RIEN);
	Pokemon *pk_=&don_pk;
	if(*don_pk.adr_nom()!=""){
		dial_->maj_pk_edite(pk_);
	}
	dial_->exec();
	bool rejet_=dial_->rejete();
	if(!rejet_){
		don_pk=dial_->nv_pk();
	}
	delete dial_;
	dial_=NULL;
}

bool DialoguePersonnage::rejete()const{
	return rejeter;
}

void DialoguePersonnage::acceptation(){
	rejeter=false;
	close();
}

void DialoguePersonnage::closeEvent(QCloseEvent* _ev){
	if(rejeter){
		return;
	}
	QString erreur_;
	int i_=0;
	QList<QString> cles_langue_=Import::_langues_.cles();
	foreach(QLineEdit *l,noms){
		QStringList args_;
		args_<<Import::_langues_.valeur(cles_langue_[i_])[langue];
		if(l->text()==""){
			erreur_+=Utilitaire::formatter(traduire("PAS_NOM"),args_)+"\n";
		}
		i_++;
	}
	int somme_c_=orientation_h->value()*orientation_h->value()+orientation_v->value()*orientation_v->value();
	if(somme_c_!=1){
		erreur_+=traduire("ERR_ORIENTATION")+"\n";
	}
	if(erreur_!=""){
		_ev->ignore();
		rejeter=true;
		QMessageBox::information(this,traduire("ERREUR"),erreur_);
	}
}

DialoguePersonnage::~DialoguePersonnage(){
	delete choix;
	choix=NULL;
}


