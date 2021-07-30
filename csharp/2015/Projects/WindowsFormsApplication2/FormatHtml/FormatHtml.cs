using Stream;
using System;
using System.Collections;
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
    public class FormatHtml
    {
        public const String ATTRIBUTE_CLASS_NAME = "className";

        public const String CLASS_NAME_ATTRIBUTE = ATTRIBUTE_CLASS_NAME;
        public const String NULL_STRING = "null";
        public const String SPACE = " ";
        public const String VAR_METHOD = "varMethod";

	    private const String PATH_CLASS_SEPARATOR = "^";

	    private const String ESCAPED_RIGHT_EL = "\\}";
	    private const String ESCAPED_LEFT_EL = "\\{";
	    private const String NEXT_FIELDS = "([^,\\}]+(,\\w+){0,2})";
	    private const String FORMAT_VAR = "$1";
	    private const String NEXT_ARG = "([^,]+),,";
	    private const String GET_ENTRY = "!";
	    private const String TR = "|";
	    private const String DOT_END = "\\.$";
    //	private const String ESCAPED_TR = "\\|";
	    private const String BOUNDS_EL = "\\{|\\}";
	    private const String RIGHT_EL = "}";
	    private const String LEFT_EL = "{";
	    private const String FILE = "file:";
    //	private const String REG_EXP_EL = "\\{[^\\}]*\\}";
	    private const String REG_EXP_EL = "\\{[^\\{\\}]*\\}";
	    private const String METHOD_ADD_ALL = "AddRange";
	    private const String REG_EXP_GET_INDEX = "^\\[[0-9]+\\]$";
    //for test	private const String REG_EXP_FIELD = "^\\w+$";
	    private const String REG_EXP_FIELD = "^\\w+(\\^\\w+)*$";
	    private const String REG_EXP_ARGS = "^\\([0-9]+(,[0-9]+)*\\)$";
    //for test	private const String TOKENS_CALLS = "(\\w+|\\([0-9]+(,[0-9]+)*\\)|\\[[0-9]+\\])";
	    private const String TOKENS_CALLS = "(\\w+(\\^\\w+)*|\\([0-9]+(,[0-9]+)*\\)|\\[[0-9]+\\])";
	    private const String REG_EXP_MAP_METH = "\\w+!";
	    private const String REG_EXP_GET_ARR = "(\\[|\\])";
	    private const String RETURN_LINE = "\n";
	    private const String ATTRIBUTE_SRC = "src";
	    private const String ATTRIBUTE_ENCODE_IMG = "wrap";
	    private const String TAG_IMG = "img";
	    private const String TAG_HEAD = "head";
	    private const String STYLESHEET = "stylesheet";
	    private const String TAG_STYLE = "style";
	    private const String ATTRIBUTE_REL = "rel";
	    private const String SCRIPT = "script";
	    private const String TAG_LINK = "link";
	    private const String ATTRIBUTE_TITLE = "title";
	    private const String COMMA_RIGHT_PAR = ",)";
	    private const String LEFT_PAR_COMMA = "(,";
	    private const String DOUBLE_COMMA = ",,";
	    private const String COMMA = ",";
	    private const String RIGHT_PAR = ")";
	    private const String ATTRIBUTE_ORDERED_KEYS = "orderedKeys";
	    private const String TAG_OPTION = "option";
	    private const String SELECTED = "selected";
	    private const String ATTRIBUTE_VALIDATOR = "validator";
	    private const String EMPTY_SELECT = "<select/>";
	    private const String ATTRIBUTE_UPDATE = "update";
	    private const String NEG_REG_EXP = "^!+";
	    private const String ATTRIBUTE_CONDITION = "condition";
	    private const String TR_END = "</tr>";
	    private const String TR_BEGIN = "<tr>";
	    private const String RIGHT_END_TAG = "/>";
	    private const String TAG_FORM = "form";
	    private const String TAG_A = "a";
	    private const String SUBMIT_TYPE = "submit";
	    private const String TAG_BODY = "body";
	    private const String LEFT_PAR = "(";
	    private const String ESCAPED_FORMAT_QUOTE = "''";
	    private const String FORMAT_QUOTE = "'";
	    private const String TAG_PARAM = "param";
	    private const String ATTRIBUTE_QUOTED = "quoted";
	    private const String ALL_TAGS = "*";
	    private const String ATTRIBUTE_CLASS = "class";
	    private const String ATTRIBUTE_TYPE = "type";
	    private const String SCRIPT_TYPE = "text/javascript";
	    private const String RADIO = "radio";
	    private const String ATTRIBUTE_LIST = "list";
	    private const String ATTRIBUTE_MAP = "map";
	    private const String ATTRIBUTE_ID = "id";
	    private const String SPACE_MESSAGE = " ";
	    private const String ATTRIBUTE_KEY = "key";
	    private const String ATTRIBUTE_VAR = "var";
	    private const String ATTRIBUTE_HREF = "href";
	    private const String ATTRIBUTE_COMMAND = "command";
	    private const String ATTRIBUTE_ACTION = "action";
	    private const String SELECT_TAG = "select";
	    private const String CHECKED = "checked";
	    private const String INPUT_TAG = "input";
	    private const String SPAN_TAG = "span";
	    private const String ATTRIBUTE_FOR = "for";
	    private const String ATTRIBUTE_VAR_VALUE = "varValue";
	    private const String INT_REG_EXP = "[0-9]+";
	    private const String GET_INDEX = ";;";
	    private const String GET_FORMAT_VAR = ".$1";
	    private const String ATTRIBUTE_ESCAPED = "escaped";
	    private const String GET_VALUE = "!value";
	    private const String GET_KEY = "!key";
	    private const String RIGHT_GET_ARR = "]";
	    private const String LEFT_GET_ARR = "[";
	    private const String GET_ATTRIBUTE = ";";
	    private const String CALL_AFTER = ";(.+)";
	    private const String CALL_METHOD = "$";
	    private const String DEFAULT_ATTRIBUTE = "default";
	    private const String RETURN_TAB = "\n\t";
	    private const String NO_PARAM_METHOD = "()";
	    private const String EMPTY_STRING = "";
	    private const String AMP = "&";
	    private const String E_AMP = "&amp;";
	    private const String E_GT = "&gt;";
	    private const String E_LT = "&lt;";
	    private const String ATTRIBUTE_VALUE_SUBMIT = "message";
	    private const String ATTRIBUTE_VALUE = "value";
	    /**with ATTRIBUTE_CLASS_NAME attribute*/
	    private const String ATTRIBUTE_METHOD = "method";
	    private const String ATTRIBUTE_NAME = "name";
        private const String ATTRIBUTE_ASSEMBLY = "assembly";
        private const String ATTRIBUTE_FORM = "form";
	    private const String DOT = ".";
	    private const String PAGE_ATTRIBUTE = "page";
	    private const String KEEPFIELD_ATTRIBUTE = "keepfields";
	    private const String EMPTY_HTML_DOC = "<html/>";
	    private const String BEAN_ATTRIBUTE = "bean";
	    private const String LT_END_TAG = "</";
	    private const String GT_TAG = ">";
	    private const String LT_BEGIN_TAG = "<";

	    private const String PREFIX = "c.";//:
	    private const String FOR_BLOCK_TAG = PREFIX+"for";
	    private const String IF_BLOCK_TAG = PREFIX+"if";
	    private const String SELECT_BLOCK_TAG = PREFIX+SELECT_TAG;
	    private const String MESSAGE_BLOCK_TAG = PREFIX+"message";
	    private const String IMPORT_BLOCK_TAG = PREFIX+"import";
	    private const String PACKAGE_BLOCK_TAG = PREFIX+"package";
	    private const String CLASS_BLOCK_TAG = PREFIX+ATTRIBUTE_CLASS;
	    private const String FIELD_BLOCK_TAG = PREFIX+"field";
        private const String BEG_TMP_BLOCK_TAG = PREFIX +"tmp";
        private const String TMP_BLOCK_TAG = PREFIX+"tmp";
        private const String IMG_BLOCK_TAG = PREFIX+TAG_IMG;
	    private const String A_BLOCK_TAG = PREFIX+TAG_A;
	    private const String SUBMIT_BLOCK_TAG = PREFIX+SUBMIT_TYPE;
	    private const String FORM_BLOCK_TAG = PREFIX+"form";
	    private const String TR_BEGIN_BLOCK_TAG = PREFIX+"tr_begin";
	    private const String TR_END_BLOCK_TAG = PREFIX+"tr_end";
	    private const String IMPLICIT_LANGUAGE = "//";
	    private const int ESCAPED_TOKEN = 2;
        private const int ESCAPED_TOKENS = 4;
        private static String addToRoot(String _body)
        {
            return LT_BEGIN_TAG + TMP_BLOCK_TAG + GT_TAG + _body + LT_END_TAG + TMP_BLOCK_TAG + GT_TAG;
        }

        public static String getCurrentBean(String _htmlText)
        {
            String htmlText_ = _htmlText;
		    try {
                XmlDocument doc_ = XmlParser.parseSaxHtml(htmlText_);
                XmlElement root_ = doc_.DocumentElement;
                return root_.GetAttribute(BEAN_ATTRIBUTE);
            } catch (Exception) {
            }
		    throw new XmlParseException(htmlText_);
        }
        private static void processOptionsList(Bean _o, XmlDocument _doc,
            XmlNode _currentModifiedNode, XmlNode _n, String _id)
        {
            String list_ = _n.Attributes.GetNamedItem(ATTRIBUTE_LIST).Value;
            String name_ = ((XmlElement) _n).GetAttribute(ATTRIBUTE_NAME);
            bool update_ = ((XmlElement) _n).HasAttribute(ATTRIBUTE_UPDATE);
            String varValue_ = ((XmlElement) _n).GetAttribute(ATTRIBUTE_VAR_VALUE);
            Enum returnedVarValue_ = null;
		    if (!varValue_.isEmpty()) {
                returnedVarValue_ = (Enum) extractObject(varValue_, _o);
            }
            IEnumerable extractedList_ = (IEnumerable) extractObject(list_, _o);
            String default_ = ((XmlElement) _n).GetAttribute(DEFAULT_ATTRIBUTE);
            XmlDocument docSelect_ = XmlParser.parseSaxHtml(EMPTY_SELECT);
            XmlElement docElementSelect_ = docSelect_.DocumentElement;
		    if (!_id.isEmpty()) {
                docElementSelect_.SetAttribute(ATTRIBUTE_ID, _id);
                docElementSelect_.SetAttribute(ATTRIBUTE_VALIDATOR, ((XmlElement)_n).GetAttribute(ATTRIBUTE_VALIDATOR));
            }
		    if (default_.isEmpty() || returnedVarValue_ != null && update_) {
                foreach (Object o in extractedList_)
                {
                    Enum enum_ = (Enum)o;
                    XmlElement option_ = docSelect_.CreateElement(TAG_OPTION);
                    option_.SetAttribute(ATTRIBUTE_VALUE, enum_.name());
                    if (returnedVarValue_ == enum_)
                    {
                        option_.SetAttribute(SELECTED, SELECTED);
                    }
                    option_.AppendChild(docSelect_.CreateTextNode(o.ToString()));
                    docElementSelect_.AppendChild(option_);
                }
                docElementSelect_.SetAttribute(ATTRIBUTE_NAME, name_);
                docElementSelect_.SetAttribute(CLASS_NAME_ATTRIBUTE, ((XmlElement)_n).GetAttribute(ATTRIBUTE_CLASS_NAME));
                _currentModifiedNode.AppendChild(_doc.ImportNode(docElementSelect_, true));
            } else {
                if (default_.StartsWith(CALL_METHOD))
                {
                    String command_ = default_.Substring(1);
                    Enum defaultEnum_ = (Enum) extractObject(command_, _o);
                    foreach (Object o in extractedList_)
                    {
                        Enum enum_ = (Enum)o;
                        XmlElement option_ = docSelect_.CreateElement(TAG_OPTION);
                        option_.SetAttribute(ATTRIBUTE_VALUE, enum_.name());
                        if (enum_.name().Equals(defaultEnum_.name()))
                        {
                            option_.SetAttribute(SELECTED, SELECTED);
                        }
                        option_.AppendChild(docSelect_.CreateTextNode(o.ToString()));
                        docElementSelect_.AppendChild(option_);
                    }
                    docElementSelect_.SetAttribute(ATTRIBUTE_NAME, name_);
                    docElementSelect_.SetAttribute(CLASS_NAME_ATTRIBUTE, ((XmlElement)_n).GetAttribute(ATTRIBUTE_CLASS_NAME));
                    _currentModifiedNode.AppendChild(_doc.ImportNode(docElementSelect_, true));
                }
                else {
                    foreach (Object o in extractedList_)
                    {
                        Enum enum_ = (Enum)o;
                        XmlElement option_ = docSelect_.CreateElement(TAG_OPTION);
                        option_.SetAttribute(ATTRIBUTE_VALUE, enum_.name());
                        if (enum_.name().Equals(default_))
                        {
                            option_.SetAttribute(SELECTED, SELECTED);
                        }
                        option_.AppendChild(docSelect_.CreateTextNode(o.ToString()));
                        docElementSelect_.AppendChild(option_);
                    }
                    docElementSelect_.SetAttribute(ATTRIBUTE_NAME, name_);
                    docElementSelect_.SetAttribute(CLASS_NAME_ATTRIBUTE, ((XmlElement)_n).GetAttribute(ATTRIBUTE_CLASS_NAME));
                    _currentModifiedNode.AppendChild(_doc.ImportNode(docElementSelect_, true));
                }
            }
        }

        private static void processOptionsMap(Bean _o, XmlDocument _doc,
                XmlNode _currentModifiedNode, XmlNode _n, String _map, String _id)

        {
            String name_ = ((XmlElement) _n).GetAttribute(ATTRIBUTE_NAME);
            bool update_ = ((XmlElement)_n).HasAttribute(ATTRIBUTE_UPDATE);
            String varValue_ = ((XmlElement) _n).GetAttribute(ATTRIBUTE_VAR_VALUE);
            Object returnedVarValue_ = null;
		    if (!varValue_.isEmpty()) {
                returnedVarValue_ = extractObject(varValue_, _o);
            }
            ListableKey extractedMap_ = (ListableKey) extractObject(_map, _o);
            String default_ = ((XmlElement) _n).GetAttribute(DEFAULT_ATTRIBUTE);
            XmlDocument docSelect_ = XmlParser.parseSaxHtml(EMPTY_SELECT);
            XmlElement docElementSelect_ = docSelect_.DocumentElement;
		    if (!_id.isEmpty()) {
                docElementSelect_.SetAttribute(ATTRIBUTE_ID, _id);
                docElementSelect_.SetAttribute(ATTRIBUTE_VALIDATOR, ((XmlElement)_n).GetAttribute(ATTRIBUTE_VALIDATOR));
            }
		    if (default_.isEmpty() || returnedVarValue_ != null && update_) {
                processOptionsMapEnumName(extractedMap_,
                        docSelect_, docElementSelect_,
                        returnedVarValue_);
                docElementSelect_.SetAttribute(ATTRIBUTE_NAME, name_);
                docElementSelect_.SetAttribute(CLASS_NAME_ATTRIBUTE, ((XmlElement)_n).GetAttribute(ATTRIBUTE_CLASS_NAME));
                _currentModifiedNode.AppendChild(_doc.ImportNode(docElementSelect_, true));
            } else {
                if (default_.StartsWith(CALL_METHOD))
                {
                    String command_ = default_.Substring(1);
                    Object defaultEnum_ = extractObject(command_, _o);
                    processOptionsMapEnumName(extractedMap_,
                            docSelect_, docElementSelect_,
                            defaultEnum_);
                    docElementSelect_.SetAttribute(ATTRIBUTE_NAME, name_);
                    docElementSelect_.SetAttribute(CLASS_NAME_ATTRIBUTE, ((XmlElement)_n).GetAttribute(ATTRIBUTE_CLASS_NAME));
                    _currentModifiedNode.AppendChild(_doc.ImportNode(docElementSelect_, true));
                }
                else {
                    processOptionsMapEnum(extractedMap_, default_,
                            docSelect_, docElementSelect_);
                    docElementSelect_.SetAttribute(ATTRIBUTE_NAME, name_);
                    docElementSelect_.SetAttribute(CLASS_NAME_ATTRIBUTE, ((XmlElement)_n).GetAttribute(ATTRIBUTE_CLASS_NAME));
                    _currentModifiedNode.AppendChild(_doc.ImportNode(docElementSelect_, true));
                }
            }
        }

        private static void processOptionsMapEnum(ListableKey _extractedMap,
                String _default, XmlDocument _docSelect, XmlElement _docElementSelect)
        {
            foreach (IEntry e in _extractedMap.entryListGene())
            {
                Object o_ = e.getKeyObj();
                if (o_ == null)
                {
                    continue;
                }
                XmlElement option_ = _docSelect.CreateElement(TAG_OPTION);
                if (o_ is Enum) {
                    option_.SetAttribute(ATTRIBUTE_VALUE, ((Enum) o_).name());
                    if (((Enum) o_).name().Equals(_default)) {
                        option_.SetAttribute(SELECTED, SELECTED);
                    }
                } else {
                    option_.SetAttribute(ATTRIBUTE_VALUE, o_.ToString());
                    if (o_.Equals(_default))
                    {
                        option_.SetAttribute(SELECTED, SELECTED);
                    }
                }
                option_.AppendChild(_docSelect.CreateTextNode(e.getValueObj().ToString()));
                _docElementSelect.AppendChild(option_);
            }
        }

        private static void processOptionsMapEnumName(ListableKey _extractedMap,
                XmlDocument _docSelect, XmlElement _docElementSelect, Object _returnedVarValue)
        {
            foreach (IEntry e in _extractedMap.entryListGene())
            {
                Object o_ = e.getKeyObj();
                if (o_ == null)
                {
                    continue;
                }
                XmlElement option_ = _docSelect.CreateElement(TAG_OPTION);
                if (o_ is Enum) {
                    option_.SetAttribute(ATTRIBUTE_VALUE, ((Enum) o_).name());
                    if (o_ == _returnedVarValue)
                    {
                        option_.SetAttribute(SELECTED, SELECTED);
                    }
                } else {
                    option_.SetAttribute(ATTRIBUTE_VALUE, o_.ToString());
                    if (o_.Equals(_returnedVarValue))
                    {
                        option_.SetAttribute(SELECTED, SELECTED);
                    }
                }
                option_.AppendChild(_docSelect.CreateTextNode(e.getValueObj().ToString()));
                _docElementSelect.AppendChild(option_);
            }
        }
        /**This method does not allow the list of booleans but allows the list of object with a boolean field*/
        public static void setObject(Object _container, String _command, String _varMethod, Object _attribute, String _method, String _className, MyList<long> _indexes)

        {
            String command_ = _command;
            Object obj_ = _container;
		    if (_command.Contains(DOT)) {
                command_ = _command.Substring(List.FIRST_INDEX, _command.LastIndexOf(DOT));
                obj_ = extractObject(command_, _container);
            }
            Type class_ = obj_.GetType();
            StringList traces_ = new StringList();
		    if (!_varMethod.isEmpty()) {
			    //use defined class in className attribute
			    try {
				    MethodInfo m_ = SerializeXmlObject.getDeclaredMethod(class_, _varMethod, Constants.classForName(_className));
            //m_.setAccessible(access(m_));
				    m_.Invoke(obj_, new object[] { _attribute });
				    return;
			    } catch (Exception e_) {
				    traces_.Add(getInvokeExceptionTrace(e_).join(RETURN_LINE));
			    }
		    }
		    if (_command.Contains(DOT)) {
			    try {
				    FieldInfo field_ = SerializeXmlObject.getDeclaredField(class_, _command.Substring(_command.LastIndexOf(DOT) + 1));
                    //field_.setAccessible(access(field_));
				    if (_method.isEmpty()) {
					    field_.SetValue(obj_, _attribute);
					    return;
				    }
				    ValueChangeEvent valueChangeEvent_ = new ValueChangeEvent(_indexes, field_.GetValue(obj_), _attribute);
                    field_.SetValue(obj_, _attribute);
                    MethodInfo meth_ = SerializeXmlObject.getDeclaredMethod(class_, _method, typeof(ValueChangeEvent));
                    meth_.Invoke(obj_, new object[] { valueChangeEvent_ });
				    return;
			    } catch (Exception e_) {
				    traces_.Add(getInvokeExceptionTrace(e_).join(RETURN_LINE));
			    }
		    } else {
			    try {
				    FieldInfo field_ = SerializeXmlObject.getDeclaredField(class_, _command);
                    //field_.setAccessible(access(field_));
				    if (_method.isEmpty()) {
					    field_.SetValue(obj_, _attribute);
					    return;
				    }
				    ValueChangeEvent valueChangeEvent_ = new ValueChangeEvent(_indexes, field_.GetValue(obj_), _attribute);
                    field_.SetValue(obj_, _attribute);
                    MethodInfo meth_ = SerializeXmlObject.getDeclaredMethod(class_, _method, typeof(ValueChangeEvent));
                    meth_.Invoke(obj_, new object[] { valueChangeEvent_ });
				    return;
			    } catch (Exception e_) {
				    traces_.Add(getInvokeExceptionTrace(e_).join(RETURN_LINE));
			    }
		    }

		    throw new SetterException(traces_.join(RETURN_LINE));
	    }
        public static Object invokeMethodWithNumbers(Object _container, String _command, params long[] _args)

        {
            String command_ = _command;
            Object obj_ = _container;
		    if (_command.Contains(DOT)) {
                command_ = _command.Substring(List.FIRST_INDEX, _command.LastIndexOf(DOT));
                obj_ = extractObject(command_, _container);
            }
            Type class_ = obj_.GetType();
            StringList traces_ = new StringList();
            String commandExtract_ = _command;
		    if (_command.Contains(DOT)) {
			    commandExtract_ = _command.Substring(_command.LastIndexOf(DOT)+1);
		    }
            MyList<Type> types_ = new MyList<Type>();
            int len_;
            len_ = _args.Length;
            object[] args_ = new object[len_];
            for (int i = List.FIRST_INDEX; i<len_;i++) {
			    types_.Add(typeof(long));
                args_[i] = _args[i];
            }
            MethodInfo method_;
		    try {
			    method_ = SerializeXmlObject.getDeclaredMethod(class_, commandExtract_, types_.ToArray());
		    } catch (Exception e2_) {
			    throw new InvokeException(getInvokeExceptionTrace(e2_).join(RETURN_LINE));
		    }
            Exception e_ = null;
		    try {

			    //method_.setAccessible(access(method_));
			    return method_.Invoke(obj_, args_);
		    } catch (TargetInvocationException e) {
			    e_ = e.GetBaseException();
		    } catch (Exception e) {
			    e_ = e;
		    }
		    StringList locTraces_ = getInvokeExceptionTrace(e_);
            traces_.AddRange(locTraces_);
		    throw new InvokeException(traces_.join(RETURN_LINE));
	    }
        private static StringList getInvokeExceptionTrace(Exception _exception)
        {
            StringList locTraces_ = new StringList();
            Exception tr_ = _exception;
            String trace_ = getExceptionTrace(tr_).join(EMPTY_STRING);
            locTraces_.Add(trace_);
            while (tr_.GetBaseException() != null)
            {
                trace_ = getExceptionTrace(tr_).join(EMPTY_STRING);
                locTraces_.Add(trace_);
                tr_ = tr_.GetBaseException();
            }
            return locTraces_;
        }

        public static StringList getExceptionTrace(Exception _exception)
        {
            StringList locTraces_ = new StringList();
            Exception tr_ = _exception;
            String trace_ = tr_.ToString();
            trace_ += _exception.StackTrace;
            locTraces_.Add(trace_);
            return locTraces_;
        }
        public static String processImports(String _htmlText, Configuration _conf, String _loc, Map<String, String> _files, params String[] _resourcesFolder)
        {
            String mainBeanName_ = getCurrentBean(_htmlText);
            Bean mainBean_ = _conf.getBeans().getVal(mainBeanName_);
            String htmlText_ = processHtmlJava(_htmlText, _conf, _loc, _files, _resourcesFolder);
            int i_ = List.FIRST_INDEX;
            XmlDocument docOrig_;
            MyList<XmlNode> currentNodesToBeRead_;
            MyList<XmlNode> newNodesToBeRead_;
            XmlDocument doc_;
            MyList<XmlNode> currentNodesToBeModified_;
            MyList<XmlNode> newNodesToBeModified_;
            bool modif_;
            int len_;
            while (keepLoop(htmlText_, _conf, _loc, i_, _files, _resourcesFolder)) {
			    docOrig_ = XmlParser.parseSaxHtml(htmlText_);
        
                currentNodesToBeRead_ = new MyList<XmlNode>();
                currentNodesToBeRead_.Add(docOrig_.DocumentElement);
                newNodesToBeRead_ = new MyList<XmlNode>();
                doc_ = XmlParser.parseSaxHtml(EMPTY_HTML_DOC);
                currentNodesToBeModified_ = new MyList<XmlNode>();
                currentNodesToBeModified_.Add(doc_.DocumentElement);
                newNodesToBeModified_ = new MyList<XmlNode>();
                modif_ = true;
			    while (modif_) {
				    modif_ = false;
				    newNodesToBeRead_ = new MyList<XmlNode>();
				    newNodesToBeModified_ = new MyList<XmlNode>();
				    len_ = currentNodesToBeRead_.size();
				    for (int i = List.FIRST_INDEX; i<len_; i++) {
					    XmlNode currentNode_ = currentNodesToBeRead_.get(i);
                        XmlNode currentModifiedNode_ = currentNodesToBeModified_.get(i);
					    foreach (XmlNode n in XmlParser.childrenNodes(currentNode_)) {
						    if (n is XmlElement) {
							    if (n.Name.Equals(IMPORT_BLOCK_TAG)) {
								    String pageName_ = ((XmlElement)n).GetAttribute(PAGE_ATTRIBUTE);
								    if (pageName_.isEmpty()) {
									    continue;
								    }
								    bool keepField_ = ((XmlElement)n).HasAttribute(KEEPFIELD_ATTRIBUTE);
                                    String subHtml_ = loadPage(_conf.getAssembly(),_files, pageName_, _resourcesFolder);
                                    String beanName_ = getCurrentBean(subHtml_);

                                    setBeanForms(_conf, mainBean_, n, keepField_,
                                            beanName_);

                                    setFieldsImportBean(_conf, n,
                                            beanName_);
                                    subHtml_ = processHtmlJava(subHtml_, _conf, _loc, _files, _resourcesFolder);
                                    XmlDocument subDoc_ = XmlParser.parseSaxHtml(subHtml_);
                                    XmlNodeList subList_ = subDoc_.GetElementsByTagName(TAG_BODY).Item(List.FIRST_INDEX).ChildNodes;
                                    int length_ = subList_.Count;
								    for (int k = List.FIRST_INDEX; k<length_; k++) {
									    XmlNode subNode_ = subList_.Item(k);
                                        newNodesToBeRead_.Add(subNode_);
									    if (subNode_ is XmlElement) {
										    XmlElement ne_ = doc_.CreateElement(subNode_.Name);
                                            XmlNamedNodeMap mapElt_ = subNode_.Attributes;
                                            int lentElt_ = mapElt_.Count;
										    for (int j = List.FIRST_INDEX; j< lentElt_; j++) {
											    String formatted_ = mapElt_.Item(j).Value;
                                                formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
											    formatted_ = formatted_.Replace(E_GT, GT_TAG);
                                                ne_.SetAttribute(mapElt_.Item(j).Name, formatted_);
										    }
                                            newNodesToBeModified_.Add(ne_);
										    currentModifiedNode_.AppendChild(ne_);
									    }
									    if (subNode_ is XmlText) {
										    String formatted_ = subNode_.InnerText;
                                            formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
										    formatted_ = formatted_.Replace(E_GT, GT_TAG);
										    XmlText nt_ = doc_.CreateTextNode(formatted_);
                                            newNodesToBeModified_.Add(nt_);
										    currentModifiedNode_.AppendChild(nt_);
									    }
								    }
								    continue;
							    }
							    newNodesToBeRead_.Add(n);
							    XmlElement n_ = doc_.CreateElement(n.Name);
                                XmlNamedNodeMap map_ = n.Attributes;
                                int lentgh_ = map_.Count;
							    for (int j = List.FIRST_INDEX; j<lentgh_;j++) {
								    String formatted_ = map_.Item(j).Value;
                                    formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
								    formatted_ = formatted_.Replace(E_GT, GT_TAG);
								    n_.SetAttribute(map_.Item(j).Name, formatted_);
							    }
							    newNodesToBeModified_.Add(n_);
							    currentModifiedNode_.AppendChild(n_);
							    continue;
						    }
						    if (n is XmlText) {
							    newNodesToBeRead_.Add(n);
							    String formatted_ = n.InnerText;
                                formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
							    formatted_ = formatted_.Replace(E_GT, GT_TAG);
							    XmlText n_ = doc_.CreateTextNode(formatted_);
                                newNodesToBeModified_.Add(n_);
							    currentModifiedNode_.AppendChild(n_);
						    }
					    }
				    }
				    if (!newNodesToBeRead_.isEmpty()) {
					    currentNodesToBeRead_ = new MyList<XmlNode>(newNodesToBeRead_);
					    currentNodesToBeModified_ = new MyList<XmlNode>(newNodesToBeModified_);
					    modif_ = true;
				    }
			    }
			    htmlText_ = XmlParser.toHtml(doc_);
			    i_ ++;
		    }
		    docOrig_ = XmlParser.parseSaxHtml(htmlText_);
            currentNodesToBeRead_ = new MyList<XmlNode>();
            currentNodesToBeRead_.Add(docOrig_.DocumentElement);
            newNodesToBeRead_ = new MyList<XmlNode>();
            doc_ = XmlParser.parseSaxHtml(EMPTY_HTML_DOC);
            currentNodesToBeModified_ = new MyList<XmlNode>();
            currentNodesToBeModified_.Add(doc_.DocumentElement);
            newNodesToBeModified_ = new MyList<XmlNode>();
            modif_ = true;
		    while (modif_) {
			    modif_ = false;
                newNodesToBeRead_ = new MyList<XmlNode>();
			    newNodesToBeModified_ = new MyList<XmlNode>();
			    len_ = currentNodesToBeRead_.size();
			    for (int i = List.FIRST_INDEX; i<len_; i++) {
                    XmlNode currentNode_ = currentNodesToBeRead_.get(i);
                    XmlNode currentModifiedNode_ = currentNodesToBeModified_.get(i);
				    foreach (XmlNode n in XmlParser.childrenNodes(currentNode_)) {
					    if (n is XmlElement) {
						    if (n.Name.Equals(IMPORT_BLOCK_TAG)) {
							    continue;
						    }
						    newNodesToBeRead_.Add(n);
						    XmlElement n_ = doc_.CreateElement(n.Name);
                            XmlNamedNodeMap map_ = n.Attributes;
                            int lentgh_ = map_.Count;
						    for (int j = List.FIRST_INDEX; j<lentgh_;j++) {
							    String formatted_ = map_.Item(j).Value;
                                formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
							    formatted_ = formatted_.Replace(E_GT, GT_TAG);
							    n_.SetAttribute(map_.Item(j).Name, formatted_);
						    }
						    newNodesToBeModified_.Add(n_);
						    currentModifiedNode_.AppendChild(n_);
						    continue;
					    }
					    if (n is XmlText) {
						    newNodesToBeRead_.Add(n);
						    String formatted_ = n.InnerText;
                            formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
						    formatted_ = formatted_.Replace(E_GT, GT_TAG);
						    XmlText n_ = doc_.CreateTextNode(formatted_);
                            newNodesToBeModified_.Add(n_);
						    currentModifiedNode_.AppendChild(n_);
					    }
				    }
			    }
			    if (!newNodesToBeRead_.isEmpty()) {
				    currentNodesToBeRead_ = new MyList<XmlNode>(newNodesToBeRead_);
				    currentNodesToBeModified_ = new MyList<XmlNode>(newNodesToBeModified_);
				    modif_ = true;
			    }
		    }
		    XmlNodeList anchors_ = doc_.GetElementsByTagName(TAG_A);
            len_ = anchors_.Count;
		    for (int i = List.FIRST_INDEX; i<len_; i++) {
			    XmlElement elt_ = (XmlElement)anchors_.Item(i);
			    if (elt_.HasAttribute(ATTRIBUTE_COMMAND)) {
				    elt_.SetAttribute(ATTRIBUTE_HREF, EMPTY_STRING);
			    }
		    }
		    anchors_ = doc_.GetElementsByTagName(TAG_FORM);
		    len_ = anchors_.Count;
		    for (int i = List.FIRST_INDEX; i<len_; i++) {
                XmlElement elt_ = (XmlElement)anchors_.Item(i);
			    if (elt_.HasAttribute(ATTRIBUTE_COMMAND)) {
				    elt_.SetAttribute(ATTRIBUTE_ACTION, EMPTY_STRING);
			    }
		    }
		    htmlText_ = XmlParser.toHtml(doc_);
		    return htmlText_;
	    }

	    private static bool keepLoop(String _htmlText, Configuration _conf, String _loc, int _i, Map<String, String> _files, params String[] _resourcesFolder)
        {
		    if (_files.isEmpty()) {
                XmlDocument docOrig_ = XmlParser.parseSaxHtml(_htmlText);
                XmlNodeList imports_ = docOrig_.GetElementsByTagName(IMPORT_BLOCK_TAG);
                int lenImports_ = imports_.Count;
                if (lenImports_ == 0)
                {
                    return false;
                }
                return true;
            }
		    return _i < _files.size();
        }
        private static void setBeanForms(Configuration _conf, Bean _mainBean,
            XmlNode _node, bool _keepField, String _beanName)
        {
            try
            {
                Bean bean_ = _conf.getBeans().getVal(_beanName);
                if (_keepField)
                {
                    foreach (XmlNode f_ in XmlParser.childrenNodes(_node))
                    {
                        if (!f_.Name.Equals(FORM_BLOCK_TAG))
                        {
                            continue;
                        }
                        String name_ = ((XmlElement)f_).GetAttribute(ATTRIBUTE_FORM);
                        bean_.getForms().put(name_, _mainBean.getForms().getVal(name_));
                    }
                }
                else {
                    //add option for copying forms (default copy)
                    bean_.getForms().putAllMap(_mainBean.getForms());
                }
            }
            catch (Exception)
            {
            }
        }

        private static void setFieldsImportBean(Configuration _conf, XmlNode _node,
                String _beanName)
        {
            Bean bean_ = _conf.getBeans().getVal(_beanName);
            foreach (XmlNode n in XmlParser.childrenNodes(_node))
            {
                if (!n.Name.Equals(PACKAGE_BLOCK_TAG))
                {
                    continue;
                }
                String package_ = ((XmlElement)n).GetAttribute(ATTRIBUTE_NAME);
                String assembly_ = ((XmlElement)n).GetAttribute(ATTRIBUTE_ASSEMBLY);
                if (assembly_.isEmpty())
                {
                    assembly_ = _conf.getAssembly();
                }
                foreach (XmlNode nTwo_ in XmlParser.childrenNodes(n))
                {
                    if (!nTwo_.Name.Equals(CLASS_BLOCK_TAG))
                    {
                        continue;
                    }
                    String className_ = ((XmlElement)nTwo_).GetAttribute(ATTRIBUTE_NAME);
                    className_ = className_.Replace(".]", _conf.getAssembly()+"]");
                    String fullName_ = assembly_ + DOT + package_ + DOT + className_;
                    fullName_ = fullName_.ToLower();
                    Type class_ = bean_.GetType();
                    while (true)
                    {
                        if (class_ == typeof(Object)) {
						    break;
					    }
                        //string currentFullName_ = Constants.getTypeFullString(class_);
                        string currentFullName_ = class_.Assembly.GetName().Name+"."+class_.FullName;
                        if (currentFullName_.Contains("["))
                        {
                            currentFullName_ = currentFullName_.Split('[').ElementAt(0);
                        }
                        if (currentFullName_.ToLower().Equals(fullName_)) {
						    break;
					    }
					    class_ = class_.BaseType;
				    }
				    foreach (XmlNode nThree_ in XmlParser.childrenNodes(nTwo_)) {
					    if (!nThree_.Name.Equals(FIELD_BLOCK_TAG)) {
						    continue;
					    }
					    try {
                            String beanNameFromValue_;
                            Bean beanFromValue_;
                            String fieldValue_;
                            String command_;
                            if (((XmlElement)nThree_).HasAttribute(ATTRIBUTE_METHOD)) {
							    String methodName_ = ((XmlElement)nThree_).GetAttribute(ATTRIBUTE_METHOD);
                                fieldValue_ = ((XmlElement)nThree_).GetAttribute(ATTRIBUTE_VALUE);
                                String classNameParam_ = ((XmlElement)nThree_).GetAttribute(ATTRIBUTE_CLASS_NAME);
								if (classNameParam_.StartsWith(".")) {
									classNameParam_ = _conf.getAssembly()+classNameParam_;
								}
                                classNameParam_ = classNameParam_.Replace(".]", _conf.getAssembly() + "]");
                                Type classParam_ = Constants.classForName(classNameParam_);
                                MethodInfo m_ = SerializeXmlObject.getDirectDeclaredMethod(class_, methodName_, classParam_);
                            //m_.setAccessible(access(m_));
							    try {
								    int intValue_ = int.Parse(fieldValue_);
                                    m_.Invoke(bean_, new object[] { intValue_ });
								    continue;
							    } catch (Exception) {
							    }
							    beanNameFromValue_ = fieldValue_.Substring(List.FIRST_INDEX, fieldValue_.IndexOf(DOT));
                                command_ = fieldValue_.Substring(fieldValue_.IndexOf(DOT) + 1);
                                beanFromValue_ = _conf.getBeans().getVal(beanNameFromValue_);
                                m_.Invoke(bean_, new object[] { extractObject(command_, beanFromValue_) });
							    continue;
						    }
						    String fieldName_ = ((XmlElement)nThree_).GetAttribute(ATTRIBUTE_NAME);
                            fieldValue_ = ((XmlElement)nThree_).GetAttribute(ATTRIBUTE_VALUE);
                            FieldInfo f_ = SerializeXmlObject.getDirectDeclaredField(class_, fieldName_);
                            //f_.setAccessible(access(f_));
						    try {
							    int intValue_ = int.Parse(fieldValue_);
                                f_.SetValue(bean_, intValue_);
							    continue;
						    } catch (Exception) {
						    }
						    beanNameFromValue_ = fieldValue_.Substring(0, fieldValue_.IndexOf(DOT));
                            command_ = fieldValue_.Substring(fieldValue_.IndexOf(DOT) + 1);
                            beanFromValue_ = _conf.getBeans().getVal(beanNameFromValue_);
                            f_.SetValue(bean_, extractObject(command_, beanFromValue_));
					    } catch (Exception) {
						    //e.printStackTrace();
					    }
				    }
			    }
		    }
	    }
        public static String processHtmlJava(String _htmlText, Configuration _conf, String _loc, Map<String, String> _files, params String[] _resourcesFolder)
        {
            String htmlText_ = _htmlText;
            String beanName_ = null;
            Bean bean_ = null;
            XmlDocument doc_ = XmlParser.parseSaxHtml(htmlText_);
            beanName_ = getCurrentBean(_htmlText);
            bean_ = _conf.getBeans().getVal(beanName_);
            htmlText_ = XmlParser.toHtml(doc_);
		    if (bean_ != null) {
                bean_.beforeDisplaying();
            }
            htmlText_ = FormatHtml.processHtml(XmlParser.parseSaxHtml(htmlText_).DocumentElement, _conf, _files, bean_);
            htmlText_ = htmlText_.Replace(LT_BEGIN_TAG+TMP_BLOCK_TAG+GT_TAG, EMPTY_STRING);
            htmlText_ = htmlText_.Replace(LT_BEGIN_TAG+TMP_BLOCK_TAG+RIGHT_END_TAG, EMPTY_STRING);
            htmlText_ = htmlText_.Replace(LT_END_TAG+TMP_BLOCK_TAG+GT_TAG, EMPTY_STRING);
            htmlText_ = htmlText_.Replace(LT_BEGIN_TAG+TR_BEGIN_BLOCK_TAG+RIGHT_END_TAG, TR_BEGIN);
            htmlText_ = htmlText_.Replace(LT_BEGIN_TAG+TR_END_BLOCK_TAG+RIGHT_END_TAG, TR_END);
            htmlText_ = FormatHtml.processVarInputValue(htmlText_, bean_);
            htmlText_ = formatClassAndMessage(htmlText_, bean_);
            htmlText_ = FormatHtml.formatNamedVariables(htmlText_, _conf, _files, bean_);
            htmlText_ = processMessages(_conf, htmlText_, bean_, _loc, _files, _resourcesFolder);
            htmlText_ = processSubmitTags(_conf, htmlText_, bean_, _loc, _files, _resourcesFolder);
            htmlText_ = processTitles(_conf, htmlText_, bean_, _loc, _files, _resourcesFolder);
            htmlText_ = FormatHtml.processRadio(htmlText_, bean_);
            htmlText_ = FormatHtml.processVarInputName(htmlText_, beanName_);
            htmlText_ = processImages(_conf.getAssembly(), htmlText_, _files, _resourcesFolder);
            htmlText_ = processImagesTags(htmlText_);
            htmlText_ = processCss(_conf.getAssembly(), htmlText_, _files, _resourcesFolder);
            htmlText_ = processScript(_conf.getAssembly(), htmlText_, _files, _resourcesFolder);
            htmlText_ = processSpansErrors(htmlText_);
		    return htmlText_;
        }

        public static String formatClassAndMessage(String _htmlText, Bean _bean)

        {
            XmlDocument doc_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList nodes_ = doc_.GetElementsByTagName(ALL_TAGS);

            int length_ = nodes_.Count;
		    for (int j = List.FIRST_INDEX; j<length_;j++) {
			    XmlNode node_ = nodes_.Item(j);
                XmlElement element_ = (XmlElement)node_;
                String class_ = element_.GetAttribute(ATTRIBUTE_CLASS);
			    if (!class_.Contains(CALL_METHOD)) {
				    continue;
			    }
			    String command_ = class_.Substring(class_.IndexOf(CALL_METHOD) + 1);
                Object returnedObject_ = extractObject(command_, _bean);
			    if (returnedObject_ == null) {
				    element_.RemoveAttribute(ATTRIBUTE_CLASS);
				    continue;
			    }
                element_.SetAttribute(ATTRIBUTE_CLASS, returnedObject_.ToString());
		    }
            nodes_ = doc_.GetElementsByTagName(MESSAGE_BLOCK_TAG);
		    length_ = nodes_.Count;
		    for (int j = List.FIRST_INDEX; j<length_;j++) {
			    XmlNode node_ = nodes_.Item(j);
                XmlElement element_ = (XmlElement)node_;
			    if (!element_.HasAttribute(ATTRIBUTE_QUOTED)) {
				    continue;
			    }
			    XmlNodeList listParam_ = element_.GetElementsByTagName(TAG_PARAM);
                int len_ = listParam_.Count;
			    for (int i = List.FIRST_INDEX; i<len_; i++) {
				    XmlElement param_ = (XmlElement)listParam_.Item(i);
                    param_.SetAttribute(ATTRIBUTE_VALUE, param_.GetAttribute(ATTRIBUTE_VALUE).Replace(FORMAT_QUOTE, ESCAPED_FORMAT_QUOTE));
			    }
		    }
		    return XmlParser.toHtml(doc_);
	    }
        public static String processVarInputValue(String _htmlText, Object _o)
        {
            XmlDocument doc_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList inputs_ = doc_.GetElementsByTagName(INPUT_TAG);
		    int length_ = inputs_.Count;
		    for (int i = List.FIRST_INDEX; i<length_; i++) {
                XmlElement elt_ = (XmlElement)inputs_.Item(i);
                if (!elt_.HasAttribute(ATTRIBUTE_VAR_VALUE))
                {
                    continue;
                }
                String attribute_ = elt_.GetAttribute(ATTRIBUTE_VAR_VALUE);
                try
                {
                    elt_.SetAttribute(ATTRIBUTE_VALUE, long.Parse(attribute_).ToString());
                }
                catch (FormatException)
                {
                    Object o_ = extractObject(attribute_, _o);
                    if (o_ == null)
                    {
                        elt_.SetAttribute(ATTRIBUTE_VALUE, (String)o_);
                    }
                    else if (o_ is Boolean) {
                        if ((Boolean)o_)
                        {
                            elt_.SetAttribute(CHECKED, CHECKED);
                        }
                    } else {
                        elt_.SetAttribute(ATTRIBUTE_VALUE, o_.ToString());
                    }
                }
            }
		    return XmlParser.toHtml(doc_);
        }
        public static String processVarInputName(String _htmlText, String _beanName)
        {
            XmlDocument doc_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList inputs_ = doc_.GetElementsByTagName(INPUT_TAG);
		    int length_ = inputs_.Count;
		    for (int i = List.FIRST_INDEX; i<length_; i++) {
                XmlElement elt_ = (XmlElement)inputs_.Item(i);
                if (!elt_.HasAttribute(ATTRIBUTE_NAME))
                {
                    continue;
                }
                elt_.SetAttribute(ATTRIBUTE_NAME, _beanName + DOT + elt_.GetAttribute(ATTRIBUTE_NAME));
            }
            inputs_ = doc_.GetElementsByTagName(SELECT_TAG);
            length_ = inputs_.Count;
		    for (int i = List.FIRST_INDEX; i<length_; i++) {
                XmlElement elt_ = (XmlElement)inputs_.Item(i);
                if (elt_.GetAttribute(ATTRIBUTE_NAME).isEmpty())
                {
                    continue;
                }
                elt_.SetAttribute(ATTRIBUTE_NAME, _beanName + DOT + elt_.GetAttribute(ATTRIBUTE_NAME));
            }
            inputs_ = doc_.GetElementsByTagName(FIELD_BLOCK_TAG);
            length_ = inputs_.Count;
		    for (int i = List.FIRST_INDEX; i<length_; i++) {
                XmlElement elt_ = (XmlElement)inputs_.Item(i);
                if (!elt_.HasAttribute(ATTRIBUTE_VALUE))
                {
                    continue;
                }
                try
                {
                    int.Parse(elt_.GetAttribute(ATTRIBUTE_VALUE));
                }
                catch (Exception)
                {
                    elt_.SetAttribute(ATTRIBUTE_VALUE, _beanName + DOT + elt_.GetAttribute(ATTRIBUTE_VALUE));
                }
            }
            inputs_ = doc_.GetElementsByTagName(TAG_A);
            length_ = inputs_.Count;
		    for (int i = List.FIRST_INDEX; i<length_; i++) {
                XmlElement elt_ = (XmlElement)inputs_.Item(i);
                if (!elt_.GetAttribute(ATTRIBUTE_HREF).StartsWith(CALL_METHOD))
                {
                    if (!elt_.GetAttribute(ATTRIBUTE_COMMAND).StartsWith(CALL_METHOD))
                    {
                        continue;
                    }
                }
                String href_ = elt_.GetAttribute(ATTRIBUTE_HREF);
                if (href_.StartsWith(CALL_METHOD))
                {
                    elt_.SetAttribute(ATTRIBUTE_HREF, CALL_METHOD + _beanName + DOT + href_.Substring(1));
                    continue;
                }
                href_ = elt_.GetAttribute(ATTRIBUTE_COMMAND);
                elt_.SetAttribute(ATTRIBUTE_COMMAND, CALL_METHOD + _beanName + DOT + href_.Substring(1));
            }
            inputs_ = doc_.GetElementsByTagName(TAG_FORM);
            length_ = inputs_.Count;
		    for (int i = List.FIRST_INDEX; i<length_; i++) {
                XmlElement elt_ = (XmlElement)inputs_.Item(i);
                if (!elt_.GetAttribute(ATTRIBUTE_ACTION).StartsWith(CALL_METHOD))
                {
                    if (!elt_.GetAttribute(ATTRIBUTE_COMMAND).StartsWith(CALL_METHOD))
                    {
                        continue;
                    }
                }
                String href_ = elt_.GetAttribute(ATTRIBUTE_ACTION);
                if (href_.StartsWith(CALL_METHOD))
                {
                    elt_.SetAttribute(ATTRIBUTE_ACTION, CALL_METHOD + _beanName + DOT + href_.Substring(1));
                    continue;
                }
                href_ = elt_.GetAttribute(ATTRIBUTE_COMMAND);
                elt_.SetAttribute(ATTRIBUTE_COMMAND, CALL_METHOD + _beanName + DOT + href_.Substring(1));
            }
		    return XmlParser.toHtml(doc_);
        }

        public static String processRadio(String _htmlText, Bean _bean)
        {
            XmlDocument doc_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList inputs_ = doc_.GetElementsByTagName(INPUT_TAG);
		    int length_ = inputs_.Count;
            StringList names_ = new StringList();
		    for (int i = List.FIRST_INDEX; i<length_;i++) {
			    XmlElement elt_ = (XmlElement)inputs_.Item(i);
			    if (!elt_.GetAttribute(ATTRIBUTE_TYPE).Equals(RADIO)) {
				    continue;
			    }
			    names_.Add(elt_.GetAttribute(ATTRIBUTE_NAME));
		    }
		    names_.removeDuplicates();
		    Map<String, Object> objects_ = new Map<String, Object>();
		    foreach (String n in names_) {
			    objects_.put(n, extractObject(n, _bean));
		    }
            foreach (String n in names_) {
			    for (int i = List.FIRST_INDEX; i<length_;i++) {
				    XmlElement elt_ = (XmlElement)inputs_.Item(i);
				    if (!elt_.GetAttribute(ATTRIBUTE_TYPE).Equals(RADIO)) {
					    continue;
				    }
				    if (elt_.GetAttribute(ATTRIBUTE_NAME).Equals(n)) {
					    if (elt_.GetAttribute(ATTRIBUTE_VALUE).Equals(objects_.getVal(n).ToString())) {
						    elt_.SetAttribute(CHECKED, CHECKED);
					    } else {
						    elt_.RemoveAttribute(CHECKED);
					    }
				    }
			    }
		    }
		    return XmlParser.toHtml(doc_);
	    }
        public static String processHtml(XmlNode _root, Configuration _conf, Map<String, String> _files, Bean _o)
        {
            MyList<XmlNode> currentNodesToBeRead_ = new MyList<XmlNode>();
		    currentNodesToBeRead_.Add(_root);
            MyList<XmlNode> newNodesToBeRead_ = new MyList<XmlNode>();
            XmlDocument doc_ = XmlParser.parseSaxHtml(EMPTY_HTML_DOC);
            MyList<XmlNode> currentNodesToBeModified_ = new MyList<XmlNode>();
            currentNodesToBeModified_.Add(doc_.DocumentElement);
            MyList<XmlNode> newNodesToBeModified_ = new MyList<XmlNode>();
            bool modif_ = true;
		    while (modif_) {
			    modif_ = false;
			    newNodesToBeRead_ = new MyList<XmlNode>();
			    newNodesToBeModified_ = new MyList<XmlNode>();
			    int len_;
                len_ = currentNodesToBeRead_.size();
			    for (int i = List.FIRST_INDEX; i<len_; i++) {
                    XmlNode currentNode_ = currentNodesToBeRead_.get(i);
                    XmlNode currentModifiedNode_ = currentNodesToBeModified_.get(i);
				    foreach (XmlNode n in XmlParser.childrenNodes(currentNode_)) {
					    if (n is XmlElement) {
						    if (n.Name.Equals(SELECT_BLOCK_TAG)) {
							    String mapColl_ = ((XmlElement)n).GetAttribute(ATTRIBUTE_MAP);
                                String id_ = ((XmlElement)n).GetAttribute(ATTRIBUTE_ID);
							    if (!mapColl_.isEmpty()) {

                                    processOptionsMap(_o, doc_,
                                            currentModifiedNode_, n, mapColl_, id_);
								    continue;
							    }

                                processOptionsList(_o,
                                        doc_, currentModifiedNode_, n, id_);
							    continue;
						    }
						    if (n.Name.Equals(FOR_BLOCK_TAG)) {
							    String contents_ = toHtmlString(n);
                                XmlNodeList forElements_ = ((XmlElement)n).GetElementsByTagName(FOR_BLOCK_TAG);
                                int forNbs_ = forElements_.Count;
                                StringList vars_ = new StringList();
							    for (int j = List.FIRST_INDEX; j<forNbs_; j++) {
                                    XmlElement elt_ = (XmlElement)forElements_.Item(j);
                                    vars_.Add(elt_.GetAttribute(ATTRIBUTE_VAR));
								    vars_.Add(elt_.GetAttribute(ATTRIBUTE_KEY));
								    vars_.Add(elt_.GetAttribute(ATTRIBUTE_VALUE));
							    }
							    vars_.removeDuplicates();
							    vars_.removeObj(EMPTY_STRING);
							    int nbVars_ = vars_.size();
                                vars_.removedObj(((XmlElement) n).GetAttribute(ATTRIBUTE_VAR));
							    vars_.removedObj(((XmlElement) n).GetAttribute(ATTRIBUTE_KEY));
							    vars_.removedObj(((XmlElement) n).GetAttribute(ATTRIBUTE_VALUE));
							    if (nbVars_ != vars_.size()) {
								    String message_ = ((XmlElement)n).GetAttribute(ATTRIBUTE_VAR);
                                    message_ += SPACE_MESSAGE;
								    message_ += ((XmlElement) n).GetAttribute(ATTRIBUTE_KEY);
                                    message_ += SPACE_MESSAGE;
								    message_ += ((XmlElement) n).GetAttribute(ATTRIBUTE_VALUE);
								    throw new AlreadyDefinedVarException(message_);
							    }
							    if (n.Attributes.GetNamedItem(ATTRIBUTE_LIST) == null) {
                                    processLoopMap(_conf, _files, _o,
                                        newNodesToBeRead_, doc_,
                                        newNodesToBeModified_,
                                        currentModifiedNode_, n, contents_);
								    continue;
							    }

                                processLoopList(_conf, _files, _o, newNodesToBeRead_, doc_, newNodesToBeModified_, currentModifiedNode_, n, contents_);
							    continue;
						    }
						    if (n.Name.Equals(IF_BLOCK_TAG)) {
							    String condition_ = n.Attributes.GetNamedItem(ATTRIBUTE_CONDITION).Value;
                                String conditionWithoutNeg_ = condition_.replaceAll(NEG_REG_EXP, EMPTY_STRING);
                                int nbNeg_ = condition_.Length - conditionWithoutNeg_.Length;
                                conditionWithoutNeg_ = formatNamedVariables(conditionWithoutNeg_, _conf, _files, _o);
                                Boolean b_ = (Boolean)extractObject(conditionWithoutNeg_, _o);
							    if (nbNeg_%2 == 1) {
								    b_ = !b_;
							    }
							    if (!b_) {
								    continue;
							    }
							    String contents_ = toHtmlString(n);
                                XmlDocument docLoc_ = XmlParser.parseSaxHtml(addToRoot(contents_));
                                newNodesToBeRead_.Add(docLoc_.DocumentElement);
							    XmlElement ne_ = doc_.CreateElement(docLoc_.DocumentElement.Name);
                                XmlNamedNodeMap mapAttr_ = docLoc_.DocumentElement.Attributes;

                                setAttributes(ne_, mapAttr_);
                                newNodesToBeModified_.Add(ne_);
							    currentModifiedNode_.AppendChild(ne_);
							    continue;
						    }
						    newNodesToBeRead_.Add(n);
						    XmlElement n_ = doc_.CreateElement(n.Name);
                            XmlNamedNodeMap map_ = n.Attributes;

                            setAttributes(n_, map_);
                            newNodesToBeModified_.Add(n_);
						    currentModifiedNode_.AppendChild(n_);
						    continue;
					    }
					    if (n is XmlText) {
						    newNodesToBeRead_.Add(n);
                            XmlText n_ = doc_.CreateTextNode(n.InnerText);
                            newNodesToBeModified_.Add(n_);
						    currentModifiedNode_.AppendChild(n_);
					    }
				    }
			    }
			    if (!newNodesToBeRead_.isEmpty()) {
				    currentNodesToBeRead_ = new MyList<XmlNode>(newNodesToBeRead_);
				    currentNodesToBeModified_ = new MyList<XmlNode>(newNodesToBeModified_);
				    modif_ = true;
			    }
		    }
		    return XmlParser.toHtml(doc_);
	    }
        private static String toHtmlString(XmlNode _node)
        {
            String contents_ = EMPTY_STRING;
            foreach (XmlNode nTwo_ in XmlParser.childrenNodes(_node))
            {
                contents_ += XmlParser.toXml(nTwo_);
            }
            return contents_;
        }
        private static void processLoopList(Configuration _conf,
            Map<String, String> _files, Bean _o, MyList<XmlNode> _newNodesToBeRead,
            XmlDocument _doc, MyList<XmlNode> _newNodesToBeModified,
            XmlNode _currentModifiedNode, XmlNode _n, String _contents)

        {
            String container_ = _n.Attributes.GetNamedItem(ATTRIBUTE_LIST).Value;
            container_ = formatNamedVariables(container_, _conf, _files, _o);
            Object o_ = extractObject(container_, _o);
            String var_ = _n.Attributes.GetNamedItem(ATTRIBUTE_VAR).Value;
            IEnumerable listCast_ = (IEnumerable) o_;

            int i_ = 0;
		    foreach (Object o in listCast_) {
			    String copyContents_ = _contents;
                copyContents_ = copyContents_.Replace(LEFT_EL+var_+GET_INDEX+RIGHT_EL, i_.ToString());
			    copyContents_ = copyContents_.replaceAll(ESCAPED_LEFT_EL+var_+GET_ATTRIBUTE+NEXT_FIELDS+ESCAPED_RIGHT_EL, LEFT_EL+container_+LEFT_GET_ARR+i_+RIGHT_GET_ARR+GET_FORMAT_VAR+RIGHT_EL);
			    copyContents_ = addToRoot(copyContents_.Replace(LEFT_EL+var_+GET_ATTRIBUTE+RIGHT_EL, o.ToString()));
			    XmlDocument docLoc_ = XmlParser.parseSaxHtml(copyContents_);

                updateNotEmptyAttributesMap(docLoc_, i_, FOR_BLOCK_TAG, ATTRIBUTE_LIST, var_, var_, container_, EMPTY_STRING);

                updateNotEmptyAttributesMap(docLoc_, i_, FOR_BLOCK_TAG, ATTRIBUTE_MAP, var_, var_, container_, EMPTY_STRING);

                updateNotEmptyAttributesMap(docLoc_, i_, FOR_BLOCK_TAG, ATTRIBUTE_ORDERED_KEYS, var_, var_, container_, EMPTY_STRING);

                updateNotEmptyAttributesMap(docLoc_, i_, FIELD_BLOCK_TAG, ATTRIBUTE_METHOD, var_, var_, container_, EMPTY_STRING);

                updateNotEmptyAttributesMap(docLoc_, i_, INPUT_TAG, VAR_METHOD, var_, var_, container_, EMPTY_STRING);

                updateNotEmptyAttributesMap(docLoc_, i_, SELECT_BLOCK_TAG, VAR_METHOD, var_, var_, container_, EMPTY_STRING);

                updateAllAttributesMap(docLoc_, i_, IF_BLOCK_TAG, ATTRIBUTE_CONDITION, var_, var_, container_, EMPTY_STRING);

                updateAllAttributesMap(docLoc_, i_, INPUT_TAG, ATTRIBUTE_NAME, var_, var_, container_, EMPTY_STRING);

                updateAllAttributesMap(docLoc_, i_, INPUT_TAG, ATTRIBUTE_VAR_VALUE, var_, var_, container_, EMPTY_STRING);//ADDED

                updateAllAttributesMap(docLoc_, i_, SELECT_BLOCK_TAG, ATTRIBUTE_LIST, var_, var_, container_, EMPTY_STRING);

                updateAllAttributesMap(docLoc_, i_, SELECT_BLOCK_TAG, ATTRIBUTE_NAME, var_, var_, container_, EMPTY_STRING);

                updateAllAttributesMap(docLoc_, i_, SELECT_BLOCK_TAG, ATTRIBUTE_VAR_VALUE, var_, var_, container_, EMPTY_STRING);

                updateAllAttributesMap(docLoc_, i_, FIELD_BLOCK_TAG, ATTRIBUTE_VALUE, var_, var_, container_, EMPTY_STRING);

                updateNotEmptyAttributesMap(docLoc_, i_, ALL_TAGS, ATTRIBUTE_ID, var_, var_, container_, EMPTY_STRING);

                updateNotEmptyAttributesMap(docLoc_, i_, SPAN_TAG, ATTRIBUTE_FOR, var_, var_, container_, EMPTY_STRING);

                updateSelectTags(container_, var_, var_, EMPTY_STRING, i_, docLoc_);

                updateAttributesWithPrefix(docLoc_, i_, TAG_A, ATTRIBUTE_HREF);

                updateAttributesWithPrefix(docLoc_, i_, TAG_FORM, ATTRIBUTE_ACTION);

                updateAttributesWithPrefix(docLoc_, i_, TAG_A, ATTRIBUTE_COMMAND);

                updateAttributesWithPrefix(docLoc_, i_, TAG_FORM, ATTRIBUTE_COMMAND);

                updateAttributesWithPrefix(docLoc_, i_, ALL_TAGS, ATTRIBUTE_CLASS);

                updateFormTags(i_, docLoc_);

                _newNodesToBeRead.Add(docLoc_.DocumentElement);
			    XmlElement n_ = _doc.CreateElement(docLoc_.DocumentElement.Name);
                XmlNamedNodeMap map_ = docLoc_.DocumentElement.Attributes;

                setAttributes(n_, map_);
                _newNodesToBeModified.Add(n_);
			    _currentModifiedNode.AppendChild(n_);
			    i_++;
		    }
        }

        private static void processLoopMap(Configuration _conf,
                Map<String, String> _files, Bean _o, MyList<XmlNode> _newNodesToBeRead,
                XmlDocument _doc, MyList<XmlNode> _newNodesToBeModified,
                XmlNode _currentModifiedNode, XmlNode _n, String _contents)

        {
            String container_ = _n.Attributes.GetNamedItem(ATTRIBUTE_MAP).Value;
            container_ = formatNamedVariables(container_, _conf, _files, _o);
            String key_ = _n.Attributes.GetNamedItem(ATTRIBUTE_KEY).Value;
            String value_ = _n.Attributes.GetNamedItem(ATTRIBUTE_VALUE).Value;
		    if (key_.Equals(value_)) {
                throw new KeyValueException(key_);
            }
            Object o_ = extractObject(container_, _o);
            String listMethod_ = null;
		    if (_n.Attributes.GetNamedItem(ATTRIBUTE_ORDERED_KEYS) != null) {
                listMethod_ = _n.Attributes.GetNamedItem(ATTRIBUTE_ORDERED_KEYS).Value;
            }
            IEnumerable iterable_;
            ListableKey mapCast_ = (ListableKey) o_;
		    if (o_ is IComparableKeys) {
                iterable_ = mapCast_.getKeysGene();
            } else {
                IEnumerable keys_ = mapCast_.getKeysGene();
                if (listMethod_ == null)
                {
                    iterable_ = orderedList(keys_);
                }
                else {
                    iterable_ = (IEnumerable) extractObject(listMethod_ + NO_PARAM_METHOD, _o);
                }
            }
		    int i_ = 0;
		    foreach (Object o in iterable_) {
                String copyContents_ = _contents;
                copyContents_ = copyContents_.Replace(LEFT_EL + key_ + GET_INDEX + RIGHT_EL, i_.ToString());
                copyContents_ = copyContents_.replaceAll(ESCAPED_LEFT_EL + key_ + GET_ATTRIBUTE + NEXT_FIELDS + ESCAPED_RIGHT_EL, LEFT_EL + container_ + LEFT_GET_ARR + i_ + RIGHT_GET_ARR + listMethod_ + GET_KEY + GET_FORMAT_VAR + RIGHT_EL);
                copyContents_ = copyContents_.replaceAll(ESCAPED_LEFT_EL + value_ + GET_ATTRIBUTE + NEXT_FIELDS + ESCAPED_RIGHT_EL, LEFT_EL + container_ + LEFT_GET_ARR + i_ + RIGHT_GET_ARR + listMethod_ + GET_VALUE + GET_FORMAT_VAR + RIGHT_EL);
                copyContents_ = copyContents_.Replace(LEFT_EL + key_ + GET_ATTRIBUTE + RIGHT_EL, o.ToString());
                copyContents_ = addToRoot(copyContents_.Replace(LEFT_EL + value_ + GET_ATTRIBUTE + RIGHT_EL, mapCast_.getGene(o).ToString()));
                XmlDocument docLoc_ = XmlParser.parseSaxHtml(copyContents_);
                updateNotEmptyAttributesMap(docLoc_, i_, FOR_BLOCK_TAG, ATTRIBUTE_LIST, key_, value_, container_, listMethod_);
                updateNotEmptyAttributesMap(docLoc_, i_, FOR_BLOCK_TAG, ATTRIBUTE_MAP, key_, value_, container_, listMethod_);
                updateNotEmptyAttributesMap(docLoc_, i_, FOR_BLOCK_TAG, ATTRIBUTE_ORDERED_KEYS, key_, value_, container_, listMethod_);
                updateNotEmptyAttributesMap(docLoc_, i_, FIELD_BLOCK_TAG, ATTRIBUTE_METHOD, key_, value_, container_, listMethod_);
                updateNotEmptyAttributesMap(docLoc_, i_, INPUT_TAG, VAR_METHOD, key_, value_, container_, listMethod_);
                updateNotEmptyAttributesMap(docLoc_, i_, SELECT_BLOCK_TAG, VAR_METHOD, key_, value_, container_, listMethod_);
                updateAllAttributesMap(docLoc_, i_, IF_BLOCK_TAG, ATTRIBUTE_CONDITION, key_, value_, container_, listMethod_);
                updateAllAttributesMap(docLoc_, i_, INPUT_TAG, ATTRIBUTE_NAME, key_, value_, container_, listMethod_);
                updateAllAttributesMap(docLoc_, i_, INPUT_TAG, ATTRIBUTE_VAR_VALUE, key_, value_, container_, listMethod_);//ADDED
                updateAllAttributesMap(docLoc_, i_, SELECT_BLOCK_TAG, ATTRIBUTE_LIST, key_, value_, container_, listMethod_);
                updateAllAttributesMap(docLoc_, i_, SELECT_BLOCK_TAG, ATTRIBUTE_NAME, key_, value_, container_, listMethod_);
                updateAllAttributesMap(docLoc_, i_, SELECT_BLOCK_TAG, ATTRIBUTE_VAR_VALUE, key_, value_, container_, listMethod_);
                updateAllAttributesMap(docLoc_, i_, FIELD_BLOCK_TAG, ATTRIBUTE_VALUE, key_, value_, container_, listMethod_);
                updateNotEmptyAttributesMap(docLoc_, i_, ALL_TAGS, ATTRIBUTE_ID, key_, value_, container_, listMethod_);
                updateNotEmptyAttributesMap(docLoc_, i_, SPAN_TAG, ATTRIBUTE_FOR, key_, value_, container_, listMethod_);
                updateSelectTags(container_, key_, value_,
                        listMethod_, i_, docLoc_);
                updateAttributesWithPrefix(docLoc_, i_, TAG_A, ATTRIBUTE_HREF);
                updateAttributesWithPrefix(docLoc_, i_, TAG_FORM, ATTRIBUTE_ACTION);
                updateAttributesWithPrefix(docLoc_, i_, TAG_A, ATTRIBUTE_COMMAND);
                updateAttributesWithPrefix(docLoc_, i_, TAG_FORM, ATTRIBUTE_COMMAND);
                updateAttributesWithPrefix(docLoc_, i_, ALL_TAGS, ATTRIBUTE_CLASS);
                updateFormTags(i_, docLoc_);

                _newNodesToBeRead.Add(docLoc_.DocumentElement);
                XmlElement n_ = _doc.CreateElement(docLoc_.DocumentElement.Name);
                XmlNamedNodeMap map_ = docLoc_.DocumentElement.Attributes;
                setAttributes(n_, map_);
                _newNodesToBeModified.Add(n_);
                _currentModifiedNode.AppendChild(n_);
                i_++;
            }
        }

        public static void updateFormTags(int _index, XmlDocument _docLoc)
        {
            XmlNodeList nodes_;
            int length_;
            nodes_ = _docLoc.GetElementsByTagName(TAG_FORM);
            length_ = nodes_.Count;
            for (int j = List.FIRST_INDEX; j < length_; j++)
            {
                XmlNode node_ = nodes_.Item(j);
                XmlElement elt_ = (XmlElement)node_;
                String name_ = elt_.GetAttribute(ATTRIBUTE_NAME);
                if (name_.isEmpty())
                {
                    continue;
                }
                if (name_.Contains(LEFT_PAR_COMMA))
                {
                    name_ = name_.Replace(LEFT_PAR_COMMA, LEFT_PAR + _index + COMMA);
                }
                else if (name_.Contains(DOUBLE_COMMA))
                {
                    name_ = name_.replaceAll(NEXT_ARG, FORMAT_VAR + COMMA + _index + COMMA);
                }
                else if (name_.Contains(COMMA_RIGHT_PAR))
                {
                    name_ = name_.Replace(COMMA_RIGHT_PAR, COMMA + _index + RIGHT_PAR);
                }
                else if (name_.Contains(NO_PARAM_METHOD))
                {
                    name_ = name_.Replace(NO_PARAM_METHOD, LEFT_PAR + _index + RIGHT_PAR);
                }
                elt_.SetAttribute(ATTRIBUTE_NAME, name_);
            }
        }

        public static void updateSelectTags(String _container, String _key,
                String _value, String _listMethod, int _index, XmlDocument _docLoc)
        {
            XmlNodeList nodes_;
            int length_;
            nodes_ = _docLoc.GetElementsByTagName(SELECT_BLOCK_TAG);
            length_ = nodes_.Count;
            if (_key.Equals(_value))
            {
                for (int j = List.FIRST_INDEX; j < length_; j++)
                {
                    XmlNode node_ = nodes_.Item(j);
                    XmlElement elt_ = (XmlElement)node_;
                    String varLoc_ = elt_.GetAttribute(DEFAULT_ATTRIBUTE);
                    if (varLoc_.StartsWith(CALL_METHOD))
                    {
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + CALL_AFTER, _container + LEFT_GET_ARR + _index + RIGHT_GET_ARR + GET_FORMAT_VAR);
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + GET_ATTRIBUTE, _container + LEFT_GET_ARR + _index + RIGHT_GET_ARR);
                        elt_.SetAttribute(DEFAULT_ATTRIBUTE, varLoc_);
                    }
                }
            }
            else {
                for (int j = List.FIRST_INDEX; j < length_; j++)
                {
                    XmlNode node_ = nodes_.Item(j);
                    XmlElement elt_ = (XmlElement)node_;
                    String varLoc_ = elt_.GetAttribute(DEFAULT_ATTRIBUTE);
                    if (varLoc_.StartsWith(CALL_METHOD))
                    {
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + CALL_AFTER, _container + LEFT_GET_ARR + _index + RIGHT_GET_ARR + _listMethod + GET_KEY + GET_FORMAT_VAR);
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + GET_ATTRIBUTE, _container + LEFT_GET_ARR + _index + RIGHT_GET_ARR + _listMethod + GET_KEY);
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _value + CALL_AFTER, _container + LEFT_GET_ARR + _index + RIGHT_GET_ARR + _listMethod + GET_VALUE + GET_FORMAT_VAR);
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _value + GET_ATTRIBUTE, _container + LEFT_GET_ARR + _index + RIGHT_GET_ARR + _listMethod + GET_VALUE);
                        elt_.SetAttribute(DEFAULT_ATTRIBUTE, varLoc_);
                    }
                }
            }
        }

        public static void setAttributes(XmlElement _n, XmlNamedNodeMap _map)
        {
            int length_ = _map.Count;
            for (int j = List.FIRST_INDEX; j < length_; j++)
            {
                _n.SetAttribute(_map.Item(j).Name, _map.Item(j).Value);
            }
        }

        public static void updateNotEmptyAttributesMap(XmlDocument _docLoc, int _i,
                String _tagName, String _attributeName,
                String _key, String _value,
                String _container, String _listMethod)
        {
            XmlNodeList nodes_ = _docLoc.GetElementsByTagName(_tagName);
            int length_ = nodes_.Count;
            if (_key.Equals(_value))
            {
                for (int j = List.FIRST_INDEX; j < length_; j++)
                {
                    XmlNode node_ = nodes_.Item(j);
                    XmlElement elt_ = (XmlElement)node_;
                    String varLoc_ = elt_.GetAttribute(_attributeName);
                    if (!varLoc_.isEmpty())
                    {
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + GET_INDEX, _i.ToString());
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + CALL_AFTER, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR + GET_FORMAT_VAR);
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + GET_ATTRIBUTE, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR);
                        elt_.SetAttribute(_attributeName, varLoc_);
                    }
                }
            }
            else {
                for (int j = List.FIRST_INDEX; j < length_; j++)
                {
                    XmlNode node_ = nodes_.Item(j);
                    XmlElement elt_ = (XmlElement)node_;
                    String varLoc_ = elt_.GetAttribute(_attributeName);
                    if (!varLoc_.isEmpty())
                    {
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + GET_INDEX, _i.ToString());
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + CALL_AFTER, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR + _listMethod + GET_KEY + GET_FORMAT_VAR);
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + GET_ATTRIBUTE, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR + _listMethod + GET_KEY);
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _value + CALL_AFTER, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR + _listMethod + GET_VALUE + GET_FORMAT_VAR);
                        varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _value + GET_ATTRIBUTE, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR + _listMethod + GET_VALUE);
                        elt_.SetAttribute(_attributeName, varLoc_);
                    }
                }
            }
        }

        public static void updateAllAttributesMap(XmlDocument _docLoc, int _i,
                String _tagName, String _attributeName,
                String _key, String _value,
                String _container, String _listMethod)
        {
            XmlNodeList nodes_ = _docLoc.GetElementsByTagName(_tagName);
            int length_ = nodes_.Count;
            if (_key.Equals(_value))
            {
                for (int j = List.FIRST_INDEX; j < length_; j++)
                {
                    XmlNode node_ = nodes_.Item(j);
                    XmlElement elt_ = (XmlElement)node_;
                    String varLoc_ = elt_.GetAttribute(_attributeName);
                    varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + GET_INDEX, _i.ToString());
                    varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + CALL_AFTER, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR + GET_FORMAT_VAR);
                    varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + GET_ATTRIBUTE, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR);
                    elt_.SetAttribute(_attributeName, varLoc_);
                }
            }
            else {
                for (int j = List.FIRST_INDEX; j < length_; j++)
                {
                    XmlNode node_ = nodes_.Item(j);
                    XmlElement elt_ = (XmlElement)node_;
                    String varLoc_ = elt_.GetAttribute(_attributeName);
                    varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + GET_INDEX, _i.ToString());
                    varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + CALL_AFTER, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR + _listMethod + GET_KEY + GET_FORMAT_VAR);
                    varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _key + GET_ATTRIBUTE, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR + _listMethod + GET_KEY);
                    varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _value + CALL_AFTER, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR + _listMethod + GET_VALUE + GET_FORMAT_VAR);
                    varLoc_ = varLoc_.replaceAll(StringList.BOUNDS + _value + GET_ATTRIBUTE, _container + LEFT_GET_ARR + _i + RIGHT_GET_ARR + _listMethod + GET_VALUE);
                    elt_.SetAttribute(_attributeName, varLoc_);
                }
            }
        }

        public static void updateAttributesWithPrefix(XmlDocument _docLoc, int _i,
                String _tagName, String _attributeName)
        {
            XmlNodeList nodes_;
            int length_;
            nodes_ = _docLoc.GetElementsByTagName(_tagName);
            length_ = nodes_.Count;
            for (int j = List.FIRST_INDEX; j < length_; j++)
            {
                XmlNode node_ = nodes_.Item(j);
                XmlElement elt_ = (XmlElement)node_;
                String varLoc_ = elt_.GetAttribute(_attributeName);
                if (!varLoc_.Contains(CALL_METHOD))
                {
                    continue;
                }
                if (varLoc_.Contains(LEFT_PAR_COMMA))
                {
                    varLoc_ = varLoc_.Replace(LEFT_PAR_COMMA, LEFT_PAR + _i + COMMA);
                }
                else if (varLoc_.Contains(DOUBLE_COMMA))
                {
                    varLoc_ = varLoc_.replaceAll(NEXT_ARG, FORMAT_VAR + COMMA + _i + COMMA);
                }
                else if (varLoc_.Contains(COMMA_RIGHT_PAR))
                {
                    varLoc_ = varLoc_.Replace(COMMA_RIGHT_PAR, COMMA + _i + RIGHT_PAR);
                }
                else if (varLoc_.Contains(NO_PARAM_METHOD))
                {
                    varLoc_ = varLoc_.Replace(NO_PARAM_METHOD, LEFT_PAR + _i + RIGHT_PAR);
                }
                elt_.SetAttribute(_attributeName, varLoc_);
            }
        }
        public static String processMessages(Configuration _conf, String _htmlText, Bean _bean, String _loc, Map<String, String> _files, params String[] _resourcesFolder)
        {
            XmlDocument docOrig_ = XmlParser.parseSaxHtml(_htmlText);
            MyList<XmlNode> currentNodesToBeRead_ = new MyList<XmlNode>();
		    currentNodesToBeRead_.Add(docOrig_.DocumentElement);
            MyList<XmlNode> newNodesToBeRead_ = new MyList<XmlNode>();
            XmlDocument doc_ = XmlParser.parseSaxHtml(EMPTY_HTML_DOC);
            MyList<XmlNode> currentNodesToBeModified_ = new MyList<XmlNode>();
            currentNodesToBeModified_.Add(doc_.DocumentElement);
            MyList<XmlNode> newNodesToBeModified_ = new MyList<XmlNode>();
            bool modif_ = true;
            int len_;
		    while (modif_) {
			    modif_ = false;
			    newNodesToBeRead_ = new MyList<XmlNode>();
			    newNodesToBeModified_ = new MyList<XmlNode>();
			    len_ = currentNodesToBeRead_.size();
			    for (int i = List.FIRST_INDEX; i<len_; i++) {
                    XmlNode currentNode_ = currentNodesToBeRead_.get(i);
                    XmlNode currentModifiedNode_ = currentNodesToBeModified_.get(i);
				    foreach (XmlNode n in XmlParser.childrenNodes(currentNode_)) {
					    if (n is XmlElement) {
						    if (n.Name.Equals(MESSAGE_BLOCK_TAG)) {
							    String formatted_ = formatMessage(_conf, _loc, _bean, (XmlElement)n, _files, _resourcesFolder);
							    if (!((XmlElement) n).GetAttribute(ATTRIBUTE_ESCAPED).isEmpty()) {
								    XmlText nt_ = doc_.CreateTextNode(formatted_);
                                    newNodesToBeModified_.Add(nt_);
								    currentModifiedNode_.AppendChild(nt_);
								    continue;
							    }
                                formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
							    formatted_ = formatted_.Replace(E_GT, GT_TAG);
							    formatted_ = formatted_.Replace(E_AMP, AMP);
							    XmlDocument docLoc_ = XmlParser.parseSaxHtml(addToRoot(formatted_));
							    foreach (XmlNode nTwo_ in XmlParser.childrenNodes(docLoc_.DocumentElement)) {
								    newNodesToBeRead_.Add(nTwo_);
								    if (nTwo_ is XmlElement) {
									    XmlElement ne_ = doc_.CreateElement(nTwo_.Name);
                                        XmlNamedNodeMap mapElt_ = nTwo_.Attributes;
                                        int length_ = mapElt_.Count;
									    for (int j = List.FIRST_INDEX; j< length_; j++) {
										    formatted_ = mapElt_.Item(j).Value;
                                            formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
										    formatted_ = formatted_.Replace(E_GT, GT_TAG);
										    formatted_ = formatted_.Replace(E_AMP, AMP);
                                            ne_.SetAttribute(mapElt_.Item(j).Name, formatted_);
									    }
                                        newNodesToBeModified_.Add(ne_);
									    currentModifiedNode_.AppendChild(ne_);
								    }
								    if (nTwo_ is XmlText) {
									    formatted_ = nTwo_.InnerText;
									    formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
									    formatted_ = formatted_.Replace(E_GT, GT_TAG);
									    formatted_ = formatted_.Replace(E_AMP, AMP);
                                        XmlText nt_ = doc_.CreateTextNode(formatted_);
                                        newNodesToBeModified_.Add(nt_);
									    currentModifiedNode_.AppendChild(nt_);
								    }
							    }
							    continue;
						    }
						    newNodesToBeRead_.Add(n);
						    XmlElement n_ = doc_.CreateElement(n.Name);
                            XmlNamedNodeMap map_ = n.Attributes;
                            int lentgh_ = map_.Count;
						    for (int j = List.FIRST_INDEX; j<lentgh_;j++) {
							    String formatted_ = map_.Item(j).Value;
                                formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
							    formatted_ = formatted_.Replace(E_GT, GT_TAG);
							    formatted_ = formatted_.Replace(E_AMP, AMP);
							    n_.SetAttribute(map_.Item(j).Name, formatted_);
						    }
						    newNodesToBeModified_.Add(n_);
						    currentModifiedNode_.AppendChild(n_);
						    continue;
					    }
					    if (n is XmlText) {
						    newNodesToBeRead_.Add(n);
						    String formatted_ = n.InnerText;
                            formatted_ = formatted_.Replace(E_LT, LT_BEGIN_TAG);
						    formatted_ = formatted_.Replace(E_GT, GT_TAG);
						    formatted_ = formatted_.Replace(E_AMP, AMP);
						    XmlText nt_ = doc_.CreateTextNode(formatted_);
                            newNodesToBeModified_.Add(nt_);
						    currentModifiedNode_.AppendChild(nt_);
					    }
				    }
			    }
			    if (!newNodesToBeRead_.isEmpty()) {
				    currentNodesToBeRead_ = new MyList<XmlNode>(newNodesToBeRead_);
				    currentNodesToBeModified_ = new MyList<XmlNode>(newNodesToBeModified_);
				    modif_ = true;
			    }
		    }
		    return XmlParser.toHtml(doc_);
	    }

	    public static String processSubmitTags(Configuration _conf, String _htmlText, Bean _bean, String _loc, Map<String, String> _files, params String[] _resourcesFolder)
        {
            XmlDocument docOrig_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList list_ = docOrig_.GetElementsByTagName(SUBMIT_BLOCK_TAG);
		    int length_ = list_.Count;
		    for (int j = List.FIRST_INDEX; j<length_; j++) {
                XmlElement node_ = (XmlElement)list_.Item(j);
                String value_ = node_.GetAttribute(ATTRIBUTE_VALUE_SUBMIT);
                StringList elts_ = StringList.splitStrings(value_, COMMA);
                String var_ = elts_.first();
                String fileName_ = _conf.getProperties().getVal(var_);
                if (fileName_ == null)
                {
                    fileName_ = var_;
                }
                Map<String, String> messages_ = getInnerMessagesFromLocaleClass(_conf.getAssembly(), _conf.getMessagesFolder(), _loc, fileName_, _files, _resourcesFolder);
                String preformatted_ = messages_.getVal(elts_.last());
                preformatted_ = XmlParser.transformSpecialChars(preformatted_);
                MyList<Object> objects_ = new MyList<Object>();
                int i_ = List.FIRST_INDEX;
                while (node_.HasAttribute(TAG_PARAM + i_))
                {
                    String attribute_ = node_.GetAttribute(TAG_PARAM + i_);
                    if (attribute_.StartsWith(CALL_METHOD))
                    {
                        objects_.Add(extractObject(attribute_.Substring(1), _bean));
                    }
                    else {
                        objects_.Add(attribute_);
                    }
                    i_++;
                }
                node_.SetAttribute(ATTRIBUTE_VALUE, string.Format(preformatted_, objects_.ToArray()));
                node_.SetAttribute(ATTRIBUTE_TYPE, SUBMIT_TYPE);
            }
            list_ = docOrig_.GetElementsByTagName(SUBMIT_BLOCK_TAG);
		    for (int j = List.FIRST_INDEX; j<length_; j++) {
                XmlElement node_ = (XmlElement)list_.Item(j);
                renameElement(node_, INPUT_TAG);
                //docOrig_.RenameNode(node_, node_.NamespaceURI, INPUT_TAG);
            }
		    return XmlParser.toHtml(docOrig_);
        }

        public static String processTitles(Configuration _conf, String _htmlText, Bean _bean, String _loc, Map<String, String> _files, params String[] _resourcesFolder)
        {
            XmlDocument docOrig_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList list_ = docOrig_.GetElementsByTagName(A_BLOCK_TAG);
		    int length_ = list_.Count;
		    for (int j = List.FIRST_INDEX; j<length_; j++) {
                XmlElement node_ = (XmlElement)list_.Item(j);
                String value_ = node_.GetAttribute(ATTRIBUTE_VALUE);
                StringList elts_ = StringList.splitStrings(value_, COMMA);
                String var_ = elts_.first();
                String fileName_ = _conf.getProperties().getVal(var_);
                if (fileName_ == null)
                {
                    fileName_ = var_;
                }
                Map<String, String> messages_ = getInnerMessagesFromLocaleClass(_conf.getAssembly(), _conf.getMessagesFolder(), _loc, fileName_, _files, _resourcesFolder);
                String preformatted_ = messages_.getVal(elts_.last());
                preformatted_ = XmlParser.transformSpecialChars(preformatted_);
                MyList<Object> objects_ = new MyList<Object>();
                int i_ = List.FIRST_INDEX;
                while (node_.HasAttribute(TAG_PARAM + i_))
                {
                    String attribute_ = node_.GetAttribute(TAG_PARAM + i_);
                    if (attribute_.StartsWith(CALL_METHOD))
                    {
                        objects_.Add(extractObject(attribute_.Substring(1), _bean));
                    }
                    else {
                        objects_.Add(attribute_);
                    }
                    i_++;
                }
                node_.SetAttribute(ATTRIBUTE_TITLE, string.Format(preformatted_, objects_.ToArray()));
            }
            list_ = docOrig_.GetElementsByTagName(A_BLOCK_TAG);
		    for (int j = List.FIRST_INDEX; j<length_; j++) {
                XmlElement node_ = (XmlElement)list_.Item(j);
                renameElement(node_, TAG_A);
                //docOrig_.renameNode(node_, node_.NamespaceURI, TAG_A);
            }
		    return XmlParser.toHtml(docOrig_);
        }

        public static String formatErrorMessage(Configuration _conf, String _textId, String _loc, Map<String, String> _files, String _resourcesFolder, params Object[] _args)
        {
            String value_ = _textId;
            StringList elts_ = StringList.splitStrings(value_, COMMA);
            String var_ = elts_.first();
            String fileName_ = _conf.getProperties().getVal(var_);
            if (fileName_ == null)
            {
                fileName_ = var_;
            }
            Map<String, String> messages_ = getInnerMessagesFromLocaleClass(_conf.getAssembly(), _conf.getMessagesFolder(), _loc, fileName_, _files, _resourcesFolder);
            String preformatted_ = messages_.getVal(elts_.last());
            preformatted_ = XmlParser.transformSpecialChars(preformatted_);
            return string.Format(preformatted_, _args);
        }

        public static String processCss(String _assembly,String _htmlText, Map<String, String> _files, params String[] _resourcesFolder)
        {
            XmlDocument docOrig_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList list_ = docOrig_.GetElementsByTagName(TAG_LINK);
            XmlNode link_ = null;
            XmlElement style_ = null;
		    int length_ = list_.Count;
            bool success_ = false;
            bool successAdd_ = false;
		    for (int j = List.FIRST_INDEX; j<length_; j++) {
                link_ = list_.Item(j);
                XmlNamedNodeMap map_ = link_.Attributes;
                if (!((XmlElement)link_).GetAttribute(ATTRIBUTE_REL).Equals(STYLESHEET))
                {
                    continue;
                }
                XmlNode href_ = map_.GetNamedItem(ATTRIBUTE_HREF);
                if (href_ == null)
                {
                    continue;
                }
                XmlNodeList styles_ = docOrig_.GetElementsByTagName(TAG_STYLE);
                if (styles_.Count == 0)
                {
                    style_ = docOrig_.CreateElement(TAG_STYLE);
                    XmlText txt_ = docOrig_.CreateTextNode(getContentFile(_assembly, _files, href_.Value, _resourcesFolder));
                    style_.AppendChild(txt_);
                    successAdd_ = true;
                }
                else {
                    style_ = (XmlElement)styles_.Item(0);
                    if (style_.ChildNodes.Count == 0)
                    {
                        XmlText txt_ = docOrig_.CreateTextNode(getContentFile(_assembly, _files, href_.Value, _resourcesFolder));
                        style_.AppendChild(txt_);

                    }
                    else {
                        XmlText child_ = (XmlText)style_.ChildNodes.Item(0);
                        child_.AppendData(getContentFile(_assembly, _files, href_.Value, _resourcesFolder));
                    }
                    successAdd_ = false;
                }
                success_ = true;
                break;
            }
		    if (success_) {
                list_ = docOrig_.GetElementsByTagName(TAG_HEAD);
                list_.Item(0).RemoveChild(link_);
                if (successAdd_)
                {
                    list_.Item(0).AppendChild(style_);
                }
            }
		    return XmlParser.toHtml(docOrig_);
        }

        public static String processScript(String _assembly, String _htmlText, Map<String, String> _files, params String[] _resourcesFolder)
        {
            XmlDocument docOrig_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList list_ = docOrig_.GetElementsByTagName(SCRIPT);
            XmlElement link_ = null;
		    int length_ = list_.Count;
		    for (int j = List.FIRST_INDEX; j<length_; j++) {
                link_ = (XmlElement)list_.Item(j);
                XmlNamedNodeMap map_ = link_.Attributes;
                XmlNode href_ = map_.GetNamedItem(ATTRIBUTE_HREF);
                if (href_ == null)
                {
                    continue;
                }
                link_.SetAttribute(ATTRIBUTE_TYPE, SCRIPT_TYPE);
                XmlText txt_ = docOrig_.CreateTextNode(getContentFile(_assembly, _files, href_.Value, _resourcesFolder));
                link_.AppendChild(txt_);
                break;
            }
		    return XmlParser.toHtml(docOrig_);
        }

        public static String processSpansErrors(String _htmlText)
        {
            XmlDocument docOrig_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList list_ = docOrig_.GetElementsByTagName(SPAN_TAG);
            XmlElement link_ = null;
		    int length_ = list_.Count;
		    for (int j = List.FIRST_INDEX; j<length_; j++) {
                link_ = (XmlElement)list_.Item(j);
                XmlNamedNodeMap map_ = link_.Attributes;
                XmlNode href_ = map_.GetNamedItem(ATTRIBUTE_FOR);
                if (href_ == null)
                {
                    continue;
                }
                if (!XmlParser.childrenNodes(link_).isEmpty())
                {
                    continue;
                }
                XmlText txt_ = docOrig_.CreateTextNode(SPACE);
                link_.AppendChild(txt_);
            }
		    return XmlParser.toHtml(docOrig_);
        }

        static String processImagesTags(String _htmlText)
        {
            XmlDocument docOrig_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList list_ = docOrig_.GetElementsByTagName(IMG_BLOCK_TAG);
		    int length_ = list_.Count;
		    for (int j = List.FIRST_INDEX; j<length_; j++) {
                XmlElement node_ = (XmlElement)list_.Item(j);
                renameElement(node_, TAG_IMG);
                //docOrig_.renameNode(node_, node_.NamespaceURI, TAG_IMG);
            }
		    return XmlParser.toHtml(docOrig_);
        }

        static String processImages(String _assembly,String _htmlText, Map<String, String> _files, params String[] _resourcesFolder)
        {
            XmlDocument docOrig_ = XmlParser.parseSaxHtml(_htmlText);
            XmlNodeList list_ = docOrig_.GetElementsByTagName(TAG_IMG);
		    int length_ = list_.Count;
		    for (int j=List.FIRST_INDEX; j<length_; j++) {
                XmlNode node_ = list_.Item(j);
                String src_ = ((XmlElement)node_).GetAttribute(ATTRIBUTE_SRC);
                if (src_.isEmpty())
                {
                    continue;
                }
                bool keep_ = ((XmlElement)node_).GetAttribute(ATTRIBUTE_ENCODE_IMG).isEmpty();
                String content_ = getContentFile(_assembly, _files, src_, _resourcesFolder);
                if (keep_)
                {
                    ((XmlElement)node_).SetAttribute(ATTRIBUTE_SRC, content_);
                }
                else {
                    content_ = ConverterBufferedImage.surroundImage(content_);
                    ((XmlElement)node_).SetAttribute(ATTRIBUTE_SRC, content_);
                }
            }
		    return XmlParser.toHtml(docOrig_);
        }
        //A VERY VERY hard method to understand vs JAVA
        public static XmlElement renameElement(XmlElement _e, string _newName)
        {
            XmlElement oldElement_ = _e;
            XmlElement newElement_ = _e.OwnerDocument.CreateElement(_newName, _e.NamespaceURI);
            while (oldElement_.HasAttributes)
            {
                newElement_.SetAttributeNode(oldElement_.RemoveAttributeNode(oldElement_.Attributes[0]));
            }
            while (oldElement_.HasChildNodes)
            {
                newElement_.AppendChild(oldElement_.FirstChild);
            }
            if (oldElement_.ParentNode != null)
            {
                oldElement_.ParentNode.ReplaceChild(newElement_, oldElement_);
            }
            return newElement_;
            /*XmlDocument doc_ = _e.OwnerDocument;
            XmlElement newElement_ = doc_.CreateElement(_newName);
            while (_e.HasChildNodes)
            {
                newElement_.AppendChild(_e.FirstChild);
            }
            setAttributes(newElement_, _e.Attributes);
            XmlAttributeCollection ac_ = _e.Attributes;*/
            /*int len_ = ac_.Count;
            for (int i = 0; i < len_; i++)
            {
                newElement_.SetAttribute(ac_.Item(i).Name, ac_.Item(i).Value);
            }
            while (ac_.Count > 0)
            {
                newElement_.Attributes.Append(ac_[0]);
            }*/
            /*XmlNode parent_ = _e.ParentNode;
            parent_.InsertBefore(newElement_, _e);
            parent_.RemoveChild(_e);
            return newElement_;*/
        }
        public static String formatMessage(Configuration _conf, String _loc, Bean _object, XmlElement _element, Map<String, String> _files, params String[] _resourcesFolder)

        {
            String value_ = _element.GetAttribute(ATTRIBUTE_VALUE);
            MyList<Object> objects_;
            String preformatted_;
            if (value_.StartsWith(CALL_METHOD))
            {
                preformatted_ = extractObject(value_.Substring(1), _object).ToString();
                objects_ = new MyList<Object>();
                foreach (XmlNode n in XmlParser.childrenNodes(_element))
                {
                    if (!(n is XmlElement))
                    {
                        continue;
                    }
                    String attribute_ = ((XmlElement)n).GetAttribute(ATTRIBUTE_VALUE);
                    if (attribute_.StartsWith(CALL_METHOD))
                    {
                        objects_.Add(extractObject(attribute_.Substring(1), _object));
                    }
                    else {
                        objects_.Add(attribute_);
                    }
                }
                return string.Format(preformatted_, objects_.ToArray());
            }
            StringList elts_ = StringList.splitStrings(value_, COMMA);
            String var_ = elts_.first();
            String fileName_ = _conf.getProperties().getVal(var_);
            if (fileName_ == null)
            {
                fileName_ = var_;
            }
            Map<String, String> messages_ = getInnerMessagesFromLocaleClass(_conf.getAssembly(), _conf.getMessagesFolder(), _loc, fileName_, _files, _resourcesFolder);
            preformatted_ = messages_.getVal(elts_.last());
            objects_ = new MyList<object>();
            foreach (XmlNode n in XmlParser.childrenNodes(_element))
            {
                if (!(n is XmlElement))
                {
                    continue;
                }
                String attribute_ = ((XmlElement)n).GetAttribute(ATTRIBUTE_VALUE);
                if (attribute_.StartsWith(CALL_METHOD))
                {
                    objects_.Add(extractObject(attribute_.Substring(1), _object));
                }
                else {
                    objects_.Add(attribute_);
                }
            }
            return string.Format(preformatted_, objects_.ToArray());
        }
        public static Object extractObject(String _command, Object _container)
        {
            Object object_ = _container;
            int index_;
            StringList indexRegExp_;
            StringList methRegExp_;
            String methodName_;
            foreach (String f in calls(_command)) {
                Type class_ = object_.GetType();
                String token_ = f;
                if (f.Contains(PATH_CLASS_SEPARATOR))
                {
                    int lastIndex_ = f.LastIndexOf(PATH_CLASS_SEPARATOR);
                    String subString_ = f.Substring(List.FIRST_INDEX, lastIndex_);
                    subString_ = subString_.Replace(PATH_CLASS_SEPARATOR, DOT);
                    class_ = getSuperClass(class_, subString_);
                    lastIndex_++;
                    token_ = f.Substring(lastIndex_);
                }
                if (token_.EndsWith(NO_PARAM_METHOD))
                {
                    try
                    {
                        MethodInfo m_ = SerializeXmlObject.getDeclaredMethod(class_, token_.Substring(0, token_.Length - 2));
                        // m_.setAccessible(access(m_));
                        object_ = m_.Invoke(object_, new object[0]);
                    }
                    catch (Exception e_)
                    {
                        Console.WriteLine(e_.StackTrace);
                        throw e_;
                    }
                    continue;
                }
                if (token_.Contains(LEFT_PAR))
                {
                    try
                    {
                        String mName_ = token_.Substring(List.FIRST_INDEX, token_.IndexOf(LEFT_PAR));
                        String args_ = token_.Substring(token_.IndexOf(LEFT_PAR) + 1);
                        args_ = args_.Substring(List.FIRST_INDEX, args_.Length - 1);
                        MyList<Type> classes_ = new MyList<Type>();
                        MyList<object> argsLong_ = new MyList<object>();
                        foreach (String l in StringList.splitStrings(args_, COMMA))
                        {
                            argsLong_.Add(long.Parse(l));
                            classes_.Add(typeof(long));
					    }
                        MethodInfo m_ = SerializeXmlObject.getDeclaredMethod(class_, mName_, classes_.ToArray());
                        //m_.setAccessible(access(m_));
                        object_ = m_.Invoke(object_, argsLong_.ToArray());
				    } catch (Exception e_) {
					    throw e_;
				    }
    
				    continue;
			    }
			    if (token_.StartsWith(LEFT_GET_ARR) && token_.EndsWith(RIGHT_GET_ARR)) {
                    Regex regOne_ = new Regex(REG_EXP_GET_ARR);
				    String info_ = regOne_.Replace(token_, EMPTY_STRING);
                    index_ = int.Parse(info_);
                    object_ = (object_ as IEnumerable).getObj(index_);
				    continue;
			    }
			    if (token_.StartsWith(LEFT_GET_ARR)) {
                    ListableKey mapCast_;
                    IEnumerable keys_;
                    if (token_.EndsWith(GET_KEY)) {
					    indexRegExp_ = StringList.matchingRegExp(token_, INT_REG_EXP);
                        methRegExp_ = StringList.matchingRegExp(token_, REG_EXP_MAP_METH);
                        index_ = int.Parse(indexRegExp_.first());
                        methodName_ = methRegExp_.first().Replace(GET_ENTRY, EMPTY_STRING);
					    if (!methodName_.Equals(NULL_STRING)) {
						    try {
							    MethodInfo m_ = SerializeXmlObject.getDeclaredMethod(class_, methodName_);
                                //m_.setAccessible(access(m_));
							    object_ = (m_.Invoke(object_, new object[0]) as IEnumerable).getObj(index_);
						    } catch (Exception e_) {
							    throw e_;
						    }
						    continue;
					    }
					    mapCast_ = (ListableKey) object_;
					    keys_ = mapCast_.getKeysGene();
					    if (!(mapCast_ is IComparableKeys)) {
						    keys_ = orderedList(keys_);
					    }
					    object_ = keys_.getObj(index_);
					    continue;
				    }
				    indexRegExp_ = StringList.matchingRegExp(token_, INT_REG_EXP);
                    methRegExp_ = StringList.matchingRegExp(token_, REG_EXP_MAP_METH);
                    index_ = int.Parse(indexRegExp_.first());
                    methodName_ = methRegExp_.first().Replace(GET_ENTRY, EMPTY_STRING);
                    Object key_ = null;
                    if (!methodName_.Equals(NULL_STRING)) {
					    try {
                            MethodInfo m_ = SerializeXmlObject.getDeclaredMethod(class_, methodName_);
                            //m_.setAccessible(access(m_));
						    key_ = (m_.Invoke(object_, new object[0]) as IEnumerable).getObj(index_);
                            mapCast_ = (ListableKey) object_;
						    object_ = mapCast_.getGene(key_);
					    } catch (Exception e_) {
						    throw e_;
					    }
					    continue;
				    }
                    mapCast_ = (ListableKey) object_;
				    keys_ = mapCast_.getKeysGene();
				    if (!(mapCast_ is IComparableKeys)) {
					    keys_ = orderedList(keys_);
				    }
				    object_ = mapCast_.getGene(keys_.getObj(index_));
				    continue;
			    }
			    FieldInfo f_ = SerializeXmlObject.getDeclaredField(class_, token_);
                //f_.setAccessible(access(f_));
			    object_ = f_.GetValue(object_);
		    }
		    return object_;
	    }
        private static IEnumerable orderedList(IEnumerable _map)
        {
            MyList<object> list_ = new MyList<object>(_map);
            list_.Sort();
		    return list_;
	    }

        public static Type getSuperClass(Type _class, String _name)
        {
            bool found_ = false;
            Type class_ = _class;
            string name_ = _name;
            string suffix_ = name_.Split('.').Last();
            if (StringList.isInteger(suffix_))
            {
                name_ = name_.Replace("." + suffix_, ElementsSerial.SPECIAL_SEP+suffix_);
            }
            while (true) {
                string fullName_ = class_.Assembly.GetName().Name + "." + class_.FullName;
                if (fullName_.Contains("["))
                {
                    fullName_ = fullName_.Split('[').ElementAt(0);
                }
                //string fullName_ = Constants.getTypeFullString(class_);
                //SPECIAL_SEP
                if (fullName_.ToLower().Equals(name_.ToLower()))
                {
                    found_ = true;
                    break;
                }
                if (class_ == typeof(object)) {
				    break;
			    }
			    class_ = class_.BaseType;
		    }
		    if (found_) {
			    return class_;
		    }
            string fullNameEx_ = Constants.getTypeFullString(class_);
            throw new SuperClassNotFoundException(fullNameEx_, _name);
	    }
        public static StringList calls(String _command)
        {
            StringList tokensSepar_ = StringList.getTokensSeparators(_command, TOKENS_CALLS);
            StringList calls_ = new StringList();
            int i_ = List.FIRST_INDEX;
            while (i_ < tokensSepar_.size())
            {
                if (i_ % ESCAPED_TOKEN == 0)
                {
                    i_++;
                    continue;
                }
                String token_ = tokensSepar_.get(i_);
                if (!StringList.matchingRegExp(token_, REG_EXP_FIELD).isEmpty())
                {
                    bool method_ = false;
                    if (i_ + ESCAPED_TOKEN < tokensSepar_.size())
                    {
                        if (tokensSepar_.get(i_ + 1).StartsWith(NO_PARAM_METHOD))
                        {
                            String newToken_ = token_;
                            newToken_ += NO_PARAM_METHOD;
                            calls_.Add(newToken_);
                            method_ = true;
                        }
                        if (!StringList.matchingRegExp(tokensSepar_.get(i_ + ESCAPED_TOKEN), REG_EXP_ARGS).isEmpty())
                        {
                            String newToken_ = token_;
                            i_ += ESCAPED_TOKEN;
                            newToken_ += tokensSepar_.get(i_);
                            calls_.Add(newToken_);
                            method_ = true;
                        }
                    }
                    else if (i_ + 1 < tokensSepar_.size())
                    {
                        String newToken_ = token_;
                        newToken_ += NO_PARAM_METHOD;
                        calls_.Add(newToken_);
                        method_ = true;
                    }
                    if (!method_)
                    {
                        calls_.Add(token_);
                    }
                }
                if (!StringList.matchingRegExp(token_, REG_EXP_GET_INDEX).isEmpty())
                {
                    if (i_ + 1 == tokensSepar_.size())
                    {
                        calls_.Add(token_);
                        i_++;
                        continue;
                    }
                    if (tokensSepar_.get(i_ + 1).Equals(DOT))
                    {
                        calls_.Add(token_);
                        i_++;
                        continue;
                    }
                    if (!StringList.matchingRegExp(tokensSepar_.get(i_ + ESCAPED_TOKEN), REG_EXP_GET_INDEX).isEmpty())
                    {
                        calls_.Add(token_);
                        i_++;
                        continue;
                    }
                    calls_.Add(token_ + tokensSepar_.get(i_ + ESCAPED_TOKEN) + GET_ENTRY + tokensSepar_.get(i_ + ESCAPED_TOKENS));
                    i_ += ESCAPED_TOKENS;
                }
                i_++;
            }
            return calls_;
        }
        public static String formatNamedVariables(String _pattern, Configuration _conf, Map<String, String> _files, Bean _object)
        {
            Map<String,String> fields_ = new Map<String, String>();
		    foreach (String k in getFields(_pattern)) {
			    if (!k.Contains(TR)) {
				    Object o_ = extractObject(k, _object);
                    fields_.put(LEFT_EL+k+RIGHT_EL, encodeXml(o_));
			    } else {
				    StringList infos_ = StringList.splitStrings(k, TR);
                    Regex reg_ = new Regex(DOT_END);
                    Object o_ = extractObject(reg_.Replace(infos_.first(), EMPTY_STRING), _object);
                    o_ = _conf.getTranslators().getVal(infos_.last()).getString(_pattern, _conf, _files, _object, o_);
                    fields_.put(LEFT_EL+k+RIGHT_EL, encodeXml(o_));
			    }
		    }
		    return StringList.formatQuote(_pattern, fields_);
	    }
        public static StringList getFields(String _pattern)
        {
            StringList tokens_;
            tokens_ = new StringList();
            int i_ = List.FIRST_INDEX;
            while (i_ < _pattern.Length)
            {
                int indexOne_ = _pattern.IndexOf(FORMAT_QUOTE, i_);
                StringList tokensSep_;
                int nbTokensSep_;
                if (indexOne_ == List.INDEX_NOT_FOUND_ELT)
                {
                    //add tokens from _pattern (min:i_+1)
                    tokensSep_ = StringList.getTokensSeparators(_pattern.Substring(i_), REG_EXP_EL);
                    nbTokensSep_ = tokensSep_.size();
                    for (int i = List.FIRST_INDEX; i < nbTokensSep_; i++)
                    {
                        if (i % 2 == 0)
                        {
                            continue;
                        }
                        Regex reg_ = new Regex(BOUNDS_EL);
                        String token_ = reg_.Replace(tokensSep_.get(i), EMPTY_STRING);
                        tokens_.Add(token_);
                    }
                    break;
                }
                tokensSep_ = StringList.getTokensSeparators(_pattern.Substring(i_, indexOne_ - i_), REG_EXP_EL);
                nbTokensSep_ = tokensSep_.size();
                for (int i = List.FIRST_INDEX; i < nbTokensSep_; i++)
                {
                    if (i % 2 == 0)
                    {
                        continue;
                    }
                    Regex reg_ = new Regex(BOUNDS_EL);
                    String token_ = reg_.Replace(tokensSep_.get(i), EMPTY_STRING);
                    tokens_.Add(token_);
                }
                int indexTwo_ = _pattern.IndexOf(FORMAT_QUOTE, indexOne_ + 1);
                if (indexTwo_ == List.INDEX_NOT_FOUND_ELT)
                {
                    break;
                }
                i_ = indexTwo_ + 1;
            }
            return tokens_;
        }
        public static String encodeXml(Object _object)
        {
            if (_object == null)
            {
                return null;
            }
            String string_ = _object.ToString();
            Map<String, String> chars_ = new Map<String, String>();
            chars_.put(AMP, E_AMP);
            chars_.put(LT_BEGIN_TAG, E_LT);
            chars_.put(GT_TAG, E_GT);
            return StringList.formatBasic(string_, chars_, true);
        }
        public static Map<String, String> getInnerMessagesFromLocaleClass(String _assembly, String _folder, String _loc, String _relative, Map<String, String> _files, params String[] _resourcesFolder)
        {
            String fileName_ = StreamTextFile.getPropertiesPath(_folder, _loc, _relative);
            String content_ = getContentFile(_assembly, _files, fileName_, _resourcesFolder);
            return StreamTextFile.getMessages(content_);
        }
        public static String getContentFile(String _assembly, Map<String, String> _files, String _fileName, params String[] _resourcesFolder)
        {
            string fileName_ = _fileName.ToLower();
            foreach (Entry<String, String> e in _files.entryList())
            {
                if (e.getKey().ToLower().Equals(fileName_))
                {
                    return e.getValue();
                }
            }
            return StreamTextFile.resourceFileUrls(_assembly, _fileName, _resourcesFolder);
        }
        public static String loadPage(string _assembly,Map<String, String> _files, String _link, params String[] _resourcesFolder)
        {
            String link_ = _link;
            link_ = link_.Replace(IMPLICIT_LANGUAGE, StreamTextFile.SEPARATEUR + Constants.getLanguage() + StreamTextFile.SEPARATEUR);
            String contents_ = getContentFile(_assembly, _files, link_, _resourcesFolder);
            return transformResourceUrl(contents_);
        }
        private static String transformResourceUrl(String _htmlText)
        {
            String newHtmlText_ = _htmlText;
            try
            {
                XmlDocument doc_ = XmlParser.parseSaxHtml(newHtmlText_);
                XmlNodeList ls_ = doc_.GetElementsByTagName(TAG_IMG);
                int s_ = ls_.Count;
                for (int i = List.FIRST_INDEX; i < s_; i++)
                {
                    XmlNamedNodeMap map_ = ls_.Item(i).Attributes;
                    XmlNode src_ = map_.GetNamedItem(ATTRIBUTE_SRC);
                    if (src_ == null)
                    {
                        continue;
                    }
                    String attribute_ = src_.Value;
                    if (attribute_.StartsWith(FILE))
                    {
                        continue;
                    }
                    attribute_ = attribute_.Replace(IMPLICIT_LANGUAGE, StreamTextFile.SEPARATEUR + Constants.getLanguage() + StreamTextFile.SEPARATEUR);
                    src_.Value = attribute_;
                }
                ls_ = doc_.GetElementsByTagName(TAG_LINK);
                s_ = ls_.Count;
                for (int i = List.FIRST_INDEX; i < s_; i++)
                {
                    XmlNamedNodeMap map_ = ls_.Item(i).Attributes;
                    XmlNode rel_ = map_.GetNamedItem(ATTRIBUTE_REL);
                    if (rel_ == null || !rel_.Value.Equals(STYLESHEET))
                    {
                        continue;
                    }
                    XmlNode href_ = map_.GetNamedItem(ATTRIBUTE_HREF);
                    if (href_ == null)
                    {
                        continue;
                    }
                    String attribute_ = href_.Value;
                    if (attribute_.StartsWith(FILE))
                    {
                        continue;
                    }
                    attribute_ = attribute_.Replace(IMPLICIT_LANGUAGE, StreamTextFile.SEPARATEUR + Constants.getLanguage() + StreamTextFile.SEPARATEUR);
                    href_.Value=attribute_;
                }
                ls_ = doc_.GetElementsByTagName(TAG_A);
                s_ = ls_.Count;
                for (int i = List.FIRST_INDEX; i < s_; i++)
                {
                    XmlNamedNodeMap map_ = ls_.Item(i).Attributes;
                    XmlNode href_ = map_.GetNamedItem(ATTRIBUTE_HREF);
                    if (href_ == null)
                    {
                        continue;
                    }
                    String attribute_ = href_.Value;
                    if (attribute_.isEmpty())
                    {
                        href_ = map_.GetNamedItem(ATTRIBUTE_COMMAND);
                        if (href_ == null)
                        {
                            continue;
                        }
                        attribute_ = href_.Value;
                    }
                    if (attribute_.StartsWith(FILE))
                    {
                        continue;
                    }
                    attribute_ = attribute_.Replace(IMPLICIT_LANGUAGE, StreamTextFile.SEPARATEUR + Constants.getLanguage() + StreamTextFile.SEPARATEUR);
                    href_.Value=attribute_;
                }
                ls_ = doc_.GetElementsByTagName(TAG_FORM);
                s_ = ls_.Count;
                for (int i = List.FIRST_INDEX; i < s_; i++)
                {
                    XmlNamedNodeMap map_ = ls_.Item(i).Attributes;
                    XmlNode action_ = map_.GetNamedItem(ATTRIBUTE_ACTION);
                    if (action_ == null)
                    {
                        continue;
                    }
                    String attribute_ = action_.Value;
                    if (attribute_.isEmpty())
                    {
                        action_ = map_.GetNamedItem(ATTRIBUTE_COMMAND);
                        if (action_ == null)
                        {
                            continue;
                        }
                        attribute_ = action_.Value;
                    }
                    if (attribute_.StartsWith(FILE))
                    {
                        continue;
                    }
                    attribute_ = attribute_.Replace(IMPLICIT_LANGUAGE, StreamTextFile.SEPARATEUR + Constants.getLanguage() + StreamTextFile.SEPARATEUR);
                    action_.Value=attribute_;
                }
                newHtmlText_ = XmlParser.toHtml(doc_);
            }
            catch (Exception)
            {
            }
            return newHtmlText_;
        }
    }
}
