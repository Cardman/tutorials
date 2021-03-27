from cust_points import Point
from vecteur import Vecteur
from tri_constantes import LinearDirection
#import math

class Polygone:

    def __init__(self):
        self.pts=[]
    def getConvex(self) :
        p_ = Polygone();
        if len(self.pts) == 0 :
            return p_
        return self.getConvexHull(p_)
    def getConvexHull(self,_sortie) :
        cust_ = self.pts[0]
        for p in self.pts :
            if Polygone.hasToRedef(cust_, p) :
                cust_ = p
        endPoint_ = self.pts[0]
        nbVertices_ = len(self.pts);
        while len(_sortie.pts) == 0 or endPoint_ is not _sortie.pts[0] :
            _sortie.pts.append(cust_)
            endPoint_ = self.pts[0]
            for j in range(nbVertices_):
                if endPoint_ is cust_ :
                    endPoint_ = self.pts[j]
                else :
                    b_ = _sortie.pts[len(_sortie.pts)-1];
                    affineSegment_ = Vecteur(b_, endPoint_)
                    affinePoint_ = Vecteur(self.pts[j], endPoint_)
                    currentSide_ = Polygone.getSide(affineSegment_, affinePoint_)
                    if currentSide_ == LinearDirection.LEFT :
                        endPoint_ = self.pts[j]
            cust_ = endPoint_
        return _sortie


    @staticmethod
    def hasToRedef(_cust,_p) :
        return _p.x < _cust.x or (_p.x == _cust.x and _p.y < _cust.y)

    @staticmethod
    def getSide(_a,_b):
        x_ = _a.det(_b)
        if x_ < 0 :
            return LinearDirection.LEFT
        if x_ > 0 :
            return LinearDirection.RIGHT
        return LinearDirection.NONE
    def __repr__(self):
        return str(self.pts)


if __name__ == "__main__":
    polygone=Polygone()
    polygone.pts.append(Point(0, 0))
    polygone.pts.append(Point(0, 1))
    polygone.pts.append(Point(1, 1))
    polygone.pts.append(Point(1, 2))
    polygone.pts.append(Point(2, 2))
    polygone.pts.append(Point(2, 0))
    print(polygone.getConvex())