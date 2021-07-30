using Microsoft.VisualStudio.TestTools.UnitTesting;
using SampleUmlForComponents;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleUmlForComponents.Tests
{
    [TestClass()]
    public class StringListTests
    {
        [TestMethod()]
        public void matchingRegExpTest()
        {
            //            StringList list_ = StringList.matchingRegExp("azertyuiopqsdfghjklmwxcvbn,;:!ù*^$?./%¨`1234567890&é\"'(-è_çà)=~#{[|`\\^@]}","\\w");
            StringList list_ = StringList.matchingRegExp("Ÿazertyuiopqsdfghjklmwxcvbn,;:!ùâä¨*^$?./%`1234567890&é\"'(-èÉ_çà)=~#{[|`\\^@]}", "\\w");
            //            StringList list_ = StringList.matchingRegExp("azertyuiopqsdfghjklmwxcvbn", "\\w");
            Assert.AreEqual(46, list_.size());
            Console.WriteLine(list_[0]);
            //We are the character words (letters (authors), digits (scientists) and scores (sportive people))
        }

        [TestMethod()]
        public void getTokensSeparatorsTest()
        {
            string input_ = "Hello world every body";
            string regExp_ = "\\w+";
            StringList components_ = StringList.getTokensSeparators(input_, regExp_);
            Assert.AreEqual(8, components_.size());
            Assert.AreEqual("", components_.get(0));
            Assert.AreEqual("Hello", components_.get(1));
            Assert.AreEqual(" ", components_.get(2));
            Assert.AreEqual("world", components_.get(3));
            Assert.AreEqual(" ", components_.get(4));
            Assert.AreEqual("every", components_.get(5));
            Assert.AreEqual(" ", components_.get(6));
            Assert.AreEqual("body", components_.get(7));
        }

        [TestMethod()]
        public void match1Test()
        {
            Assert.IsTrue(StringList.match("hello world 1+1=2", "*world.1*"));
        }

        [TestMethod()]
        public void match2Test()
        {
            Assert.IsTrue(StringList.match("hello world 1+1=2", "*world?1*"));
        }

        [TestMethod()]
        public void match3Test()
        {
            Assert.IsTrue(StringList.match("hello world1+1=2", "*world?1*"));
        }

        [TestMethod()]
        public void match4Test()
        {
            Assert.IsTrue(StringList.match("hello world 1+1? what?", "*world?1+1\\?*"));
        }

        [TestMethod()]
        public void match5Test()
        {
            Assert.IsTrue(StringList.match("hello world 1+1\\ what?", "*world?1+1\\\\ wh*"));
        }

        [TestMethod()]
        public void match6Test()
        {
            Assert.IsTrue(StringList.match("zz.txt", "zz\\.txt"));
        }

        [TestMethod()]
        public void match7Test()
        {
            Assert.IsTrue(StringList.match("zz.txt", "*t"));
        }

        [TestMethod()]
        public void match8Test()
        {
            Assert.IsTrue(StringList.match("zztxt", "*t"));
        }

        [TestMethod()]
        public void match10Test()
        {
            Assert.IsTrue(StringList.match("zztxt", "*t*t"));
        }

        [TestMethod()]
        public void match9Test()
        {
            Assert.IsTrue(StringList.match("zzaxt", "*t"));
        }
    }
}