using Microsoft.VisualStudio.TestTools.UnitTesting;
using FormatHtml;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;
using FormatHtmlTests;

namespace FormatHtml.Tests
{
    [TestClass()]
    public class NavigationTests
    {
        [TestMethod()]
        public void processAnchorRequest3Test()
        {
            String locale_ = "LOCALE";
            String folder_ = "messages";
            String relative_ = "sample/file";
            String content_ = "one=Description one\ntwo=Description <a href=\"\">two</a>\nthree=desc &lt;{0}&gt;\nfour=''asp''";
            String html_ = "<html bean=\"bean_one\"><body>HEAD<a command=\"$goToPage\" href=\"\"/></body></html>";
            String htmlTwo_ = "<html bean=\"bean_two\"><body> NEXT<!--COMMENT--><form action=\"DELETE\" command=\"go\">{typedInt}</form><form action=\"go\">{typedInt}</form></body></html>";
            Map<String,String> files_ = new Map<String, String>();
		    files_.put(folder_+"/"+locale_+"/"+relative_+".properties", content_);
		    files_.put("page1.html", html_);
		    files_.put("page2.html", htmlTwo_);
		    BeanOne bean_ = new BeanOne();
            //bean_.setClassName(BeanOne.class.getName());
            bean_.setScope("request");
		    BeanTwo beanTwo_ = new BeanTwo();
            //beanTwo_.setClassName(BeanTwo.class.getName());
            beanTwo_.setScope("request");
		    Configuration conf_ = new Configuration();
            conf_.setBeans(new Map<String, Bean>());
		    conf_.getBeans().put("bean_one", bean_);
            conf_.getBeans().put("bean_two", beanTwo_);
            conf_.setMessagesFolder(folder_);
		    conf_.setFirstUrl("page1.html");
		    conf_.setValidators(new Map<String, Validator>());
		    conf_.setProperties(new Map<String, String>());
		    conf_.getProperties().put("msg_example", relative_);
            conf_.setTranslators(new Map<String, Translator>());
		    conf_.getTranslators().put("trans", new MyTranslator());
		    conf_.setNavigation(new Map<String, Map<String, String>>());
		    conf_.getNavigation().put("bean_one.goToPage", new Map<String, String>());
		    conf_.getNavigation().getVal("bean_one.goToPage").put("page", "page2.html");
            Navigation nav_ = new Navigation();
            nav_.setLanguage(locale_);
		    nav_.setSession(conf_);
		    nav_.setFiles(files_);
		    nav_.initializeSession();
		    nav_.processAnchorRequest("$bean_one.goToPage");

            Assert.AreEqual("page2.html", nav_.getCurrentUrl());
            Assert.AreEqual("bean_two", nav_.getCurrentBeanName());
            Assert.AreEqual("<html><body> NEXT<form action=\"\" command=\"go\">0</form><form action=\"go\">0</form></body></html>", nav_.getHtmlText());
            Assert.AreEqual(0, conf_.getBeans().getVal("bean_one").getForms().size());
            Assert.AreEqual(0, conf_.getBeans().getVal("bean_two").getForms().size());
            Assert.AreEqual(conf_.getBeans().getVal("bean_one").getForms(), conf_.getBeans().getVal("bean_two").getForms());
            Assert.AreEqual("", nav_.getTitle());
            Assert.AreEqual("", nav_.getReferenceScroll());
            Assert.AreEqual(0, nav_.getTooltips().size());
	    }

        [TestMethod()]
        public void processAnchorRequest5Test()
        {
            String locale_ = "LOCALE";
            String folder_ = "messages";
            String relative_ = "sample/file";
            String content_ = "one=Description one\ntwo=Description <a href=\"\">two</a>\nthree=desc &lt;{0}&gt;\nfour=''asp''";
            String html_ = "<html bean=\"bean_one\"><body>HEAD<a command=\"$goToPage(4)\" href=\"\"/></body></html>";
            String htmlTwo_ = "<html bean=\"bean_two\"><body> NEXT<!--COMMENT--><form action=\"DELETE\" command=\"go\">{typedInt}</form><form action=\"go\">{typedInt}</form></body></html>";
            Map<String,String> files_ = new Map<String, String>();
		    files_.put(folder_+"/"+locale_+"/"+relative_+".properties", content_);
		    files_.put("page1.html", html_);
		    files_.put("page2.html", htmlTwo_);
		    BeanOne bean_ = new BeanOne();
            //bean_.setClassName(BeanOne.class.getName());
            bean_.setScope("request");
		    BeanTwo beanTwo_ = new BeanTwo();
            //beanTwo_.setClassName(BeanTwo.class.getName());
            beanTwo_.setScope("request");
		    Configuration conf_ = new Configuration();
            conf_.setBeans(new Map<String, Bean>());
		    conf_.getBeans().put("bean_one", bean_);
            conf_.getBeans().put("bean_two", beanTwo_);
            conf_.setMessagesFolder(folder_);
		    conf_.setFirstUrl("page1.html");
		    conf_.setValidators(new Map<String, Validator>());
		    conf_.setProperties(new Map<String, String>());
		    conf_.getProperties().put("msg_example", relative_);
            conf_.setTranslators(new Map<String, Translator>());
		    conf_.getTranslators().put("trans", new MyTranslator());
		    conf_.setNavigation(new Map<String, Map<String, String>>());
		    conf_.getNavigation().put("bean_one.goToPage()", new Map<String, String>());
		    conf_.getNavigation().getVal("bean_one.goToPage()").put("page4", "page2.html");
            Navigation nav_ = new Navigation();
            nav_.setLanguage(locale_);
		    nav_.setSession(conf_);
		    nav_.setFiles(files_);
		    nav_.initializeSession();
		    nav_.processAnchorRequest("$bean_one.goToPage(4)");

            Assert.AreEqual("page2.html", nav_.getCurrentUrl());
            Assert.AreEqual("bean_two", nav_.getCurrentBeanName());
            Assert.AreEqual("<html><body> NEXT<form action=\"\" command=\"go\">0</form><form action=\"go\">0</form></body></html>", nav_.getHtmlText());
            Assert.AreEqual(0, conf_.getBeans().getVal("bean_one").getForms().size());
            Assert.AreEqual(0, conf_.getBeans().getVal("bean_two").getForms().size());
            Assert.AreSame(conf_.getBeans().getVal("bean_one").getForms(), conf_.getBeans().getVal("bean_two").getForms());
            Assert.AreEqual("", nav_.getTitle());
            Assert.AreEqual("", nav_.getReferenceScroll());
            Assert.AreEqual(0, nav_.getTooltips().size());
	    }
    }
}