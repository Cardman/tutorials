using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using System.Reflection;
using ReflectionCore;

namespace ReflectionTuto
{
    class MainWindow : Form
    {
        private TextBox textBox;
        public MainWindow(params string[] _args)
        {
            textBox = new TextBox();
            textBox.Multiline = true;
            Assembly ass_ = Assembly.Load("ReflectionCore");
            Type loadedType_ = ass_.GetType("ReflectionCore.MyClass");
            MethodInfo methodFrom_ = ConverterMethod.getFromStringMethod(loadedType_);
            MethodInfo methodTo_ = ConverterMethod.getToStringMethod(loadedType_);
            object obj_ = methodFrom_.Invoke(null, new object[] { "2" });
            MyClass cl_ = obj_ as MyClass;
            string text_ = "From " + methodFrom_.Name + " " + cl_.getInteger() + "\r\n";
            text_ += "To " + methodTo_.Name + " " + methodTo_.Invoke(cl_, new object[] { }) + "\r\n";
            foreach (PropertyInfo f in ConverterMethod.getFields(loadedType_))
            {
                text_ += f.Name+": "+f.PropertyType+ "\r\n";
            }
            Type loadedGenericType_ = ass_.GetType("ReflectionCore.GenericType`1");
            if (loadedGenericType_ == null) {
                text_ += "type not found: ReflectionCore.GenericType\r\n";
            } else {
                text_ += loadedGenericType_.ToString() + "\r\n";
                text_ += loadedGenericType_.BaseType.ToString()+ "\r\n";
            }
            Aliments<Nourriture> n;
            n = new Aliments<Nourriture>();
            n.Add(new Pomme());
            n.Add(new BoudinNoir());
            foreach (Nourriture no in n)
            {
                text_ += no.GetType() + "\r\n";
            }
            textBox.Text = text_;
            textBox.Size = new Size(300,100);
            Controls.Add(textBox);
        }
    }
}
