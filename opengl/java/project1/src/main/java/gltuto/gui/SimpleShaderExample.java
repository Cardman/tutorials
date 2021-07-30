package gltuto.gui;

import java.awt.BorderLayout;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.glu.GLU;
import com.jogamp.opengl.util.Animator;

public final class SimpleShaderExample extends GLCanvas implements GLEventListener, Runnable {

    private boolean updateUniformVars = true;
    private int vertexShaderProgram;
    private int fragmentShaderProgram;
    private int shaderprogram;
    private final Animator animator = new Animator(this);
    private float xCoords = -2;
    private float yCoords = -2;
    private float height = 4;
    private float width = 4;
    private int iterations = 255;
    private float[] couleurSec = {0.0f,255.0f,255.0f};
    private float[] couleur = {255.0f,255.0f,0.0f};
    private float[] couleurTwo = {255.0f,255.0f,0.0f};
 // Déclaration des points de notre cube
//    private float cubeVertices[] =
//    {
//        // Face de devant
//        1,1,1,
//        -1,1,1,
//        -1,-1,1,
//        1,-1,1,
//
//        1, 1, -1,
//        -1, 1, -1,
//
//        -1, -1, -1,
//        1, -1, -1,
//    };
//
//    private float cubeColours[] =
//    {
//        1, 0, 0,
//        0, 1, 0,
//        0, 1, 0,
//        1, 0, 0,
//
//        0, 0, 1,
//        1, 1, 0,
//
//        1, 1, 0,
//        0, 0, 1,
//    };
//
//    private int cubeIndices[] =
//    {
//        0, 1, 2, 3,
//        0, 4, 7, 3,
//        4, 5, 6, 7,
//        1, 2, 6, 5,
//        2, 3, 7, 6,
//        0, 1, 5, 4
//    };
//    private GLUT glut = new GLUT();
//    private GLU glu = new GLU();
//    private float camera[] = {0f, 0f, 5f};

    public SimpleShaderExample() {
        addGLEventListener(this);
        animator.start();
    }

    @Override
    public void init(GLAutoDrawable _drawable) {
        GL2 gl_ = _drawable.getGL().getGL2();

        // Enable VSync
        gl_.setSwapInterval(1);
        gl_.glShadeModel(GL2.GL_FLAT);
        try {
            attachShaders(gl_);
        } catch (Exception e) {
            e.printStackTrace();
        }
        updateUniformVars(gl_);
//        gl.glVertexPointer(3, GL2.GL_FLOAT, 0, FloatBuffer.wrap(cubeVertices));
    }

    private String[] loadShaderSrc(String _name){
        StringBuilder sb_ = new StringBuilder();
        try{
            InputStream is_ = ClassLoader.getSystemResourceAsStream(_name);
            BufferedReader br_ = new BufferedReader(new InputStreamReader(is_));
            String line_;
            while ((line_ = br_.readLine())!=null){
                sb_.append(line_);
                sb_.append('\n');
            }
            is_.close();
        } catch (Exception e){
            e.printStackTrace();
        }
//        System.out.println("Shader is "+sb.toString());
        return new String[]{sb_.toString()};
    }

    private void attachShaders(GL2 _gl) throws Exception {
        vertexShaderProgram = _gl.glCreateShader(GL2.GL_VERTEX_SHADER);
        fragmentShaderProgram = _gl.glCreateShader(GL2.GL_FRAGMENT_SHADER);

        String[] vsrc_ = new String[]{"uniform float mandel_x;\n" +
                "uniform float mandel_y;\n" +
                "uniform float mandel_width;\n" +
                "uniform float mandel_height; \n" +
                "uniform float mandel_iterations;\n" +
                "\n" +
                "void main()\n" +
                "{\n" +
                "\tgl_TexCoord[0] = gl_MultiTexCoord0;\n" +
                "\tgl_Position = ftransform();\n" +
                "}",};
        vsrc_ = loadShaderSrc("resources_gl/file.vert");
        vsrc_ = loadShaderSrc("resources_gl/data/simple.vert");
        _gl.glShaderSource(vertexShaderProgram, 1, vsrc_, null, 0);
        _gl.glCompileShader(vertexShaderProgram);

        String[] fsrc_ = new String[]{"uniform float mandel_x;\n" +
                "uniform float mandel_y;\n" +
                "uniform float mandel_width;\n" +
                "uniform float mandel_height; \n" +
                "uniform float mandel_iterations;\n" +
                "\n" +
                "float calculateMandelbrotIterations(float x, float y) {\n" +
                "\tfloat xx = 0.0;\n" +
                "    float yy = 0.0;\n" +
                "    float iter = 0.0;\n" +
                "    while (xx * xx + yy * yy <= 4.0 && iter<mandel_iterations) {\n" +
                "        float temp = xx*xx - yy*yy + x;\n" +
                "        yy = 2.0*xx*yy + y;\n" +
                "\n" +
                "        xx = temp;\n" +
                "\n" +
                "        iter ++;\n" +
                "    }\n" +
                "    return iter;\n" +
                "}\n" +
                "\n" +
                "vec4 getColor(float iterations) {\n" +
                "\tfloat oneThirdMandelIterations = mandel_iterations/3.0;\n" +
                "\tfloat green = iterations/oneThirdMandelIterations;\n" +
                "\tfloat blue = (iterations-1.3*oneThirdMandelIterations)/oneThirdMandelIterations;\n" +
                "\tfloat red = (iterations-2.2*oneThirdMandelIterations)/oneThirdMandelIterations;\n" +
                "\treturn vec4(red,green,blue,1.0);\n" +
                "}\n" +
                "\n" +
                "void main()\n" +
                "{\n" +
                "\tfloat x = mandel_x+gl_TexCoord[0].x*mandel_width;\n" +
                "\tfloat y = mandel_y+gl_TexCoord[0].y*mandel_height;\n" +
                "\tfloat iterations = calculateMandelbrotIterations(x,y);\n" +
                "\tgl_FragColor = getColor(iterations);\n" +
                "}",};
        fsrc_ = loadShaderSrc("resources_gl/file.frag");
        fsrc_ = loadShaderSrc("resources_gl/data/simple.frag");
        _gl.glShaderSource(fragmentShaderProgram, 1, fsrc_, null, 0);
        _gl.glCompileShader(fragmentShaderProgram);

        shaderprogram = _gl.glCreateProgram();
        _gl.glAttachShader(shaderprogram, vertexShaderProgram);
        _gl.glAttachShader(shaderprogram, fragmentShaderProgram);
        _gl.glLinkProgram(shaderprogram);
        _gl.glValidateProgram(shaderprogram);
        IntBuffer intBuffer_ = IntBuffer.allocate(1);
        _gl.glGetProgramiv(shaderprogram, GL2.GL_LINK_STATUS,intBuffer_);
        if (intBuffer_.get(0)!=1){
            _gl.glGetProgramiv(shaderprogram, GL2.GL_INFO_LOG_LENGTH,intBuffer_);
            int size_ = intBuffer_.get(0);
            System.err.println("Program link error: ");
            if (size_>0){
                ByteBuffer byteBuffer_ = ByteBuffer.allocate(size_);
                _gl.glGetProgramInfoLog(shaderprogram, size_, intBuffer_, byteBuffer_);
                for (byte b:byteBuffer_.array()){
                    System.err.print((char)b);
                }
            } else {
                System.out.println("Unknown");
            }
            //             System.exit(1);
        }
        _gl.glUseProgram(shaderprogram);
    }

    @Override
    public void reshape(GLAutoDrawable _drawable, int _x, int _y, int _width, int _height) {
        GL2 gl_ = _drawable.getGL().getGL2();
        GLU glu_ = new GLU();
        int height_ = _height;

        if (height_ <= 0) { // avoid a divide by zero error!

            height_ = 1;
        }
//        float h_ = (float) _width / (float) _height;
        gl_.glViewport(0, 0, _width, height_);
        gl_.glMatrixMode(GL2.GL_PROJECTION);
        gl_.glLoadIdentity();
        glu_.gluOrtho2D(0, 1, 0, 1);
        gl_.glMatrixMode(GL2.GL_MODELVIEW);
        gl_.glLoadIdentity();
    }



    @Override
    public void display(GLAutoDrawable _drawable) {
        GL2 gl_ = _drawable.getGL().getGL2();
//        gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);

//        if (updateUniformVars){
//            updateUniformVars(gl);
//        }

        // Reset the current matrix to the "identity"
//        gl.glLoadIdentity();
//        glu.gluLookAt(
//                camera[0], camera[1], camera[2],
//                0, 0, 0.0f,
//                0.0f, 1.0f, 0.0f);
//
//        gl.glColor3f(1.0f, 0.0f, 0.0f);
//        glut.glutSolidSphere(1.0f, 20, 20);
//        gl.glDrawElements(GL2.GL_QUADS, 24, GL2.GL_UNSIGNED_BYTE, IntBuffer.wrap(cubeIndices));
        // Draw A Quad
        gl_.glBegin(GL2.GL_QUADS);
//        gl.glColor3f(1.0f, 0.0f, 0.0f);
        //{
//            gl.glColor4f(255, 0, 255, 255);
        gl_.glTexCoord2f(0.0f, 1.0f);
//        gl_.glVertexAttrib
        gl_.glVertex3f(0.0f, 1.0f, 1.0f);  // Top Left
        gl_.glTexCoord2f(1.0f, 1.0f);
        gl_.glVertex3f(1.0f, 1.0f, 1.0f);   // Top Right
//            gl.glColor4f(255, 255, 0, 255);
        gl_.glTexCoord2f(1.0f, 0.0f);
        gl_.glVertex3f(1.0f, 0.0f, 1.0f);  // Bottom Right
        gl_.glTexCoord2f(0.0f, 0.0f);
        gl_.glVertex3f(0.0f, 0.0f, 1.0f); // Bottom Left
        //}
        // Done Drawing The Quad
        gl_.glEnd();

        // Flush all drawing operations to the graphics card
        gl_.glFlush();
    }

    private void updateUniformVars(GL2 _gl) {
        int mandelX_ = _gl.glGetUniformLocation(shaderprogram, "mandel_x");
        int mandelY_ = _gl.glGetUniformLocation(shaderprogram, "mandel_y");
        int mandelWidth_ = _gl.glGetUniformLocation(shaderprogram, "mandel_width");
        int mandelHeight_ = _gl.glGetUniformLocation(shaderprogram, "mandel_height");
        int mandelIterations_ = _gl.glGetUniformLocation(shaderprogram, "mandel_iterations");
        int mandelCouleur_ = _gl.glGetUniformLocation(shaderprogram, "mandel_couleur");
        int couleurSec_ = _gl.glGetUniformLocation(shaderprogram, "couleur");
        int couleurSec2_ = _gl.glGetAttribLocation(shaderprogram, "couleur2");
//        assert(mandel_x!=-1);
//        assert(mandel_y!=-1);
//        assert(mandel_width!=-1);
//        assert(mandel_height!=-1);
//        assert(mandel_iterations!=-1);

        _gl.glUniform1f(mandelX_, xCoords);
        _gl.glUniform1f(mandelY_, yCoords);
        _gl.glUniform1f(mandelWidth_, width);
        _gl.glUniform1f(mandelHeight_, height);
        _gl.glUniform1f(mandelIterations_, iterations);
        _gl.glUniform3f(couleurSec_, couleurSec[0], couleurSec[1], couleurSec[2]);
        _gl.glUniform3f(couleurSec2_, couleurTwo[0], couleurTwo[1], couleurTwo[2]);
        _gl.glUniform3f(mandelCouleur_, couleur[0], couleur[1], couleur[2]);
        _gl.glEnableVertexAttribArray(couleurSec2_);
//        errorState = glGetError();

//        gl.glVertexAttribPointer(couleurSec2_,
//                              3,
//                              GL2.GL_FLOAT,
//                              true,
//                              0,
//                              FloatBuffer.wrap(cubeColours));

    }

    public void displayChanged(GLAutoDrawable _drawable, boolean _modeChanged, boolean _deviceChanged) {
    }

    public static void main(String[] _args) {
        SwingUtilities.invokeLater(new SimpleShaderExample());
    }

    @Override
    public void dispose(GLAutoDrawable _drawable) {
        // TODO Auto-generated method stub

    }

    @Override
	public void run() {
        JFrame jf_ = new JFrame();
        jf_.setSize(800,800);
        jf_.getContentPane().setLayout(new BorderLayout());
        jf_.getContentPane().add(this, BorderLayout.CENTER);
        jf_.setVisible(true);
        jf_.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}

