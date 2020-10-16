from fractions import Fraction
import random
import sys

class Ints:


    def modCust(cls,_one,_two):
        return _one - _two * cls.quotCust(_one, _two)

    def quotCust(cls,_one,_two):
        if _two == -sys.maxsize - 1 :
            if _one >= 0 :
                return 0
            return 1
        if _one >= 0 :
            if _two >= 0 :
                return _one//_two
            return -(_one//(-_two))
        if _two <= 0 :
            if _one == -sys.maxsize - 1 :
                return (-(-_one+1))//(-_two)+1
            if (-_one) % (-_two) == 0 :
                return (-_one)//(-_two)
            return (-_one)//(-_two)+1
        if _one == -sys.maxsize - 1 :
            return -(-(-_one+1)//_two)-1
        if (-_one) % _two == 0 :
            return -((-_one)//_two)
        return -((-_one)//_two)-1

    modCust = classmethod(modCust)
    quotCust = classmethod(quotCust)

print(Ints.quotCust(7,3))#2
