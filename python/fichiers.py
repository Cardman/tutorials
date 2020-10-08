
class Fichiers:
    def lire(cls,nom):
        mon_fichier = open(nom, "r")
        contenu = mon_fichier.read()
        mon_fichier.close()
        return contenu
    def ecrire(cls,nom,contenu):
        mon_fichier = open(nom, "w")
        mon_fichier.write(contenu)
        mon_fichier.close()
    lire = classmethod(lire)
    ecrire = classmethod(ecrire)

