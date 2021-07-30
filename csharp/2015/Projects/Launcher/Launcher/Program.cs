using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Launcher
{
    static class Program
    {
        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);


            //At init
            Label lab = new Label();
            Console.WriteLine(lab.Font.Size);
            Form1 form = new Form1();
            form.mainForm = form;

            //validate code and initialize static members

            //begin sample of static invokeLater
            MyRun r_ = new MyRun();
            r_.form = form;
            form.del2 = r_.Run;
            //end sample of static invokeLater

            //Code initializing the window
            form.InitializeComponent();
            Application.Run(form);
            
            //Process errors
        }
    }
    public class Pr
    {
        public delegate void ini(Form1 form);

        public void init(Form1 form)
        {
            Console.WriteLine(form.Size.Height);
            Console.WriteLine(form.Size.Width);
            //Application.Run(new Form1());
        }
    }
    public class MyRun : Runnable
    {
        public Form1 form;
        public void Run()
        {
            Console.WriteLine("Run size");
            Console.WriteLine(form.Size.Height);
            Console.WriteLine(form.Size.Width);
        }
    }
    public interface Runnable
    {
        void Run();
    }
}
