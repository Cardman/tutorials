using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace FormatHtml
{
    public class Bean
    {
        [NonSerialized()]
        private Object dataBase;

        [NonSerialized()]
        private Map<String, Object> forms;

        private String scope;

        private String className;

        [NonSerialized()]
        private String language;

        //[NonSerialized()]
        //private Navigation navigation;

        public Bean()
        {
            className = Constants.getTypeFullString(GetType());
        }

        public virtual void beforeDisplaying()
        {
        }

        public Object getDataBase()
        {
            return dataBase;
        }

        internal void setDataBase(Object _dataBase)
        {
            dataBase = _dataBase;
        }

        public Map<String, Object> getForms()
        {
            return forms;
        }

        public void setForms(Map<String, Object> _forms)
        {
            if (_forms == null)
            {
                return;
            }
            forms = _forms;
        }

        public String getScope()
        {
            return scope;
        }

        public void setScope(String _scope)
        {
            if (_scope == null)
            {
                return;
            }
            scope = _scope;
        }

        public String getClassName()
        {
            return className;
        }

        internal void setClassName(String _className)
        {
            className = _className;
        }

        protected String getLanguage()
        {
            return language;
        }

        internal void setLanguage(String _language)
        {
            language = _language;
        }

        /*internal Navigation getNavigation()
        {
            return navigation;
        }

        internal void setNavigation(Navigation _navigation)
        {
            navigation = _navigation;
        }*/
    }
}
