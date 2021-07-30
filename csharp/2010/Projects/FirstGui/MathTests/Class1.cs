using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using MyLibrary;

namespace MathTests
{
    [TestFixture]
    public class MyTest
    {
        [Test]
        public void Test()
        {
            Assert.AreEqual(3, Class1.SayHello(1,2));
        }
    }
}
