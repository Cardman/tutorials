import csv
import collections

Point=collections.namedtuple('Point',['x','y'])
p=Point(11,y=22)
print(p[0]+p[1])
x,y=p
print(p.x+p.y)

def lireCsv(lien):
    EmployeeRecord=collections.namedtuple('EmployeeRecord','name, age, title, department, paygrade')
    for emp in map(EmployeeRecord._make,csv.reader(open(lien,"rt"))):
        print(emp.name, emp.title)

lireCsv("employees.csv")