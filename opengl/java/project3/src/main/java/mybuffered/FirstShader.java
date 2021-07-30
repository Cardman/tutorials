package mybuffered;
// This code example is created for educational purpose
// by Thorsten Thormaehlen (contact: www.thormae.de).
// It is distributed without any warranty.

import java.io.BufferedReader;
import java.io.FileReader;
import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;

import javax.swing.JFrame;

import com.jogamp.common.nio.Buffers;
import com.jogamp.opengl.GL3;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLCapabilities;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.GLProfile;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.util.FPSAnimator;

class Renderer {
 
  private enum VAOs {Triangle, numVAOs};
  private enum VBOs {TriangleAll, numVBOs};
  private int[] vaoID  = new int[VAOs.numVAOs.ordinal()];
  private int[] bufID = new int[VBOs.numVBOs.ordinal()];
  private int triangleVertNo = 0;
  private int progID = 0;
  private int vertID = 0;
  private int fragID = 0;
  private int vertexLoc = 0;
  private int colorLoc = 0;
  
  public void init(GLAutoDrawable d) {
    GL3 gl = d.getGL().getGL3(); // get the OpenGL 3 graphics context
    gl.glEnable(GL3.GL_DEPTH_TEST);
    
    setupShaders(d);
    
    // create a Vertex Array Objects (VAO)
    gl.glGenVertexArrays(VAOs.numVAOs.ordinal(), vaoID, 0);

    // generate a Vertex Buffer Object (VBO)
    gl.glGenBuffers(VBOs.numVBOs.ordinal(), bufID, 0);

    // binding the Triangle VAO
    gl.glBindVertexArray(vaoID[VAOs.Triangle.ordinal()]);

    float triangleVertexData[] = {
       0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      -0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
       0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    };
    triangleVertNo = 3;

    int floatItems = triangleVertNo *(3+4);
    FloatBuffer triangleVertexFB = Buffers.newDirectFloatBuffer(floatItems);
    triangleVertexFB.put(triangleVertexData);
    triangleVertexFB.flip();
    
    gl.glBindBuffer(GL3.GL_ARRAY_BUFFER, bufID[VBOs.TriangleAll.ordinal()]);
    gl.glBufferData(GL3.GL_ARRAY_BUFFER, triangleVertexFB.capacity()*Buffers.SIZEOF_FLOAT, 
                    triangleVertexFB, GL3.GL_STATIC_DRAW);
    
    int stride = (3+4)*Buffers.SIZEOF_FLOAT;
    int offset = 0;

    // position
    gl.glVertexAttribPointer(vertexLoc, 3, GL3.GL_FLOAT, false, stride, offset);
    gl.glEnableVertexAttribArray(vertexLoc);
    
    // color
    offset = 0 + 3*Buffers.SIZEOF_FLOAT;
    gl.glVertexAttribPointer(colorLoc, 4, GL3.GL_FLOAT, false, stride, offset);
    gl.glEnableVertexAttribArray(colorLoc);
    
  }
 
  public void  setupShaders(GLAutoDrawable d) {
    GL3 gl = d.getGL().getGL3(); // get the OpenGL 3 graphics context
    
    vertID = gl.glCreateShader(GL3.GL_VERTEX_SHADER);
    fragID = gl.glCreateShader(GL3.GL_FRAGMENT_SHADER);
    
    String[] vs = loadShaderSrc("./first.vert");
    String[] fs = loadShaderSrc("./first.frag");
    
    gl.glShaderSource(vertID, 1, vs, null, 0);
    gl.glShaderSource(fragID, 1, fs, null, 0);

    // compile the shader
    gl.glCompileShader(vertID);
    gl.glCompileShader(fragID);

    // check for errors
    printShaderInfoLog(d, vertID);
    printShaderInfoLog(d, fragID);

    // create program and attach shaders
    progID = gl.glCreateProgram();
    gl.glAttachShader(progID, vertID);
    gl.glAttachShader(progID, fragID);

    // "outColor" is a user-provided OUT variable
    // of the fragment shader.
    // Its output is bound to the first color buffer
    // in the framebuffer
    gl.glBindFragDataLocation(progID, 0, "outputColor");

    // link the program
    gl.glLinkProgram(progID);
    // output error messages
    printProgramInfoLog(d, progID);

    // "inputPosition" and "inputColor" are user-provided
    // IN variables of the vertex shader.
    // Their locations are stored to be used later with
    // glEnableVertexAttribArray()
    vertexLoc = gl.glGetAttribLocation(progID,"inputPosition");
    colorLoc = gl.glGetAttribLocation(progID, "inputColor");
  }
  
  private String[] loadShaderSrc(String name){
    StringBuilder sb = new StringBuilder();
    try{
       BufferedReader br = new BufferedReader(new FileReader(name));
       String line;
       while ((line = br.readLine())!=null){
          sb.append(line);
          sb.append('\n');
       }
       br.close();
    }
    catch (Exception e){
       e.printStackTrace();
    }
    return new String[]{sb.toString()};
  }
 
  private void printShaderInfoLog(GLAutoDrawable d, int obj) {
    GL3 gl = d.getGL().getGL3(); // get the OpenGL 3 graphics context
    IntBuffer infoLogLengthBuf = IntBuffer.allocate(1);
    int infoLogLength;
    gl.glGetShaderiv(obj, GL3.GL_INFO_LOG_LENGTH, infoLogLengthBuf);
    infoLogLength = infoLogLengthBuf.get(0);
    if (infoLogLength > 0) {
      ByteBuffer byteBuffer = ByteBuffer.allocate(infoLogLength);
      gl.glGetShaderInfoLog(obj, infoLogLength, infoLogLengthBuf, byteBuffer);
      for (byte b:byteBuffer.array()){
        System.err.print((char)b);
      }
    }
  }
  
  
  private void printProgramInfoLog(GLAutoDrawable d, int obj) {
    GL3 gl = d.getGL().getGL3(); // get the OpenGL 3 graphics context
    IntBuffer infoLogLengthBuf = IntBuffer.allocate(1);
    int infoLogLength;
    gl.glGetProgramiv(obj, GL3.GL_INFO_LOG_LENGTH, infoLogLengthBuf);
    infoLogLength = infoLogLengthBuf.get(0);
    if (infoLogLength > 0) {
      ByteBuffer byteBuffer = ByteBuffer.allocate(infoLogLength);
      gl.glGetProgramInfoLog(obj, infoLogLength, infoLogLengthBuf, byteBuffer);
      for (byte b:byteBuffer.array()){
        System.err.print((char)b);
      }
    }
  }
  
  public void resize(GLAutoDrawable d, int w, int h) {
    GL3 gl = d.getGL().getGL3(); // get the OpenGL 3 graphics context
    gl.glViewport(0, 0, w, h);
  }

  public void display(GLAutoDrawable d) {
    GL3 gl = d.getGL().getGL3();  // get the OpenGL >= 3 graphics context
    
    gl.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gl.glClear(GL3.GL_COLOR_BUFFER_BIT | GL3.GL_DEPTH_BUFFER_BIT);

    gl. glUseProgram(progID); 
    
    // bind Triangle VAO
    gl.glBindVertexArray(vaoID[VAOs.Triangle.ordinal()]);
    // render data
    gl.glDrawArrays(GL3.GL_TRIANGLES, 0, triangleVertNo);

    gl.glFlush();
  }
}

class MyGui extends JFrame implements GLEventListener {

  private Renderer renderer;

  public void createGUI() {
    setTitle("First Shader Example");
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    GLProfile glp = GLProfile.getDefault();
    GLCapabilities caps = new GLCapabilities(glp);
    GLCanvas canvas = new GLCanvas(caps);
    setSize(320, 320);

    getContentPane().add(canvas);
    final FPSAnimator ani = new FPSAnimator(canvas, 60, true);
    canvas.addGLEventListener(this);
    setVisible(true);
    renderer = new Renderer();

    ani.start();
  }

  @Override
  public void init(GLAutoDrawable d) {
    renderer.init(d);
  }

  @Override
  public void reshape(GLAutoDrawable d, int x, int y, int width, int height) {
    renderer.resize(d, width, height);
  }

  @Override
  public void display(GLAutoDrawable d) {
    renderer.display(d);
  }

  @Override
  public void dispose(GLAutoDrawable d) {
  }
}

public class FirstShader {
  public static void main(String[] args) {
    javax.swing.SwingUtilities.invokeLater(new Runnable() {
      @Override
	public void run() {
    	MyGui myGUI = new MyGui();
        myGUI.createGUI();
      }
    });
  }
}
