ma_liste = [1, 2, 3]
for element in ma_liste:
    print(element)

ma_chaine = "test"
iterateur_de_ma_chaine = iter(ma_chaine)
print(next(iterateur_de_ma_chaine))
print(next(iterateur_de_ma_chaine))
print(next(iterateur_de_ma_chaine))
print(next(iterateur_de_ma_chaine))
try:
    print(next(iterateur_de_ma_chaine))
except:
    pass

class RevStr(str):
    
    def __iter__(self):
        return ItRevStr(self)

class ItRevStr:
    def __init__(self, chaine_a_parcourir):
        self.chaine_a_parcourir = chaine_a_parcourir
        self.position = len(chaine_a_parcourir)
    def __next__(self):
        
        if self.position == 0: # Fin du parcours
            raise StopIteration
        self.position -= 1
        return self.chaine_a_parcourir[self.position]
ma_chaine = RevStr("Bonjour")
print(ma_chaine)
for lettre in ma_chaine:
    print(lettre)

def mon_generateur():
    """Notre premier générateur. Il va simplement renvoyer 1, 2 et 3"""
    yield 1
    yield 2
    yield 3

print("\n")
mon_iterateur = iter(mon_generateur())
print(next(mon_iterateur))
print(next(mon_iterateur))
print(next(mon_iterateur))
try:
    print(next(mon_iterateur))
except:
    pass
print("\n")
for nombre in mon_generateur(): # Attention on exécute la fonction
    print(nombre)
print("\n")
def intervalle(borne_inf, borne_sup):
    """Générateur parcourant la série des entiers entre borne_inf et borne_sup.
    
    Note: borne_inf doit être inférieure à borne_sup"""
    
    borne_inf += 1
    while borne_inf < borne_sup:
        print("gestion de ",borne_inf)
        yield borne_inf
        borne_inf += 1
print("\n")
for nombre in intervalle(5, 10):
    print(nombre)
print("\n")
generateur = intervalle(5, 20)
for nombre in generateur:
    if nombre > 17:
        generateur.close() # Interruption de la boucle
    print(nombre)

def intervalle2(borne_inf, borne_sup):
    """Générateur parcourant la série des entiers entre borne_inf et borne_sup.
    Notre générateur doit pouvoir "sauter" une certaine plage de nombres
    en fonction d'une valeur qu'on lui donne pendant le parcours. La
    valeur qu'on lui passe est la nouvelle valeur de borne_inf.
    
    Note: borne_inf doit être inférieure à borne_sup"""
    borne_inf += 1
    while borne_inf < borne_sup:
        valeur_recue = (yield borne_inf)
        if valeur_recue is not None: # Notre générateur a reçu quelque chose
            borne_inf = valeur_recue
        borne_inf += 1

generateur = intervalle2(10, 25)
for nombre in generateur:
    if nombre == 15: # On saute à 20
        generateur.send(20)
    print(nombre, end=" ")