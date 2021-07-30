package myshadersbis;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import com.jogamp.opengl.GL2;

public final class MyShadersUtil {

	private MyShadersUtil() {
	}

	public static ShaderIds loadShader(GL2 _gl, String _vertexShader, String _fragShader) {
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
            return null;
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
            return null;
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

//            _gl.glGetShaderInfoLog
            // On peut allouer la mémoire, une fois que l'on a la taille du log
            //            log = (GLchar*)malloc(logSize);
//            System.out.println(logSize_[0]);
            byte[] log_ = new byte[logSize_[0]-1];

            // Et on récupère le log
            _gl.glGetProgramInfoLog(programId_, log_.length, null, 0, log_, 0);

            // On affiche
            System.out.println("Erreur lors du liage du shader:\n"+new String(log_));
            deleteShader(_gl,vertexId_, fragmentId_, programId_);
            return null;
        }
        return new ShaderIds(vertexId_, fragmentId_, programId_);
    }

	public static String getError(GL2 _gl, int _pr) {
		int[] logSize_ = new int[]{0};

        _gl.glGetProgramiv(_pr, GL2.GL_INFO_LOG_LENGTH, logSize_, 0);

        // On peut allouer la mémoire, une fois que l'on a la taille du log
        //            log = (GLchar*)malloc(logSize);
        byte[] log_ = new byte[logSize_[0]-1];

        // Et on récupère le log
        _gl.glGetProgramInfoLog(_pr, log_.length, null, 0, log_, 0);

        // On affiche
        return new String(log_);
	}

	public static void deleteShader(GL2 _gl, int _vert, int _frag) {
        // On arrête d'utiliser le programme shader
        _gl.glUseProgram(0);
        // Destruction des IDs des shaders
        _gl.glDeleteShader(_vert);
        _gl.glDeleteShader(_frag);
    }

	public static void deleteShader(GL2 _gl, int _vert, int _frag, int _prog) {
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

	// Pour plus de simplicité, j'ajoute une fonction qui vérifie la compilation des shaders
	public static boolean checkShaderCompilation(GL2 _gl, int _shaderID) {
        int[] compilationStatus_ = new int[]{0};

        // Verification de la compialtion pour le vertex shader
        _gl.glGetShaderiv(_shaderID, GL2.GL_COMPILE_STATUS, compilationStatus_, 0);
        if ( compilationStatus_[0] == 0) {
            // Nous savons que la compilation a échoué, donc nous devons savoir pourquoi
            // Nous devons récupéré la taille du log
            int[] logLength_ = new int[]{0};

            _gl.glGetShaderiv(_shaderID, GL2.GL_INFO_LOG_LENGTH, logLength_, 0);

            // Maintenant que nous avons la taille, nous pouvons alloué la mémoire suffisante pour ce log
            byte[] log_ = new byte[logLength_[0]-1];

            _gl.glGetShaderInfoLog(_shaderID, log_.length, null, 0, log_, 0);

            // On peut afficher le message
            System.out.println("Erreur de compilation:\n"+new String(log_));

            // Et on n'oublie pas de libéré la mémoire
            //            free(log);

            return false;
        }

        return true; // Pas d'erreur
    }

	/**
    Load a text file and return it as a String.
	 */
	public static String loadFile(String _filename) {
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
