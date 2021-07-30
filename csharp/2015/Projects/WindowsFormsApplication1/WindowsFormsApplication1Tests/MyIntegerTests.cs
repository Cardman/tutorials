using Microsoft.VisualStudio.TestTools.UnitTesting;
using WindowsFormsApplication1;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApplication1.Tests
{
    [TestClass()]
    public class MyIntegerTests
    {
        [TestMethod()]
        public void sumTest()
        {
            Console.WriteLine(new MyInteger(1).sum(new MyInteger(2)) + " pas la");
            Console.WriteLine(new MyInteger(1).Equals("my string"));
            Console.WriteLine(new MyInteger(1).GetType() == typeof(MyInteger));
            Assert.AreEqual(new MyInteger(3), new MyInteger(1).sum(new MyInteger(2)));
        }

        [TestMethod()]
        public void prodTest()
        {
            Assert.AreEqual(new MyInteger(2), new MyInteger(1).prod(new MyInteger(2)));
        }
    }
}