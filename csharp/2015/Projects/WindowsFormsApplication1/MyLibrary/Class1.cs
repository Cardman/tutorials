using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyLibrary
{
    public class MyIntegerLib
    {
        private int field;

        public MyIntegerLib()
        {
            field = 0;
        }

        public MyIntegerLib(int _field)
        {
            field = _field;
        }

        public static IEnumerable<string> ObtenirListeDePrenoms()
        {

            yield return "Nicolas";

            yield return "Jeremie";

            yield return "Delphine";

        }

        public MyIntegerLib sum(MyIntegerLib _other)
        {
            MyIntegerLib sum_ = new MyIntegerLib(field);
            sum_.field += _other.field;
            return sum_;
        }
        public MyIntegerLib prod(MyIntegerLib _other)
        {
            MyIntegerLib sum_ = new MyIntegerLib(field);
            sum_.field *= _other.field;
            return sum_;
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
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
            if (_other.GetType() != typeof(MyIntegerLib))
            {
                return false;
            }
            MyIntegerLib myInt_ = _other as MyIntegerLib;
            return myInt_.field == field;
        }
        public override string ToString()
        {
            return "" + field;
        }
        public int getField()
        {
            return field;
        }

        public void setField(int _field)
        {
            field = _field;
        }
    }
}
