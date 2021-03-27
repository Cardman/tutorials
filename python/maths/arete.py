from vecteur import Vecteur
from site_info import SiteInfo
from site_point import SitePoint
from tri_constantes import IndexConstants
from functools import cmp_to_key;

class Arete:
    def __init__(self,_one,_two):
        self.x=_one
        self.y=_two
    
    def meme(self, autre):
        if self.x is autre.x and self.y is autre.y :
            return True
        if self.x is autre.y :
            return self.y is autre.x
        return False
    def egal(self, autre) :
        if self.x.eq(autre.x) and self.y.eq(autre.y) :
            return True
        if self.x.eq(autre.y) :
            return self.y.eq(autre.x)
        return False
    def intersectNotContains(self, _other) :
        return self.intersectBoundsOpt(_other,False);

    def intersectNotContainsBound(self,_other) :
        points_ = []
        points_.append(self.x);
        points_.append(self.y);
        points_.append(_other.x);
        points_.append(_other.y);
        if self.x.eq(_other.x) and not(self.y.eq(_other.y)) :
            return False;
        if self.x.eq(_other.y) and not(self.y.eq(_other.x)) :
            return False;
        if self.y.eq(_other.x) and not(self.x.eq(_other.y)) :
            return False;
        if self.y.eq(_other.y) and not(self.x.eq(_other.x)) :
            return False;
        return self.procLines(_other, points_);

    def procLines(self, _other, _points) :
        if (self.containsPoint(_other.y)) :
            return True;
        if (self.containsPoint(_other.x)) :
            return True;
        if (_other.containsPoint(self.x)) :
            return True;
        if (_other.containsPoint(self.y)) :
            return True;
        return Arete.lookForIntersectEdges(_points);

    @staticmethod
    def lookForIntersectEdges(_points) :
        index_ = IndexConstants.FIRST_INDEX;
        for p in _points :
            others_ = []
            if index_ <= IndexConstants.SECOND_INDEX :
                next_ = Arete.getNext(index_)
                nextOthOne_ = IndexConstants.SECOND_INDEX + IndexConstants.ONE_ELEMENT
                nextOthTwo_ = nextOthOne_ + IndexConstants.ONE_ELEMENT
            else :
                next_ = Arete.getNext2(index_);
                nextOthOne_ = IndexConstants.FIRST_INDEX
                nextOthTwo_ = IndexConstants.SECOND_INDEX
            sites_ = Arete.getSites(_points, p, others_, next_, nextOthOne_, nextOthTwo_)
            if Arete.noIntersect(sites_) :
                return False;
            index_+=1;
        return True;

    @staticmethod
    def getNext2(_index) :
        if _index == IndexConstants.SECOND_INDEX + IndexConstants.ONE_ELEMENT :
            next_ = _index + IndexConstants.ONE_ELEMENT;
        else :
            next_ = _index - IndexConstants.ONE_ELEMENT;
        return next_;

    @staticmethod
    def getNext( _index) :
        if _index == IndexConstants.FIRST_INDEX :
            next_ = IndexConstants.SECOND_INDEX;
        else :
            next_ = IndexConstants.FIRST_INDEX;
        return next_;

    @staticmethod
    def getSites(_points,  _p,  _others, _next, _nextOthOne, _nextOthTwo) :
        o_ = _points[_next]
        _others.append(_points[_nextOthOne])
        _others.append(_points[_nextOthTwo])
        sites_ = []
        v_ = Vecteur(_p, o_);
        for n in _others :
            sites_.append(SitePoint(n, _p, v_));
        return sorted(sites_,key=cmp_to_key(SiteInfo.compare))

    @staticmethod
    def noIntersect(_sites) :
        return _sites[0].info.nb >= SiteInfo.QUAD_THREE or _sites[len(_sites)-1].info.nb < SiteInfo.QUAD_THREE;

    def intersect(self,_other): 
        return self.intersectBoundsOpt(_other,True);

    def intersectBoundsOpt(self,_other, _nonStrict) :
        points_ = []
        points_.append(self.x)
        points_.append(self.y)
        points_.append(_other.x)
        points_.append(_other.y)
        if (self.containsPoint(_other.y)) :
            return _nonStrict;
        if (_other.containsPoint(self.x)) :
            return _nonStrict;
        if (_other.containsPoint(self.y)) :
            return _nonStrict;
        if (self.containsPoint(_other.x)) :
            return _nonStrict;
        return self.lookForIntersectEdges(points_);

    def containsPoint(self, _c) :
        one_ = Vecteur(self.x, _c)
        two_ = Vecteur(self.y, _c)
        return one_.det(two_) == 0 and one_.scal(two_) <= 0
    def __repr__(self):
        return str(self.x)+";"+str(self.y)


