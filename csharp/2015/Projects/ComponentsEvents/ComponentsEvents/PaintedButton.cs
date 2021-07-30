using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ComponentsEvents
{
    public class PaintedButton : Button
    {
        private bool clicked;
        public void setClicked(bool _clicked)
        {
            clicked = _clicked;
            Update();
        }
        public bool isClicked()
        {
            return clicked;
        }
        protected override void OnPaint(PaintEventArgs _event)
        {
            Brush brush_;
            Brush penBrush_;
            if (clicked)
            {
                brush_ = new SolidBrush(Color.FromArgb(255, 0, 0));
                penBrush_ = new SolidBrush(Color.FromArgb(255, 255, 0));
            } else
            {
                brush_ = new SolidBrush(Color.FromArgb(0, 0, 255));
                penBrush_ = new SolidBrush(Color.FromArgb(0, 255, 255));
            }
            _event.Graphics.FillRectangle(brush_, new Rectangle(0, 0, Width, Height));
            _event.Graphics.DrawString(Text,
                new Font("Arial", 10), penBrush_, new Point(0, 0));
            brush_.Dispose();
            penBrush_.Dispose();
        }
    }
}
