import unittest
import sys
from maths2 import Ints

class RandomTest(unittest.TestCase):
    def test_quotCust1(self):
        self.assertIsInstance(Ints.quotCust(7,3),int)
        self.assertEqual(2,Ints.quotCust(7,3))
    def test_quotCust2(self):
        self.assertIsInstance(Ints.quotCust(-23,-7),int)
        self.assertEqual(4,Ints.quotCust(-23,-7))
    def test_quotCust3(self):
        self.assertIsInstance(Ints.quotCust(-23,7),int)
        self.assertEqual(-4,Ints.quotCust(-23,7))
    def test_quotCust4(self):
        self.assertIsInstance(Ints.quotCust(23,-7),int)
        self.assertEqual(-3,Ints.quotCust(23,-7))
    def test_quotCust5(self):
        self.assertIsInstance(Ints.quotCust(-28,-7),int)
        self.assertEqual(4,Ints.quotCust(-28,-7))
    def test_quotCust6(self):
        self.assertIsInstance(Ints.quotCust(-28,7),int)
        self.assertEqual(-4,Ints.quotCust(-28,7))
    def test_quotCust7(self):
        self.assertIsInstance(Ints.quotCust(23,7),int)
        self.assertEqual(3,Ints.quotCust(23,7))
    def test_quotCust8(self):
        self.assertIsInstance(Ints.quotCust(0,-sys.maxsize - 1),int)
        self.assertEqual(0,Ints.quotCust(0,-sys.maxsize - 1))
    def test_quotCust9(self):
        self.assertIsInstance(Ints.quotCust(-1,-sys.maxsize - 1),int)
        self.assertEqual(1,Ints.quotCust(-1,-sys.maxsize - 1))
    def test_quotCust10(self):
        self.assertIsInstance(Ints.quotCust(-sys.maxsize - 1,1),int)
        self.assertEqual(sys.maxsize + 1,Ints.quotCust(-sys.maxsize - 1,1))
    def test_quotCust11(self):
        self.assertIsInstance(Ints.quotCust(-sys.maxsize - 1,-1),int)
        self.assertEqual(-sys.maxsize-1,Ints.quotCust(-sys.maxsize - 1,-1))
    def test_modCust1(self):
        self.assertIsInstance(Ints.modCust(7,3),int)
        self.assertEqual(1,Ints.modCust(7,3))
    def test_modCust2(self):
        self.assertIsInstance(Ints.modCust(-23,-7),int)
        self.assertEqual(5,Ints.modCust(-23,-7))
    def test_modCust3(self):
        self.assertIsInstance(Ints.modCust(-23,7),int)
        self.assertEqual(5,Ints.modCust(-23,7))
    def test_modCust4(self):
        self.assertIsInstance(Ints.modCust(23,-7),int)
        self.assertEqual(2,Ints.modCust(23,-7))
    def test_modCust5(self):
        self.assertIsInstance(Ints.modCust(-28,-7),int)
        self.assertEqual(0,Ints.modCust(-28,-7))
    def test_modCust6(self):
        self.assertIsInstance(Ints.modCust(-28,7),int)
        self.assertEqual(0,Ints.modCust(-28,7))
    def test_modCust7(self):
        self.assertIsInstance(Ints.modCust(23,7),int)
        self.assertEqual(2,Ints.modCust(23,7))
    def test_quotCustQuick1(self):
        self.assertIsInstance(Ints.quotCustQuick(7,3),int)
        self.assertEqual(2,Ints.quotCustQuick(7,3))
    def test_quotCustQuick2(self):
        self.assertIsInstance(Ints.quotCustQuick(-23,-7),int)
        self.assertEqual(4,Ints.quotCustQuick(-23,-7))
    def test_quotCustQuick3(self):
        self.assertIsInstance(Ints.quotCustQuick(-23,7),int)
        self.assertEqual(-4,Ints.quotCustQuick(-23,7))
    def test_quotCustQuick4(self):
        self.assertIsInstance(Ints.quotCustQuick(23,-7),int)
        self.assertEqual(-3,Ints.quotCustQuick(23,-7))
    def test_quotCustQuick5(self):
        self.assertIsInstance(Ints.quotCustQuick(-28,-7),int)
        self.assertEqual(4,Ints.quotCustQuick(-28,-7))
    def test_quotCustQuick6(self):
        self.assertIsInstance(Ints.quotCustQuick(-28,7),int)
        self.assertEqual(-4,Ints.quotCustQuick(-28,7))
    def test_quotCustQuick7(self):
        self.assertIsInstance(Ints.quotCustQuick(23,7),int)
        self.assertEqual(3,Ints.quotCustQuick(23,7))
    def test_quotCustQuick8(self):
        self.assertIsInstance(Ints.quotCustQuick(0,-sys.maxsize - 1),int)
        self.assertEqual(0,Ints.quotCustQuick(0,-sys.maxsize - 1))
    def test_quotCustQuick9(self):
        self.assertIsInstance(Ints.quotCustQuick(-1,-sys.maxsize - 1),int)
        self.assertEqual(1,Ints.quotCustQuick(-1,-sys.maxsize - 1))
    def test_quotCustQuick10(self):
        self.assertIsInstance(Ints.quotCustQuick(-sys.maxsize - 1,1),int)
        self.assertEqual(sys.maxsize + 1,Ints.quotCustQuick(-sys.maxsize - 1,1))
    def test_quotCustQuick11(self):
        self.assertIsInstance(Ints.quotCustQuick(-sys.maxsize - 1,-1),int)
        self.assertEqual(-sys.maxsize-1,Ints.quotCustQuick(-sys.maxsize - 1,-1))

unittest.main()