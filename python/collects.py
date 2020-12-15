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