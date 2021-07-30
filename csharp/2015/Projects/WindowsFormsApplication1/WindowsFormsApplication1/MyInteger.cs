using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApplication1
{
    public class MyInteger
    {
        private int champ { get; set; }

        public MyInteger()
        {
            champ = 0;
        }

        public MyInteger(int _field)
        {
            champ = _field;
        }

        public MyInteger sum(MyInteger _other)
        {
            MyInteger sum_ = new MyInteger(champ);
            sum_.champ += _other.champ;
            return sum_;
        }
        public MyInteger prod(MyInteger _other)
        {
            MyInteger sum_ = new MyInteger(champ);
            sum_.champ *= _other.champ;
            return sum_;
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public string name()
        {
            return "new name: " + champ;
        }
        public override bool Equals(object _other)
        {
            if (_other == null)
            {
                return false;
            }
            /*if (myInt_ == null)
            {
                return false;
            }*/
            if (_other.GetType() != typeof(MyInteger))
            {
                return false;
            }
            MyInteger myInt_ = _other as MyInteger;
            return myInt_.champ == champ;
        }
        public override string ToString()
        {
            return ""+ champ;
        }
        public int getField()
        {
            return champ;
        }

        public void setField(int _field)
        {
            champ = _field;
        }
        public int getChamp()
        {
            return champ;
        }
        public void setChamp(int _field)
        {
            champ = _field;
        }
    }
}
