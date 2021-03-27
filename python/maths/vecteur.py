class Vecteur:
    def __init__(self,_one,_two):
        self.x=_two.x-_one.x
        self.y=_two.y-_one.y
    def prodScal(self,autre):
        return self.x * autre.x + self.y * autre.y
    def det(self,autre):
        return self.x * autre.y - self.y * autre.x
    def eq(self,_obj):
        if self.x != _obj.x:
            return False
        return self.y == _obj.y
    def normeCarree(self):
        return self.x * self.x + self.y * self.y

