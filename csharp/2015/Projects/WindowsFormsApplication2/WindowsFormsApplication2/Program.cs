using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization.Formatters.Binary;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Util;

namespace WindowsFormsApplication2
{
    static class Program
    {
        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //Application.EnableVisualStyles();
            //Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new Form1());
            CompilerParameters parameters = new CompilerParameters();
            parameters.GenerateExecutable = false;
            parameters.GenerateInMemory = true;
            parameters.ReferencedAssemblies.Add("System.dll");
            //parameters.OutputAssembly = "AutoGen.dll";

            CompilerResults r = CodeDomProvider.CreateProvider("CSharp").CompileAssemblyFromSource(parameters, "using System.Collections.Generic;namespace Toto{public class B {public static int k=7;public List<B> list;}}", "public class C {public static int k=6;}");
            Assembly as_ = r.CompiledAssembly;
            Console.WriteLine(r.PathToAssembly);
            //verify generation
            // Console.WriteLine(Assembly.LoadFrom("AutoGen.dll").GetType("B").GetField("k").GetValue(null));
            Console.WriteLine(as_.GetName().Name);
            foreach (TypeInfo t in as_.DefinedTypes)
            {
                Console.WriteLine(t.AsType()+"%%%");
            }
            foreach (AssemblyName a in typeof(Form1).Assembly.GetReferencedAssemblies()) {
                Console.WriteLine(a.Name);
            }
            Console.WriteLine("%%%");
            Console.WriteLine(typeof(MyList<string>).FullName);
            Console.WriteLine(typeof(MyList<>).FullName);
            Console.WriteLine(typeof(MyList<string>).BaseType.FullName);
            Console.WriteLine(typeof(MyList<>).BaseType.FullName);
            Map<string, string> map_ = new Map<string, string>();
            map_.put("B.cs", "using System.Collections.Generic;namespace Toto{public class B {public static int k=7;public List<B> list = new List<B>();}}");
            map_.put("C.cs", "namespace Toto{public class C {public static int k=6;}}");
            Thread workerThread_ = new Thread(new MemoryCompiler(map_, new StringList("System.dll")).compileFiles);
            workerThread_.Start();
            //Console.WriteLine(as_.Location);
            //Console.WriteLine(as_.GetType("Toto.B").GetField("k").GetValue(null));
            //Console.WriteLine(as_.GetType("C").GetField("k").GetValue(null));
            //Console.WriteLine(Constants.getTypeFullString(as_.GetType("Toto.B").GetField("list").FieldType));
            //Console.WriteLine(Constants.getTypeFullString(typeof(List<string>)));
            //string typeStr_ = as_.GetType("Toto.B").GetField("list").FieldType.ToString();
            //typeStr_ = Constants.getTypeFullString(as_.GetType("Toto.B").GetField("list").FieldType);
            //typeStr_ = typeStr_.Replace("[.", "[");
            //int indexDot_ = typeStr_.IndexOf(".");
            //string lib_ = typeStr_.Substring(0, indexDot_);
            //string type_ = typeStr_.Substring(indexDot_ + 1);
            //Console.WriteLine(as_.GetType(type_, false, true));
            //Type gene_ = typeof(List<>);
            //Console.WriteLine(gene_.MakeGenericType(as_.GetType("Toto.B")));
            //byte[] dllAsArray;

            /*using (MemoryStream stream = new MemoryStream())

            {

                BinaryFormatter formatter = new BinaryFormatter();

                formatter.Serialize(stream, as_);

                dllAsArray = stream.ToArray();

            }*/
            //Constants.setAssembly(as_);
            //Console.WriteLine("%%"+(Constants.classForName("mscorlib.System.Collections.Generic.List`1[[Toto.B, .]]") == gene_.MakeGenericType(as_.GetType("Toto.B"))));
            //Console.WriteLine(Assembly.Load(dllAsArray) == as_);
            //Assembly.
            //Console.WriteLine(Assembly.Load("AutoGen").GetType("B").GetField("k").GetValue(null));
            //Console.WriteLine(Assembly.Load("AutoGen").GetType("C").GetField("k").GetValue(null));
        }
    }
}