import urllib.request
import json
import fichiers

def lire(site):
    response=urllib.request.urlopen(site)
    return json.loads(response.read())
def lireJson(nom):
    contenu=fichiers.Fichiers.lire(nom)
    return json.loads(contenu)

emp = lireJson("employees.json")
print(len(emp))
print(emp[0])
print(emp[0]["name"], emp[0]["title"])