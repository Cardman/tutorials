using Microsoft.VisualStudio.TestTools.UnitTesting;
using Util;
using System;
using System.Xml;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util.Tests
{
    [TestClass()]
    public class XmlParserTests
    {
        [TestMethod()]
        public void parseSaxTest()
        {
            String hello_ = "<hello/>";
            XmlDocument doc_ = XmlParser.parseSax(hello_);
            Assert.AreEqual(1, doc_.GetElementsByTagName("hello").Count);
        }

        [TestMethod()]
        public void toXml1Test()
        {
            String hello_ = "<hello/>";
            XmlDocument doc_ = XmlParser.parseSax(hello_);
            XmlNode n_ = doc_.GetElementsByTagName("hello").Item(0);
            Assert.AreEqual("<hello/>", XmlParser.toXml(n_));
        }


        [TestMethod()]
        public void toXml2Test()
        {
            String hello_ = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><hello att=\"\"/>";
            XmlDocument doc_ = XmlParser.parseSax(hello_);
            //XmlNode n_ = doc_.GetElementsByTagName("hello").Item(0);
            Assert.AreEqual("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><hello att=\"\"/>", XmlParser.toXml(doc_));
        }


        [TestMethod()]
        public void toXml3Test()
        {
            String hello_ = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><hello>yours</hello>";
            XmlDocument doc_ = XmlParser.parseSax(hello_);
            //XmlNode n_ = doc_.GetElementsByTagName("hello").Item(0);
            Assert.AreEqual("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><hello>yours</hello>", XmlParser.toXml(doc_));
        }

        [TestMethod()]
        public void toXml4Test()
        {
            String hello_ = "<hello>yours</hello>";
            XmlDocument doc_ = XmlParser.parseSax(hello_);
            //XmlNode n_ = doc_.GetElementsByTagName("hello").Item(0);
            Assert.AreEqual("<hello>yours</hello>", XmlParser.toXml(doc_));
        }
        [TestMethod()]
        public void process()
        {
            string elt_ = "<html xmlns:c='javahtml' xmlns='javahtml'><body><e c:attr='elt'/>THREENEXT<c:toto/><c:elt c:r='titi'/></body></html>";
            XmlDocument xml_ = XmlParser.parseSax(elt_);//c:attr
            XmlElement e_ = xml_.DocumentElement.FirstChild.FirstChild as XmlElement;
            Assert.AreEqual("c", xml_.DocumentElement.GetPrefixOfNamespace("javahtml"));
            Assert.AreEqual("javahtml", xml_.DocumentElement.GetNamespaceOfPrefix("c"));
            Assert.AreEqual("", e_.Prefix);
            Assert.AreEqual("elt", e_.GetAttribute("c:attr"));
            e_ = xml_.DocumentElement.FirstChild.FirstChild.NextSibling.NextSibling as XmlElement;
            Assert.AreEqual("c", e_.Prefix);
            Assert.AreEqual("c:toto", e_.Name);
            e_ = xml_.DocumentElement.FirstChild.FirstChild.NextSibling.NextSibling.NextSibling as XmlElement;
            Assert.AreEqual("titi", e_.GetAttribute("c:r"));
            //Assert.AreEqual("javahtml", xml_.GetNamespaceOfPrefix("c"));
            //Assert.AreEqual("c", xml_.GetPrefixOfNamespace("javahtml"));
        }
    }
}