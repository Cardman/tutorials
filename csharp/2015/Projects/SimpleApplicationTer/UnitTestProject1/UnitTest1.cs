using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

namespace UnitTestProject1
{
    [TestClass]
    public class UnitTest1
    {
        private Chut chut;

        [ClassInitialize]
        public static void ecole(TestContext con)
        {
            Console.WriteLine("oh");
        }

        [TestInitialize]
        public void Call() { 
            chut = new Chut();
            Console.WriteLine("First");
        }
        [TestMethod]
        public void TestMethod1()
        {
            Console.WriteLine("Middle way");
            Assert.AreEqual(30, chut.inter(6));
            //SimpleApplicationTer.SubGene s;
        }
        [TestMethod]
        public void TestMethod2()
        {
            Console.WriteLine("Middle way 2");
            Assert.AreEqual(32, chut.inter(8));
            //SimpleApplicationTer.SubGene s;
        }
        [TestCleanup]
        public void Call2()
        {
            chut = null;
            Console.WriteLine("Last");
        }
        [ClassCleanup]
        public static void vacances()
        {
            Console.WriteLine("oura");
        }
    }
    public class Chut
    {
        private int Val = 24;
        internal int inter(int nez)
        {
            return Val+ nez;
        }
    }
    [TestClass]
    public class UnitTest2
    {
        [TestMethod]
        public void TestMethod3()
        {
            //long s = 21; // Change this value to perform other tests

            /*for (long i = 4; i < 100; i++)
            {
                Change m = Solution.OptimalChange(i);

                Console.WriteLine("\nCoin(s)  2€: " + m.coin2);
                Console.WriteLine("Bill(s)  5€: " + m.bill5);
                Console.WriteLine("Bill(s) 10€: " + m.bill10);

                long result = m.coin2 * 2 + m.bill5 * 5 + m.bill10 * 10;
                Console.WriteLine("Change given = " + result);
            }*/
            var o = new object();
            var d = new Dictionary<object, int>();
            var dany= o;
            d[dany] = 1;
            var boon = dany;
            d[boon] = 2;
            Console.WriteLine(d[dany]);
        }
    }
    
        // Do not modify Change
    class Change
    {
        public long coin2 = 0;
        public long bill5 = 0;
        public long bill10 = 0;
    }

    class Solution
    {

        // Do not modify this method​​​​​​‌​​​​‌‌‌‌‌​​‌​‌‌​​​​​​​‌​ signature
        public static Change OptimalChange(long s)
        {
            if (s < 2)
            {
                return null;
            }
            if (s == 3)
            {
                return null;
            }
            long current = s;
            Change ch = new Change();
            while (current > 20)
            {
                ch.bill10++;
                current -= 10;
            }
            if (current % 10 == 0)
            {
                ch.bill10 += current / 10;
                return ch;
            }
            if (current % 10 == 9)
            {
                ch.bill10 += current / 10;
                ch.bill5++;
                ch.coin2 = 2;
                return ch;
            }
            if (current % 10 == 8)
            {
                ch.bill10 += current / 10;
                ch.coin2 = 4;
                return ch;
            }
            if (current % 10 == 7)
            {
                ch.bill10 += current / 10;
                ch.bill5++;
                ch.coin2 = 1;
                return ch;
            }
            if (current % 10 == 6)
            {
                ch.bill10 += current / 10;
                ch.coin2 = 3;
                return ch;
            }
            if (current % 10 == 5)
            {
                ch.bill10 += current / 10;
                ch.bill5++;
                return ch;
            }
            if (current % 10 == 4)
            {
                ch.bill10 += current / 10;
                ch.coin2 = 2;
                return ch;
            }
            if (current % 10 == 3)
            {
                ch.bill5++;
                ch.coin2 = 4;
                return ch;
            }
            if (current % 10 == 2)
            {
                ch.bill10 += current / 10;
                ch.coin2 = 1;
                return ch;
            }
            ch.bill5++;
            ch.coin2 = 3;
            return ch;
        }
    }
}
