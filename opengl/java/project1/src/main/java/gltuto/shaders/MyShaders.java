package gltuto.shaders;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;
import java.util.HashMap;

import com.jogamp.common.nio.Buffers;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GL3;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.GLException;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.glu.GLU;
import com.jogamp.opengl.util.Animator;
import com.jogamp.opengl.util.texture.Texture;
import com.jogamp.opengl.util.texture.TextureData;
import com.jogamp.opengl.util.texture.TextureIO;

public class MyShaders extends GLCanvas implements GLEventListener {
    private static final String UNIFORM_TEXTURE = "mytex";
	private static final String ATTRIBUTE_COLOUR_2 = "couleur2";
	private static final String ATTRIBUTE_COLOUR = "couleur";
	private static final String TEXTURE_RES = "resources_gl/avatar.jpg";
	private static final String QUAD_FRAG = "resources_gl/data/quad.frag";
    private static final String QUAD_VERT = "resources_gl/data/quad.vert";
    private static final String SIMPLE_FRAG = "resources_gl/data/simple.frag";
    private static final String SIMPLE_VERT = "resources_gl/data/simple.vert";
    private static final String SIMPLE_VERT_BIS = "resources_gl/data/simplebis.vert";
    private static int _rotationAngle_;
    private float cubeVertices[] =
        {
            // Face de devant
            1,1,1,
            -1,1,1,
            -1,-1,1,
            1,-1,1,

            1, 1, -1,
            -1, 1, -1,

            -1, -1, -1,
            1, -1, -1,
        };

    private float cubeVerticesBis[] =
        {
            // Face de devant
            1,1,4,
            -1,1,4,
            -1,-1,4,
            1,-1,4,

            1, 1, 2,
            -1, 1, 2,

            -1, -1, 2,
            1, -1, 2,
        };

    private float quadVertices[] =
        {
            // Face de devant
            3,1,1,
            1,1,1,
            1,-1,1,
            3,-1,1,
        };

    private float cubeColours[] =
        {
            1, 0, 0,
            0, 1, 0,
            0, 1, 0,
            1, 0, 0,

            0, 0, 1,
            1, 1, 0,

            1, 1, 0,
            0, 0, 1,
        };

    private byte cubeIndices[] =
        {
            0, 1, 2, 3,
            0, 4, 7, 3,
            4, 5, 6, 7,
            1, 2, 6, 5,
            2, 3, 7, 6,
            0, 1, 5, 4,
        };

    private byte quadIndices[] =
        {
            0, 1, 2, 3,
        };

    private HashMap<String,Integer> verticesId = new HashMap<String,Integer>();
    private HashMap<String,Integer> fragmentsId = new HashMap<String,Integer>();
    private HashMap<String,Integer> programsId = new HashMap<String,Integer>();
    private int shaderOne;
    private int shaderTwo;
    private int shaderThree;

    private int attributeId;

    private Texture txt;
    private TextureData txtData;
    private int txtId;
    private GLU glu = new GLU();
    private final Animator animator = new Animator(this);

    public MyShaders() {
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
        try {
            InputStream inputStream_ = null;
            inputStream_ = ClassLoader.getSystemResourceAsStream(TEXTURE_RES);
            txt = TextureIO.newTexture(inputStream_, true, TextureIO.JPG);
            txtId = txt.getTextureObject();
            inputStream_ = ClassLoader.getSystemResourceAsStream(TEXTURE_RES);
            txtData = TextureIO.newTextureData(gl_.getGLProfile(), inputStream_, true, TextureIO.JPG);
//            gl_.glGenerateMipmap(GL2.GL_TEXTURE_2D);
        } catch (Exception _0) {
            throw new GLException(_0);
        }
        shaderOne = loadShader(gl_,SIMPLE_VERT,SIMPLE_FRAG);
        if (shaderOne <= 0) {
        	throw new GLException("Bad first shader");
        }
        shaderTwo = loadShader(gl_,SIMPLE_VERT_BIS,SIMPLE_FRAG);
        if (shaderTwo <= 0) {
        	throw new GLException("Bad second shader");
        }
        shaderThree = loadShader(gl_,QUAD_VERT,QUAD_FRAG);
        if (shaderThree <= 0) {
        	throw new GLException("Bad third shader");
        }
        gl_.glEnable(GL2.GL_FOG);
        gl_.glEnable(GL2.GL_LIGHTING);
        gl_.glEnable(GL2.GL_LIGHT0);
        gl_.glEnable(GL2.GL_NORMALIZE);
        gl_.glEnable(GL2.GL_COLOR_MATERIAL);
//        gl_.glFogf(GL2.GL_FOG_DENSITY, 0.5f);
    }

    public static byte[] resourceFile(String _file) {
        ClassLoader classLoader_;
        classLoader_ = ClassLoader.getSystemClassLoader();
        URL url_ = classLoader_.getResource(_file);
        URLConnection connect_ = null;
        InputStream inputStream_ = null;
        BufferedInputStream buff_ = null;
        try {
            connect_ = url_.openConnection();
            inputStream_ = connect_.getInputStream();
            buff_ = new BufferedInputStream(inputStream_);
            int len_ = connect_.getContentLength();
            int index_ = 0;
            byte[] bytes_ = new byte[len_];
            while (true) {
                int read_ = buff_.read(bytes_, index_, len_ - index_);
                if (read_ == -1) {
                    break;
                }
                if (index_ == len_) {
                    break;
                }
                index_ += read_;
            }
            return bytes_;
        } catch (IOException _0) {
            _0.printStackTrace();
            return null;
        } finally {
            try {
                if (buff_ != null) {
                    buff_.close();
                }
                if (inputStream_ != null) {
                    inputStream_.close();
                }
            } catch ( Exception _0) {
                _0.printStackTrace();
            }
        }
    }

    @Override
    public void dispose(GLAutoDrawable _drawable) {
        quitScene(_drawable.getGL().getGL2());
    }

    @Override
    public void display(GLAutoDrawable _drawable) {
    	renderScene(_drawable.getGL().getGL2());
    }

    @Override
    public void reshape(GLAutoDrawable _drawable, int _x, int _y, int _width,
            int _height) {
        initScene(_drawable.getGL().getGL2());
    }

    void deleteShaders(GL2 _gl) {
        _gl.glUseProgram(0);
        for (String k: verticesId.keySet()) {
            _gl.glDeleteShader(verticesId.get(k));
        }
        for (String k: fragmentsId.keySet()) {
            _gl.glDeleteShader(fragmentsId.get(k));
        }
        for (String k: programsId.keySet()) {
            String[] ids_ = k.split("//");
            int idPr_ = programsId.get(k);
            int vert_ = verticesId.get(ids_[0]);
            int frag_ = fragmentsId.get(ids_[1]);
            _gl.glDetachShader(idPr_, frag_);
            _gl.glDetachShader(idPr_, vert_);
            _gl.glDeleteProgram(idPr_);
            _gl.glDeleteShader(frag_);
            _gl.glDeleteShader(vert_);
        }
        verticesId.clear();
        fragmentsId.clear();
        programsId.clear();
    }

    void deleteShader(GL2 _gl, int _vert, int _frag) {
        // On arrête d'utiliser le programme shader
        _gl.glUseProgram(0);
        // Destruction des IDs des shaders
        _gl.glDeleteShader(_vert);
        _gl.glDeleteShader(_frag);
    }

    void deleteShader(GL2 _gl, int _vert, int _frag, int _prog) {
        // On arrête d'utiliser le programme shader
        _gl.glUseProgram(0);

        // Deliage des shaders au programme
        _gl.glDetachShader(_prog, _frag);
        _gl.glDetachShader(_prog, _vert);

        // Destruction du programme
        _gl.glDeleteProgram(_prog);

        // Destruction des IDs des shaders
        _gl.glDeleteShader(_vert);
        _gl.glDeleteShader(_frag);
    }

    

    int loadShader(GL2 _gl, String _vertexShader, String _fragShader) {
        String vertexSource_ = null;
        String fragmentSource_ = null;
        int[] programState_ = new int[]{0};

        // Création des IDs
        int vertexId_ = _gl.glCreateShader(GL2.GL_VERTEX_SHADER);
        int fragmentId_ = _gl.glCreateShader(GL2.GL_FRAGMENT_SHADER);

        // Lecture des fichiers
        // Certaines personnes aiment avoir le fichier du vertex shader avec l'extion .vert
        // et le fichier du fragement shader avec l'extension .frag
        vertexSource_ = MyShadersUtil.loadFile(_vertexShader);
        fragmentSource_ = MyShadersUtil.loadFile(_fragShader);

        if (vertexSource_ == null || fragmentSource_ == null) {
            // Ici, il faudrait faire en sorte que le programme s'arrête
            deleteShader(_gl, vertexId_, fragmentId_);    // Nettoyage
            return -1;
        }

        // Chargement des sources dans OpenGL
        _gl.glShaderSource(vertexId_, 1, new String[]{vertexSource_}, (int[])null, 0);
        _gl.glShaderSource(fragmentId_, 1, new String[]{fragmentSource_}, (int[])null, 0);

        // Compilation du vertex shader
        _gl.glCompileShader(vertexId_);
        _gl.glCompileShader(fragmentId_);

        // Vérification des erreurs
        if (!MyShadersUtil.checkShaderCompilation(_gl,vertexId_) || !MyShadersUtil.checkShaderCompilation(_gl,fragmentId_)) {
            deleteShader(_gl, vertexId_, fragmentId_);
            return -1;
        }

        // Creation de l'ID pour le programme
        int programId_ = _gl.glCreateProgram();

        // On attache les shader ensemble
        _gl.glAttachShader(programId_, vertexId_);
        _gl.glAttachShader(programId_, fragmentId_);

        // On peut enfin passer aux liage.
        _gl.glLinkProgram(programId_);
        _gl.glValidateProgram(programId_);

        // Et encore une fois on vérifie si tout se passe bien
        _gl.glGetProgramiv(programId_, GL2.GL_LINK_STATUS, programState_, 0);
        if ( programState_[0] == 0) {
            // On récupère la taille du log


            int[] logSize_ = new int[]{0};

            _gl.glGetProgramiv(programId_, GL2.GL_INFO_LOG_LENGTH, logSize_, 0);

            // On peut allouer la mémoire, une fois que l'on a la taille du log
            //            log = (GLchar*)malloc(logSize);
            byte[] log_ = new byte[logSize_[0]-1];

            // Et on récupère le log
            _gl.glGetProgramInfoLog(programId_, log_.length, null, 0, log_, 0);

            // On affiche
            System.out.println("Erreur lors du liage du shader:\n"+new String(log_));
            deleteShader(_gl,vertexId_, fragmentId_, programId_);
            return -1;
        }
        verticesId.put(_vertexShader, vertexId_);
        fragmentsId.put(_fragShader, fragmentId_);
        programsId.put(_vertexShader+"//"+_fragShader, programId_);
        return programId_;
    }

    void initScene(GL2 _gl) {

        // Perspective mode
        _gl.glMatrixMode(GL2.GL_PROJECTION);
        _gl.glLoadIdentity();

        glu.gluPerspective(45.0f,(float)640/(float)480,0.1f,100.0f);

        _gl.glMatrixMode(GL2.GL_MODELVIEW);

    }

    void renderScene(GL2 _gl) {

        _gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);
        _gl.glLoadIdentity();
        _gl.glClearColor(0.0f,0.5f,0.0f,1.0f);
        _gl.glFogf(GL2.GL_FOG_START, -1f);
        _gl.glFogf(GL2.GL_FOG_END, 10f);
//        gl_.glFogf(GL2.GL_FOG_MODE, GL2.GL_EXP);
        _gl.glFogf(GL2.GL_FOG_MODE, GL2.GL_LINEAR);
        _gl.glFogfv(GL2.GL_FOG_COLOR, Buffers.newDirectFloatBuffer(new float[]{0.5f, 0.5f, 0.5f, 1}));

        float ambientLight[] = {0.3f, 0.3f, 0.0f, 1.0f};
        _gl.glLightModelfv(GL2.GL_LIGHT_MODEL_AMBIENT, ambientLight, 0);

        float lightColor[] = {0.7f, 0.7f, 0.0f, 1.0f};
        int boxSise_ = 7;
        float lightPos[] = {-2 * boxSise_, boxSise_, 4 * boxSise_, 1.0f};
    	_gl.glLightfv(GL2.GL_LIGHT0, GL2.GL_DIFFUSE, lightColor, 0);
    	_gl.glLightfv(GL2.GL_LIGHT0, GL2.GL_POSITION, lightPos, 0);
        glu.gluLookAt(-2,5,-4,
        		0,0,0,
        		0,1,0);
//        glu.gluLookAt(-7,6,-6,
//                0,0,0,
//                0,1,0);

        _gl.glRotated(_rotationAngle_, 1, 1, 0);

//        int prog_ = programsId.get(SIMPLE_VERT+"//"+SIMPLE_FRAG);
        int prog_ = shaderOne;
        _gl.glUseProgram(prog_);
        attributeId = _gl.glGetAttribLocation(prog_, ATTRIBUTE_COLOUR);
        int errorState_ = _gl.glGetError();
        if ( attributeId == -1 || errorState_ != GL2.GL_NO_ERROR ) {
            throw new GLException("Erreur ("+errorState_+") lors de la récupération de l'id de la variable attribute 'couleur'"+attributeId+" \n");
        }

        _gl.glEnableVertexAttribArray(attributeId);
        errorState_ = _gl.glGetError();

        _gl.glVertexAttribPointer(attributeId,
                3,
                GL2.GL_FLOAT,
                true,
                0,
                Buffers.newDirectFloatBuffer(cubeColours));

        if ( errorState_ != GL2.GL_NO_ERROR ) {
        	throw new GLException("Erreur ("+errorState_+") lors du passage du tableau de valeur à la variable attribute 'couleur'\n");
        }
        _gl.glEnableClientState(GL2.GL_VERTEX_ARRAY);

        _gl.glVertexPointer(3, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(cubeVertices));
        _gl.glDrawElements(GL2.GL_QUADS, 24, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(cubeIndices));

        _gl.glDisableVertexAttribArray(attributeId);
        //            Other shader
//        prog_ = programsId.get(SIMPLE_VERT_BIS+"//"+SIMPLE_FRAG);
        _gl.glClearColor(0.5f,0.5f,0.5f,1.0f);
        prog_ = shaderTwo;
        _gl.glUseProgram(prog_);
        attributeId = _gl.glGetAttribLocation(prog_, ATTRIBUTE_COLOUR_2);
        errorState_ = _gl.glGetError();
        if ( attributeId == -1 || errorState_ != GL2.GL_NO_ERROR ) {
        	throw new GLException("Erreur ("+errorState_+") lors de la récupération de l'id de la variable attribute 'couleur2'\n");
        }
        _gl.glEnableVertexAttribArray(attributeId);
        errorState_ = _gl.glGetError();

        _gl.glVertexAttribPointer(attributeId,
                3,
                GL2.GL_FLOAT,
                true,
                0,
                Buffers.newDirectFloatBuffer(cubeColours));

        if ( errorState_ != GL2.GL_NO_ERROR ) {
        	throw new GLException("Erreur ("+errorState_+") lors du passage du tableau de valeur à la variable attribute 'couleur2'\n");
        }
        _gl.glVertexPointer(3, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(cubeVerticesBis));
        _gl.glDrawElements(GL2.GL_QUADS, 24, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(cubeIndices));
        _gl.glDisableVertexAttribArray(attributeId);

//        prog_ = programsId.get(QUAD_VERT+"//"+QUAD_FRAG);
        prog_ = shaderThree;
        _gl.glEnableClientState(GL2.GL_TEXTURE_COORD_ARRAY);
        _gl.glUseProgram(prog_);
        //When rendering an objectwith this program.
//        _gl.glActiveTexture(GL2.GL_TEXTURE0 + 0);
        _gl.glBindTexture(GL2.GL_TEXTURE_2D, txtId);
        GL3 glThree_ = _gl.getGL3();
        int[] samplerObj_ = new int[1];

//        //Texture unit 0 is for base images.
//
        _gl.glTexCoordPointer(1, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(quadVertices));
        _gl.glTexImage2D(GL2.GL_TEXTURE_2D, 0, txtData.getInternalFormat(), txtData.getWidth(), txtData.getHeight(), 0, txtData.getPixelFormat(), GL2.GL_UNSIGNED_BYTE, txtData.getBuffer());
        _gl.glGenerateMipmap(GL2.GL_TEXTURE_2D);
        glThree_.glGenSamplers(1, samplerObj_, 0);
        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_MAG_FILTER, GL2.GL_LINEAR);
        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_MIN_FILTER, GL2.GL_LINEAR_MIPMAP_NEAREST);
        int index_ = 0;
        _gl.glActiveTexture(GL2.GL_TEXTURE0 + index_);
        _gl.glBindTexture(GL2.GL_TEXTURE_2D, txtId);
        glThree_.glBindSampler(index_, samplerObj_[0]);
        attributeId = _gl.glGetUniformLocation(prog_, UNIFORM_TEXTURE);
        _gl.glUniform1i(attributeId, index_);
        _gl.glDrawElements(GL2.GL_QUADS, 4, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(quadIndices));
        _gl.glBindTexture(GL2.GL_TEXTURE_2D,0);
        glThree_.glDeleteSamplers(1, samplerObj_, 0);

        _rotationAngle_++;
    }

    void quitScene(GL2 _gl) {
         _gl.glDisableClientState(GL2.GL_VERTEX_ARRAY);

        deleteShaders(_gl);
    }
    
}
