from fractions import Fraction
import random
import sys

print(sys.argv)
if len(sys.argv) >= 2:
    fr = Fraction(sys.argv[1])
    print(sys.argv[1],"=",fr)
un_demi = Fraction(1, 2)
print(un_demi)
un_quart = Fraction('1/4')
print(un_quart)
autre_fraction = Fraction(-5, 30)
print(autre_fraction)
print(Fraction.from_float(0.5))
print(random.random())
print(random.randrange(5, 10, 2))#inf inc, sup exc, ecart [5, 7, 9]
print(random.randint(1, 6))#inf inc, sup exc [1, 2, 3, 4, 5, 6]