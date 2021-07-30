using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Project1
{
    class Class1
    {
        public static void Main(string[] _args) {
            foreach (string s in ObtenirListeDePrenoms())
            {
                Console.WriteLine(s);
            }
            
        }
        public static IEnumerable<string> ObtenirListeDePrenoms()
        {
            yield return "Nicolas";
            yield return "Jérémie";
            yield return "Delphine";
        }
    }

}
