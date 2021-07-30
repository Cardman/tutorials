using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace ReflectionCore
{
    public sealed class ConverterMethod
    {
        private ConverterMethod()
        {
        }
        public static List<PropertyInfo> getFields(Type _class)
        {
            List<PropertyInfo> l_;
            l_ = new List<PropertyInfo>();
            foreach (PropertyInfo fieldInfo_ in _class.GetProperties(BindingFlags.NonPublic |
                         BindingFlags.Instance))
            {
                l_.Add(fieldInfo_);
            }
            return l_;
        }
        public static MethodInfo getFromStringMethod(Type _class)
        {
            Console.WriteLine("%%%%");
            //_class.GetFields()[0].
            MethodInfo method_ = null;
            foreach (MethodInfo methClass_ in _class.GetMethods())
            {
                if (!methClass_.IsStatic)
                {
                    continue;
                }
                /*if (!(methClass_.GetCustomAttribute(typeof(FromAndToString)) is FromAndToString))
                {
                    continue;
                }*/
                if (methClass_.GetCustomAttribute(typeof(FromAndToString)) == null)
                {
                    continue;
                }
                if (methClass_.ReturnType == null)
                {
                    Console.WriteLine(methClass_.Name);
                    continue;
                }
                if (!_class.IsAssignableFrom(methClass_.ReturnType))
                {
                    Console.WriteLine(methClass_.Name);
                    continue;
                }
                ParameterInfo[] param_ = methClass_.GetParameters();
                if (param_.LongLength  != 1)
                {
                    Console.WriteLine(methClass_.Name);
                    continue;
                }
                if (param_[0].ParameterType != typeof(string))
                {
                    Console.WriteLine(methClass_.Name);
                    continue;
                }
			    if (method_ == null) {
				    method_ = methClass_;
			    } else {
				    method_ = null;
				    break;
			    }
		    }
		    return method_;
	    }

	    public static MethodInfo getToStringMethod(Type _class)
        {
            Console.WriteLine("%%%%");
            MethodInfo method_ = null;
            foreach (MethodInfo methClass_ in _class.GetMethods())
            {
                if (methClass_.IsStatic)
                {
                    continue;
                }
                /*if (!(methClass_.GetCustomAttribute(typeof(FromAndToString)) is FromAndToString))
                {
                    continue;
                }*/
                if (methClass_.GetCustomAttribute(typeof(FromAndToString)) == null)
                {
                    continue;
                }
                if (methClass_.ReturnType != typeof(string))
                {
                    Console.WriteLine(methClass_.Name);
                    continue;
                }
                ParameterInfo[] param_ = methClass_.GetParameters();
                if (param_.LongLength > 0)
                {
                    Console.WriteLine(methClass_.Name);
                    continue;
                }
			    if (method_ == null) {
				    method_ = methClass_;
			    } else {
				    method_ = null;
				    break;
			    }
		    }
		    return method_;
	    }
    }
}
