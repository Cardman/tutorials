using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;

namespace ThreadsPoolGui
{
    public class Ex {
        public virtual void run() {
        }
    }
    public class MainWindow : Form
    {
        private string Result { get { return this.txtResult.Text; } set { this.txtResult.Text = value; } }
        private TextBox txtResult;
        private Button btnStart;
        public MainWindow(string[] _args)
        {
            SuspendLayout();
            Ex e = new Ex();
            txtResult.Invoke(new Action(e.run));
            //Thread t = new Thread(e.run);
            //t.
            setTitle(_args);
            btnStart = new Button();
            btnStart.Text = "start";
            btnStart.MouseUp += new MouseEventHandler(btnStart_Click);
            Controls.Add(btnStart);
            txtResult = new TextBox();
            Controls.Add(txtResult);
            txtResult.Location = new Point(0, btnStart.Height);
            //InitializeComponent();
            ResumeLayout(false);
            PerformLayout();
            FormClosing += new FormClosingEventHandler(closeWindow);
        }
        public void closeWindow(object _sender, FormClosingEventArgs _args)
        {
            Console.WriteLine(_args == null);
            /*if (_args == null)
            {
                return;
            }*/
            MessageDialog dial_ = MessageDialog.getDialog(this);
            //Console.WriteLine(dial_.isOk());
            if (dial_.isOk())
            {
                Hide();
                Environment.Exit(0);
            } else
            {
                _args.Cancel = true;
            }
            
        }
        public void setTitle(string[] _args)
        {
            if (_args.Length > 0)
            {
                Text = _args[0];
            } else
            {
                Text = "no title";
            }
        }
        private void btnStart_Click(object sender, EventArgs e)
        {
            //start work
            this.StartBackgroundWork();
        }

        private void StartBackgroundWork()
        {
            //create new work item
            //We could pass in any state data to use in the
            //operation into the constructor here. We'd have
            //to write the constructor first through, obviously ;)/>
            WorkItem item = new WorkItem();
            //subscribe to be notified when result is ready
            item.Completed += item_Completed;
            //start work going from form
            item.DoWork();
        }

        //handler method to run when work has completed
        private void item_Completed(object sender, WorkItemCompletedEventArgs e)
        {
            //GUI is free to update itself
            this.Result = e.Result;
        }
    }

}
