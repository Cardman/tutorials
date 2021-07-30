using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing.Imaging;
using System.Threading.Tasks;
using System.Drawing;
using System.IO;

namespace FormatHtml
{
    public class ConverterBufferedImage
    {
        public const String IMG_EXT = "png";
        private const String BASE64 = ";base64,";

	    private const String DATA_IMAGE = "data:image/";

	    private const String EMPTY_STRING = "";
        public static String surroundImage(String _image)
        {
            String contourChart_ = EMPTY_STRING;
            StringBuilder sb_ = new StringBuilder();
            sb_.Append(DATA_IMAGE + IMG_EXT + BASE64);
            sb_.Append(_image);
            contourChart_ = sb_.ToString();
            return contourChart_;
        }
        public static String toBaseSixtyFour(Image _buffer)
        {
            return toBaseSixtyFour(_buffer, ImageFormat.Png);
        }
        public static String toBaseSixtyFour(Image _buffer, ImageFormat _format)
        {
            using (MemoryStream ms = new MemoryStream())
            {
                // Convert Image to byte[]
                _buffer.Save(ms, _format);
                byte[] imageBytes = ms.ToArray();

                // Convert byte[] to Base64 String
                string base64String = Convert.ToBase64String(imageBytes);
                return base64String;
            }
        }
        public static Image decodeToImage(string base64String)
        {
            // Convert Base64 String to byte[]
            byte[] imageBytes = Convert.FromBase64String(base64String);
            MemoryStream ms = new MemoryStream(imageBytes, 0,
              imageBytes.Length);

            // Convert byte[] to Image
            ms.Write(imageBytes, 0, imageBytes.Length);
            Image image = Image.FromStream(ms, true);
            return image;
        }
    }
}
