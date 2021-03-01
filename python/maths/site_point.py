from fractions import Fraction
from tri_constantes import TriConstantes
from site_info import SiteInfo
from vecteur import Vecteur

class SitePoint:
    def __init__(self,_point,_first,_vect) :
        self.point = _point
        vect_ = Vecteur(_first, _point)
        det_ = _vect.det(vect_)
        scal_ = _vect.prodScal(vect_)
        self.info = SiteInfo()
        if (scal_ >= 0 and det_ <= 0) :
            self.info.nb=(SiteInfo.QUAD_ONE)
        elif (scal_ < 0 and det_ <= 0) :
            self.info.nb=(SiteInfo.QUAD_TWO)
        elif (scal_ <= 0) :
            #det_ < 0
            self.info.nb=(SiteInfo.QUAD_THREE)
        else :
            self.info.nb=(SiteInfo.QUAD_FOUR)
        self.info.norme=vect_.normeCarree()
        self.info.scal=scal_


