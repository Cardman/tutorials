package gltuto.gui;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import sdljava.SDLException;
import sdljava.SDLMain;
import sdljava.event.SDLEvent;
import sdljava.video.SDLRect;
import sdljava.video.SDLSurface;
import sdljava.video.SDLVideo;


public class Installation {

    private SDLSurface screen;

    public Installation() throws SDLException, InterruptedException {
        SDLMain.init(SDLMain.SDL_INIT_VIDEO);

        screen = SDLVideo.setVideoMode(640, 480, 32, SDLVideo.SDL_DOUBLEBUF | SDLVideo.SDL_HWSURFACE);
        SDLVideo.wmSetCaption("Ma première fenêtre avec sdljava", null);

        Thread.sleep(1000);
        screen.freeSurface();
        SDLMain.quit();
    }

    public static void main(String[] _args) throws SDLException, InterruptedException, IOException {
        // Gestion des événements 1/2
        SDLEvent event_ = null;
        boolean boucle_ = true;

        // Initialisation de SDL et de l'affichage
        SDLMain.init(SDLMain.SDL_INIT_VIDEO);
        SDLVideo.wmSetCaption("Des images avec sdljava", null);
//        SDLSurface rectangle = SDLVideo.createRGBSurface(SDLVideo.SDL_HWSURFACE, 200, 150, 32, 0, 0, 0, 0);
//        rectangle.fillRect(rectangle.mapRGB(255, 0, 0));
        SDLSurface screen_ = SDLVideo.setVideoMode(640, 480, 32, SDLVideo.SDL_DOUBLEBUF | SDLVideo.SDL_HWSURFACE);

//        rectangle.blitSurface(screen);
        // Chargement des images
        int[] pix_ = new int[20000];
        int i_ = 0;
        for (int i = 0; i < 200; i++) {
            for (int j = 0; j < 100; j++) {
                pix_[i_] = i * 200 + j;
                i_++;
            }
        }
        SDLSurface rectangle_ = SDLVideo.createRGBSurfaceFrom(pix_, 100, 200, 32, 400, 0, 0, 0, 0);
        rectangle_.blitSurface(screen_);
//        rectangle.getPixelData();
//        SDLVideo.loadBMP("resources_gl/objectif.png");
//        InputStream is = ClassLoader.getSystemResourceAsStream("resources_gl/objectif.png");
        
//        SDLSurface aeris = SDLImage.load("images/aerith.png");
        //                InputStream is = ClassLoader.getSystemResourceAsStream("resources_gl/objectif.png");
        //                SDLSurface aeris = SDLImage.load(is);
//        SDLSurface zack = SDLImage.load("images/zack.png");
        SDLRect aerisPos_ = new SDLRect(0, 0);
        SDLRect zackPos_ = new SDLRect(300, 50);


        while (boucle_) {
            event_ = SDLEvent.waitEvent();
            if (event_.getType() == SDLEvent.SDL_QUIT) {
                boucle_ = false;
            }

//            aeris_.blitSurface(screen_, aerisPos_);
//            zack_.blitSurface(screen_, zackPos_);
            screen_.flip();
        }

        // On quitte :: Libération de la mémoire
//        aeris_.freeSurface();
//        zack_.freeSurface();
        screen_.freeSurface();
        SDLMain.quit();
        //        new Installation();
    }

    private static String loadFile(String _filename) {
        StringBuilder vertexCode_ = new StringBuilder();
        String line_ = null;
        try {
            InputStream is_ = ClassLoader.getSystemResourceAsStream(_filename);
            BufferedReader reader_ = new BufferedReader(new InputStreamReader(is_));
            while( (line_ = reader_.readLine()) !=null ) {
                vertexCode_.append(line_);
                vertexCode_.append('\n');
            }
        } catch(Exception _0) {
            throw new IllegalArgumentException("unable to load shader from file ["+_filename+"]", _0);
        }

        return vertexCode_.toString();
    }
}

