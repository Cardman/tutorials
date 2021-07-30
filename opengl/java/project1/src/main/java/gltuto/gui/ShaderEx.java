package gltuto.gui;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.nio.FloatBuffer;
import java.util.Arrays;

import com.jogamp.common.nio.Buffers;
import com.jogamp.opengl.GL;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GL3;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.util.Animator;

public final class ShaderEx extends GLCanvas implements GLEventListener {

    private int myIdentityShader;
    private final Animator animator = new Animator(this);
    private ShaderProgram shader;

    public ShaderEx() {
        addGLEventListener(this);
        animator.start();
    }

    @Override
    public void init(GLAutoDrawable _drawable) {
        GL3 gl_ = _drawable.getGL().getGL3();

        gl_.glPointSize(30);
        gl_.glClearColor(0.7f, 0.7f, 0, 1);
        // compile and link vertex and fragment shaders into
        // a "program" that resides in the OpenGL driver
        shader = new ShaderProgram(_drawable.getGL().getGL2());
 
        // do the heavy lifting of loading, compiling and linking
        // the two shaders into a usable shader program
//        shader.init("resources_gl/data/simple.vertex", "resources_gl/data/simple.fragment");        
        shader.init("resources_gl/data/myfile.vert", "resources_gl/data/myfile.frag");        
    }

    @Override
    public void dispose(GLAutoDrawable _drawable) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void display(GLAutoDrawable _drawable) {
        GL2 gl_ = _drawable.getGL().getGL2();
        // TODO Auto-generated method stub
        int vaoHandle_ = constructVertexArrayObject(gl_);
        gl_.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);
         
        // tell OpenGL to use the shader
        gl_.glUseProgram( shader.getProgramId() );
        // bind vertex and color data
        gl_.glBindVertexArray(vaoHandle_);
        gl_.glEnableVertexAttribArray(0); // VertexPosition
        gl_.glEnableVertexAttribArray(1); // VertexColor

        // draw VAO
        gl_.glDrawArrays(GL.GL_TRIANGLES, 0, 3);
        gl_.glEnd();
    }

    private int constructVertexArrayObject(GL2 _gl) {
        // create vertex data 
        float[] positionData_ = new float[] {
            0f,        0f,        0f,
            -1f,    0f,     0f,
            0f,        1f,        0f,
        };
 
        // create color data
        float[] colorData_ = new float[]{
            0f,            0f,            1f,
            1f,            0f,            0f,
            0f,            1f,            0f,
        };
 
        // convert vertex array to buffer
        FloatBuffer positionBuffer_ = Buffers.newDirectFloatBuffer(positionData_.length);
        positionBuffer_.put(positionData_);
        positionBuffer_.flip();
 
        // convert color array to buffer
        FloatBuffer colorBuffer_ = Buffers.newDirectFloatBuffer(colorData_.length);
        colorBuffer_.put(colorData_);
        colorBuffer_.flip();        
 
        // create vertex byffer object (VBO) for vertices
        int[] buffers_ = new int[1];
        _gl.glGenBuffers(1, buffers_, 0);
        int positionBufferHandle_ = buffers_[0];
        _gl.glBindBuffer(GL.GL_ARRAY_BUFFER, buffers_[0]);
//        _gl.glBufferData(GL.GL_ARRAY_BUFFER, positionBuffer, GL.GL_STATIC_DRAW);
        _gl.glBufferData(GL.GL_ARRAY_BUFFER, positionBuffer_.capacity(), positionBuffer_,GL.GL_STATIC_DRAW);
 
        // create VBO for color values
        buffers_ = new int[1];
        _gl.glGenBuffers(1, buffers_, 0);
        int colorBufferHandle_ = buffers_[0];
        _gl.glBindBuffer(GL.GL_ARRAY_BUFFER, buffers_[0]);
        //GL3.GL_ARRAY_BUFFER, data.capacity(), data, GL3.GL_STATIC_DRAW
        _gl.glBufferData(GL.GL_ARRAY_BUFFER, colorBuffer_.capacity(), colorBuffer_, GL.GL_STATIC_DRAW);
 
        // unbind VBO
        _gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);
 
        // create vertex array object (VAO)
        int[] vertexArrayObject_ = new int[1];
//        int vaoHandle = _gl.glGenVertexArrays();
        _gl.glGenVertexArrays(1, vertexArrayObject_, 0);
//        _gl.glBindVertexArray(vaoHandle);
        _gl.glBindVertexArray(vertexArrayObject_[0]);
        _gl.glEnableVertexAttribArray(0);
        _gl.glEnableVertexAttribArray(1);
 
        // assign vertex VBO to slot 0 of VAO
        _gl.glBindBuffer(GL.GL_ARRAY_BUFFER, positionBufferHandle_);
        _gl.glVertexAttribPointer(0, 3, GL.GL_FLOAT, false, 0, 0);
 
        // assign vertex VBO to slot 1 of VAO
        _gl.glBindBuffer(GL.GL_ARRAY_BUFFER, colorBufferHandle_);
        _gl.glVertexAttribPointer(1, 3, GL.GL_FLOAT, false, 0, 0);
 
        // unbind VBO
        _gl.glBindBuffer(GL.GL_ARRAY_BUFFER, 0);
 
        return vertexArrayObject_[0];
    }

    @Override
    public void reshape(GLAutoDrawable _drawable, int _x, int _y, int _width,
            int _height) {
        // TODO Auto-generated method stub
        
    }

    public static void main(String[] _args) {
//        SwingUtilities.invokeLater(new Runnable() {
//            @Override
//            public void run() {
//                JFrame jf = new JFrame();
//                jf.setSize(800,800);
//                jf.getContentPane().setLayout(new BorderLayout());
//                jf.getContentPane().add(new ShaderEx(), BorderLayout.CENTER);
//                jf.setVisible(true);
//                jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//            }
//        });
        byte[] one_ = loadFile("C:/Users/cardman/code_blocks/example2/verue/example.exe");
        byte[] two_ = loadFile("C:/Users/cardman/code_blocks/example2/bin/Release/example.exe");
        System.out.println(one_.length == two_.length);
        System.out.println(Arrays.equals(one_, two_));
    }

    public static byte[] loadFile(String _file) {
        try {
            File file_ = new File(_file);
            FileInputStream fis_ = new FileInputStream(file_);
            BufferedInputStream buff_ = new BufferedInputStream(fis_);
            long len_ = file_.length();
            int index_ = 0;
            byte[] bytes_ = new byte[(int) len_];
            while (true) {
                int read_ = buff_.read(bytes_, index_, (int) (len_ - index_));
                if (read_ == -1) {
                    break;
                }
                if (index_ == len_) {
                    break;
                }
                index_ += read_;
            }
            buff_.close();
            fis_.close();
            return bytes_;
        } catch (Exception _0) {
            _0.printStackTrace();
            return null;
        }
    }
}
