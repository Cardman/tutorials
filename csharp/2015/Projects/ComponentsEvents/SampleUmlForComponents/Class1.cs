using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleUmlForComponents
{
    public class City
    {
        private string name { get; set; }
        private List<string> usedSports { get; set; } = new List<string>();
        private string beginBuildingDate { get; set; }
        public City(string _name, string _beginBuildingDate)
        {
            name = _name;
            beginBuildingDate = _beginBuildingDate;
        }
        public string getName()
        {
            return name;
        }
        public string getBeginBuildingDate()
        {
            return beginBuildingDate;
        }
        public string getSport(int _index)
        {
            return usedSports[_index];
        }
        public void addSport(string _sport)
        {
            usedSports.Add(_sport);
        }
        public void removeSport(string _sport)
        {
            usedSports.Remove(_sport);
        }
        public int getSportsCount()
        {
            return usedSports.Count;
        }
        public override string ToString()
        {
            return name;
        }
    }
}
