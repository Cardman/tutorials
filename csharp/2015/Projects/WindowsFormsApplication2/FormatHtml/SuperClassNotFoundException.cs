using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FormatHtml
{
    public class SuperClassNotFoundException: Exception
    {
        private const String CONCAT = " - ";

	    public SuperClassNotFoundException()
        {
        }

        public SuperClassNotFoundException(String _className, String _typedName)
            : base(_className + CONCAT + _typedName)
        {
        }
    }
}
