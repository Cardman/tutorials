using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace FormatHtml
{
    public class Configuration
    {
        private String assembly = "";

        private String firstUrl = "";

        private Map<String, Validator> validators = new Map<String, Validator>();

        private Map<String, Translator> translators = new Map<String, Translator>();

        private Map<String, Bean> beans = new Map<String, Bean>();

        private Map<String, Map<String, String>> navigation = new Map<String, Map<String, String>>();

        private Map<String, String> properties = new Map<String, String>();

        private String messagesFolder = "";

        public String getAssembly()
        {
            return assembly;
        }

        public void setAssembly(String _assembly)
        {
            assembly = _assembly;
        }

        public String getFirstUrl()
        {
            return firstUrl;
        }

        public void setFirstUrl(String _firstUrl)
        {
            firstUrl = _firstUrl;
        }

        public Map<String, Validator> getValidators()
        {
            return validators;
        }

        public void setValidators(Map<String, Validator> _validators)
        {
            validators = _validators;
        }

        public Map<String, Translator> getTranslators()
        {
            return translators;
        }

        public void setTranslators(Map<String, Translator> _translators)
        {
            translators = _translators;
        }

        public Map<String, Bean> getBeans()
        {
            return beans;
        }

        public void setBeans(Map<String, Bean> _beans)
        {
            beans = _beans;
        }

        public Map<String, Map<String, String>> getNavigation()
        {
            return navigation;
        }

        public void setNavigation(Map<String, Map<String, String>> _navigation)
        {
            navigation = _navigation;
        }

        public Map<String, String> getProperties()
        {
            return properties;
        }

        public void setProperties(Map<String, String> _properties)
        {
            properties = _properties;
        }

        public String getMessagesFolder()
        {
            return messagesFolder;
        }

        public void setMessagesFolder(String _messagesFolder)
        {
            messagesFolder = _messagesFolder;
        }
    }
}
