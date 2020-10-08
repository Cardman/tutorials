import argparse
parser = argparse.ArgumentParser()
parser.add_argument("x", type=int, help="le 1 nombre à mettre au carré")
parser.add_argument("y", type=int, help="le 2 nombre à mettre au carré")
args = parser.parse_args()
x = args.x
y = args.y
retour = x ** 2 + y ** 2
print(retour)