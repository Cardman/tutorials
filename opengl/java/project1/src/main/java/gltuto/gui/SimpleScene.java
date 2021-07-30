package gltuto.gui;

import java.awt.BorderLayout;
import java.nio.FloatBuffer;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

import com.jogamp.opengl.GL3;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.util.Animator;

public final class SimpleScene extends GLCanvas implements GLEventListener, Runnable {

    private GL3 gl;
    private final Animator animator = new Animator(this);
    private int myIdentityShader;

    private String vertexShader = "#version 130                                                         \n" +
            "in vec4 position;                                                  \n" +
            "void main(void)                                                    \n" + 
            "{                                                                  \n" + 
            "    gl_Position = position;                                        \n" +
            "}                                                                  \n";

    private String fragmentShader = "#version 130                                                       \n" +
            "out vec4 vFragColor;                                               \n" +
            "void main(void)                                                    \n" + 
            "{                                                                  \n" + 
            "    vFragColor = vec4(0.0, 0.8, 1.0, 1.0);                         \n" +
            "}                                                                  \n";
    private int[] vertexArrayObject = new int[1];


    public SimpleScene() {
        addGLEventListener(this);
        animator.start();
    }

    @Override
    public void display(GLAutoDrawable _drawable) {
        gl.glClear(GL3.GL_COLOR_BUFFER_BIT);

        gl.glUseProgram(myIdentityShader);
        gl.glDrawArrays(GL3.GL_POINTS, 0, 3);
    }
    @Override
    public void dispose(GLAutoDrawable _drawable) {
        gl.glDeleteProgram(myIdentityShader);
        gl.glDeleteVertexArrays(1, vertexArrayObject, 0);
    }

    @Override
    public void init(GLAutoDrawable _drawable) {
        gl = _drawable.getGL().getGL3();

        try {
            myIdentityShader = createShaderProgram();
        } catch (Exception e) {
            e.printStackTrace();
            return;
        }

        gl.glPointSize(30);
        gl.glClearColor(0.7f, 0, 0, 1);

        float[] floatData_ = {
            0.25f, -0.25f, 0.5f, 1.0f,
            -0.25f, -0.25f, 0.5f, 1.0f,
            0.25f, 0.25f, 0.5f, 1.0f,
        };

        FloatBuffer data_ = FloatBuffer.allocate(3 * 4); 
        for (int i=0;i<12;i++) {
            data_.put(floatData_[i]);
//            data = (FloatBuffer) data.flip();
        }
        data_.flip();
        gl.glGenVertexArrays(1, vertexArrayObject, 0);
        gl.glBindVertexArray(vertexArrayObject[0]);

        int[] buffers_ = new int[1];
        gl.glGenBuffers(1, buffers_, 0);
        gl.glBindBuffer(GL3.GL_ARRAY_BUFFER, buffers_[0]);
        gl.glBufferData(GL3.GL_ARRAY_BUFFER, data_.capacity(), data_, GL3.GL_STATIC_DRAW);

        gl.glVertexAttribPointer(2, 4, GL3.GL_FLOAT, false, 0, 0);
        gl.glEnableVertexAttribArray(2);
    }

    @Override
    public void reshape(GLAutoDrawable _drawable, int _arg1, int _arg2, int _arg3,
            int _arg4) {
        // TODO Add reshape code

    }

    private int createShaderProgram() throws Exception {
        int hVertexShader_;
        int hFragmentShader_;
        int hShaderProgram_;
        int[] successTest_ = new int[] {1};

        hVertexShader_ = gl.glCreateShader(GL3.GL_VERTEX_SHADER);
        hFragmentShader_ = gl.glCreateShader(GL3.GL_FRAGMENT_SHADER);

        gl.glShaderSource(hVertexShader_, 1, new String[] {vertexShader}, null);
        gl.glShaderSource(hFragmentShader_, 1, new String[] {fragmentShader}, null);

        gl.glCompileShader(hVertexShader_);
        gl.glCompileShader(hFragmentShader_);

        gl.glGetShaderiv(hVertexShader_, GL3.GL_COMPILE_STATUS, successTest_, 0);
        if (successTest_[0] == 0) {
            byte[] infoLog_ = new byte[1024];
            gl.glGetShaderInfoLog(hVertexShader_, 1024, null, 0, infoLog_, 0);
            gl.glDeleteShader(hVertexShader_);
            gl.glDeleteShader(hFragmentShader_);
            throw new Exception("Vertex shader compilation failed with: " + new String(infoLog_));
        }
        gl.glGetShaderiv(hFragmentShader_, GL3.GL_COMPILE_STATUS, successTest_, 0);
        if (successTest_[0] == 0) {
            byte[] infoLog_ = new byte[1024];
            gl.glGetShaderInfoLog(hFragmentShader_, 1024, null, 0, infoLog_, 0);
            gl.glDeleteShader(hVertexShader_);
            gl.glDeleteShader(hFragmentShader_);
            throw new Exception("Fragment shader compilation failed with: " + new String(infoLog_));
        }

        hShaderProgram_ = gl.glCreateProgram();
        gl.glAttachShader(hShaderProgram_, hVertexShader_);
        gl.glAttachShader(hShaderProgram_, hFragmentShader_);

        gl.glBindAttribLocation(hShaderProgram_, 2, "position");

        gl.glLinkProgram(hShaderProgram_);

        gl.glGetProgramiv(hShaderProgram_, GL3.GL_LINK_STATUS, successTest_, 0);
        if (successTest_[0] == 0) {
            byte[] infoLog_ = new byte[1024];
            gl.glGetProgramInfoLog(hShaderProgram_, 1024, null, 0, infoLog_, 0);
            gl.glDeleteProgram(hShaderProgram_);
            throw new Exception("Shader linking failed with: " + new String(infoLog_));
        }

        gl.glDeleteShader(hVertexShader_);
        gl.glDeleteShader(hFragmentShader_);

        return hShaderProgram_;

    }

    public static void main(String[] _args) {
        SwingUtilities.invokeLater(new SimpleScene());

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
