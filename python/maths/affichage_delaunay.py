from delaunay import Delaunay
from cust_points import Point
import matplotlib.pyplot as plt

if __name__ == "__main__":
    liste=[]
    liste.append(Point(0, 0))
    liste.append(Point(0, 1))
    liste.append(Point(1, 1))
    liste.append(Point(1, 2))
    liste.append(Point(2, 2))
    liste.append(Point(2, 0))
    delaunay = Delaunay()
    delaunay.appliquer(liste)
    first = []
    second = []
    for p in liste:
        first.append(p.x)
        second.append(p.y)
    firstCenter = []
    secondCenter = []
    for t in delaunay.triangles:
        pt=t.centreCirconscrit()
        firstCenter.append(pt.x)
        secondCenter.append(pt.y)
        trix = [t.one.x,t.two.x,t.three.x,t.one.x]
        triy = [t.one.y,t.two.y,t.three.y,t.one.y]
        plt.plot(trix, triy,color='#004000')
    plt.plot(first, second, 'ro')
    plt.plot(firstCenter, secondCenter, 'bo')
    plt.axis([-1, 4, -1, 4])
    plt.show()