using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Util;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        private ComboBoxEx combo;
        public Form1()
        {
            InitializeComponent();
            combo = new ComboBoxEx();
            combo.setWithDefaultValue(true);
            Map<CarOptions?, string> m_ = new Map<CarOptions?, string>();
            m_.put(CarOptions.FogLights,"lights");
            m_.put(CarOptions.SunRoof, "roof");
            combo.refresh(m_);
            combo.SelectedIndexChanged += chgt;
            Controls.Add(combo);
        }

        private void chgt(object sender, EventArgs e)
        {
            Console.WriteLine(combo.getCurrent() == null);
        }
    }
}
