import functools#functools.cmp_to_key
from fractions import Fraction

a=[i for i in range(10)]
liste_origine = [0, 1, 2, 3, 4, 5]
resultat=[nb * nb for nb in liste_origine]
print(resultat)
liste_origine = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
resultat=[nb for nb in liste_origine if nb % 2 == 0]
print(resultat)
b=[0]*10
d={"k":"v","k2":10}
print(d.items())
print(d.keys())
print(d.values())
d2={}
d2["k"]="v"
d2["k2"]=10
print(d2.items())
print(d2.keys())
print(d2.values())

d3={}
d3["k",1]="v"
d3["k2",2]=10
print(d3.items())
print(d3.keys())
print(d3.values())
d4={("k",1):"v",("k2",2):10}
print(d4.items())
print(d4.keys())
print(d4.values())

point2d=(10,20)
point3d=(10,20,30)
print(point2d)
print(point3d)
s=set(['a','b','c'])
print(s)

qtt_a_retirer = 7 # On retire chaque semaine 7 fruits de chaque sorte
fruits_stockes = [15, 3, 18, 21] # Par exemple 15 pommes, 3 melons...
res=[nb_fruits-qtt_a_retirer for nb_fruits in fruits_stockes if nb_fruits>qtt_a_retirer]
print(res)#[8, 11, 14]

inventaire = [
    ("pommes", 22),
    ("melons", 4),
    ("poires", 18),
    ("fraises", 76),
    ("prunes", 51),
]
print(inventaire)
# On change le sens de l'inventaire, la quantité avant le nom
inventaire_inverse = [(qtt, nom_fruit) for nom_fruit,qtt in inventaire]
print(inventaire_inverse)
# On n'a plus qu'à trier dans l'ordre décroissant l'inventaire inversé
# On reconstitue l'inventaire trié
inventaire = [(nom_fruit, qtt) for qtt,nom_fruit in sorted(inventaire_inverse, \
    reverse=True)]
print(inventaire)
# On change le sens de l'inventaire, la quantité avant le nom
inventaire_inverse = [(qtt, nom_fruit) for nom_fruit,qtt in inventaire]
print(inventaire_inverse)
# On trie l'inventaire inversé dans l'ordre décroissant
inventaire_inverse.sort(reverse=True)
print(inventaire_inverse)
# Et on reconstitue l'inventaire
inventaire = [(nom_fruit, qtt) for qtt,nom_fruit in inventaire_inverse]
print(inventaire)

placard = {"chemise":3, "pantalon":6, "tee shirt":7}
del placard["chemise"]
print(placard)
placard = {"chemise":3, "pantalon":6, "tee shirt":7}
print(placard.pop("chemise"))

print_2 = print # L'objet print_2 pointera sur la fonction print
print_2("Affichons un message")


def premier():
    print("Prems")

def deuxieme():
    print("Deb")

fonctions = {}
fonctions["premier"] = premier # on ne met pas les parenthèses
fonctions["deuxieme"] = deuxieme
fonctions["premier"]() # on essaye de l'appeler
fonctions["deuxieme"]() # on essaye de l'appeler

monens={0,1,2}
print(3 in monens)#False
print(monens.discard(3))#None
print(1 in monens)#True
print(monens.discard(1))#None
#print(monens[0])#erreur
cond=5
maval=12 if cond > 1 else 2
print(maval)#12
maval=12 if cond > 10 else 2
print(maval)#2

class MaClasse1:
    def __init__(self):
        self.champ1=1

class MaClasse2:
    def __init__(self):
        self.champ2=2

collect_cls=[MaClasse1(),MaClasse2()]
print(collect_cls[0].champ1)
print(collect_cls[1].champ2)
print()
mult = complex(1,2)*complex(1,2)
print(mult)
print(mult.real)
print(mult.imag)
mult = complex(Fraction(1),Fraction(2))*complex(Fraction(1),Fraction(2))
print(mult)
print(mult.real)
print(mult.imag)
print()
for e in filter(lambda x:x>2,[1,2,3,4]):
    print(e)
print()
for e in map(lambda x:x*2,[1,2,3,4]):
    print(e)
print()
print(functools.reduce(lambda x,y:x*y,[1,2,3,4]))
print(functools.reduce(lambda x,y:x*y,map(lambda x:x*2,[1,2,3,4])))
print(functools.reduce(lambda x,y:x*y,map(lambda x:x*2,filter(lambda x:x>2,[1,2,3,4]))))
print()
for e in map(lambda x,y:x*y*2,[1,2,3,4],[11,12,13,14]):
    print(e)
print()

class MaCmp:
    def __init__(self,nb):
        self.macmp=nb
    @staticmethod
    def utilcmp(val):
        return val.macmp
    @staticmethod
    def utilcmpopp(val):
        return -val.macmp
    @staticmethod
    def utilcmptwo(val,val2):
        return val.macmp-val2.macmp
    @staticmethod
    def utilcmpopptwo(val,val2):
        return val2.macmp-val.macmp
    def __repr__(self):#dev, utilise par les listes
        return str(MaCmp.utilcmp(self))
    def __str__(self):#client
        return str(self.macmp)

print(max([1,2,3,4]))
print(max(1,2,3,4))
print(max([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=lambda x:x.macmp)," >< ",\
    max([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=lambda x:-x.macmp))
print(max([],key=lambda x:x.macmp,default=MaCmp(5))," >< ",\
    max([],key=lambda x:-x.macmp,default=MaCmp(5)))
print(max(MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4),key=lambda x:x.macmp)," >< ",\
    max(MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4),key=lambda x:-x.macmp))
print()
print(max([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=MaCmp.utilcmp)," >< ",\
    max([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=MaCmp.utilcmpopp))
print(max([],key=lambda x:x.macmp,default=MaCmp(5))," >< ",\
    max([],key=lambda x:-x.macmp,default=MaCmp(5)))
print(max(MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4),key=MaCmp.utilcmp)," >< ",\
    max(MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4),key=MaCmp.utilcmpopp))
print()
print(min([1,2,3,4]))
print(min(1,2,3,4))
print(min([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=lambda x:x.macmp)," >< ",\
    min([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=lambda x:-x.macmp))
print(min([],key=lambda x:x.macmp,default=MaCmp(5))," >< ",\
    min([],key=lambda x:-x.macmp,default=MaCmp(5)))
print(min(MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4),key=lambda x:x.macmp)," >< ",\
    min(MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4),key=lambda x:-x.macmp))
print()
print(min([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=MaCmp.utilcmp)," >< ",\
    min([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=MaCmp.utilcmpopp))
print(min([],key=lambda x:x.macmp,default=MaCmp(5))," >< ",\
    min([],key=lambda x:-x.macmp,default=MaCmp(5)))
print(min(MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4),key=MaCmp.utilcmp)," >< ",\
    min(MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4),key=MaCmp.utilcmpopp))
print()
print()

class MaCollec:
    def __init__(self,ls):
        self.ls=ls
    def __iter__(self):
        return MonIter(self.ls)
    def __reversed__(self):
        return MonIterInv(self.ls)
    @staticmethod
    def concat(*mesArgs):
        out=""
        for a in mesArgs:
            out += str(a)+";"
        return out
class MonIter:
    def __init__(self,ls):
        self.ls=ls
        self.ind=0
    def __iter__(self):
        return self
    def __next__(self):
        if self.ind >= len(self.ls):
            raise StopIteration()
        val = self.ls[self.ind]
        self.ind+=1
        return val
class MonIterInv:
    def __init__(self,ls):
        self.ls=ls
        self.ind=-1
    def __iter__(self):
        return self
    def __next__(self):
        if self.ind < -len(self.ls):
            raise StopIteration()
        val = self.ls[self.ind]
        self.ind-=1
        return val

perso_iter = MaCollec([1,2,3,4])
for i in perso_iter:
    print(i)
print()
for i in reversed(perso_iter):
    print(i)
print()
print()
print(sorted([MaCmp(4),MaCmp(2),MaCmp(3),MaCmp(1)],key=lambda x:x.macmp)," >< ",\
    sorted([MaCmp(4),MaCmp(2),MaCmp(3),MaCmp(1)],key=lambda x:-x.macmp))
print(sorted([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=MaCmp.utilcmp)," >< ",\
    sorted([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=MaCmp.utilcmpopp))
print(sorted([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=functools.cmp_to_key(MaCmp.utilcmptwo))," >< ",\
    sorted([MaCmp(1),MaCmp(2),MaCmp(3),MaCmp(4)],key=functools.cmp_to_key(MaCmp.utilcmpopptwo)))

for i,x in enumerate([15,25,32,41]):
    print(i,",",x)
liste_paires = [(i, x) for i,x in enumerate([15,25,32,41])]
for p in liste_paires:
    print(p[0],",",p[1])

for p in [(i, x) for i,x in enumerate([15,25,32,41])]:
    print(p[0],",",p[1])

print()
print(MaCmp.utilcmp(val=MaCmp(nb=12)))
print()
print("string"[-1])
print()
a = {'a', 'b', 'c'}
b = {'d', 'e', 'f'}
a.update(b)
print(a)
print()
print(MaCollec.concat(1,2,3,4,5,6))