from fractions import Fraction
import random
import sys
#import math

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
    def quotCustQuick(cls,_one,_two):
        if _two == -sys.maxsize - 1 :
            if _one >= 0 :
                return 0
            return 1
        if _one == -sys.maxsize - 1 :
            if _two <= 0 :
                return (-(-_one+1))//(-_two)+1
            return -(-(-_one+1)//_two)-1
        absDiv_ = abs(_two)
        absNb_ = abs(_one)
        q_ = absNb_ // absDiv_
        sigDiv_ = cls.signe(_two)
        q_ *= cls.signe(_one) * sigDiv_
        if _one >= 0:
            return q_
        m_ = absNb_ % absDiv_
        if m_ != 0:
            # sigDiv_ == 1 || sigDiv_ == -1
            q_ += -sigDiv_
        return q_
    def signe(cls,_one):
        if _one > 0:
            return 1
        if _one < 0:
            return -1
        return 0

    modCust = classmethod(modCust)
    quotCust = classmethod(quotCust)
    quotCustQuick = classmethod(quotCustQuick)
    signe = classmethod(signe)

#print(Ints.quotCust(7,3))#2
