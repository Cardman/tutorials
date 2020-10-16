import unittest
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

unittest.main()