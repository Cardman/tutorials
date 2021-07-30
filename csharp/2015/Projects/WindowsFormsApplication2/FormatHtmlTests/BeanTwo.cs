using FormatHtml;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace FormatHtmlTests
{
    public class BeanTwo : Bean
    {
        private bool checkedField;

	    private String typedString;

        private EnumNumber chosenNumber;

        private int typedInt;

        private Rate rate;

        private Boolean? nullableCheckbox;

        private long? nullableInt;

        private String newOld = "";

        private String field;

        private String choose1_2;

        public override void beforeDisplaying()
        {
            chosenNumber = EnumNumber.TWO;
            if (typedString == null)
            {
                typedString = "TYPED_STRING";
            }
            else {
                typedString += 2;
            }
        }


        public MyList<EnumNumber> getChosenNumbers()
        {
            MyList<EnumNumber> enums_ = new MyList<EnumNumber>();
            enums_.Add(EnumNumber.ONE);
            enums_.Add(EnumNumber.TWO);
            enums_.Add(EnumNumber.THREE);
            return enums_;
        }

        public String go(long _index)
        {
            getForms().put("checked", checkedField);
            getForms().put("typedString", typedString);
            getForms().put("chosenNumber", chosenNumber);
            getForms().put("typedInt", typedInt);
            getForms().put("rate", rate);
            getForms().put("nullableCheckbox", nullableCheckbox);
            getForms().put("nullableInt", nullableInt);
            getForms().put("field", field);
            if (typedString.Length + _index > 5)
            {
                return "change";
            }
            return "no_change";
        }

        public String go()
        {
            getForms().put("checked", checkedField);
            getForms().put("typedString", typedString);
            getForms().put("chosenNumber", chosenNumber);
            getForms().put("typedInt", typedInt);
            getForms().put("rate", rate);
            getForms().put("nullableCheckbox", nullableCheckbox);
            getForms().put("nullableInt", nullableInt);
            getForms().put("field", field);
            if (typedString.Length > 5)
            {
                return "change";
            }
            return "no_change";
        }

        public void validate()
        {
            if (typedString == null)
            {
                typedString = "";
            }
            getForms().put("checked", checkedField);
            getForms().put("typedString", typedString);
            getForms().put("chosenNumber", chosenNumber);
            getForms().put("typedInt", typedInt);
            getForms().put("rate", rate);
            getForms().put("nullableCheckbox", nullableCheckbox);
            getForms().put("nullableInt", nullableInt);
            getForms().put("field", field);
        }


        public String choose(long _index)
        {
            return _index.ToString();
        }

        public void changeText(ValueChangeEvent _event)
        {
            newOld = _event.getNewValue() + " " + _event.getOldValue();
        }

        public bool isChecked()
        {
            return checkedField;
        }

        public void setChecked(bool _checked)
        {
            checkedField = _checked;
        }


        public String getTypedString()
        {
            return typedString;
        }

        public void setTypedString(String _typedString)
        {
            typedString = _typedString;
        }


        public void setChosenNumber(EnumNumber _chosenNumber)
        {
            chosenNumber = _chosenNumber;
        }

        public EnumNumber getChosenNumber()
        {
            return chosenNumber;
        }

        public void setRate(Rate _rate)
        {
            rate = _rate;
        }

        public Rate getRate()
        {
            return rate;
        }

        public String getNewOld()
        {
            return newOld;
        }

        public int getTypedInt()
        {
            return typedInt;
        }

        public void setTypedInt(int _typedInt)
        {
            typedInt = _typedInt;
        }

        public Boolean? getNullableCheckbox()
        {
            return nullableCheckbox;
        }

        public void setNullableCheckbox(Boolean? _nullableCheckbox)
        {
            nullableCheckbox = _nullableCheckbox;
        }

        public long? getNullableInt()
        {
            return nullableInt;
        }

        public void setNullableInt(long? _nullableInt)
        {
            nullableInt = _nullableInt;
        }

        public String getField()
        {
            return field;
        }

        public void setField(String _field)
        {
            field = _field;
        }

        public void setNewOld(String _newOld)
        {
            newOld = _newOld;
        }
    }
}
