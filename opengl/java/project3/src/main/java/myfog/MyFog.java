package myfog;

import java.io.IOException;
import java.io.InputStream;

import myshaders.MyShadersUtil;
import myshaders.ShaderIds;

import com.jogamp.common.nio.Buffers;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.GLException;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.glu.GLU;
import com.jogamp.opengl.glu.GLUquadric;
import com.jogamp.opengl.util.Animator;
import com.jogamp.opengl.util.texture.TextureData;
import com.jogamp.opengl.util.texture.TextureIO;

public class MyFog extends GLCanvas implements GLEventListener {

	static final float BOX_SIZE = 7.0f; //The length of each side of the cube
	private static final String TEXT_FRAG = "resources_gl/data/text.frag";
    private static final String TEXT_VERT = "resources_gl/data/text.vert";
//    private static final String TEXTURE_RES = "resources_gl/vtr.bmp";
    private static final String TEXTURE_RES = "resources_gl/vtr.png";
	private static final String TEXTURE_RES_SEC = "resources_gl/texture.jpg";
	private ShaderIds ids;
	float _angle = 0;            //The rotation of the box
	int _textureId;
	int _textureIdSec;
	private float quadColours[] =
	    {
	        1, 0, 0, 1,
	        0, 0, 1, 1,
	        0, 0, 1, 1,
	        1, 0, 0, 1,
	    };

	GLU glu = new GLU();
    private final Animator animator = new Animator(this);

    public MyFog() {
    	addGLEventListener(this);
        animator.start();
    }

	//Makes the image into a texture, and returns the id of the texture
	int loadTexture(GL2 _gl, TextureData image) {
		int[] textureId = new int[1];
		_gl.glGenTextures(1, textureId, 0);
		_gl.glBindTexture(GL2.GL_TEXTURE_2D, textureId[0]);
		_gl.glTexImage2D(GL2.GL_TEXTURE_2D,
					 0,
					 GL2.GL_RGB,
					 image.getWidth(), image.getHeight(),
					 0,
					 GL2.GL_RGB,
					 GL2.GL_UNSIGNED_BYTE,
					 image.getBuffer());
		return textureId[0];
	}

	int loadTextureBis(GL2 _gl, TextureData image) {
		int[] textureId = new int[1];
		_gl.glGenTextures(1, textureId, 0);
		_gl.glBindTexture(GL2.GL_TEXTURE_2D, textureId[0]);
		_gl.glTexImage2D(GL2.GL_TEXTURE_2D,
					 0,
					 image.getInternalFormat(),
					 image.getWidth(), image.getHeight(),
					 0,
					 image.getPixelFormat(),
					 GL2.GL_UNSIGNED_BYTE,
					 image.getBuffer());
		return textureId[0];
	}

	@Override
	public void display(GLAutoDrawable _arg0) {
		GL2 gl_ = _arg0.getGL().getGL2();
		gl_.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);

		gl_.glMatrixMode(GL2.GL_MODELVIEW);
		gl_.glLoadIdentity();

		float fogColor[] = {0.5f, 0.5f, 0.5f, 1};
		gl_.glFogfv(GL2.GL_FOG_COLOR, fogColor, 0);
//		gl_.glFogi(GL2.GL_FOG_MODE, GL2.GL_LINEAR);
//		gl_.glFogf(GL2.GL_FOG_START, 10.0f);
//		gl_.glFogf(GL2.GL_FOG_END, 20.0f);
//		gl_.glFogf(GL2.GL_FOG_START, 20.0f);
//		gl_.glFogf(GL2.GL_FOG_END, 25.0f);
		gl_.glFogi(GL2.GL_FOG_MODE, GL2.GL_EXP);
		gl_.glFogf(GL2.GL_FOG_DENSITY, 0.5f);

		gl_.glTranslatef(0.0f, 0.0f, -20.0f);
//		gl_.glTranslatef(0.0f, 0.0f, 20.0f);
//		gl_.glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
//		glu.gluLookAt(0.0f, 0.0f, -20.0f,
//				0.0f, 0.0f, 0.0f,
//				1.0f, 0.0f, 0.0f);

		float ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
		gl_.glLightModelfv(GL2.GL_LIGHT_MODEL_AMBIENT, ambientLight, 0);

		float lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
//		float lightColor[] = {1f, 1f, 0f, 1.0f};
		float lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
		gl_.glLightfv(GL2.GL_LIGHT0, GL2.GL_DIFFUSE, lightColor, 0);
		gl_.glLightfv(GL2.GL_LIGHT0, GL2.GL_POSITION, lightPos, 0);

//		gl_.glRotatef(-_angle, 1.0f, 1.0f, 0.0f);
		gl_.glRotatef(-_angle, 0.5f, 0.5f, 0.0f);

		gl_.glUseProgram(ids.getProgramId());
		int attributeId_;// = gl_.glGetAttribLocation(ids.getProgramId(), "mycolor");
		attributeId_ = gl_.glGetAttribLocation(ids.getProgramId(), "mycolor");
		System.out.println(attributeId_);
		gl_.glBegin(GL2.GL_QUADS);

		//Top face
		gl_.glColor3f(1.0f, 1.0f, 0.0f);
//		gl_.glNormal3f(0.0f, 1.0f, 0.0f);
		gl_.glNormal3f(-1.0f, 1.0f, -1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
		gl_.glNormal3f(-1.0f, 1.0f, 1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glNormal3f(1.0f, 1.0f, 1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glNormal3f(1.0f, 1.0f, -1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

		//Bottom face
		gl_.glColor3f(1.0f, 0.0f, 1.0f);
//		gl_.glNormal3f(0.0f, -1.0f, 0.0f);
		gl_.glNormal3f(-1.0f, -1.0f, -1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
		gl_.glNormal3f(1.0f, -1.0f, -1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
		gl_.glNormal3f(1.0f, -1.0f, 1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glNormal3f(-1.0f, -1.0f, 1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

		//Left face
//		gl_.glNormal3f(-1.0f, 0.0f, 0.0f);
		gl_.glColor3f(0.0f, 1.0f, 1.0f);
		gl_.glNormal3f(-1.0f, -1.0f, -1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
		gl_.glNormal3f(-1.0f, -1.0f, 1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glColor3f(0.0f, 0.0f, 1.0f);
		gl_.glNormal3f(-1.0f, 1.0f, 1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glNormal3f(-1.0f, 1.0f, -1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

		//Right face
//		gl_.glNormal3f(1.0f, 0.0f, 0.0f);
		gl_.glColor3f(1.0f, 0.0f, 0.0f);
		gl_.glNormal3f(1.0f, -1.0f, -1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
		gl_.glNormal3f(1.0f, 1.0f, -1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
		gl_.glColor3f(0.0f, 1.0f, 0.0f);
		gl_.glNormal3f(1.0f, 1.0f, 1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glNormal3f(1.0f, -1.0f, 1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

		gl_.glEnd();

//		gl_.glUseProgram(ids.getProgramId());
//		int attributeId_;// = gl_.glGetAttribLocation(ids.getProgramId(), "mycolor");
//		attributeId_ = gl_.glGetAttribLocation(ids.getProgramId(), "mycolor");
//		System.out.println(attributeId_);
//		System.out.println(gl_.glGetError());
//		System.out.println(MyShadersUtil.getError(gl_, ids.getProgramId()));
		gl_.glEnable(GL2.GL_TEXTURE_2D);
		gl_.glActiveTexture(GL2.GL_TEXTURE0);
		gl_.glBindTexture(GL2.GL_TEXTURE_2D, _textureId);
		gl_.glTexParameteri(GL2.GL_TEXTURE_2D, GL2.GL_TEXTURE_MIN_FILTER, GL2.GL_LINEAR);
		gl_.glTexParameteri(GL2.GL_TEXTURE_2D, GL2.GL_TEXTURE_MAG_FILTER, GL2.GL_LINEAR);
		int loc_ = gl_.glGetUniformLocation(ids.getProgramId(), "mytex");
		gl_.glUniform1i(loc_, 0);
		gl_.glColor3f(1.0f, 1.0f, 1.0f);
		gl_.glBegin(GL2.GL_QUADS);

		//Front face
//		gl_.glNormal3f(0.0f, 0.0f, 1.0f);
		gl_.glTexCoord2f(0.0f, 0.0f);
		gl_.glNormal3f(-1.0f, -1.0f, 1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glTexCoord2f(1.0f, 0.0f);
		gl_.glNormal3f(1.0f, -1.0f, 1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glTexCoord2f(1.0f, 1.0f);
		gl_.glNormal3f(1.0f, 1.0f, 1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glTexCoord2f(0.0f, 1.0f);
		gl_.glNormal3f(-1.0f, 1.0f, 1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

		//Back face
//		gl_.glNormal3f(0.0f, 0.0f, -1.0f);
//		gl_.glBindTexture(GL2.GL_TEXTURE_2D, 0);
//		gl_.glBindTexture(GL2.GL_TEXTURE_2D, _textureIdSec);
//		gl_.glTexParameteri(GL2.GL_TEXTURE_2D, GL2.GL_TEXTURE_MIN_FILTER, GL2.GL_LINEAR);
//		gl_.glTexParameteri(GL2.GL_TEXTURE_2D, GL2.GL_TEXTURE_MAG_FILTER, GL2.GL_LINEAR);
//		loc_ = gl_.glGetUniformLocation(ids.getProgramId(), "mytex");
//		gl_.glUniform1i(loc_, 0);

		gl_.glTexCoord2f(0.0f, 0.0f);
		gl_.glNormal3f(-1.0f, -1.0f, -1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
		gl_.glTexCoord2f(1.0f, 0.0f);
		gl_.glNormal3f(-1.0f, 1.0f, -1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
		gl_.glTexCoord2f(1.0f, 1.0f);
		gl_.glNormal3f(1.0f, 1.0f, -1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
		gl_.glTexCoord2f(0.0f, 1.0f);
		gl_.glNormal3f(1.0f, -1.0f, -1.0f);
		gl_.glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);

		gl_.glEnd();
		gl_.glDisable(GL2.GL_TEXTURE_2D);
		gl_.glEnableClientState(GL2.GL_TEXTURE_COORD_ARRAY);
        gl_.glEnableClientState(GL2.GL_VERTEX_ARRAY);

		gl_.glEnable(GL2.GL_TEXTURE_2D);
		gl_.glActiveTexture(GL2.GL_TEXTURE0);
		gl_.glBindTexture(GL2.GL_TEXTURE_2D, _textureIdSec);
		gl_.glTexParameteri(GL2.GL_TEXTURE_2D, GL2.GL_TEXTURE_MIN_FILTER, GL2.GL_LINEAR);
		gl_.glTexParameteri(GL2.GL_TEXTURE_2D, GL2.GL_TEXTURE_MAG_FILTER, GL2.GL_LINEAR);
//		attributeId_ = gl_.glGetAttribLocation(ids.getProgramId(), "mycolor");
//		System.out.println(attributeId_);
//		System.out.println(gl_.glGetError());

//		gl_.glGetFragDataLocation(program, name)
		gl_.glEnableVertexAttribArray(attributeId_);
		gl_.glVertexAttribPointer(attributeId_,
                4,
                GL2.GL_FLOAT,
                true,
                0,
                Buffers.newDirectFloatBuffer(quadColours));
		loc_ = gl_.glGetUniformLocation(ids.getProgramId(), "mytex");
		gl_.glUniform1i(loc_, 0);
//		gl_.glColor3f(1.0f, 1.0f, 0.0f);
		//TODO
		gl_.glTexCoordPointer(2, GL2.GL_DOUBLE, 0, Buffers.newDirectDoubleBuffer(new double[]{0,0,1,0,1,1,0,1}));
		double[] vertices_ = new double[12];
        vertices_[0] = -BOX_SIZE / 2 + 7;
        vertices_[1] = -BOX_SIZE / 2;
        vertices_[2] = BOX_SIZE / 2;
        vertices_[3] = BOX_SIZE / 2 + 7;
        vertices_[4] = -BOX_SIZE / 2;
        vertices_[5] = BOX_SIZE / 2;
        vertices_[6] = BOX_SIZE / 2 + 7;
        vertices_[7] = BOX_SIZE / 2;
        vertices_[8] = BOX_SIZE / 2;
        vertices_[9] = -BOX_SIZE / 2 + 7;
        vertices_[10] = BOX_SIZE / 2;
        vertices_[11] = BOX_SIZE / 2;
        gl_.glVertexPointer(3, GL2.GL_DOUBLE, 0, Buffers.newDirectDoubleBuffer(vertices_));
        byte[] indices_ = new byte[4];
        indices_[1] = 1;
        indices_[2] = 2;
        indices_[3] = 3;
        gl_.glDrawElements(GL2.GL_QUADS, indices_.length, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(indices_));
        gl_.glDisableVertexAttribArray(attributeId_);
//        gl_.glColorPointer(4, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(quadColours));
//		gl_.glBegin(GL2.GL_QUADS);
//		gl_.glTexCoord2f(0.0f, 0.0f);
//		gl_.glNormal3f(-1.0f, -1.0f, 1.0f);
//		gl_.glVertex3f(-BOX_SIZE / 2 + 7, -BOX_SIZE / 2, BOX_SIZE / 2);
//		gl_.glTexCoord2f(1.0f, 0.0f);
//		gl_.glNormal3f(1.0f, -1.0f, 1.0f);
//		gl_.glVertex3f(BOX_SIZE / 2 + 7, -BOX_SIZE / 2, BOX_SIZE / 2);
//		gl_.glTexCoord2f(1.0f, 1.0f);
//		gl_.glNormal3f(1.0f, 1.0f, 1.0f);
//		gl_.glVertex3f(BOX_SIZE / 2 + 7, BOX_SIZE / 2, BOX_SIZE / 2);
//		gl_.glTexCoord2f(0.0f, 1.0f);
//		gl_.glNormal3f(-1.0f, 1.0f, 1.0f);
//		gl_.glVertex3f(-BOX_SIZE / 2 + 7, BOX_SIZE / 2, BOX_SIZE / 2);
//		gl_.glEnd();
		gl_.glColor3f(1.0f, 1.0f, 0.0f);
		gl_.glBegin(GL2.GL_TRIANGLES);
		gl_.glTexCoord2f(0.0f, 0.0f);
		gl_.glNormal3f(-1.0f, -1.0f, 1.0f);
		gl_.glVertex3f(-BOX_SIZE / 2 + 14, -BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glTexCoord2f(1.0f, 0.0f);
		gl_.glNormal3f(1.0f, -1.0f, 1.0f);
		gl_.glVertex3f(BOX_SIZE / 2 + 14, -BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glTexCoord2f(0.5f, 1.0f);
		gl_.glNormal3f(1.0f, 1.0f, 1.0f);
		gl_.glVertex3f(BOX_SIZE / 2 + 14, BOX_SIZE / 2, BOX_SIZE / 2);
		gl_.glEnd();
		gl_.glUseProgram(0);
		gl_.glPushMatrix();
		gl_.glTranslated(-7+1.75, 0, 0);
		GLUquadric params_ = glu.gluNewQuadric(); //création du quadrique
		glu.gluQuadricTexture(params_,true);
        glu.gluDisk(params_,0.875,1.75,40,1);
        gl_.glTranslated(-3.5, 0, 0);
		//glu.gluQuadricTexture(params_,true);
        glu.gluCylinder(params_,1.75,1.75,7,40,2);
//        glu.gluDeleteQuadric(params_); //je supprime le quadrique
        gl_.glTranslated(-3.5-1.75, 0, 0);
        glu.gluCylinder(params_,3.5,1.75,7,40,2);
        //glu.gluQuadricTexture(params_,true);
        glu.gluDeleteQuadric(params_); //je supprime le quadrique
        gl_.glPopMatrix();
		gl_.glDisable(GL2.GL_TEXTURE_2D);
//        gl_.glPushMatrix();
        gl_.glTranslated(0, -7+1.75, 0);
        gl_.glColor3d(1, 1, 0);
        gl_.glBegin(GL2.GL_TRIANGLE_FAN);
        gl_.glVertex3d(0, 0, 0);
        int nb_ = 40;
        indices_ = new byte[nb_+2];
        vertices_ = new double[(nb_+2)*3];
        indices_[0] = 0;
        vertices_[0] = 0;
        vertices_[1] = 0;
        //vertices_[2] = 0;
        double rx_ = 2;
        double ry_ = 1;
        double nbDeg_ = 360.0d / nb_;
        double rad_ = nbDeg_ * Math.PI / 180;
    	for (int i = 0; i <= nb_; i++) {
        	double radi_ = rad_ * i;
        	indices_[i+1] = (byte) (i+1);
        	vertices_[(i+1) * 3] = rx_ * Math.cos(radi_);
            vertices_[(i+1) * 3+1] = ry_ * Math.sin(radi_);
            //vertices_[(i+1) * 3+2] = 0;
        	gl_.glVertex3d(rx_ * Math.cos(radi_), ry_ * Math.sin(radi_), 0);
        }
        gl_.glEnd();
        gl_.glTranslated(0, -2, 0);

        gl_.glEnableClientState(GL2.GL_VERTEX_ARRAY);

        gl_.glVertexPointer(3, GL2.GL_DOUBLE, 0, Buffers.newDirectDoubleBuffer(vertices_));
        gl_.glDrawElements(GL2.GL_TRIANGLE_FAN, nb_+2, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(indices_));
        gl_.glDisableClientState(GL2.GL_VERTEX_ARRAY);
        gl_.glTranslated(0, -4, 0);

        gl_.glUseProgram(ids.getProgramId());
        gl_.glEnable(GL2.GL_TEXTURE_2D);
		gl_.glActiveTexture(GL2.GL_TEXTURE0);
		gl_.glBindTexture(GL2.GL_TEXTURE_2D, _textureIdSec);
        gl_.glEnableClientState(GL2.GL_TEXTURE_COORD_ARRAY);
        gl_.glEnableClientState(GL2.GL_VERTEX_ARRAY);
//        gl_.glTexCoordPointer(4, GL2.GL_DOUBLE, 0, Buffers.newDirectDoubleBuffer(new double[]{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}));
        gl_.glTexCoordPointer(2, GL2.GL_DOUBLE, 0, Buffers.newDirectDoubleBuffer(new double[]{0,0,1,0,1,1,0,1}));
        vertices_ = new double[12];
        vertices_[0] = -2;
        vertices_[1] = -2;
        vertices_[3] = 2;
        vertices_[4] = -2;
        vertices_[6] = 2;
        vertices_[7] = 2;
        vertices_[9] = -2;
        vertices_[10] = 2;
        gl_.glVertexPointer(3, GL2.GL_DOUBLE, 0, Buffers.newDirectDoubleBuffer(vertices_));
        indices_ = new byte[4];
        indices_[1] = 1;
        indices_[2] = 2;
        indices_[3] = 3;
        gl_.glDrawElements(GL2.GL_QUADS, indices_.length, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(indices_));
        gl_.glDisableClientState(GL2.GL_TEXTURE_COORD_ARRAY);
        gl_.glDisableClientState(GL2.GL_VERTEX_ARRAY);
        gl_.glBindTexture(GL2.GL_TEXTURE_2D, 0);
        gl_.glDisable(GL2.GL_TEXTURE_2D);
        gl_.glTranslated(0, 14-1.5+4, 0);
        gl_.glUseProgram(0);
        drawEllipsoid(gl_, 3.5, 2.5, 1.5, 40, 40);
		_angle += 1.0f;
		if (_angle > 360) {
			_angle -= 360;
		}
	}

	void drawEllipsoid(GL2 _gl,double a, double b, double c, int lats, int longs)
	{
	    int i, j;
	    _gl.glBegin(GL2.GL_QUAD_STRIP);
        for(i = 0; i <= lats; i++)
	    {
	    	double lat0 = Math.PI * (-0.5f + (double) (i - 1) / lats);
	        double z0  = Math.sin(lat0);
	        double zr0 = Math.cos(lat0);
	        
	        double lat1 = Math.PI * (-0.5f + (double) i / lats);
	        double z1 = Math.sin(lat1);
	        double zr1 = Math.cos(lat1);
	        //_gl.glBegin(GL2.GL_QUAD_STRIP);
	        for(j = 0; j <= longs; j++)
	        {
	        	double lng = 2 * Math.PI * (double) (j - 1) / longs;
	            double x = Math.cos(lng);
	            double y = Math.sin(lng);
	            
	            _gl.glNormal3d(x * zr0, y * zr0, z0);
	            _gl.glVertex3d(x * zr0 * a, y * zr0 * b, z0 * c);
	            _gl.glNormal3d(x * zr1, y * zr1, z1);
	            _gl.glVertex3d(x * zr1 * a, y * zr1 * b, z1 * c);
	        }
	        //_gl.glEnd();
	    }
        _gl.glEnd();
	}

	@Override
	public void dispose(GLAutoDrawable _arg0) {
	}

	@Override
	public void init(GLAutoDrawable _arg0) {
		GL2 gl_ = _arg0.getGL().getGL2();
		gl_.glClearColor(0.5f, 0.5f, 0.5f, 1);
		//gl_.getClass() ==  jogamp.opengl.gl4.GL4bcImpl.class
//		gl_.glClearDepth(1.0);
//        gl_.glDepthFunc(GL2.GL_LESS);
		gl_.glEnable(GL2.GL_DEPTH_TEST);
		gl_.glEnable(GL2.GL_LIGHTING);
		gl_.glEnable(GL2.GL_LIGHT0);
		gl_.glEnable(GL2.GL_NORMALIZE);
		gl_.glEnable(GL2.GL_COLOR_MATERIAL);
		gl_.glEnable(GL2.GL_FOG);
//		gl_.glClearColor(0.5f, 0.5f, 0.5f, 1);

		InputStream inputStream_ = ClassLoader.getSystemResourceAsStream(TEXTURE_RES);
		TextureData txtData;
		try {
//			txtData = TextureIO.newTextureData(gl_.getGLProfile(), inputStream_, true, "bmp");
			txtData = TextureIO.newTextureData(gl_.getGLProfile(), inputStream_, true, "png");
//			_textureId = loadTexture(gl_,txtData);
			_textureId = loadTextureBis(gl_,txtData);
		} catch (IOException e) {
			throw new GLException(e);
		}
		inputStream_ = ClassLoader.getSystemResourceAsStream(TEXTURE_RES_SEC);
		try {
			txtData = TextureIO.newTextureData(gl_.getGLProfile(), inputStream_, true, "jpg");
			_textureIdSec = loadTextureBis(gl_,txtData);
		} catch (IOException e) {
			throw new GLException(e);
		}
		ids = MyShadersUtil.loadShader(gl_, TEXT_VERT, TEXT_FRAG);
		if (ids == null) {
			throw new GLException("Bad shader");
		}
//		Image* image = loadBMP("vtr.bmp");
	}

	@Override
	public void reshape(GLAutoDrawable _drawable, int _x, int _y, int _width,
            int _height) {
		GL2 gl_ = _drawable.getGL().getGL2();
		gl_.glViewport(0, 0, _width, _height);
		gl_.glMatrixMode(GL2.GL_PROJECTION);
		gl_.glLoadIdentity();
//		glu.gluPerspective(45.0, (float)_width / (float)_height, 1.0, 200.0);
		glu.gluPerspective(75.0, (float)_width / (float)_height, 1.0, 200.0);
	}

}
