using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApplication1
{
    public static class ExtCards
    {//Use this class only for no parameter methods
        public static List<Cards> getTrumps()
        {
            List<Cards> l_ = new List<Cards>();
            foreach (Cards s in typeof(Cards).GetEnumValues())
            {
                if (s.isTrump())
                {
                    l_.Add(s);
                }
            }
            return l_;
        }
        public static string name(this Cards _c)
        {
            return typeof(Cards).GetEnumName(_c);
        }
        public static bool isTrump(this Cards _c)
        {
            if (_c == Cards.EXCUSE)
            {
                return false;
            }
            return true;
        }
        public static string ToFormattedString(this Cards _c)
        {
            if (_c == Cards.EXCUSE)
            {
                return "L'Excuse";
            }
            if (_c == Cards.TRUMP_21)
            {
                return "21 d'Atout";
            }
            if (_c == Cards.TRUMP_1)
            {
                return "1 d'Atout";
            }
            return "";
        }
    }
    public enum Cards
    {
        EXCUSE,
        TRUMP_21,
        TRUMP_1
    }

    public static class ExtensionsEnum
    {
        public static string getFullName(this Enum _o)
        {
            Type t_ = _o.GetType();
            return t_.Assembly.GetName().Name + "." + t_ .Namespace+ "." + t_.Name + "."+_o.ToString();
        }
    }
}
