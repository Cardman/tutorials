import random
import unittest


class CustList:
    SIZE_EMPTY=0
    FIRST_INDEX=0
    INDEX_NOT_FOUND_ELT=-1
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
    def getFirstPrintableCharIndex(cls,mach):
        i_ = cls.FIRST_INDEX
        len_ = len(mach)
        while i_ < len_ :
            if ord(mach[i_]) < 33 :
                i_=i_+1
                continue
            return i_
        return cls.INDEX_NOT_FOUND_ELT
    def getLastPrintableCharIndex(cls,mach):
        i_ = len(mach) - 1
        while i_ >= cls.FIRST_INDEX :
            if ord(mach[i_]) < 33 :
                i_=i_-1
                continue
            return i_
        return cls.INDEX_NOT_FOUND_ELT
    def __iter__(self):
        return iter(self.list)
    def peter(cls,positif):
        if positif > 0:
            return 2*positif
    getFirstPrintableCharIndex = classmethod(getFirstPrintableCharIndex)
    getLastPrintableCharIndex = classmethod(getLastPrintableCharIndex)
    peter = classmethod(peter)

class MyNumber:
    def __init__(self,value):
        self.value = value
    def __bool__(self):
        return self.value >= 0

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
print("\n")
print(list.get(0))
print(list.get(1))
print("\n")
list.set(0,3)
print(list.get(0))
print(list.get(1))
print("\n")
list.insert(1,5)
print("\n")
print(list.get(0))
print(list.get(1))
print(list.get(2))
print("\n")
print("len=",list.size())
print(list.removed(1))
print("len=",list.size())
print("\n")
print(list.get(0))
print(list.get(1))
print("SIZE_EMPTY=",CustList.SIZE_EMPTY)

print(list);
print(repr(list));
print(list.toStr());
print(CustList.peter(2));
print(CustList.peter(0));
ma_chaine=str(input("Saisie"))
print(ma_chaine,CustList.getFirstPrintableCharIndex(ma_chaine))
print(ma_chaine,CustList.getLastPrintableCharIndex(ma_chaine))
myNb = MyNumber(1)
if myNb:
	print("Vrai")
else:
	print("Faux")
myNb2 = MyNumber(-1)
if myNb2:
	print("Vrai")
else:
	print("Faux")

