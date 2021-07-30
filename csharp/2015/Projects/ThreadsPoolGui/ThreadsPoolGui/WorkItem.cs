using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ThreadsPoolGui
{
    public class WorkItem
    {
        //async operation representing the work item
        private AsyncOperation op;

        //event handler to be run when work has completed with a result
        public event EventHandler<WorkItemCompletedEventArgs> Completed;

        public void DoWork()
        {
            //get new async op object ***from current synchronisation context***
            //which is the caller's sync context (i.e. the form's)
            this.op = AsyncOperationManager.CreateOperation(null);
            //queue work so a thread from the thread pool can pick it
            //up and execute it
            //ThreadPool.QueueUserWorkItem((o) => { this.PerformWork(); });
            ThreadPool.QueueUserWorkItem(PerformWorkObject);
        }
        private void PerformWorkObject(object o)
        {
            PerformWork();
        }
        private void PerformWork()
        {
            //do work here...
            //The work could use passed state data 
            //held in properties of this class
            //if we needed to pass in data from the UI
            //for example 
            for (int i = 0; i < 5; i++)
            {
                Thread.Sleep(1000);
                //Call a method that is executed while the thread is running
                //The method Post of the class AsyncOperation is very useful
                //because you can call it more than once.
                //op.Post((o) => { this.OnCompleted(new WorkItemCompletedEventArgs(o.ToString())); }, "Update with result " + i + "!");
                op.Post(CallComplete, "Update with result " + i + "!");
            }
            Thread.Sleep(1000);
            //once completed, call the post completed method, passing in the result
            this.PostCompleted("Update with result!");
        }


        private void PostCompleted(string result)
        {
            //complete the async operation, calling OnCompleted, passing in the result to it
            // The lambda passed into this method is invoked on the synchronisation context
            //the async operation was created on (i.e. the form's)
            //op.PostOperationCompleted((o) => { this.OnCompleted(new WorkItemCompletedEventArgs(o.ToString())); }, result);
            op.PostOperationCompleted(CallComplete, result);
        }

        protected void CallComplete(object _o)
        {
            OnCompleted(new WorkItemCompletedEventArgs(_o.ToString()));
        }

        protected virtual void OnCompleted(WorkItemCompletedEventArgs e)
        {
            //raise the Completed event ***on the form's synchronisation context***
            EventHandler<WorkItemCompletedEventArgs> temp = this.Completed;
            if (temp != null)
            {
                temp.Invoke(this, e);
            }
        }
    }
}
