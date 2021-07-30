using GuiCommon;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace WindowsFormsApplication2
{
    public class ComboBoxEx : MyComboBox<CarOptions>
    {
        public override void refresh(MyList<CarOptions?> _order, string _language, bool _sortStrings)
        {
            /*if (_sortStrings)
            {
                List<CarOptions?> sortedByString_ = new List<CarOptions?>(_order);
                //			sortedByString_.sort(new Comparator<Statistic>(){
                //				public int compare(Statistic _o1, Statistic _o2) {
                //					Map<Statistic,String> tr_;
                //					tr_ = getFacade().getData().getTranslatedStatistics().getVal(Constants.getLanguage());
                //					return tr_.getVal(_o1).compareTo(tr_.getVal(_o2));
                //				}
                //			});
                sortedByString_.sortElts(new ComparatorStatisticTr(getFacade().getData(), Constants.getLanguage()));
                Map<CarOptions?, String> tr_;
                tr_ = getFacade().getData().getTranslatedStatistics().getVal(Constants.getLanguage());
                refresh(sortedByString_, tr_);
            }
            else {
                Map<CarOptions?, String> tr_;
                tr_ = getFacade().getData().getTranslatedStatistics().getVal(Constants.getLanguage());
                refresh(_order, tr_);
            }*/
        }
    }
}
