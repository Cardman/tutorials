using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SimpleApplicationTer
{
    class MyAtmicInteger
    {
        public int Value;
        public int Incr()
        {
            return Interlocked.Increment(ref Value);
        }
        public int Add(int val)
        {
            return Interlocked.Add(ref Value,val);
        }
        /*public static Pref MyVal;
        public static ref Pref CurVal()
        {
            return ref MyVal;
        }*/
    }
    class MyAtmicBoolean
    {
        public int Value;
        public void Set(bool val)
        {
            if(val)
            {
                Interlocked.Exchange(ref Value, 1);
            } else
            {
                Interlocked.Exchange(ref Value, 0);
            }
        }
        public bool Get()
        {
            //Interlocked.Read(ref Value);
            if (Value == 1)
            {
                return true;
            }
            return false;
        }
        /*public static Pref MyVal;
        public static ref Pref CurVal()
        {
            return ref MyVal;
        }*/
    }
    class Pref
    {
        public static bool operator == (Pref one, Pref two)
        {
            Console.WriteLine("==");
            return ReferenceEquals(one, two);
        }
        public static bool operator !=(Pref one, Pref two)
        {
            Console.WriteLine("!=");
            return !ReferenceEquals(one, two);
        }
        public override bool Equals(object obj)
        {
            Console.WriteLine("Eq");
            return base.Equals(obj);
        }
    }
    class CustList<T>
    {
        protected List<T> l = new List<T>();
        public void Add(T t)
        {
            l.Add(t);
        }
        public int IndexOf(T t)
        {
            for (int i = 0; i < l.Count; i++)
            {
                //bool e = (object)l[i] == (object)t;
                //if (ReferenceEquals(l[i], t))
                if((object)l[i] == (object)t)
                {
                    return i;
                }
            }
            return -1;
        }
    }
    class NbCustList : CustList<long>
    {
        public int IndexOfNb(long t)
        {
            for (int i = 0; i < l.Count; i++)
            {
                //bool e = (object)l[i] == (object)t;
                //if (ReferenceEquals(l[i], t))
                if (l[i] == t)
                {
                    return i;
                }
            }
            return -1;
        }
    }
    struct MyStruct
    {
        public Overs o;
        public MyStruct(int s)
        {
            Console.WriteLine("ctor call");
            o = new Overs();
        }
    }
    public interface GeneInt<T,S>
    {
        void Eq(T t);
        void Eq(S t);
    }
    public class Gene<T,S>: GeneInt<T,S>
    {
        public void Eq(T t)
        {

        }
        public void Eq(S t)
        {

        }
    }
    public class SubGene : Gene<string, string>
    {
        /*public override void Eq(string t)
        {

        }*/
    }
    static class Program
    {
        const int LOWERBOUND = 0;
        const int UPPERBOUND = 1001;

        static Object lockObj = new Object();
        static Random rnd = new Random();
        static CountdownEvent cte;

        //static int totalCount = 0;
        //static int totalMidpoint = 0;
        static MyAtmicInteger myTotalCount = new MyAtmicInteger();
        static MyAtmicInteger myTotalAtMidPt = new MyAtmicInteger();
        static MyAtmicInteger myAtMidPt = new MyAtmicInteger();
        static MyAtmicInteger loading = new MyAtmicInteger();
        static MyAtmicBoolean flag = new MyAtmicBoolean();
        //static int midpointCount = 0;
        static void Opt(int i, int j=1, MyStruct tortue = new MyStruct())
        {
            GeneInt<string, string> g = new SubGene();
            //g.Eq("");
            Console.WriteLine("fct call "+tortue.o+" value "+ new MyStruct(5).o);
        }
        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Opt(0);
            //ref int i = ref myTotalCount.Value;
            //int t =  CurVal();
            /* List<string> list = new List<string>();
             list.Add("b");
             list.Add("a");
             list.Add("bb");
             list.Add("aa");
             list.Sort();
             foreach (string s in list) {
                 Console.WriteLine(s);
             }
             Console.WriteLine(list.Max(s => { return s.Length; }));
             Console.WriteLine(list.Min(s => { return s.Length; }));
             Predicate<string> predic = s => s.StartsWith("a");
             //Func<string, bool> fct = predic;
             //list.Select<string,bool>(predic);
             foreach ( int l in list.Select(s => s.Length)) {
                 Console.WriteLine("len:" + l);
             }
             foreach (string s in list.FindAll(s => s.StartsWith("a")))
             {
                 Console.WriteLine("found:"+s);
             }
             CustList<Pref> pr = new CustList<Pref>();
             Pref e = new Pref();
             pr.Add(e);
             Console.WriteLine(pr.IndexOf(e));
             NbCustList prNb = new NbCustList();
             int eNb = 2;
             prNb.Add(eNb);
             Console.WriteLine(prNb.IndexOf(eNb));
             Console.WriteLine(prNb.IndexOfNb(eNb));
             Console.WriteLine("def str:" + (default(string) == null));
             Console.WriteLine("def int:" + (default(int) == 0));*/
            //;
            //List.Sort()
            /*List<Pref> Prefs = new List<Pref>();
            Prefs.Add(new Pref());
            Prefs.Add(new Pref());
            Prefs.Sort();
            //List.Max(string::Length);
            cte = new CountdownEvent(1);
            // Start three threads. 
            for (int ctr = 0; ctr <= 2; ctr++)
            {
                cte.AddCount();
                Thread th = new Thread(GenerateNumbers);
                th.Name = "Thread" + ctr.ToString();
                th.Start();
            }
            cte.Signal();
            cte.Wait();
            Console.WriteLine();
            Console.WriteLine("Total midpoint values:  {0,10:N0} ({1:P3})",
                              myTotalAtMidPt.Value, myTotalAtMidPt.Value / ((double)myTotalCount.Value));
            Console.WriteLine("Total number of values: {0,10:N0}",
                              myTotalCount.Value);*/
            /*Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());*/

            //sstring c = (string)b;
            /*flag.Set(true);
            Thread thFl = new Thread(Display);
            Thread thLo = new Thread(Load);
            thFl.Start();
            thLo.Start();
            thFl.Join();
            thLo.Join();*/
            Overs o = new Overs();
            o.Overload("");
            OversSup o2 = new OversSup();
            o2.Overload2("");
            Overload2(o2, "");
            o2.Overload3("");
            o2.Overload3(1);
            Overload3(o2, "");
            o2 = new Overs();
            Overload3(o2, "");
            Overload4(o2, "", "");
        }

        private static void Load()
        {
            for (int i = 0; i < 10; i++)
            {
                loading.Incr();
                Thread.Sleep(3000);
            }
            flag.Set(false);
        }
        private static void Display()
        {
            int p_ = loading.Value;
            while (flag.Get())
            {
                int q_ = loading.Value;
                if (q_ != p_)
                {
                    Console.WriteLine(q_);
                    p_ = q_;
                }
            }
            Console.WriteLine(loading.Value);
            Console.WriteLine("End");
        }
        private static void GenerateNumbers()
        {
            int midpoint = (UPPERBOUND - LOWERBOUND) / 2;
            int value = 0;
            int total = 0;
            int midpt = 0;

            do
            {
                lock (lockObj)
                {
                    value = rnd.Next(LOWERBOUND, UPPERBOUND);
                }
                if (value == midpoint)
                {
                    myAtMidPt.Incr();
                    //Interlocked.Increment(ref midpointCount);
                    midpt++;
                }
                total++;
            } while (myAtMidPt.Value < 10000);
            //while (midpointCount < 10000);
            //

            //Interlocked.Add(ref totalCount, total);
            myTotalCount.Add(total);
            myTotalAtMidPt.Add(midpt);
            //Interlocked.Add(ref totalMidpoint, midpt);

            string s = String.Format("Thread {0}:\n", Thread.CurrentThread.Name) +
                       String.Format("   Random Numbers: {0:N0}\n", total) +
                       String.Format("   Midpoint values: {0:N0} ({1:P3})", midpt,
                                     ((double)midpt) / total);
            Console.WriteLine(s);
            cte.Signal();
        }
        public static void Overload2(this OversSup o, string t)
        {

        }
        public static void Overload3(this OversSup o, object t)
        {
            Console.WriteLine("super method");
        }
        public static void Overload3(this Overs o, object t)
        {
            Console.WriteLine("sub method");
        }
        public static void Overload4(this OversSup o, string p, params string[] a)
        {
            Console.WriteLine("long method");
            IControl i = new MyControl();
            i.Paint();
        }
        public static void Overload4(this OversSup o, params string[] a)
        {
            Console.WriteLine("short method");
            Overload5(o, 1);
        }
        public static void Overload5(this OversSup o, sbyte s)
        {

        }
        public static void Overload5(this OversSup o, byte s)
        {

        }
    }
    public class OversSup
    {
        public void Overload3(string a)
        {
        }
        public void Overload2(object a)
        {
        }
        public void Overload(string a)
        {
            //if (a <= "") { }
            /*Labl: for (int i = 0; i< 10; i++)
            {
                break Labl;
            }*/
            /*object Obj = null;
            bool Res = Obj is null;*/
        }
        public virtual void Rire() { }
    }
    public class Overs : OversSup
    {

        public void Overload(params string[] a)
        {

        }
        public override void Rire() { }
    }
    public class OversSub : Overs
    {
        public override void Rire() { }
    }
    interface IControl
    {
        void Paint();
    }
    class Control : IControl
    {
        void IControl.Paint() {}
    }
    class MyControl : Control, IControl
    {
        public void Paint() { Console.WriteLine("sub method Paint"); }
    }
    /*public class Book
    {
        public string Author;
        public string Title;
    }

    public class BookCollection
    {
        private Book[] books = { new Book { Title = "Call of the Wild, The", Author = "Jack London" },
                        new Book { Title = "Tale of Two Cities, A", Author = "Charles Dickens" }
                       };
        private Book nobook = null;

        public ref Book GetBookByTitle(string title)
        {
            for (int ctr = 0; ctr < books.Length; ctr++)
            {
                if (title == books[ctr].Title)
                    return ref books[ctr];
            }
            return ref nobook;
        }

        public void ListBooks()
        {
            foreach (var book in books)
            {
                Console.WriteLine($"{book.Title}, by {book.Author}");
            }
            Console.WriteLine();
        }
    }*/
}
