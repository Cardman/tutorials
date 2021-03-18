from math import *
N, a, b = 500, 0, 1 + floor(38 * pi)
def rho(theta):
    return 1 + cos(theta*20/19) / 3
def echelle(t, xmin=a, xmax=b, numpoints=N):
    return xmin + t/numpoints * (xmax - xmin)
s = ("\\documentclass{article}\n\n"
    "\\usepackage[mathletters]{ucs}\n"
    "\\usepackage[utf8x]{inputenc}\n"
    "\\usepackage[Tl]{fontenc}\n"
    "\\usepackage{xcolor}\n"
    "\\usepackage{tikz}\n\n"
    "\\begin{document}\n"
    "\\begin{tikzpicture}[scale=2]\n"
    "\\clip (-1.7,-1.7) rectangle ( 1.7,1.7) ;\n"
    "\\draw[->] (-1.5,0) -- (1.5,0) node[right] {$x$};\n"
    "\\draw[->] (0,-1.5) -- (0,1.5) node[above] {$y$};\n"
    "\\draw[color=blue] plot[smooth] file {courbe.table};\n"
    "\\end{tikzpicture}\n"
    "\\end{document}\n")

with open("courbe.tex", 'w') as f:
    f.writelines(s)
with open("courbe.table", 'w') as f:
    for i in range(N):
        theta = echelle(i)
        r = rho(theta)
        x, y = r * cos(theta), r * sin(theta)
        f.write("{:8.5f} {:8.5f}\n".format(x, y))

#import os
#os.system("rubber -d {0}.tex && evince {0}.pdf &".format('courbe'))