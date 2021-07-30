using Microsoft.VisualStudio.TestTools.UnitTesting;
using FormatHtml;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;
using System.Xml;
using FormatHtmlTests;

namespace FormatHtml.Tests
{
    [TestClass()]
    public class FormatHtmlTests
    {
        [TestMethod()]
        public void extractObject1Test()
        {
            //TreeMap<string, CarOptions> tree_;
            //tree_ = new TreeMap<string, CarOptions>();
            //tree_.put("hello", CarOptions.FogLights);
            Assert.AreEqual("FogLights", FormatHtml.extractObject("ToString()", CarOptions.FogLights));
        }
        [TestMethod()]
        public void extractObject2Test()
        {
            Pair<int, string> p_ = new Pair<int, string>();
            p_.setFirst(0);
            p_.setSecond("str");
            Assert.AreEqual("str", FormatHtml.extractObject("second", p_));
        }
        [TestMethod()]
        public void extractObject3Test()
        {
            Pair<int, string> p_ = new Pair<int, string>();
            p_.setFirst(0);
            p_.setSecond("str");
            Assert.AreEqual("str", FormatHtml.extractObject("Util^Util^Pair^2^second", p_));
        }
        [TestMethod()]
        public void extractObject4Test()
        {
            Assert.AreEqual("ONE", FormatHtml.extractObject("FormatHtmlTests^FormatHtmlTests^BeanOne^selectedString", new BeanOne()));
        }
        [TestMethod()]
        public void setObject1Test()
        {
            BeanOne b_ = new BeanOne();
            MyList<EnumNumber> l_ = new MyList<EnumNumber>();
            l_.Add(EnumNumber.ONE);
            FormatHtml.setObject(b_, "", "setCombobox", l_, "", "Util.Util.MyList`1[[FormatHtmlTests.EnumNumber, FormatHtmlTests]]", new MyList<long>());
            MyList<EnumNumber> c_ = b_.getCombobox();
            Assert.AreEqual(1, c_.size());
            Assert.AreEqual(EnumNumber.ONE, c_.get(0));
        }
        //selectedString
        [TestMethod()]
        public void renameElement1Test()
        {
            XmlDocument doc_ = new XmlDocument();
            XmlElement elt_ = doc_.CreateElement("main");
            doc_.AppendChild(elt_);
            XmlElement main_ = elt_;
            elt_ = doc_.CreateElement("hello");
            main_.AppendChild(elt_);
            elt_ = doc_.CreateElement("world");
            main_.AppendChild(elt_);
            Console.WriteLine(XmlParser.toXml(doc_));
            XmlElement other_ = FormatHtml.renameElement(elt_, "word");
            Console.WriteLine(XmlParser.toXml(doc_));
            Console.WriteLine(other_ == elt_);
        }
        [TestMethod()]
        public void processHtml1Test()
        {
            String locale_ = "LOCALE";
            String folder_ = "messages";
            String relative_ = "sample/file";
            String content_ = "one=Description one\ntwo=Description two\nthree=desc &lt;{0}&gt;";
            String html_ = "<html><body><ul><c.for var=\"s\" list=\"composite.strings\"><li>{s;}</li></c.for></ul></body></html>";
            Map<String,String> files_ = new Map<String, String>();
		    files_.put(folder_+"/"+locale_+"/"+relative_+".properties", content_);
		    BeanOne bean_ = new BeanOne();
            bean_.getComposite().getStrings().Add("FIRST");
            bean_.getComposite().getStrings().Add("SECOND");
            bean_.getComposite().setInteger(5);
            Configuration conf_ = new Configuration();
            conf_.setBeans(new Map<String, Bean>());
		    conf_.getBeans().put("bean_one", bean_);
            conf_.setMessagesFolder(folder_);
		    conf_.setProperties(new Map<String, String>());
		    conf_.getProperties().put("msg_example", relative_);
            conf_.setTranslators(new Map<String, Translator>());
		    conf_.getTranslators().put("trans", new MyTranslator());
		    XmlDocument doc_ = XmlParser.parseSaxHtml(html_);
            String render_ = FormatHtml.processHtml(doc_.DocumentElement, conf_, files_, bean_);

            Assert.AreEqual("<html><body><ul><c.tmp><li>FIRST</li></c.tmp><c.tmp><li>SECOND</li></c.tmp></ul></body></html>", render_);
        }
        [TestMethod()]
        public void processHtml9Test()
        {
            String locale_ = "LOCALE";
            String folder_ = "messages";
            String relative_ = "sample/file";
            String content_ = "one=Description one\ntwo=Description two\nthree=desc &lt;{0}&gt;";
            String html_ = "<html><body><c.select list=\"combobox\"/></body></html>";
            Map<String,String> files_ = new Map<String, String>();
		    files_.put(folder_+"/"+locale_+"/"+relative_+".properties", content_);
		    BeanOne bean_ = new BeanOne();
            bean_.getComposite().getStrings().Add("FIRST");
            bean_.getComposite().getStrings().Add("SECOND");
            bean_.getComposite().setInteger(5);
            Configuration conf_ = new Configuration();
            conf_.setBeans(new Map<String, Bean>());
		    conf_.getBeans().put("bean_one", bean_);
            conf_.setMessagesFolder(folder_);
		    conf_.setProperties(new Map<String, String>());
		    conf_.getProperties().put("msg_example", relative_);
            conf_.setTranslators(new Map<String, Translator>());
		    conf_.getTranslators().put("trans", new MyTranslator());
            XmlDocument doc_ = XmlParser.parseSaxHtml(html_);
            String render_ = FormatHtml.processHtml(doc_.DocumentElement, conf_, files_, bean_);

            Assert.AreEqual("<html><body><select name=\"\" className=\"\"><option value=\"ONE\">ONE</option><option value=\"TWO\">TWO</option><option value=\"THREE\">THREE</option><option value=\"FOUR\">FOUR</option><option value=\"FIVE\">FIVE</option><option value=\"SIX\">SIX</option></select></body></html>", render_);
        }
        [TestMethod()]
        public void processHtml18Test()
        {
            String locale_ = "LOCALE";
            String folder_ = "messages";
            String relative_ = "sample/file";
            String content_ = "one=Description one\ntwo=Description two\nthree=desc &lt;{0}&gt;";
            String html_ = "<html><body><c.select map=\"translations\"/></body></html>";
            Map<String,String> files_ = new Map<String, String>();
		    files_.put(folder_+"/"+locale_+"/"+relative_+".properties", content_);
		    BeanOne bean_ = new BeanOne();
            bean_.getComposite().getStrings().Add("FIRST");
            bean_.getComposite().getStrings().Add("SECOND");
            bean_.getComposite().setInteger(5);
            Configuration conf_ = new Configuration();
            conf_.setBeans(new Map<String, Bean>());
		    conf_.getBeans().put("bean_one", bean_);
            conf_.setMessagesFolder(folder_);
		    conf_.setProperties(new Map<String, String>());
		    conf_.getProperties().put("msg_example", relative_);
            conf_.setTranslators(new Map<String, Translator>());
		    conf_.getTranslators().put("trans", new MyTranslator());
		    XmlDocument doc_ = XmlParser.parseSaxHtml(html_);
            String render_ = FormatHtml.processHtml(doc_.DocumentElement, conf_, files_, bean_);

            Assert.AreEqual("<html><body><select name=\"\" className=\"\"><option value=\"ONE\">1</option><option value=\"TWO\">2</option><option value=\"THREE\">3</option><option value=\"FOUR\">4</option><option value=\"FIVE\">5</option><option value=\"SIX\">6</option></select></body></html>", render_);
        }
        [TestMethod()]
        public void processHtmlJava1Test()
        {
            String locale_ = "LOCALE";
            String folder_ = "messages";
            String relative_ = "sample/file";
            String content_ = "one=Description one\ntwo=Description <a href=\"\">two</a>\nthree=desc &lt;{0}&gt;\nfour=''asp''";
            String html_ = "<html bean=\"bean_two\"><body><c.a value=\"sample/file,three\" param0=\"$typedString\">Content</c.a></body></html>";
            Map<String,String> files_ = new Map<String, String>();
		    files_.put(folder_+"/"+locale_+"/"+relative_+".properties", content_);
		    BeanOne bean_ = new BeanOne();
            bean_.getComposite().getStrings().Add("FIRST");
            bean_.getComposite().getStrings().Add("SECOND");
            bean_.getComposite().setInteger(5);
            bean_.getTree().put("ONE", 1);
            bean_.getTree().put("TWO", 2);
            BeanTwo beanTwo_ = new BeanTwo();
            beanTwo_.setTypedString("TITLE");
		    Configuration conf_ = new Configuration();
            conf_.setBeans(new Map<String, Bean>());
		    conf_.getBeans().put("bean_one", bean_);
            conf_.getBeans().put("bean_two", beanTwo_);
            conf_.setMessagesFolder(folder_);
		    conf_.setProperties(new Map<String, String>());
		    conf_.getProperties().put("msg_example", relative_);
            conf_.setTranslators(new Map<String, Translator>());
		    conf_.getTranslators().put("trans", new MyTranslator());
		    String render_ = FormatHtml.processHtmlJava(html_, conf_, locale_, files_);

            Assert.AreEqual("<html><body><a value=\"sample/file,three\" param0=\"$typedString\" title=\"desc &amp;lt;TITLE2&amp;gt;\">Content</a></body></html>", render_);

            Assert.AreEqual("TITLE2", beanTwo_.getTypedString());
	    }

        [TestMethod()]
        public void processImports5Test()
        {
            String locale_ = "LOCALE";
            String folder_ = "messages";
            String relative_ = "sample/file";
            String content_ = "one=Description one\ntwo=Description <a href=\"\">two</a>\nthree=desc &lt;{0}&gt;\nfour=''asp''";
            String html_ = "<html bean=\"bean_one\"><body><c.import page=\"page2.html\"><a/><c.package name=\"FormatHtmlTests\"><a/><c.class name=\"BeanTwo\"><a/><c.field name=\"typedString\" value=\"message\"><a/></c.field></c.class></c.package></c.import></body></html>";
            String htmlTwo_ = "<html bean=\"bean_two\"><body><a href=\"DELETE\" command=\"go\">{typedString}</a></body></html>";
            Map<String,String> files_ = new Map<String, String>();
		    files_.put(folder_+"/"+locale_+"/"+relative_+".properties", content_);
		    files_.put("page1.html", html_);
		    files_.put("page2.html", htmlTwo_);
		    BeanOne bean_ = new BeanOne();
            bean_.getComposite().getStrings().Add("FIRST");
            bean_.getComposite().getStrings().Add("SECOND");
            bean_.getComposite().setInteger(5);
            bean_.getTree().put("ONE", 1);
            bean_.getTree().put("TWO", 2);
            bean_.setForms(new Map<String, Object>());
		    bean_.getForms().put("key", "sample_value");
            BeanTwo beanTwo_ = new BeanTwo();
            beanTwo_.setTypedString("TITLE");
		    beanTwo_.setForms(new Map<String, Object>());
		    Configuration conf_ = new Configuration();
            conf_.setAssembly("FormatHtmlTests");
            conf_.setBeans(new Map<String, Bean>());
		    conf_.getBeans().put("bean_one", bean_);
            conf_.getBeans().put("bean_two", beanTwo_);
            conf_.setMessagesFolder(folder_);
		    conf_.setProperties(new Map<String, String>());
		    conf_.getProperties().put("msg_example", relative_);
            conf_.setTranslators(new Map<String, Translator>());
		    conf_.getTranslators().put("trans", new MyTranslator());
		    String render_ = FormatHtml.processImports(html_, conf_, locale_, files_);

            Assert.AreEqual("<html><body><a href=\"\" command=\"go\">Test {0}2</a></body></html>", render_);

            Assert.AreEqual(1, beanTwo_.getForms().size());
            Assert.AreEqual("key", beanTwo_.getForms().getKeys().get(0));
            Assert.AreEqual("sample_value", beanTwo_.getForms().values().get(0));
	    }
        [TestMethod()]
        public void process()
        {
            string elt_ = "<html xmlns:c='javahtml' xmlns='javahtml'><body>THREENEXT</body></html>";
            XmlDocument xml_ = XmlParser.parseSax(elt_);
            Assert.AreEqual("javahtml", xml_.GetNamespaceOfPrefix("c"));
            Assert.AreEqual("c", xml_.GetPrefixOfNamespace("javahtml"));
        }
    }
}