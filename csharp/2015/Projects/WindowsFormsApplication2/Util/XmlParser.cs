using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Xml;

namespace Util
{
    public class XmlParser
    {
        private const char ASCII_32 = (char) 32;
        private const char ASCII_37 = (char)37;
        private const char ASCII_38 = (char)38;
        private const char ASCII_128 = (char)128;
        private const char ASCII_256 = (char)256;
        private const char IEXCL = (char)161;
        private const char CENT = (char)162;
        private const char POUND = (char)163;
        private const char CURREN = (char)164;
        private const char YEN = (char)165;
        private const char BRVBAR = (char)166;
        private const char SECT = (char)167;
        private const char UML = (char)168;
        private const char COPY = (char)169;
        private const char ORDF = (char)170;
        private const char LAQUO = (char)171;
        private const char NOT = (char)172;
        private const char SHY = (char)173;
        private const char REG = (char)174;
        private const char MACR = (char)175;
        private const char DEG = (char)176;
        private const char PLUSMN = (char)177;
        private const char SUP2 = (char)178;
        private const char SUP3 = (char)179;
        private const char ACUTE = (char)180;
        private const char MICRO = (char)181;
        private const char PARA = (char)182;
        private const char MIDDOT = (char)183;
        private const char CEDIL = (char)184;
        private const char SUP1 = (char)185;
        private const char ORDM = (char)186;
        private const char RAQUO = (char)187;
        private const char FRAC14 = (char)188;
        private const char FRAC12 = (char)189;
        private const char FRAC34 = (char)190;
        private const char IQUEST = (char)191;
        private const char U_A_GRAVE = (char)192;
        private const char U_A_ACUTE = (char)193;
        private const char U_A_CIRC = (char)194;
        private const char U_A_TILDE = (char)195;
        private const char U_A_UML = (char)196;
        private const char U_A_RING = (char)197;
        private const char U_AE_LIG = (char)198;
        private const char U_C_CEDIL = (char)199;
        private const char U_E_GRAVE = (char)200;
        private const char U_E_ACUTE = (char)201;
        private const char U_E_CIRC = (char)202;
        private const char U_E_UML = (char)203;
        private const char U_I_GRAVE = (char)204;
        private const char U_I_ACUTE = (char)205;
        private const char U_I_CIRC = (char)206;
        private const char U_I_UML = (char)207;
        private const char U_ETH = (char)208;
        private const char U_N_TILDE = (char)209;
        private const char U_O_GRAVE = (char)210;
        private const char U_O_ACUTE = (char)211;
        private const char U_O_CIRC = (char)212;
        private const char U_O_TILDE = (char)213;
        private const char U_O_UML = (char)214;
        private const char TIMES = (char)215;
        private const char U_O_SLASH = (char)216;
        private const char U_U_GRAVE = (char)217;
        private const char U_U_ACUTE = (char)218;
        private const char U_U_CIRC = (char)219;
        private const char U_U_UML = (char)220;
        private const char U_Y_ACUTE = (char)221;
        private const char U_THORN = (char)222;
        private const char SZLIG = (char)223;
        private const char AGRAVE = (char)224;
        private const char AACUTE = (char)225;
        private const char ACIRC = (char)226;
        private const char ATILDE = (char)227;
        private const char AUML = (char)228;
        private const char ARING = (char)229;
        private const char AELIG = (char)230;
        private const char CCEDIL = (char)231;
        private const char EGRAVE = (char)232;
        private const char EACUTE = (char)233;
        private const char ECIRC = (char)234;
        private const char EUML = (char)235;
        private const char IGRAVE = (char)236;
        private const char IACUTE = (char)237;
        private const char ICIRC = (char)238;
        private const char IUML = (char)239;
        private const char ETH = (char)240;
        private const char NTILDE = (char)241;
        private const char OGRAVE = (char)242;
        private const char OACUTE = (char)243;
        private const char OCIRC = (char)244;
        private const char OTILDE = (char)245;
        private const char OUML = (char)246;
        private const char DIVIDE = (char)247;
        private const char OSLASH = (char)248;
        private const char UGRAVE = (char)249;
        private const char UACUTE = (char)250;
        private const char UCIRC = (char)251;
        private const char UUML = (char)252;
        private const char YACUTE = (char)253;
        private const char THORN = (char)254;
        private const char YUML = (char)255;
        private const char U_OE_LIG = (char)338;
        private const char OELIG = (char)339;
        private const char U_SCARON = (char)352;
        private const char SCARON = (char)353;
        private const char U_Y_UML = (char)376;
        private const char CIRC = (char)710;
        private const char TILDE = (char)732;
        private const char ENSP = (char)8194;
        private const char EMSP = (char)8195;
        private const char THINSP = (char)8201;
        private const char ZWNJ = (char)8204;
        private const char ZWJ = (char)8205;
        private const char LRM = (char)8206;
        private const char RLM = (char)8207;
        private const char NDASH = (char)8211;
        private const char MDASH = (char)8212;
        private const char LSQUO = (char) 8216;
        private const char RSQUO = (char) 8217;
        private const char SBQUO = (char) 8218;
        private const char LDQUO = (char) 8220;
        private const char RDQUO = (char) 8221;
        private const char BDQUO = (char) 8222;
        private const char D_AGGER = (char) 8224;
        private const char DAGGER = (char) 8225;
        private const char PERMIL = (char) 8240;
        private const char LSAQUO = (char) 8249;
        private const char RSAQUO = (char) 8250;
        private const char EURO = (char) 8364;
        private const char FNOF = (char) 402;
        private const char U_A_LPHA = (char) 913;
        private const char U_B_ETA = (char) 914;
        private const char U_G_AMMA = (char) 915;
        private const char U_D_ELTA = (char) 916;
        private const char U_E_PSILON = (char) 917;
        private const char U_Z_ETA = (char) 918;
        private const char U_E_TA = (char) 919;
        private const char U_T_HETA = (char) 920;
        private const char U_I_OTA = (char) 921;
        private const char U_K_APPA = (char) 922;
        private const char U_L_AMBDA = (char) 923;
        private const char U_M_U = (char) 924;
        private const char U_N_U = (char) 925;
        private const char U_X_I = (char) 926;
        private const char U_O_MICRON = (char) 927;
        private const char U_P_I = (char) 928;
        private const char U_R_HO = (char) 929;
        private const char U_S_IGMA = (char) 931;
        private const char U_T_AU = (char) 932;
        private const char U_U_PSILON = (char) 933;
        private const char U_P_HI = (char) 934;
        private const char U_C_HI = (char) 935;
        private const char U_P_SI = (char) 936;
        private const char U_O_MEGA = (char) 937;
        private const char ALPHA = (char) 945;
        private const char BETA = (char) 946;
        private const char GAMMA = (char) 947;
        private const char DELTA = (char) 948;
        private const char EPSILON = (char) 949;
        private const char ZETA = (char) 950;
        private const char ETA = (char) 951;
        private const char THETA = (char) 952;
        private const char IOTA = (char) 953;
        private const char KAPPA = (char) 954;
        private const char LAMBDA = (char) 955;
        private const char MU = (char) 956;
        private const char NU = (char) 957;
        private const char XI = (char) 958;
        private const char OMICRON = (char) 959;
        private const char PI = (char) 960;
        private const char RHO = (char) 961;
        private const char SIGMAF = (char) 962;
        private const char SIGMA = (char) 963;
        private const char TAU = (char) 964;
        private const char UPSILON = (char) 965;
        private const char PHI = (char) 966;
        private const char CHI = (char) 967;
        private const char PSI = (char) 968;
        private const char OMEGA = (char) 969;
        private const char THETASYM = (char) 977;
        private const char UPSIH = (char) 978;
        private const char PIV = (char) 982;
        private const char BULL = (char) 8226;
        private const char HELLIP = (char) 8230;
        private const char PRIME = (char) 8242;
        private const char U_PRIME = (char) 8243;
        private const char OLINE = (char) 8254;
        private const char FRASL = (char) 8260;
        private const char WEIERP = (char) 8472;
        private const char IMAGE = (char) 8465;
        private const char REAL = (char) 8476;
        private const char TRADE = (char) 8482;
        private const char ALEFSYM = (char) 8501;
        private const char LARR = (char) 8592;
        private const char UARR = (char) 8593;
        private const char RARR = (char) 8594;
        private const char DARR = (char) 8595;
        private const char HARR = (char) 8596;
        private const char CRARR = (char) 8629;
        private const char U_LARR = (char) 8656;
        private const char U_UARR = (char) 8657;
        private const char U_RARR = (char) 8658;
        private const char U_DARR = (char) 8659;
        private const char U_HARR = (char) 8660;
        private const char FORALL = (char) 8704;
        private const char PART = (char) 8706;
        private const char EXIST = (char) 8707;
        private const char EMPTY = (char) 8709;
        private const char NABLA = (char) 8711;
        private const char ISIN = (char) 8712;
        private const char NOTIN = (char) 8713;
        private const char NI = (char) 8715;
        private const char PROD = (char) 8719;
        private const char SUM = (char) 8721;
        private const char MINUS = (char) 8722;
        private const char LOWAST = (char) 8727;
        private const char RADIC = (char) 8730;
        private const char PROP = (char) 8733;
        private const char INFIN = (char) 8734;
        private const char ANG = (char) 8736;
        private const char AND = (char) 8743;
        private const char OR = (char) 8744;
        private const char CAP = (char) 8745;
        private const char CUP = (char) 8746;
        private const char INT = (char) 8747;
        private const char THERE4 = (char) 8756;
        private const char SIM = (char) 8764;
        private const char CONG = (char) 8773;
        private const char ASYMP = (char) 8776;
        private const char NE = (char) 8800;
        private const char EQUIV = (char) 8801;
        private const char LE = (char) 8804;
        private const char GE = (char) 8805;
        private const char SUB = (char) 8834;
        private const char SUP = (char) 8835;
        private const char NSUB = (char) 8836;
        private const char SUBE = (char) 8838;
        private const char SUPE = (char) 8839;
        private const char OPLUS = (char) 8853;
        private const char OTIMES = (char) 8855;
        private const char PERP = (char)8869;
        private const char SDOT = (char)8901;
        private const char LCEIL = (char)8968;
        private const char RCEIL = (char)8969;
        private const char LFLOOR = (char)8970;
        private const char RFLOOR = (char)8971;
        private const char LANG = (char)9001;
        private const char RANG = (char)9002;
        private const char LOZ = (char)9674;
        private const char SPADES = (char)9824;
        private const char CLUBS = (char)9827;
        private const char HEARTS = (char)9829;
        private const char DIAMS = (char)9830;
        private const char NBSP = (char)160;
        private const char QUOT = (char)34;
        private const char APOS = (char)39;
        private const char LT = (char)60;
        private const char GT = (char)62;
        private const String E_U_AELIG = "&AElig;";
	private const String E_U_AGGER = "&AGGER;";
	private const String E_U_AACUTE = "&Aacute;";
	private const String E_U_ACIRC = "&Acirc;";
	private const String E_U_AGRAVE = "&Agrave;";
	private const String E_U_ALPHA = "&Alpha;";
	private const String E_U_ARING = "&Aring;";
	private const String E_U_ATILDE = "&Atilde;";
	private const String E_U_AUML = "&Auml;";
	private const String E_U_BETA = "&Beta;";
	private const String E_U_CCEDIL = "&Ccedil;";
	private const String E_U_CHI = "&Chi;";
	private const String E_U_DARR = "&DARR;";
	private const String E_U_DAGGER = "&Dagger;";
	private const String E_U_DELTA = "&Delta;";
	private const String E_U_ETH = "&ETH;";
	private const String E_U_EACUTE = "&Eacute;";
	private const String E_U_ECIRC = "&Ecirc;";
	private const String E_U_EGRAVE = "&Egrave;";
	private const String E_U_EPSILON = "&Epsilon;";
	private const String E_U_ETA = "&Eta;";
	private const String E_U_EUML = "&Euml;";
	private const String E_U_GAMMA = "&Gamma;";
	private const String E_U_HARR = "&HARR;";
	private const String E_U_IACUTE = "&Iacute;";
	private const String E_U_ICIRC = "&Icirc;";
	private const String E_U_IGRAVE = "&Igrave;";
	private const String E_U_IOTA = "&Iota;";
	private const String E_U_IUML = "&Iuml;";
	private const String E_U_KAPPA = "&Kappa;";
	private const String E_U_LARR = "&LARR;";
	private const String E_U_LAMBDA = "&Lambda;";
	private const String E_U_MU = "&Mu;";
	private const String E_U_NTILDE = "&Ntilde;";
	private const String E_U_NU = "&Nu;";
	private const String E_U_OELIG = "&OElig;";
	private const String E_U_OACUTE = "&Oacute;";
	private const String E_U_OCIRC = "&Ocirc;";
	private const String E_U_OGRAVE = "&Ograve;";
	private const String E_U_OMEGA = "&Omega;";
	private const String E_U_OMICRON = "&Omicron;";
	private const String E_U_OSLASH = "&Oslash;";
	private const String E_U_OTILDE = "&Otilde;";
	private const String E_U_OUML = "&Ouml;";
	private const String E_U_PRIME = "&PRIME;";
	private const String E_U_PHI = "&Phi;";
	private const String E_U_PI = "&Pi;";
	private const String E_P_RIME = "&Prime;";
	private const String E_U_PSI = "&Psi;";
	private const String E_U_RARR = "&RARR;";
	private const String E_U_RHO = "&Rho;";
	private const String E_U_SCARON = "&SCARON;";
	private const String E_S_CARON = "&Scaron;";
	private const String E_U_SIGMA = "&Sigma;";
	private const String E_U_THORN = "&THORN;";
	private const String E_U_TAU = "&Tau;";
	private const String E_U_THETA = "&Theta;";
	private const String E_U_UARR = "&UARR;";
	private const String E_U_UACUTE = "&Uacute;";
	private const String E_U_UCIRC = "&Ucirc;";
	private const String E_U_UGRAVE = "&Ugrave;";
	private const String E_U_UPSILON = "&Upsilon;";
	private const String E_U_UUML = "&Uuml;";
	private const String E_U_XI = "&Xi;";
	private const String E_U_YACUTE = "&Yacute;";
	private const String E_U_YUML = "&Yuml;";
	private const String E_U_ZETA = "&Zeta;";
	private const String E_AACUTE = "&aacute;";
	private const String E_ACIRC = "&acirc;";
	private const String E_ACUTE = "&acute;";
	private const String E_AELIG = "&aelig;";
	private const String E_AGRAVE = "&agrave;";
	private const String E_ALEFSYM = "&alefsym;";
	private const String E_ALPHA = "&alpha;";
	private const String E_AMP = "&amp;";
	private const String E_AND = "&and;";
	private const String E_ANG = "&ang;";
	private const String E_APOS = "&apos;";
	private const String E_ARING = "&aring;";
	private const String E_ASYMP = "&asymp;";
	private const String E_ATILDE = "&atilde;";
	private const String E_AUML = "&auml;";
	private const String E_BDQUO = "&bdquo;";
	private const String E_BETA = "&beta;";
	private const String E_BRVBAR = "&brvbar;";
	private const String E_BULL = "&bull;";
	private const String E_CAP = "&cap;";
	private const String E_CCEDIL = "&ccedil;";
	private const String E_CEDIL = "&cedil;";
	private const String E_CENT = "&cent;";
	private const String E_CHI = "&chi;";
	private const String E_CIRC = "&circ;";
	private const String E_CLUBS = "&clubs;";
	private const String E_CONG = "&cong;";
	private const String E_COPY = "&copy;";
	private const String E_CRARR = "&crarr;";
	private const String E_CUP = "&cup;";
	private const String E_CURREN = "&curren;";
	private const String E_D_ARR = "&dArr;";
	private const String E_DAGGER = "&dagger;";
	private const String E_DARR = "&darr;";
	private const String E_DEG = "&deg;";
	private const String E_DELTA = "&delta;";
	private const String E_DIAMS = "&diams;";
	private const String E_DIVIDE = "&divide;";
	private const String E_EACUTE = "&eacute;";
	private const String E_ECIRC = "&ecirc;";
	private const String E_EGRAVE = "&egrave;";
	private const String E_EMPTY = "&empty;";
	private const String E_EMSP = "&emsp;";
	private const String E_ENSP = "&ensp;";
	private const String E_EPSILON = "&epsilon;";
	private const String E_EQUIV = "&equiv;";
	private const String E_ETA = "&eta;";
	private const String E_ETH = "&eth;";
	private const String E_EUML = "&euml;";
	private const String E_EURO = "&euro;";
	private const String E_EXIST = "&exist;";
	private const String E_FNOF = "&fnof;";
	private const String E_FORALL = "&forall;";
	private const String E_FRAC12 = "&frac12;";
	private const String E_FRAC14 = "&frac14;";
	private const String E_FRAC34 = "&frac34;";
	private const String E_FRASL = "&frasl;";
	private const String E_GAMMA = "&gamma;";
	private const String E_GE = "&ge;";
	private const String E_GT = "&gt;";
	private const String E_H_ARR = "&hArr;";
	private const String E_HARR = "&harr;";
	private const String E_HEARTS = "&hearts;";
	private const String E_HELLIP = "&hellip;";
	private const String E_IACUTE = "&iacute;";
	private const String E_ICIRC = "&icirc;";
	private const String E_IEXCL = "&iexcl;";
	private const String E_IGRAVE = "&igrave;";
	private const String E_IMAGE = "&image;";
	private const String E_INFIN = "&infin;";
	private const String E_INT = "&int;";
	private const String E_IOTA = "&iota;";
	private const String E_IQUEST = "&iquest;";
	private const String E_ISIN = "&isin;";
	private const String E_IUML = "&iuml;";
	private const String E_KAPPA = "&kappa;";
	private const String E_L_ARR = "&lArr;";
	private const String E_LAMBDA = "&lambda;";
	private const String E_LANG = "&lang;";
	private const String E_LAQUO = "&laquo;";
	private const String E_LARR = "&larr;";
	private const String E_LCEIL = "&lceil;";
	private const String E_LDQUO = "&ldquo;";
	private const String E_LE = "&le;";
	private const String E_LFLOOR = "&lfloor;";
	private const String E_LOWAST = "&lowast;";
	private const String E_LOZ = "&loz;";
	private const String E_LRM = "&lrm;";
	private const String E_LSAQUO = "&lsaquo;";
	private const String E_LSQUO = "&lsquo;";
	private const String E_LT = "&lt;";
	private const String E_MACR = "&macr;";
	private const String E_MDASH = "&mdash;";
	private const String E_MICRO = "&micro;";
	private const String E_MIDDOT = "&middot;";
	private const String E_MINUS = "&minus;";
	private const String E_MU = "&mu;";
	private const String E_NABLA = "&nabla;";
	private const String E_NBSP = "&nbsp;";
	private const String E_NDASH = "&ndash;";
	private const String E_NE = "&ne;";
	private const String E_NI = "&ni;";
	private const String E_NOT = "&not;";
	private const String E_NOTIN = "&notin;";
	private const String E_NSUB = "&nsub;";
	private const String E_NTILDE = "&ntilde;";
	private const String E_NU = "&nu;";
	private const String E_OACUTE = "&oacute;";
	private const String E_OCIRC = "&ocirc;";
	private const String E_OELIG = "&oelig;";
	private const String E_OGRAVE = "&ograve;";
	private const String E_OLINE = "&oline;";
	private const String E_OMEGA = "&omega;";
	private const String E_OMICRON = "&omicron;";
	private const String E_OPLUS = "&oplus;";
	private const String E_OR = "&or;";
	private const String E_ORDF = "&ordf;";
	private const String E_ORDM = "&ordm;";
	private const String E_OSLASH = "&oslash;";
	private const String E_OTILDE = "&otilde;";
	private const String E_OTIMES = "&otimes;";
	private const String E_OUML = "&ouml;";
	private const String E_PARA = "&para;";
	private const String E_PART = "&part;";
	private const String E_PERMIL = "&permil;";
	private const String E_PERP = "&perp;";
	private const String E_PHI = "&phi;";
	private const String E_PI = "&pi;";
	private const String E_PIV = "&piv;";
	private const String E_PLUSMN = "&plusmn;";
	private const String E_POUND = "&pound;";
	private const String E_PRIME = "&prime;";
	private const String E_PROD = "&prod;";
	private const String E_PROP = "&prop;";
	private const String E_PSI = "&psi;";
	private const String E_QUOT = "&quot;";
	private const String E_R_ARR = "&rArr;";
	private const String E_RADIC = "&radic;";
	private const String E_RANG = "&rang;";
	private const String E_RAQUO = "&raquo;";
	private const String E_RARR = "&rarr;";
	private const String E_RCEIL = "&rceil;";
	private const String E_RDQUO = "&rdquo;";
	private const String E_REAL = "&real;";
	private const String E_REG = "&reg;";
	private const String E_RFLOOR = "&rfloor;";
	private const String E_RHO = "&rho;";
	private const String E_RLM = "&rlm;";
	private const String E_RSAQUO = "&rsaquo;";
	private const String E_RSQUO = "&rsquo;";
	private const String E_SBQUO = "&sbquo;";
	private const String E_SCARON = "&scaron;";
	private const String E_SDOT = "&sdot;";
	private const String E_SECT = "&sect;";
	private const String E_SHY = "&shy;";
	private const String E_SIGMA = "&sigma;";
	private const String E_SIGMAF = "&sigmaf;";
	private const String E_SIM = "&sim;";
	private const String E_SPADES = "&spades;";
	private const String E_SUB = "&sub;";
	private const String E_SUBE = "&sube;";
	private const String E_SUM = "&sum;";
	private const String E_SUP1 = "&sup1;";
	private const String E_SUP2 = "&sup2;";
	private const String E_SUP3 = "&sup3;";
	private const String E_SUP = "&sup;";
	private const String E_SUPE = "&supe;";
	private const String E_SZLIG = "&szlig;";
	private const String E_TAU = "&tau;";
	private const String E_THERE4 = "&there4;";
	private const String E_THETA = "&theta;";
	private const String E_THETASYM = "&thetasym;";
	private const String E_THINSP = "&thinsp;";
	private const String E_THORN = "&thorn;";
	private const String E_TILDE = "&tilde;";
	private const String E_TIMES = "&times;";
	private const String E_TRADE = "&trade;";
	private const String E_U_ARR = "&uArr;";
	private const String E_UACUTE = "&uacute;";
	private const String E_UARR = "&uarr;";
	private const String E_UCIRC = "&ucirc;";
	private const String E_UGRAVE = "&ugrave;";
	private const String E_UML = "&uml;";
	private const String E_UPSIH = "&upsih;";
	private const String E_UPSILON = "&upsilon;";
	private const String E_UUML = "&uuml;";
	private const String E_WEIERP = "&weierp;";
	private const String E_XI = "&xi;";
	private const String E_YACUTE = "&yacute;";
	private const String E_YEN = "&yen;";
	private const String E_YUML = "&yuml;";
	private const String E_ZETA = "&zeta;";
	private const String E_ZWJ = "&zwj;";
	private const String E_ZWNJ = "&zwnj;";

	private const String ENCODE = "&#{0};";

	private const String INDENT_KEY = "{http://xml.apache.org/xslt}indent-amount";

	private const String ALL = "*";

	private const String EMPTY_STRING = "";

	private const char ENCODED = '&';

        private const String PER_CENT = "%";
	private const String ENCODE_PER_CENT = "%25";
	private const String SPACE = " ";
	private const String ENCODE_SPACE = "+";

	private const String YES = "yes";
	private const String XML = "xml";

	private const String NO_DIGITS = "[^0-9]+";

	private const int NB_INDENT = 4;
        private static Map<String, String> _specialChars_ = new Map<String, String>();

        private static Map<String, String> _encodedChars_ = new Map<String, String>();

        private XmlParser()
        {
        }

        public static XmlElement getElementById(XmlDocument _doc, String _attr, String _id)
        {
            XmlElement element_ = null;
            XmlNodeList all_ = _doc.GetElementsByTagName(ALL);
            int lengthAll_ = all_.Count;
            for (int i = List.FIRST_INDEX; i < lengthAll_; i++)
            {
                XmlNode n_ = all_.Item(i);
                if (!(n_ is XmlElement)) {
                    continue;
                }
                element_ = (XmlElement)n_;
                if (element_.GetAttribute(_attr).Equals(_id))
                {
                    break;
                }
            }
		    return element_;
	    }

        public static MyList<XmlNode> childrenNodes(XmlNode _noeud)
        {
            MyList<XmlNode> noeuds_ = new MyList<XmlNode>();
            XmlNodeList noeudsListe_ = _noeud.ChildNodes;
            int nbNoeuds_ = noeudsListe_.Count;
            for (int i = List.FIRST_INDEX; i < nbNoeuds_; i++)
            {
                noeuds_.Add(noeudsListe_.Item(i));
            }
            return noeuds_;
        }
        public static XmlDocument parseSax(String _xml)
        {
            XmlDocument doc_ = new XmlDocument();
            doc_.LoadXml(_xml);
            return doc_;
//		DocumentBuilderFactory dbFactory_ = DocumentBuilderFactory.newInstance();
//		DocumentBuilder dBuilder_ = dbFactory_.newDocumentBuilder();
//		InputSource is_ = new InputSource();
////		is_.setEncoding(StandardCharsets.UTF_8.name());
//		is_.setEncoding(StandardCharsets.ISO_8859_1.name());
//		is_.setCharacterStream(new StringReader(_xml));
//		return dBuilder_.parse(is_);
	}
        public static string toXml(XmlNode _myxml)
        {
            //_myxml.Normalize();
            StringWriter sw = new StringWriter();
            XmlTextWriter tx = new XmlTextWriter(sw);
            _myxml.WriteTo(tx);
            return sw.ToString().Replace(" />","/>");
        }
        public static XmlElement documentElement(XmlDocument _doc)
        {
            XmlElement element_ = _doc.DocumentElement;
            element_.Normalize();
            return element_;
        }
        public static XmlDocument parseSaxHtml(String _xml)
        {
		    return parseSax(encodeHtml(_xml));
        }
        public static String toHtml(XmlDocument _doc)
        {
            XmlElement root_ = _doc.DocumentElement;
            return toXml(root_);
        }
        public static String transformSpecialChars(String _htmlText)
        {
            Map<String, String> map_ = getMapSpecialChars();
            int length_ = _htmlText.Length;
            StringBuilder str_ = new StringBuilder();
            int i_ = 0;
            int iBegin_ = 0;
            while (i_ < length_)
            {
                char ch_ = _htmlText.ElementAt(i_);
                if (ch_ != ENCODED)
                {
                    str_.Append(ch_);
                    i_++;
                    continue;
                }
                iBegin_ = i_;
                while (true)
                {
                    i_++;
                    if (i_ >= length_)
                    {
                        break;
                    }
                    ch_ = _htmlText.ElementAt(i_);
                    if (!char.IsLetterOrDigit(ch_))
                    {
                        break;
                    }
                }
                if (i_ >= length_)
                {
                    str_.Append(_htmlText.Substring(iBegin_));
                    break;
                }
                bool add_ = false;
                foreach (Entry<String, String> k in map_.entryList())
                {
                    bool equals_ = true;
                    int j_ = 0;
                    String key_ = k.getKey();
                    for (int i = iBegin_; i <= i_; i++)
                    {
                        if (_htmlText.ElementAt(i) != key_.ElementAt(j_))
                        {
                            equals_ = false;
                            break;
                        }
                        j_++;
                    }
                    if (equals_)
                    {
                        Regex reg_ = new Regex(NO_DIGITS);
                        String repl_ = reg_.Replace(k.getValue(), EMPTY_STRING);
                        int ascii_ = int.Parse(repl_);
                        char char_ = (char)ascii_;
                        str_.Append(char_);
                        i_++;
                        add_ = true;
                        break;
                    }
                }
                if (!add_)
                {
                    str_.Append(_htmlText.Substring(iBegin_, i_ + 1 - iBegin_));
                    i_++;
                }
            }
            return str_.ToString();
        }
        public static String encodeHtml(String _htmlText)
        {
            Map<String, String> map_ = getMapEncodedChars();
            int length_ = _htmlText.Length;
            StringBuilder str_ = new StringBuilder();
            int i_ = 0;
            int iBegin_ = 0;
            while (i_ < length_)
            {
                char ch_ = _htmlText.ElementAt(i_);
                if (ch_ != ENCODED)
                {
                    str_.Append(ch_);
                    i_++;
                    continue;
                }
                iBegin_ = i_;
                while (true)
                {
                    i_++;
                    if (i_ >= length_)
                    {
                        break;
                    }
                    ch_ = _htmlText.ElementAt(i_);
                    if (!char.IsLetterOrDigit(ch_))
                    {
                        break;
                    }
                }
                if (i_ >= length_)
                {
                    str_.Append(_htmlText.Substring(iBegin_));
                    break;
                }
                bool add_ = false;
                foreach (Entry<String, String> k in map_.entryList())
                {
                    bool equals_ = true;
                    int j_ = 0;
                    String key_ = k.getKey();
                    for (int i = iBegin_; i <= i_; i++)
                    {
                        if (_htmlText.ElementAt(i) != key_.ElementAt(j_))
                        {
                            equals_ = false;
                            break;
                        }
                        j_++;
                    }
                    if (equals_)
                    {
                        str_.Append(k.getValue());
                        i_++;
                        add_ = true;
                        break;
                    }
                }
                if (!add_)
                {
                    str_.Append(_htmlText.Substring(iBegin_, i_ + 1 - iBegin_));
                    i_++;
                }
            }
            return str_.ToString();
        }
        public static String encodeUrlString(String _urlString, bool _encodeAccent)
        {
            Map<String, String> replacedStrings_ = new Map<String, String>();
            replacedStrings_.put(ENCODE_SPACE, SPACE);
            for (short c = (short) ASCII_32; c < ASCII_37; c++)
            {
                replacedStrings_.put(PER_CENT + c.ToString("X").ToUpper(), char.ToString((char)c));
            }
            if (_encodeAccent)
            {
                for (short c = (short)ASCII_38; c < ASCII_256; c++)
                {
                    replacedStrings_.put(PER_CENT + c.ToString("X").ToUpper(), char.ToString((char)c));
                }
                replacedStrings_.put(ENCODE_PER_CENT, PER_CENT);
                return StringList.formatBasic(_urlString, replacedStrings_, false);
            }
            for (short c = (short)ASCII_38; c < ASCII_128; c++)
            {
                replacedStrings_.put(PER_CENT + c.ToString("X").ToUpper(), char.ToString((char)c));
            }
            replacedStrings_.put(ENCODE_PER_CENT, PER_CENT);
            return StringList.formatBasic(_urlString, replacedStrings_, true);
        }
        private static Map<String,String> getMapSpecialChars()
        {
            if (_specialChars_.isEmpty())
            {
                _specialChars_.put(E_NBSP, String.Format(ENCODE, (int)NBSP));
                _specialChars_.put(E_IEXCL, String.Format(ENCODE, (int)IEXCL));
                _specialChars_.put(E_CENT, String.Format(ENCODE, (int)CENT));
                _specialChars_.put(E_POUND, String.Format(ENCODE, (int)POUND));
                _specialChars_.put(E_CURREN, String.Format(ENCODE, (int)CURREN));
                _specialChars_.put(E_YEN, String.Format(ENCODE, (int)YEN));
                _specialChars_.put(E_BRVBAR, String.Format(ENCODE, (int)BRVBAR));
                _specialChars_.put(E_SECT, String.Format(ENCODE, (int)SECT));
                _specialChars_.put(E_UML, String.Format(ENCODE, (int)UML));
                _specialChars_.put(E_COPY, String.Format(ENCODE, (int)COPY));
                _specialChars_.put(E_ORDF, String.Format(ENCODE, (int)ORDF));
                _specialChars_.put(E_LAQUO, String.Format(ENCODE, (int)LAQUO));
                _specialChars_.put(E_NOT, String.Format(ENCODE, (int)NOT));
                _specialChars_.put(E_SHY, String.Format(ENCODE, (int)SHY));
                _specialChars_.put(E_REG, String.Format(ENCODE, (int)REG));
                _specialChars_.put(E_MACR, String.Format(ENCODE, (int)MACR));
                _specialChars_.put(E_DEG, String.Format(ENCODE, (int)DEG));
                _specialChars_.put(E_PLUSMN, String.Format(ENCODE, (int)PLUSMN));
                _specialChars_.put(E_SUP2, String.Format(ENCODE, (int)SUP2));
                _specialChars_.put(E_SUP3, String.Format(ENCODE, (int)SUP3));
                _specialChars_.put(E_ACUTE, String.Format(ENCODE, (int)ACUTE));
                _specialChars_.put(E_MICRO, String.Format(ENCODE, (int)MICRO));
                _specialChars_.put(E_PARA, String.Format(ENCODE, (int)PARA));
                _specialChars_.put(E_MIDDOT, String.Format(ENCODE, (int)MIDDOT));
                _specialChars_.put(E_CEDIL, String.Format(ENCODE, (int)CEDIL));
                _specialChars_.put(E_SUP1, String.Format(ENCODE, (int)SUP1));
                _specialChars_.put(E_ORDM, String.Format(ENCODE, (int)ORDM));
                _specialChars_.put(E_RAQUO, String.Format(ENCODE, (int)RAQUO));
                _specialChars_.put(E_FRAC14, String.Format(ENCODE, (int)FRAC14));
                _specialChars_.put(E_FRAC12, String.Format(ENCODE, (int)FRAC12));
                _specialChars_.put(E_FRAC34, String.Format(ENCODE, (int)FRAC34));
                _specialChars_.put(E_IQUEST, String.Format(ENCODE, (int)IQUEST));
                _specialChars_.put(E_U_AGRAVE, String.Format(ENCODE, (int)U_A_GRAVE));
                _specialChars_.put(E_U_AACUTE, String.Format(ENCODE, (int)U_A_ACUTE));
                _specialChars_.put(E_U_ACIRC, String.Format(ENCODE, (int)U_A_CIRC));
                _specialChars_.put(E_U_ATILDE, String.Format(ENCODE, (int)U_A_TILDE));
                _specialChars_.put(E_U_AUML, String.Format(ENCODE, (int)U_A_UML));
                _specialChars_.put(E_U_ARING, String.Format(ENCODE, (int)U_A_RING));
                _specialChars_.put(E_U_AELIG, String.Format(ENCODE, (int)U_AE_LIG));
                _specialChars_.put(E_U_CCEDIL, String.Format(ENCODE, (int)U_C_CEDIL));
                _specialChars_.put(E_U_EGRAVE, String.Format(ENCODE, (int)U_E_GRAVE));
                _specialChars_.put(E_U_EACUTE, String.Format(ENCODE, (int)U_E_ACUTE));
                _specialChars_.put(E_U_ECIRC, String.Format(ENCODE, (int)U_E_CIRC));
                _specialChars_.put(E_U_EUML, String.Format(ENCODE, (int)U_E_UML));
                _specialChars_.put(E_U_IGRAVE, String.Format(ENCODE, (int)U_I_GRAVE));
                _specialChars_.put(E_U_IACUTE, String.Format(ENCODE, (int)U_I_ACUTE));
                _specialChars_.put(E_U_ICIRC, String.Format(ENCODE, (int)U_I_CIRC));
                _specialChars_.put(E_U_IUML, String.Format(ENCODE, (int)U_I_UML));
                _specialChars_.put(E_U_ETH, String.Format(ENCODE, (int)U_ETH));
                _specialChars_.put(E_U_NTILDE, String.Format(ENCODE, (int)U_N_TILDE));
                _specialChars_.put(E_U_OGRAVE, String.Format(ENCODE, (int)U_O_GRAVE));
                _specialChars_.put(E_U_OACUTE, String.Format(ENCODE, (int)U_O_ACUTE));
                _specialChars_.put(E_U_OCIRC, String.Format(ENCODE, (int)U_O_CIRC));
                _specialChars_.put(E_U_OTILDE, String.Format(ENCODE, (int)U_O_TILDE));
                _specialChars_.put(E_U_OUML, String.Format(ENCODE, (int)U_O_UML));
                _specialChars_.put(E_TIMES, String.Format(ENCODE, (int)TIMES));
                _specialChars_.put(E_U_OSLASH, String.Format(ENCODE, (int)U_O_SLASH));
                _specialChars_.put(E_U_UGRAVE, String.Format(ENCODE, (int)U_U_GRAVE));
                _specialChars_.put(E_U_UACUTE, String.Format(ENCODE, (int)U_U_ACUTE));
                _specialChars_.put(E_U_UCIRC, String.Format(ENCODE, (int)U_U_CIRC));
                _specialChars_.put(E_U_UUML, String.Format(ENCODE, (int)U_U_UML));
                _specialChars_.put(E_U_YACUTE, String.Format(ENCODE, (int)U_Y_ACUTE));
                _specialChars_.put(E_U_THORN, String.Format(ENCODE, (int)U_THORN));
                _specialChars_.put(E_SZLIG, String.Format(ENCODE, (int)SZLIG));
                _specialChars_.put(E_AGRAVE, String.Format(ENCODE, (int)AGRAVE));
                _specialChars_.put(E_AACUTE, String.Format(ENCODE, (int)AACUTE));
                _specialChars_.put(E_ACIRC, String.Format(ENCODE, (int)ACIRC));
                _specialChars_.put(E_ATILDE, String.Format(ENCODE, (int)ATILDE));
                _specialChars_.put(E_AUML, String.Format(ENCODE, (int)AUML));
                _specialChars_.put(E_ARING, String.Format(ENCODE, (int)ARING));
                _specialChars_.put(E_AELIG, String.Format(ENCODE, (int)AELIG));
                _specialChars_.put(E_CCEDIL, String.Format(ENCODE, (int)CCEDIL));
                _specialChars_.put(E_EGRAVE, String.Format(ENCODE, (int)EGRAVE));
                _specialChars_.put(E_EACUTE, String.Format(ENCODE, (int)EACUTE));
                _specialChars_.put(E_ECIRC, String.Format(ENCODE, (int)ECIRC));
                _specialChars_.put(E_EUML, String.Format(ENCODE, (int)EUML));
                _specialChars_.put(E_IGRAVE, String.Format(ENCODE, (int)IGRAVE));
                _specialChars_.put(E_IACUTE, String.Format(ENCODE, (int)IACUTE));
                _specialChars_.put(E_ICIRC, String.Format(ENCODE, (int)ICIRC));
                _specialChars_.put(E_IUML, String.Format(ENCODE, (int)IUML));
                _specialChars_.put(E_ETH, String.Format(ENCODE, (int)ETH));
                _specialChars_.put(E_NTILDE, String.Format(ENCODE, (int)NTILDE));
                _specialChars_.put(E_OGRAVE, String.Format(ENCODE, (int)OGRAVE));
                _specialChars_.put(E_OACUTE, String.Format(ENCODE, (int)OACUTE));
                _specialChars_.put(E_OCIRC, String.Format(ENCODE, (int)OCIRC));
                _specialChars_.put(E_OTILDE, String.Format(ENCODE, (int)OTILDE));
                _specialChars_.put(E_OUML, String.Format(ENCODE, (int)OUML));
                _specialChars_.put(E_DIVIDE, String.Format(ENCODE, (int)DIVIDE));
                _specialChars_.put(E_OSLASH, String.Format(ENCODE, (int)OSLASH));
                _specialChars_.put(E_UGRAVE, String.Format(ENCODE, (int)UGRAVE));
                _specialChars_.put(E_UACUTE, String.Format(ENCODE, (int)UACUTE));
                _specialChars_.put(E_UCIRC, String.Format(ENCODE, (int)UCIRC));
                _specialChars_.put(E_UUML, String.Format(ENCODE, (int)UUML));
                _specialChars_.put(E_YACUTE, String.Format(ENCODE, (int)YACUTE));
                _specialChars_.put(E_THORN, String.Format(ENCODE, (int)THORN));
                _specialChars_.put(E_YUML, String.Format(ENCODE, (int)YUML));
                _specialChars_.put(E_QUOT, String.Format(ENCODE, (int)QUOT));
                //		_specialChars_.put(E_LT, String.Format(ENCODE, (int)LT));
                //		_specialChars_.put(E_GT, String.Format(ENCODE, (int)GT));
                _specialChars_.put(E_APOS, String.Format(ENCODE, (int)APOS));
                _specialChars_.put(E_U_OELIG, String.Format(ENCODE, (int)U_OE_LIG));
                _specialChars_.put(E_OELIG, String.Format(ENCODE, (int)OELIG));
                _specialChars_.put(E_S_CARON, String.Format(ENCODE, (int)U_SCARON));
                _specialChars_.put(E_SCARON, String.Format(ENCODE, (int)SCARON));
                _specialChars_.put(E_U_YUML, String.Format(ENCODE, (int)U_Y_UML));
                _specialChars_.put(E_CIRC, String.Format(ENCODE, (int)CIRC));
                _specialChars_.put(E_TILDE, String.Format(ENCODE, (int)TILDE));
                _specialChars_.put(E_ENSP, String.Format(ENCODE, (int)ENSP));
                _specialChars_.put(E_EMSP, String.Format(ENCODE, (int)EMSP));
                _specialChars_.put(E_THINSP, String.Format(ENCODE, (int)THINSP));
                _specialChars_.put(E_ZWNJ, String.Format(ENCODE, (int)ZWNJ));
                _specialChars_.put(E_ZWJ, String.Format(ENCODE, (int)ZWJ));
                _specialChars_.put(E_LRM, String.Format(ENCODE, (int)LRM));
                _specialChars_.put(E_RLM, String.Format(ENCODE, (int)RLM));
                _specialChars_.put(E_NDASH, String.Format(ENCODE, (int)NDASH));
                _specialChars_.put(E_MDASH, String.Format(ENCODE, (int)MDASH));
                _specialChars_.put(E_LSQUO, String.Format(ENCODE, (int)LSQUO));
                _specialChars_.put(E_RSQUO, String.Format(ENCODE, (int)RSQUO));
                _specialChars_.put(E_SBQUO, String.Format(ENCODE, (int)SBQUO));
                _specialChars_.put(E_LDQUO, String.Format(ENCODE, (int)LDQUO));
                _specialChars_.put(E_RDQUO, String.Format(ENCODE, (int)RDQUO));
                _specialChars_.put(E_BDQUO, String.Format(ENCODE, (int)BDQUO));
                _specialChars_.put(E_DAGGER, String.Format(ENCODE, (int)D_AGGER));
                _specialChars_.put(E_U_DAGGER, String.Format(ENCODE, (int)DAGGER));
                _specialChars_.put(E_PERMIL, String.Format(ENCODE, (int)PERMIL));
                _specialChars_.put(E_LSAQUO, String.Format(ENCODE, (int)LSAQUO));
                _specialChars_.put(E_RSAQUO, String.Format(ENCODE, (int)RSAQUO));
                _specialChars_.put(E_EURO, String.Format(ENCODE, (int)EURO));
                _specialChars_.put(E_FNOF, String.Format(ENCODE, (int)FNOF));
                _specialChars_.put(E_U_ALPHA, String.Format(ENCODE, (int)U_A_LPHA));
                _specialChars_.put(E_U_BETA, String.Format(ENCODE, (int)U_B_ETA));
                _specialChars_.put(E_U_GAMMA, String.Format(ENCODE, (int)U_G_AMMA));
                _specialChars_.put(E_U_DELTA, String.Format(ENCODE, (int)U_D_ELTA));
                _specialChars_.put(E_U_EPSILON, String.Format(ENCODE, (int)U_E_PSILON));
                _specialChars_.put(E_U_ZETA, String.Format(ENCODE, (int)U_Z_ETA));
                _specialChars_.put(E_U_ETA, String.Format(ENCODE, (int)U_E_TA));
                _specialChars_.put(E_U_THETA, String.Format(ENCODE, (int)U_T_HETA));
                _specialChars_.put(E_U_IOTA, String.Format(ENCODE, (int)U_I_OTA));
                _specialChars_.put(E_U_KAPPA, String.Format(ENCODE, (int)U_K_APPA));
                _specialChars_.put(E_U_LAMBDA, String.Format(ENCODE, (int)U_L_AMBDA));
                _specialChars_.put(E_U_MU, String.Format(ENCODE, (int)U_M_U));
                _specialChars_.put(E_U_NU, String.Format(ENCODE, (int)U_N_U));
                _specialChars_.put(E_U_XI, String.Format(ENCODE, (int)U_X_I));
                _specialChars_.put(E_U_OMICRON, String.Format(ENCODE, (int)U_O_MICRON));
                _specialChars_.put(E_U_PI, String.Format(ENCODE, (int)U_P_I));
                _specialChars_.put(E_U_RHO, String.Format(ENCODE, (int)U_R_HO));
                _specialChars_.put(E_U_SIGMA, String.Format(ENCODE, (int)U_S_IGMA));
                _specialChars_.put(E_U_TAU, String.Format(ENCODE, (int)U_T_AU));
                _specialChars_.put(E_U_UPSILON, String.Format(ENCODE, (int)U_U_PSILON));
                _specialChars_.put(E_U_PHI, String.Format(ENCODE, (int)U_P_HI));
                _specialChars_.put(E_U_CHI, String.Format(ENCODE, (int)U_C_HI));
                _specialChars_.put(E_U_PSI, String.Format(ENCODE, (int)U_P_SI));
                _specialChars_.put(E_U_OMEGA, String.Format(ENCODE, (int)U_O_MEGA));
                _specialChars_.put(E_ALPHA, String.Format(ENCODE, (int)ALPHA));
                _specialChars_.put(E_BETA, String.Format(ENCODE, (int)BETA));
                _specialChars_.put(E_GAMMA, String.Format(ENCODE, (int)GAMMA));
                _specialChars_.put(E_DELTA, String.Format(ENCODE, (int)DELTA));
                _specialChars_.put(E_EPSILON, String.Format(ENCODE, (int)EPSILON));
                _specialChars_.put(E_ZETA, String.Format(ENCODE, (int)ZETA));
                _specialChars_.put(E_ETA, String.Format(ENCODE, (int)ETA));
                _specialChars_.put(E_THETA, String.Format(ENCODE, (int)THETA));
                _specialChars_.put(E_IOTA, String.Format(ENCODE, (int)IOTA));
                _specialChars_.put(E_KAPPA, String.Format(ENCODE, (int)KAPPA));
                _specialChars_.put(E_LAMBDA, String.Format(ENCODE, (int)LAMBDA));
                _specialChars_.put(E_MU, String.Format(ENCODE, (int)MU));
                _specialChars_.put(E_NU, String.Format(ENCODE, (int)NU));
                _specialChars_.put(E_XI, String.Format(ENCODE, (int)XI));
                _specialChars_.put(E_OMICRON, String.Format(ENCODE, (int)OMICRON));
                _specialChars_.put(E_PI, String.Format(ENCODE, (int)PI));
                _specialChars_.put(E_RHO, String.Format(ENCODE, (int)RHO));
                _specialChars_.put(E_SIGMAF, String.Format(ENCODE, (int)SIGMAF));
                _specialChars_.put(E_SIGMA, String.Format(ENCODE, (int)SIGMA));
                _specialChars_.put(E_TAU, String.Format(ENCODE, (int)TAU));
                _specialChars_.put(E_UPSILON, String.Format(ENCODE, (int)UPSILON));
                _specialChars_.put(E_PHI, String.Format(ENCODE, (int)PHI));
                _specialChars_.put(E_CHI, String.Format(ENCODE, (int)CHI));
                _specialChars_.put(E_PSI, String.Format(ENCODE, (int)PSI));
                _specialChars_.put(E_OMEGA, String.Format(ENCODE, (int)OMEGA));
                _specialChars_.put(E_THETASYM, String.Format(ENCODE, (int)THETASYM));
                _specialChars_.put(E_UPSIH, String.Format(ENCODE, (int)UPSIH));
                _specialChars_.put(E_PIV, String.Format(ENCODE, (int)PIV));
                _specialChars_.put(E_BULL, String.Format(ENCODE, (int)BULL));
                _specialChars_.put(E_HELLIP, String.Format(ENCODE, (int)HELLIP));
                _specialChars_.put(E_PRIME, String.Format(ENCODE, (int)PRIME));
                _specialChars_.put(E_P_RIME, String.Format(ENCODE, (int)U_PRIME));
                _specialChars_.put(E_OLINE, String.Format(ENCODE, (int)OLINE));
                _specialChars_.put(E_FRASL, String.Format(ENCODE, (int)FRASL));
                _specialChars_.put(E_WEIERP, String.Format(ENCODE, (int)WEIERP));
                _specialChars_.put(E_IMAGE, String.Format(ENCODE, (int)IMAGE));
                _specialChars_.put(E_REAL, String.Format(ENCODE, (int)REAL));
                _specialChars_.put(E_TRADE, String.Format(ENCODE, (int)TRADE));
                _specialChars_.put(E_ALEFSYM, String.Format(ENCODE, (int)ALEFSYM));
                _specialChars_.put(E_LARR, String.Format(ENCODE, (int)LARR));
                _specialChars_.put(E_UARR, String.Format(ENCODE, (int)UARR));
                _specialChars_.put(E_RARR, String.Format(ENCODE, (int)RARR));
                _specialChars_.put(E_DARR, String.Format(ENCODE, (int)DARR));
                _specialChars_.put(E_HARR, String.Format(ENCODE, (int)HARR));
                _specialChars_.put(E_CRARR, String.Format(ENCODE, (int)CRARR));
                _specialChars_.put(E_L_ARR, String.Format(ENCODE, (int)U_LARR));
                _specialChars_.put(E_U_ARR, String.Format(ENCODE, (int)U_UARR));
                _specialChars_.put(E_R_ARR, String.Format(ENCODE, (int)U_RARR));
                _specialChars_.put(E_D_ARR, String.Format(ENCODE, (int)U_DARR));
                _specialChars_.put(E_H_ARR, String.Format(ENCODE, (int)U_HARR));
                _specialChars_.put(E_FORALL, String.Format(ENCODE, (int)FORALL));
                _specialChars_.put(E_PART, String.Format(ENCODE, (int)PART));
                _specialChars_.put(E_EXIST, String.Format(ENCODE, (int)EXIST));
                _specialChars_.put(E_EMPTY, String.Format(ENCODE, (int)EMPTY));
                _specialChars_.put(E_NABLA, String.Format(ENCODE, (int)NABLA));
                _specialChars_.put(E_ISIN, String.Format(ENCODE, (int)ISIN));
                _specialChars_.put(E_NOTIN, String.Format(ENCODE, (int)NOTIN));
                _specialChars_.put(E_NI, String.Format(ENCODE, (int)NI));
                _specialChars_.put(E_PROD, String.Format(ENCODE, (int)PROD));
                _specialChars_.put(E_SUM, String.Format(ENCODE, (int)SUM));
                _specialChars_.put(E_MINUS, String.Format(ENCODE, (int)MINUS));
                _specialChars_.put(E_LOWAST, String.Format(ENCODE, (int)LOWAST));
                _specialChars_.put(E_RADIC, String.Format(ENCODE, (int)RADIC));
                _specialChars_.put(E_PROP, String.Format(ENCODE, (int)PROP));
                _specialChars_.put(E_INFIN, String.Format(ENCODE, (int)INFIN));
                _specialChars_.put(E_ANG, String.Format(ENCODE, (int)ANG));
                _specialChars_.put(E_AND, String.Format(ENCODE, (int)AND));
                _specialChars_.put(E_OR, String.Format(ENCODE, (int)OR));
                _specialChars_.put(E_CAP, String.Format(ENCODE, (int)CAP));
                _specialChars_.put(E_CUP, String.Format(ENCODE, (int)CUP));
                _specialChars_.put(E_INT, String.Format(ENCODE, (int)INT));
                _specialChars_.put(E_THERE4, String.Format(ENCODE, (int)THERE4));
                _specialChars_.put(E_SIM, String.Format(ENCODE, (int)SIM));
                _specialChars_.put(E_CONG, String.Format(ENCODE, (int)CONG));
                _specialChars_.put(E_ASYMP, String.Format(ENCODE, (int)ASYMP));
                _specialChars_.put(E_NE, String.Format(ENCODE, (int)NE));
                _specialChars_.put(E_EQUIV, String.Format(ENCODE, (int)EQUIV));
                _specialChars_.put(E_LE, String.Format(ENCODE, (int)LE));
                _specialChars_.put(E_GE, String.Format(ENCODE, (int)GE));
                _specialChars_.put(E_SUB, String.Format(ENCODE, (int)SUB));
                _specialChars_.put(E_SUP, String.Format(ENCODE, (int)SUP));
                _specialChars_.put(E_NSUB, String.Format(ENCODE, (int)NSUB));
                _specialChars_.put(E_SUBE, String.Format(ENCODE, (int)SUBE));
                _specialChars_.put(E_SUPE, String.Format(ENCODE, (int)SUPE));
                _specialChars_.put(E_OPLUS, String.Format(ENCODE, (int)OPLUS));
                _specialChars_.put(E_OTIMES, String.Format(ENCODE, (int)OTIMES));
                _specialChars_.put(E_PERP, String.Format(ENCODE, (int)PERP));
                _specialChars_.put(E_SDOT, String.Format(ENCODE, (int)SDOT));
                _specialChars_.put(E_LCEIL, String.Format(ENCODE, (int)LCEIL));
                _specialChars_.put(E_RCEIL, String.Format(ENCODE, (int)RCEIL));
                _specialChars_.put(E_LFLOOR, String.Format(ENCODE, (int)LFLOOR));
                _specialChars_.put(E_RFLOOR, String.Format(ENCODE, (int)RFLOOR));
                _specialChars_.put(E_LANG, String.Format(ENCODE, (int)LANG));
                _specialChars_.put(E_RANG, String.Format(ENCODE, (int)RANG));
                _specialChars_.put(E_LOZ, String.Format(ENCODE, (int)LOZ));
                _specialChars_.put(E_SPADES, String.Format(ENCODE, (int)SPADES));
                _specialChars_.put(E_CLUBS, String.Format(ENCODE, (int)CLUBS));
                _specialChars_.put(E_HEARTS, String.Format(ENCODE, (int)HEARTS));
                _specialChars_.put(E_DIAMS, String.Format(ENCODE, (int)DIAMS));
                _specialChars_.put(E_AMP, String.Format(ENCODE, (int)ASCII_38));
            }
            return _specialChars_;
        }
        private static Map<String, String> getMapEncodedChars()
        {
            if (_encodedChars_.isEmpty())
            {
                _encodedChars_.put(E_NBSP, String.Format(ENCODE, (int)NBSP));
                _encodedChars_.put(E_IEXCL, String.Format(ENCODE, (int)IEXCL));
                _encodedChars_.put(E_CENT, String.Format(ENCODE, (int)CENT));
                _encodedChars_.put(E_POUND, String.Format(ENCODE, (int)POUND));
                _encodedChars_.put(E_CURREN, String.Format(ENCODE, (int)CURREN));
                _encodedChars_.put(E_YEN, String.Format(ENCODE, (int)YEN));
                _encodedChars_.put(E_BRVBAR, String.Format(ENCODE, (int)BRVBAR));
                _encodedChars_.put(E_SECT, String.Format(ENCODE, (int)SECT));
                _encodedChars_.put(E_UML, String.Format(ENCODE, (int)UML));
                _encodedChars_.put(E_COPY, String.Format(ENCODE, (int)COPY));
                _encodedChars_.put(E_ORDF, String.Format(ENCODE, (int)ORDF));
                _encodedChars_.put(E_LAQUO, String.Format(ENCODE, (int)LAQUO));
                _encodedChars_.put(E_NOT, String.Format(ENCODE, (int)NOT));
                _encodedChars_.put(E_SHY, String.Format(ENCODE, (int)SHY));
                _encodedChars_.put(E_REG, String.Format(ENCODE, (int)REG));
                _encodedChars_.put(E_MACR, String.Format(ENCODE, (int)MACR));
                _encodedChars_.put(E_DEG, String.Format(ENCODE, (int)DEG));
                _encodedChars_.put(E_PLUSMN, String.Format(ENCODE, (int)PLUSMN));
                _encodedChars_.put(E_SUP2, String.Format(ENCODE, (int)SUP2));
                _encodedChars_.put(E_SUP3, String.Format(ENCODE, (int)SUP3));
                _encodedChars_.put(E_ACUTE, String.Format(ENCODE, (int)ACUTE));
                _encodedChars_.put(E_MICRO, String.Format(ENCODE, (int)MICRO));
                _encodedChars_.put(E_PARA, String.Format(ENCODE, (int)PARA));
                _encodedChars_.put(E_MIDDOT, String.Format(ENCODE, (int)MIDDOT));
                _encodedChars_.put(E_CEDIL, String.Format(ENCODE, (int)CEDIL));
                _encodedChars_.put(E_SUP1, String.Format(ENCODE, (int)SUP1));
                _encodedChars_.put(E_ORDM, String.Format(ENCODE, (int)ORDM));
                _encodedChars_.put(E_RAQUO, String.Format(ENCODE, (int)RAQUO));
                _encodedChars_.put(E_FRAC14, String.Format(ENCODE, (int)FRAC14));
                _encodedChars_.put(E_FRAC12, String.Format(ENCODE, (int)FRAC12));
                _encodedChars_.put(E_FRAC34, String.Format(ENCODE, (int)FRAC34));
                _encodedChars_.put(E_IQUEST, String.Format(ENCODE, (int)IQUEST));
                _encodedChars_.put(E_U_AGRAVE, String.Format(ENCODE, (int)U_A_GRAVE));
                _encodedChars_.put(E_U_AACUTE, String.Format(ENCODE, (int)U_A_ACUTE));
                _encodedChars_.put(E_U_ACIRC, String.Format(ENCODE, (int)U_A_CIRC));
                _encodedChars_.put(E_U_ATILDE, String.Format(ENCODE, (int)U_A_TILDE));
                _encodedChars_.put(E_U_AUML, String.Format(ENCODE, (int)U_A_UML));
                _encodedChars_.put(E_U_ARING, String.Format(ENCODE, (int)U_A_RING));
                _encodedChars_.put(E_U_AELIG, String.Format(ENCODE, (int)U_AE_LIG));
                _encodedChars_.put(E_U_CCEDIL, String.Format(ENCODE, (int)U_C_CEDIL));
                _encodedChars_.put(E_U_EGRAVE, String.Format(ENCODE, (int)U_E_GRAVE));
                _encodedChars_.put(E_U_EACUTE, String.Format(ENCODE, (int)U_E_ACUTE));
                _encodedChars_.put(E_U_ECIRC, String.Format(ENCODE, (int)U_E_CIRC));
                _encodedChars_.put(E_U_EUML, String.Format(ENCODE, (int)U_E_UML));
                _encodedChars_.put(E_U_IGRAVE, String.Format(ENCODE, (int)U_I_GRAVE));
                _encodedChars_.put(E_U_IACUTE, String.Format(ENCODE, (int)U_I_ACUTE));
                _encodedChars_.put(E_U_ICIRC, String.Format(ENCODE, (int)U_I_CIRC));
                _encodedChars_.put(E_U_IUML, String.Format(ENCODE, (int)U_I_UML));
                _encodedChars_.put(E_U_ETH, String.Format(ENCODE, (int)U_ETH));
                _encodedChars_.put(E_U_NTILDE, String.Format(ENCODE, (int)U_N_TILDE));
                _encodedChars_.put(E_U_OGRAVE, String.Format(ENCODE, (int)U_O_GRAVE));
                _encodedChars_.put(E_U_OACUTE, String.Format(ENCODE, (int)U_O_ACUTE));
                _encodedChars_.put(E_U_OCIRC, String.Format(ENCODE, (int)U_O_CIRC));
                _encodedChars_.put(E_U_OTILDE, String.Format(ENCODE, (int)U_O_TILDE));
                _encodedChars_.put(E_U_OUML, String.Format(ENCODE, (int)U_O_UML));
                _encodedChars_.put(E_TIMES, String.Format(ENCODE, (int)TIMES));
                _encodedChars_.put(E_U_OSLASH, String.Format(ENCODE, (int)U_O_SLASH));
                _encodedChars_.put(E_U_UGRAVE, String.Format(ENCODE, (int)U_U_GRAVE));
                _encodedChars_.put(E_U_UACUTE, String.Format(ENCODE, (int)U_U_ACUTE));
                _encodedChars_.put(E_U_UCIRC, String.Format(ENCODE, (int)U_U_CIRC));
                _encodedChars_.put(E_U_UUML, String.Format(ENCODE, (int)U_U_UML));
                _encodedChars_.put(E_U_YACUTE, String.Format(ENCODE, (int)U_Y_ACUTE));
                _encodedChars_.put(E_U_THORN, String.Format(ENCODE, (int)U_THORN));
                _encodedChars_.put(E_SZLIG, String.Format(ENCODE, (int)SZLIG));
                _encodedChars_.put(E_AGRAVE, String.Format(ENCODE, (int)AGRAVE));
                _encodedChars_.put(E_AACUTE, String.Format(ENCODE, (int)AACUTE));
                _encodedChars_.put(E_ACIRC, String.Format(ENCODE, (int)ACIRC));
                _encodedChars_.put(E_ATILDE, String.Format(ENCODE, (int)ATILDE));
                _encodedChars_.put(E_AUML, String.Format(ENCODE, (int)AUML));
                _encodedChars_.put(E_ARING, String.Format(ENCODE, (int)ARING));
                _encodedChars_.put(E_AELIG, String.Format(ENCODE, (int)AELIG));
                _encodedChars_.put(E_CCEDIL, String.Format(ENCODE, (int)CCEDIL));
                _encodedChars_.put(E_EGRAVE, String.Format(ENCODE, (int)EGRAVE));
                _encodedChars_.put(E_EACUTE, String.Format(ENCODE, (int)EACUTE));
                _encodedChars_.put(E_ECIRC, String.Format(ENCODE, (int)ECIRC));
                _encodedChars_.put(E_EUML, String.Format(ENCODE, (int)EUML));
                _encodedChars_.put(E_IGRAVE, String.Format(ENCODE, (int)IGRAVE));
                _encodedChars_.put(E_IACUTE, String.Format(ENCODE, (int)IACUTE));
                _encodedChars_.put(E_ICIRC, String.Format(ENCODE, (int)ICIRC));
                _encodedChars_.put(E_IUML, String.Format(ENCODE, (int)IUML));
                _encodedChars_.put(E_ETH, String.Format(ENCODE, (int)ETH));
                _encodedChars_.put(E_NTILDE, String.Format(ENCODE, (int)NTILDE));
                _encodedChars_.put(E_OGRAVE, String.Format(ENCODE, (int)OGRAVE));
                _encodedChars_.put(E_OACUTE, String.Format(ENCODE, (int)OACUTE));
                _encodedChars_.put(E_OCIRC, String.Format(ENCODE, (int)OCIRC));
                _encodedChars_.put(E_OTILDE, String.Format(ENCODE, (int)OTILDE));
                _encodedChars_.put(E_OUML, String.Format(ENCODE, (int)OUML));
                _encodedChars_.put(E_DIVIDE, String.Format(ENCODE, (int)DIVIDE));
                _encodedChars_.put(E_OSLASH, String.Format(ENCODE, (int)OSLASH));
                _encodedChars_.put(E_UGRAVE, String.Format(ENCODE, (int)UGRAVE));
                _encodedChars_.put(E_UACUTE, String.Format(ENCODE, (int)UACUTE));
                _encodedChars_.put(E_UCIRC, String.Format(ENCODE, (int)UCIRC));
                _encodedChars_.put(E_UUML, String.Format(ENCODE, (int)UUML));
                _encodedChars_.put(E_YACUTE, String.Format(ENCODE, (int)YACUTE));
                _encodedChars_.put(E_THORN, String.Format(ENCODE, (int)THORN));
                _encodedChars_.put(E_YUML, String.Format(ENCODE, (int)YUML));
                _encodedChars_.put(E_QUOT, String.Format(ENCODE, (int)QUOT));
                _encodedChars_.put(E_LT, String.Format(ENCODE, (int)LT));
                _encodedChars_.put(E_GT, String.Format(ENCODE, (int)GT));
                _encodedChars_.put(E_APOS, String.Format(ENCODE, (int)APOS));
                _encodedChars_.put(E_U_OELIG, String.Format(ENCODE, (int)U_OE_LIG));
                _encodedChars_.put(E_OELIG, String.Format(ENCODE, (int)OELIG));
                _encodedChars_.put(E_S_CARON, String.Format(ENCODE, (int)U_SCARON));
                _encodedChars_.put(E_SCARON, String.Format(ENCODE, (int)SCARON));
                _encodedChars_.put(E_U_YUML, String.Format(ENCODE, (int)U_Y_UML));
                _encodedChars_.put(E_CIRC, String.Format(ENCODE, (int)CIRC));
                _encodedChars_.put(E_TILDE, String.Format(ENCODE, (int)TILDE));
                _encodedChars_.put(E_ENSP, String.Format(ENCODE, (int)ENSP));
                _encodedChars_.put(E_EMSP, String.Format(ENCODE, (int)EMSP));
                _encodedChars_.put(E_THINSP, String.Format(ENCODE, (int)THINSP));
                _encodedChars_.put(E_ZWNJ, String.Format(ENCODE, (int)ZWNJ));
                _encodedChars_.put(E_ZWJ, String.Format(ENCODE, (int)ZWJ));
                _encodedChars_.put(E_LRM, String.Format(ENCODE, (int)LRM));
                _encodedChars_.put(E_RLM, String.Format(ENCODE, (int)RLM));
                _encodedChars_.put(E_NDASH, String.Format(ENCODE, (int)NDASH));
                _encodedChars_.put(E_MDASH, String.Format(ENCODE, (int)MDASH));
                _encodedChars_.put(E_LSQUO, String.Format(ENCODE, (int)LSQUO));
                _encodedChars_.put(E_RSQUO, String.Format(ENCODE, (int)RSQUO));
                _encodedChars_.put(E_SBQUO, String.Format(ENCODE, (int)SBQUO));
                _encodedChars_.put(E_LDQUO, String.Format(ENCODE, (int)LDQUO));
                _encodedChars_.put(E_RDQUO, String.Format(ENCODE, (int)RDQUO));
                _encodedChars_.put(E_BDQUO, String.Format(ENCODE, (int)BDQUO));
                _encodedChars_.put(E_DAGGER, String.Format(ENCODE, (int)D_AGGER));
                _encodedChars_.put(E_U_DAGGER, String.Format(ENCODE, (int)DAGGER));
                _encodedChars_.put(E_PERMIL, String.Format(ENCODE, (int)PERMIL));
                _encodedChars_.put(E_LSAQUO, String.Format(ENCODE, (int)LSAQUO));
                _encodedChars_.put(E_RSAQUO, String.Format(ENCODE, (int)RSAQUO));
                _encodedChars_.put(E_EURO, String.Format(ENCODE, (int)EURO));
                _encodedChars_.put(E_FNOF, String.Format(ENCODE, (int)FNOF));
                _encodedChars_.put(E_U_ALPHA, String.Format(ENCODE, (int)U_A_LPHA));
                _encodedChars_.put(E_U_BETA, String.Format(ENCODE, (int)U_B_ETA));
                _encodedChars_.put(E_U_GAMMA, String.Format(ENCODE, (int)U_G_AMMA));
                _encodedChars_.put(E_U_DELTA, String.Format(ENCODE, (int)U_D_ELTA));
                _encodedChars_.put(E_U_EPSILON, String.Format(ENCODE, (int)U_E_PSILON));
                _encodedChars_.put(E_U_ZETA, String.Format(ENCODE, (int)U_Z_ETA));
                _encodedChars_.put(E_U_ETA, String.Format(ENCODE, (int)U_E_TA));
                _encodedChars_.put(E_U_THETA, String.Format(ENCODE, (int)U_T_HETA));
                _encodedChars_.put(E_U_IOTA, String.Format(ENCODE, (int)U_I_OTA));
                _encodedChars_.put(E_U_KAPPA, String.Format(ENCODE, (int)U_K_APPA));
                _encodedChars_.put(E_U_LAMBDA, String.Format(ENCODE, (int)U_L_AMBDA));
                _encodedChars_.put(E_U_MU, String.Format(ENCODE, (int)U_M_U));
                _encodedChars_.put(E_U_NU, String.Format(ENCODE, (int)U_N_U));
                _encodedChars_.put(E_U_XI, String.Format(ENCODE, (int)U_X_I));
                _encodedChars_.put(E_U_OMICRON, String.Format(ENCODE, (int)U_O_MICRON));
                _encodedChars_.put(E_U_PI, String.Format(ENCODE, (int)U_P_I));
                _encodedChars_.put(E_U_RHO, String.Format(ENCODE, (int)U_R_HO));
                _encodedChars_.put(E_U_SIGMA, String.Format(ENCODE, (int)U_S_IGMA));
                _encodedChars_.put(E_U_TAU, String.Format(ENCODE, (int)U_T_AU));
                _encodedChars_.put(E_U_UPSILON, String.Format(ENCODE, (int)U_U_PSILON));
                _encodedChars_.put(E_U_PHI, String.Format(ENCODE, (int)U_P_HI));
                _encodedChars_.put(E_U_CHI, String.Format(ENCODE, (int)U_C_HI));
                _encodedChars_.put(E_U_PSI, String.Format(ENCODE, (int)U_P_SI));
                _encodedChars_.put(E_U_OMEGA, String.Format(ENCODE, (int)U_O_MEGA));
                _encodedChars_.put(E_ALPHA, String.Format(ENCODE, (int)ALPHA));
                _encodedChars_.put(E_BETA, String.Format(ENCODE, (int)BETA));
                _encodedChars_.put(E_GAMMA, String.Format(ENCODE, (int)GAMMA));
                _encodedChars_.put(E_DELTA, String.Format(ENCODE, (int)DELTA));
                _encodedChars_.put(E_EPSILON, String.Format(ENCODE, (int)EPSILON));
                _encodedChars_.put(E_ZETA, String.Format(ENCODE, (int)ZETA));
                _encodedChars_.put(E_ETA, String.Format(ENCODE, (int)ETA));
                _encodedChars_.put(E_THETA, String.Format(ENCODE, (int)THETA));
                _encodedChars_.put(E_IOTA, String.Format(ENCODE, (int)IOTA));
                _encodedChars_.put(E_KAPPA, String.Format(ENCODE, (int)KAPPA));
                _encodedChars_.put(E_LAMBDA, String.Format(ENCODE, (int)LAMBDA));
                _encodedChars_.put(E_MU, String.Format(ENCODE, (int)MU));
                _encodedChars_.put(E_NU, String.Format(ENCODE, (int)NU));
                _encodedChars_.put(E_XI, String.Format(ENCODE, (int)XI));
                _encodedChars_.put(E_OMICRON, String.Format(ENCODE, (int)OMICRON));
                _encodedChars_.put(E_PI, String.Format(ENCODE, (int)PI));
                _encodedChars_.put(E_RHO, String.Format(ENCODE, (int)RHO));
                _encodedChars_.put(E_SIGMAF, String.Format(ENCODE, (int)SIGMAF));
                _encodedChars_.put(E_SIGMA, String.Format(ENCODE, (int)SIGMA));
                _encodedChars_.put(E_TAU, String.Format(ENCODE, (int)TAU));
                _encodedChars_.put(E_UPSILON, String.Format(ENCODE, (int)UPSILON));
                _encodedChars_.put(E_PHI, String.Format(ENCODE, (int)PHI));
                _encodedChars_.put(E_CHI, String.Format(ENCODE, (int)CHI));
                _encodedChars_.put(E_PSI, String.Format(ENCODE, (int)PSI));
                _encodedChars_.put(E_OMEGA, String.Format(ENCODE, (int)OMEGA));
                _encodedChars_.put(E_THETASYM, String.Format(ENCODE, (int)THETASYM));
                _encodedChars_.put(E_UPSIH, String.Format(ENCODE, (int)UPSIH));
                _encodedChars_.put(E_PIV, String.Format(ENCODE, (int)PIV));
                _encodedChars_.put(E_BULL, String.Format(ENCODE, (int)BULL));
                _encodedChars_.put(E_HELLIP, String.Format(ENCODE, (int)HELLIP));
                _encodedChars_.put(E_PRIME, String.Format(ENCODE, (int)PRIME));
                _encodedChars_.put(E_P_RIME, String.Format(ENCODE, (int)U_PRIME));
                _encodedChars_.put(E_OLINE, String.Format(ENCODE, (int)OLINE));
                _encodedChars_.put(E_FRASL, String.Format(ENCODE, (int)FRASL));
                _encodedChars_.put(E_WEIERP, String.Format(ENCODE, (int)WEIERP));
                _encodedChars_.put(E_IMAGE, String.Format(ENCODE, (int)IMAGE));
                _encodedChars_.put(E_REAL, String.Format(ENCODE, (int)REAL));
                _encodedChars_.put(E_TRADE, String.Format(ENCODE, (int)TRADE));
                _encodedChars_.put(E_ALEFSYM, String.Format(ENCODE, (int)ALEFSYM));
                _encodedChars_.put(E_LARR, String.Format(ENCODE, (int)LARR));
                _encodedChars_.put(E_UARR, String.Format(ENCODE, (int)UARR));
                _encodedChars_.put(E_RARR, String.Format(ENCODE, (int)RARR));
                _encodedChars_.put(E_DARR, String.Format(ENCODE, (int)DARR));
                _encodedChars_.put(E_HARR, String.Format(ENCODE, (int)HARR));
                _encodedChars_.put(E_CRARR, String.Format(ENCODE, (int)CRARR));
                _encodedChars_.put(E_L_ARR, String.Format(ENCODE, (int)U_LARR));
                _encodedChars_.put(E_U_ARR, String.Format(ENCODE, (int)U_UARR));
                _encodedChars_.put(E_R_ARR, String.Format(ENCODE, (int)U_RARR));
                _encodedChars_.put(E_D_ARR, String.Format(ENCODE, (int)U_DARR));
                _encodedChars_.put(E_H_ARR, String.Format(ENCODE, (int)U_HARR));
                _encodedChars_.put(E_FORALL, String.Format(ENCODE, (int)FORALL));
                _encodedChars_.put(E_PART, String.Format(ENCODE, (int)PART));
                _encodedChars_.put(E_EXIST, String.Format(ENCODE, (int)EXIST));
                _encodedChars_.put(E_EMPTY, String.Format(ENCODE, (int)EMPTY));
                _encodedChars_.put(E_NABLA, String.Format(ENCODE, (int)NABLA));
                _encodedChars_.put(E_ISIN, String.Format(ENCODE, (int)ISIN));
                _encodedChars_.put(E_NOTIN, String.Format(ENCODE, (int)NOTIN));
                _encodedChars_.put(E_NI, String.Format(ENCODE, (int)NI));
                _encodedChars_.put(E_PROD, String.Format(ENCODE, (int)PROD));
                _encodedChars_.put(E_SUM, String.Format(ENCODE, (int)SUM));
                _encodedChars_.put(E_MINUS, String.Format(ENCODE, (int)MINUS));
                _encodedChars_.put(E_LOWAST, String.Format(ENCODE, (int)LOWAST));
                _encodedChars_.put(E_RADIC, String.Format(ENCODE, (int)RADIC));
                _encodedChars_.put(E_PROP, String.Format(ENCODE, (int)PROP));
                _encodedChars_.put(E_INFIN, String.Format(ENCODE, (int)INFIN));
                _encodedChars_.put(E_ANG, String.Format(ENCODE, (int)ANG));
                _encodedChars_.put(E_AND, String.Format(ENCODE, (int)AND));
                _encodedChars_.put(E_OR, String.Format(ENCODE, (int)OR));
                _encodedChars_.put(E_CAP, String.Format(ENCODE, (int)CAP));
                _encodedChars_.put(E_CUP, String.Format(ENCODE, (int)CUP));
                _encodedChars_.put(E_INT, String.Format(ENCODE, (int)INT));
                _encodedChars_.put(E_THERE4, String.Format(ENCODE, (int)THERE4));
                _encodedChars_.put(E_SIM, String.Format(ENCODE, (int)SIM));
                _encodedChars_.put(E_CONG, String.Format(ENCODE, (int)CONG));
                _encodedChars_.put(E_ASYMP, String.Format(ENCODE, (int)ASYMP));
                _encodedChars_.put(E_NE, String.Format(ENCODE, (int)NE));
                _encodedChars_.put(E_EQUIV, String.Format(ENCODE, (int)EQUIV));
                _encodedChars_.put(E_LE, String.Format(ENCODE, (int)LE));
                _encodedChars_.put(E_GE, String.Format(ENCODE, (int)GE));
                _encodedChars_.put(E_SUB, String.Format(ENCODE, (int)SUB));
                _encodedChars_.put(E_SUP, String.Format(ENCODE, (int)SUP));
                _encodedChars_.put(E_NSUB, String.Format(ENCODE, (int)NSUB));
                _encodedChars_.put(E_SUBE, String.Format(ENCODE, (int)SUBE));
                _encodedChars_.put(E_SUPE, String.Format(ENCODE, (int)SUPE));
                _encodedChars_.put(E_OPLUS, String.Format(ENCODE, (int)OPLUS));
                _encodedChars_.put(E_OTIMES, String.Format(ENCODE, (int)OTIMES));
                _encodedChars_.put(E_PERP, String.Format(ENCODE, (int)PERP));
                _encodedChars_.put(E_SDOT, String.Format(ENCODE, (int)SDOT));
                _encodedChars_.put(E_LCEIL, String.Format(ENCODE, (int)LCEIL));
                _encodedChars_.put(E_RCEIL, String.Format(ENCODE, (int)RCEIL));
                _encodedChars_.put(E_LFLOOR, String.Format(ENCODE, (int)LFLOOR));
                _encodedChars_.put(E_RFLOOR, String.Format(ENCODE, (int)RFLOOR));
                _encodedChars_.put(E_LANG, String.Format(ENCODE, (int)LANG));
                _encodedChars_.put(E_RANG, String.Format(ENCODE, (int)RANG));
                _encodedChars_.put(E_LOZ, String.Format(ENCODE, (int)LOZ));
                _encodedChars_.put(E_SPADES, String.Format(ENCODE, (int)SPADES));
                _encodedChars_.put(E_CLUBS, String.Format(ENCODE, (int)CLUBS));
                _encodedChars_.put(E_HEARTS, String.Format(ENCODE, (int)HEARTS));
                _encodedChars_.put(E_DIAMS, String.Format(ENCODE, (int)DIAMS));
                _encodedChars_.put(E_AMP, String.Format(ENCODE, (int)ASCII_38));
            }
            return _encodedChars_;
        }
   }
}
