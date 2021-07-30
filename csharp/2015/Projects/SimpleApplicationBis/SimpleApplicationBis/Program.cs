using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace MyCust.MyInner
{
    namespace MyCustBis.MyInnerBis
    {
        public class SampleClassInt { }
    }
}

namespace SimpleApplicationBis
{
    using MyCust.MyInner.MyCustBis.MyInnerBis;
    class Program
    {
        static void Main(string[] args)
        {
            //Convert.
            SampleClassInt s;
            StringBuilder str = new StringBuilder("hello world every body");
            int ind = str.ToString().IndexOf(" ")+1;
            str.Remove(ind, "world every ".Length);
            str.Insert(ind, "simple ");
            //args.Contains("");
            String original = "aaabbb";
            Console.WriteLine("The original string: '{0}'", original);
            String modified = original.Insert(3, " ");
            Console.WriteLine("The modified string: '{0}'", modified);
            Console.WriteLine("The original string: '{0}'", original);
            int v = int.MinValue;
            //MyStaticClass.Method();
        }
        private static async Task GetPageSizeAsync(string url)
        {
            var client = new HttpClient();
            var uri = new Uri(Uri.EscapeUriString(url));
            byte[] urlContents = await client.GetByteArrayAsync(uri);
            Console.WriteLine($"{url}: {urlContents.Length / 2:N0} characters");
        }
    }
    public class SuperClassImpl
    {
        public int Hello()
        {
            return 4;
        }
    }
    public interface Interface
    {
        int Hello();
    }
    public class SubClassImpl: SuperClassImpl, Interface
    {

    }
    public interface Interface2
    {
        int Hello();
    }
    public class SubClassImpl2 : Interface2
    {
        public int Hello()
        {
            return 6;
        }
    }
    public static class MyStaticClass
    {
        public static string LaunchTime = string.Format("{0:yyyy_MM_dd_HH_mm_ss_fff}", DateTime.Now);
        public const string Cst = "";
        public static void Method()
        {
            /*StringBuilder str = new StringBuilder("");
            str.AppendLine("1 + 1");
            str.Append(true);
            str.Append(" ");
            str.AppendLine(""+false);
            Console.WriteLine(str);
            try
            {
                SuperClass one = new SuperClass(1);
                SuperClass two = new SubClass(1);
                SubClass three = new SubClass(1);
                SuperClass four = new SubSubClass(1);
                one[1] = "1";
                two[1] = "2";
                three[1] = "3";
                four[1] = "4";
                str = new StringBuilder("");
                str.AppendLine(one[1]);
                str.AppendLine(two[1]);
                str.AppendLine(three[1]);
                str.AppendLine(four[1]);
                Console.WriteLine(str);
                //DateTime Now = DateTime.Now;
                //Write(@"E:\csharp\my_c_sharp_file1" + ".txt", string.Format("{0:yyyy_MM_dd_HH_mm_ss_fff}", Now)+"\n"+str.ToString());
            } catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            var t = new IncrDecr();
            var o = t;
            var r = t++;
            Append(@"E:\csharp\my_c_sharp_file.txt", "before " + t.MyValue);
            Append(@"E:\csharp\my_c_sharp_file.txt", "after " + r.MyValue);
            Append(@"E:\csharp\my_c_sharp_file.txt", "ch " + (o == t));
            var u = new IncrDecr();
            var p = u;
            var s = ++u;
            Append(@"E:\csharp\my_c_sharp_file.txt", "before " + u.MyValue);
            Append(@"E:\csharp\my_c_sharp_file.txt", "after " + s.MyValue);
            Append(@"E:\csharp\my_c_sharp_file.txt", "ch " + (p == u));
            var t2 = new IncrDecrBis();
            var o2 = t2;
            var r2 = t2++;
            Append(@"E:\csharp\my_c_sharp_file.txt", "before " + t2.MyValue);
            Append(@"E:\csharp\my_c_sharp_file.txt", "after " + r2.MyValue);
            Append(@"E:\csharp\my_c_sharp_file.txt", "ch " + (o2 == t2));
            var u2 = new IncrDecrBis();
            var p2 = u2;
            var s2 = ++u2;
            Append(@"E:\csharp\my_c_sharp_file.txt", "before " + u2.MyValue);
            Append(@"E:\csharp\my_c_sharp_file.txt", "after " + s2.MyValue);
            Append(@"E:\csharp\my_c_sharp_file.txt", "ch " + (p2 == u2));
            List<string> List = new List<string>();
            List.Add("toto");
            List.Add("titi");
            int it = 5;
            byte bt = 5;
            ValueType v = it;
            ValueType v2 = bt;
            foreach (var tt in List) {
                Append(@"E:\csharp\my_c_sharp_file.txt", "in List " + tt.ExtString(1,3));
            }*/
            Append(@"E:\csharp\my_c_sharp_file.txt", " ");
            Append(@"E:\csharp\my_c_sharp_file.txt", @"E:\csharp\my_c_sharp_file.txt " + Directory.Exists(@"E:\csharp\my_c_sharp_file.txt"));
            Append(@"E:\csharp\my_c_sharp_file.txt", @"E:\csharp\my_c_sharp_file " + Directory.Exists(@"E:\csharp\my_c_sharp_file"));
            Append(@"E:\csharp\my_c_sharp_file.txt", @"E:\csharp " + Directory.Exists(@"E:\csharp"));
            foreach (var f in Directory.EnumerateFiles(@"E:\csharp","*",SearchOption.AllDirectories))
            {
                Append(@"E:\csharp\my_c_sharp_file.txt", @"E:\csharp file:" + f+":"+File.Exists(f)+"," + Directory.Exists(f)+","+new FileInfo(f).Length + "," + new FileInfo(f).Name + "," + new FileInfo(f).Directory.Name);
            }
            foreach (var f in Directory.EnumerateFiles(@"E:\csharp", "*", SearchOption.AllDirectories))
            {
                Append(@"E:\csharp\my_c_sharp_file.txt", @"E:\csharp found file:" + f + ":" + File.Exists(f) + "," + Directory.Exists(f) + "," + new FileInfo(f).Length + "," + new FileInfo(f).Directory.Name);
            }
            foreach (var f in Directory.EnumerateDirectories(@"E:\csharp", "*", SearchOption.AllDirectories))
            {
                Append(@"E:\csharp\my_c_sharp_file.txt", @"E:\csharp file:" + f + ":" + File.Exists(f) + "," + Directory.Exists(f));
            }
            foreach (var f in Directory.EnumerateDirectories(@"E:\csharp"))
            {
                Append(@"E:\csharp\my_c_sharp_file.txt", @"E:\csharp file:" + f + ":" + File.Exists(f) + "," + Directory.Exists(f));
            }
            new[] { "p"}.Max(p => p.Length);
            //object res = n(0) ?? n(1) ?? n(2);
        }
        public static object n(int i)
        {
            Append(@"E:\csharp\my_c_sharp_file.txt", "call " + i);
            return null;
        }
        public static void Write(string fileName, string content)
        {
            using (StreamWriter sw = File.CreateText(fileName))
            {
                sw.WriteLine(content);
            }
        }
        public static void Append(string fileName, string content)
        {
            using (StreamWriter sw = File.AppendText(fileName))
            {
                sw.WriteLine(content);
            }
        }
    }
    public class SuperClass
    {
        public const string Cst2 = "";
        public int Length {
            get { return array.Length; }
        }
        private string[] innerArray;
        protected string[] array {
            get { return innerArray; }
            private set { innerArray = value; }
        }
        public SuperClass(int l=0)
        {
            array = new string[l];
        }
        public virtual string this[int index]{
            get{
                MyStaticClass.Append(@"E:\csharp\my_c_sharp_file.txt", MyStaticClass.LaunchTime + ":reader");
                return array[index - 1]; }
            set {
                MyStaticClass.Append(@"E:\csharp\my_c_sharp_file.txt", MyStaticClass.LaunchTime + ":writer base");
                array[index - 1] = value; }
        }
    }
    public class SubClass : SuperClass
    {
        public SubClass(int l = 0):base(l)
        {
        }
        public override string this[int index]
        {
            set {
                MyStaticClass.Append(@"E:\csharp\my_c_sharp_file.txt", MyStaticClass.LaunchTime + ":writer sub");
                array[index - 1] = value; }
        }
    }
    public class SubSubClass : SubClass
    {
        public SubSubClass(int l = 0) : base(l)
        {
        }
        public override string this[int index]
        {
            get
            {
                MyStaticClass.Append(@"E:\csharp\my_c_sharp_file.txt", MyStaticClass.LaunchTime + ":reader sub sub");
                return array[index - 1];
            }
        }
    }
    public class IncrDecr
    {
        public int MyValue;
        public static IncrDecr operator++(IncrDecr v)
        {
            IncrDecr out_ = new IncrDecr();
            out_.MyValue = v.MyValue + 1;
            return out_;
        }
        public static IncrDecr operator --(IncrDecr v)
        {
            IncrDecr out_ = new IncrDecr();
            out_.MyValue = v.MyValue - 1;
            return out_;
        }
    }
    public class IncrDecrBis
    {
        public int MyValue;
        public static IncrDecrBis operator ++(IncrDecrBis v)
        {
            v.MyValue++;
            return v;
        }
        public static IncrDecrBis operator --(IncrDecrBis v)
        {
            v.MyValue--;
            return v;
        }
    }
    public static class StringUtil
    {
        public static string ExtString(this string instance, int min, int max)
        {
            return instance.Substring(min, max - min);
        }
    }
}
