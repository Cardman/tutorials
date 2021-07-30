using Microsoft.VisualStudio.TestTools.UnitTesting;
using Util;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.CodeDom.Compiler;

namespace Util.Tests
{
    [TestClass()]
    public class MemoryCompilerTests
    {
        [TestMethod()]
        public void compileFiles1Test()
        {
            Map<string, string> map_ = new Map<string, string>();
            map_.put("B.cs", "using System.Collections.Generic;namespace Toto{public class B {public static int k=7;public List<B> list = new List<B>();}}");
            map_.put("C.cs", "namespace Toto{public class C {public static int k=6;}}");
            MemoryCompiler mem_ = new MemoryCompiler(map_, new StringList("System.dll"));
            mem_.compileFiles();
            Type gene_ = typeof(List<>);
            Type listDyn_ = gene_.MakeGenericType(Constants.getAssembly().GetType("Toto.B"));
            Assert.AreSame(listDyn_, Constants.classForName("mscorlib.System.Collections.Generic.List`1[[Toto.B, .]]"));
            Assert.AreEqual(7, Constants.getAssembly().GetType("Toto.B").GetField("k").GetValue(null));
            Assert.AreEqual(6, Constants.getAssembly().GetType("Toto.C").GetField("k").GetValue(null));
            Type dynType_ = Constants.getAssembly().GetType("Toto.B");
            object obj_ = dynType_.GetConstructor(new Type[0]).Invoke(new object[0]);
            object list_ = dynType_.GetField("list").GetValue(obj_);
            Assert.AreSame(listDyn_, list_.GetType());
            Assert.AreEqual(0, listDyn_.GetProperty("Count").GetValue(list_));
        }

        [TestMethod()]
        public void compileFiles1FailTest()
        {
            Map<string, string> map_ = new Map<string, string>();
            map_.put("B.cs", "using System.Collections.Generic;namespace Toto{public class B {public static int k=7;public List<B> list = new List<B>()}}");
            map_.put("C.cs", "namespace Toto{public class C {public static int k=6;}}");
            MemoryCompiler mem_ = new MemoryCompiler(map_, new StringList("System.dll"));
            mem_.compileFiles();
            CompilerErrorCollection e_ = mem_.getErrors();
            Assert.AreEqual(1, e_.Count);
            Assert.AreEqual(1, e_[0].Line);
            Assert.AreEqual(122, e_[0].Column);
            Assert.AreEqual(false, e_[0].IsWarning);
            //Assert.AreEqual("", e_[0].FileName);
        }

        [TestMethod()]
        public void map1Test()
        {
            Map<int?, int?> zeros_ = new Map<int?, int?>();
            zeros_.put(null, 0);
            zeros_.put(0, null);
            Type[] types_ = zeros_.GetType().GetGenericArguments();
            Console.WriteLine(types_[0].FullName);
            Console.WriteLine(zeros_.GetType().FullName);
            Assert.AreEqual(2, zeros_.size());
            Assert.AreEqual(0, zeros_.getVal(null));
            Assert.IsNull(zeros_.getVal(0));
            Assert.IsNull(zeros_.getVal(1));
            Assert.IsTrue(zeros_.contains(null));
            Assert.IsTrue(zeros_.contains(0));
            Assert.IsTrue(!zeros_.contains(1));
        }
    }
}