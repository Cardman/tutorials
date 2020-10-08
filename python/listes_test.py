import random
import unittest
from listes import CustList

class RandomTest(unittest.TestCase):
    def test_is_valid_index1(self):
        liste = CustList()
        liste.add(4)
        self.assertIsInstance(liste.isValidIndex(0),bool)
        self.assertTrue(liste.isValidIndex(0))
    def test_is_valid_index2(self):
        liste = CustList()
        liste.add(4)
        self.assertIsInstance(liste.isValidIndex(-1),bool)
        self.assertTrue(not liste.isValidIndex(-1))
    def test_is_valid_index3(self):
        liste = CustList()
        liste.add(4)
        self.assertIsInstance(liste.isValidIndex(1),bool)
        self.assertTrue(not liste.isValidIndex(1))

unittest.main()