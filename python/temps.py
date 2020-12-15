import time
import datetime
print(time.time())

debut = time.time()
# On attend quelques secondes avant de taper la commande suivante
fin = time.time()
print(debut, fin)
print(debut < fin)
print(fin - debut) # Combien de secondes entre debut et fin ?
print(time.localtime())


temps = time.localtime(debut)
print(temps)
ts_debut = time.mktime(temps)
print(ts_debut)
#time.sleep(3.5) # Faire une pause pendant 3,5 secondes

aujourdhui = datetime.date.today()
print(aujourdhui)
print(datetime.date(2011, 2, 14))
print(datetime.date.fromtimestamp(time.time())) # Équivalent à date.today
print(datetime.date(2011, 2, 14))
print(datetime.datetime(2011, 2, 14, 5, 8, 22, 359000))
