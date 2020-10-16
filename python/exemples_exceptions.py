numerateur = 1
denominateur = 1
try:
    resultat = numerateur // denominateur
except ZeroDivisionError as e:
    print("La variable denominateur est égale à 0:",e)
else:
    print("Le résultat obtenu est", resultat)
denominateur = 0
try:
    resultat = numerateur // denominateur
except ZeroDivisionError as e:
    print("La variable denominateur est égale à 0:",e)
else:
    print("Le résultat obtenu est", resultat)

def mon_finally(_numerateur,_denominateur,_ent):
    try:
        resultat_ = _numerateur // _denominateur
        print(_ent)
        return
    except ZeroDivisionError as e:
        print("La variable denominateur est égale à 0:",e)
    else:
        print("Le résultat obtenu est", resultat_)
    finally:
        print("Et finallement: ",_ent)

mon_finally(1,1,1)
mon_finally(1,0,2)