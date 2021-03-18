def composition(f, g):
    """
    Renvoie la composee de deux fonctions f et g.
    >>> #from math import sin, cos
    >>> db = lambda v:2*v
    >>> sq = lambda v:v*v
    >>> f = composition(db, sq)
    >>> g = composition(sq, db)
    >>> [f(x) - g(x) for x in range(0, 3)]
    [0, -2, -8]
    """
    return lambda x: f(g(x))

if __name__ == "__main__":
    import doctest
    doctest.testmod()
#python exemple_doctest.py -v