#include "ihm/combat/etiquettes/imagecreaturecombat.h"
#include "serialisable/combat/creaturecombat.h"
#include "base_donnees/donnees.h"
#include "base_donnees/pokemon/fichepokemon.h"
#include <QMouseEvent>
#include <QGridLayout>
ImageCreatureCombat::ImageCreatureCombat(const Combattant& _cbt,const CreatureCombat& _cr_c,Donnees* _d){
	cbt=_cbt;
	QGridLayout *grid_=new QGridLayout();
	img_pk=new QLabel();
	QString genre_=_cr_c.genre_pk();
	if(_d->genres_non_assexues().contains(genre_)){
		if(genre_.startsWith("M")){
			if(_cbt.equipe()==(uchar)_d->val_ut()){
				img_pk->setPixmap(QPixmap::fromImage(_d->val_images_dos_m().valeur(_cr_c.fiche_pokemon(_d)->num())));
			}else{
				img_pk->setPixmap(QPixmap::fromImage(_d->val_images_face_m().valeur(_cr_c.fiche_pokemon(_d)->num())));
			}
		}else{
			if(_cbt.equipe()==(uchar)_d->val_ut()){
				img_pk->setPixmap(QPixmap::fromImage(_d->val_images_dos_f().valeur(_cr_c.fiche_pokemon(_d)->num())));
			}else{
				img_pk->setPixmap(QPixmap::fromImage(_d->val_images_face_f().valeur(_cr_c.fiche_pokemon(_d)->num())));
			}
		}
	}else{
		if(_cbt.equipe()==(uchar)_d->val_ut()){
			img_pk->setPixmap(QPixmap::fromImage(_d->val_images_dos_m().valeur(_cr_c.fiche_pokemon(_d)->num())));
		}else{
			img_pk->setPixmap(QPixmap::fromImage(_d->val_images_face_m().valeur(_cr_c.fiche_pokemon(_d)->num())));
		}
	}
	//img_pk->setPixmap(QPixmap::fromImage(_d->val_miniatures().valeur(_cr_c.fiche_pokemon(_d)->num())));//TODO attention images macro
	grid_->addWidget(img_pk,0,0);
	ico_objet=new QLabel();
	QString obj_=_cr_c.objet();
	if(obj_!=""){
		ico_objet->setPixmap(QPixmap::fromImage(_d->val_images_objets().valeur(obj_)));
	}
	grid_->addWidget(ico_objet,1,0);
	setLayout(grid_);
	setMinimumSize(100,150);
}

void ImageCreatureCombat::maj_cbt(const Combattant& _cbt){
	cbt=_cbt;
}

void ImageCreatureCombat::maj_img_pk(const QImage& _img){
	img_pk->setPixmap(QPixmap::fromImage(_img));
}

void ImageCreatureCombat::maj_ico_objet(const QImage& _img){
	ico_objet->setPixmap(QPixmap::fromImage(_img));
}

void ImageCreatureCombat::mouseReleaseEvent(QMouseEvent *){
	emit clic(cbt);
}
