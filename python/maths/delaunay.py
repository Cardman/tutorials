from cust_points import Point
from arete import Arete
from site_info import SiteInfo
from site_point import SitePoint
from vecteur import Vecteur
from tri_constantes import IndexConstants,TriConstantes
from cust_polygon import Polygone
from cust_triangles import Triangle
from functools import cmp_to_key,reduce;

class Delaunay:
    def __init__(self):
        self.triangles = []
        self.enveloppe = Polygone()
        self.aretes = {}
        self.ptsSuiv = {}
        self.trisSuiv = {}
    def appliquer(self,pts):
        if len(pts) < 3 :
            return None
        if len(pts) == 3 :
            vOne_ = Vecteur(pts[0], pts[1]);
            vTwo_ = Vecteur(pts[0], pts[2]);
            if vOne_.det(vTwo_) == 0 :
                return None
            self.triangles.append(Triangle(pts[0], pts[1], pts[2]));
            return None
        extendedEdge_ = Delaunay.getExtendedEdge(pts);
        xMax_ = extendedEdge_.y.x
        xMin_ = extendedEdge_.x.x
        yMax_ =  extendedEdge_.y.y
        yMin_ = extendedEdge_.x.y
        self.loopMain(pts, xMax_, xMin_, yMax_, yMin_);
        self.enveloppe = self.enveloppe.getConvex()
        self.ptsSuiv = self.calculateNextPoints()
        self.aretes = self.evaluateEdges()
        return None
    
    def loopMain(self, _points, _xMax, _xMin, _yMax, _yMin) :
        firstPoint_ = Point(_xMin, _yMin);
        secondPoint_ = Point(_xMax + _xMax - _xMin, _yMin);
        thirdPoint_ = Point(_xMin, _yMax + _yMax - _yMin);
        superTriangle_ = Triangle(firstPoint_, secondPoint_, thirdPoint_);
        self.triangles.append(superTriangle_);
        for c in _points:
            self.enveloppe.pts.append(c);
            badTriangles_ = self.filterTriangles2(c);
            edges_ = Delaunay.getEdgesFromBadTriangles(badTriangles_);
            for t in badTriangles_:
                self.triangles.remove(t);
            for e in edges_:
                self.triangles.append(Triangle(e.x, e.y, c));
        badTriangles_ = self.filterTriangles(superTriangle_);
        for b in badTriangles_:
            self.triangles.remove(b);

    @staticmethod
    def getEdgesFromBadTriangles(_badTriangles) :
        edges_ = []
        for t in _badTriangles:
            for e in t.aretes() :
                if Delaunay.addEdge(_badTriangles, t, e):
                    edges_.append(e);
        return edges_;
    
    @staticmethod
    def addEdge(_badTriangles, _triangle, _edge) :
        addEdge_ = True;
        for o in _badTriangles :
            if o is not _triangle :
                if Delaunay.foundSameEdge(_edge, o) :
                    addEdge_ = False;
                    break;
        return addEdge_;

    @staticmethod
    def foundSameEdge(_edge, _o) :
        break_ = False
        for e_ in _o.aretes():
            if _edge.meme(e_) :
                break_ = True;
                break;
        return break_;
    def filterTriangles2(self,_c):
        badTriangles_ = []
        for t in self.triangles:
            if t.dansCercle(_c) :
                badTriangles_.append(t)
            
        return badTriangles_

    @staticmethod
    def getExtendedEdge(_points) :
        xMax_ = _points[0].x
        xMin_ = _points[0].x
        yMax_ = _points[0].y
        yMin_ = _points[0].y
        for c in _points :
            if (c.x < xMin_) :
                xMin_ = c.x;
            if (c.x > xMax_) :
                xMax_ = c.x;
            if (c.y < yMin_) :
                yMin_ = c.y;
            if (c.y > yMax_) :
                yMax_ = c.y;
        xMin_-=1
        yMin_-=1
        xMax_+=1
        yMax_+=1
        return Arete(Point(xMin_,yMin_),Point(xMax_,yMax_))
    
    def filterTriangles(self, _superTriangle) :
        badTriangles_ = []
        for b in self.triangles :
            if Delaunay.hasToRemove(_superTriangle, b) :
                badTriangles_.append(b);
        return badTriangles_;
    @staticmethod
    def hasToRemove(_superTriangle, _b) :
        remove_ = False;
        for s in _superTriangle.pts():
            for p in _b.pts():
                if s is p:
                    remove_ = True
                    break;
            if remove_ :
                break;
        return remove_;
    
    def calculateNextPoints(self) :
        id_ = {}
        list_ = []
        self.feedListPt(list_);
        for p in list_ :
            contained_ = self.isContainedHull(p);
            all_ = {}
            allKeys_ = []
            self.feedMapping(p, all_,allKeys_);
            next_ = all_.keys()
            first_ = allKeys_[0]
            once_ = []
            for k, v in all_.items() :
                if v != IndexConstants.ONE_ELEMENT :
                    continue
                once_.append(k);
            if len(once_) > 0 and contained_ :
                eOne_ = once_[0]
                eTwo_ = once_[len(once_)-1]
                v_ = Vecteur(p, eTwo_);
                sOne_ = SitePoint(eOne_, p, v_);
                v_ = Vecteur(p, eOne_);
                sTwo_ = SitePoint(eTwo_, p, v_);
                if SiteInfo.compare(sOne_,sTwo_) == TriConstantes.NO_SWAP_SORT :
                    first_ = eTwo_;
                else :
                    first_ = eOne_;
            Delaunay.putPts(id_, p, next_, first_);
        return id_;
    
    def evaluateEdges(self) :
        id_ = {}
        for (k,v) in self.ptsSuiv.items() :
            k_ = k;
            v_ = v;
            p_ = Polygone();
            self.fetchCircumCenters(k_, v_, p_);
            edges_ = []
            len_ = len(p_.pts);
            for i in range(len_):
                one_ = p_.pts[i];
                two_ = p_.pts[(i+1)%len_];
                e_ = Arete(one_, two_);
                edges_.append(e_);
            id_[k_]= edges_;
        
        return id_;

    def isContainedHull(self,_k) :
        contained_ = False;
        for c in self.enveloppe.pts:
            if c is _k :
                contained_ = True;
                break;
        return contained_;

    @staticmethod
    def putPts(_id, _p, _next, _first) :
        sites_ = []
        v_ = Vecteur(_p, _first);
        for n in _next:
            sites_.append(SitePoint(n, _p, v_))
        pts_ = []
        for s in sorted(sites_,key=cmp_to_key(SiteInfo.compare)):
            pts_.append(s.point)
        _id[_p] = pts_
    
    def feedListPt(self,_list) :
        for t in self.triangles:
            for p in t.pts() :
                if not(Delaunay.isFoundPoint(p, _list)):
                    _list.append(p);
    def feedMapping(self, _p, _all,_allKeys) :
        for t in self.triangles :
            if not(Delaunay.isFoundPoint(_p, t.pts())) :
                continue;
            for n in t.pts():
                if n is _p :
                    continue;
                if n in _all:
                    _all[n] = _all[n] + 1
                else :
                    _all[n] = 1
                    _allKeys.append(n)
    @staticmethod
    def isFoundPoint(_p, _points) :
        found_ = False;
        for n in _points:
            if n is _p:
                found_ = True;
                break;
        
        return found_

    def fetchCircumCenters(self, _k, _v, _p) :
        len_ = len(_v);
        for i in range(len_):
            one_ = _v[i];
            two_ = _v[(i + 1) % len_];
            for t in self.triangles:
                nbPoints_ = Delaunay.getNbPoints(_k, one_, two_, t);
                if (nbPoints_ == 3) :
                    c_ = t.centreCirconscrit();
                    _p.pts.append(c_);
                    break;

    @staticmethod
    def getNbPoints(_k, _one, _two, _t) :
        nbPoints_ = 0;
        for p in _t.pts() :
            if (p is _k) :
                nbPoints_+=1

            if (p is _one) :
                nbPoints_+=1

            if (p is _two) :
                nbPoints_+=1

        
        return nbPoints_


if __name__ == "__main__":
    liste=[]
    liste.append(Point(0, 0))
    liste.append(Point(0, 1))
    liste.append(Point(1, 1))
    liste.append(Point(1, 2))
    liste.append(Point(2, 2))
    liste.append(Point(2, 0))
    delaunay = Delaunay()
    delaunay.appliquer(liste)
    print(delaunay.triangles)
    print(delaunay.enveloppe)
    print(delaunay.ptsSuiv)
    print(delaunay.aretes)