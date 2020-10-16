class ExempleStatic:
    def afficher():
        print("Contenu d'une méthode statique")
    afficher = staticmethod(afficher)

ExempleStatic.afficher()