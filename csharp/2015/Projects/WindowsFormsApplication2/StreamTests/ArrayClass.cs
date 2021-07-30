using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StreamTests
{
    public class ArrayClass
    {
        private int[] sampleArray;
        public ArrayClass()
        {
            sampleArray = new int[0];
        }
        public ArrayClass(int _len)
        {
            sampleArray = new int[_len];
        }
        public int[] getSampleArray()
        {
            return sampleArray;
        }
        public void setSampleArray(int[] _sampleArray)
        {
            sampleArray = _sampleArray;
        }
    }
}
