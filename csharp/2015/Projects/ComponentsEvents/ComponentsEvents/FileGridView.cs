using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ComponentsEvents
{
    public partial class FileGridView : DataGridView
    {
        public FileGridView()
        {
            InitializeComponent();
            ColumnCount = 1;
            Columns.Add("Name", "Name");
        }
    }
}
