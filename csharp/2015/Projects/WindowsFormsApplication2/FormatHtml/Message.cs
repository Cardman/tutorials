using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FormatHtml
{
    public class Message
    {
        private String message;

        private Object[] args;

        private bool formatMessage;

        public String format()
        {
            if (!formatMessage)
            {
                return message;
            }
            return string.Format(message, args);
        }

        public String getMessage()
        {
            return message;
        }

        public void setMessage(String _message)
        {
            message = _message;
        }

        public Object[] getArgs()
        {
            return args;
        }

        public void setArgs(params Object[] _args)
        {
            args = _args;
        }

        public bool isFormatMessage()
        {
            return formatMessage;
        }

        public void setFormatMessage(bool _formatMessage)
        {
            formatMessage = _formatMessage;
        }
    }
}
