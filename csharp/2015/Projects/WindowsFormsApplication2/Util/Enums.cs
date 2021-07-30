using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public static class Enums
    {
        public static string name(this Enum _enum)
        {
            Type t_ = _enum.GetType();
            return t_.GetEnumName(_enum);
        }

        public static S? getEnum<[EnumConstraint] S>(string _elt) where S : struct
        {
            foreach (S e in typeof(S).GetEnumValues())
            {
                if (typeof(S).GetEnumName(e).Equals(_elt))
                {
                    return e;
                }
            }
            return null;
        }
        public static int ordinal<S>(this S _elt) where S : struct
        {
            Type t_ = typeof(S);
            string name_ = t_.GetEnumName(_elt);
            int i_ = 0;
            foreach (string o in t_.GetEnumNames())
            {
                if (o.Equals(name_))
                {
                    return i_;
                }
                i_++;
            }
            return -1;
        }
    }
    [Flags]
    public enum CarOptions
    {
        // The flag for SunRoof is 0001.
        SunRoof = 0x01,
        // The flag for Spoiler is 0010.
        Spoiler = 0x02,
        // The flag for FogLights is 0100.
        FogLights = 0x04,
        // The flag for TintedWindows is 1000.
        TintedWindows = 0x08,
    }
}
