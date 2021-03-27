from tri_constantes import TriConstantes

class SiteInfo:
    QUAD_ONE = 1
    QUAD_TWO = 2
    QUAD_THREE = 3
    QUAD_FOUR = 4
    def __init__(self):
        self.nb=0
        self.scal=0
        self.norme=0
    
    @staticmethod
    def compare(_one, _two):
        if (_one.info.nb < _two.info.nb) :
            return TriConstantes.NO_SWAP_SORT;
        if (_one.info.nb > _two.info.nb) :
            return TriConstantes.SWAP_SORT;
        firstMember_ = _one.info.scal * _one.info.scal * _two.info.norme
        secondMember_ = _two.info.scal * _two.info.scal * _one.info.norme
        if _one.info.nb == SiteInfo.QUAD_ONE or _one.info.nb == SiteInfo.QUAD_THREE :
            if firstMember_ > secondMember_ :
                return TriConstantes.NO_SWAP_SORT
            if firstMember_ < secondMember_ :
                return TriConstantes.SWAP_SORT
        else :
            if firstMember_ < secondMember_ :
                return TriConstantes.NO_SWAP_SORT
            if firstMember_ > secondMember_ :
                return TriConstantes.SWAP_SORT
        return TriConstantes.EQ_CMP;


