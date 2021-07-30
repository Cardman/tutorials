using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ReflectionCore
{
    class Enums
    {
        public static void showEnums()
        {
            //CarOptions.
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
