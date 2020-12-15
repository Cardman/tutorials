class MaClasseMere1:
     def __init__(self, param):
        self.nom = param
class MaClasseMere2:
     def __init__(self, param):
        self.autre = param
class MaClasseHeritee(MaClasseMere1, MaClasseMere2):
    def __init__(self, param,param2,param3):
        MaClasseMere1.__init__(self,param)
        MaClasseMere2.__init__(self,param2)
        self.elt = param3
    def __str__(self):
        return self.nom+","+self.autre+","+self.elt

o=MaClasseHeritee("A","B","C")
print(o.nom)
print(o.autre)
print(o.elt)
print(o)