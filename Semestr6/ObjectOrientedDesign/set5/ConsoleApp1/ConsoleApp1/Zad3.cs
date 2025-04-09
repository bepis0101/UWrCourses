using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{ 
    public class Zad3
    {
        // Comparison<int> to be converted

        public class ComparisonAdapter : IComparer
        {
            private readonly Comparison<int> _cmp;

            public ComparisonAdapter(Comparison<int> cmp)
            {
                _cmp = cmp;
            }

            public int Compare(object x, object y)
            {
                return _cmp((int)x, (int)y);
            }
        }
    }

}
