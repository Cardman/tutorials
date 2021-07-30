using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleUmlForComponents
{
    public enum Hobbies
    {
        AIKIDO,
        ANGLAIS_ECRIT,
        BD,
        BELOTE,
        BILLARD,
        BLAGUES,
        CHORALE,
        CUISINE,
        DEVELOPPEMENT,
        FOOT,
        HALO,
        JEDI_KNIGHT,
        MAGIE,
        MATHS,
        MOTS_FLECHES,
        NATATION,
        POKEMON,
        PRESIDENT,
        RANDONNEES_MONTAGNARGES,
        RUGBY,
        SKI,
        STAR_WARS_GALACTIC_BATTLEGROUND,
        TAROT,
        TENNIS_DE_TABLE,
        TOUR_MAGIE,
        VELO,
        WARIO_LAND
    }
    public static class HobbiesExt
    {
        public static Hobbies randomHobby()
        {
            MyList<Hobbies> hobbies_ = new MyList<Hobbies>();
            foreach (object h in typeof(Hobbies).GetEnumValues())
            {
                hobbies_.Add((Hobbies)h);
            }
            int editedNb_ = new Random().Next() % hobbies_.Count;
            return hobbies_[editedNb_];
        }
    }
    public static class ExtensionsEnum
    {
        public static string getFullName(this Enum _o)
        {
            Type t_ = _o.GetType();
            return t_.Assembly.GetName().Name + "." + t_.Namespace + "." + t_.Name + "." + _o.ToString();
        }
    }
}
