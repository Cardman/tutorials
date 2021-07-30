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
    public partial class MyDockPanel : Panel
    {
        public MyDockPanel()
        {
            InitializeComponent();
        }

        public MyDockPanel(IContainer container)
        {
            container.Add(this);

            InitializeComponent();
        }
        public Panel getPanelOne()
        {
            return panel1;
        }
        public Panel getPanelTwo()
        {
            return panel2;
        }
        public Panel getPanelThree()
        {
            return panel3;
        }
        public Panel getPanelFour()
        {
            return panel4;
        }
        public Panel getPanelFive()
        {
            return panel5;
        }
    }
}
