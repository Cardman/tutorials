package gltuto.gui;

import java.io.InputStream;

import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.glu.GLU;
import com.jogamp.opengl.glu.GLUquadric;
import com.jogamp.opengl.util.gl2.GLUT;
import com.jogamp.opengl.util.texture.Texture;
import com.jogamp.opengl.util.texture.TextureIO;

public final class MyGLEventListener implements GLEventListener {

//    private Direction dir;

    private double xPt;
    private double yPt;
//    private boolean moving;
    private int xEyeBack;
    private int yEyeBack;
    private double thetaRad;
    private double phiRad;
    private int xEye;
    private int yEye;
    private double zPt;
    private Texture txt;
    private Texture bottom;
    private Texture middle;
    private Texture motor;
    private Texture top;


    private GLU glu = new GLU();
    private GLUT glut = new GLUT();

    private float camera[] = {0f, 0f, 5f};

    private float[] lightAmbient = {0.015625f, 0.015625f, 0.015625f, 0.015625f};
    private float[] lightDiffuse = {1.0f, 1.0f, 1.0f, 1.0f};
    private float[] lightSpecular = {1.0f,1.0f, 1.0f, 1.0f};
    private float[] lightPosition = {100f, 0f, 10f, 1f};

    private float[] materialSpecular = {1.0f, 1.0f, 1.0f, 1.0f};

    private float angle;

    @Override
    public void init(GLAutoDrawable _drawable) {
        GL2 gl_ = _drawable.getGL().getGL2();
        gl_.glEnable(GL2.GL_TEXTURE_2D);
        try {
            InputStream inputStream_ = null;
            inputStream_ = ClassLoader.getSystemResourceAsStream("resources_gl/avatar.jpg");
            txt = TextureIO.newTexture(inputStream_, true, TextureIO.JPG);
//            gl.glBindTexture(GL2.GL_TEXTURE_2D, txt.getTextureObject());
        } catch (Exception _0) {
            _0.printStackTrace();
        }
        try {
            InputStream inputStream_ = null;
            inputStream_ = ClassLoader.getSystemResourceAsStream("resources_gl/rocket_bottom.jpg");
            bottom = TextureIO.newTexture(inputStream_, true, TextureIO.JPG);
//            gl.glBindTexture(GL2.GL_TEXTURE_2D, txt.getTextureObject());
        } catch (Exception _0) {
            _0.printStackTrace();
        }
        try {
            InputStream inputStream_ = null;
            inputStream_ = ClassLoader.getSystemResourceAsStream("resources_gl/rocket_middle.jpg");
            middle = TextureIO.newTexture(inputStream_, true, TextureIO.JPG);
//            gl.glBindTexture(GL2.GL_TEXTURE_2D, txt.getTextureObject());
        } catch (Exception _0) {
            _0.printStackTrace();
        }
        try {
            InputStream inputStream_ = null;
            inputStream_ = ClassLoader.getSystemResourceAsStream("resources_gl/rocket_motor.jpg");
            motor = TextureIO.newTexture(inputStream_, true, TextureIO.JPG);
//            gl.glBindTexture(GL2.GL_TEXTURE_2D, txt.getTextureObject());
        } catch (Exception _0) {
            _0.printStackTrace();
        }
        try {
            InputStream inputStream_ = null;
            inputStream_ = ClassLoader.getSystemResourceAsStream("resources_gl/rocket_top.jpg");
            top = TextureIO.newTexture(inputStream_, true, TextureIO.JPG);
//            gl.glBindTexture(GL2.GL_TEXTURE_2D, txt.getTextureObject());
        } catch (Exception _0) {
            _0.printStackTrace();
        }

        gl_.glClearColor(0.8125f, 0.5f, 0.0f, 1.0f);

        gl_.glEnable(GL2.GL_DEPTH_TEST);
        gl_.glClearDepth(1.0f);

        gl_.glShadeModel(GL2.GL_SMOOTH);
        gl_.glEnable(GL2.GL_LIGHTING);

        gl_.glEnable(GL2.GL_LIGHT0);
        gl_.glLightfv(GL2.GL_LIGHT0, GL2.GL_AMBIENT, lightAmbient, 0);
        gl_.glLightfv(GL2.GL_LIGHT0, GL2.GL_DIFFUSE, lightDiffuse, 0);
        gl_.glLightfv(GL2.GL_LIGHT0, GL2.GL_SPECULAR, lightSpecular, 0);
        gl_.glLightfv(GL2.GL_LIGHT0, GL2.GL_POSITION, lightPosition, 0);

        gl_.glEnable(GL2.GL_COLOR_MATERIAL);
        gl_.glColorMaterial(GL2.GL_FRONT_AND_BACK, GL2.GL_AMBIENT_AND_DIFFUSE);
        gl_.glMateriali(GL2.GL_FRONT_AND_BACK, GL2.GL_SHININESS, 90);
        gl_.glMaterialfv(GL2.GL_FRONT_AND_BACK, GL2.GL_SPECULAR, materialSpecular, 0);
    }

    @Override
    public void dispose(GLAutoDrawable _drawable) {
    }

    public void setDirection(Direction _dir) {
//        dir = _dir;
        if (_dir == Direction.LEFT) {
            xPt-=0.125d;
        } else if (_dir == Direction.RIGHT) {
            xPt+=0.125d;
        } else if (_dir == Direction.UP) {
            yPt-=0.125d;
        } else if (_dir == Direction.DOWN) {
            yPt+=0.125d;
        }
    }

    public void move(int _x, int _y) {
        xEyeBack = xEye;
        yEyeBack = yEye;
        xEye = _x;
        yEye = _y;
//        moving = true;
        thetaRad -= Math.atan((xEye - xEyeBack)/160.0d);
        phiRad -= Math.atan((yEye - yEyeBack)/120.0d);
    }

    public void setzPt(int _zPt) {
        zPt += _zPt / 8d;
    }

    @Override
    public void display(GLAutoDrawable _drawable) {
        GL2 gl_ = _drawable.getGL().getGL2();
        gl_.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);
        gl_.glLoadIdentity();
//        drawRocket(gl_);
//        if (dir == Direction.LEFT) {
//            xPt-=0.125d;
//        } else if (dir == Direction.RIGHT) {
//            xPt+=0.125d;
//        } else if (dir == Direction.UP) {
//            yPt-=0.125d;
//        } else if (dir == Direction.DOWN) {
//            yPt+=0.125d;
//        }
//        glu.gluLookAt(
//                camera[0], camera[1], camera[2] + zPt,
//                -xPt, yPt, 0.0f,
//                0.0f, 1.0f, 0.0f
//                );
//        double thetaRad_ = Math.atan((xEye - xEyeBack)/320.0d);
//        double thetaRad_ = Math.atan((xEye - xEyeBack)/640.0d);
//        double thetaRad_ = Math.atan((xEye - xEyeBack)/640.0d);
//        if (!Double.toString(xEye - xEyeBack).equals("0.0")) {
//            System.out.println(thetaRad_ * 180.0d/ Math.PI);
//            System.out.println("x="+((camera[0]+xPt) * Math.cos(thetaRad_) - (camera[2] + zPt-1) * Math.sin(thetaRad_)));
//            System.out.println("z="+((camera[2] + zPt-1) * Math.cos(thetaRad_) + (camera[0]+xPt) * Math.sin(thetaRad_)));
//        }
        
//        if (!Double.toString(xEye - xEyeBack).equals("0.0"))
//        System.out.println(Math.atan((xEye - xEyeBack)/320.0d)*180.0d/Math.PI);
//        glu.gluLookAt(
//                camera[0]+xPt, camera[1]-yPt, camera[2] + zPt,
//                xPt , -yPt, zPt,
//                0.0, 1.0, 0.0
//                );
//        glu.gluLookAt(
//                camera[0]-xPt, camera[1]-yPt, camera[2] + zPt,
//                camera[0]-xPt + Math.sin(thetaRad), camera[1]-yPt, camera[2] + zPt - Math.cos(thetaRad),
//                0.0, 1.0, 0.0
//                );
        glu.gluLookAt(
            camera[0]+xPt, camera[1]-yPt, camera[2] + zPt,
            camera[0]+xPt - Math.sin(thetaRad), camera[1]-yPt + Math.cos(thetaRad)*Math.sin(phiRad), camera[2] + zPt - Math.cos(thetaRad)*Math.cos(phiRad),
            0.0, 1.0, 0.0
        );
//        glu.gluLookAt(
//                camera[0]+xPt, camera[1]-yPt, camera[2] + zPt,
//                (camera[0]+xPt) * Math.cos(thetaRad_) + (camera[2] + zPt-1) * Math.sin(thetaRad_), camera[1]-yPt, (camera[2] + zPt-1) * Math.cos(thetaRad_) - (camera[0]+xPt) * Math.sin(thetaRad_),
//                0.0, 1.0, 0.0
//                );
//        glu.gluLookAt(
//                camera[0]+xPt, camera[1]-yPt, camera[2] + zPt,
//                camera[0]+xPt + Math.sin(thetaRad_), camera[1]-yPt, camera[2] + zPt - Math.cos(thetaRad_),
//                0.0, 1.0, 0.0
//        );
//        if (moving) {
//            xPt = 
//        }
//        gl_.glRotated(-Math.atan(xEye - xEyeBack)*180/Math.PI, 0d, 1d, 0d);
//        System.out.println();
//        System.out.println(xEye - xEyeBack);
//        gl_.glRotated(angle, 0, 1, 0);

        double translate_[]; 
        translate_ = new double[] {
            Math.cos(angle*3.1415/180),0,-Math.sin(angle*3.1415/180),0,
            0,1,0,0,
            Math.sin(angle*3.1415/180),0,Math.cos(angle*3.1415/180),0,
            0,0,0,1,};
        gl_.glMultMatrixd(translate_, 0);
//        gl_.glRotated(-Math.atan(xEye - xEyeBack)*180/Math.PI, 0d, 1d, 0d);

        //draw red Sphere
        gl_.glColor3f(1.0f, 0.0f, 0.0f);
        glut.glutSolidSphere(1.0f, 20, 20);

        if (txt != null) {
//            gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);
//            gl_.glColor3f(1.0f, 1.0f, 1.0f);
//            gl.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//            gl.glPopAttrib();
            gl_.glBindTexture(GL2.GL_TEXTURE_2D, txt.getTextureObject(gl_));
            gl_.glBegin(GL2.GL_QUADS);
            gl_.glTexCoord2d(0,1);
//            gl.glVertex3d(1,-1,1);
            gl_.glVertex3d(-1,1,1);
            gl_.glTexCoord2d(0,0);
//            gl.glVertex3d(1,-1,-1);
            gl_.glVertex3d(-1,-1,1);
            gl_.glTexCoord2d(1,0);
//            gl.glVertex3d(-1,-1,-1);
            gl_.glVertex3d(1,-1,1);
            gl_.glTexCoord2d(1,1);
//            gl.glVertex3d(-1,-1,1);
            gl_.glVertex3d(1,1,1);
            gl_.glEnd();
        }
//        gl_.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);
//        gl_.glMatrixMode(GL2.GL_MODELVIEW );
//        gl_.glLoadIdentity();
//        gl_.glMatrixMode(GL2.GL_PROJECTION_MATRIX );
//        gl_.glPushMatrix();
//        gl_.glLoadIdentity();
        translate_ = new double[] {1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            2,0,0,1,};
//        gl_.glTranslated(2,0,0);
        gl_.glMultMatrixd(translate_, 0);
//        gl_.glPopMatrix();
        drawRocket(gl_, true);
        translate_ = new double[] {1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            -2,0,0,1,};
        gl_.glMultMatrixd(translate_, 0);
        translate_ = new double[] {
            Math.cos(angle*3.1415/180),0,-Math.sin(-angle*3.1415/180),0,
            0,1,0,0,
            Math.sin(-angle*3.1415/180),0,Math.cos(angle*3.1415/180),0,
            0,0,0,1,};
        gl_.glMultMatrixd(translate_, 0);
//        gl_.glRotatef(-angle, 0f, 1f, 0f);
//        gl_.glMatrixMode(GL2.GL_PROJECTION);
//        gl_.glMatrixMode(GL2.GL_PROJECTION);
//        gl_.glPushMatrix();                                 /* Push current projection matrix   */
//        gl_.glGetIntegerv(GL2.GL_VIEWPORT,viewport);            /* Get the current viewport size    */
//        gl_.glGetDoublev(GL2.GL_PROJECTION_MATRIX,translate, 0);  /* Get the projection matrix        */
//        gl_.glLoadIdentity();                               /* Reset the projection matrix      */
//        glu.gluPickMatrix(x,y,delX,delY,viewport);          /* Set the picking matrix           */
//        gl_.glMultMatrixd(translate, 0); 
//        gl_.glPushMatrix();
//        gl_.glLoadIdentity();
//        gl_.glGetDoublev(GL2.GL_PROJECTION_MATRIX, translate, 0);
//        gl_.glLoadIdentity();
        translate_ = new double[] {1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            2,0,0,1,}; 
//        gl_.glGetDoublev(GL2.GL_PROJECTION_MATRIX, translate, 0);
        gl_.glMultMatrixd(translate_, 0);
        translate_ = new double[] {1,0,0,0,
            0,0,1,0,
            0,-1,0,0,
            1,0,0,1,}; 
//        gl_.glGetDoublev(GL2.GL_PROJECTION_MATRIX, translate, 0);
        gl_.glMultMatrixd(translate_, 0);
//        gl_.glPopMatrix();
//        gl_.glTranslated(2,0,0); //je me déplace pour la 2ème roquette
//        gl_.glRotated(90,1,0,0);
        /*je vais tourner celle-là pour que son axe principal
        soit horizontal */
        drawRocket(gl_, false); //et je la dessine
//        angle += 0.1f;
        angle += 1f;
        angle %= 360f;
//        dir = null;
//        zPt = 0;
//        xEyeBack = xEye;
//        yEyeBack = yEye;
//        moving = false;
    }

    /* J'ai choisi de faire une fonction Dessiner Rocket.
    Je pourrai ainsi l'appeler plusieurs fois, et dans n'importe quelle
    position initiale du repère initial */
    void drawRocket(GL2 _gl, boolean _pushPop) {
        if (_pushPop) {
            _gl.glPushMatrix(); //pour que les transformations soient réversibles
        }

        GLUquadric params_ = glu.gluNewQuadric(); //création du quadrique
        glu.gluQuadricTexture(params_,true);

        _gl.glBindTexture(GL2.GL_TEXTURE_2D,top.getTextureObject(_gl)); //texture du haut
        glu.gluCylinder(params_,0.5,0,1.6,20,1); //cône 1

        _gl.glBindTexture(GL2.GL_TEXTURE_2D,middle.getTextureObject(_gl));
        _gl.glTranslated(0,0,-1.05); //je descends pour faire le 2ème cône
        glu.gluCylinder(params_,0.15,0.5,1.05,20,1); //cône 2

        _gl.glBindTexture(GL2.GL_TEXTURE_2D,bottom.getTextureObject(_gl));
        _gl.glTranslated(0,0,-0.25); //je descends enfin tout en bas (sur le schéma)
        glu.gluCylinder(params_,0.3,0.15,0.25,20,1); //cône 3

        //et à la même position je dessine le disque de sortie des flammes
        _gl.glBindTexture(GL2.GL_TEXTURE_2D,motor.getTextureObject(_gl));
        glu.gluDisk(params_,0,0.3,20,1); //disque 4

        glu.gluDeleteQuadric(params_); //je supprime le quadrique

        if (_pushPop) {
            _gl.glPopMatrix(); //hop je remets tout comme je l'ai trouvé
        }
    }

    @Override
    public void reshape(GLAutoDrawable _drawable, int _x, int _y, int _width,
            int _height) {
        GL2 gl_ = _drawable.getGL().getGL2();
        gl_.glViewport(_x, _y, _width, _height);

        gl_.glMatrixMode(GL2.GL_PROJECTION);
        gl_.glLoadIdentity();
        glu.gluPerspective(60.0f, ((double) _width)/((double) _height), 0.125f, 10.0f);

        gl_.glMatrixMode(GL2.GL_MODELVIEW);
    }

}
