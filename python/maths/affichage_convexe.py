from cust_polygon import Polygone
from cust_points import Point
from fractions import Fraction
import matplotlib.pyplot as plt

if __name__ == "__main__":
    polygone=Polygone()
    polygone.pts.append(Point(1, 1))
    polygone.pts.append(Point(1, 2))
    polygone.pts.append(Point(2, 2))
    polygone.pts.append(Point(2, 3))
    polygone.pts.append(Point(3, 3))
    polygone.pts.append(Point(3, 1))
    polygone.pts.append(Point(2, Fraction(1,2)))
    polygone.pts.append(Point(Fraction(7,2), 2))
    polygone.pts.append(Point(3, 2))
    first = []
    second = []
    for p in polygone.pts:
        first.append(p.x)
        second.append(p.y)
    conv = polygone.getConvex()
    firstConv = []
    secondConv = []
    for p in conv.pts:
        firstConv.append(p.x)
        secondConv.append(p.y)
    firstConv.append(conv.pts[0].x)
    secondConv.append(conv.pts[0].y)
    
    plt.plot(first, second, 'ro')
    plt.plot(firstConv, secondConv)
    plt.axis([0, 4, 0, 4])
    plt.show()

