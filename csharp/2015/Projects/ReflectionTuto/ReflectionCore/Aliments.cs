using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReflectionCore
{
    public class Aliments<T> : List<T> where T : Nourriture
    {
        public Aliments()
        {

        }
    }
}
