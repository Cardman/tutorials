using System;
using System.Drawing;
using System.Drawing.Imaging;
using NGif;

namespace Example
{
	class ExampleMain
	{
		[STAThread]
		static void Main(string[] args)
		{
            /* create Gif */
            //you should replace filepath
            string folder = "C:/Users/cardman/Documents/Visual Studio 2015/Projects/Gif/Example/bolt/";

            //String [] imageFilePaths = new String[]{"G:\\01.png"};
            String[] imageFilePaths = new String[] {
                folder +"0.png", folder + "1.png", folder + "2.png",
             folder+"3.png", folder + "4.png", folder + "5.png",
            folder+"6.png", folder + "7.png", folder + "8.png", folder + "9.png"};
            //String outputFilePath = "G:\\test.gif";
            String outputFilePath = folder + "bolt.gif";
            AnimatedGifEncoder e = new AnimatedGifEncoder();
			e.Start( outputFilePath );
			e.SetDelay(500);
			//-1:no repeat,0:always repeat
			e.SetRepeat(0);
			for (int i = 0, count = imageFilePaths.Length; i < count; i++ ) 
			{
				e.AddFrame( Image.FromFile( imageFilePaths[i] ) );
			}
			e.Finish();
			/* extract Gif */
			//string outputPath = "G:\\";
            string outputPath = folder;
            GifDecoder gifDecoder = new GifDecoder();
			//gifDecoder.Read( "G:\\test.gif" );
            gifDecoder.Read(outputFilePath);
            for ( int i = 0, count = gifDecoder.GetFrameCount(); i < count; i++ ) 
			{
				Image frame = gifDecoder.GetFrame( i );  // frame i
				frame.Save( outputPath +"_"+ i + ".png", ImageFormat.Png );
			}
		}
	}
}
