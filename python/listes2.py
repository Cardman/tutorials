import time

class CustList:
    def __init__(self):
        self.list = []
    def addAllElts(self,other):
        self.list.extend(other.list)
    def add(self,elt):
        self.list.append(elt)
    def insert(self,index,elt):
        self.list.insert(index,elt)
    def size(self):
        return len(self.list)
    def isValidIndex(self,index):
        if index < 0:
            return False
        if index >= self.size():
            return False
        return True
    def get(self,index):
        return self.list[index]
    def getList(self):
        return self.list
    def set(self,index,elt):
        self.list[index]=elt
    def removed(self,index):
        old=self.list[index]
        del self.list[index]
        return old
    def clear(self):
        self.list=[]
    def __repr__(self):
        list2= []
        for e in self.list:
            list2.append(str(e))
        return ";".join(list2)
    def toStr(self):
        return ";".join([str(elt) for elt in self.list])
    def __iter__(self):
        return ItRevList(self.list)

class ItRevList:
    def __init__(self, list):
        self.list = list
        self.position = len(list)
    def __next__(self):
        if self.position == 0:
            raise StopIteration
        self.position -= 1
        return self.list[self.position]

list = CustList()
list.add(2)
for e in list.getList():
    print(e)
print("\n")
print("len=",list.size())
list.add(4)
print("len=",list.size())
for e in list.getList():
    print(e)
print("\n")
print("iter\n")
for e in list:
    print(e)
print(time.localtime())

