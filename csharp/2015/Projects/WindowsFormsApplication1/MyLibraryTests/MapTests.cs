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
    public class MapTests
    {
        [TestMethod()]
        public void put1Test()
        {
            Map<string, string> map_;
            map_ = new Map<string, string>();
            map_.put("hello", "world");
            Assert.AreEqual(1, map_.size());
            Assert.AreEqual("hello", map_.entryList()[0].getKey());
            Assert.AreEqual("world", map_.entryList()[0].getValue());
            Assert.AreEqual("world", map_.getVal("hello"));
            Assert.AreEqual(null, map_.getVal("world"));
        }

        [TestMethod()]
        public void put2Test()
        {
            Map<string, int> map_;
            map_ = new Map<string, int>();
            map_.put("hello", 3);
            Assert.AreEqual(1, map_.size());
            Assert.AreEqual("hello", map_.entryList()[0].getKey());
            Assert.AreEqual(3, map_.entryList()[0].getValue());
            Assert.AreEqual(3, map_.getVal("hello"));
            Assert.AreEqual(0, map_.getVal("world"));
        }
    }
}