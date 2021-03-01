from fractions import Fraction
import random
import sys
from cust_points import Point
from arete import Arete
from site_info import SiteInfo
#import math

class Triangle:

    def __init__(self,_one,_two,_three):
        self.one=_one
        self.two=_two
        self.three=_three
    def centreCirconscrit(self):
        bpx_ = self.two.x - self.one.x;
        cpx_ = self.three.x - self.one.x;
        bpy_ = self.two.y - self.one.y;
        cpy_ = self.three.y - self.one.y;
        dp_ = 2*(bpx_ * cpy_ - bpy_ * cpx_);
        x_ = cpy_ * (bpx_ * bpx_ + bpy_ * bpy_);
        x_ -= bpy_ * (cpx_ * cpx_ + cpy_ * cpy_);
        y_ = bpx_ * (cpx_ * cpx_ + cpy_ * cpy_);
        y_ -= cpx_ * (bpx_ * bpx_ + bpy_ * bpy_);
        x_ += self.one.x * dp_;
        y_ += self.one.y * dp_;
        return Point(Fraction(x_,dp_), Fraction(y_,dp_))
    def centreGravite(self):
        x_ = self.one.x + self.two.x + self.three.x;
        y_ = self.one.y + self.two.y + self.three.y;
        return Point(Fraction(x_,3), Fraction(y_,3))
    def dansCercle(self,pt):
        omega = self.centreCirconscrit();
        return Point.distanceCarree(self.one,omega) >= Point.distanceCarree(pt,omega)
    def dansCercleStrict(self,pt):
        omega = self.centreCirconscrit();
        return Point.distanceCarree(self.one,omega) > Point.distanceCarree(pt,omega)

if __name__ == "__main__":
    tri=Triangle(Point(Fraction(1,1),Fraction(1,1)),Point(Fraction(3,1),Fraction(2,1)),Point(Fraction(2,1),Fraction(4,1)))
    pt =tri.centreCirconscrit()
    print(pt.x)
    print(pt.y)
    print(tri.dansCercle(Point(Fraction(-1,1),Fraction(3,1))))
    print(tri.dansCercle(Point(Fraction(2,1),Fraction(3,1))))
    print(tri.dansCercleStrict(Point(Fraction(0,1),Fraction(3,1))))
    print(tri.dansCercleStrict(Point(Fraction(2,1),Fraction(3,1))))
    print(Arete(Point(Fraction(2,1),Fraction(3,1)),Point(Fraction(2,1),Fraction(2,1))).egal(Arete(Point(Fraction(2,1),Fraction(3,1)),Point(Fraction(2,1),Fraction(2,1)))))#2
    print(Arete(Point(Fraction(2,1),Fraction(3,1)),Point(Fraction(2,1),Fraction(2,1))).meme(Arete(Point(Fraction(2,1),Fraction(3,1)),Point(Fraction(2,1),Fraction(2,1)))))#2
    
    
    one_ = Point(1, 0);
    two_ = Point(3, 2);
    three_ = Point(0, 0);
    four_ = Point(4, 2);
    oneEd_ = Arete(one_, two_);
    twoEd_ = Arete(three_, four_);
    print(twoEd_.intersectNotContains(oneEd_));
    one_ = Point(3, 2);
    two_ = Point(5, 4);
    three_ = Point(0, 0);
    four_ = Point(4, 2);
    oneEd_ = Arete(one_, two_);
    twoEd_ = Arete(three_, four_);
    print(twoEd_.intersectNotContains(oneEd_));

