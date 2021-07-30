using Microsoft.VisualStudio.TestTools.UnitTesting;
using MyLibrary;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyLibrary.Tests
{
    [TestClass()]
    public class MyIntegerLibTests
    {
        [TestMethod()]
        public void sumTest()
        {
            Console.WriteLine(new MyIntegerLib(1).sum(new MyIntegerLib(2)) + " pas la");
            Console.WriteLine(new MyIntegerLib(1).Equals("my string"));
            Console.WriteLine(new MyIntegerLib(1).GetType() == typeof(MyIntegerLib));
            Assert.AreEqual(new MyIntegerLib(3), new MyIntegerLib(1).sum(new MyIntegerLib(2)));
        }

        [TestMethod()]
        public void prodTest()
        {
            Assert.AreEqual(new MyIntegerLib(2), new MyIntegerLib(1).prod(new MyIntegerLib(2)));
        }

        [TestMethod()]
        public void ObtenirListeDePrenoms1Test()
        {
            IEnumerable<string> res_ = MyIntegerLib.ObtenirListeDePrenoms();
            Assert.AreEqual(3, res_.Count<string>());
            Assert.AreEqual("Nicolas", res_.ElementAt<string>(0));
            Assert.AreEqual("Jeremie", res_.ElementAt<string>(1));
            Assert.AreEqual("Delphine", res_.ElementAt<string>(2));
        }
    }
}