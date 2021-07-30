using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ThreadsPoolGui
{
    public class WorkItemCompletedEventArgs : EventArgs
    {

        public string Result { get; private set; }

        public WorkItemCompletedEventArgs(string result)
        {
            this.Result = result;
        }
    }
}
