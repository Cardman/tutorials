using Microsoft.VisualStudio.TestTools.UnitTesting;
using Stream;
using StreamTests;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream.Tests
{
    [TestClass()]
    public class SerializeXmlObjectTests
    {
        [TestMethod()]
        public void toXmlString1Test()
        {
            long i_ = 1;
            Assert.AreEqual("<mscorlib.System.Int64 value=\"1\"/>", SerializeXmlObject.toXmlString(i_));
        }
        [TestMethod()]
        public void toXmlString2Test()
        {
            CarOptions j_ = CarOptions.Spoiler;
            Assert.AreEqual("<Util.Util.CarOptions value=\"Spoiler\"/>", SerializeXmlObject.toXmlString(j_));
        }
        [TestMethod()]
        public void toXmlString3Test()
        {
            MyList<CarOptions> opts_ = new MyList<CarOptions>();
            opts_.Add(CarOptions.SunRoof);
            Assert.AreEqual("<Util.Util.MyList types=\"`1[[Util.CarOptions, Util]]\"><Util.Util.CarOptions class=\"mscorlib.System.Collections.IEnumerable\" value=\"SunRoof\"/></Util.Util.MyList>", SerializeXmlObject.toXmlString(opts_));
        }
        [TestMethod()]
        public void toXmlString4Test()
        {
            Assert.AreEqual("<mscorlib.System.String value=\"hello\"/>", SerializeXmlObject.toXmlString("hello"));
        }
        [TestMethod()]
        public void toXmlString5Test()
        {
            Map<String, CarOptions> opts2_ = new Map<String, CarOptions>();
            opts2_.put("1", CarOptions.SunRoof);
            Assert.AreEqual("<Util.Util.Map types=\"`2[[System.String, mscorlib], [Util.CarOptions, Util]]\"><mscorlib.System.String class=\"Util.Util.ListableKey\" key=\"\" value=\"1\"/><Util.Util.CarOptions class=\"Util.Util.ListableKey\" value=\"SunRoof\"/></Util.Util.Map>", SerializeXmlObject.toXmlString(opts2_));
        }
        [TestMethod()]
        public void toXmlString6Test()
        {
            int k_ = 4;
            Assert.AreEqual("<mscorlib.System.Int32 value=\"4\"/>", SerializeXmlObject.toXmlString(k_));
        }
        [TestMethod()]
        public void toXmlString7Test()
        {
            Assert.AreEqual("<StreamTests.StreamTests.Rate value=\"1/2\"/>", SerializeXmlObject.toXmlString(new Rate(1, 2)));
        }
        [TestMethod()]
        public void toXmlString8Test()
        {
            Assert.AreEqual("<StreamTests.StreamTests.Composite><mscorlib.System.Int64 field=\"num\" class=\"StreamTests.StreamTests.Composite\" value=\"1\"/><mscorlib.System.Int64 field=\"den\" class=\"StreamTests.StreamTests.Composite\" value=\"2\"/></StreamTests.StreamTests.Composite>", SerializeXmlObject.toXmlString(new Composite(1, 2)));
        }
        [TestMethod()]
        public void toXmlString9Test()
        {
            TreeMap<String, CarOptions> opts2_ = new TreeMap<String, CarOptions>();
            opts2_.put("1", CarOptions.SunRoof);
            opts2_.put("2", CarOptions.FogLights);
            Assert.AreEqual("<Util.Util.TreeMap types=\"`2[[System.String, mscorlib], [Util.CarOptions, Util]]\"><mscorlib.System.String class=\"Util.Util.ListableKey\" key=\"\" value=\"1\"/><Util.Util.CarOptions class=\"Util.Util.ListableKey\" value=\"SunRoof\"/><mscorlib.System.String class=\"Util.Util.ListableKey\" key=\"\" value=\"2\"/><Util.Util.CarOptions class=\"Util.Util.ListableKey\" value=\"FogLights\"/></Util.Util.TreeMap>", SerializeXmlObject.toXmlString(opts2_));
        }
        [TestMethod()]
        public void toXmlString10Test()
        {
            TreeMap<String, CarOptions> opts2_ = new TreeMap<String, CarOptions>(new ReverseComparer());
            opts2_.put("1", CarOptions.SunRoof);
            opts2_.put("2", CarOptions.FogLights);
            Assert.AreEqual("<Util.Util.TreeMap types=\"`2[[System.String, mscorlib], [Util.CarOptions, Util]]\"><StreamTests.StreamTests.ReverseComparer class=\"Util.Util.ListableKey\" Comparer=\"\"/><mscorlib.System.String class=\"Util.Util.ListableKey\" key=\"\" value=\"2\"/><Util.Util.CarOptions class=\"Util.Util.ListableKey\" value=\"FogLights\"/><mscorlib.System.String class=\"Util.Util.ListableKey\" key=\"\" value=\"1\"/><Util.Util.CarOptions class=\"Util.Util.ListableKey\" value=\"SunRoof\"/></Util.Util.TreeMap>", SerializeXmlObject.toXmlString(opts2_));
        }
        [TestMethod()]
        public void toXmlString11Test()
        {
            CarOptions j_ = CarOptions.Spoiler | CarOptions.SunRoof;
            Assert.AreEqual("<Util.Util.CarOptions value=\"SunRoof, Spoiler\"/>", SerializeXmlObject.toXmlString(j_));
        }
        [TestMethod()]
        public void toXmlString12Test()
        {
            char i_ = '1';
            Assert.AreEqual("<mscorlib.System.Char value=\"1\"/>", SerializeXmlObject.toXmlString(i_));
        }
        [TestMethod()]
        public void toXmlString13Test()
        {
            ArrayClass arr_ = new ArrayClass();
            int[] i_ = new int[2];
            i_[0] = 5;
            i_[1] = 3;
            arr_.setSampleArray(i_);
            Assert.AreEqual("<StreamTests.StreamTests.ArrayClass><array field=\"sampleArray\" class=\"StreamTests.StreamTests.ArrayClass\" type=\"mscorlib.System.Int32\"><mscorlib.System.Int32 value=\"5\"/><mscorlib.System.Int32 value=\"3\"/></array></StreamTests.StreamTests.ArrayClass>", SerializeXmlObject.toXmlString(arr_));
        }
        [TestMethod()]
        public void fromXmlString1Test()
        {
            long obj_ = (long) SerializeXmlObject.fromXmlStringObject("<mscorlib.System.Int64 value=\"1\" />");
            Assert.AreEqual(1, obj_);
        }
        [TestMethod()]
        public void fromXmlString2Test()
        {
            CarOptions obj_ = (CarOptions)SerializeXmlObject.fromXmlStringObject("<Util.Util.CarOptions value=\"Spoiler\" />");
            Assert.AreEqual(CarOptions.Spoiler, obj_);
        }
        [TestMethod()]
        public void fromXmlString3Test()
        {
            string obj_ = (string)SerializeXmlObject.fromXmlStringObject("<mscorlib.System.String value=\"hello\" />");
            Assert.AreEqual("hello", obj_);
        }
        [TestMethod()]
        public void fromXmlString4Test()
        {
            int obj_ = (int)SerializeXmlObject.fromXmlStringObject("<mscorlib.System.Int32 value=\"4\" />");
            Assert.AreEqual(4, obj_);
        }
        [TestMethod()]
        public void fromXmlString5Test()
        {
            Rate obj_ = (Rate)SerializeXmlObject.fromXmlStringObject("<StreamTests.StreamTests.Rate value=\"1/2\" />");
            Assert.AreEqual(new Rate(1,2), obj_);
        }
        [TestMethod()]
        public void fromXmlString6Test()
        {
            Composite obj_ = (Composite)SerializeXmlObject.fromXmlStringObject("<StreamTests.StreamTests.Composite><mscorlib.System.Int64 field=\"num\" class=\"StreamTests.StreamTests.Composite\" value=\"1\" /><mscorlib.System.Int64 field=\"den\" class=\"StreamTests.StreamTests.Composite\" value=\"2\" /></StreamTests.StreamTests.Composite>");
            Assert.AreEqual(new Composite(1, 2), obj_);
        }
        [TestMethod()]
        public void fromXmlString7Test()
        {
            MyList<CarOptions> obj_ = (MyList<CarOptions>)SerializeXmlObject.fromXmlStringObject("<Util.Util.MyList types=\"`1[[Util.CarOptions, Util]]\"><Util.Util.CarOptions class=\"mscorlib.System.Collections.IEnumerable\" value=\"SunRoof\" /></Util.Util.MyList>");
            Assert.AreEqual(1, obj_.size());
            Assert.AreEqual(CarOptions.SunRoof, obj_.get(0));
        }
        [TestMethod()]
        public void fromXmlString8Test()
        {
            Map<string,CarOptions> obj_ = (Map < string, CarOptions>) SerializeXmlObject.fromXmlStringObject("<Util.Util.Map types=\"`2[[System.String, mscorlib], [Util.CarOptions, Util]]\"><mscorlib.System.String class=\"Util.Util.ListableKey\" key=\"\" value=\"hello\" /><Util.Util.CarOptions class=\"Util.Util.ListableKey\" value=\"SunRoof\" /></Util.Util.Map>");
            Assert.AreEqual(1, obj_.size());
            Assert.AreEqual(CarOptions.SunRoof, obj_.getVal("hello"));
        }
        [TestMethod()]
        public void fromXmlString9Test()
        {
            TreeMap<string, CarOptions> obj_ = (TreeMap<string, CarOptions>)SerializeXmlObject.fromXmlStringObject("<Util.Util.TreeMap types=\"`2[[System.String, mscorlib], [Util.CarOptions, Util]]\"><mscorlib.System.String class=\"Util.Util.ListableKey\" key=\"\" value=\"1\" /><Util.Util.CarOptions class=\"Util.Util.ListableKey\" value=\"SunRoof\" /><mscorlib.System.String class=\"Util.Util.ListableKey\" key=\"\" value=\"2\" /><Util.Util.CarOptions class=\"Util.Util.ListableKey\" value=\"FogLights\" /></Util.Util.TreeMap>");
            Assert.AreEqual(2, obj_.size());
            Assert.AreEqual("1", obj_.getKey(0));
            Assert.AreEqual(CarOptions.SunRoof, obj_.getValue(0));
            Assert.AreEqual("2", obj_.getKey(1));
            Assert.AreEqual(CarOptions.FogLights, obj_.getValue(1));
        }
        [TestMethod()]
        public void fromXmlString10Test()
        {
            TreeMap<string, CarOptions> obj_ = (TreeMap<string, CarOptions>)SerializeXmlObject.fromXmlStringObject("<Util.Util.TreeMap types=\"`2[[System.String, mscorlib], [Util.CarOptions, Util]]\"><StreamTests.StreamTests.ReverseComparer class=\"Util.Util.ListableKey\" Comparer=\"\" /><mscorlib.System.String class=\"Util.Util.ListableKey\" key=\"\" value=\"2\" /><Util.Util.CarOptions class=\"Util.Util.ListableKey\" value=\"FogLights\" /><mscorlib.System.String class=\"Util.Util.ListableKey\" key=\"\" value=\"1\" /><Util.Util.CarOptions class=\"Util.Util.ListableKey\" value=\"SunRoof\" /></Util.Util.TreeMap>");
            Assert.AreEqual(2, obj_.size());
            Assert.AreEqual("2", obj_.getKey(0));
            Assert.AreEqual(CarOptions.FogLights, obj_.getValue(0));
            Assert.AreEqual("1", obj_.getKey(1));
            Assert.AreEqual(CarOptions.SunRoof, obj_.getValue(1));
        }
        [TestMethod()]
        public void fromXmlString11Test()
        {
            CarOptions obj_ = (CarOptions)SerializeXmlObject.fromXmlStringObject("<Util.Util.CarOptions value=\"Spoiler, SunRoof\" />");
            Assert.AreEqual(CarOptions.Spoiler|CarOptions.SunRoof, obj_);
        }
        [TestMethod()]
        public void fromXmlString12Test()
        {
            char obj_ = (char)SerializeXmlObject.fromXmlStringObject("<mscorlib.System.Char value=\"1\" />");
            Assert.AreEqual('1', obj_);
        }
        [TestMethod()]
        public void fromXmlString13Test()
        {
            ArrayClass arr_ = (ArrayClass)SerializeXmlObject.fromXmlStringObject("<StreamTests.StreamTests.ArrayClass><array field=\"sampleArray\" class=\"StreamTests.StreamTests.ArrayClass\" type=\"mscorlib.System.Int32\"><mscorlib.System.Int32 value=\"5\" /><mscorlib.System.Int32 value=\"3\" /></array></StreamTests.StreamTests.ArrayClass>");
            Assert.AreEqual(2, arr_.getSampleArray().Length);
            Assert.AreEqual(5, arr_.getSampleArray().ElementAt(0));
            Assert.AreEqual(3, arr_.getSampleArray().ElementAt(1));
        }
    }
}