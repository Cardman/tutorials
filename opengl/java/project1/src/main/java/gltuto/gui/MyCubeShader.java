package gltuto.gui;

import java.awt.BorderLayout;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;
import java.util.HashMap;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;
//import com.sun.opengl.util.BufferUtil;

import com.jogamp.common.nio.Buffers;
import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GL3;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.GLEventListener;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.glu.GLU;
import com.jogamp.opengl.util.Animator;
import com.jogamp.opengl.util.texture.TextureData;
import com.jogamp.opengl.util.texture.TextureIO;

public final class MyCubeShader extends GLCanvas implements Runnable, GLEventListener {

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


    private float quadColours[] =
    {
        1, 0, 0, 1,
        0, 0, 1, 1,
        0, 0, 1, 1,
        1, 0, 0, 1,
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

    private int attributeId;

//    private Texture txt;
    private TextureData txtData;
    private int txtId;
    private GLU glu = new GLU();
    private final Animator animator = new Animator(this);
//    private BufferedImage img;
//	private ByteBuffer imageBuffer;

    //    private GLUT glut = new GLUT();

    public MyCubeShader() {
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
//            inputStream_ = ClassLoader.getSystemResourceAsStream("resources_gl/avatar.jpg");
//            txt = TextureIO.newTexture(inputStream_, true, TextureIO.JPG);
//            txtId = txt.getTextureObject();
            inputStream_ = ClassLoader.getSystemResourceAsStream("resources_gl/avatar.jpg");
            txtData = TextureIO.newTextureData(gl_.getGLProfile(), inputStream_, true, TextureIO.JPG);
            txtId = loadTextureBis(gl_, txtData);
//            byte[] data_ = resourceFile("resources_gl/avatar.jpg");
//            ByteArrayInputStream bis_ = new ByteArrayInputStream(data_);
//            img = ImageIO.read(bis_);
//            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
//            ImageIO.write(img, "jpg", byteArrayOutputStream);
//            byte[] imageData = byteArrayOutputStream.toByteArray();
//            imageBuffer = ByteBuffer.wrap(imageData);
            //gl_.glBindTexture(GL2.GL_TEXTURE_2D,txtId);
        //            gl.glBindTexture(GL2.GL_TEXTURE_2D, txt.getTextureObject());
        } catch (Exception _0) {
            _0.printStackTrace();
        }
//        imageBuffer.rewind();
        loadShader(gl_,SIMPLE_VERT,SIMPLE_FRAG);
        loadShader(gl_,SIMPLE_VERT_BIS,SIMPLE_FRAG);
        loadShader(gl_,QUAD_VERT,QUAD_FRAG);
        gl_.glEnable(GL2.GL_FOG);
//        gl_.glFogf(GL2.GL_FOG_DENSITY, 0.5f);
        gl_.glFogf(GL2.GL_FOG_MODE, GL2.GL_EXP);
        gl_.glFogfv(GL2.GL_FOG_COLOR, Buffers.newDirectFloatBuffer(new float[]{0.5f, 0.5f, 0.5f, 1}));
        gl_.glFogf(GL2.GL_FOG_START, 1.f);
        gl_.glFogf(GL2.GL_FOG_END, 40.f);
        //        initScene(_drawable.getGL().getGL2());
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
//        int vert_ = verticesId.get(_vert);
//        int frag_ = fragmentsId.get(_frag);
//        int prog_ = programsId.get(_vert+"//"+_frag);
//
//        // Deliage des shaders au programme
//        _gl.glDetachShader(prog_, _frag);
//        _gl.glDetachShader(prog_, _vert);
//
//        // Destruction du programme
//        _gl.glDeleteProgram(prog_);

        // Destruction des IDs des shaders
        _gl.glDeleteShader(_vert);
        _gl.glDeleteShader(_frag);
    }

    void deleteShader(GL2 _gl, int _vert, int _frag, int _prog) {
        // On arrête d'utiliser le programme shader
        _gl.glUseProgram(0);
//        int vert_ = verticesId.get(_vert);
//        int frag_ = fragmentsId.get(_frag);
//        int prog_ = programsId.get(_vert+"//"+_frag);
//
//        // Deliage des shaders au programme
        _gl.glDetachShader(_prog, _frag);
        _gl.glDetachShader(_prog, _vert);

        // Destruction du programme
        _gl.glDeleteProgram(_prog);

        // Destruction des IDs des shaders
        _gl.glDeleteShader(_vert);
        _gl.glDeleteShader(_frag);
    }

    // Pour plus de simplicité, j'ajoute une fonction qui vérifie la compilation des shaders
    byte checkShaderCompilation(GL2 _gl, int _shaderID) {
        int[] compilationStatus_ = new int[]{0};

        // Verification de la compialtion pour le vertex shader
//        _gl.glGetShaderiv(vertexId, GL2.GL_COMPILE_STATUS, compilationStatus_, 0);
        _gl.glGetShaderiv(_shaderID, GL2.GL_COMPILE_STATUS, compilationStatus_, 0);
        if ( compilationStatus_[0] == 0) {
            // Nous savons que la compilation a échoué, donc nous devons savoir pourquoi
            // Nous devons récupéré la taille du log
            int[] logLength_ = new int[]{0};

            _gl.glGetShaderiv(_shaderID, GL2.GL_INFO_LOG_LENGTH, logLength_, 0);

            // Maintenant que nous avons la taille, nous pouvons alloué la mémoire suffisante pour ce log
            byte[] log_ = new byte[logLength_[0]-1];
            //            if ( log == NULL )
            //            {
            //                fprintf(stderr,"Erreur d'allocation de mémoire pour le log de la compilation du shader\n");
            //                return 0;
            //            }

            _gl.glGetShaderInfoLog(_shaderID, log_.length, null, 0, log_, 0);

            // On peut afficher le message
            System.out.println("Erreur de compilation:\n"+new String(log_));

            // Et on n'oublie pas de libéré la mémoire
            //            free(log);

            return 0;
        }

        return 1; // Pas d'erreur
    }

    void loadShader(GL2 _gl, String _vertexShader, String _fragShader) {
//        _gl.glEnable(GL2.GL_TEXTURE_2D);
//        try {
//            InputStream inputStream_ = null;
//            inputStream_ = ClassLoader.getSystemResourceAsStream("resources_gl/avatar.jpg");
//            txt = TextureIO.newTexture(inputStream_, true, TextureIO.JPG);
//            txtId = txt.getTextureObject();
//            //            _gl.glBindTexture(GL2.GL_TEXTURE_2D,txtId);
//            //            gl.glBindTexture(GL2.GL_TEXTURE_2D, txt.getTextureObject());
//        } catch (Exception _0) {
//            _0.printStackTrace();
//        }
        String vertexSource_ = null;
        String fragmentSource_ = null;
        int[] programState_ = new int[]{0};
        //        int vertexSize = 0;
        //        int fragmentSize = 0;
//        int errorState_ = GL2.GL_NO_ERROR;

        // Création des IDs
        int vertexId_ = _gl.glCreateShader(GL2.GL_VERTEX_SHADER);
        int fragmentId_ = _gl.glCreateShader(GL2.GL_FRAGMENT_SHADER);

        // Lecture des fichiers
        // Certaines personnes aiment avoir le fichier du vertex shader avec l'extion .vert
        // et le fichier du fragement shader avec l'extension .frag
        vertexSource_ = loadFile(_vertexShader);
        fragmentSource_ = loadFile(_fragShader);

        if (vertexSource_ == null || fragmentSource_ == null) {
            // Ici, il faudrait faire en sorte que le programme s'arrête
            deleteShader(_gl, vertexId_, fragmentId_);    // Nettoyage
            return;
        }

        // Chargement des sources dans OpenGL
        //        vertexSize = vertexSource.length();
        //        fragmentSize = fragmentSource.length();
        _gl.glShaderSource(vertexId_, 1, new String[]{vertexSource_}, (int[])null, 0);
        _gl.glShaderSource(fragmentId_, 1, new String[]{fragmentSource_}, (int[])null, 0);

        // Compilation du vertex shader
        _gl.glCompileShader(vertexId_);
        _gl.glCompileShader(fragmentId_);

        // Vérification des erreurs
        if ( checkShaderCompilation(_gl,vertexId_) == 0 || checkShaderCompilation(_gl,fragmentId_) == 0) {
            deleteShader(_gl, vertexId_, fragmentId_);
            return;
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
            //            GLchar* log = NULL;

            _gl.glGetProgramiv(programId_, GL2.GL_INFO_LOG_LENGTH, logSize_, 0);
            //            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logSize);

            // On peut allouer la mémoire, une fois que l'on a la taille du log
            //            log = (GLchar*)malloc(logSize);
            byte[] log_ = new byte[logSize_[0]-1];
            //            if ( log == NULL )
            //            {
            //                fprintf(stderr,"Erreur d'allocation de mémoire pour le log de la compilation du programme\n");
            //                deleteShader();
            //                return;
            //            }

            // Et on récupère le log
            _gl.glGetProgramInfoLog(programId_, log_.length, null, 0, log_, 0);
            //            glGetProgramInfoLog(programID, logSize, &logSize, log);

            // On affiche
            System.out.println("Erreur lors du liage du shader:\n"+new String(log_));
            //            fprintf(stderr,"Erreur lors du liage du shader:\n%s",log);

            //            free(log);
            deleteShader(_gl,vertexId_, fragmentId_, programId_);
            return;
        }
//        _gl.glUseProgram(programId);
        verticesId.put(_vertexShader, vertexId_);
        fragmentsId.put(_fragShader, fragmentId_);
        programsId.put(_vertexShader+"//"+_fragShader, programId_);

//        System.out.println(_gl.glGetUniformLocation(programId, "mytex"));
//        System.out.println(_gl.glGetError());
//        attributeId = _gl.glGetAttribLocation(programId, "couleur");
//        errorState_ = _gl.glGetError();
//        if ( attributeId == -1 || errorState_ != GL2.GL_NO_ERROR ) {
//            System.out.println("Erreur ("+errorState_+") lors de la récupération de l'id de la variable attribute 'couleur'\n");
//            //            fprintf(stderr,"Erreur (%d) lors de la récupération de l'id de la variable attribute 'couleur'\n",errorState);
//        }
//
//        // Voilà, nous sommes prêt
////        _gl.glUseProgram(programId);
////        int tex_ = _gl.glGetUniformLocation(programId, "mytex");
////        System.out.println(attributeId);
//        _gl.glEnableVertexAttribArray(attributeId);
//        errorState_ = _gl.glGetError();
//
//        _gl.glVertexAttribPointer(attributeId,
//                3,
//                GL2.GL_FLOAT,
//                true,
//                0,
//                Buffers.newDirectFloatBuffer(cubeColours));
//
//        if ( errorState_ != GL2.GL_NO_ERROR ) {
//            System.out.println("Erreur ("+errorState_+") lors du passage du tableau de valeur à la variable attribute 'couleur'\n");
//            //            fprintf(stderr,"Erreur (%d) lors du passage du tableau de valeur à la variable attribute 'couleur'\n",errorState);
//        }
    }

    void initScene(GL2 _gl) {
        //        _gl.glClearColor(0.0,0.5,0.0,1.0);

        // Depth
        //        _gl.glClearDepth(1.0);
        //        _gl.glDepthFunc(GL2.GL_LESS);
        //        _gl.glEnable(GL2.GL_DEPTH_TEST);

        // Perspective mode
        _gl.glMatrixMode(GL2.GL_PROJECTION);
//        _gl.glLoadIdentity();

        glu.gluPerspective(45.0f,(float)640/(float)480,0.1f,100.0f);

        _gl.glMatrixMode(GL2.GL_MODELVIEW);

//        loadShader(_gl);

        // Init the cube
        // Tell to OpenGL that we are using :
        //  - Vertices
        //  - Colours
//        _gl.glEnableClientState(GL2.GL_VERTEX_ARRAY);
        //glEnableClientState(GL_COLOR_ARRAY);

        // Assign our data to OpenGL
        //        Buffers.newDirectFloatBuffer(cubeVertices);
        //        _gl.glVertexPointer(3, GL2.GL_FLOAT, 0, cubeVertices);
//        _gl.glVertexPointer(3, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(cubeVertices));
        //glColorPointer(3, GL_FLOAT, 0, cubeColours);
    }

    void renderScene(GL2 _gl) {
        // Rotation stuff
        //        static unsigned int rotationAngle;

        _gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);
//        _gl.glFogf(GL2.GL_FOG_MODE, GL2.GL_LINEAR);
//        _gl.glFogf(GL2.GL_FOG_START, 1.f);
//        _gl.glFogf(GL2.GL_FOG_END, 40.f);
        _gl.glLoadIdentity();

        glu.gluLookAt(-2,5,-4,
                0,0,0,
                0,1,0);

        _gl.glRotated(_rotationAngle_, 1, 1, 0);

        // draw the cube
        //        _gl.glDrawElements(GL2.GL_QUADS, 24, GL2.GL_UNSIGNED_BYTE, cubeIndices);
        //        _gl.glBindTexture(GL2.GL_TEXTURE_2D,txtId);
//        int tex_ = _gl.glGetUniformLocation(programId, "tex");
//        System.out.println(tex_);
//        _gl.glUniform1i(tex_, 0);
//        _gl.glActiveTexture(GL2.GL_TEXTURE0);
//        _gl.glBindTexture(GL2.GL_TEXTURE_2D,txtId);
//        loadShader(_gl,SIMPLE_VERT,SIMPLE_FRAG);
        int prog_ = programsId.get(SIMPLE_VERT+"//"+SIMPLE_FRAG);
        _gl.glUseProgram(prog_);
        attributeId = _gl.glGetAttribLocation(prog_, "couleur");
        int errorState_ = _gl.glGetError();
        if ( attributeId == -1 || errorState_ != GL2.GL_NO_ERROR ) {
            System.out.println("Erreur ("+errorState_+") lors de la récupération de l'id de la variable attribute 'couleur'\n");
            //            fprintf(stderr,"Erreur (%d) lors de la récupération de l'id de la variable attribute 'couleur'\n",errorState);
        }

        // Voilà, nous sommes prêt
//        _gl.glUseProgram(programId);
//        int tex_ = _gl.glGetUniformLocation(programId, "mytex");
//        System.out.println(attributeId);
        _gl.glEnableVertexAttribArray(attributeId);
        errorState_ = _gl.glGetError();

        _gl.glVertexAttribPointer(attributeId,
                3,
                GL2.GL_FLOAT,
                true,
                0,
                Buffers.newDirectFloatBuffer(cubeColours));

        if ( errorState_ != GL2.GL_NO_ERROR ) {
            System.out.println("Erreur ("+errorState_+") lors du passage du tableau de valeur à la variable attribute 'couleur'\n");
            //            fprintf(stderr,"Erreur (%d) lors du passage du tableau de valeur à la variable attribute 'couleur'\n",errorState);
        }
        _gl.glEnableClientState(GL2.GL_VERTEX_ARRAY);
        //glEnableClientState(GL_COLOR_ARRAY);

        // Assign our data to OpenGL
        //        Buffers.newDirectFloatBuffer(cubeVertices);
        //        _gl.glVertexPointer(3, GL2.GL_FLOAT, 0, cubeVertices);
        _gl.glVertexPointer(3, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(cubeVertices));
        _gl.glDrawElements(GL2.GL_QUADS, 24, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(cubeIndices));

//        _gl.glUseProgram(0);
//        int vert_ = verticesId.get(SIMPLE_VERT);
//        int frag_ = fragmentsId.get(SIMPLE_FRAG);
//        deleteShader(_gl, vert_, frag_, prog_);
//        _gl.glDetachShader(prog_, frag_);
//        _gl.glDetachShader(prog_, vert_);

        _gl.glDisableVertexAttribArray(attributeId);
//        Other shader
        prog_ = programsId.get(SIMPLE_VERT_BIS+"//"+SIMPLE_FRAG);
        _gl.glUseProgram(prog_);
//        System.out.println(_gl.glGetError());
        attributeId = _gl.glGetAttribLocation(prog_, "couleur2");
        errorState_ = _gl.glGetError();
        if ( attributeId == -1 || errorState_ != GL2.GL_NO_ERROR ) {
            System.out.println("Erreur ("+errorState_+") lors de la récupération de l'id de la variable attribute 'couleur2'\n");
            //            fprintf(stderr,"Erreur (%d) lors de la récupération de l'id de la variable attribute 'couleur'\n",errorState);
        }
        _gl.glEnableVertexAttribArray(attributeId);
        errorState_ = _gl.glGetError();

//        System.out.println(attributeId);
        _gl.glVertexAttribPointer(attributeId,
                3,
                GL2.GL_FLOAT,
                true,
                0,
                Buffers.newDirectFloatBuffer(cubeColours));

        if ( errorState_ != GL2.GL_NO_ERROR ) {
            System.out.println("Erreur ("+errorState_+") lors du passage du tableau de valeur à la variable attribute 'couleur2'\n");
            //            fprintf(stderr,"Erreur (%d) lors du passage du tableau de valeur à la variable attribute 'couleur'\n",errorState);
        }
        _gl.glVertexPointer(3, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(cubeVerticesBis));
        _gl.glDrawElements(GL2.GL_QUADS, 24, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(cubeIndices));

        _gl.glDisableVertexAttribArray(attributeId);
        prog_ = programsId.get(QUAD_VERT+"//"+QUAD_FRAG);
        _gl.glEnableClientState(GL2.GL_TEXTURE_COORD_ARRAY);
        _gl.glEnableClientState(GL2.GL_COLOR_ARRAY);
        _gl.glUseProgram(prog_);
        //When rendering an objectwith this program.
        _gl.glActiveTexture(GL2.GL_TEXTURE0 + 0);
        _gl.glBindTexture(GL2.GL_TEXTURE_2D, txtId);
        attributeId = _gl.glGetUniformLocation(prog_, "mytex");
        GL3 glThree_ = _gl.getGL3();
        int[] samplerObj_ = new int[1];

        glThree_.glGenSamplers(1, samplerObj_, 0);
//        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_WRAP_S, GL2.GL_CLAMP_TO_EDGE);
//        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_WRAP_T, GL2.GL_CLAMP_TO_EDGE);
//        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_MAG_FILTER, GL2.GL_NEAREST);
//        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_MIN_FILTER, GL2.GL_NEAREST);
//        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_MAG_FILTER, GL2.GL_LINEAR_MIPMAP_LINEAR);
//        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_MIN_FILTER, GL2.GL_LINEAR_MIPMAP_LINEAR);
        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_MAG_FILTER, GL2.GL_LINEAR);
        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_MIN_FILTER, GL2.GL_LINEAR);
        glThree_.glBindSampler(0, samplerObj_[0]);
        _gl.glUniform1i(attributeId, 0); //Texture unit 0 is for base images.
//        attributeId = _gl.glGetUniformLocation(prog_, "mytex");
////        _gl.glEnableClientState(GL2.GL_VERTEX_TEXTURE);
////        int[] ids_ = new int[1];
////        _gl.glGenTextures(1, ids_, 0);
//        _gl.glTexParameteri(GL2.GL_TEXTURE_2D, GL2.GL_TEXTURE_MIN_FILTER, GL2.GL_NEAREST);
//        _gl.glUniform1i(normalMapLoc, 2); //Texture unit 2 is for normal maps.
//        _gl.glUniform1i(shadowMapLoc, 4); //Texture unit 4 is for shadow maps.

//        _gl.glBindSampler(0, linearFiltering);
//        _gl.glActiveTexture(GL_TEXTURE0 + 2);
//        _gl.glBindTexture(GL_TEXTURE_2D, object1NormalMap);
//        _gl.glBindSampler(2, linearFiltering); //Same filtering as before
//        _gl.glActiveTexture(GL_TEXTURE0 + 4);
//        _gl.glBindTexture(GL_TEXTURE_2D, shadowMap);
//        _gl.glBindSampler(4, depthComparison); //Special sampler for depth comparisons.

        
        
//        _gl.glProgramUniform1i(prog_, attributeId , 0);
//        _gl.glActiveTexture(GL2.GL_TEXTURE0);
//        _gl.glBindTexture(GL2.GL_TEXTURE_2D,txtId);
        _gl.glVertexPointer(3, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(quadVertices));
        _gl.glColorPointer(4, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(quadColours));
        _gl.glTexCoordPointer(2, GL2.GL_DOUBLE, 0, Buffers.newDirectDoubleBuffer(new double[]{0,0,1,0,1,1,0,1}));
//        _gl.glTexCoordPointer(1, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(quadVertices));
//        _gl.glTexImage2D(GL2.GL_TEXTURE_2D, 0, txtData.getInternalFormat(), txtData.getWidth(), txtData.getHeight(), 0, txtData.getPixelFormat(), GL2.GL_UNSIGNED_BYTE, txtData.getBuffer());
        _gl.glDrawElements(GL2.GL_QUADS, 4, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(quadIndices));
//        glThree_.glDeleteSamplers(1, samplerObj_, 0);
//        _gl.glUseProgram(0);
//        glThree_.glGenSamplers(1, samplerObj_, 0);
//        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_MAG_FILTER, GL2.GL_LINEAR);
//        glThree_.glSamplerParameteri(samplerObj_[0], GL2.GL_TEXTURE_MIN_FILTER, GL2.GL_LINEAR);
//        glThree_.glBindSampler(0, samplerObj_[0]);
//        _gl.glBindTexture(GL2.GL_TEXTURE_2D,0);
//        _gl.glBindTexture(GL2.GL_TEXTURE_2D, txtId);
        _gl.glTranslated(-4, 0, 0);
        _gl.glVertexPointer(3, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(quadVertices));
        _gl.glColorPointer(4, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(quadColours));
        _gl.glTexCoordPointer(2, GL2.GL_DOUBLE, 0, Buffers.newDirectDoubleBuffer(new double[]{0,0,1,0,1,1,0,1}));
//        _gl.glTexImage2D(GL2.GL_TEXTURE_2D, 0, txtData.getInternalFormat(), txtData.getWidth(), txtData.getHeight(), 0, txtData.getPixelFormat(), GL2.GL_UNSIGNED_BYTE, txtData.getBuffer());
        _gl.glDrawElements(GL2.GL_QUADS, 4, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(quadIndices));
//        glThree_.glDeleteSamplers(1, samplerObj_, 0);
        _gl.glDisableClientState(GL2.GL_COLOR_ARRAY);
        _gl.glDisableClientState(GL2.GL_TEXTURE_COORD_ARRAY);

        _gl.glBindTexture(GL2.GL_TEXTURE_2D,0);
        _gl.glUseProgram(0);

//        deleteShader(_gl);
//        System.out.println(prog_);
//        prog_ = programsId.get(QUAD_VERT+"//"+QUAD_FRAG);
////        System.out.println(prog_);
//        _gl.glUseProgram(prog_);
////        loadShader(_gl,"resources_gl/data/quad.vert","resources_gl/data/quad.frag");
////        _gl.glEnableClientState(GL2.GL_VERTEX_TEXTURE);
//        int tex_ = _gl.glGetUniformLocation(programId, "mytex");
////        System.out.println(tex_);
//        _gl.glProgramUniform1i(programId, tex_ , 0);
//        _gl.glActiveTexture(GL2.GL_TEXTURE0);
//////        System.out.println(txtId);
//        _gl.glBindTexture(GL2.GL_TEXTURE_2D,txtId);
////        /*
////        2,1,1,
////            0,1,1,
////            0,-1,1,
////            2,-1,1,*/
////        _gl.glVertexPointer(1, GL2.GL_FLOAT, 0, Buffers.newDirectFloatBuffer(quadVertices));
//        _gl.glTexCoordPointer(1, GL2.GL_FLOAT, 0, Buffers.newDirectByteBuffer(quadIndices));
////        _gl.glBegin(GL2.GL_QUADS);
////        _gl.glTexCoord2d(0,1);
//////        gl.glVertex3d(1,-1,1);
////        _gl.glVertex3d(2,1,1);
////        _gl.glTexCoord2d(0,0);
//////        gl.glVertex3d(1,-1,-1);
////        _gl.glVertex3d(0,1,1);
////        _gl.glTexCoord2d(1,0);
//////        gl.glVertex3d(-1,-1,-1);
////        _gl.glVertex3d(0,-1,1);
////        _gl.glTexCoord2d(1,1);
//////        gl.glVertex3d(-1,-1,1);
////        _gl.glVertex3d(2,-1,1);
////        _gl.glEnd();
//        _gl.glDrawElements(GL2.GL_QUADS, 4, GL2.GL_UNSIGNED_BYTE, Buffers.newDirectByteBuffer(quadIndices));
//        deleteShader(_gl);
//        _gl.glBindTexture(GL2.GL_TEXTURE_2D,0);
//        _gl.glActiveTexture(GL2.GL_TEXTURE0);
        //        if ( _gl.glGetError() != GL2.GL_NO_ERROR )
        //        {
        //            fprintf(stderr,"Error occur during drawing");
        //            return;
        //        }

        //        glut.glutSwapBuffers();

        _rotationAngle_++;
    }

    void quitScene(GL2 _gl) {
        _gl.glDisableVertexAttribArray(attributeId);
        //glDisableClientState(GL_COLOR_ARRAY);
        _gl.glDisableClientState(GL2.GL_VERTEX_ARRAY);

        deleteShaders(_gl);
    }
    /**
    Load a text file and return it as a String.
     */
    private String loadFile(String _filename) {
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

    public static void main(String[] _args) {
        SwingUtilities.invokeLater(new MyCubeShader());
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
