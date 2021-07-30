using SampleUmlForComponents;
using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ComponentsEvents
{
    [Serializable]
    public class FileTable : DataTable
    {
        const int NAME_INDEX = 0;

        const int DATE_INDEX = 1;

        const int SIZE_INDEX = 2;

        const int PATH_INDEX = 3;

        private const string END_NUM = " 98";

	    private const string BEGIN_NUM = " 01";

	    private const string END_ALPH = " ZY";

	    private const string BEGIN_ALPH = " AB";

        private const string DATE_FORMAT = "dd-MM-yyyy HH-mm-ss";
        private string folder = "";
        private bool increasing;
        public FileTable()
        {
            /*DateTime.Parse("", new IFormatProvider() {
                object GetFormat(
                    Type formatType
                ){
                    return null;
                  }
            });*/
            DataColumn col_;
            col_ = new DataColumn();
            col_.DataType = typeof(string);
            col_.ColumnName = "Name";
            col_.ReadOnly = true;
            col_.Unique = false;
            Columns.Add(col_);
            col_ = new DataColumn();
            col_.DataType = typeof(DateTime);
            col_.ColumnName = "Date";
            col_.ReadOnly = true;
            col_.Unique = false;
            Columns.Add(col_);
            col_ = new DataColumn();
            col_.DataType = typeof(long);
            col_.ColumnName = "Size";
            col_.ReadOnly = true;
            col_.Unique = false;
            Columns.Add(col_);
            col_ = new DataColumn();
            col_.DataType = typeof(string);
            col_.ColumnName = "Path";
            col_.ReadOnly = true;
            col_.Unique = true;
            Columns.Add(col_);
        }
        public void setupColumnNames()
        {
            Columns[0].Caption = "Name";
            Columns[1].Caption = "Date";
            Columns[2].Caption = "Size";
            Columns[3].Caption = "Path";
        }
        public void sortColumns(int _index)
        {
            increasing = !increasing;
            DataView d_ = DefaultView;
            if (increasing) {
                d_.Sort = Columns[_index].ColumnName + " asc";
            } else
            {
                d_.Sort = Columns[_index].ColumnName + " desc";
            }
            d_.ToTable();
        }
        public void setupFiles(MyList<FileInfo> _files, string _folder)
        {
            folder = _folder;
            Rows.Clear();
            foreach (FileInfo f in _files)
            {
                DataRow row_ = NewRow();
                row_["Name"] = f.Name;
                row_["Date"] = f.LastWriteTime;
                row_["Size"] = f.Length;
                row_["Path"] = f.FullName.Substring(_folder.Count()).Replace("\\","/");
                Rows.Add(row_);
            }
        }
    }
}
