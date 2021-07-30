using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReflectionCore
{
    public class MyClass
    {
        private int integer { get; set; }
        private List<string> strings { get; set; } = new List<string>();
        public MyClass()
        {
        }
        private MyClass(string _str)
        {
            integer = int.Parse(_str);
        }
        [FromAndToString]
        public static MyClass toMyClass(string _str)
        {
            return new MyClass(_str);
        }
        [FromAndToString]
        public static int toMyClassSecond(string _str)
        {
            return int.Parse(_str);
        }
        [FromAndToString]
        public static void toMyClassThird(string _str)
        {
        }
        [FromAndToString]
        public static MyClass toMyClassFourth(string _str, int _i)
        {
            return new MyClass(_str + _i);
        }
        [FromAndToString]
        public static MyClass toMyClassFifth(int _i)
        {
            return new MyClass("" + _i);
        }
        [FromAndToString]
        public string fromMyClass()
        {
            return "" + integer;
        }
        [FromAndToString]
        public int fromMyClassSecond()
        {
            return integer;
        }
        [FromAndToString]
        public string fromMyClassThird(int _t)
        {
            return ""+integer+ _t;
        }
        public int getInteger()
        {
            return integer;
        }
    }
}
