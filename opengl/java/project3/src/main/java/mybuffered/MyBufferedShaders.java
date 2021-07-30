package mybuffered;

import java.nio.FloatBuffer;

import com.jogamp.common.nio.Buffers;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.GLException;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.glu.GLU;
import com.jogamp.opengl.util.Animator;

public class MyBufferedShaders extends GLCanvas implements GLEventListener {

	private static final String BUFF_FRAG = "resources_gl/data/buff.frag";
    private static final String BUFF_VERT = "resources_gl/data/buff.vert";
 	private ShaderIds shaderFirst;
	private GLU glu = new GLU();

	private final Animator animator;

	private int progID = 0;
	private int bufID = 0;
	private int vertexLoc = 0;
	private int colorLoc = 0;
    public MyBufferedShaders() {
    	animator = new Animator(this);
        addGLEventListener(this);
        animator.start();
    }

	@Override
	public void init(GLAutoDrawable _drawable) {
		GL2 gl_ = _drawable.getGL().getGL2();
        gl_.glClearColor(0.0f,0.5f,0.0f,1.0f);
        gl_.glClearDepth(1.0);
        gl_.glDepthFunc(GL2.GL_LESS);
        gl_.glEnable(GL2.GL_DEPTH_TEST);
        gl_.glEnable(GL2.GL_TEXTURE_2D);
        //txtString
        shaderFirst = MyShadersUtil.loadShader(gl_,BUFF_VERT,BUFF_FRAG);
        if (shaderFirst == null) {
        	throw new GLException("Bad first shader");
        }
        progID = shaderFirst.getProgramId();
        gl_.glEnable(GL2.GL_FOG);
        gl_.glEnable(GL2.GL_LIGHTING);
        gl_.glEnable(GL2.GL_LIGHT0);
        gl_.glEnable(GL2.GL_NORMALIZE);
        gl_.glEnable(GL2.GL_COLOR_MATERIAL);
        vertexLoc = gl_.glGetAttribLocation(progID,"inputPosition");
        colorLoc = gl_.glGetAttribLocation(progID, "inputColor");
	}

	@Override
	public void dispose(GLAutoDrawable _drawable) {		
	}

	@Override
	public void display(GLAutoDrawable _drawable) {
		GL2 gl_ = _drawable.getGL().getGL2();
		gl_.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		gl_.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);

		int[] id_ = new int[1];
		gl_.glGenBuffers(1, id_, 0);
		bufID = id_[0];
		gl_.glUseProgram(progID);
//		System.out.println(bufID);
	    
	    float[] triangleVertexData = new float[]{ 
	      -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	      -1.0f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	      0.0f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	    };       
	    
	    FloatBuffer buff_ = Buffers.newDirectFloatBuffer(triangleVertexData);
	    int bytes_ = Buffers.SIZEOF_FLOAT;
	    gl_.glBindBuffer(GL2.GL_ARRAY_BUFFER, bufID);
	    gl_.glBufferData(GL2.GL_ARRAY_BUFFER, buff_.capacity() * bytes_,buff_ , GL2.GL_STATIC_DRAW);
	    
	    // position
	    int offset = 0;
	    int stride = (3+4)*bytes_;
	    gl_.glVertexAttribPointer(vertexLoc, 3, GL2.GL_FLOAT, false, stride, offset);
	    gl_.glEnableVertexAttribArray(vertexLoc);    
	    
	    // color
	    offset = 0 + 3*bytes_;
	    gl_.glVertexAttribPointer(colorLoc, 4, GL2.GL_FLOAT, false, stride, offset);
	    gl_.glEnableVertexAttribArray(colorLoc);
	    
	    gl_.glBindBuffer(GL2.GL_ARRAY_BUFFER, bufID);
	    gl_.glDrawArrays(GL2.GL_TRIANGLES, 0, 3);
	    gl_.glUseProgram(0);
	    gl_.glDeleteBuffers(1, id_, 0);
//	    gl_.gl
	}

	@Override
	public void reshape(GLAutoDrawable _drawable, int _x, int _y, int _width,
			int _height) {
		GL2 gl_ = _drawable.getGL().getGL2();
		// Perspective mode
		gl_.glMatrixMode(GL2.GL_PROJECTION);
		gl_.glLoadIdentity();

        glu.gluPerspective(75.0f,(float)640/(float)480,0.1f,100.0f);

        gl_.glMatrixMode(GL2.GL_MODELVIEW);
		
	}

}
