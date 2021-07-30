using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ComponentsEvents
{
    public class MySpliterPane : SplitContainer
    {
        public MySpliterPane()
        {
            
        }
        protected override void OnSizeChanged(EventArgs e)

        {

            if (this.Handle != null)

            {

                this.BeginInvoke((MethodInvoker)delegate

                {

                    base.OnSizeChanged(e);

                });

            }

        }
    }
}
