from operator import itemgetter
from operator import attrgetter
class Duree:
    """Classe contenant des durées sous la forme d'un nombre de minutes
    et de secondes"""
    
    def __init__(self, min=0, sec=0):
        """Constructeur de la classe"""
        self.min = min # Nombre de minutes
        self.sec = sec # Nombre de secondes
    def __str__(self):
        """Affichage un peu plus joli de nos objets"""
        return "{0:02}:{1:02}".format(self.min, self.sec)
    def __add__(self, objet_a_ajouter):
        """L'objet à ajouter est un entier, le nombre de secondes"""
        nouvelle_duree = Duree()
        # On va copier self dans l'objet créé pour avoir la même durée
        nouvelle_duree.min = self.min
        nouvelle_duree.sec = self.sec
        # On ajoute la durée
        nouvelle_duree.sec += objet_a_ajouter
        # Si le nombre de secondes >= 60
        if nouvelle_duree.sec >= 60:
            nouvelle_duree.min += nouvelle_duree.sec // 60
            nouvelle_duree.sec = nouvelle_duree.sec % 60
        # On renvoie la nouvelle durée
        return nouvelle_duree
    def __radd__(self, objet_a_ajouter):
        """Cette méthode est appelée si on écrit 4 + objet et que
        le premier objet (4 dans cet exemple) ne sait pas comment ajouter
        le second. On se contente de rediriger sur __add__ puisque,
        ici, cela revient au même : l'opération doit avoir le même résultat,
        posée dans un sens ou dans l'autre"""
        
        return self + objet_a_ajouter
    def __iadd__(self, objet_a_ajouter):
        """L'objet à ajouter est un entier, le nombre de secondes"""
        # On travaille directement sur self cette fois
        # On ajoute la durée
        self.sec += objet_a_ajouter
        # Si le nombre de secondes >= 60
        if self.sec >= 60:
            self.min += self.sec // 60
            self.sec = self.sec % 60
        # On renvoie self
        return self

print(Duree(2,30))
d1 = Duree(3, 5)
print(d1 + 4)
print(4 + d1)
d1 = Duree(12, 8)
print(d1)
d2 = d1 + 54 # d1 + 54 secondes
print(d2)
d1 = Duree(8, 5)
d1 += 128
print(d1)

etudiants = [
    ("Clément", 14, 16),
    ("Charles", 12, 15),
    ("Oriane", 14, 18),
    ("Thomas", 11, 12),
    ("Damien", 12, 15),
]
print(sorted(etudiants))
print(sorted(etudiants, key=lambda colonnes: colonnes[2]))


class Etudiant:

    """Classe représentant un étudiant.

    On représente un étudiant par son prénom (attribut prenom), son âge
    (attribut age) et sa note moyenne (attribut moyenne, entre 0 et 20).

    Paramètres du constructeur :
        prenom -- le prénom de l'étudiant
        age -- l'âge de l'étudiant
        moyenne -- la moyenne de l'étudiant

    """

    def __init__(self, prenom, age, moyenne):
        self.prenom = prenom
        self.age = age
        self.moyenne = moyenne

    def __repr__(self):
        return "<Étudiant {} (âge={}, moyenne={})>".format(
                self.prenom, self.age, self.moyenne)

etudiants = [
    Etudiant("Clément", 14, 16),
    Etudiant("Charles", 12, 15),
    Etudiant("Oriane", 14, 18),
    Etudiant("Thomas", 11, 12),
    Etudiant("Damien", 12, 15),
]
print(sorted(etudiants, key=lambda etudiant: etudiant.moyenne))
print(sorted(etudiants, key=lambda etudiant: etudiant.age, reverse=True))
etudiants = [
    ("Clément", 14, 16),
    ("Charles", 12, 15),
    ("Oriane", 14, 18),
    ("Thomas", 11, 12),
    ("Damien", 12, 15),
]
print(sorted(etudiants, key=itemgetter(2)))
etudiants = [
    Etudiant("Clément", 14, 16),
    Etudiant("Charles", 12, 15),
    Etudiant("Oriane", 14, 18),
    Etudiant("Thomas", 11, 12),
    Etudiant("Damien", 12, 15),
]
print(sorted(etudiants, key=attrgetter("moyenne")))
print(sorted(etudiants, key=attrgetter("age", "moyenne")))


class LigneInventaire:

    """Classe représentant une ligne d'un inventaire de vente.

    Attributs attendus par le constructeur :
        produit -- le nom du produit
        prix -- le prix unitaire du produit
        quantite -- la quantité vendue du produit.

    """

    def __init__(self, produit, prix, quantite):
        self.produit = produit
        self.prix = prix
        self.quantite = quantite

    def __repr__(self):
        return "<Ligne d'inventaire {} ({}X{})>".format(
                self.produit, self.prix, self.quantite)

# Création de l'inventaire
inventaire = [
    LigneInventaire("pomme rouge", 1.2, 19),
    LigneInventaire("orange", 1.4, 24),
    LigneInventaire("banane", 0.9, 21),
    LigneInventaire("poire", 1.2, 24),
]
print(sorted(inventaire, key=attrgetter("prix", "quantite")))

inventaire.sort(key=attrgetter("quantite"), reverse=True)
print(sorted(inventaire, key=attrgetter("prix")))