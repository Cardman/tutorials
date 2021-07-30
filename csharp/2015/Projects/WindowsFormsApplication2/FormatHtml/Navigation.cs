using Stream;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace FormatHtml
{
    public class Navigation
    {
        private const String EXT = ".";

        private const String FORMAT_PNG = "png";

        private const String PROPERTIES = ".properties";

        private const String CSS = ".css";

        private const String XML = ".xml";

        private const String HTML = ".html";

        private const String TXT = ".txt";

        private const String JPG = ".jpg";

        private const String PNG = ".png";

        private const String END_PATH = ":";

        private const String BEGIN_ARGS = "(";

        private const String ATTRIBUTE_TITLE = "title";

        private const String ATTRIBUTE_HREF = "href";

        private const String TAG_A = "a";

        private const String REF_TAG = "#";

        private const String TAG_HEAD = "head";

        private const String TAG_TITLE = "title";

        private const String PAGE = "page";

        private const String SESSION = "session";

        private const String SELECTED = "selected";

        private const String TAG_OPTION = "option";

        private const String CHECKED = "checked";

        private const String ATTRIBUTE_VALUE = "value";

        private const String ATTRIBUTE_VALUE_MESSAGE = "valueMessage";

        private const String ATTRIBUTE_FOR = "for";

        private const String TAG_SPAN = "span";

        private const String REG_EXP_POSITIVE_INT = "([0-9]+)";

        private const String OFF = "off";

        private const String SEP_FIELDS = "&";

        private const String SEP_KEY_VALUE = "=";

        private const String ENCODE_U_Y_UML = "%u0178";

        private const String ENCODE_URL = "%C3%";

        private const String ON = "on";

        private const String TAG_SELECT = "select";

        private const String CHECKBOX = "checkbox";

        private const String TEXT = "text";

        private const String RANGE = "range";

        private const String RADIO = "radio";

        private const String NUMBER = "number";

        private const String ATTRIBUTE_TYPE = "type";

        private const String ATTRIBUTE_VALUE_CHANGE_EVENT = "valueChangeEvent";

        private const String ATTRIBUTE_VALIDATOR = "validator";

        private const String ATTRIBUTE_ID = "id";

        private const String TAG_INPUT = "input";

        private const String ATTRIBUTE_COMMAND = "command";

        private const String ATTRIBUTE_ACTION = "action";

        private const String ATTRIBUTE_NAME = "name";

        private const String TAG_FORM = "form";

        private const String COMMA = ",";

        private const String REG_EXP_ARGS = "(-?[0-9]+(,-?[0-9]+)*)";

        private const String DOT = ".";

        private const String BEGIN_REG_EXP = "^";

        private const String REG_EXP_INT = "-?[0-9]+";

        private const String CALL_METHOD = "$";

        private const String EMPTY_STRING = "";

        private const char U_Y_UML = (char)376;

        private const char MIN_EXT_ASCII = (char)128;
        private const char MAX_EXT_ASCII = (char)256;
        private const int DELTA_EXT_ASCII = 64;

        private Configuration session = new Configuration();

        private String currentBeanName;

        private String htmlText;

        private String referenceScroll;

        private String currentUrl;

        private String language;

        private Map<String, String> files;

        private Object dataBase;

        private StringList tooltips = new StringList();

        private String title = EMPTY_STRING;

        private String assembly = EMPTY_STRING;

        private String resourcesFolder = EMPTY_STRING;

        /*public void setFiles(String _assembly, String _resourcesFile)
        {
            assembly = _assembly;
            List<String> list_ = StreamZipFile.zippedFiles(_assembly);
            if (list_.isEmpty())
            {
                list_ = StreamTextFile.files(_resourcesFile);
            }
            files = new Map<String, String>();
            foreach (String f in list_)
            {
                if (f.EndsWith(PNG) || f.EndsWith(JPG))
                {
                    try
                    {
                        files.put(f, toBaseSixtyFour(f));
                    }
                    catch (Exception)
                    {
                        //e.printStackTrace();
                    }
                    continue;
                }
                if (f.EndsWith(TXT))
                {
                    try
                    {
                        BufferedImage buff_ = ConverterBufferedImageIo.readImage(f);
                        String txt_ = ConverterBufferedImage.toBaseSixtyFour(buff_, FORMAT_PNG);
                        files.put(f, txt_);
                    }
                    catch (Exception)
                    {
                        files.put(f, StreamTextFile.getContentFileInJar(assembly, f));
                    }
                }
                if (f.EndsWith(HTML) || f.EndsWith(XML) || f.EndsWith(CSS) || f.EndsWith(PROPERTIES))
                {
                    files.put(f, StreamTextFile.getContentFileInJar(assembly, f));
                }
            }
        }*/
        public void loadConfiguration(String _conf)
        {
            string confFile_ = _conf.ToLower();
            bool found_ = false;
            String fileName_ = EMPTY_STRING;
		    foreach (Entry<String, String> e in files.entryList()) {
                if (e.getKey().ToLower().Equals(confFile_))
                {
                    fileName_ = e.getKey();
                    found_ = true;
                    break;
                }
            }
            String content_;
		    if (found_) {
                content_ = files.getVal(fileName_);
            } else {
                content_ = StreamTextFile.getContentFileInJar(assembly,_conf);
            }
            content_ = content_.Replace("<.", "<"+assembly+".");
            content_ = content_.Replace("</.", "</" + assembly + ".");
            //content_ = content_.Replace(".]", assembly + "]");
            XmlDocument doc_ = XmlParser.parseSax(content_);
            XmlNodeList list_ = doc_.GetElementsByTagName("*");
            int length_ = list_.Count;
            for (int i = 0; i < length_; i++)
            {
                XmlElement elt_ = list_.Item(i) as XmlElement;
                string class_ = elt_.GetAttribute("class");
                class_ = class_.Replace(".]",assembly+"]");
                if (class_.StartsWith("."))
                {
                    elt_.SetAttribute("class", assembly+class_);
                }
            }
            content_ = XmlParser.toXml(doc_);
            session = (Configuration) SerializeXmlObject.fromXmlStringObject(content_);
            session.setAssembly(assembly);
			foreach (String b in session.getBeans().getKeys()) {
				Bean bean_ = session.getBeans().getVal(b);
				if (bean_.getClassName().StartsWith(".")) {
					bean_.setClassName(assembly+bean_.getClassName().Replace(".]", assembly + "]"));
				} else
                {
                    bean_.setClassName(bean_.getClassName().Replace(".]", assembly + "]"));
                }
			}
        }
        public void initializeSession()
        {
		    foreach (String b in session.getBeans().getKeys()) {
                Bean bean_ = newBean(session.getBeans().getVal(b));
                bean_.setForms(new Map<String, Object>());
                bean_.setDataBase(dataBase);
                bean_.setLanguage(language);
                //bean_.setNavigation(this);
                session.getBeans().put(b, bean_);
            }
            String currentUrl_ = session.getFirstUrl();
            String text_ = FormatHtml.loadPage(assembly,files, currentUrl_, resourcesFolder);
            String currentBeanName_ = FormatHtml.getCurrentBean(text_);
            htmlText = FormatHtml.processImports(text_, session, language, files, resourcesFolder);
            //For title
            currentBeanName = currentBeanName_;
            currentUrl = currentUrl_;
            setupText(htmlText);
        }
        public void processFormRequest(String _data, String _formName)
        {
            //String textToBeChanged_;
            Map<String, String> inputClasses_ = new Map<String, String>();
		    Map<String, String> changing_ = new Map<String, String>();
            Map<String, String> validators_ = new Map<String, String>();
            Map<String, String> varMethodsQuery_ = new Map<String, String>();
            Map<String, String> varMethods_ = new Map<String, String>();

            MyList<String> names_ = new MyList<String>();

            XmlDocument doc_ = XmlParser.parseSaxHtml(htmlText);
            XmlNodeList nodeList_ = doc_.GetElementsByTagName(TAG_FORM);
            int length_ = nodeList_.Count;
            String actionCommand_ = EMPTY_STRING;
            bool found_ = false;
            XmlElement formElement_ = null;
            Type longType_ = typeof(long);
            Type booleanType_ = typeof(bool);
            Type stringType_ = typeof(string);
            //retrieving form that is submitted
            for (int i = List.FIRST_INDEX; i<length_; i++) {
			    XmlElement n_ = (XmlElement)nodeList_.Item(i);
			    if (!n_.GetAttribute(ATTRIBUTE_NAME).Equals(_formName)) {
				    continue;
			    }
			    found_ = true;
			    formElement_ = n_;
			    //As soon as the form is retrieved, then process on it and exit from the loop
			    actionCommand_ = n_.GetAttribute(ATTRIBUTE_ACTION);
			    if (actionCommand_.isEmpty()
					    || actionCommand_.EndsWith(END_PATH)) {
				    actionCommand_ = n_.GetAttribute(ATTRIBUTE_COMMAND);
			    }
                XmlDocument docLoc_ = XmlParser
                .parseSaxHtml(XmlParser
                        .toXml(n_));

                //Retrieving classes for typed values
                //Retrieving methods that notify changes for values
                //Retrieving name of each field
                XmlNodeList nodeListLoc_ = docLoc_
                        .GetElementsByTagName(TAG_INPUT);
                int lengthLoc_ = nodeListLoc_.Count;
			    for (int j = List.FIRST_INDEX; j<lengthLoc_; j++) {
				    XmlElement nLoc_ = (XmlElement)nodeListLoc_.Item(j);
                    String name_ = nLoc_
                            .GetAttribute(ATTRIBUTE_NAME);
                    String id_ = nLoc_
                            .GetAttribute(ATTRIBUTE_ID);
				    if (name_.isEmpty()) {
					    continue;
				    }
				    if (!id_.isEmpty()) {
					    String validator_ = nLoc_
                                .GetAttribute(ATTRIBUTE_VALIDATOR);
					    if (!validator_.isEmpty()) {
						    validators_.put(id_, validator_);
					    }
				    }
				    names_.Add(name_);
				    varMethods_.put(name_, nLoc_.GetAttribute(FormatHtml.VAR_METHOD));
				    String changingInput_ = nLoc_
                            .GetAttribute(ATTRIBUTE_VALUE_CHANGE_EVENT);
				    if (!changingInput_.isEmpty()) {
					    changing_.put(name_, changingInput_);
				    }
				    String class_ = nLoc_
                            .GetAttribute(FormatHtml.CLASS_NAME_ATTRIBUTE);
				    if (!class_.isEmpty()) {
					    inputClasses_.put(name_, class_);
					    continue;
				    }
				    if (nLoc_.GetAttribute(
						    ATTRIBUTE_TYPE).Equals(NUMBER)) {
					    inputClasses_.put(name_,
							    Constants.getTypeFullString(longType_));
					    //continue;
				    }
				    if (nLoc_.GetAttribute(
						    ATTRIBUTE_TYPE).Equals(RANGE)) {
					    inputClasses_.put(name_,
                                Constants.getTypeFullString(longType_));
				    }
				    //Begin
				    if (nLoc_.GetAttribute(
						    ATTRIBUTE_TYPE).Equals(RADIO)) {
					    inputClasses_.put(name_,
                                Constants.getTypeFullString(longType_));
				    }
				    //End
				    if (nLoc_.GetAttribute(
						    ATTRIBUTE_TYPE).Equals(TEXT)) {
					    inputClasses_.put(name_,
							    Constants.getTypeFullString(stringType_));
				    }
				    if (nLoc_.GetAttribute(
						    ATTRIBUTE_TYPE).Equals(CHECKBOX)) {
					    inputClasses_.put(name_,
							    Constants.getTypeFullString(booleanType_));
				    }
			    }
			    nodeListLoc_ = docLoc_
                        .GetElementsByTagName(TAG_SELECT);
			    lengthLoc_ = nodeListLoc_.Count;
			    for (int j = List.FIRST_INDEX; j<lengthLoc_; j++) {
				    XmlElement nLoc_ = (XmlElement)nodeListLoc_.Item(j);
                    String name_ = nLoc_
                    .GetAttribute(ATTRIBUTE_NAME);
				    if (name_.isEmpty()) {
					    continue;
				    }
				    String id_ = nLoc_
                            .GetAttribute(ATTRIBUTE_ID);
				    if (!id_.isEmpty()) {
					    String validator_ = nLoc_
                                .GetAttribute(ATTRIBUTE_VALIDATOR);
					    if (!validator_.isEmpty()) {
						    validators_.put(id_, validator_);
					    }
				    }
				    names_.Add(name_);
				    varMethods_.put(name_, nLoc_.GetAttribute(FormatHtml.VAR_METHOD));
				    String class_ = nLoc_
                            .GetAttribute(FormatHtml.CLASS_NAME_ATTRIBUTE);
				    if (!class_.isEmpty()) {
					    inputClasses_.put(name_, class_);
				    }
			    }
			    break;
		    }

		    if (!found_) {
			    throw new FormNotFoundException(_formName);
		    }
		    //getting data from submitting form
		    Map<String, String> query_ = processDataRequest(_data, _formName,
                    names_);
		    foreach (String k in query_.getKeys()) {
			    varMethodsQuery_.put(k, EMPTY_STRING);
		    }
		    varMethodsQuery_.putAllMap(varMethods_);
		    Map<String, String> errors_;
            errors_ = new Map<String, String>();
		    Map<String, Object[]> errorsArgs_;
            errorsArgs_ = new Map<String, Object[]>();
		    foreach (String i in validators_.getKeys()) {
			    XmlElement node_ = XmlParser.getElementById(doc_, ATTRIBUTE_ID, i);
                String name_ = node_.GetAttribute(ATTRIBUTE_NAME);
                String v_ = query_.getVal(name_);
                Object obj_ = null;
			    try {
				    String className_ = inputClasses_.getVal(name_);
                    Type class_ = Constants.classForName(className_);
                    if (class_.IsEnum)
                    {
                        //Enum
                        foreach (Enum o in class_.GetEnumValues()) {
					        if (o.name().Equals(v_)) {
						        //The field value is an enum value
						        obj_ = o;
						        break;
					        }
                        }

                    }
				    
			    } catch (Exception) {
			    }
			    if (obj_ == null) {
				    try {
					    String className_ = inputClasses_.getVal(name_);
						if (className_.StartsWith(".")) {
							className_ = assembly + className_;
                        }
                        className_ = className_.Replace(".]", assembly + "]");
                        Type class_ = Constants.classForName(className_);
					    if (class_ == booleanType_) {
						    obj_ = v_.Equals(ON);
					    }
					    if (obj_ == null && class_.IsValueType) {
                            MethodInfo methNb_ = Constants.getParseMethod(class_);
                            //ConstructorInfo c_ = class_.GetConstructor(new Type[] { stringType_ });
                            object objNew_ = methNb_.Invoke(null, new object[] { v_ });
                            obj_ = objNew_;
                            /*try {
							    class_.asSubclass(Number.class);
							    obj_ = class_.getConstructor(String.class).newInstance(v_);
						    } catch (Exception e_) {
						    }*/
					    }
					    if (obj_ == null && typeof(Primitivable).IsAssignableFrom(class_)) {
                            ConstructorInfo c_ = class_.GetConstructor(new Type[] { stringType_ });
                            object objNew_ = c_.Invoke(new object[] { v_ });
                            obj_ = objNew_;
                           /*     try {
							    class_.asSubclass(Primitivable.class);
							    obj_ = class_.getConstructor(String.class).newInstance(v_);
						    } catch (Exception e_) {
						    }*/
					    }
					    if (obj_ == null) {
						    obj_ = v_;
					    }
				    } catch (Exception) {
				    }
			    }
			    String valId_ = validators_.getVal(i);
                Validator validator_ = session.getValidators().getVal(valId_);
			    try {
				    validator_.validate(this, node_, obj_);
                } catch (ValidatorException e_) {
				    errors_.put(i, e_.format());
				    errorsArgs_.put(i, e_.getArgs());
			    }
		    }
		    if (!errors_.isEmpty()) {

                processFormErrors(doc_, formElement_, query_, errors_, errorsArgs_);
			    return;
		    }
            //Setting values for bean
            updateBean(inputClasses_, changing_, query_, varMethodsQuery_);

            //invoke application
            processAnchorRequest(actionCommand_);
	    }
        private static Map<String, String> processDataRequest(String _data,
            String _formName, MyList<String> _names)
        {
            Map<String, String> query_ = new Map<String, String>();
            Map<String, String> replacedStrings_ = new Map<String, String>();

            //decode characters that are not ascii base
            for (short c = (short) MIN_EXT_ASCII; c <= MAX_EXT_ASCII; c++)
            {
                replacedStrings_.put(ENCODE_URL + c.ToString("X").ToUpper(), char.ToString((char)(c + DELTA_EXT_ASCII)));
            }
            replacedStrings_.put(ENCODE_U_Y_UML, char.ToString(U_Y_UML));
            foreach (String d in StringList.splitStrings(_data, SEP_FIELDS))
            {
                if (!d.Contains(SEP_KEY_VALUE))
                {
                    query_.put(d, EMPTY_STRING);
                }
                else {
                    String key_ = d.Substring(0, d.IndexOf(SEP_KEY_VALUE));
                    key_ = XmlParser.encodeUrlString(key_, true);
                    if (!_names.containsObj(key_))
                    {
                        if (key_.Equals(_formName))
                        {
                            continue;
                        }
                    }
                    String value_ = d.Substring(d.IndexOf(SEP_KEY_VALUE) + 1);
                    value_ = StringList.formatBasic(value_, replacedStrings_, true);
                    query_.put(key_, XmlParser.encodeUrlString(value_, false));
                }
            }
            foreach (String n in _names)
            {
                //if the value of check box is false, then it is not part of data, so default value is off
                if (!query_.contains(n))
                {
                    query_.put(n, OFF);
                }
            }
            return query_;
        }

        private void updateBean(Map<String, String> _inputClasses,
                Map<String, String> _changing, Map<String, String> _query, Map<String, String> _varMethods)

        {
            Type strType_ = typeof(string);
            foreach (String k in _query.getKeys()) {
			    if (k.isEmpty()) {
				    continue;
			    }
			    String simpleKey_ = k;
                String beanName_ = k.Substring(0, k.IndexOf(DOT));
                Bean bean_ = session.getBeans().getVal(beanName_);
                String v_ = _query.getVal(k);
                String varMethod_ = _varMethods.getVal(k);
                simpleKey_ = k.Substring(k.IndexOf(DOT) + 1);
			    Object obj_ = FormatHtml.extractObject(simpleKey_, bean_);
                Match m_ = new Regex(REG_EXP_POSITIVE_INT).Match(simpleKey_);
                MyList<long> indexes_ = new MyList<long>();
			    if (m_.Success) {
				    int nb_ = m_.Groups.Count;
				    for (int i = 1; i <= nb_; i++) {
					    indexes_.Add(long.Parse(m_.Groups[i].Value));
				    }
                }
                String changingValue_ = EMPTY_STRING;
			    if (_changing.contains(k)) {
				    String method_ = _changing.getVal(k);
				    try {
					    //checking for existence of method_ in the bean class
					    bean_.GetType().GetMethod(method_,
                                new Type[] { typeof(ValueChangeEvent) });
					    changingValue_ = method_;
				    } catch (Exception) {
				    }
			    }
                String className_ = _inputClasses.getVal(k);
				if (className_.StartsWith(".")) {
					className_ = session.getAssembly()+className_;
				}
                className_ = className_.Replace(".]", session.getAssembly() + "]");
                if (obj_ == null) {
				    //case where it is better to test on class of the value
				    Type class_ = Constants.classForName(className_);
                    if (class_.IsEnum)
                    {
                        bool success_ = false;
                        //Enum
                        foreach (Enum o in class_.GetEnumValues()) {
				            if (o.name().Equals(v_)) {
					            //The field value is an enum value
					            FormatHtml.setObject(bean_, simpleKey_, varMethod_, o,
							            changingValue_, className_, indexes_);
					            success_ = true;
					            break;
				            }
                        }
					    if (!success_) {
						    //throw new InexistingValueForEnum(v_, class_.Name);
                            throw new InexistingValueForEnum();

                        }
					    continue;
                    }
				    /*try {
					    bool success_ = false;
					    //Enum
					    for (Enum<?> o : class_.asSubclass(Enum.class).getEnumConstants()) {
						    if (o.name().equals(v_)) {
							    //The field value is an enum value
							    FormatHtml.setObject(bean_, simpleKey_, varMethod_, o,
									    changingValue_, className_, indexes_);
							    success_ = true;
							    break;
						    }
					    }
					    if (!success_) {
						    throw new InexistingValueForEnum(v_, class_.getName());
					    }
					    continue;
				    } catch (ClassCastException e) {
				    }*/
				    //Boolean
				    if (class_ == typeof(Boolean)) {
					    FormatHtml.setObject(bean_, simpleKey_, varMethod_,
							    v_.Equals(ON), changingValue_,
							    className_, indexes_);
					    continue;
				    }
                    //Number
                    if (class_.IsValueType) {
                        MethodInfo methNb_ = Constants.getParseMethod(class_);
                        //ConstructorInfo c_ = class_.GetConstructor(new Type[] { strType_ });
                        object objNew_ = methNb_.Invoke(null, new object[] { v_ });
                        FormatHtml.setObject(bean_, simpleKey_, varMethod_, objNew_, changingValue_,
							className_, indexes_);
                        continue;
                    }
				    //Number
				    /*try {
					    class_.asSubclass(Number.class);
					    FormatHtml.setObject(bean_, simpleKey_, varMethod_, class_
                                .getConstructor(String.class)
							    .newInstance(v_), changingValue_,
							    className_, indexes_);
					    continue;
				    } catch (ClassCastException e) {
				    }*/
				    //Primitivable
                    if (typeof(Primitivable).IsAssignableFrom(class_))
                    {
                        ConstructorInfo c_ = class_.GetConstructor(new Type[] { strType_ });
                        object objNew_ = c_.Invoke(new object[] { v_ });
                        FormatHtml.setObject(bean_, simpleKey_, varMethod_, objNew_, changingValue_,
                            className_, indexes_);
                        continue;
                    }
				    /*try {
					    class_.asSubclass(Primitivable.class);
					    FormatHtml.setObject(bean_, simpleKey_, varMethod_, class_
                                .getConstructor(String.class)
							    .newInstance(v_), changingValue_,
							    className_, indexes_);
					    continue;
				    } catch (ClassCastException e) {
				    }*/
			        FormatHtml.setObject(bean_, simpleKey_, varMethod_, v_,
					        changingValue_, className_, indexes_);
			        continue;
		        }
			    //Enum
			    if (obj_ is Enum) {
				    bool success_ = false;
                    foreach (Enum o in obj_.GetType().GetEnumValues())
                    {
                        if (o.name().Equals(v_))
                        {
                            //The field value is an enum value
                            FormatHtml.setObject(bean_, simpleKey_, varMethod_, o,
                                    changingValue_, className_, indexes_);
                            success_ = true;
                            break;
                        }
                    }
                    /*for (Enum<?> o : obj_.getClass().asSubclass(Enum.class)
						    .getEnumConstants()) {
					    if (o.name().equals(v_)) {
						    FormatHtml.setObject(bean_, simpleKey_, varMethod_, o,
								    changingValue_, className_, indexes_);
						    success_ = true;
						    break;
					    }
				    }*/
				    /*if (!success_) {
					    throw new InexistingValueForEnum(v_, obj_.getClass().getName());
				    }*/
                    if (!success_)
                    {
                        //throw new InexistingValueForEnum(v_, class_.Name);
                        throw new InexistingValueForEnum();

                    }
                    continue;
			    }
			    //Boolean
			    if (obj_ is Boolean) {
				    FormatHtml.setObject(bean_, simpleKey_, varMethod_, v_.Equals(ON),
						    changingValue_, className_, indexes_);
				    continue;
			    }
			    //Number, Primitivable
			    if (obj_.GetType().IsValueType) {
                    MethodInfo methNb_ = Constants.getParseMethod(obj_.GetType());
                    //ConstructorInfo c_ = obj_.GetType().GetConstructor(new Type[] { strType_ });
                    object objNew_ = methNb_.Invoke(null, new object[] { v_ });
                    FormatHtml.setObject(bean_, simpleKey_, varMethod_, objNew_, changingValue_,
						    className_, indexes_);
				    continue;
			    }
                if (obj_ is Primitivable)
                {
                    ConstructorInfo c_ = obj_.GetType().GetConstructor(new Type[] { strType_ });
                    object objNew_ = c_.Invoke(new object[] { v_ });
                    FormatHtml.setObject(bean_, simpleKey_, varMethod_, objNew_, changingValue_,
                            className_, indexes_);
                    continue;
                }
                FormatHtml.setObject(bean_, simpleKey_, varMethod_, v_, changingValue_,
					    className_, indexes_);
		    }
	    }

	    private void processFormErrors(XmlDocument _doc, XmlElement _formElement, Map<String, String> _query,
                Map<String, String> _errors, Map<String, Object[]> _errorsArgs)
        {
            //begin deleting previous errors
            XmlNodeList spansForm_ = _formElement.GetElementsByTagName(TAG_SPAN);
            int lengthSpansForom_ = spansForm_.Count;
            for (int j = List.FIRST_INDEX; j < lengthSpansForom_; j++)
            {
                XmlElement elt_ = (XmlElement)spansForm_.Item(j);
                if (!elt_.HasAttribute(ATTRIBUTE_FOR))
                {
                    continue;
                }
                XmlNodeList children_ = elt_.ChildNodes;
                int ch_ = children_.Count;
                for (int i = List.FIRST_INDEX; i < ch_; i++)
                {
                    elt_.RemoveChild(children_.Item(i));
                }
                XmlText text_ = _doc.CreateTextNode(FormatHtml.SPACE);
                elt_.AppendChild(text_);
            }
            //end deleting previous errors
            foreach (String i in _errors.getKeys())
            {
                XmlNodeList spans_ = _formElement.GetElementsByTagName(TAG_SPAN);
                int lengthSpans_ = spans_.Count;
                for (int j = List.FIRST_INDEX; j < lengthSpans_; j++)
                {
                    XmlElement elt_ = (XmlElement)spans_.Item(j);
                    if (!elt_.GetAttribute(ATTRIBUTE_FOR).Equals(i))
                    {
                        continue;
                    }
                    elt_.RemoveChild(elt_.ChildNodes.Item(0));
                    String error_ = _errors.getVal(i);
                    if (!elt_.GetAttribute(ATTRIBUTE_VALUE_MESSAGE).isEmpty())
                    {
                        error_ = FormatHtml.formatErrorMessage(session, elt_.GetAttribute(ATTRIBUTE_VALUE_MESSAGE), language, files, resourcesFolder, _errorsArgs.getVal(i));
                    }
                    XmlText text_ = _doc.CreateTextNode(error_);
                    elt_.AppendChild(text_);
                }
            }
            XmlNodeList inputs_ = _doc.GetElementsByTagName(TAG_INPUT);
            int lengthInputs_ = inputs_.Count;
            for (int i = List.FIRST_INDEX; i < lengthInputs_; i++)
            {
                XmlElement elt_ = (XmlElement)inputs_.Item(i);
                foreach (String k in _query.getKeys())
                {
                    if (!elt_.GetAttribute(ATTRIBUTE_NAME).Equals(k))
                    {
                        continue;
                    }
                    if (elt_.GetAttribute(ATTRIBUTE_TYPE).Equals(TEXT))
                    {
                        elt_.SetAttribute(ATTRIBUTE_VALUE, _query.getVal(k));
                        continue;
                    }
                    if (elt_.GetAttribute(ATTRIBUTE_TYPE).Equals(NUMBER))
                    {
                        elt_.SetAttribute(ATTRIBUTE_VALUE, _query.getVal(k));
                        continue;
                    }
                    if (elt_.GetAttribute(ATTRIBUTE_TYPE).Equals(CHECKBOX))
                    {
                        if (_query.getVal(k).Equals(ON))
                        {
                            elt_.SetAttribute(CHECKED, CHECKED);
                        }
                        else {
                            elt_.RemoveAttribute(CHECKED);
                        }
                        continue;
                    }
                }
            }
            inputs_ = _doc.GetElementsByTagName(TAG_SELECT);
            lengthInputs_ = inputs_.Count;
            for (int i = List.FIRST_INDEX; i < lengthInputs_; i++)
            {
                XmlElement elt_ = (XmlElement)inputs_.Item(i);
                foreach (String k in _query.getKeys())
                {
                    if (!elt_.GetAttribute(ATTRIBUTE_NAME).Equals(k))
                    {
                        continue;
                    }
                    XmlNodeList options_ = elt_.GetElementsByTagName(TAG_OPTION);
                    int optionsLen_ = options_.Count;
                    for (int j = List.FIRST_INDEX; j < optionsLen_; j++)
                    {
                        XmlElement option_ = (XmlElement)options_.Item(j);
                        if (option_.GetAttribute(ATTRIBUTE_VALUE).Equals(_query.getVal(k)))
                        {
                            option_.SetAttribute(SELECTED, SELECTED);
                        }
                        else {
                            option_.RemoveAttribute(SELECTED);
                        }
                    }
                }
            }
            setupText(XmlParser.toHtml(_doc));
        }
        public void processAnchorRequest(String _anchorRef)
        {
            String textToBeChanged_;
            Bean bean_;
            Map<String, Object> forms_;
            String currentUrl_;
            String currentBeanName_;
            if (_anchorRef.Contains(CALL_METHOD)) {
                Regex pattern_ = new Regex(REG_EXP_ARGS);
                int indexPoint_ = _anchorRef.IndexOf(DOT);
                String action_ = _anchorRef
                        .Substring(indexPoint_ + 1);
                String key_ = action_.replaceAll(REG_EXP_INT, EMPTY_STRING);
                Match match_ = pattern_.Match(action_);
                String argsString_ = EMPTY_STRING;
                if (match_.Success)
                {
                    argsString_ = match_.Groups[1].Value;
                    //argsString_ = match_.Value;
                }
                MyList<long> args_ = new MyList<long>();
                foreach (String l in StringList.splitStrings(argsString_, COMMA))
                {
                    if (l.isEmpty())
                    {
                        continue;
                    }
                    args_.Add(long.Parse(l));
                }
                String command_ = StringList.getFirstToken(action_, BEGIN_ARGS);
                int begin_ = _anchorRef.IndexOf(CALL_METHOD) + 1;
                String beanName_ = _anchorRef
                        .Substring(begin_, indexPoint_ - begin_);
                bean_ = session.getBeans().getVal(beanName_);
                Object return_ = FormatHtml.invokeMethodWithNumbers(
                        bean_, command_, args_.ToArray());
                forms_ = bean_.getForms();
                String urlDest_ = currentUrl;
                if (return_ != null)
                {
                    urlDest_ = session.getNavigation()
                            .getVal(beanName_ + DOT + key_)
                            .getVal(return_.ToString());
                    if (urlDest_ == null)
                    {
                        urlDest_ = currentUrl;
                    }
                }
                foreach (String b in session.getBeans().getKeys())
                {
                    if (!reinitBean(urlDest_, beanName_, b))
                    {
                        continue;
                    }
                    bean_ = session.getBeans().getVal(b);
                    bean_ = newBean(bean_);
                    bean_.setForms(forms_);
                    session.getBeans().put(b, bean_);
                }
                currentUrl_ = urlDest_;
                textToBeChanged_ = FormatHtml.loadPage(assembly,files, StringList.getFirstToken(urlDest_, REF_TAG), resourcesFolder);
                currentBeanName_ = FormatHtml
                        .getCurrentBean(textToBeChanged_);
                bean_ = session.getBeans().getVal(currentBeanName_);
                bean_.setForms(forms_);
                textToBeChanged_ = FormatHtml.processImports(
                        textToBeChanged_, session, language, files, resourcesFolder);
                currentBeanName = currentBeanName_;
                currentUrl = currentUrl_;
                setupText(textToBeChanged_);
                return;
            }
		    if (_anchorRef.isEmpty()) {
                return;
            }
            bean_ = session.getBeans().getVal(currentBeanName);
            forms_ = bean_.getForms();
		    foreach (String b in session.getBeans().getKeys()) {
                if (!reinitBean(_anchorRef, currentBeanName, b))
                {
                    continue;
                }
                bean_ = session.getBeans().getVal(b);
                bean_ = newBean(bean_);
                bean_.setForms(forms_);
                session.getBeans().put(b, bean_);
            }
            currentUrl_ = _anchorRef;
            textToBeChanged_ = FormatHtml.loadPage(assembly, files, StringList.getFirstToken(_anchorRef, REF_TAG), resourcesFolder);
            currentBeanName_ = FormatHtml
				.getCurrentBean(textToBeChanged_);
            bean_ = session.getBeans().getVal(currentBeanName_);
            bean_.setForms(forms_);
            textToBeChanged_ = FormatHtml.processImports(
				textToBeChanged_, session, language, files, resourcesFolder);
            currentBeanName = currentBeanName_;
            currentUrl = currentUrl_;
            setupText(textToBeChanged_);
        }
        public bool reinitBean(String _dest, String _beanName, String _currentBean)
        {
            if (!_currentBean.Equals(_beanName))
            {
                return false;
            }
            Bean bean_ = session.getBeans().getVal(_currentBean);
            if (bean_.getScope().Equals(SESSION))
            {
                return false;
            }
            if (bean_.getScope().Equals(PAGE))
            {
                if (currentUrl.Equals(StringList.getFirstToken(_dest, REF_TAG)))
                {
                    return false;
                }
            }
            return true;
        }
        public Bean newBean(Bean _bean)
        {
            Type t_ = Constants.classForName(_bean.getClassName());
            ConstructorInfo c_ = t_.GetConstructor(new Type[0]);
            Bean bean_ = (Bean)c_.Invoke(new object[0]);
            bean_.setDataBase(_bean.getDataBase());
            bean_.setForms(_bean.getForms());
            bean_.setClassName(_bean.getClassName());
            bean_.setLanguage(language);
            //bean_.setNavigation(this);
            bean_.setScope(_bean.getScope());
		    return bean_;
        }

        public void setupText(String _text)
        {
            String textToDisplay_ = _text;
            tooltips.Clear();
            try
            {
                XmlDocument doc_ = XmlParser.parseSaxHtml(textToDisplay_);
                XmlNodeList nodes_ = doc_.GetElementsByTagName(TAG_A);
                int size_ = nodes_.Count;
                for (int i = List.FIRST_INDEX; i < size_; i++)
                {
                    XmlNode node_ = nodes_.Item(i);
                    XmlNamedNodeMap map_ = node_.Attributes;
                    XmlNode href_ = map_.GetNamedItem(ATTRIBUTE_HREF);
                    if (href_ == null)
                    {
                        continue;
                    }
                    XmlNode title_ = map_.GetNamedItem(ATTRIBUTE_TITLE);
                    if (title_ == null)
                    {
                        continue;
                    }
                    tooltips.Add(title_.Value);
                }
            }
            catch (Exception)
            {
                //e.printStackTrace();
            }
            title = EMPTY_STRING;
            try
            {
                XmlDocument doc_ = XmlParser.parseSaxHtml(textToDisplay_);
                XmlNodeList nodes_ = doc_.GetElementsByTagName(TAG_HEAD);
                int size_ = nodes_.Count;
                for (int i = List.FIRST_INDEX; i < size_; i++)
                {
                    XmlElement node_ = (XmlElement)nodes_.Item(i);
                    XmlNodeList subNodes_ = node_.GetElementsByTagName(TAG_TITLE);
                    int subListSize_ = subNodes_.Count;
                    for (int j = List.FIRST_INDEX; j < subListSize_; j++)
                    {
                        XmlElement subNode_ = (XmlElement)subNodes_.Item(j);
                        title = XmlParser.transformSpecialChars(subNode_.InnerText.Trim());
                    }
                }
            }
            catch (Exception)
            {
                //e_.printStackTrace();
            }
            htmlText = textToDisplay_;
            StringList tokens_ = StringList.splitStrings(currentUrl, REF_TAG);
            if (tokens_.size() > List.ONE_ELEMENT)
            {
                referenceScroll = tokens_.get(List.SECOND_INDEX);
            }
            else {
                referenceScroll = EMPTY_STRING;
            }
        }

        public Configuration getSession()
        {
            return session;
        }

        public void setSession(Configuration _session)
        {
            session = _session;
        }

        public String getCurrentBeanName()
        {
            return currentBeanName;
        }

        public void setCurrentBeanName(String _currentBeanName)
        {
            currentBeanName = _currentBeanName;
        }

        public String getCurrentUrl()
        {
            return currentUrl;
        }

        public void setCurrentUrl(String _currentUrl)
        {
            currentUrl = _currentUrl;
        }

        public Map<String, String> getFiles()
        {
            return files;
        }

        public void setFiles(Map<String, String> _files)
        {
            files = _files;
        }

        public String getLanguage()
        {
            return language;
        }

        public Object getDataBase()
        {
            return dataBase;
        }

        public void setHtmlText(String _htmlText)
        {
            htmlText = _htmlText;
        }

        public void setTooltips(StringList _tooltips)
        {
            tooltips = _tooltips;
        }

        public String getTitle()
        {
            return title;
        }

        public String getResourcesFolder()
        {
            return resourcesFolder;
        }

        public void setResourcesFolder(String _resourcesFolder)
        {
            resourcesFolder = _resourcesFolder;
        }
        public void setLanguage(String _language)
        {
            language = _language;
        }
        public void setAssembly(String _assembly)
        {
            assembly = _assembly;
        }
        public void setDataBase(Object _dataBase)
        {
            dataBase = _dataBase;
        }

        public StringList getTooltips()
        {
            return tooltips;
        }

        public String getHtmlText()
        {
            return htmlText;
        }

        public String getReferenceScroll()
        {
            return referenceScroll;
        }
    }
}
