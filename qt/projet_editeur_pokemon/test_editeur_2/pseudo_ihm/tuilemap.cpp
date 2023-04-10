#include "pseudo_ihm/tuilemap.h"

TuileMap::TuileMap(const QImage& _img){
	image=_img;
}

void TuileMap::maj_image(const QImage& _img){
	image=_img;
}

QImage TuileMap::imag()const{
	return image;
}

void TuileMap::affecter(TuileMap* _autre){
	image=_autre->image;
}

void TuileMap::reinit(){
	image=Import::_tuile_invalide_;
}


