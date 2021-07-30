using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace Stream
{
    public class StreamZipFile
    {
        private static Map<String, Assembly> _assemblies_ = new Map<String,Assembly>();
        public static Map<String, String> zippedTextFiles(String _zipFileName)
        {
            Map<String, String> map_ = new Map<String, String>();
            ZipArchive zip_ = ZipFile.OpenRead(_zipFileName);
            ReadOnlyCollection<ZipArchiveEntry> e_ = zip_.Entries;
            foreach (ZipArchiveEntry e in e_)
            {
                System.IO.Stream str_ = e.Open();
                using (StreamReader reader_ = new StreamReader(str_))
                {
                    map_.put(e.FullName, reader_.ReadToEnd());
                }
                str_.Dispose();
            }
            return map_;
        }
        public static String getInsensitiveCaseFileInJar(String _assembly, String _file)
        {
            String file_ = _file.Replace(StreamTextFile.B_SEPARATEUR, StreamTextFile.SEPARATEUR);
            file_ = file_.ToLower().Replace("/",".");
            foreach (String s in zippedFiles(_assembly))
            {
                if (s.ToLower().Equals(file_))
                {
                    return s;
                }
            }
            return _file;
        }
        public static void freeAssembly(string _assembly)
        {
            _assemblies_.removeKey(_assembly);
        }
        public static StringList zippedFiles(string _assembly)
        {
            StringList files_ = new StringList();
            Assembly as_ = getAssembly(_assembly);
            string[] files = as_.GetManifestResourceNames();
            foreach(string f in files)
            {
                files_.Add(f.Replace(".","/"));
            }
            return files_;
        }
        internal static Assembly getAssembly(string _assembly)
        {
            if (!_assemblies_.contains(_assembly))
            {
                Assembly as_ = Assembly.Load(_assembly);
                _assemblies_.put(_assembly, as_);
                return as_;
            }
            else
            {
                return _assemblies_.getVal(_assembly);
            }
        }
    }
}
