parametres = {"sep":" >> ", "end":" -\n"}
print("Voici", "un", "exemple", "d'appel", **parametres)

def nom_fct(*params):
    print(params)
    print(type(params))

params_ = [1,2]
nom_fct(*params_)#(1, 2)
print("\n")
nom_fct(params_)#([1, 2],)
print("\n")
nom_fct(5,6)#(5, 6)
print("\n")
nom_fct()#()
print("\n")
