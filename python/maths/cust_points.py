from fractions import Fraction

class Point:
    def __init__(self,_one,_two):
        self.x=_one
        self.y=_two
    def eq(self,_obj):
        if _obj.x != self.x:
            return False
        return _obj.y == self.y
    @staticmethod
    def distanceCarree(one,two):
        return (one.x - two.x) * (one.x - two.x) + (one.y - two.y) * (one.y - two.y);
    def __repr__(self):
        return str(self.x)+","+str(self.y)


