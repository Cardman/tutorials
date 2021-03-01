def decomposer(entier, divise_par):
    """Cette fonction retourne la partie entière et le reste de
    entier / divise_par"""

    p_e = entier // divise_par
    reste = entier % divise_par
    return p_e, reste

partie_entiere, reste = decomposer(20, 3)
print(partie_entiere)
print(reste)