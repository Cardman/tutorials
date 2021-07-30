using Microsoft.VisualStudio.TestTools.UnitTesting;
using Util;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace Util.Tests
{
    [TestClass()]
    public class ConstantsTests
    {
        [TestMethod()]
        public void dynamicClassForName1Test()
        {
            String str_ = Constants.getTypeFullString(typeof(string));
            Console.WriteLine(Constants.dynamicClassForName(null, str_) == typeof(string));
            str_ = Constants.getTypeFullString(typeof(Pair<int,int>));
            Console.WriteLine(Constants.dynamicClassForName(null, str_) == typeof(Pair<int, int>));
            str_ = Constants.getTypeFullString(typeof(Pair<Pair<int, MyList<string>>, Map<CarOptions, char>>));
            Console.WriteLine(Constants.dynamicClassForName(null, str_) == typeof(Pair<Pair<int, MyList<string>>, Map<CarOptions, char>>));
            str_ = Constants.getTypeFullString(typeof(Pair<Pair<int, string>, Map<CarOptions, char>>));
            Console.WriteLine(Constants.dynamicClassForName(null, str_) == typeof(Pair<Pair<int, string>, Map<CarOptions, char>>));
            MyList<int> l = new MyList<int>();
            MethodInfo m_ = typeof(Pair<int, int>).GetMethod("getFirst", new Type[0]);
            Console.WriteLine(m_.ReturnType.ToString());
            l.Add(5);
            l.Add(8);
            IEnumerator<int> e_ = l.GetEnumerator();
            Console.WriteLine("not empty");
            while (e_.MoveNext())
            {
                Console.WriteLine(e_.Current);
            }
            l = new MyList<int>();
            e_ = l.GetEnumerator();
            Console.WriteLine("empty");
            while (e_.MoveNext())
            {
                Console.WriteLine(e_.Current);
            }
        }
    }
}