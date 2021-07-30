using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace Stream
{
    public class StreamTextFile
    {
        public const String SEPARATEUR = "/";
        public const String B_SEPARATEUR = "\\";
        private const String EMPTY_STRING = "";
        private const String PROPERTIES_PATTERN = "{0}/{1}/{2}.properties";
        private const String TAB = "\t";
        private const String EQUALS = "=";
        private const String LINE_RETURN = "\n";
        private const String BEFORE_LINE_RETURN = "\r\n";
        private const String DOT = ".";
        public static String getPropertiesPath(String _folder, String _language, String _file)
        {
            return string.Format(PROPERTIES_PATTERN, _folder, _language, _file.Replace(DOT, SEPARATEUR).ToLower());
        }
        public static String resourceFileUrls(String _assembly, String _filePath, params String[] _resourcesFolder)
        {
            StringList urls_ = new StringList();
            urls_.Add(EMPTY_STRING);
            foreach (String u in _resourcesFolder)
            {
                urls_.Add(u);
            }
            foreach (String u in urls_)
            {
                try
                {
                    return getContentFileInJar(_assembly, u + _filePath);
                }
                catch (Exception)
                {
                }
            }
            return contentsOfFile(_filePath);
        }
        public static String getContentFileInJar(String _assembly, String _file)
        {
            String file_ = _file.Replace(StreamTextFile.B_SEPARATEUR, StreamTextFile.SEPARATEUR);
            file_ = file_.ToLower().Replace("/", ".");
            Assembly as_ = StreamZipFile.getAssembly(_assembly);
            System.IO.Stream str_;
            StreamReader read_;
            string content_;
            foreach (String s in as_.GetManifestResourceNames())
            {
                if (s.ToLower().Equals(file_))
                {
                    str_ = as_.GetManifestResourceStream(s);
                    read_ = new StreamReader(str_);
                    content_ = read_.ReadToEnd();
                    read_.Dispose();
                    str_.Dispose();
                    return content_;
                }
            }
            str_ = as_.GetManifestResourceStream(_file);
            read_ = new StreamReader(str_);
            content_ = read_.ReadToEnd();
            read_.Dispose();
            str_.Dispose();
            return content_;
        }
        public static Map<String, String> getMessages(String _content)
        {
            String lastKey_ = EMPTY_STRING;
            Map<String, String> messages_ = new Map<String, String>();
            foreach (String l in StringList.splitStrings(_content, BEFORE_LINE_RETURN, LINE_RETURN))
            {
                if (l.isEmpty())
                {
                    continue;
                }
                if (l.StartsWith(TAB))
                {
                    String text_ = messages_.getVal(lastKey_);
                    if (text_ != null)
                    {
                        text_ += l.Substring(1);
                        messages_.put(lastKey_, text_);
                    }
                }
                else {
                    int indexSep_ = l.IndexOf(EQUALS);
                    lastKey_ = l.Substring(0, indexSep_);
                    messages_.put(lastKey_, l.Substring(indexSep_ + 1));
                }
            }
            return messages_;
        }
        public static String contentsOfFile(String _nomFichier)
        {
            FileStream fileStream_ = new FileStream(_nomFichier, FileMode.Open, FileAccess.Read);
            // read from file
            string contentFile_ = "";
            using (StreamReader reader_ = new StreamReader(fileStream_))
            {
                contentFile_ = reader_.ReadToEnd();
            }
            fileStream_.Dispose();
            return contentFile_;
        }
        public static void saveTextFile(String _nomFichier, String _text)
        {
            FileStream fileStream_ = new FileStream(_nomFichier, FileMode.Create, FileAccess.Write);
            using (StreamWriter writer_ = new StreamWriter(fileStream_))
            {
                writer_.Write(_text);
                writer_.Flush();
            }
        }
    }
}
