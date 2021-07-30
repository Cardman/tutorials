using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.Windows.Forms;

namespace MyProject.gui
{
    public class MyLabel : Label
    {
        private Color textColor;
        private Image img;

        public MyLabel()
        {
            //Paint += OnPaint;
            //Image img_ = Base64ToImage("iVBORw0KGgoAAAANSUhEUgAAAAcAAAAHCAIAAABLMMCEAAAAEUlEQVR42mN4K6OCiRgGgSgAfEs5nifMv08AAAAASUVORK5CYII=");
            //Console.WriteLine(ImageToBase64(img_));
            Image imgOne_ = null;
            Image imgTwo_ = null;
            Assembly a_ = Assembly.GetAssembly(typeof(MyLabel));
            /*string[] files = Assembly.GetAssembly(typeof(MyLabel)).GetManifestResourceNames();
            foreach (string s in files)
            {
            }*/
            using (Stream stream = a_.GetManifestResourceStream("MyProject.myresources.trs.imgs.MAGICARPE.txt"))
            {
                using (StreamReader reader = new StreamReader(stream))
                {
                    string result = reader.ReadToEnd();
                    imgOne_ = Base64ToImage(result);
                    //textContainer.Text += result + "\n";
                }
            }
            using (Stream stream = a_.GetManifestResourceStream("MyProject.myresources.trs.imgs.LEVIATOR.txt"))
            {
                using (StreamReader reader = new StreamReader(stream))
                {
                    string result = reader.ReadToEnd();
                    imgTwo_ = Base64ToImage(result);
                    //textContainer.Text += result + "\n";
                }
            }
            img = stackImages(imgOne_, imgTwo_);
            //img = 
            /*Graphics g_ = CreateGraphics();
            g_.Dispose();*/
            textColor = Color.Gray;
        }

        public int getWidth(string _string)
        {
            int w_ = TextRenderer.MeasureText(_string, Font).Width;
            return w_;
        }

        public static string ImageToBase64(Image image)
        {
            return ImageToBase64(image, ImageFormat.Png);
        }
        public static string ImageToBase64(Image image,
                ImageFormat format)
        {
            using (MemoryStream ms = new MemoryStream())
            {
                // Convert Image to byte[]
                image.Save(ms, format);
                byte[] imageBytes = ms.ToArray();

                // Convert byte[] to Base64 String
                string base64String = Convert.ToBase64String(imageBytes);
                return base64String;
            }
        }
        public void setColorText(string _rgb)
        {
            try
            {
                string[] tab_ = _rgb.Split(';');
                textColor = Color.FromArgb(int.Parse(tab_[0]), int.Parse(tab_[1]), int.Parse(tab_[2]));
            } catch (Exception e)
            {

            }
            Invalidate();
            Update();
        }
        public static Image stackImages(Image image1, Image image2)
        {
            Bitmap bitmap = new Bitmap(image1.Width + image2.Width, Math.Max(image1.Height, image2.Height));
            //bitmap.
            using (Graphics g = Graphics.FromImage(bitmap))
            {
                g.DrawImage(image1, 0, 0);
                g.DrawImage(image2, image1.Width, 0);
            }
            return bitmap;
        }
        //Base64 String to Image
        public static Image Base64ToImage(string base64String)
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
        protected override void OnPaint(PaintEventArgs e)
        {
            // Create a local version of the graphics object for the PictureBox.
            Graphics g = e.Graphics;

            // Draw a string on the PictureBox.
            SolidBrush s_ = new SolidBrush(textColor);
            g.DrawString("This is a diagonal line drawn on the control",
                new Font("Arial", 10), s_, new Point(30, 30));
            s_.Dispose();
            //new Brush(new Color());
            // Draw a line in the PictureBox.
            /*g.DrawLine(Pens.Red, Left, Top,
                Right, Bottom);*/
            Pen p_ = new Pen(Color.FromArgb(255, 0, 0));
            g.DrawLine(p_, 0, 0,
                Right, Bottom);
            p_.Dispose();
            g.DrawImage(img, new Point(0,30));
        }
    }
}
